\name{dev2swf}
\alias{dev2swf}
\title{Convert R graphics to SWF using different graphics devices}
\usage{
dev2swf(expr, outdir = tempdir(), output = "movie.swf", 
    bgColor = "white", interval = 1, dev = "png", file.ext = "png", 
    img.name = "Rplot", ...)
}
\arguments{
  \item{expr}{an expression to generate a sequence of
  images}

  \item{outdir}{the output directory}

  \item{output}{the name of the output swf file}

  \item{bgColor}{background color of the output SWF file}

  \item{interval}{the time interval between animation
  frames}

  \item{dev}{the name of the graphics device to use (e.g.
  \code{'png'} or \code{'jpeg'})}

  \item{file.ext}{the file extension for the images}

  \item{img.name}{the file name of the images without the
  extension}

  \item{\dots}{other arguments to be passed to the graphics
  device}
}
\value{
  The path of the generated swf file if succeeded.
}
\description{
  Given an R expression that can produce a sequence of
  images, this function will record the images with the
  device provided (e.g. \code{\link[grDevices]{png}()} or
  \code{\link[grDevices]{jpeg}()}) and convert them to a
  Flash file.
}
\details{
  You can also use devices which are not in the
  \pkg{grDevices} package by setting the \code{dev}
  argument to the name of the function that opens a device,
  e.g. \code{\link[Cairo]{CairoPNG}()} in the \pkg{Cairo}
  package. Note that the \code{file.ext} argument should be
  set accordingly.
}
\examples{
output1 = dev2swf({
    for (i in 1:10) plot(runif(20), ylim = c(0, 1))
}, dev = "png", file.ext = "png", output = "movie-png.swf")
print(output1)

output2 = dev2swf({
    for (i in 1:10) plot(runif(20), ylim = c(0, 1))
}, dev = "jpeg", file.ext = "jpg", output = "movie-jpeg.swf")
print(output2)
}
\author{
  Yihui Xie <\url{http://yihui.name}>
}
