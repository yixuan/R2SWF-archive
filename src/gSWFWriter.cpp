#include "SWF.h"
#include "SWFItem.h"
#include "SWFList.h"
namespace SWF {
//////////////////////////////////// Rectangle
void Rectangle::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Rectangle @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(bits,5);
	w->putNBitInt(left,bits,true);
	w->putNBitInt(right,bits,true);
	w->putNBitInt(top,bits,true);
	w->putNBitInt(bottom,bits,true);
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Rectangle has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Color
void Color::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Color @%i\n", start/8 );
		dump(1,ctx);
	}
w->putByte(red);
	w->putByte(green);
	w->putByte(blue);
	if( ctx->alpha ) {
		w->putByte(alpha);
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Color has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// String
void String::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE String @%i\n", start/8 );
		dump(1,ctx);
	}
w->putString(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: String has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// String2
void String2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE String2 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putPStringU30(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: String2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Transform
void Transform::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Transform @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(scaled,1);
	if( scaled ) {
		w->putNBitInt(bitsScale,5);
	w->putNBitFixed(scaleX,bitsScale,16,true);
	w->putNBitFixed(scaleY,bitsScale,16,true);
	}
w->putNBitInt(skewed,1);
	if( skewed ) {
		w->putNBitInt(bitsSkew,5);
	w->putNBitFixed(skewX,bitsSkew,16,true);
	w->putNBitFixed(skewY,bitsSkew,16,true);
	}
w->putNBitInt(bitsTranslate,5);
	w->putNBitInt(transX,bitsTranslate,true);
	w->putNBitInt(transY,bitsTranslate,true);
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Transform has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ColorTransform2
void ColorTransform2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ColorTransform2 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(hasOffset,1);
	w->putNBitInt(hasFactor,1);
	w->putNBitInt(bits,4);
	if( hasFactor ) {
		w->putNBitInt(factorRed,bits,true);
	w->putNBitInt(factorGreen,bits,true);
	w->putNBitInt(factorBlue,bits,true);
	w->putNBitInt(factorAlpha,bits,true);
	}
	if( hasOffset ) {
		w->putNBitInt(offsetRed,bits,true);
	w->putNBitInt(offsetGreen,bits,true);
	w->putNBitInt(offsetBlue,bits,true);
	w->putNBitInt(offsetAlpha,bits,true);
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ColorTransform2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Header
void Header::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Header @%i\n", start/8 );
		dump(1,ctx);
	}
size.write(w,ctx);
w->putNBitInt(framerate,16);
	w->putWord(frames);
	{
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list tags has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Header has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// LineStyle
void LineStyle::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE LineStyle @%i\n", start/8 );
		dump(1,ctx);
	}
w->putWord(width);
	if( ctx->tagVersion < 4 ) {
		color.write(w,ctx);
	}
	if( ctx->tagVersion > 3 ) {
		w->putNBitInt(startCapStyle,2);
	w->putNBitInt(jointStyle,2);
	w->putNBitInt(hasFill,1);
	w->putNBitInt(noHScale,1);
	w->putNBitInt(noVScale,1);
	w->putNBitInt(pixelHinting,1);
	w->putNBitInt(reserved,5);
	w->putNBitInt(noClose,1);
	w->putNBitInt(endCapStyle,2);
	if( jointStyle==2 ) {
		w->putNBitFixed2(miterLimitFactor,16,8,true);
	}
	if( hasFill ) {
	{
		ListItem<Style>* i;
		i = fillStyles.first();
		for( int j=0; j<1; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list fillStyles has %i items (%i expected)\n", j, 1 );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !hasFill ) {
		fillColor.write(w,ctx);
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: LineStyle has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StyleList
void StyleList::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StyleList @%i\n", start/8 );
		dump(1,ctx);
	}
    {
        int v = n_fillStyles;
        if( v >= 255  && ctx->tagVersion >= 2 ) {
            w->putByte( 255 );
            w->putWord( v );
        } else {
            w->putByte( v );
        }
    }
	{
		ListItem<Style>* i;
		i = fillStyles.first();
		for( int j=0; j<n_fillStyles; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list fillStyles has %i items (%i expected)\n", j, n_fillStyles );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
    {
        int v = n_lineStyles;
        if( v >= 255  && ctx->tagVersion >= 2 ) {
            w->putByte( 255 );
            w->putWord( v );
        } else {
            w->putByte( v );
        }
    }
	{
		ListItem<LineStyle>* i;
		i = lineStyles.first();
		for( int j=0; j<n_lineStyles; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list lineStyles has %i items (%i expected)\n", j, n_lineStyles );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putNBitInt(fillBits,4);
		ctx->fillBits = fillBits;
	w->putNBitInt(lineBits,4);
		ctx->lineBits = lineBits;
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StyleList has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ShapeSetup
void ShapeSetup::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ShapeSetup @%i\n", start/8 );
		dump(1,ctx);
	}
ShapeItem::writeHeader( w, ctx, getSize(ctx,w->getBitPosition())/8 );
		w->putNBitInt(hasNewStyles,1);
	w->putNBitInt(hasLineStyle,1);
	w->putNBitInt(hasFillStyle1,1);
	w->putNBitInt(hasFillStyle0,1);
	w->putNBitInt(hasMoveTo,1);
	if( hasMoveTo ) {
		w->putNBitInt(xybits,5);
	w->putNBitInt(x,xybits,true);
	w->putNBitInt(y,xybits,true);
	}
	if( hasFillStyle0 ) {
		w->putNBitInt(fillStyle0,ctx->fillBits);
	}
	if( hasFillStyle1 ) {
		w->putNBitInt(fillStyle1,ctx->fillBits);
	}
	if( hasLineStyle ) {
		w->putNBitInt(lineStyle,ctx->lineBits);
	}
	if( hasNewStyles ) {
	w->byteAlign();
styles.write(w,ctx);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ShapeSetup has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// CurveTo
void CurveTo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE CurveTo @%i\n", start/8 );
		dump(1,ctx);
	}
ShapeItem::writeHeader( w, ctx, getSize(ctx,w->getBitPosition())/8 );
		w->putNBitInt(bits,4);
	w->putNBitInt(x1,bits+2,true);
	w->putNBitInt(y1,bits+2,true);
	w->putNBitInt(x2,bits+2,true);
	w->putNBitInt(y2,bits+2,true);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: CurveTo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Shape
void Shape::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Shape @%i\n", start/8 );
		dump(1,ctx);
	}
	{
		ListItem<ShapeItem>* i;
		i = edges.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list edges has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Shape has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GlyphShape
void GlyphShape::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GlyphShape @%i\n", start/8 );
		dump(1,ctx);
	}
	ctx->fillBits = 1;
	ctx->lineBits = 0;
w->putNBitInt(fillBits,4);
	w->putNBitInt(lineBits,4);
	{
		ListItem<ShapeItem>* i;
		i = edges.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list edges has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GlyphShape has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GradientItem
void GradientItem::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GradientItem @%i\n", start/8 );
		dump(1,ctx);
	}
w->putByte(position);
	color.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GradientItem has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Symbol
void Symbol::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Symbol @%i\n", start/8 );
		dump(1,ctx);
	}
w->putWord(objectID);
	w->putString(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Symbol has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Frame
void Frame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Frame @%i\n", start/8 );
		dump(1,ctx);
	}
w->putEncodedU32(number);
	w->putString(label);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Frame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Scene
void Scene::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Scene @%i\n", start/8 );
		dump(1,ctx);
	}
w->putEncodedU32(offset);
	w->putString(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Scene has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Parameter
void Parameter::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Parameter @%i\n", start/8 );
		dump(1,ctx);
	}
w->putByte(reg);
	w->putString(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Parameter has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// UChar
void UChar::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE UChar @%i\n", start/8 );
		dump(1,ctx);
	}
w->putByte(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: UChar has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// UShort
void UShort::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE UShort @%i\n", start/8 );
		dump(1,ctx);
	}
w->putWord(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: UShort has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ULong
void ULong::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ULong @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(value,32);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ULong has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Short
void Short::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Short @%i\n", start/8 );
		dump(1,ctx);
	}
w->putWord(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Short has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Float
void Float::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Float @%i\n", start/8 );
		dump(1,ctx);
	}
w->putFloat(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Float has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Double
void Double::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Double @%i\n", start/8 );
		dump(1,ctx);
	}
w->putDouble2(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Double has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Kerning
void Kerning::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Kerning @%i\n", start/8 );
		dump(1,ctx);
	}
w->putByte(a);
	w->putByte(b);
	w->putNBitInt(adjustment,16,true);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Kerning has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// WideKerning
void WideKerning::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE WideKerning @%i\n", start/8 );
		dump(1,ctx);
	}
w->putWord(a);
	w->putWord(b);
	w->putWord(adjustment);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: WideKerning has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextEntry
void TextEntry::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextEntry @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(glyph,ctx->glyphBits);
	w->putNBitInt(advance,ctx->advanceBits,true);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextEntry has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextEntry2
void TextEntry2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextEntry2 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(glyph,ctx->glyphBits);
	w->putNBitInt(advance,ctx->advanceBits,true);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextEntry2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextRecord6
void TextRecord6::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextRecord6 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(isSetup,1);
	if( isSetup ) {
		w->putNBitInt(reserved,3);
	w->putNBitInt(hasFont,1);
	w->putNBitInt(hasColor,1);
	w->putNBitInt(hasMoveY,1);
	w->putNBitInt(hasMoveX,1);
	if( hasFont ) {
		w->putWord(objectID);
	}
	if( hasColor ) {
		color.write(w,ctx);
	}
	if( hasMoveX ) {
		w->putWord(x);
	}
	if( hasMoveY ) {
		w->putWord(y);
	}
	if( hasFont ) {
		w->putWord(fontHeight);
	}
	}
	if( !isSetup ) {
		w->putNBitInt(nGlyphs,7);
	{
		ListItem<TextEntry>* i;
		i = glyphs.first();
		for( int j=0; j<nGlyphs; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list glyphs has %i items (%i expected)\n", j, nGlyphs );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	w->byteAlign();
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextRecord6 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextRecord62
void TextRecord62::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextRecord62 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(isSetup,1);
	if( isSetup ) {
		w->putNBitInt(reserved,3);
	w->putNBitInt(hasFont,1);
	w->putNBitInt(hasColor,1);
	w->putNBitInt(hasMoveY,1);
	w->putNBitInt(hasMoveX,1);
	if( hasFont ) {
		w->putWord(objectID);
	}
	if( hasColor ) {
		color.write(w,ctx);
	}
	if( hasMoveX ) {
		w->putWord(x);
	}
	if( hasMoveY ) {
		w->putWord(y);
	}
	if( hasFont ) {
		w->putWord(fontHeight);
	}
	}
	if( !isSetup ) {
		w->putNBitInt(nGlyphs,7);
	{
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		for( int j=0; j<nGlyphs; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list glyphs has %i items (%i expected)\n", j, nGlyphs );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	w->byteAlign();
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextRecord62 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextRecord7
void TextRecord7::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextRecord7 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(isSetup,1);
	w->putNBitInt(reserved,3);
	w->putNBitInt(hasFont,1);
	w->putNBitInt(hasColor,1);
	w->putNBitInt(hasMoveY,1);
	w->putNBitInt(hasMoveX,1);
	if( hasFont ) {
		w->putWord(objectID);
	}
	if( hasColor ) {
		color.write(w,ctx);
	}
	if( hasMoveX ) {
		w->putWord(x);
	}
	if( hasMoveY ) {
		w->putWord(y);
	}
	if( hasFont ) {
		w->putWord(fontHeight);
	}
	if( isSetup ) {
		w->putByte(nGlyphs);
	{
		ListItem<TextEntry>* i;
		i = glyphs.first();
		for( int j=0; j<nGlyphs; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list glyphs has %i items (%i expected)\n", j, nGlyphs );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextRecord7 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextRecord72
void TextRecord72::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextRecord72 @%i\n", start/8 );
		dump(1,ctx);
	}
	ctx->alpha = 1;
w->putNBitInt(isSetup,1);
	w->putNBitInt(reserved,3);
	w->putNBitInt(hasFont,1);
	w->putNBitInt(hasColor,1);
	w->putNBitInt(hasMoveY,1);
	w->putNBitInt(hasMoveX,1);
	if( hasFont ) {
		w->putWord(fontRef);
	}
	if( hasColor ) {
		color.write(w,ctx);
	}
	if( hasMoveX ) {
		w->putWord(x);
	}
	if( hasMoveY ) {
		w->putWord(y);
	}
	if( hasFont ) {
		w->putWord(fontHeight);
	}
	if( isSetup ) {
		w->putByte(nGlyphs);
	{
		ListItem<TextEntry2>* i;
		i = glyphs.first();
		for( int j=0; j<nGlyphs; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list glyphs has %i items (%i expected)\n", j, nGlyphs );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextRecord72 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextRecord
void TextRecord::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextRecord @%i\n", start/8 );
		dump(1,ctx);
	}
	if( ctx->tagVersion < 2 ) {
	{
		ListItem<TextRecord6>* i;
		i = records.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list records has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->tagVersion >= 2 ) {
		string.write(w,ctx);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextRecord has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TextRecord2
void TextRecord2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TextRecord2 @%i\n", start/8 );
		dump(1,ctx);
	}
	if( ctx->swfVersion < 7 ) {
	{
		ListItem<TextRecord62>* i;
		i = records.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list records has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( ctx->swfVersion >= 7 ) {
		textString.write(w,ctx);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TextRecord2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Button
void Button::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Button @%i\n", start/8 );
		dump(1,ctx);
	}
w->putNBitInt(reserved1,2);
	if( ctx->swfVersion < 8 ) {
		w->putNBitInt(reserved2,2);
	}
	if( ctx->swfVersion >= 8 ) {
		w->putNBitInt(hasBlendMode,1);
	w->putNBitInt(hasFilterList,1);
	}
w->putNBitInt(hitTest,1);
	w->putNBitInt(down,1);
	w->putNBitInt(over,1);
	w->putNBitInt(up,1);
	if( hitTest || down || over || up ) {
		w->putWord(objectID);
	w->putWord(depth);
	transform.write(w,ctx);
	if( ctx->tagVersion >= 2 ) {
		colorTransform.write(w,ctx);
	}
	if( hasFilterList ) {
		w->putByte(numFilters);
	{
		ListItem<Filter>* i;
		i = filters.first();
		for( int j=0; j<numFilters; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list filters has %i items (%i expected)\n", j, numFilters );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
		w->putByte(blendMode);
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Button has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Event
void Event::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Event @%i\n", start/8 );
		dump(1,ctx);
	}
	w->byteAlign();
w->putWord(flags1);
	if( ctx->swfVersion>=6 ) {
		w->putWord(flags2);
	}
	if( (flags1 | flags2) ) {
		w->putInt(actionLength);
	{
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list actions has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Event has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Condition
void Condition::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Condition @%i\n", start/8 );
		dump(1,ctx);
	}
		if( !ctx->isLast ) {
			int r = 0;
	r++;
	r++;
	r++;
	r++;
	r++;
	r++;
	r++;
	r++;
	r += 7;
	r++;
	{
		Action* item;
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			item = i->data();
			if( item ) {
				r += item->getSize(ctx,r);
			}
			i = i->next();
		}
	}
next = (r/8) - (-2);
		} else {
			next = 0;
		}
	w->putWord(next);
	w->putNBitInt(menuEnter,1);
	w->putNBitInt(pointerReleaseOutside,1);
	w->putNBitInt(pointerDragEnter,1);
	w->putNBitInt(pointerDragLeave,1);
	w->putNBitInt(pointerReleaseInside,1);
	w->putNBitInt(pointerPush,1);
	w->putNBitInt(pointerLeave,1);
	w->putNBitInt(pointerEnter,1);
	w->putNBitInt(key,7);
	w->putNBitInt(menuLeave,1);
	{
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list actions has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Condition has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// U30
void U30::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE U30 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: U30 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// S24
void S24::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE S24 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putS24(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: S24 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ValueKind
void ValueKind::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ValueKind @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(index);
	w->putByte(kind);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ValueKind has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MethodInfo
void MethodInfo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MethodInfo @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(paramCount);
	w->putU30(retType);
	{
		ListItem<U30>* i;
		i = paramTypes.first();
		for( unsigned int j=0; j<paramCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list paramTypes has %i items (%i expected)\n", j, paramCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(nameIndex);
	w->putNBitInt(hasParamNames,1);
	w->putNBitInt(setSDXNs,1);
	w->putNBitInt(isExplicit,1);
	w->putNBitInt(ignoreRest,1);
	w->putNBitInt(hasOptional,1);
	w->putNBitInt(needRest,1);
	w->putNBitInt(needActivation,1);
	w->putNBitInt(needArguments,1);
	if( hasOptional ) {
		w->putU30(optionalCount);
	{
		ListItem<ValueKind>* i;
		i = optional.first();
		for( unsigned int j=0; j<optionalCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list optional has %i items (%i expected)\n", j, optionalCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasParamNames ) {
	{
		ListItem<U30>* i;
		i = paramNames.first();
		for( unsigned int j=0; j<paramCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list paramNames has %i items (%i expected)\n", j, paramCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MethodInfo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MetadataInfo
void MetadataInfo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MetadataInfo @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(nameIndex);
	w->putU30(valuesCount);
	{
		ListItem<U30>* i;
		i = keys.first();
		for( unsigned int j=0; j<valuesCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list keys has %i items (%i expected)\n", j, valuesCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<U30>* i;
		i = values.first();
		for( unsigned int j=0; j<valuesCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list values has %i items (%i expected)\n", j, valuesCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MetadataInfo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// NamespaceSet
void NamespaceSet::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE NamespaceSet @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(count);
	{
		ListItem<U30>* i;
		i = namespaces.first();
		for( unsigned int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list namespaces has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: NamespaceSet has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TraitInfo
void TraitInfo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TraitInfo @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(nameIndex);
	w->putNBitInt(reserved,1);
	w->putNBitInt(hasMetadata,1);
	w->putNBitInt(override,1);
	w->putNBitInt(final,1);
	{
		ListItem<Trait>* i;
		i = trait.first();
		for( unsigned int j=0; j<1; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list trait has %i items (%i expected)\n", j, 1 );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	if( hasMetadata ) {
		w->putU30(metadataCount);
	{
		ListItem<U30>* i;
		i = metadata.first();
		for( unsigned int j=0; j<metadataCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list metadata has %i items (%i expected)\n", j, metadataCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TraitInfo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// InstanceInfo
void InstanceInfo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE InstanceInfo @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(nameIndex);
	w->putU30(superIndex);
	w->putNBitInt(reserved,4);
	w->putNBitInt(hasProtectedNS,1);
	w->putNBitInt(interface,1);
	w->putNBitInt(final,1);
	w->putNBitInt(sealed,1);
	if( hasProtectedNS ) {
		w->putU30(protectedNS);
	}
w->putU30(interfaceCount);
	{
		ListItem<U30>* i;
		i = interfaces.first();
		for( unsigned int j=0; j<interfaceCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list interfaces has %i items (%i expected)\n", j, interfaceCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(iInitIndex);
	w->putU30(traitCount);
	{
		ListItem<TraitInfo>* i;
		i = traits.first();
		for( unsigned int j=0; j<traitCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list traits has %i items (%i expected)\n", j, traitCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: InstanceInfo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ClassInfo
void ClassInfo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ClassInfo @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(cInitIndex);
	w->putU30(traitCount);
	{
		ListItem<TraitInfo>* i;
		i = traits.first();
		for( unsigned int j=0; j<traitCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list traits has %i items (%i expected)\n", j, traitCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ClassInfo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ScriptInfo
void ScriptInfo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ScriptInfo @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(initIndex);
	w->putU30(traitCount);
	{
		ListItem<TraitInfo>* i;
		i = traits.first();
		for( unsigned int j=0; j<traitCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list traits has %i items (%i expected)\n", j, traitCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ScriptInfo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Exception
void Exception::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Exception @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(tryStart);
	w->putU30(tryEnd);
	w->putU30(target);
	w->putU30(type);
	w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Exception has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MethodBody
void MethodBody::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MethodBody @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(methodInfo);
	w->putU30(maxStack);
	w->putU30(maxRegs);
	w->putU30(scopeDepth);
	w->putU30(maxScope);
	w->putU30(codeLength);
	{
		ListItem<OpCode>* i;
		i = code.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list code has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(exceptionCount);
	{
		ListItem<Exception>* i;
		i = exceptions.first();
		for( unsigned int j=0; j<exceptionCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list exceptions has %i items (%i expected)\n", j, exceptionCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(traitCount);
	{
		ListItem<TraitInfo>* i;
		i = traits.first();
		for( unsigned int j=0; j<traitCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list traits has %i items (%i expected)\n", j, traitCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MethodBody has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Constants
void Constants::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Constants @%i\n", start/8 );
		dump(1,ctx);
	}
w->putU30(intCount);
	{
		ListItem<U30>* i;
		i = ints.first();
		for( unsigned int j=0; j<
				( intCount < 1
				  ? 0
				  : intCount - 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list ints has %i items (%i expected)\n", j, 
				//( intCount < 1
				//  ? 0
				//  : intCount - 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(uintCount);
	{
		ListItem<U30>* i;
		i = uints.first();
		for( unsigned int j=0; j<
				( uintCount < 1
				  ? 0
				  : uintCount - 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list uints has %i items (%i expected)\n", j, 
				//( uintCount < 1
				//  ? 0
				//  : uintCount - 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(doubleCount);
	{
		ListItem<Double>* i;
		i = doubles.first();
		for( unsigned int j=0; j<
				( doubleCount < 1
				  ? 0
				  : doubleCount - 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list doubles has %i items (%i expected)\n", j, 
				//( doubleCount < 1
				//  ? 0
				//  : doubleCount - 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(stringCount);
	{
		ListItem<String2>* i;
		i = strings.first();
		for( unsigned int j=0; j<
				( stringCount < 1
				  ? 0
				  : stringCount - 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list strings has %i items (%i expected)\n", j, 
				//( stringCount < 1
				//  ? 0
				//  : stringCount - 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(namespaceConstantCount);
	{
		ListItem<NamespaceConstant>* i;
		i = namespaces.first();
		for( unsigned int j=0; j<
				( namespaceConstantCount < 1
				  ? 0
				  : namespaceConstantCount - 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list namespaces has %i items (%i expected)\n", j, 
				//( namespaceConstantCount < 1
				//  ? 0
				//  : namespaceConstantCount - 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(namespaceSetCount);
	{
		ListItem<NamespaceSet>* i;
		i = namespaceSets.first();
		for( unsigned int j=0; j<
				( namespaceSetCount < 1
				  ? 0
				  : namespaceSetCount - 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list namespaceSets has %i items (%i expected)\n", j, 
				//( namespaceSetCount < 1
				//  ? 0
				//  : namespaceSetCount - 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(multinameConstantCount);
	{
		ListItem<MultinameConstant>* i;
		i = multinames.first();
		for( unsigned int j=0; j<
				( multinameConstantCount < 1
				  ? 0
				  : multinameConstantCount - 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list multinames has %i items (%i expected)\n", j, 
				//( multinameConstantCount < 1
				//  ? 0
				//  : multinameConstantCount - 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Constants has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Action3
void Action3::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Action3 @%i\n", start/8 );
		dump(1,ctx);
	}
w->putWord(minorVersion);
	w->putWord(majorVersion);
	constants.write(w,ctx);
w->putU30(methodInfoCount);
	{
		ListItem<MethodInfo>* i;
		i = methods.first();
		for( unsigned int j=0; j<methodInfoCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list methods has %i items (%i expected)\n", j, methodInfoCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(metadataInfoCount);
	{
		ListItem<MetadataInfo>* i;
		i = metadata.first();
		for( unsigned int j=0; j<metadataInfoCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list metadata has %i items (%i expected)\n", j, metadataInfoCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(classCount);
	{
		ListItem<InstanceInfo>* i;
		i = instances.first();
		for( unsigned int j=0; j<classCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list instances has %i items (%i expected)\n", j, classCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<ClassInfo>* i;
		i = classes.first();
		for( unsigned int j=0; j<classCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list classes has %i items (%i expected)\n", j, classCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(scriptCount);
	{
		ListItem<ScriptInfo>* i;
		i = scripts.first();
		for( unsigned int j=0; j<scriptCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list scripts has %i items (%i expected)\n", j, scriptCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putU30(methodBodyCount);
	{
		ListItem<MethodBody>* i;
		i = methodBodies.first();
		for( unsigned int j=0; j<methodBodyCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list methodBodies has %i items (%i expected)\n", j, methodBodyCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Action3 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ZoneData
void ZoneData::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ZoneData @%i\n", start/8 );
		dump(1,ctx);
	}
w->putHalf(position);
	w->putHalf(size);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ZoneData has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ZoneArray
void ZoneArray::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ZoneArray @%i\n", start/8 );
		dump(1,ctx);
	}
w->putByte(count);
	{
		ListItem<ZoneData>* i;
		i = zones.first();
		for( unsigned int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list zones has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putNBitInt(zoneX,1);
	w->putNBitInt(zoneY,1);
	w->putNBitInt(reserved,6);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ZoneArray has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// UnknownFilter
void UnknownFilter::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE UnknownFilter @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	if( len && data ) {
		w->putData( data, len );
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: UnknownFilter has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DropShadow
void DropShadow::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DropShadow @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
color.write(w,ctx);
w->putNBitFixed2(blurX,32,16,true);
	w->putNBitFixed2(blurY,32,16,true);
	w->putNBitFixed2(angle,32,16,true);
	w->putNBitFixed2(distance,32,16,true);
	w->putNBitFixed2(strength,16,8,true);
	w->putNBitInt(innerShadow,1);
	w->putNBitInt(knockout,1);
	w->putNBitInt(compositeSource,1);
	w->putNBitInt(passes,5);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DropShadow has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Blur
void Blur::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Blur @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putNBitFixed2(blurX,32,16,true);
	w->putNBitFixed2(blurY,32,16,true);
	w->putNBitInt(passes,5);
	w->putNBitInt(reserved1,3);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Blur has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Glow
void Glow::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Glow @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
color.write(w,ctx);
w->putNBitFixed2(blurX,32,16,true);
	w->putNBitFixed2(blurY,32,16,true);
	w->putNBitFixed2(strength,16,8,true);
	w->putNBitInt(innerGlow,1);
	w->putNBitInt(knockout,1);
	w->putNBitInt(compositeSource,1);
	w->putNBitInt(passes,5);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Glow has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Bevel
void Bevel::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Bevel @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
shadowColor.write(w,ctx);
highlightColor.write(w,ctx);
w->putNBitFixed2(blurX,32,16,true);
	w->putNBitFixed2(blurY,32,16,true);
	w->putNBitFixed2(angle,32,16,true);
	w->putNBitFixed2(distance,32,16,true);
	w->putNBitFixed2(strength,16,8,true);
	w->putNBitInt(innerShadow,1);
	w->putNBitInt(knockout,1);
	w->putNBitInt(compositeSource,1);
	w->putNBitInt(onTop,1);
	w->putNBitInt(passes,4);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Bevel has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GradientGlow
void GradientGlow::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GradientGlow @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
w->putByte(numColors);
	{
		ListItem<Color>* i;
		i = colors.first();
		for( unsigned int j=0; j<numColors; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list colors has %i items (%i expected)\n", j, numColors );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<UChar>* i;
		i = ratio.first();
		for( unsigned int j=0; j<numColors; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list ratio has %i items (%i expected)\n", j, numColors );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putNBitFixed2(blurX,32,16,true);
	w->putNBitFixed2(blurY,32,16,true);
	w->putNBitFixed2(angle,32,16,true);
	w->putNBitFixed2(distance,32,16,true);
	w->putNBitFixed2(strength,16,8,true);
	w->putNBitInt(innerGlow,1);
	w->putNBitInt(knockout,1);
	w->putNBitInt(compositeSource,1);
	w->putNBitInt(onTop,1);
	w->putNBitInt(passes,4);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GradientGlow has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Convolution
void Convolution::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Convolution @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
w->putByte(matrixX);
	w->putByte(matrixY);
	w->putFloat(divizor);
	w->putFloat(bias);
	{
		ListItem<Float>* i;
		i = matrix.first();
		for( unsigned int j=0; j<(matrixX * matrixY); j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list matrix has %i items (%i expected)\n", j, (matrixX * matrixY) );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
defaultColor.write(w,ctx);
w->putNBitInt(reserved,5);
	w->putNBitInt(clamp,1);
	w->putNBitInt(preserveAlpha,1);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Convolution has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ColorMatrix
void ColorMatrix::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ColorMatrix @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	{
		ListItem<Float>* i;
		i = matrix.first();
		for( unsigned int j=0; j<20; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list matrix has %i items (%i expected)\n", j, 20 );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ColorMatrix has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GradientBevel
void GradientBevel::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GradientBevel @%i\n", start/8 );
		dump(1,ctx);
	}
Filter::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
w->putByte(numColors);
	{
		ListItem<Color>* i;
		i = colors.first();
		for( unsigned int j=0; j<numColors; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list colors has %i items (%i expected)\n", j, numColors );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<UChar>* i;
		i = ratio.first();
		for( unsigned int j=0; j<numColors; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list ratio has %i items (%i expected)\n", j, numColors );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putNBitFixed2(blurX,32,16,true);
	w->putNBitFixed2(blurY,32,16,true);
	w->putNBitFixed2(angle,32,16,true);
	w->putNBitFixed2(distance,32,16,true);
	w->putNBitFixed2(strength,16,8,true);
	w->putNBitInt(innerGlow,1);
	w->putNBitInt(knockout,1);
	w->putNBitInt(compositeSource,1);
	w->putNBitInt(onTop,1);
	w->putNBitInt(passes,4);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GradientBevel has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Solid
void Solid::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Solid @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		color.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Solid has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// LinearGradient
void LinearGradient::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE LinearGradient @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		matrix.write(w,ctx);
	if( ctx->tagVersion < 4 ) {
		w->putNBitInt(reserved,4);
	}
	if( ctx->tagVersion >= 4 ) {
		w->putNBitInt(spreadMode,2);
	w->putNBitInt(interpolationMode,2);
	}
w->putNBitInt(count,4);
	{
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		for( int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list gradientColors has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: LinearGradient has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RadialGradient
void RadialGradient::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RadialGradient @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		matrix.write(w,ctx);
	if( ctx->tagVersion < 4 ) {
		w->putNBitInt(reserved,4);
	}
	if( ctx->tagVersion >= 4 ) {
		w->putNBitInt(spreadMode,2);
	w->putNBitInt(interpolationMode,2);
	}
w->putNBitInt(count,4);
	{
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		for( int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list gradientColors has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RadialGradient has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ShiftedRadialGradient
void ShiftedRadialGradient::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ShiftedRadialGradient @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		matrix.write(w,ctx);
	if( ctx->tagVersion < 4 ) {
		w->putNBitInt(reserved,4);
	}
	if( ctx->tagVersion >= 4 ) {
		w->putNBitInt(spreadMode,2);
	w->putNBitInt(interpolationMode,2);
	}
w->putNBitInt(count,4);
	{
		ListItem<GradientItem>* i;
		i = gradientColors.first();
		for( int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list gradientColors has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putNBitFixed2(shift,16,8,true);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ShiftedRadialGradient has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TiledBitmap
void TiledBitmap::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TiledBitmap @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	matrix.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TiledBitmap has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ClippedBitmap
void ClippedBitmap::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ClippedBitmap @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	matrix.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ClippedBitmap has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TiledBitmap2
void TiledBitmap2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TiledBitmap2 @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	matrix.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TiledBitmap2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ClippedBitmap2
void ClippedBitmap2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ClippedBitmap2 @%i\n", start/8 );
		dump(1,ctx);
	}
Style::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	matrix.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ClippedBitmap2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// UnknownTag
void UnknownTag::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE UnknownTag @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	if( len && data ) {
		w->putData( data, len );
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: UnknownTag has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// End
void End::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE End @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: End has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ShowFrame
void ShowFrame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ShowFrame @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ShowFrame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineShape
void DefineShape::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineShape @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 0;
	ctx->many_shapes = 0;
	ctx->tagVersion = 1;
w->putWord(objectID);
	bounds.write(w,ctx);
styles.write(w,ctx);
shapes.write(w,ctx);
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineShape has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RemoveObject
void RemoveObject::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RemoveObject @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putWord(depth);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RemoveObject has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineBits
void DefineBits::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineBits @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineBits has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetBackgroundColor
void SetBackgroundColor::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetBackgroundColor @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 0;
color.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetBackgroundColor has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineText
void DefineText::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineText @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	bounds.write(w,ctx);
transform.write(w,ctx);
w->putByte(glyphBits);
		ctx->glyphBits = glyphBits;
	w->putByte(advanceBits);
		ctx->advanceBits = advanceBits;
	ctx->alpha = 0;
	ctx->tagVersion = 1;
	{
		ListItem<TextRecord>* i;
		i = records.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list records has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineText has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineText2
void DefineText2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineText2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
w->putWord(objectID);
	bounds.write(w,ctx);
transform.write(w,ctx);
w->putByte(glyphBits);
		ctx->glyphBits = glyphBits;
	w->putByte(advanceBits);
		ctx->advanceBits = advanceBits;
	{
		ListItem<TextRecord2>* i;
		i = records.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list records has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineText2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DoAction
void DoAction::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DoAction @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	{
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list actions has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DoAction has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineFontInfo
void DefineFontInfo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineFontInfo @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putByte(nameLength);
	if( nameLength && nameData ) {
		w->putData( nameData, nameLength );
	}
	w->byteAlign();
w->putNBitInt(reserved,2);
	w->putNBitInt(smallTextOrUnicode,1);
	w->putNBitInt(isShiftJIS,1);
	w->putNBitInt(isANSII,1);
	w->putNBitInt(isItalic,1);
	w->putNBitInt(isBold,1);
	w->putNBitInt(isWide,1);
	if( ctx->swfVersion>=6 ) {
		w->putByte(language);
	}
map.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineFontInfo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineSound
void DefineSound::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineSound @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putNBitInt(format,4);
	w->putNBitInt(rate,2);
	w->putNBitInt(is16bit,1);
	w->putNBitInt(stereo,1);
	w->putInt(samples);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineSound has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StartSound
void StartSound::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StartSound @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putNBitInt(reserved,2);
	w->putNBitInt(stopPlayback,1);
	w->putNBitInt(noMultiple,1);
	w->putNBitInt(hasEnvelope,1);
	w->putNBitInt(hasLoop,1);
	w->putNBitInt(hasOutPoint,1);
	w->putNBitInt(hasInPoint,1);
	if( hasInPoint ) {
		w->putInt(inPoint);
	}
	if( hasOutPoint ) {
		w->putInt(outPoint);
	}
	if( hasLoop ) {
		w->putWord(loop);
	}
	if( hasEnvelope ) {
		w->putByte(envelopeCount);
	envelopeData.write(w,ctx);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StartSound has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineShape2
void DefineShape2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineShape2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 0;
	ctx->many_shapes = 1;
	ctx->tagVersion = 2;
w->putWord(objectID);
	bounds.write(w,ctx);
styles.write(w,ctx);
shapes.write(w,ctx);
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineShape2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineShape3
void DefineShape3::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineShape3 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 3;
w->putWord(objectID);
	bounds.write(w,ctx);
styles.write(w,ctx);
shapes.write(w,ctx);
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineShape3 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineShape4
void DefineShape4::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineShape4 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineShape4 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineShape5
void DefineShape5::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineShape5 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 5;
w->putWord(objectID);
	bounds.write(w,ctx);
strokeBounds.write(w,ctx);
w->putNBitInt(reserved,6);
	w->putNBitInt(nonScalingStrokes,1);
	w->putNBitInt(scalingStrokes,1);
	styles.write(w,ctx);
shapes.write(w,ctx);
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineShape5 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineMorphShape
void DefineMorphShape::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineMorphShape @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineMorphShape has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineFontInfo2
void DefineFontInfo2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineFontInfo2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putByte(nameLength);
	if( nameLength && nameData ) {
		w->putData( nameData, nameLength );
	}
	w->byteAlign();
w->putNBitInt(reserved,2);
	w->putNBitInt(smallTextOrUnicode,1);
	w->putNBitInt(isShiftJIS,1);
	w->putNBitInt(isANSII,1);
	w->putNBitInt(isItalic,1);
	w->putNBitInt(isBold,1);
	w->putNBitInt(isWide,1);
	if( ctx->swfVersion>=6 ) {
		w->putByte(language);
	}
map.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineFontInfo2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SoundStreamHead
void SoundStreamHead::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SoundStreamHead @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putNBitInt(reserved,4);
	w->putNBitInt(playbackRate,2);
	w->putNBitInt(playbackSize,1);
	w->putNBitInt(playbackStereo,1);
	w->putNBitInt(compression,4);
	w->putNBitInt(soundRate,2);
	w->putNBitInt(soundSize,1);
	w->putNBitInt(soundStereo,1);
	w->putWord(sampleSize);
	if( compression==2 ) {
		latencySeek.write(w,ctx);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SoundStreamHead has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineBitsLossless
void DefineBitsLossless::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineBitsLossless @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putByte(format);
	w->putWord(width);
	w->putWord(height);
	if( format==3 ) {
		w->putByte(n_colormap);
	}
data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineBitsLossless has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineBitsJPEG2
void DefineBitsJPEG2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineBitsJPEG2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineBitsJPEG2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineBitsJPEG3
void DefineBitsJPEG3::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineBitsJPEG3 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putInt(offset_to_alpha);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineBitsJPEG3 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineBitsLossless2
void DefineBitsLossless2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineBitsLossless2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putByte(format);
	w->putWord(width);
	w->putWord(height);
	if( format==3 ) {
		w->putByte(n_colormap);
	}
data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineBitsLossless2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// PlaceObject2
void PlaceObject2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE PlaceObject2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putNBitInt(hasEventHandler,1);
	w->putNBitInt(hasClipDepth,1);
	w->putNBitInt(hasName,1);
	w->putNBitInt(hasMorph,1);
	w->putNBitInt(hasColorTransform,1);
	w->putNBitInt(hasTransform,1);
	w->putNBitInt(hasID,1);
	w->putNBitInt(replace,1);
	w->putWord(depth);
	if( hasID ) {
		w->putWord(objectID);
	}
	if( hasTransform ) {
		transform.write(w,ctx);
	}
	if( hasColorTransform ) {
		colorTransform.write(w,ctx);
	}
	if( hasMorph ) {
		w->putWord(morph);
	}
	if( hasName ) {
		w->putString(name);
	}
	if( hasClipDepth ) {
		w->putWord(clipDepth);
	}
	if( hasEventHandler ) {
		w->putWord(reserved);
	w->putWord(allflags1);
	if( ctx->swfVersion>=6 ) {
		w->putWord(allflags2);
	}
	{
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list events has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: PlaceObject2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RemoveObject2
void RemoveObject2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RemoveObject2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(depth);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RemoveObject2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineEditText
void DefineEditText::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineEditText @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->alpha = 1;
w->putWord(objectID);
	size.write(w,ctx);
w->putNBitInt(hasText,1);
	w->putNBitInt(wordWrap,1);
	w->putNBitInt(multiLine,1);
	w->putNBitInt(password,1);
	w->putNBitInt(readOnly,1);
	w->putNBitInt(hasColor,1);
	w->putNBitInt(hasMaxLength,1);
	w->putNBitInt(hasFont,1);
	w->putNBitInt(reserved,1);
	w->putNBitInt(autoSize,1);
	w->putNBitInt(hasLayout,1);
	w->putNBitInt(notSelectable,1);
	w->putNBitInt(hasBorder,1);
	w->putNBitInt(reserved2,1);
	w->putNBitInt(isHTML,1);
	w->putNBitInt(useOutlines,1);
	if( hasFont ) {
		w->putWord(fontRef);
	w->putWord(fontHeight);
	}
	if( hasColor ) {
		color.write(w,ctx);
	}
	if( hasMaxLength ) {
		w->putWord(maxLength);
	}
	if( hasLayout ) {
		w->putByte(align);
	w->putWord(leftMargin);
	w->putWord(rightMargin);
	w->putWord(indent);
	w->putWord(leading);
	}
w->putString(variableName);
	if( hasText ) {
		w->putString(initialText);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineEditText has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineSprite
void DefineSprite::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineSprite @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putWord(frames);
	{
		ListItem<Tag>* i;
		i = tags.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list tags has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineSprite has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// FrameLabel
void FrameLabel::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE FrameLabel @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(label);
	flags.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: FrameLabel has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SoundStreamHead2
void SoundStreamHead2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SoundStreamHead2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putNBitInt(reserved,4);
	w->putNBitInt(playbackRate,2);
	w->putNBitInt(playbackSize,1);
	w->putNBitInt(playbackStereo,1);
	w->putNBitInt(compression,4);
	w->putNBitInt(soundRate,2);
	w->putNBitInt(soundSize,1);
	w->putNBitInt(soundStereo,1);
	w->putWord(sampleSize);
	if( compression==2 ) {
		latencySeek.write(w,ctx);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SoundStreamHead2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineFont
void DefineFont::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineFont @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->tagVersion = 1;
	ctx->wideGlyphOffsets = 0;
w->putWord(objectID);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineFont has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineFont2
void DefineFont2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineFont2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->tagVersion = 2;
w->putWord(objectID);
	w->putNBitInt(hasLayout,1);
	w->putNBitInt(isShiftJIS,1);
	w->putNBitInt(isUnicode,1);
	w->putNBitInt(isANSII,1);
	w->putNBitInt(wideGlyphOffsets,1);
		ctx->wideGlyphOffsets = wideGlyphOffsets;
	w->putNBitInt(wideMap,1);
		ctx->wideMap = wideMap;
	w->putNBitInt(italic,1);
	w->putNBitInt(bold,1);
	w->putByte(language);
	w->putPString(name);
	w->putWord(glyphCount);
		ctx->glyphCount = glyphCount;
	glyphs.write(w,ctx);
	if( hasLayout ) {
		w->putWord(ascent);
	w->putWord(descent);
	w->putWord(leading);
	{
		ListItem<Short>* i;
		i = advance.first();
		for( unsigned int j=0; j<glyphCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list advance has %i items (%i expected)\n", j, glyphCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<Rectangle>* i;
		i = bounds.first();
		for( unsigned int j=0; j<glyphCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list bounds has %i items (%i expected)\n", j, glyphCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putWord(kerningCount);
	if( wideMap ) {
	{
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		for( unsigned int j=0; j<kerningCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list wideKerning has %i items (%i expected)\n", j, kerningCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	{
		ListItem<Kerning>* i;
		i = kerning.first();
		for( unsigned int j=0; j<kerningCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list kerning has %i items (%i expected)\n", j, kerningCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineFont2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineFont3
void DefineFont3::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineFont3 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->tagVersion = 2;
w->putWord(objectID);
	w->putNBitInt(hasLayout,1);
	w->putNBitInt(isShiftJIS,1);
	w->putNBitInt(isUnicode,1);
	w->putNBitInt(isANSII,1);
	w->putNBitInt(wideGlyphOffsets,1);
		ctx->wideGlyphOffsets = wideGlyphOffsets;
	w->putNBitInt(wideMap,1);
		ctx->wideMap = wideMap;
	w->putNBitInt(italic,1);
	w->putNBitInt(bold,1);
	w->putByte(language);
	w->putPString(name);
	w->putWord(glyphCount);
		ctx->glyphCount = glyphCount;
	glyphs.write(w,ctx);
	if( hasLayout ) {
		w->putWord(ascent);
	w->putWord(descent);
	w->putWord(leading);
	{
		ListItem<Short>* i;
		i = advance.first();
		for( unsigned int j=0; j<glyphCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list advance has %i items (%i expected)\n", j, glyphCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<Rectangle>* i;
		i = bounds.first();
		for( unsigned int j=0; j<glyphCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list bounds has %i items (%i expected)\n", j, glyphCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putWord(kerningCount);
	if( wideMap ) {
	{
		ListItem<WideKerning>* i;
		i = wideKerning.first();
		for( unsigned int j=0; j<kerningCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list wideKerning has %i items (%i expected)\n", j, kerningCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( !wideMap ) {
	{
		ListItem<Kerning>* i;
		i = kerning.first();
		for( unsigned int j=0; j<kerningCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list kerning has %i items (%i expected)\n", j, kerningCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineFont3 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineButton
void DefineButton::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineButton @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->tagVersion = 1;
w->putWord(objectID);
	{
		ListItem<Button>* i;
		i = buttons.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list buttons has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list actions has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineButton has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineButton2
void DefineButton2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineButton2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	ctx->tagVersion = 2;
w->putWord(objectID);
	w->putNBitInt(reserved,7);
	w->putNBitInt(menu,1);
	w->putWord(buttonsSize);
	{
		ListItem<Button>* i;
		i = buttons.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list buttons has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	{
		ListItem<Condition>* i;
		i = conditions.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list conditions has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineButton2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Export
void Export::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Export @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(count);
	{
		ListItem<Symbol>* i;
		i = symbols.first();
		for( unsigned int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list symbols has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Export has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Import
void Import::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Import @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(url);
	w->putWord(count);
	{
		ListItem<Symbol>* i;
		i = symbols.first();
		for( unsigned int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list symbols has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Import has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DoInitAction
void DoInitAction::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DoInitAction @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(sprite);
	{
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list actions has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DoInitAction has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SoundStreamBlock
void SoundStreamBlock::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SoundStreamBlock @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	if( len && data ) {
		w->putData( data, len );
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SoundStreamBlock has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineVideoStream
void DefineVideoStream::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineVideoStream @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putWord(frames);
	w->putWord(width);
	w->putWord(height);
	w->putNBitInt(reserved,5);
	w->putNBitInt(deblocking,2);
	w->putNBitInt(smoothing,1);
	w->putByte(codec);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineVideoStream has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// VideoFrame
void VideoFrame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE VideoFrame @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putWord(frame);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: VideoFrame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ScriptLimits
void ScriptLimits::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ScriptLimits @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(maxRecursionDepth);
	w->putWord(timeout);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ScriptLimits has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetTabIndex
void SetTabIndex::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetTabIndex @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(depth);
	w->putWord(tabIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetTabIndex has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// PlaceObject3
void PlaceObject3::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE PlaceObject3 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putNBitInt(hasEventHandler,1);
	w->putNBitInt(hasClipDepth,1);
	w->putNBitInt(hasName,1);
	w->putNBitInt(hasMorph,1);
	w->putNBitInt(hasColorTransform,1);
	w->putNBitInt(hasTransform,1);
	w->putNBitInt(hasID,1);
	w->putNBitInt(replace,1);
	w->putNBitInt(reserved1,5);
	w->putNBitInt(hasCacheAsBitmap,1);
	w->putNBitInt(hasBlendMode,1);
	w->putNBitInt(hasFilterList,1);
	w->putWord(depth);
	if( hasID ) {
		w->putWord(objectID);
	}
	if( hasTransform ) {
		transform.write(w,ctx);
	}
	if( hasColorTransform ) {
		colorTransform.write(w,ctx);
	}
	if( hasMorph ) {
		w->putWord(morph);
	}
	if( hasName ) {
		w->putString(name);
	}
	if( hasClipDepth ) {
		w->putWord(clipDepth);
	}
	if( hasFilterList ) {
		w->putByte(numFilters);
	{
		ListItem<Filter>* i;
		i = filters.first();
		for( unsigned int j=0; j<numFilters; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list filters has %i items (%i expected)\n", j, numFilters );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	if( hasBlendMode ) {
		w->putByte(blendMode);
	}
	if( hasCacheAsBitmap ) {
		w->putByte(bitmapCaching);
	}
	if( hasEventHandler ) {
		w->putWord(reserved);
	w->putWord(allflags1);
	if( ctx->swfVersion>=6 ) {
		w->putWord(allflags2);
	}
	{
		ListItem<Event>* i;
		i = events.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list events has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: PlaceObject3 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ImportAssets2
void ImportAssets2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ImportAssets2 @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(url);
	w->putByte(reserved1);
	w->putByte(reserved2);
	w->putWord(count);
	{
		ListItem<Symbol>* i;
		i = symbols.first();
		for( unsigned int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list symbols has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ImportAssets2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// FileAttributes
void FileAttributes::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE FileAttributes @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putNBitInt(reserved1,3);
	w->putNBitInt(hasMetaData,1);
	if( ctx->swfVersion < 9 ) {
		w->putNBitInt(reserved2,3);
	}
	if( ctx->swfVersion >= 9 ) {
		w->putNBitInt(allowABC,1);
	w->putNBitInt(suppressCrossDomainCaching,1);
	w->putNBitInt(swfRelativeURLs,1);
	}
w->putNBitInt(useNetwork,1);
	w->putNBitInt(reserved3,24);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: FileAttributes has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineFontAlignZones
void DefineFontAlignZones::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineFontAlignZones @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putNBitInt(csmTableHint,2);
	w->putNBitInt(reserved,6);
	{
		ListItem<ZoneArray>* i;
		i = zoneArrays.first();
		for( unsigned int j=0; j<ctx->glyphCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list zoneArrays has %i items (%i expected)\n", j, ctx->glyphCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineFontAlignZones has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// CSMTextSettings
void CSMTextSettings::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE CSMTextSettings @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putNBitInt(useFlashType,2);
	w->putNBitInt(gridFit,3);
	w->putNBitInt(reserved1,3);
	w->putFloat(thickness);
	w->putFloat(sharpness);
	w->putByte(reserved2);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: CSMTextSettings has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Metadata
void Metadata::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Metadata @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(RDF);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Metadata has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineScalingGrid
void DefineScalingGrid::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineScalingGrid @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	splitter.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineScalingGrid has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DoABC
void DoABC::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DoABC @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		actions.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DoABC has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DoABCDefine
void DoABCDefine::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DoABCDefine @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putInt(flags);
	w->putString(name);
	actions.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DoABCDefine has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SymbolClass
void SymbolClass::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SymbolClass @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(count);
	{
		ListItem<Symbol>* i;
		i = symbols.first();
		for( unsigned int j=0; j<count; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list symbols has %i items (%i expected)\n", j, count );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SymbolClass has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineSceneAndFrameLabelData
void DefineSceneAndFrameLabelData::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineSceneAndFrameLabelData @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putEncodedU32(sceneCount);
	{
		ListItem<Scene>* i;
		i = scenes.first();
		for( unsigned int j=0; j<sceneCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list scenes has %i items (%i expected)\n", j, sceneCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putEncodedU32(frameCount);
	{
		ListItem<Frame>* i;
		i = frames.first();
		for( unsigned int j=0; j<frameCount; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list frames has %i items (%i expected)\n", j, frameCount );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineSceneAndFrameLabelData has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineBinaryData
void DefineBinaryData::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineBinaryData @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putInt(reserved);
	data.write(w,ctx);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineBinaryData has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineFontName
void DefineFontName::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineFontName @%i\n", start/8 );
		dump(1,ctx);
	}
Tag::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(objectID);
	w->putString(name);
	w->putString(copyright);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineFontName has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackString
void StackString::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackString @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackString has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackFloat
void StackFloat::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackFloat @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putFloat(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackFloat has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackNull
void StackNull::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackNull @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackNull has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackUndefined
void StackUndefined::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackUndefined @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackUndefined has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackRegister
void StackRegister::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackRegister @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(reg);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackRegister has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackBoolean
void StackBoolean::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackBoolean @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackBoolean has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackDouble
void StackDouble::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackDouble @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putDouble(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackDouble has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackInteger
void StackInteger::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackInteger @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putInt(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackInteger has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackDictionaryLookup
void StackDictionaryLookup::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackDictionaryLookup @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackDictionaryLookup has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StackLargeDictionaryLookup
void StackLargeDictionaryLookup::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StackLargeDictionaryLookup @%i\n", start/8 );
		dump(1,ctx);
	}
StackItem::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StackLargeDictionaryLookup has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// UnknownAction
void UnknownAction::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE UnknownAction @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	if( len && data ) {
		w->putData( data, len );
	}
	w->byteAlign();
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: UnknownAction has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// EndAction
void EndAction::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE EndAction @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: EndAction has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// NextFrame
void NextFrame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE NextFrame @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: NextFrame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// PreviousFrame
void PreviousFrame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE PreviousFrame @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: PreviousFrame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Play
void Play::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Play @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Play has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Stop
void Stop::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Stop @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Stop has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ToggleQuality
void ToggleQuality::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ToggleQuality @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ToggleQuality has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StopSound
void StopSound::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StopSound @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StopSound has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// AddCast
void AddCast::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE AddCast @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: AddCast has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Substract
void Substract::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Substract @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Substract has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Mulitply
void Mulitply::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Mulitply @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Mulitply has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Divide
void Divide::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Divide @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Divide has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// EqualCast
void EqualCast::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE EqualCast @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: EqualCast has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// LessThanCast
void LessThanCast::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE LessThanCast @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: LessThanCast has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// LogicalAND
void LogicalAND::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE LogicalAND @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: LogicalAND has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// LogicalOR
void LogicalOR::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE LogicalOR @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: LogicalOR has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// LogicalNOT
void LogicalNOT::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE LogicalNOT @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: LogicalNOT has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StringEqual
void StringEqual::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StringEqual @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StringEqual has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StringLength
void StringLength::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StringLength @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StringLength has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SubString
void SubString::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SubString @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SubString has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Pop
void Pop::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Pop @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Pop has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// IntegralPart
void IntegralPart::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE IntegralPart @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: IntegralPart has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GetVariable
void GetVariable::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GetVariable @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GetVariable has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetVariable
void SetVariable::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetVariable @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetVariable has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetTargetDynamic
void SetTargetDynamic::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetTargetDynamic @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetTargetDynamic has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ConcatenateString
void ConcatenateString::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ConcatenateString @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ConcatenateString has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GetProperty
void GetProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GetProperty @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GetProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetProperty
void SetProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetProperty @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DuplicateSprite
void DuplicateSprite::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DuplicateSprite @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DuplicateSprite has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RemoveSprite
void RemoveSprite::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RemoveSprite @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RemoveSprite has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Trace
void Trace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Trace @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Trace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StartDrag
void StartDrag::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StartDrag @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StartDrag has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StopDrag
void StopDrag::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StopDrag @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StopDrag has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StringLessThan
void StringLessThan::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StringLessThan @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StringLessThan has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Throw
void Throw::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Throw @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Throw has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// CastObject
void CastObject::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE CastObject @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: CastObject has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Implements
void Implements::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Implements @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Implements has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Random
void Random::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Random @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Random has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MultibyteStringLength
void MultibyteStringLength::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MultibyteStringLength @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MultibyteStringLength has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ORD
void ORD::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ORD @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ORD has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// CHR
void CHR::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE CHR @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: CHR has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GetTimer
void GetTimer::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GetTimer @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GetTimer has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MultibyteSubString
void MultibyteSubString::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MultibyteSubString @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MultibyteSubString has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MultibyteORD
void MultibyteORD::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MultibyteORD @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MultibyteORD has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MultibyteCHR
void MultibyteCHR::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MultibyteCHR @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MultibyteCHR has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Delete
void Delete::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Delete @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Delete has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DeleteAll
void DeleteAll::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DeleteAll @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DeleteAll has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetLocalVariable
void SetLocalVariable::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetLocalVariable @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetLocalVariable has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// CallFunction
void CallFunction::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE CallFunction @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: CallFunction has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Return
void Return::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Return @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Return has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Modulo
void Modulo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Modulo @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Modulo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// New
void New::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE New @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: New has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DeclareLocalVariable
void DeclareLocalVariable::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DeclareLocalVariable @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DeclareLocalVariable has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DeclareArray
void DeclareArray::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DeclareArray @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DeclareArray has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DeclareObject
void DeclareObject::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DeclareObject @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DeclareObject has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// TypeOf
void TypeOf::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE TypeOf @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: TypeOf has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GetTarget
void GetTarget::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GetTarget @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GetTarget has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Enumerate
void Enumerate::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Enumerate @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Enumerate has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// AddTyped
void AddTyped::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE AddTyped @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: AddTyped has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// LessThanTyped
void LessThanTyped::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE LessThanTyped @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: LessThanTyped has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// EqualTyped
void EqualTyped::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE EqualTyped @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: EqualTyped has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineNumber
void DefineNumber::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineNumber @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineNumber has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DefineString
void DefineString::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DefineString @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DefineString has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Duplicate
void Duplicate::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Duplicate @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Duplicate has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Swap
void Swap::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Swap @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Swap has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GetMember
void GetMember::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GetMember @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GetMember has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetMember
void SetMember::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetMember @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetMember has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Increment
void Increment::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Increment @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Increment has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Decrement
void Decrement::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Decrement @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Decrement has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// CallMethod
void CallMethod::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE CallMethod @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: CallMethod has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// NewMethod
void NewMethod::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE NewMethod @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: NewMethod has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// InstanceOf
void InstanceOf::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE InstanceOf @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: InstanceOf has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// EnumerateObject
void EnumerateObject::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE EnumerateObject @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: EnumerateObject has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// AND
void AND::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE AND @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: AND has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OR
void OR::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OR @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OR has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// XOR
void XOR::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE XOR @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: XOR has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ShiftLeft
void ShiftLeft::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ShiftLeft @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ShiftLeft has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ShiftRight
void ShiftRight::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ShiftRight @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ShiftRight has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ShiftRightUnsigned
void ShiftRightUnsigned::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ShiftRightUnsigned @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ShiftRightUnsigned has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StrictEqual
void StrictEqual::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StrictEqual @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StrictEqual has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GreaterThanTyped
void GreaterThanTyped::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GreaterThanTyped @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GreaterThanTyped has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StringGreaterThan
void StringGreaterThan::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StringGreaterThan @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StringGreaterThan has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Extends
void Extends::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Extends @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Extends has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GotoFrame
void GotoFrame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GotoFrame @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(frame);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GotoFrame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GetURL
void GetURL::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GetURL @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(url);
	w->putString(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GetURL has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// StoreRegister
void StoreRegister::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE StoreRegister @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(reg);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: StoreRegister has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Dictionary
void Dictionary::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Dictionary @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(length);
	{
		ListItem<String>* i;
		i = strings.first();
		for( unsigned int j=0; j<length; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list strings has %i items (%i expected)\n", j, length );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Dictionary has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// WaitForFrame
void WaitForFrame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE WaitForFrame @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(frame);
	w->putByte(skip);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: WaitForFrame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// SetTarget
void SetTarget::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE SetTarget @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(label);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: SetTarget has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GotoLabel
void GotoLabel::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GotoLabel @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(label);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GotoLabel has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// WaitForFrameDynamic
void WaitForFrameDynamic::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE WaitForFrameDynamic @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(frame);
	w->putByte(skip);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: WaitForFrameDynamic has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DeclareFunction2
void DeclareFunction2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DeclareFunction2 @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  - length );
		w->putString(name);
	w->putWord(argc);
	w->putByte(regc);
	w->putNBitInt(preloadParent,1);
	w->putNBitInt(preloadRoot,1);
	w->putNBitInt(suppressSuper,1);
	w->putNBitInt(preloadSuper,1);
	w->putNBitInt(suppressArguments,1);
	w->putNBitInt(preloadArguments,1);
	w->putNBitInt(suppressThis,1);
	w->putNBitInt(preloadThis,1);
	w->putNBitInt(reserved,7);
	w->putNBitInt(preloadGlobal,1);
	{
		ListItem<Parameter>* i;
		i = args.first();
		for( unsigned int j=0; j<argc; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list args has %i items (%i expected)\n", j, argc );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putWord(length);
	{
		ListItem<Action>* i;
		i = actions.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list actions has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DeclareFunction2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Try
void Try::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Try @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putNBitInt(reserved,5);
	w->putNBitInt(catchInRegister,1);
	w->putNBitInt(doFinally,1);
	w->putNBitInt(doCatch,1);
	w->putWord(trySize);
	w->putWord(catchSize);
	w->putWord(finallySize);
	if( catchInRegister ) {
		w->putByte(reg);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Try has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// With
void With::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE With @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(size);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: With has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// PushData
void PushData::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE PushData @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	{
		ListItem<StackItem>* i;
		i = items.first();
		while( i ) {
			if( !i->data() ) {
				//printf("WARNING: list items has an invalid item\n" );
			} else {
				ctx->isLast = i->isLast();
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: PushData has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GetURL2
void GetURL2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GetURL2 @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(method);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GetURL2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// DeclareFunction
void DeclareFunction::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE DeclareFunction @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putString(name);
	w->putWord(argc);
	{
		ListItem<String>* i;
		i = args.first();
		for( unsigned int j=0; j<argc; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list args has %i items (%i expected)\n", j, argc );
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
w->putWord(length);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: DeclareFunction has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// BranchAlways
void BranchAlways::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE BranchAlways @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(byteOffset);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: BranchAlways has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// BranchIfTrue
void BranchIfTrue::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE BranchIfTrue @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putWord(byteOffset);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: BranchIfTrue has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// CallFrame
void CallFrame::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE CallFrame @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: CallFrame has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// GotoExpression
void GotoExpression::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE GotoExpression @%i\n", start/8 );
		dump(1,ctx);
	}
Action::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(play);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: GotoExpression has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// PrivateNamespace
void PrivateNamespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE PrivateNamespace @%i\n", start/8 );
		dump(1,ctx);
	}
NamespaceConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: PrivateNamespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Namespace
void Namespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Namespace @%i\n", start/8 );
		dump(1,ctx);
	}
NamespaceConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Namespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// PackageNamespace
void PackageNamespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE PackageNamespace @%i\n", start/8 );
		dump(1,ctx);
	}
NamespaceConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: PackageNamespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// PackageInternalNamespace
void PackageInternalNamespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE PackageInternalNamespace @%i\n", start/8 );
		dump(1,ctx);
	}
NamespaceConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: PackageInternalNamespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ProtectedNamespace
void ProtectedNamespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ProtectedNamespace @%i\n", start/8 );
		dump(1,ctx);
	}
NamespaceConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ProtectedNamespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// ExplicitNamespace
void ExplicitNamespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE ExplicitNamespace @%i\n", start/8 );
		dump(1,ctx);
	}
NamespaceConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: ExplicitNamespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MultinameLNamespace
void MultinameLNamespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MultinameLNamespace @%i\n", start/8 );
		dump(1,ctx);
	}
NamespaceConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MultinameLNamespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// QName
void QName::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE QName @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(namespaceIndex);
	w->putU30(nameIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: QName has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// QNameA
void QNameA::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE QNameA @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(namespaceIndex);
	w->putU30(nameIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: QNameA has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Multiname
void Multiname::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Multiname @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(nameIndex);
	w->putU30(namespaceSetIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Multiname has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MultinameA
void MultinameA::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MultinameA @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(nameIndex);
	w->putU30(namespaceSetIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MultinameA has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RTQName
void RTQName::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RTQName @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(nameIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RTQName has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RTQNameA
void RTQNameA::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RTQNameA @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(nameIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RTQNameA has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// MultinameL
void MultinameL::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE MultinameL @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(namespaceSetIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: MultinameL has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RTQNameL
void RTQNameL::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RTQNameL @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RTQNameL has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// RTQNameLA
void RTQNameLA::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE RTQNameLA @%i\n", start/8 );
		dump(1,ctx);
	}
MultinameConstant::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: RTQNameLA has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Slot
void Slot::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Slot @%i\n", start/8 );
		dump(1,ctx);
	}
Trait::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	w->putU30(typeIndex);
	w->putU30(valueIndex);
	if( valueIndex != 0 ) {
		w->putByte(valueKind);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Slot has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Const
void Const::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Const @%i\n", start/8 );
		dump(1,ctx);
	}
Trait::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	w->putU30(typeIndex);
	w->putU30(valueIndex);
	if( valueIndex != 0 ) {
		w->putByte(valueKind);
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Const has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Method
void Method::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Method @%i\n", start/8 );
		dump(1,ctx);
	}
Trait::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(dispID);
	w->putU30(methodInfo);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Method has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Getter
void Getter::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Getter @%i\n", start/8 );
		dump(1,ctx);
	}
Trait::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(dispID);
	w->putU30(methodInfo);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Getter has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Setter
void Setter::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Setter @%i\n", start/8 );
		dump(1,ctx);
	}
Trait::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(dispID);
	w->putU30(methodInfo);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Setter has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Class
void Class::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Class @%i\n", start/8 );
		dump(1,ctx);
	}
Trait::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	w->putU30(classInfo);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Class has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// Function
void Function::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE Function @%i\n", start/8 );
		dump(1,ctx);
	}
Trait::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	w->putU30(methodInfo);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: Function has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpBkPt
void OpBkPt::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpBkPt @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpBkPt has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNop
void OpNop::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNop @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNop has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpThrow
void OpThrow::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpThrow @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpThrow has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetSuper
void OpGetSuper::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetSuper @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetSuper has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetSuper
void OpSetSuper::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetSuper @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetSuper has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDXNs
void OpDXNs::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDXNs @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(dxns);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDXNs has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDXNsLate
void OpDXNsLate::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDXNsLate @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDXNsLate has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpKill
void OpKill::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpKill @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(address);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpKill has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpLabel
void OpLabel::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpLabel @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpLabel has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfNlt
void OpIfNlt::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfNlt @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfNlt has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfNle
void OpIfNle::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfNle @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfNle has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfNgt
void OpIfNgt::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfNgt @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfNgt has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfNge
void OpIfNge::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfNge @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfNge has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpJump
void OpJump::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpJump @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpJump has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfTrue
void OpIfTrue::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfTrue @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfTrue has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfFalse
void OpIfFalse::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfFalse @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfFalse has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfEq
void OpIfEq::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfEq @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfEq has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfNe
void OpIfNe::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfNe @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfNe has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfLt
void OpIfLt::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfLt @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfLt has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfLe
void OpIfLe::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfLe @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfLe has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfGt
void OpIfGt::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfGt @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfGt has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfGe
void OpIfGe::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfGe @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfGe has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfStrictEq
void OpIfStrictEq::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfStrictEq @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfStrictEq has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIfStrictNe
void OpIfStrictNe::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIfStrictNe @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(target);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIfStrictNe has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpLookupSwitch
void OpLookupSwitch::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpLookupSwitch @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putS24(defaulTarget);
	w->putU30(caseCount);
	{
		ListItem<S24>* i;
		i = targetTable.first();
		for( unsigned int j=0; j<
				( caseCount + 1 )
			; j++ ) {
			if( !i || !i->data() ) {
				//printf("WARNING: list targetTable has %i items (%i expected)\n", j, 
				//( caseCount + 1 )
			  //);
			} else {
				i->data()->write( w, ctx );
			}
			i = i->next();
		}
	}
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpLookupSwitch has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushWith
void OpPushWith::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushWith @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushWith has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPopScope
void OpPopScope::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPopScope @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPopScope has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNextName
void OpNextName::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNextName @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNextName has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpHasNext
void OpHasNext::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpHasNext @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpHasNext has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushNull
void OpPushNull::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushNull @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushNull has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushUndefined
void OpPushUndefined::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushUndefined @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushUndefined has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNextValue
void OpNextValue::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNextValue @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNextValue has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushByte
void OpPushByte::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushByte @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushByte has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushShort
void OpPushShort::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushShort @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(value);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushShort has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushTrue
void OpPushTrue::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushTrue @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushTrue has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushFalse
void OpPushFalse::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushFalse @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushFalse has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushNaN
void OpPushNaN::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushNaN @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushNaN has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPop
void OpPop::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPop @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPop has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDup
void OpDup::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDup @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDup has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSwap
void OpSwap::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSwap @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSwap has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushString
void OpPushString::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushString @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushString has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushInt
void OpPushInt::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushInt @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushInt has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushUInt
void OpPushUInt::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushUInt @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushUInt has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushDouble
void OpPushDouble::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushDouble @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushDouble has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushScope
void OpPushScope::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushScope @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushScope has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpPushNamespace
void OpPushNamespace::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpPushNamespace @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpPushNamespace has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpHasNext2
void OpHasNext2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpHasNext2 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(object);
	w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpHasNext2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNewFunction
void OpNewFunction::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNewFunction @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(index);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNewFunction has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCall
void OpCall::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCall @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCall has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConstruct
void OpConstruct::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConstruct @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConstruct has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCallMethod
void OpCallMethod::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCallMethod @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(dispID);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCallMethod has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCallStatic
void OpCallStatic::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCallStatic @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(methodID);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCallStatic has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCallSuper
void OpCallSuper::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCallSuper @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCallSuper has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCallProperty
void OpCallProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCallProperty @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCallProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpReturnVoid
void OpReturnVoid::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpReturnVoid @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpReturnVoid has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpReturnValue
void OpReturnValue::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpReturnValue @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpReturnValue has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConstructSuper
void OpConstructSuper::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConstructSuper @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConstructSuper has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConstructProp
void OpConstructProp::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConstructProp @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConstructProp has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCallPropLex
void OpCallPropLex::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCallPropLex @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCallPropLex has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCallSuperVoid
void OpCallSuperVoid::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCallSuperVoid @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCallSuperVoid has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCallPropVoid
void OpCallPropVoid::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCallPropVoid @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCallPropVoid has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNewObject
void OpNewObject::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNewObject @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNewObject has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNewArray
void OpNewArray::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNewArray @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(argc);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNewArray has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNewActivation
void OpNewActivation::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNewActivation @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNewActivation has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNewClass
void OpNewClass::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNewClass @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(classIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNewClass has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetDescendants
void OpGetDescendants::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetDescendants @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetDescendants has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNewCatch
void OpNewCatch::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNewCatch @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(exceptionIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNewCatch has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpFindPropStrict
void OpFindPropStrict::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpFindPropStrict @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpFindPropStrict has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpFindProperty
void OpFindProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpFindProperty @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpFindProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpFindDef
void OpFindDef::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpFindDef @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpFindDef has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetLex
void OpGetLex::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetLex @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetLex has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetProperty
void OpSetProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetProperty @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetLocal
void OpGetLocal::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetLocal @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(address);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetLocal has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetLocal
void OpSetLocal::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetLocal @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(address);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetLocal has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetGlobalScope
void OpGetGlobalScope::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetGlobalScope @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetGlobalScope has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetScopeObject
void OpGetScopeObject::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetScopeObject @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(scopeIndex);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetScopeObject has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetProperty
void OpGetProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetProperty @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpInitProperty
void OpInitProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpInitProperty @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpInitProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDeleteProperty
void OpDeleteProperty::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDeleteProperty @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDeleteProperty has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetSlot
void OpGetSlot::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetSlot @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetSlot has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetSlot
void OpSetSlot::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetSlot @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetSlot has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetGlobalSlot
void OpGetGlobalSlot::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetGlobalSlot @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetGlobalSlot has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetGlobalSlot
void OpSetGlobalSlot::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetGlobalSlot @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(slotID);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetGlobalSlot has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConvertS
void OpConvertS::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConvertS @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConvertS has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpEscXelem
void OpEscXelem::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpEscXelem @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpEscXelem has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpEscXattr
void OpEscXattr::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpEscXattr @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpEscXattr has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConvertI
void OpConvertI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConvertI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConvertI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConvertU
void OpConvertU::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConvertU @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConvertU has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConvertD
void OpConvertD::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConvertD @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConvertD has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConvertB
void OpConvertB::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConvertB @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConvertB has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpConvertO
void OpConvertO::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpConvertO @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpConvertO has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCheckFilter
void OpCheckFilter::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCheckFilter @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCheckFilter has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerce
void OpCoerce::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerce @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerce has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerceB
void OpCoerceB::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerceB @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerceB has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerceA
void OpCoerceA::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerceA @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerceA has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerceI
void OpCoerceI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerceI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerceI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerceD
void OpCoerceD::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerceD @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerceD has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerceS
void OpCoerceS::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerceS @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerceS has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpAsType
void OpAsType::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpAsType @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpAsType has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpAsTypeLate
void OpAsTypeLate::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpAsTypeLate @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpAsTypeLate has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerceU
void OpCoerceU::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerceU @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerceU has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpCoerceO
void OpCoerceO::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpCoerceO @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpCoerceO has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNegate
void OpNegate::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNegate @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNegate has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIncrement
void OpIncrement::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIncrement @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIncrement has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIncLocal
void OpIncLocal::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIncLocal @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(address);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIncLocal has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDecrement
void OpDecrement::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDecrement @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDecrement has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDecLocal
void OpDecLocal::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDecLocal @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(address);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDecLocal has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpTypeOf
void OpTypeOf::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpTypeOf @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpTypeOf has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNot
void OpNot::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNot @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNot has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpBitNot
void OpBitNot::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpBitNot @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpBitNot has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpAdd
void OpAdd::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpAdd @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpAdd has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSubtract
void OpSubtract::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSubtract @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSubtract has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpMultiply
void OpMultiply::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpMultiply @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpMultiply has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDivide
void OpDivide::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDivide @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDivide has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpModulo
void OpModulo::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpModulo @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpModulo has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpLShift
void OpLShift::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpLShift @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpLShift has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpRShift
void OpRShift::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpRShift @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpRShift has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpURShift
void OpURShift::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpURShift @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpURShift has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpBitAnd
void OpBitAnd::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpBitAnd @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpBitAnd has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpBitOr
void OpBitOr::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpBitOr @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpBitOr has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpBitXor
void OpBitXor::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpBitXor @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpBitXor has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpEquals
void OpEquals::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpEquals @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpEquals has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpStrictEquals
void OpStrictEquals::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpStrictEquals @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpStrictEquals has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpLessThan
void OpLessThan::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpLessThan @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpLessThan has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpLessEquals
void OpLessEquals::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpLessEquals @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpLessEquals has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGreaterThan
void OpGreaterThan::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGreaterThan @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGreaterThan has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGreaterEquals
void OpGreaterEquals::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGreaterEquals @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGreaterEquals has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpInstanceOf
void OpInstanceOf::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpInstanceOf @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpInstanceOf has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIsType
void OpIsType::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIsType @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(name);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIsType has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIsTypeLate
void OpIsTypeLate::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIsTypeLate @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIsTypeLate has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIn
void OpIn::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIn @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIn has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIncrementI
void OpIncrementI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIncrementI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIncrementI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDecrementI
void OpDecrementI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDecrementI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDecrementI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpIncLocalI
void OpIncLocalI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpIncLocalI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(address);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpIncLocalI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDecLocalI
void OpDecLocalI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDecLocalI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(address);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDecLocalI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpNegateI
void OpNegateI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpNegateI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpNegateI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpAddI
void OpAddI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpAddI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpAddI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSubtractI
void OpSubtractI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSubtractI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSubtractI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpMultiplyI
void OpMultiplyI::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpMultiplyI @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpMultiplyI has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetLocal0
void OpGetLocal0::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetLocal0 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetLocal0 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetLocal1
void OpGetLocal1::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetLocal1 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetLocal1 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetLocal2
void OpGetLocal2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetLocal2 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetLocal2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpGetLocal3
void OpGetLocal3::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpGetLocal3 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpGetLocal3 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetLocal0
void OpSetLocal0::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetLocal0 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetLocal0 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetLocal1
void OpSetLocal1::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetLocal1 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetLocal1 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetLocal2
void OpSetLocal2::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetLocal2 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetLocal2 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpSetLocal3
void OpSetLocal3::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpSetLocal3 @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpSetLocal3 has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDebugReg
void OpDebugReg::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDebugReg @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putByte(unknown);
	w->putU30(name);
	w->putU30(reg);
	w->putU30(line);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDebugReg has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDebugLine
void OpDebugLine::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDebugLine @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(line);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDebugLine has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpDebugFile
void OpDebugFile::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpDebugFile @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(file);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpDebugFile has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpBkPtLine
void OpBkPtLine::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpBkPtLine @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
		w->putU30(line);
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpBkPtLine has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
//////////////////////////////////// OpTimestamp
void OpTimestamp::write( Writer *w, Context *ctx ) {
	int start=w->getBitPosition();
	if( ctx->debugTrace ) {
		//printf("WRITE OpTimestamp @%i\n", start/8 );
		dump(1,ctx);
	}
OpCode::writeHeader( w, ctx, (getSize(ctx,w->getBitPosition())/8)  );
	unsigned int l = w->getBitPosition()-start;
	if( l != getSize(ctx,start)) {
		//printf("WARNING: OpTimestamp has different size than expected: %i bits instead of %i\n", l, getSize(ctx,start) );
	}
}
}
