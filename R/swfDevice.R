#' SWF graphics device
#' 
#' This function opens a SWF device that produces Flash animation
#' in SWF format. Every time you call a high level plotting function
#' like \code{\link[graphics]{plot}()}, the movie will create a new
#' frame and draw following shapes on it.
#' 
#' @param file a character string giving the output SWF file
#' @param width the width of the device in inches
#' @param height the height of the device in inches
#' @param bg the background color of the SWF file
#' @param fg initial foreground color
#' @param frameRate how many frames to be played in 1 second
#' 
#' @export
#' 
#' @author Yixuan Qiu <\url{http://yixuan.cos.name/}>
#' 
#' @examples \dontrun{
#' ## A demonstration of K-means clustering, using animation package
#' if(require(animation)) {
#'     swf("kmeans.swf", frameRate = 1)
#'     kmeans.ani()
#'     dev.off()
#' }
#' }
swf <- function(file = "Rplots.swf", width = 7, height = 7, bg = "white",
                fg = "black", frameRate = 12)
{
    .Call("swfDevice", as.character(file),
          as.double(width), as.double(height),
          c(col2rgb(bg)), c(col2rgb(fg)),
          as.double(frameRate), .pkg.env, PACKAGE='R2SWF');
    invisible(NULL);
}
