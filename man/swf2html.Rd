\name{swf2html}
\alias{swf2html}
\title{Embed the SWF file into an HTML page}
\usage{
swf2html(swf.file, output, width = 480, height = 480)
}
\arguments{
  \item{swf.file}{the path of the SWF file}

  \item{output}{the output path of the HTML file}

  \item{width}{width of the Flash}

  \item{height}{height of the Flash}
}
\value{
  The output path of the HTML file.
}
\description{
  This function will generate an HTML file to display the
  Flash animation.
}
\examples{
output = dev2swf({
    for (i in 1:10) plot(runif(20), ylim = c(0, 1))
}, output = "test.swf")
swf2html(output)
}
\author{
  Yihui Xie <\url{http://yihui.name}>
}
