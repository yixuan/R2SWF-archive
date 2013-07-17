\name{swf}
\alias{swf}
\title{SWF graphics device}
\usage{
  swf(file = "Rplots.swf", width = 7, height = 7,
    bg = "white", fg = "black", frameRate = 12)
}
\arguments{
  \item{file}{a character string giving the output SWF
  file}

  \item{width}{the width of the device in inches}

  \item{height}{the height of the device in inches}

  \item{bg}{the background color of the SWF file}

  \item{fg}{initial foreground color}

  \item{frameRate}{how many frames to be played in 1
  second}
}
\description{
  This function opens a SWF device that produces Flash
  animation in SWF format. Every time you call a high level
  plotting function like \code{\link[graphics]{plot}()},
  the movie will create a new frame and draw following
  shapes on it.
}
\examples{
\dontrun{
## A demonstration of K-means clustering, using animation package
if(require(animation)) {
    swf("kmeans.swf", frameRate = 1)
    kmeans.ani()
    dev.off()
}
}
}
\author{
  Yixuan Qiu <\url{http://yixuan.cos.name/}>
}

