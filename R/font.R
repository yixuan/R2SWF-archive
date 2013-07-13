.pkg.env = new.env();
.pkg.env$.font.list = list();

list.fonts = function()
{
    return(.pkg.env$.font.list);
}

# TODO: what if ftname is used already?
add.fonts = function(ftname,
                     regular,
                     bold = NULL,
                     italic = NULL,
                     bolditalic = NULL)
{
    # The maximum length for font family name is 200 bytes
    ftname = as.character(ftname);
    if(nchar(ftname, type = "bytes") > 200)
        stop("ftname is too long");
    
    if(!file.exists(regular))
        stop("'regular' font file does not exist");
    
    r = .Call("swfLoadFont", regular, PACKAGE = "R2SWF");
    
    # If other font faces are not specified, use the regular one
    if(is.null(bold))
    {
        b = r;
    } else {
        if(!file.exists(bold))
            stop("'bold' font file does not exist");
        b = .Call("swfLoadFont", bold, PACKAGE = "R2SWF");
    }
    
    if(is.null(italic))
    {
        i = r;
    } else {
        if(!file.exists(italic))
            stop("'italic' font file does not exist");
        i = .Call("swfLoadFont", italic, PACKAGE = "R2SWF");
    }
    
    if(is.null(bolditalic))
    {
        bi = r;
    } else {
        if(!file.exists(bolditalic))
            stop("'bolditalic' font file does not exist");
        bi = .Call("swfLoadFont", bolditalic, PACKAGE = "R2SWF");
    }
    
    lst = list.fonts();
    lst[[ftname]] = list(regular = r, bold = b,
                         italic = i, bolditalic = bi);
    .pkg.env$.font.list = lst;
    
    invisible(lst);
}

.add.default.fonts = function()
{
    packageStartupMessage("Loading fonts...");

    sans.r = system.file("fonts", "Lato-Reg.ttf", package = "R2SWF");
    sans.b = system.file("fonts", "Lato-Bol.ttf", package = "R2SWF");
    sans.i = system.file("fonts", "Lato-RegIta.ttf", package = "R2SWF");
    sans.bi = system.file("fonts", "Lato-BolIta.ttf", package = "R2SWF");
    
    serif.r = system.file("fonts", "VeraSerif.ttf", package = "R2SWF");
    serif.b = system.file("fonts", "VeraSerif-Bold.ttf", package = "R2SWF");
    serif.i = system.file("fonts", "DroidSerif-Italic.ttf", package = "R2SWF");
    serif.bi = system.file("fonts", "DroidSerif-BoldItalic.ttf", package = "R2SWF");
    
    mono.r = system.file("fonts", "VeraMono.ttf", package = "R2SWF");
    mono.b = system.file("fonts", "VeraMoBd.ttf", package = "R2SWF");
    mono.i = system.file("fonts", "VeraMoIt.ttf", package = "R2SWF");
    mono.bi = system.file("fonts", "VeraMoBI.ttf", package = "R2SWF");
    
    add.fonts("sans", sans.r, sans.b, sans.i, sans.bi);
    add.fonts("serif", serif.r, serif.b, serif.i, serif.bi);
    add.fonts("mono", mono.r, mono.b, mono.i, mono.bi);
    
    packageStartupMessage("Loading fonts finished");
    
    invisible(NULL);
}

.clean.fonts = function()
{
    lst = unique(unlist(.pkg.env$.font.list));
    for(i in seq_along(lst))
    {
        .Call("swfCleanFont", lst[[i]], PACKAGE = "swf");
    }
    .pkg.env$.font.list = list();
    invisible(NULL);
}
