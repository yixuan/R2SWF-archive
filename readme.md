This is an R package to convert images to a Flash file (SWF).

R2SWF depends on the following libraries:

- zlib         http://www.zlib.net/
- libpng       http://www.libpng.org/
- libming      http://www.libming.org/

However, the source code of the dependent libraries (with minor modifications) are included in the package, so you don't need to install them by yourself.

To install the package here:

```r
## For users: 
install.packages('devtools')
library(devtools)
install_github('R2SWF', 'yihui')
```

