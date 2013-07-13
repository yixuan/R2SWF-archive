swf <- function(file = "Rplots.swf", width = 7, height = 7, bg = "white",
                fg = "black", frameRate = 12)
{
    .Call("swfDevice", as.character(file),
          as.double(width), as.double(height),
          c(col2rgb(bg)), c(col2rgb(fg)),
          as.double(frameRate), .pkg.env, PACKAGE='R2SWF');
    invisible(NULL);
}
