#include "swfText.h"

int outlineMoveTo(const FT_Vector* to, void* user)
{
    OutlineData *data = (OutlineData *) user;
    SWFShape shape = data->shape;
    double ratio_EM = data->ratio_EM;

    double dx = to->x * ratio_EM + data->deltax;
    double dy = -to->y * ratio_EM;

    SWFShape_movePenTo(shape, dx, dy);

    return 0;
}
int outlineLineTo(const FT_Vector* to, void* user)
{
    OutlineData *data = (OutlineData *) user;
    SWFShape shape = data->shape;
    double ratio_EM = data->ratio_EM;

    double dx = to->x * ratio_EM + data->deltax;
    double dy = -to->y * ratio_EM;

    SWFShape_drawLineTo(shape, dx, dy);

    return 0;
}
int outlineConicTo(const FT_Vector* control, const FT_Vector* to, void* user)
{
    OutlineData *data = (OutlineData *) user;
    SWFShape shape = data->shape;
    double ratio_EM = data->ratio_EM;

    double cx = control->x * ratio_EM + data->deltax;
    double cy = -control->y * ratio_EM;
    double ax = to->x * ratio_EM + data->deltax;
    double ay = -to->y * ratio_EM;

    SWFShape_drawCurveTo(shape, cx, cy, ax, ay);

    return 0;
}

int outlineCubicTo(const FT_Vector* control1, const FT_Vector* control2,
            const FT_Vector* to, void* user)
{
    FT_Vector midpnt;
    double cx, cy, ax, ay;
    OutlineData *data = (OutlineData *) user;
    SWFShape shape = data->shape;
    double ratio_EM = data->ratio_EM;

    /* This is handled by breaking the cubic into 2 conic segments */
    midpnt.x = (control1->x + control2->x) / 2;
    midpnt.y = (control1->y + control2->y) / 2;

    /* First half */
    cx = control1->x * ratio_EM + data->deltax;
    cy = -control1->y * ratio_EM;
    ax = midpnt.x * ratio_EM + data->deltax;
    ay = -midpnt.y * ratio_EM;
    SWFShape_drawCurveTo(shape, cx, cy, ax, ay);

    /* Second half */
    cx = control2->x * ratio_EM + data->deltax;
    cy = -control2->y * ratio_EM;
    ax = to->x * ratio_EM + data->deltax;
    ay = -to->y * ratio_EM;
    SWFShape_drawCurveTo(shape, cx, cy, ax, ay);
    return 0;
}

void SWFShape_addString(SWFShape shape, const wchar_t* str, size_t nchar,
                        double fontSize,
                        FT_Face face, FT_Outline_Funcs *funs)
{
    OutlineData data;
    FT_Outline outline;
    int i;
    
    data.shape = shape;
    data.ratio_EM = fontSize / face->units_per_EM;
    data.deltax = 0.0;

    for(i = 0; i < nchar; i++)
    {
        /* str should be Unicode */
        FT_Load_Char(face, str[i], FT_LOAD_NO_SCALE);
        outline = face->glyph->outline;
        FT_Outline_Decompose(&outline, funs, &data);
        /* After we draw a character, we move the pen right to a distance
        of the advance */
        /* See the picture in
        http://www.freetype.org/freetype2/docs/tutorial/step2.html */
        data.deltax += face->glyph->metrics.horiAdvance * data.ratio_EM;
    }
}
