##' Get the size of an image. This function returns the width and
##' height of an image. Supported formats are jpg/jpeg, png, gif and svg.
##' 
##' This function is mainly used internally to decide the width and height
##' of the SWF file according to the sizes of input images.
##'
##' For jpg/jpeg, png and gif formats, the function returns the image
##' size in pixels. For svg file, width is always set to 640 px and height
##' is adjusted according to the width/height ratio. If the image size
##' could not be determined, then default values (640x640, in pixels) are used.
##'
##' @param filename the path of the image file.
##' @return A list containing the width and height of the image.
##' @author Yixuan Qiu \email{yixuan.qiu@@cos.name}
##' @export
##' @examples get.image.size(normalizePath(file.path(R.home("doc"),"html/logo.jpg")))
get.image.size <- function(filename)
{
	tmp = rawToChar(readBin(filename[1], "raw", 5))
	if(tmp == "<?xml")
	{
		tmp = readLines(filename[1], n = 20)
		svgfile = grep("<svg ", tmp, value = TRUE)
		if(length(svgfile))
		{
			svg.attrs = unlist(strsplit(svgfile[1], " "))
			svg.width = grep("^width=", svg.attrs, value = TRUE)
			svg.height = grep("^height=", svg.attrs, value = TRUE)
			svg.width = as.numeric(gsub("[^0-9\\.]", "", svg.width))
			svg.height = as.numeric(gsub("[^0-9\\.]", "", svg.height))
			width = 640
			height = ceiling(width * svg.height / svg.width)
			return(list(width = width, height = height))
		}else{
			stop("File format not supported.")
		}
	}else{
		size = .C("getImageSize", filename[1], 0L, 0L, PACKAGE = "R2SWF")
		return(list(width = size[[2]], height = size[[3]]))
	}
}

##' Convert a sequence of images to SWF file.
##' Given the file names of a sequence of images, this function can
##' convert them to a Flash file. Supported input formats are jpg/jpeg,
##' png, tiff and svg.
##' 
##' This function creates a temporary XML file and then calls the swfmill
##' programme(http://swfmill.org/) to implement the conversion. Currently
##' the support of SVG file is not perfected yet.
##'
##' @param filenames the file names of the images to be converted.
##' @param output the name of the output swf file.
##' @param interval the time interval between animation frames.
##' @return The path of the generated swf file if successful, or NULL is returned.
##' @author Yixuan Qiu \email{yixuan.qiu@@cos.name}
##' @export
##' @examples \dontrun{
##' png("Rplot\%03d.png")
##' for(i in 1:9) plot(runif(20), ylim = c(0, 1))
##' dev.off()
##' image2swf(paste("Rplot00", 1:9, ".png", sep = ""))
##' }
image2swf <- function(filenames, output = "movie.swf", interval = 1)
{
	size = get.image.size(filenames[1])
	tempxml = "temp.xml"
	sink(tempxml)
	cat("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n")
	cat(sprintf("<movie width=\"%d\" height=\"%d\" framerate=\"%d\">\n",
			size$width, size$height, ceiling(1/interval)))
	cat("<background color=\"#ffffff\"/>\n")
	create.frame <- function(filename, index)
	{
		cat("<frame>\n")
		cat(sprintf("<clip id=\"image%d\" import=\"%s\"/>\n", index, filename))
		cat(sprintf("<place id=\"image%d\" depth=\"2\"/>\n", index))
		cat("</frame>\n")
	}
	mapply(create.frame, filenames, 1:length(filenames))
	cat("</movie>")
	sink()

    flag = .C("R_xml2swf", 2L, c(tempxml, output), 1L, PACKAGE = "R2SWF")[[3]]
    if(!flag)
	{
		message("\nFlash has been created at: ", normalizePath(output))
		invisible(normalizePath(output))
	}else{
		message("\nError occurs when converting!")
		invisible(NULL)
	}
}

##' Convert R graphics to SWF using PNG device.
##' Given an R expression that can produce a sequence of images, this
##' function can record the images with the
##' \code{\link[grDevices]{png}()} device and convert them to a Flash
##' file.
##' 
##' You can use another PNG device instead of the default
##' \code{\link[grDevices]{png}()} by setting the \code{dev} argument
##' to the name of the function that opens a PNG device, e.g. \link[Cairo]{CairoPNG} 
##' in the \pkg{Cairo} package.
##'
##' @param expr an expression to generate a sequence of images.
##' @param interval the time interval between animation frames.
##' @param output the name of the output swf file.
##' @param dev the name of the graphics device to use (should be a PNG device but
##' not limited to the \link[grDevices]{png} device in the
##' \pkg{grDevice} package).
##' @param img.name the file name of the png images.
##' @param ... other arguments to be passed to the graphics device.
##' @return The path of the generated swf file if successful, or NULL is returned.
##' @author Yixuan Qiu \email{yixuan.qiu@@cos.name}
##' @export
##' @examples png2swf({
##'   for(i in 1:10) plot(runif(20), ylim = c(0, 1))
##' })
png2swf <- function(expr, interval = 1, output = "movie.swf",
    dev = "png", img.name = "Rplot", ...)
{
    if (is.character(dev)) dev = get(dev)
	olddir = setwd(tempdir())
    dev(paste(img.name, "%d.", "png", sep = ""), ...)
    eval(expr)
    dev.off()

    png.files = list.files(pattern = paste(img.name, "[0-9]*\\.png$", sep = ''))
    output = image2swf(png.files, output, interval)
    
    setwd(olddir)
	invisible(output)
}

##' Convert R graphics to SWF using JPEG device.
##' Given an R expression that can produce a sequence of images, this
##' function can record the images with the
##' \code{\link[grDevices]{jpeg}()} device and convert them to a Flash
##' file.
##' 
##' You can use another JPEG device instead of the default
##' \code{\link[grDevices]{jpeg}()} by setting the \code{dev} argument
##' to the name of the function that opens a JPEG device, e.g. \link[Cairo]{CairoJPEG} 
##' in the \pkg{Cairo} package.
##'
##' @param expr an expression to generate a sequence of images.
##' @param interval the time interval between animation frames.
##' @param output the name of the output swf file.
##' @param dev the name of the graphics device to use (should be a JPEG device but
##' not limited to the \link[grDevices]{jpeg} device in the
##' \pkg{grDevice} package).
##' @param img.name the file name of the png images.
##' @param ... other arguments to be passed to the graphics device.
##' @return The path of the generated swf file if successful, or NULL is returned.
##' @author Yixuan Qiu \email{yixuan.qiu@@cos.name}
##' @export
##' @examples jpeg2swf({
##'   for(i in 1:10) plot(runif(20), ylim = c(0, 1))
##' })
jpeg2swf <- function(expr, interval = 1, output = "movie.swf",
    dev = "jpeg", img.name = "Rplot", ...)
{
    if (is.character(dev)) dev = get(dev)
	olddir = setwd(tempdir())
    dev(paste(img.name, "%d.", "jpeg", sep = ""), ...)
    eval(expr)
    dev.off()

    jpeg.files = list.files(pattern = paste(img.name, "[0-9]*\\.jpeg$", sep = ''))
    output = image2swf(jpeg.files, output, interval)
    
    setwd(olddir)
	invisible(output)
}

