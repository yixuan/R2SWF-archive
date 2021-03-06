\name{file2swf}
\alias{file2swf}
\title{Convert image files to SWF}
\usage{
  file2swf(files, output, bgColor = "white", interval = 1)
}
\arguments{
  \item{files}{a character vector of input filenames}

  \item{output}{the name of the output swf file}

  \item{bgColor}{background color of the output SWF file}

  \item{interval}{the time interval between animation
  frames}
}
\value{
  The name of the SWF file.
}
\description{
  This function converts a sequence of PNG/JPEG/SVG image
  files to SWF. Based on the image format, it calls
  \code{\link{image2swf}} or \code{\link{svg2swf}}.
}
\author{
  Yihui Xie <\url{http://yihui.name}>
}

