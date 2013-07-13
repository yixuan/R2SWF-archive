.onLoad <- function(libname, pkgname) {
    library.dynam("R2SWF", pkgname, libname);
    .Call("swfInit", PACKAGE = "R2SWF");
    .add.default.fonts();
}

.onUnload <- function(libpath) {
    .clean.fonts();
    .C("Ming_collectGarbage", PACKAGE = "R2SWF");
    library.dynam.unload("R2SWF", libpath);
}

