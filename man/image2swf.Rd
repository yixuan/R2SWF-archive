\name{image2swf}
\alias{image2swf}
\title{Convert a sequence of images to a SWF file}
\usage{
image2swf(input, output = "./movie.swf", bgColor = "white", 
    interval = 1)
}
\arguments{
  \item{input}{the file names of the images to be
  converted}

  \item{output}{the name of the output SWF file}

  \item{bgColor}{background color of the output SWF file}

  \item{interval}{the time interval (in seconds) between
  animation frames}
}
\value{
  The path of the generated swf file if successful, or NULL
  is returned.
}
\description{
  Given the file names of a sequence of images, this
  function can convert them into a Flash file (.swf).
  Supported input formats are jpg/jpeg and png. The two
  formats are allowed to appear in the same sequence.
}
\details{
  This function uses the Ming library
  (\url{http://www.libming.org/}) to implement the
  conversion. If you want to create a Flash file consisting
  of vector graphics, use \code{\link{svg2swf}()} instead.
}
\examples{
if (capabilities("png")) {
    olddir = setwd(tempdir())
    png("Rplot\%03d.png")
    for (i in 1:9) plot(runif(20), ylim = c(0, 1))
    dev.off()
    output = image2swf(sprintf("Rplot\%03d.png", 1:9))
    print(output)
    setwd(olddir)
}
}
\author{
  Yixuan Qiu <\email{yixuan.qiu@cos.name}>
}
