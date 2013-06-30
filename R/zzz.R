.onLoad <- function(lib, pkg) {
  library.dynam("R2SWF", pkg, lib)
  .Call("swfInit", PACKAGE = "R2SWF");
}
