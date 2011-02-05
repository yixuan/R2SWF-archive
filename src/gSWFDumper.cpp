#include "SWF.h"
namespace SWF {
void print_indent( int n ) {
	for( int i=0; i<n; i++ ) printf("  ");
}
void Rectangle::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Rectangle"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("bits: "); 
	printf("%i\n", bits);
	print_indent(indent);
	printf("left: "); 
	printf("%i\n", left);
	print_indent(indent);
	printf("right: "); 
	printf("%i\n", right);
	print_indent(indent);
	printf("top: "); 
	printf("%i\n", top);
	print_indent(indent);
	printf("bottom: "); 
	printf("%i\n", bottom);
}
void Color::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Color"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("red: "); 
	printf("%i\n", red);
	print_indent(indent);
	printf("green: "); 
	printf("%i\n", green);
	print_indent(indent);
	printf("blue: "); 
	printf("%i\n", blue);
	if( ctx->alpha ) {
	print_indent(indent);
	printf("alpha: "); 
	printf("%i\n", alpha);
	}
}
void String::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("String"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%s\n", value?value:"(nil)");
}
void String2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("String2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%s\n", value?value:"(nil)");
}
void Transform::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Transform"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("scaled: "); 
	printf("%i\n", scaled);
	if( scaled ) {
	print_indent(indent);
	printf("bitsScale: "); 
	printf("%i\n", bitsScale);
	print_indent(indent);
	printf("scaleX: "); 
	printf("%G\n", scaleX);
	print_indent(indent);
	printf("scaleY: "); 
	printf("%G\n", scaleY);
	}
	print_indent(indent);
	printf("skewed: "); 
	printf("%i\n", skewed);
	if( skewed ) {
	print_indent(indent);
	printf("bitsSkew: "); 
	printf("%i\n", bitsSkew);
	print_indent(indent);
	printf("skewX: "); 
	printf("%G\n", skewX);
	print_indent(indent);
	printf("skewY: "); 
	printf("%G\n", skewY);
	}
	print_indent(indent);
	printf("bitsTranslate: "); 
	printf("%i\n", bitsTranslate);
	print_indent(indent);
	printf("transX: "); 
	printf("%i\n", transX);
	print_indent(indent);
	printf("transY: "); 
	printf("%i\n", transY);
}
void ColorTransform2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ColorTransform2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("hasOffset: "); 
	printf("%i\n", hasOffset);
	print_indent(indent);
	printf("hasFactor: "); 
	printf("%i\n", hasFactor);
	print_indent(indent);
	printf("bits: "); 
	printf("%i\n", bits);
	if( hasFactor ) {
	print_indent(indent);
	printf("factorRed: "); 
	printf("%i\n", factorRed);
	print_indent(indent);
	printf("factorGreen: "); 
	printf("%i\n", factorGreen);
	print_indent(indent);
	printf("factorBlue: "); 
	printf("%i\n", factorBlue);
	print_indent(indent);
	printf("factorAlpha: "); 
	printf("%i\n", factorAlpha);
	}
	if( hasOffset ) {
	print_indent(indent);
	printf("offsetRed: "); 
	printf("%i\n", offsetRed);
	print_indent(indent);
	printf("offsetGreen: "); 
	printf("%i\n", offsetGreen);
	print_indent(indent);
	printf("offsetBlue: "); 
	printf("%i\n", offsetBlue);
	print_indent(indent);
	printf("offsetAlpha: "); 
	printf("%i\n", offsetAlpha);
	}
}
void Header::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Header"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("size: "); 
	printf("[Rectangle]\n");
	size.dump( indent+1, ctx );
	print_indent(indent);
	printf("framerate: "); 
	printf("%i\n", framerate);
	print_indent(indent);
	printf("frames: "); 
	printf("%i\n", frames);
	print_indent(indent);
	printf("tags: "); 
	{
		printf("[list of Tags]\n");
		Tag *item;
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void LineStyle::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("LineStyle"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("width: "); 
	printf("%i\n", width);
	if( ctx->tagVersion < 4 ) {
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	}
	if( ctx->tagVersion > 3 ) {
	print_indent(indent);
	printf("startCapStyle: "); 
	printf("%i\n", startCapStyle);
	print_indent(indent);
	printf("jointStyle: "); 
	printf("%i\n", jointStyle);
	print_indent(indent);
	printf("hasFill: "); 
	printf("%i\n", hasFill);
	print_indent(indent);
	printf("noHScale: "); 
	printf("%i\n", noHScale);
	print_indent(indent);
	printf("noVScale: "); 
	printf("%i\n", noVScale);
	print_indent(indent);
	printf("pixelHinting: "); 
	printf("%i\n", pixelHinting);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("noClose: "); 
	printf("%i\n", noClose);
	print_indent(indent);
	printf("endCapStyle: "); 
	printf("%i\n", endCapStyle);
	if( jointStyle==2 ) {
	print_indent(indent);
	printf("miterLimitFactor: "); 
	printf("%G\n", miterLimitFactor);
	}
	if( hasFill ) {
	print_indent(indent);
	printf("fillStyles: "); 
	{
		printf("[list of Styles]\n");
		Style *item;
		ListItem<Style>* i;
		i = fillStyles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( !hasFill ) {
	print_indent(indent);
	printf("fillColor: "); 
	printf("[Color]\n");
	fillColor.dump( indent+1, ctx );
	}
	}
}
void StyleList::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("StyleList"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("n_fillStyles: "); 
	printf("%i\n", n_fillStyles);
	print_indent(indent);
	printf("fillStyles: "); 
	{
		printf("[list of Styles]\n");
		Style *item;
		ListItem<Style>* i;
		i = fillStyles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("n_lineStyles: "); 
	printf("%i\n", n_lineStyles);
	print_indent(indent);
	printf("lineStyles: "); 
	{
		printf("[list of LineStyles]\n");
		LineStyle *item;
		ListItem<LineStyle>* i;
		i = lineStyles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("fillBits: "); 
	printf("%i\n", fillBits);
	print_indent(indent);
	printf("lineBits: "); 
	printf("%i\n", lineBits);
}
void ShapeSetup::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ShapeSetup"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("hasNewStyles: "); 
	printf("%i\n", hasNewStyles);
	print_indent(indent);
	printf("hasLineStyle: "); 
	printf("%i\n", hasLineStyle);
	print_indent(indent);
	printf("hasFillStyle1: "); 
	printf("%i\n", hasFillStyle1);
	print_indent(indent);
	printf("hasFillStyle0: "); 
	printf("%i\n", hasFillStyle0);
	print_indent(indent);
	printf("hasMoveTo: "); 
	printf("%i\n", hasMoveTo);
	if( hasMoveTo ) {
	print_indent(indent);
	printf("xybits: "); 
	printf("%i\n", xybits);
	print_indent(indent);
	printf("x: "); 
	printf("%i\n", x);
	print_indent(indent);
	printf("y: "); 
	printf("%i\n", y);
	}
	if( hasFillStyle0 ) {
	print_indent(indent);
	printf("fillStyle0: "); 
	printf("%i\n", fillStyle0);
	}
	if( hasFillStyle1 ) {
	print_indent(indent);
	printf("fillStyle1: "); 
	printf("%i\n", fillStyle1);
	}
	if( hasLineStyle ) {
	print_indent(indent);
	printf("lineStyle: "); 
	printf("%i\n", lineStyle);
	}
	if( hasNewStyles ) {
	print_indent(indent);
	printf("styles: "); 
	printf("[StyleList]\n");
	styles.dump( indent+1, ctx );
	}
}
void CurveTo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("CurveTo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("bits: "); 
	printf("%i\n", bits);
	print_indent(indent);
	printf("x1: "); 
	printf("%i\n", x1);
	print_indent(indent);
	printf("y1: "); 
	printf("%i\n", y1);
	print_indent(indent);
	printf("x2: "); 
	printf("%i\n", x2);
	print_indent(indent);
	printf("y2: "); 
	printf("%i\n", y2);
}
void Shape::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Shape"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("edges: "); 
	{
		printf("[list of ShapeItems]\n");
		ShapeItem *item;
		ListItem<ShapeItem>* i;
		i = edges.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void GlyphShape::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("GlyphShape"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->fillBits = 1;
	ctx->lineBits = 0;
	print_indent(indent);
	printf("fillBits: "); 
	printf("%i\n", fillBits);
	print_indent(indent);
	printf("lineBits: "); 
	printf("%i\n", lineBits);
	print_indent(indent);
	printf("edges: "); 
	{
		printf("[list of ShapeItems]\n");
		ShapeItem *item;
		ListItem<ShapeItem>* i;
		i = edges.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void GradientItem::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("GradientItem"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("position: "); 
	printf("%i\n", position);
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
}
void Symbol::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Symbol"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
}
void Frame::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Frame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("number: "); 
	print_indent(indent);
	printf("label: "); 
	printf("%s\n", label?label:"(nil)");
}
void Scene::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Scene"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("offset: "); 
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
}
void Parameter::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Parameter"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reg: "); 
	printf("%i\n", reg);
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
}
void UChar::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("UChar"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void UShort::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("UShort"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void ULong::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ULong"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void Short::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Short"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void Float::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Float"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
}
void Double::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Double"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
}
void Kerning::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Kerning"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("a: "); 
	printf("%i\n", a);
	print_indent(indent);
	printf("b: "); 
	printf("%i\n", b);
	print_indent(indent);
	printf("adjustment: "); 
	printf("%i\n", adjustment);
}
void WideKerning::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("WideKerning"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("a: "); 
	printf("%i\n", a);
	print_indent(indent);
	printf("b: "); 
	printf("%i\n", b);
	print_indent(indent);
	printf("adjustment: "); 
	printf("%i\n", adjustment);
}
void TextEntry::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextEntry"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("glyph: "); 
	printf("%i\n", glyph);
	print_indent(indent);
	printf("advance: "); 
	printf("%i\n", advance);
}
void TextEntry2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextEntry2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("glyph: "); 
	printf("%i\n", glyph);
	print_indent(indent);
	printf("advance: "); 
	printf("%i\n", advance);
}
void TextRecord6::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextRecord6"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("isSetup: "); 
	printf("%i\n", isSetup);
	if( isSetup ) {
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("hasFont: "); 
	printf("%i\n", hasFont);
	print_indent(indent);
	printf("hasColor: "); 
	printf("%i\n", hasColor);
	print_indent(indent);
	printf("hasMoveY: "); 
	printf("%i\n", hasMoveY);
	print_indent(indent);
	printf("hasMoveX: "); 
	printf("%i\n", hasMoveX);
	if( hasFont ) {
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	}
	if( hasColor ) {
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	}
	if( hasMoveX ) {
	print_indent(indent);
	printf("x: "); 
	printf("%i\n", x);
	}
	if( hasMoveY ) {
	print_indent(indent);
	printf("y: "); 
	printf("%i\n", y);
	}
	if( hasFont ) {
	print_indent(indent);
	printf("fontHeight: "); 
	printf("%i\n", fontHeight);
	}
	}
	if( !isSetup ) {
	print_indent(indent);
	printf("nGlyphs: "); 
	printf("%i\n", nGlyphs);
	print_indent(indent);
	printf("glyphs: "); 
	{
		printf("[list of TextEntrys]\n");
		TextEntry *item;
		ListItem<TextEntry>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void TextRecord62::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextRecord62"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("isSetup: "); 
	printf("%i\n", isSetup);
	if( isSetup ) {
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("hasFont: "); 
	printf("%i\n", hasFont);
	print_indent(indent);
	printf("hasColor: "); 
	printf("%i\n", hasColor);
	print_indent(indent);
	printf("hasMoveY: "); 
	printf("%i\n", hasMoveY);
	print_indent(indent);
	printf("hasMoveX: "); 
	printf("%i\n", hasMoveX);
	if( hasFont ) {
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	}
	if( hasColor ) {
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	}
	if( hasMoveX ) {
	print_indent(indent);
	printf("x: "); 
	printf("%i\n", x);
	}
	if( hasMoveY ) {
	print_indent(indent);
	printf("y: "); 
	printf("%i\n", y);
	}
	if( hasFont ) {
	print_indent(indent);
	printf("fontHeight: "); 
	printf("%i\n", fontHeight);
	}
	}
	if( !isSetup ) {
	print_indent(indent);
	printf("nGlyphs: "); 
	printf("%i\n", nGlyphs);
	print_indent(indent);
	printf("glyphs: "); 
	{
		printf("[list of TextEntry2s]\n");
		TextEntry2 *item;
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void TextRecord7::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextRecord7"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("isSetup: "); 
	printf("%i\n", isSetup);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("hasFont: "); 
	printf("%i\n", hasFont);
	print_indent(indent);
	printf("hasColor: "); 
	printf("%i\n", hasColor);
	print_indent(indent);
	printf("hasMoveY: "); 
	printf("%i\n", hasMoveY);
	print_indent(indent);
	printf("hasMoveX: "); 
	printf("%i\n", hasMoveX);
	if( hasFont ) {
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	}
	if( hasColor ) {
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	}
	if( hasMoveX ) {
	print_indent(indent);
	printf("x: "); 
	printf("%i\n", x);
	}
	if( hasMoveY ) {
	print_indent(indent);
	printf("y: "); 
	printf("%i\n", y);
	}
	if( hasFont ) {
	print_indent(indent);
	printf("fontHeight: "); 
	printf("%i\n", fontHeight);
	}
	if( isSetup ) {
	print_indent(indent);
	printf("nGlyphs: "); 
	printf("%i\n", nGlyphs);
	print_indent(indent);
	printf("glyphs: "); 
	{
		printf("[list of TextEntrys]\n");
		TextEntry *item;
		ListItem<TextEntry>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void TextRecord72::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextRecord72"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("isSetup: "); 
	printf("%i\n", isSetup);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("hasFont: "); 
	printf("%i\n", hasFont);
	print_indent(indent);
	printf("hasColor: "); 
	printf("%i\n", hasColor);
	print_indent(indent);
	printf("hasMoveY: "); 
	printf("%i\n", hasMoveY);
	print_indent(indent);
	printf("hasMoveX: "); 
	printf("%i\n", hasMoveX);
	if( hasFont ) {
	print_indent(indent);
	printf("fontRef: "); 
	printf("%i\n", fontRef);
	}
	if( hasColor ) {
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	}
	if( hasMoveX ) {
	print_indent(indent);
	printf("x: "); 
	printf("%i\n", x);
	}
	if( hasMoveY ) {
	print_indent(indent);
	printf("y: "); 
	printf("%i\n", y);
	}
	if( hasFont ) {
	print_indent(indent);
	printf("fontHeight: "); 
	printf("%i\n", fontHeight);
	}
	if( isSetup ) {
	print_indent(indent);
	printf("nGlyphs: "); 
	printf("%i\n", nGlyphs);
	print_indent(indent);
	printf("glyphs: "); 
	{
		printf("[list of TextEntry2s]\n");
		TextEntry2 *item;
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void TextRecord::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextRecord"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	if( ctx->tagVersion < 2 ) {
	print_indent(indent);
	printf("records: "); 
	{
		printf("[list of TextRecord6s]\n");
		TextRecord6 *item;
		ListItem<TextRecord6>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( ctx->tagVersion >= 2 ) {
	print_indent(indent);
	printf("string: "); 
	printf("[TextRecord7]\n");
	string.dump( indent+1, ctx );
	}
}
void TextRecord2::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TextRecord2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	if( ctx->swfVersion < 7 ) {
	print_indent(indent);
	printf("records: "); 
	{
		printf("[list of TextRecord62s]\n");
		TextRecord62 *item;
		ListItem<TextRecord62>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( ctx->swfVersion >= 7 ) {
	print_indent(indent);
	printf("textString: "); 
	printf("[TextRecord72]\n");
	textString.dump( indent+1, ctx );
	}
}
void Button::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Button"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reserved1: "); 
	printf("%i\n", reserved1);
	if( ctx->swfVersion < 8 ) {
	print_indent(indent);
	printf("reserved2: "); 
	printf("%i\n", reserved2);
	}
	if( ctx->swfVersion >= 8 ) {
	print_indent(indent);
	printf("hasBlendMode: "); 
	printf("%i\n", hasBlendMode);
	print_indent(indent);
	printf("hasFilterList: "); 
	printf("%i\n", hasFilterList);
	}
	print_indent(indent);
	printf("hitTest: "); 
	printf("%i\n", hitTest);
	print_indent(indent);
	printf("down: "); 
	printf("%i\n", down);
	print_indent(indent);
	printf("over: "); 
	printf("%i\n", over);
	print_indent(indent);
	printf("up: "); 
	printf("%i\n", up);
	if( hitTest || down || over || up ) {
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("depth: "); 
	printf("%i\n", depth);
	print_indent(indent);
	printf("transform: "); 
	printf("[Transform]\n");
	transform.dump( indent+1, ctx );
	if( ctx->tagVersion >= 2 ) {
	print_indent(indent);
	printf("colorTransform: "); 
	printf("[ColorTransform2]\n");
	colorTransform.dump( indent+1, ctx );
	}
	if( hasFilterList ) {
	print_indent(indent);
	printf("numFilters: "); 
	printf("%i\n", numFilters);
	print_indent(indent);
	printf("filters: "); 
	{
		printf("[list of Filters]\n");
		Filter *item;
		ListItem<Filter>* i;
		i = filters.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
	print_indent(indent);
	printf("blendMode: "); 
	printf("%i\n", blendMode);
	}
	}
}
void Event::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Event"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("flags1: "); 
	printf("%i\n", flags1);
	if( ctx->swfVersion>=6 ) {
	print_indent(indent);
	printf("flags2: "); 
	printf("%i\n", flags2);
	}
	if( (flags1 | flags2) ) {
	print_indent(indent);
	printf("actionLength: "); 
	print_indent(indent);
	printf("actions: "); 
	{
		printf("[list of Actions]\n");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void Condition::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Condition"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("next: "); 
	printf("%i\n", next);
	print_indent(indent);
	printf("menuEnter: "); 
	printf("%i\n", menuEnter);
	print_indent(indent);
	printf("pointerReleaseOutside: "); 
	printf("%i\n", pointerReleaseOutside);
	print_indent(indent);
	printf("pointerDragEnter: "); 
	printf("%i\n", pointerDragEnter);
	print_indent(indent);
	printf("pointerDragLeave: "); 
	printf("%i\n", pointerDragLeave);
	print_indent(indent);
	printf("pointerReleaseInside: "); 
	printf("%i\n", pointerReleaseInside);
	print_indent(indent);
	printf("pointerPush: "); 
	printf("%i\n", pointerPush);
	print_indent(indent);
	printf("pointerLeave: "); 
	printf("%i\n", pointerLeave);
	print_indent(indent);
	printf("pointerEnter: "); 
	printf("%i\n", pointerEnter);
	print_indent(indent);
	printf("key: "); 
	printf("%i\n", key);
	print_indent(indent);
	printf("menuLeave: "); 
	printf("%i\n", menuLeave);
	print_indent(indent);
	printf("actions: "); 
	{
		printf("[list of Actions]\n");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void U30::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("U30"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void S24::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("S24"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void ValueKind::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ValueKind"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
	print_indent(indent);
	printf("kind: "); 
	printf("%i\n", kind);
}
void MethodInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("MethodInfo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("paramCount: "); 
	printf("%i\n", paramCount);
	print_indent(indent);
	printf("retType: "); 
	printf("%i\n", retType);
	print_indent(indent);
	printf("paramTypes: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = paramTypes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
	print_indent(indent);
	printf("hasParamNames: "); 
	printf("%i\n", hasParamNames);
	print_indent(indent);
	printf("setSDXNs: "); 
	printf("%i\n", setSDXNs);
	print_indent(indent);
	printf("isExplicit: "); 
	printf("%i\n", isExplicit);
	print_indent(indent);
	printf("ignoreRest: "); 
	printf("%i\n", ignoreRest);
	print_indent(indent);
	printf("hasOptional: "); 
	printf("%i\n", hasOptional);
	print_indent(indent);
	printf("needRest: "); 
	printf("%i\n", needRest);
	print_indent(indent);
	printf("needActivation: "); 
	printf("%i\n", needActivation);
	print_indent(indent);
	printf("needArguments: "); 
	printf("%i\n", needArguments);
	if( hasOptional ) {
	print_indent(indent);
	printf("optionalCount: "); 
	printf("%i\n", optionalCount);
	print_indent(indent);
	printf("optional: "); 
	{
		printf("[list of ValueKinds]\n");
		ValueKind *item;
		ListItem<ValueKind>* i;
		i = optional.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( hasParamNames ) {
	print_indent(indent);
	printf("paramNames: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = paramNames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void MetadataInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("MetadataInfo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
	print_indent(indent);
	printf("valuesCount: "); 
	printf("%i\n", valuesCount);
	print_indent(indent);
	printf("keys: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = keys.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("values: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = values.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void NamespaceSet::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("NamespaceSet"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("namespaces: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void TraitInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("TraitInfo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("hasMetadata: "); 
	printf("%i\n", hasMetadata);
	print_indent(indent);
	printf("override: "); 
	printf("%i\n", override);
	print_indent(indent);
	printf("final: "); 
	printf("%i\n", final);
	print_indent(indent);
	printf("trait: "); 
	{
		printf("[list of Traits]\n");
		Trait *item;
		ListItem<Trait>* i;
		i = trait.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	if( hasMetadata ) {
	print_indent(indent);
	printf("metadataCount: "); 
	printf("%i\n", metadataCount);
	print_indent(indent);
	printf("metadata: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void InstanceInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("InstanceInfo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
	print_indent(indent);
	printf("superIndex: "); 
	printf("%i\n", superIndex);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("hasProtectedNS: "); 
	printf("%i\n", hasProtectedNS);
	print_indent(indent);
	printf("interface: "); 
	printf("%i\n", interface);
	print_indent(indent);
	printf("final: "); 
	printf("%i\n", final);
	print_indent(indent);
	printf("sealed: "); 
	printf("%i\n", sealed);
	if( hasProtectedNS ) {
	print_indent(indent);
	printf("protectedNS: "); 
	printf("%i\n", protectedNS);
	}
	print_indent(indent);
	printf("interfaceCount: "); 
	printf("%i\n", interfaceCount);
	print_indent(indent);
	printf("interfaces: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = interfaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("iInitIndex: "); 
	printf("%i\n", iInitIndex);
	print_indent(indent);
	printf("traitCount: "); 
	printf("%i\n", traitCount);
	print_indent(indent);
	printf("traits: "); 
	{
		printf("[list of TraitInfos]\n");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void ClassInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ClassInfo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("cInitIndex: "); 
	printf("%i\n", cInitIndex);
	print_indent(indent);
	printf("traitCount: "); 
	printf("%i\n", traitCount);
	print_indent(indent);
	printf("traits: "); 
	{
		printf("[list of TraitInfos]\n");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void ScriptInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ScriptInfo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("initIndex: "); 
	printf("%i\n", initIndex);
	print_indent(indent);
	printf("traitCount: "); 
	printf("%i\n", traitCount);
	print_indent(indent);
	printf("traits: "); 
	{
		printf("[list of TraitInfos]\n");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void Exception::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Exception"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("tryStart: "); 
	printf("%i\n", tryStart);
	print_indent(indent);
	printf("tryEnd: "); 
	printf("%i\n", tryEnd);
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
	print_indent(indent);
	printf("type: "); 
	printf("%i\n", type);
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void MethodBody::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("MethodBody"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("methodInfo: "); 
	printf("%i\n", methodInfo);
	print_indent(indent);
	printf("maxStack: "); 
	printf("%i\n", maxStack);
	print_indent(indent);
	printf("maxRegs: "); 
	printf("%i\n", maxRegs);
	print_indent(indent);
	printf("scopeDepth: "); 
	printf("%i\n", scopeDepth);
	print_indent(indent);
	printf("maxScope: "); 
	printf("%i\n", maxScope);
	print_indent(indent);
	printf("codeLength: "); 
	printf("%i\n", codeLength);
	print_indent(indent);
	printf("code: "); 
	{
		printf("[list of OpCodes]\n");
		OpCode *item;
		ListItem<OpCode>* i;
		i = code.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("exceptionCount: "); 
	printf("%i\n", exceptionCount);
	print_indent(indent);
	printf("exceptions: "); 
	{
		printf("[list of Exceptions]\n");
		Exception *item;
		ListItem<Exception>* i;
		i = exceptions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("traitCount: "); 
	printf("%i\n", traitCount);
	print_indent(indent);
	printf("traits: "); 
	{
		printf("[list of TraitInfos]\n");
		TraitInfo *item;
		ListItem<TraitInfo>* i;
		i = traits.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void Constants::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Constants"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("intCount: "); 
	printf("%i\n", intCount);
	print_indent(indent);
	printf("ints: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = ints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("uintCount: "); 
	printf("%i\n", uintCount);
	print_indent(indent);
	printf("uints: "); 
	{
		printf("[list of U30s]\n");
		U30 *item;
		ListItem<U30>* i;
		i = uints.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("doubleCount: "); 
	printf("%i\n", doubleCount);
	print_indent(indent);
	printf("doubles: "); 
	{
		printf("[list of Doubles]\n");
		Double *item;
		ListItem<Double>* i;
		i = doubles.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("stringCount: "); 
	printf("%i\n", stringCount);
	print_indent(indent);
	printf("strings: "); 
	{
		printf("[list of String2s]\n");
		String2 *item;
		ListItem<String2>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("namespaceConstantCount: "); 
	printf("%i\n", namespaceConstantCount);
	print_indent(indent);
	printf("namespaces: "); 
	{
		printf("[list of NamespaceConstants]\n");
		NamespaceConstant *item;
		ListItem<NamespaceConstant>* i;
		i = namespaces.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("namespaceSetCount: "); 
	printf("%i\n", namespaceSetCount);
	print_indent(indent);
	printf("namespaceSets: "); 
	{
		printf("[list of NamespaceSets]\n");
		NamespaceSet *item;
		ListItem<NamespaceSet>* i;
		i = namespaceSets.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("multinameConstantCount: "); 
	printf("%i\n", multinameConstantCount);
	print_indent(indent);
	printf("multinames: "); 
	{
		printf("[list of MultinameConstants]\n");
		MultinameConstant *item;
		ListItem<MultinameConstant>* i;
		i = multinames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void Action3::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("Action3"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("minorVersion: "); 
	printf("%i\n", minorVersion);
	print_indent(indent);
	printf("majorVersion: "); 
	printf("%i\n", majorVersion);
	print_indent(indent);
	printf("constants: "); 
	printf("[Constants]\n");
	constants.dump( indent+1, ctx );
	print_indent(indent);
	printf("methodInfoCount: "); 
	printf("%i\n", methodInfoCount);
	print_indent(indent);
	printf("methods: "); 
	{
		printf("[list of MethodInfos]\n");
		MethodInfo *item;
		ListItem<MethodInfo>* i;
		i = methods.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("metadataInfoCount: "); 
	printf("%i\n", metadataInfoCount);
	print_indent(indent);
	printf("metadata: "); 
	{
		printf("[list of MetadataInfos]\n");
		MetadataInfo *item;
		ListItem<MetadataInfo>* i;
		i = metadata.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("classCount: "); 
	printf("%i\n", classCount);
	print_indent(indent);
	printf("instances: "); 
	{
		printf("[list of InstanceInfos]\n");
		InstanceInfo *item;
		ListItem<InstanceInfo>* i;
		i = instances.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("classes: "); 
	{
		printf("[list of ClassInfos]\n");
		ClassInfo *item;
		ListItem<ClassInfo>* i;
		i = classes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("scriptCount: "); 
	printf("%i\n", scriptCount);
	print_indent(indent);
	printf("scripts: "); 
	{
		printf("[list of ScriptInfos]\n");
		ScriptInfo *item;
		ListItem<ScriptInfo>* i;
		i = scripts.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("methodBodyCount: "); 
	printf("%i\n", methodBodyCount);
	print_indent(indent);
	printf("methodBodies: "); 
	{
		printf("[list of MethodBodys]\n");
		MethodBody *item;
		ListItem<MethodBody>* i;
		i = methodBodies.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void ZoneData::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ZoneData"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("position: "); 
	print_indent(indent);
	printf("size: "); 
}
void ZoneArray::dump( int indent, Context *ctx ) {
	print_indent(indent);
	printf("ZoneArray"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("zones: "); 
	{
		printf("[list of ZoneDatas]\n");
		ZoneData *item;
		ListItem<ZoneData>* i;
		i = zones.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("zoneX: "); 
	printf("%i\n", zoneX);
	print_indent(indent);
	printf("zoneY: "); 
	printf("%i\n", zoneY);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
}
void UnknownFilter::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //-1);
	printf("UnknownFilter"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("data: "); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}
}
void DropShadow::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x00);
	printf("DropShadow"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	print_indent(indent);
	printf("blurX: "); 
	printf("%G\n", blurX);
	print_indent(indent);
	printf("blurY: "); 
	printf("%G\n", blurY);
	print_indent(indent);
	printf("angle: "); 
	printf("%G\n", angle);
	print_indent(indent);
	printf("distance: "); 
	printf("%G\n", distance);
	print_indent(indent);
	printf("strength: "); 
	printf("%G\n", strength);
	print_indent(indent);
	printf("innerShadow: "); 
	printf("%i\n", innerShadow);
	print_indent(indent);
	printf("knockout: "); 
	printf("%i\n", knockout);
	print_indent(indent);
	printf("compositeSource: "); 
	printf("%i\n", compositeSource);
	print_indent(indent);
	printf("passes: "); 
	printf("%i\n", passes);
}
void Blur::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x01);
	printf("Blur"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("blurX: "); 
	printf("%G\n", blurX);
	print_indent(indent);
	printf("blurY: "); 
	printf("%G\n", blurY);
	print_indent(indent);
	printf("passes: "); 
	printf("%i\n", passes);
	print_indent(indent);
	printf("reserved1: "); 
	printf("%i\n", reserved1);
}
void Glow::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x02);
	printf("Glow"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	print_indent(indent);
	printf("blurX: "); 
	printf("%G\n", blurX);
	print_indent(indent);
	printf("blurY: "); 
	printf("%G\n", blurY);
	print_indent(indent);
	printf("strength: "); 
	printf("%G\n", strength);
	print_indent(indent);
	printf("innerGlow: "); 
	printf("%i\n", innerGlow);
	print_indent(indent);
	printf("knockout: "); 
	printf("%i\n", knockout);
	print_indent(indent);
	printf("compositeSource: "); 
	printf("%i\n", compositeSource);
	print_indent(indent);
	printf("passes: "); 
	printf("%i\n", passes);
}
void Bevel::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x03);
	printf("Bevel"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("shadowColor: "); 
	printf("[Color]\n");
	shadowColor.dump( indent+1, ctx );
	print_indent(indent);
	printf("highlightColor: "); 
	printf("[Color]\n");
	highlightColor.dump( indent+1, ctx );
	print_indent(indent);
	printf("blurX: "); 
	printf("%G\n", blurX);
	print_indent(indent);
	printf("blurY: "); 
	printf("%G\n", blurY);
	print_indent(indent);
	printf("angle: "); 
	printf("%G\n", angle);
	print_indent(indent);
	printf("distance: "); 
	printf("%G\n", distance);
	print_indent(indent);
	printf("strength: "); 
	printf("%G\n", strength);
	print_indent(indent);
	printf("innerShadow: "); 
	printf("%i\n", innerShadow);
	print_indent(indent);
	printf("knockout: "); 
	printf("%i\n", knockout);
	print_indent(indent);
	printf("compositeSource: "); 
	printf("%i\n", compositeSource);
	print_indent(indent);
	printf("onTop: "); 
	printf("%i\n", onTop);
	print_indent(indent);
	printf("passes: "); 
	printf("%i\n", passes);
}
void GradientGlow::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x04);
	printf("GradientGlow"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("numColors: "); 
	printf("%i\n", numColors);
	print_indent(indent);
	printf("colors: "); 
	{
		printf("[list of Colors]\n");
		Color *item;
		ListItem<Color>* i;
		i = colors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("ratio: "); 
	{
		printf("[list of UChars]\n");
		UChar *item;
		ListItem<UChar>* i;
		i = ratio.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("blurX: "); 
	printf("%G\n", blurX);
	print_indent(indent);
	printf("blurY: "); 
	printf("%G\n", blurY);
	print_indent(indent);
	printf("angle: "); 
	printf("%G\n", angle);
	print_indent(indent);
	printf("distance: "); 
	printf("%G\n", distance);
	print_indent(indent);
	printf("strength: "); 
	printf("%G\n", strength);
	print_indent(indent);
	printf("innerGlow: "); 
	printf("%i\n", innerGlow);
	print_indent(indent);
	printf("knockout: "); 
	printf("%i\n", knockout);
	print_indent(indent);
	printf("compositeSource: "); 
	printf("%i\n", compositeSource);
	print_indent(indent);
	printf("onTop: "); 
	printf("%i\n", onTop);
	print_indent(indent);
	printf("passes: "); 
	printf("%i\n", passes);
}
void Convolution::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x05);
	printf("Convolution"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("matrixX: "); 
	printf("%i\n", matrixX);
	print_indent(indent);
	printf("matrixY: "); 
	printf("%i\n", matrixY);
	print_indent(indent);
	printf("divizor: "); 
	print_indent(indent);
	printf("bias: "); 
	print_indent(indent);
	printf("matrix: "); 
	{
		printf("[list of Floats]\n");
		Float *item;
		ListItem<Float>* i;
		i = matrix.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("defaultColor: "); 
	printf("[Color]\n");
	defaultColor.dump( indent+1, ctx );
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("clamp: "); 
	printf("%i\n", clamp);
	print_indent(indent);
	printf("preserveAlpha: "); 
	printf("%i\n", preserveAlpha);
}
void ColorMatrix::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x06);
	printf("ColorMatrix"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("matrix: "); 
	{
		printf("[list of Floats]\n");
		Float *item;
		ListItem<Float>* i;
		i = matrix.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void GradientBevel::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x07);
	printf("GradientBevel"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("numColors: "); 
	printf("%i\n", numColors);
	print_indent(indent);
	printf("colors: "); 
	{
		printf("[list of Colors]\n");
		Color *item;
		ListItem<Color>* i;
		i = colors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("ratio: "); 
	{
		printf("[list of UChars]\n");
		UChar *item;
		ListItem<UChar>* i;
		i = ratio.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("blurX: "); 
	printf("%G\n", blurX);
	print_indent(indent);
	printf("blurY: "); 
	printf("%G\n", blurY);
	print_indent(indent);
	printf("angle: "); 
	printf("%G\n", angle);
	print_indent(indent);
	printf("distance: "); 
	printf("%G\n", distance);
	print_indent(indent);
	printf("strength: "); 
	printf("%G\n", strength);
	print_indent(indent);
	printf("innerGlow: "); 
	printf("%i\n", innerGlow);
	print_indent(indent);
	printf("knockout: "); 
	printf("%i\n", knockout);
	print_indent(indent);
	printf("compositeSource: "); 
	printf("%i\n", compositeSource);
	print_indent(indent);
	printf("onTop: "); 
	printf("%i\n", onTop);
	print_indent(indent);
	printf("passes: "); 
	printf("%i\n", passes);
}
void Solid::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x00);
	printf("Solid"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
}
void LinearGradient::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x10);
	printf("LinearGradient"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("matrix: "); 
	printf("[Transform]\n");
	matrix.dump( indent+1, ctx );
	if( ctx->tagVersion < 4 ) {
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	}
	if( ctx->tagVersion >= 4 ) {
	print_indent(indent);
	printf("spreadMode: "); 
	printf("%i\n", spreadMode);
	print_indent(indent);
	printf("interpolationMode: "); 
	printf("%i\n", interpolationMode);
	}
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("gradientColors: "); 
	{
		printf("[list of GradientItems]\n");
		GradientItem *item;
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void RadialGradient::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x12);
	printf("RadialGradient"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("matrix: "); 
	printf("[Transform]\n");
	matrix.dump( indent+1, ctx );
	if( ctx->tagVersion < 4 ) {
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	}
	if( ctx->tagVersion >= 4 ) {
	print_indent(indent);
	printf("spreadMode: "); 
	printf("%i\n", spreadMode);
	print_indent(indent);
	printf("interpolationMode: "); 
	printf("%i\n", interpolationMode);
	}
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("gradientColors: "); 
	{
		printf("[list of GradientItems]\n");
		GradientItem *item;
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void ShiftedRadialGradient::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x13);
	printf("ShiftedRadialGradient"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("matrix: "); 
	printf("[Transform]\n");
	matrix.dump( indent+1, ctx );
	if( ctx->tagVersion < 4 ) {
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	}
	if( ctx->tagVersion >= 4 ) {
	print_indent(indent);
	printf("spreadMode: "); 
	printf("%i\n", spreadMode);
	print_indent(indent);
	printf("interpolationMode: "); 
	printf("%i\n", interpolationMode);
	}
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("gradientColors: "); 
	{
		printf("[list of GradientItems]\n");
		GradientItem *item;
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("shift: "); 
	printf("%G\n", shift);
}
void TiledBitmap::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x40);
	printf("TiledBitmap"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("matrix: "); 
	printf("[Transform]\n");
	matrix.dump( indent+1, ctx );
}
void ClippedBitmap::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x41);
	printf("ClippedBitmap"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("matrix: "); 
	printf("[Transform]\n");
	matrix.dump( indent+1, ctx );
}
void TiledBitmap2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x42);
	printf("TiledBitmap2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("matrix: "); 
	printf("[Transform]\n");
	matrix.dump( indent+1, ctx );
}
void ClippedBitmap2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x43);
	printf("ClippedBitmap2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("matrix: "); 
	printf("[Transform]\n");
	matrix.dump( indent+1, ctx );
}
void UnknownTag::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //-1);
	printf("UnknownTag"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("data: "); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}
}
void End::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x00);
	printf("End"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void ShowFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x01);
	printf("ShowFrame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DefineShape::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x02);
	printf("DefineShape"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 0;
	ctx->many_shapes = 0;
	ctx->tagVersion = 1;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("bounds: "); 
	printf("[Rectangle]\n");
	bounds.dump( indent+1, ctx );
	print_indent(indent);
	printf("styles: "); 
	printf("[StyleList]\n");
	styles.dump( indent+1, ctx );
	print_indent(indent);
	printf("shapes: "); 
	printf("[Shape]\n");
	shapes.dump( indent+1, ctx );
}
void RemoveObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x05);
	printf("RemoveObject"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("depth: "); 
	printf("%i\n", depth);
}
void DefineBits::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x06);
	printf("DefineBits"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void SetBackgroundColor::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x09);
	printf("SetBackgroundColor"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 0;
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
}
void DefineText::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0B);
	printf("DefineText"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("bounds: "); 
	printf("[Rectangle]\n");
	bounds.dump( indent+1, ctx );
	print_indent(indent);
	printf("transform: "); 
	printf("[Transform]\n");
	transform.dump( indent+1, ctx );
	print_indent(indent);
	printf("glyphBits: "); 
	printf("%i\n", glyphBits);
	print_indent(indent);
	printf("advanceBits: "); 
	printf("%i\n", advanceBits);
	ctx->alpha = 0;
	ctx->tagVersion = 1;
	print_indent(indent);
	printf("records: "); 
	{
		printf("[list of TextRecords]\n");
		TextRecord *item;
		ListItem<TextRecord>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void DefineText2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x21);
	printf("DefineText2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("bounds: "); 
	printf("[Rectangle]\n");
	bounds.dump( indent+1, ctx );
	print_indent(indent);
	printf("transform: "); 
	printf("[Transform]\n");
	transform.dump( indent+1, ctx );
	print_indent(indent);
	printf("glyphBits: "); 
	printf("%i\n", glyphBits);
	print_indent(indent);
	printf("advanceBits: "); 
	printf("%i\n", advanceBits);
	print_indent(indent);
	printf("records: "); 
	{
		printf("[list of TextRecord2s]\n");
		TextRecord2 *item;
		ListItem<TextRecord2>* i;
		i = records.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void DoAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0C);
	printf("DoAction"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("actions: "); 
	{
		printf("[list of Actions]\n");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void DefineFontInfo::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0D);
	printf("DefineFontInfo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("nameLength: "); 
	printf("%i\n", nameLength);
	print_indent(indent);
	printf("nameData: "); 
	printf("(length %i)\n", nameLength );
	if( nameLength && nameData != NULL ) {
		int i=0;
		while( i<nameLength ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<nameLength; n++ ) {
				printf(" %02X",  nameData[i] );
				i++;
			}
			printf("\n");
		}
	}
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("smallTextOrUnicode: "); 
	printf("%i\n", smallTextOrUnicode);
	print_indent(indent);
	printf("isShiftJIS: "); 
	printf("%i\n", isShiftJIS);
	print_indent(indent);
	printf("isANSII: "); 
	printf("%i\n", isANSII);
	print_indent(indent);
	printf("isItalic: "); 
	printf("%i\n", isItalic);
	print_indent(indent);
	printf("isBold: "); 
	printf("%i\n", isBold);
	print_indent(indent);
	printf("isWide: "); 
	printf("%i\n", isWide);
	if( ctx->swfVersion>=6 ) {
	print_indent(indent);
	printf("language: "); 
	printf("%i\n", language);
	}
	print_indent(indent);
	printf("map: "); 
	printf("[Rest]\n");
	map.dump( indent+1, ctx );
}
void DefineSound::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0E);
	printf("DefineSound"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("format: "); 
	printf("%i\n", format);
	print_indent(indent);
	printf("rate: "); 
	printf("%i\n", rate);
	print_indent(indent);
	printf("is16bit: "); 
	printf("%i\n", is16bit);
	print_indent(indent);
	printf("stereo: "); 
	printf("%i\n", stereo);
	print_indent(indent);
	printf("samples: "); 
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void StartSound::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0F);
	printf("StartSound"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("stopPlayback: "); 
	printf("%i\n", stopPlayback);
	print_indent(indent);
	printf("noMultiple: "); 
	printf("%i\n", noMultiple);
	print_indent(indent);
	printf("hasEnvelope: "); 
	printf("%i\n", hasEnvelope);
	print_indent(indent);
	printf("hasLoop: "); 
	printf("%i\n", hasLoop);
	print_indent(indent);
	printf("hasOutPoint: "); 
	printf("%i\n", hasOutPoint);
	print_indent(indent);
	printf("hasInPoint: "); 
	printf("%i\n", hasInPoint);
	if( hasInPoint ) {
	print_indent(indent);
	printf("inPoint: "); 
	}
	if( hasOutPoint ) {
	print_indent(indent);
	printf("outPoint: "); 
	}
	if( hasLoop ) {
	print_indent(indent);
	printf("loop: "); 
	printf("%i\n", loop);
	}
	if( hasEnvelope ) {
	print_indent(indent);
	printf("envelopeCount: "); 
	printf("%i\n", envelopeCount);
	print_indent(indent);
	printf("envelopeData: "); 
	printf("[Rest]\n");
	envelopeData.dump( indent+1, ctx );
	}
}
void DefineShape2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x16);
	printf("DefineShape2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 0;
	ctx->many_shapes = 1;
	ctx->tagVersion = 2;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("bounds: "); 
	printf("[Rectangle]\n");
	bounds.dump( indent+1, ctx );
	print_indent(indent);
	printf("styles: "); 
	printf("[StyleList]\n");
	styles.dump( indent+1, ctx );
	print_indent(indent);
	printf("shapes: "); 
	printf("[Shape]\n");
	shapes.dump( indent+1, ctx );
}
void DefineShape3::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x20);
	printf("DefineShape3"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 3;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("bounds: "); 
	printf("[Rectangle]\n");
	bounds.dump( indent+1, ctx );
	print_indent(indent);
	printf("styles: "); 
	printf("[StyleList]\n");
	styles.dump( indent+1, ctx );
	print_indent(indent);
	printf("shapes: "); 
	printf("[Shape]\n");
	shapes.dump( indent+1, ctx );
}
void DefineShape4::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x43);
	printf("DefineShape4"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void DefineShape5::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x53);
	printf("DefineShape5"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 5;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("bounds: "); 
	printf("[Rectangle]\n");
	bounds.dump( indent+1, ctx );
	print_indent(indent);
	printf("strokeBounds: "); 
	printf("[Rectangle]\n");
	strokeBounds.dump( indent+1, ctx );
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("nonScalingStrokes: "); 
	printf("%i\n", nonScalingStrokes);
	print_indent(indent);
	printf("scalingStrokes: "); 
	printf("%i\n", scalingStrokes);
	print_indent(indent);
	printf("styles: "); 
	printf("[StyleList]\n");
	styles.dump( indent+1, ctx );
	print_indent(indent);
	printf("shapes: "); 
	printf("[Shape]\n");
	shapes.dump( indent+1, ctx );
}
void DefineMorphShape::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2E);
	printf("DefineMorphShape"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void DefineFontInfo2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3E);
	printf("DefineFontInfo2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("nameLength: "); 
	printf("%i\n", nameLength);
	print_indent(indent);
	printf("nameData: "); 
	printf("(length %i)\n", nameLength );
	if( nameLength && nameData != NULL ) {
		int i=0;
		while( i<nameLength ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<nameLength; n++ ) {
				printf(" %02X",  nameData[i] );
				i++;
			}
			printf("\n");
		}
	}
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("smallTextOrUnicode: "); 
	printf("%i\n", smallTextOrUnicode);
	print_indent(indent);
	printf("isShiftJIS: "); 
	printf("%i\n", isShiftJIS);
	print_indent(indent);
	printf("isANSII: "); 
	printf("%i\n", isANSII);
	print_indent(indent);
	printf("isItalic: "); 
	printf("%i\n", isItalic);
	print_indent(indent);
	printf("isBold: "); 
	printf("%i\n", isBold);
	print_indent(indent);
	printf("isWide: "); 
	printf("%i\n", isWide);
	if( ctx->swfVersion>=6 ) {
	print_indent(indent);
	printf("language: "); 
	printf("%i\n", language);
	}
	print_indent(indent);
	printf("map: "); 
	printf("[Rest]\n");
	map.dump( indent+1, ctx );
}
void SoundStreamHead::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x12);
	printf("SoundStreamHead"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("playbackRate: "); 
	printf("%i\n", playbackRate);
	print_indent(indent);
	printf("playbackSize: "); 
	printf("%i\n", playbackSize);
	print_indent(indent);
	printf("playbackStereo: "); 
	printf("%i\n", playbackStereo);
	print_indent(indent);
	printf("compression: "); 
	printf("%i\n", compression);
	print_indent(indent);
	printf("soundRate: "); 
	printf("%i\n", soundRate);
	print_indent(indent);
	printf("soundSize: "); 
	printf("%i\n", soundSize);
	print_indent(indent);
	printf("soundStereo: "); 
	printf("%i\n", soundStereo);
	print_indent(indent);
	printf("sampleSize: "); 
	printf("%i\n", sampleSize);
	if( compression==2 ) {
	print_indent(indent);
	printf("latencySeek: "); 
	printf("[Rest]\n");
	latencySeek.dump( indent+1, ctx );
	}
}
void DefineBitsLossless::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x14);
	printf("DefineBitsLossless"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("format: "); 
	printf("%i\n", format);
	print_indent(indent);
	printf("width: "); 
	printf("%i\n", width);
	print_indent(indent);
	printf("height: "); 
	printf("%i\n", height);
	if( format==3 ) {
	print_indent(indent);
	printf("n_colormap: "); 
	printf("%i\n", n_colormap);
	}
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void DefineBitsJPEG2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x15);
	printf("DefineBitsJPEG2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void DefineBitsJPEG3::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x23);
	printf("DefineBitsJPEG3"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("offset_to_alpha: "); 
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void DefineBitsLossless2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x24);
	printf("DefineBitsLossless2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("format: "); 
	printf("%i\n", format);
	print_indent(indent);
	printf("width: "); 
	printf("%i\n", width);
	print_indent(indent);
	printf("height: "); 
	printf("%i\n", height);
	if( format==3 ) {
	print_indent(indent);
	printf("n_colormap: "); 
	printf("%i\n", n_colormap);
	}
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void PlaceObject2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1A);
	printf("PlaceObject2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("hasEventHandler: "); 
	printf("%i\n", hasEventHandler);
	print_indent(indent);
	printf("hasClipDepth: "); 
	printf("%i\n", hasClipDepth);
	print_indent(indent);
	printf("hasName: "); 
	printf("%i\n", hasName);
	print_indent(indent);
	printf("hasMorph: "); 
	printf("%i\n", hasMorph);
	print_indent(indent);
	printf("hasColorTransform: "); 
	printf("%i\n", hasColorTransform);
	print_indent(indent);
	printf("hasTransform: "); 
	printf("%i\n", hasTransform);
	print_indent(indent);
	printf("hasID: "); 
	printf("%i\n", hasID);
	print_indent(indent);
	printf("replace: "); 
	printf("%i\n", replace);
	print_indent(indent);
	printf("depth: "); 
	printf("%i\n", depth);
	if( hasID ) {
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	}
	if( hasTransform ) {
	print_indent(indent);
	printf("transform: "); 
	printf("[Transform]\n");
	transform.dump( indent+1, ctx );
	}
	if( hasColorTransform ) {
	print_indent(indent);
	printf("colorTransform: "); 
	printf("[ColorTransform2]\n");
	colorTransform.dump( indent+1, ctx );
	}
	if( hasMorph ) {
	print_indent(indent);
	printf("morph: "); 
	printf("%i\n", morph);
	}
	if( hasName ) {
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	}
	if( hasClipDepth ) {
	print_indent(indent);
	printf("clipDepth: "); 
	printf("%i\n", clipDepth);
	}
	if( hasEventHandler ) {
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("allflags1: "); 
	printf("%i\n", allflags1);
	if( ctx->swfVersion>=6 ) {
	print_indent(indent);
	printf("allflags2: "); 
	printf("%i\n", allflags2);
	}
	print_indent(indent);
	printf("events: "); 
	{
		printf("[list of Events]\n");
		Event *item;
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void RemoveObject2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1C);
	printf("RemoveObject2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("depth: "); 
	printf("%i\n", depth);
}
void DefineEditText::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x25);
	printf("DefineEditText"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->alpha = 1;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("size: "); 
	printf("[Rectangle]\n");
	size.dump( indent+1, ctx );
	print_indent(indent);
	printf("hasText: "); 
	printf("%i\n", hasText);
	print_indent(indent);
	printf("wordWrap: "); 
	printf("%i\n", wordWrap);
	print_indent(indent);
	printf("multiLine: "); 
	printf("%i\n", multiLine);
	print_indent(indent);
	printf("password: "); 
	printf("%i\n", password);
	print_indent(indent);
	printf("readOnly: "); 
	printf("%i\n", readOnly);
	print_indent(indent);
	printf("hasColor: "); 
	printf("%i\n", hasColor);
	print_indent(indent);
	printf("hasMaxLength: "); 
	printf("%i\n", hasMaxLength);
	print_indent(indent);
	printf("hasFont: "); 
	printf("%i\n", hasFont);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("autoSize: "); 
	printf("%i\n", autoSize);
	print_indent(indent);
	printf("hasLayout: "); 
	printf("%i\n", hasLayout);
	print_indent(indent);
	printf("notSelectable: "); 
	printf("%i\n", notSelectable);
	print_indent(indent);
	printf("hasBorder: "); 
	printf("%i\n", hasBorder);
	print_indent(indent);
	printf("reserved2: "); 
	printf("%i\n", reserved2);
	print_indent(indent);
	printf("isHTML: "); 
	printf("%i\n", isHTML);
	print_indent(indent);
	printf("useOutlines: "); 
	printf("%i\n", useOutlines);
	if( hasFont ) {
	print_indent(indent);
	printf("fontRef: "); 
	printf("%i\n", fontRef);
	print_indent(indent);
	printf("fontHeight: "); 
	printf("%i\n", fontHeight);
	}
	if( hasColor ) {
	print_indent(indent);
	printf("color: "); 
	printf("[Color]\n");
	color.dump( indent+1, ctx );
	}
	if( hasMaxLength ) {
	print_indent(indent);
	printf("maxLength: "); 
	printf("%i\n", maxLength);
	}
	if( hasLayout ) {
	print_indent(indent);
	printf("align: "); 
	printf("%i\n", align);
	print_indent(indent);
	printf("leftMargin: "); 
	printf("%i\n", leftMargin);
	print_indent(indent);
	printf("rightMargin: "); 
	printf("%i\n", rightMargin);
	print_indent(indent);
	printf("indent: "); 
	printf("%i\n", indent);
	print_indent(indent);
	printf("leading: "); 
	printf("%i\n", leading);
	}
	print_indent(indent);
	printf("variableName: "); 
	printf("%s\n", variableName?variableName:"(nil)");
	if( hasText ) {
	print_indent(indent);
	printf("initialText: "); 
	printf("%s\n", initialText?initialText:"(nil)");
	}
}
void DefineSprite::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x27);
	printf("DefineSprite"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("frames: "); 
	printf("%i\n", frames);
	print_indent(indent);
	printf("tags: "); 
	{
		printf("[list of Tags]\n");
		Tag *item;
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void FrameLabel::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2B);
	printf("FrameLabel"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("label: "); 
	printf("%s\n", label?label:"(nil)");
	print_indent(indent);
	printf("flags: "); 
	printf("[Rest]\n");
	flags.dump( indent+1, ctx );
}
void SoundStreamHead2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2D);
	printf("SoundStreamHead2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("playbackRate: "); 
	printf("%i\n", playbackRate);
	print_indent(indent);
	printf("playbackSize: "); 
	printf("%i\n", playbackSize);
	print_indent(indent);
	printf("playbackStereo: "); 
	printf("%i\n", playbackStereo);
	print_indent(indent);
	printf("compression: "); 
	printf("%i\n", compression);
	print_indent(indent);
	printf("soundRate: "); 
	printf("%i\n", soundRate);
	print_indent(indent);
	printf("soundSize: "); 
	printf("%i\n", soundSize);
	print_indent(indent);
	printf("soundStereo: "); 
	printf("%i\n", soundStereo);
	print_indent(indent);
	printf("sampleSize: "); 
	printf("%i\n", sampleSize);
	if( compression==2 ) {
	print_indent(indent);
	printf("latencySeek: "); 
	printf("[Rest]\n");
	latencySeek.dump( indent+1, ctx );
	}
}
void DefineFont::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0A);
	printf("DefineFont"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->tagVersion = 1;
	ctx->wideGlyphOffsets = 0;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void DefineFont2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x30);
	printf("DefineFont2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->tagVersion = 2;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("hasLayout: "); 
	printf("%i\n", hasLayout);
	print_indent(indent);
	printf("isShiftJIS: "); 
	printf("%i\n", isShiftJIS);
	print_indent(indent);
	printf("isUnicode: "); 
	printf("%i\n", isUnicode);
	print_indent(indent);
	printf("isANSII: "); 
	printf("%i\n", isANSII);
	print_indent(indent);
	printf("wideGlyphOffsets: "); 
	printf("%i\n", wideGlyphOffsets);
	print_indent(indent);
	printf("wideMap: "); 
	printf("%i\n", wideMap);
	print_indent(indent);
	printf("italic: "); 
	printf("%i\n", italic);
	print_indent(indent);
	printf("bold: "); 
	printf("%i\n", bold);
	print_indent(indent);
	printf("language: "); 
	printf("%i\n", language);
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	print_indent(indent);
	printf("glyphCount: "); 
	printf("%i\n", glyphCount);
	print_indent(indent);
	printf("glyphs: "); 
	printf("[GlyphList]\n");
	glyphs.dump( indent+1, ctx );
	if( hasLayout ) {
	print_indent(indent);
	printf("ascent: "); 
	printf("%i\n", ascent);
	print_indent(indent);
	printf("descent: "); 
	printf("%i\n", descent);
	print_indent(indent);
	printf("leading: "); 
	printf("%i\n", leading);
	print_indent(indent);
	printf("advance: "); 
	{
		printf("[list of Shorts]\n");
		Short *item;
		ListItem<Short>* i;
		i = advance.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("bounds: "); 
	{
		printf("[list of Rectangles]\n");
		Rectangle *item;
		ListItem<Rectangle>* i;
		i = bounds.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("kerningCount: "); 
	printf("%i\n", kerningCount);
	if( wideMap ) {
	print_indent(indent);
	printf("wideKerning: "); 
	{
		printf("[list of WideKernings]\n");
		WideKerning *item;
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	print_indent(indent);
	printf("kerning: "); 
	{
		printf("[list of Kernings]\n");
		Kerning *item;
		ListItem<Kerning>* i;
		i = kerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	}
}
void DefineFont3::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4B);
	printf("DefineFont3"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->tagVersion = 2;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("hasLayout: "); 
	printf("%i\n", hasLayout);
	print_indent(indent);
	printf("isShiftJIS: "); 
	printf("%i\n", isShiftJIS);
	print_indent(indent);
	printf("isUnicode: "); 
	printf("%i\n", isUnicode);
	print_indent(indent);
	printf("isANSII: "); 
	printf("%i\n", isANSII);
	print_indent(indent);
	printf("wideGlyphOffsets: "); 
	printf("%i\n", wideGlyphOffsets);
	print_indent(indent);
	printf("wideMap: "); 
	printf("%i\n", wideMap);
	print_indent(indent);
	printf("italic: "); 
	printf("%i\n", italic);
	print_indent(indent);
	printf("bold: "); 
	printf("%i\n", bold);
	print_indent(indent);
	printf("language: "); 
	printf("%i\n", language);
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	print_indent(indent);
	printf("glyphCount: "); 
	printf("%i\n", glyphCount);
	print_indent(indent);
	printf("glyphs: "); 
	printf("[GlyphList]\n");
	glyphs.dump( indent+1, ctx );
	if( hasLayout ) {
	print_indent(indent);
	printf("ascent: "); 
	printf("%i\n", ascent);
	print_indent(indent);
	printf("descent: "); 
	printf("%i\n", descent);
	print_indent(indent);
	printf("leading: "); 
	printf("%i\n", leading);
	print_indent(indent);
	printf("advance: "); 
	{
		printf("[list of Shorts]\n");
		Short *item;
		ListItem<Short>* i;
		i = advance.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("bounds: "); 
	{
		printf("[list of Rectangles]\n");
		Rectangle *item;
		ListItem<Rectangle>* i;
		i = bounds.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("kerningCount: "); 
	printf("%i\n", kerningCount);
	if( wideMap ) {
	print_indent(indent);
	printf("wideKerning: "); 
	{
		printf("[list of WideKernings]\n");
		WideKerning *item;
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	print_indent(indent);
	printf("kerning: "); 
	{
		printf("[list of Kernings]\n");
		Kerning *item;
		ListItem<Kerning>* i;
		i = kerning.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	}
}
void DefineButton::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x07);
	printf("DefineButton"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->tagVersion = 1;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("buttons: "); 
	{
		printf("[list of Buttons]\n");
		Button *item;
		ListItem<Button>* i;
		i = buttons.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("actions: "); 
	{
		printf("[list of Actions]\n");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void DefineButton2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x22);
	printf("DefineButton2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	ctx->tagVersion = 2;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("menu: "); 
	printf("%i\n", menu);
	print_indent(indent);
	printf("buttonsSize: "); 
	printf("%i\n", buttonsSize);
	print_indent(indent);
	printf("buttons: "); 
	{
		printf("[list of Buttons]\n");
		Button *item;
		ListItem<Button>* i;
		i = buttons.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("conditions: "); 
	{
		printf("[list of Conditions]\n");
		Condition *item;
		ListItem<Condition>* i;
		i = conditions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void Export::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x38);
	printf("Export"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("symbols: "); 
	{
		printf("[list of Symbols]\n");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void Import::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x39);
	printf("Import"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("url: "); 
	printf("%s\n", url?url:"(nil)");
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("symbols: "); 
	{
		printf("[list of Symbols]\n");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void DoInitAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3B);
	printf("DoInitAction"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("sprite: "); 
	printf("%i\n", sprite);
	print_indent(indent);
	printf("actions: "); 
	{
		printf("[list of Actions]\n");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void SoundStreamBlock::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x13);
	printf("SoundStreamBlock"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("data: "); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}
}
void DefineVideoStream::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3C);
	printf("DefineVideoStream"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("frames: "); 
	printf("%i\n", frames);
	print_indent(indent);
	printf("width: "); 
	printf("%i\n", width);
	print_indent(indent);
	printf("height: "); 
	printf("%i\n", height);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("deblocking: "); 
	printf("%i\n", deblocking);
	print_indent(indent);
	printf("smoothing: "); 
	printf("%i\n", smoothing);
	print_indent(indent);
	printf("codec: "); 
	printf("%i\n", codec);
}
void VideoFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3D);
	printf("VideoFrame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("frame: "); 
	printf("%i\n", frame);
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void ScriptLimits::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x41);
	printf("ScriptLimits"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("maxRecursionDepth: "); 
	printf("%i\n", maxRecursionDepth);
	print_indent(indent);
	printf("timeout: "); 
	printf("%i\n", timeout);
}
void SetTabIndex::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x42);
	printf("SetTabIndex"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("depth: "); 
	printf("%i\n", depth);
	print_indent(indent);
	printf("tabIndex: "); 
	printf("%i\n", tabIndex);
}
void PlaceObject3::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x46);
	printf("PlaceObject3"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("hasEventHandler: "); 
	printf("%i\n", hasEventHandler);
	print_indent(indent);
	printf("hasClipDepth: "); 
	printf("%i\n", hasClipDepth);
	print_indent(indent);
	printf("hasName: "); 
	printf("%i\n", hasName);
	print_indent(indent);
	printf("hasMorph: "); 
	printf("%i\n", hasMorph);
	print_indent(indent);
	printf("hasColorTransform: "); 
	printf("%i\n", hasColorTransform);
	print_indent(indent);
	printf("hasTransform: "); 
	printf("%i\n", hasTransform);
	print_indent(indent);
	printf("hasID: "); 
	printf("%i\n", hasID);
	print_indent(indent);
	printf("replace: "); 
	printf("%i\n", replace);
	print_indent(indent);
	printf("reserved1: "); 
	printf("%i\n", reserved1);
	print_indent(indent);
	printf("hasCacheAsBitmap: "); 
	printf("%i\n", hasCacheAsBitmap);
	print_indent(indent);
	printf("hasBlendMode: "); 
	printf("%i\n", hasBlendMode);
	print_indent(indent);
	printf("hasFilterList: "); 
	printf("%i\n", hasFilterList);
	print_indent(indent);
	printf("depth: "); 
	printf("%i\n", depth);
	if( hasID ) {
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	}
	if( hasTransform ) {
	print_indent(indent);
	printf("transform: "); 
	printf("[Transform]\n");
	transform.dump( indent+1, ctx );
	}
	if( hasColorTransform ) {
	print_indent(indent);
	printf("colorTransform: "); 
	printf("[ColorTransform2]\n");
	colorTransform.dump( indent+1, ctx );
	}
	if( hasMorph ) {
	print_indent(indent);
	printf("morph: "); 
	printf("%i\n", morph);
	}
	if( hasName ) {
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	}
	if( hasClipDepth ) {
	print_indent(indent);
	printf("clipDepth: "); 
	printf("%i\n", clipDepth);
	}
	if( hasFilterList ) {
	print_indent(indent);
	printf("numFilters: "); 
	printf("%i\n", numFilters);
	print_indent(indent);
	printf("filters: "); 
	{
		printf("[list of Filters]\n");
		Filter *item;
		ListItem<Filter>* i;
		i = filters.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
	print_indent(indent);
	printf("blendMode: "); 
	printf("%i\n", blendMode);
	}
	if( hasCacheAsBitmap ) {
	print_indent(indent);
	printf("bitmapCaching: "); 
	printf("%i\n", bitmapCaching);
	}
	if( hasEventHandler ) {
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("allflags1: "); 
	printf("%i\n", allflags1);
	if( ctx->swfVersion>=6 ) {
	print_indent(indent);
	printf("allflags2: "); 
	printf("%i\n", allflags2);
	}
	print_indent(indent);
	printf("events: "); 
	{
		printf("[list of Events]\n");
		Event *item;
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	}
}
void ImportAssets2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x47);
	printf("ImportAssets2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("url: "); 
	printf("%s\n", url?url:"(nil)");
	print_indent(indent);
	printf("reserved1: "); 
	printf("%i\n", reserved1);
	print_indent(indent);
	printf("reserved2: "); 
	printf("%i\n", reserved2);
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("symbols: "); 
	{
		printf("[list of Symbols]\n");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void FileAttributes::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x45);
	printf("FileAttributes"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reserved1: "); 
	printf("%i\n", reserved1);
	print_indent(indent);
	printf("hasMetaData: "); 
	printf("%i\n", hasMetaData);
	if( ctx->swfVersion < 9 ) {
	print_indent(indent);
	printf("reserved2: "); 
	printf("%i\n", reserved2);
	}
	if( ctx->swfVersion >= 9 ) {
	print_indent(indent);
	printf("allowABC: "); 
	printf("%i\n", allowABC);
	print_indent(indent);
	printf("suppressCrossDomainCaching: "); 
	printf("%i\n", suppressCrossDomainCaching);
	print_indent(indent);
	printf("swfRelativeURLs: "); 
	printf("%i\n", swfRelativeURLs);
	}
	print_indent(indent);
	printf("useNetwork: "); 
	printf("%i\n", useNetwork);
	print_indent(indent);
	printf("reserved3: "); 
	printf("%i\n", reserved3);
}
void DefineFontAlignZones::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x49);
	printf("DefineFontAlignZones"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("csmTableHint: "); 
	printf("%i\n", csmTableHint);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("zoneArrays: "); 
	{
		printf("[list of ZoneArrays]\n");
		ZoneArray *item;
		ListItem<ZoneArray>* i;
		i = zoneArrays.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void CSMTextSettings::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4A);
	printf("CSMTextSettings"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("useFlashType: "); 
	printf("%i\n", useFlashType);
	print_indent(indent);
	printf("gridFit: "); 
	printf("%i\n", gridFit);
	print_indent(indent);
	printf("reserved1: "); 
	printf("%i\n", reserved1);
	print_indent(indent);
	printf("thickness: "); 
	print_indent(indent);
	printf("sharpness: "); 
	print_indent(indent);
	printf("reserved2: "); 
	printf("%i\n", reserved2);
}
void Metadata::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4D);
	printf("Metadata"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("RDF: "); 
}
void DefineScalingGrid::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4E);
	printf("DefineScalingGrid"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("splitter: "); 
	printf("[Rectangle]\n");
	splitter.dump( indent+1, ctx );
}
void DoABC::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x48);
	printf("DoABC"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("actions: "); 
	printf("[Action3]\n");
	actions.dump( indent+1, ctx );
}
void DoABCDefine::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x52);
	printf("DoABCDefine"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("flags: "); 
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	print_indent(indent);
	printf("actions: "); 
	printf("[Action3]\n");
	actions.dump( indent+1, ctx );
}
void SymbolClass::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4C);
	printf("SymbolClass"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("count: "); 
	printf("%i\n", count);
	print_indent(indent);
	printf("symbols: "); 
	{
		printf("[list of Symbols]\n");
		Symbol *item;
		ListItem<Symbol>* i;
		i = symbols.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void DefineSceneAndFrameLabelData::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x56);
	printf("DefineSceneAndFrameLabelData"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("sceneCount: "); 
	print_indent(indent);
	printf("scenes: "); 
	{
		printf("[list of Scenes]\n");
		Scene *item;
		ListItem<Scene>* i;
		i = scenes.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("frameCount: "); 
	print_indent(indent);
	printf("frames: "); 
	{
		printf("[list of Frames]\n");
		Frame *item;
		ListItem<Frame>* i;
		i = frames.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void DefineBinaryData::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x57);
	printf("DefineBinaryData"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("reserved: "); 
	print_indent(indent);
	printf("data: "); 
	printf("[Rest]\n");
	data.dump( indent+1, ctx );
}
void DefineFontName::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x58);
	printf("DefineFontName"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("objectID: "); 
	printf("%i\n", objectID);
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	print_indent(indent);
	printf("copyright: "); 
	printf("%s\n", copyright?copyright:"(nil)");
}
void StackString::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x00);
	printf("StackString"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%s\n", value?value:"(nil)");
}
void StackFloat::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x01);
	printf("StackFloat"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
}
void StackNull::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x02);
	printf("StackNull"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StackUndefined::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x03);
	printf("StackUndefined"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StackRegister::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x04);
	printf("StackRegister"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reg: "); 
	printf("%i\n", reg);
}
void StackBoolean::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x05);
	printf("StackBoolean"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void StackDouble::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x06);
	printf("StackDouble"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
}
void StackInteger::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x07);
	printf("StackInteger"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
}
void StackDictionaryLookup::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x08);
	printf("StackDictionaryLookup"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void StackLargeDictionaryLookup::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x09);
	printf("StackLargeDictionaryLookup"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void UnknownAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //-1);
	printf("UnknownAction"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("data: "); 
	printf("(length %i)\n", len );
	if( len && data != NULL ) {
		int i=0;
		while( i<len ) {
			print_indent( indent+1 );
			for( int n=0; n<8 && i<len; n++ ) {
				printf(" %02X",  data[i] );
				i++;
			}
			printf("\n");
		}
	}
}
void EndAction::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x00);
	printf("EndAction"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void NextFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x04);
	printf("NextFrame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void PreviousFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x05);
	printf("PreviousFrame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Play::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x06);
	printf("Play"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Stop::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x07);
	printf("Stop"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void ToggleQuality::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x08);
	printf("ToggleQuality"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StopSound::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x09);
	printf("StopSound"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void AddCast::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0A);
	printf("AddCast"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Substract::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0B);
	printf("Substract"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Mulitply::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0C);
	printf("Mulitply"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Divide::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0D);
	printf("Divide"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void EqualCast::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0E);
	printf("EqualCast"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void LessThanCast::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0F);
	printf("LessThanCast"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void LogicalAND::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x10);
	printf("LogicalAND"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void LogicalOR::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x11);
	printf("LogicalOR"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void LogicalNOT::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x12);
	printf("LogicalNOT"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StringEqual::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x13);
	printf("StringEqual"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StringLength::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x14);
	printf("StringLength"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void SubString::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x15);
	printf("SubString"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Pop::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x17);
	printf("Pop"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void IntegralPart::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x18);
	printf("IntegralPart"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GetVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1C);
	printf("GetVariable"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void SetVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1D);
	printf("SetVariable"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void SetTargetDynamic::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x20);
	printf("SetTargetDynamic"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void ConcatenateString::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x21);
	printf("ConcatenateString"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x22);
	printf("GetProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void SetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x23);
	printf("SetProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DuplicateSprite::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x24);
	printf("DuplicateSprite"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void RemoveSprite::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x25);
	printf("RemoveSprite"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Trace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x26);
	printf("Trace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StartDrag::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x27);
	printf("StartDrag"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StopDrag::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x28);
	printf("StopDrag"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StringLessThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x29);
	printf("StringLessThan"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Throw::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2A);
	printf("Throw"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void CastObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2B);
	printf("CastObject"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Implements::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2C);
	printf("Implements"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Random::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x30);
	printf("Random"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void MultibyteStringLength::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x31);
	printf("MultibyteStringLength"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void ORD::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x32);
	printf("ORD"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void CHR::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x33);
	printf("CHR"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GetTimer::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x34);
	printf("GetTimer"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void MultibyteSubString::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x35);
	printf("MultibyteSubString"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void MultibyteORD::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x36);
	printf("MultibyteORD"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void MultibyteCHR::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x37);
	printf("MultibyteCHR"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Delete::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3A);
	printf("Delete"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DeleteAll::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3B);
	printf("DeleteAll"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void SetLocalVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3C);
	printf("SetLocalVariable"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void CallFunction::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3D);
	printf("CallFunction"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Return::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3E);
	printf("Return"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Modulo::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x3F);
	printf("Modulo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void New::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x40);
	printf("New"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DeclareLocalVariable::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x41);
	printf("DeclareLocalVariable"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DeclareArray::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x42);
	printf("DeclareArray"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DeclareObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x43);
	printf("DeclareObject"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void TypeOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x44);
	printf("TypeOf"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GetTarget::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x45);
	printf("GetTarget"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Enumerate::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x46);
	printf("Enumerate"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void AddTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x47);
	printf("AddTyped"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void LessThanTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x48);
	printf("LessThanTyped"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void EqualTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x49);
	printf("EqualTyped"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DefineNumber::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4A);
	printf("DefineNumber"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void DefineString::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4B);
	printf("DefineString"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Duplicate::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4C);
	printf("Duplicate"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Swap::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4D);
	printf("Swap"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GetMember::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4E);
	printf("GetMember"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void SetMember::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4F);
	printf("SetMember"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Increment::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x50);
	printf("Increment"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Decrement::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x51);
	printf("Decrement"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void CallMethod::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x52);
	printf("CallMethod"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void NewMethod::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x53);
	printf("NewMethod"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void InstanceOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x54);
	printf("InstanceOf"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void EnumerateObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x55);
	printf("EnumerateObject"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void AND::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x60);
	printf("AND"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OR::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x61);
	printf("OR"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void XOR::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x62);
	printf("XOR"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void ShiftLeft::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x63);
	printf("ShiftLeft"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void ShiftRight::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x64);
	printf("ShiftRight"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void ShiftRightUnsigned::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x65);
	printf("ShiftRightUnsigned"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StrictEqual::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x66);
	printf("StrictEqual"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GreaterThanTyped::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x67);
	printf("GreaterThanTyped"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void StringGreaterThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x68);
	printf("StringGreaterThan"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Extends::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x69);
	printf("Extends"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GotoFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x81);
	printf("GotoFrame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("frame: "); 
	printf("%i\n", frame);
}
void GetURL::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x83);
	printf("GetURL"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("url: "); 
	printf("%s\n", url?url:"(nil)");
	print_indent(indent);
	printf("target: "); 
	printf("%s\n", target?target:"(nil)");
}
void StoreRegister::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x87);
	printf("StoreRegister"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reg: "); 
	printf("%i\n", reg);
}
void Dictionary::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x88);
	printf("Dictionary"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("length: "); 
	printf("%i\n", length);
	print_indent(indent);
	printf("strings: "); 
	{
		printf("[list of Strings]\n");
		String *item;
		ListItem<String>* i;
		i = strings.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void WaitForFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x8A);
	printf("WaitForFrame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("frame: "); 
	printf("%i\n", frame);
	print_indent(indent);
	printf("skip: "); 
	printf("%i\n", skip);
}
void SetTarget::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x8B);
	printf("SetTarget"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("label: "); 
	printf("%s\n", label?label:"(nil)");
}
void GotoLabel::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x8C);
	printf("GotoLabel"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("label: "); 
	printf("%s\n", label?label:"(nil)");
}
void WaitForFrameDynamic::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x8D);
	printf("WaitForFrameDynamic"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("frame: "); 
	printf("%i\n", frame);
	print_indent(indent);
	printf("skip: "); 
	printf("%i\n", skip);
}
void DeclareFunction2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x8E);
	printf("DeclareFunction2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
	print_indent(indent);
	printf("regc: "); 
	printf("%i\n", regc);
	print_indent(indent);
	printf("preloadParent: "); 
	printf("%i\n", preloadParent);
	print_indent(indent);
	printf("preloadRoot: "); 
	printf("%i\n", preloadRoot);
	print_indent(indent);
	printf("suppressSuper: "); 
	printf("%i\n", suppressSuper);
	print_indent(indent);
	printf("preloadSuper: "); 
	printf("%i\n", preloadSuper);
	print_indent(indent);
	printf("suppressArguments: "); 
	printf("%i\n", suppressArguments);
	print_indent(indent);
	printf("preloadArguments: "); 
	printf("%i\n", preloadArguments);
	print_indent(indent);
	printf("suppressThis: "); 
	printf("%i\n", suppressThis);
	print_indent(indent);
	printf("preloadThis: "); 
	printf("%i\n", preloadThis);
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("preloadGlobal: "); 
	printf("%i\n", preloadGlobal);
	print_indent(indent);
	printf("args: "); 
	{
		printf("[list of Parameters]\n");
		Parameter *item;
		ListItem<Parameter>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("length: "); 
	printf("%i\n", length);
	print_indent(indent);
	printf("actions: "); 
	{
		printf("[list of Actions]\n");
		Action *item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void Try::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x8F);
	printf("Try"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("reserved: "); 
	printf("%i\n", reserved);
	print_indent(indent);
	printf("catchInRegister: "); 
	printf("%i\n", catchInRegister);
	print_indent(indent);
	printf("doFinally: "); 
	printf("%i\n", doFinally);
	print_indent(indent);
	printf("doCatch: "); 
	printf("%i\n", doCatch);
	print_indent(indent);
	printf("trySize: "); 
	printf("%i\n", trySize);
	print_indent(indent);
	printf("catchSize: "); 
	printf("%i\n", catchSize);
	print_indent(indent);
	printf("finallySize: "); 
	printf("%i\n", finallySize);
	if( catchInRegister ) {
	print_indent(indent);
	printf("reg: "); 
	printf("%i\n", reg);
	}
}
void With::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x94);
	printf("With"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("size: "); 
	printf("%i\n", size);
}
void PushData::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x96);
	printf("PushData"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("items: "); 
	{
		printf("[list of StackItems]\n");
		StackItem *item;
		ListItem<StackItem>* i;
		i = items.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void GetURL2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x9A);
	printf("GetURL2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("method: "); 
	printf("%i\n", method);
}
void DeclareFunction::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x9B);
	printf("DeclareFunction"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%s\n", name?name:"(nil)");
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
	print_indent(indent);
	printf("args: "); 
	{
		printf("[list of Strings]\n");
		String *item;
		ListItem<String>* i;
		i = args.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
	print_indent(indent);
	printf("length: "); 
	printf("%i\n", length);
}
void BranchAlways::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x99);
	printf("BranchAlways"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("byteOffset: "); 
	printf("%i\n", byteOffset);
}
void BranchIfTrue::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x9D);
	printf("BranchIfTrue"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("byteOffset: "); 
	printf("%i\n", byteOffset);
}
void CallFrame::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x9E);
	printf("CallFrame"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void GotoExpression::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x9F);
	printf("GotoExpression"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("play: "); 
	printf("%i\n", play);
}
void PrivateNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //5);
	printf("PrivateNamespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void Namespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //8);
	printf("Namespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void PackageNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //22);
	printf("PackageNamespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void PackageInternalNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //23);
	printf("PackageInternalNamespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void ProtectedNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //24);
	printf("ProtectedNamespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void ExplicitNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //25);
	printf("ExplicitNamespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void MultinameLNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //26);
	printf("MultinameLNamespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void QName::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //7);
	printf("QName"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("namespaceIndex: "); 
	printf("%i\n", namespaceIndex);
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
}
void QNameA::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //13);
	printf("QNameA"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("namespaceIndex: "); 
	printf("%i\n", namespaceIndex);
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
}
void Multiname::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //9);
	printf("Multiname"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
	print_indent(indent);
	printf("namespaceSetIndex: "); 
	printf("%i\n", namespaceSetIndex);
}
void MultinameA::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //14);
	printf("MultinameA"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
	print_indent(indent);
	printf("namespaceSetIndex: "); 
	printf("%i\n", namespaceSetIndex);
}
void RTQName::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //15);
	printf("RTQName"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
}
void RTQNameA::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //16);
	printf("RTQNameA"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("nameIndex: "); 
	printf("%i\n", nameIndex);
}
void MultinameL::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //27);
	printf("MultinameL"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("namespaceSetIndex: "); 
	printf("%i\n", namespaceSetIndex);
}
void RTQNameL::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //17);
	printf("RTQNameL"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void RTQNameLA::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //18);
	printf("RTQNameLA"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void Slot::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0);
	printf("Slot"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
	print_indent(indent);
	printf("typeIndex: "); 
	printf("%i\n", typeIndex);
	print_indent(indent);
	printf("valueIndex: "); 
	printf("%i\n", valueIndex);
	if( valueIndex != 0 ) {
	print_indent(indent);
	printf("valueKind: "); 
	printf("%i\n", valueKind);
	}
}
void Const::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //6);
	printf("Const"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
	print_indent(indent);
	printf("typeIndex: "); 
	printf("%i\n", typeIndex);
	print_indent(indent);
	printf("valueIndex: "); 
	printf("%i\n", valueIndex);
	if( valueIndex != 0 ) {
	print_indent(indent);
	printf("valueKind: "); 
	printf("%i\n", valueKind);
	}
}
void Method::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //1);
	printf("Method"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("dispID: "); 
	printf("%i\n", dispID);
	print_indent(indent);
	printf("methodInfo: "); 
	printf("%i\n", methodInfo);
}
void Getter::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //2);
	printf("Getter"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("dispID: "); 
	printf("%i\n", dispID);
	print_indent(indent);
	printf("methodInfo: "); 
	printf("%i\n", methodInfo);
}
void Setter::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //3);
	printf("Setter"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("dispID: "); 
	printf("%i\n", dispID);
	print_indent(indent);
	printf("methodInfo: "); 
	printf("%i\n", methodInfo);
}
void Class::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //4);
	printf("Class"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
	print_indent(indent);
	printf("classInfo: "); 
	printf("%i\n", classInfo);
}
void Function::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //5);
	printf("Function"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
	print_indent(indent);
	printf("methodInfo: "); 
	printf("%i\n", methodInfo);
}
void OpBkPt::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x01);
	printf("OpBkPt"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpNop::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x02);
	printf("OpNop"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpThrow::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x03);
	printf("OpThrow"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGetSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x04);
	printf("OpGetSuper"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpSetSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x05);
	printf("OpSetSuper"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpDXNs::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x06);
	printf("OpDXNs"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("dxns: "); 
	printf("%i\n", dxns);
}
void OpDXNsLate::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x07);
	printf("OpDXNsLate"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpKill::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x08);
	printf("OpKill"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("address: "); 
	printf("%i\n", address);
}
void OpLabel::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x09);
	printf("OpLabel"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpIfNlt::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0C);
	printf("OpIfNlt"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfNle::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0D);
	printf("OpIfNle"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfNgt::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0E);
	printf("OpIfNgt"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfNge::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x0F);
	printf("OpIfNge"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpJump::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x10);
	printf("OpJump"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfTrue::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x11);
	printf("OpIfTrue"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfFalse::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x12);
	printf("OpIfFalse"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfEq::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x13);
	printf("OpIfEq"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfNe::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x14);
	printf("OpIfNe"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfLt::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x15);
	printf("OpIfLt"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfLe::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x16);
	printf("OpIfLe"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfGt::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x17);
	printf("OpIfGt"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfGe::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x18);
	printf("OpIfGe"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfStrictEq::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x19);
	printf("OpIfStrictEq"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpIfStrictNe::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1A);
	printf("OpIfStrictNe"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("target: "); 
	printf("%i\n", target);
}
void OpLookupSwitch::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1B);
	printf("OpLookupSwitch"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("defaulTarget: "); 
	printf("%i\n", defaulTarget);
	print_indent(indent);
	printf("caseCount: "); 
	printf("%i\n", caseCount);
	print_indent(indent);
	printf("targetTable: "); 
	{
		printf("[list of S24s]\n");
		S24 *item;
		ListItem<S24>* i;
		i = targetTable.first();
		while( i ) {
			item = i->data();
			if( item ) {
				item->dump(indent+1,ctx);
			}
			i = i->next();
		}
	}
}
void OpPushWith::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1C);
	printf("OpPushWith"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPopScope::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1D);
	printf("OpPopScope"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpNextName::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1E);
	printf("OpNextName"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpHasNext::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x1F);
	printf("OpHasNext"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPushNull::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x20);
	printf("OpPushNull"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPushUndefined::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x21);
	printf("OpPushUndefined"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpNextValue::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x23);
	printf("OpNextValue"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPushByte::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x24);
	printf("OpPushByte"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void OpPushShort::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x25);
	printf("OpPushShort"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("value: "); 
	printf("%i\n", value);
}
void OpPushTrue::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x26);
	printf("OpPushTrue"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPushFalse::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x27);
	printf("OpPushFalse"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPushNaN::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x28);
	printf("OpPushNaN"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPop::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x29);
	printf("OpPop"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpDup::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2A);
	printf("OpDup"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpSwap::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2B);
	printf("OpSwap"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPushString::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2C);
	printf("OpPushString"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void OpPushInt::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2D);
	printf("OpPushInt"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void OpPushUInt::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2E);
	printf("OpPushUInt"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void OpPushDouble::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x2F);
	printf("OpPushDouble"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void OpPushScope::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x30);
	printf("OpPushScope"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpPushNamespace::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x31);
	printf("OpPushNamespace"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void OpHasNext2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x32);
	printf("OpHasNext2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("object: "); 
	printf("%i\n", object);
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void OpNewFunction::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x40);
	printf("OpNewFunction"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("index: "); 
	printf("%i\n", index);
}
void OpCall::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x41);
	printf("OpCall"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpConstruct::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x42);
	printf("OpConstruct"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpCallMethod::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x43);
	printf("OpCallMethod"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("dispID: "); 
	printf("%i\n", dispID);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpCallStatic::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x44);
	printf("OpCallStatic"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("methodID: "); 
	printf("%i\n", methodID);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpCallSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x45);
	printf("OpCallSuper"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpCallProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x46);
	printf("OpCallProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpReturnVoid::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x47);
	printf("OpReturnVoid"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpReturnValue::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x48);
	printf("OpReturnValue"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpConstructSuper::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x49);
	printf("OpConstructSuper"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpConstructProp::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4A);
	printf("OpConstructProp"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpCallPropLex::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4C);
	printf("OpCallPropLex"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpCallSuperVoid::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4E);
	printf("OpCallSuperVoid"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpCallPropVoid::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x4F);
	printf("OpCallPropVoid"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpNewObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x55);
	printf("OpNewObject"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpNewArray::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x56);
	printf("OpNewArray"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("argc: "); 
	printf("%i\n", argc);
}
void OpNewActivation::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x57);
	printf("OpNewActivation"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpNewClass::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x58);
	printf("OpNewClass"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("classIndex: "); 
	printf("%i\n", classIndex);
}
void OpGetDescendants::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x59);
	printf("OpGetDescendants"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpNewCatch::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x5A);
	printf("OpNewCatch"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("exceptionIndex: "); 
	printf("%i\n", exceptionIndex);
}
void OpFindPropStrict::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x5D);
	printf("OpFindPropStrict"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpFindProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x5E);
	printf("OpFindProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpFindDef::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x5F);
	printf("OpFindDef"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpGetLex::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x60);
	printf("OpGetLex"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpSetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x61);
	printf("OpSetProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpGetLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x62);
	printf("OpGetLocal"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("address: "); 
	printf("%i\n", address);
}
void OpSetLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x63);
	printf("OpSetLocal"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("address: "); 
	printf("%i\n", address);
}
void OpGetGlobalScope::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x64);
	printf("OpGetGlobalScope"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGetScopeObject::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x65);
	printf("OpGetScopeObject"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("scopeIndex: "); 
	printf("%i\n", scopeIndex);
}
void OpGetProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x66);
	printf("OpGetProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpInitProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x68);
	printf("OpInitProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpDeleteProperty::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x6A);
	printf("OpDeleteProperty"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpGetSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x6C);
	printf("OpGetSlot"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
}
void OpSetSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x6D);
	printf("OpSetSlot"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
}
void OpGetGlobalSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x6E);
	printf("OpGetGlobalSlot"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
}
void OpSetGlobalSlot::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x6F);
	printf("OpSetGlobalSlot"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("slotID: "); 
	printf("%i\n", slotID);
}
void OpConvertS::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x70);
	printf("OpConvertS"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpEscXelem::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x71);
	printf("OpEscXelem"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpEscXattr::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x72);
	printf("OpEscXattr"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpConvertI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x73);
	printf("OpConvertI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpConvertU::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x74);
	printf("OpConvertU"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpConvertD::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x75);
	printf("OpConvertD"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpConvertB::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x76);
	printf("OpConvertB"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpConvertO::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x77);
	printf("OpConvertO"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCheckFilter::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x78);
	printf("OpCheckFilter"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCoerce::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x80);
	printf("OpCoerce"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpCoerceB::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x81);
	printf("OpCoerceB"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCoerceA::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x82);
	printf("OpCoerceA"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCoerceI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x83);
	printf("OpCoerceI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCoerceD::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x84);
	printf("OpCoerceD"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCoerceS::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x85);
	printf("OpCoerceS"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpAsType::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x86);
	printf("OpAsType"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpAsTypeLate::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x87);
	printf("OpAsTypeLate"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCoerceU::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x88);
	printf("OpCoerceU"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpCoerceO::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x89);
	printf("OpCoerceO"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpNegate::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x90);
	printf("OpNegate"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpIncrement::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x91);
	printf("OpIncrement"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpIncLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x92);
	printf("OpIncLocal"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("address: "); 
	printf("%i\n", address);
}
void OpDecrement::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x93);
	printf("OpDecrement"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpDecLocal::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x94);
	printf("OpDecLocal"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("address: "); 
	printf("%i\n", address);
}
void OpTypeOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x95);
	printf("OpTypeOf"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpNot::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x96);
	printf("OpNot"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpBitNot::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0x97);
	printf("OpBitNot"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpAdd::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA0);
	printf("OpAdd"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpSubtract::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA1);
	printf("OpSubtract"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpMultiply::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA2);
	printf("OpMultiply"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpDivide::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA3);
	printf("OpDivide"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpModulo::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA4);
	printf("OpModulo"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpLShift::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA5);
	printf("OpLShift"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpRShift::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA6);
	printf("OpRShift"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpURShift::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA7);
	printf("OpURShift"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpBitAnd::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA8);
	printf("OpBitAnd"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpBitOr::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xA9);
	printf("OpBitOr"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpBitXor::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xAA);
	printf("OpBitXor"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xAB);
	printf("OpEquals"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpStrictEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xAC);
	printf("OpStrictEquals"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpLessThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xAD);
	printf("OpLessThan"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpLessEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xAE);
	printf("OpLessEquals"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGreaterThan::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xAF);
	printf("OpGreaterThan"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGreaterEquals::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xB0);
	printf("OpGreaterEquals"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpInstanceOf::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xB1);
	printf("OpInstanceOf"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpIsType::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xB2);
	printf("OpIsType"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
}
void OpIsTypeLate::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xB3);
	printf("OpIsTypeLate"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpIn::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xB4);
	printf("OpIn"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpIncrementI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC0);
	printf("OpIncrementI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpDecrementI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC1);
	printf("OpDecrementI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpIncLocalI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC2);
	printf("OpIncLocalI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("address: "); 
	printf("%i\n", address);
}
void OpDecLocalI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC3);
	printf("OpDecLocalI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("address: "); 
	printf("%i\n", address);
}
void OpNegateI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC4);
	printf("OpNegateI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpAddI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC5);
	printf("OpAddI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpSubtractI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC6);
	printf("OpSubtractI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpMultiplyI::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xC7);
	printf("OpMultiplyI"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGetLocal0::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD0);
	printf("OpGetLocal0"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGetLocal1::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD1);
	printf("OpGetLocal1"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGetLocal2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD2);
	printf("OpGetLocal2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpGetLocal3::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD3);
	printf("OpGetLocal3"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpSetLocal0::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD4);
	printf("OpSetLocal0"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpSetLocal1::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD5);
	printf("OpSetLocal1"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpSetLocal2::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD6);
	printf("OpSetLocal2"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpSetLocal3::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xD7);
	printf("OpSetLocal3"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
void OpDebugReg::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xEF);
	printf("OpDebugReg"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("unknown: "); 
	printf("%i\n", unknown);
	print_indent(indent);
	printf("name: "); 
	printf("%i\n", name);
	print_indent(indent);
	printf("reg: "); 
	printf("%i\n", reg);
	print_indent(indent);
	printf("line: "); 
	printf("%i\n", line);
}
void OpDebugLine::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xF0);
	printf("OpDebugLine"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("line: "); 
	printf("%i\n", line);
}
void OpDebugFile::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xF1);
	printf("OpDebugFile"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("file: "); 
	printf("%i\n", file);
}
void OpBkPtLine::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xF2);
	printf("OpBkPtLine"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
	print_indent(indent);
	printf("line: "); 
	printf("%i\n", line);
}
void OpTimestamp::dump( int indent, Context *ctx ) {
	print_indent(indent);
		printf("[%02X] ", type ); //0xF3);
	printf("OpTimestamp"); // (sz %i)", getSize( ctx ) );
	printf("\n");
	indent++;
}
}
