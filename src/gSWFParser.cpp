#include "SWF.h"
#include "SWFItem.h"
#include "SWFList.h"
namespace SWF {
//////////////////////////////////// Rectangle
bool Rectangle::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Rectangle @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	bits = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bits: %i\n", bits );
	left = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE left: %i\n", left );
	right = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE right: %i\n", right );
	top = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE top: %i\n", top );
	bottom = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bottom: %i\n", bottom );
	r->byteAlign();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Color
bool Color::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Color @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	red = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE red: %i\n", red );
	green = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE green: %i\n", green );
	blue = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blue: %i\n", blue );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->alpha - " );
	if( ctx->alpha ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		alpha = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE alpha: %i\n", alpha );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
		alpha =  0;
	}
	r->byteAlign();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// String
bool String::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE String @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %s\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// String2
bool String2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE String2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getPStringU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %s\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Transform
bool Transform::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Transform @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	scaled = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE scaled: %i\n", scaled );
	if( scaled ) {
		bitsScale = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bitsScale: %i\n", bitsScale );
	scaleX = r->getNBitFixed(bitsScale,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE scaleX: %G\n", scaleX );
	scaleY = r->getNBitFixed(bitsScale,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE scaleY: %G\n", scaleY );
	} else {
		scaleX =  1;
		scaleY =  1;
	}
skewed = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE skewed: %i\n", skewed );
	if( skewed ) {
		bitsSkew = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bitsSkew: %i\n", bitsSkew );
	skewX = r->getNBitFixed(bitsSkew,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE skewX: %G\n", skewX );
	skewY = r->getNBitFixed(bitsSkew,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE skewY: %G\n", skewY );
	} else {
		skewX =  1;
		skewY =  1;
	}
bitsTranslate = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bitsTranslate: %i\n", bitsTranslate );
	transX = r->getNBitInt(bitsTranslate,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE transX: %i\n", transX );
	transY = r->getNBitInt(bitsTranslate,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE transY: %i\n", transY );
	r->byteAlign();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ColorTransform2
bool ColorTransform2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ColorTransform2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	hasOffset = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasOffset: %i\n", hasOffset );
	hasFactor = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFactor: %i\n", hasFactor );
	bits = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bits: %i\n", bits );
	if( hasFactor ) {
		factorRed = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE factorRed: %i\n", factorRed );
	factorGreen = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE factorGreen: %i\n", factorGreen );
	factorBlue = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE factorBlue: %i\n", factorBlue );
	factorAlpha = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE factorAlpha: %i\n", factorAlpha );
	} else {
		factorRed =  1;
		factorGreen =  1;
		factorBlue =  1;
		factorAlpha =  1;
	}
	if( hasOffset ) {
		offsetRed = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE offsetRed: %i\n", offsetRed );
	offsetGreen = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE offsetGreen: %i\n", offsetGreen );
	offsetBlue = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE offsetBlue: %i\n", offsetBlue );
	offsetAlpha = r->getNBitInt(bits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE offsetAlpha: %i\n", offsetAlpha );
	} else {
		offsetRed =  1;
		offsetGreen =  1;
		offsetBlue =  1;
		offsetAlpha =  1;
	}
	r->byteAlign();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Header
bool Header::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Header @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	size.parse(r,end,ctx);
framerate = r->getNBitInt(16);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE framerate: %i\n", framerate );
	frames = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frames: %i\n", frames );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Tag> tags @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Tag *item;
			item = Tag::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				tags.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Tag::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// LineStyle
bool LineStyle::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE LineStyle @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	width = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE width: %i\n", width );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion < 4 - " );
	if( ctx->tagVersion < 4 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		color.parse(r,end,ctx);
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion > 3 - " );
	if( ctx->tagVersion > 3 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		startCapStyle = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE startCapStyle: %i\n", startCapStyle );
	jointStyle = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE jointStyle: %i\n", jointStyle );
	hasFill = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFill: %i\n", hasFill );
	noHScale = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE noHScale: %i\n", noHScale );
	noVScale = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE noVScale: %i\n", noVScale );
	pixelHinting = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pixelHinting: %i\n", pixelHinting );
	reserved = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	noClose = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE noClose: %i\n", noClose );
	endCapStyle = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE endCapStyle: %i\n", endCapStyle );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF jointStyle==2 - " );
	if( jointStyle==2 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		miterLimitFactor = r->getNBitFixed2(16,8,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE miterLimitFactor: %G\n", miterLimitFactor );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF hasFill - " );
	if( hasFill ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Style> fillStyles: %i items, @%i-%i :%i\n",  1, r->getPosition(), r->getBits(), end );
		Style *item;
		for( int i=0; i<1; i++ ) {
			item = Style::get(r,end,ctx);
			fillStyles.append( item );
		}
	}
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF !hasFill - " );
	if( !hasFill ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		fillColor.parse(r,end,ctx);
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StyleList
bool StyleList::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StyleList @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	n_fillStyles = r->getByte();
    if( n_fillStyles == 0xff && ctx->tagVersion >= 2 ) {
        n_fillStyles = r->getWord();
    }
	if( ctx->debugTrace ) fprintf( stderr, "PARSE n_fillStyles: %i\n", n_fillStyles );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Style> fillStyles: %i items, @%i-%i :%i\n",  n_fillStyles, r->getPosition(), r->getBits(), end );
		Style *item;
		for( int i=0; i<n_fillStyles; i++ ) {
			item = Style::get(r,end,ctx);
			fillStyles.append( item );
		}
	}
n_lineStyles = r->getByte();
    if( n_lineStyles == 0xff && ctx->tagVersion >= 2 ) {
        n_lineStyles = r->getWord();
    }
	if( ctx->debugTrace ) fprintf( stderr, "PARSE n_lineStyles: %i\n", n_lineStyles );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<LineStyle> lineStyles: %i items, @%i-%i :%i\n",  n_lineStyles, r->getPosition(), r->getBits(), end );
		LineStyle *item;
		for( int i=0; i<n_lineStyles; i++ ) {
			item = LineStyle::get(r,end,ctx);
			lineStyles.append( item );
		}
	}
fillBits = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fillBits: %i\n", fillBits );
		ctx->fillBits = fillBits;
	lineBits = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE lineBits: %i\n", lineBits );
		ctx->lineBits = lineBits;
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ShapeSetup
bool ShapeSetup::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ShapeSetup @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	hasNewStyles = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasNewStyles: %i\n", hasNewStyles );
	hasLineStyle = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasLineStyle: %i\n", hasLineStyle );
	hasFillStyle1 = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFillStyle1: %i\n", hasFillStyle1 );
	hasFillStyle0 = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFillStyle0: %i\n", hasFillStyle0 );
	hasMoveTo = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveTo: %i\n", hasMoveTo );
	if( hasMoveTo ) {
		xybits = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE xybits: %i\n", xybits );
	x = r->getNBitInt(xybits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE x: %i\n", x );
	y = r->getNBitInt(xybits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE y: %i\n", y );
	} else {
		x =  0;
		y =  0;
	}
	if( hasFillStyle0 ) {
		fillStyle0 = r->getNBitInt(ctx->fillBits);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fillStyle0: %i\n", fillStyle0 );
	} else {
		fillStyle0 =  0;
	}
	if( hasFillStyle1 ) {
		fillStyle1 = r->getNBitInt(ctx->fillBits);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fillStyle1: %i\n", fillStyle1 );
	} else {
		fillStyle1 =  0;
	}
	if( hasLineStyle ) {
		lineStyle = r->getNBitInt(ctx->lineBits);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE lineStyle: %i\n", lineStyle );
	} else {
		lineStyle =  0;
	}
	if( hasNewStyles ) {
	r->byteAlign();
styles.parse(r,end,ctx);
	} else {
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// CurveTo
bool CurveTo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE CurveTo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	bits = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bits: %i\n", bits );
	x1 = r->getNBitInt(bits+2,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE x1: %i\n", x1 );
	y1 = r->getNBitInt(bits+2,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE y1: %i\n", y1 );
	x2 = r->getNBitInt(bits+2,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE x2: %i\n", x2 );
	y2 = r->getNBitInt(bits+2,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE y2: %i\n", y2 );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Shape
bool Shape::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Shape @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<ShapeItem> edges @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			ShapeItem *item;
			item = ShapeItem::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				edges.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = ShapeItem::get(r,myend,ctx);
				else item = NULL;
					if(item && item->isEnd()) {
						edges.append( item );
						item = NULL;
					}
			}
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GlyphShape
bool GlyphShape::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GlyphShape @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->fillBits = 1;
	ctx->lineBits = 0;
fillBits = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fillBits: %i\n", fillBits );
	lineBits = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE lineBits: %i\n", lineBits );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<ShapeItem> edges @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			ShapeItem *item;
			item = ShapeItem::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				edges.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = ShapeItem::get(r,myend,ctx);
				else item = NULL;
					if(item && item->isEnd()) {
						edges.append( item );
						item = NULL;
					}
			}
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GradientItem
bool GradientItem::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GradientItem @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	position = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE position: %i\n", position );
	color.parse(r,end,ctx);
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Symbol
bool Symbol::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Symbol @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Frame
bool Frame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Frame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	number = r->getEncodedU32();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE number: %i\n", number );
	label = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE label: %s\n", label );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Scene
bool Scene::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Scene @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	offset = r->getEncodedU32();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE offset: %i\n", offset );
	name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Parameter
bool Parameter::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Parameter @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reg = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reg: %i\n", reg );
	name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// UChar
bool UChar::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE UChar @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// UShort
bool UShort::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE UShort @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ULong
bool ULong::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ULong @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getNBitInt(32);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Short
bool Short::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Short @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Float
bool Float::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Float @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getFloat();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %g\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Double
bool Double::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Double @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getDouble2();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %g\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Kerning
bool Kerning::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Kerning @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	a = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE a: %i\n", a );
	b = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE b: %i\n", b );
	adjustment = r->getNBitInt(16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE adjustment: %i\n", adjustment );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// WideKerning
bool WideKerning::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE WideKerning @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	a = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE a: %i\n", a );
	b = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE b: %i\n", b );
	adjustment = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE adjustment: %i\n", adjustment );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextEntry
bool TextEntry::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextEntry @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	glyph = r->getNBitInt(ctx->glyphBits);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE glyph: %i\n", glyph );
	advance = r->getNBitInt(ctx->advanceBits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE advance: %i\n", advance );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextEntry2
bool TextEntry2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextEntry2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	glyph = r->getNBitInt(ctx->glyphBits);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE glyph: %i\n", glyph );
	advance = r->getNBitInt(ctx->advanceBits,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE advance: %i\n", advance );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextRecord6
bool TextRecord6::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextRecord6 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	isSetup = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isSetup: %i\n", isSetup );
	if( isSetup ) {
		reserved = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	hasFont = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFont: %i\n", hasFont );
	hasColor = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasColor: %i\n", hasColor );
	hasMoveY = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveY: %i\n", hasMoveY );
	hasMoveX = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveX: %i\n", hasMoveX );
	if( hasFont ) {
		objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	} else {
	}
	if( hasColor ) {
		color.parse(r,end,ctx);
	} else {
	}
	if( hasMoveX ) {
		x = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE x: %i\n", x );
	} else {
	}
	if( hasMoveY ) {
		y = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE y: %i\n", y );
	} else {
	}
	if( hasFont ) {
		fontHeight = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fontHeight: %i\n", fontHeight );
	} else {
	}
	} else {
	}
	if( !isSetup ) {
		nGlyphs = r->getNBitInt(7);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nGlyphs: %i\n", nGlyphs );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextEntry> glyphs: %i items, @%i-%i :%i\n",  nGlyphs, r->getPosition(), r->getBits(), end );
		TextEntry *item;
		for( int i=0; i<nGlyphs; i++ ) {
			item = TextEntry::get(r,end,ctx);
			glyphs.append( item );
		}
	}
	r->byteAlign();
	} else {
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextRecord62
bool TextRecord62::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextRecord62 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	isSetup = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isSetup: %i\n", isSetup );
	if( isSetup ) {
		reserved = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	hasFont = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFont: %i\n", hasFont );
	hasColor = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasColor: %i\n", hasColor );
	hasMoveY = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveY: %i\n", hasMoveY );
	hasMoveX = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveX: %i\n", hasMoveX );
	if( hasFont ) {
		objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	} else {
	}
	if( hasColor ) {
		color.parse(r,end,ctx);
	} else {
	}
	if( hasMoveX ) {
		x = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE x: %i\n", x );
	} else {
	}
	if( hasMoveY ) {
		y = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE y: %i\n", y );
	} else {
	}
	if( hasFont ) {
		fontHeight = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fontHeight: %i\n", fontHeight );
	} else {
	}
	} else {
	}
	if( !isSetup ) {
		nGlyphs = r->getNBitInt(7);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nGlyphs: %i\n", nGlyphs );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextEntry2> glyphs: %i items, @%i-%i :%i\n",  nGlyphs, r->getPosition(), r->getBits(), end );
		TextEntry2 *item;
		for( int i=0; i<nGlyphs; i++ ) {
			item = TextEntry2::get(r,end,ctx);
			glyphs.append( item );
		}
	}
	r->byteAlign();
	} else {
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextRecord7
bool TextRecord7::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextRecord7 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	isSetup = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isSetup: %i\n", isSetup );
	reserved = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	hasFont = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFont: %i\n", hasFont );
	hasColor = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasColor: %i\n", hasColor );
	hasMoveY = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveY: %i\n", hasMoveY );
	hasMoveX = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveX: %i\n", hasMoveX );
	if( hasFont ) {
		objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	} else {
	}
	if( hasColor ) {
		color.parse(r,end,ctx);
	} else {
	}
	if( hasMoveX ) {
		x = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE x: %i\n", x );
	} else {
	}
	if( hasMoveY ) {
		y = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE y: %i\n", y );
	} else {
	}
	if( hasFont ) {
		fontHeight = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fontHeight: %i\n", fontHeight );
	} else {
	}
	if( isSetup ) {
		nGlyphs = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nGlyphs: %i\n", nGlyphs );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextEntry> glyphs: %i items, @%i-%i :%i\n",  nGlyphs, r->getPosition(), r->getBits(), end );
		TextEntry *item;
		for( int i=0; i<nGlyphs; i++ ) {
			item = TextEntry::get(r,end,ctx);
			glyphs.append( item );
		}
	}
	} else {
	}
	r->byteAlign();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextRecord72
bool TextRecord72::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextRecord72 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
isSetup = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isSetup: %i\n", isSetup );
	reserved = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	hasFont = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFont: %i\n", hasFont );
	hasColor = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasColor: %i\n", hasColor );
	hasMoveY = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveY: %i\n", hasMoveY );
	hasMoveX = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMoveX: %i\n", hasMoveX );
	if( hasFont ) {
		fontRef = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fontRef: %i\n", fontRef );
	} else {
	}
	if( hasColor ) {
		color.parse(r,end,ctx);
	} else {
	}
	if( hasMoveX ) {
		x = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE x: %i\n", x );
	} else {
	}
	if( hasMoveY ) {
		y = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE y: %i\n", y );
	} else {
	}
	if( hasFont ) {
		fontHeight = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fontHeight: %i\n", fontHeight );
	} else {
	}
	if( isSetup ) {
		nGlyphs = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nGlyphs: %i\n", nGlyphs );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextEntry2> glyphs: %i items, @%i-%i :%i\n",  nGlyphs, r->getPosition(), r->getBits(), end );
		TextEntry2 *item;
		for( int i=0; i<nGlyphs; i++ ) {
			item = TextEntry2::get(r,end,ctx);
			glyphs.append( item );
		}
	}
	} else {
	}
	r->byteAlign();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextRecord
bool TextRecord::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextRecord @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion < 2 - " );
	if( ctx->tagVersion < 2 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextRecord6> records @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			TextRecord6 *item;
			item = TextRecord6::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				records.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = TextRecord6::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion >= 2 - " );
	if( ctx->tagVersion >= 2 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		string.parse(r,end,ctx);
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TextRecord2
bool TextRecord2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TextRecord2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion < 7 - " );
	if( ctx->swfVersion < 7 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextRecord62> records @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			TextRecord62 *item;
			item = TextRecord62::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				records.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = TextRecord62::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion >= 7 - " );
	if( ctx->swfVersion >= 7 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		textString.parse(r,end,ctx);
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Button
bool Button::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Button @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reserved1 = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved1: %i\n", reserved1 );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion < 8 - " );
	if( ctx->swfVersion < 8 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		reserved2 = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved2: %i\n", reserved2 );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion >= 8 - " );
	if( ctx->swfVersion >= 8 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		hasBlendMode = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasBlendMode: %i\n", hasBlendMode );
	hasFilterList = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFilterList: %i\n", hasFilterList );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
hitTest = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hitTest: %i\n", hitTest );
	down = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE down: %i\n", down );
	over = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE over: %i\n", over );
	up = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE up: %i\n", up );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF hitTest || down || over || up - " );
	if( hitTest || down || over || up ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	depth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE depth: %i\n", depth );
	transform.parse(r,end,ctx);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion >= 2 - " );
	if( ctx->tagVersion >= 2 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		colorTransform.parse(r,end,ctx);
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( hasFilterList ) {
		numFilters = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE numFilters: %i\n", numFilters );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Filter> filters: %i items, @%i-%i :%i\n",  numFilters, r->getPosition(), r->getBits(), end );
		Filter *item;
		for( int i=0; i<numFilters; i++ ) {
			item = Filter::get(r,end,ctx);
			filters.append( item );
		}
	}
	} else {
	}
	if( hasBlendMode ) {
		blendMode = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blendMode: %i\n", blendMode );
	} else {
		blendMode =  0;
	}
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Event
bool Event::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Event @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	r->byteAlign();
flags1 = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE flags1: %i\n", flags1 );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion>=6 - " );
	if( ctx->swfVersion>=6 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		flags2 = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE flags2: %i\n", flags2 );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF (flags1 | flags2) - " );
	if( (flags1 | flags2) ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		actionLength = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE actionLength: %i\n", actionLength );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Action> actions @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
			myend = r->getPosition() + actionLength;
		if( r->getPosition() < myend ) {
			Action *item;
			item = Action::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				actions.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Action::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Condition
bool Condition::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Condition @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	next = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE next: %i\n", next );
		if( next && next+r->getPosition() < end ) {
			if( ctx->debugTrace ) fprintf(stderr, "- has next offset, setting end to current+%i\n", next );
			end = r->getPosition() + next + (-2);
		}
	menuEnter = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE menuEnter: %i\n", menuEnter );
	pointerReleaseOutside = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pointerReleaseOutside: %i\n", pointerReleaseOutside );
	pointerDragEnter = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pointerDragEnter: %i\n", pointerDragEnter );
	pointerDragLeave = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pointerDragLeave: %i\n", pointerDragLeave );
	pointerReleaseInside = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pointerReleaseInside: %i\n", pointerReleaseInside );
	pointerPush = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pointerPush: %i\n", pointerPush );
	pointerLeave = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pointerLeave: %i\n", pointerLeave );
	pointerEnter = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE pointerEnter: %i\n", pointerEnter );
	key = r->getNBitInt(7);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE key: %i\n", key );
	menuLeave = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE menuLeave: %i\n", menuLeave );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Action> actions @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Action *item;
			item = Action::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				actions.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Action::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// U30
bool U30::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE U30 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// S24
bool S24::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE S24 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ValueKind
bool ValueKind::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ValueKind @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	kind = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE kind: %i\n", kind );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MethodInfo
bool MethodInfo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MethodInfo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	paramCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE paramCount: %i\n", paramCount );
	retType = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE retType: %i\n", retType );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> paramTypes: %i items, @%i-%i :%i\n",  paramCount, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<paramCount; i++ ) {
			item = U30::get(r,end,ctx);
			paramTypes.append( item );
		}
	}
nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	hasParamNames = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasParamNames: %i\n", hasParamNames );
	setSDXNs = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE setSDXNs: %i\n", setSDXNs );
	isExplicit = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isExplicit: %i\n", isExplicit );
	ignoreRest = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ignoreRest: %i\n", ignoreRest );
	hasOptional = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasOptional: %i\n", hasOptional );
	needRest = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE needRest: %i\n", needRest );
	needActivation = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE needActivation: %i\n", needActivation );
	needArguments = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE needArguments: %i\n", needArguments );
	if( hasOptional ) {
		optionalCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE optionalCount: %i\n", optionalCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<ValueKind> optional: %i items, @%i-%i :%i\n",  optionalCount, r->getPosition(), r->getBits(), end );
		ValueKind *item;
		for( unsigned int i=0; i<optionalCount; i++ ) {
			item = ValueKind::get(r,end,ctx);
			optional.append( item );
		}
	}
	} else {
	}
	if( hasParamNames ) {
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> paramNames: %i items, @%i-%i :%i\n",  paramCount, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<paramCount; i++ ) {
			item = U30::get(r,end,ctx);
			paramNames.append( item );
		}
	}
	} else {
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MetadataInfo
bool MetadataInfo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MetadataInfo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	valuesCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE valuesCount: %i\n", valuesCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> keys: %i items, @%i-%i :%i\n",  valuesCount, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<valuesCount; i++ ) {
			item = U30::get(r,end,ctx);
			keys.append( item );
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> values: %i items, @%i-%i :%i\n",  valuesCount, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<valuesCount; i++ ) {
			item = U30::get(r,end,ctx);
			values.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// NamespaceSet
bool NamespaceSet::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE NamespaceSet @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	count = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> namespaces: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<count; i++ ) {
			item = U30::get(r,end,ctx);
			namespaces.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TraitInfo
bool TraitInfo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TraitInfo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	reserved = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	hasMetadata = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMetadata: %i\n", hasMetadata );
	override = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE override: %i\n", override );
	final = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE final: %i\n", final );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Trait> trait: %i items, @%i-%i :%i\n",  1, r->getPosition(), r->getBits(), end );
		Trait *item;
		for( unsigned int i=0; i<1; i++ ) {
			item = Trait::get(r,end,ctx);
			trait.append( item );
		}
	}
	if( hasMetadata ) {
		metadataCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE metadataCount: %i\n", metadataCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> metadata: %i items, @%i-%i :%i\n",  metadataCount, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<metadataCount; i++ ) {
			item = U30::get(r,end,ctx);
			metadata.append( item );
		}
	}
	} else {
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// InstanceInfo
bool InstanceInfo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE InstanceInfo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	superIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE superIndex: %i\n", superIndex );
	reserved = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	hasProtectedNS = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasProtectedNS: %i\n", hasProtectedNS );
	interface = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE interface: %i\n", interface );
	final = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE final: %i\n", final );
	sealed = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE sealed: %i\n", sealed );
	if( hasProtectedNS ) {
		protectedNS = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE protectedNS: %i\n", protectedNS );
	} else {
	}
interfaceCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE interfaceCount: %i\n", interfaceCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> interfaces: %i items, @%i-%i :%i\n",  interfaceCount, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<interfaceCount; i++ ) {
			item = U30::get(r,end,ctx);
			interfaces.append( item );
		}
	}
iInitIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE iInitIndex: %i\n", iInitIndex );
	traitCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE traitCount: %i\n", traitCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TraitInfo> traits: %i items, @%i-%i :%i\n",  traitCount, r->getPosition(), r->getBits(), end );
		TraitInfo *item;
		for( unsigned int i=0; i<traitCount; i++ ) {
			item = TraitInfo::get(r,end,ctx);
			traits.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ClassInfo
bool ClassInfo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ClassInfo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	cInitIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE cInitIndex: %i\n", cInitIndex );
	traitCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE traitCount: %i\n", traitCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TraitInfo> traits: %i items, @%i-%i :%i\n",  traitCount, r->getPosition(), r->getBits(), end );
		TraitInfo *item;
		for( unsigned int i=0; i<traitCount; i++ ) {
			item = TraitInfo::get(r,end,ctx);
			traits.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ScriptInfo
bool ScriptInfo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ScriptInfo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	initIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE initIndex: %i\n", initIndex );
	traitCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE traitCount: %i\n", traitCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TraitInfo> traits: %i items, @%i-%i :%i\n",  traitCount, r->getPosition(), r->getBits(), end );
		TraitInfo *item;
		for( unsigned int i=0; i<traitCount; i++ ) {
			item = TraitInfo::get(r,end,ctx);
			traits.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Exception
bool Exception::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Exception @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	tryStart = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE tryStart: %i\n", tryStart );
	tryEnd = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE tryEnd: %i\n", tryEnd );
	target = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	type = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE type: %i\n", type );
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MethodBody
bool MethodBody::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MethodBody @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	methodInfo = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodInfo: %i\n", methodInfo );
	maxStack = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE maxStack: %i\n", maxStack );
	maxRegs = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE maxRegs: %i\n", maxRegs );
	scopeDepth = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE scopeDepth: %i\n", scopeDepth );
	maxScope = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE maxScope: %i\n", maxScope );
	codeLength = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE codeLength: %i\n", codeLength );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<OpCode> code @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
			myend = r->getPosition() + codeLength;
		if( r->getPosition() < myend ) {
			OpCode *item;
			item = OpCode::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				code.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = OpCode::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
exceptionCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE exceptionCount: %i\n", exceptionCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Exception> exceptions: %i items, @%i-%i :%i\n",  exceptionCount, r->getPosition(), r->getBits(), end );
		Exception *item;
		for( unsigned int i=0; i<exceptionCount; i++ ) {
			item = Exception::get(r,end,ctx);
			exceptions.append( item );
		}
	}
traitCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE traitCount: %i\n", traitCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TraitInfo> traits: %i items, @%i-%i :%i\n",  traitCount, r->getPosition(), r->getBits(), end );
		TraitInfo *item;
		for( unsigned int i=0; i<traitCount; i++ ) {
			item = TraitInfo::get(r,end,ctx);
			traits.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Constants
bool Constants::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Constants @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	intCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE intCount: %i\n", intCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> ints: %i items, @%i-%i :%i\n",  
				( intCount < 1
				  ? 0
				  : intCount - 1 )
			, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<
				( intCount < 1
				  ? 0
				  : intCount - 1 )
			; i++ ) {
			item = U30::get(r,end,ctx);
			ints.append( item );
		}
	}
uintCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE uintCount: %i\n", uintCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<U30> uints: %i items, @%i-%i :%i\n",  
				( uintCount < 1
				  ? 0
				  : uintCount - 1 )
			, r->getPosition(), r->getBits(), end );
		U30 *item;
		for( unsigned int i=0; i<
				( uintCount < 1
				  ? 0
				  : uintCount - 1 )
			; i++ ) {
			item = U30::get(r,end,ctx);
			uints.append( item );
		}
	}
doubleCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE doubleCount: %i\n", doubleCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Double> doubles: %i items, @%i-%i :%i\n",  
				( doubleCount < 1
				  ? 0
				  : doubleCount - 1 )
			, r->getPosition(), r->getBits(), end );
		Double *item;
		for( unsigned int i=0; i<
				( doubleCount < 1
				  ? 0
				  : doubleCount - 1 )
			; i++ ) {
			item = Double::get(r,end,ctx);
			doubles.append( item );
		}
	}
stringCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE stringCount: %i\n", stringCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<String2> strings: %i items, @%i-%i :%i\n",  
				( stringCount < 1
				  ? 0
				  : stringCount - 1 )
			, r->getPosition(), r->getBits(), end );
		String2 *item;
		for( unsigned int i=0; i<
				( stringCount < 1
				  ? 0
				  : stringCount - 1 )
			; i++ ) {
			item = String2::get(r,end,ctx);
			strings.append( item );
		}
	}
namespaceConstantCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE namespaceConstantCount: %i\n", namespaceConstantCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<NamespaceConstant> namespaces: %i items, @%i-%i :%i\n",  
				( namespaceConstantCount < 1
				  ? 0
				  : namespaceConstantCount - 1 )
			, r->getPosition(), r->getBits(), end );
		NamespaceConstant *item;
		for( unsigned int i=0; i<
				( namespaceConstantCount < 1
				  ? 0
				  : namespaceConstantCount - 1 )
			; i++ ) {
			item = NamespaceConstant::get(r,end,ctx);
			namespaces.append( item );
		}
	}
namespaceSetCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE namespaceSetCount: %i\n", namespaceSetCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<NamespaceSet> namespaceSets: %i items, @%i-%i :%i\n",  
				( namespaceSetCount < 1
				  ? 0
				  : namespaceSetCount - 1 )
			, r->getPosition(), r->getBits(), end );
		NamespaceSet *item;
		for( unsigned int i=0; i<
				( namespaceSetCount < 1
				  ? 0
				  : namespaceSetCount - 1 )
			; i++ ) {
			item = NamespaceSet::get(r,end,ctx);
			namespaceSets.append( item );
		}
	}
multinameConstantCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE multinameConstantCount: %i\n", multinameConstantCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<MultinameConstant> multinames: %i items, @%i-%i :%i\n",  
				( multinameConstantCount < 1
				  ? 0
				  : multinameConstantCount - 1 )
			, r->getPosition(), r->getBits(), end );
		MultinameConstant *item;
		for( unsigned int i=0; i<
				( multinameConstantCount < 1
				  ? 0
				  : multinameConstantCount - 1 )
			; i++ ) {
			item = MultinameConstant::get(r,end,ctx);
			multinames.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Action3
bool Action3::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Action3 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	minorVersion = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE minorVersion: %i\n", minorVersion );
	majorVersion = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE majorVersion: %i\n", majorVersion );
	constants.parse(r,end,ctx);
methodInfoCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodInfoCount: %i\n", methodInfoCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<MethodInfo> methods: %i items, @%i-%i :%i\n",  methodInfoCount, r->getPosition(), r->getBits(), end );
		MethodInfo *item;
		for( unsigned int i=0; i<methodInfoCount; i++ ) {
			item = MethodInfo::get(r,end,ctx);
			methods.append( item );
		}
	}
metadataInfoCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE metadataInfoCount: %i\n", metadataInfoCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<MetadataInfo> metadata: %i items, @%i-%i :%i\n",  metadataInfoCount, r->getPosition(), r->getBits(), end );
		MetadataInfo *item;
		for( unsigned int i=0; i<metadataInfoCount; i++ ) {
			item = MetadataInfo::get(r,end,ctx);
			metadata.append( item );
		}
	}
classCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE classCount: %i\n", classCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<InstanceInfo> instances: %i items, @%i-%i :%i\n",  classCount, r->getPosition(), r->getBits(), end );
		InstanceInfo *item;
		for( unsigned int i=0; i<classCount; i++ ) {
			item = InstanceInfo::get(r,end,ctx);
			instances.append( item );
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<ClassInfo> classes: %i items, @%i-%i :%i\n",  classCount, r->getPosition(), r->getBits(), end );
		ClassInfo *item;
		for( unsigned int i=0; i<classCount; i++ ) {
			item = ClassInfo::get(r,end,ctx);
			classes.append( item );
		}
	}
scriptCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE scriptCount: %i\n", scriptCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<ScriptInfo> scripts: %i items, @%i-%i :%i\n",  scriptCount, r->getPosition(), r->getBits(), end );
		ScriptInfo *item;
		for( unsigned int i=0; i<scriptCount; i++ ) {
			item = ScriptInfo::get(r,end,ctx);
			scripts.append( item );
		}
	}
methodBodyCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodBodyCount: %i\n", methodBodyCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<MethodBody> methodBodies: %i items, @%i-%i :%i\n",  methodBodyCount, r->getPosition(), r->getBits(), end );
		MethodBody *item;
		for( unsigned int i=0; i<methodBodyCount; i++ ) {
			item = MethodBody::get(r,end,ctx);
			methodBodies.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ZoneData
bool ZoneData::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ZoneData @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	position = r->getHalf();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE position: %g\n", position );
	size = r->getHalf();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE size: %g\n", size );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ZoneArray
bool ZoneArray::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ZoneArray @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	count = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<ZoneData> zones: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		ZoneData *item;
		for( unsigned int i=0; i<count; i++ ) {
			item = ZoneData::get(r,end,ctx);
			zones.append( item );
		}
	}
zoneX = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE zoneX: %i\n", zoneX );
	zoneY = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE zoneY: %i\n", zoneY );
	reserved = r->getNBitInt(6);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// UnknownFilter
bool UnknownFilter::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE UnknownFilter @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		int sz = len;
		data = new unsigned char[ sz ];
		r->getData( data, sz );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DropShadow
bool DropShadow::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DropShadow @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
color.parse(r,end,ctx);
blurX = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurX: %G\n", blurX );
	blurY = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurY: %G\n", blurY );
	angle = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE angle: %G\n", angle );
	distance = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE distance: %G\n", distance );
	strength = r->getNBitFixed2(16,8,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE strength: %G\n", strength );
	innerShadow = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE innerShadow: %i\n", innerShadow );
	knockout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE knockout: %i\n", knockout );
	compositeSource = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE compositeSource: %i\n", compositeSource );
	passes = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE passes: %i\n", passes );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Blur
bool Blur::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Blur @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	blurX = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurX: %G\n", blurX );
	blurY = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurY: %G\n", blurY );
	passes = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE passes: %i\n", passes );
	reserved1 = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved1: %i\n", reserved1 );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Glow
bool Glow::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Glow @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
color.parse(r,end,ctx);
blurX = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurX: %G\n", blurX );
	blurY = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurY: %G\n", blurY );
	strength = r->getNBitFixed2(16,8,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE strength: %G\n", strength );
	innerGlow = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE innerGlow: %i\n", innerGlow );
	knockout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE knockout: %i\n", knockout );
	compositeSource = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE compositeSource: %i\n", compositeSource );
	passes = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE passes: %i\n", passes );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Bevel
bool Bevel::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Bevel @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
shadowColor.parse(r,end,ctx);
highlightColor.parse(r,end,ctx);
blurX = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurX: %G\n", blurX );
	blurY = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurY: %G\n", blurY );
	angle = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE angle: %G\n", angle );
	distance = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE distance: %G\n", distance );
	strength = r->getNBitFixed2(16,8,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE strength: %G\n", strength );
	innerShadow = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE innerShadow: %i\n", innerShadow );
	knockout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE knockout: %i\n", knockout );
	compositeSource = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE compositeSource: %i\n", compositeSource );
	onTop = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE onTop: %i\n", onTop );
	passes = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE passes: %i\n", passes );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GradientGlow
bool GradientGlow::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GradientGlow @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
numColors = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE numColors: %i\n", numColors );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Color> colors: %i items, @%i-%i :%i\n",  numColors, r->getPosition(), r->getBits(), end );
		Color *item;
		for( unsigned int i=0; i<numColors; i++ ) {
			item = Color::get(r,end,ctx);
			colors.append( item );
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<UChar> ratio: %i items, @%i-%i :%i\n",  numColors, r->getPosition(), r->getBits(), end );
		UChar *item;
		for( unsigned int i=0; i<numColors; i++ ) {
			item = UChar::get(r,end,ctx);
			ratio.append( item );
		}
	}
blurX = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurX: %G\n", blurX );
	blurY = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurY: %G\n", blurY );
	angle = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE angle: %G\n", angle );
	distance = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE distance: %G\n", distance );
	strength = r->getNBitFixed2(16,8,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE strength: %G\n", strength );
	innerGlow = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE innerGlow: %i\n", innerGlow );
	knockout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE knockout: %i\n", knockout );
	compositeSource = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE compositeSource: %i\n", compositeSource );
	onTop = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE onTop: %i\n", onTop );
	passes = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE passes: %i\n", passes );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Convolution
bool Convolution::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Convolution @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
matrixX = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE matrixX: %i\n", matrixX );
	matrixY = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE matrixY: %i\n", matrixY );
	divizor = r->getFloat();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE divizor: %g\n", divizor );
	bias = r->getFloat();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bias: %g\n", bias );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Float> matrix: %i items, @%i-%i :%i\n",  (matrixX * matrixY), r->getPosition(), r->getBits(), end );
		Float *item;
		for( unsigned int i=0; i<(matrixX * matrixY); i++ ) {
			item = Float::get(r,end,ctx);
			matrix.append( item );
		}
	}
defaultColor.parse(r,end,ctx);
reserved = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	clamp = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE clamp: %i\n", clamp );
	preserveAlpha = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE preserveAlpha: %i\n", preserveAlpha );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ColorMatrix
bool ColorMatrix::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ColorMatrix @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Float> matrix: %i items, @%i-%i :%i\n",  20, r->getPosition(), r->getBits(), end );
		Float *item;
		for( unsigned int i=0; i<20; i++ ) {
			item = Float::get(r,end,ctx);
			matrix.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GradientBevel
bool GradientBevel::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GradientBevel @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
numColors = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE numColors: %i\n", numColors );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Color> colors: %i items, @%i-%i :%i\n",  numColors, r->getPosition(), r->getBits(), end );
		Color *item;
		for( unsigned int i=0; i<numColors; i++ ) {
			item = Color::get(r,end,ctx);
			colors.append( item );
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<UChar> ratio: %i items, @%i-%i :%i\n",  numColors, r->getPosition(), r->getBits(), end );
		UChar *item;
		for( unsigned int i=0; i<numColors; i++ ) {
			item = UChar::get(r,end,ctx);
			ratio.append( item );
		}
	}
blurX = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurX: %G\n", blurX );
	blurY = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blurY: %G\n", blurY );
	angle = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE angle: %G\n", angle );
	distance = r->getNBitFixed2(32,16,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE distance: %G\n", distance );
	strength = r->getNBitFixed2(16,8,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE strength: %G\n", strength );
	innerGlow = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE innerGlow: %i\n", innerGlow );
	knockout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE knockout: %i\n", knockout );
	compositeSource = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE compositeSource: %i\n", compositeSource );
	onTop = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE onTop: %i\n", onTop );
	passes = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE passes: %i\n", passes );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Solid
bool Solid::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Solid @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	color.parse(r,end,ctx);
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// LinearGradient
bool LinearGradient::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE LinearGradient @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	matrix.parse(r,end,ctx);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion < 4 - " );
	if( ctx->tagVersion < 4 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		reserved = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion >= 4 - " );
	if( ctx->tagVersion >= 4 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		spreadMode = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE spreadMode: %i\n", spreadMode );
	interpolationMode = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE interpolationMode: %i\n", interpolationMode );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
count = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<GradientItem> gradientColors: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		GradientItem *item;
		for( int i=0; i<count; i++ ) {
			item = GradientItem::get(r,end,ctx);
			gradientColors.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RadialGradient
bool RadialGradient::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RadialGradient @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	matrix.parse(r,end,ctx);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion < 4 - " );
	if( ctx->tagVersion < 4 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		reserved = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion >= 4 - " );
	if( ctx->tagVersion >= 4 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		spreadMode = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE spreadMode: %i\n", spreadMode );
	interpolationMode = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE interpolationMode: %i\n", interpolationMode );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
count = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<GradientItem> gradientColors: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		GradientItem *item;
		for( int i=0; i<count; i++ ) {
			item = GradientItem::get(r,end,ctx);
			gradientColors.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ShiftedRadialGradient
bool ShiftedRadialGradient::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ShiftedRadialGradient @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	matrix.parse(r,end,ctx);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion < 4 - " );
	if( ctx->tagVersion < 4 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		reserved = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->tagVersion >= 4 - " );
	if( ctx->tagVersion >= 4 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		spreadMode = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE spreadMode: %i\n", spreadMode );
	interpolationMode = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE interpolationMode: %i\n", interpolationMode );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
count = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<GradientItem> gradientColors: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		GradientItem *item;
		for( int i=0; i<count; i++ ) {
			item = GradientItem::get(r,end,ctx);
			gradientColors.append( item );
		}
	}
shift = r->getNBitFixed2(16,8,true);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE shift: %G\n", shift );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TiledBitmap
bool TiledBitmap::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TiledBitmap @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	matrix.parse(r,end,ctx);
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ClippedBitmap
bool ClippedBitmap::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ClippedBitmap @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	matrix.parse(r,end,ctx);
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TiledBitmap2
bool TiledBitmap2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TiledBitmap2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	matrix.parse(r,end,ctx);
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ClippedBitmap2
bool ClippedBitmap2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ClippedBitmap2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	matrix.parse(r,end,ctx);
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// UnknownTag
bool UnknownTag::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE UnknownTag @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		int sz = len;
		data = new unsigned char[ sz ];
		r->getData( data, sz );
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag UnknownTag is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// End
bool End::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE End @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag End is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ShowFrame
bool ShowFrame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ShowFrame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag ShowFrame is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineShape
bool DefineShape::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineShape @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 0;
	ctx->many_shapes = 0;
	ctx->tagVersion = 1;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	bounds.parse(r,end,ctx);
styles.parse(r,end,ctx);
shapes.parse(r,end,ctx);
	r->byteAlign();
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineShape is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RemoveObject
bool RemoveObject::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RemoveObject @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	depth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE depth: %i\n", depth );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag RemoveObject is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineBits
bool DefineBits::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineBits @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineBits is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetBackgroundColor
bool SetBackgroundColor::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetBackgroundColor @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 0;
color.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag SetBackgroundColor is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineText
bool DefineText::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineText @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	bounds.parse(r,end,ctx);
transform.parse(r,end,ctx);
glyphBits = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE glyphBits: %i\n", glyphBits );
		ctx->glyphBits = glyphBits;
	advanceBits = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE advanceBits: %i\n", advanceBits );
		ctx->advanceBits = advanceBits;
	ctx->alpha = 0;
	ctx->tagVersion = 1;
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextRecord> records @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			TextRecord *item;
			item = TextRecord::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				records.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = TextRecord::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineText is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineText2
bool DefineText2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineText2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	bounds.parse(r,end,ctx);
transform.parse(r,end,ctx);
glyphBits = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE glyphBits: %i\n", glyphBits );
		ctx->glyphBits = glyphBits;
	advanceBits = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE advanceBits: %i\n", advanceBits );
		ctx->advanceBits = advanceBits;
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<TextRecord2> records @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			TextRecord2 *item;
			item = TextRecord2::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				records.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = TextRecord2::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineText2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DoAction
bool DoAction::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DoAction @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Action> actions @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Action *item;
			item = Action::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				actions.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Action::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DoAction is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineFontInfo
bool DefineFontInfo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineFontInfo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	nameLength = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameLength: %i\n", nameLength );
	{
		int sz = nameLength;
		nameData = new unsigned char[ sz ];
		r->getData( nameData, sz );
	}
reserved = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	smallTextOrUnicode = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE smallTextOrUnicode: %i\n", smallTextOrUnicode );
	isShiftJIS = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isShiftJIS: %i\n", isShiftJIS );
	isANSII = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isANSII: %i\n", isANSII );
	isItalic = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isItalic: %i\n", isItalic );
	isBold = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isBold: %i\n", isBold );
	isWide = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isWide: %i\n", isWide );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion>=6 - " );
	if( ctx->swfVersion>=6 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		language = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE language: %i\n", language );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
map.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineFontInfo is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineSound
bool DefineSound::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineSound @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	format = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE format: %i\n", format );
	rate = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE rate: %i\n", rate );
	is16bit = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE is16bit: %i\n", is16bit );
	stereo = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE stereo: %i\n", stereo );
	samples = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE samples: %i\n", samples );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineSound is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StartSound
bool StartSound::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StartSound @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	reserved = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	stopPlayback = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE stopPlayback: %i\n", stopPlayback );
	noMultiple = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE noMultiple: %i\n", noMultiple );
	hasEnvelope = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasEnvelope: %i\n", hasEnvelope );
	hasLoop = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasLoop: %i\n", hasLoop );
	hasOutPoint = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasOutPoint: %i\n", hasOutPoint );
	hasInPoint = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasInPoint: %i\n", hasInPoint );
	if( hasInPoint ) {
		inPoint = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE inPoint: %i\n", inPoint );
	} else {
	}
	if( hasOutPoint ) {
		outPoint = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE outPoint: %i\n", outPoint );
	} else {
	}
	if( hasLoop ) {
		loop = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE loop: %i\n", loop );
	} else {
	}
	if( hasEnvelope ) {
		envelopeCount = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE envelopeCount: %i\n", envelopeCount );
	envelopeData.parse(r,end,ctx);
	} else {
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag StartSound is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineShape2
bool DefineShape2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineShape2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 0;
	ctx->many_shapes = 1;
	ctx->tagVersion = 2;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	bounds.parse(r,end,ctx);
styles.parse(r,end,ctx);
shapes.parse(r,end,ctx);
	r->byteAlign();
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineShape2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineShape3
bool DefineShape3::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineShape3 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 3;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	bounds.parse(r,end,ctx);
styles.parse(r,end,ctx);
shapes.parse(r,end,ctx);
	r->byteAlign();
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineShape3 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineShape4
bool DefineShape4::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineShape4 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineShape4 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineShape5
bool DefineShape5::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineShape5 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
	ctx->many_shapes = 1;
	ctx->tagVersion = 5;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	bounds.parse(r,end,ctx);
strokeBounds.parse(r,end,ctx);
reserved = r->getNBitInt(6);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	nonScalingStrokes = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nonScalingStrokes: %i\n", nonScalingStrokes );
	scalingStrokes = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE scalingStrokes: %i\n", scalingStrokes );
	styles.parse(r,end,ctx);
shapes.parse(r,end,ctx);
	r->byteAlign();
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineShape5 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineMorphShape
bool DefineMorphShape::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineMorphShape @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineMorphShape is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineFontInfo2
bool DefineFontInfo2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineFontInfo2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	nameLength = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameLength: %i\n", nameLength );
	{
		int sz = nameLength;
		nameData = new unsigned char[ sz ];
		r->getData( nameData, sz );
	}
reserved = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	smallTextOrUnicode = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE smallTextOrUnicode: %i\n", smallTextOrUnicode );
	isShiftJIS = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isShiftJIS: %i\n", isShiftJIS );
	isANSII = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isANSII: %i\n", isANSII );
	isItalic = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isItalic: %i\n", isItalic );
	isBold = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isBold: %i\n", isBold );
	isWide = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isWide: %i\n", isWide );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion>=6 - " );
	if( ctx->swfVersion>=6 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		language = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE language: %i\n", language );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
map.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineFontInfo2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SoundStreamHead
bool SoundStreamHead::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SoundStreamHead @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reserved = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	playbackRate = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE playbackRate: %i\n", playbackRate );
	playbackSize = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE playbackSize: %i\n", playbackSize );
	playbackStereo = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE playbackStereo: %i\n", playbackStereo );
	compression = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE compression: %i\n", compression );
	soundRate = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE soundRate: %i\n", soundRate );
	soundSize = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE soundSize: %i\n", soundSize );
	soundStereo = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE soundStereo: %i\n", soundStereo );
	sampleSize = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE sampleSize: %i\n", sampleSize );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF compression==2 - " );
	if( compression==2 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		latencySeek.parse(r,end,ctx);
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag SoundStreamHead is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineBitsLossless
bool DefineBitsLossless::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineBitsLossless @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	format = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE format: %i\n", format );
	width = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE width: %i\n", width );
	height = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE height: %i\n", height );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF format==3 - " );
	if( format==3 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		n_colormap = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE n_colormap: %i\n", n_colormap );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineBitsLossless is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineBitsJPEG2
bool DefineBitsJPEG2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineBitsJPEG2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineBitsJPEG2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineBitsJPEG3
bool DefineBitsJPEG3::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineBitsJPEG3 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	offset_to_alpha = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE offset_to_alpha: %i\n", offset_to_alpha );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineBitsJPEG3 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineBitsLossless2
bool DefineBitsLossless2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineBitsLossless2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	format = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE format: %i\n", format );
	width = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE width: %i\n", width );
	height = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE height: %i\n", height );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF format==3 - " );
	if( format==3 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		n_colormap = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE n_colormap: %i\n", n_colormap );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineBitsLossless2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// PlaceObject2
bool PlaceObject2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE PlaceObject2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	hasEventHandler = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasEventHandler: %i\n", hasEventHandler );
	hasClipDepth = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasClipDepth: %i\n", hasClipDepth );
	hasName = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasName: %i\n", hasName );
	hasMorph = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMorph: %i\n", hasMorph );
	hasColorTransform = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasColorTransform: %i\n", hasColorTransform );
	hasTransform = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasTransform: %i\n", hasTransform );
	hasID = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasID: %i\n", hasID );
	replace = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE replace: %i\n", replace );
	depth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE depth: %i\n", depth );
	if( hasID ) {
		objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	} else {
		objectID =  0;
	}
	if( hasTransform ) {
		transform.parse(r,end,ctx);
	} else {
	}
	if( hasColorTransform ) {
		colorTransform.parse(r,end,ctx);
	} else {
	}
	if( hasMorph ) {
		morph = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE morph: %i\n", morph );
	} else {
	}
	if( hasName ) {
		name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	} else {
		name =  NULL;
	}
	if( hasClipDepth ) {
		clipDepth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE clipDepth: %i\n", clipDepth );
	} else {
		clipDepth =  0;
	}
	if( hasEventHandler ) {
		reserved = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	allflags1 = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE allflags1: %i\n", allflags1 );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion>=6 - " );
	if( ctx->swfVersion>=6 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		allflags2 = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE allflags2: %i\n", allflags2 );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Event> events @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Event *item;
			item = Event::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				events.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Event::get(r,myend,ctx);
				else item = NULL;
					if(item && !(item->getflags1() | item->getflags2())) {
						events.append( item );
						item = NULL;
					}
			}
		}
	}
	} else {
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag PlaceObject2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RemoveObject2
bool RemoveObject2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RemoveObject2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	depth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE depth: %i\n", depth );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag RemoveObject2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineEditText
bool DefineEditText::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineEditText @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->alpha = 1;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	size.parse(r,end,ctx);
hasText = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasText: %i\n", hasText );
	wordWrap = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE wordWrap: %i\n", wordWrap );
	multiLine = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE multiLine: %i\n", multiLine );
	password = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE password: %i\n", password );
	readOnly = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE readOnly: %i\n", readOnly );
	hasColor = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasColor: %i\n", hasColor );
	hasMaxLength = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMaxLength: %i\n", hasMaxLength );
	hasFont = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFont: %i\n", hasFont );
	reserved = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	autoSize = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE autoSize: %i\n", autoSize );
	hasLayout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasLayout: %i\n", hasLayout );
	notSelectable = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE notSelectable: %i\n", notSelectable );
	hasBorder = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasBorder: %i\n", hasBorder );
	reserved2 = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved2: %i\n", reserved2 );
	isHTML = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isHTML: %i\n", isHTML );
	useOutlines = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE useOutlines: %i\n", useOutlines );
	if( hasFont ) {
		fontRef = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fontRef: %i\n", fontRef );
	fontHeight = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE fontHeight: %i\n", fontHeight );
	} else {
	}
	if( hasColor ) {
		color.parse(r,end,ctx);
	} else {
	}
	if( hasMaxLength ) {
		maxLength = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE maxLength: %i\n", maxLength );
	} else {
	}
	if( hasLayout ) {
		align = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE align: %i\n", align );
	leftMargin = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE leftMargin: %i\n", leftMargin );
	rightMargin = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE rightMargin: %i\n", rightMargin );
	indent = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE indent: %i\n", indent );
	leading = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE leading: %i\n", leading );
	} else {
	}
variableName = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE variableName: %s\n", variableName );
	if( hasText ) {
		initialText = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE initialText: %s\n", initialText );
	} else {
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineEditText is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineSprite
bool DefineSprite::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineSprite @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	frames = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frames: %i\n", frames );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Tag> tags @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Tag *item;
			item = Tag::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				tags.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Tag::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineSprite is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// FrameLabel
bool FrameLabel::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE FrameLabel @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	label = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE label: %s\n", label );
	flags.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag FrameLabel is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SoundStreamHead2
bool SoundStreamHead2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SoundStreamHead2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reserved = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	playbackRate = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE playbackRate: %i\n", playbackRate );
	playbackSize = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE playbackSize: %i\n", playbackSize );
	playbackStereo = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE playbackStereo: %i\n", playbackStereo );
	compression = r->getNBitInt(4);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE compression: %i\n", compression );
	soundRate = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE soundRate: %i\n", soundRate );
	soundSize = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE soundSize: %i\n", soundSize );
	soundStereo = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE soundStereo: %i\n", soundStereo );
	sampleSize = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE sampleSize: %i\n", sampleSize );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF compression==2 - " );
	if( compression==2 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		latencySeek.parse(r,end,ctx);
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag SoundStreamHead2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineFont
bool DefineFont::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineFont @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->tagVersion = 1;
	ctx->wideGlyphOffsets = 0;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineFont is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineFont2
bool DefineFont2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineFont2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->tagVersion = 2;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	hasLayout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasLayout: %i\n", hasLayout );
	isShiftJIS = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isShiftJIS: %i\n", isShiftJIS );
	isUnicode = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isUnicode: %i\n", isUnicode );
	isANSII = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isANSII: %i\n", isANSII );
	wideGlyphOffsets = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE wideGlyphOffsets: %i\n", wideGlyphOffsets );
		ctx->wideGlyphOffsets = wideGlyphOffsets;
	wideMap = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE wideMap: %i\n", wideMap );
		ctx->wideMap = wideMap;
	italic = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE italic: %i\n", italic );
	bold = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bold: %i\n", bold );
	language = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE language: %i\n", language );
	name = r->getPString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	glyphCount = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE glyphCount: %i\n", glyphCount );
		ctx->glyphCount = glyphCount;
	glyphs.parse(r,end,ctx);
	if( hasLayout ) {
		ascent = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ascent: %i\n", ascent );
	descent = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE descent: %i\n", descent );
	leading = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE leading: %i\n", leading );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Short> advance: %i items, @%i-%i :%i\n",  glyphCount, r->getPosition(), r->getBits(), end );
		Short *item;
		for( unsigned int i=0; i<glyphCount; i++ ) {
			item = Short::get(r,end,ctx);
			advance.append( item );
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Rectangle> bounds: %i items, @%i-%i :%i\n",  glyphCount, r->getPosition(), r->getBits(), end );
		Rectangle *item;
		for( unsigned int i=0; i<glyphCount; i++ ) {
			item = Rectangle::get(r,end,ctx);
			bounds.append( item );
		}
	}
kerningCount = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE kerningCount: %i\n", kerningCount );
	if( wideMap ) {
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<WideKerning> wideKerning: %i items, @%i-%i :%i\n",  kerningCount, r->getPosition(), r->getBits(), end );
		WideKerning *item;
		for( unsigned int i=0; i<kerningCount; i++ ) {
			item = WideKerning::get(r,end,ctx);
			wideKerning.append( item );
		}
	}
	} else {
	}
	if( !wideMap ) {
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Kerning> kerning: %i items, @%i-%i :%i\n",  kerningCount, r->getPosition(), r->getBits(), end );
		Kerning *item;
		for( unsigned int i=0; i<kerningCount; i++ ) {
			item = Kerning::get(r,end,ctx);
			kerning.append( item );
		}
	}
	} else {
	}
	} else {
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineFont2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineFont3
bool DefineFont3::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineFont3 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->tagVersion = 2;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	hasLayout = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasLayout: %i\n", hasLayout );
	isShiftJIS = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isShiftJIS: %i\n", isShiftJIS );
	isUnicode = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isUnicode: %i\n", isUnicode );
	isANSII = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE isANSII: %i\n", isANSII );
	wideGlyphOffsets = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE wideGlyphOffsets: %i\n", wideGlyphOffsets );
		ctx->wideGlyphOffsets = wideGlyphOffsets;
	wideMap = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE wideMap: %i\n", wideMap );
		ctx->wideMap = wideMap;
	italic = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE italic: %i\n", italic );
	bold = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bold: %i\n", bold );
	language = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE language: %i\n", language );
	name = r->getPString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	glyphCount = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE glyphCount: %i\n", glyphCount );
		ctx->glyphCount = glyphCount;
	glyphs.parse(r,end,ctx);
	if( hasLayout ) {
		ascent = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ascent: %i\n", ascent );
	descent = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE descent: %i\n", descent );
	leading = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE leading: %i\n", leading );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Short> advance: %i items, @%i-%i :%i\n",  glyphCount, r->getPosition(), r->getBits(), end );
		Short *item;
		for( unsigned int i=0; i<glyphCount; i++ ) {
			item = Short::get(r,end,ctx);
			advance.append( item );
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Rectangle> bounds: %i items, @%i-%i :%i\n",  glyphCount, r->getPosition(), r->getBits(), end );
		Rectangle *item;
		for( unsigned int i=0; i<glyphCount; i++ ) {
			item = Rectangle::get(r,end,ctx);
			bounds.append( item );
		}
	}
kerningCount = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE kerningCount: %i\n", kerningCount );
	if( wideMap ) {
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<WideKerning> wideKerning: %i items, @%i-%i :%i\n",  kerningCount, r->getPosition(), r->getBits(), end );
		WideKerning *item;
		for( unsigned int i=0; i<kerningCount; i++ ) {
			item = WideKerning::get(r,end,ctx);
			wideKerning.append( item );
		}
	}
	} else {
	}
	if( !wideMap ) {
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Kerning> kerning: %i items, @%i-%i :%i\n",  kerningCount, r->getPosition(), r->getBits(), end );
		Kerning *item;
		for( unsigned int i=0; i<kerningCount; i++ ) {
			item = Kerning::get(r,end,ctx);
			kerning.append( item );
		}
	}
	} else {
	}
	} else {
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineFont3 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineButton
bool DefineButton::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineButton @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->tagVersion = 1;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Button> buttons @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Button *item;
			item = Button::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				buttons.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Button::get(r,myend,ctx);
				else item = NULL;
					if(item && !(item->gethitTest() || item->getdown() || item->getover() || item->getup())) {
						buttons.append( item );
						item = NULL;
					}
			}
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Action> actions @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Action *item;
			item = Action::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				actions.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Action::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineButton is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineButton2
bool DefineButton2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineButton2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	ctx->tagVersion = 2;
objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	reserved = r->getNBitInt(7);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	menu = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE menu: %i\n", menu );
	buttonsSize = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE buttonsSize: %i\n", buttonsSize );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Button> buttons @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Button *item;
			item = Button::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				buttons.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Button::get(r,myend,ctx);
				else item = NULL;
					if(item && !(item->gethitTest() || item->getdown() || item->getover() || item->getup())) {
						buttons.append( item );
						item = NULL;
					}
			}
		}
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Condition> conditions @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Condition *item;
			item = Condition::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				conditions.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Condition::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineButton2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Export
bool Export::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Export @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	count = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Symbol> symbols: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		Symbol *item;
		for( unsigned int i=0; i<count; i++ ) {
			item = Symbol::get(r,end,ctx);
			symbols.append( item );
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag Export is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Import
bool Import::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Import @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	url = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE url: %s\n", url );
	count = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Symbol> symbols: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		Symbol *item;
		for( unsigned int i=0; i<count; i++ ) {
			item = Symbol::get(r,end,ctx);
			symbols.append( item );
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag Import is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DoInitAction
bool DoInitAction::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DoInitAction @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	sprite = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE sprite: %i\n", sprite );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Action> actions @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Action *item;
			item = Action::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				actions.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Action::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DoInitAction is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SoundStreamBlock
bool SoundStreamBlock::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SoundStreamBlock @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		int sz = len;
		data = new unsigned char[ sz ];
		r->getData( data, sz );
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag SoundStreamBlock is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineVideoStream
bool DefineVideoStream::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineVideoStream @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	frames = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frames: %i\n", frames );
	width = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE width: %i\n", width );
	height = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE height: %i\n", height );
	reserved = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	deblocking = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE deblocking: %i\n", deblocking );
	smoothing = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE smoothing: %i\n", smoothing );
	codec = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE codec: %i\n", codec );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineVideoStream is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// VideoFrame
bool VideoFrame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE VideoFrame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	frame = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frame: %i\n", frame );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag VideoFrame is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ScriptLimits
bool ScriptLimits::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ScriptLimits @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	maxRecursionDepth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE maxRecursionDepth: %i\n", maxRecursionDepth );
	timeout = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE timeout: %i\n", timeout );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag ScriptLimits is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetTabIndex
bool SetTabIndex::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetTabIndex @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	depth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE depth: %i\n", depth );
	tabIndex = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE tabIndex: %i\n", tabIndex );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag SetTabIndex is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// PlaceObject3
bool PlaceObject3::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE PlaceObject3 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	hasEventHandler = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasEventHandler: %i\n", hasEventHandler );
	hasClipDepth = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasClipDepth: %i\n", hasClipDepth );
	hasName = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasName: %i\n", hasName );
	hasMorph = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMorph: %i\n", hasMorph );
	hasColorTransform = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasColorTransform: %i\n", hasColorTransform );
	hasTransform = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasTransform: %i\n", hasTransform );
	hasID = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasID: %i\n", hasID );
	replace = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE replace: %i\n", replace );
	reserved1 = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved1: %i\n", reserved1 );
	hasCacheAsBitmap = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasCacheAsBitmap: %i\n", hasCacheAsBitmap );
	hasBlendMode = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasBlendMode: %i\n", hasBlendMode );
	hasFilterList = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasFilterList: %i\n", hasFilterList );
	depth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE depth: %i\n", depth );
	if( hasID ) {
		objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	} else {
		objectID =  0;
	}
	if( hasTransform ) {
		transform.parse(r,end,ctx);
	} else {
	}
	if( hasColorTransform ) {
		colorTransform.parse(r,end,ctx);
	} else {
	}
	if( hasMorph ) {
		morph = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE morph: %i\n", morph );
	} else {
	}
	if( hasName ) {
		name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	} else {
		name =  NULL;
	}
	if( hasClipDepth ) {
		clipDepth = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE clipDepth: %i\n", clipDepth );
	} else {
		clipDepth =  0;
	}
	if( hasFilterList ) {
		numFilters = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE numFilters: %i\n", numFilters );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Filter> filters: %i items, @%i-%i :%i\n",  numFilters, r->getPosition(), r->getBits(), end );
		Filter *item;
		for( unsigned int i=0; i<numFilters; i++ ) {
			item = Filter::get(r,end,ctx);
			filters.append( item );
		}
	}
	} else {
	}
	if( hasBlendMode ) {
		blendMode = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE blendMode: %i\n", blendMode );
	} else {
		blendMode =  0;
	}
	if( hasCacheAsBitmap ) {
		bitmapCaching = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE bitmapCaching: %i\n", bitmapCaching );
	} else {
		bitmapCaching =  0;
	}
	if( hasEventHandler ) {
		reserved = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	allflags1 = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE allflags1: %i\n", allflags1 );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion>=6 - " );
	if( ctx->swfVersion>=6 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		allflags2 = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE allflags2: %i\n", allflags2 );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Event> events @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			Event *item;
			item = Event::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				events.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Event::get(r,myend,ctx);
				else item = NULL;
					if(item && !(item->getflags1() | item->getflags2())) {
						events.append( item );
						item = NULL;
					}
			}
		}
	}
	} else {
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag PlaceObject3 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ImportAssets2
bool ImportAssets2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ImportAssets2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	url = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE url: %s\n", url );
	reserved1 = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved1: %i\n", reserved1 );
	reserved2 = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved2: %i\n", reserved2 );
	count = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Symbol> symbols: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		Symbol *item;
		for( unsigned int i=0; i<count; i++ ) {
			item = Symbol::get(r,end,ctx);
			symbols.append( item );
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag ImportAssets2 is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// FileAttributes
bool FileAttributes::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE FileAttributes @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reserved1 = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved1: %i\n", reserved1 );
	hasMetaData = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE hasMetaData: %i\n", hasMetaData );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion < 9 - " );
	if( ctx->swfVersion < 9 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		reserved2 = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved2: %i\n", reserved2 );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF ctx->swfVersion >= 9 - " );
	if( ctx->swfVersion >= 9 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		allowABC = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE allowABC: %i\n", allowABC );
	suppressCrossDomainCaching = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE suppressCrossDomainCaching: %i\n", suppressCrossDomainCaching );
	swfRelativeURLs = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE swfRelativeURLs: %i\n", swfRelativeURLs );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
useNetwork = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE useNetwork: %i\n", useNetwork );
	reserved3 = r->getNBitInt(24);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved3: %i\n", reserved3 );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag FileAttributes is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineFontAlignZones
bool DefineFontAlignZones::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineFontAlignZones @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	csmTableHint = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE csmTableHint: %i\n", csmTableHint );
	reserved = r->getNBitInt(6);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<ZoneArray> zoneArrays: %i items, @%i-%i :%i\n",  ctx->glyphCount, r->getPosition(), r->getBits(), end );
		ZoneArray *item;
		for( unsigned int i=0; i<ctx->glyphCount; i++ ) {
			item = ZoneArray::get(r,end,ctx);
			zoneArrays.append( item );
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineFontAlignZones is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// CSMTextSettings
bool CSMTextSettings::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE CSMTextSettings @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	useFlashType = r->getNBitInt(2);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE useFlashType: %i\n", useFlashType );
	gridFit = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE gridFit: %i\n", gridFit );
	reserved1 = r->getNBitInt(3);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved1: %i\n", reserved1 );
	thickness = r->getFloat();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE thickness: %g\n", thickness );
	sharpness = r->getFloat();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE sharpness: %g\n", sharpness );
	reserved2 = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved2: %i\n", reserved2 );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag CSMTextSettings is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Metadata
bool Metadata::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Metadata @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	RDF = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RDF: %s\n", RDF );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag Metadata is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineScalingGrid
bool DefineScalingGrid::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineScalingGrid @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	splitter.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineScalingGrid is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DoABC
bool DoABC::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DoABC @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	actions.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DoABC is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DoABCDefine
bool DoABCDefine::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DoABCDefine @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	flags = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE flags: %i\n", flags );
	name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	actions.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DoABCDefine is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SymbolClass
bool SymbolClass::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SymbolClass @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	count = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE count: %i\n", count );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Symbol> symbols: %i items, @%i-%i :%i\n",  count, r->getPosition(), r->getBits(), end );
		Symbol *item;
		for( unsigned int i=0; i<count; i++ ) {
			item = Symbol::get(r,end,ctx);
			symbols.append( item );
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag SymbolClass is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineSceneAndFrameLabelData
bool DefineSceneAndFrameLabelData::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineSceneAndFrameLabelData @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	sceneCount = r->getEncodedU32();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE sceneCount: %i\n", sceneCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Scene> scenes: %i items, @%i-%i :%i\n",  sceneCount, r->getPosition(), r->getBits(), end );
		Scene *item;
		for( unsigned int i=0; i<sceneCount; i++ ) {
			item = Scene::get(r,end,ctx);
			scenes.append( item );
		}
	}
frameCount = r->getEncodedU32();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frameCount: %i\n", frameCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Frame> frames: %i items, @%i-%i :%i\n",  frameCount, r->getPosition(), r->getBits(), end );
		Frame *item;
		for( unsigned int i=0; i<frameCount; i++ ) {
			item = Frame::get(r,end,ctx);
			frames.append( item );
		}
	}
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineSceneAndFrameLabelData is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineBinaryData
bool DefineBinaryData::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineBinaryData @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	reserved = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	data.parse(r,end,ctx);
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineBinaryData is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineFontName
bool DefineFontName::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineFontName @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	objectID = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE objectID: %i\n", objectID );
	name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	copyright = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE copyright: %s\n", copyright );
	if( r->getPosition() != file_offset + len ) {
		fprintf( stderr, "WARNING: end of tag DefineFontName is @%i, should be @%i\n", r->getPosition(), file_offset+len );
		r->seekTo( file_offset + len );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackString
bool StackString::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackString @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %s\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackFloat
bool StackFloat::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackFloat @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getFloat();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %g\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackNull
bool StackNull::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackNull @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackUndefined
bool StackUndefined::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackUndefined @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackRegister
bool StackRegister::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackRegister @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reg = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reg: %i\n", reg );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackBoolean
bool StackBoolean::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackBoolean @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackDouble
bool StackDouble::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackDouble @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getDouble();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %g\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackInteger
bool StackInteger::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackInteger @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getInt();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackDictionaryLookup
bool StackDictionaryLookup::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackDictionaryLookup @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StackLargeDictionaryLookup
bool StackLargeDictionaryLookup::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StackLargeDictionaryLookup @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// UnknownAction
bool UnknownAction::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE UnknownAction @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		int sz = len;
		data = new unsigned char[ sz ];
		r->getData( data, sz );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// EndAction
bool EndAction::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE EndAction @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// NextFrame
bool NextFrame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE NextFrame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// PreviousFrame
bool PreviousFrame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE PreviousFrame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Play
bool Play::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Play @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Stop
bool Stop::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Stop @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ToggleQuality
bool ToggleQuality::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ToggleQuality @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StopSound
bool StopSound::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StopSound @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// AddCast
bool AddCast::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE AddCast @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Substract
bool Substract::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Substract @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Mulitply
bool Mulitply::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Mulitply @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Divide
bool Divide::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Divide @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// EqualCast
bool EqualCast::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE EqualCast @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// LessThanCast
bool LessThanCast::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE LessThanCast @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// LogicalAND
bool LogicalAND::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE LogicalAND @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// LogicalOR
bool LogicalOR::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE LogicalOR @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// LogicalNOT
bool LogicalNOT::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE LogicalNOT @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StringEqual
bool StringEqual::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StringEqual @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StringLength
bool StringLength::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StringLength @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SubString
bool SubString::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SubString @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Pop
bool Pop::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Pop @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// IntegralPart
bool IntegralPart::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IntegralPart @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GetVariable
bool GetVariable::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GetVariable @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetVariable
bool SetVariable::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetVariable @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetTargetDynamic
bool SetTargetDynamic::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetTargetDynamic @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ConcatenateString
bool ConcatenateString::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ConcatenateString @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GetProperty
bool GetProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GetProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetProperty
bool SetProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DuplicateSprite
bool DuplicateSprite::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DuplicateSprite @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RemoveSprite
bool RemoveSprite::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RemoveSprite @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Trace
bool Trace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Trace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StartDrag
bool StartDrag::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StartDrag @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StopDrag
bool StopDrag::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StopDrag @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StringLessThan
bool StringLessThan::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StringLessThan @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Throw
bool Throw::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Throw @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// CastObject
bool CastObject::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE CastObject @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Implements
bool Implements::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Implements @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Random
bool Random::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Random @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MultibyteStringLength
bool MultibyteStringLength::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MultibyteStringLength @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ORD
bool ORD::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ORD @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// CHR
bool CHR::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE CHR @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GetTimer
bool GetTimer::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GetTimer @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MultibyteSubString
bool MultibyteSubString::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MultibyteSubString @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MultibyteORD
bool MultibyteORD::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MultibyteORD @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MultibyteCHR
bool MultibyteCHR::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MultibyteCHR @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Delete
bool Delete::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Delete @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DeleteAll
bool DeleteAll::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DeleteAll @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetLocalVariable
bool SetLocalVariable::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetLocalVariable @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// CallFunction
bool CallFunction::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE CallFunction @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Return
bool Return::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Return @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Modulo
bool Modulo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Modulo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// New
bool New::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE New @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DeclareLocalVariable
bool DeclareLocalVariable::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DeclareLocalVariable @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DeclareArray
bool DeclareArray::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DeclareArray @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DeclareObject
bool DeclareObject::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DeclareObject @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// TypeOf
bool TypeOf::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE TypeOf @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GetTarget
bool GetTarget::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GetTarget @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Enumerate
bool Enumerate::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Enumerate @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// AddTyped
bool AddTyped::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE AddTyped @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// LessThanTyped
bool LessThanTyped::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE LessThanTyped @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// EqualTyped
bool EqualTyped::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE EqualTyped @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineNumber
bool DefineNumber::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineNumber @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DefineString
bool DefineString::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DefineString @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Duplicate
bool Duplicate::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Duplicate @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Swap
bool Swap::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Swap @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GetMember
bool GetMember::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GetMember @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetMember
bool SetMember::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetMember @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Increment
bool Increment::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Increment @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Decrement
bool Decrement::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Decrement @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// CallMethod
bool CallMethod::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE CallMethod @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// NewMethod
bool NewMethod::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE NewMethod @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// InstanceOf
bool InstanceOf::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE InstanceOf @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// EnumerateObject
bool EnumerateObject::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE EnumerateObject @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// AND
bool AND::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE AND @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OR
bool OR::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OR @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// XOR
bool XOR::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE XOR @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ShiftLeft
bool ShiftLeft::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ShiftLeft @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ShiftRight
bool ShiftRight::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ShiftRight @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ShiftRightUnsigned
bool ShiftRightUnsigned::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ShiftRightUnsigned @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StrictEqual
bool StrictEqual::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StrictEqual @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GreaterThanTyped
bool GreaterThanTyped::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GreaterThanTyped @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StringGreaterThan
bool StringGreaterThan::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StringGreaterThan @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Extends
bool Extends::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Extends @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GotoFrame
bool GotoFrame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GotoFrame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	frame = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frame: %i\n", frame );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GetURL
bool GetURL::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GetURL @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	url = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE url: %s\n", url );
	target = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %s\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// StoreRegister
bool StoreRegister::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE StoreRegister @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reg = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reg: %i\n", reg );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Dictionary
bool Dictionary::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Dictionary @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	length = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE length: %i\n", length );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<String> strings: %i items, @%i-%i :%i\n",  length, r->getPosition(), r->getBits(), end );
		String *item;
		for( unsigned int i=0; i<length; i++ ) {
			item = String::get(r,end,ctx);
			strings.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// WaitForFrame
bool WaitForFrame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE WaitForFrame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	frame = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frame: %i\n", frame );
	skip = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE skip: %i\n", skip );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// SetTarget
bool SetTarget::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE SetTarget @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	label = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE label: %s\n", label );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GotoLabel
bool GotoLabel::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GotoLabel @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	label = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE label: %s\n", label );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// WaitForFrameDynamic
bool WaitForFrameDynamic::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE WaitForFrameDynamic @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	frame = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE frame: %i\n", frame );
	skip = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE skip: %i\n", skip );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DeclareFunction2
bool DeclareFunction2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DeclareFunction2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	argc = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	regc = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE regc: %i\n", regc );
	preloadParent = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE preloadParent: %i\n", preloadParent );
	preloadRoot = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE preloadRoot: %i\n", preloadRoot );
	suppressSuper = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE suppressSuper: %i\n", suppressSuper );
	preloadSuper = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE preloadSuper: %i\n", preloadSuper );
	suppressArguments = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE suppressArguments: %i\n", suppressArguments );
	preloadArguments = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE preloadArguments: %i\n", preloadArguments );
	suppressThis = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE suppressThis: %i\n", suppressThis );
	preloadThis = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE preloadThis: %i\n", preloadThis );
	reserved = r->getNBitInt(7);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	preloadGlobal = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE preloadGlobal: %i\n", preloadGlobal );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Parameter> args: %i items, @%i-%i :%i\n",  argc, r->getPosition(), r->getBits(), end );
		Parameter *item;
		for( unsigned int i=0; i<argc; i++ ) {
			item = Parameter::get(r,end,ctx);
			args.append( item );
		}
	}
length = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE length: %i\n", length );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<Action> actions @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
			myend = r->getPosition() + length;
		if( r->getPosition() < myend ) {
			Action *item;
			item = Action::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				actions.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = Action::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Try
bool Try::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Try @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	reserved = r->getNBitInt(5);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reserved: %i\n", reserved );
	catchInRegister = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE catchInRegister: %i\n", catchInRegister );
	doFinally = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE doFinally: %i\n", doFinally );
	doCatch = r->getNBitInt(1);
	if( ctx->debugTrace ) fprintf( stderr, "PARSE doCatch: %i\n", doCatch );
	trySize = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE trySize: %i\n", trySize );
	catchSize = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE catchSize: %i\n", catchSize );
	finallySize = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE finallySize: %i\n", finallySize );
	if( catchInRegister ) {
		reg = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reg: %i\n", reg );
	} else {
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// With
bool With::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE With @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	size = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE size: %i\n", size );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// PushData
bool PushData::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE PushData @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<StackItem> items @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
		int myend = end;
		if( r->getPosition() < myend ) {
			StackItem *item;
			item = StackItem::get(r,end,ctx);
			while( item && r->getPosition() <= myend ) {
				items.append( item );
				if( r->getPosition() < myend || (r->getPosition()==myend && r->getBits() ))
					item = StackItem::get(r,myend,ctx);
				else item = NULL;
			}
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GetURL2
bool GetURL2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GetURL2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	method = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE method: %i\n", method );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// DeclareFunction
bool DeclareFunction::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE DeclareFunction @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getString();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %s\n", name );
	argc = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<String> args: %i items, @%i-%i :%i\n",  argc, r->getPosition(), r->getBits(), end );
		String *item;
		for( unsigned int i=0; i<argc; i++ ) {
			item = String::get(r,end,ctx);
			args.append( item );
		}
	}
length = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE length: %i\n", length );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// BranchAlways
bool BranchAlways::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE BranchAlways @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	byteOffset = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE byteOffset: %i\n", byteOffset );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// BranchIfTrue
bool BranchIfTrue::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE BranchIfTrue @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	byteOffset = r->getWord();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE byteOffset: %i\n", byteOffset );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// CallFrame
bool CallFrame::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE CallFrame @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// GotoExpression
bool GotoExpression::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE GotoExpression @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	play = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE play: %i\n", play );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// PrivateNamespace
bool PrivateNamespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE PrivateNamespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Namespace
bool Namespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Namespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// PackageNamespace
bool PackageNamespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE PackageNamespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// PackageInternalNamespace
bool PackageInternalNamespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE PackageInternalNamespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ProtectedNamespace
bool ProtectedNamespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ProtectedNamespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// ExplicitNamespace
bool ExplicitNamespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE ExplicitNamespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MultinameLNamespace
bool MultinameLNamespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MultinameLNamespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// QName
bool QName::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE QName @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	namespaceIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE namespaceIndex: %i\n", namespaceIndex );
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// QNameA
bool QNameA::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE QNameA @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	namespaceIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE namespaceIndex: %i\n", namespaceIndex );
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Multiname
bool Multiname::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Multiname @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	namespaceSetIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE namespaceSetIndex: %i\n", namespaceSetIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MultinameA
bool MultinameA::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MultinameA @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	namespaceSetIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE namespaceSetIndex: %i\n", namespaceSetIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RTQName
bool RTQName::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RTQName @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RTQNameA
bool RTQNameA::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RTQNameA @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	nameIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE nameIndex: %i\n", nameIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// MultinameL
bool MultinameL::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE MultinameL @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	namespaceSetIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE namespaceSetIndex: %i\n", namespaceSetIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RTQNameL
bool RTQNameL::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RTQNameL @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// RTQNameLA
bool RTQNameLA::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE RTQNameLA @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Slot
bool Slot::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Slot @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	typeIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE typeIndex: %i\n", typeIndex );
	valueIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE valueIndex: %i\n", valueIndex );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF valueIndex != 0 - " );
	if( valueIndex != 0 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		valueKind = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE valueKind: %i\n", valueKind );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Const
bool Const::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Const @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	typeIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE typeIndex: %i\n", typeIndex );
	valueIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE valueIndex: %i\n", valueIndex );
	if( ctx->debugTrace ) fprintf( stderr, "PARSE IF valueIndex != 0 - " );
	if( valueIndex != 0 ) {
		if( ctx->debugTrace ) fprintf( stderr, "TRUE\n" );
		valueKind = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE valueKind: %i\n", valueKind );
	} else {
		if( ctx->debugTrace ) fprintf( stderr, "FALSE\n" );
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Method
bool Method::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Method @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	dispID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE dispID: %i\n", dispID );
	methodInfo = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodInfo: %i\n", methodInfo );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Getter
bool Getter::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Getter @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	dispID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE dispID: %i\n", dispID );
	methodInfo = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodInfo: %i\n", methodInfo );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Setter
bool Setter::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Setter @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	dispID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE dispID: %i\n", dispID );
	methodInfo = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodInfo: %i\n", methodInfo );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Class
bool Class::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Class @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	classInfo = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE classInfo: %i\n", classInfo );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// Function
bool Function::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE Function @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	methodInfo = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodInfo: %i\n", methodInfo );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpBkPt
bool OpBkPt::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpBkPt @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNop
bool OpNop::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNop @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpThrow
bool OpThrow::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpThrow @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetSuper
bool OpGetSuper::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetSuper @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetSuper
bool OpSetSuper::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetSuper @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDXNs
bool OpDXNs::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDXNs @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	dxns = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE dxns: %i\n", dxns );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDXNsLate
bool OpDXNsLate::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDXNsLate @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpKill
bool OpKill::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpKill @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	address = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE address: %i\n", address );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpLabel
bool OpLabel::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpLabel @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfNlt
bool OpIfNlt::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfNlt @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfNle
bool OpIfNle::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfNle @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfNgt
bool OpIfNgt::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfNgt @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfNge
bool OpIfNge::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfNge @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpJump
bool OpJump::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpJump @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfTrue
bool OpIfTrue::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfTrue @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfFalse
bool OpIfFalse::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfFalse @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfEq
bool OpIfEq::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfEq @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfNe
bool OpIfNe::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfNe @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfLt
bool OpIfLt::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfLt @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfLe
bool OpIfLe::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfLe @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfGt
bool OpIfGt::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfGt @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfGe
bool OpIfGe::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfGe @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfStrictEq
bool OpIfStrictEq::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfStrictEq @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIfStrictNe
bool OpIfStrictNe::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIfStrictNe @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	target = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE target: %i\n", target );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpLookupSwitch
bool OpLookupSwitch::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpLookupSwitch @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	defaulTarget = r->getS24();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE defaulTarget: %i\n", defaulTarget );
	caseCount = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE caseCount: %i\n", caseCount );
	{
		if( ctx->debugTrace ) fprintf( stderr, "PARSE list<S24> targetTable: %i items, @%i-%i :%i\n",  
				( caseCount + 1 )
			, r->getPosition(), r->getBits(), end );
		S24 *item;
		for( unsigned int i=0; i<
				( caseCount + 1 )
			; i++ ) {
			item = S24::get(r,end,ctx);
			targetTable.append( item );
		}
	}
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushWith
bool OpPushWith::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushWith @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPopScope
bool OpPopScope::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPopScope @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNextName
bool OpNextName::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNextName @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpHasNext
bool OpHasNext::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpHasNext @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushNull
bool OpPushNull::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushNull @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushUndefined
bool OpPushUndefined::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushUndefined @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNextValue
bool OpNextValue::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNextValue @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushByte
bool OpPushByte::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushByte @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushShort
bool OpPushShort::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushShort @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	value = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE value: %i\n", value );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushTrue
bool OpPushTrue::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushTrue @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushFalse
bool OpPushFalse::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushFalse @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushNaN
bool OpPushNaN::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushNaN @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPop
bool OpPop::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPop @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDup
bool OpDup::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDup @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSwap
bool OpSwap::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSwap @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushString
bool OpPushString::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushString @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushInt
bool OpPushInt::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushInt @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushUInt
bool OpPushUInt::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushUInt @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushDouble
bool OpPushDouble::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushDouble @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushScope
bool OpPushScope::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushScope @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpPushNamespace
bool OpPushNamespace::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpPushNamespace @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpHasNext2
bool OpHasNext2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpHasNext2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	object = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE object: %i\n", object );
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNewFunction
bool OpNewFunction::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNewFunction @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	index = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE index: %i\n", index );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCall
bool OpCall::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCall @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConstruct
bool OpConstruct::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConstruct @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCallMethod
bool OpCallMethod::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCallMethod @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	dispID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE dispID: %i\n", dispID );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCallStatic
bool OpCallStatic::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCallStatic @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	methodID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE methodID: %i\n", methodID );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCallSuper
bool OpCallSuper::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCallSuper @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCallProperty
bool OpCallProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCallProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpReturnVoid
bool OpReturnVoid::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpReturnVoid @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpReturnValue
bool OpReturnValue::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpReturnValue @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConstructSuper
bool OpConstructSuper::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConstructSuper @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConstructProp
bool OpConstructProp::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConstructProp @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCallPropLex
bool OpCallPropLex::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCallPropLex @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCallSuperVoid
bool OpCallSuperVoid::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCallSuperVoid @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCallPropVoid
bool OpCallPropVoid::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCallPropVoid @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNewObject
bool OpNewObject::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNewObject @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNewArray
bool OpNewArray::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNewArray @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	argc = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE argc: %i\n", argc );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNewActivation
bool OpNewActivation::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNewActivation @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNewClass
bool OpNewClass::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNewClass @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	classIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE classIndex: %i\n", classIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetDescendants
bool OpGetDescendants::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetDescendants @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNewCatch
bool OpNewCatch::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNewCatch @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	exceptionIndex = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE exceptionIndex: %i\n", exceptionIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpFindPropStrict
bool OpFindPropStrict::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpFindPropStrict @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpFindProperty
bool OpFindProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpFindProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpFindDef
bool OpFindDef::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpFindDef @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetLex
bool OpGetLex::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetLex @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetProperty
bool OpSetProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetLocal
bool OpGetLocal::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetLocal @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	address = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE address: %i\n", address );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetLocal
bool OpSetLocal::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetLocal @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	address = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE address: %i\n", address );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetGlobalScope
bool OpGetGlobalScope::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetGlobalScope @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetScopeObject
bool OpGetScopeObject::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetScopeObject @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	scopeIndex = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE scopeIndex: %i\n", scopeIndex );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetProperty
bool OpGetProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpInitProperty
bool OpInitProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpInitProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDeleteProperty
bool OpDeleteProperty::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDeleteProperty @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetSlot
bool OpGetSlot::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetSlot @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetSlot
bool OpSetSlot::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetSlot @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetGlobalSlot
bool OpGetGlobalSlot::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetGlobalSlot @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetGlobalSlot
bool OpSetGlobalSlot::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetGlobalSlot @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	slotID = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE slotID: %i\n", slotID );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConvertS
bool OpConvertS::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConvertS @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpEscXelem
bool OpEscXelem::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpEscXelem @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpEscXattr
bool OpEscXattr::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpEscXattr @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConvertI
bool OpConvertI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConvertI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConvertU
bool OpConvertU::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConvertU @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConvertD
bool OpConvertD::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConvertD @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConvertB
bool OpConvertB::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConvertB @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpConvertO
bool OpConvertO::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpConvertO @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCheckFilter
bool OpCheckFilter::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCheckFilter @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerce
bool OpCoerce::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerce @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerceB
bool OpCoerceB::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerceB @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerceA
bool OpCoerceA::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerceA @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerceI
bool OpCoerceI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerceI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerceD
bool OpCoerceD::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerceD @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerceS
bool OpCoerceS::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerceS @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpAsType
bool OpAsType::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpAsType @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpAsTypeLate
bool OpAsTypeLate::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpAsTypeLate @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerceU
bool OpCoerceU::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerceU @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpCoerceO
bool OpCoerceO::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpCoerceO @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNegate
bool OpNegate::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNegate @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIncrement
bool OpIncrement::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIncrement @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIncLocal
bool OpIncLocal::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIncLocal @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	address = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE address: %i\n", address );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDecrement
bool OpDecrement::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDecrement @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDecLocal
bool OpDecLocal::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDecLocal @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	address = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE address: %i\n", address );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpTypeOf
bool OpTypeOf::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpTypeOf @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNot
bool OpNot::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNot @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpBitNot
bool OpBitNot::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpBitNot @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpAdd
bool OpAdd::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpAdd @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSubtract
bool OpSubtract::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSubtract @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpMultiply
bool OpMultiply::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpMultiply @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDivide
bool OpDivide::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDivide @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpModulo
bool OpModulo::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpModulo @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpLShift
bool OpLShift::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpLShift @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpRShift
bool OpRShift::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpRShift @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpURShift
bool OpURShift::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpURShift @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpBitAnd
bool OpBitAnd::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpBitAnd @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpBitOr
bool OpBitOr::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpBitOr @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpBitXor
bool OpBitXor::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpBitXor @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpEquals
bool OpEquals::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpEquals @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpStrictEquals
bool OpStrictEquals::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpStrictEquals @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpLessThan
bool OpLessThan::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpLessThan @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpLessEquals
bool OpLessEquals::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpLessEquals @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGreaterThan
bool OpGreaterThan::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGreaterThan @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGreaterEquals
bool OpGreaterEquals::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGreaterEquals @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpInstanceOf
bool OpInstanceOf::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpInstanceOf @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIsType
bool OpIsType::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIsType @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIsTypeLate
bool OpIsTypeLate::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIsTypeLate @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIn
bool OpIn::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIn @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIncrementI
bool OpIncrementI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIncrementI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDecrementI
bool OpDecrementI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDecrementI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpIncLocalI
bool OpIncLocalI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpIncLocalI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	address = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE address: %i\n", address );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDecLocalI
bool OpDecLocalI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDecLocalI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	address = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE address: %i\n", address );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpNegateI
bool OpNegateI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpNegateI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpAddI
bool OpAddI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpAddI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSubtractI
bool OpSubtractI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSubtractI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpMultiplyI
bool OpMultiplyI::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpMultiplyI @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetLocal0
bool OpGetLocal0::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetLocal0 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetLocal1
bool OpGetLocal1::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetLocal1 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetLocal2
bool OpGetLocal2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetLocal2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpGetLocal3
bool OpGetLocal3::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpGetLocal3 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetLocal0
bool OpSetLocal0::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetLocal0 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetLocal1
bool OpSetLocal1::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetLocal1 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetLocal2
bool OpSetLocal2::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetLocal2 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpSetLocal3
bool OpSetLocal3::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpSetLocal3 @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDebugReg
bool OpDebugReg::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDebugReg @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	unknown = r->getByte();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE unknown: %i\n", unknown );
	name = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE name: %i\n", name );
	reg = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE reg: %i\n", reg );
	line = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE line: %i\n", line );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDebugLine
bool OpDebugLine::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDebugLine @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	line = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE line: %i\n", line );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpDebugFile
bool OpDebugFile::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpDebugFile @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	file = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE file: %i\n", file );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpBkPtLine
bool OpBkPtLine::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpBkPtLine @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	line = r->getU30();
	if( ctx->debugTrace ) fprintf( stderr, "PARSE line: %i\n", line );
	return r->getError() == SWFR_OK;
}
//////////////////////////////////// OpTimestamp
bool OpTimestamp::parse( Reader *r, int end, Context *ctx ) {
	if( ctx->debugTrace ) fprintf( stderr, "PARSE OpTimestamp @%i-%i :%i\n", r->getPosition(), r->getBits(), end );
	file_offset = r->getPosition();
	return r->getError() == SWFR_OK;
}
}
