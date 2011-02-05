#include "SWF.h"
#include "base64.h"
#include <cstring>
#include <errno.h>
/* #include <iconv.h> */
namespace SWF {
xmlChar *toXmlChar(const Context *ctx, const char *from_str) {
	/*if (ctx->convertEncoding) {
		size_t len = strlen(from_str);
		iconv_t cd = iconv_open("UTF-8", ctx->swf_encoding);
		if (cd < 0) {
			fprintf(stderr, "iconv_open failed.\n");
			return xmlCharStrdup("");
		}
		size_t buf_size = (len + 1) * 2;
		char *dst;
		for (;;) {
			dst = new char[buf_size];
			size_t inbytesleft = len;
			size_t outbytesleft = buf_size - 1;
			char *pin = (char*)from_str;
			char *pout = dst;
			bool expandbuf = false;
			while (inbytesleft > 0) {
				size_t r = iconv(cd, &pin, &inbytesleft, &pout, &outbytesleft);
				if (r == (size_t)-1) {
					if (errno == E2BIG) {
						// buf_size shorten
						expandbuf = true;
					} else {
						//bad input charctor
						fprintf(stderr, "iconv failed: %s\n", from_str);
					}
					break;
				}
			}
			if (expandbuf) {
				delete[] dst;
				iconv(cd, 0, 0, 0, 0);
				buf_size *= 2;
				continue;
			}
                        *pout = '\0';
			break;
		}
		iconv_close(cd);
		xmlChar *ret = xmlCharStrdup(dst);
		delete[] dst;
		return ret;
	} else {*/
		return xmlCharStrdup(from_str);
	/*}*/
}
#define TMP_STRLEN 0xFF
void Rectangle::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Rectangle", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", left);
	xmlSetProp( node, (const xmlChar *)"left", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", right);
	xmlSetProp( node, (const xmlChar *)"right", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", top);
	xmlSetProp( node, (const xmlChar *)"top", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", bottom);
	xmlSetProp( node, (const xmlChar *)"bottom", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", bits);
	xmlSetProp( node, (const xmlChar *)"bits", (const xmlChar *)&tmp );
	}
}
void Color::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Color", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", red);
	xmlSetProp( node, (const xmlChar *)"red", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", green);
	xmlSetProp( node, (const xmlChar *)"green", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", blue);
	xmlSetProp( node, (const xmlChar *)"blue", (const xmlChar *)&tmp );
	if( ctx->alpha ) {
	snprintf(tmp,TMP_STRLEN,"%i", alpha);
	xmlSetProp( node, (const xmlChar *)"alpha", (const xmlChar *)&tmp );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->alpha ) {
	snprintf(tmp,TMP_STRLEN,"%i", alpha);
	xmlSetProp( node, (const xmlChar *)"alpha", (const xmlChar *)&tmp );
	}
	}
}
void String::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"String", NULL );
	if( value ) {
		xmlChar *xmlstr = toXmlChar(ctx, value);
		xmlSetProp(node, (const xmlChar *)"value", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void String2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"String2", NULL );
	if( value ) {
		xmlChar *xmlstr = toXmlChar(ctx, value);
		xmlSetProp(node, (const xmlChar *)"value", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Transform::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Transform", NULL );
	if( scaled ) {
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, scaleX);
	xmlSetProp( node, (const xmlChar *)"scaleX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, scaleY);
	xmlSetProp( node, (const xmlChar *)"scaleY", (const xmlChar *)&tmp );
	}
	if( skewed ) {
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, skewX);
	xmlSetProp( node, (const xmlChar *)"skewX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, skewY);
	xmlSetProp( node, (const xmlChar *)"skewY", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", transX);
	xmlSetProp( node, (const xmlChar *)"transX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", transY);
	xmlSetProp( node, (const xmlChar *)"transY", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", scaled);
	xmlSetProp( node, (const xmlChar *)"scaled", (const xmlChar *)&tmp );
	if( scaled ) {
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, scaleX);
	xmlSetProp( node, (const xmlChar *)"scaleX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, scaleY);
	xmlSetProp( node, (const xmlChar *)"scaleY", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", skewed);
	xmlSetProp( node, (const xmlChar *)"skewed", (const xmlChar *)&tmp );
	if( skewed ) {
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, skewX);
	xmlSetProp( node, (const xmlChar *)"skewX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, skewY);
	xmlSetProp( node, (const xmlChar *)"skewY", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", bitsTranslate);
	xmlSetProp( node, (const xmlChar *)"bitsTranslate", (const xmlChar *)&tmp );
	}
}
void ColorTransform2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ColorTransform2", NULL );
	if( hasFactor ) {
	snprintf(tmp,TMP_STRLEN,"%i", factorRed);
	xmlSetProp( node, (const xmlChar *)"factorRed", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", factorGreen);
	xmlSetProp( node, (const xmlChar *)"factorGreen", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", factorBlue);
	xmlSetProp( node, (const xmlChar *)"factorBlue", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", factorAlpha);
	xmlSetProp( node, (const xmlChar *)"factorAlpha", (const xmlChar *)&tmp );
	}
	if( hasOffset ) {
	snprintf(tmp,TMP_STRLEN,"%i", offsetRed);
	xmlSetProp( node, (const xmlChar *)"offsetRed", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", offsetGreen);
	xmlSetProp( node, (const xmlChar *)"offsetGreen", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", offsetBlue);
	xmlSetProp( node, (const xmlChar *)"offsetBlue", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", offsetAlpha);
	xmlSetProp( node, (const xmlChar *)"offsetAlpha", (const xmlChar *)&tmp );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasOffset);
	xmlSetProp( node, (const xmlChar *)"hasOffset", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFactor);
	xmlSetProp( node, (const xmlChar *)"hasFactor", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", bits);
	xmlSetProp( node, (const xmlChar *)"bits", (const xmlChar *)&tmp );
	if( hasFactor ) {
	snprintf(tmp,TMP_STRLEN,"%i", factorRed);
	xmlSetProp( node, (const xmlChar *)"factorRed", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", factorGreen);
	xmlSetProp( node, (const xmlChar *)"factorGreen", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", factorBlue);
	xmlSetProp( node, (const xmlChar *)"factorBlue", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", factorAlpha);
	xmlSetProp( node, (const xmlChar *)"factorAlpha", (const xmlChar *)&tmp );
	}
	if( hasOffset ) {
	snprintf(tmp,TMP_STRLEN,"%i", offsetRed);
	xmlSetProp( node, (const xmlChar *)"offsetRed", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", offsetGreen);
	xmlSetProp( node, (const xmlChar *)"offsetGreen", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", offsetBlue);
	xmlSetProp( node, (const xmlChar *)"offsetBlue", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", offsetAlpha);
	xmlSetProp( node, (const xmlChar *)"offsetAlpha", (const xmlChar *)&tmp );
	}
	}
}
void Header::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Header", NULL );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"size", NULL );
	size.writeXML( node2, ctx );
	snprintf(tmp,TMP_STRLEN,"%i", framerate);
	xmlSetProp( node, (const xmlChar *)"framerate", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", frames);
	xmlSetProp( node, (const xmlChar *)"frames", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"tags", NULL );
		Tag *item;
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void LineStyle::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"LineStyle", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", width);
	xmlSetProp( node, (const xmlChar *)"width", (const xmlChar *)&tmp );
	if( ctx->tagVersion < 4 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( ctx->tagVersion > 3 ) {
	snprintf(tmp,TMP_STRLEN,"%i", startCapStyle);
	xmlSetProp( node, (const xmlChar *)"startCapStyle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", jointStyle);
	xmlSetProp( node, (const xmlChar *)"jointStyle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFill);
	xmlSetProp( node, (const xmlChar *)"hasFill", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", noHScale);
	xmlSetProp( node, (const xmlChar *)"noHScale", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", noVScale);
	xmlSetProp( node, (const xmlChar *)"noVScale", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pixelHinting);
	xmlSetProp( node, (const xmlChar *)"pixelHinting", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", noClose);
	xmlSetProp( node, (const xmlChar *)"noClose", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", endCapStyle);
	xmlSetProp( node, (const xmlChar *)"endCapStyle", (const xmlChar *)&tmp );
	if( jointStyle==2 ) {
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, miterLimitFactor);
	xmlSetProp( node, (const xmlChar *)"miterLimitFactor", (const xmlChar *)&tmp );
	}
	if( hasFill ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"fillStyles", NULL );
		Style *item;
		ListItem<Style>* i;
		i = fillStyles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !hasFill ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"fillColor", NULL );
	fillColor.writeXML( node2, ctx );
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->tagVersion < 4 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( ctx->tagVersion > 3 ) {
	snprintf(tmp,TMP_STRLEN,"%i", startCapStyle);
	xmlSetProp( node, (const xmlChar *)"startCapStyle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", jointStyle);
	xmlSetProp( node, (const xmlChar *)"jointStyle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFill);
	xmlSetProp( node, (const xmlChar *)"hasFill", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", noHScale);
	xmlSetProp( node, (const xmlChar *)"noHScale", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", noVScale);
	xmlSetProp( node, (const xmlChar *)"noVScale", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pixelHinting);
	xmlSetProp( node, (const xmlChar *)"pixelHinting", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", noClose);
	xmlSetProp( node, (const xmlChar *)"noClose", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", endCapStyle);
	xmlSetProp( node, (const xmlChar *)"endCapStyle", (const xmlChar *)&tmp );
	if( jointStyle==2 ) {
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, miterLimitFactor);
	xmlSetProp( node, (const xmlChar *)"miterLimitFactor", (const xmlChar *)&tmp );
	}
	if( hasFill ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"fillStyles", NULL );
		Style *item;
		ListItem<Style>* i;
		i = fillStyles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !hasFill ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"fillColor", NULL );
	fillColor.writeXML( node2, ctx );
	}
	}
	}
}
void StyleList::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StyleList", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"fillStyles", NULL );
		Style *item;
		ListItem<Style>* i;
		i = fillStyles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"lineStyles", NULL );
		LineStyle *item;
		ListItem<LineStyle>* i;
		i = lineStyles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", n_fillStyles);
	xmlSetProp( node, (const xmlChar *)"n_fillStyles", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", n_lineStyles);
	xmlSetProp( node, (const xmlChar *)"n_lineStyles", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", fillBits);
	xmlSetProp( node, (const xmlChar *)"fillBits", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", lineBits);
	xmlSetProp( node, (const xmlChar *)"lineBits", (const xmlChar *)&tmp );
	}
}
void ShapeSetup::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ShapeSetup", NULL );
	if( hasMoveTo ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFillStyle0 ) {
	snprintf(tmp,TMP_STRLEN,"%i", fillStyle0);
	xmlSetProp( node, (const xmlChar *)"fillStyle0", (const xmlChar *)&tmp );
	}
	if( hasFillStyle1 ) {
	snprintf(tmp,TMP_STRLEN,"%i", fillStyle1);
	xmlSetProp( node, (const xmlChar *)"fillStyle1", (const xmlChar *)&tmp );
	}
	if( hasLineStyle ) {
	snprintf(tmp,TMP_STRLEN,"%i", lineStyle);
	xmlSetProp( node, (const xmlChar *)"lineStyle", (const xmlChar *)&tmp );
	}
	if( hasNewStyles ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"styles", NULL );
	styles.writeXML( node2, ctx );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasNewStyles);
	xmlSetProp( node, (const xmlChar *)"hasNewStyles", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasLineStyle);
	xmlSetProp( node, (const xmlChar *)"hasLineStyle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFillStyle1);
	xmlSetProp( node, (const xmlChar *)"hasFillStyle1", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFillStyle0);
	xmlSetProp( node, (const xmlChar *)"hasFillStyle0", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMoveTo);
	xmlSetProp( node, (const xmlChar *)"hasMoveTo", (const xmlChar *)&tmp );
	if( hasMoveTo ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFillStyle0 ) {
	snprintf(tmp,TMP_STRLEN,"%i", fillStyle0);
	xmlSetProp( node, (const xmlChar *)"fillStyle0", (const xmlChar *)&tmp );
	}
	if( hasFillStyle1 ) {
	snprintf(tmp,TMP_STRLEN,"%i", fillStyle1);
	xmlSetProp( node, (const xmlChar *)"fillStyle1", (const xmlChar *)&tmp );
	}
	if( hasLineStyle ) {
	snprintf(tmp,TMP_STRLEN,"%i", lineStyle);
	xmlSetProp( node, (const xmlChar *)"lineStyle", (const xmlChar *)&tmp );
	}
	if( hasNewStyles ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"styles", NULL );
	styles.writeXML( node2, ctx );
	}
	}
}
void CurveTo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"CurveTo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", x1);
	xmlSetProp( node, (const xmlChar *)"x1", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", y1);
	xmlSetProp( node, (const xmlChar *)"y1", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", x2);
	xmlSetProp( node, (const xmlChar *)"x2", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", y2);
	xmlSetProp( node, (const xmlChar *)"y2", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", bits);
	xmlSetProp( node, (const xmlChar *)"bits", (const xmlChar *)&tmp );
	}
}
void Shape::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Shape", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"edges", NULL );
		ShapeItem *item;
		ListItem<ShapeItem>* i;
		i = edges.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GlyphShape::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GlyphShape", NULL );
	ctx->fillBits = 1;
	ctx->lineBits = 0;
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"edges", NULL );
		ShapeItem *item;
		ListItem<ShapeItem>* i;
		i = edges.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->fillBits = 1;
	ctx->lineBits = 0;
	snprintf(tmp,TMP_STRLEN,"%i", fillBits);
	xmlSetProp( node, (const xmlChar *)"fillBits", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", lineBits);
	xmlSetProp( node, (const xmlChar *)"lineBits", (const xmlChar *)&tmp );
	}
}
void GradientItem::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GradientItem", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", position);
	xmlSetProp( node, (const xmlChar *)"position", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Symbol::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Symbol", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Frame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Frame", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", number);
	xmlSetProp( node, (const xmlChar *)"number", (const xmlChar *)&tmp );
	if( label ) {
		xmlChar *xmlstr = toXmlChar(ctx, label);
		xmlSetProp(node, (const xmlChar *)"label", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Scene::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Scene", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", offset);
	xmlSetProp( node, (const xmlChar *)"offset", (const xmlChar *)&tmp );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Parameter::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Parameter", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", reg);
	xmlSetProp( node, (const xmlChar *)"reg", (const xmlChar *)&tmp );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void UChar::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"UChar", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void UShort::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"UShort", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ULong::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ULong", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Short::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Short", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Float::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Float", NULL );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Double::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Double", NULL );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Kerning::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Kerning", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", a);
	xmlSetProp( node, (const xmlChar *)"a", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", b);
	xmlSetProp( node, (const xmlChar *)"b", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", adjustment);
	xmlSetProp( node, (const xmlChar *)"adjustment", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void WideKerning::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"WideKerning", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", a);
	xmlSetProp( node, (const xmlChar *)"a", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", b);
	xmlSetProp( node, (const xmlChar *)"b", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", adjustment);
	xmlSetProp( node, (const xmlChar *)"adjustment", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void TextEntry::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextEntry", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", glyph);
	xmlSetProp( node, (const xmlChar *)"glyph", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", advance);
	xmlSetProp( node, (const xmlChar *)"advance", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void TextEntry2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextEntry2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", glyph);
	xmlSetProp( node, (const xmlChar *)"glyph", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", advance);
	xmlSetProp( node, (const xmlChar *)"advance", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void TextRecord6::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextRecord6", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", isSetup);
	xmlSetProp( node, (const xmlChar *)"isSetup", (const xmlChar *)&tmp );
	if( isSetup ) {
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	}
	if( !isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry *item;
		ListItem<TextEntry>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( isSetup ) {
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	}
	if( !isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry *item;
		ListItem<TextEntry>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void TextRecord62::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextRecord62", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", isSetup);
	xmlSetProp( node, (const xmlChar *)"isSetup", (const xmlChar *)&tmp );
	if( isSetup ) {
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	}
	if( !isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry2 *item;
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( isSetup ) {
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	}
	if( !isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry2 *item;
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void TextRecord7::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextRecord7", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", isSetup);
	xmlSetProp( node, (const xmlChar *)"isSetup", (const xmlChar *)&tmp );
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	if( isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry *item;
		ListItem<TextEntry>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFont);
	xmlSetProp( node, (const xmlChar *)"hasFont", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasColor);
	xmlSetProp( node, (const xmlChar *)"hasColor", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMoveY);
	xmlSetProp( node, (const xmlChar *)"hasMoveY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMoveX);
	xmlSetProp( node, (const xmlChar *)"hasMoveX", (const xmlChar *)&tmp );
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	if( isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry *item;
		ListItem<TextEntry>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void TextRecord72::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextRecord72", NULL );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", isSetup);
	xmlSetProp( node, (const xmlChar *)"isSetup", (const xmlChar *)&tmp );
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontRef);
	xmlSetProp( node, (const xmlChar *)"fontRef", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	if( isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry2 *item;
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFont);
	xmlSetProp( node, (const xmlChar *)"hasFont", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasColor);
	xmlSetProp( node, (const xmlChar *)"hasColor", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMoveY);
	xmlSetProp( node, (const xmlChar *)"hasMoveY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMoveX);
	xmlSetProp( node, (const xmlChar *)"hasMoveX", (const xmlChar *)&tmp );
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontRef);
	xmlSetProp( node, (const xmlChar *)"fontRef", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMoveX ) {
	snprintf(tmp,TMP_STRLEN,"%i", x);
	xmlSetProp( node, (const xmlChar *)"x", (const xmlChar *)&tmp );
	}
	if( hasMoveY ) {
	snprintf(tmp,TMP_STRLEN,"%i", y);
	xmlSetProp( node, (const xmlChar *)"y", (const xmlChar *)&tmp );
	}
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	if( isSetup ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
		TextEntry2 *item;
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void TextRecord::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextRecord", NULL );
	if( ctx->tagVersion < 2 ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"records", NULL );
		TextRecord6 *item;
		ListItem<TextRecord6>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->tagVersion >= 2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"string", NULL );
	string.writeXML( node2, ctx );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->tagVersion < 2 ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"records", NULL );
		TextRecord6 *item;
		ListItem<TextRecord6>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->tagVersion >= 2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"string", NULL );
	string.writeXML( node2, ctx );
	}
	}
}
void TextRecord2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TextRecord2", NULL );
	if( ctx->swfVersion < 7 ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"records", NULL );
		TextRecord62 *item;
		ListItem<TextRecord62>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->swfVersion >= 7 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"textString", NULL );
	textString.writeXML( node2, ctx );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->swfVersion < 7 ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"records", NULL );
		TextRecord62 *item;
		ListItem<TextRecord62>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->swfVersion >= 7 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"textString", NULL );
	textString.writeXML( node2, ctx );
	}
	}
}
void Button::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Button", NULL );
	if( ctx->swfVersion < 8 ) {
	}
	if( ctx->swfVersion >= 8 ) {
	}
	snprintf(tmp,TMP_STRLEN,"%i", hitTest);
	xmlSetProp( node, (const xmlChar *)"hitTest", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", down);
	xmlSetProp( node, (const xmlChar *)"down", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", over);
	xmlSetProp( node, (const xmlChar *)"over", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", up);
	xmlSetProp( node, (const xmlChar *)"up", (const xmlChar *)&tmp );
	if( hitTest || down || over || up ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", depth);
	xmlSetProp( node, (const xmlChar *)"depth", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	if( ctx->tagVersion >= 2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"colorTransform", NULL );
	colorTransform.writeXML( node2, ctx );
	}
	if( hasFilterList ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"filters", NULL );
		Filter *item;
		ListItem<Filter>* i;
		i = filters.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
	snprintf(tmp,TMP_STRLEN,"%i", blendMode);
	xmlSetProp( node, (const xmlChar *)"blendMode", (const xmlChar *)&tmp );
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved1);
	xmlSetProp( node, (const xmlChar *)"reserved1", (const xmlChar *)&tmp );
	if( ctx->swfVersion < 8 ) {
	}
	if( ctx->swfVersion >= 8 ) {
	}
	if( hitTest || down || over || up ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", depth);
	xmlSetProp( node, (const xmlChar *)"depth", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	if( ctx->tagVersion >= 2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"colorTransform", NULL );
	colorTransform.writeXML( node2, ctx );
	}
	if( hasFilterList ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"filters", NULL );
		Filter *item;
		ListItem<Filter>* i;
		i = filters.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
	snprintf(tmp,TMP_STRLEN,"%i", blendMode);
	xmlSetProp( node, (const xmlChar *)"blendMode", (const xmlChar *)&tmp );
	}
	}
	}
}
void Event::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Event", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", flags1);
	xmlSetProp( node, (const xmlChar *)"flags1", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", flags2);
	xmlSetProp( node, (const xmlChar *)"flags2", (const xmlChar *)&tmp );
	}
	if( (flags1 | flags2) ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", flags2);
	xmlSetProp( node, (const xmlChar *)"flags2", (const xmlChar *)&tmp );
	}
	if( (flags1 | flags2) ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void Condition::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Condition", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", next);
	xmlSetProp( node, (const xmlChar *)"next", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", menuEnter);
	xmlSetProp( node, (const xmlChar *)"menuEnter", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pointerReleaseOutside);
	xmlSetProp( node, (const xmlChar *)"pointerReleaseOutside", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pointerDragEnter);
	xmlSetProp( node, (const xmlChar *)"pointerDragEnter", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pointerDragLeave);
	xmlSetProp( node, (const xmlChar *)"pointerDragLeave", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pointerReleaseInside);
	xmlSetProp( node, (const xmlChar *)"pointerReleaseInside", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pointerPush);
	xmlSetProp( node, (const xmlChar *)"pointerPush", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pointerLeave);
	xmlSetProp( node, (const xmlChar *)"pointerLeave", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", pointerEnter);
	xmlSetProp( node, (const xmlChar *)"pointerEnter", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", key);
	xmlSetProp( node, (const xmlChar *)"key", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", menuLeave);
	xmlSetProp( node, (const xmlChar *)"menuLeave", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void U30::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"U30", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void S24::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"S24", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ValueKind::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ValueKind", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", kind);
	xmlSetProp( node, (const xmlChar *)"kind", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MethodInfo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MethodInfo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", retType);
	xmlSetProp( node, (const xmlChar *)"retType", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"paramTypes", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = paramTypes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasParamNames);
	xmlSetProp( node, (const xmlChar *)"hasParamNames", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", setSDXNs);
	xmlSetProp( node, (const xmlChar *)"setSDXNs", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isExplicit);
	xmlSetProp( node, (const xmlChar *)"isExplicit", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", ignoreRest);
	xmlSetProp( node, (const xmlChar *)"ignoreRest", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasOptional);
	xmlSetProp( node, (const xmlChar *)"hasOptional", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", needRest);
	xmlSetProp( node, (const xmlChar *)"needRest", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", needActivation);
	xmlSetProp( node, (const xmlChar *)"needActivation", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", needArguments);
	xmlSetProp( node, (const xmlChar *)"needArguments", (const xmlChar *)&tmp );
	if( hasOptional ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"optional", NULL );
		ValueKind *item;
		ListItem<ValueKind>* i;
		i = optional.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasParamNames ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"paramNames", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = paramNames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", paramCount);
	xmlSetProp( node, (const xmlChar *)"paramCount", (const xmlChar *)&tmp );
	if( hasOptional ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"optional", NULL );
		ValueKind *item;
		ListItem<ValueKind>* i;
		i = optional.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasParamNames ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"paramNames", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = paramNames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void MetadataInfo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MetadataInfo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"keys", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = keys.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"values", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = values.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", valuesCount);
	xmlSetProp( node, (const xmlChar *)"valuesCount", (const xmlChar *)&tmp );
	}
}
void NamespaceSet::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"NamespaceSet", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"namespaces", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void TraitInfo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TraitInfo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", override);
	xmlSetProp( node, (const xmlChar *)"override", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", final);
	xmlSetProp( node, (const xmlChar *)"final", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"trait", NULL );
		Trait *item;
		ListItem<Trait>* i;
		i = trait.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( hasMetadata ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"metadata", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMetadata);
	xmlSetProp( node, (const xmlChar *)"hasMetadata", (const xmlChar *)&tmp );
	if( hasMetadata ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"metadata", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void InstanceInfo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"InstanceInfo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", superIndex);
	xmlSetProp( node, (const xmlChar *)"superIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasProtectedNS);
	xmlSetProp( node, (const xmlChar *)"hasProtectedNS", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", interface);
	xmlSetProp( node, (const xmlChar *)"interface", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", final);
	xmlSetProp( node, (const xmlChar *)"final", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", sealed);
	xmlSetProp( node, (const xmlChar *)"sealed", (const xmlChar *)&tmp );
	if( hasProtectedNS ) {
	snprintf(tmp,TMP_STRLEN,"%i", protectedNS);
	xmlSetProp( node, (const xmlChar *)"protectedNS", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"interfaces", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = interfaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%i", iInitIndex);
	xmlSetProp( node, (const xmlChar *)"iInitIndex", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"traits", NULL );
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	if( hasProtectedNS ) {
	snprintf(tmp,TMP_STRLEN,"%i", protectedNS);
	xmlSetProp( node, (const xmlChar *)"protectedNS", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", interfaceCount);
	xmlSetProp( node, (const xmlChar *)"interfaceCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", traitCount);
	xmlSetProp( node, (const xmlChar *)"traitCount", (const xmlChar *)&tmp );
	}
}
void ClassInfo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ClassInfo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", cInitIndex);
	xmlSetProp( node, (const xmlChar *)"cInitIndex", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"traits", NULL );
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", traitCount);
	xmlSetProp( node, (const xmlChar *)"traitCount", (const xmlChar *)&tmp );
	}
}
void ScriptInfo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ScriptInfo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", initIndex);
	xmlSetProp( node, (const xmlChar *)"initIndex", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"traits", NULL );
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", traitCount);
	xmlSetProp( node, (const xmlChar *)"traitCount", (const xmlChar *)&tmp );
	}
}
void Exception::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Exception", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", tryStart);
	xmlSetProp( node, (const xmlChar *)"tryStart", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", tryEnd);
	xmlSetProp( node, (const xmlChar *)"tryEnd", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", type);
	xmlSetProp( node, (const xmlChar *)"type", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MethodBody::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MethodBody", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", methodInfo);
	xmlSetProp( node, (const xmlChar *)"methodInfo", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", maxStack);
	xmlSetProp( node, (const xmlChar *)"maxStack", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", maxRegs);
	xmlSetProp( node, (const xmlChar *)"maxRegs", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", scopeDepth);
	xmlSetProp( node, (const xmlChar *)"scopeDepth", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", maxScope);
	xmlSetProp( node, (const xmlChar *)"maxScope", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"code", NULL );
		OpCode *item;
		ListItem<OpCode>* i;
		i = code.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%i", exceptionCount);
	xmlSetProp( node, (const xmlChar *)"exceptionCount", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"exceptions", NULL );
		Exception *item;
		ListItem<Exception>* i;
		i = exceptions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"traits", NULL );
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", codeLength);
	xmlSetProp( node, (const xmlChar *)"codeLength", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", traitCount);
	xmlSetProp( node, (const xmlChar *)"traitCount", (const xmlChar *)&tmp );
	}
}
void Constants::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Constants", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"ints", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = ints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"uints", NULL );
		U30 *item;
		ListItem<U30>* i;
		i = uints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"doubles", NULL );
		Double *item;
		ListItem<Double>* i;
		i = doubles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"strings", NULL );
		String2 *item;
		ListItem<String2>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"namespaces", NULL );
		NamespaceConstant *item;
		ListItem<NamespaceConstant>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"namespaceSets", NULL );
		NamespaceSet *item;
		ListItem<NamespaceSet>* i;
		i = namespaceSets.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"multinames", NULL );
		MultinameConstant *item;
		ListItem<MultinameConstant>* i;
		i = multinames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", intCount);
	xmlSetProp( node, (const xmlChar *)"intCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", uintCount);
	xmlSetProp( node, (const xmlChar *)"uintCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", doubleCount);
	xmlSetProp( node, (const xmlChar *)"doubleCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", stringCount);
	xmlSetProp( node, (const xmlChar *)"stringCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", namespaceConstantCount);
	xmlSetProp( node, (const xmlChar *)"namespaceConstantCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", namespaceSetCount);
	xmlSetProp( node, (const xmlChar *)"namespaceSetCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", multinameConstantCount);
	xmlSetProp( node, (const xmlChar *)"multinameConstantCount", (const xmlChar *)&tmp );
	}
}
void Action3::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Action3", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", minorVersion);
	xmlSetProp( node, (const xmlChar *)"minorVersion", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", majorVersion);
	xmlSetProp( node, (const xmlChar *)"majorVersion", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"constants", NULL );
	constants.writeXML( node2, ctx );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"methods", NULL );
		MethodInfo *item;
		ListItem<MethodInfo>* i;
		i = methods.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"metadata", NULL );
		MetadataInfo *item;
		ListItem<MetadataInfo>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"instances", NULL );
		InstanceInfo *item;
		ListItem<InstanceInfo>* i;
		i = instances.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"classes", NULL );
		ClassInfo *item;
		ListItem<ClassInfo>* i;
		i = classes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"scripts", NULL );
		ScriptInfo *item;
		ListItem<ScriptInfo>* i;
		i = scripts.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"methodBodies", NULL );
		MethodBody *item;
		ListItem<MethodBody>* i;
		i = methodBodies.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", methodInfoCount);
	xmlSetProp( node, (const xmlChar *)"methodInfoCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", metadataInfoCount);
	xmlSetProp( node, (const xmlChar *)"metadataInfoCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", classCount);
	xmlSetProp( node, (const xmlChar *)"classCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", scriptCount);
	xmlSetProp( node, (const xmlChar *)"scriptCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", methodBodyCount);
	xmlSetProp( node, (const xmlChar *)"methodBodyCount", (const xmlChar *)&tmp );
	}
}
void ZoneData::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ZoneData", NULL );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, position);
	xmlSetProp( node, (const xmlChar *)"position", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, size);
	xmlSetProp( node, (const xmlChar *)"size", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ZoneArray::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ZoneArray", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"zones", NULL );
		ZoneData *item;
		ListItem<ZoneData>* i;
		i = zones.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%i", zoneX);
	xmlSetProp( node, (const xmlChar *)"zoneX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", zoneY);
	xmlSetProp( node, (const xmlChar *)"zoneY", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	}
}
void UnknownFilter::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"UnknownFilter", NULL );
	{
		if( len && data ) {
			char *tmp_data = (char *)data;
			int sz = len;
			char *tmpstr = new char[ (sz * 3) ];
			int l = base64_encode( tmpstr, tmp_data, sz );
			if( l > 0 ) {
				tmpstr[l] = 0;
				xmlNewTextChild( node, NULL, (const xmlChar *)"data", (const xmlChar *)tmpstr );
			}
			delete tmpstr;
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DropShadow::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DropShadow", NULL );
	ctx->alpha = 1;
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurX);
	xmlSetProp( node, (const xmlChar *)"blurX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurY);
	xmlSetProp( node, (const xmlChar *)"blurY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, angle);
	xmlSetProp( node, (const xmlChar *)"angle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, distance);
	xmlSetProp( node, (const xmlChar *)"distance", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, strength);
	xmlSetProp( node, (const xmlChar *)"strength", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", innerShadow);
	xmlSetProp( node, (const xmlChar *)"innerShadow", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", knockout);
	xmlSetProp( node, (const xmlChar *)"knockout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", passes);
	xmlSetProp( node, (const xmlChar *)"passes", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", compositeSource);
	xmlSetProp( node, (const xmlChar *)"compositeSource", (const xmlChar *)&tmp );
	}
}
void Blur::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Blur", NULL );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurX);
	xmlSetProp( node, (const xmlChar *)"blurX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurY);
	xmlSetProp( node, (const xmlChar *)"blurY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", passes);
	xmlSetProp( node, (const xmlChar *)"passes", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved1);
	xmlSetProp( node, (const xmlChar *)"reserved1", (const xmlChar *)&tmp );
	}
}
void Glow::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Glow", NULL );
	ctx->alpha = 1;
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurX);
	xmlSetProp( node, (const xmlChar *)"blurX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurY);
	xmlSetProp( node, (const xmlChar *)"blurY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, strength);
	xmlSetProp( node, (const xmlChar *)"strength", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", innerGlow);
	xmlSetProp( node, (const xmlChar *)"innerGlow", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", knockout);
	xmlSetProp( node, (const xmlChar *)"knockout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", passes);
	xmlSetProp( node, (const xmlChar *)"passes", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", compositeSource);
	xmlSetProp( node, (const xmlChar *)"compositeSource", (const xmlChar *)&tmp );
	}
}
void Bevel::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Bevel", NULL );
	ctx->alpha = 1;
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"shadowColor", NULL );
	shadowColor.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"highlightColor", NULL );
	highlightColor.writeXML( node2, ctx );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurX);
	xmlSetProp( node, (const xmlChar *)"blurX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurY);
	xmlSetProp( node, (const xmlChar *)"blurY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, angle);
	xmlSetProp( node, (const xmlChar *)"angle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, distance);
	xmlSetProp( node, (const xmlChar *)"distance", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, strength);
	xmlSetProp( node, (const xmlChar *)"strength", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", innerShadow);
	xmlSetProp( node, (const xmlChar *)"innerShadow", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", knockout);
	xmlSetProp( node, (const xmlChar *)"knockout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", onTop);
	xmlSetProp( node, (const xmlChar *)"onTop", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", passes);
	xmlSetProp( node, (const xmlChar *)"passes", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", compositeSource);
	xmlSetProp( node, (const xmlChar *)"compositeSource", (const xmlChar *)&tmp );
	}
}
void GradientGlow::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GradientGlow", NULL );
	ctx->alpha = 1;
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"colors", NULL );
		Color *item;
		ListItem<Color>* i;
		i = colors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"ratio", NULL );
		UChar *item;
		ListItem<UChar>* i;
		i = ratio.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurX);
	xmlSetProp( node, (const xmlChar *)"blurX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurY);
	xmlSetProp( node, (const xmlChar *)"blurY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, angle);
	xmlSetProp( node, (const xmlChar *)"angle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, distance);
	xmlSetProp( node, (const xmlChar *)"distance", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, strength);
	xmlSetProp( node, (const xmlChar *)"strength", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", innerGlow);
	xmlSetProp( node, (const xmlChar *)"innerGlow", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", knockout);
	xmlSetProp( node, (const xmlChar *)"knockout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", onTop);
	xmlSetProp( node, (const xmlChar *)"onTop", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", passes);
	xmlSetProp( node, (const xmlChar *)"passes", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", numColors);
	xmlSetProp( node, (const xmlChar *)"numColors", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", compositeSource);
	xmlSetProp( node, (const xmlChar *)"compositeSource", (const xmlChar *)&tmp );
	}
}
void Convolution::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Convolution", NULL );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", matrixX);
	xmlSetProp( node, (const xmlChar *)"matrixX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", matrixY);
	xmlSetProp( node, (const xmlChar *)"matrixY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, divizor);
	xmlSetProp( node, (const xmlChar *)"divizor", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, bias);
	xmlSetProp( node, (const xmlChar *)"bias", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
		Float *item;
		ListItem<Float>* i;
		i = matrix.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"defaultColor", NULL );
	defaultColor.writeXML( node2, ctx );
	snprintf(tmp,TMP_STRLEN,"%i", clamp);
	xmlSetProp( node, (const xmlChar *)"clamp", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", preserveAlpha);
	xmlSetProp( node, (const xmlChar *)"preserveAlpha", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	}
}
void ColorMatrix::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ColorMatrix", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
		Float *item;
		ListItem<Float>* i;
		i = matrix.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GradientBevel::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GradientBevel", NULL );
	ctx->alpha = 1;
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"colors", NULL );
		Color *item;
		ListItem<Color>* i;
		i = colors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"ratio", NULL );
		UChar *item;
		ListItem<UChar>* i;
		i = ratio.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurX);
	xmlSetProp( node, (const xmlChar *)"blurX", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, blurY);
	xmlSetProp( node, (const xmlChar *)"blurY", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, angle);
	xmlSetProp( node, (const xmlChar *)"angle", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, distance);
	xmlSetProp( node, (const xmlChar *)"distance", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, strength);
	xmlSetProp( node, (const xmlChar *)"strength", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", innerGlow);
	xmlSetProp( node, (const xmlChar *)"innerGlow", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", knockout);
	xmlSetProp( node, (const xmlChar *)"knockout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", onTop);
	xmlSetProp( node, (const xmlChar *)"onTop", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", passes);
	xmlSetProp( node, (const xmlChar *)"passes", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", numColors);
	xmlSetProp( node, (const xmlChar *)"numColors", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", compositeSource);
	xmlSetProp( node, (const xmlChar *)"compositeSource", (const xmlChar *)&tmp );
	}
}
void Solid::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Solid", NULL );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void LinearGradient::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"LinearGradient", NULL );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
	matrix.writeXML( node2, ctx );
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	snprintf(tmp,TMP_STRLEN,"%i", spreadMode);
	xmlSetProp( node, (const xmlChar *)"spreadMode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", interpolationMode);
	xmlSetProp( node, (const xmlChar *)"interpolationMode", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"gradientColors", NULL );
		GradientItem *item;
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	snprintf(tmp,TMP_STRLEN,"%i", spreadMode);
	xmlSetProp( node, (const xmlChar *)"spreadMode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", interpolationMode);
	xmlSetProp( node, (const xmlChar *)"interpolationMode", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void RadialGradient::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RadialGradient", NULL );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
	matrix.writeXML( node2, ctx );
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	snprintf(tmp,TMP_STRLEN,"%i", spreadMode);
	xmlSetProp( node, (const xmlChar *)"spreadMode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", interpolationMode);
	xmlSetProp( node, (const xmlChar *)"interpolationMode", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"gradientColors", NULL );
		GradientItem *item;
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	snprintf(tmp,TMP_STRLEN,"%i", spreadMode);
	xmlSetProp( node, (const xmlChar *)"spreadMode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", interpolationMode);
	xmlSetProp( node, (const xmlChar *)"interpolationMode", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void ShiftedRadialGradient::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ShiftedRadialGradient", NULL );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
	matrix.writeXML( node2, ctx );
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	snprintf(tmp,TMP_STRLEN,"%i", spreadMode);
	xmlSetProp( node, (const xmlChar *)"spreadMode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", interpolationMode);
	xmlSetProp( node, (const xmlChar *)"interpolationMode", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"gradientColors", NULL );
		GradientItem *item;
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, shift);
	xmlSetProp( node, (const xmlChar *)"shift", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	snprintf(tmp,TMP_STRLEN,"%i", spreadMode);
	xmlSetProp( node, (const xmlChar *)"spreadMode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", interpolationMode);
	xmlSetProp( node, (const xmlChar *)"interpolationMode", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void TiledBitmap::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TiledBitmap", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
	matrix.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ClippedBitmap::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ClippedBitmap", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
	matrix.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void TiledBitmap2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TiledBitmap2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
	matrix.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ClippedBitmap2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ClippedBitmap2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"matrix", NULL );
	matrix.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void UnknownTag::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"UnknownTag", NULL );
	{
		if( len && data ) {
			char *tmp_data = (char *)data;
			int sz = len;
			char *tmpstr = new char[ (sz * 3) ];
			int l = base64_encode( tmpstr, tmp_data, sz );
			if( l > 0 ) {
				tmpstr[l] = 0;
				xmlNewTextChild( node, NULL, (const xmlChar *)"data", (const xmlChar *)tmpstr );
			}
			delete tmpstr;
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
		snprintf( tmp, TMP_STRLEN, "0x%02X", type );
		xmlSetProp( node, (const xmlChar *)"id", (const xmlChar *)tmp );
}
void End::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"End", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ShowFrame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ShowFrame", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineShape::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineShape", NULL );
	ctx->alpha = 0;
	ctx->many_shapes = 0;
	ctx->tagVersion = 1;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
	bounds.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"styles", NULL );
	styles.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"shapes", NULL );
	shapes.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 0;
	ctx->many_shapes = 0;
	ctx->tagVersion = 1;
	}
}
void RemoveObject::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RemoveObject", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", depth);
	xmlSetProp( node, (const xmlChar *)"depth", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineBits::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineBits", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetBackgroundColor::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetBackgroundColor", NULL );
	ctx->alpha = 0;
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 0;
	}
}
void DefineText::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineText", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
	bounds.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	ctx->alpha = 0;
	ctx->tagVersion = 1;
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"records", NULL );
		TextRecord *item;
		ListItem<TextRecord>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", glyphBits);
	xmlSetProp( node, (const xmlChar *)"glyphBits", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", advanceBits);
	xmlSetProp( node, (const xmlChar *)"advanceBits", (const xmlChar *)&tmp );
	ctx->alpha = 0;
	ctx->tagVersion = 1;
	}
}
void DefineText2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineText2", NULL );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
	bounds.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"records", NULL );
		TextRecord2 *item;
		ListItem<TextRecord2>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", glyphBits);
	xmlSetProp( node, (const xmlChar *)"glyphBits", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", advanceBits);
	xmlSetProp( node, (const xmlChar *)"advanceBits", (const xmlChar *)&tmp );
	}
}
void DoAction::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DoAction", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineFontInfo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineFontInfo", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", smallTextOrUnicode);
	xmlSetProp( node, (const xmlChar *)"smallTextOrUnicode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isShiftJIS);
	xmlSetProp( node, (const xmlChar *)"isShiftJIS", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isANSII);
	xmlSetProp( node, (const xmlChar *)"isANSII", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isItalic);
	xmlSetProp( node, (const xmlChar *)"isItalic", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isBold);
	xmlSetProp( node, (const xmlChar *)"isBold", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isWide);
	xmlSetProp( node, (const xmlChar *)"isWide", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", language);
	xmlSetProp( node, (const xmlChar *)"language", (const xmlChar *)&tmp );
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"map", NULL );
	map.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", nameLength);
	xmlSetProp( node, (const xmlChar *)"nameLength", (const xmlChar *)&tmp );
	{
		if( nameLength && nameData ) {
			char *tmp_data = (char *)nameData;
			int sz = nameLength;
			char *tmpstr = new char[ (sz * 3) ];
			int l = base64_encode( tmpstr, tmp_data, sz );
			if( l > 0 ) {
				tmpstr[l] = 0;
				xmlNewTextChild( node, NULL, (const xmlChar *)"nameData", (const xmlChar *)tmpstr );
			}
			delete tmpstr;
		}
	}
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", language);
	xmlSetProp( node, (const xmlChar *)"language", (const xmlChar *)&tmp );
	}
	}
}
void DefineSound::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineSound", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", format);
	xmlSetProp( node, (const xmlChar *)"format", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", rate);
	xmlSetProp( node, (const xmlChar *)"rate", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", is16bit);
	xmlSetProp( node, (const xmlChar *)"is16bit", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", stereo);
	xmlSetProp( node, (const xmlChar *)"stereo", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", samples);
	xmlSetProp( node, (const xmlChar *)"samples", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StartSound::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StartSound", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", stopPlayback);
	xmlSetProp( node, (const xmlChar *)"stopPlayback", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", noMultiple);
	xmlSetProp( node, (const xmlChar *)"noMultiple", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasEnvelope);
	xmlSetProp( node, (const xmlChar *)"hasEnvelope", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasLoop);
	xmlSetProp( node, (const xmlChar *)"hasLoop", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasOutPoint);
	xmlSetProp( node, (const xmlChar *)"hasOutPoint", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasInPoint);
	xmlSetProp( node, (const xmlChar *)"hasInPoint", (const xmlChar *)&tmp );
	if( hasInPoint ) {
	snprintf(tmp,TMP_STRLEN,"%i", inPoint);
	xmlSetProp( node, (const xmlChar *)"inPoint", (const xmlChar *)&tmp );
	}
	if( hasOutPoint ) {
	snprintf(tmp,TMP_STRLEN,"%i", outPoint);
	xmlSetProp( node, (const xmlChar *)"outPoint", (const xmlChar *)&tmp );
	}
	if( hasLoop ) {
	snprintf(tmp,TMP_STRLEN,"%i", loop);
	xmlSetProp( node, (const xmlChar *)"loop", (const xmlChar *)&tmp );
	}
	if( hasEnvelope ) {
	snprintf(tmp,TMP_STRLEN,"%i", envelopeCount);
	xmlSetProp( node, (const xmlChar *)"envelopeCount", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"envelopeData", NULL );
	envelopeData.writeXML( node2, ctx );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	if( hasInPoint ) {
	snprintf(tmp,TMP_STRLEN,"%i", inPoint);
	xmlSetProp( node, (const xmlChar *)"inPoint", (const xmlChar *)&tmp );
	}
	if( hasOutPoint ) {
	snprintf(tmp,TMP_STRLEN,"%i", outPoint);
	xmlSetProp( node, (const xmlChar *)"outPoint", (const xmlChar *)&tmp );
	}
	if( hasLoop ) {
	snprintf(tmp,TMP_STRLEN,"%i", loop);
	xmlSetProp( node, (const xmlChar *)"loop", (const xmlChar *)&tmp );
	}
	if( hasEnvelope ) {
	snprintf(tmp,TMP_STRLEN,"%i", envelopeCount);
	xmlSetProp( node, (const xmlChar *)"envelopeCount", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"envelopeData", NULL );
	envelopeData.writeXML( node2, ctx );
	}
	}
}
void DefineShape2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineShape2", NULL );
	ctx->alpha = 0;
	ctx->many_shapes = 1;
	ctx->tagVersion = 2;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
	bounds.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"styles", NULL );
	styles.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"shapes", NULL );
	shapes.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 0;
	ctx->many_shapes = 1;
	ctx->tagVersion = 2;
	}
}
void DefineShape3::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineShape3", NULL );
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 3;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
	bounds.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"styles", NULL );
	styles.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"shapes", NULL );
	shapes.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 3;
	}
}
void DefineShape4::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineShape4", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineShape5::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineShape5", NULL );
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 5;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
	bounds.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"strokeBounds", NULL );
	strokeBounds.writeXML( node2, ctx );
	snprintf(tmp,TMP_STRLEN,"%i", nonScalingStrokes);
	xmlSetProp( node, (const xmlChar *)"nonScalingStrokes", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", scalingStrokes);
	xmlSetProp( node, (const xmlChar *)"scalingStrokes", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"styles", NULL );
	styles.writeXML( node2, ctx );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"shapes", NULL );
	shapes.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 5;
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	}
}
void DefineMorphShape::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineMorphShape", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineFontInfo2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineFontInfo2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", smallTextOrUnicode);
	xmlSetProp( node, (const xmlChar *)"smallTextOrUnicode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isShiftJIS);
	xmlSetProp( node, (const xmlChar *)"isShiftJIS", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isANSII);
	xmlSetProp( node, (const xmlChar *)"isANSII", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isItalic);
	xmlSetProp( node, (const xmlChar *)"isItalic", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isBold);
	xmlSetProp( node, (const xmlChar *)"isBold", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isWide);
	xmlSetProp( node, (const xmlChar *)"isWide", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", language);
	xmlSetProp( node, (const xmlChar *)"language", (const xmlChar *)&tmp );
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"map", NULL );
	map.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", nameLength);
	xmlSetProp( node, (const xmlChar *)"nameLength", (const xmlChar *)&tmp );
	{
		if( nameLength && nameData ) {
			char *tmp_data = (char *)nameData;
			int sz = nameLength;
			char *tmpstr = new char[ (sz * 3) ];
			int l = base64_encode( tmpstr, tmp_data, sz );
			if( l > 0 ) {
				tmpstr[l] = 0;
				xmlNewTextChild( node, NULL, (const xmlChar *)"nameData", (const xmlChar *)tmpstr );
			}
			delete tmpstr;
		}
	}
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", language);
	xmlSetProp( node, (const xmlChar *)"language", (const xmlChar *)&tmp );
	}
	}
}
void SoundStreamHead::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SoundStreamHead", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", playbackRate);
	xmlSetProp( node, (const xmlChar *)"playbackRate", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", playbackSize);
	xmlSetProp( node, (const xmlChar *)"playbackSize", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", playbackStereo);
	xmlSetProp( node, (const xmlChar *)"playbackStereo", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", compression);
	xmlSetProp( node, (const xmlChar *)"compression", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", soundRate);
	xmlSetProp( node, (const xmlChar *)"soundRate", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", soundSize);
	xmlSetProp( node, (const xmlChar *)"soundSize", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", soundStereo);
	xmlSetProp( node, (const xmlChar *)"soundStereo", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", sampleSize);
	xmlSetProp( node, (const xmlChar *)"sampleSize", (const xmlChar *)&tmp );
	if( compression==2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"latencySeek", NULL );
	latencySeek.writeXML( node2, ctx );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	if( compression==2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"latencySeek", NULL );
	latencySeek.writeXML( node2, ctx );
	}
	}
}
void DefineBitsLossless::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineBitsLossless", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", format);
	xmlSetProp( node, (const xmlChar *)"format", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", width);
	xmlSetProp( node, (const xmlChar *)"width", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", height);
	xmlSetProp( node, (const xmlChar *)"height", (const xmlChar *)&tmp );
	if( format==3 ) {
	snprintf(tmp,TMP_STRLEN,"%i", n_colormap);
	xmlSetProp( node, (const xmlChar *)"n_colormap", (const xmlChar *)&tmp );
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( format==3 ) {
	snprintf(tmp,TMP_STRLEN,"%i", n_colormap);
	xmlSetProp( node, (const xmlChar *)"n_colormap", (const xmlChar *)&tmp );
	}
	}
}
void DefineBitsJPEG2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineBitsJPEG2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineBitsJPEG3::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineBitsJPEG3", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", offset_to_alpha);
	xmlSetProp( node, (const xmlChar *)"offset_to_alpha", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineBitsLossless2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineBitsLossless2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", format);
	xmlSetProp( node, (const xmlChar *)"format", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", width);
	xmlSetProp( node, (const xmlChar *)"width", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", height);
	xmlSetProp( node, (const xmlChar *)"height", (const xmlChar *)&tmp );
	if( format==3 ) {
	snprintf(tmp,TMP_STRLEN,"%i", n_colormap);
	xmlSetProp( node, (const xmlChar *)"n_colormap", (const xmlChar *)&tmp );
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( format==3 ) {
	snprintf(tmp,TMP_STRLEN,"%i", n_colormap);
	xmlSetProp( node, (const xmlChar *)"n_colormap", (const xmlChar *)&tmp );
	}
	}
}
void PlaceObject2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"PlaceObject2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", replace);
	xmlSetProp( node, (const xmlChar *)"replace", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", depth);
	xmlSetProp( node, (const xmlChar *)"depth", (const xmlChar *)&tmp );
	if( hasID ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	}
	if( hasColorTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"colorTransform", NULL );
	colorTransform.writeXML( node2, ctx );
	}
	if( hasMorph ) {
	snprintf(tmp,TMP_STRLEN,"%i", morph);
	xmlSetProp( node, (const xmlChar *)"morph", (const xmlChar *)&tmp );
	}
	if( hasName ) {
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	}
	if( hasClipDepth ) {
	snprintf(tmp,TMP_STRLEN,"%i", clipDepth);
	xmlSetProp( node, (const xmlChar *)"clipDepth", (const xmlChar *)&tmp );
	}
	if( hasEventHandler ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags1);
	xmlSetProp( node, (const xmlChar *)"allflags1", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags2);
	xmlSetProp( node, (const xmlChar *)"allflags2", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"events", NULL );
		Event *item;
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasEventHandler);
	xmlSetProp( node, (const xmlChar *)"hasEventHandler", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasClipDepth);
	xmlSetProp( node, (const xmlChar *)"hasClipDepth", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasName);
	xmlSetProp( node, (const xmlChar *)"hasName", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMorph);
	xmlSetProp( node, (const xmlChar *)"hasMorph", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasColorTransform);
	xmlSetProp( node, (const xmlChar *)"hasColorTransform", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasTransform);
	xmlSetProp( node, (const xmlChar *)"hasTransform", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasID);
	xmlSetProp( node, (const xmlChar *)"hasID", (const xmlChar *)&tmp );
	if( hasID ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	}
	if( hasColorTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"colorTransform", NULL );
	colorTransform.writeXML( node2, ctx );
	}
	if( hasMorph ) {
	snprintf(tmp,TMP_STRLEN,"%i", morph);
	xmlSetProp( node, (const xmlChar *)"morph", (const xmlChar *)&tmp );
	}
	if( hasName ) {
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	}
	if( hasClipDepth ) {
	snprintf(tmp,TMP_STRLEN,"%i", clipDepth);
	xmlSetProp( node, (const xmlChar *)"clipDepth", (const xmlChar *)&tmp );
	}
	if( hasEventHandler ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags1);
	xmlSetProp( node, (const xmlChar *)"allflags1", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags2);
	xmlSetProp( node, (const xmlChar *)"allflags2", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"events", NULL );
		Event *item;
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void RemoveObject2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RemoveObject2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", depth);
	xmlSetProp( node, (const xmlChar *)"depth", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineEditText::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineEditText", NULL );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"size", NULL );
	size.writeXML( node2, ctx );
	snprintf(tmp,TMP_STRLEN,"%i", wordWrap);
	xmlSetProp( node, (const xmlChar *)"wordWrap", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", multiLine);
	xmlSetProp( node, (const xmlChar *)"multiLine", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", password);
	xmlSetProp( node, (const xmlChar *)"password", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", readOnly);
	xmlSetProp( node, (const xmlChar *)"readOnly", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", autoSize);
	xmlSetProp( node, (const xmlChar *)"autoSize", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasLayout);
	xmlSetProp( node, (const xmlChar *)"hasLayout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", notSelectable);
	xmlSetProp( node, (const xmlChar *)"notSelectable", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasBorder);
	xmlSetProp( node, (const xmlChar *)"hasBorder", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isHTML);
	xmlSetProp( node, (const xmlChar *)"isHTML", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", useOutlines);
	xmlSetProp( node, (const xmlChar *)"useOutlines", (const xmlChar *)&tmp );
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontRef);
	xmlSetProp( node, (const xmlChar *)"fontRef", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMaxLength ) {
	snprintf(tmp,TMP_STRLEN,"%i", maxLength);
	xmlSetProp( node, (const xmlChar *)"maxLength", (const xmlChar *)&tmp );
	}
	if( hasLayout ) {
	snprintf(tmp,TMP_STRLEN,"%i", align);
	xmlSetProp( node, (const xmlChar *)"align", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leftMargin);
	xmlSetProp( node, (const xmlChar *)"leftMargin", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", rightMargin);
	xmlSetProp( node, (const xmlChar *)"rightMargin", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", indent);
	xmlSetProp( node, (const xmlChar *)"indent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leading);
	xmlSetProp( node, (const xmlChar *)"leading", (const xmlChar *)&tmp );
	}
	if( variableName ) {
		xmlChar *xmlstr = toXmlChar(ctx, variableName);
		xmlSetProp(node, (const xmlChar *)"variableName", xmlstr);
	}
	if( hasText ) {
	if( initialText ) {
		xmlChar *xmlstr = toXmlChar(ctx, initialText);
		xmlSetProp(node, (const xmlChar *)"initialText", xmlstr);
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->alpha = 1;
	snprintf(tmp,TMP_STRLEN,"%i", hasText);
	xmlSetProp( node, (const xmlChar *)"hasText", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasColor);
	xmlSetProp( node, (const xmlChar *)"hasColor", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMaxLength);
	xmlSetProp( node, (const xmlChar *)"hasMaxLength", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFont);
	xmlSetProp( node, (const xmlChar *)"hasFont", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved2);
	xmlSetProp( node, (const xmlChar *)"reserved2", (const xmlChar *)&tmp );
	if( hasFont ) {
	snprintf(tmp,TMP_STRLEN,"%i", fontRef);
	xmlSetProp( node, (const xmlChar *)"fontRef", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", fontHeight);
	xmlSetProp( node, (const xmlChar *)"fontHeight", (const xmlChar *)&tmp );
	}
	if( hasColor ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"color", NULL );
	color.writeXML( node2, ctx );
	}
	if( hasMaxLength ) {
	snprintf(tmp,TMP_STRLEN,"%i", maxLength);
	xmlSetProp( node, (const xmlChar *)"maxLength", (const xmlChar *)&tmp );
	}
	if( hasLayout ) {
	snprintf(tmp,TMP_STRLEN,"%i", align);
	xmlSetProp( node, (const xmlChar *)"align", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leftMargin);
	xmlSetProp( node, (const xmlChar *)"leftMargin", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", rightMargin);
	xmlSetProp( node, (const xmlChar *)"rightMargin", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", indent);
	xmlSetProp( node, (const xmlChar *)"indent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leading);
	xmlSetProp( node, (const xmlChar *)"leading", (const xmlChar *)&tmp );
	}
	if( hasText ) {
	if( initialText ) {
		xmlChar *xmlstr = toXmlChar(ctx, initialText);
		xmlSetProp(node, (const xmlChar *)"initialText", xmlstr);
	}
	}
	}
}
void DefineSprite::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineSprite", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", frames);
	xmlSetProp( node, (const xmlChar *)"frames", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"tags", NULL );
		Tag *item;
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void FrameLabel::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"FrameLabel", NULL );
	if( label ) {
		xmlChar *xmlstr = toXmlChar(ctx, label);
		xmlSetProp(node, (const xmlChar *)"label", xmlstr);
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"flags", NULL );
	flags.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SoundStreamHead2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SoundStreamHead2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", playbackRate);
	xmlSetProp( node, (const xmlChar *)"playbackRate", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", playbackSize);
	xmlSetProp( node, (const xmlChar *)"playbackSize", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", playbackStereo);
	xmlSetProp( node, (const xmlChar *)"playbackStereo", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", compression);
	xmlSetProp( node, (const xmlChar *)"compression", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", soundRate);
	xmlSetProp( node, (const xmlChar *)"soundRate", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", soundSize);
	xmlSetProp( node, (const xmlChar *)"soundSize", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", soundStereo);
	xmlSetProp( node, (const xmlChar *)"soundStereo", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", sampleSize);
	xmlSetProp( node, (const xmlChar *)"sampleSize", (const xmlChar *)&tmp );
	if( compression==2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"latencySeek", NULL );
	latencySeek.writeXML( node2, ctx );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	if( compression==2 ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"latencySeek", NULL );
	latencySeek.writeXML( node2, ctx );
	}
	}
}
void DefineFont::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineFont", NULL );
	ctx->tagVersion = 1;
	ctx->wideGlyphOffsets = 0;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->tagVersion = 1;
	ctx->wideGlyphOffsets = 0;
	}
}
void DefineFont2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineFont2", NULL );
	ctx->tagVersion = 2;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isShiftJIS);
	xmlSetProp( node, (const xmlChar *)"isShiftJIS", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isUnicode);
	xmlSetProp( node, (const xmlChar *)"isUnicode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isANSII);
	xmlSetProp( node, (const xmlChar *)"isANSII", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", wideGlyphOffsets);
	xmlSetProp( node, (const xmlChar *)"wideGlyphOffsets", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", italic);
	xmlSetProp( node, (const xmlChar *)"italic", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", bold);
	xmlSetProp( node, (const xmlChar *)"bold", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", language);
	xmlSetProp( node, (const xmlChar *)"language", (const xmlChar *)&tmp );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
	glyphs.writeXML( node2, ctx );
	if( hasLayout ) {
	snprintf(tmp,TMP_STRLEN,"%i", ascent);
	xmlSetProp( node, (const xmlChar *)"ascent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", descent);
	xmlSetProp( node, (const xmlChar *)"descent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leading);
	xmlSetProp( node, (const xmlChar *)"leading", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"advance", NULL );
		Short *item;
		ListItem<Short>* i;
		i = advance.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
		Rectangle *item;
		ListItem<Rectangle>* i;
		i = bounds.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"wideKerning", NULL );
		WideKerning *item;
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"kerning", NULL );
		Kerning *item;
		ListItem<Kerning>* i;
		i = kerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->tagVersion = 2;
	snprintf(tmp,TMP_STRLEN,"%i", hasLayout);
	xmlSetProp( node, (const xmlChar *)"hasLayout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", wideMap);
	xmlSetProp( node, (const xmlChar *)"wideMap", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", glyphCount);
	xmlSetProp( node, (const xmlChar *)"glyphCount", (const xmlChar *)&tmp );
	if( hasLayout ) {
	snprintf(tmp,TMP_STRLEN,"%i", ascent);
	xmlSetProp( node, (const xmlChar *)"ascent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", descent);
	xmlSetProp( node, (const xmlChar *)"descent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leading);
	xmlSetProp( node, (const xmlChar *)"leading", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"advance", NULL );
		Short *item;
		ListItem<Short>* i;
		i = advance.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
		Rectangle *item;
		ListItem<Rectangle>* i;
		i = bounds.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"wideKerning", NULL );
		WideKerning *item;
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"kerning", NULL );
		Kerning *item;
		ListItem<Kerning>* i;
		i = kerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
	}
}
void DefineFont3::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineFont3", NULL );
	ctx->tagVersion = 2;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isShiftJIS);
	xmlSetProp( node, (const xmlChar *)"isShiftJIS", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isUnicode);
	xmlSetProp( node, (const xmlChar *)"isUnicode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", isANSII);
	xmlSetProp( node, (const xmlChar *)"isANSII", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", wideGlyphOffsets);
	xmlSetProp( node, (const xmlChar *)"wideGlyphOffsets", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", italic);
	xmlSetProp( node, (const xmlChar *)"italic", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", bold);
	xmlSetProp( node, (const xmlChar *)"bold", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", language);
	xmlSetProp( node, (const xmlChar *)"language", (const xmlChar *)&tmp );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"glyphs", NULL );
	glyphs.writeXML( node2, ctx );
	if( hasLayout ) {
	snprintf(tmp,TMP_STRLEN,"%i", ascent);
	xmlSetProp( node, (const xmlChar *)"ascent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", descent);
	xmlSetProp( node, (const xmlChar *)"descent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leading);
	xmlSetProp( node, (const xmlChar *)"leading", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"advance", NULL );
		Short *item;
		ListItem<Short>* i;
		i = advance.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
		Rectangle *item;
		ListItem<Rectangle>* i;
		i = bounds.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"wideKerning", NULL );
		WideKerning *item;
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"kerning", NULL );
		Kerning *item;
		ListItem<Kerning>* i;
		i = kerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->tagVersion = 2;
	snprintf(tmp,TMP_STRLEN,"%i", hasLayout);
	xmlSetProp( node, (const xmlChar *)"hasLayout", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", wideMap);
	xmlSetProp( node, (const xmlChar *)"wideMap", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", glyphCount);
	xmlSetProp( node, (const xmlChar *)"glyphCount", (const xmlChar *)&tmp );
	if( hasLayout ) {
	snprintf(tmp,TMP_STRLEN,"%i", ascent);
	xmlSetProp( node, (const xmlChar *)"ascent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", descent);
	xmlSetProp( node, (const xmlChar *)"descent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", leading);
	xmlSetProp( node, (const xmlChar *)"leading", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"advance", NULL );
		Short *item;
		ListItem<Short>* i;
		i = advance.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"bounds", NULL );
		Rectangle *item;
		ListItem<Rectangle>* i;
		i = bounds.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"wideKerning", NULL );
		WideKerning *item;
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"kerning", NULL );
		Kerning *item;
		ListItem<Kerning>* i;
		i = kerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
	}
}
void DefineButton::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineButton", NULL );
	ctx->tagVersion = 1;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"buttons", NULL );
		Button *item;
		ListItem<Button>* i;
		i = buttons.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->tagVersion = 1;
	}
}
void DefineButton2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineButton2", NULL );
	ctx->tagVersion = 2;
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", menu);
	xmlSetProp( node, (const xmlChar *)"menu", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", buttonsSize);
	xmlSetProp( node, (const xmlChar *)"buttonsSize", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"buttons", NULL );
		Button *item;
		ListItem<Button>* i;
		i = buttons.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"conditions", NULL );
		Condition *item;
		ListItem<Condition>* i;
		i = conditions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	ctx->tagVersion = 2;
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	}
}
void Export::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Export", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"symbols", NULL );
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void Import::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Import", NULL );
	if( url ) {
		xmlChar *xmlstr = toXmlChar(ctx, url);
		xmlSetProp(node, (const xmlChar *)"url", xmlstr);
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"symbols", NULL );
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void DoInitAction::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DoInitAction", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", sprite);
	xmlSetProp( node, (const xmlChar *)"sprite", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SoundStreamBlock::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SoundStreamBlock", NULL );
	{
		if( len && data ) {
			char *tmp_data = (char *)data;
			int sz = len;
			char *tmpstr = new char[ (sz * 3) ];
			int l = base64_encode( tmpstr, tmp_data, sz );
			if( l > 0 ) {
				tmpstr[l] = 0;
				xmlNewTextChild( node, NULL, (const xmlChar *)"data", (const xmlChar *)tmpstr );
			}
			delete tmpstr;
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineVideoStream::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineVideoStream", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", frames);
	xmlSetProp( node, (const xmlChar *)"frames", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", width);
	xmlSetProp( node, (const xmlChar *)"width", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", height);
	xmlSetProp( node, (const xmlChar *)"height", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", deblocking);
	xmlSetProp( node, (const xmlChar *)"deblocking", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", smoothing);
	xmlSetProp( node, (const xmlChar *)"smoothing", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", codec);
	xmlSetProp( node, (const xmlChar *)"codec", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	}
}
void VideoFrame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"VideoFrame", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", frame);
	xmlSetProp( node, (const xmlChar *)"frame", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ScriptLimits::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ScriptLimits", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", maxRecursionDepth);
	xmlSetProp( node, (const xmlChar *)"maxRecursionDepth", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", timeout);
	xmlSetProp( node, (const xmlChar *)"timeout", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetTabIndex::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetTabIndex", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", depth);
	xmlSetProp( node, (const xmlChar *)"depth", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", tabIndex);
	xmlSetProp( node, (const xmlChar *)"tabIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void PlaceObject3::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"PlaceObject3", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", replace);
	xmlSetProp( node, (const xmlChar *)"replace", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", depth);
	xmlSetProp( node, (const xmlChar *)"depth", (const xmlChar *)&tmp );
	if( hasID ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	}
	if( hasColorTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"colorTransform", NULL );
	colorTransform.writeXML( node2, ctx );
	}
	if( hasMorph ) {
	snprintf(tmp,TMP_STRLEN,"%i", morph);
	xmlSetProp( node, (const xmlChar *)"morph", (const xmlChar *)&tmp );
	}
	if( hasName ) {
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	}
	if( hasClipDepth ) {
	snprintf(tmp,TMP_STRLEN,"%i", clipDepth);
	xmlSetProp( node, (const xmlChar *)"clipDepth", (const xmlChar *)&tmp );
	}
	if( hasFilterList ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"filters", NULL );
		Filter *item;
		ListItem<Filter>* i;
		i = filters.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
	snprintf(tmp,TMP_STRLEN,"%i", blendMode);
	xmlSetProp( node, (const xmlChar *)"blendMode", (const xmlChar *)&tmp );
	}
	if( hasCacheAsBitmap ) {
	snprintf(tmp,TMP_STRLEN,"%i", bitmapCaching);
	xmlSetProp( node, (const xmlChar *)"bitmapCaching", (const xmlChar *)&tmp );
	}
	if( hasEventHandler ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags1);
	xmlSetProp( node, (const xmlChar *)"allflags1", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags2);
	xmlSetProp( node, (const xmlChar *)"allflags2", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"events", NULL );
		Event *item;
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasEventHandler);
	xmlSetProp( node, (const xmlChar *)"hasEventHandler", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasClipDepth);
	xmlSetProp( node, (const xmlChar *)"hasClipDepth", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasName);
	xmlSetProp( node, (const xmlChar *)"hasName", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasMorph);
	xmlSetProp( node, (const xmlChar *)"hasMorph", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasColorTransform);
	xmlSetProp( node, (const xmlChar *)"hasColorTransform", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasTransform);
	xmlSetProp( node, (const xmlChar *)"hasTransform", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasID);
	xmlSetProp( node, (const xmlChar *)"hasID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved1);
	xmlSetProp( node, (const xmlChar *)"reserved1", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasCacheAsBitmap);
	xmlSetProp( node, (const xmlChar *)"hasCacheAsBitmap", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasBlendMode);
	xmlSetProp( node, (const xmlChar *)"hasBlendMode", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", hasFilterList);
	xmlSetProp( node, (const xmlChar *)"hasFilterList", (const xmlChar *)&tmp );
	if( hasID ) {
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	}
	if( hasTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"transform", NULL );
	transform.writeXML( node2, ctx );
	}
	if( hasColorTransform ) {
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"colorTransform", NULL );
	colorTransform.writeXML( node2, ctx );
	}
	if( hasMorph ) {
	snprintf(tmp,TMP_STRLEN,"%i", morph);
	xmlSetProp( node, (const xmlChar *)"morph", (const xmlChar *)&tmp );
	}
	if( hasName ) {
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	}
	if( hasClipDepth ) {
	snprintf(tmp,TMP_STRLEN,"%i", clipDepth);
	xmlSetProp( node, (const xmlChar *)"clipDepth", (const xmlChar *)&tmp );
	}
	if( hasFilterList ) {
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"filters", NULL );
		Filter *item;
		ListItem<Filter>* i;
		i = filters.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
	snprintf(tmp,TMP_STRLEN,"%i", blendMode);
	xmlSetProp( node, (const xmlChar *)"blendMode", (const xmlChar *)&tmp );
	}
	if( hasCacheAsBitmap ) {
	snprintf(tmp,TMP_STRLEN,"%i", bitmapCaching);
	xmlSetProp( node, (const xmlChar *)"bitmapCaching", (const xmlChar *)&tmp );
	}
	if( hasEventHandler ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags1);
	xmlSetProp( node, (const xmlChar *)"allflags1", (const xmlChar *)&tmp );
	if( ctx->swfVersion>=6 ) {
	snprintf(tmp,TMP_STRLEN,"%i", allflags2);
	xmlSetProp( node, (const xmlChar *)"allflags2", (const xmlChar *)&tmp );
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"events", NULL );
		Event *item;
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	}
	}
}
void ImportAssets2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ImportAssets2", NULL );
	if( url ) {
		xmlChar *xmlstr = toXmlChar(ctx, url);
		xmlSetProp(node, (const xmlChar *)"url", xmlstr);
	}
	snprintf(tmp,TMP_STRLEN,"%i", reserved1);
	xmlSetProp( node, (const xmlChar *)"reserved1", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved2);
	xmlSetProp( node, (const xmlChar *)"reserved2", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"symbols", NULL );
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void FileAttributes::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"FileAttributes", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", hasMetaData);
	xmlSetProp( node, (const xmlChar *)"hasMetaData", (const xmlChar *)&tmp );
	if( ctx->swfVersion < 9 ) {
	}
	if( ctx->swfVersion >= 9 ) {
	snprintf(tmp,TMP_STRLEN,"%i", allowABC);
	xmlSetProp( node, (const xmlChar *)"allowABC", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", suppressCrossDomainCaching);
	xmlSetProp( node, (const xmlChar *)"suppressCrossDomainCaching", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", swfRelativeURLs);
	xmlSetProp( node, (const xmlChar *)"swfRelativeURLs", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", useNetwork);
	xmlSetProp( node, (const xmlChar *)"useNetwork", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved1);
	xmlSetProp( node, (const xmlChar *)"reserved1", (const xmlChar *)&tmp );
	if( ctx->swfVersion < 9 ) {
	}
	if( ctx->swfVersion >= 9 ) {
	snprintf(tmp,TMP_STRLEN,"%i", allowABC);
	xmlSetProp( node, (const xmlChar *)"allowABC", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", suppressCrossDomainCaching);
	xmlSetProp( node, (const xmlChar *)"suppressCrossDomainCaching", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", swfRelativeURLs);
	xmlSetProp( node, (const xmlChar *)"swfRelativeURLs", (const xmlChar *)&tmp );
	}
	snprintf(tmp,TMP_STRLEN,"%i", reserved3);
	xmlSetProp( node, (const xmlChar *)"reserved3", (const xmlChar *)&tmp );
	}
}
void DefineFontAlignZones::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineFontAlignZones", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", csmTableHint);
	xmlSetProp( node, (const xmlChar *)"csmTableHint", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"zoneArrays", NULL );
		ZoneArray *item;
		ListItem<ZoneArray>* i;
		i = zoneArrays.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	}
}
void CSMTextSettings::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"CSMTextSettings", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", useFlashType);
	xmlSetProp( node, (const xmlChar *)"useFlashType", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", gridFit);
	xmlSetProp( node, (const xmlChar *)"gridFit", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, thickness);
	xmlSetProp( node, (const xmlChar *)"thickness", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, sharpness);
	xmlSetProp( node, (const xmlChar *)"sharpness", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved1);
	xmlSetProp( node, (const xmlChar *)"reserved1", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved2);
	xmlSetProp( node, (const xmlChar *)"reserved2", (const xmlChar *)&tmp );
	}
}
void Metadata::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Metadata", NULL );
	{
		if(RDF ) {
			xmlDocPtr doc = xmlParseMemory(RDF, strlen(RDF));
			if( doc ) {
				xmlNodePtr child = doc->children;
				child = xmlDocCopyNode(child, node->doc, 1);
				xmlAddChild(node, child);
				xmlFreeDoc(doc);
			}
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineScalingGrid::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineScalingGrid", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"splitter", NULL );
	splitter.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DoABC::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DoABC", NULL );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
	actions.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DoABCDefine::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DoABCDefine", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", flags);
	xmlSetProp( node, (const xmlChar *)"flags", (const xmlChar *)&tmp );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
	actions.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SymbolClass::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SymbolClass", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"symbols", NULL );
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", count);
	xmlSetProp( node, (const xmlChar *)"count", (const xmlChar *)&tmp );
	}
}
void DefineSceneAndFrameLabelData::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineSceneAndFrameLabelData", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"scenes", NULL );
		Scene *item;
		ListItem<Scene>* i;
		i = scenes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"frames", NULL );
		Frame *item;
		ListItem<Frame>* i;
		i = frames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", sceneCount);
	xmlSetProp( node, (const xmlChar *)"sceneCount", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", frameCount);
	xmlSetProp( node, (const xmlChar *)"frameCount", (const xmlChar *)&tmp );
	}
}
void DefineBinaryData::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineBinaryData", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	node2 = xmlNewChild( node, NULL, (const xmlChar *)"data", NULL );
	data.writeXML( node2, ctx );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	}
}
void DefineFontName::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineFontName", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", objectID);
	xmlSetProp( node, (const xmlChar *)"objectID", (const xmlChar *)&tmp );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	if( copyright ) {
		xmlChar *xmlstr = toXmlChar(ctx, copyright);
		xmlSetProp(node, (const xmlChar *)"copyright", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackString::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackString", NULL );
	if( value ) {
		xmlChar *xmlstr = toXmlChar(ctx, value);
		xmlSetProp(node, (const xmlChar *)"value", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackFloat::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackFloat", NULL );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackNull::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackNull", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackUndefined::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackUndefined", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackRegister::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackRegister", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", reg);
	xmlSetProp( node, (const xmlChar *)"reg", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackBoolean::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackBoolean", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackDouble::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackDouble", NULL );
	snprintf(tmp,TMP_STRLEN,"%#.*g", 16, value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackInteger::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackInteger", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackDictionaryLookup::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackDictionaryLookup", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StackLargeDictionaryLookup::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StackLargeDictionaryLookup", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void UnknownAction::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"UnknownAction", NULL );
	{
		if( len && data ) {
			char *tmp_data = (char *)data;
			int sz = len;
			char *tmpstr = new char[ (sz * 3) ];
			int l = base64_encode( tmpstr, tmp_data, sz );
			if( l > 0 ) {
				tmpstr[l] = 0;
				xmlNewTextChild( node, NULL, (const xmlChar *)"data", (const xmlChar *)tmpstr );
			}
			delete tmpstr;
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
		snprintf( tmp, TMP_STRLEN, "0x%02X", type );
		xmlSetProp( node, (const xmlChar *)"id", (const xmlChar *)tmp );
}
void EndAction::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"EndAction", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void NextFrame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"NextFrame", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void PreviousFrame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"PreviousFrame", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Play::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Play", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Stop::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Stop", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ToggleQuality::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ToggleQuality", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StopSound::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StopSound", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void AddCast::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"AddCast", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Substract::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Substract", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Mulitply::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Mulitply", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Divide::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Divide", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void EqualCast::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"EqualCast", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void LessThanCast::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"LessThanCast", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void LogicalAND::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"LogicalAND", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void LogicalOR::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"LogicalOR", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void LogicalNOT::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"LogicalNOT", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StringEqual::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StringEqual", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StringLength::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StringLength", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SubString::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SubString", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Pop::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Pop", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void IntegralPart::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"IntegralPart", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GetVariable::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GetVariable", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetVariable::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetVariable", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetTargetDynamic::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetTargetDynamic", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ConcatenateString::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ConcatenateString", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GetProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GetProperty", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetProperty", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DuplicateSprite::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DuplicateSprite", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void RemoveSprite::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RemoveSprite", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Trace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Trace", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StartDrag::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StartDrag", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StopDrag::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StopDrag", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StringLessThan::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StringLessThan", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Throw::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Throw", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void CastObject::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"CastObject", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Implements::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Implements", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Random::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Random", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MultibyteStringLength::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MultibyteStringLength", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ORD::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ORD", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void CHR::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"CHR", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GetTimer::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GetTimer", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MultibyteSubString::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MultibyteSubString", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MultibyteORD::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MultibyteORD", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MultibyteCHR::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MultibyteCHR", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Delete::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Delete", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DeleteAll::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DeleteAll", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetLocalVariable::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetLocalVariable", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void CallFunction::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"CallFunction", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Return::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Return", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Modulo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Modulo", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void New::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"New", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DeclareLocalVariable::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DeclareLocalVariable", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DeclareArray::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DeclareArray", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DeclareObject::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DeclareObject", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void TypeOf::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"TypeOf", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GetTarget::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GetTarget", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Enumerate::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Enumerate", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void AddTyped::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"AddTyped", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void LessThanTyped::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"LessThanTyped", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void EqualTyped::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"EqualTyped", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineNumber::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineNumber", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DefineString::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DefineString", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Duplicate::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Duplicate", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Swap::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Swap", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GetMember::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GetMember", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetMember::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetMember", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Increment::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Increment", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Decrement::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Decrement", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void CallMethod::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"CallMethod", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void NewMethod::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"NewMethod", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void InstanceOf::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"InstanceOf", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void EnumerateObject::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"EnumerateObject", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void AND::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"AND", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OR::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OR", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void XOR::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"XOR", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ShiftLeft::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ShiftLeft", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ShiftRight::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ShiftRight", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ShiftRightUnsigned::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ShiftRightUnsigned", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StrictEqual::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StrictEqual", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GreaterThanTyped::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GreaterThanTyped", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StringGreaterThan::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StringGreaterThan", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Extends::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Extends", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GotoFrame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GotoFrame", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", frame);
	xmlSetProp( node, (const xmlChar *)"frame", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GetURL::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GetURL", NULL );
	if( url ) {
		xmlChar *xmlstr = toXmlChar(ctx, url);
		xmlSetProp(node, (const xmlChar *)"url", xmlstr);
	}
	if( target ) {
		xmlChar *xmlstr = toXmlChar(ctx, target);
		xmlSetProp(node, (const xmlChar *)"target", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void StoreRegister::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"StoreRegister", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", reg);
	xmlSetProp( node, (const xmlChar *)"reg", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Dictionary::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Dictionary", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"strings", NULL );
		String *item;
		ListItem<String>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", length);
	xmlSetProp( node, (const xmlChar *)"length", (const xmlChar *)&tmp );
	}
}
void WaitForFrame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"WaitForFrame", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", frame);
	xmlSetProp( node, (const xmlChar *)"frame", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", skip);
	xmlSetProp( node, (const xmlChar *)"skip", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void SetTarget::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"SetTarget", NULL );
	if( label ) {
		xmlChar *xmlstr = toXmlChar(ctx, label);
		xmlSetProp(node, (const xmlChar *)"label", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GotoLabel::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GotoLabel", NULL );
	if( label ) {
		xmlChar *xmlstr = toXmlChar(ctx, label);
		xmlSetProp(node, (const xmlChar *)"label", xmlstr);
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void WaitForFrameDynamic::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"WaitForFrameDynamic", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", frame);
	xmlSetProp( node, (const xmlChar *)"frame", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", skip);
	xmlSetProp( node, (const xmlChar *)"skip", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DeclareFunction2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DeclareFunction2", NULL );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", regc);
	xmlSetProp( node, (const xmlChar *)"regc", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", preloadParent);
	xmlSetProp( node, (const xmlChar *)"preloadParent", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", preloadRoot);
	xmlSetProp( node, (const xmlChar *)"preloadRoot", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", suppressSuper);
	xmlSetProp( node, (const xmlChar *)"suppressSuper", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", preloadSuper);
	xmlSetProp( node, (const xmlChar *)"preloadSuper", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", suppressArguments);
	xmlSetProp( node, (const xmlChar *)"suppressArguments", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", preloadArguments);
	xmlSetProp( node, (const xmlChar *)"preloadArguments", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", suppressThis);
	xmlSetProp( node, (const xmlChar *)"suppressThis", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", preloadThis);
	xmlSetProp( node, (const xmlChar *)"preloadThis", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", preloadGlobal);
	xmlSetProp( node, (const xmlChar *)"preloadGlobal", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"args", NULL );
		Parameter *item;
		ListItem<Parameter>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"actions", NULL );
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", length);
	xmlSetProp( node, (const xmlChar *)"length", (const xmlChar *)&tmp );
	}
}
void Try::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Try", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", doFinally);
	xmlSetProp( node, (const xmlChar *)"doFinally", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", doCatch);
	xmlSetProp( node, (const xmlChar *)"doCatch", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", trySize);
	xmlSetProp( node, (const xmlChar *)"trySize", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", catchSize);
	xmlSetProp( node, (const xmlChar *)"catchSize", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", finallySize);
	xmlSetProp( node, (const xmlChar *)"finallySize", (const xmlChar *)&tmp );
	if( catchInRegister ) {
	snprintf(tmp,TMP_STRLEN,"%i", reg);
	xmlSetProp( node, (const xmlChar *)"reg", (const xmlChar *)&tmp );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reserved);
	xmlSetProp( node, (const xmlChar *)"reserved", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", catchInRegister);
	xmlSetProp( node, (const xmlChar *)"catchInRegister", (const xmlChar *)&tmp );
	if( catchInRegister ) {
	snprintf(tmp,TMP_STRLEN,"%i", reg);
	xmlSetProp( node, (const xmlChar *)"reg", (const xmlChar *)&tmp );
	}
	}
}
void With::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"With", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", size);
	xmlSetProp( node, (const xmlChar *)"size", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void PushData::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"PushData", NULL );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"items", NULL );
		StackItem *item;
		ListItem<StackItem>* i;
		i = items.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GetURL2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GetURL2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", method);
	xmlSetProp( node, (const xmlChar *)"method", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void DeclareFunction::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"DeclareFunction", NULL );
	if( name ) {
		xmlChar *xmlstr = toXmlChar(ctx, name);
		xmlSetProp(node, (const xmlChar *)"name", xmlstr);
	}
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"args", NULL );
		String *item;
		ListItem<String>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	snprintf(tmp,TMP_STRLEN,"%i", length);
	xmlSetProp( node, (const xmlChar *)"length", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void BranchAlways::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"BranchAlways", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", byteOffset);
	xmlSetProp( node, (const xmlChar *)"byteOffset", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void BranchIfTrue::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"BranchIfTrue", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", byteOffset);
	xmlSetProp( node, (const xmlChar *)"byteOffset", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void CallFrame::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"CallFrame", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void GotoExpression::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"GotoExpression", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", play);
	xmlSetProp( node, (const xmlChar *)"play", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void PrivateNamespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"PrivateNamespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Namespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Namespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void PackageNamespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"PackageNamespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void PackageInternalNamespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"PackageInternalNamespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ProtectedNamespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ProtectedNamespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void ExplicitNamespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"ExplicitNamespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MultinameLNamespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MultinameLNamespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void QName::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"QName", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", namespaceIndex);
	xmlSetProp( node, (const xmlChar *)"namespaceIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void QNameA::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"QNameA", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", namespaceIndex);
	xmlSetProp( node, (const xmlChar *)"namespaceIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Multiname::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Multiname", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", namespaceSetIndex);
	xmlSetProp( node, (const xmlChar *)"namespaceSetIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MultinameA::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MultinameA", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", namespaceSetIndex);
	xmlSetProp( node, (const xmlChar *)"namespaceSetIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void RTQName::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RTQName", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void RTQNameA::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RTQNameA", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", nameIndex);
	xmlSetProp( node, (const xmlChar *)"nameIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void MultinameL::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"MultinameL", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", namespaceSetIndex);
	xmlSetProp( node, (const xmlChar *)"namespaceSetIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void RTQNameL::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RTQNameL", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void RTQNameLA::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"RTQNameLA", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Slot::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Slot", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", typeIndex);
	xmlSetProp( node, (const xmlChar *)"typeIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", valueIndex);
	xmlSetProp( node, (const xmlChar *)"valueIndex", (const xmlChar *)&tmp );
	if( valueIndex != 0 ) {
	snprintf(tmp,TMP_STRLEN,"%i", valueKind);
	xmlSetProp( node, (const xmlChar *)"valueKind", (const xmlChar *)&tmp );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( valueIndex != 0 ) {
	snprintf(tmp,TMP_STRLEN,"%i", valueKind);
	xmlSetProp( node, (const xmlChar *)"valueKind", (const xmlChar *)&tmp );
	}
	}
}
void Const::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Const", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", typeIndex);
	xmlSetProp( node, (const xmlChar *)"typeIndex", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", valueIndex);
	xmlSetProp( node, (const xmlChar *)"valueIndex", (const xmlChar *)&tmp );
	if( valueIndex != 0 ) {
	snprintf(tmp,TMP_STRLEN,"%i", valueKind);
	xmlSetProp( node, (const xmlChar *)"valueKind", (const xmlChar *)&tmp );
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	if( valueIndex != 0 ) {
	snprintf(tmp,TMP_STRLEN,"%i", valueKind);
	xmlSetProp( node, (const xmlChar *)"valueKind", (const xmlChar *)&tmp );
	}
	}
}
void Method::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Method", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", dispID);
	xmlSetProp( node, (const xmlChar *)"dispID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", methodInfo);
	xmlSetProp( node, (const xmlChar *)"methodInfo", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Getter::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Getter", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", dispID);
	xmlSetProp( node, (const xmlChar *)"dispID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", methodInfo);
	xmlSetProp( node, (const xmlChar *)"methodInfo", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Setter::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Setter", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", dispID);
	xmlSetProp( node, (const xmlChar *)"dispID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", methodInfo);
	xmlSetProp( node, (const xmlChar *)"methodInfo", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Class::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Class", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", classInfo);
	xmlSetProp( node, (const xmlChar *)"classInfo", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void Function::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"Function", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", methodInfo);
	xmlSetProp( node, (const xmlChar *)"methodInfo", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpBkPt::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpBkPt", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNop::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNop", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpThrow::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpThrow", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetSuper::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetSuper", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetSuper::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetSuper", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDXNs::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDXNs", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", dxns);
	xmlSetProp( node, (const xmlChar *)"dxns", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDXNsLate::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDXNsLate", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpKill::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpKill", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", address);
	xmlSetProp( node, (const xmlChar *)"address", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpLabel::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpLabel", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfNlt::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfNlt", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfNle::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfNle", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfNgt::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfNgt", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfNge::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfNge", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpJump::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpJump", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfTrue::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfTrue", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfFalse::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfFalse", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfEq::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfEq", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfNe::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfNe", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfLt::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfLt", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfLe::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfLe", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfGt::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfGt", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfGe::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfGe", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfStrictEq::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfStrictEq", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIfStrictNe::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIfStrictNe", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", target);
	xmlSetProp( node, (const xmlChar *)"target", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpLookupSwitch::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	xmlNodePtr node2;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpLookupSwitch", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", defaulTarget);
	xmlSetProp( node, (const xmlChar *)"defaulTarget", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", caseCount);
	xmlSetProp( node, (const xmlChar *)"caseCount", (const xmlChar *)&tmp );
	{
		node2 = xmlNewChild( node, NULL, (const xmlChar *)"targetTable", NULL );
		S24 *item;
		ListItem<S24>* i;
		i = targetTable.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->writeXML( node2, ctx );
			}
			i = i->next();
		}
	}
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushWith::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushWith", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPopScope::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPopScope", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNextName::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNextName", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpHasNext::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpHasNext", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushNull::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushNull", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushUndefined::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushUndefined", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNextValue::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNextValue", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushByte::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushByte", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushShort::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushShort", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", value);
	xmlSetProp( node, (const xmlChar *)"value", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushTrue::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushTrue", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushFalse::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushFalse", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushNaN::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushNaN", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPop::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPop", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDup::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDup", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSwap::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSwap", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushString::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushString", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushInt::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushInt", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushUInt::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushUInt", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushDouble::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushDouble", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushScope::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushScope", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpPushNamespace::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpPushNamespace", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpHasNext2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpHasNext2", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", object);
	xmlSetProp( node, (const xmlChar *)"object", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNewFunction::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNewFunction", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", index);
	xmlSetProp( node, (const xmlChar *)"index", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCall::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCall", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConstruct::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConstruct", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCallMethod::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCallMethod", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", dispID);
	xmlSetProp( node, (const xmlChar *)"dispID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCallStatic::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCallStatic", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", methodID);
	xmlSetProp( node, (const xmlChar *)"methodID", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCallSuper::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCallSuper", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCallProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCallProperty", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpReturnVoid::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpReturnVoid", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpReturnValue::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpReturnValue", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConstructSuper::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConstructSuper", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConstructProp::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConstructProp", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCallPropLex::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCallPropLex", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCallSuperVoid::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCallSuperVoid", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCallPropVoid::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCallPropVoid", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNewObject::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNewObject", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNewArray::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNewArray", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", argc);
	xmlSetProp( node, (const xmlChar *)"argc", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNewActivation::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNewActivation", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNewClass::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNewClass", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", classIndex);
	xmlSetProp( node, (const xmlChar *)"classIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetDescendants::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetDescendants", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNewCatch::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNewCatch", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", exceptionIndex);
	xmlSetProp( node, (const xmlChar *)"exceptionIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpFindPropStrict::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpFindPropStrict", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpFindProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpFindProperty", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpFindDef::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpFindDef", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetLex::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetLex", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetProperty", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetLocal::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetLocal", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", address);
	xmlSetProp( node, (const xmlChar *)"address", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetLocal::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetLocal", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", address);
	xmlSetProp( node, (const xmlChar *)"address", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetGlobalScope::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetGlobalScope", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetScopeObject::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetScopeObject", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", scopeIndex);
	xmlSetProp( node, (const xmlChar *)"scopeIndex", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetProperty", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpInitProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpInitProperty", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDeleteProperty::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDeleteProperty", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetSlot::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetSlot", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetSlot::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetSlot", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetGlobalSlot::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetGlobalSlot", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetGlobalSlot::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetGlobalSlot", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", slotID);
	xmlSetProp( node, (const xmlChar *)"slotID", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConvertS::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConvertS", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpEscXelem::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpEscXelem", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpEscXattr::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpEscXattr", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConvertI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConvertI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConvertU::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConvertU", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConvertD::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConvertD", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConvertB::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConvertB", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpConvertO::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpConvertO", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCheckFilter::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCheckFilter", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerce::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerce", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerceB::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerceB", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerceA::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerceA", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerceI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerceI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerceD::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerceD", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerceS::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerceS", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpAsType::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpAsType", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpAsTypeLate::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpAsTypeLate", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerceU::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerceU", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpCoerceO::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpCoerceO", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNegate::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNegate", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIncrement::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIncrement", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIncLocal::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIncLocal", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", address);
	xmlSetProp( node, (const xmlChar *)"address", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDecrement::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDecrement", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDecLocal::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDecLocal", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", address);
	xmlSetProp( node, (const xmlChar *)"address", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpTypeOf::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpTypeOf", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNot::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNot", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpBitNot::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpBitNot", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpAdd::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpAdd", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSubtract::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSubtract", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpMultiply::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpMultiply", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDivide::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDivide", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpModulo::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpModulo", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpLShift::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpLShift", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpRShift::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpRShift", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpURShift::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpURShift", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpBitAnd::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpBitAnd", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpBitOr::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpBitOr", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpBitXor::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpBitXor", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpEquals::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpEquals", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpStrictEquals::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpStrictEquals", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpLessThan::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpLessThan", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpLessEquals::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpLessEquals", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGreaterThan::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGreaterThan", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGreaterEquals::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGreaterEquals", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpInstanceOf::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpInstanceOf", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIsType::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIsType", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIsTypeLate::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIsTypeLate", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIn::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIn", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIncrementI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIncrementI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDecrementI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDecrementI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpIncLocalI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpIncLocalI", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", address);
	xmlSetProp( node, (const xmlChar *)"address", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDecLocalI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDecLocalI", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", address);
	xmlSetProp( node, (const xmlChar *)"address", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpNegateI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpNegateI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpAddI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpAddI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSubtractI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSubtractI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpMultiplyI::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpMultiplyI", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetLocal0::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetLocal0", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetLocal1::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetLocal1", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetLocal2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetLocal2", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpGetLocal3::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpGetLocal3", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetLocal0::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetLocal0", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetLocal1::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetLocal1", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetLocal2::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetLocal2", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpSetLocal3::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpSetLocal3", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDebugReg::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDebugReg", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", unknown);
	xmlSetProp( node, (const xmlChar *)"unknown", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", name);
	xmlSetProp( node, (const xmlChar *)"name", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", reg);
	xmlSetProp( node, (const xmlChar *)"reg", (const xmlChar *)&tmp );
	snprintf(tmp,TMP_STRLEN,"%i", line);
	xmlSetProp( node, (const xmlChar *)"line", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDebugLine::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDebugLine", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", line);
	xmlSetProp( node, (const xmlChar *)"line", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpDebugFile::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpDebugFile", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", file);
	xmlSetProp( node, (const xmlChar *)"file", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpBkPtLine::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpBkPtLine", NULL );
	snprintf(tmp,TMP_STRLEN,"%i", line);
	xmlSetProp( node, (const xmlChar *)"line", (const xmlChar *)&tmp );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
void OpTimestamp::writeXML( xmlNodePtr xml, Context *ctx ) {
	char tmp[TMP_STRLEN];
	xmlNodePtr node = xml;
	node = xmlNewChild( node, NULL, (const xmlChar *)"OpTimestamp", NULL );
	if( ctx->transientPropsToXML ) {
		snprintf( tmp, TMP_STRLEN, "%i", file_offset );
		xmlSetProp( node, (const xmlChar *)"file_offset", (const xmlChar *)tmp );
	}
}
}
