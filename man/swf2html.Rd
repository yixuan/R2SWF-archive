\name{swf2html}
\alias{swf2html}
\title{Embed the SWF file into an HTML page}
\usage{
  swf2html(swf.file, output, width = 480, height = 480,
    fragment = FALSE)
}
\arguments{
  \item{swf.file}{the path of the SWF file}

  \item{output}{the output path of the HTML file; by
  default \file{foo.swf} produces \code{foo.html} if not
  specified (set \code{FALSE} so that no file will be
  written)}

  \item{width}{width of the Flash}

  \item{height}{height of the Flash}

  \item{fragment}{whether to produce an HTML fragment only}
}
\value{
  The HTML code as a character string.
}
\description{
  This function will generate an HTML file to display the
  Flash animation.
}
\examples{
output = dev2swf({
  for (i in 1:10) plot(runif(20), ylim = c(0, 1))
}, output = 'test.swf')
swf2html(output)
}
\author{
  Yihui Xie <\url{http://yihui.name}>
}

