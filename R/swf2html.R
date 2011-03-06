##' Embed the SWF file into an HTML page.
##'
##' @param swf.file the path of the SWF file
##' @param output the output path of the HTML file
##' @param width width of the Flash
##' @param height height of the Flash
##' @return the output path of the HTML file
##' @author Yihui Xie <\url{http://yihui.name}>
##' @export
##' @examples
##' output = dev2swf({
##'   for (i in 1:10) plot(runif(20), ylim = c(0, 1))
##' }, output = 'test.swf')
##' swf2html(output)
swf2html = function(swf.file, output, width = 480, height = 480) {
    if (missing(output)) output = paste(sub('\\.swf$', '', swf.file), '.html', sep = '')
    cat(sprintf('
<html>
<head>
  <title>%s</title>
</head>
<body>
<div align="center">
', paste('Flash Animation by R2SWF', packageVersion('R2SWF'))), file = output)
    cat(sprintf('<object style="width: %spx; height: %spx;" classid="clsid:d27cdb6e-ae6d-11cf-96b8-444553540000" width="%s" height="%s" codebase="http://download.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=6,0,40,0">
  <param name="src" value="%s" />
  <embed style="width: %spx; height: %spx;" type="application/x-shockwave-flash" width="%s" height="%s" src="%s"></embed>
</object>',
            width, height, width, height, swf.file,
            width, height, width, height, swf.file),
        file = output, append = TRUE)
    cat('
</div>
</body>
</html>
', file = output, append = TRUE)
    if (interactive()) try(browseURL(output), silent = TRUE)
    invisible(output)
}
