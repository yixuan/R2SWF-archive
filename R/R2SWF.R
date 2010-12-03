##' Convert PNG files to SWF.
##' Given an R expression that can produce a sequence of images, this function can
##' convert these images to a Flash file.
##'
##' @param expr an expression to generate the animation
##' @param interval the time interval between animation frames
##' @param output the name of the output
##' @param dev the graphics device to use (should be a PNG device but
##' not limited to the \code{png()} in the \pkg{grDevice} package)
##' @param filename the file name of the png images
##' @param fmt the name format of the png images
##' @param tmpdir the temporary directory to save all the intermediate
##' png files
##' @param para the (base) graphics parameters to set
##' @param ... other arguments to be passed to the graphics device
##' @return NULL
##' @author Yixuan Qiu \email{yixuan.qiu@@cos.name}
##' @examples png2swf({
##'   for (i in 1:10) plot(runif(20), ylim = c(0, 1))
##' })
png2swf <- function(expr, interval = 1, output = "movie.swf",
    dev = "png", filename = "Rplot", fmt = "%03d",
    tmpdir = tempdir(), para = list(),
    ...) {
    if (is.character(dev)) dev = get(dev)
    dev(file.path(tmpdir, paste(filename, fmt, ".", "png", sep = "")), ...)
    par(para)
    eval(expr)
    dev.off()

    png.files = list.files(tmpdir, "\\.png$", full.names = TRUE)
    .C("png2swf", png.files, length(png.files), as.numeric(interval),
        output, PACKAGE = "R2SWF")
    message("\nFlash has been created at: ", normalizePath(output))
}
