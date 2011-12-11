##' Convert a sequence of images to a SWF file
##'
##' Given the file names of a sequence of images, this function can
##' convert them into a Flash file (.swf). Supported input formats are
##' jpg/jpeg and png. The two formats are allowed to appear in the same
##' sequence.
##'
##' This function uses the Ming library (\url{http://www.libming.org/}) to
##' implement the conversion. If you want to create a Flash file
##' consisting of vector graphics, use \code{\link{svg2swf}()} instead.
##'
##' @param input the file names of the images to be converted
##' @param output the name of the output SWF file
##' @param bgColor background color of the output SWF file
##' @param interval the time interval (in seconds) between animation frames
##' @return The path of the generated swf file if successful, or NULL is
##' returned.
##' @export
##' @author Yixuan Qiu <\email{yixuan.qiu@@cos.name}>
##' @examples if(capabilities("png")) {
##'   olddir = setwd(tempdir())
##'   png("Rplot%03d.png")
##'   for(i in 1:9) plot(runif(20), ylim = c(0, 1))
##'   dev.off()
##'   output = image2swf(sprintf("Rplot%03d.png", 1:9))
##'   print(output)
##'   setwd(olddir)
##' }
##'
image2swf <- function(input, output = "./movie.swf", bgColor = "white",
					  interval = 1)
{
    if(!inherits(input, "character")) 
        stop("'input' must be a character vector naming the input images");
	
	outDir = dirname(output);
	outFile = basename(output);
	bg = col2rgb(bgColor, alpha = FALSE);
	bg = as.integer(bg);

	# The formats of files. 1 for png, 2 for jpg/jpeg, and 0 for others.
	fmt = rep(0, length(input));
	fmt[grep("\\.[Pp][Nn][Gg]$", input)] = 1;
    fmt[grep("\\.[Jj][Pp][Ee]?[Gg]$", input)] = 2;
	
	oldwd = setwd(outDir);
    .Call("image2swf", as.character(input), as.integer(fmt),
	      as.character(output), bg, as.numeric(interval),
		  PACKAGE = "R2SWF");
	setwd(oldwd);

	output = normalizePath(output);
	cat("SWF file created at ", output, ".\n", sep = "");
	invisible(output);
}

##' Convert R graphics to SWF using different graphics devices
##'
##' Given an R expression that can produce a sequence of images, this
##' function will record the images with the device provided (e.g.
##' \code{\link[grDevices]{png}()} or \code{\link[grDevices]{jpeg}()})
##' and convert them to a Flash file.
##'
##' You can also use devices which are not in the \pkg{grDevices}
##' package by setting the \code{dev} argument to the name of the
##' function that opens a device, e.g. \code{\link[Cairo]{CairoPNG}()}
##' in the \pkg{Cairo} package. Note that the \code{file.ext}
##' argument should be set accordingly.
##'
##' @param expr an expression to generate a sequence of images
##' @param outdir the output directory
##' @param output the name of the output swf file
##' @param bgColor background color of the output SWF file
##' @param interval the time interval between animation frames
##' @param dev the name of the graphics device to use
##' (e.g. \code{'png'} or \code{'jpeg'})
##' @param file.ext the file extension for the images
##' @param img.name the file name of the images without the extension
##' @param \dots other arguments to be passed to the graphics device
##' @return The path of the generated swf file if succeeded.
##' @export
##' @author Yihui Xie <\url{http://yihui.name}>
##' @examples
##' output1 = dev2swf({
##'   for(i in 1:10) plot(runif(20), ylim = c(0, 1))
##' }, dev='png', file.ext='png', output='movie-png.swf')
##' print(output1)
##'
##' output2 = dev2swf({
##'   for(i in 1:10) plot(runif(20), ylim = c(0, 1))
##' }, dev='jpeg', file.ext='jpg', output='movie-jpeg.swf')
##' print(output2)
##'
dev2swf <- function(expr, outdir = tempdir(), output = "movie.swf",
					bgColor = "white", interval = 1, dev = "png",
					file.ext = "png", img.name = "Rplot", ...)
{
    if (is.character(dev)) dev = get(dev)

	tmp = sample(LETTERS, 10);
	tmp = paste(tmp, collapse = "");
    tmpfolder = file.path(tempdir(), tmp);
	dir.create(tmpfolder);

	olddir = setwd(tmpfolder)
    dev(paste(img.name, "%d.", file.ext, sep = ""), ...)
    eval(expr)
    dev.off()

    files = list.files(pattern = paste(img.name, "[0-9]*\\.", file.ext, '$', sep = ''))
	files = file.path(tmpfolder, files)
    output = image2swf(files, file.path(outdir, output), bgColor, interval)
	setwd(olddir)

    invisible(output)
}

