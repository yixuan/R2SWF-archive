##' Convert PNG files to SWF.
##' Given an R expression that can produce a sequence of images, this
##' function can record the images with the
##' \code{\link[grDevices]{png}()} device and convert them to a Flash
##' file.
##'
##' @param expr an expression to generate a sequence of images
##' @param interval the time interval between animation frames
##' @param output the name of the output
##' @param dev the graphics device to use (should be a PNG device but
##' not limited to the \code{\link[grDevices]{png}()} device in the
##' \pkg{grDevice} package)
##' @param img.name the file name of the png images
##' @param ... other arguments to be passed to the graphics device
##' @return NULL
##' @author Yixuan Qiu \email{yixuan.qiu@@cos.name}
##' @examples png2swf({
##'   for (i in 1:10) plot(runif(20), ylim = c(0, 1))
##' })
png2swf <- function(expr, interval = 1, output = "movie.swf",
    dev = "png", img.name = "Rplot", ...) {
    if (is.character(dev)) dev = get(dev)
    dev(file.path(tempdir(), paste(filename, "%d.", "png", sep = "")), ...)
    eval(expr)
    dev.off()

    png.files = list.files(tempdir(), paste(img.name, "[0-9]*\\.png$", sep = ''),
                           full.names = TRUE)
    .C("png2swf", png.files, length(png.files), as.numeric(interval),
        output, PACKAGE = "R2SWF")
    message("\nFlash has been created at: ", normalizePath(output))
}
