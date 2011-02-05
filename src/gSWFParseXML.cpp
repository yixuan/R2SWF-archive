#include "SWF.h"
#include <cstring>
#include <cctype>
#include <cstdlib>
#include "base64.h"
#include <errno.h>
/* #include <iconv.h> */
using namespace std;
namespace SWF {
char *fromXmlChar(const Context *ctx, const xmlChar *from_str) {
	/*if (ctx->convertEncoding) {
		size_t len = strlen((const char *)from_str);
		iconv_t cd = iconv_open(ctx->swf_encoding, "UTF-8");
		if (cd < 0) {
			fprintf(stderr, "iconv_open failed.\n");
			char *buf = new char[1];
			buf[0] = '\0';
			return buf;
		}
		size_t buf_size = (len + 1) * 2;
		for (;;) {
			char * const dst = new char[buf_size];
			size_t inbytesleft = len;
			size_t outbytesleft = buf_size - 1; // reserve 1 byte for '\0'
			char *pin = (char*)from_str;
			char *pout = dst;
			bool expandbuf = false;
			while (inbytesleft > 0) {
				size_t r = iconv(cd, &pin, &inbytesleft, &pout, &outbytesleft);
				if (r == (size_t)-1) {
					if (errno == E2BIG) {
						expandbuf = true;
					} else {
						// bad input charctor
						fprintf(stderr, "iconv failed: %s\n", from_str);
					}
					break;
				}
			}
			if (expandbuf) {
				iconv(cd, 0, 0, 0, 0);
				delete[] dst;
				buf_size *= 2;
				continue;
			}
			*pout = '\0';
			iconv_close(cd);
			return dst;
		}
	} else {*/
		size_t len = strlen((const char *)from_str) + 1;
		char *buf = new char[len];
		strcpy(buf, (const char *)from_str);
		return buf;
	/*}*/
}
char *strdupx(const char *src) {
	char *t = new char[strlen(src)+1];
	strcpy(t, src);
	return  t;
}
void Rectangle::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Rectangle::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"left" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &left);
		xmlFree( tmp );
				int b = SWFBitsNeeded( left, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no left property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"right" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &right);
		xmlFree( tmp );
				int b = SWFBitsNeeded( right, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no right property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"top" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &top);
		xmlFree( tmp );
				int b = SWFBitsNeeded( top, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no top property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"bottom" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &bottom);
		xmlFree( tmp );
				int b = SWFBitsNeeded( bottom, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no bottom property in %s element\n", (const char *)node->name );
	}
}
void Color::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Color::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"red" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		red = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"green" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		green = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blue" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		blue = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->alpha ) {
	tmp = xmlGetProp( node, (const xmlChar *)"alpha" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		alpha = tmp_int;
		xmlFree( tmp );
	}
	}
}
void String::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("String::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		value = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no value property in %s element\n", (const char *)node->name );
		value = strdupx("[undefined]");
	}
}
void String2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("String2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		value = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no value property in %s element\n", (const char *)node->name );
		value = strdupx("[undefined]");
	}
}
void Transform::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Transform::parseXML\n");
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"scaleX" ) ) has = true;
					if( has ) scaled = true;
	if( xmlHasProp( node, (const xmlChar *)"scaleY" ) ) has = true;
					if( has ) scaled = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"scaleX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		scaleX = t;
		xmlFree( tmp );
				int b = SWFBitsNeeded( (long)(scaleX*(1<< 16)), true );
				if( b > bitsScale ) bitsScale = b;
	} else {
		fprintf(stderr,"WARNING: no scaleX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"scaleY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		scaleY = t;
		xmlFree( tmp );
				int b = SWFBitsNeeded( (long)(scaleY*(1<< 16)), true );
				if( b > bitsScale ) bitsScale = b;
	} else {
		fprintf(stderr,"WARNING: no scaleY property in %s element\n", (const char *)node->name );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"skewX" ) ) has = true;
					if( has ) skewed = true;
	if( xmlHasProp( node, (const xmlChar *)"skewY" ) ) has = true;
					if( has ) skewed = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"skewX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		skewX = t;
		xmlFree( tmp );
				int b = SWFBitsNeeded( (long)(skewX*(1<< 16)), true );
				if( b > bitsSkew ) bitsSkew = b;
	} else {
		fprintf(stderr,"WARNING: no skewX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"skewY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		skewY = t;
		xmlFree( tmp );
				int b = SWFBitsNeeded( (long)(skewY*(1<< 16)), true );
				if( b > bitsSkew ) bitsSkew = b;
	} else {
		fprintf(stderr,"WARNING: no skewY property in %s element\n", (const char *)node->name );
	}
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"transX" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &transX);
		xmlFree( tmp );
				int b = SWFBitsNeeded( transX, true );
				if( b > bitsTranslate ) bitsTranslate = b;
	} else {
		fprintf(stderr,"WARNING: no transX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"transY" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &transY);
		xmlFree( tmp );
				int b = SWFBitsNeeded( transY, true );
				if( b > bitsTranslate ) bitsTranslate = b;
	} else {
		fprintf(stderr,"WARNING: no transY property in %s element\n", (const char *)node->name );
	}
}
void ColorTransform2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("ColorTransform2::parseXML\n");
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"factorRed" ) ) has = true;
					if( has ) hasFactor = true;
	if( xmlHasProp( node, (const xmlChar *)"factorGreen" ) ) has = true;
					if( has ) hasFactor = true;
	if( xmlHasProp( node, (const xmlChar *)"factorBlue" ) ) has = true;
					if( has ) hasFactor = true;
	if( xmlHasProp( node, (const xmlChar *)"factorAlpha" ) ) has = true;
					if( has ) hasFactor = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"factorRed" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &factorRed);
		xmlFree( tmp );
				int b = SWFBitsNeeded( factorRed, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no factorRed property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"factorGreen" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &factorGreen);
		xmlFree( tmp );
				int b = SWFBitsNeeded( factorGreen, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no factorGreen property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"factorBlue" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &factorBlue);
		xmlFree( tmp );
				int b = SWFBitsNeeded( factorBlue, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no factorBlue property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"factorAlpha" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &factorAlpha);
		xmlFree( tmp );
				int b = SWFBitsNeeded( factorAlpha, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no factorAlpha property in %s element\n", (const char *)node->name );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"offsetRed" ) ) has = true;
					if( has ) hasOffset = true;
	if( xmlHasProp( node, (const xmlChar *)"offsetGreen" ) ) has = true;
					if( has ) hasOffset = true;
	if( xmlHasProp( node, (const xmlChar *)"offsetBlue" ) ) has = true;
					if( has ) hasOffset = true;
	if( xmlHasProp( node, (const xmlChar *)"offsetAlpha" ) ) has = true;
					if( has ) hasOffset = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"offsetRed" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &offsetRed);
		xmlFree( tmp );
				int b = SWFBitsNeeded( offsetRed, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no offsetRed property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"offsetGreen" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &offsetGreen);
		xmlFree( tmp );
				int b = SWFBitsNeeded( offsetGreen, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no offsetGreen property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"offsetBlue" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &offsetBlue);
		xmlFree( tmp );
				int b = SWFBitsNeeded( offsetBlue, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no offsetBlue property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"offsetAlpha" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &offsetAlpha);
		xmlFree( tmp );
				int b = SWFBitsNeeded( offsetAlpha, true );
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no offsetAlpha property in %s element\n", (const char *)node->name );
	}
		}
	}
}
void Header::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Header::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "size" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					size.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	tmp = xmlGetProp( node, (const xmlChar *)"framerate" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &framerate);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no framerate property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"frames" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		frames = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "tags" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Tag* item = Tag::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						tags.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void LineStyle::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("LineStyle::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"width" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		width = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->tagVersion < 4 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	}
	if( ctx->tagVersion > 3 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"startCapStyle" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &startCapStyle);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no startCapStyle property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"jointStyle" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &jointStyle);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no jointStyle property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasFill" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasFill = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"noHScale" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		noHScale = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"noVScale" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		noVScale = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pixelHinting" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pixelHinting = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"noClose" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		noClose = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"endCapStyle" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &endCapStyle);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no endCapStyle property in %s element\n", (const char *)node->name );
	}
	if( jointStyle==2 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"miterLimitFactor" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		miterLimitFactor = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no miterLimitFactor property in %s element\n", (const char *)node->name );
	}
	}
	if( hasFill ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "fillStyles" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Style* item = Style::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						fillStyles.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	}
	if( !hasFill ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "fillColor" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					fillColor.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	}
	}
}
void StyleList::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("StyleList::parseXML\n");
		ctx->fillBits = 0;
		ctx->lineBits = 0;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "fillStyles" ) ) {
			n_fillStyles=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Style* item = Style::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						fillStyles.append( item );
						n_fillStyles++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "lineStyles" ) ) {
			n_lineStyles=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					LineStyle* item = LineStyle::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						lineStyles.append( item );
						n_lineStyles++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
fillBits = SWFBitsNeeded( n_fillStyles );
				if( fillBits > ctx->fillBits ) ctx->fillBits = fillBits;
			lineBits = SWFBitsNeeded( n_lineStyles );
				if( lineBits > ctx->lineBits ) ctx->lineBits = lineBits;
}
void ShapeSetup::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ShapeSetup::parseXML\n");
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"x" ) ) has = true;
					if( has ) hasMoveTo = true;
	if( xmlHasProp( node, (const xmlChar *)"y" ) ) has = true;
					if( has ) hasMoveTo = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"x" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &x);
		xmlFree( tmp );
				int b = SWFBitsNeeded( x, true );
				if( b > xybits ) xybits = b;
	} else {
		fprintf(stderr,"WARNING: no x property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"y" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &y);
		xmlFree( tmp );
				int b = SWFBitsNeeded( y, true );
				if( b > xybits ) xybits = b;
	} else {
		fprintf(stderr,"WARNING: no y property in %s element\n", (const char *)node->name );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fillStyle0" ) ) has = true;
					if( has ) hasFillStyle0 = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fillStyle0" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &fillStyle0);
		xmlFree( tmp );
				int b = SWFBitsNeeded( fillStyle0 );
				if( b > ctx->fillBits ) ctx->fillBits = b;
	} else {
		fprintf(stderr,"WARNING: no fillStyle0 property in %s element\n", (const char *)node->name );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fillStyle1" ) ) has = true;
					if( has ) hasFillStyle1 = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fillStyle1" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &fillStyle1);
		xmlFree( tmp );
				int b = SWFBitsNeeded( fillStyle1 );
				if( b > ctx->fillBits ) ctx->fillBits = b;
	} else {
		fprintf(stderr,"WARNING: no fillStyle1 property in %s element\n", (const char *)node->name );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"lineStyle" ) ) has = true;
					if( has ) hasLineStyle = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"lineStyle" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &lineStyle);
		xmlFree( tmp );
				int b = SWFBitsNeeded( lineStyle );
				if( b > ctx->lineBits ) ctx->lineBits = b;
	} else {
		fprintf(stderr,"WARNING: no lineStyle property in %s element\n", (const char *)node->name );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "styles" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasNewStyles = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "styles" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					styles.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
}
void CurveTo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("CurveTo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"x1" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &x1);
		xmlFree( tmp );
				int b = SWFBitsNeeded( x1, true );
				b -= 2;
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no x1 property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"y1" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &y1);
		xmlFree( tmp );
				int b = SWFBitsNeeded( y1, true );
				b -= 2;
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no y1 property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"x2" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &x2);
		xmlFree( tmp );
				int b = SWFBitsNeeded( x2, true );
				b -= 2;
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no x2 property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"y2" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &y2);
		xmlFree( tmp );
				int b = SWFBitsNeeded( y2, true );
				b -= 2;
				if( b > bits ) bits = b;
	} else {
		fprintf(stderr,"WARNING: no y2 property in %s element\n", (const char *)node->name );
	}
}
void Shape::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("Shape::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "edges" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					ShapeItem* item = ShapeItem::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						edges.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void GlyphShape::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("GlyphShape::parseXML\n");
	ctx->fillBits = 1;
	ctx->lineBits = 0;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "edges" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					ShapeItem* item = ShapeItem::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						edges.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void GradientItem::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("GradientItem::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"position" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		position = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void Symbol::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Symbol::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
}
void Frame::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Frame::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"label" );
	if( tmp ) {
		label = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no label property in %s element\n", (const char *)node->name );
		label = strdupx("[undefined]");
	}
}
void Scene::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Scene::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
}
void Parameter::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Parameter::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"reg" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		reg = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
}
void UChar::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("UChar::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void UShort::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("UShort::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void ULong::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("ULong::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &value);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no value property in %s element\n", (const char *)node->name );
	}
}
void Short::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Short::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void Float::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Float::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		value = tmp_float;
		xmlFree( tmp );
	}
}
void Double::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Double::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		value = tmp_float;
		xmlFree( tmp );
	}
}
void Kerning::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Kerning::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"a" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		a = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"b" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		b = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"adjustment" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &adjustment);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no adjustment property in %s element\n", (const char *)node->name );
	}
}
void WideKerning::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("WideKerning::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"a" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		a = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"b" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		b = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"adjustment" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		adjustment = tmp_int;
		xmlFree( tmp );
	}
}
void TextEntry::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("TextEntry::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"glyph" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &glyph);
		xmlFree( tmp );
				int b = SWFBitsNeeded( glyph );
				if( b > ctx->glyphBits ) ctx->glyphBits = b;
	} else {
		fprintf(stderr,"WARNING: no glyph property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"advance" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &advance);
		xmlFree( tmp );
				int b = SWFBitsNeeded( advance, true );
				if( b > ctx->advanceBits ) ctx->advanceBits = b;
	} else {
		fprintf(stderr,"WARNING: no advance property in %s element\n", (const char *)node->name );
	}
}
void TextEntry2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("TextEntry2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"glyph" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &glyph);
		xmlFree( tmp );
				int b = SWFBitsNeeded( glyph );
				if( b > ctx->glyphBits ) ctx->glyphBits = b;
	} else {
		fprintf(stderr,"WARNING: no glyph property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"advance" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &advance);
		xmlFree( tmp );
				int b = SWFBitsNeeded( advance, true );
				if( b > ctx->advanceBits ) ctx->advanceBits = b;
	} else {
		fprintf(stderr,"WARNING: no advance property in %s element\n", (const char *)node->name );
	}
}
void TextRecord6::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("TextRecord6::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"isSetup" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isSetup = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"objectID" ) ) has = true;
					if( has ) isSetup = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "color" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) isSetup = true;
	if( xmlHasProp( node, (const xmlChar *)"x" ) ) has = true;
					if( has ) isSetup = true;
	if( xmlHasProp( node, (const xmlChar *)"y" ) ) has = true;
					if( has ) isSetup = true;
	if( xmlHasProp( node, (const xmlChar *)"fontHeight" ) ) has = true;
					if( has ) isSetup = true;
		if( has ) {
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"objectID" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "color" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasColor = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"x" ) ) has = true;
					if( has ) hasMoveX = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"x" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		x = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"y" ) ) has = true;
					if( has ) hasMoveY = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"y" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		y = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fontHeight" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fontHeight" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		fontHeight = tmp_int;
		xmlFree( tmp );
	}
		}
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "glyphs" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) isSetup = !true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "glyphs" ) ) {
			nGlyphs=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextEntry* item = TextEntry::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						glyphs.append( item );
						nGlyphs++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void TextRecord62::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("TextRecord62::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"isSetup" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isSetup = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"objectID" ) ) has = true;
					if( has ) isSetup = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "color" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) isSetup = true;
	if( xmlHasProp( node, (const xmlChar *)"x" ) ) has = true;
					if( has ) isSetup = true;
	if( xmlHasProp( node, (const xmlChar *)"y" ) ) has = true;
					if( has ) isSetup = true;
	if( xmlHasProp( node, (const xmlChar *)"fontHeight" ) ) has = true;
					if( has ) isSetup = true;
		if( has ) {
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"objectID" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "color" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasColor = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"x" ) ) has = true;
					if( has ) hasMoveX = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"x" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		x = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"y" ) ) has = true;
					if( has ) hasMoveY = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"y" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		y = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fontHeight" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fontHeight" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		fontHeight = tmp_int;
		xmlFree( tmp );
	}
		}
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "glyphs" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) isSetup = !true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "glyphs" ) ) {
			nGlyphs=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextEntry2* item = TextEntry2::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						glyphs.append( item );
						nGlyphs++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void TextRecord7::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("TextRecord7::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"isSetup" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isSetup = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"objectID" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "color" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasColor = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"x" ) ) has = true;
					if( has ) hasMoveX = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"x" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		x = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"y" ) ) has = true;
					if( has ) hasMoveY = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"y" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		y = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fontHeight" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fontHeight" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		fontHeight = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "glyphs" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) isSetup = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "glyphs" ) ) {
			nGlyphs=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextEntry* item = TextEntry::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						glyphs.append( item );
						nGlyphs++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void TextRecord72::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("TextRecord72::parseXML\n");
	ctx->alpha = 1;
	tmp = xmlGetProp( node, (const xmlChar *)"isSetup" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isSetup = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fontRef" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fontRef" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		fontRef = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "color" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasColor = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"x" ) ) has = true;
					if( has ) hasMoveX = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"x" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		x = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"y" ) ) has = true;
					if( has ) hasMoveY = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"y" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		y = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fontHeight" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fontHeight" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		fontHeight = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "glyphs" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) isSetup = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "glyphs" ) ) {
			nGlyphs=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextEntry2* item = TextEntry2::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						glyphs.append( item );
						nGlyphs++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void TextRecord::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("TextRecord::parseXML\n");
	if( ctx->tagVersion < 2 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "records" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextRecord6* item = TextRecord6::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						records.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	}
	if( ctx->tagVersion >= 2 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "string" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					string.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	}
}
void TextRecord2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("TextRecord2::parseXML\n");
	if( ctx->swfVersion < 7 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "records" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextRecord62* item = TextRecord62::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						records.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	}
	if( ctx->swfVersion >= 7 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "textString" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					textString.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	}
}
void Button::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Button::parseXML\n");
	if( ctx->swfVersion < 8 ) {
	}
	if( ctx->swfVersion >= 8 ) {
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hitTest" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hitTest = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"down" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		down = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"over" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		over = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"up" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		up = tmp_int;
		xmlFree( tmp );
	}
	if( hitTest || down || over || up ) {
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"depth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		depth = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "transform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					transform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	if( ctx->tagVersion >= 2 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "colorTransform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					colorTransform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "filters" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasFilterList = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "filters" ) ) {
			numFilters=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Filter* item = Filter::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						filters.append( item );
						numFilters++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"blendMode" ) ) has = true;
					if( has ) hasBlendMode = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"blendMode" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		blendMode = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	}
}
void Event::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Event::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"flags1" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		flags1 = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->swfVersion>=6 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"flags2" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		flags2 = tmp_int;
		xmlFree( tmp );
	}
	}
	if( (flags1 | flags2) ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
				size_t l = 0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Action* item = Action::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						actions.append( item );
							l += item->getSize(ctx, l);
					}
				}
				child = child->next;
			}
			actionLength = (l/8);
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	}
}
void Condition::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Condition::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"next" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		next = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"menuEnter" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		menuEnter = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pointerReleaseOutside" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pointerReleaseOutside = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pointerDragEnter" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pointerDragEnter = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pointerDragLeave" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pointerDragLeave = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pointerReleaseInside" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pointerReleaseInside = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pointerPush" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pointerPush = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pointerLeave" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pointerLeave = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"pointerEnter" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		pointerEnter = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"key" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &key);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no key property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"menuLeave" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		menuLeave = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Action* item = Action::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						actions.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void U30::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("U30::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void S24::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("S24::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void ValueKind::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("ValueKind::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"kind" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		kind = tmp_int;
		xmlFree( tmp );
	}
}
void MethodInfo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("MethodInfo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"retType" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		retType = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "paramTypes" ) ) {
			paramCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						paramTypes.append( item );
						paramCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasParamNames" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasParamNames = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"setSDXNs" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		setSDXNs = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isExplicit" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isExplicit = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"ignoreRest" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		ignoreRest = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasOptional" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasOptional = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"needRest" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		needRest = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"needActivation" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		needActivation = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"needArguments" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		needArguments = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "optional" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasOptional = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "optional" ) ) {
			optionalCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					ValueKind* item = ValueKind::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						optional.append( item );
						optionalCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "paramNames" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasParamNames = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "paramNames" ) ) {
			paramCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						paramNames.append( item );
						paramCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void MetadataInfo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("MetadataInfo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "keys" ) ) {
			valuesCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						keys.append( item );
						valuesCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "values" ) ) {
			valuesCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						values.append( item );
						valuesCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void NamespaceSet::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("NamespaceSet::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "namespaces" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						namespaces.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void TraitInfo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("TraitInfo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"override" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		override = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"final" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		final = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "trait" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Trait* item = Trait::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						trait.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "metadata" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasMetadata = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "metadata" ) ) {
			metadataCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						metadata.append( item );
						metadataCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void InstanceInfo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("InstanceInfo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"superIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		superIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasProtectedNS" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasProtectedNS = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"interface" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		interface = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"final" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		final = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"sealed" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		sealed = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"protectedNS" ) ) has = true;
					if( has ) hasProtectedNS = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"protectedNS" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		protectedNS = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "interfaces" ) ) {
			interfaceCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						interfaces.append( item );
						interfaceCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"iInitIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		iInitIndex = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "traits" ) ) {
			traitCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TraitInfo* item = TraitInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						traits.append( item );
						traitCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void ClassInfo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ClassInfo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"cInitIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		cInitIndex = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "traits" ) ) {
			traitCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TraitInfo* item = TraitInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						traits.append( item );
						traitCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void ScriptInfo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ScriptInfo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"initIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		initIndex = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "traits" ) ) {
			traitCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TraitInfo* item = TraitInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						traits.append( item );
						traitCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void Exception::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Exception::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"tryStart" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		tryStart = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"tryEnd" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		tryEnd = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"type" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		type = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void MethodBody::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("MethodBody::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"methodInfo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		methodInfo = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"maxStack" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		maxStack = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"maxRegs" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		maxRegs = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"scopeDepth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		scopeDepth = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"maxScope" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		maxScope = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "code" ) ) {
				size_t l = 0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					OpCode* item = OpCode::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						code.append( item );
							l += item->getSize(ctx, l);
					}
				}
				child = child->next;
			}
			codeLength = (l/8);
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"exceptionCount" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		exceptionCount = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "exceptions" ) ) {
			exceptionCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Exception* item = Exception::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						exceptions.append( item );
						exceptionCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "traits" ) ) {
			traitCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TraitInfo* item = TraitInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						traits.append( item );
						traitCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void Constants::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("Constants::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "ints" ) ) {
			intCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						ints.append( item );
						intCount++;
					}
				}
				child = child->next;
			}
				if( intCount > 0 ) {
					intCount += 1;
				}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "uints" ) ) {
			uintCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					U30* item = U30::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						uints.append( item );
						uintCount++;
					}
				}
				child = child->next;
			}
				if( uintCount > 0 ) {
					uintCount += 1;
				}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "doubles" ) ) {
			doubleCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Double* item = Double::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						doubles.append( item );
						doubleCount++;
					}
				}
				child = child->next;
			}
				if( doubleCount > 0 ) {
					doubleCount += 1;
				}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "strings" ) ) {
			stringCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					String2* item = String2::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						strings.append( item );
						stringCount++;
					}
				}
				child = child->next;
			}
				if( stringCount > 0 ) {
					stringCount += 1;
				}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "namespaces" ) ) {
			namespaceConstantCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					NamespaceConstant* item = NamespaceConstant::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						namespaces.append( item );
						namespaceConstantCount++;
					}
				}
				child = child->next;
			}
				if( namespaceConstantCount > 0 ) {
					namespaceConstantCount += 1;
				}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "namespaceSets" ) ) {
			namespaceSetCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					NamespaceSet* item = NamespaceSet::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						namespaceSets.append( item );
						namespaceSetCount++;
					}
				}
				child = child->next;
			}
				if( namespaceSetCount > 0 ) {
					namespaceSetCount += 1;
				}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "multinames" ) ) {
			multinameConstantCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					MultinameConstant* item = MultinameConstant::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						multinames.append( item );
						multinameConstantCount++;
					}
				}
				child = child->next;
			}
				if( multinameConstantCount > 0 ) {
					multinameConstantCount += 1;
				}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void Action3::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Action3::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"minorVersion" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		minorVersion = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"majorVersion" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		majorVersion = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "constants" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					constants.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "methods" ) ) {
			methodInfoCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					MethodInfo* item = MethodInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						methods.append( item );
						methodInfoCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "metadata" ) ) {
			metadataInfoCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					MetadataInfo* item = MetadataInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						metadata.append( item );
						metadataInfoCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "instances" ) ) {
			classCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					InstanceInfo* item = InstanceInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						instances.append( item );
						classCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "classes" ) ) {
			classCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					ClassInfo* item = ClassInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						classes.append( item );
						classCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "scripts" ) ) {
			scriptCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					ScriptInfo* item = ScriptInfo::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						scripts.append( item );
						scriptCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "methodBodies" ) ) {
			methodBodyCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					MethodBody* item = MethodBody::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						methodBodies.append( item );
						methodBodyCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void ZoneData::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("ZoneData::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"position" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		position = tmp_float;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"size" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		size = tmp_float;
		xmlFree( tmp );
	}
}
void ZoneArray::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ZoneArray::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "zones" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					ZoneData* item = ZoneData::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						zones.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"zoneX" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &zoneX);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no zoneX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"zoneY" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &zoneY);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no zoneY property in %s element\n", (const char *)node->name );
	}
}
void UnknownFilter::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("UnknownFilter::parseXML\n");
	{
		data = NULL;
		len = 0;
		xmlChar *xmld = xmlNodeGetContent( node );
		char *d = (char *)xmld;
		if( d ) {
			// unsure if this is neccessary
			for( int i=strlen(d)-1; i>0 && isspace(d[i]); i-- ) d[i]=0;
			while( isspace(d[0]) ) d++;
			int l = strlen(d); //BASE64_GET_MAX_DECODED_LEN(strlen( d ));
			char *dst = new char[ l ];
			int lout = base64_decode( dst, (char*)d, l );
			if( lout > 0 ) {
				len = lout;
				data = new unsigned char[ lout ];
				memcpy( data, dst, lout );
			}
			delete dst;
			xmlFree( xmld );
		}
	}
}
void DropShadow::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DropShadow::parseXML\n");
	ctx->alpha = 1;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurX = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurY = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurY property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"angle" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		angle = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no angle property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"distance" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		distance = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no distance property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"strength" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		strength = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no strength property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"innerShadow" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		innerShadow = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"knockout" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		knockout = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"passes" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &passes);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no passes property in %s element\n", (const char *)node->name );
	}
}
void Blur::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Blur::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"blurX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurX = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurY = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurY property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"passes" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &passes);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no passes property in %s element\n", (const char *)node->name );
	}
}
void Glow::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Glow::parseXML\n");
	ctx->alpha = 1;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurX = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurY = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurY property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"strength" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		strength = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no strength property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"innerGlow" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		innerGlow = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"knockout" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		knockout = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"passes" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &passes);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no passes property in %s element\n", (const char *)node->name );
	}
}
void Bevel::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Bevel::parseXML\n");
	ctx->alpha = 1;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "shadowColor" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					shadowColor.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "highlightColor" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					highlightColor.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurX = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurY = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurY property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"angle" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		angle = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no angle property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"distance" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		distance = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no distance property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"strength" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		strength = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no strength property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"innerShadow" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		innerShadow = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"knockout" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		knockout = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"onTop" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		onTop = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"passes" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &passes);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no passes property in %s element\n", (const char *)node->name );
	}
}
void GradientGlow::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("GradientGlow::parseXML\n");
	ctx->alpha = 1;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "colors" ) ) {
			numColors=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Color* item = Color::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						colors.append( item );
						numColors++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "ratio" ) ) {
			numColors=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					UChar* item = UChar::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						ratio.append( item );
						numColors++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurX = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurY = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurY property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"angle" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		angle = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no angle property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"distance" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		distance = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no distance property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"strength" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		strength = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no strength property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"innerGlow" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		innerGlow = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"knockout" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		knockout = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"onTop" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		onTop = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"passes" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &passes);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no passes property in %s element\n", (const char *)node->name );
	}
}
void Convolution::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Convolution::parseXML\n");
	ctx->alpha = 1;
	tmp = xmlGetProp( node, (const xmlChar *)"matrixX" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		matrixX = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"matrixY" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		matrixY = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"divizor" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		divizor = tmp_float;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"bias" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		bias = tmp_float;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Float* item = Float::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						matrix.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "defaultColor" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					defaultColor.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	tmp = xmlGetProp( node, (const xmlChar *)"clamp" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		clamp = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"preserveAlpha" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		preserveAlpha = tmp_int;
		xmlFree( tmp );
	}
}
void ColorMatrix::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("ColorMatrix::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Float* item = Float::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						matrix.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void GradientBevel::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("GradientBevel::parseXML\n");
	ctx->alpha = 1;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "colors" ) ) {
			numColors=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Color* item = Color::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						colors.append( item );
						numColors++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "ratio" ) ) {
			numColors=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					UChar* item = UChar::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						ratio.append( item );
						numColors++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurX" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurX = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurX property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"blurY" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		blurY = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no blurY property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"angle" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		angle = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no angle property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"distance" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		distance = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no distance property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"strength" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		strength = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no strength property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"innerGlow" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		innerGlow = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"knockout" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		knockout = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"onTop" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		onTop = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"passes" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &passes);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no passes property in %s element\n", (const char *)node->name );
	}
}
void Solid::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("Solid::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void LinearGradient::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("LinearGradient::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					matrix.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"spreadMode" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &spreadMode);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no spreadMode property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"interpolationMode" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &interpolationMode);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no interpolationMode property in %s element\n", (const char *)node->name );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "gradientColors" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					GradientItem* item = GradientItem::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						gradientColors.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void RadialGradient::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("RadialGradient::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					matrix.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"spreadMode" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &spreadMode);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no spreadMode property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"interpolationMode" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &interpolationMode);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no interpolationMode property in %s element\n", (const char *)node->name );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "gradientColors" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					GradientItem* item = GradientItem::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						gradientColors.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void ShiftedRadialGradient::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ShiftedRadialGradient::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					matrix.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	if( ctx->tagVersion < 4 ) {
	}
	if( ctx->tagVersion >= 4 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"spreadMode" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &spreadMode);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no spreadMode property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"interpolationMode" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &interpolationMode);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no interpolationMode property in %s element\n", (const char *)node->name );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "gradientColors" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					GradientItem* item = GradientItem::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						gradientColors.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"shift" );
	if( tmp ) {
		double t;
		sscanf( (char *)tmp, "%lg", &t);
		shift = t;
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no shift property in %s element\n", (const char *)node->name );
	}
}
void TiledBitmap::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("TiledBitmap::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					matrix.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void ClippedBitmap::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ClippedBitmap::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					matrix.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void TiledBitmap2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("TiledBitmap2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					matrix.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void ClippedBitmap2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ClippedBitmap2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "matrix" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					matrix.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void UnknownTag::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("UnknownTag::parseXML\n");
	{
		data = NULL;
		len = 0;
		xmlChar *xmld = xmlNodeGetContent( node );
		char *d = (char *)xmld;
		if( d ) {
			// unsure if this is neccessary
			for( int i=strlen(d)-1; i>0 && isspace(d[i]); i-- ) d[i]=0;
			while( isspace(d[0]) ) d++;
			int l = strlen(d); //BASE64_GET_MAX_DECODED_LEN(strlen( d ));
			char *dst = new char[ l ];
			int lout = base64_decode( dst, (char*)d, l );
			if( lout > 0 ) {
				len = lout;
				data = new unsigned char[ lout ];
				memcpy( data, dst, lout );
			}
			delete dst;
			xmlFree( xmld );
		}
	}
		tmp = xmlGetProp( node, (const xmlChar *)"id" );
		if( tmp ) { 
			sscanf( (char *)tmp, "%X", &type ); 
			xmlFree( (xmlChar *)tmp ); 
		}
}
void End::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("End::parseXML\n");
}
void ShowFrame::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("ShowFrame::parseXML\n");
}
void DefineShape::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineShape::parseXML\n");
	ctx->alpha = 0;
	ctx->many_shapes = 0;
	ctx->tagVersion = 1;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					bounds.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "styles" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					styles.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "shapes" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					shapes.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void RemoveObject::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("RemoveObject::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"depth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		depth = tmp_int;
		xmlFree( tmp );
	}
}
void DefineBits::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineBits::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void SetBackgroundColor::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("SetBackgroundColor::parseXML\n");
	ctx->alpha = 0;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineText::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineText::parseXML\n");
		ctx->glyphBits = 0;
		ctx->advanceBits = 0;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					bounds.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "transform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					transform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	ctx->alpha = 0;
	ctx->tagVersion = 1;
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "records" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextRecord* item = TextRecord::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						records.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
glyphBits = ctx->glyphBits;
			advanceBits = ctx->advanceBits;
}
void DefineText2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineText2::parseXML\n");
		ctx->glyphBits = 0;
		ctx->advanceBits = 0;
	ctx->alpha = 1;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					bounds.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "transform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					transform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "records" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					TextRecord2* item = TextRecord2::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						records.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
glyphBits = ctx->glyphBits;
			advanceBits = ctx->advanceBits;
}
void DoAction::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("DoAction::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Action* item = Action::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						actions.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void DefineFontInfo::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineFontInfo::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"smallTextOrUnicode" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		smallTextOrUnicode = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isShiftJIS" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isShiftJIS = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isANSII" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isANSII = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isItalic" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isItalic = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isBold" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isBold = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isWide" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isWide = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->swfVersion>=6 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"language" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		language = tmp_int;
		xmlFree( tmp );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "map" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					map.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineSound::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineSound::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"format" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &format);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no format property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"rate" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &rate);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no rate property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"is16bit" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		is16bit = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"stereo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		stereo = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"samples" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		samples = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void StartSound::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("StartSound::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"stopPlayback" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		stopPlayback = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"noMultiple" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		noMultiple = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasEnvelope" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasEnvelope = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasLoop" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasLoop = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasOutPoint" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasOutPoint = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasInPoint" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasInPoint = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"inPoint" ) ) has = true;
					if( has ) hasInPoint = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"inPoint" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		inPoint = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"outPoint" ) ) has = true;
					if( has ) hasOutPoint = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"outPoint" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		outPoint = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"loop" ) ) has = true;
					if( has ) hasLoop = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"loop" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		loop = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"envelopeCount" ) ) has = true;
					if( has ) hasEnvelope = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "envelopeData" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasEnvelope = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"envelopeCount" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		envelopeCount = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "envelopeData" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					envelopeData.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
}
void DefineShape2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineShape2::parseXML\n");
	ctx->alpha = 0;
	ctx->many_shapes = 1;
	ctx->tagVersion = 2;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					bounds.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "styles" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					styles.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "shapes" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					shapes.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineShape3::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineShape3::parseXML\n");
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 3;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					bounds.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "styles" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					styles.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "shapes" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					shapes.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineShape4::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineShape4::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineShape5::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineShape5::parseXML\n");
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 5;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					bounds.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "strokeBounds" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					strokeBounds.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	tmp = xmlGetProp( node, (const xmlChar *)"nonScalingStrokes" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nonScalingStrokes = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"scalingStrokes" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		scalingStrokes = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "styles" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					styles.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "shapes" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					shapes.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineMorphShape::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineMorphShape::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineFontInfo2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineFontInfo2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"smallTextOrUnicode" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		smallTextOrUnicode = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isShiftJIS" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isShiftJIS = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isANSII" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isANSII = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isItalic" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isItalic = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isBold" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isBold = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isWide" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isWide = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->swfVersion>=6 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"language" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		language = tmp_int;
		xmlFree( tmp );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "map" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					map.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void SoundStreamHead::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("SoundStreamHead::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"playbackRate" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &playbackRate);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no playbackRate property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"playbackSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		playbackSize = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"playbackStereo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		playbackStereo = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"compression" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &compression);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no compression property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"soundRate" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &soundRate);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no soundRate property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"soundSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		soundSize = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"soundStereo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		soundStereo = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"sampleSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		sampleSize = tmp_int;
		xmlFree( tmp );
	}
	if( compression==2 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "latencySeek" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					latencySeek.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	}
}
void DefineBitsLossless::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineBitsLossless::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"format" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		format = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"width" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		width = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"height" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		height = tmp_int;
		xmlFree( tmp );
	}
	if( format==3 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"n_colormap" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		n_colormap = tmp_int;
		xmlFree( tmp );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineBitsJPEG2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineBitsJPEG2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineBitsJPEG3::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineBitsJPEG3::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"offset_to_alpha" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		offset_to_alpha = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineBitsLossless2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineBitsLossless2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"format" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		format = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"width" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		width = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"height" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		height = tmp_int;
		xmlFree( tmp );
	}
	if( format==3 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"n_colormap" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		n_colormap = tmp_int;
		xmlFree( tmp );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void PlaceObject2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("PlaceObject2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"replace" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		replace = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"depth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		depth = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"objectID" ) ) has = true;
					if( has ) hasID = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "transform" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasTransform = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "transform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					transform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "colorTransform" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasColorTransform = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "colorTransform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					colorTransform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"morph" ) ) has = true;
					if( has ) hasMorph = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"morph" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		morph = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"name" ) ) has = true;
					if( has ) hasName = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"clipDepth" ) ) has = true;
					if( has ) hasClipDepth = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"clipDepth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		clipDepth = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"allflags1" ) ) has = true;
					if( has ) hasEventHandler = true;
	if( xmlHasProp( node, (const xmlChar *)"allflags2" ) ) has = true;
					if( has ) hasEventHandler = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "events" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasEventHandler = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"allflags1" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		allflags1 = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->swfVersion>=6 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"allflags2" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		allflags2 = tmp_int;
		xmlFree( tmp );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "events" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Event* item = Event::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						events.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void RemoveObject2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("RemoveObject2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"depth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		depth = tmp_int;
		xmlFree( tmp );
	}
}
void DefineEditText::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineEditText::parseXML\n");
	ctx->alpha = 1;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "size" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					size.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	tmp = xmlGetProp( node, (const xmlChar *)"wordWrap" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		wordWrap = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"multiLine" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		multiLine = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"password" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		password = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"readOnly" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		readOnly = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"autoSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		autoSize = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasLayout" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasLayout = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"notSelectable" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		notSelectable = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"hasBorder" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasBorder = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isHTML" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isHTML = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"useOutlines" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		useOutlines = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"fontRef" ) ) has = true;
					if( has ) hasFont = true;
	if( xmlHasProp( node, (const xmlChar *)"fontHeight" ) ) has = true;
					if( has ) hasFont = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"fontRef" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		fontRef = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"fontHeight" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		fontHeight = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "color" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasColor = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "color" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					color.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"maxLength" ) ) has = true;
					if( has ) hasMaxLength = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"maxLength" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		maxLength = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"align" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"leftMargin" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"rightMargin" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"indent" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"leading" ) ) has = true;
					if( has ) hasLayout = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"align" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		align = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"leftMargin" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		leftMargin = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"rightMargin" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		rightMargin = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"indent" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		indent = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"leading" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		leading = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"variableName" );
	if( tmp ) {
		variableName = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no variableName property in %s element\n", (const char *)node->name );
		variableName = strdupx("[undefined]");
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"initialText" ) ) has = true;
					if( has ) hasText = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"initialText" );
	if( tmp ) {
		initialText = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no initialText property in %s element\n", (const char *)node->name );
		initialText = strdupx("[undefined]");
	}
		}
	}
}
void DefineSprite::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineSprite::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"frames" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		frames = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "tags" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Tag* item = Tag::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						tags.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void FrameLabel::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("FrameLabel::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"label" );
	if( tmp ) {
		label = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no label property in %s element\n", (const char *)node->name );
		label = strdupx("[undefined]");
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "flags" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					flags.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void SoundStreamHead2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("SoundStreamHead2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"playbackRate" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &playbackRate);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no playbackRate property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"playbackSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		playbackSize = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"playbackStereo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		playbackStereo = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"compression" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &compression);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no compression property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"soundRate" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &soundRate);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no soundRate property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"soundSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		soundSize = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"soundStereo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		soundStereo = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"sampleSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		sampleSize = tmp_int;
		xmlFree( tmp );
	}
	if( compression==2 ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "latencySeek" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					latencySeek.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	}
}
void DefineFont::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineFont::parseXML\n");
	ctx->tagVersion = 1;
	ctx->wideGlyphOffsets = 0;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineFont2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineFont2::parseXML\n");
		ctx->wideGlyphOffsets = 0;
		ctx->wideMap = 0;
		ctx->glyphCount = 0;
	ctx->tagVersion = 2;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isShiftJIS" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isShiftJIS = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isUnicode" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isUnicode = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isANSII" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isANSII = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"wideGlyphOffsets" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		wideGlyphOffsets = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"italic" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		italic = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"bold" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		bold = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"language" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		language = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "glyphs" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					glyphs.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"ascent" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"descent" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"leading" ) ) has = true;
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "advance" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "bounds" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "wideKerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "kerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"ascent" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		ascent = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"descent" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		descent = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"leading" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		leading = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "advance" ) ) {
			glyphCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Short* item = Short::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						advance.append( item );
						glyphCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
			glyphCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Rectangle* item = Rectangle::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						bounds.append( item );
						glyphCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "wideKerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) wideMap = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "wideKerning" ) ) {
			kerningCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					WideKerning* item = WideKerning::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						wideKerning.append( item );
						kerningCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "kerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) wideMap = !true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "kerning" ) ) {
			kerningCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Kerning* item = Kerning::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						kerning.append( item );
						kerningCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
		}
	}
				ctx->wideGlyphOffsets = wideGlyphOffsets;
				ctx->wideMap = wideMap;
			glyphCount = ctx->glyphCount;
}
void DefineFont3::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineFont3::parseXML\n");
		ctx->wideGlyphOffsets = 0;
		ctx->wideMap = 0;
		ctx->glyphCount = 0;
	ctx->tagVersion = 2;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isShiftJIS" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isShiftJIS = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isUnicode" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isUnicode = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"isANSII" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		isANSII = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"wideGlyphOffsets" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		wideGlyphOffsets = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"italic" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		italic = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"bold" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		bold = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"language" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		language = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "glyphs" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					glyphs.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"ascent" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"descent" ) ) has = true;
					if( has ) hasLayout = true;
	if( xmlHasProp( node, (const xmlChar *)"leading" ) ) has = true;
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "advance" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "bounds" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "wideKerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "kerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasLayout = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"ascent" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		ascent = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"descent" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		descent = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"leading" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		leading = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "advance" ) ) {
			glyphCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Short* item = Short::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						advance.append( item );
						glyphCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "bounds" ) ) {
			glyphCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Rectangle* item = Rectangle::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						bounds.append( item );
						glyphCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "wideKerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) wideMap = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "wideKerning" ) ) {
			kerningCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					WideKerning* item = WideKerning::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						wideKerning.append( item );
						kerningCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "kerning" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) wideMap = !true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "kerning" ) ) {
			kerningCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Kerning* item = Kerning::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						kerning.append( item );
						kerningCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
		}
	}
				ctx->wideGlyphOffsets = wideGlyphOffsets;
				ctx->wideMap = wideMap;
			glyphCount = ctx->glyphCount;
}
void DefineButton::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineButton::parseXML\n");
	ctx->tagVersion = 1;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "buttons" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Button* item = Button::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						buttons.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Action* item = Action::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						actions.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void DefineButton2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineButton2::parseXML\n");
	ctx->tagVersion = 2;
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"menu" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		menu = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"buttonsSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		buttonsSize = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "buttons" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Button* item = Button::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						buttons.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "conditions" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Condition* item = Condition::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						conditions.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void Export::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("Export::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "symbols" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Symbol* item = Symbol::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						symbols.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void Import::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("Import::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"url" );
	if( tmp ) {
		url = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no url property in %s element\n", (const char *)node->name );
		url = strdupx("[undefined]");
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "symbols" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Symbol* item = Symbol::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						symbols.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void DoInitAction::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DoInitAction::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"sprite" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		sprite = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Action* item = Action::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						actions.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void SoundStreamBlock::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("SoundStreamBlock::parseXML\n");
	{
		data = NULL;
		len = 0;
		xmlChar *xmld = xmlNodeGetContent( node );
		char *d = (char *)xmld;
		if( d ) {
			// unsure if this is neccessary
			for( int i=strlen(d)-1; i>0 && isspace(d[i]); i-- ) d[i]=0;
			while( isspace(d[0]) ) d++;
			int l = strlen(d); //BASE64_GET_MAX_DECODED_LEN(strlen( d ));
			char *dst = new char[ l ];
			int lout = base64_decode( dst, (char*)d, l );
			if( lout > 0 ) {
				len = lout;
				data = new unsigned char[ lout ];
				memcpy( data, dst, lout );
			}
			delete dst;
			xmlFree( xmld );
		}
	}
}
void DefineVideoStream::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("DefineVideoStream::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"frames" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		frames = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"width" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		width = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"height" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		height = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"deblocking" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &deblocking);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no deblocking property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"smoothing" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		smoothing = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"codec" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		codec = tmp_int;
		xmlFree( tmp );
	}
}
void VideoFrame::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("VideoFrame::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"frame" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		frame = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void ScriptLimits::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("ScriptLimits::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"maxRecursionDepth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		maxRecursionDepth = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"timeout" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		timeout = tmp_int;
		xmlFree( tmp );
	}
}
void SetTabIndex::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("SetTabIndex::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"depth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		depth = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"tabIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		tabIndex = tmp_int;
		xmlFree( tmp );
	}
}
void PlaceObject3::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("PlaceObject3::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"replace" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		replace = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"depth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		depth = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"objectID" ) ) has = true;
					if( has ) hasID = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "transform" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasTransform = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "transform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					transform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "colorTransform" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasColorTransform = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "colorTransform" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					colorTransform.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"morph" ) ) has = true;
					if( has ) hasMorph = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"morph" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		morph = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"name" ) ) has = true;
					if( has ) hasName = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"clipDepth" ) ) has = true;
					if( has ) hasClipDepth = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"clipDepth" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		clipDepth = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "filters" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasFilterList = true;
		if( has ) {
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "filters" ) ) {
			numFilters=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Filter* item = Filter::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						filters.append( item );
						numFilters++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"blendMode" ) ) has = true;
					if( has ) hasBlendMode = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"blendMode" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		blendMode = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"bitmapCaching" ) ) has = true;
					if( has ) hasCacheAsBitmap = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"bitmapCaching" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		bitmapCaching = tmp_int;
		xmlFree( tmp );
	}
		}
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"allflags1" ) ) has = true;
					if( has ) hasEventHandler = true;
	if( xmlHasProp( node, (const xmlChar *)"allflags2" ) ) has = true;
					if( has ) hasEventHandler = true;
	{
		xmlNodePtr child = node->children;
		while( child && !has ) {
			if( !strcmp( (const char *)child->name, "events" ) ) has = true;
			child = child->next;
		}
	}
					if( has ) hasEventHandler = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"allflags1" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		allflags1 = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->swfVersion>=6 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"allflags2" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		allflags2 = tmp_int;
		xmlFree( tmp );
	}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "events" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Event* item = Event::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						events.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
		}
	}
}
void ImportAssets2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("ImportAssets2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"url" );
	if( tmp ) {
		url = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no url property in %s element\n", (const char *)node->name );
		url = strdupx("[undefined]");
	}
	tmp = xmlGetProp( node, (const xmlChar *)"reserved1" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		reserved1 = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"reserved2" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		reserved2 = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "symbols" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Symbol* item = Symbol::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						symbols.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void FileAttributes::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("FileAttributes::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"hasMetaData" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		hasMetaData = tmp_int;
		xmlFree( tmp );
	}
	if( ctx->swfVersion < 9 ) {
	}
	if( ctx->swfVersion >= 9 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"allowABC" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		allowABC = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"suppressCrossDomainCaching" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		suppressCrossDomainCaching = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"swfRelativeURLs" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		swfRelativeURLs = tmp_int;
		xmlFree( tmp );
	}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"useNetwork" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		useNetwork = tmp_int;
		xmlFree( tmp );
	}
}
void DefineFontAlignZones::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineFontAlignZones::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"csmTableHint" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &csmTableHint);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no csmTableHint property in %s element\n", (const char *)node->name );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "zoneArrays" ) ) {
			ctx->glyphCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					ZoneArray* item = ZoneArray::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						zoneArrays.append( item );
						ctx->glyphCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void CSMTextSettings::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("CSMTextSettings::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"useFlashType" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &useFlashType);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no useFlashType property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"gridFit" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &gridFit);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no gridFit property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"thickness" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		thickness = tmp_float;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"sharpness" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		sharpness = tmp_float;
		xmlFree( tmp );
	}
}
void Metadata::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Metadata::parseXML\n");
	{
		xmlNodePtr child = NULL;
		xmlNodePtr currentChild = node->children;
		while( currentChild && child == NULL) {
			if( ! strcmp( (const char *)currentChild->name, (const char *)"RDF" ) ) {
				child = currentChild;
			}
			currentChild = currentChild->next;
		}
		if (child == NULL) {
			fprintf(stderr,"WARNING: no RDF child element in %s element\n", (const char *)node->name );
			RDF = strdupx("[undefined]");
		} else {
			xmlDocPtr out = xmlNewDoc((const xmlChar*)"1.0");
			out->xmlRootNode = xmlCopyNode( child, 1 );
			char *data; int size;
			xmlDocDumpFormatMemory( out, (xmlChar**)&data, &size, 1 );
			RDF = data;
		}
	}
}
void DefineScalingGrid::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineScalingGrid::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "splitter" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					splitter.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DoABC::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("DoABC::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					actions.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DoABCDefine::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DoABCDefine::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"flags" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		flags = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					actions.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void SymbolClass::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("SymbolClass::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "symbols" ) ) {
			count=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Symbol* item = Symbol::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						symbols.append( item );
						count++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void DefineSceneAndFrameLabelData::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("DefineSceneAndFrameLabelData::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "scenes" ) ) {
			sceneCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Scene* item = Scene::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						scenes.append( item );
						sceneCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "frames" ) ) {
			frameCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Frame* item = Frame::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						frames.append( item );
						frameCount++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void DefineBinaryData::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DefineBinaryData::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "data" ) ) {
		xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					data.parseXML( child, ctx );
					node2 = child = NULL;
					node2 = NULL;
				} else {
					child = child->next;
				}
			}
		}
		if( node2 ) node2 = node2->next;
	}
}
void DefineFontName::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("DefineFontName::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"objectID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		objectID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
	tmp = xmlGetProp( node, (const xmlChar *)"copyright" );
	if( tmp ) {
		copyright = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no copyright property in %s element\n", (const char *)node->name );
		copyright = strdupx("[undefined]");
	}
}
void StackString::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackString::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		value = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no value property in %s element\n", (const char *)node->name );
		value = strdupx("[undefined]");
	}
}
void StackFloat::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackFloat::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		value = tmp_float;
		xmlFree( tmp );
	}
}
void StackNull::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StackNull::parseXML\n");
}
void StackUndefined::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StackUndefined::parseXML\n");
}
void StackRegister::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackRegister::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"reg" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		reg = tmp_int;
		xmlFree( tmp );
	}
}
void StackBoolean::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackBoolean::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void StackDouble::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackDouble::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		double tmp_float;
		sscanf( (char *)tmp, "%lg", &tmp_float );
		value = tmp_float;
		xmlFree( tmp );
	}
}
void StackInteger::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackInteger::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void StackDictionaryLookup::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackDictionaryLookup::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void StackLargeDictionaryLookup::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StackLargeDictionaryLookup::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void UnknownAction::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("UnknownAction::parseXML\n");
	{
		data = NULL;
		len = 0;
		xmlChar *xmld = xmlNodeGetContent( node );
		char *d = (char *)xmld;
		if( d ) {
			// unsure if this is neccessary
			for( int i=strlen(d)-1; i>0 && isspace(d[i]); i-- ) d[i]=0;
			while( isspace(d[0]) ) d++;
			int l = strlen(d); //BASE64_GET_MAX_DECODED_LEN(strlen( d ));
			char *dst = new char[ l ];
			int lout = base64_decode( dst, (char*)d, l );
			if( lout > 0 ) {
				len = lout;
				data = new unsigned char[ lout ];
				memcpy( data, dst, lout );
			}
			delete dst;
			xmlFree( xmld );
		}
	}
		tmp = xmlGetProp( node, (const xmlChar *)"id" );
		if( tmp ) { 
			sscanf( (char *)tmp, "%X", &type ); 
			xmlFree( (xmlChar *)tmp ); 
		}
}
void EndAction::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("EndAction::parseXML\n");
}
void NextFrame::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("NextFrame::parseXML\n");
}
void PreviousFrame::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("PreviousFrame::parseXML\n");
}
void Play::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Play::parseXML\n");
}
void Stop::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Stop::parseXML\n");
}
void ToggleQuality::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("ToggleQuality::parseXML\n");
}
void StopSound::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StopSound::parseXML\n");
}
void AddCast::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("AddCast::parseXML\n");
}
void Substract::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Substract::parseXML\n");
}
void Mulitply::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Mulitply::parseXML\n");
}
void Divide::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Divide::parseXML\n");
}
void EqualCast::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("EqualCast::parseXML\n");
}
void LessThanCast::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("LessThanCast::parseXML\n");
}
void LogicalAND::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("LogicalAND::parseXML\n");
}
void LogicalOR::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("LogicalOR::parseXML\n");
}
void LogicalNOT::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("LogicalNOT::parseXML\n");
}
void StringEqual::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StringEqual::parseXML\n");
}
void StringLength::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StringLength::parseXML\n");
}
void SubString::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("SubString::parseXML\n");
}
void Pop::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Pop::parseXML\n");
}
void IntegralPart::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("IntegralPart::parseXML\n");
}
void GetVariable::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("GetVariable::parseXML\n");
}
void SetVariable::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("SetVariable::parseXML\n");
}
void SetTargetDynamic::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("SetTargetDynamic::parseXML\n");
}
void ConcatenateString::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("ConcatenateString::parseXML\n");
}
void GetProperty::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("GetProperty::parseXML\n");
}
void SetProperty::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("SetProperty::parseXML\n");
}
void DuplicateSprite::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("DuplicateSprite::parseXML\n");
}
void RemoveSprite::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("RemoveSprite::parseXML\n");
}
void Trace::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Trace::parseXML\n");
}
void StartDrag::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StartDrag::parseXML\n");
}
void StopDrag::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StopDrag::parseXML\n");
}
void StringLessThan::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StringLessThan::parseXML\n");
}
void Throw::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Throw::parseXML\n");
}
void CastObject::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("CastObject::parseXML\n");
}
void Implements::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Implements::parseXML\n");
}
void Random::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Random::parseXML\n");
}
void MultibyteStringLength::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("MultibyteStringLength::parseXML\n");
}
void ORD::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("ORD::parseXML\n");
}
void CHR::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("CHR::parseXML\n");
}
void GetTimer::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("GetTimer::parseXML\n");
}
void MultibyteSubString::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("MultibyteSubString::parseXML\n");
}
void MultibyteORD::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("MultibyteORD::parseXML\n");
}
void MultibyteCHR::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("MultibyteCHR::parseXML\n");
}
void Delete::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Delete::parseXML\n");
}
void DeleteAll::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("DeleteAll::parseXML\n");
}
void SetLocalVariable::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("SetLocalVariable::parseXML\n");
}
void CallFunction::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("CallFunction::parseXML\n");
}
void Return::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Return::parseXML\n");
}
void Modulo::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Modulo::parseXML\n");
}
void New::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("New::parseXML\n");
}
void DeclareLocalVariable::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("DeclareLocalVariable::parseXML\n");
}
void DeclareArray::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("DeclareArray::parseXML\n");
}
void DeclareObject::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("DeclareObject::parseXML\n");
}
void TypeOf::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("TypeOf::parseXML\n");
}
void GetTarget::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("GetTarget::parseXML\n");
}
void Enumerate::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Enumerate::parseXML\n");
}
void AddTyped::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("AddTyped::parseXML\n");
}
void LessThanTyped::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("LessThanTyped::parseXML\n");
}
void EqualTyped::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("EqualTyped::parseXML\n");
}
void DefineNumber::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("DefineNumber::parseXML\n");
}
void DefineString::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("DefineString::parseXML\n");
}
void Duplicate::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Duplicate::parseXML\n");
}
void Swap::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Swap::parseXML\n");
}
void GetMember::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("GetMember::parseXML\n");
}
void SetMember::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("SetMember::parseXML\n");
}
void Increment::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Increment::parseXML\n");
}
void Decrement::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Decrement::parseXML\n");
}
void CallMethod::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("CallMethod::parseXML\n");
}
void NewMethod::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("NewMethod::parseXML\n");
}
void InstanceOf::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("InstanceOf::parseXML\n");
}
void EnumerateObject::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("EnumerateObject::parseXML\n");
}
void AND::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("AND::parseXML\n");
}
void OR::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OR::parseXML\n");
}
void XOR::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("XOR::parseXML\n");
}
void ShiftLeft::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("ShiftLeft::parseXML\n");
}
void ShiftRight::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("ShiftRight::parseXML\n");
}
void ShiftRightUnsigned::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("ShiftRightUnsigned::parseXML\n");
}
void StrictEqual::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StrictEqual::parseXML\n");
}
void GreaterThanTyped::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("GreaterThanTyped::parseXML\n");
}
void StringGreaterThan::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("StringGreaterThan::parseXML\n");
}
void Extends::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("Extends::parseXML\n");
}
void GotoFrame::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("GotoFrame::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"frame" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		frame = tmp_int;
		xmlFree( tmp );
	}
}
void GetURL::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("GetURL::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"url" );
	if( tmp ) {
		url = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no url property in %s element\n", (const char *)node->name );
		url = strdupx("[undefined]");
	}
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		target = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no target property in %s element\n", (const char *)node->name );
		target = strdupx("[undefined]");
	}
}
void StoreRegister::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("StoreRegister::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"reg" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		reg = tmp_int;
		xmlFree( tmp );
	}
}
void Dictionary::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("Dictionary::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "strings" ) ) {
			length=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					String* item = String::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						strings.append( item );
						length++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void WaitForFrame::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("WaitForFrame::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"frame" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		frame = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"skip" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		skip = tmp_int;
		xmlFree( tmp );
	}
}
void SetTarget::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("SetTarget::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"label" );
	if( tmp ) {
		label = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no label property in %s element\n", (const char *)node->name );
		label = strdupx("[undefined]");
	}
}
void GotoLabel::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("GotoLabel::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"label" );
	if( tmp ) {
		label = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no label property in %s element\n", (const char *)node->name );
		label = strdupx("[undefined]");
	}
}
void WaitForFrameDynamic::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("WaitForFrameDynamic::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"frame" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		frame = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"skip" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		skip = tmp_int;
		xmlFree( tmp );
	}
}
void DeclareFunction2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DeclareFunction2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"regc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		regc = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"preloadParent" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		preloadParent = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"preloadRoot" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		preloadRoot = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"suppressSuper" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		suppressSuper = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"preloadSuper" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		preloadSuper = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"suppressArguments" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		suppressArguments = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"preloadArguments" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		preloadArguments = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"suppressThis" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		suppressThis = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"preloadThis" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		preloadThis = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"reserved" );
	if( tmp ) {
		sscanf( (char *)tmp, "%i", &reserved);
		xmlFree( tmp );
	} else {
		fprintf(stderr,"WARNING: no reserved property in %s element\n", (const char *)node->name );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"preloadGlobal" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		preloadGlobal = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "args" ) ) {
			argc=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Parameter* item = Parameter::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						args.append( item );
						argc++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "actions" ) ) {
				size_t l = 0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					Action* item = Action::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						actions.append( item );
							l += item->getSize(ctx, l);
					}
				}
				child = child->next;
			}
			length = (l/8);
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void Try::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Try::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"doFinally" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		doFinally = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"doCatch" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		doCatch = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"trySize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		trySize = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"catchSize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		catchSize = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"finallySize" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		finallySize = tmp_int;
		xmlFree( tmp );
	}
	{
		bool has = false;
	if( xmlHasProp( node, (const xmlChar *)"reg" ) ) has = true;
					if( has ) catchInRegister = true;
		if( has ) {
	tmp = xmlGetProp( node, (const xmlChar *)"reg" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		reg = tmp_int;
		xmlFree( tmp );
	}
		}
	}
}
void With::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("With::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"size" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		size = tmp_int;
		xmlFree( tmp );
	}
}
void PushData::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
//	printf("PushData::parseXML\n");
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "items" ) ) {
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					StackItem* item = StackItem::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						items.append( item );
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void GetURL2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("GetURL2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"method" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		method = tmp_int;
		xmlFree( tmp );
	}
}
void DeclareFunction::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("DeclareFunction::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		name = fromXmlChar(ctx, (const xmlChar*)tmp);
		xmlFree(tmp);
	} else {
		fprintf(stderr,"WARNING: no name property in %s element\n", (const char *)node->name );
		name = strdupx("[undefined]");
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "args" ) ) {
			argc=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					String* item = String::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						args.append( item );
						argc++;
					}
				}
				child = child->next;
			}
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
	tmp = xmlGetProp( node, (const xmlChar *)"length" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		length = tmp_int;
		xmlFree( tmp );
	}
}
void BranchAlways::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("BranchAlways::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"byteOffset" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		byteOffset = tmp_int;
		xmlFree( tmp );
	}
}
void BranchIfTrue::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("BranchIfTrue::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"byteOffset" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		byteOffset = tmp_int;
		xmlFree( tmp );
	}
}
void CallFrame::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("CallFrame::parseXML\n");
}
void GotoExpression::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("GotoExpression::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"play" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		play = tmp_int;
		xmlFree( tmp );
	}
}
void PrivateNamespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("PrivateNamespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void Namespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Namespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void PackageNamespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("PackageNamespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void PackageInternalNamespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("PackageInternalNamespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void ProtectedNamespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("ProtectedNamespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void ExplicitNamespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("ExplicitNamespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void MultinameLNamespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("MultinameLNamespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void QName::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("QName::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"namespaceIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		namespaceIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
}
void QNameA::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("QNameA::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"namespaceIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		namespaceIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
}
void Multiname::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Multiname::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"namespaceSetIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		namespaceSetIndex = tmp_int;
		xmlFree( tmp );
	}
}
void MultinameA::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("MultinameA::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"namespaceSetIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		namespaceSetIndex = tmp_int;
		xmlFree( tmp );
	}
}
void RTQName::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("RTQName::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
}
void RTQNameA::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("RTQNameA::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"nameIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		nameIndex = tmp_int;
		xmlFree( tmp );
	}
}
void MultinameL::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("MultinameL::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"namespaceSetIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		namespaceSetIndex = tmp_int;
		xmlFree( tmp );
	}
}
void RTQNameL::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("RTQNameL::parseXML\n");
}
void RTQNameLA::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("RTQNameLA::parseXML\n");
}
void Slot::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Slot::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"typeIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		typeIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"valueIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		valueIndex = tmp_int;
		xmlFree( tmp );
	}
	if( valueIndex != 0 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"valueKind" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		valueKind = tmp_int;
		xmlFree( tmp );
	}
	}
}
void Const::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Const::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"typeIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		typeIndex = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"valueIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		valueIndex = tmp_int;
		xmlFree( tmp );
	}
	if( valueIndex != 0 ) {
	tmp = xmlGetProp( node, (const xmlChar *)"valueKind" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		valueKind = tmp_int;
		xmlFree( tmp );
	}
	}
}
void Method::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Method::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"dispID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		dispID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"methodInfo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		methodInfo = tmp_int;
		xmlFree( tmp );
	}
}
void Getter::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Getter::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"dispID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		dispID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"methodInfo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		methodInfo = tmp_int;
		xmlFree( tmp );
	}
}
void Setter::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Setter::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"dispID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		dispID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"methodInfo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		methodInfo = tmp_int;
		xmlFree( tmp );
	}
}
void Class::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Class::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"classInfo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		classInfo = tmp_int;
		xmlFree( tmp );
	}
}
void Function::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("Function::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"methodInfo" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		methodInfo = tmp_int;
		xmlFree( tmp );
	}
}
void OpBkPt::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpBkPt::parseXML\n");
}
void OpNop::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpNop::parseXML\n");
}
void OpThrow::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpThrow::parseXML\n");
}
void OpGetSuper::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetSuper::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpSetSuper::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpSetSuper::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpDXNs::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpDXNs::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"dxns" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		dxns = tmp_int;
		xmlFree( tmp );
	}
}
void OpDXNsLate::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpDXNsLate::parseXML\n");
}
void OpKill::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpKill::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"address" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		address = tmp_int;
		xmlFree( tmp );
	}
}
void OpLabel::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpLabel::parseXML\n");
}
void OpIfNlt::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfNlt::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfNle::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfNle::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfNgt::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfNgt::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfNge::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfNge::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpJump::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpJump::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfTrue::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfTrue::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfFalse::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfFalse::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfEq::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfEq::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfNe::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfNe::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfLt::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfLt::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfLe::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfLe::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfGt::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfGt::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfGe::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfGe::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfStrictEq::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfStrictEq::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpIfStrictNe::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIfStrictNe::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"target" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		target = tmp_int;
		xmlFree( tmp );
	}
}
void OpLookupSwitch::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlNodePtr node2;
	xmlChar *tmp;
//	printf("OpLookupSwitch::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"defaulTarget" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		defaulTarget = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"caseCount" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		caseCount = tmp_int;
		xmlFree( tmp );
	}
	node2 = node->children;
	while( node2 ) {
		if( !strcmp( (const char *)node2->name, "targetTable" ) ) {
			caseCount=0;
			xmlNodePtr child = node2->children;
			while( child ) {
				if( !xmlNodeIsText( child ) ) {
					S24* item = S24::getByName( (const char *)child->name );
					if( item ) {
						item->parseXML( child, ctx );
						targetTable.append( item );
						caseCount++;
					}
				}
				child = child->next;
			}
			caseCount -= 1;
			node2=NULL;
		} else {
			node2 = node2->next;
		}
	}
}
void OpPushWith::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPushWith::parseXML\n");
}
void OpPopScope::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPopScope::parseXML\n");
}
void OpNextName::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpNextName::parseXML\n");
}
void OpHasNext::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpHasNext::parseXML\n");
}
void OpPushNull::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPushNull::parseXML\n");
}
void OpPushUndefined::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPushUndefined::parseXML\n");
}
void OpNextValue::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpNextValue::parseXML\n");
}
void OpPushByte::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpPushByte::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void OpPushShort::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpPushShort::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"value" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		value = tmp_int;
		xmlFree( tmp );
	}
}
void OpPushTrue::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPushTrue::parseXML\n");
}
void OpPushFalse::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPushFalse::parseXML\n");
}
void OpPushNaN::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPushNaN::parseXML\n");
}
void OpPop::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPop::parseXML\n");
}
void OpDup::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpDup::parseXML\n");
}
void OpSwap::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpSwap::parseXML\n");
}
void OpPushString::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpPushString::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void OpPushInt::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpPushInt::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void OpPushUInt::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpPushUInt::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void OpPushDouble::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpPushDouble::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void OpPushScope::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpPushScope::parseXML\n");
}
void OpPushNamespace::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpPushNamespace::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void OpHasNext2::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpHasNext2::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"object" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		object = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void OpNewFunction::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpNewFunction::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"index" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		index = tmp_int;
		xmlFree( tmp );
	}
}
void OpCall::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCall::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpConstruct::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpConstruct::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpCallMethod::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCallMethod::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"dispID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		dispID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpCallStatic::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCallStatic::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"methodID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		methodID = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpCallSuper::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCallSuper::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpCallProperty::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCallProperty::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpReturnVoid::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpReturnVoid::parseXML\n");
}
void OpReturnValue::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpReturnValue::parseXML\n");
}
void OpConstructSuper::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpConstructSuper::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpConstructProp::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpConstructProp::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpCallPropLex::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCallPropLex::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpCallSuperVoid::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCallSuperVoid::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpCallPropVoid::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCallPropVoid::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpNewObject::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpNewObject::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpNewArray::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpNewArray::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"argc" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		argc = tmp_int;
		xmlFree( tmp );
	}
}
void OpNewActivation::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpNewActivation::parseXML\n");
}
void OpNewClass::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpNewClass::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"classIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		classIndex = tmp_int;
		xmlFree( tmp );
	}
}
void OpGetDescendants::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetDescendants::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpNewCatch::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpNewCatch::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"exceptionIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		exceptionIndex = tmp_int;
		xmlFree( tmp );
	}
}
void OpFindPropStrict::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpFindPropStrict::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpFindProperty::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpFindProperty::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpFindDef::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpFindDef::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpGetLex::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetLex::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpSetProperty::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpSetProperty::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpGetLocal::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetLocal::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"address" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		address = tmp_int;
		xmlFree( tmp );
	}
}
void OpSetLocal::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpSetLocal::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"address" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		address = tmp_int;
		xmlFree( tmp );
	}
}
void OpGetGlobalScope::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpGetGlobalScope::parseXML\n");
}
void OpGetScopeObject::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetScopeObject::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"scopeIndex" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		scopeIndex = tmp_int;
		xmlFree( tmp );
	}
}
void OpGetProperty::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetProperty::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpInitProperty::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpInitProperty::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpDeleteProperty::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpDeleteProperty::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpGetSlot::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetSlot::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
}
void OpSetSlot::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpSetSlot::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
}
void OpGetGlobalSlot::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpGetGlobalSlot::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
}
void OpSetGlobalSlot::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpSetGlobalSlot::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"slotID" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		slotID = tmp_int;
		xmlFree( tmp );
	}
}
void OpConvertS::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpConvertS::parseXML\n");
}
void OpEscXelem::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpEscXelem::parseXML\n");
}
void OpEscXattr::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpEscXattr::parseXML\n");
}
void OpConvertI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpConvertI::parseXML\n");
}
void OpConvertU::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpConvertU::parseXML\n");
}
void OpConvertD::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpConvertD::parseXML\n");
}
void OpConvertB::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpConvertB::parseXML\n");
}
void OpConvertO::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpConvertO::parseXML\n");
}
void OpCheckFilter::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCheckFilter::parseXML\n");
}
void OpCoerce::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpCoerce::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpCoerceB::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCoerceB::parseXML\n");
}
void OpCoerceA::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCoerceA::parseXML\n");
}
void OpCoerceI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCoerceI::parseXML\n");
}
void OpCoerceD::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCoerceD::parseXML\n");
}
void OpCoerceS::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCoerceS::parseXML\n");
}
void OpAsType::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpAsType::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpAsTypeLate::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpAsTypeLate::parseXML\n");
}
void OpCoerceU::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCoerceU::parseXML\n");
}
void OpCoerceO::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpCoerceO::parseXML\n");
}
void OpNegate::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpNegate::parseXML\n");
}
void OpIncrement::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpIncrement::parseXML\n");
}
void OpIncLocal::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIncLocal::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"address" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		address = tmp_int;
		xmlFree( tmp );
	}
}
void OpDecrement::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpDecrement::parseXML\n");
}
void OpDecLocal::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpDecLocal::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"address" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		address = tmp_int;
		xmlFree( tmp );
	}
}
void OpTypeOf::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpTypeOf::parseXML\n");
}
void OpNot::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpNot::parseXML\n");
}
void OpBitNot::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpBitNot::parseXML\n");
}
void OpAdd::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpAdd::parseXML\n");
}
void OpSubtract::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpSubtract::parseXML\n");
}
void OpMultiply::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpMultiply::parseXML\n");
}
void OpDivide::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpDivide::parseXML\n");
}
void OpModulo::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpModulo::parseXML\n");
}
void OpLShift::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpLShift::parseXML\n");
}
void OpRShift::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpRShift::parseXML\n");
}
void OpURShift::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpURShift::parseXML\n");
}
void OpBitAnd::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpBitAnd::parseXML\n");
}
void OpBitOr::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpBitOr::parseXML\n");
}
void OpBitXor::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpBitXor::parseXML\n");
}
void OpEquals::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpEquals::parseXML\n");
}
void OpStrictEquals::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpStrictEquals::parseXML\n");
}
void OpLessThan::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpLessThan::parseXML\n");
}
void OpLessEquals::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpLessEquals::parseXML\n");
}
void OpGreaterThan::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpGreaterThan::parseXML\n");
}
void OpGreaterEquals::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpGreaterEquals::parseXML\n");
}
void OpInstanceOf::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpInstanceOf::parseXML\n");
}
void OpIsType::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIsType::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
}
void OpIsTypeLate::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpIsTypeLate::parseXML\n");
}
void OpIn::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpIn::parseXML\n");
}
void OpIncrementI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpIncrementI::parseXML\n");
}
void OpDecrementI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpDecrementI::parseXML\n");
}
void OpIncLocalI::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpIncLocalI::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"address" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		address = tmp_int;
		xmlFree( tmp );
	}
}
void OpDecLocalI::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpDecLocalI::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"address" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		address = tmp_int;
		xmlFree( tmp );
	}
}
void OpNegateI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpNegateI::parseXML\n");
}
void OpAddI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpAddI::parseXML\n");
}
void OpSubtractI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpSubtractI::parseXML\n");
}
void OpMultiplyI::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpMultiplyI::parseXML\n");
}
void OpGetLocal0::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpGetLocal0::parseXML\n");
}
void OpGetLocal1::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpGetLocal1::parseXML\n");
}
void OpGetLocal2::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpGetLocal2::parseXML\n");
}
void OpGetLocal3::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpGetLocal3::parseXML\n");
}
void OpSetLocal0::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpSetLocal0::parseXML\n");
}
void OpSetLocal1::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpSetLocal1::parseXML\n");
}
void OpSetLocal2::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpSetLocal2::parseXML\n");
}
void OpSetLocal3::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpSetLocal3::parseXML\n");
}
void OpDebugReg::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpDebugReg::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"unknown" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		unknown = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"name" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		name = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"reg" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		reg = tmp_int;
		xmlFree( tmp );
	}
	tmp = xmlGetProp( node, (const xmlChar *)"line" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		line = tmp_int;
		xmlFree( tmp );
	}
}
void OpDebugLine::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpDebugLine::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"line" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		line = tmp_int;
		xmlFree( tmp );
	}
}
void OpDebugFile::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpDebugFile::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"file" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		file = tmp_int;
		xmlFree( tmp );
	}
}
void OpBkPtLine::parseXML( xmlNodePtr node, Context *ctx ) {
	xmlChar *tmp;
//	printf("OpBkPtLine::parseXML\n");
	tmp = xmlGetProp( node, (const xmlChar *)"line" );
	if( tmp ) {
		int tmp_int;
		sscanf( (char *)tmp, "%i", &tmp_int );
		line = tmp_int;
		xmlFree( tmp );
	}
}
void OpTimestamp::parseXML( xmlNodePtr node, Context *ctx ) {
//	printf("OpTimestamp::parseXML\n");
}
}
