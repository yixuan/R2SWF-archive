#include "SWF.h"
#include "SWFTag.h"
#include <cstring>
namespace SWF {
// ------------ context structure
Context::Context() : swf_encoding(0) {
	swfVersion = 0;
	transientPropsToXML = false;
	debugTrace = false;
	exportAssets = false;
	isLast = false;
	tagVersion = 0;
	quiet = false;
	convertEncoding = false;
	fillBits = 0;
lineBits = 0;
glyphBits = 0;
advanceBits = 0;
glyphBits = 0;
advanceBits = 0;
wideGlyphOffsets = 0;
wideMap = 0;
glyphCount = 0;
wideGlyphOffsets = 0;
wideMap = 0;
glyphCount = 0;
}
// ------------ basic object functions
Rectangle::Rectangle() {
	bits = 0;
left = 0;
right = 0;
top = 0;
bottom = 0;
}
Rectangle::~Rectangle() {
}
Rectangle* Rectangle::get( Reader *r, int end, Context *ctx ) {
	Rectangle* ret = new Rectangle;
	ret->parse( r, end, ctx );
	return ret;
}
Rectangle* Rectangle::getByName( const char *name ) {
	if( strcmp( name, "Rectangle" ) ) return NULL;
	Rectangle* ret = new Rectangle;
	return ret;
}
	// Constant Size Primitive
	int Rectangle::getbits() {
		return bits;
	}
	void Rectangle::setbits( int v ) {
		bits = v;
	}
	// NBitInt
	int Rectangle::getleft() {
		return left;
	}
	void Rectangle::setleft( int v ) {
		left = v;
	}
	// NBitInt
	int Rectangle::getright() {
		return right;
	}
	void Rectangle::setright( int v ) {
		right = v;
	}
	// NBitInt
	int Rectangle::gettop() {
		return top;
	}
	void Rectangle::settop( int v ) {
		top = v;
	}
	// NBitInt
	int Rectangle::getbottom() {
		return bottom;
	}
	void Rectangle::setbottom( int v ) {
		bottom = v;
	}
Color::Color() {
	red = 0;
green = 0;
blue = 0;
alpha = 0;
}
Color::~Color() {
}
Color* Color::get( Reader *r, int end, Context *ctx ) {
	Color* ret = new Color;
	ret->parse( r, end, ctx );
	return ret;
}
Color* Color::getByName( const char *name ) {
	if( strcmp( name, "Color" ) ) return NULL;
	Color* ret = new Color;
	return ret;
}
	// Constant Size Primitive
	unsigned char Color::getred() {
		return red;
	}
	void Color::setred( unsigned char v ) {
		red = v;
	}
	// Constant Size Primitive
	unsigned char Color::getgreen() {
		return green;
	}
	void Color::setgreen( unsigned char v ) {
		green = v;
	}
	// Constant Size Primitive
	unsigned char Color::getblue() {
		return blue;
	}
	void Color::setblue( unsigned char v ) {
		blue = v;
	}
	// Constant Size Primitive
	unsigned char Color::getalpha() {
		return alpha;
	}
	void Color::setalpha( unsigned char v ) {
		alpha = v;
	}
String::String() {
	value = NULL;
}
String::~String() {
	delete[] value;
}
String* String::get( Reader *r, int end, Context *ctx ) {
	String* ret = new String;
	ret->parse( r, end, ctx );
	return ret;
}
String* String::getByName( const char *name ) {
	if( strcmp( name, "String" ) ) return NULL;
	String* ret = new String;
	return ret;
}
char * String::getvalue() {
		return value;
	}
	void String::setvalue( char * v ) {
		delete value;
		value = v;
	}
String2::String2() {
	value = NULL;
}
String2::~String2() {
	delete[] value;
}
String2* String2::get( Reader *r, int end, Context *ctx ) {
	String2* ret = new String2;
	ret->parse( r, end, ctx );
	return ret;
}
String2* String2::getByName( const char *name ) {
	if( strcmp( name, "String2" ) ) return NULL;
	String2* ret = new String2;
	return ret;
}
char * String2::getvalue() {
		return value;
	}
	void String2::setvalue( char * v ) {
		delete value;
		value = v;
	}
Transform::Transform() {
	scaled = 0;
bitsScale = 0;
scaleX = 1;
scaleY = 1;
skewed = 0;
bitsSkew = 0;
skewX = 1;
skewY = 1;
bitsTranslate = 0;
transX = 0;
transY = 0;
}
Transform::~Transform() {
}
Transform* Transform::get( Reader *r, int end, Context *ctx ) {
	Transform* ret = new Transform;
	ret->parse( r, end, ctx );
	return ret;
}
Transform* Transform::getByName( const char *name ) {
	if( strcmp( name, "Transform" ) ) return NULL;
	Transform* ret = new Transform;
	return ret;
}
	// Constant Size Primitive
	bool Transform::getscaled() {
		return scaled;
	}
	void Transform::setscaled( bool v ) {
		scaled = v;
	}
	// Constant Size Primitive
	int Transform::getbitsScale() {
		return bitsScale;
	}
	void Transform::setbitsScale( int v ) {
		bitsScale = v;
	}
	// Constant Size Primitive
	float Transform::getscaleX() {
		return scaleX;
	}
	void Transform::setscaleX( float v ) {
		scaleX = v;
	}
	// Constant Size Primitive
	float Transform::getscaleY() {
		return scaleY;
	}
	void Transform::setscaleY( float v ) {
		scaleY = v;
	}
	// Constant Size Primitive
	bool Transform::getskewed() {
		return skewed;
	}
	void Transform::setskewed( bool v ) {
		skewed = v;
	}
	// Constant Size Primitive
	int Transform::getbitsSkew() {
		return bitsSkew;
	}
	void Transform::setbitsSkew( int v ) {
		bitsSkew = v;
	}
	// Constant Size Primitive
	float Transform::getskewX() {
		return skewX;
	}
	void Transform::setskewX( float v ) {
		skewX = v;
	}
	// Constant Size Primitive
	float Transform::getskewY() {
		return skewY;
	}
	void Transform::setskewY( float v ) {
		skewY = v;
	}
	// Constant Size Primitive
	int Transform::getbitsTranslate() {
		return bitsTranslate;
	}
	void Transform::setbitsTranslate( int v ) {
		bitsTranslate = v;
	}
	// NBitInt
	int Transform::gettransX() {
		return transX;
	}
	void Transform::settransX( int v ) {
		transX = v;
	}
	// NBitInt
	int Transform::gettransY() {
		return transY;
	}
	void Transform::settransY( int v ) {
		transY = v;
	}
ColorTransform2::ColorTransform2() {
	hasOffset = 0;
hasFactor = 0;
bits = 0;
factorRed = 1;
factorGreen = 1;
factorBlue = 1;
factorAlpha = 1;
offsetRed = 1;
offsetGreen = 1;
offsetBlue = 1;
offsetAlpha = 1;
}
ColorTransform2::~ColorTransform2() {
}
ColorTransform2* ColorTransform2::get( Reader *r, int end, Context *ctx ) {
	ColorTransform2* ret = new ColorTransform2;
	ret->parse( r, end, ctx );
	return ret;
}
ColorTransform2* ColorTransform2::getByName( const char *name ) {
	if( strcmp( name, "ColorTransform2" ) ) return NULL;
	ColorTransform2* ret = new ColorTransform2;
	return ret;
}
	// Constant Size Primitive
	bool ColorTransform2::gethasOffset() {
		return hasOffset;
	}
	void ColorTransform2::sethasOffset( bool v ) {
		hasOffset = v;
	}
	// Constant Size Primitive
	bool ColorTransform2::gethasFactor() {
		return hasFactor;
	}
	void ColorTransform2::sethasFactor( bool v ) {
		hasFactor = v;
	}
	// Constant Size Primitive
	int ColorTransform2::getbits() {
		return bits;
	}
	void ColorTransform2::setbits( int v ) {
		bits = v;
	}
	// NBitInt
	int ColorTransform2::getfactorRed() {
		return factorRed;
	}
	void ColorTransform2::setfactorRed( int v ) {
		factorRed = v;
	}
	// NBitInt
	int ColorTransform2::getfactorGreen() {
		return factorGreen;
	}
	void ColorTransform2::setfactorGreen( int v ) {
		factorGreen = v;
	}
	// NBitInt
	int ColorTransform2::getfactorBlue() {
		return factorBlue;
	}
	void ColorTransform2::setfactorBlue( int v ) {
		factorBlue = v;
	}
	// NBitInt
	int ColorTransform2::getfactorAlpha() {
		return factorAlpha;
	}
	void ColorTransform2::setfactorAlpha( int v ) {
		factorAlpha = v;
	}
	// NBitInt
	int ColorTransform2::getoffsetRed() {
		return offsetRed;
	}
	void ColorTransform2::setoffsetRed( int v ) {
		offsetRed = v;
	}
	// NBitInt
	int ColorTransform2::getoffsetGreen() {
		return offsetGreen;
	}
	void ColorTransform2::setoffsetGreen( int v ) {
		offsetGreen = v;
	}
	// NBitInt
	int ColorTransform2::getoffsetBlue() {
		return offsetBlue;
	}
	void ColorTransform2::setoffsetBlue( int v ) {
		offsetBlue = v;
	}
	// NBitInt
	int ColorTransform2::getoffsetAlpha() {
		return offsetAlpha;
	}
	void ColorTransform2::setoffsetAlpha( int v ) {
		offsetAlpha = v;
	}
Header::Header() {
	framerate = 0;
frames = 1;
}
Header::~Header() {
}
Header* Header::get( Reader *r, int end, Context *ctx ) {
	Header* ret = new Header;
	ret->parse( r, end, ctx );
	return ret;
}
Header* Header::getByName( const char *name ) {
	if( strcmp( name, "Header" ) ) return NULL;
	Header* ret = new Header;
	return ret;
}
Rectangle *Header::getsize() {
		return &size;
	}
	// Constant Size Primitive
	int Header::getframerate() {
		return framerate;
	}
	void Header::setframerate( int v ) {
		framerate = v;
	}
	// Constant Size Primitive
	unsigned short Header::getframes() {
		return frames;
	}
	void Header::setframes( unsigned short v ) {
		frames = v;
	}
List<Tag> *Header::gettags() {
		return &tags;
	}
LineStyle::LineStyle() {
	width = 0;
startCapStyle = 0;
jointStyle = 0;
hasFill = 0;
noHScale = 0;
noVScale = 0;
pixelHinting = 0;
reserved = 0;
noClose = 0;
endCapStyle = 0;
miterLimitFactor = 0;
}
LineStyle::~LineStyle() {
}
LineStyle* LineStyle::get( Reader *r, int end, Context *ctx ) {
	LineStyle* ret = new LineStyle;
	ret->parse( r, end, ctx );
	return ret;
}
LineStyle* LineStyle::getByName( const char *name ) {
	if( strcmp( name, "LineStyle" ) ) return NULL;
	LineStyle* ret = new LineStyle;
	return ret;
}
	// Constant Size Primitive
	unsigned short LineStyle::getwidth() {
		return width;
	}
	void LineStyle::setwidth( unsigned short v ) {
		width = v;
	}
Color *LineStyle::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	int LineStyle::getstartCapStyle() {
		return startCapStyle;
	}
	void LineStyle::setstartCapStyle( int v ) {
		startCapStyle = v;
	}
	// Constant Size Primitive
	int LineStyle::getjointStyle() {
		return jointStyle;
	}
	void LineStyle::setjointStyle( int v ) {
		jointStyle = v;
	}
	// Constant Size Primitive
	bool LineStyle::gethasFill() {
		return hasFill;
	}
	void LineStyle::sethasFill( bool v ) {
		hasFill = v;
	}
	// Constant Size Primitive
	bool LineStyle::getnoHScale() {
		return noHScale;
	}
	void LineStyle::setnoHScale( bool v ) {
		noHScale = v;
	}
	// Constant Size Primitive
	bool LineStyle::getnoVScale() {
		return noVScale;
	}
	void LineStyle::setnoVScale( bool v ) {
		noVScale = v;
	}
	// Constant Size Primitive
	bool LineStyle::getpixelHinting() {
		return pixelHinting;
	}
	void LineStyle::setpixelHinting( bool v ) {
		pixelHinting = v;
	}
	// Constant Size Primitive
	int LineStyle::getreserved() {
		return reserved;
	}
	void LineStyle::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool LineStyle::getnoClose() {
		return noClose;
	}
	void LineStyle::setnoClose( bool v ) {
		noClose = v;
	}
	// Constant Size Primitive
	int LineStyle::getendCapStyle() {
		return endCapStyle;
	}
	void LineStyle::setendCapStyle( int v ) {
		endCapStyle = v;
	}
	// Constant Size Primitive
	float LineStyle::getmiterLimitFactor() {
		return miterLimitFactor;
	}
	void LineStyle::setmiterLimitFactor( float v ) {
		miterLimitFactor = v;
	}
List<Style> *LineStyle::getfillStyles() {
		return &fillStyles;
	}
Color *LineStyle::getfillColor() {
		return &fillColor;
	}
StyleList::StyleList() {
	n_fillStyles = 0;
n_lineStyles = 0;
fillBits = 0;
lineBits = 0;
}
StyleList::~StyleList() {
}
StyleList* StyleList::get( Reader *r, int end, Context *ctx ) {
	StyleList* ret = new StyleList;
	ret->parse( r, end, ctx );
	return ret;
}
StyleList* StyleList::getByName( const char *name ) {
	if( strcmp( name, "StyleList" ) ) return NULL;
	StyleList* ret = new StyleList;
	return ret;
}
	// Constant Size Primitive
	unsigned short StyleList::getn_fillStyles() {
		return n_fillStyles;
	}
	void StyleList::setn_fillStyles( unsigned short v ) {
		n_fillStyles = v;
	}
List<Style> *StyleList::getfillStyles() {
		return &fillStyles;
	}
	// Constant Size Primitive
	unsigned short StyleList::getn_lineStyles() {
		return n_lineStyles;
	}
	void StyleList::setn_lineStyles( unsigned short v ) {
		n_lineStyles = v;
	}
List<LineStyle> *StyleList::getlineStyles() {
		return &lineStyles;
	}
	// Constant Size Primitive
	int StyleList::getfillBits() {
		return fillBits;
	}
	void StyleList::setfillBits( int v ) {
		fillBits = v;
	}
	// Constant Size Primitive
	int StyleList::getlineBits() {
		return lineBits;
	}
	void StyleList::setlineBits( int v ) {
		lineBits = v;
	}
ShapeSetup::ShapeSetup() {
	hasNewStyles = 0;
hasLineStyle = 0;
hasFillStyle1 = 0;
hasFillStyle0 = 0;
hasMoveTo = 0;
xybits = 0;
x = 0;
y = 0;
fillStyle0 = 0;
fillStyle1 = 0;
lineStyle = 0;
}
ShapeSetup::~ShapeSetup() {
}
ShapeSetup* ShapeSetup::get( Reader *r, int end, Context *ctx ) {
	ShapeSetup* ret = new ShapeSetup;
	ret->parse( r, end, ctx );
	return ret;
}
ShapeSetup* ShapeSetup::getByName( const char *name ) {
	if( strcmp( name, "ShapeSetup" ) ) return NULL;
	ShapeSetup* ret = new ShapeSetup;
	return ret;
}
	// Constant Size Primitive
	bool ShapeSetup::gethasNewStyles() {
		return hasNewStyles;
	}
	void ShapeSetup::sethasNewStyles( bool v ) {
		hasNewStyles = v;
	}
	// Constant Size Primitive
	bool ShapeSetup::gethasLineStyle() {
		return hasLineStyle;
	}
	void ShapeSetup::sethasLineStyle( bool v ) {
		hasLineStyle = v;
	}
	// Constant Size Primitive
	bool ShapeSetup::gethasFillStyle1() {
		return hasFillStyle1;
	}
	void ShapeSetup::sethasFillStyle1( bool v ) {
		hasFillStyle1 = v;
	}
	// Constant Size Primitive
	bool ShapeSetup::gethasFillStyle0() {
		return hasFillStyle0;
	}
	void ShapeSetup::sethasFillStyle0( bool v ) {
		hasFillStyle0 = v;
	}
	// Constant Size Primitive
	bool ShapeSetup::gethasMoveTo() {
		return hasMoveTo;
	}
	void ShapeSetup::sethasMoveTo( bool v ) {
		hasMoveTo = v;
	}
	// Constant Size Primitive
	int ShapeSetup::getxybits() {
		return xybits;
	}
	void ShapeSetup::setxybits( int v ) {
		xybits = v;
	}
	// NBitInt
	int ShapeSetup::getx() {
		return x;
	}
	void ShapeSetup::setx( int v ) {
		x = v;
	}
	// NBitInt
	int ShapeSetup::gety() {
		return y;
	}
	void ShapeSetup::sety( int v ) {
		y = v;
	}
	// NBitInt
	int ShapeSetup::getfillStyle0() {
		return fillStyle0;
	}
	void ShapeSetup::setfillStyle0( int v ) {
		fillStyle0 = v;
	}
	// NBitInt
	int ShapeSetup::getfillStyle1() {
		return fillStyle1;
	}
	void ShapeSetup::setfillStyle1( int v ) {
		fillStyle1 = v;
	}
	// NBitInt
	int ShapeSetup::getlineStyle() {
		return lineStyle;
	}
	void ShapeSetup::setlineStyle( int v ) {
		lineStyle = v;
	}
StyleList *ShapeSetup::getstyles() {
		return &styles;
	}
CurveTo::CurveTo() {
	bits = 0;
x1 = 0;
y1 = 0;
x2 = 0;
y2 = 0;
}
CurveTo::~CurveTo() {
}
CurveTo* CurveTo::get( Reader *r, int end, Context *ctx ) {
	CurveTo* ret = new CurveTo;
	ret->parse( r, end, ctx );
	return ret;
}
CurveTo* CurveTo::getByName( const char *name ) {
	if( strcmp( name, "CurveTo" ) ) return NULL;
	CurveTo* ret = new CurveTo;
	return ret;
}
	// Constant Size Primitive
	int CurveTo::getbits() {
		return bits;
	}
	void CurveTo::setbits( int v ) {
		bits = v;
	}
	// NBitInt
	int CurveTo::getx1() {
		return x1;
	}
	void CurveTo::setx1( int v ) {
		x1 = v;
	}
	// NBitInt
	int CurveTo::gety1() {
		return y1;
	}
	void CurveTo::sety1( int v ) {
		y1 = v;
	}
	// NBitInt
	int CurveTo::getx2() {
		return x2;
	}
	void CurveTo::setx2( int v ) {
		x2 = v;
	}
	// NBitInt
	int CurveTo::gety2() {
		return y2;
	}
	void CurveTo::sety2( int v ) {
		y2 = v;
	}
Shape::Shape() {
}
Shape::~Shape() {
}
Shape* Shape::get( Reader *r, int end, Context *ctx ) {
	Shape* ret = new Shape;
	ret->parse( r, end, ctx );
	return ret;
}
Shape* Shape::getByName( const char *name ) {
	if( strcmp( name, "Shape" ) ) return NULL;
	Shape* ret = new Shape;
	return ret;
}
List<ShapeItem> *Shape::getedges() {
		return &edges;
	}
GlyphShape::GlyphShape() {
	fillBits = 0;
lineBits = 0;
}
GlyphShape::~GlyphShape() {
}
GlyphShape* GlyphShape::get( Reader *r, int end, Context *ctx ) {
	GlyphShape* ret = new GlyphShape;
	ret->parse( r, end, ctx );
	return ret;
}
GlyphShape* GlyphShape::getByName( const char *name ) {
	if( strcmp( name, "GlyphShape" ) ) return NULL;
	GlyphShape* ret = new GlyphShape;
	return ret;
}
	// Constant Size Primitive
	int GlyphShape::getfillBits() {
		return fillBits;
	}
	void GlyphShape::setfillBits( int v ) {
		fillBits = v;
	}
	// Constant Size Primitive
	int GlyphShape::getlineBits() {
		return lineBits;
	}
	void GlyphShape::setlineBits( int v ) {
		lineBits = v;
	}
List<ShapeItem> *GlyphShape::getedges() {
		return &edges;
	}
GradientItem::GradientItem() {
	position = 0;
}
GradientItem::~GradientItem() {
}
GradientItem* GradientItem::get( Reader *r, int end, Context *ctx ) {
	GradientItem* ret = new GradientItem;
	ret->parse( r, end, ctx );
	return ret;
}
GradientItem* GradientItem::getByName( const char *name ) {
	if( strcmp( name, "GradientItem" ) ) return NULL;
	GradientItem* ret = new GradientItem;
	return ret;
}
	// Constant Size Primitive
	unsigned char GradientItem::getposition() {
		return position;
	}
	void GradientItem::setposition( unsigned char v ) {
		position = v;
	}
Color *GradientItem::getcolor() {
		return &color;
	}
Symbol::Symbol() {
	objectID = 0;
name = NULL;
}
Symbol::~Symbol() {
	delete[] name;
}
Symbol* Symbol::get( Reader *r, int end, Context *ctx ) {
	Symbol* ret = new Symbol;
	ret->parse( r, end, ctx );
	return ret;
}
Symbol* Symbol::getByName( const char *name ) {
	if( strcmp( name, "Symbol" ) ) return NULL;
	Symbol* ret = new Symbol;
	return ret;
}
	// Constant Size Primitive
	unsigned short Symbol::getobjectID() {
		return objectID;
	}
	void Symbol::setobjectID( unsigned short v ) {
		objectID = v;
	}
char * Symbol::getname() {
		return name;
	}
	void Symbol::setname( char * v ) {
		delete name;
		name = v;
	}
Frame::Frame() {
	number = 0;
label = NULL;
}
Frame::~Frame() {
	delete[] label;
}
Frame* Frame::get( Reader *r, int end, Context *ctx ) {
	Frame* ret = new Frame;
	ret->parse( r, end, ctx );
	return ret;
}
Frame* Frame::getByName( const char *name ) {
	if( strcmp( name, "Frame" ) ) return NULL;
	Frame* ret = new Frame;
	return ret;
}
	// Constant Size Primitive
	unsigned int Frame::getnumber() {
		return number;
	}
	void Frame::setnumber( unsigned int v ) {
		number = v;
	}
char * Frame::getlabel() {
		return label;
	}
	void Frame::setlabel( char * v ) {
		delete label;
		label = v;
	}
Scene::Scene() {
	offset = 0;
name = NULL;
}
Scene::~Scene() {
	delete[] name;
}
Scene* Scene::get( Reader *r, int end, Context *ctx ) {
	Scene* ret = new Scene;
	ret->parse( r, end, ctx );
	return ret;
}
Scene* Scene::getByName( const char *name ) {
	if( strcmp( name, "Scene" ) ) return NULL;
	Scene* ret = new Scene;
	return ret;
}
	// Constant Size Primitive
	unsigned int Scene::getoffset() {
		return offset;
	}
	void Scene::setoffset( unsigned int v ) {
		offset = v;
	}
char * Scene::getname() {
		return name;
	}
	void Scene::setname( char * v ) {
		delete name;
		name = v;
	}
Parameter::Parameter() {
	reg = 0;
name = NULL;
}
Parameter::~Parameter() {
	delete[] name;
}
Parameter* Parameter::get( Reader *r, int end, Context *ctx ) {
	Parameter* ret = new Parameter;
	ret->parse( r, end, ctx );
	return ret;
}
Parameter* Parameter::getByName( const char *name ) {
	if( strcmp( name, "Parameter" ) ) return NULL;
	Parameter* ret = new Parameter;
	return ret;
}
	// Constant Size Primitive
	unsigned char Parameter::getreg() {
		return reg;
	}
	void Parameter::setreg( unsigned char v ) {
		reg = v;
	}
char * Parameter::getname() {
		return name;
	}
	void Parameter::setname( char * v ) {
		delete name;
		name = v;
	}
UChar::UChar() {
	value = 0;
}
UChar::~UChar() {
}
UChar* UChar::get( Reader *r, int end, Context *ctx ) {
	UChar* ret = new UChar;
	ret->parse( r, end, ctx );
	return ret;
}
UChar* UChar::getByName( const char *name ) {
	if( strcmp( name, "UChar" ) ) return NULL;
	UChar* ret = new UChar;
	return ret;
}
	// Constant Size Primitive
	unsigned char UChar::getvalue() {
		return value;
	}
	void UChar::setvalue( unsigned char v ) {
		value = v;
	}
UShort::UShort() {
	value = 0;
}
UShort::~UShort() {
}
UShort* UShort::get( Reader *r, int end, Context *ctx ) {
	UShort* ret = new UShort;
	ret->parse( r, end, ctx );
	return ret;
}
UShort* UShort::getByName( const char *name ) {
	if( strcmp( name, "UShort" ) ) return NULL;
	UShort* ret = new UShort;
	return ret;
}
	// Constant Size Primitive
	unsigned short UShort::getvalue() {
		return value;
	}
	void UShort::setvalue( unsigned short v ) {
		value = v;
	}
ULong::ULong() {
	value = 0;
}
ULong::~ULong() {
}
ULong* ULong::get( Reader *r, int end, Context *ctx ) {
	ULong* ret = new ULong;
	ret->parse( r, end, ctx );
	return ret;
}
ULong* ULong::getByName( const char *name ) {
	if( strcmp( name, "ULong" ) ) return NULL;
	ULong* ret = new ULong;
	return ret;
}
	// Constant Size Primitive
	int ULong::getvalue() {
		return value;
	}
	void ULong::setvalue( int v ) {
		value = v;
	}
Short::Short() {
	value = 0;
}
Short::~Short() {
}
Short* Short::get( Reader *r, int end, Context *ctx ) {
	Short* ret = new Short;
	ret->parse( r, end, ctx );
	return ret;
}
Short* Short::getByName( const char *name ) {
	if( strcmp( name, "Short" ) ) return NULL;
	Short* ret = new Short;
	return ret;
}
	// Constant Size Primitive
	unsigned short Short::getvalue() {
		return value;
	}
	void Short::setvalue( unsigned short v ) {
		value = v;
	}
Float::Float() {
	value = 0;
}
Float::~Float() {
}
Float* Float::get( Reader *r, int end, Context *ctx ) {
	Float* ret = new Float;
	ret->parse( r, end, ctx );
	return ret;
}
Float* Float::getByName( const char *name ) {
	if( strcmp( name, "Float" ) ) return NULL;
	Float* ret = new Float;
	return ret;
}
Double::Double() {
	value = 0;
}
Double::~Double() {
}
Double* Double::get( Reader *r, int end, Context *ctx ) {
	Double* ret = new Double;
	ret->parse( r, end, ctx );
	return ret;
}
Double* Double::getByName( const char *name ) {
	if( strcmp( name, "Double" ) ) return NULL;
	Double* ret = new Double;
	return ret;
}
Kerning::Kerning() {
	a = 0;
b = 0;
adjustment = 0;
}
Kerning::~Kerning() {
}
Kerning* Kerning::get( Reader *r, int end, Context *ctx ) {
	Kerning* ret = new Kerning;
	ret->parse( r, end, ctx );
	return ret;
}
Kerning* Kerning::getByName( const char *name ) {
	if( strcmp( name, "Kerning" ) ) return NULL;
	Kerning* ret = new Kerning;
	return ret;
}
	// Constant Size Primitive
	unsigned char Kerning::geta() {
		return a;
	}
	void Kerning::seta( unsigned char v ) {
		a = v;
	}
	// Constant Size Primitive
	unsigned char Kerning::getb() {
		return b;
	}
	void Kerning::setb( unsigned char v ) {
		b = v;
	}
	// Constant Size Primitive
	int Kerning::getadjustment() {
		return adjustment;
	}
	void Kerning::setadjustment( int v ) {
		adjustment = v;
	}
WideKerning::WideKerning() {
	a = 0;
b = 0;
adjustment = 0;
}
WideKerning::~WideKerning() {
}
WideKerning* WideKerning::get( Reader *r, int end, Context *ctx ) {
	WideKerning* ret = new WideKerning;
	ret->parse( r, end, ctx );
	return ret;
}
WideKerning* WideKerning::getByName( const char *name ) {
	if( strcmp( name, "WideKerning" ) ) return NULL;
	WideKerning* ret = new WideKerning;
	return ret;
}
	// Constant Size Primitive
	unsigned short WideKerning::geta() {
		return a;
	}
	void WideKerning::seta( unsigned short v ) {
		a = v;
	}
	// Constant Size Primitive
	unsigned short WideKerning::getb() {
		return b;
	}
	void WideKerning::setb( unsigned short v ) {
		b = v;
	}
	// Constant Size Primitive
	unsigned short WideKerning::getadjustment() {
		return adjustment;
	}
	void WideKerning::setadjustment( unsigned short v ) {
		adjustment = v;
	}
TextEntry::TextEntry() {
	glyph = 0;
advance = 0;
}
TextEntry::~TextEntry() {
}
TextEntry* TextEntry::get( Reader *r, int end, Context *ctx ) {
	TextEntry* ret = new TextEntry;
	ret->parse( r, end, ctx );
	return ret;
}
TextEntry* TextEntry::getByName( const char *name ) {
	if( strcmp( name, "TextEntry" ) ) return NULL;
	TextEntry* ret = new TextEntry;
	return ret;
}
	// NBitInt
	int TextEntry::getglyph() {
		return glyph;
	}
	void TextEntry::setglyph( int v ) {
		glyph = v;
	}
	// NBitInt
	int TextEntry::getadvance() {
		return advance;
	}
	void TextEntry::setadvance( int v ) {
		advance = v;
	}
TextEntry2::TextEntry2() {
	glyph = 0;
advance = 0;
}
TextEntry2::~TextEntry2() {
}
TextEntry2* TextEntry2::get( Reader *r, int end, Context *ctx ) {
	TextEntry2* ret = new TextEntry2;
	ret->parse( r, end, ctx );
	return ret;
}
TextEntry2* TextEntry2::getByName( const char *name ) {
	if( strcmp( name, "TextEntry2" ) ) return NULL;
	TextEntry2* ret = new TextEntry2;
	return ret;
}
	// NBitInt
	int TextEntry2::getglyph() {
		return glyph;
	}
	void TextEntry2::setglyph( int v ) {
		glyph = v;
	}
	// NBitInt
	int TextEntry2::getadvance() {
		return advance;
	}
	void TextEntry2::setadvance( int v ) {
		advance = v;
	}
TextRecord6::TextRecord6() {
	isSetup = 0;
reserved = 0;
hasFont = 0;
hasColor = 0;
hasMoveY = 0;
hasMoveX = 0;
objectID = 0;
x = 0;
y = 0;
fontHeight = 0;
nGlyphs = 0;
}
TextRecord6::~TextRecord6() {
}
TextRecord6* TextRecord6::get( Reader *r, int end, Context *ctx ) {
	TextRecord6* ret = new TextRecord6;
	ret->parse( r, end, ctx );
	return ret;
}
TextRecord6* TextRecord6::getByName( const char *name ) {
	if( strcmp( name, "TextRecord6" ) ) return NULL;
	TextRecord6* ret = new TextRecord6;
	return ret;
}
	// Constant Size Primitive
	bool TextRecord6::getisSetup() {
		return isSetup;
	}
	void TextRecord6::setisSetup( bool v ) {
		isSetup = v;
	}
	// Constant Size Primitive
	int TextRecord6::getreserved() {
		return reserved;
	}
	void TextRecord6::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool TextRecord6::gethasFont() {
		return hasFont;
	}
	void TextRecord6::sethasFont( bool v ) {
		hasFont = v;
	}
	// Constant Size Primitive
	bool TextRecord6::gethasColor() {
		return hasColor;
	}
	void TextRecord6::sethasColor( bool v ) {
		hasColor = v;
	}
	// Constant Size Primitive
	bool TextRecord6::gethasMoveY() {
		return hasMoveY;
	}
	void TextRecord6::sethasMoveY( bool v ) {
		hasMoveY = v;
	}
	// Constant Size Primitive
	bool TextRecord6::gethasMoveX() {
		return hasMoveX;
	}
	void TextRecord6::sethasMoveX( bool v ) {
		hasMoveX = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord6::getobjectID() {
		return objectID;
	}
	void TextRecord6::setobjectID( unsigned short v ) {
		objectID = v;
	}
Color *TextRecord6::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	unsigned short TextRecord6::getx() {
		return x;
	}
	void TextRecord6::setx( unsigned short v ) {
		x = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord6::gety() {
		return y;
	}
	void TextRecord6::sety( unsigned short v ) {
		y = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord6::getfontHeight() {
		return fontHeight;
	}
	void TextRecord6::setfontHeight( unsigned short v ) {
		fontHeight = v;
	}
	// Constant Size Primitive
	int TextRecord6::getnGlyphs() {
		return nGlyphs;
	}
	void TextRecord6::setnGlyphs( int v ) {
		nGlyphs = v;
	}
List<TextEntry> *TextRecord6::getglyphs() {
		return &glyphs;
	}
TextRecord62::TextRecord62() {
	isSetup = 0;
reserved = 0;
hasFont = 0;
hasColor = 0;
hasMoveY = 0;
hasMoveX = 0;
objectID = 0;
x = 0;
y = 0;
fontHeight = 0;
nGlyphs = 0;
}
TextRecord62::~TextRecord62() {
}
TextRecord62* TextRecord62::get( Reader *r, int end, Context *ctx ) {
	TextRecord62* ret = new TextRecord62;
	ret->parse( r, end, ctx );
	return ret;
}
TextRecord62* TextRecord62::getByName( const char *name ) {
	if( strcmp( name, "TextRecord62" ) ) return NULL;
	TextRecord62* ret = new TextRecord62;
	return ret;
}
	// Constant Size Primitive
	bool TextRecord62::getisSetup() {
		return isSetup;
	}
	void TextRecord62::setisSetup( bool v ) {
		isSetup = v;
	}
	// Constant Size Primitive
	int TextRecord62::getreserved() {
		return reserved;
	}
	void TextRecord62::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool TextRecord62::gethasFont() {
		return hasFont;
	}
	void TextRecord62::sethasFont( bool v ) {
		hasFont = v;
	}
	// Constant Size Primitive
	bool TextRecord62::gethasColor() {
		return hasColor;
	}
	void TextRecord62::sethasColor( bool v ) {
		hasColor = v;
	}
	// Constant Size Primitive
	bool TextRecord62::gethasMoveY() {
		return hasMoveY;
	}
	void TextRecord62::sethasMoveY( bool v ) {
		hasMoveY = v;
	}
	// Constant Size Primitive
	bool TextRecord62::gethasMoveX() {
		return hasMoveX;
	}
	void TextRecord62::sethasMoveX( bool v ) {
		hasMoveX = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord62::getobjectID() {
		return objectID;
	}
	void TextRecord62::setobjectID( unsigned short v ) {
		objectID = v;
	}
Color *TextRecord62::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	unsigned short TextRecord62::getx() {
		return x;
	}
	void TextRecord62::setx( unsigned short v ) {
		x = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord62::gety() {
		return y;
	}
	void TextRecord62::sety( unsigned short v ) {
		y = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord62::getfontHeight() {
		return fontHeight;
	}
	void TextRecord62::setfontHeight( unsigned short v ) {
		fontHeight = v;
	}
	// Constant Size Primitive
	int TextRecord62::getnGlyphs() {
		return nGlyphs;
	}
	void TextRecord62::setnGlyphs( int v ) {
		nGlyphs = v;
	}
List<TextEntry2> *TextRecord62::getglyphs() {
		return &glyphs;
	}
TextRecord7::TextRecord7() {
	isSetup = 0;
reserved = 0;
hasFont = 0;
hasColor = 0;
hasMoveY = 0;
hasMoveX = 0;
objectID = 0;
x = 0;
y = 0;
fontHeight = 0;
nGlyphs = 0;
}
TextRecord7::~TextRecord7() {
}
TextRecord7* TextRecord7::get( Reader *r, int end, Context *ctx ) {
	TextRecord7* ret = new TextRecord7;
	ret->parse( r, end, ctx );
	return ret;
}
TextRecord7* TextRecord7::getByName( const char *name ) {
	if( strcmp( name, "TextRecord7" ) ) return NULL;
	TextRecord7* ret = new TextRecord7;
	return ret;
}
	// Constant Size Primitive
	bool TextRecord7::getisSetup() {
		return isSetup;
	}
	void TextRecord7::setisSetup( bool v ) {
		isSetup = v;
	}
	// Constant Size Primitive
	int TextRecord7::getreserved() {
		return reserved;
	}
	void TextRecord7::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool TextRecord7::gethasFont() {
		return hasFont;
	}
	void TextRecord7::sethasFont( bool v ) {
		hasFont = v;
	}
	// Constant Size Primitive
	bool TextRecord7::gethasColor() {
		return hasColor;
	}
	void TextRecord7::sethasColor( bool v ) {
		hasColor = v;
	}
	// Constant Size Primitive
	bool TextRecord7::gethasMoveY() {
		return hasMoveY;
	}
	void TextRecord7::sethasMoveY( bool v ) {
		hasMoveY = v;
	}
	// Constant Size Primitive
	bool TextRecord7::gethasMoveX() {
		return hasMoveX;
	}
	void TextRecord7::sethasMoveX( bool v ) {
		hasMoveX = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord7::getobjectID() {
		return objectID;
	}
	void TextRecord7::setobjectID( unsigned short v ) {
		objectID = v;
	}
Color *TextRecord7::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	unsigned short TextRecord7::getx() {
		return x;
	}
	void TextRecord7::setx( unsigned short v ) {
		x = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord7::gety() {
		return y;
	}
	void TextRecord7::sety( unsigned short v ) {
		y = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord7::getfontHeight() {
		return fontHeight;
	}
	void TextRecord7::setfontHeight( unsigned short v ) {
		fontHeight = v;
	}
	// Constant Size Primitive
	unsigned char TextRecord7::getnGlyphs() {
		return nGlyphs;
	}
	void TextRecord7::setnGlyphs( unsigned char v ) {
		nGlyphs = v;
	}
List<TextEntry> *TextRecord7::getglyphs() {
		return &glyphs;
	}
TextRecord72::TextRecord72() {
	isSetup = 0;
reserved = 0;
hasFont = 0;
hasColor = 0;
hasMoveY = 0;
hasMoveX = 0;
fontRef = 0;
x = 0;
y = 0;
fontHeight = 0;
nGlyphs = 0;
}
TextRecord72::~TextRecord72() {
}
TextRecord72* TextRecord72::get( Reader *r, int end, Context *ctx ) {
	TextRecord72* ret = new TextRecord72;
	ret->parse( r, end, ctx );
	return ret;
}
TextRecord72* TextRecord72::getByName( const char *name ) {
	if( strcmp( name, "TextRecord72" ) ) return NULL;
	TextRecord72* ret = new TextRecord72;
	return ret;
}
	// Constant Size Primitive
	bool TextRecord72::getisSetup() {
		return isSetup;
	}
	void TextRecord72::setisSetup( bool v ) {
		isSetup = v;
	}
	// Constant Size Primitive
	int TextRecord72::getreserved() {
		return reserved;
	}
	void TextRecord72::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool TextRecord72::gethasFont() {
		return hasFont;
	}
	void TextRecord72::sethasFont( bool v ) {
		hasFont = v;
	}
	// Constant Size Primitive
	bool TextRecord72::gethasColor() {
		return hasColor;
	}
	void TextRecord72::sethasColor( bool v ) {
		hasColor = v;
	}
	// Constant Size Primitive
	bool TextRecord72::gethasMoveY() {
		return hasMoveY;
	}
	void TextRecord72::sethasMoveY( bool v ) {
		hasMoveY = v;
	}
	// Constant Size Primitive
	bool TextRecord72::gethasMoveX() {
		return hasMoveX;
	}
	void TextRecord72::sethasMoveX( bool v ) {
		hasMoveX = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord72::getfontRef() {
		return fontRef;
	}
	void TextRecord72::setfontRef( unsigned short v ) {
		fontRef = v;
	}
Color *TextRecord72::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	unsigned short TextRecord72::getx() {
		return x;
	}
	void TextRecord72::setx( unsigned short v ) {
		x = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord72::gety() {
		return y;
	}
	void TextRecord72::sety( unsigned short v ) {
		y = v;
	}
	// Constant Size Primitive
	unsigned short TextRecord72::getfontHeight() {
		return fontHeight;
	}
	void TextRecord72::setfontHeight( unsigned short v ) {
		fontHeight = v;
	}
	// Constant Size Primitive
	unsigned char TextRecord72::getnGlyphs() {
		return nGlyphs;
	}
	void TextRecord72::setnGlyphs( unsigned char v ) {
		nGlyphs = v;
	}
List<TextEntry2> *TextRecord72::getglyphs() {
		return &glyphs;
	}
TextRecord::TextRecord() {
}
TextRecord::~TextRecord() {
}
TextRecord* TextRecord::get( Reader *r, int end, Context *ctx ) {
	TextRecord* ret = new TextRecord;
	ret->parse( r, end, ctx );
	return ret;
}
TextRecord* TextRecord::getByName( const char *name ) {
	if( strcmp( name, "TextRecord" ) ) return NULL;
	TextRecord* ret = new TextRecord;
	return ret;
}
List<TextRecord6> *TextRecord::getrecords() {
		return &records;
	}
TextRecord7 *TextRecord::getstring() {
		return &string;
	}
TextRecord2::TextRecord2() {
}
TextRecord2::~TextRecord2() {
}
TextRecord2* TextRecord2::get( Reader *r, int end, Context *ctx ) {
	TextRecord2* ret = new TextRecord2;
	ret->parse( r, end, ctx );
	return ret;
}
TextRecord2* TextRecord2::getByName( const char *name ) {
	if( strcmp( name, "TextRecord2" ) ) return NULL;
	TextRecord2* ret = new TextRecord2;
	return ret;
}
List<TextRecord62> *TextRecord2::getrecords() {
		return &records;
	}
TextRecord72 *TextRecord2::gettextString() {
		return &textString;
	}
Button::Button() {
	reserved1 = 0;
reserved2 = 0;
hasBlendMode = 0;
hasFilterList = 0;
hitTest = 0;
down = 0;
over = 0;
up = 0;
objectID = 0;
depth = 0;
numFilters = 0;
blendMode = 0;
}
Button::~Button() {
}
Button* Button::get( Reader *r, int end, Context *ctx ) {
	Button* ret = new Button;
	ret->parse( r, end, ctx );
	return ret;
}
Button* Button::getByName( const char *name ) {
	if( strcmp( name, "Button" ) ) return NULL;
	Button* ret = new Button;
	return ret;
}
	// Constant Size Primitive
	int Button::getreserved1() {
		return reserved1;
	}
	void Button::setreserved1( int v ) {
		reserved1 = v;
	}
	// Constant Size Primitive
	int Button::getreserved2() {
		return reserved2;
	}
	void Button::setreserved2( int v ) {
		reserved2 = v;
	}
	// Constant Size Primitive
	bool Button::gethasBlendMode() {
		return hasBlendMode;
	}
	void Button::sethasBlendMode( bool v ) {
		hasBlendMode = v;
	}
	// Constant Size Primitive
	bool Button::gethasFilterList() {
		return hasFilterList;
	}
	void Button::sethasFilterList( bool v ) {
		hasFilterList = v;
	}
	// Constant Size Primitive
	bool Button::gethitTest() {
		return hitTest;
	}
	void Button::sethitTest( bool v ) {
		hitTest = v;
	}
	// Constant Size Primitive
	bool Button::getdown() {
		return down;
	}
	void Button::setdown( bool v ) {
		down = v;
	}
	// Constant Size Primitive
	bool Button::getover() {
		return over;
	}
	void Button::setover( bool v ) {
		over = v;
	}
	// Constant Size Primitive
	bool Button::getup() {
		return up;
	}
	void Button::setup( bool v ) {
		up = v;
	}
	// Constant Size Primitive
	unsigned short Button::getobjectID() {
		return objectID;
	}
	void Button::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned short Button::getdepth() {
		return depth;
	}
	void Button::setdepth( unsigned short v ) {
		depth = v;
	}
Transform *Button::gettransform() {
		return &transform;
	}
ColorTransform2 *Button::getcolorTransform() {
		return &colorTransform;
	}
	// Constant Size Primitive
	unsigned char Button::getnumFilters() {
		return numFilters;
	}
	void Button::setnumFilters( unsigned char v ) {
		numFilters = v;
	}
List<Filter> *Button::getfilters() {
		return &filters;
	}
	// Constant Size Primitive
	unsigned char Button::getblendMode() {
		return blendMode;
	}
	void Button::setblendMode( unsigned char v ) {
		blendMode = v;
	}
Event::Event() {
	flags1 = 0;
flags2 = 0;
actionLength = 0;
}
Event::~Event() {
}
Event* Event::get( Reader *r, int end, Context *ctx ) {
	Event* ret = new Event;
	ret->parse( r, end, ctx );
	return ret;
}
Event* Event::getByName( const char *name ) {
	if( strcmp( name, "Event" ) ) return NULL;
	Event* ret = new Event;
	return ret;
}
	// Constant Size Primitive
	unsigned short Event::getflags1() {
		return flags1;
	}
	void Event::setflags1( unsigned short v ) {
		flags1 = v;
	}
	// Constant Size Primitive
	unsigned short Event::getflags2() {
		return flags2;
	}
	void Event::setflags2( unsigned short v ) {
		flags2 = v;
	}
	// Constant Size Primitive
	unsigned int Event::getactionLength() {
		return actionLength;
	}
	void Event::setactionLength( unsigned int v ) {
		actionLength = v;
	}
List<Action> *Event::getactions() {
		return &actions;
	}
Condition::Condition() {
	next = 0;
menuEnter = 0;
pointerReleaseOutside = 0;
pointerDragEnter = 0;
pointerDragLeave = 0;
pointerReleaseInside = 0;
pointerPush = 0;
pointerLeave = 0;
pointerEnter = 0;
key = 0;
menuLeave = 0;
}
Condition::~Condition() {
}
Condition* Condition::get( Reader *r, int end, Context *ctx ) {
	Condition* ret = new Condition;
	ret->parse( r, end, ctx );
	return ret;
}
Condition* Condition::getByName( const char *name ) {
	if( strcmp( name, "Condition" ) ) return NULL;
	Condition* ret = new Condition;
	return ret;
}
	// Constant Size Primitive
	unsigned short Condition::getnext() {
		return next;
	}
	void Condition::setnext( unsigned short v ) {
		next = v;
	}
	// Constant Size Primitive
	bool Condition::getmenuEnter() {
		return menuEnter;
	}
	void Condition::setmenuEnter( bool v ) {
		menuEnter = v;
	}
	// Constant Size Primitive
	bool Condition::getpointerReleaseOutside() {
		return pointerReleaseOutside;
	}
	void Condition::setpointerReleaseOutside( bool v ) {
		pointerReleaseOutside = v;
	}
	// Constant Size Primitive
	bool Condition::getpointerDragEnter() {
		return pointerDragEnter;
	}
	void Condition::setpointerDragEnter( bool v ) {
		pointerDragEnter = v;
	}
	// Constant Size Primitive
	bool Condition::getpointerDragLeave() {
		return pointerDragLeave;
	}
	void Condition::setpointerDragLeave( bool v ) {
		pointerDragLeave = v;
	}
	// Constant Size Primitive
	bool Condition::getpointerReleaseInside() {
		return pointerReleaseInside;
	}
	void Condition::setpointerReleaseInside( bool v ) {
		pointerReleaseInside = v;
	}
	// Constant Size Primitive
	bool Condition::getpointerPush() {
		return pointerPush;
	}
	void Condition::setpointerPush( bool v ) {
		pointerPush = v;
	}
	// Constant Size Primitive
	bool Condition::getpointerLeave() {
		return pointerLeave;
	}
	void Condition::setpointerLeave( bool v ) {
		pointerLeave = v;
	}
	// Constant Size Primitive
	bool Condition::getpointerEnter() {
		return pointerEnter;
	}
	void Condition::setpointerEnter( bool v ) {
		pointerEnter = v;
	}
	// Constant Size Primitive
	int Condition::getkey() {
		return key;
	}
	void Condition::setkey( int v ) {
		key = v;
	}
	// Constant Size Primitive
	bool Condition::getmenuLeave() {
		return menuLeave;
	}
	void Condition::setmenuLeave( bool v ) {
		menuLeave = v;
	}
List<Action> *Condition::getactions() {
		return &actions;
	}
U30::U30() {
	value = 0;
}
U30::~U30() {
}
U30* U30::get( Reader *r, int end, Context *ctx ) {
	U30* ret = new U30;
	ret->parse( r, end, ctx );
	return ret;
}
U30* U30::getByName( const char *name ) {
	if( strcmp( name, "U30" ) ) return NULL;
	U30* ret = new U30;
	return ret;
}
	// Constant Size Primitive
	unsigned int U30::getvalue() {
		return value;
	}
	void U30::setvalue( unsigned int v ) {
		value = v;
	}
S24::S24() {
	value = 0;
}
S24::~S24() {
}
S24* S24::get( Reader *r, int end, Context *ctx ) {
	S24* ret = new S24;
	ret->parse( r, end, ctx );
	return ret;
}
S24* S24::getByName( const char *name ) {
	if( strcmp( name, "S24" ) ) return NULL;
	S24* ret = new S24;
	return ret;
}
	// Constant Size Primitive
	int S24::getvalue() {
		return value;
	}
	void S24::setvalue( int v ) {
		value = v;
	}
ValueKind::ValueKind() {
	index = 0;
kind = 0;
}
ValueKind::~ValueKind() {
}
ValueKind* ValueKind::get( Reader *r, int end, Context *ctx ) {
	ValueKind* ret = new ValueKind;
	ret->parse( r, end, ctx );
	return ret;
}
ValueKind* ValueKind::getByName( const char *name ) {
	if( strcmp( name, "ValueKind" ) ) return NULL;
	ValueKind* ret = new ValueKind;
	return ret;
}
	// Constant Size Primitive
	unsigned int ValueKind::getindex() {
		return index;
	}
	void ValueKind::setindex( unsigned int v ) {
		index = v;
	}
	// Constant Size Primitive
	unsigned char ValueKind::getkind() {
		return kind;
	}
	void ValueKind::setkind( unsigned char v ) {
		kind = v;
	}
MethodInfo::MethodInfo() {
	paramCount = 0;
retType = 0;
nameIndex = 0;
hasParamNames = 0;
setSDXNs = 0;
isExplicit = 0;
ignoreRest = 0;
hasOptional = 0;
needRest = 0;
needActivation = 0;
needArguments = 0;
optionalCount = 0;
}
MethodInfo::~MethodInfo() {
}
MethodInfo* MethodInfo::get( Reader *r, int end, Context *ctx ) {
	MethodInfo* ret = new MethodInfo;
	ret->parse( r, end, ctx );
	return ret;
}
MethodInfo* MethodInfo::getByName( const char *name ) {
	if( strcmp( name, "MethodInfo" ) ) return NULL;
	MethodInfo* ret = new MethodInfo;
	return ret;
}
	// Constant Size Primitive
	unsigned int MethodInfo::getparamCount() {
		return paramCount;
	}
	void MethodInfo::setparamCount( unsigned int v ) {
		paramCount = v;
	}
	// Constant Size Primitive
	unsigned int MethodInfo::getretType() {
		return retType;
	}
	void MethodInfo::setretType( unsigned int v ) {
		retType = v;
	}
List<U30> *MethodInfo::getparamTypes() {
		return &paramTypes;
	}
	// Constant Size Primitive
	unsigned int MethodInfo::getnameIndex() {
		return nameIndex;
	}
	void MethodInfo::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
	// Constant Size Primitive
	bool MethodInfo::gethasParamNames() {
		return hasParamNames;
	}
	void MethodInfo::sethasParamNames( bool v ) {
		hasParamNames = v;
	}
	// Constant Size Primitive
	bool MethodInfo::getsetSDXNs() {
		return setSDXNs;
	}
	void MethodInfo::setsetSDXNs( bool v ) {
		setSDXNs = v;
	}
	// Constant Size Primitive
	bool MethodInfo::getisExplicit() {
		return isExplicit;
	}
	void MethodInfo::setisExplicit( bool v ) {
		isExplicit = v;
	}
	// Constant Size Primitive
	bool MethodInfo::getignoreRest() {
		return ignoreRest;
	}
	void MethodInfo::setignoreRest( bool v ) {
		ignoreRest = v;
	}
	// Constant Size Primitive
	bool MethodInfo::gethasOptional() {
		return hasOptional;
	}
	void MethodInfo::sethasOptional( bool v ) {
		hasOptional = v;
	}
	// Constant Size Primitive
	bool MethodInfo::getneedRest() {
		return needRest;
	}
	void MethodInfo::setneedRest( bool v ) {
		needRest = v;
	}
	// Constant Size Primitive
	bool MethodInfo::getneedActivation() {
		return needActivation;
	}
	void MethodInfo::setneedActivation( bool v ) {
		needActivation = v;
	}
	// Constant Size Primitive
	bool MethodInfo::getneedArguments() {
		return needArguments;
	}
	void MethodInfo::setneedArguments( bool v ) {
		needArguments = v;
	}
	// Constant Size Primitive
	unsigned int MethodInfo::getoptionalCount() {
		return optionalCount;
	}
	void MethodInfo::setoptionalCount( unsigned int v ) {
		optionalCount = v;
	}
List<ValueKind> *MethodInfo::getoptional() {
		return &optional;
	}
List<U30> *MethodInfo::getparamNames() {
		return &paramNames;
	}
MetadataInfo::MetadataInfo() {
	nameIndex = 0;
valuesCount = 0;
}
MetadataInfo::~MetadataInfo() {
}
MetadataInfo* MetadataInfo::get( Reader *r, int end, Context *ctx ) {
	MetadataInfo* ret = new MetadataInfo;
	ret->parse( r, end, ctx );
	return ret;
}
MetadataInfo* MetadataInfo::getByName( const char *name ) {
	if( strcmp( name, "MetadataInfo" ) ) return NULL;
	MetadataInfo* ret = new MetadataInfo;
	return ret;
}
	// Constant Size Primitive
	unsigned int MetadataInfo::getnameIndex() {
		return nameIndex;
	}
	void MetadataInfo::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
	// Constant Size Primitive
	unsigned int MetadataInfo::getvaluesCount() {
		return valuesCount;
	}
	void MetadataInfo::setvaluesCount( unsigned int v ) {
		valuesCount = v;
	}
List<U30> *MetadataInfo::getkeys() {
		return &keys;
	}
List<U30> *MetadataInfo::getvalues() {
		return &values;
	}
NamespaceSet::NamespaceSet() {
	count = 0;
}
NamespaceSet::~NamespaceSet() {
}
NamespaceSet* NamespaceSet::get( Reader *r, int end, Context *ctx ) {
	NamespaceSet* ret = new NamespaceSet;
	ret->parse( r, end, ctx );
	return ret;
}
NamespaceSet* NamespaceSet::getByName( const char *name ) {
	if( strcmp( name, "NamespaceSet" ) ) return NULL;
	NamespaceSet* ret = new NamespaceSet;
	return ret;
}
	// Constant Size Primitive
	unsigned int NamespaceSet::getcount() {
		return count;
	}
	void NamespaceSet::setcount( unsigned int v ) {
		count = v;
	}
List<U30> *NamespaceSet::getnamespaces() {
		return &namespaces;
	}
TraitInfo::TraitInfo() {
	nameIndex = 0;
reserved = 0;
hasMetadata = 0;
override = 0;
final = 0;
metadataCount = 0;
}
TraitInfo::~TraitInfo() {
}
TraitInfo* TraitInfo::get( Reader *r, int end, Context *ctx ) {
	TraitInfo* ret = new TraitInfo;
	ret->parse( r, end, ctx );
	return ret;
}
TraitInfo* TraitInfo::getByName( const char *name ) {
	if( strcmp( name, "TraitInfo" ) ) return NULL;
	TraitInfo* ret = new TraitInfo;
	return ret;
}
	// Constant Size Primitive
	unsigned int TraitInfo::getnameIndex() {
		return nameIndex;
	}
	void TraitInfo::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
	// Constant Size Primitive
	bool TraitInfo::getreserved() {
		return reserved;
	}
	void TraitInfo::setreserved( bool v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool TraitInfo::gethasMetadata() {
		return hasMetadata;
	}
	void TraitInfo::sethasMetadata( bool v ) {
		hasMetadata = v;
	}
	// Constant Size Primitive
	bool TraitInfo::getoverride() {
		return override;
	}
	void TraitInfo::setoverride( bool v ) {
		override = v;
	}
	// Constant Size Primitive
	bool TraitInfo::getfinal() {
		return final;
	}
	void TraitInfo::setfinal( bool v ) {
		final = v;
	}
List<Trait> *TraitInfo::gettrait() {
		return &trait;
	}
	// Constant Size Primitive
	unsigned int TraitInfo::getmetadataCount() {
		return metadataCount;
	}
	void TraitInfo::setmetadataCount( unsigned int v ) {
		metadataCount = v;
	}
List<U30> *TraitInfo::getmetadata() {
		return &metadata;
	}
InstanceInfo::InstanceInfo() {
	nameIndex = 0;
superIndex = 0;
reserved = 0;
hasProtectedNS = 0;
interface = 0;
final = 0;
sealed = 0;
protectedNS = 0;
interfaceCount = 0;
iInitIndex = 0;
traitCount = 0;
}
InstanceInfo::~InstanceInfo() {
}
InstanceInfo* InstanceInfo::get( Reader *r, int end, Context *ctx ) {
	InstanceInfo* ret = new InstanceInfo;
	ret->parse( r, end, ctx );
	return ret;
}
InstanceInfo* InstanceInfo::getByName( const char *name ) {
	if( strcmp( name, "InstanceInfo" ) ) return NULL;
	InstanceInfo* ret = new InstanceInfo;
	return ret;
}
	// Constant Size Primitive
	unsigned int InstanceInfo::getnameIndex() {
		return nameIndex;
	}
	void InstanceInfo::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
	// Constant Size Primitive
	unsigned int InstanceInfo::getsuperIndex() {
		return superIndex;
	}
	void InstanceInfo::setsuperIndex( unsigned int v ) {
		superIndex = v;
	}
	// Constant Size Primitive
	int InstanceInfo::getreserved() {
		return reserved;
	}
	void InstanceInfo::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool InstanceInfo::gethasProtectedNS() {
		return hasProtectedNS;
	}
	void InstanceInfo::sethasProtectedNS( bool v ) {
		hasProtectedNS = v;
	}
	// Constant Size Primitive
	bool InstanceInfo::getinterface() {
		return interface;
	}
	void InstanceInfo::setinterface( bool v ) {
		interface = v;
	}
	// Constant Size Primitive
	bool InstanceInfo::getfinal() {
		return final;
	}
	void InstanceInfo::setfinal( bool v ) {
		final = v;
	}
	// Constant Size Primitive
	bool InstanceInfo::getsealed() {
		return sealed;
	}
	void InstanceInfo::setsealed( bool v ) {
		sealed = v;
	}
	// Constant Size Primitive
	unsigned int InstanceInfo::getprotectedNS() {
		return protectedNS;
	}
	void InstanceInfo::setprotectedNS( unsigned int v ) {
		protectedNS = v;
	}
	// Constant Size Primitive
	unsigned int InstanceInfo::getinterfaceCount() {
		return interfaceCount;
	}
	void InstanceInfo::setinterfaceCount( unsigned int v ) {
		interfaceCount = v;
	}
List<U30> *InstanceInfo::getinterfaces() {
		return &interfaces;
	}
	// Constant Size Primitive
	unsigned int InstanceInfo::getiInitIndex() {
		return iInitIndex;
	}
	void InstanceInfo::setiInitIndex( unsigned int v ) {
		iInitIndex = v;
	}
	// Constant Size Primitive
	unsigned int InstanceInfo::gettraitCount() {
		return traitCount;
	}
	void InstanceInfo::settraitCount( unsigned int v ) {
		traitCount = v;
	}
List<TraitInfo> *InstanceInfo::gettraits() {
		return &traits;
	}
ClassInfo::ClassInfo() {
	cInitIndex = 0;
traitCount = 0;
}
ClassInfo::~ClassInfo() {
}
ClassInfo* ClassInfo::get( Reader *r, int end, Context *ctx ) {
	ClassInfo* ret = new ClassInfo;
	ret->parse( r, end, ctx );
	return ret;
}
ClassInfo* ClassInfo::getByName( const char *name ) {
	if( strcmp( name, "ClassInfo" ) ) return NULL;
	ClassInfo* ret = new ClassInfo;
	return ret;
}
	// Constant Size Primitive
	unsigned int ClassInfo::getcInitIndex() {
		return cInitIndex;
	}
	void ClassInfo::setcInitIndex( unsigned int v ) {
		cInitIndex = v;
	}
	// Constant Size Primitive
	unsigned int ClassInfo::gettraitCount() {
		return traitCount;
	}
	void ClassInfo::settraitCount( unsigned int v ) {
		traitCount = v;
	}
List<TraitInfo> *ClassInfo::gettraits() {
		return &traits;
	}
ScriptInfo::ScriptInfo() {
	initIndex = 0;
traitCount = 0;
}
ScriptInfo::~ScriptInfo() {
}
ScriptInfo* ScriptInfo::get( Reader *r, int end, Context *ctx ) {
	ScriptInfo* ret = new ScriptInfo;
	ret->parse( r, end, ctx );
	return ret;
}
ScriptInfo* ScriptInfo::getByName( const char *name ) {
	if( strcmp( name, "ScriptInfo" ) ) return NULL;
	ScriptInfo* ret = new ScriptInfo;
	return ret;
}
	// Constant Size Primitive
	unsigned int ScriptInfo::getinitIndex() {
		return initIndex;
	}
	void ScriptInfo::setinitIndex( unsigned int v ) {
		initIndex = v;
	}
	// Constant Size Primitive
	unsigned int ScriptInfo::gettraitCount() {
		return traitCount;
	}
	void ScriptInfo::settraitCount( unsigned int v ) {
		traitCount = v;
	}
List<TraitInfo> *ScriptInfo::gettraits() {
		return &traits;
	}
Exception::Exception() {
	tryStart = 0;
tryEnd = 0;
target = 0;
type = 0;
name = 0;
}
Exception::~Exception() {
}
Exception* Exception::get( Reader *r, int end, Context *ctx ) {
	Exception* ret = new Exception;
	ret->parse( r, end, ctx );
	return ret;
}
Exception* Exception::getByName( const char *name ) {
	if( strcmp( name, "Exception" ) ) return NULL;
	Exception* ret = new Exception;
	return ret;
}
	// Constant Size Primitive
	unsigned int Exception::gettryStart() {
		return tryStart;
	}
	void Exception::settryStart( unsigned int v ) {
		tryStart = v;
	}
	// Constant Size Primitive
	unsigned int Exception::gettryEnd() {
		return tryEnd;
	}
	void Exception::settryEnd( unsigned int v ) {
		tryEnd = v;
	}
	// Constant Size Primitive
	unsigned int Exception::gettarget() {
		return target;
	}
	void Exception::settarget( unsigned int v ) {
		target = v;
	}
	// Constant Size Primitive
	unsigned int Exception::gettype() {
		return type;
	}
	void Exception::settype( unsigned int v ) {
		type = v;
	}
	// Constant Size Primitive
	unsigned int Exception::getname() {
		return name;
	}
	void Exception::setname( unsigned int v ) {
		name = v;
	}
MethodBody::MethodBody() {
	methodInfo = 0;
maxStack = 0;
maxRegs = 0;
scopeDepth = 0;
maxScope = 0;
codeLength = 0;
exceptionCount = 0;
traitCount = 0;
}
MethodBody::~MethodBody() {
}
MethodBody* MethodBody::get( Reader *r, int end, Context *ctx ) {
	MethodBody* ret = new MethodBody;
	ret->parse( r, end, ctx );
	return ret;
}
MethodBody* MethodBody::getByName( const char *name ) {
	if( strcmp( name, "MethodBody" ) ) return NULL;
	MethodBody* ret = new MethodBody;
	return ret;
}
	// Constant Size Primitive
	unsigned int MethodBody::getmethodInfo() {
		return methodInfo;
	}
	void MethodBody::setmethodInfo( unsigned int v ) {
		methodInfo = v;
	}
	// Constant Size Primitive
	unsigned int MethodBody::getmaxStack() {
		return maxStack;
	}
	void MethodBody::setmaxStack( unsigned int v ) {
		maxStack = v;
	}
	// Constant Size Primitive
	unsigned int MethodBody::getmaxRegs() {
		return maxRegs;
	}
	void MethodBody::setmaxRegs( unsigned int v ) {
		maxRegs = v;
	}
	// Constant Size Primitive
	unsigned int MethodBody::getscopeDepth() {
		return scopeDepth;
	}
	void MethodBody::setscopeDepth( unsigned int v ) {
		scopeDepth = v;
	}
	// Constant Size Primitive
	unsigned int MethodBody::getmaxScope() {
		return maxScope;
	}
	void MethodBody::setmaxScope( unsigned int v ) {
		maxScope = v;
	}
	// Constant Size Primitive
	unsigned int MethodBody::getcodeLength() {
		return codeLength;
	}
	void MethodBody::setcodeLength( unsigned int v ) {
		codeLength = v;
	}
List<OpCode> *MethodBody::getcode() {
		return &code;
	}
	// Constant Size Primitive
	unsigned int MethodBody::getexceptionCount() {
		return exceptionCount;
	}
	void MethodBody::setexceptionCount( unsigned int v ) {
		exceptionCount = v;
	}
List<Exception> *MethodBody::getexceptions() {
		return &exceptions;
	}
	// Constant Size Primitive
	unsigned int MethodBody::gettraitCount() {
		return traitCount;
	}
	void MethodBody::settraitCount( unsigned int v ) {
		traitCount = v;
	}
List<TraitInfo> *MethodBody::gettraits() {
		return &traits;
	}
Constants::Constants() {
	intCount = 0;
uintCount = 0;
doubleCount = 0;
stringCount = 0;
namespaceConstantCount = 0;
namespaceSetCount = 0;
multinameConstantCount = 0;
}
Constants::~Constants() {
}
Constants* Constants::get( Reader *r, int end, Context *ctx ) {
	Constants* ret = new Constants;
	ret->parse( r, end, ctx );
	return ret;
}
Constants* Constants::getByName( const char *name ) {
	if( strcmp( name, "Constants" ) ) return NULL;
	Constants* ret = new Constants;
	return ret;
}
	// Constant Size Primitive
	unsigned int Constants::getintCount() {
		return intCount;
	}
	void Constants::setintCount( unsigned int v ) {
		intCount = v;
	}
List<U30> *Constants::getints() {
		return &ints;
	}
	// Constant Size Primitive
	unsigned int Constants::getuintCount() {
		return uintCount;
	}
	void Constants::setuintCount( unsigned int v ) {
		uintCount = v;
	}
List<U30> *Constants::getuints() {
		return &uints;
	}
	// Constant Size Primitive
	unsigned int Constants::getdoubleCount() {
		return doubleCount;
	}
	void Constants::setdoubleCount( unsigned int v ) {
		doubleCount = v;
	}
List<Double> *Constants::getdoubles() {
		return &doubles;
	}
	// Constant Size Primitive
	unsigned int Constants::getstringCount() {
		return stringCount;
	}
	void Constants::setstringCount( unsigned int v ) {
		stringCount = v;
	}
List<String2> *Constants::getstrings() {
		return &strings;
	}
	// Constant Size Primitive
	unsigned int Constants::getnamespaceConstantCount() {
		return namespaceConstantCount;
	}
	void Constants::setnamespaceConstantCount( unsigned int v ) {
		namespaceConstantCount = v;
	}
List<NamespaceConstant> *Constants::getnamespaces() {
		return &namespaces;
	}
	// Constant Size Primitive
	unsigned int Constants::getnamespaceSetCount() {
		return namespaceSetCount;
	}
	void Constants::setnamespaceSetCount( unsigned int v ) {
		namespaceSetCount = v;
	}
List<NamespaceSet> *Constants::getnamespaceSets() {
		return &namespaceSets;
	}
	// Constant Size Primitive
	unsigned int Constants::getmultinameConstantCount() {
		return multinameConstantCount;
	}
	void Constants::setmultinameConstantCount( unsigned int v ) {
		multinameConstantCount = v;
	}
List<MultinameConstant> *Constants::getmultinames() {
		return &multinames;
	}
Action3::Action3() {
	minorVersion = 0;
majorVersion = 0;
methodInfoCount = 0;
metadataInfoCount = 0;
classCount = 0;
scriptCount = 0;
methodBodyCount = 0;
}
Action3::~Action3() {
}
Action3* Action3::get( Reader *r, int end, Context *ctx ) {
	Action3* ret = new Action3;
	ret->parse( r, end, ctx );
	return ret;
}
Action3* Action3::getByName( const char *name ) {
	if( strcmp( name, "Action3" ) ) return NULL;
	Action3* ret = new Action3;
	return ret;
}
	// Constant Size Primitive
	unsigned short Action3::getminorVersion() {
		return minorVersion;
	}
	void Action3::setminorVersion( unsigned short v ) {
		minorVersion = v;
	}
	// Constant Size Primitive
	unsigned short Action3::getmajorVersion() {
		return majorVersion;
	}
	void Action3::setmajorVersion( unsigned short v ) {
		majorVersion = v;
	}
Constants *Action3::getconstants() {
		return &constants;
	}
	// Constant Size Primitive
	unsigned int Action3::getmethodInfoCount() {
		return methodInfoCount;
	}
	void Action3::setmethodInfoCount( unsigned int v ) {
		methodInfoCount = v;
	}
List<MethodInfo> *Action3::getmethods() {
		return &methods;
	}
	// Constant Size Primitive
	unsigned int Action3::getmetadataInfoCount() {
		return metadataInfoCount;
	}
	void Action3::setmetadataInfoCount( unsigned int v ) {
		metadataInfoCount = v;
	}
List<MetadataInfo> *Action3::getmetadata() {
		return &metadata;
	}
	// Constant Size Primitive
	unsigned int Action3::getclassCount() {
		return classCount;
	}
	void Action3::setclassCount( unsigned int v ) {
		classCount = v;
	}
List<InstanceInfo> *Action3::getinstances() {
		return &instances;
	}
List<ClassInfo> *Action3::getclasses() {
		return &classes;
	}
	// Constant Size Primitive
	unsigned int Action3::getscriptCount() {
		return scriptCount;
	}
	void Action3::setscriptCount( unsigned int v ) {
		scriptCount = v;
	}
List<ScriptInfo> *Action3::getscripts() {
		return &scripts;
	}
	// Constant Size Primitive
	unsigned int Action3::getmethodBodyCount() {
		return methodBodyCount;
	}
	void Action3::setmethodBodyCount( unsigned int v ) {
		methodBodyCount = v;
	}
List<MethodBody> *Action3::getmethodBodies() {
		return &methodBodies;
	}
ZoneData::ZoneData() {
	position = 0;
size = 0;
}
ZoneData::~ZoneData() {
}
ZoneData* ZoneData::get( Reader *r, int end, Context *ctx ) {
	ZoneData* ret = new ZoneData;
	ret->parse( r, end, ctx );
	return ret;
}
ZoneData* ZoneData::getByName( const char *name ) {
	if( strcmp( name, "ZoneData" ) ) return NULL;
	ZoneData* ret = new ZoneData;
	return ret;
}
ZoneArray::ZoneArray() {
	count = 0;
zoneX = 0;
zoneY = 0;
reserved = 0;
}
ZoneArray::~ZoneArray() {
}
ZoneArray* ZoneArray::get( Reader *r, int end, Context *ctx ) {
	ZoneArray* ret = new ZoneArray;
	ret->parse( r, end, ctx );
	return ret;
}
ZoneArray* ZoneArray::getByName( const char *name ) {
	if( strcmp( name, "ZoneArray" ) ) return NULL;
	ZoneArray* ret = new ZoneArray;
	return ret;
}
	// Constant Size Primitive
	unsigned char ZoneArray::getcount() {
		return count;
	}
	void ZoneArray::setcount( unsigned char v ) {
		count = v;
	}
List<ZoneData> *ZoneArray::getzones() {
		return &zones;
	}
	// Constant Size Primitive
	int ZoneArray::getzoneX() {
		return zoneX;
	}
	void ZoneArray::setzoneX( int v ) {
		zoneX = v;
	}
	// Constant Size Primitive
	int ZoneArray::getzoneY() {
		return zoneY;
	}
	void ZoneArray::setzoneY( int v ) {
		zoneY = v;
	}
	// Constant Size Primitive
	int ZoneArray::getreserved() {
		return reserved;
	}
	void ZoneArray::setreserved( int v ) {
		reserved = v;
	}
UnknownFilter::UnknownFilter() {
	data = NULL;
}
UnknownFilter::~UnknownFilter() {
	delete[] data;
}
UnknownFilter* UnknownFilter::get( Reader *r, int end, Context *ctx ) {
	UnknownFilter* ret = new UnknownFilter;
	ret->parse( r, end, ctx );
	return ret;
}
UnknownFilter* UnknownFilter::getByName( const char *name ) {
	if( strcmp( name, "UnknownFilter" ) ) return NULL;
	UnknownFilter* ret = new UnknownFilter;
	return ret;
}
		void UnknownFilter::getdata( unsigned char **dst, int *size ) {
			*dst = data;
			*size = len;
		}
		void UnknownFilter::setdata( const unsigned char *src, int size ) {
			delete data;
			len = size;
			data = new unsigned char[ size ];
			memcpy( data, src, size ); 
		}
DropShadow::DropShadow() {
	blurX = 0;
blurY = 0;
angle = 0;
distance = 0;
strength = 0;
innerShadow = 0;
knockout = 0;
compositeSource = 1;
passes = 0;
}
DropShadow::~DropShadow() {
}
DropShadow* DropShadow::get( Reader *r, int end, Context *ctx ) {
	DropShadow* ret = new DropShadow;
	ret->parse( r, end, ctx );
	return ret;
}
DropShadow* DropShadow::getByName( const char *name ) {
	if( strcmp( name, "DropShadow" ) ) return NULL;
	DropShadow* ret = new DropShadow;
	return ret;
}
Color *DropShadow::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	float DropShadow::getblurX() {
		return blurX;
	}
	void DropShadow::setblurX( float v ) {
		blurX = v;
	}
	// Constant Size Primitive
	float DropShadow::getblurY() {
		return blurY;
	}
	void DropShadow::setblurY( float v ) {
		blurY = v;
	}
	// Constant Size Primitive
	float DropShadow::getangle() {
		return angle;
	}
	void DropShadow::setangle( float v ) {
		angle = v;
	}
	// Constant Size Primitive
	float DropShadow::getdistance() {
		return distance;
	}
	void DropShadow::setdistance( float v ) {
		distance = v;
	}
	// Constant Size Primitive
	float DropShadow::getstrength() {
		return strength;
	}
	void DropShadow::setstrength( float v ) {
		strength = v;
	}
	// Constant Size Primitive
	bool DropShadow::getinnerShadow() {
		return innerShadow;
	}
	void DropShadow::setinnerShadow( bool v ) {
		innerShadow = v;
	}
	// Constant Size Primitive
	bool DropShadow::getknockout() {
		return knockout;
	}
	void DropShadow::setknockout( bool v ) {
		knockout = v;
	}
	// Constant Size Primitive
	bool DropShadow::getcompositeSource() {
		return compositeSource;
	}
	void DropShadow::setcompositeSource( bool v ) {
		compositeSource = v;
	}
	// Constant Size Primitive
	int DropShadow::getpasses() {
		return passes;
	}
	void DropShadow::setpasses( int v ) {
		passes = v;
	}
Blur::Blur() {
	blurX = 0;
blurY = 0;
passes = 0;
reserved1 = 0;
}
Blur::~Blur() {
}
Blur* Blur::get( Reader *r, int end, Context *ctx ) {
	Blur* ret = new Blur;
	ret->parse( r, end, ctx );
	return ret;
}
Blur* Blur::getByName( const char *name ) {
	if( strcmp( name, "Blur" ) ) return NULL;
	Blur* ret = new Blur;
	return ret;
}
	// Constant Size Primitive
	float Blur::getblurX() {
		return blurX;
	}
	void Blur::setblurX( float v ) {
		blurX = v;
	}
	// Constant Size Primitive
	float Blur::getblurY() {
		return blurY;
	}
	void Blur::setblurY( float v ) {
		blurY = v;
	}
	// Constant Size Primitive
	int Blur::getpasses() {
		return passes;
	}
	void Blur::setpasses( int v ) {
		passes = v;
	}
	// Constant Size Primitive
	int Blur::getreserved1() {
		return reserved1;
	}
	void Blur::setreserved1( int v ) {
		reserved1 = v;
	}
Glow::Glow() {
	blurX = 0;
blurY = 0;
strength = 0;
innerGlow = 0;
knockout = 0;
compositeSource = 1;
passes = 0;
}
Glow::~Glow() {
}
Glow* Glow::get( Reader *r, int end, Context *ctx ) {
	Glow* ret = new Glow;
	ret->parse( r, end, ctx );
	return ret;
}
Glow* Glow::getByName( const char *name ) {
	if( strcmp( name, "Glow" ) ) return NULL;
	Glow* ret = new Glow;
	return ret;
}
Color *Glow::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	float Glow::getblurX() {
		return blurX;
	}
	void Glow::setblurX( float v ) {
		blurX = v;
	}
	// Constant Size Primitive
	float Glow::getblurY() {
		return blurY;
	}
	void Glow::setblurY( float v ) {
		blurY = v;
	}
	// Constant Size Primitive
	float Glow::getstrength() {
		return strength;
	}
	void Glow::setstrength( float v ) {
		strength = v;
	}
	// Constant Size Primitive
	bool Glow::getinnerGlow() {
		return innerGlow;
	}
	void Glow::setinnerGlow( bool v ) {
		innerGlow = v;
	}
	// Constant Size Primitive
	bool Glow::getknockout() {
		return knockout;
	}
	void Glow::setknockout( bool v ) {
		knockout = v;
	}
	// Constant Size Primitive
	bool Glow::getcompositeSource() {
		return compositeSource;
	}
	void Glow::setcompositeSource( bool v ) {
		compositeSource = v;
	}
	// Constant Size Primitive
	int Glow::getpasses() {
		return passes;
	}
	void Glow::setpasses( int v ) {
		passes = v;
	}
Bevel::Bevel() {
	blurX = 0;
blurY = 0;
angle = 0;
distance = 0;
strength = 0;
innerShadow = 0;
knockout = 0;
compositeSource = 1;
onTop = 0;
passes = 0;
}
Bevel::~Bevel() {
}
Bevel* Bevel::get( Reader *r, int end, Context *ctx ) {
	Bevel* ret = new Bevel;
	ret->parse( r, end, ctx );
	return ret;
}
Bevel* Bevel::getByName( const char *name ) {
	if( strcmp( name, "Bevel" ) ) return NULL;
	Bevel* ret = new Bevel;
	return ret;
}
Color *Bevel::getshadowColor() {
		return &shadowColor;
	}
Color *Bevel::gethighlightColor() {
		return &highlightColor;
	}
	// Constant Size Primitive
	float Bevel::getblurX() {
		return blurX;
	}
	void Bevel::setblurX( float v ) {
		blurX = v;
	}
	// Constant Size Primitive
	float Bevel::getblurY() {
		return blurY;
	}
	void Bevel::setblurY( float v ) {
		blurY = v;
	}
	// Constant Size Primitive
	float Bevel::getangle() {
		return angle;
	}
	void Bevel::setangle( float v ) {
		angle = v;
	}
	// Constant Size Primitive
	float Bevel::getdistance() {
		return distance;
	}
	void Bevel::setdistance( float v ) {
		distance = v;
	}
	// Constant Size Primitive
	float Bevel::getstrength() {
		return strength;
	}
	void Bevel::setstrength( float v ) {
		strength = v;
	}
	// Constant Size Primitive
	bool Bevel::getinnerShadow() {
		return innerShadow;
	}
	void Bevel::setinnerShadow( bool v ) {
		innerShadow = v;
	}
	// Constant Size Primitive
	bool Bevel::getknockout() {
		return knockout;
	}
	void Bevel::setknockout( bool v ) {
		knockout = v;
	}
	// Constant Size Primitive
	bool Bevel::getcompositeSource() {
		return compositeSource;
	}
	void Bevel::setcompositeSource( bool v ) {
		compositeSource = v;
	}
	// Constant Size Primitive
	bool Bevel::getonTop() {
		return onTop;
	}
	void Bevel::setonTop( bool v ) {
		onTop = v;
	}
	// Constant Size Primitive
	int Bevel::getpasses() {
		return passes;
	}
	void Bevel::setpasses( int v ) {
		passes = v;
	}
GradientGlow::GradientGlow() {
	numColors = 0;
blurX = 0;
blurY = 0;
angle = 0;
distance = 0;
strength = 0;
innerGlow = 0;
knockout = 0;
compositeSource = 1;
onTop = 0;
passes = 0;
}
GradientGlow::~GradientGlow() {
}
GradientGlow* GradientGlow::get( Reader *r, int end, Context *ctx ) {
	GradientGlow* ret = new GradientGlow;
	ret->parse( r, end, ctx );
	return ret;
}
GradientGlow* GradientGlow::getByName( const char *name ) {
	if( strcmp( name, "GradientGlow" ) ) return NULL;
	GradientGlow* ret = new GradientGlow;
	return ret;
}
	// Constant Size Primitive
	unsigned char GradientGlow::getnumColors() {
		return numColors;
	}
	void GradientGlow::setnumColors( unsigned char v ) {
		numColors = v;
	}
List<Color> *GradientGlow::getcolors() {
		return &colors;
	}
List<UChar> *GradientGlow::getratio() {
		return &ratio;
	}
	// Constant Size Primitive
	float GradientGlow::getblurX() {
		return blurX;
	}
	void GradientGlow::setblurX( float v ) {
		blurX = v;
	}
	// Constant Size Primitive
	float GradientGlow::getblurY() {
		return blurY;
	}
	void GradientGlow::setblurY( float v ) {
		blurY = v;
	}
	// Constant Size Primitive
	float GradientGlow::getangle() {
		return angle;
	}
	void GradientGlow::setangle( float v ) {
		angle = v;
	}
	// Constant Size Primitive
	float GradientGlow::getdistance() {
		return distance;
	}
	void GradientGlow::setdistance( float v ) {
		distance = v;
	}
	// Constant Size Primitive
	float GradientGlow::getstrength() {
		return strength;
	}
	void GradientGlow::setstrength( float v ) {
		strength = v;
	}
	// Constant Size Primitive
	bool GradientGlow::getinnerGlow() {
		return innerGlow;
	}
	void GradientGlow::setinnerGlow( bool v ) {
		innerGlow = v;
	}
	// Constant Size Primitive
	bool GradientGlow::getknockout() {
		return knockout;
	}
	void GradientGlow::setknockout( bool v ) {
		knockout = v;
	}
	// Constant Size Primitive
	bool GradientGlow::getcompositeSource() {
		return compositeSource;
	}
	void GradientGlow::setcompositeSource( bool v ) {
		compositeSource = v;
	}
	// Constant Size Primitive
	bool GradientGlow::getonTop() {
		return onTop;
	}
	void GradientGlow::setonTop( bool v ) {
		onTop = v;
	}
	// Constant Size Primitive
	int GradientGlow::getpasses() {
		return passes;
	}
	void GradientGlow::setpasses( int v ) {
		passes = v;
	}
Convolution::Convolution() {
	matrixX = 0;
matrixY = 0;
divizor = 0;
bias = 0;
reserved = 0;
clamp = 0;
preserveAlpha = 0;
}
Convolution::~Convolution() {
}
Convolution* Convolution::get( Reader *r, int end, Context *ctx ) {
	Convolution* ret = new Convolution;
	ret->parse( r, end, ctx );
	return ret;
}
Convolution* Convolution::getByName( const char *name ) {
	if( strcmp( name, "Convolution" ) ) return NULL;
	Convolution* ret = new Convolution;
	return ret;
}
	// Constant Size Primitive
	unsigned char Convolution::getmatrixX() {
		return matrixX;
	}
	void Convolution::setmatrixX( unsigned char v ) {
		matrixX = v;
	}
	// Constant Size Primitive
	unsigned char Convolution::getmatrixY() {
		return matrixY;
	}
	void Convolution::setmatrixY( unsigned char v ) {
		matrixY = v;
	}
List<Float> *Convolution::getmatrix() {
		return &matrix;
	}
Color *Convolution::getdefaultColor() {
		return &defaultColor;
	}
	// Constant Size Primitive
	int Convolution::getreserved() {
		return reserved;
	}
	void Convolution::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool Convolution::getclamp() {
		return clamp;
	}
	void Convolution::setclamp( bool v ) {
		clamp = v;
	}
	// Constant Size Primitive
	bool Convolution::getpreserveAlpha() {
		return preserveAlpha;
	}
	void Convolution::setpreserveAlpha( bool v ) {
		preserveAlpha = v;
	}
ColorMatrix::ColorMatrix() {
}
ColorMatrix::~ColorMatrix() {
}
ColorMatrix* ColorMatrix::get( Reader *r, int end, Context *ctx ) {
	ColorMatrix* ret = new ColorMatrix;
	ret->parse( r, end, ctx );
	return ret;
}
ColorMatrix* ColorMatrix::getByName( const char *name ) {
	if( strcmp( name, "ColorMatrix" ) ) return NULL;
	ColorMatrix* ret = new ColorMatrix;
	return ret;
}
List<Float> *ColorMatrix::getmatrix() {
		return &matrix;
	}
GradientBevel::GradientBevel() {
	numColors = 0;
blurX = 0;
blurY = 0;
angle = 0;
distance = 0;
strength = 0;
innerGlow = 0;
knockout = 0;
compositeSource = 1;
onTop = 0;
passes = 0;
}
GradientBevel::~GradientBevel() {
}
GradientBevel* GradientBevel::get( Reader *r, int end, Context *ctx ) {
	GradientBevel* ret = new GradientBevel;
	ret->parse( r, end, ctx );
	return ret;
}
GradientBevel* GradientBevel::getByName( const char *name ) {
	if( strcmp( name, "GradientBevel" ) ) return NULL;
	GradientBevel* ret = new GradientBevel;
	return ret;
}
	// Constant Size Primitive
	unsigned char GradientBevel::getnumColors() {
		return numColors;
	}
	void GradientBevel::setnumColors( unsigned char v ) {
		numColors = v;
	}
List<Color> *GradientBevel::getcolors() {
		return &colors;
	}
List<UChar> *GradientBevel::getratio() {
		return &ratio;
	}
	// Constant Size Primitive
	float GradientBevel::getblurX() {
		return blurX;
	}
	void GradientBevel::setblurX( float v ) {
		blurX = v;
	}
	// Constant Size Primitive
	float GradientBevel::getblurY() {
		return blurY;
	}
	void GradientBevel::setblurY( float v ) {
		blurY = v;
	}
	// Constant Size Primitive
	float GradientBevel::getangle() {
		return angle;
	}
	void GradientBevel::setangle( float v ) {
		angle = v;
	}
	// Constant Size Primitive
	float GradientBevel::getdistance() {
		return distance;
	}
	void GradientBevel::setdistance( float v ) {
		distance = v;
	}
	// Constant Size Primitive
	float GradientBevel::getstrength() {
		return strength;
	}
	void GradientBevel::setstrength( float v ) {
		strength = v;
	}
	// Constant Size Primitive
	bool GradientBevel::getinnerGlow() {
		return innerGlow;
	}
	void GradientBevel::setinnerGlow( bool v ) {
		innerGlow = v;
	}
	// Constant Size Primitive
	bool GradientBevel::getknockout() {
		return knockout;
	}
	void GradientBevel::setknockout( bool v ) {
		knockout = v;
	}
	// Constant Size Primitive
	bool GradientBevel::getcompositeSource() {
		return compositeSource;
	}
	void GradientBevel::setcompositeSource( bool v ) {
		compositeSource = v;
	}
	// Constant Size Primitive
	bool GradientBevel::getonTop() {
		return onTop;
	}
	void GradientBevel::setonTop( bool v ) {
		onTop = v;
	}
	// Constant Size Primitive
	int GradientBevel::getpasses() {
		return passes;
	}
	void GradientBevel::setpasses( int v ) {
		passes = v;
	}
Solid::Solid() {
}
Solid::~Solid() {
}
Solid* Solid::get( Reader *r, int end, Context *ctx ) {
	Solid* ret = new Solid;
	ret->parse( r, end, ctx );
	return ret;
}
Solid* Solid::getByName( const char *name ) {
	if( strcmp( name, "Solid" ) ) return NULL;
	Solid* ret = new Solid;
	return ret;
}
Color *Solid::getcolor() {
		return &color;
	}
LinearGradient::LinearGradient() {
	reserved = 0;
spreadMode = 0;
interpolationMode = 0;
count = 0;
}
LinearGradient::~LinearGradient() {
}
LinearGradient* LinearGradient::get( Reader *r, int end, Context *ctx ) {
	LinearGradient* ret = new LinearGradient;
	ret->parse( r, end, ctx );
	return ret;
}
LinearGradient* LinearGradient::getByName( const char *name ) {
	if( strcmp( name, "LinearGradient" ) ) return NULL;
	LinearGradient* ret = new LinearGradient;
	return ret;
}
Transform *LinearGradient::getmatrix() {
		return &matrix;
	}
	// Constant Size Primitive
	int LinearGradient::getreserved() {
		return reserved;
	}
	void LinearGradient::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	int LinearGradient::getspreadMode() {
		return spreadMode;
	}
	void LinearGradient::setspreadMode( int v ) {
		spreadMode = v;
	}
	// Constant Size Primitive
	int LinearGradient::getinterpolationMode() {
		return interpolationMode;
	}
	void LinearGradient::setinterpolationMode( int v ) {
		interpolationMode = v;
	}
	// Constant Size Primitive
	int LinearGradient::getcount() {
		return count;
	}
	void LinearGradient::setcount( int v ) {
		count = v;
	}
List<GradientItem> *LinearGradient::getgradientColors() {
		return &gradientColors;
	}
RadialGradient::RadialGradient() {
	reserved = 0;
spreadMode = 0;
interpolationMode = 0;
count = 0;
}
RadialGradient::~RadialGradient() {
}
RadialGradient* RadialGradient::get( Reader *r, int end, Context *ctx ) {
	RadialGradient* ret = new RadialGradient;
	ret->parse( r, end, ctx );
	return ret;
}
RadialGradient* RadialGradient::getByName( const char *name ) {
	if( strcmp( name, "RadialGradient" ) ) return NULL;
	RadialGradient* ret = new RadialGradient;
	return ret;
}
Transform *RadialGradient::getmatrix() {
		return &matrix;
	}
	// Constant Size Primitive
	int RadialGradient::getreserved() {
		return reserved;
	}
	void RadialGradient::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	int RadialGradient::getspreadMode() {
		return spreadMode;
	}
	void RadialGradient::setspreadMode( int v ) {
		spreadMode = v;
	}
	// Constant Size Primitive
	int RadialGradient::getinterpolationMode() {
		return interpolationMode;
	}
	void RadialGradient::setinterpolationMode( int v ) {
		interpolationMode = v;
	}
	// Constant Size Primitive
	int RadialGradient::getcount() {
		return count;
	}
	void RadialGradient::setcount( int v ) {
		count = v;
	}
List<GradientItem> *RadialGradient::getgradientColors() {
		return &gradientColors;
	}
ShiftedRadialGradient::ShiftedRadialGradient() {
	reserved = 0;
spreadMode = 0;
interpolationMode = 0;
count = 0;
shift = 0;
}
ShiftedRadialGradient::~ShiftedRadialGradient() {
}
ShiftedRadialGradient* ShiftedRadialGradient::get( Reader *r, int end, Context *ctx ) {
	ShiftedRadialGradient* ret = new ShiftedRadialGradient;
	ret->parse( r, end, ctx );
	return ret;
}
ShiftedRadialGradient* ShiftedRadialGradient::getByName( const char *name ) {
	if( strcmp( name, "ShiftedRadialGradient" ) ) return NULL;
	ShiftedRadialGradient* ret = new ShiftedRadialGradient;
	return ret;
}
Transform *ShiftedRadialGradient::getmatrix() {
		return &matrix;
	}
	// Constant Size Primitive
	int ShiftedRadialGradient::getreserved() {
		return reserved;
	}
	void ShiftedRadialGradient::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	int ShiftedRadialGradient::getspreadMode() {
		return spreadMode;
	}
	void ShiftedRadialGradient::setspreadMode( int v ) {
		spreadMode = v;
	}
	// Constant Size Primitive
	int ShiftedRadialGradient::getinterpolationMode() {
		return interpolationMode;
	}
	void ShiftedRadialGradient::setinterpolationMode( int v ) {
		interpolationMode = v;
	}
	// Constant Size Primitive
	int ShiftedRadialGradient::getcount() {
		return count;
	}
	void ShiftedRadialGradient::setcount( int v ) {
		count = v;
	}
List<GradientItem> *ShiftedRadialGradient::getgradientColors() {
		return &gradientColors;
	}
	// Constant Size Primitive
	float ShiftedRadialGradient::getshift() {
		return shift;
	}
	void ShiftedRadialGradient::setshift( float v ) {
		shift = v;
	}
TiledBitmap::TiledBitmap() {
	objectID = 0;
}
TiledBitmap::~TiledBitmap() {
}
TiledBitmap* TiledBitmap::get( Reader *r, int end, Context *ctx ) {
	TiledBitmap* ret = new TiledBitmap;
	ret->parse( r, end, ctx );
	return ret;
}
TiledBitmap* TiledBitmap::getByName( const char *name ) {
	if( strcmp( name, "TiledBitmap" ) ) return NULL;
	TiledBitmap* ret = new TiledBitmap;
	return ret;
}
	// Constant Size Primitive
	unsigned short TiledBitmap::getobjectID() {
		return objectID;
	}
	void TiledBitmap::setobjectID( unsigned short v ) {
		objectID = v;
	}
Transform *TiledBitmap::getmatrix() {
		return &matrix;
	}
ClippedBitmap::ClippedBitmap() {
	objectID = 0;
}
ClippedBitmap::~ClippedBitmap() {
}
ClippedBitmap* ClippedBitmap::get( Reader *r, int end, Context *ctx ) {
	ClippedBitmap* ret = new ClippedBitmap;
	ret->parse( r, end, ctx );
	return ret;
}
ClippedBitmap* ClippedBitmap::getByName( const char *name ) {
	if( strcmp( name, "ClippedBitmap" ) ) return NULL;
	ClippedBitmap* ret = new ClippedBitmap;
	return ret;
}
	// Constant Size Primitive
	unsigned short ClippedBitmap::getobjectID() {
		return objectID;
	}
	void ClippedBitmap::setobjectID( unsigned short v ) {
		objectID = v;
	}
Transform *ClippedBitmap::getmatrix() {
		return &matrix;
	}
TiledBitmap2::TiledBitmap2() {
	objectID = 0;
}
TiledBitmap2::~TiledBitmap2() {
}
TiledBitmap2* TiledBitmap2::get( Reader *r, int end, Context *ctx ) {
	TiledBitmap2* ret = new TiledBitmap2;
	ret->parse( r, end, ctx );
	return ret;
}
TiledBitmap2* TiledBitmap2::getByName( const char *name ) {
	if( strcmp( name, "TiledBitmap2" ) ) return NULL;
	TiledBitmap2* ret = new TiledBitmap2;
	return ret;
}
	// Constant Size Primitive
	unsigned short TiledBitmap2::getobjectID() {
		return objectID;
	}
	void TiledBitmap2::setobjectID( unsigned short v ) {
		objectID = v;
	}
Transform *TiledBitmap2::getmatrix() {
		return &matrix;
	}
ClippedBitmap2::ClippedBitmap2() {
	objectID = 0;
}
ClippedBitmap2::~ClippedBitmap2() {
}
ClippedBitmap2* ClippedBitmap2::get( Reader *r, int end, Context *ctx ) {
	ClippedBitmap2* ret = new ClippedBitmap2;
	ret->parse( r, end, ctx );
	return ret;
}
ClippedBitmap2* ClippedBitmap2::getByName( const char *name ) {
	if( strcmp( name, "ClippedBitmap2" ) ) return NULL;
	ClippedBitmap2* ret = new ClippedBitmap2;
	return ret;
}
	// Constant Size Primitive
	unsigned short ClippedBitmap2::getobjectID() {
		return objectID;
	}
	void ClippedBitmap2::setobjectID( unsigned short v ) {
		objectID = v;
	}
Transform *ClippedBitmap2::getmatrix() {
		return &matrix;
	}
UnknownTag::UnknownTag() {
	data = NULL;
}
UnknownTag::~UnknownTag() {
	delete[] data;
}
UnknownTag* UnknownTag::get( Reader *r, int end, Context *ctx ) {
	UnknownTag* ret = new UnknownTag;
	ret->parse( r, end, ctx );
	return ret;
}
UnknownTag* UnknownTag::getByName( const char *name ) {
	if( strcmp( name, "UnknownTag" ) ) return NULL;
	UnknownTag* ret = new UnknownTag;
	return ret;
}
		void UnknownTag::getdata( unsigned char **dst, int *size ) {
			*dst = data;
			*size = len;
		}
		void UnknownTag::setdata( const unsigned char *src, int size ) {
			delete data;
			len = size;
			data = new unsigned char[ size ];
			memcpy( data, src, size ); 
		}
End::End() {
}
End::~End() {
}
End* End::get( Reader *r, int end, Context *ctx ) {
	End* ret = new End;
	ret->parse( r, end, ctx );
	return ret;
}
End* End::getByName( const char *name ) {
	if( strcmp( name, "End" ) ) return NULL;
	End* ret = new End;
	return ret;
}
ShowFrame::ShowFrame() {
}
ShowFrame::~ShowFrame() {
}
ShowFrame* ShowFrame::get( Reader *r, int end, Context *ctx ) {
	ShowFrame* ret = new ShowFrame;
	ret->parse( r, end, ctx );
	return ret;
}
ShowFrame* ShowFrame::getByName( const char *name ) {
	if( strcmp( name, "ShowFrame" ) ) return NULL;
	ShowFrame* ret = new ShowFrame;
	return ret;
}
DefineShape::DefineShape() {
	objectID = 0;
}
DefineShape::~DefineShape() {
}
DefineShape* DefineShape::get( Reader *r, int end, Context *ctx ) {
	DefineShape* ret = new DefineShape;
	ret->parse( r, end, ctx );
	return ret;
}
DefineShape* DefineShape::getByName( const char *name ) {
	if( strcmp( name, "DefineShape" ) ) return NULL;
	DefineShape* ret = new DefineShape;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineShape::getobjectID() {
		return objectID;
	}
	void DefineShape::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineShape::getbounds() {
		return &bounds;
	}
StyleList *DefineShape::getstyles() {
		return &styles;
	}
Shape *DefineShape::getshapes() {
		return &shapes;
	}
RemoveObject::RemoveObject() {
	objectID = 0;
depth = 0;
}
RemoveObject::~RemoveObject() {
}
RemoveObject* RemoveObject::get( Reader *r, int end, Context *ctx ) {
	RemoveObject* ret = new RemoveObject;
	ret->parse( r, end, ctx );
	return ret;
}
RemoveObject* RemoveObject::getByName( const char *name ) {
	if( strcmp( name, "RemoveObject" ) ) return NULL;
	RemoveObject* ret = new RemoveObject;
	return ret;
}
	// Constant Size Primitive
	unsigned short RemoveObject::getobjectID() {
		return objectID;
	}
	void RemoveObject::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned short RemoveObject::getdepth() {
		return depth;
	}
	void RemoveObject::setdepth( unsigned short v ) {
		depth = v;
	}
DefineBits::DefineBits() {
	objectID = 0;
}
DefineBits::~DefineBits() {
}
DefineBits* DefineBits::get( Reader *r, int end, Context *ctx ) {
	DefineBits* ret = new DefineBits;
	ret->parse( r, end, ctx );
	return ret;
}
DefineBits* DefineBits::getByName( const char *name ) {
	if( strcmp( name, "DefineBits" ) ) return NULL;
	DefineBits* ret = new DefineBits;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineBits::getobjectID() {
		return objectID;
	}
	void DefineBits::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rest *DefineBits::getdata() {
		return &data;
	}
SetBackgroundColor::SetBackgroundColor() {
}
SetBackgroundColor::~SetBackgroundColor() {
}
SetBackgroundColor* SetBackgroundColor::get( Reader *r, int end, Context *ctx ) {
	SetBackgroundColor* ret = new SetBackgroundColor;
	ret->parse( r, end, ctx );
	return ret;
}
SetBackgroundColor* SetBackgroundColor::getByName( const char *name ) {
	if( strcmp( name, "SetBackgroundColor" ) ) return NULL;
	SetBackgroundColor* ret = new SetBackgroundColor;
	return ret;
}
Color *SetBackgroundColor::getcolor() {
		return &color;
	}
DefineText::DefineText() {
	objectID = 0;
glyphBits = 0;
advanceBits = 0;
}
DefineText::~DefineText() {
}
DefineText* DefineText::get( Reader *r, int end, Context *ctx ) {
	DefineText* ret = new DefineText;
	ret->parse( r, end, ctx );
	return ret;
}
DefineText* DefineText::getByName( const char *name ) {
	if( strcmp( name, "DefineText" ) ) return NULL;
	DefineText* ret = new DefineText;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineText::getobjectID() {
		return objectID;
	}
	void DefineText::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineText::getbounds() {
		return &bounds;
	}
Transform *DefineText::gettransform() {
		return &transform;
	}
	// Constant Size Primitive
	unsigned char DefineText::getglyphBits() {
		return glyphBits;
	}
	void DefineText::setglyphBits( unsigned char v ) {
		glyphBits = v;
	}
	// Constant Size Primitive
	unsigned char DefineText::getadvanceBits() {
		return advanceBits;
	}
	void DefineText::setadvanceBits( unsigned char v ) {
		advanceBits = v;
	}
List<TextRecord> *DefineText::getrecords() {
		return &records;
	}
DefineText2::DefineText2() {
	objectID = 0;
glyphBits = 0;
advanceBits = 0;
}
DefineText2::~DefineText2() {
}
DefineText2* DefineText2::get( Reader *r, int end, Context *ctx ) {
	DefineText2* ret = new DefineText2;
	ret->parse( r, end, ctx );
	return ret;
}
DefineText2* DefineText2::getByName( const char *name ) {
	if( strcmp( name, "DefineText2" ) ) return NULL;
	DefineText2* ret = new DefineText2;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineText2::getobjectID() {
		return objectID;
	}
	void DefineText2::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineText2::getbounds() {
		return &bounds;
	}
Transform *DefineText2::gettransform() {
		return &transform;
	}
	// Constant Size Primitive
	unsigned char DefineText2::getglyphBits() {
		return glyphBits;
	}
	void DefineText2::setglyphBits( unsigned char v ) {
		glyphBits = v;
	}
	// Constant Size Primitive
	unsigned char DefineText2::getadvanceBits() {
		return advanceBits;
	}
	void DefineText2::setadvanceBits( unsigned char v ) {
		advanceBits = v;
	}
List<TextRecord2> *DefineText2::getrecords() {
		return &records;
	}
DoAction::DoAction() {
}
DoAction::~DoAction() {
}
DoAction* DoAction::get( Reader *r, int end, Context *ctx ) {
	DoAction* ret = new DoAction;
	ret->parse( r, end, ctx );
	return ret;
}
DoAction* DoAction::getByName( const char *name ) {
	if( strcmp( name, "DoAction" ) ) return NULL;
	DoAction* ret = new DoAction;
	return ret;
}
List<Action> *DoAction::getactions() {
		return &actions;
	}
DefineFontInfo::DefineFontInfo() {
	objectID = 0;
nameLength = 0;
nameData = NULL;
reserved = 0;
smallTextOrUnicode = 0;
isShiftJIS = 0;
isANSII = 0;
isItalic = 0;
isBold = 0;
isWide = 0;
language = 0;
}
DefineFontInfo::~DefineFontInfo() {
	delete[] nameData;
}
DefineFontInfo* DefineFontInfo::get( Reader *r, int end, Context *ctx ) {
	DefineFontInfo* ret = new DefineFontInfo;
	ret->parse( r, end, ctx );
	return ret;
}
DefineFontInfo* DefineFontInfo::getByName( const char *name ) {
	if( strcmp( name, "DefineFontInfo" ) ) return NULL;
	DefineFontInfo* ret = new DefineFontInfo;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineFontInfo::getobjectID() {
		return objectID;
	}
	void DefineFontInfo::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned char DefineFontInfo::getnameLength() {
		return nameLength;
	}
	void DefineFontInfo::setnameLength( unsigned char v ) {
		nameLength = v;
	}
		void DefineFontInfo::getnameData( unsigned char **dst, int *size ) {
			*dst = nameData;
			*size = nameLength;
		}
		void DefineFontInfo::setnameData( const unsigned char *src, int size ) {
			delete nameData;
			nameLength = size;
			nameData = new unsigned char[ size ];
			memcpy( nameData, src, size ); 
		}
	// NBitInt
	int DefineFontInfo::getreserved() {
		return reserved;
	}
	void DefineFontInfo::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo::getsmallTextOrUnicode() {
		return smallTextOrUnicode;
	}
	void DefineFontInfo::setsmallTextOrUnicode( bool v ) {
		smallTextOrUnicode = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo::getisShiftJIS() {
		return isShiftJIS;
	}
	void DefineFontInfo::setisShiftJIS( bool v ) {
		isShiftJIS = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo::getisANSII() {
		return isANSII;
	}
	void DefineFontInfo::setisANSII( bool v ) {
		isANSII = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo::getisItalic() {
		return isItalic;
	}
	void DefineFontInfo::setisItalic( bool v ) {
		isItalic = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo::getisBold() {
		return isBold;
	}
	void DefineFontInfo::setisBold( bool v ) {
		isBold = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo::getisWide() {
		return isWide;
	}
	void DefineFontInfo::setisWide( bool v ) {
		isWide = v;
	}
	// Constant Size Primitive
	unsigned char DefineFontInfo::getlanguage() {
		return language;
	}
	void DefineFontInfo::setlanguage( unsigned char v ) {
		language = v;
	}
Rest *DefineFontInfo::getmap() {
		return &map;
	}
DefineSound::DefineSound() {
	objectID = 0;
format = 0;
rate = 0;
is16bit = 0;
stereo = 0;
samples = 0;
}
DefineSound::~DefineSound() {
}
DefineSound* DefineSound::get( Reader *r, int end, Context *ctx ) {
	DefineSound* ret = new DefineSound;
	ret->parse( r, end, ctx );
	return ret;
}
DefineSound* DefineSound::getByName( const char *name ) {
	if( strcmp( name, "DefineSound" ) ) return NULL;
	DefineSound* ret = new DefineSound;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineSound::getobjectID() {
		return objectID;
	}
	void DefineSound::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	int DefineSound::getformat() {
		return format;
	}
	void DefineSound::setformat( int v ) {
		format = v;
	}
	// Constant Size Primitive
	int DefineSound::getrate() {
		return rate;
	}
	void DefineSound::setrate( int v ) {
		rate = v;
	}
	// Constant Size Primitive
	bool DefineSound::getis16bit() {
		return is16bit;
	}
	void DefineSound::setis16bit( bool v ) {
		is16bit = v;
	}
	// Constant Size Primitive
	bool DefineSound::getstereo() {
		return stereo;
	}
	void DefineSound::setstereo( bool v ) {
		stereo = v;
	}
	// Constant Size Primitive
	unsigned int DefineSound::getsamples() {
		return samples;
	}
	void DefineSound::setsamples( unsigned int v ) {
		samples = v;
	}
Rest *DefineSound::getdata() {
		return &data;
	}
StartSound::StartSound() {
	objectID = 0;
reserved = 0;
stopPlayback = 0;
noMultiple = 0;
hasEnvelope = 0;
hasLoop = 0;
hasOutPoint = 0;
hasInPoint = 0;
inPoint = 0;
outPoint = 0;
loop = 0;
envelopeCount = 0;
}
StartSound::~StartSound() {
}
StartSound* StartSound::get( Reader *r, int end, Context *ctx ) {
	StartSound* ret = new StartSound;
	ret->parse( r, end, ctx );
	return ret;
}
StartSound* StartSound::getByName( const char *name ) {
	if( strcmp( name, "StartSound" ) ) return NULL;
	StartSound* ret = new StartSound;
	return ret;
}
	// Constant Size Primitive
	unsigned short StartSound::getobjectID() {
		return objectID;
	}
	void StartSound::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	int StartSound::getreserved() {
		return reserved;
	}
	void StartSound::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool StartSound::getstopPlayback() {
		return stopPlayback;
	}
	void StartSound::setstopPlayback( bool v ) {
		stopPlayback = v;
	}
	// Constant Size Primitive
	bool StartSound::getnoMultiple() {
		return noMultiple;
	}
	void StartSound::setnoMultiple( bool v ) {
		noMultiple = v;
	}
	// Constant Size Primitive
	bool StartSound::gethasEnvelope() {
		return hasEnvelope;
	}
	void StartSound::sethasEnvelope( bool v ) {
		hasEnvelope = v;
	}
	// Constant Size Primitive
	bool StartSound::gethasLoop() {
		return hasLoop;
	}
	void StartSound::sethasLoop( bool v ) {
		hasLoop = v;
	}
	// Constant Size Primitive
	bool StartSound::gethasOutPoint() {
		return hasOutPoint;
	}
	void StartSound::sethasOutPoint( bool v ) {
		hasOutPoint = v;
	}
	// Constant Size Primitive
	bool StartSound::gethasInPoint() {
		return hasInPoint;
	}
	void StartSound::sethasInPoint( bool v ) {
		hasInPoint = v;
	}
	// Constant Size Primitive
	unsigned int StartSound::getinPoint() {
		return inPoint;
	}
	void StartSound::setinPoint( unsigned int v ) {
		inPoint = v;
	}
	// Constant Size Primitive
	unsigned int StartSound::getoutPoint() {
		return outPoint;
	}
	void StartSound::setoutPoint( unsigned int v ) {
		outPoint = v;
	}
	// Constant Size Primitive
	unsigned short StartSound::getloop() {
		return loop;
	}
	void StartSound::setloop( unsigned short v ) {
		loop = v;
	}
	// Constant Size Primitive
	unsigned char StartSound::getenvelopeCount() {
		return envelopeCount;
	}
	void StartSound::setenvelopeCount( unsigned char v ) {
		envelopeCount = v;
	}
Rest *StartSound::getenvelopeData() {
		return &envelopeData;
	}
DefineShape2::DefineShape2() {
	objectID = 0;
}
DefineShape2::~DefineShape2() {
}
DefineShape2* DefineShape2::get( Reader *r, int end, Context *ctx ) {
	DefineShape2* ret = new DefineShape2;
	ret->parse( r, end, ctx );
	return ret;
}
DefineShape2* DefineShape2::getByName( const char *name ) {
	if( strcmp( name, "DefineShape2" ) ) return NULL;
	DefineShape2* ret = new DefineShape2;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineShape2::getobjectID() {
		return objectID;
	}
	void DefineShape2::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineShape2::getbounds() {
		return &bounds;
	}
StyleList *DefineShape2::getstyles() {
		return &styles;
	}
Shape *DefineShape2::getshapes() {
		return &shapes;
	}
DefineShape3::DefineShape3() {
	objectID = 0;
}
DefineShape3::~DefineShape3() {
}
DefineShape3* DefineShape3::get( Reader *r, int end, Context *ctx ) {
	DefineShape3* ret = new DefineShape3;
	ret->parse( r, end, ctx );
	return ret;
}
DefineShape3* DefineShape3::getByName( const char *name ) {
	if( strcmp( name, "DefineShape3" ) ) return NULL;
	DefineShape3* ret = new DefineShape3;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineShape3::getobjectID() {
		return objectID;
	}
	void DefineShape3::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineShape3::getbounds() {
		return &bounds;
	}
StyleList *DefineShape3::getstyles() {
		return &styles;
	}
Shape *DefineShape3::getshapes() {
		return &shapes;
	}
DefineShape4::DefineShape4() {
	objectID = 0;
}
DefineShape4::~DefineShape4() {
}
DefineShape4* DefineShape4::get( Reader *r, int end, Context *ctx ) {
	DefineShape4* ret = new DefineShape4;
	ret->parse( r, end, ctx );
	return ret;
}
DefineShape4* DefineShape4::getByName( const char *name ) {
	if( strcmp( name, "DefineShape4" ) ) return NULL;
	DefineShape4* ret = new DefineShape4;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineShape4::getobjectID() {
		return objectID;
	}
	void DefineShape4::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rest *DefineShape4::getdata() {
		return &data;
	}
DefineShape5::DefineShape5() {
	objectID = 0;
reserved = 0;
nonScalingStrokes = 0;
scalingStrokes = 0;
}
DefineShape5::~DefineShape5() {
}
DefineShape5* DefineShape5::get( Reader *r, int end, Context *ctx ) {
	DefineShape5* ret = new DefineShape5;
	ret->parse( r, end, ctx );
	return ret;
}
DefineShape5* DefineShape5::getByName( const char *name ) {
	if( strcmp( name, "DefineShape5" ) ) return NULL;
	DefineShape5* ret = new DefineShape5;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineShape5::getobjectID() {
		return objectID;
	}
	void DefineShape5::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineShape5::getbounds() {
		return &bounds;
	}
Rectangle *DefineShape5::getstrokeBounds() {
		return &strokeBounds;
	}
	// Constant Size Primitive
	int DefineShape5::getreserved() {
		return reserved;
	}
	void DefineShape5::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool DefineShape5::getnonScalingStrokes() {
		return nonScalingStrokes;
	}
	void DefineShape5::setnonScalingStrokes( bool v ) {
		nonScalingStrokes = v;
	}
	// Constant Size Primitive
	bool DefineShape5::getscalingStrokes() {
		return scalingStrokes;
	}
	void DefineShape5::setscalingStrokes( bool v ) {
		scalingStrokes = v;
	}
StyleList *DefineShape5::getstyles() {
		return &styles;
	}
Shape *DefineShape5::getshapes() {
		return &shapes;
	}
DefineMorphShape::DefineMorphShape() {
	objectID = 0;
}
DefineMorphShape::~DefineMorphShape() {
}
DefineMorphShape* DefineMorphShape::get( Reader *r, int end, Context *ctx ) {
	DefineMorphShape* ret = new DefineMorphShape;
	ret->parse( r, end, ctx );
	return ret;
}
DefineMorphShape* DefineMorphShape::getByName( const char *name ) {
	if( strcmp( name, "DefineMorphShape" ) ) return NULL;
	DefineMorphShape* ret = new DefineMorphShape;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineMorphShape::getobjectID() {
		return objectID;
	}
	void DefineMorphShape::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rest *DefineMorphShape::getdata() {
		return &data;
	}
DefineFontInfo2::DefineFontInfo2() {
	objectID = 0;
nameLength = 0;
nameData = NULL;
reserved = 0;
smallTextOrUnicode = 0;
isShiftJIS = 0;
isANSII = 0;
isItalic = 0;
isBold = 0;
isWide = 0;
language = 0;
}
DefineFontInfo2::~DefineFontInfo2() {
	delete[] nameData;
}
DefineFontInfo2* DefineFontInfo2::get( Reader *r, int end, Context *ctx ) {
	DefineFontInfo2* ret = new DefineFontInfo2;
	ret->parse( r, end, ctx );
	return ret;
}
DefineFontInfo2* DefineFontInfo2::getByName( const char *name ) {
	if( strcmp( name, "DefineFontInfo2" ) ) return NULL;
	DefineFontInfo2* ret = new DefineFontInfo2;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineFontInfo2::getobjectID() {
		return objectID;
	}
	void DefineFontInfo2::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned char DefineFontInfo2::getnameLength() {
		return nameLength;
	}
	void DefineFontInfo2::setnameLength( unsigned char v ) {
		nameLength = v;
	}
		void DefineFontInfo2::getnameData( unsigned char **dst, int *size ) {
			*dst = nameData;
			*size = nameLength;
		}
		void DefineFontInfo2::setnameData( const unsigned char *src, int size ) {
			delete nameData;
			nameLength = size;
			nameData = new unsigned char[ size ];
			memcpy( nameData, src, size ); 
		}
	// NBitInt
	int DefineFontInfo2::getreserved() {
		return reserved;
	}
	void DefineFontInfo2::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo2::getsmallTextOrUnicode() {
		return smallTextOrUnicode;
	}
	void DefineFontInfo2::setsmallTextOrUnicode( bool v ) {
		smallTextOrUnicode = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo2::getisShiftJIS() {
		return isShiftJIS;
	}
	void DefineFontInfo2::setisShiftJIS( bool v ) {
		isShiftJIS = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo2::getisANSII() {
		return isANSII;
	}
	void DefineFontInfo2::setisANSII( bool v ) {
		isANSII = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo2::getisItalic() {
		return isItalic;
	}
	void DefineFontInfo2::setisItalic( bool v ) {
		isItalic = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo2::getisBold() {
		return isBold;
	}
	void DefineFontInfo2::setisBold( bool v ) {
		isBold = v;
	}
	// Constant Size Primitive
	bool DefineFontInfo2::getisWide() {
		return isWide;
	}
	void DefineFontInfo2::setisWide( bool v ) {
		isWide = v;
	}
	// Constant Size Primitive
	unsigned char DefineFontInfo2::getlanguage() {
		return language;
	}
	void DefineFontInfo2::setlanguage( unsigned char v ) {
		language = v;
	}
Rest *DefineFontInfo2::getmap() {
		return &map;
	}
SoundStreamHead::SoundStreamHead() {
	reserved = 0;
playbackRate = 0;
playbackSize = 0;
playbackStereo = 0;
compression = 0;
soundRate = 0;
soundSize = 0;
soundStereo = 0;
sampleSize = 0;
}
SoundStreamHead::~SoundStreamHead() {
}
SoundStreamHead* SoundStreamHead::get( Reader *r, int end, Context *ctx ) {
	SoundStreamHead* ret = new SoundStreamHead;
	ret->parse( r, end, ctx );
	return ret;
}
SoundStreamHead* SoundStreamHead::getByName( const char *name ) {
	if( strcmp( name, "SoundStreamHead" ) ) return NULL;
	SoundStreamHead* ret = new SoundStreamHead;
	return ret;
}
	// Constant Size Primitive
	int SoundStreamHead::getreserved() {
		return reserved;
	}
	void SoundStreamHead::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	int SoundStreamHead::getplaybackRate() {
		return playbackRate;
	}
	void SoundStreamHead::setplaybackRate( int v ) {
		playbackRate = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead::getplaybackSize() {
		return playbackSize;
	}
	void SoundStreamHead::setplaybackSize( bool v ) {
		playbackSize = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead::getplaybackStereo() {
		return playbackStereo;
	}
	void SoundStreamHead::setplaybackStereo( bool v ) {
		playbackStereo = v;
	}
	// Constant Size Primitive
	int SoundStreamHead::getcompression() {
		return compression;
	}
	void SoundStreamHead::setcompression( int v ) {
		compression = v;
	}
	// Constant Size Primitive
	int SoundStreamHead::getsoundRate() {
		return soundRate;
	}
	void SoundStreamHead::setsoundRate( int v ) {
		soundRate = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead::getsoundSize() {
		return soundSize;
	}
	void SoundStreamHead::setsoundSize( bool v ) {
		soundSize = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead::getsoundStereo() {
		return soundStereo;
	}
	void SoundStreamHead::setsoundStereo( bool v ) {
		soundStereo = v;
	}
	// Constant Size Primitive
	unsigned short SoundStreamHead::getsampleSize() {
		return sampleSize;
	}
	void SoundStreamHead::setsampleSize( unsigned short v ) {
		sampleSize = v;
	}
Rest *SoundStreamHead::getlatencySeek() {
		return &latencySeek;
	}
DefineBitsLossless::DefineBitsLossless() {
	objectID = 0;
format = 0;
width = 0;
height = 0;
n_colormap = 0;
}
DefineBitsLossless::~DefineBitsLossless() {
}
DefineBitsLossless* DefineBitsLossless::get( Reader *r, int end, Context *ctx ) {
	DefineBitsLossless* ret = new DefineBitsLossless;
	ret->parse( r, end, ctx );
	return ret;
}
DefineBitsLossless* DefineBitsLossless::getByName( const char *name ) {
	if( strcmp( name, "DefineBitsLossless" ) ) return NULL;
	DefineBitsLossless* ret = new DefineBitsLossless;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineBitsLossless::getobjectID() {
		return objectID;
	}
	void DefineBitsLossless::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned char DefineBitsLossless::getformat() {
		return format;
	}
	void DefineBitsLossless::setformat( unsigned char v ) {
		format = v;
	}
	// Constant Size Primitive
	unsigned short DefineBitsLossless::getwidth() {
		return width;
	}
	void DefineBitsLossless::setwidth( unsigned short v ) {
		width = v;
	}
	// Constant Size Primitive
	unsigned short DefineBitsLossless::getheight() {
		return height;
	}
	void DefineBitsLossless::setheight( unsigned short v ) {
		height = v;
	}
	// Constant Size Primitive
	unsigned char DefineBitsLossless::getn_colormap() {
		return n_colormap;
	}
	void DefineBitsLossless::setn_colormap( unsigned char v ) {
		n_colormap = v;
	}
Rest *DefineBitsLossless::getdata() {
		return &data;
	}
DefineBitsJPEG2::DefineBitsJPEG2() {
	objectID = 0;
}
DefineBitsJPEG2::~DefineBitsJPEG2() {
}
DefineBitsJPEG2* DefineBitsJPEG2::get( Reader *r, int end, Context *ctx ) {
	DefineBitsJPEG2* ret = new DefineBitsJPEG2;
	ret->parse( r, end, ctx );
	return ret;
}
DefineBitsJPEG2* DefineBitsJPEG2::getByName( const char *name ) {
	if( strcmp( name, "DefineBitsJPEG2" ) ) return NULL;
	DefineBitsJPEG2* ret = new DefineBitsJPEG2;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineBitsJPEG2::getobjectID() {
		return objectID;
	}
	void DefineBitsJPEG2::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rest *DefineBitsJPEG2::getdata() {
		return &data;
	}
DefineBitsJPEG3::DefineBitsJPEG3() {
	objectID = 0;
offset_to_alpha = 0;
}
DefineBitsJPEG3::~DefineBitsJPEG3() {
}
DefineBitsJPEG3* DefineBitsJPEG3::get( Reader *r, int end, Context *ctx ) {
	DefineBitsJPEG3* ret = new DefineBitsJPEG3;
	ret->parse( r, end, ctx );
	return ret;
}
DefineBitsJPEG3* DefineBitsJPEG3::getByName( const char *name ) {
	if( strcmp( name, "DefineBitsJPEG3" ) ) return NULL;
	DefineBitsJPEG3* ret = new DefineBitsJPEG3;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineBitsJPEG3::getobjectID() {
		return objectID;
	}
	void DefineBitsJPEG3::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned int DefineBitsJPEG3::getoffset_to_alpha() {
		return offset_to_alpha;
	}
	void DefineBitsJPEG3::setoffset_to_alpha( unsigned int v ) {
		offset_to_alpha = v;
	}
Rest *DefineBitsJPEG3::getdata() {
		return &data;
	}
DefineBitsLossless2::DefineBitsLossless2() {
	objectID = 0;
format = 0;
width = 0;
height = 0;
n_colormap = 0;
}
DefineBitsLossless2::~DefineBitsLossless2() {
}
DefineBitsLossless2* DefineBitsLossless2::get( Reader *r, int end, Context *ctx ) {
	DefineBitsLossless2* ret = new DefineBitsLossless2;
	ret->parse( r, end, ctx );
	return ret;
}
DefineBitsLossless2* DefineBitsLossless2::getByName( const char *name ) {
	if( strcmp( name, "DefineBitsLossless2" ) ) return NULL;
	DefineBitsLossless2* ret = new DefineBitsLossless2;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineBitsLossless2::getobjectID() {
		return objectID;
	}
	void DefineBitsLossless2::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned char DefineBitsLossless2::getformat() {
		return format;
	}
	void DefineBitsLossless2::setformat( unsigned char v ) {
		format = v;
	}
	// Constant Size Primitive
	unsigned short DefineBitsLossless2::getwidth() {
		return width;
	}
	void DefineBitsLossless2::setwidth( unsigned short v ) {
		width = v;
	}
	// Constant Size Primitive
	unsigned short DefineBitsLossless2::getheight() {
		return height;
	}
	void DefineBitsLossless2::setheight( unsigned short v ) {
		height = v;
	}
	// Constant Size Primitive
	unsigned char DefineBitsLossless2::getn_colormap() {
		return n_colormap;
	}
	void DefineBitsLossless2::setn_colormap( unsigned char v ) {
		n_colormap = v;
	}
Rest *DefineBitsLossless2::getdata() {
		return &data;
	}
PlaceObject2::PlaceObject2() {
	hasEventHandler = 0;
hasClipDepth = 0;
hasName = 0;
hasMorph = 0;
hasColorTransform = 0;
hasTransform = 0;
hasID = 0;
replace = 0;
depth = 0;
objectID = 0;
morph = 0;
name = NULL;
clipDepth = 0;
reserved = 0;
allflags1 = 0;
allflags2 = 0;
}
PlaceObject2::~PlaceObject2() {
	delete[] name;
}
PlaceObject2* PlaceObject2::get( Reader *r, int end, Context *ctx ) {
	PlaceObject2* ret = new PlaceObject2;
	ret->parse( r, end, ctx );
	return ret;
}
PlaceObject2* PlaceObject2::getByName( const char *name ) {
	if( strcmp( name, "PlaceObject2" ) ) return NULL;
	PlaceObject2* ret = new PlaceObject2;
	return ret;
}
	// Constant Size Primitive
	bool PlaceObject2::gethasEventHandler() {
		return hasEventHandler;
	}
	void PlaceObject2::sethasEventHandler( bool v ) {
		hasEventHandler = v;
	}
	// Constant Size Primitive
	bool PlaceObject2::gethasClipDepth() {
		return hasClipDepth;
	}
	void PlaceObject2::sethasClipDepth( bool v ) {
		hasClipDepth = v;
	}
	// Constant Size Primitive
	bool PlaceObject2::gethasName() {
		return hasName;
	}
	void PlaceObject2::sethasName( bool v ) {
		hasName = v;
	}
	// Constant Size Primitive
	bool PlaceObject2::gethasMorph() {
		return hasMorph;
	}
	void PlaceObject2::sethasMorph( bool v ) {
		hasMorph = v;
	}
	// Constant Size Primitive
	bool PlaceObject2::gethasColorTransform() {
		return hasColorTransform;
	}
	void PlaceObject2::sethasColorTransform( bool v ) {
		hasColorTransform = v;
	}
	// Constant Size Primitive
	bool PlaceObject2::gethasTransform() {
		return hasTransform;
	}
	void PlaceObject2::sethasTransform( bool v ) {
		hasTransform = v;
	}
	// Constant Size Primitive
	bool PlaceObject2::gethasID() {
		return hasID;
	}
	void PlaceObject2::sethasID( bool v ) {
		hasID = v;
	}
	// Constant Size Primitive
	bool PlaceObject2::getreplace() {
		return replace;
	}
	void PlaceObject2::setreplace( bool v ) {
		replace = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject2::getdepth() {
		return depth;
	}
	void PlaceObject2::setdepth( unsigned short v ) {
		depth = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject2::getobjectID() {
		return objectID;
	}
	void PlaceObject2::setobjectID( unsigned short v ) {
		objectID = v;
	}
Transform *PlaceObject2::gettransform() {
		return &transform;
	}
ColorTransform2 *PlaceObject2::getcolorTransform() {
		return &colorTransform;
	}
	// Constant Size Primitive
	unsigned short PlaceObject2::getmorph() {
		return morph;
	}
	void PlaceObject2::setmorph( unsigned short v ) {
		morph = v;
	}
char * PlaceObject2::getname() {
		return name;
	}
	void PlaceObject2::setname( char * v ) {
		delete name;
		name = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject2::getclipDepth() {
		return clipDepth;
	}
	void PlaceObject2::setclipDepth( unsigned short v ) {
		clipDepth = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject2::getreserved() {
		return reserved;
	}
	void PlaceObject2::setreserved( unsigned short v ) {
		reserved = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject2::getallflags1() {
		return allflags1;
	}
	void PlaceObject2::setallflags1( unsigned short v ) {
		allflags1 = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject2::getallflags2() {
		return allflags2;
	}
	void PlaceObject2::setallflags2( unsigned short v ) {
		allflags2 = v;
	}
List<Event> *PlaceObject2::getevents() {
		return &events;
	}
RemoveObject2::RemoveObject2() {
	depth = 0;
}
RemoveObject2::~RemoveObject2() {
}
RemoveObject2* RemoveObject2::get( Reader *r, int end, Context *ctx ) {
	RemoveObject2* ret = new RemoveObject2;
	ret->parse( r, end, ctx );
	return ret;
}
RemoveObject2* RemoveObject2::getByName( const char *name ) {
	if( strcmp( name, "RemoveObject2" ) ) return NULL;
	RemoveObject2* ret = new RemoveObject2;
	return ret;
}
	// Constant Size Primitive
	unsigned short RemoveObject2::getdepth() {
		return depth;
	}
	void RemoveObject2::setdepth( unsigned short v ) {
		depth = v;
	}
DefineEditText::DefineEditText() {
	objectID = 0;
hasText = 0;
wordWrap = 0;
multiLine = 0;
password = 0;
readOnly = 0;
hasColor = 0;
hasMaxLength = 0;
hasFont = 0;
reserved = 0;
autoSize = 0;
hasLayout = 0;
notSelectable = 0;
hasBorder = 0;
reserved2 = 0;
isHTML = 0;
useOutlines = 0;
fontRef = 0;
fontHeight = 0;
maxLength = 0;
align = 0;
leftMargin = 0;
rightMargin = 0;
indent = 0;
leading = 0;
variableName = NULL;
initialText = NULL;
}
DefineEditText::~DefineEditText() {
	delete[] variableName;
	delete[] initialText;
}
DefineEditText* DefineEditText::get( Reader *r, int end, Context *ctx ) {
	DefineEditText* ret = new DefineEditText;
	ret->parse( r, end, ctx );
	return ret;
}
DefineEditText* DefineEditText::getByName( const char *name ) {
	if( strcmp( name, "DefineEditText" ) ) return NULL;
	DefineEditText* ret = new DefineEditText;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineEditText::getobjectID() {
		return objectID;
	}
	void DefineEditText::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineEditText::getsize() {
		return &size;
	}
	// Constant Size Primitive
	bool DefineEditText::gethasText() {
		return hasText;
	}
	void DefineEditText::sethasText( bool v ) {
		hasText = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getwordWrap() {
		return wordWrap;
	}
	void DefineEditText::setwordWrap( bool v ) {
		wordWrap = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getmultiLine() {
		return multiLine;
	}
	void DefineEditText::setmultiLine( bool v ) {
		multiLine = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getpassword() {
		return password;
	}
	void DefineEditText::setpassword( bool v ) {
		password = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getreadOnly() {
		return readOnly;
	}
	void DefineEditText::setreadOnly( bool v ) {
		readOnly = v;
	}
	// Constant Size Primitive
	bool DefineEditText::gethasColor() {
		return hasColor;
	}
	void DefineEditText::sethasColor( bool v ) {
		hasColor = v;
	}
	// Constant Size Primitive
	bool DefineEditText::gethasMaxLength() {
		return hasMaxLength;
	}
	void DefineEditText::sethasMaxLength( bool v ) {
		hasMaxLength = v;
	}
	// Constant Size Primitive
	bool DefineEditText::gethasFont() {
		return hasFont;
	}
	void DefineEditText::sethasFont( bool v ) {
		hasFont = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getreserved() {
		return reserved;
	}
	void DefineEditText::setreserved( bool v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getautoSize() {
		return autoSize;
	}
	void DefineEditText::setautoSize( bool v ) {
		autoSize = v;
	}
	// Constant Size Primitive
	bool DefineEditText::gethasLayout() {
		return hasLayout;
	}
	void DefineEditText::sethasLayout( bool v ) {
		hasLayout = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getnotSelectable() {
		return notSelectable;
	}
	void DefineEditText::setnotSelectable( bool v ) {
		notSelectable = v;
	}
	// Constant Size Primitive
	bool DefineEditText::gethasBorder() {
		return hasBorder;
	}
	void DefineEditText::sethasBorder( bool v ) {
		hasBorder = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getreserved2() {
		return reserved2;
	}
	void DefineEditText::setreserved2( bool v ) {
		reserved2 = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getisHTML() {
		return isHTML;
	}
	void DefineEditText::setisHTML( bool v ) {
		isHTML = v;
	}
	// Constant Size Primitive
	bool DefineEditText::getuseOutlines() {
		return useOutlines;
	}
	void DefineEditText::setuseOutlines( bool v ) {
		useOutlines = v;
	}
	// Constant Size Primitive
	unsigned short DefineEditText::getfontRef() {
		return fontRef;
	}
	void DefineEditText::setfontRef( unsigned short v ) {
		fontRef = v;
	}
	// Constant Size Primitive
	unsigned short DefineEditText::getfontHeight() {
		return fontHeight;
	}
	void DefineEditText::setfontHeight( unsigned short v ) {
		fontHeight = v;
	}
Color *DefineEditText::getcolor() {
		return &color;
	}
	// Constant Size Primitive
	unsigned short DefineEditText::getmaxLength() {
		return maxLength;
	}
	void DefineEditText::setmaxLength( unsigned short v ) {
		maxLength = v;
	}
	// Constant Size Primitive
	unsigned char DefineEditText::getalign() {
		return align;
	}
	void DefineEditText::setalign( unsigned char v ) {
		align = v;
	}
	// Constant Size Primitive
	unsigned short DefineEditText::getleftMargin() {
		return leftMargin;
	}
	void DefineEditText::setleftMargin( unsigned short v ) {
		leftMargin = v;
	}
	// Constant Size Primitive
	unsigned short DefineEditText::getrightMargin() {
		return rightMargin;
	}
	void DefineEditText::setrightMargin( unsigned short v ) {
		rightMargin = v;
	}
	// Constant Size Primitive
	unsigned short DefineEditText::getindent() {
		return indent;
	}
	void DefineEditText::setindent( unsigned short v ) {
		indent = v;
	}
	// Constant Size Primitive
	unsigned short DefineEditText::getleading() {
		return leading;
	}
	void DefineEditText::setleading( unsigned short v ) {
		leading = v;
	}
char * DefineEditText::getvariableName() {
		return variableName;
	}
	void DefineEditText::setvariableName( char * v ) {
		delete variableName;
		variableName = v;
	}
char * DefineEditText::getinitialText() {
		return initialText;
	}
	void DefineEditText::setinitialText( char * v ) {
		delete initialText;
		initialText = v;
	}
DefineSprite::DefineSprite() {
	objectID = 0;
frames = 0;
}
DefineSprite::~DefineSprite() {
}
DefineSprite* DefineSprite::get( Reader *r, int end, Context *ctx ) {
	DefineSprite* ret = new DefineSprite;
	ret->parse( r, end, ctx );
	return ret;
}
DefineSprite* DefineSprite::getByName( const char *name ) {
	if( strcmp( name, "DefineSprite" ) ) return NULL;
	DefineSprite* ret = new DefineSprite;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineSprite::getobjectID() {
		return objectID;
	}
	void DefineSprite::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned short DefineSprite::getframes() {
		return frames;
	}
	void DefineSprite::setframes( unsigned short v ) {
		frames = v;
	}
List<Tag> *DefineSprite::gettags() {
		return &tags;
	}
FrameLabel::FrameLabel() {
	label = NULL;
}
FrameLabel::~FrameLabel() {
	delete[] label;
}
FrameLabel* FrameLabel::get( Reader *r, int end, Context *ctx ) {
	FrameLabel* ret = new FrameLabel;
	ret->parse( r, end, ctx );
	return ret;
}
FrameLabel* FrameLabel::getByName( const char *name ) {
	if( strcmp( name, "FrameLabel" ) ) return NULL;
	FrameLabel* ret = new FrameLabel;
	return ret;
}
char * FrameLabel::getlabel() {
		return label;
	}
	void FrameLabel::setlabel( char * v ) {
		delete label;
		label = v;
	}
Rest *FrameLabel::getflags() {
		return &flags;
	}
SoundStreamHead2::SoundStreamHead2() {
	reserved = 0;
playbackRate = 0;
playbackSize = 0;
playbackStereo = 0;
compression = 0;
soundRate = 0;
soundSize = 0;
soundStereo = 0;
sampleSize = 0;
}
SoundStreamHead2::~SoundStreamHead2() {
}
SoundStreamHead2* SoundStreamHead2::get( Reader *r, int end, Context *ctx ) {
	SoundStreamHead2* ret = new SoundStreamHead2;
	ret->parse( r, end, ctx );
	return ret;
}
SoundStreamHead2* SoundStreamHead2::getByName( const char *name ) {
	if( strcmp( name, "SoundStreamHead2" ) ) return NULL;
	SoundStreamHead2* ret = new SoundStreamHead2;
	return ret;
}
	// Constant Size Primitive
	int SoundStreamHead2::getreserved() {
		return reserved;
	}
	void SoundStreamHead2::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	int SoundStreamHead2::getplaybackRate() {
		return playbackRate;
	}
	void SoundStreamHead2::setplaybackRate( int v ) {
		playbackRate = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead2::getplaybackSize() {
		return playbackSize;
	}
	void SoundStreamHead2::setplaybackSize( bool v ) {
		playbackSize = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead2::getplaybackStereo() {
		return playbackStereo;
	}
	void SoundStreamHead2::setplaybackStereo( bool v ) {
		playbackStereo = v;
	}
	// Constant Size Primitive
	int SoundStreamHead2::getcompression() {
		return compression;
	}
	void SoundStreamHead2::setcompression( int v ) {
		compression = v;
	}
	// Constant Size Primitive
	int SoundStreamHead2::getsoundRate() {
		return soundRate;
	}
	void SoundStreamHead2::setsoundRate( int v ) {
		soundRate = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead2::getsoundSize() {
		return soundSize;
	}
	void SoundStreamHead2::setsoundSize( bool v ) {
		soundSize = v;
	}
	// Constant Size Primitive
	bool SoundStreamHead2::getsoundStereo() {
		return soundStereo;
	}
	void SoundStreamHead2::setsoundStereo( bool v ) {
		soundStereo = v;
	}
	// Constant Size Primitive
	unsigned short SoundStreamHead2::getsampleSize() {
		return sampleSize;
	}
	void SoundStreamHead2::setsampleSize( unsigned short v ) {
		sampleSize = v;
	}
Rest *SoundStreamHead2::getlatencySeek() {
		return &latencySeek;
	}
DefineFont::DefineFont() {
	objectID = 0;
}
DefineFont::~DefineFont() {
}
DefineFont* DefineFont::get( Reader *r, int end, Context *ctx ) {
	DefineFont* ret = new DefineFont;
	ret->parse( r, end, ctx );
	return ret;
}
DefineFont* DefineFont::getByName( const char *name ) {
	if( strcmp( name, "DefineFont" ) ) return NULL;
	DefineFont* ret = new DefineFont;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineFont::getobjectID() {
		return objectID;
	}
	void DefineFont::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rest *DefineFont::getdata() {
		return &data;
	}
DefineFont2::DefineFont2() {
	objectID = 0;
hasLayout = 0;
isShiftJIS = 0;
isUnicode = 0;
isANSII = 0;
wideGlyphOffsets = 0;
wideMap = 0;
italic = 0;
bold = 0;
language = 0;
name = NULL;
glyphCount = 0;
ascent = 0;
descent = 0;
leading = 0;
kerningCount = 0;
}
DefineFont2::~DefineFont2() {
	delete[] name;
}
DefineFont2* DefineFont2::get( Reader *r, int end, Context *ctx ) {
	DefineFont2* ret = new DefineFont2;
	ret->parse( r, end, ctx );
	return ret;
}
DefineFont2* DefineFont2::getByName( const char *name ) {
	if( strcmp( name, "DefineFont2" ) ) return NULL;
	DefineFont2* ret = new DefineFont2;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineFont2::getobjectID() {
		return objectID;
	}
	void DefineFont2::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	bool DefineFont2::gethasLayout() {
		return hasLayout;
	}
	void DefineFont2::sethasLayout( bool v ) {
		hasLayout = v;
	}
	// Constant Size Primitive
	bool DefineFont2::getisShiftJIS() {
		return isShiftJIS;
	}
	void DefineFont2::setisShiftJIS( bool v ) {
		isShiftJIS = v;
	}
	// Constant Size Primitive
	bool DefineFont2::getisUnicode() {
		return isUnicode;
	}
	void DefineFont2::setisUnicode( bool v ) {
		isUnicode = v;
	}
	// Constant Size Primitive
	bool DefineFont2::getisANSII() {
		return isANSII;
	}
	void DefineFont2::setisANSII( bool v ) {
		isANSII = v;
	}
	// Constant Size Primitive
	bool DefineFont2::getwideGlyphOffsets() {
		return wideGlyphOffsets;
	}
	void DefineFont2::setwideGlyphOffsets( bool v ) {
		wideGlyphOffsets = v;
	}
	// Constant Size Primitive
	bool DefineFont2::getwideMap() {
		return wideMap;
	}
	void DefineFont2::setwideMap( bool v ) {
		wideMap = v;
	}
	// Constant Size Primitive
	bool DefineFont2::getitalic() {
		return italic;
	}
	void DefineFont2::setitalic( bool v ) {
		italic = v;
	}
	// Constant Size Primitive
	bool DefineFont2::getbold() {
		return bold;
	}
	void DefineFont2::setbold( bool v ) {
		bold = v;
	}
	// Constant Size Primitive
	unsigned char DefineFont2::getlanguage() {
		return language;
	}
	void DefineFont2::setlanguage( unsigned char v ) {
		language = v;
	}
char * DefineFont2::getname() {
		return name;
	}
	void DefineFont2::setname( char * v ) {
		delete name;
		name = v;
	}
	// Constant Size Primitive
	unsigned short DefineFont2::getglyphCount() {
		return glyphCount;
	}
	void DefineFont2::setglyphCount( unsigned short v ) {
		glyphCount = v;
	}
GlyphList *DefineFont2::getglyphs() {
		return &glyphs;
	}
	// Constant Size Primitive
	unsigned short DefineFont2::getascent() {
		return ascent;
	}
	void DefineFont2::setascent( unsigned short v ) {
		ascent = v;
	}
	// Constant Size Primitive
	unsigned short DefineFont2::getdescent() {
		return descent;
	}
	void DefineFont2::setdescent( unsigned short v ) {
		descent = v;
	}
	// Constant Size Primitive
	unsigned short DefineFont2::getleading() {
		return leading;
	}
	void DefineFont2::setleading( unsigned short v ) {
		leading = v;
	}
List<Short> *DefineFont2::getadvance() {
		return &advance;
	}
List<Rectangle> *DefineFont2::getbounds() {
		return &bounds;
	}
	// Constant Size Primitive
	unsigned short DefineFont2::getkerningCount() {
		return kerningCount;
	}
	void DefineFont2::setkerningCount( unsigned short v ) {
		kerningCount = v;
	}
List<WideKerning> *DefineFont2::getwideKerning() {
		return &wideKerning;
	}
List<Kerning> *DefineFont2::getkerning() {
		return &kerning;
	}
DefineFont3::DefineFont3() {
	objectID = 0;
hasLayout = 0;
isShiftJIS = 0;
isUnicode = 0;
isANSII = 0;
wideGlyphOffsets = 0;
wideMap = 0;
italic = 0;
bold = 0;
language = 0;
name = NULL;
glyphCount = 0;
ascent = 0;
descent = 0;
leading = 0;
kerningCount = 0;
}
DefineFont3::~DefineFont3() {
	delete[] name;
}
DefineFont3* DefineFont3::get( Reader *r, int end, Context *ctx ) {
	DefineFont3* ret = new DefineFont3;
	ret->parse( r, end, ctx );
	return ret;
}
DefineFont3* DefineFont3::getByName( const char *name ) {
	if( strcmp( name, "DefineFont3" ) ) return NULL;
	DefineFont3* ret = new DefineFont3;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineFont3::getobjectID() {
		return objectID;
	}
	void DefineFont3::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	bool DefineFont3::gethasLayout() {
		return hasLayout;
	}
	void DefineFont3::sethasLayout( bool v ) {
		hasLayout = v;
	}
	// Constant Size Primitive
	bool DefineFont3::getisShiftJIS() {
		return isShiftJIS;
	}
	void DefineFont3::setisShiftJIS( bool v ) {
		isShiftJIS = v;
	}
	// Constant Size Primitive
	bool DefineFont3::getisUnicode() {
		return isUnicode;
	}
	void DefineFont3::setisUnicode( bool v ) {
		isUnicode = v;
	}
	// Constant Size Primitive
	bool DefineFont3::getisANSII() {
		return isANSII;
	}
	void DefineFont3::setisANSII( bool v ) {
		isANSII = v;
	}
	// Constant Size Primitive
	bool DefineFont3::getwideGlyphOffsets() {
		return wideGlyphOffsets;
	}
	void DefineFont3::setwideGlyphOffsets( bool v ) {
		wideGlyphOffsets = v;
	}
	// Constant Size Primitive
	bool DefineFont3::getwideMap() {
		return wideMap;
	}
	void DefineFont3::setwideMap( bool v ) {
		wideMap = v;
	}
	// Constant Size Primitive
	bool DefineFont3::getitalic() {
		return italic;
	}
	void DefineFont3::setitalic( bool v ) {
		italic = v;
	}
	// Constant Size Primitive
	bool DefineFont3::getbold() {
		return bold;
	}
	void DefineFont3::setbold( bool v ) {
		bold = v;
	}
	// Constant Size Primitive
	unsigned char DefineFont3::getlanguage() {
		return language;
	}
	void DefineFont3::setlanguage( unsigned char v ) {
		language = v;
	}
char * DefineFont3::getname() {
		return name;
	}
	void DefineFont3::setname( char * v ) {
		delete name;
		name = v;
	}
	// Constant Size Primitive
	unsigned short DefineFont3::getglyphCount() {
		return glyphCount;
	}
	void DefineFont3::setglyphCount( unsigned short v ) {
		glyphCount = v;
	}
GlyphList *DefineFont3::getglyphs() {
		return &glyphs;
	}
	// Constant Size Primitive
	unsigned short DefineFont3::getascent() {
		return ascent;
	}
	void DefineFont3::setascent( unsigned short v ) {
		ascent = v;
	}
	// Constant Size Primitive
	unsigned short DefineFont3::getdescent() {
		return descent;
	}
	void DefineFont3::setdescent( unsigned short v ) {
		descent = v;
	}
	// Constant Size Primitive
	unsigned short DefineFont3::getleading() {
		return leading;
	}
	void DefineFont3::setleading( unsigned short v ) {
		leading = v;
	}
List<Short> *DefineFont3::getadvance() {
		return &advance;
	}
List<Rectangle> *DefineFont3::getbounds() {
		return &bounds;
	}
	// Constant Size Primitive
	unsigned short DefineFont3::getkerningCount() {
		return kerningCount;
	}
	void DefineFont3::setkerningCount( unsigned short v ) {
		kerningCount = v;
	}
List<WideKerning> *DefineFont3::getwideKerning() {
		return &wideKerning;
	}
List<Kerning> *DefineFont3::getkerning() {
		return &kerning;
	}
DefineButton::DefineButton() {
	objectID = 0;
}
DefineButton::~DefineButton() {
}
DefineButton* DefineButton::get( Reader *r, int end, Context *ctx ) {
	DefineButton* ret = new DefineButton;
	ret->parse( r, end, ctx );
	return ret;
}
DefineButton* DefineButton::getByName( const char *name ) {
	if( strcmp( name, "DefineButton" ) ) return NULL;
	DefineButton* ret = new DefineButton;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineButton::getobjectID() {
		return objectID;
	}
	void DefineButton::setobjectID( unsigned short v ) {
		objectID = v;
	}
List<Button> *DefineButton::getbuttons() {
		return &buttons;
	}
List<Action> *DefineButton::getactions() {
		return &actions;
	}
DefineButton2::DefineButton2() {
	objectID = 0;
reserved = 0;
menu = 0;
buttonsSize = 0;
}
DefineButton2::~DefineButton2() {
}
DefineButton2* DefineButton2::get( Reader *r, int end, Context *ctx ) {
	DefineButton2* ret = new DefineButton2;
	ret->parse( r, end, ctx );
	return ret;
}
DefineButton2* DefineButton2::getByName( const char *name ) {
	if( strcmp( name, "DefineButton2" ) ) return NULL;
	DefineButton2* ret = new DefineButton2;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineButton2::getobjectID() {
		return objectID;
	}
	void DefineButton2::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	int DefineButton2::getreserved() {
		return reserved;
	}
	void DefineButton2::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool DefineButton2::getmenu() {
		return menu;
	}
	void DefineButton2::setmenu( bool v ) {
		menu = v;
	}
	// Constant Size Primitive
	unsigned short DefineButton2::getbuttonsSize() {
		return buttonsSize;
	}
	void DefineButton2::setbuttonsSize( unsigned short v ) {
		buttonsSize = v;
	}
List<Button> *DefineButton2::getbuttons() {
		return &buttons;
	}
List<Condition> *DefineButton2::getconditions() {
		return &conditions;
	}
Export::Export() {
	count = 0;
}
Export::~Export() {
}
Export* Export::get( Reader *r, int end, Context *ctx ) {
	Export* ret = new Export;
	ret->parse( r, end, ctx );
	return ret;
}
Export* Export::getByName( const char *name ) {
	if( strcmp( name, "Export" ) ) return NULL;
	Export* ret = new Export;
	return ret;
}
	// Constant Size Primitive
	unsigned short Export::getcount() {
		return count;
	}
	void Export::setcount( unsigned short v ) {
		count = v;
	}
List<Symbol> *Export::getsymbols() {
		return &symbols;
	}
Import::Import() {
	url = NULL;
count = 0;
}
Import::~Import() {
	delete[] url;
}
Import* Import::get( Reader *r, int end, Context *ctx ) {
	Import* ret = new Import;
	ret->parse( r, end, ctx );
	return ret;
}
Import* Import::getByName( const char *name ) {
	if( strcmp( name, "Import" ) ) return NULL;
	Import* ret = new Import;
	return ret;
}
char * Import::geturl() {
		return url;
	}
	void Import::seturl( char * v ) {
		delete url;
		url = v;
	}
	// Constant Size Primitive
	unsigned short Import::getcount() {
		return count;
	}
	void Import::setcount( unsigned short v ) {
		count = v;
	}
List<Symbol> *Import::getsymbols() {
		return &symbols;
	}
DoInitAction::DoInitAction() {
	sprite = 0;
}
DoInitAction::~DoInitAction() {
}
DoInitAction* DoInitAction::get( Reader *r, int end, Context *ctx ) {
	DoInitAction* ret = new DoInitAction;
	ret->parse( r, end, ctx );
	return ret;
}
DoInitAction* DoInitAction::getByName( const char *name ) {
	if( strcmp( name, "DoInitAction" ) ) return NULL;
	DoInitAction* ret = new DoInitAction;
	return ret;
}
	// Constant Size Primitive
	unsigned short DoInitAction::getsprite() {
		return sprite;
	}
	void DoInitAction::setsprite( unsigned short v ) {
		sprite = v;
	}
List<Action> *DoInitAction::getactions() {
		return &actions;
	}
SoundStreamBlock::SoundStreamBlock() {
	data = NULL;
}
SoundStreamBlock::~SoundStreamBlock() {
	delete[] data;
}
SoundStreamBlock* SoundStreamBlock::get( Reader *r, int end, Context *ctx ) {
	SoundStreamBlock* ret = new SoundStreamBlock;
	ret->parse( r, end, ctx );
	return ret;
}
SoundStreamBlock* SoundStreamBlock::getByName( const char *name ) {
	if( strcmp( name, "SoundStreamBlock" ) ) return NULL;
	SoundStreamBlock* ret = new SoundStreamBlock;
	return ret;
}
		void SoundStreamBlock::getdata( unsigned char **dst, int *size ) {
			*dst = data;
			*size = len;
		}
		void SoundStreamBlock::setdata( const unsigned char *src, int size ) {
			delete data;
			len = size;
			data = new unsigned char[ size ];
			memcpy( data, src, size ); 
		}
DefineVideoStream::DefineVideoStream() {
	objectID = 0;
frames = 0;
width = 0;
height = 0;
reserved = 0;
deblocking = 0;
smoothing = 0;
codec = 0;
}
DefineVideoStream::~DefineVideoStream() {
}
DefineVideoStream* DefineVideoStream::get( Reader *r, int end, Context *ctx ) {
	DefineVideoStream* ret = new DefineVideoStream;
	ret->parse( r, end, ctx );
	return ret;
}
DefineVideoStream* DefineVideoStream::getByName( const char *name ) {
	if( strcmp( name, "DefineVideoStream" ) ) return NULL;
	DefineVideoStream* ret = new DefineVideoStream;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineVideoStream::getobjectID() {
		return objectID;
	}
	void DefineVideoStream::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned short DefineVideoStream::getframes() {
		return frames;
	}
	void DefineVideoStream::setframes( unsigned short v ) {
		frames = v;
	}
	// Constant Size Primitive
	unsigned short DefineVideoStream::getwidth() {
		return width;
	}
	void DefineVideoStream::setwidth( unsigned short v ) {
		width = v;
	}
	// Constant Size Primitive
	unsigned short DefineVideoStream::getheight() {
		return height;
	}
	void DefineVideoStream::setheight( unsigned short v ) {
		height = v;
	}
	// Constant Size Primitive
	int DefineVideoStream::getreserved() {
		return reserved;
	}
	void DefineVideoStream::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	int DefineVideoStream::getdeblocking() {
		return deblocking;
	}
	void DefineVideoStream::setdeblocking( int v ) {
		deblocking = v;
	}
	// Constant Size Primitive
	bool DefineVideoStream::getsmoothing() {
		return smoothing;
	}
	void DefineVideoStream::setsmoothing( bool v ) {
		smoothing = v;
	}
	// Constant Size Primitive
	unsigned char DefineVideoStream::getcodec() {
		return codec;
	}
	void DefineVideoStream::setcodec( unsigned char v ) {
		codec = v;
	}
VideoFrame::VideoFrame() {
	objectID = 0;
frame = 0;
}
VideoFrame::~VideoFrame() {
}
VideoFrame* VideoFrame::get( Reader *r, int end, Context *ctx ) {
	VideoFrame* ret = new VideoFrame;
	ret->parse( r, end, ctx );
	return ret;
}
VideoFrame* VideoFrame::getByName( const char *name ) {
	if( strcmp( name, "VideoFrame" ) ) return NULL;
	VideoFrame* ret = new VideoFrame;
	return ret;
}
	// Constant Size Primitive
	unsigned short VideoFrame::getobjectID() {
		return objectID;
	}
	void VideoFrame::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned short VideoFrame::getframe() {
		return frame;
	}
	void VideoFrame::setframe( unsigned short v ) {
		frame = v;
	}
Rest *VideoFrame::getdata() {
		return &data;
	}
ScriptLimits::ScriptLimits() {
	maxRecursionDepth = 0;
timeout = 0;
}
ScriptLimits::~ScriptLimits() {
}
ScriptLimits* ScriptLimits::get( Reader *r, int end, Context *ctx ) {
	ScriptLimits* ret = new ScriptLimits;
	ret->parse( r, end, ctx );
	return ret;
}
ScriptLimits* ScriptLimits::getByName( const char *name ) {
	if( strcmp( name, "ScriptLimits" ) ) return NULL;
	ScriptLimits* ret = new ScriptLimits;
	return ret;
}
	// Constant Size Primitive
	unsigned short ScriptLimits::getmaxRecursionDepth() {
		return maxRecursionDepth;
	}
	void ScriptLimits::setmaxRecursionDepth( unsigned short v ) {
		maxRecursionDepth = v;
	}
	// Constant Size Primitive
	unsigned short ScriptLimits::gettimeout() {
		return timeout;
	}
	void ScriptLimits::settimeout( unsigned short v ) {
		timeout = v;
	}
SetTabIndex::SetTabIndex() {
	depth = 0;
tabIndex = 0;
}
SetTabIndex::~SetTabIndex() {
}
SetTabIndex* SetTabIndex::get( Reader *r, int end, Context *ctx ) {
	SetTabIndex* ret = new SetTabIndex;
	ret->parse( r, end, ctx );
	return ret;
}
SetTabIndex* SetTabIndex::getByName( const char *name ) {
	if( strcmp( name, "SetTabIndex" ) ) return NULL;
	SetTabIndex* ret = new SetTabIndex;
	return ret;
}
	// Constant Size Primitive
	unsigned short SetTabIndex::getdepth() {
		return depth;
	}
	void SetTabIndex::setdepth( unsigned short v ) {
		depth = v;
	}
	// Constant Size Primitive
	unsigned short SetTabIndex::gettabIndex() {
		return tabIndex;
	}
	void SetTabIndex::settabIndex( unsigned short v ) {
		tabIndex = v;
	}
PlaceObject3::PlaceObject3() {
	hasEventHandler = 0;
hasClipDepth = 0;
hasName = 0;
hasMorph = 0;
hasColorTransform = 0;
hasTransform = 0;
hasID = 0;
replace = 0;
reserved1 = 0;
hasCacheAsBitmap = 0;
hasBlendMode = 0;
hasFilterList = 0;
depth = 0;
objectID = 0;
morph = 0;
name = NULL;
clipDepth = 0;
numFilters = 0;
blendMode = 0;
bitmapCaching = 0;
reserved = 0;
allflags1 = 0;
allflags2 = 0;
}
PlaceObject3::~PlaceObject3() {
	delete[] name;
}
PlaceObject3* PlaceObject3::get( Reader *r, int end, Context *ctx ) {
	PlaceObject3* ret = new PlaceObject3;
	ret->parse( r, end, ctx );
	return ret;
}
PlaceObject3* PlaceObject3::getByName( const char *name ) {
	if( strcmp( name, "PlaceObject3" ) ) return NULL;
	PlaceObject3* ret = new PlaceObject3;
	return ret;
}
	// Constant Size Primitive
	bool PlaceObject3::gethasEventHandler() {
		return hasEventHandler;
	}
	void PlaceObject3::sethasEventHandler( bool v ) {
		hasEventHandler = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasClipDepth() {
		return hasClipDepth;
	}
	void PlaceObject3::sethasClipDepth( bool v ) {
		hasClipDepth = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasName() {
		return hasName;
	}
	void PlaceObject3::sethasName( bool v ) {
		hasName = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasMorph() {
		return hasMorph;
	}
	void PlaceObject3::sethasMorph( bool v ) {
		hasMorph = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasColorTransform() {
		return hasColorTransform;
	}
	void PlaceObject3::sethasColorTransform( bool v ) {
		hasColorTransform = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasTransform() {
		return hasTransform;
	}
	void PlaceObject3::sethasTransform( bool v ) {
		hasTransform = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasID() {
		return hasID;
	}
	void PlaceObject3::sethasID( bool v ) {
		hasID = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::getreplace() {
		return replace;
	}
	void PlaceObject3::setreplace( bool v ) {
		replace = v;
	}
	// Constant Size Primitive
	int PlaceObject3::getreserved1() {
		return reserved1;
	}
	void PlaceObject3::setreserved1( int v ) {
		reserved1 = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasCacheAsBitmap() {
		return hasCacheAsBitmap;
	}
	void PlaceObject3::sethasCacheAsBitmap( bool v ) {
		hasCacheAsBitmap = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasBlendMode() {
		return hasBlendMode;
	}
	void PlaceObject3::sethasBlendMode( bool v ) {
		hasBlendMode = v;
	}
	// Constant Size Primitive
	bool PlaceObject3::gethasFilterList() {
		return hasFilterList;
	}
	void PlaceObject3::sethasFilterList( bool v ) {
		hasFilterList = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject3::getdepth() {
		return depth;
	}
	void PlaceObject3::setdepth( unsigned short v ) {
		depth = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject3::getobjectID() {
		return objectID;
	}
	void PlaceObject3::setobjectID( unsigned short v ) {
		objectID = v;
	}
Transform *PlaceObject3::gettransform() {
		return &transform;
	}
ColorTransform2 *PlaceObject3::getcolorTransform() {
		return &colorTransform;
	}
	// Constant Size Primitive
	unsigned short PlaceObject3::getmorph() {
		return morph;
	}
	void PlaceObject3::setmorph( unsigned short v ) {
		morph = v;
	}
char * PlaceObject3::getname() {
		return name;
	}
	void PlaceObject3::setname( char * v ) {
		delete name;
		name = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject3::getclipDepth() {
		return clipDepth;
	}
	void PlaceObject3::setclipDepth( unsigned short v ) {
		clipDepth = v;
	}
	// Constant Size Primitive
	unsigned char PlaceObject3::getnumFilters() {
		return numFilters;
	}
	void PlaceObject3::setnumFilters( unsigned char v ) {
		numFilters = v;
	}
List<Filter> *PlaceObject3::getfilters() {
		return &filters;
	}
	// Constant Size Primitive
	unsigned char PlaceObject3::getblendMode() {
		return blendMode;
	}
	void PlaceObject3::setblendMode( unsigned char v ) {
		blendMode = v;
	}
	// Constant Size Primitive
	unsigned char PlaceObject3::getbitmapCaching() {
		return bitmapCaching;
	}
	void PlaceObject3::setbitmapCaching( unsigned char v ) {
		bitmapCaching = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject3::getreserved() {
		return reserved;
	}
	void PlaceObject3::setreserved( unsigned short v ) {
		reserved = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject3::getallflags1() {
		return allflags1;
	}
	void PlaceObject3::setallflags1( unsigned short v ) {
		allflags1 = v;
	}
	// Constant Size Primitive
	unsigned short PlaceObject3::getallflags2() {
		return allflags2;
	}
	void PlaceObject3::setallflags2( unsigned short v ) {
		allflags2 = v;
	}
List<Event> *PlaceObject3::getevents() {
		return &events;
	}
ImportAssets2::ImportAssets2() {
	url = NULL;
reserved1 = 0;
reserved2 = 0;
count = 0;
}
ImportAssets2::~ImportAssets2() {
	delete[] url;
}
ImportAssets2* ImportAssets2::get( Reader *r, int end, Context *ctx ) {
	ImportAssets2* ret = new ImportAssets2;
	ret->parse( r, end, ctx );
	return ret;
}
ImportAssets2* ImportAssets2::getByName( const char *name ) {
	if( strcmp( name, "ImportAssets2" ) ) return NULL;
	ImportAssets2* ret = new ImportAssets2;
	return ret;
}
char * ImportAssets2::geturl() {
		return url;
	}
	void ImportAssets2::seturl( char * v ) {
		delete url;
		url = v;
	}
	// Constant Size Primitive
	unsigned char ImportAssets2::getreserved1() {
		return reserved1;
	}
	void ImportAssets2::setreserved1( unsigned char v ) {
		reserved1 = v;
	}
	// Constant Size Primitive
	unsigned char ImportAssets2::getreserved2() {
		return reserved2;
	}
	void ImportAssets2::setreserved2( unsigned char v ) {
		reserved2 = v;
	}
	// Constant Size Primitive
	unsigned short ImportAssets2::getcount() {
		return count;
	}
	void ImportAssets2::setcount( unsigned short v ) {
		count = v;
	}
List<Symbol> *ImportAssets2::getsymbols() {
		return &symbols;
	}
FileAttributes::FileAttributes() {
	reserved1 = 0;
hasMetaData = 0;
reserved2 = 0;
allowABC = 0;
suppressCrossDomainCaching = 0;
swfRelativeURLs = 0;
useNetwork = 0;
reserved3 = 0;
}
FileAttributes::~FileAttributes() {
}
FileAttributes* FileAttributes::get( Reader *r, int end, Context *ctx ) {
	FileAttributes* ret = new FileAttributes;
	ret->parse( r, end, ctx );
	return ret;
}
FileAttributes* FileAttributes::getByName( const char *name ) {
	if( strcmp( name, "FileAttributes" ) ) return NULL;
	FileAttributes* ret = new FileAttributes;
	return ret;
}
	// Constant Size Primitive
	int FileAttributes::getreserved1() {
		return reserved1;
	}
	void FileAttributes::setreserved1( int v ) {
		reserved1 = v;
	}
	// Constant Size Primitive
	bool FileAttributes::gethasMetaData() {
		return hasMetaData;
	}
	void FileAttributes::sethasMetaData( bool v ) {
		hasMetaData = v;
	}
	// Constant Size Primitive
	int FileAttributes::getreserved2() {
		return reserved2;
	}
	void FileAttributes::setreserved2( int v ) {
		reserved2 = v;
	}
	// Constant Size Primitive
	bool FileAttributes::getallowABC() {
		return allowABC;
	}
	void FileAttributes::setallowABC( bool v ) {
		allowABC = v;
	}
	// Constant Size Primitive
	bool FileAttributes::getsuppressCrossDomainCaching() {
		return suppressCrossDomainCaching;
	}
	void FileAttributes::setsuppressCrossDomainCaching( bool v ) {
		suppressCrossDomainCaching = v;
	}
	// Constant Size Primitive
	bool FileAttributes::getswfRelativeURLs() {
		return swfRelativeURLs;
	}
	void FileAttributes::setswfRelativeURLs( bool v ) {
		swfRelativeURLs = v;
	}
	// Constant Size Primitive
	bool FileAttributes::getuseNetwork() {
		return useNetwork;
	}
	void FileAttributes::setuseNetwork( bool v ) {
		useNetwork = v;
	}
	// Constant Size Primitive
	int FileAttributes::getreserved3() {
		return reserved3;
	}
	void FileAttributes::setreserved3( int v ) {
		reserved3 = v;
	}
DefineFontAlignZones::DefineFontAlignZones() {
	objectID = 0;
csmTableHint = 0;
reserved = 0;
}
DefineFontAlignZones::~DefineFontAlignZones() {
}
DefineFontAlignZones* DefineFontAlignZones::get( Reader *r, int end, Context *ctx ) {
	DefineFontAlignZones* ret = new DefineFontAlignZones;
	ret->parse( r, end, ctx );
	return ret;
}
DefineFontAlignZones* DefineFontAlignZones::getByName( const char *name ) {
	if( strcmp( name, "DefineFontAlignZones" ) ) return NULL;
	DefineFontAlignZones* ret = new DefineFontAlignZones;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineFontAlignZones::getobjectID() {
		return objectID;
	}
	void DefineFontAlignZones::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	int DefineFontAlignZones::getcsmTableHint() {
		return csmTableHint;
	}
	void DefineFontAlignZones::setcsmTableHint( int v ) {
		csmTableHint = v;
	}
	// Constant Size Primitive
	int DefineFontAlignZones::getreserved() {
		return reserved;
	}
	void DefineFontAlignZones::setreserved( int v ) {
		reserved = v;
	}
List<ZoneArray> *DefineFontAlignZones::getzoneArrays() {
		return &zoneArrays;
	}
CSMTextSettings::CSMTextSettings() {
	objectID = 0;
useFlashType = 0;
gridFit = 0;
reserved1 = 0;
thickness = 0;
sharpness = 0;
reserved2 = 0;
}
CSMTextSettings::~CSMTextSettings() {
}
CSMTextSettings* CSMTextSettings::get( Reader *r, int end, Context *ctx ) {
	CSMTextSettings* ret = new CSMTextSettings;
	ret->parse( r, end, ctx );
	return ret;
}
CSMTextSettings* CSMTextSettings::getByName( const char *name ) {
	if( strcmp( name, "CSMTextSettings" ) ) return NULL;
	CSMTextSettings* ret = new CSMTextSettings;
	return ret;
}
	// Constant Size Primitive
	unsigned short CSMTextSettings::getobjectID() {
		return objectID;
	}
	void CSMTextSettings::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	int CSMTextSettings::getuseFlashType() {
		return useFlashType;
	}
	void CSMTextSettings::setuseFlashType( int v ) {
		useFlashType = v;
	}
	// Constant Size Primitive
	int CSMTextSettings::getgridFit() {
		return gridFit;
	}
	void CSMTextSettings::setgridFit( int v ) {
		gridFit = v;
	}
	// Constant Size Primitive
	int CSMTextSettings::getreserved1() {
		return reserved1;
	}
	void CSMTextSettings::setreserved1( int v ) {
		reserved1 = v;
	}
	// Constant Size Primitive
	unsigned char CSMTextSettings::getreserved2() {
		return reserved2;
	}
	void CSMTextSettings::setreserved2( unsigned char v ) {
		reserved2 = v;
	}
Metadata::Metadata() {
	RDF = NULL;
}
Metadata::~Metadata() {
}
Metadata* Metadata::get( Reader *r, int end, Context *ctx ) {
	Metadata* ret = new Metadata;
	ret->parse( r, end, ctx );
	return ret;
}
Metadata* Metadata::getByName( const char *name ) {
	if( strcmp( name, "Metadata" ) ) return NULL;
	Metadata* ret = new Metadata;
	return ret;
}
char * Metadata::getRDF() {
		return RDF;
	}
	void Metadata::setRDF( char * v ) {
		delete RDF;
		RDF = v;
	}
DefineScalingGrid::DefineScalingGrid() {
	objectID = 0;
}
DefineScalingGrid::~DefineScalingGrid() {
}
DefineScalingGrid* DefineScalingGrid::get( Reader *r, int end, Context *ctx ) {
	DefineScalingGrid* ret = new DefineScalingGrid;
	ret->parse( r, end, ctx );
	return ret;
}
DefineScalingGrid* DefineScalingGrid::getByName( const char *name ) {
	if( strcmp( name, "DefineScalingGrid" ) ) return NULL;
	DefineScalingGrid* ret = new DefineScalingGrid;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineScalingGrid::getobjectID() {
		return objectID;
	}
	void DefineScalingGrid::setobjectID( unsigned short v ) {
		objectID = v;
	}
Rectangle *DefineScalingGrid::getsplitter() {
		return &splitter;
	}
DoABC::DoABC() {
}
DoABC::~DoABC() {
}
DoABC* DoABC::get( Reader *r, int end, Context *ctx ) {
	DoABC* ret = new DoABC;
	ret->parse( r, end, ctx );
	return ret;
}
DoABC* DoABC::getByName( const char *name ) {
	if( strcmp( name, "DoABC" ) ) return NULL;
	DoABC* ret = new DoABC;
	return ret;
}
Action3 *DoABC::getactions() {
		return &actions;
	}
DoABCDefine::DoABCDefine() {
	flags = 0;
name = NULL;
}
DoABCDefine::~DoABCDefine() {
	delete[] name;
}
DoABCDefine* DoABCDefine::get( Reader *r, int end, Context *ctx ) {
	DoABCDefine* ret = new DoABCDefine;
	ret->parse( r, end, ctx );
	return ret;
}
DoABCDefine* DoABCDefine::getByName( const char *name ) {
	if( strcmp( name, "DoABCDefine" ) ) return NULL;
	DoABCDefine* ret = new DoABCDefine;
	return ret;
}
	// Constant Size Primitive
	unsigned int DoABCDefine::getflags() {
		return flags;
	}
	void DoABCDefine::setflags( unsigned int v ) {
		flags = v;
	}
char * DoABCDefine::getname() {
		return name;
	}
	void DoABCDefine::setname( char * v ) {
		delete name;
		name = v;
	}
Action3 *DoABCDefine::getactions() {
		return &actions;
	}
SymbolClass::SymbolClass() {
	count = 0;
}
SymbolClass::~SymbolClass() {
}
SymbolClass* SymbolClass::get( Reader *r, int end, Context *ctx ) {
	SymbolClass* ret = new SymbolClass;
	ret->parse( r, end, ctx );
	return ret;
}
SymbolClass* SymbolClass::getByName( const char *name ) {
	if( strcmp( name, "SymbolClass" ) ) return NULL;
	SymbolClass* ret = new SymbolClass;
	return ret;
}
	// Constant Size Primitive
	unsigned short SymbolClass::getcount() {
		return count;
	}
	void SymbolClass::setcount( unsigned short v ) {
		count = v;
	}
List<Symbol> *SymbolClass::getsymbols() {
		return &symbols;
	}
DefineSceneAndFrameLabelData::DefineSceneAndFrameLabelData() {
	sceneCount = 0;
frameCount = 0;
}
DefineSceneAndFrameLabelData::~DefineSceneAndFrameLabelData() {
}
DefineSceneAndFrameLabelData* DefineSceneAndFrameLabelData::get( Reader *r, int end, Context *ctx ) {
	DefineSceneAndFrameLabelData* ret = new DefineSceneAndFrameLabelData;
	ret->parse( r, end, ctx );
	return ret;
}
DefineSceneAndFrameLabelData* DefineSceneAndFrameLabelData::getByName( const char *name ) {
	if( strcmp( name, "DefineSceneAndFrameLabelData" ) ) return NULL;
	DefineSceneAndFrameLabelData* ret = new DefineSceneAndFrameLabelData;
	return ret;
}
	// Constant Size Primitive
	unsigned int DefineSceneAndFrameLabelData::getsceneCount() {
		return sceneCount;
	}
	void DefineSceneAndFrameLabelData::setsceneCount( unsigned int v ) {
		sceneCount = v;
	}
List<Scene> *DefineSceneAndFrameLabelData::getscenes() {
		return &scenes;
	}
	// Constant Size Primitive
	unsigned int DefineSceneAndFrameLabelData::getframeCount() {
		return frameCount;
	}
	void DefineSceneAndFrameLabelData::setframeCount( unsigned int v ) {
		frameCount = v;
	}
List<Frame> *DefineSceneAndFrameLabelData::getframes() {
		return &frames;
	}
DefineBinaryData::DefineBinaryData() {
	objectID = 0;
reserved = 0;
}
DefineBinaryData::~DefineBinaryData() {
}
DefineBinaryData* DefineBinaryData::get( Reader *r, int end, Context *ctx ) {
	DefineBinaryData* ret = new DefineBinaryData;
	ret->parse( r, end, ctx );
	return ret;
}
DefineBinaryData* DefineBinaryData::getByName( const char *name ) {
	if( strcmp( name, "DefineBinaryData" ) ) return NULL;
	DefineBinaryData* ret = new DefineBinaryData;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineBinaryData::getobjectID() {
		return objectID;
	}
	void DefineBinaryData::setobjectID( unsigned short v ) {
		objectID = v;
	}
	// Constant Size Primitive
	unsigned int DefineBinaryData::getreserved() {
		return reserved;
	}
	void DefineBinaryData::setreserved( unsigned int v ) {
		reserved = v;
	}
Rest *DefineBinaryData::getdata() {
		return &data;
	}
DefineFontName::DefineFontName() {
	objectID = 0;
name = NULL;
copyright = NULL;
}
DefineFontName::~DefineFontName() {
	delete[] name;
	delete[] copyright;
}
DefineFontName* DefineFontName::get( Reader *r, int end, Context *ctx ) {
	DefineFontName* ret = new DefineFontName;
	ret->parse( r, end, ctx );
	return ret;
}
DefineFontName* DefineFontName::getByName( const char *name ) {
	if( strcmp( name, "DefineFontName" ) ) return NULL;
	DefineFontName* ret = new DefineFontName;
	return ret;
}
	// Constant Size Primitive
	unsigned short DefineFontName::getobjectID() {
		return objectID;
	}
	void DefineFontName::setobjectID( unsigned short v ) {
		objectID = v;
	}
char * DefineFontName::getname() {
		return name;
	}
	void DefineFontName::setname( char * v ) {
		delete name;
		name = v;
	}
char * DefineFontName::getcopyright() {
		return copyright;
	}
	void DefineFontName::setcopyright( char * v ) {
		delete copyright;
		copyright = v;
	}
StackString::StackString() {
	value = NULL;
}
StackString::~StackString() {
	delete[] value;
}
StackString* StackString::get( Reader *r, int end, Context *ctx ) {
	StackString* ret = new StackString;
	ret->parse( r, end, ctx );
	return ret;
}
StackString* StackString::getByName( const char *name ) {
	if( strcmp( name, "StackString" ) ) return NULL;
	StackString* ret = new StackString;
	return ret;
}
char * StackString::getvalue() {
		return value;
	}
	void StackString::setvalue( char * v ) {
		delete value;
		value = v;
	}
StackFloat::StackFloat() {
	value = 0;
}
StackFloat::~StackFloat() {
}
StackFloat* StackFloat::get( Reader *r, int end, Context *ctx ) {
	StackFloat* ret = new StackFloat;
	ret->parse( r, end, ctx );
	return ret;
}
StackFloat* StackFloat::getByName( const char *name ) {
	if( strcmp( name, "StackFloat" ) ) return NULL;
	StackFloat* ret = new StackFloat;
	return ret;
}
StackNull::StackNull() {
}
StackNull::~StackNull() {
}
StackNull* StackNull::get( Reader *r, int end, Context *ctx ) {
	StackNull* ret = new StackNull;
	ret->parse( r, end, ctx );
	return ret;
}
StackNull* StackNull::getByName( const char *name ) {
	if( strcmp( name, "StackNull" ) ) return NULL;
	StackNull* ret = new StackNull;
	return ret;
}
StackUndefined::StackUndefined() {
}
StackUndefined::~StackUndefined() {
}
StackUndefined* StackUndefined::get( Reader *r, int end, Context *ctx ) {
	StackUndefined* ret = new StackUndefined;
	ret->parse( r, end, ctx );
	return ret;
}
StackUndefined* StackUndefined::getByName( const char *name ) {
	if( strcmp( name, "StackUndefined" ) ) return NULL;
	StackUndefined* ret = new StackUndefined;
	return ret;
}
StackRegister::StackRegister() {
	reg = 0;
}
StackRegister::~StackRegister() {
}
StackRegister* StackRegister::get( Reader *r, int end, Context *ctx ) {
	StackRegister* ret = new StackRegister;
	ret->parse( r, end, ctx );
	return ret;
}
StackRegister* StackRegister::getByName( const char *name ) {
	if( strcmp( name, "StackRegister" ) ) return NULL;
	StackRegister* ret = new StackRegister;
	return ret;
}
	// Constant Size Primitive
	unsigned char StackRegister::getreg() {
		return reg;
	}
	void StackRegister::setreg( unsigned char v ) {
		reg = v;
	}
StackBoolean::StackBoolean() {
	value = 0;
}
StackBoolean::~StackBoolean() {
}
StackBoolean* StackBoolean::get( Reader *r, int end, Context *ctx ) {
	StackBoolean* ret = new StackBoolean;
	ret->parse( r, end, ctx );
	return ret;
}
StackBoolean* StackBoolean::getByName( const char *name ) {
	if( strcmp( name, "StackBoolean" ) ) return NULL;
	StackBoolean* ret = new StackBoolean;
	return ret;
}
	// Constant Size Primitive
	unsigned char StackBoolean::getvalue() {
		return value;
	}
	void StackBoolean::setvalue( unsigned char v ) {
		value = v;
	}
StackDouble::StackDouble() {
	value = 0;
}
StackDouble::~StackDouble() {
}
StackDouble* StackDouble::get( Reader *r, int end, Context *ctx ) {
	StackDouble* ret = new StackDouble;
	ret->parse( r, end, ctx );
	return ret;
}
StackDouble* StackDouble::getByName( const char *name ) {
	if( strcmp( name, "StackDouble" ) ) return NULL;
	StackDouble* ret = new StackDouble;
	return ret;
}
StackInteger::StackInteger() {
	value = 0;
}
StackInteger::~StackInteger() {
}
StackInteger* StackInteger::get( Reader *r, int end, Context *ctx ) {
	StackInteger* ret = new StackInteger;
	ret->parse( r, end, ctx );
	return ret;
}
StackInteger* StackInteger::getByName( const char *name ) {
	if( strcmp( name, "StackInteger" ) ) return NULL;
	StackInteger* ret = new StackInteger;
	return ret;
}
	// Constant Size Primitive
	unsigned int StackInteger::getvalue() {
		return value;
	}
	void StackInteger::setvalue( unsigned int v ) {
		value = v;
	}
StackDictionaryLookup::StackDictionaryLookup() {
	index = 0;
}
StackDictionaryLookup::~StackDictionaryLookup() {
}
StackDictionaryLookup* StackDictionaryLookup::get( Reader *r, int end, Context *ctx ) {
	StackDictionaryLookup* ret = new StackDictionaryLookup;
	ret->parse( r, end, ctx );
	return ret;
}
StackDictionaryLookup* StackDictionaryLookup::getByName( const char *name ) {
	if( strcmp( name, "StackDictionaryLookup" ) ) return NULL;
	StackDictionaryLookup* ret = new StackDictionaryLookup;
	return ret;
}
	// Constant Size Primitive
	unsigned char StackDictionaryLookup::getindex() {
		return index;
	}
	void StackDictionaryLookup::setindex( unsigned char v ) {
		index = v;
	}
StackLargeDictionaryLookup::StackLargeDictionaryLookup() {
	index = 0;
}
StackLargeDictionaryLookup::~StackLargeDictionaryLookup() {
}
StackLargeDictionaryLookup* StackLargeDictionaryLookup::get( Reader *r, int end, Context *ctx ) {
	StackLargeDictionaryLookup* ret = new StackLargeDictionaryLookup;
	ret->parse( r, end, ctx );
	return ret;
}
StackLargeDictionaryLookup* StackLargeDictionaryLookup::getByName( const char *name ) {
	if( strcmp( name, "StackLargeDictionaryLookup" ) ) return NULL;
	StackLargeDictionaryLookup* ret = new StackLargeDictionaryLookup;
	return ret;
}
	// Constant Size Primitive
	unsigned short StackLargeDictionaryLookup::getindex() {
		return index;
	}
	void StackLargeDictionaryLookup::setindex( unsigned short v ) {
		index = v;
	}
UnknownAction::UnknownAction() {
	data = NULL;
}
UnknownAction::~UnknownAction() {
	delete[] data;
}
UnknownAction* UnknownAction::get( Reader *r, int end, Context *ctx ) {
	UnknownAction* ret = new UnknownAction;
	ret->parse( r, end, ctx );
	return ret;
}
UnknownAction* UnknownAction::getByName( const char *name ) {
	if( strcmp( name, "UnknownAction" ) ) return NULL;
	UnknownAction* ret = new UnknownAction;
	return ret;
}
		void UnknownAction::getdata( unsigned char **dst, int *size ) {
			*dst = data;
			*size = len;
		}
		void UnknownAction::setdata( const unsigned char *src, int size ) {
			delete data;
			len = size;
			data = new unsigned char[ size ];
			memcpy( data, src, size ); 
		}
EndAction::EndAction() {
}
EndAction::~EndAction() {
}
EndAction* EndAction::get( Reader *r, int end, Context *ctx ) {
	EndAction* ret = new EndAction;
	ret->parse( r, end, ctx );
	return ret;
}
EndAction* EndAction::getByName( const char *name ) {
	if( strcmp( name, "EndAction" ) ) return NULL;
	EndAction* ret = new EndAction;
	return ret;
}
NextFrame::NextFrame() {
}
NextFrame::~NextFrame() {
}
NextFrame* NextFrame::get( Reader *r, int end, Context *ctx ) {
	NextFrame* ret = new NextFrame;
	ret->parse( r, end, ctx );
	return ret;
}
NextFrame* NextFrame::getByName( const char *name ) {
	if( strcmp( name, "NextFrame" ) ) return NULL;
	NextFrame* ret = new NextFrame;
	return ret;
}
PreviousFrame::PreviousFrame() {
}
PreviousFrame::~PreviousFrame() {
}
PreviousFrame* PreviousFrame::get( Reader *r, int end, Context *ctx ) {
	PreviousFrame* ret = new PreviousFrame;
	ret->parse( r, end, ctx );
	return ret;
}
PreviousFrame* PreviousFrame::getByName( const char *name ) {
	if( strcmp( name, "PreviousFrame" ) ) return NULL;
	PreviousFrame* ret = new PreviousFrame;
	return ret;
}
Play::Play() {
}
Play::~Play() {
}
Play* Play::get( Reader *r, int end, Context *ctx ) {
	Play* ret = new Play;
	ret->parse( r, end, ctx );
	return ret;
}
Play* Play::getByName( const char *name ) {
	if( strcmp( name, "Play" ) ) return NULL;
	Play* ret = new Play;
	return ret;
}
Stop::Stop() {
}
Stop::~Stop() {
}
Stop* Stop::get( Reader *r, int end, Context *ctx ) {
	Stop* ret = new Stop;
	ret->parse( r, end, ctx );
	return ret;
}
Stop* Stop::getByName( const char *name ) {
	if( strcmp( name, "Stop" ) ) return NULL;
	Stop* ret = new Stop;
	return ret;
}
ToggleQuality::ToggleQuality() {
}
ToggleQuality::~ToggleQuality() {
}
ToggleQuality* ToggleQuality::get( Reader *r, int end, Context *ctx ) {
	ToggleQuality* ret = new ToggleQuality;
	ret->parse( r, end, ctx );
	return ret;
}
ToggleQuality* ToggleQuality::getByName( const char *name ) {
	if( strcmp( name, "ToggleQuality" ) ) return NULL;
	ToggleQuality* ret = new ToggleQuality;
	return ret;
}
StopSound::StopSound() {
}
StopSound::~StopSound() {
}
StopSound* StopSound::get( Reader *r, int end, Context *ctx ) {
	StopSound* ret = new StopSound;
	ret->parse( r, end, ctx );
	return ret;
}
StopSound* StopSound::getByName( const char *name ) {
	if( strcmp( name, "StopSound" ) ) return NULL;
	StopSound* ret = new StopSound;
	return ret;
}
AddCast::AddCast() {
}
AddCast::~AddCast() {
}
AddCast* AddCast::get( Reader *r, int end, Context *ctx ) {
	AddCast* ret = new AddCast;
	ret->parse( r, end, ctx );
	return ret;
}
AddCast* AddCast::getByName( const char *name ) {
	if( strcmp( name, "AddCast" ) ) return NULL;
	AddCast* ret = new AddCast;
	return ret;
}
Substract::Substract() {
}
Substract::~Substract() {
}
Substract* Substract::get( Reader *r, int end, Context *ctx ) {
	Substract* ret = new Substract;
	ret->parse( r, end, ctx );
	return ret;
}
Substract* Substract::getByName( const char *name ) {
	if( strcmp( name, "Substract" ) ) return NULL;
	Substract* ret = new Substract;
	return ret;
}
Mulitply::Mulitply() {
}
Mulitply::~Mulitply() {
}
Mulitply* Mulitply::get( Reader *r, int end, Context *ctx ) {
	Mulitply* ret = new Mulitply;
	ret->parse( r, end, ctx );
	return ret;
}
Mulitply* Mulitply::getByName( const char *name ) {
	if( strcmp( name, "Mulitply" ) ) return NULL;
	Mulitply* ret = new Mulitply;
	return ret;
}
Divide::Divide() {
}
Divide::~Divide() {
}
Divide* Divide::get( Reader *r, int end, Context *ctx ) {
	Divide* ret = new Divide;
	ret->parse( r, end, ctx );
	return ret;
}
Divide* Divide::getByName( const char *name ) {
	if( strcmp( name, "Divide" ) ) return NULL;
	Divide* ret = new Divide;
	return ret;
}
EqualCast::EqualCast() {
}
EqualCast::~EqualCast() {
}
EqualCast* EqualCast::get( Reader *r, int end, Context *ctx ) {
	EqualCast* ret = new EqualCast;
	ret->parse( r, end, ctx );
	return ret;
}
EqualCast* EqualCast::getByName( const char *name ) {
	if( strcmp( name, "EqualCast" ) ) return NULL;
	EqualCast* ret = new EqualCast;
	return ret;
}
LessThanCast::LessThanCast() {
}
LessThanCast::~LessThanCast() {
}
LessThanCast* LessThanCast::get( Reader *r, int end, Context *ctx ) {
	LessThanCast* ret = new LessThanCast;
	ret->parse( r, end, ctx );
	return ret;
}
LessThanCast* LessThanCast::getByName( const char *name ) {
	if( strcmp( name, "LessThanCast" ) ) return NULL;
	LessThanCast* ret = new LessThanCast;
	return ret;
}
LogicalAND::LogicalAND() {
}
LogicalAND::~LogicalAND() {
}
LogicalAND* LogicalAND::get( Reader *r, int end, Context *ctx ) {
	LogicalAND* ret = new LogicalAND;
	ret->parse( r, end, ctx );
	return ret;
}
LogicalAND* LogicalAND::getByName( const char *name ) {
	if( strcmp( name, "LogicalAND" ) ) return NULL;
	LogicalAND* ret = new LogicalAND;
	return ret;
}
LogicalOR::LogicalOR() {
}
LogicalOR::~LogicalOR() {
}
LogicalOR* LogicalOR::get( Reader *r, int end, Context *ctx ) {
	LogicalOR* ret = new LogicalOR;
	ret->parse( r, end, ctx );
	return ret;
}
LogicalOR* LogicalOR::getByName( const char *name ) {
	if( strcmp( name, "LogicalOR" ) ) return NULL;
	LogicalOR* ret = new LogicalOR;
	return ret;
}
LogicalNOT::LogicalNOT() {
}
LogicalNOT::~LogicalNOT() {
}
LogicalNOT* LogicalNOT::get( Reader *r, int end, Context *ctx ) {
	LogicalNOT* ret = new LogicalNOT;
	ret->parse( r, end, ctx );
	return ret;
}
LogicalNOT* LogicalNOT::getByName( const char *name ) {
	if( strcmp( name, "LogicalNOT" ) ) return NULL;
	LogicalNOT* ret = new LogicalNOT;
	return ret;
}
StringEqual::StringEqual() {
}
StringEqual::~StringEqual() {
}
StringEqual* StringEqual::get( Reader *r, int end, Context *ctx ) {
	StringEqual* ret = new StringEqual;
	ret->parse( r, end, ctx );
	return ret;
}
StringEqual* StringEqual::getByName( const char *name ) {
	if( strcmp( name, "StringEqual" ) ) return NULL;
	StringEqual* ret = new StringEqual;
	return ret;
}
StringLength::StringLength() {
}
StringLength::~StringLength() {
}
StringLength* StringLength::get( Reader *r, int end, Context *ctx ) {
	StringLength* ret = new StringLength;
	ret->parse( r, end, ctx );
	return ret;
}
StringLength* StringLength::getByName( const char *name ) {
	if( strcmp( name, "StringLength" ) ) return NULL;
	StringLength* ret = new StringLength;
	return ret;
}
SubString::SubString() {
}
SubString::~SubString() {
}
SubString* SubString::get( Reader *r, int end, Context *ctx ) {
	SubString* ret = new SubString;
	ret->parse( r, end, ctx );
	return ret;
}
SubString* SubString::getByName( const char *name ) {
	if( strcmp( name, "SubString" ) ) return NULL;
	SubString* ret = new SubString;
	return ret;
}
Pop::Pop() {
}
Pop::~Pop() {
}
Pop* Pop::get( Reader *r, int end, Context *ctx ) {
	Pop* ret = new Pop;
	ret->parse( r, end, ctx );
	return ret;
}
Pop* Pop::getByName( const char *name ) {
	if( strcmp( name, "Pop" ) ) return NULL;
	Pop* ret = new Pop;
	return ret;
}
IntegralPart::IntegralPart() {
}
IntegralPart::~IntegralPart() {
}
IntegralPart* IntegralPart::get( Reader *r, int end, Context *ctx ) {
	IntegralPart* ret = new IntegralPart;
	ret->parse( r, end, ctx );
	return ret;
}
IntegralPart* IntegralPart::getByName( const char *name ) {
	if( strcmp( name, "IntegralPart" ) ) return NULL;
	IntegralPart* ret = new IntegralPart;
	return ret;
}
GetVariable::GetVariable() {
}
GetVariable::~GetVariable() {
}
GetVariable* GetVariable::get( Reader *r, int end, Context *ctx ) {
	GetVariable* ret = new GetVariable;
	ret->parse( r, end, ctx );
	return ret;
}
GetVariable* GetVariable::getByName( const char *name ) {
	if( strcmp( name, "GetVariable" ) ) return NULL;
	GetVariable* ret = new GetVariable;
	return ret;
}
SetVariable::SetVariable() {
}
SetVariable::~SetVariable() {
}
SetVariable* SetVariable::get( Reader *r, int end, Context *ctx ) {
	SetVariable* ret = new SetVariable;
	ret->parse( r, end, ctx );
	return ret;
}
SetVariable* SetVariable::getByName( const char *name ) {
	if( strcmp( name, "SetVariable" ) ) return NULL;
	SetVariable* ret = new SetVariable;
	return ret;
}
SetTargetDynamic::SetTargetDynamic() {
}
SetTargetDynamic::~SetTargetDynamic() {
}
SetTargetDynamic* SetTargetDynamic::get( Reader *r, int end, Context *ctx ) {
	SetTargetDynamic* ret = new SetTargetDynamic;
	ret->parse( r, end, ctx );
	return ret;
}
SetTargetDynamic* SetTargetDynamic::getByName( const char *name ) {
	if( strcmp( name, "SetTargetDynamic" ) ) return NULL;
	SetTargetDynamic* ret = new SetTargetDynamic;
	return ret;
}
ConcatenateString::ConcatenateString() {
}
ConcatenateString::~ConcatenateString() {
}
ConcatenateString* ConcatenateString::get( Reader *r, int end, Context *ctx ) {
	ConcatenateString* ret = new ConcatenateString;
	ret->parse( r, end, ctx );
	return ret;
}
ConcatenateString* ConcatenateString::getByName( const char *name ) {
	if( strcmp( name, "ConcatenateString" ) ) return NULL;
	ConcatenateString* ret = new ConcatenateString;
	return ret;
}
GetProperty::GetProperty() {
}
GetProperty::~GetProperty() {
}
GetProperty* GetProperty::get( Reader *r, int end, Context *ctx ) {
	GetProperty* ret = new GetProperty;
	ret->parse( r, end, ctx );
	return ret;
}
GetProperty* GetProperty::getByName( const char *name ) {
	if( strcmp( name, "GetProperty" ) ) return NULL;
	GetProperty* ret = new GetProperty;
	return ret;
}
SetProperty::SetProperty() {
}
SetProperty::~SetProperty() {
}
SetProperty* SetProperty::get( Reader *r, int end, Context *ctx ) {
	SetProperty* ret = new SetProperty;
	ret->parse( r, end, ctx );
	return ret;
}
SetProperty* SetProperty::getByName( const char *name ) {
	if( strcmp( name, "SetProperty" ) ) return NULL;
	SetProperty* ret = new SetProperty;
	return ret;
}
DuplicateSprite::DuplicateSprite() {
}
DuplicateSprite::~DuplicateSprite() {
}
DuplicateSprite* DuplicateSprite::get( Reader *r, int end, Context *ctx ) {
	DuplicateSprite* ret = new DuplicateSprite;
	ret->parse( r, end, ctx );
	return ret;
}
DuplicateSprite* DuplicateSprite::getByName( const char *name ) {
	if( strcmp( name, "DuplicateSprite" ) ) return NULL;
	DuplicateSprite* ret = new DuplicateSprite;
	return ret;
}
RemoveSprite::RemoveSprite() {
}
RemoveSprite::~RemoveSprite() {
}
RemoveSprite* RemoveSprite::get( Reader *r, int end, Context *ctx ) {
	RemoveSprite* ret = new RemoveSprite;
	ret->parse( r, end, ctx );
	return ret;
}
RemoveSprite* RemoveSprite::getByName( const char *name ) {
	if( strcmp( name, "RemoveSprite" ) ) return NULL;
	RemoveSprite* ret = new RemoveSprite;
	return ret;
}
Trace::Trace() {
}
Trace::~Trace() {
}
Trace* Trace::get( Reader *r, int end, Context *ctx ) {
	Trace* ret = new Trace;
	ret->parse( r, end, ctx );
	return ret;
}
Trace* Trace::getByName( const char *name ) {
	if( strcmp( name, "Trace" ) ) return NULL;
	Trace* ret = new Trace;
	return ret;
}
StartDrag::StartDrag() {
}
StartDrag::~StartDrag() {
}
StartDrag* StartDrag::get( Reader *r, int end, Context *ctx ) {
	StartDrag* ret = new StartDrag;
	ret->parse( r, end, ctx );
	return ret;
}
StartDrag* StartDrag::getByName( const char *name ) {
	if( strcmp( name, "StartDrag" ) ) return NULL;
	StartDrag* ret = new StartDrag;
	return ret;
}
StopDrag::StopDrag() {
}
StopDrag::~StopDrag() {
}
StopDrag* StopDrag::get( Reader *r, int end, Context *ctx ) {
	StopDrag* ret = new StopDrag;
	ret->parse( r, end, ctx );
	return ret;
}
StopDrag* StopDrag::getByName( const char *name ) {
	if( strcmp( name, "StopDrag" ) ) return NULL;
	StopDrag* ret = new StopDrag;
	return ret;
}
StringLessThan::StringLessThan() {
}
StringLessThan::~StringLessThan() {
}
StringLessThan* StringLessThan::get( Reader *r, int end, Context *ctx ) {
	StringLessThan* ret = new StringLessThan;
	ret->parse( r, end, ctx );
	return ret;
}
StringLessThan* StringLessThan::getByName( const char *name ) {
	if( strcmp( name, "StringLessThan" ) ) return NULL;
	StringLessThan* ret = new StringLessThan;
	return ret;
}
Throw::Throw() {
}
Throw::~Throw() {
}
Throw* Throw::get( Reader *r, int end, Context *ctx ) {
	Throw* ret = new Throw;
	ret->parse( r, end, ctx );
	return ret;
}
Throw* Throw::getByName( const char *name ) {
	if( strcmp( name, "Throw" ) ) return NULL;
	Throw* ret = new Throw;
	return ret;
}
CastObject::CastObject() {
}
CastObject::~CastObject() {
}
CastObject* CastObject::get( Reader *r, int end, Context *ctx ) {
	CastObject* ret = new CastObject;
	ret->parse( r, end, ctx );
	return ret;
}
CastObject* CastObject::getByName( const char *name ) {
	if( strcmp( name, "CastObject" ) ) return NULL;
	CastObject* ret = new CastObject;
	return ret;
}
Implements::Implements() {
}
Implements::~Implements() {
}
Implements* Implements::get( Reader *r, int end, Context *ctx ) {
	Implements* ret = new Implements;
	ret->parse( r, end, ctx );
	return ret;
}
Implements* Implements::getByName( const char *name ) {
	if( strcmp( name, "Implements" ) ) return NULL;
	Implements* ret = new Implements;
	return ret;
}
Random::Random() {
}
Random::~Random() {
}
Random* Random::get( Reader *r, int end, Context *ctx ) {
	Random* ret = new Random;
	ret->parse( r, end, ctx );
	return ret;
}
Random* Random::getByName( const char *name ) {
	if( strcmp( name, "Random" ) ) return NULL;
	Random* ret = new Random;
	return ret;
}
MultibyteStringLength::MultibyteStringLength() {
}
MultibyteStringLength::~MultibyteStringLength() {
}
MultibyteStringLength* MultibyteStringLength::get( Reader *r, int end, Context *ctx ) {
	MultibyteStringLength* ret = new MultibyteStringLength;
	ret->parse( r, end, ctx );
	return ret;
}
MultibyteStringLength* MultibyteStringLength::getByName( const char *name ) {
	if( strcmp( name, "MultibyteStringLength" ) ) return NULL;
	MultibyteStringLength* ret = new MultibyteStringLength;
	return ret;
}
ORD::ORD() {
}
ORD::~ORD() {
}
ORD* ORD::get( Reader *r, int end, Context *ctx ) {
	ORD* ret = new ORD;
	ret->parse( r, end, ctx );
	return ret;
}
ORD* ORD::getByName( const char *name ) {
	if( strcmp( name, "ORD" ) ) return NULL;
	ORD* ret = new ORD;
	return ret;
}
CHR::CHR() {
}
CHR::~CHR() {
}
CHR* CHR::get( Reader *r, int end, Context *ctx ) {
	CHR* ret = new CHR;
	ret->parse( r, end, ctx );
	return ret;
}
CHR* CHR::getByName( const char *name ) {
	if( strcmp( name, "CHR" ) ) return NULL;
	CHR* ret = new CHR;
	return ret;
}
GetTimer::GetTimer() {
}
GetTimer::~GetTimer() {
}
GetTimer* GetTimer::get( Reader *r, int end, Context *ctx ) {
	GetTimer* ret = new GetTimer;
	ret->parse( r, end, ctx );
	return ret;
}
GetTimer* GetTimer::getByName( const char *name ) {
	if( strcmp( name, "GetTimer" ) ) return NULL;
	GetTimer* ret = new GetTimer;
	return ret;
}
MultibyteSubString::MultibyteSubString() {
}
MultibyteSubString::~MultibyteSubString() {
}
MultibyteSubString* MultibyteSubString::get( Reader *r, int end, Context *ctx ) {
	MultibyteSubString* ret = new MultibyteSubString;
	ret->parse( r, end, ctx );
	return ret;
}
MultibyteSubString* MultibyteSubString::getByName( const char *name ) {
	if( strcmp( name, "MultibyteSubString" ) ) return NULL;
	MultibyteSubString* ret = new MultibyteSubString;
	return ret;
}
MultibyteORD::MultibyteORD() {
}
MultibyteORD::~MultibyteORD() {
}
MultibyteORD* MultibyteORD::get( Reader *r, int end, Context *ctx ) {
	MultibyteORD* ret = new MultibyteORD;
	ret->parse( r, end, ctx );
	return ret;
}
MultibyteORD* MultibyteORD::getByName( const char *name ) {
	if( strcmp( name, "MultibyteORD" ) ) return NULL;
	MultibyteORD* ret = new MultibyteORD;
	return ret;
}
MultibyteCHR::MultibyteCHR() {
}
MultibyteCHR::~MultibyteCHR() {
}
MultibyteCHR* MultibyteCHR::get( Reader *r, int end, Context *ctx ) {
	MultibyteCHR* ret = new MultibyteCHR;
	ret->parse( r, end, ctx );
	return ret;
}
MultibyteCHR* MultibyteCHR::getByName( const char *name ) {
	if( strcmp( name, "MultibyteCHR" ) ) return NULL;
	MultibyteCHR* ret = new MultibyteCHR;
	return ret;
}
Delete::Delete() {
}
Delete::~Delete() {
}
Delete* Delete::get( Reader *r, int end, Context *ctx ) {
	Delete* ret = new Delete;
	ret->parse( r, end, ctx );
	return ret;
}
Delete* Delete::getByName( const char *name ) {
	if( strcmp( name, "Delete" ) ) return NULL;
	Delete* ret = new Delete;
	return ret;
}
DeleteAll::DeleteAll() {
}
DeleteAll::~DeleteAll() {
}
DeleteAll* DeleteAll::get( Reader *r, int end, Context *ctx ) {
	DeleteAll* ret = new DeleteAll;
	ret->parse( r, end, ctx );
	return ret;
}
DeleteAll* DeleteAll::getByName( const char *name ) {
	if( strcmp( name, "DeleteAll" ) ) return NULL;
	DeleteAll* ret = new DeleteAll;
	return ret;
}
SetLocalVariable::SetLocalVariable() {
}
SetLocalVariable::~SetLocalVariable() {
}
SetLocalVariable* SetLocalVariable::get( Reader *r, int end, Context *ctx ) {
	SetLocalVariable* ret = new SetLocalVariable;
	ret->parse( r, end, ctx );
	return ret;
}
SetLocalVariable* SetLocalVariable::getByName( const char *name ) {
	if( strcmp( name, "SetLocalVariable" ) ) return NULL;
	SetLocalVariable* ret = new SetLocalVariable;
	return ret;
}
CallFunction::CallFunction() {
}
CallFunction::~CallFunction() {
}
CallFunction* CallFunction::get( Reader *r, int end, Context *ctx ) {
	CallFunction* ret = new CallFunction;
	ret->parse( r, end, ctx );
	return ret;
}
CallFunction* CallFunction::getByName( const char *name ) {
	if( strcmp( name, "CallFunction" ) ) return NULL;
	CallFunction* ret = new CallFunction;
	return ret;
}
Return::Return() {
}
Return::~Return() {
}
Return* Return::get( Reader *r, int end, Context *ctx ) {
	Return* ret = new Return;
	ret->parse( r, end, ctx );
	return ret;
}
Return* Return::getByName( const char *name ) {
	if( strcmp( name, "Return" ) ) return NULL;
	Return* ret = new Return;
	return ret;
}
Modulo::Modulo() {
}
Modulo::~Modulo() {
}
Modulo* Modulo::get( Reader *r, int end, Context *ctx ) {
	Modulo* ret = new Modulo;
	ret->parse( r, end, ctx );
	return ret;
}
Modulo* Modulo::getByName( const char *name ) {
	if( strcmp( name, "Modulo" ) ) return NULL;
	Modulo* ret = new Modulo;
	return ret;
}
New::New() {
}
New::~New() {
}
New* New::get( Reader *r, int end, Context *ctx ) {
	New* ret = new New;
	ret->parse( r, end, ctx );
	return ret;
}
New* New::getByName( const char *name ) {
	if( strcmp( name, "New" ) ) return NULL;
	New* ret = new New;
	return ret;
}
DeclareLocalVariable::DeclareLocalVariable() {
}
DeclareLocalVariable::~DeclareLocalVariable() {
}
DeclareLocalVariable* DeclareLocalVariable::get( Reader *r, int end, Context *ctx ) {
	DeclareLocalVariable* ret = new DeclareLocalVariable;
	ret->parse( r, end, ctx );
	return ret;
}
DeclareLocalVariable* DeclareLocalVariable::getByName( const char *name ) {
	if( strcmp( name, "DeclareLocalVariable" ) ) return NULL;
	DeclareLocalVariable* ret = new DeclareLocalVariable;
	return ret;
}
DeclareArray::DeclareArray() {
}
DeclareArray::~DeclareArray() {
}
DeclareArray* DeclareArray::get( Reader *r, int end, Context *ctx ) {
	DeclareArray* ret = new DeclareArray;
	ret->parse( r, end, ctx );
	return ret;
}
DeclareArray* DeclareArray::getByName( const char *name ) {
	if( strcmp( name, "DeclareArray" ) ) return NULL;
	DeclareArray* ret = new DeclareArray;
	return ret;
}
DeclareObject::DeclareObject() {
}
DeclareObject::~DeclareObject() {
}
DeclareObject* DeclareObject::get( Reader *r, int end, Context *ctx ) {
	DeclareObject* ret = new DeclareObject;
	ret->parse( r, end, ctx );
	return ret;
}
DeclareObject* DeclareObject::getByName( const char *name ) {
	if( strcmp( name, "DeclareObject" ) ) return NULL;
	DeclareObject* ret = new DeclareObject;
	return ret;
}
TypeOf::TypeOf() {
}
TypeOf::~TypeOf() {
}
TypeOf* TypeOf::get( Reader *r, int end, Context *ctx ) {
	TypeOf* ret = new TypeOf;
	ret->parse( r, end, ctx );
	return ret;
}
TypeOf* TypeOf::getByName( const char *name ) {
	if( strcmp( name, "TypeOf" ) ) return NULL;
	TypeOf* ret = new TypeOf;
	return ret;
}
GetTarget::GetTarget() {
}
GetTarget::~GetTarget() {
}
GetTarget* GetTarget::get( Reader *r, int end, Context *ctx ) {
	GetTarget* ret = new GetTarget;
	ret->parse( r, end, ctx );
	return ret;
}
GetTarget* GetTarget::getByName( const char *name ) {
	if( strcmp( name, "GetTarget" ) ) return NULL;
	GetTarget* ret = new GetTarget;
	return ret;
}
Enumerate::Enumerate() {
}
Enumerate::~Enumerate() {
}
Enumerate* Enumerate::get( Reader *r, int end, Context *ctx ) {
	Enumerate* ret = new Enumerate;
	ret->parse( r, end, ctx );
	return ret;
}
Enumerate* Enumerate::getByName( const char *name ) {
	if( strcmp( name, "Enumerate" ) ) return NULL;
	Enumerate* ret = new Enumerate;
	return ret;
}
AddTyped::AddTyped() {
}
AddTyped::~AddTyped() {
}
AddTyped* AddTyped::get( Reader *r, int end, Context *ctx ) {
	AddTyped* ret = new AddTyped;
	ret->parse( r, end, ctx );
	return ret;
}
AddTyped* AddTyped::getByName( const char *name ) {
	if( strcmp( name, "AddTyped" ) ) return NULL;
	AddTyped* ret = new AddTyped;
	return ret;
}
LessThanTyped::LessThanTyped() {
}
LessThanTyped::~LessThanTyped() {
}
LessThanTyped* LessThanTyped::get( Reader *r, int end, Context *ctx ) {
	LessThanTyped* ret = new LessThanTyped;
	ret->parse( r, end, ctx );
	return ret;
}
LessThanTyped* LessThanTyped::getByName( const char *name ) {
	if( strcmp( name, "LessThanTyped" ) ) return NULL;
	LessThanTyped* ret = new LessThanTyped;
	return ret;
}
EqualTyped::EqualTyped() {
}
EqualTyped::~EqualTyped() {
}
EqualTyped* EqualTyped::get( Reader *r, int end, Context *ctx ) {
	EqualTyped* ret = new EqualTyped;
	ret->parse( r, end, ctx );
	return ret;
}
EqualTyped* EqualTyped::getByName( const char *name ) {
	if( strcmp( name, "EqualTyped" ) ) return NULL;
	EqualTyped* ret = new EqualTyped;
	return ret;
}
DefineNumber::DefineNumber() {
}
DefineNumber::~DefineNumber() {
}
DefineNumber* DefineNumber::get( Reader *r, int end, Context *ctx ) {
	DefineNumber* ret = new DefineNumber;
	ret->parse( r, end, ctx );
	return ret;
}
DefineNumber* DefineNumber::getByName( const char *name ) {
	if( strcmp( name, "DefineNumber" ) ) return NULL;
	DefineNumber* ret = new DefineNumber;
	return ret;
}
DefineString::DefineString() {
}
DefineString::~DefineString() {
}
DefineString* DefineString::get( Reader *r, int end, Context *ctx ) {
	DefineString* ret = new DefineString;
	ret->parse( r, end, ctx );
	return ret;
}
DefineString* DefineString::getByName( const char *name ) {
	if( strcmp( name, "DefineString" ) ) return NULL;
	DefineString* ret = new DefineString;
	return ret;
}
Duplicate::Duplicate() {
}
Duplicate::~Duplicate() {
}
Duplicate* Duplicate::get( Reader *r, int end, Context *ctx ) {
	Duplicate* ret = new Duplicate;
	ret->parse( r, end, ctx );
	return ret;
}
Duplicate* Duplicate::getByName( const char *name ) {
	if( strcmp( name, "Duplicate" ) ) return NULL;
	Duplicate* ret = new Duplicate;
	return ret;
}
Swap::Swap() {
}
Swap::~Swap() {
}
Swap* Swap::get( Reader *r, int end, Context *ctx ) {
	Swap* ret = new Swap;
	ret->parse( r, end, ctx );
	return ret;
}
Swap* Swap::getByName( const char *name ) {
	if( strcmp( name, "Swap" ) ) return NULL;
	Swap* ret = new Swap;
	return ret;
}
GetMember::GetMember() {
}
GetMember::~GetMember() {
}
GetMember* GetMember::get( Reader *r, int end, Context *ctx ) {
	GetMember* ret = new GetMember;
	ret->parse( r, end, ctx );
	return ret;
}
GetMember* GetMember::getByName( const char *name ) {
	if( strcmp( name, "GetMember" ) ) return NULL;
	GetMember* ret = new GetMember;
	return ret;
}
SetMember::SetMember() {
}
SetMember::~SetMember() {
}
SetMember* SetMember::get( Reader *r, int end, Context *ctx ) {
	SetMember* ret = new SetMember;
	ret->parse( r, end, ctx );
	return ret;
}
SetMember* SetMember::getByName( const char *name ) {
	if( strcmp( name, "SetMember" ) ) return NULL;
	SetMember* ret = new SetMember;
	return ret;
}
Increment::Increment() {
}
Increment::~Increment() {
}
Increment* Increment::get( Reader *r, int end, Context *ctx ) {
	Increment* ret = new Increment;
	ret->parse( r, end, ctx );
	return ret;
}
Increment* Increment::getByName( const char *name ) {
	if( strcmp( name, "Increment" ) ) return NULL;
	Increment* ret = new Increment;
	return ret;
}
Decrement::Decrement() {
}
Decrement::~Decrement() {
}
Decrement* Decrement::get( Reader *r, int end, Context *ctx ) {
	Decrement* ret = new Decrement;
	ret->parse( r, end, ctx );
	return ret;
}
Decrement* Decrement::getByName( const char *name ) {
	if( strcmp( name, "Decrement" ) ) return NULL;
	Decrement* ret = new Decrement;
	return ret;
}
CallMethod::CallMethod() {
}
CallMethod::~CallMethod() {
}
CallMethod* CallMethod::get( Reader *r, int end, Context *ctx ) {
	CallMethod* ret = new CallMethod;
	ret->parse( r, end, ctx );
	return ret;
}
CallMethod* CallMethod::getByName( const char *name ) {
	if( strcmp( name, "CallMethod" ) ) return NULL;
	CallMethod* ret = new CallMethod;
	return ret;
}
NewMethod::NewMethod() {
}
NewMethod::~NewMethod() {
}
NewMethod* NewMethod::get( Reader *r, int end, Context *ctx ) {
	NewMethod* ret = new NewMethod;
	ret->parse( r, end, ctx );
	return ret;
}
NewMethod* NewMethod::getByName( const char *name ) {
	if( strcmp( name, "NewMethod" ) ) return NULL;
	NewMethod* ret = new NewMethod;
	return ret;
}
InstanceOf::InstanceOf() {
}
InstanceOf::~InstanceOf() {
}
InstanceOf* InstanceOf::get( Reader *r, int end, Context *ctx ) {
	InstanceOf* ret = new InstanceOf;
	ret->parse( r, end, ctx );
	return ret;
}
InstanceOf* InstanceOf::getByName( const char *name ) {
	if( strcmp( name, "InstanceOf" ) ) return NULL;
	InstanceOf* ret = new InstanceOf;
	return ret;
}
EnumerateObject::EnumerateObject() {
}
EnumerateObject::~EnumerateObject() {
}
EnumerateObject* EnumerateObject::get( Reader *r, int end, Context *ctx ) {
	EnumerateObject* ret = new EnumerateObject;
	ret->parse( r, end, ctx );
	return ret;
}
EnumerateObject* EnumerateObject::getByName( const char *name ) {
	if( strcmp( name, "EnumerateObject" ) ) return NULL;
	EnumerateObject* ret = new EnumerateObject;
	return ret;
}
AND::AND() {
}
AND::~AND() {
}
AND* AND::get( Reader *r, int end, Context *ctx ) {
	AND* ret = new AND;
	ret->parse( r, end, ctx );
	return ret;
}
AND* AND::getByName( const char *name ) {
	if( strcmp( name, "AND" ) ) return NULL;
	AND* ret = new AND;
	return ret;
}
OR::OR() {
}
OR::~OR() {
}
OR* OR::get( Reader *r, int end, Context *ctx ) {
	OR* ret = new OR;
	ret->parse( r, end, ctx );
	return ret;
}
OR* OR::getByName( const char *name ) {
	if( strcmp( name, "OR" ) ) return NULL;
	OR* ret = new OR;
	return ret;
}
XOR::XOR() {
}
XOR::~XOR() {
}
XOR* XOR::get( Reader *r, int end, Context *ctx ) {
	XOR* ret = new XOR;
	ret->parse( r, end, ctx );
	return ret;
}
XOR* XOR::getByName( const char *name ) {
	if( strcmp( name, "XOR" ) ) return NULL;
	XOR* ret = new XOR;
	return ret;
}
ShiftLeft::ShiftLeft() {
}
ShiftLeft::~ShiftLeft() {
}
ShiftLeft* ShiftLeft::get( Reader *r, int end, Context *ctx ) {
	ShiftLeft* ret = new ShiftLeft;
	ret->parse( r, end, ctx );
	return ret;
}
ShiftLeft* ShiftLeft::getByName( const char *name ) {
	if( strcmp( name, "ShiftLeft" ) ) return NULL;
	ShiftLeft* ret = new ShiftLeft;
	return ret;
}
ShiftRight::ShiftRight() {
}
ShiftRight::~ShiftRight() {
}
ShiftRight* ShiftRight::get( Reader *r, int end, Context *ctx ) {
	ShiftRight* ret = new ShiftRight;
	ret->parse( r, end, ctx );
	return ret;
}
ShiftRight* ShiftRight::getByName( const char *name ) {
	if( strcmp( name, "ShiftRight" ) ) return NULL;
	ShiftRight* ret = new ShiftRight;
	return ret;
}
ShiftRightUnsigned::ShiftRightUnsigned() {
}
ShiftRightUnsigned::~ShiftRightUnsigned() {
}
ShiftRightUnsigned* ShiftRightUnsigned::get( Reader *r, int end, Context *ctx ) {
	ShiftRightUnsigned* ret = new ShiftRightUnsigned;
	ret->parse( r, end, ctx );
	return ret;
}
ShiftRightUnsigned* ShiftRightUnsigned::getByName( const char *name ) {
	if( strcmp( name, "ShiftRightUnsigned" ) ) return NULL;
	ShiftRightUnsigned* ret = new ShiftRightUnsigned;
	return ret;
}
StrictEqual::StrictEqual() {
}
StrictEqual::~StrictEqual() {
}
StrictEqual* StrictEqual::get( Reader *r, int end, Context *ctx ) {
	StrictEqual* ret = new StrictEqual;
	ret->parse( r, end, ctx );
	return ret;
}
StrictEqual* StrictEqual::getByName( const char *name ) {
	if( strcmp( name, "StrictEqual" ) ) return NULL;
	StrictEqual* ret = new StrictEqual;
	return ret;
}
GreaterThanTyped::GreaterThanTyped() {
}
GreaterThanTyped::~GreaterThanTyped() {
}
GreaterThanTyped* GreaterThanTyped::get( Reader *r, int end, Context *ctx ) {
	GreaterThanTyped* ret = new GreaterThanTyped;
	ret->parse( r, end, ctx );
	return ret;
}
GreaterThanTyped* GreaterThanTyped::getByName( const char *name ) {
	if( strcmp( name, "GreaterThanTyped" ) ) return NULL;
	GreaterThanTyped* ret = new GreaterThanTyped;
	return ret;
}
StringGreaterThan::StringGreaterThan() {
}
StringGreaterThan::~StringGreaterThan() {
}
StringGreaterThan* StringGreaterThan::get( Reader *r, int end, Context *ctx ) {
	StringGreaterThan* ret = new StringGreaterThan;
	ret->parse( r, end, ctx );
	return ret;
}
StringGreaterThan* StringGreaterThan::getByName( const char *name ) {
	if( strcmp( name, "StringGreaterThan" ) ) return NULL;
	StringGreaterThan* ret = new StringGreaterThan;
	return ret;
}
Extends::Extends() {
}
Extends::~Extends() {
}
Extends* Extends::get( Reader *r, int end, Context *ctx ) {
	Extends* ret = new Extends;
	ret->parse( r, end, ctx );
	return ret;
}
Extends* Extends::getByName( const char *name ) {
	if( strcmp( name, "Extends" ) ) return NULL;
	Extends* ret = new Extends;
	return ret;
}
GotoFrame::GotoFrame() {
	frame = 0;
}
GotoFrame::~GotoFrame() {
}
GotoFrame* GotoFrame::get( Reader *r, int end, Context *ctx ) {
	GotoFrame* ret = new GotoFrame;
	ret->parse( r, end, ctx );
	return ret;
}
GotoFrame* GotoFrame::getByName( const char *name ) {
	if( strcmp( name, "GotoFrame" ) ) return NULL;
	GotoFrame* ret = new GotoFrame;
	return ret;
}
	// Constant Size Primitive
	unsigned short GotoFrame::getframe() {
		return frame;
	}
	void GotoFrame::setframe( unsigned short v ) {
		frame = v;
	}
GetURL::GetURL() {
	url = NULL;
target = NULL;
}
GetURL::~GetURL() {
	delete[] url;
	delete[] target;
}
GetURL* GetURL::get( Reader *r, int end, Context *ctx ) {
	GetURL* ret = new GetURL;
	ret->parse( r, end, ctx );
	return ret;
}
GetURL* GetURL::getByName( const char *name ) {
	if( strcmp( name, "GetURL" ) ) return NULL;
	GetURL* ret = new GetURL;
	return ret;
}
char * GetURL::geturl() {
		return url;
	}
	void GetURL::seturl( char * v ) {
		delete url;
		url = v;
	}
char * GetURL::gettarget() {
		return target;
	}
	void GetURL::settarget( char * v ) {
		delete target;
		target = v;
	}
StoreRegister::StoreRegister() {
	reg = 0;
}
StoreRegister::~StoreRegister() {
}
StoreRegister* StoreRegister::get( Reader *r, int end, Context *ctx ) {
	StoreRegister* ret = new StoreRegister;
	ret->parse( r, end, ctx );
	return ret;
}
StoreRegister* StoreRegister::getByName( const char *name ) {
	if( strcmp( name, "StoreRegister" ) ) return NULL;
	StoreRegister* ret = new StoreRegister;
	return ret;
}
	// Constant Size Primitive
	unsigned char StoreRegister::getreg() {
		return reg;
	}
	void StoreRegister::setreg( unsigned char v ) {
		reg = v;
	}
Dictionary::Dictionary() {
	length = 0;
}
Dictionary::~Dictionary() {
}
Dictionary* Dictionary::get( Reader *r, int end, Context *ctx ) {
	Dictionary* ret = new Dictionary;
	ret->parse( r, end, ctx );
	return ret;
}
Dictionary* Dictionary::getByName( const char *name ) {
	if( strcmp( name, "Dictionary" ) ) return NULL;
	Dictionary* ret = new Dictionary;
	return ret;
}
	// Constant Size Primitive
	unsigned short Dictionary::getlength() {
		return length;
	}
	void Dictionary::setlength( unsigned short v ) {
		length = v;
	}
List<String> *Dictionary::getstrings() {
		return &strings;
	}
WaitForFrame::WaitForFrame() {
	frame = 0;
skip = 0;
}
WaitForFrame::~WaitForFrame() {
}
WaitForFrame* WaitForFrame::get( Reader *r, int end, Context *ctx ) {
	WaitForFrame* ret = new WaitForFrame;
	ret->parse( r, end, ctx );
	return ret;
}
WaitForFrame* WaitForFrame::getByName( const char *name ) {
	if( strcmp( name, "WaitForFrame" ) ) return NULL;
	WaitForFrame* ret = new WaitForFrame;
	return ret;
}
	// Constant Size Primitive
	unsigned short WaitForFrame::getframe() {
		return frame;
	}
	void WaitForFrame::setframe( unsigned short v ) {
		frame = v;
	}
	// Constant Size Primitive
	unsigned char WaitForFrame::getskip() {
		return skip;
	}
	void WaitForFrame::setskip( unsigned char v ) {
		skip = v;
	}
SetTarget::SetTarget() {
	label = NULL;
}
SetTarget::~SetTarget() {
	delete[] label;
}
SetTarget* SetTarget::get( Reader *r, int end, Context *ctx ) {
	SetTarget* ret = new SetTarget;
	ret->parse( r, end, ctx );
	return ret;
}
SetTarget* SetTarget::getByName( const char *name ) {
	if( strcmp( name, "SetTarget" ) ) return NULL;
	SetTarget* ret = new SetTarget;
	return ret;
}
char * SetTarget::getlabel() {
		return label;
	}
	void SetTarget::setlabel( char * v ) {
		delete label;
		label = v;
	}
GotoLabel::GotoLabel() {
	label = NULL;
}
GotoLabel::~GotoLabel() {
	delete[] label;
}
GotoLabel* GotoLabel::get( Reader *r, int end, Context *ctx ) {
	GotoLabel* ret = new GotoLabel;
	ret->parse( r, end, ctx );
	return ret;
}
GotoLabel* GotoLabel::getByName( const char *name ) {
	if( strcmp( name, "GotoLabel" ) ) return NULL;
	GotoLabel* ret = new GotoLabel;
	return ret;
}
char * GotoLabel::getlabel() {
		return label;
	}
	void GotoLabel::setlabel( char * v ) {
		delete label;
		label = v;
	}
WaitForFrameDynamic::WaitForFrameDynamic() {
	frame = 0;
skip = 0;
}
WaitForFrameDynamic::~WaitForFrameDynamic() {
}
WaitForFrameDynamic* WaitForFrameDynamic::get( Reader *r, int end, Context *ctx ) {
	WaitForFrameDynamic* ret = new WaitForFrameDynamic;
	ret->parse( r, end, ctx );
	return ret;
}
WaitForFrameDynamic* WaitForFrameDynamic::getByName( const char *name ) {
	if( strcmp( name, "WaitForFrameDynamic" ) ) return NULL;
	WaitForFrameDynamic* ret = new WaitForFrameDynamic;
	return ret;
}
	// Constant Size Primitive
	unsigned short WaitForFrameDynamic::getframe() {
		return frame;
	}
	void WaitForFrameDynamic::setframe( unsigned short v ) {
		frame = v;
	}
	// Constant Size Primitive
	unsigned char WaitForFrameDynamic::getskip() {
		return skip;
	}
	void WaitForFrameDynamic::setskip( unsigned char v ) {
		skip = v;
	}
DeclareFunction2::DeclareFunction2() {
	name = NULL;
argc = 0;
regc = 0;
preloadParent = 0;
preloadRoot = 0;
suppressSuper = 0;
preloadSuper = 0;
suppressArguments = 0;
preloadArguments = 0;
suppressThis = 0;
preloadThis = 0;
reserved = 0;
preloadGlobal = 0;
length = 0;
}
DeclareFunction2::~DeclareFunction2() {
	delete[] name;
}
DeclareFunction2* DeclareFunction2::get( Reader *r, int end, Context *ctx ) {
	DeclareFunction2* ret = new DeclareFunction2;
	ret->parse( r, end, ctx );
	return ret;
}
DeclareFunction2* DeclareFunction2::getByName( const char *name ) {
	if( strcmp( name, "DeclareFunction2" ) ) return NULL;
	DeclareFunction2* ret = new DeclareFunction2;
	return ret;
}
char * DeclareFunction2::getname() {
		return name;
	}
	void DeclareFunction2::setname( char * v ) {
		delete name;
		name = v;
	}
	// Constant Size Primitive
	unsigned short DeclareFunction2::getargc() {
		return argc;
	}
	void DeclareFunction2::setargc( unsigned short v ) {
		argc = v;
	}
	// Constant Size Primitive
	unsigned char DeclareFunction2::getregc() {
		return regc;
	}
	void DeclareFunction2::setregc( unsigned char v ) {
		regc = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getpreloadParent() {
		return preloadParent;
	}
	void DeclareFunction2::setpreloadParent( bool v ) {
		preloadParent = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getpreloadRoot() {
		return preloadRoot;
	}
	void DeclareFunction2::setpreloadRoot( bool v ) {
		preloadRoot = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getsuppressSuper() {
		return suppressSuper;
	}
	void DeclareFunction2::setsuppressSuper( bool v ) {
		suppressSuper = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getpreloadSuper() {
		return preloadSuper;
	}
	void DeclareFunction2::setpreloadSuper( bool v ) {
		preloadSuper = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getsuppressArguments() {
		return suppressArguments;
	}
	void DeclareFunction2::setsuppressArguments( bool v ) {
		suppressArguments = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getpreloadArguments() {
		return preloadArguments;
	}
	void DeclareFunction2::setpreloadArguments( bool v ) {
		preloadArguments = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getsuppressThis() {
		return suppressThis;
	}
	void DeclareFunction2::setsuppressThis( bool v ) {
		suppressThis = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getpreloadThis() {
		return preloadThis;
	}
	void DeclareFunction2::setpreloadThis( bool v ) {
		preloadThis = v;
	}
	// Constant Size Primitive
	int DeclareFunction2::getreserved() {
		return reserved;
	}
	void DeclareFunction2::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool DeclareFunction2::getpreloadGlobal() {
		return preloadGlobal;
	}
	void DeclareFunction2::setpreloadGlobal( bool v ) {
		preloadGlobal = v;
	}
List<Parameter> *DeclareFunction2::getargs() {
		return &args;
	}
	// Constant Size Primitive
	unsigned short DeclareFunction2::getlength() {
		return length;
	}
	void DeclareFunction2::setlength( unsigned short v ) {
		length = v;
	}
List<Action> *DeclareFunction2::getactions() {
		return &actions;
	}
Try::Try() {
	reserved = 0;
catchInRegister = 0;
doFinally = 0;
doCatch = 0;
trySize = 0;
catchSize = 0;
finallySize = 0;
reg = 0;
}
Try::~Try() {
}
Try* Try::get( Reader *r, int end, Context *ctx ) {
	Try* ret = new Try;
	ret->parse( r, end, ctx );
	return ret;
}
Try* Try::getByName( const char *name ) {
	if( strcmp( name, "Try" ) ) return NULL;
	Try* ret = new Try;
	return ret;
}
	// Constant Size Primitive
	int Try::getreserved() {
		return reserved;
	}
	void Try::setreserved( int v ) {
		reserved = v;
	}
	// Constant Size Primitive
	bool Try::getcatchInRegister() {
		return catchInRegister;
	}
	void Try::setcatchInRegister( bool v ) {
		catchInRegister = v;
	}
	// Constant Size Primitive
	bool Try::getdoFinally() {
		return doFinally;
	}
	void Try::setdoFinally( bool v ) {
		doFinally = v;
	}
	// Constant Size Primitive
	bool Try::getdoCatch() {
		return doCatch;
	}
	void Try::setdoCatch( bool v ) {
		doCatch = v;
	}
	// Constant Size Primitive
	unsigned short Try::gettrySize() {
		return trySize;
	}
	void Try::settrySize( unsigned short v ) {
		trySize = v;
	}
	// Constant Size Primitive
	unsigned short Try::getcatchSize() {
		return catchSize;
	}
	void Try::setcatchSize( unsigned short v ) {
		catchSize = v;
	}
	// Constant Size Primitive
	unsigned short Try::getfinallySize() {
		return finallySize;
	}
	void Try::setfinallySize( unsigned short v ) {
		finallySize = v;
	}
	// Constant Size Primitive
	unsigned char Try::getreg() {
		return reg;
	}
	void Try::setreg( unsigned char v ) {
		reg = v;
	}
With::With() {
	size = 0;
}
With::~With() {
}
With* With::get( Reader *r, int end, Context *ctx ) {
	With* ret = new With;
	ret->parse( r, end, ctx );
	return ret;
}
With* With::getByName( const char *name ) {
	if( strcmp( name, "With" ) ) return NULL;
	With* ret = new With;
	return ret;
}
	// Constant Size Primitive
	unsigned short With::getsize() {
		return size;
	}
	void With::setsize( unsigned short v ) {
		size = v;
	}
PushData::PushData() {
}
PushData::~PushData() {
}
PushData* PushData::get( Reader *r, int end, Context *ctx ) {
	PushData* ret = new PushData;
	ret->parse( r, end, ctx );
	return ret;
}
PushData* PushData::getByName( const char *name ) {
	if( strcmp( name, "PushData" ) ) return NULL;
	PushData* ret = new PushData;
	return ret;
}
List<StackItem> *PushData::getitems() {
		return &items;
	}
GetURL2::GetURL2() {
	method = 0;
}
GetURL2::~GetURL2() {
}
GetURL2* GetURL2::get( Reader *r, int end, Context *ctx ) {
	GetURL2* ret = new GetURL2;
	ret->parse( r, end, ctx );
	return ret;
}
GetURL2* GetURL2::getByName( const char *name ) {
	if( strcmp( name, "GetURL2" ) ) return NULL;
	GetURL2* ret = new GetURL2;
	return ret;
}
	// Constant Size Primitive
	unsigned char GetURL2::getmethod() {
		return method;
	}
	void GetURL2::setmethod( unsigned char v ) {
		method = v;
	}
DeclareFunction::DeclareFunction() {
	name = NULL;
argc = 0;
length = 0;
}
DeclareFunction::~DeclareFunction() {
	delete[] name;
}
DeclareFunction* DeclareFunction::get( Reader *r, int end, Context *ctx ) {
	DeclareFunction* ret = new DeclareFunction;
	ret->parse( r, end, ctx );
	return ret;
}
DeclareFunction* DeclareFunction::getByName( const char *name ) {
	if( strcmp( name, "DeclareFunction" ) ) return NULL;
	DeclareFunction* ret = new DeclareFunction;
	return ret;
}
char * DeclareFunction::getname() {
		return name;
	}
	void DeclareFunction::setname( char * v ) {
		delete name;
		name = v;
	}
	// Constant Size Primitive
	unsigned short DeclareFunction::getargc() {
		return argc;
	}
	void DeclareFunction::setargc( unsigned short v ) {
		argc = v;
	}
List<String> *DeclareFunction::getargs() {
		return &args;
	}
	// Constant Size Primitive
	unsigned short DeclareFunction::getlength() {
		return length;
	}
	void DeclareFunction::setlength( unsigned short v ) {
		length = v;
	}
BranchAlways::BranchAlways() {
	byteOffset = 0;
}
BranchAlways::~BranchAlways() {
}
BranchAlways* BranchAlways::get( Reader *r, int end, Context *ctx ) {
	BranchAlways* ret = new BranchAlways;
	ret->parse( r, end, ctx );
	return ret;
}
BranchAlways* BranchAlways::getByName( const char *name ) {
	if( strcmp( name, "BranchAlways" ) ) return NULL;
	BranchAlways* ret = new BranchAlways;
	return ret;
}
	// Constant Size Primitive
	unsigned short BranchAlways::getbyteOffset() {
		return byteOffset;
	}
	void BranchAlways::setbyteOffset( unsigned short v ) {
		byteOffset = v;
	}
BranchIfTrue::BranchIfTrue() {
	byteOffset = 0;
}
BranchIfTrue::~BranchIfTrue() {
}
BranchIfTrue* BranchIfTrue::get( Reader *r, int end, Context *ctx ) {
	BranchIfTrue* ret = new BranchIfTrue;
	ret->parse( r, end, ctx );
	return ret;
}
BranchIfTrue* BranchIfTrue::getByName( const char *name ) {
	if( strcmp( name, "BranchIfTrue" ) ) return NULL;
	BranchIfTrue* ret = new BranchIfTrue;
	return ret;
}
	// Constant Size Primitive
	unsigned short BranchIfTrue::getbyteOffset() {
		return byteOffset;
	}
	void BranchIfTrue::setbyteOffset( unsigned short v ) {
		byteOffset = v;
	}
CallFrame::CallFrame() {
}
CallFrame::~CallFrame() {
}
CallFrame* CallFrame::get( Reader *r, int end, Context *ctx ) {
	CallFrame* ret = new CallFrame;
	ret->parse( r, end, ctx );
	return ret;
}
CallFrame* CallFrame::getByName( const char *name ) {
	if( strcmp( name, "CallFrame" ) ) return NULL;
	CallFrame* ret = new CallFrame;
	return ret;
}
GotoExpression::GotoExpression() {
	play = 0;
}
GotoExpression::~GotoExpression() {
}
GotoExpression* GotoExpression::get( Reader *r, int end, Context *ctx ) {
	GotoExpression* ret = new GotoExpression;
	ret->parse( r, end, ctx );
	return ret;
}
GotoExpression* GotoExpression::getByName( const char *name ) {
	if( strcmp( name, "GotoExpression" ) ) return NULL;
	GotoExpression* ret = new GotoExpression;
	return ret;
}
	// Constant Size Primitive
	unsigned char GotoExpression::getplay() {
		return play;
	}
	void GotoExpression::setplay( unsigned char v ) {
		play = v;
	}
PrivateNamespace::PrivateNamespace() {
	index = 0;
}
PrivateNamespace::~PrivateNamespace() {
}
PrivateNamespace* PrivateNamespace::get( Reader *r, int end, Context *ctx ) {
	PrivateNamespace* ret = new PrivateNamespace;
	ret->parse( r, end, ctx );
	return ret;
}
PrivateNamespace* PrivateNamespace::getByName( const char *name ) {
	if( strcmp( name, "PrivateNamespace" ) ) return NULL;
	PrivateNamespace* ret = new PrivateNamespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int PrivateNamespace::getindex() {
		return index;
	}
	void PrivateNamespace::setindex( unsigned int v ) {
		index = v;
	}
Namespace::Namespace() {
	index = 0;
}
Namespace::~Namespace() {
}
Namespace* Namespace::get( Reader *r, int end, Context *ctx ) {
	Namespace* ret = new Namespace;
	ret->parse( r, end, ctx );
	return ret;
}
Namespace* Namespace::getByName( const char *name ) {
	if( strcmp( name, "Namespace" ) ) return NULL;
	Namespace* ret = new Namespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int Namespace::getindex() {
		return index;
	}
	void Namespace::setindex( unsigned int v ) {
		index = v;
	}
PackageNamespace::PackageNamespace() {
	index = 0;
}
PackageNamespace::~PackageNamespace() {
}
PackageNamespace* PackageNamespace::get( Reader *r, int end, Context *ctx ) {
	PackageNamespace* ret = new PackageNamespace;
	ret->parse( r, end, ctx );
	return ret;
}
PackageNamespace* PackageNamespace::getByName( const char *name ) {
	if( strcmp( name, "PackageNamespace" ) ) return NULL;
	PackageNamespace* ret = new PackageNamespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int PackageNamespace::getindex() {
		return index;
	}
	void PackageNamespace::setindex( unsigned int v ) {
		index = v;
	}
PackageInternalNamespace::PackageInternalNamespace() {
	index = 0;
}
PackageInternalNamespace::~PackageInternalNamespace() {
}
PackageInternalNamespace* PackageInternalNamespace::get( Reader *r, int end, Context *ctx ) {
	PackageInternalNamespace* ret = new PackageInternalNamespace;
	ret->parse( r, end, ctx );
	return ret;
}
PackageInternalNamespace* PackageInternalNamespace::getByName( const char *name ) {
	if( strcmp( name, "PackageInternalNamespace" ) ) return NULL;
	PackageInternalNamespace* ret = new PackageInternalNamespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int PackageInternalNamespace::getindex() {
		return index;
	}
	void PackageInternalNamespace::setindex( unsigned int v ) {
		index = v;
	}
ProtectedNamespace::ProtectedNamespace() {
	index = 0;
}
ProtectedNamespace::~ProtectedNamespace() {
}
ProtectedNamespace* ProtectedNamespace::get( Reader *r, int end, Context *ctx ) {
	ProtectedNamespace* ret = new ProtectedNamespace;
	ret->parse( r, end, ctx );
	return ret;
}
ProtectedNamespace* ProtectedNamespace::getByName( const char *name ) {
	if( strcmp( name, "ProtectedNamespace" ) ) return NULL;
	ProtectedNamespace* ret = new ProtectedNamespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int ProtectedNamespace::getindex() {
		return index;
	}
	void ProtectedNamespace::setindex( unsigned int v ) {
		index = v;
	}
ExplicitNamespace::ExplicitNamespace() {
	index = 0;
}
ExplicitNamespace::~ExplicitNamespace() {
}
ExplicitNamespace* ExplicitNamespace::get( Reader *r, int end, Context *ctx ) {
	ExplicitNamespace* ret = new ExplicitNamespace;
	ret->parse( r, end, ctx );
	return ret;
}
ExplicitNamespace* ExplicitNamespace::getByName( const char *name ) {
	if( strcmp( name, "ExplicitNamespace" ) ) return NULL;
	ExplicitNamespace* ret = new ExplicitNamespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int ExplicitNamespace::getindex() {
		return index;
	}
	void ExplicitNamespace::setindex( unsigned int v ) {
		index = v;
	}
MultinameLNamespace::MultinameLNamespace() {
	index = 0;
}
MultinameLNamespace::~MultinameLNamespace() {
}
MultinameLNamespace* MultinameLNamespace::get( Reader *r, int end, Context *ctx ) {
	MultinameLNamespace* ret = new MultinameLNamespace;
	ret->parse( r, end, ctx );
	return ret;
}
MultinameLNamespace* MultinameLNamespace::getByName( const char *name ) {
	if( strcmp( name, "MultinameLNamespace" ) ) return NULL;
	MultinameLNamespace* ret = new MultinameLNamespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int MultinameLNamespace::getindex() {
		return index;
	}
	void MultinameLNamespace::setindex( unsigned int v ) {
		index = v;
	}
QName::QName() {
	namespaceIndex = 0;
nameIndex = 0;
}
QName::~QName() {
}
QName* QName::get( Reader *r, int end, Context *ctx ) {
	QName* ret = new QName;
	ret->parse( r, end, ctx );
	return ret;
}
QName* QName::getByName( const char *name ) {
	if( strcmp( name, "QName" ) ) return NULL;
	QName* ret = new QName;
	return ret;
}
	// Constant Size Primitive
	unsigned int QName::getnamespaceIndex() {
		return namespaceIndex;
	}
	void QName::setnamespaceIndex( unsigned int v ) {
		namespaceIndex = v;
	}
	// Constant Size Primitive
	unsigned int QName::getnameIndex() {
		return nameIndex;
	}
	void QName::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
QNameA::QNameA() {
	namespaceIndex = 0;
nameIndex = 0;
}
QNameA::~QNameA() {
}
QNameA* QNameA::get( Reader *r, int end, Context *ctx ) {
	QNameA* ret = new QNameA;
	ret->parse( r, end, ctx );
	return ret;
}
QNameA* QNameA::getByName( const char *name ) {
	if( strcmp( name, "QNameA" ) ) return NULL;
	QNameA* ret = new QNameA;
	return ret;
}
	// Constant Size Primitive
	unsigned int QNameA::getnamespaceIndex() {
		return namespaceIndex;
	}
	void QNameA::setnamespaceIndex( unsigned int v ) {
		namespaceIndex = v;
	}
	// Constant Size Primitive
	unsigned int QNameA::getnameIndex() {
		return nameIndex;
	}
	void QNameA::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
Multiname::Multiname() {
	nameIndex = 0;
namespaceSetIndex = 0;
}
Multiname::~Multiname() {
}
Multiname* Multiname::get( Reader *r, int end, Context *ctx ) {
	Multiname* ret = new Multiname;
	ret->parse( r, end, ctx );
	return ret;
}
Multiname* Multiname::getByName( const char *name ) {
	if( strcmp( name, "Multiname" ) ) return NULL;
	Multiname* ret = new Multiname;
	return ret;
}
	// Constant Size Primitive
	unsigned int Multiname::getnameIndex() {
		return nameIndex;
	}
	void Multiname::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
	// Constant Size Primitive
	unsigned int Multiname::getnamespaceSetIndex() {
		return namespaceSetIndex;
	}
	void Multiname::setnamespaceSetIndex( unsigned int v ) {
		namespaceSetIndex = v;
	}
MultinameA::MultinameA() {
	nameIndex = 0;
namespaceSetIndex = 0;
}
MultinameA::~MultinameA() {
}
MultinameA* MultinameA::get( Reader *r, int end, Context *ctx ) {
	MultinameA* ret = new MultinameA;
	ret->parse( r, end, ctx );
	return ret;
}
MultinameA* MultinameA::getByName( const char *name ) {
	if( strcmp( name, "MultinameA" ) ) return NULL;
	MultinameA* ret = new MultinameA;
	return ret;
}
	// Constant Size Primitive
	unsigned int MultinameA::getnameIndex() {
		return nameIndex;
	}
	void MultinameA::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
	// Constant Size Primitive
	unsigned int MultinameA::getnamespaceSetIndex() {
		return namespaceSetIndex;
	}
	void MultinameA::setnamespaceSetIndex( unsigned int v ) {
		namespaceSetIndex = v;
	}
RTQName::RTQName() {
	nameIndex = 0;
}
RTQName::~RTQName() {
}
RTQName* RTQName::get( Reader *r, int end, Context *ctx ) {
	RTQName* ret = new RTQName;
	ret->parse( r, end, ctx );
	return ret;
}
RTQName* RTQName::getByName( const char *name ) {
	if( strcmp( name, "RTQName" ) ) return NULL;
	RTQName* ret = new RTQName;
	return ret;
}
	// Constant Size Primitive
	unsigned int RTQName::getnameIndex() {
		return nameIndex;
	}
	void RTQName::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
RTQNameA::RTQNameA() {
	nameIndex = 0;
}
RTQNameA::~RTQNameA() {
}
RTQNameA* RTQNameA::get( Reader *r, int end, Context *ctx ) {
	RTQNameA* ret = new RTQNameA;
	ret->parse( r, end, ctx );
	return ret;
}
RTQNameA* RTQNameA::getByName( const char *name ) {
	if( strcmp( name, "RTQNameA" ) ) return NULL;
	RTQNameA* ret = new RTQNameA;
	return ret;
}
	// Constant Size Primitive
	unsigned int RTQNameA::getnameIndex() {
		return nameIndex;
	}
	void RTQNameA::setnameIndex( unsigned int v ) {
		nameIndex = v;
	}
MultinameL::MultinameL() {
	namespaceSetIndex = 0;
}
MultinameL::~MultinameL() {
}
MultinameL* MultinameL::get( Reader *r, int end, Context *ctx ) {
	MultinameL* ret = new MultinameL;
	ret->parse( r, end, ctx );
	return ret;
}
MultinameL* MultinameL::getByName( const char *name ) {
	if( strcmp( name, "MultinameL" ) ) return NULL;
	MultinameL* ret = new MultinameL;
	return ret;
}
	// Constant Size Primitive
	unsigned int MultinameL::getnamespaceSetIndex() {
		return namespaceSetIndex;
	}
	void MultinameL::setnamespaceSetIndex( unsigned int v ) {
		namespaceSetIndex = v;
	}
RTQNameL::RTQNameL() {
}
RTQNameL::~RTQNameL() {
}
RTQNameL* RTQNameL::get( Reader *r, int end, Context *ctx ) {
	RTQNameL* ret = new RTQNameL;
	ret->parse( r, end, ctx );
	return ret;
}
RTQNameL* RTQNameL::getByName( const char *name ) {
	if( strcmp( name, "RTQNameL" ) ) return NULL;
	RTQNameL* ret = new RTQNameL;
	return ret;
}
RTQNameLA::RTQNameLA() {
}
RTQNameLA::~RTQNameLA() {
}
RTQNameLA* RTQNameLA::get( Reader *r, int end, Context *ctx ) {
	RTQNameLA* ret = new RTQNameLA;
	ret->parse( r, end, ctx );
	return ret;
}
RTQNameLA* RTQNameLA::getByName( const char *name ) {
	if( strcmp( name, "RTQNameLA" ) ) return NULL;
	RTQNameLA* ret = new RTQNameLA;
	return ret;
}
Slot::Slot() {
	slotID = 0;
typeIndex = 0;
valueIndex = 0;
valueKind = 0;
}
Slot::~Slot() {
}
Slot* Slot::get( Reader *r, int end, Context *ctx ) {
	Slot* ret = new Slot;
	ret->parse( r, end, ctx );
	return ret;
}
Slot* Slot::getByName( const char *name ) {
	if( strcmp( name, "Slot" ) ) return NULL;
	Slot* ret = new Slot;
	return ret;
}
	// Constant Size Primitive
	unsigned int Slot::getslotID() {
		return slotID;
	}
	void Slot::setslotID( unsigned int v ) {
		slotID = v;
	}
	// Constant Size Primitive
	unsigned int Slot::gettypeIndex() {
		return typeIndex;
	}
	void Slot::settypeIndex( unsigned int v ) {
		typeIndex = v;
	}
	// Constant Size Primitive
	unsigned int Slot::getvalueIndex() {
		return valueIndex;
	}
	void Slot::setvalueIndex( unsigned int v ) {
		valueIndex = v;
	}
	// Constant Size Primitive
	unsigned char Slot::getvalueKind() {
		return valueKind;
	}
	void Slot::setvalueKind( unsigned char v ) {
		valueKind = v;
	}
Const::Const() {
	slotID = 0;
typeIndex = 0;
valueIndex = 0;
valueKind = 0;
}
Const::~Const() {
}
Const* Const::get( Reader *r, int end, Context *ctx ) {
	Const* ret = new Const;
	ret->parse( r, end, ctx );
	return ret;
}
Const* Const::getByName( const char *name ) {
	if( strcmp( name, "Const" ) ) return NULL;
	Const* ret = new Const;
	return ret;
}
	// Constant Size Primitive
	unsigned int Const::getslotID() {
		return slotID;
	}
	void Const::setslotID( unsigned int v ) {
		slotID = v;
	}
	// Constant Size Primitive
	unsigned int Const::gettypeIndex() {
		return typeIndex;
	}
	void Const::settypeIndex( unsigned int v ) {
		typeIndex = v;
	}
	// Constant Size Primitive
	unsigned int Const::getvalueIndex() {
		return valueIndex;
	}
	void Const::setvalueIndex( unsigned int v ) {
		valueIndex = v;
	}
	// Constant Size Primitive
	unsigned char Const::getvalueKind() {
		return valueKind;
	}
	void Const::setvalueKind( unsigned char v ) {
		valueKind = v;
	}
Method::Method() {
	dispID = 0;
methodInfo = 0;
}
Method::~Method() {
}
Method* Method::get( Reader *r, int end, Context *ctx ) {
	Method* ret = new Method;
	ret->parse( r, end, ctx );
	return ret;
}
Method* Method::getByName( const char *name ) {
	if( strcmp( name, "Method" ) ) return NULL;
	Method* ret = new Method;
	return ret;
}
	// Constant Size Primitive
	unsigned int Method::getdispID() {
		return dispID;
	}
	void Method::setdispID( unsigned int v ) {
		dispID = v;
	}
	// Constant Size Primitive
	unsigned int Method::getmethodInfo() {
		return methodInfo;
	}
	void Method::setmethodInfo( unsigned int v ) {
		methodInfo = v;
	}
Getter::Getter() {
	dispID = 0;
methodInfo = 0;
}
Getter::~Getter() {
}
Getter* Getter::get( Reader *r, int end, Context *ctx ) {
	Getter* ret = new Getter;
	ret->parse( r, end, ctx );
	return ret;
}
Getter* Getter::getByName( const char *name ) {
	if( strcmp( name, "Getter" ) ) return NULL;
	Getter* ret = new Getter;
	return ret;
}
	// Constant Size Primitive
	unsigned int Getter::getdispID() {
		return dispID;
	}
	void Getter::setdispID( unsigned int v ) {
		dispID = v;
	}
	// Constant Size Primitive
	unsigned int Getter::getmethodInfo() {
		return methodInfo;
	}
	void Getter::setmethodInfo( unsigned int v ) {
		methodInfo = v;
	}
Setter::Setter() {
	dispID = 0;
methodInfo = 0;
}
Setter::~Setter() {
}
Setter* Setter::get( Reader *r, int end, Context *ctx ) {
	Setter* ret = new Setter;
	ret->parse( r, end, ctx );
	return ret;
}
Setter* Setter::getByName( const char *name ) {
	if( strcmp( name, "Setter" ) ) return NULL;
	Setter* ret = new Setter;
	return ret;
}
	// Constant Size Primitive
	unsigned int Setter::getdispID() {
		return dispID;
	}
	void Setter::setdispID( unsigned int v ) {
		dispID = v;
	}
	// Constant Size Primitive
	unsigned int Setter::getmethodInfo() {
		return methodInfo;
	}
	void Setter::setmethodInfo( unsigned int v ) {
		methodInfo = v;
	}
Class::Class() {
	slotID = 0;
classInfo = 0;
}
Class::~Class() {
}
Class* Class::get( Reader *r, int end, Context *ctx ) {
	Class* ret = new Class;
	ret->parse( r, end, ctx );
	return ret;
}
Class* Class::getByName( const char *name ) {
	if( strcmp( name, "Class" ) ) return NULL;
	Class* ret = new Class;
	return ret;
}
	// Constant Size Primitive
	unsigned int Class::getslotID() {
		return slotID;
	}
	void Class::setslotID( unsigned int v ) {
		slotID = v;
	}
	// Constant Size Primitive
	unsigned int Class::getclassInfo() {
		return classInfo;
	}
	void Class::setclassInfo( unsigned int v ) {
		classInfo = v;
	}
Function::Function() {
	slotID = 0;
methodInfo = 0;
}
Function::~Function() {
}
Function* Function::get( Reader *r, int end, Context *ctx ) {
	Function* ret = new Function;
	ret->parse( r, end, ctx );
	return ret;
}
Function* Function::getByName( const char *name ) {
	if( strcmp( name, "Function" ) ) return NULL;
	Function* ret = new Function;
	return ret;
}
	// Constant Size Primitive
	unsigned int Function::getslotID() {
		return slotID;
	}
	void Function::setslotID( unsigned int v ) {
		slotID = v;
	}
	// Constant Size Primitive
	unsigned int Function::getmethodInfo() {
		return methodInfo;
	}
	void Function::setmethodInfo( unsigned int v ) {
		methodInfo = v;
	}
OpBkPt::OpBkPt() {
}
OpBkPt::~OpBkPt() {
}
OpBkPt* OpBkPt::get( Reader *r, int end, Context *ctx ) {
	OpBkPt* ret = new OpBkPt;
	ret->parse( r, end, ctx );
	return ret;
}
OpBkPt* OpBkPt::getByName( const char *name ) {
	if( strcmp( name, "OpBkPt" ) ) return NULL;
	OpBkPt* ret = new OpBkPt;
	return ret;
}
OpNop::OpNop() {
}
OpNop::~OpNop() {
}
OpNop* OpNop::get( Reader *r, int end, Context *ctx ) {
	OpNop* ret = new OpNop;
	ret->parse( r, end, ctx );
	return ret;
}
OpNop* OpNop::getByName( const char *name ) {
	if( strcmp( name, "OpNop" ) ) return NULL;
	OpNop* ret = new OpNop;
	return ret;
}
OpThrow::OpThrow() {
}
OpThrow::~OpThrow() {
}
OpThrow* OpThrow::get( Reader *r, int end, Context *ctx ) {
	OpThrow* ret = new OpThrow;
	ret->parse( r, end, ctx );
	return ret;
}
OpThrow* OpThrow::getByName( const char *name ) {
	if( strcmp( name, "OpThrow" ) ) return NULL;
	OpThrow* ret = new OpThrow;
	return ret;
}
OpGetSuper::OpGetSuper() {
	name = 0;
}
OpGetSuper::~OpGetSuper() {
}
OpGetSuper* OpGetSuper::get( Reader *r, int end, Context *ctx ) {
	OpGetSuper* ret = new OpGetSuper;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetSuper* OpGetSuper::getByName( const char *name ) {
	if( strcmp( name, "OpGetSuper" ) ) return NULL;
	OpGetSuper* ret = new OpGetSuper;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpGetSuper::getname() {
		return name;
	}
	void OpGetSuper::setname( unsigned int v ) {
		name = v;
	}
OpSetSuper::OpSetSuper() {
	name = 0;
}
OpSetSuper::~OpSetSuper() {
}
OpSetSuper* OpSetSuper::get( Reader *r, int end, Context *ctx ) {
	OpSetSuper* ret = new OpSetSuper;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetSuper* OpSetSuper::getByName( const char *name ) {
	if( strcmp( name, "OpSetSuper" ) ) return NULL;
	OpSetSuper* ret = new OpSetSuper;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpSetSuper::getname() {
		return name;
	}
	void OpSetSuper::setname( unsigned int v ) {
		name = v;
	}
OpDXNs::OpDXNs() {
	dxns = 0;
}
OpDXNs::~OpDXNs() {
}
OpDXNs* OpDXNs::get( Reader *r, int end, Context *ctx ) {
	OpDXNs* ret = new OpDXNs;
	ret->parse( r, end, ctx );
	return ret;
}
OpDXNs* OpDXNs::getByName( const char *name ) {
	if( strcmp( name, "OpDXNs" ) ) return NULL;
	OpDXNs* ret = new OpDXNs;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpDXNs::getdxns() {
		return dxns;
	}
	void OpDXNs::setdxns( unsigned int v ) {
		dxns = v;
	}
OpDXNsLate::OpDXNsLate() {
}
OpDXNsLate::~OpDXNsLate() {
}
OpDXNsLate* OpDXNsLate::get( Reader *r, int end, Context *ctx ) {
	OpDXNsLate* ret = new OpDXNsLate;
	ret->parse( r, end, ctx );
	return ret;
}
OpDXNsLate* OpDXNsLate::getByName( const char *name ) {
	if( strcmp( name, "OpDXNsLate" ) ) return NULL;
	OpDXNsLate* ret = new OpDXNsLate;
	return ret;
}
OpKill::OpKill() {
	address = 0;
}
OpKill::~OpKill() {
}
OpKill* OpKill::get( Reader *r, int end, Context *ctx ) {
	OpKill* ret = new OpKill;
	ret->parse( r, end, ctx );
	return ret;
}
OpKill* OpKill::getByName( const char *name ) {
	if( strcmp( name, "OpKill" ) ) return NULL;
	OpKill* ret = new OpKill;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpKill::getaddress() {
		return address;
	}
	void OpKill::setaddress( unsigned int v ) {
		address = v;
	}
OpLabel::OpLabel() {
}
OpLabel::~OpLabel() {
}
OpLabel* OpLabel::get( Reader *r, int end, Context *ctx ) {
	OpLabel* ret = new OpLabel;
	ret->parse( r, end, ctx );
	return ret;
}
OpLabel* OpLabel::getByName( const char *name ) {
	if( strcmp( name, "OpLabel" ) ) return NULL;
	OpLabel* ret = new OpLabel;
	return ret;
}
OpIfNlt::OpIfNlt() {
	target = 0;
}
OpIfNlt::~OpIfNlt() {
}
OpIfNlt* OpIfNlt::get( Reader *r, int end, Context *ctx ) {
	OpIfNlt* ret = new OpIfNlt;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfNlt* OpIfNlt::getByName( const char *name ) {
	if( strcmp( name, "OpIfNlt" ) ) return NULL;
	OpIfNlt* ret = new OpIfNlt;
	return ret;
}
	// Constant Size Primitive
	int OpIfNlt::gettarget() {
		return target;
	}
	void OpIfNlt::settarget( int v ) {
		target = v;
	}
OpIfNle::OpIfNle() {
	target = 0;
}
OpIfNle::~OpIfNle() {
}
OpIfNle* OpIfNle::get( Reader *r, int end, Context *ctx ) {
	OpIfNle* ret = new OpIfNle;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfNle* OpIfNle::getByName( const char *name ) {
	if( strcmp( name, "OpIfNle" ) ) return NULL;
	OpIfNle* ret = new OpIfNle;
	return ret;
}
	// Constant Size Primitive
	int OpIfNle::gettarget() {
		return target;
	}
	void OpIfNle::settarget( int v ) {
		target = v;
	}
OpIfNgt::OpIfNgt() {
	target = 0;
}
OpIfNgt::~OpIfNgt() {
}
OpIfNgt* OpIfNgt::get( Reader *r, int end, Context *ctx ) {
	OpIfNgt* ret = new OpIfNgt;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfNgt* OpIfNgt::getByName( const char *name ) {
	if( strcmp( name, "OpIfNgt" ) ) return NULL;
	OpIfNgt* ret = new OpIfNgt;
	return ret;
}
	// Constant Size Primitive
	int OpIfNgt::gettarget() {
		return target;
	}
	void OpIfNgt::settarget( int v ) {
		target = v;
	}
OpIfNge::OpIfNge() {
	target = 0;
}
OpIfNge::~OpIfNge() {
}
OpIfNge* OpIfNge::get( Reader *r, int end, Context *ctx ) {
	OpIfNge* ret = new OpIfNge;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfNge* OpIfNge::getByName( const char *name ) {
	if( strcmp( name, "OpIfNge" ) ) return NULL;
	OpIfNge* ret = new OpIfNge;
	return ret;
}
	// Constant Size Primitive
	int OpIfNge::gettarget() {
		return target;
	}
	void OpIfNge::settarget( int v ) {
		target = v;
	}
OpJump::OpJump() {
	target = 0;
}
OpJump::~OpJump() {
}
OpJump* OpJump::get( Reader *r, int end, Context *ctx ) {
	OpJump* ret = new OpJump;
	ret->parse( r, end, ctx );
	return ret;
}
OpJump* OpJump::getByName( const char *name ) {
	if( strcmp( name, "OpJump" ) ) return NULL;
	OpJump* ret = new OpJump;
	return ret;
}
	// Constant Size Primitive
	int OpJump::gettarget() {
		return target;
	}
	void OpJump::settarget( int v ) {
		target = v;
	}
OpIfTrue::OpIfTrue() {
	target = 0;
}
OpIfTrue::~OpIfTrue() {
}
OpIfTrue* OpIfTrue::get( Reader *r, int end, Context *ctx ) {
	OpIfTrue* ret = new OpIfTrue;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfTrue* OpIfTrue::getByName( const char *name ) {
	if( strcmp( name, "OpIfTrue" ) ) return NULL;
	OpIfTrue* ret = new OpIfTrue;
	return ret;
}
	// Constant Size Primitive
	int OpIfTrue::gettarget() {
		return target;
	}
	void OpIfTrue::settarget( int v ) {
		target = v;
	}
OpIfFalse::OpIfFalse() {
	target = 0;
}
OpIfFalse::~OpIfFalse() {
}
OpIfFalse* OpIfFalse::get( Reader *r, int end, Context *ctx ) {
	OpIfFalse* ret = new OpIfFalse;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfFalse* OpIfFalse::getByName( const char *name ) {
	if( strcmp( name, "OpIfFalse" ) ) return NULL;
	OpIfFalse* ret = new OpIfFalse;
	return ret;
}
	// Constant Size Primitive
	int OpIfFalse::gettarget() {
		return target;
	}
	void OpIfFalse::settarget( int v ) {
		target = v;
	}
OpIfEq::OpIfEq() {
	target = 0;
}
OpIfEq::~OpIfEq() {
}
OpIfEq* OpIfEq::get( Reader *r, int end, Context *ctx ) {
	OpIfEq* ret = new OpIfEq;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfEq* OpIfEq::getByName( const char *name ) {
	if( strcmp( name, "OpIfEq" ) ) return NULL;
	OpIfEq* ret = new OpIfEq;
	return ret;
}
	// Constant Size Primitive
	int OpIfEq::gettarget() {
		return target;
	}
	void OpIfEq::settarget( int v ) {
		target = v;
	}
OpIfNe::OpIfNe() {
	target = 0;
}
OpIfNe::~OpIfNe() {
}
OpIfNe* OpIfNe::get( Reader *r, int end, Context *ctx ) {
	OpIfNe* ret = new OpIfNe;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfNe* OpIfNe::getByName( const char *name ) {
	if( strcmp( name, "OpIfNe" ) ) return NULL;
	OpIfNe* ret = new OpIfNe;
	return ret;
}
	// Constant Size Primitive
	int OpIfNe::gettarget() {
		return target;
	}
	void OpIfNe::settarget( int v ) {
		target = v;
	}
OpIfLt::OpIfLt() {
	target = 0;
}
OpIfLt::~OpIfLt() {
}
OpIfLt* OpIfLt::get( Reader *r, int end, Context *ctx ) {
	OpIfLt* ret = new OpIfLt;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfLt* OpIfLt::getByName( const char *name ) {
	if( strcmp( name, "OpIfLt" ) ) return NULL;
	OpIfLt* ret = new OpIfLt;
	return ret;
}
	// Constant Size Primitive
	int OpIfLt::gettarget() {
		return target;
	}
	void OpIfLt::settarget( int v ) {
		target = v;
	}
OpIfLe::OpIfLe() {
	target = 0;
}
OpIfLe::~OpIfLe() {
}
OpIfLe* OpIfLe::get( Reader *r, int end, Context *ctx ) {
	OpIfLe* ret = new OpIfLe;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfLe* OpIfLe::getByName( const char *name ) {
	if( strcmp( name, "OpIfLe" ) ) return NULL;
	OpIfLe* ret = new OpIfLe;
	return ret;
}
	// Constant Size Primitive
	int OpIfLe::gettarget() {
		return target;
	}
	void OpIfLe::settarget( int v ) {
		target = v;
	}
OpIfGt::OpIfGt() {
	target = 0;
}
OpIfGt::~OpIfGt() {
}
OpIfGt* OpIfGt::get( Reader *r, int end, Context *ctx ) {
	OpIfGt* ret = new OpIfGt;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfGt* OpIfGt::getByName( const char *name ) {
	if( strcmp( name, "OpIfGt" ) ) return NULL;
	OpIfGt* ret = new OpIfGt;
	return ret;
}
	// Constant Size Primitive
	int OpIfGt::gettarget() {
		return target;
	}
	void OpIfGt::settarget( int v ) {
		target = v;
	}
OpIfGe::OpIfGe() {
	target = 0;
}
OpIfGe::~OpIfGe() {
}
OpIfGe* OpIfGe::get( Reader *r, int end, Context *ctx ) {
	OpIfGe* ret = new OpIfGe;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfGe* OpIfGe::getByName( const char *name ) {
	if( strcmp( name, "OpIfGe" ) ) return NULL;
	OpIfGe* ret = new OpIfGe;
	return ret;
}
	// Constant Size Primitive
	int OpIfGe::gettarget() {
		return target;
	}
	void OpIfGe::settarget( int v ) {
		target = v;
	}
OpIfStrictEq::OpIfStrictEq() {
	target = 0;
}
OpIfStrictEq::~OpIfStrictEq() {
}
OpIfStrictEq* OpIfStrictEq::get( Reader *r, int end, Context *ctx ) {
	OpIfStrictEq* ret = new OpIfStrictEq;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfStrictEq* OpIfStrictEq::getByName( const char *name ) {
	if( strcmp( name, "OpIfStrictEq" ) ) return NULL;
	OpIfStrictEq* ret = new OpIfStrictEq;
	return ret;
}
	// Constant Size Primitive
	int OpIfStrictEq::gettarget() {
		return target;
	}
	void OpIfStrictEq::settarget( int v ) {
		target = v;
	}
OpIfStrictNe::OpIfStrictNe() {
	target = 0;
}
OpIfStrictNe::~OpIfStrictNe() {
}
OpIfStrictNe* OpIfStrictNe::get( Reader *r, int end, Context *ctx ) {
	OpIfStrictNe* ret = new OpIfStrictNe;
	ret->parse( r, end, ctx );
	return ret;
}
OpIfStrictNe* OpIfStrictNe::getByName( const char *name ) {
	if( strcmp( name, "OpIfStrictNe" ) ) return NULL;
	OpIfStrictNe* ret = new OpIfStrictNe;
	return ret;
}
	// Constant Size Primitive
	int OpIfStrictNe::gettarget() {
		return target;
	}
	void OpIfStrictNe::settarget( int v ) {
		target = v;
	}
OpLookupSwitch::OpLookupSwitch() {
	defaulTarget = 0;
caseCount = 0;
}
OpLookupSwitch::~OpLookupSwitch() {
}
OpLookupSwitch* OpLookupSwitch::get( Reader *r, int end, Context *ctx ) {
	OpLookupSwitch* ret = new OpLookupSwitch;
	ret->parse( r, end, ctx );
	return ret;
}
OpLookupSwitch* OpLookupSwitch::getByName( const char *name ) {
	if( strcmp( name, "OpLookupSwitch" ) ) return NULL;
	OpLookupSwitch* ret = new OpLookupSwitch;
	return ret;
}
	// Constant Size Primitive
	int OpLookupSwitch::getdefaulTarget() {
		return defaulTarget;
	}
	void OpLookupSwitch::setdefaulTarget( int v ) {
		defaulTarget = v;
	}
	// Constant Size Primitive
	unsigned int OpLookupSwitch::getcaseCount() {
		return caseCount;
	}
	void OpLookupSwitch::setcaseCount( unsigned int v ) {
		caseCount = v;
	}
List<S24> *OpLookupSwitch::gettargetTable() {
		return &targetTable;
	}
OpPushWith::OpPushWith() {
}
OpPushWith::~OpPushWith() {
}
OpPushWith* OpPushWith::get( Reader *r, int end, Context *ctx ) {
	OpPushWith* ret = new OpPushWith;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushWith* OpPushWith::getByName( const char *name ) {
	if( strcmp( name, "OpPushWith" ) ) return NULL;
	OpPushWith* ret = new OpPushWith;
	return ret;
}
OpPopScope::OpPopScope() {
}
OpPopScope::~OpPopScope() {
}
OpPopScope* OpPopScope::get( Reader *r, int end, Context *ctx ) {
	OpPopScope* ret = new OpPopScope;
	ret->parse( r, end, ctx );
	return ret;
}
OpPopScope* OpPopScope::getByName( const char *name ) {
	if( strcmp( name, "OpPopScope" ) ) return NULL;
	OpPopScope* ret = new OpPopScope;
	return ret;
}
OpNextName::OpNextName() {
}
OpNextName::~OpNextName() {
}
OpNextName* OpNextName::get( Reader *r, int end, Context *ctx ) {
	OpNextName* ret = new OpNextName;
	ret->parse( r, end, ctx );
	return ret;
}
OpNextName* OpNextName::getByName( const char *name ) {
	if( strcmp( name, "OpNextName" ) ) return NULL;
	OpNextName* ret = new OpNextName;
	return ret;
}
OpHasNext::OpHasNext() {
}
OpHasNext::~OpHasNext() {
}
OpHasNext* OpHasNext::get( Reader *r, int end, Context *ctx ) {
	OpHasNext* ret = new OpHasNext;
	ret->parse( r, end, ctx );
	return ret;
}
OpHasNext* OpHasNext::getByName( const char *name ) {
	if( strcmp( name, "OpHasNext" ) ) return NULL;
	OpHasNext* ret = new OpHasNext;
	return ret;
}
OpPushNull::OpPushNull() {
}
OpPushNull::~OpPushNull() {
}
OpPushNull* OpPushNull::get( Reader *r, int end, Context *ctx ) {
	OpPushNull* ret = new OpPushNull;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushNull* OpPushNull::getByName( const char *name ) {
	if( strcmp( name, "OpPushNull" ) ) return NULL;
	OpPushNull* ret = new OpPushNull;
	return ret;
}
OpPushUndefined::OpPushUndefined() {
}
OpPushUndefined::~OpPushUndefined() {
}
OpPushUndefined* OpPushUndefined::get( Reader *r, int end, Context *ctx ) {
	OpPushUndefined* ret = new OpPushUndefined;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushUndefined* OpPushUndefined::getByName( const char *name ) {
	if( strcmp( name, "OpPushUndefined" ) ) return NULL;
	OpPushUndefined* ret = new OpPushUndefined;
	return ret;
}
OpNextValue::OpNextValue() {
}
OpNextValue::~OpNextValue() {
}
OpNextValue* OpNextValue::get( Reader *r, int end, Context *ctx ) {
	OpNextValue* ret = new OpNextValue;
	ret->parse( r, end, ctx );
	return ret;
}
OpNextValue* OpNextValue::getByName( const char *name ) {
	if( strcmp( name, "OpNextValue" ) ) return NULL;
	OpNextValue* ret = new OpNextValue;
	return ret;
}
OpPushByte::OpPushByte() {
	value = 0;
}
OpPushByte::~OpPushByte() {
}
OpPushByte* OpPushByte::get( Reader *r, int end, Context *ctx ) {
	OpPushByte* ret = new OpPushByte;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushByte* OpPushByte::getByName( const char *name ) {
	if( strcmp( name, "OpPushByte" ) ) return NULL;
	OpPushByte* ret = new OpPushByte;
	return ret;
}
	// Constant Size Primitive
	unsigned char OpPushByte::getvalue() {
		return value;
	}
	void OpPushByte::setvalue( unsigned char v ) {
		value = v;
	}
OpPushShort::OpPushShort() {
	value = 0;
}
OpPushShort::~OpPushShort() {
}
OpPushShort* OpPushShort::get( Reader *r, int end, Context *ctx ) {
	OpPushShort* ret = new OpPushShort;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushShort* OpPushShort::getByName( const char *name ) {
	if( strcmp( name, "OpPushShort" ) ) return NULL;
	OpPushShort* ret = new OpPushShort;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpPushShort::getvalue() {
		return value;
	}
	void OpPushShort::setvalue( unsigned int v ) {
		value = v;
	}
OpPushTrue::OpPushTrue() {
}
OpPushTrue::~OpPushTrue() {
}
OpPushTrue* OpPushTrue::get( Reader *r, int end, Context *ctx ) {
	OpPushTrue* ret = new OpPushTrue;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushTrue* OpPushTrue::getByName( const char *name ) {
	if( strcmp( name, "OpPushTrue" ) ) return NULL;
	OpPushTrue* ret = new OpPushTrue;
	return ret;
}
OpPushFalse::OpPushFalse() {
}
OpPushFalse::~OpPushFalse() {
}
OpPushFalse* OpPushFalse::get( Reader *r, int end, Context *ctx ) {
	OpPushFalse* ret = new OpPushFalse;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushFalse* OpPushFalse::getByName( const char *name ) {
	if( strcmp( name, "OpPushFalse" ) ) return NULL;
	OpPushFalse* ret = new OpPushFalse;
	return ret;
}
OpPushNaN::OpPushNaN() {
}
OpPushNaN::~OpPushNaN() {
}
OpPushNaN* OpPushNaN::get( Reader *r, int end, Context *ctx ) {
	OpPushNaN* ret = new OpPushNaN;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushNaN* OpPushNaN::getByName( const char *name ) {
	if( strcmp( name, "OpPushNaN" ) ) return NULL;
	OpPushNaN* ret = new OpPushNaN;
	return ret;
}
OpPop::OpPop() {
}
OpPop::~OpPop() {
}
OpPop* OpPop::get( Reader *r, int end, Context *ctx ) {
	OpPop* ret = new OpPop;
	ret->parse( r, end, ctx );
	return ret;
}
OpPop* OpPop::getByName( const char *name ) {
	if( strcmp( name, "OpPop" ) ) return NULL;
	OpPop* ret = new OpPop;
	return ret;
}
OpDup::OpDup() {
}
OpDup::~OpDup() {
}
OpDup* OpDup::get( Reader *r, int end, Context *ctx ) {
	OpDup* ret = new OpDup;
	ret->parse( r, end, ctx );
	return ret;
}
OpDup* OpDup::getByName( const char *name ) {
	if( strcmp( name, "OpDup" ) ) return NULL;
	OpDup* ret = new OpDup;
	return ret;
}
OpSwap::OpSwap() {
}
OpSwap::~OpSwap() {
}
OpSwap* OpSwap::get( Reader *r, int end, Context *ctx ) {
	OpSwap* ret = new OpSwap;
	ret->parse( r, end, ctx );
	return ret;
}
OpSwap* OpSwap::getByName( const char *name ) {
	if( strcmp( name, "OpSwap" ) ) return NULL;
	OpSwap* ret = new OpSwap;
	return ret;
}
OpPushString::OpPushString() {
	index = 0;
}
OpPushString::~OpPushString() {
}
OpPushString* OpPushString::get( Reader *r, int end, Context *ctx ) {
	OpPushString* ret = new OpPushString;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushString* OpPushString::getByName( const char *name ) {
	if( strcmp( name, "OpPushString" ) ) return NULL;
	OpPushString* ret = new OpPushString;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpPushString::getindex() {
		return index;
	}
	void OpPushString::setindex( unsigned int v ) {
		index = v;
	}
OpPushInt::OpPushInt() {
	index = 0;
}
OpPushInt::~OpPushInt() {
}
OpPushInt* OpPushInt::get( Reader *r, int end, Context *ctx ) {
	OpPushInt* ret = new OpPushInt;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushInt* OpPushInt::getByName( const char *name ) {
	if( strcmp( name, "OpPushInt" ) ) return NULL;
	OpPushInt* ret = new OpPushInt;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpPushInt::getindex() {
		return index;
	}
	void OpPushInt::setindex( unsigned int v ) {
		index = v;
	}
OpPushUInt::OpPushUInt() {
	index = 0;
}
OpPushUInt::~OpPushUInt() {
}
OpPushUInt* OpPushUInt::get( Reader *r, int end, Context *ctx ) {
	OpPushUInt* ret = new OpPushUInt;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushUInt* OpPushUInt::getByName( const char *name ) {
	if( strcmp( name, "OpPushUInt" ) ) return NULL;
	OpPushUInt* ret = new OpPushUInt;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpPushUInt::getindex() {
		return index;
	}
	void OpPushUInt::setindex( unsigned int v ) {
		index = v;
	}
OpPushDouble::OpPushDouble() {
	index = 0;
}
OpPushDouble::~OpPushDouble() {
}
OpPushDouble* OpPushDouble::get( Reader *r, int end, Context *ctx ) {
	OpPushDouble* ret = new OpPushDouble;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushDouble* OpPushDouble::getByName( const char *name ) {
	if( strcmp( name, "OpPushDouble" ) ) return NULL;
	OpPushDouble* ret = new OpPushDouble;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpPushDouble::getindex() {
		return index;
	}
	void OpPushDouble::setindex( unsigned int v ) {
		index = v;
	}
OpPushScope::OpPushScope() {
}
OpPushScope::~OpPushScope() {
}
OpPushScope* OpPushScope::get( Reader *r, int end, Context *ctx ) {
	OpPushScope* ret = new OpPushScope;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushScope* OpPushScope::getByName( const char *name ) {
	if( strcmp( name, "OpPushScope" ) ) return NULL;
	OpPushScope* ret = new OpPushScope;
	return ret;
}
OpPushNamespace::OpPushNamespace() {
	index = 0;
}
OpPushNamespace::~OpPushNamespace() {
}
OpPushNamespace* OpPushNamespace::get( Reader *r, int end, Context *ctx ) {
	OpPushNamespace* ret = new OpPushNamespace;
	ret->parse( r, end, ctx );
	return ret;
}
OpPushNamespace* OpPushNamespace::getByName( const char *name ) {
	if( strcmp( name, "OpPushNamespace" ) ) return NULL;
	OpPushNamespace* ret = new OpPushNamespace;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpPushNamespace::getindex() {
		return index;
	}
	void OpPushNamespace::setindex( unsigned int v ) {
		index = v;
	}
OpHasNext2::OpHasNext2() {
	object = 0;
index = 0;
}
OpHasNext2::~OpHasNext2() {
}
OpHasNext2* OpHasNext2::get( Reader *r, int end, Context *ctx ) {
	OpHasNext2* ret = new OpHasNext2;
	ret->parse( r, end, ctx );
	return ret;
}
OpHasNext2* OpHasNext2::getByName( const char *name ) {
	if( strcmp( name, "OpHasNext2" ) ) return NULL;
	OpHasNext2* ret = new OpHasNext2;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpHasNext2::getobject() {
		return object;
	}
	void OpHasNext2::setobject( unsigned int v ) {
		object = v;
	}
	// Constant Size Primitive
	unsigned int OpHasNext2::getindex() {
		return index;
	}
	void OpHasNext2::setindex( unsigned int v ) {
		index = v;
	}
OpNewFunction::OpNewFunction() {
	index = 0;
}
OpNewFunction::~OpNewFunction() {
}
OpNewFunction* OpNewFunction::get( Reader *r, int end, Context *ctx ) {
	OpNewFunction* ret = new OpNewFunction;
	ret->parse( r, end, ctx );
	return ret;
}
OpNewFunction* OpNewFunction::getByName( const char *name ) {
	if( strcmp( name, "OpNewFunction" ) ) return NULL;
	OpNewFunction* ret = new OpNewFunction;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpNewFunction::getindex() {
		return index;
	}
	void OpNewFunction::setindex( unsigned int v ) {
		index = v;
	}
OpCall::OpCall() {
	argc = 0;
}
OpCall::~OpCall() {
}
OpCall* OpCall::get( Reader *r, int end, Context *ctx ) {
	OpCall* ret = new OpCall;
	ret->parse( r, end, ctx );
	return ret;
}
OpCall* OpCall::getByName( const char *name ) {
	if( strcmp( name, "OpCall" ) ) return NULL;
	OpCall* ret = new OpCall;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCall::getargc() {
		return argc;
	}
	void OpCall::setargc( unsigned int v ) {
		argc = v;
	}
OpConstruct::OpConstruct() {
	argc = 0;
}
OpConstruct::~OpConstruct() {
}
OpConstruct* OpConstruct::get( Reader *r, int end, Context *ctx ) {
	OpConstruct* ret = new OpConstruct;
	ret->parse( r, end, ctx );
	return ret;
}
OpConstruct* OpConstruct::getByName( const char *name ) {
	if( strcmp( name, "OpConstruct" ) ) return NULL;
	OpConstruct* ret = new OpConstruct;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpConstruct::getargc() {
		return argc;
	}
	void OpConstruct::setargc( unsigned int v ) {
		argc = v;
	}
OpCallMethod::OpCallMethod() {
	dispID = 0;
argc = 0;
}
OpCallMethod::~OpCallMethod() {
}
OpCallMethod* OpCallMethod::get( Reader *r, int end, Context *ctx ) {
	OpCallMethod* ret = new OpCallMethod;
	ret->parse( r, end, ctx );
	return ret;
}
OpCallMethod* OpCallMethod::getByName( const char *name ) {
	if( strcmp( name, "OpCallMethod" ) ) return NULL;
	OpCallMethod* ret = new OpCallMethod;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCallMethod::getdispID() {
		return dispID;
	}
	void OpCallMethod::setdispID( unsigned int v ) {
		dispID = v;
	}
	// Constant Size Primitive
	unsigned int OpCallMethod::getargc() {
		return argc;
	}
	void OpCallMethod::setargc( unsigned int v ) {
		argc = v;
	}
OpCallStatic::OpCallStatic() {
	methodID = 0;
argc = 0;
}
OpCallStatic::~OpCallStatic() {
}
OpCallStatic* OpCallStatic::get( Reader *r, int end, Context *ctx ) {
	OpCallStatic* ret = new OpCallStatic;
	ret->parse( r, end, ctx );
	return ret;
}
OpCallStatic* OpCallStatic::getByName( const char *name ) {
	if( strcmp( name, "OpCallStatic" ) ) return NULL;
	OpCallStatic* ret = new OpCallStatic;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCallStatic::getmethodID() {
		return methodID;
	}
	void OpCallStatic::setmethodID( unsigned int v ) {
		methodID = v;
	}
	// Constant Size Primitive
	unsigned int OpCallStatic::getargc() {
		return argc;
	}
	void OpCallStatic::setargc( unsigned int v ) {
		argc = v;
	}
OpCallSuper::OpCallSuper() {
	name = 0;
argc = 0;
}
OpCallSuper::~OpCallSuper() {
}
OpCallSuper* OpCallSuper::get( Reader *r, int end, Context *ctx ) {
	OpCallSuper* ret = new OpCallSuper;
	ret->parse( r, end, ctx );
	return ret;
}
OpCallSuper* OpCallSuper::getByName( const char *name ) {
	if( strcmp( name, "OpCallSuper" ) ) return NULL;
	OpCallSuper* ret = new OpCallSuper;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCallSuper::getname() {
		return name;
	}
	void OpCallSuper::setname( unsigned int v ) {
		name = v;
	}
	// Constant Size Primitive
	unsigned int OpCallSuper::getargc() {
		return argc;
	}
	void OpCallSuper::setargc( unsigned int v ) {
		argc = v;
	}
OpCallProperty::OpCallProperty() {
	name = 0;
argc = 0;
}
OpCallProperty::~OpCallProperty() {
}
OpCallProperty* OpCallProperty::get( Reader *r, int end, Context *ctx ) {
	OpCallProperty* ret = new OpCallProperty;
	ret->parse( r, end, ctx );
	return ret;
}
OpCallProperty* OpCallProperty::getByName( const char *name ) {
	if( strcmp( name, "OpCallProperty" ) ) return NULL;
	OpCallProperty* ret = new OpCallProperty;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCallProperty::getname() {
		return name;
	}
	void OpCallProperty::setname( unsigned int v ) {
		name = v;
	}
	// Constant Size Primitive
	unsigned int OpCallProperty::getargc() {
		return argc;
	}
	void OpCallProperty::setargc( unsigned int v ) {
		argc = v;
	}
OpReturnVoid::OpReturnVoid() {
}
OpReturnVoid::~OpReturnVoid() {
}
OpReturnVoid* OpReturnVoid::get( Reader *r, int end, Context *ctx ) {
	OpReturnVoid* ret = new OpReturnVoid;
	ret->parse( r, end, ctx );
	return ret;
}
OpReturnVoid* OpReturnVoid::getByName( const char *name ) {
	if( strcmp( name, "OpReturnVoid" ) ) return NULL;
	OpReturnVoid* ret = new OpReturnVoid;
	return ret;
}
OpReturnValue::OpReturnValue() {
}
OpReturnValue::~OpReturnValue() {
}
OpReturnValue* OpReturnValue::get( Reader *r, int end, Context *ctx ) {
	OpReturnValue* ret = new OpReturnValue;
	ret->parse( r, end, ctx );
	return ret;
}
OpReturnValue* OpReturnValue::getByName( const char *name ) {
	if( strcmp( name, "OpReturnValue" ) ) return NULL;
	OpReturnValue* ret = new OpReturnValue;
	return ret;
}
OpConstructSuper::OpConstructSuper() {
	argc = 0;
}
OpConstructSuper::~OpConstructSuper() {
}
OpConstructSuper* OpConstructSuper::get( Reader *r, int end, Context *ctx ) {
	OpConstructSuper* ret = new OpConstructSuper;
	ret->parse( r, end, ctx );
	return ret;
}
OpConstructSuper* OpConstructSuper::getByName( const char *name ) {
	if( strcmp( name, "OpConstructSuper" ) ) return NULL;
	OpConstructSuper* ret = new OpConstructSuper;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpConstructSuper::getargc() {
		return argc;
	}
	void OpConstructSuper::setargc( unsigned int v ) {
		argc = v;
	}
OpConstructProp::OpConstructProp() {
	name = 0;
argc = 0;
}
OpConstructProp::~OpConstructProp() {
}
OpConstructProp* OpConstructProp::get( Reader *r, int end, Context *ctx ) {
	OpConstructProp* ret = new OpConstructProp;
	ret->parse( r, end, ctx );
	return ret;
}
OpConstructProp* OpConstructProp::getByName( const char *name ) {
	if( strcmp( name, "OpConstructProp" ) ) return NULL;
	OpConstructProp* ret = new OpConstructProp;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpConstructProp::getname() {
		return name;
	}
	void OpConstructProp::setname( unsigned int v ) {
		name = v;
	}
	// Constant Size Primitive
	unsigned int OpConstructProp::getargc() {
		return argc;
	}
	void OpConstructProp::setargc( unsigned int v ) {
		argc = v;
	}
OpCallPropLex::OpCallPropLex() {
	name = 0;
argc = 0;
}
OpCallPropLex::~OpCallPropLex() {
}
OpCallPropLex* OpCallPropLex::get( Reader *r, int end, Context *ctx ) {
	OpCallPropLex* ret = new OpCallPropLex;
	ret->parse( r, end, ctx );
	return ret;
}
OpCallPropLex* OpCallPropLex::getByName( const char *name ) {
	if( strcmp( name, "OpCallPropLex" ) ) return NULL;
	OpCallPropLex* ret = new OpCallPropLex;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCallPropLex::getname() {
		return name;
	}
	void OpCallPropLex::setname( unsigned int v ) {
		name = v;
	}
	// Constant Size Primitive
	unsigned int OpCallPropLex::getargc() {
		return argc;
	}
	void OpCallPropLex::setargc( unsigned int v ) {
		argc = v;
	}
OpCallSuperVoid::OpCallSuperVoid() {
	name = 0;
argc = 0;
}
OpCallSuperVoid::~OpCallSuperVoid() {
}
OpCallSuperVoid* OpCallSuperVoid::get( Reader *r, int end, Context *ctx ) {
	OpCallSuperVoid* ret = new OpCallSuperVoid;
	ret->parse( r, end, ctx );
	return ret;
}
OpCallSuperVoid* OpCallSuperVoid::getByName( const char *name ) {
	if( strcmp( name, "OpCallSuperVoid" ) ) return NULL;
	OpCallSuperVoid* ret = new OpCallSuperVoid;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCallSuperVoid::getname() {
		return name;
	}
	void OpCallSuperVoid::setname( unsigned int v ) {
		name = v;
	}
	// Constant Size Primitive
	unsigned int OpCallSuperVoid::getargc() {
		return argc;
	}
	void OpCallSuperVoid::setargc( unsigned int v ) {
		argc = v;
	}
OpCallPropVoid::OpCallPropVoid() {
	name = 0;
argc = 0;
}
OpCallPropVoid::~OpCallPropVoid() {
}
OpCallPropVoid* OpCallPropVoid::get( Reader *r, int end, Context *ctx ) {
	OpCallPropVoid* ret = new OpCallPropVoid;
	ret->parse( r, end, ctx );
	return ret;
}
OpCallPropVoid* OpCallPropVoid::getByName( const char *name ) {
	if( strcmp( name, "OpCallPropVoid" ) ) return NULL;
	OpCallPropVoid* ret = new OpCallPropVoid;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCallPropVoid::getname() {
		return name;
	}
	void OpCallPropVoid::setname( unsigned int v ) {
		name = v;
	}
	// Constant Size Primitive
	unsigned int OpCallPropVoid::getargc() {
		return argc;
	}
	void OpCallPropVoid::setargc( unsigned int v ) {
		argc = v;
	}
OpNewObject::OpNewObject() {
	argc = 0;
}
OpNewObject::~OpNewObject() {
}
OpNewObject* OpNewObject::get( Reader *r, int end, Context *ctx ) {
	OpNewObject* ret = new OpNewObject;
	ret->parse( r, end, ctx );
	return ret;
}
OpNewObject* OpNewObject::getByName( const char *name ) {
	if( strcmp( name, "OpNewObject" ) ) return NULL;
	OpNewObject* ret = new OpNewObject;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpNewObject::getargc() {
		return argc;
	}
	void OpNewObject::setargc( unsigned int v ) {
		argc = v;
	}
OpNewArray::OpNewArray() {
	argc = 0;
}
OpNewArray::~OpNewArray() {
}
OpNewArray* OpNewArray::get( Reader *r, int end, Context *ctx ) {
	OpNewArray* ret = new OpNewArray;
	ret->parse( r, end, ctx );
	return ret;
}
OpNewArray* OpNewArray::getByName( const char *name ) {
	if( strcmp( name, "OpNewArray" ) ) return NULL;
	OpNewArray* ret = new OpNewArray;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpNewArray::getargc() {
		return argc;
	}
	void OpNewArray::setargc( unsigned int v ) {
		argc = v;
	}
OpNewActivation::OpNewActivation() {
}
OpNewActivation::~OpNewActivation() {
}
OpNewActivation* OpNewActivation::get( Reader *r, int end, Context *ctx ) {
	OpNewActivation* ret = new OpNewActivation;
	ret->parse( r, end, ctx );
	return ret;
}
OpNewActivation* OpNewActivation::getByName( const char *name ) {
	if( strcmp( name, "OpNewActivation" ) ) return NULL;
	OpNewActivation* ret = new OpNewActivation;
	return ret;
}
OpNewClass::OpNewClass() {
	classIndex = 0;
}
OpNewClass::~OpNewClass() {
}
OpNewClass* OpNewClass::get( Reader *r, int end, Context *ctx ) {
	OpNewClass* ret = new OpNewClass;
	ret->parse( r, end, ctx );
	return ret;
}
OpNewClass* OpNewClass::getByName( const char *name ) {
	if( strcmp( name, "OpNewClass" ) ) return NULL;
	OpNewClass* ret = new OpNewClass;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpNewClass::getclassIndex() {
		return classIndex;
	}
	void OpNewClass::setclassIndex( unsigned int v ) {
		classIndex = v;
	}
OpGetDescendants::OpGetDescendants() {
	name = 0;
}
OpGetDescendants::~OpGetDescendants() {
}
OpGetDescendants* OpGetDescendants::get( Reader *r, int end, Context *ctx ) {
	OpGetDescendants* ret = new OpGetDescendants;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetDescendants* OpGetDescendants::getByName( const char *name ) {
	if( strcmp( name, "OpGetDescendants" ) ) return NULL;
	OpGetDescendants* ret = new OpGetDescendants;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpGetDescendants::getname() {
		return name;
	}
	void OpGetDescendants::setname( unsigned int v ) {
		name = v;
	}
OpNewCatch::OpNewCatch() {
	exceptionIndex = 0;
}
OpNewCatch::~OpNewCatch() {
}
OpNewCatch* OpNewCatch::get( Reader *r, int end, Context *ctx ) {
	OpNewCatch* ret = new OpNewCatch;
	ret->parse( r, end, ctx );
	return ret;
}
OpNewCatch* OpNewCatch::getByName( const char *name ) {
	if( strcmp( name, "OpNewCatch" ) ) return NULL;
	OpNewCatch* ret = new OpNewCatch;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpNewCatch::getexceptionIndex() {
		return exceptionIndex;
	}
	void OpNewCatch::setexceptionIndex( unsigned int v ) {
		exceptionIndex = v;
	}
OpFindPropStrict::OpFindPropStrict() {
	name = 0;
}
OpFindPropStrict::~OpFindPropStrict() {
}
OpFindPropStrict* OpFindPropStrict::get( Reader *r, int end, Context *ctx ) {
	OpFindPropStrict* ret = new OpFindPropStrict;
	ret->parse( r, end, ctx );
	return ret;
}
OpFindPropStrict* OpFindPropStrict::getByName( const char *name ) {
	if( strcmp( name, "OpFindPropStrict" ) ) return NULL;
	OpFindPropStrict* ret = new OpFindPropStrict;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpFindPropStrict::getname() {
		return name;
	}
	void OpFindPropStrict::setname( unsigned int v ) {
		name = v;
	}
OpFindProperty::OpFindProperty() {
	name = 0;
}
OpFindProperty::~OpFindProperty() {
}
OpFindProperty* OpFindProperty::get( Reader *r, int end, Context *ctx ) {
	OpFindProperty* ret = new OpFindProperty;
	ret->parse( r, end, ctx );
	return ret;
}
OpFindProperty* OpFindProperty::getByName( const char *name ) {
	if( strcmp( name, "OpFindProperty" ) ) return NULL;
	OpFindProperty* ret = new OpFindProperty;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpFindProperty::getname() {
		return name;
	}
	void OpFindProperty::setname( unsigned int v ) {
		name = v;
	}
OpFindDef::OpFindDef() {
	name = 0;
}
OpFindDef::~OpFindDef() {
}
OpFindDef* OpFindDef::get( Reader *r, int end, Context *ctx ) {
	OpFindDef* ret = new OpFindDef;
	ret->parse( r, end, ctx );
	return ret;
}
OpFindDef* OpFindDef::getByName( const char *name ) {
	if( strcmp( name, "OpFindDef" ) ) return NULL;
	OpFindDef* ret = new OpFindDef;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpFindDef::getname() {
		return name;
	}
	void OpFindDef::setname( unsigned int v ) {
		name = v;
	}
OpGetLex::OpGetLex() {
	name = 0;
}
OpGetLex::~OpGetLex() {
}
OpGetLex* OpGetLex::get( Reader *r, int end, Context *ctx ) {
	OpGetLex* ret = new OpGetLex;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetLex* OpGetLex::getByName( const char *name ) {
	if( strcmp( name, "OpGetLex" ) ) return NULL;
	OpGetLex* ret = new OpGetLex;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpGetLex::getname() {
		return name;
	}
	void OpGetLex::setname( unsigned int v ) {
		name = v;
	}
OpSetProperty::OpSetProperty() {
	name = 0;
}
OpSetProperty::~OpSetProperty() {
}
OpSetProperty* OpSetProperty::get( Reader *r, int end, Context *ctx ) {
	OpSetProperty* ret = new OpSetProperty;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetProperty* OpSetProperty::getByName( const char *name ) {
	if( strcmp( name, "OpSetProperty" ) ) return NULL;
	OpSetProperty* ret = new OpSetProperty;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpSetProperty::getname() {
		return name;
	}
	void OpSetProperty::setname( unsigned int v ) {
		name = v;
	}
OpGetLocal::OpGetLocal() {
	address = 0;
}
OpGetLocal::~OpGetLocal() {
}
OpGetLocal* OpGetLocal::get( Reader *r, int end, Context *ctx ) {
	OpGetLocal* ret = new OpGetLocal;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetLocal* OpGetLocal::getByName( const char *name ) {
	if( strcmp( name, "OpGetLocal" ) ) return NULL;
	OpGetLocal* ret = new OpGetLocal;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpGetLocal::getaddress() {
		return address;
	}
	void OpGetLocal::setaddress( unsigned int v ) {
		address = v;
	}
OpSetLocal::OpSetLocal() {
	address = 0;
}
OpSetLocal::~OpSetLocal() {
}
OpSetLocal* OpSetLocal::get( Reader *r, int end, Context *ctx ) {
	OpSetLocal* ret = new OpSetLocal;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetLocal* OpSetLocal::getByName( const char *name ) {
	if( strcmp( name, "OpSetLocal" ) ) return NULL;
	OpSetLocal* ret = new OpSetLocal;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpSetLocal::getaddress() {
		return address;
	}
	void OpSetLocal::setaddress( unsigned int v ) {
		address = v;
	}
OpGetGlobalScope::OpGetGlobalScope() {
}
OpGetGlobalScope::~OpGetGlobalScope() {
}
OpGetGlobalScope* OpGetGlobalScope::get( Reader *r, int end, Context *ctx ) {
	OpGetGlobalScope* ret = new OpGetGlobalScope;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetGlobalScope* OpGetGlobalScope::getByName( const char *name ) {
	if( strcmp( name, "OpGetGlobalScope" ) ) return NULL;
	OpGetGlobalScope* ret = new OpGetGlobalScope;
	return ret;
}
OpGetScopeObject::OpGetScopeObject() {
	scopeIndex = 0;
}
OpGetScopeObject::~OpGetScopeObject() {
}
OpGetScopeObject* OpGetScopeObject::get( Reader *r, int end, Context *ctx ) {
	OpGetScopeObject* ret = new OpGetScopeObject;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetScopeObject* OpGetScopeObject::getByName( const char *name ) {
	if( strcmp( name, "OpGetScopeObject" ) ) return NULL;
	OpGetScopeObject* ret = new OpGetScopeObject;
	return ret;
}
	// Constant Size Primitive
	unsigned char OpGetScopeObject::getscopeIndex() {
		return scopeIndex;
	}
	void OpGetScopeObject::setscopeIndex( unsigned char v ) {
		scopeIndex = v;
	}
OpGetProperty::OpGetProperty() {
	name = 0;
}
OpGetProperty::~OpGetProperty() {
}
OpGetProperty* OpGetProperty::get( Reader *r, int end, Context *ctx ) {
	OpGetProperty* ret = new OpGetProperty;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetProperty* OpGetProperty::getByName( const char *name ) {
	if( strcmp( name, "OpGetProperty" ) ) return NULL;
	OpGetProperty* ret = new OpGetProperty;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpGetProperty::getname() {
		return name;
	}
	void OpGetProperty::setname( unsigned int v ) {
		name = v;
	}
OpInitProperty::OpInitProperty() {
	name = 0;
}
OpInitProperty::~OpInitProperty() {
}
OpInitProperty* OpInitProperty::get( Reader *r, int end, Context *ctx ) {
	OpInitProperty* ret = new OpInitProperty;
	ret->parse( r, end, ctx );
	return ret;
}
OpInitProperty* OpInitProperty::getByName( const char *name ) {
	if( strcmp( name, "OpInitProperty" ) ) return NULL;
	OpInitProperty* ret = new OpInitProperty;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpInitProperty::getname() {
		return name;
	}
	void OpInitProperty::setname( unsigned int v ) {
		name = v;
	}
OpDeleteProperty::OpDeleteProperty() {
	name = 0;
}
OpDeleteProperty::~OpDeleteProperty() {
}
OpDeleteProperty* OpDeleteProperty::get( Reader *r, int end, Context *ctx ) {
	OpDeleteProperty* ret = new OpDeleteProperty;
	ret->parse( r, end, ctx );
	return ret;
}
OpDeleteProperty* OpDeleteProperty::getByName( const char *name ) {
	if( strcmp( name, "OpDeleteProperty" ) ) return NULL;
	OpDeleteProperty* ret = new OpDeleteProperty;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpDeleteProperty::getname() {
		return name;
	}
	void OpDeleteProperty::setname( unsigned int v ) {
		name = v;
	}
OpGetSlot::OpGetSlot() {
	slotID = 0;
}
OpGetSlot::~OpGetSlot() {
}
OpGetSlot* OpGetSlot::get( Reader *r, int end, Context *ctx ) {
	OpGetSlot* ret = new OpGetSlot;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetSlot* OpGetSlot::getByName( const char *name ) {
	if( strcmp( name, "OpGetSlot" ) ) return NULL;
	OpGetSlot* ret = new OpGetSlot;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpGetSlot::getslotID() {
		return slotID;
	}
	void OpGetSlot::setslotID( unsigned int v ) {
		slotID = v;
	}
OpSetSlot::OpSetSlot() {
	slotID = 0;
}
OpSetSlot::~OpSetSlot() {
}
OpSetSlot* OpSetSlot::get( Reader *r, int end, Context *ctx ) {
	OpSetSlot* ret = new OpSetSlot;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetSlot* OpSetSlot::getByName( const char *name ) {
	if( strcmp( name, "OpSetSlot" ) ) return NULL;
	OpSetSlot* ret = new OpSetSlot;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpSetSlot::getslotID() {
		return slotID;
	}
	void OpSetSlot::setslotID( unsigned int v ) {
		slotID = v;
	}
OpGetGlobalSlot::OpGetGlobalSlot() {
	slotID = 0;
}
OpGetGlobalSlot::~OpGetGlobalSlot() {
}
OpGetGlobalSlot* OpGetGlobalSlot::get( Reader *r, int end, Context *ctx ) {
	OpGetGlobalSlot* ret = new OpGetGlobalSlot;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetGlobalSlot* OpGetGlobalSlot::getByName( const char *name ) {
	if( strcmp( name, "OpGetGlobalSlot" ) ) return NULL;
	OpGetGlobalSlot* ret = new OpGetGlobalSlot;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpGetGlobalSlot::getslotID() {
		return slotID;
	}
	void OpGetGlobalSlot::setslotID( unsigned int v ) {
		slotID = v;
	}
OpSetGlobalSlot::OpSetGlobalSlot() {
	slotID = 0;
}
OpSetGlobalSlot::~OpSetGlobalSlot() {
}
OpSetGlobalSlot* OpSetGlobalSlot::get( Reader *r, int end, Context *ctx ) {
	OpSetGlobalSlot* ret = new OpSetGlobalSlot;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetGlobalSlot* OpSetGlobalSlot::getByName( const char *name ) {
	if( strcmp( name, "OpSetGlobalSlot" ) ) return NULL;
	OpSetGlobalSlot* ret = new OpSetGlobalSlot;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpSetGlobalSlot::getslotID() {
		return slotID;
	}
	void OpSetGlobalSlot::setslotID( unsigned int v ) {
		slotID = v;
	}
OpConvertS::OpConvertS() {
}
OpConvertS::~OpConvertS() {
}
OpConvertS* OpConvertS::get( Reader *r, int end, Context *ctx ) {
	OpConvertS* ret = new OpConvertS;
	ret->parse( r, end, ctx );
	return ret;
}
OpConvertS* OpConvertS::getByName( const char *name ) {
	if( strcmp( name, "OpConvertS" ) ) return NULL;
	OpConvertS* ret = new OpConvertS;
	return ret;
}
OpEscXelem::OpEscXelem() {
}
OpEscXelem::~OpEscXelem() {
}
OpEscXelem* OpEscXelem::get( Reader *r, int end, Context *ctx ) {
	OpEscXelem* ret = new OpEscXelem;
	ret->parse( r, end, ctx );
	return ret;
}
OpEscXelem* OpEscXelem::getByName( const char *name ) {
	if( strcmp( name, "OpEscXelem" ) ) return NULL;
	OpEscXelem* ret = new OpEscXelem;
	return ret;
}
OpEscXattr::OpEscXattr() {
}
OpEscXattr::~OpEscXattr() {
}
OpEscXattr* OpEscXattr::get( Reader *r, int end, Context *ctx ) {
	OpEscXattr* ret = new OpEscXattr;
	ret->parse( r, end, ctx );
	return ret;
}
OpEscXattr* OpEscXattr::getByName( const char *name ) {
	if( strcmp( name, "OpEscXattr" ) ) return NULL;
	OpEscXattr* ret = new OpEscXattr;
	return ret;
}
OpConvertI::OpConvertI() {
}
OpConvertI::~OpConvertI() {
}
OpConvertI* OpConvertI::get( Reader *r, int end, Context *ctx ) {
	OpConvertI* ret = new OpConvertI;
	ret->parse( r, end, ctx );
	return ret;
}
OpConvertI* OpConvertI::getByName( const char *name ) {
	if( strcmp( name, "OpConvertI" ) ) return NULL;
	OpConvertI* ret = new OpConvertI;
	return ret;
}
OpConvertU::OpConvertU() {
}
OpConvertU::~OpConvertU() {
}
OpConvertU* OpConvertU::get( Reader *r, int end, Context *ctx ) {
	OpConvertU* ret = new OpConvertU;
	ret->parse( r, end, ctx );
	return ret;
}
OpConvertU* OpConvertU::getByName( const char *name ) {
	if( strcmp( name, "OpConvertU" ) ) return NULL;
	OpConvertU* ret = new OpConvertU;
	return ret;
}
OpConvertD::OpConvertD() {
}
OpConvertD::~OpConvertD() {
}
OpConvertD* OpConvertD::get( Reader *r, int end, Context *ctx ) {
	OpConvertD* ret = new OpConvertD;
	ret->parse( r, end, ctx );
	return ret;
}
OpConvertD* OpConvertD::getByName( const char *name ) {
	if( strcmp( name, "OpConvertD" ) ) return NULL;
	OpConvertD* ret = new OpConvertD;
	return ret;
}
OpConvertB::OpConvertB() {
}
OpConvertB::~OpConvertB() {
}
OpConvertB* OpConvertB::get( Reader *r, int end, Context *ctx ) {
	OpConvertB* ret = new OpConvertB;
	ret->parse( r, end, ctx );
	return ret;
}
OpConvertB* OpConvertB::getByName( const char *name ) {
	if( strcmp( name, "OpConvertB" ) ) return NULL;
	OpConvertB* ret = new OpConvertB;
	return ret;
}
OpConvertO::OpConvertO() {
}
OpConvertO::~OpConvertO() {
}
OpConvertO* OpConvertO::get( Reader *r, int end, Context *ctx ) {
	OpConvertO* ret = new OpConvertO;
	ret->parse( r, end, ctx );
	return ret;
}
OpConvertO* OpConvertO::getByName( const char *name ) {
	if( strcmp( name, "OpConvertO" ) ) return NULL;
	OpConvertO* ret = new OpConvertO;
	return ret;
}
OpCheckFilter::OpCheckFilter() {
}
OpCheckFilter::~OpCheckFilter() {
}
OpCheckFilter* OpCheckFilter::get( Reader *r, int end, Context *ctx ) {
	OpCheckFilter* ret = new OpCheckFilter;
	ret->parse( r, end, ctx );
	return ret;
}
OpCheckFilter* OpCheckFilter::getByName( const char *name ) {
	if( strcmp( name, "OpCheckFilter" ) ) return NULL;
	OpCheckFilter* ret = new OpCheckFilter;
	return ret;
}
OpCoerce::OpCoerce() {
	name = 0;
}
OpCoerce::~OpCoerce() {
}
OpCoerce* OpCoerce::get( Reader *r, int end, Context *ctx ) {
	OpCoerce* ret = new OpCoerce;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerce* OpCoerce::getByName( const char *name ) {
	if( strcmp( name, "OpCoerce" ) ) return NULL;
	OpCoerce* ret = new OpCoerce;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpCoerce::getname() {
		return name;
	}
	void OpCoerce::setname( unsigned int v ) {
		name = v;
	}
OpCoerceB::OpCoerceB() {
}
OpCoerceB::~OpCoerceB() {
}
OpCoerceB* OpCoerceB::get( Reader *r, int end, Context *ctx ) {
	OpCoerceB* ret = new OpCoerceB;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerceB* OpCoerceB::getByName( const char *name ) {
	if( strcmp( name, "OpCoerceB" ) ) return NULL;
	OpCoerceB* ret = new OpCoerceB;
	return ret;
}
OpCoerceA::OpCoerceA() {
}
OpCoerceA::~OpCoerceA() {
}
OpCoerceA* OpCoerceA::get( Reader *r, int end, Context *ctx ) {
	OpCoerceA* ret = new OpCoerceA;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerceA* OpCoerceA::getByName( const char *name ) {
	if( strcmp( name, "OpCoerceA" ) ) return NULL;
	OpCoerceA* ret = new OpCoerceA;
	return ret;
}
OpCoerceI::OpCoerceI() {
}
OpCoerceI::~OpCoerceI() {
}
OpCoerceI* OpCoerceI::get( Reader *r, int end, Context *ctx ) {
	OpCoerceI* ret = new OpCoerceI;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerceI* OpCoerceI::getByName( const char *name ) {
	if( strcmp( name, "OpCoerceI" ) ) return NULL;
	OpCoerceI* ret = new OpCoerceI;
	return ret;
}
OpCoerceD::OpCoerceD() {
}
OpCoerceD::~OpCoerceD() {
}
OpCoerceD* OpCoerceD::get( Reader *r, int end, Context *ctx ) {
	OpCoerceD* ret = new OpCoerceD;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerceD* OpCoerceD::getByName( const char *name ) {
	if( strcmp( name, "OpCoerceD" ) ) return NULL;
	OpCoerceD* ret = new OpCoerceD;
	return ret;
}
OpCoerceS::OpCoerceS() {
}
OpCoerceS::~OpCoerceS() {
}
OpCoerceS* OpCoerceS::get( Reader *r, int end, Context *ctx ) {
	OpCoerceS* ret = new OpCoerceS;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerceS* OpCoerceS::getByName( const char *name ) {
	if( strcmp( name, "OpCoerceS" ) ) return NULL;
	OpCoerceS* ret = new OpCoerceS;
	return ret;
}
OpAsType::OpAsType() {
	name = 0;
}
OpAsType::~OpAsType() {
}
OpAsType* OpAsType::get( Reader *r, int end, Context *ctx ) {
	OpAsType* ret = new OpAsType;
	ret->parse( r, end, ctx );
	return ret;
}
OpAsType* OpAsType::getByName( const char *name ) {
	if( strcmp( name, "OpAsType" ) ) return NULL;
	OpAsType* ret = new OpAsType;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpAsType::getname() {
		return name;
	}
	void OpAsType::setname( unsigned int v ) {
		name = v;
	}
OpAsTypeLate::OpAsTypeLate() {
}
OpAsTypeLate::~OpAsTypeLate() {
}
OpAsTypeLate* OpAsTypeLate::get( Reader *r, int end, Context *ctx ) {
	OpAsTypeLate* ret = new OpAsTypeLate;
	ret->parse( r, end, ctx );
	return ret;
}
OpAsTypeLate* OpAsTypeLate::getByName( const char *name ) {
	if( strcmp( name, "OpAsTypeLate" ) ) return NULL;
	OpAsTypeLate* ret = new OpAsTypeLate;
	return ret;
}
OpCoerceU::OpCoerceU() {
}
OpCoerceU::~OpCoerceU() {
}
OpCoerceU* OpCoerceU::get( Reader *r, int end, Context *ctx ) {
	OpCoerceU* ret = new OpCoerceU;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerceU* OpCoerceU::getByName( const char *name ) {
	if( strcmp( name, "OpCoerceU" ) ) return NULL;
	OpCoerceU* ret = new OpCoerceU;
	return ret;
}
OpCoerceO::OpCoerceO() {
}
OpCoerceO::~OpCoerceO() {
}
OpCoerceO* OpCoerceO::get( Reader *r, int end, Context *ctx ) {
	OpCoerceO* ret = new OpCoerceO;
	ret->parse( r, end, ctx );
	return ret;
}
OpCoerceO* OpCoerceO::getByName( const char *name ) {
	if( strcmp( name, "OpCoerceO" ) ) return NULL;
	OpCoerceO* ret = new OpCoerceO;
	return ret;
}
OpNegate::OpNegate() {
}
OpNegate::~OpNegate() {
}
OpNegate* OpNegate::get( Reader *r, int end, Context *ctx ) {
	OpNegate* ret = new OpNegate;
	ret->parse( r, end, ctx );
	return ret;
}
OpNegate* OpNegate::getByName( const char *name ) {
	if( strcmp( name, "OpNegate" ) ) return NULL;
	OpNegate* ret = new OpNegate;
	return ret;
}
OpIncrement::OpIncrement() {
}
OpIncrement::~OpIncrement() {
}
OpIncrement* OpIncrement::get( Reader *r, int end, Context *ctx ) {
	OpIncrement* ret = new OpIncrement;
	ret->parse( r, end, ctx );
	return ret;
}
OpIncrement* OpIncrement::getByName( const char *name ) {
	if( strcmp( name, "OpIncrement" ) ) return NULL;
	OpIncrement* ret = new OpIncrement;
	return ret;
}
OpIncLocal::OpIncLocal() {
	address = 0;
}
OpIncLocal::~OpIncLocal() {
}
OpIncLocal* OpIncLocal::get( Reader *r, int end, Context *ctx ) {
	OpIncLocal* ret = new OpIncLocal;
	ret->parse( r, end, ctx );
	return ret;
}
OpIncLocal* OpIncLocal::getByName( const char *name ) {
	if( strcmp( name, "OpIncLocal" ) ) return NULL;
	OpIncLocal* ret = new OpIncLocal;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpIncLocal::getaddress() {
		return address;
	}
	void OpIncLocal::setaddress( unsigned int v ) {
		address = v;
	}
OpDecrement::OpDecrement() {
}
OpDecrement::~OpDecrement() {
}
OpDecrement* OpDecrement::get( Reader *r, int end, Context *ctx ) {
	OpDecrement* ret = new OpDecrement;
	ret->parse( r, end, ctx );
	return ret;
}
OpDecrement* OpDecrement::getByName( const char *name ) {
	if( strcmp( name, "OpDecrement" ) ) return NULL;
	OpDecrement* ret = new OpDecrement;
	return ret;
}
OpDecLocal::OpDecLocal() {
	address = 0;
}
OpDecLocal::~OpDecLocal() {
}
OpDecLocal* OpDecLocal::get( Reader *r, int end, Context *ctx ) {
	OpDecLocal* ret = new OpDecLocal;
	ret->parse( r, end, ctx );
	return ret;
}
OpDecLocal* OpDecLocal::getByName( const char *name ) {
	if( strcmp( name, "OpDecLocal" ) ) return NULL;
	OpDecLocal* ret = new OpDecLocal;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpDecLocal::getaddress() {
		return address;
	}
	void OpDecLocal::setaddress( unsigned int v ) {
		address = v;
	}
OpTypeOf::OpTypeOf() {
}
OpTypeOf::~OpTypeOf() {
}
OpTypeOf* OpTypeOf::get( Reader *r, int end, Context *ctx ) {
	OpTypeOf* ret = new OpTypeOf;
	ret->parse( r, end, ctx );
	return ret;
}
OpTypeOf* OpTypeOf::getByName( const char *name ) {
	if( strcmp( name, "OpTypeOf" ) ) return NULL;
	OpTypeOf* ret = new OpTypeOf;
	return ret;
}
OpNot::OpNot() {
}
OpNot::~OpNot() {
}
OpNot* OpNot::get( Reader *r, int end, Context *ctx ) {
	OpNot* ret = new OpNot;
	ret->parse( r, end, ctx );
	return ret;
}
OpNot* OpNot::getByName( const char *name ) {
	if( strcmp( name, "OpNot" ) ) return NULL;
	OpNot* ret = new OpNot;
	return ret;
}
OpBitNot::OpBitNot() {
}
OpBitNot::~OpBitNot() {
}
OpBitNot* OpBitNot::get( Reader *r, int end, Context *ctx ) {
	OpBitNot* ret = new OpBitNot;
	ret->parse( r, end, ctx );
	return ret;
}
OpBitNot* OpBitNot::getByName( const char *name ) {
	if( strcmp( name, "OpBitNot" ) ) return NULL;
	OpBitNot* ret = new OpBitNot;
	return ret;
}
OpAdd::OpAdd() {
}
OpAdd::~OpAdd() {
}
OpAdd* OpAdd::get( Reader *r, int end, Context *ctx ) {
	OpAdd* ret = new OpAdd;
	ret->parse( r, end, ctx );
	return ret;
}
OpAdd* OpAdd::getByName( const char *name ) {
	if( strcmp( name, "OpAdd" ) ) return NULL;
	OpAdd* ret = new OpAdd;
	return ret;
}
OpSubtract::OpSubtract() {
}
OpSubtract::~OpSubtract() {
}
OpSubtract* OpSubtract::get( Reader *r, int end, Context *ctx ) {
	OpSubtract* ret = new OpSubtract;
	ret->parse( r, end, ctx );
	return ret;
}
OpSubtract* OpSubtract::getByName( const char *name ) {
	if( strcmp( name, "OpSubtract" ) ) return NULL;
	OpSubtract* ret = new OpSubtract;
	return ret;
}
OpMultiply::OpMultiply() {
}
OpMultiply::~OpMultiply() {
}
OpMultiply* OpMultiply::get( Reader *r, int end, Context *ctx ) {
	OpMultiply* ret = new OpMultiply;
	ret->parse( r, end, ctx );
	return ret;
}
OpMultiply* OpMultiply::getByName( const char *name ) {
	if( strcmp( name, "OpMultiply" ) ) return NULL;
	OpMultiply* ret = new OpMultiply;
	return ret;
}
OpDivide::OpDivide() {
}
OpDivide::~OpDivide() {
}
OpDivide* OpDivide::get( Reader *r, int end, Context *ctx ) {
	OpDivide* ret = new OpDivide;
	ret->parse( r, end, ctx );
	return ret;
}
OpDivide* OpDivide::getByName( const char *name ) {
	if( strcmp( name, "OpDivide" ) ) return NULL;
	OpDivide* ret = new OpDivide;
	return ret;
}
OpModulo::OpModulo() {
}
OpModulo::~OpModulo() {
}
OpModulo* OpModulo::get( Reader *r, int end, Context *ctx ) {
	OpModulo* ret = new OpModulo;
	ret->parse( r, end, ctx );
	return ret;
}
OpModulo* OpModulo::getByName( const char *name ) {
	if( strcmp( name, "OpModulo" ) ) return NULL;
	OpModulo* ret = new OpModulo;
	return ret;
}
OpLShift::OpLShift() {
}
OpLShift::~OpLShift() {
}
OpLShift* OpLShift::get( Reader *r, int end, Context *ctx ) {
	OpLShift* ret = new OpLShift;
	ret->parse( r, end, ctx );
	return ret;
}
OpLShift* OpLShift::getByName( const char *name ) {
	if( strcmp( name, "OpLShift" ) ) return NULL;
	OpLShift* ret = new OpLShift;
	return ret;
}
OpRShift::OpRShift() {
}
OpRShift::~OpRShift() {
}
OpRShift* OpRShift::get( Reader *r, int end, Context *ctx ) {
	OpRShift* ret = new OpRShift;
	ret->parse( r, end, ctx );
	return ret;
}
OpRShift* OpRShift::getByName( const char *name ) {
	if( strcmp( name, "OpRShift" ) ) return NULL;
	OpRShift* ret = new OpRShift;
	return ret;
}
OpURShift::OpURShift() {
}
OpURShift::~OpURShift() {
}
OpURShift* OpURShift::get( Reader *r, int end, Context *ctx ) {
	OpURShift* ret = new OpURShift;
	ret->parse( r, end, ctx );
	return ret;
}
OpURShift* OpURShift::getByName( const char *name ) {
	if( strcmp( name, "OpURShift" ) ) return NULL;
	OpURShift* ret = new OpURShift;
	return ret;
}
OpBitAnd::OpBitAnd() {
}
OpBitAnd::~OpBitAnd() {
}
OpBitAnd* OpBitAnd::get( Reader *r, int end, Context *ctx ) {
	OpBitAnd* ret = new OpBitAnd;
	ret->parse( r, end, ctx );
	return ret;
}
OpBitAnd* OpBitAnd::getByName( const char *name ) {
	if( strcmp( name, "OpBitAnd" ) ) return NULL;
	OpBitAnd* ret = new OpBitAnd;
	return ret;
}
OpBitOr::OpBitOr() {
}
OpBitOr::~OpBitOr() {
}
OpBitOr* OpBitOr::get( Reader *r, int end, Context *ctx ) {
	OpBitOr* ret = new OpBitOr;
	ret->parse( r, end, ctx );
	return ret;
}
OpBitOr* OpBitOr::getByName( const char *name ) {
	if( strcmp( name, "OpBitOr" ) ) return NULL;
	OpBitOr* ret = new OpBitOr;
	return ret;
}
OpBitXor::OpBitXor() {
}
OpBitXor::~OpBitXor() {
}
OpBitXor* OpBitXor::get( Reader *r, int end, Context *ctx ) {
	OpBitXor* ret = new OpBitXor;
	ret->parse( r, end, ctx );
	return ret;
}
OpBitXor* OpBitXor::getByName( const char *name ) {
	if( strcmp( name, "OpBitXor" ) ) return NULL;
	OpBitXor* ret = new OpBitXor;
	return ret;
}
OpEquals::OpEquals() {
}
OpEquals::~OpEquals() {
}
OpEquals* OpEquals::get( Reader *r, int end, Context *ctx ) {
	OpEquals* ret = new OpEquals;
	ret->parse( r, end, ctx );
	return ret;
}
OpEquals* OpEquals::getByName( const char *name ) {
	if( strcmp( name, "OpEquals" ) ) return NULL;
	OpEquals* ret = new OpEquals;
	return ret;
}
OpStrictEquals::OpStrictEquals() {
}
OpStrictEquals::~OpStrictEquals() {
}
OpStrictEquals* OpStrictEquals::get( Reader *r, int end, Context *ctx ) {
	OpStrictEquals* ret = new OpStrictEquals;
	ret->parse( r, end, ctx );
	return ret;
}
OpStrictEquals* OpStrictEquals::getByName( const char *name ) {
	if( strcmp( name, "OpStrictEquals" ) ) return NULL;
	OpStrictEquals* ret = new OpStrictEquals;
	return ret;
}
OpLessThan::OpLessThan() {
}
OpLessThan::~OpLessThan() {
}
OpLessThan* OpLessThan::get( Reader *r, int end, Context *ctx ) {
	OpLessThan* ret = new OpLessThan;
	ret->parse( r, end, ctx );
	return ret;
}
OpLessThan* OpLessThan::getByName( const char *name ) {
	if( strcmp( name, "OpLessThan" ) ) return NULL;
	OpLessThan* ret = new OpLessThan;
	return ret;
}
OpLessEquals::OpLessEquals() {
}
OpLessEquals::~OpLessEquals() {
}
OpLessEquals* OpLessEquals::get( Reader *r, int end, Context *ctx ) {
	OpLessEquals* ret = new OpLessEquals;
	ret->parse( r, end, ctx );
	return ret;
}
OpLessEquals* OpLessEquals::getByName( const char *name ) {
	if( strcmp( name, "OpLessEquals" ) ) return NULL;
	OpLessEquals* ret = new OpLessEquals;
	return ret;
}
OpGreaterThan::OpGreaterThan() {
}
OpGreaterThan::~OpGreaterThan() {
}
OpGreaterThan* OpGreaterThan::get( Reader *r, int end, Context *ctx ) {
	OpGreaterThan* ret = new OpGreaterThan;
	ret->parse( r, end, ctx );
	return ret;
}
OpGreaterThan* OpGreaterThan::getByName( const char *name ) {
	if( strcmp( name, "OpGreaterThan" ) ) return NULL;
	OpGreaterThan* ret = new OpGreaterThan;
	return ret;
}
OpGreaterEquals::OpGreaterEquals() {
}
OpGreaterEquals::~OpGreaterEquals() {
}
OpGreaterEquals* OpGreaterEquals::get( Reader *r, int end, Context *ctx ) {
	OpGreaterEquals* ret = new OpGreaterEquals;
	ret->parse( r, end, ctx );
	return ret;
}
OpGreaterEquals* OpGreaterEquals::getByName( const char *name ) {
	if( strcmp( name, "OpGreaterEquals" ) ) return NULL;
	OpGreaterEquals* ret = new OpGreaterEquals;
	return ret;
}
OpInstanceOf::OpInstanceOf() {
}
OpInstanceOf::~OpInstanceOf() {
}
OpInstanceOf* OpInstanceOf::get( Reader *r, int end, Context *ctx ) {
	OpInstanceOf* ret = new OpInstanceOf;
	ret->parse( r, end, ctx );
	return ret;
}
OpInstanceOf* OpInstanceOf::getByName( const char *name ) {
	if( strcmp( name, "OpInstanceOf" ) ) return NULL;
	OpInstanceOf* ret = new OpInstanceOf;
	return ret;
}
OpIsType::OpIsType() {
	name = 0;
}
OpIsType::~OpIsType() {
}
OpIsType* OpIsType::get( Reader *r, int end, Context *ctx ) {
	OpIsType* ret = new OpIsType;
	ret->parse( r, end, ctx );
	return ret;
}
OpIsType* OpIsType::getByName( const char *name ) {
	if( strcmp( name, "OpIsType" ) ) return NULL;
	OpIsType* ret = new OpIsType;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpIsType::getname() {
		return name;
	}
	void OpIsType::setname( unsigned int v ) {
		name = v;
	}
OpIsTypeLate::OpIsTypeLate() {
}
OpIsTypeLate::~OpIsTypeLate() {
}
OpIsTypeLate* OpIsTypeLate::get( Reader *r, int end, Context *ctx ) {
	OpIsTypeLate* ret = new OpIsTypeLate;
	ret->parse( r, end, ctx );
	return ret;
}
OpIsTypeLate* OpIsTypeLate::getByName( const char *name ) {
	if( strcmp( name, "OpIsTypeLate" ) ) return NULL;
	OpIsTypeLate* ret = new OpIsTypeLate;
	return ret;
}
OpIn::OpIn() {
}
OpIn::~OpIn() {
}
OpIn* OpIn::get( Reader *r, int end, Context *ctx ) {
	OpIn* ret = new OpIn;
	ret->parse( r, end, ctx );
	return ret;
}
OpIn* OpIn::getByName( const char *name ) {
	if( strcmp( name, "OpIn" ) ) return NULL;
	OpIn* ret = new OpIn;
	return ret;
}
OpIncrementI::OpIncrementI() {
}
OpIncrementI::~OpIncrementI() {
}
OpIncrementI* OpIncrementI::get( Reader *r, int end, Context *ctx ) {
	OpIncrementI* ret = new OpIncrementI;
	ret->parse( r, end, ctx );
	return ret;
}
OpIncrementI* OpIncrementI::getByName( const char *name ) {
	if( strcmp( name, "OpIncrementI" ) ) return NULL;
	OpIncrementI* ret = new OpIncrementI;
	return ret;
}
OpDecrementI::OpDecrementI() {
}
OpDecrementI::~OpDecrementI() {
}
OpDecrementI* OpDecrementI::get( Reader *r, int end, Context *ctx ) {
	OpDecrementI* ret = new OpDecrementI;
	ret->parse( r, end, ctx );
	return ret;
}
OpDecrementI* OpDecrementI::getByName( const char *name ) {
	if( strcmp( name, "OpDecrementI" ) ) return NULL;
	OpDecrementI* ret = new OpDecrementI;
	return ret;
}
OpIncLocalI::OpIncLocalI() {
	address = 0;
}
OpIncLocalI::~OpIncLocalI() {
}
OpIncLocalI* OpIncLocalI::get( Reader *r, int end, Context *ctx ) {
	OpIncLocalI* ret = new OpIncLocalI;
	ret->parse( r, end, ctx );
	return ret;
}
OpIncLocalI* OpIncLocalI::getByName( const char *name ) {
	if( strcmp( name, "OpIncLocalI" ) ) return NULL;
	OpIncLocalI* ret = new OpIncLocalI;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpIncLocalI::getaddress() {
		return address;
	}
	void OpIncLocalI::setaddress( unsigned int v ) {
		address = v;
	}
OpDecLocalI::OpDecLocalI() {
	address = 0;
}
OpDecLocalI::~OpDecLocalI() {
}
OpDecLocalI* OpDecLocalI::get( Reader *r, int end, Context *ctx ) {
	OpDecLocalI* ret = new OpDecLocalI;
	ret->parse( r, end, ctx );
	return ret;
}
OpDecLocalI* OpDecLocalI::getByName( const char *name ) {
	if( strcmp( name, "OpDecLocalI" ) ) return NULL;
	OpDecLocalI* ret = new OpDecLocalI;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpDecLocalI::getaddress() {
		return address;
	}
	void OpDecLocalI::setaddress( unsigned int v ) {
		address = v;
	}
OpNegateI::OpNegateI() {
}
OpNegateI::~OpNegateI() {
}
OpNegateI* OpNegateI::get( Reader *r, int end, Context *ctx ) {
	OpNegateI* ret = new OpNegateI;
	ret->parse( r, end, ctx );
	return ret;
}
OpNegateI* OpNegateI::getByName( const char *name ) {
	if( strcmp( name, "OpNegateI" ) ) return NULL;
	OpNegateI* ret = new OpNegateI;
	return ret;
}
OpAddI::OpAddI() {
}
OpAddI::~OpAddI() {
}
OpAddI* OpAddI::get( Reader *r, int end, Context *ctx ) {
	OpAddI* ret = new OpAddI;
	ret->parse( r, end, ctx );
	return ret;
}
OpAddI* OpAddI::getByName( const char *name ) {
	if( strcmp( name, "OpAddI" ) ) return NULL;
	OpAddI* ret = new OpAddI;
	return ret;
}
OpSubtractI::OpSubtractI() {
}
OpSubtractI::~OpSubtractI() {
}
OpSubtractI* OpSubtractI::get( Reader *r, int end, Context *ctx ) {
	OpSubtractI* ret = new OpSubtractI;
	ret->parse( r, end, ctx );
	return ret;
}
OpSubtractI* OpSubtractI::getByName( const char *name ) {
	if( strcmp( name, "OpSubtractI" ) ) return NULL;
	OpSubtractI* ret = new OpSubtractI;
	return ret;
}
OpMultiplyI::OpMultiplyI() {
}
OpMultiplyI::~OpMultiplyI() {
}
OpMultiplyI* OpMultiplyI::get( Reader *r, int end, Context *ctx ) {
	OpMultiplyI* ret = new OpMultiplyI;
	ret->parse( r, end, ctx );
	return ret;
}
OpMultiplyI* OpMultiplyI::getByName( const char *name ) {
	if( strcmp( name, "OpMultiplyI" ) ) return NULL;
	OpMultiplyI* ret = new OpMultiplyI;
	return ret;
}
OpGetLocal0::OpGetLocal0() {
}
OpGetLocal0::~OpGetLocal0() {
}
OpGetLocal0* OpGetLocal0::get( Reader *r, int end, Context *ctx ) {
	OpGetLocal0* ret = new OpGetLocal0;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetLocal0* OpGetLocal0::getByName( const char *name ) {
	if( strcmp( name, "OpGetLocal0" ) ) return NULL;
	OpGetLocal0* ret = new OpGetLocal0;
	return ret;
}
OpGetLocal1::OpGetLocal1() {
}
OpGetLocal1::~OpGetLocal1() {
}
OpGetLocal1* OpGetLocal1::get( Reader *r, int end, Context *ctx ) {
	OpGetLocal1* ret = new OpGetLocal1;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetLocal1* OpGetLocal1::getByName( const char *name ) {
	if( strcmp( name, "OpGetLocal1" ) ) return NULL;
	OpGetLocal1* ret = new OpGetLocal1;
	return ret;
}
OpGetLocal2::OpGetLocal2() {
}
OpGetLocal2::~OpGetLocal2() {
}
OpGetLocal2* OpGetLocal2::get( Reader *r, int end, Context *ctx ) {
	OpGetLocal2* ret = new OpGetLocal2;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetLocal2* OpGetLocal2::getByName( const char *name ) {
	if( strcmp( name, "OpGetLocal2" ) ) return NULL;
	OpGetLocal2* ret = new OpGetLocal2;
	return ret;
}
OpGetLocal3::OpGetLocal3() {
}
OpGetLocal3::~OpGetLocal3() {
}
OpGetLocal3* OpGetLocal3::get( Reader *r, int end, Context *ctx ) {
	OpGetLocal3* ret = new OpGetLocal3;
	ret->parse( r, end, ctx );
	return ret;
}
OpGetLocal3* OpGetLocal3::getByName( const char *name ) {
	if( strcmp( name, "OpGetLocal3" ) ) return NULL;
	OpGetLocal3* ret = new OpGetLocal3;
	return ret;
}
OpSetLocal0::OpSetLocal0() {
}
OpSetLocal0::~OpSetLocal0() {
}
OpSetLocal0* OpSetLocal0::get( Reader *r, int end, Context *ctx ) {
	OpSetLocal0* ret = new OpSetLocal0;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetLocal0* OpSetLocal0::getByName( const char *name ) {
	if( strcmp( name, "OpSetLocal0" ) ) return NULL;
	OpSetLocal0* ret = new OpSetLocal0;
	return ret;
}
OpSetLocal1::OpSetLocal1() {
}
OpSetLocal1::~OpSetLocal1() {
}
OpSetLocal1* OpSetLocal1::get( Reader *r, int end, Context *ctx ) {
	OpSetLocal1* ret = new OpSetLocal1;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetLocal1* OpSetLocal1::getByName( const char *name ) {
	if( strcmp( name, "OpSetLocal1" ) ) return NULL;
	OpSetLocal1* ret = new OpSetLocal1;
	return ret;
}
OpSetLocal2::OpSetLocal2() {
}
OpSetLocal2::~OpSetLocal2() {
}
OpSetLocal2* OpSetLocal2::get( Reader *r, int end, Context *ctx ) {
	OpSetLocal2* ret = new OpSetLocal2;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetLocal2* OpSetLocal2::getByName( const char *name ) {
	if( strcmp( name, "OpSetLocal2" ) ) return NULL;
	OpSetLocal2* ret = new OpSetLocal2;
	return ret;
}
OpSetLocal3::OpSetLocal3() {
}
OpSetLocal3::~OpSetLocal3() {
}
OpSetLocal3* OpSetLocal3::get( Reader *r, int end, Context *ctx ) {
	OpSetLocal3* ret = new OpSetLocal3;
	ret->parse( r, end, ctx );
	return ret;
}
OpSetLocal3* OpSetLocal3::getByName( const char *name ) {
	if( strcmp( name, "OpSetLocal3" ) ) return NULL;
	OpSetLocal3* ret = new OpSetLocal3;
	return ret;
}
OpDebugReg::OpDebugReg() {
	unknown = 0;
name = 0;
reg = 0;
line = 0;
}
OpDebugReg::~OpDebugReg() {
}
OpDebugReg* OpDebugReg::get( Reader *r, int end, Context *ctx ) {
	OpDebugReg* ret = new OpDebugReg;
	ret->parse( r, end, ctx );
	return ret;
}
OpDebugReg* OpDebugReg::getByName( const char *name ) {
	if( strcmp( name, "OpDebugReg" ) ) return NULL;
	OpDebugReg* ret = new OpDebugReg;
	return ret;
}
	// Constant Size Primitive
	unsigned char OpDebugReg::getunknown() {
		return unknown;
	}
	void OpDebugReg::setunknown( unsigned char v ) {
		unknown = v;
	}
	// Constant Size Primitive
	unsigned int OpDebugReg::getname() {
		return name;
	}
	void OpDebugReg::setname( unsigned int v ) {
		name = v;
	}
	// Constant Size Primitive
	unsigned int OpDebugReg::getreg() {
		return reg;
	}
	void OpDebugReg::setreg( unsigned int v ) {
		reg = v;
	}
	// Constant Size Primitive
	unsigned int OpDebugReg::getline() {
		return line;
	}
	void OpDebugReg::setline( unsigned int v ) {
		line = v;
	}
OpDebugLine::OpDebugLine() {
	line = 0;
}
OpDebugLine::~OpDebugLine() {
}
OpDebugLine* OpDebugLine::get( Reader *r, int end, Context *ctx ) {
	OpDebugLine* ret = new OpDebugLine;
	ret->parse( r, end, ctx );
	return ret;
}
OpDebugLine* OpDebugLine::getByName( const char *name ) {
	if( strcmp( name, "OpDebugLine" ) ) return NULL;
	OpDebugLine* ret = new OpDebugLine;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpDebugLine::getline() {
		return line;
	}
	void OpDebugLine::setline( unsigned int v ) {
		line = v;
	}
OpDebugFile::OpDebugFile() {
	file = 0;
}
OpDebugFile::~OpDebugFile() {
}
OpDebugFile* OpDebugFile::get( Reader *r, int end, Context *ctx ) {
	OpDebugFile* ret = new OpDebugFile;
	ret->parse( r, end, ctx );
	return ret;
}
OpDebugFile* OpDebugFile::getByName( const char *name ) {
	if( strcmp( name, "OpDebugFile" ) ) return NULL;
	OpDebugFile* ret = new OpDebugFile;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpDebugFile::getfile() {
		return file;
	}
	void OpDebugFile::setfile( unsigned int v ) {
		file = v;
	}
OpBkPtLine::OpBkPtLine() {
	line = 0;
}
OpBkPtLine::~OpBkPtLine() {
}
OpBkPtLine* OpBkPtLine::get( Reader *r, int end, Context *ctx ) {
	OpBkPtLine* ret = new OpBkPtLine;
	ret->parse( r, end, ctx );
	return ret;
}
OpBkPtLine* OpBkPtLine::getByName( const char *name ) {
	if( strcmp( name, "OpBkPtLine" ) ) return NULL;
	OpBkPtLine* ret = new OpBkPtLine;
	return ret;
}
	// Constant Size Primitive
	unsigned int OpBkPtLine::getline() {
		return line;
	}
	void OpBkPtLine::setline( unsigned int v ) {
		line = v;
	}
OpTimestamp::OpTimestamp() {
}
OpTimestamp::~OpTimestamp() {
}
OpTimestamp* OpTimestamp::get( Reader *r, int end, Context *ctx ) {
	OpTimestamp* ret = new OpTimestamp;
	ret->parse( r, end, ctx );
	return ret;
}
OpTimestamp* OpTimestamp::getByName( const char *name ) {
	if( strcmp( name, "OpTimestamp" ) ) return NULL;
	OpTimestamp* ret = new OpTimestamp;
	return ret;
}
// ------------ object lists
Tag *UnknownTagFactory() {
			return (Tag*)new UnknownTag;
		}
	Tag *EndFactory() {
			return (Tag*)new End;
		}
	Tag *ShowFrameFactory() {
			return (Tag*)new ShowFrame;
		}
	Tag *DefineShapeFactory() {
			return (Tag*)new DefineShape;
		}
	Tag *RemoveObjectFactory() {
			return (Tag*)new RemoveObject;
		}
	Tag *DefineBitsFactory() {
			return (Tag*)new DefineBits;
		}
	Tag *SetBackgroundColorFactory() {
			return (Tag*)new SetBackgroundColor;
		}
	Tag *DefineTextFactory() {
			return (Tag*)new DefineText;
		}
	Tag *DefineText2Factory() {
			return (Tag*)new DefineText2;
		}
	Tag *DoActionFactory() {
			return (Tag*)new DoAction;
		}
	Tag *DefineFontInfoFactory() {
			return (Tag*)new DefineFontInfo;
		}
	Tag *DefineSoundFactory() {
			return (Tag*)new DefineSound;
		}
	Tag *StartSoundFactory() {
			return (Tag*)new StartSound;
		}
	Tag *DefineShape2Factory() {
			return (Tag*)new DefineShape2;
		}
	Tag *DefineShape3Factory() {
			return (Tag*)new DefineShape3;
		}
	Tag *DefineShape4Factory() {
			return (Tag*)new DefineShape4;
		}
	Tag *DefineShape5Factory() {
			return (Tag*)new DefineShape5;
		}
	Tag *DefineMorphShapeFactory() {
			return (Tag*)new DefineMorphShape;
		}
	Tag *DefineFontInfo2Factory() {
			return (Tag*)new DefineFontInfo2;
		}
	Tag *SoundStreamHeadFactory() {
			return (Tag*)new SoundStreamHead;
		}
	Tag *DefineBitsLosslessFactory() {
			return (Tag*)new DefineBitsLossless;
		}
	Tag *DefineBitsJPEG2Factory() {
			return (Tag*)new DefineBitsJPEG2;
		}
	Tag *DefineBitsJPEG3Factory() {
			return (Tag*)new DefineBitsJPEG3;
		}
	Tag *DefineBitsLossless2Factory() {
			return (Tag*)new DefineBitsLossless2;
		}
	Tag *PlaceObject2Factory() {
			return (Tag*)new PlaceObject2;
		}
	Tag *RemoveObject2Factory() {
			return (Tag*)new RemoveObject2;
		}
	Tag *DefineEditTextFactory() {
			return (Tag*)new DefineEditText;
		}
	Tag *DefineSpriteFactory() {
			return (Tag*)new DefineSprite;
		}
	Tag *FrameLabelFactory() {
			return (Tag*)new FrameLabel;
		}
	Tag *SoundStreamHead2Factory() {
			return (Tag*)new SoundStreamHead2;
		}
	Tag *DefineFontFactory() {
			return (Tag*)new DefineFont;
		}
	Tag *DefineFont2Factory() {
			return (Tag*)new DefineFont2;
		}
	Tag *DefineFont3Factory() {
			return (Tag*)new DefineFont3;
		}
	Tag *DefineButtonFactory() {
			return (Tag*)new DefineButton;
		}
	Tag *DefineButton2Factory() {
			return (Tag*)new DefineButton2;
		}
	Tag *ExportFactory() {
			return (Tag*)new Export;
		}
	Tag *ImportFactory() {
			return (Tag*)new Import;
		}
	Tag *DoInitActionFactory() {
			return (Tag*)new DoInitAction;
		}
	Tag *SoundStreamBlockFactory() {
			return (Tag*)new SoundStreamBlock;
		}
	Tag *DefineVideoStreamFactory() {
			return (Tag*)new DefineVideoStream;
		}
	Tag *VideoFrameFactory() {
			return (Tag*)new VideoFrame;
		}
	Tag *ScriptLimitsFactory() {
			return (Tag*)new ScriptLimits;
		}
	Tag *SetTabIndexFactory() {
			return (Tag*)new SetTabIndex;
		}
	Tag *PlaceObject3Factory() {
			return (Tag*)new PlaceObject3;
		}
	Tag *ImportAssets2Factory() {
			return (Tag*)new ImportAssets2;
		}
	Tag *FileAttributesFactory() {
			return (Tag*)new FileAttributes;
		}
	Tag *DefineFontAlignZonesFactory() {
			return (Tag*)new DefineFontAlignZones;
		}
	Tag *CSMTextSettingsFactory() {
			return (Tag*)new CSMTextSettings;
		}
	Tag *MetadataFactory() {
			return (Tag*)new Metadata;
		}
	Tag *DefineScalingGridFactory() {
			return (Tag*)new DefineScalingGrid;
		}
	Tag *DoABCFactory() {
			return (Tag*)new DoABC;
		}
	Tag *DoABCDefineFactory() {
			return (Tag*)new DoABCDefine;
		}
	Tag *SymbolClassFactory() {
			return (Tag*)new SymbolClass;
		}
	Tag *DefineSceneAndFrameLabelDataFactory() {
			return (Tag*)new DefineSceneAndFrameLabelData;
		}
	Tag *DefineBinaryDataFactory() {
			return (Tag*)new DefineBinaryData;
		}
	Tag *DefineFontNameFactory() {
			return (Tag*)new DefineFontName;
		}
	template<> IdItem<Tag>::Description IdItem<Tag>::Registry[] = {
			{ -1, "UnknownTag", UnknownTagFactory },
			{ 0x00, "End", EndFactory },
			{ 0x01, "ShowFrame", ShowFrameFactory },
			{ 0x02, "DefineShape", DefineShapeFactory },
			{ 0x05, "RemoveObject", RemoveObjectFactory },
			{ 0x06, "DefineBits", DefineBitsFactory },
			{ 0x09, "SetBackgroundColor", SetBackgroundColorFactory },
			{ 0x0B, "DefineText", DefineTextFactory },
			{ 0x21, "DefineText2", DefineText2Factory },
			{ 0x0C, "DoAction", DoActionFactory },
			{ 0x0D, "DefineFontInfo", DefineFontInfoFactory },
			{ 0x0E, "DefineSound", DefineSoundFactory },
			{ 0x0F, "StartSound", StartSoundFactory },
			{ 0x16, "DefineShape2", DefineShape2Factory },
			{ 0x20, "DefineShape3", DefineShape3Factory },
			{ 0x43, "DefineShape4", DefineShape4Factory },
			{ 0x53, "DefineShape5", DefineShape5Factory },
			{ 0x2E, "DefineMorphShape", DefineMorphShapeFactory },
			{ 0x3E, "DefineFontInfo2", DefineFontInfo2Factory },
			{ 0x12, "SoundStreamHead", SoundStreamHeadFactory },
			{ 0x14, "DefineBitsLossless", DefineBitsLosslessFactory },
			{ 0x15, "DefineBitsJPEG2", DefineBitsJPEG2Factory },
			{ 0x23, "DefineBitsJPEG3", DefineBitsJPEG3Factory },
			{ 0x24, "DefineBitsLossless2", DefineBitsLossless2Factory },
			{ 0x1A, "PlaceObject2", PlaceObject2Factory },
			{ 0x1C, "RemoveObject2", RemoveObject2Factory },
			{ 0x25, "DefineEditText", DefineEditTextFactory },
			{ 0x27, "DefineSprite", DefineSpriteFactory },
			{ 0x2B, "FrameLabel", FrameLabelFactory },
			{ 0x2D, "SoundStreamHead2", SoundStreamHead2Factory },
			{ 0x0A, "DefineFont", DefineFontFactory },
			{ 0x30, "DefineFont2", DefineFont2Factory },
			{ 0x4B, "DefineFont3", DefineFont3Factory },
			{ 0x07, "DefineButton", DefineButtonFactory },
			{ 0x22, "DefineButton2", DefineButton2Factory },
			{ 0x38, "Export", ExportFactory },
			{ 0x39, "Import", ImportFactory },
			{ 0x3B, "DoInitAction", DoInitActionFactory },
			{ 0x13, "SoundStreamBlock", SoundStreamBlockFactory },
			{ 0x3C, "DefineVideoStream", DefineVideoStreamFactory },
			{ 0x3D, "VideoFrame", VideoFrameFactory },
			{ 0x41, "ScriptLimits", ScriptLimitsFactory },
			{ 0x42, "SetTabIndex", SetTabIndexFactory },
			{ 0x46, "PlaceObject3", PlaceObject3Factory },
			{ 0x47, "ImportAssets2", ImportAssets2Factory },
			{ 0x45, "FileAttributes", FileAttributesFactory },
			{ 0x49, "DefineFontAlignZones", DefineFontAlignZonesFactory },
			{ 0x4A, "CSMTextSettings", CSMTextSettingsFactory },
			{ 0x4D, "Metadata", MetadataFactory },
			{ 0x4E, "DefineScalingGrid", DefineScalingGridFactory },
			{ 0x48, "DoABC", DoABCFactory },
			{ 0x52, "DoABCDefine", DoABCDefineFactory },
			{ 0x4C, "SymbolClass", SymbolClassFactory },
			{ 0x56, "DefineSceneAndFrameLabelData", DefineSceneAndFrameLabelDataFactory },
			{ 0x57, "DefineBinaryData", DefineBinaryDataFactory },
			{ 0x58, "DefineFontName", DefineFontNameFactory },
		{ 0, NULL }
	};
	template<> int IdItem<Tag>::nRegistered = 56;
	template<> const char* IdItem<Tag>::itemName = "tag";
Action *UnknownActionFactory() {
			return (Action*)new UnknownAction;
		}
	Action *EndActionFactory() {
			return (Action*)new EndAction;
		}
	Action *NextFrameFactory() {
			return (Action*)new NextFrame;
		}
	Action *PreviousFrameFactory() {
			return (Action*)new PreviousFrame;
		}
	Action *PlayFactory() {
			return (Action*)new Play;
		}
	Action *StopFactory() {
			return (Action*)new Stop;
		}
	Action *ToggleQualityFactory() {
			return (Action*)new ToggleQuality;
		}
	Action *StopSoundFactory() {
			return (Action*)new StopSound;
		}
	Action *AddCastFactory() {
			return (Action*)new AddCast;
		}
	Action *SubstractFactory() {
			return (Action*)new Substract;
		}
	Action *MulitplyFactory() {
			return (Action*)new Mulitply;
		}
	Action *DivideFactory() {
			return (Action*)new Divide;
		}
	Action *EqualCastFactory() {
			return (Action*)new EqualCast;
		}
	Action *LessThanCastFactory() {
			return (Action*)new LessThanCast;
		}
	Action *LogicalANDFactory() {
			return (Action*)new LogicalAND;
		}
	Action *LogicalORFactory() {
			return (Action*)new LogicalOR;
		}
	Action *LogicalNOTFactory() {
			return (Action*)new LogicalNOT;
		}
	Action *StringEqualFactory() {
			return (Action*)new StringEqual;
		}
	Action *StringLengthFactory() {
			return (Action*)new StringLength;
		}
	Action *SubStringFactory() {
			return (Action*)new SubString;
		}
	Action *PopFactory() {
			return (Action*)new Pop;
		}
	Action *IntegralPartFactory() {
			return (Action*)new IntegralPart;
		}
	Action *GetVariableFactory() {
			return (Action*)new GetVariable;
		}
	Action *SetVariableFactory() {
			return (Action*)new SetVariable;
		}
	Action *SetTargetDynamicFactory() {
			return (Action*)new SetTargetDynamic;
		}
	Action *ConcatenateStringFactory() {
			return (Action*)new ConcatenateString;
		}
	Action *GetPropertyFactory() {
			return (Action*)new GetProperty;
		}
	Action *SetPropertyFactory() {
			return (Action*)new SetProperty;
		}
	Action *DuplicateSpriteFactory() {
			return (Action*)new DuplicateSprite;
		}
	Action *RemoveSpriteFactory() {
			return (Action*)new RemoveSprite;
		}
	Action *TraceFactory() {
			return (Action*)new Trace;
		}
	Action *StartDragFactory() {
			return (Action*)new StartDrag;
		}
	Action *StopDragFactory() {
			return (Action*)new StopDrag;
		}
	Action *StringLessThanFactory() {
			return (Action*)new StringLessThan;
		}
	Action *ThrowFactory() {
			return (Action*)new Throw;
		}
	Action *CastObjectFactory() {
			return (Action*)new CastObject;
		}
	Action *ImplementsFactory() {
			return (Action*)new Implements;
		}
	Action *RandomFactory() {
			return (Action*)new Random;
		}
	Action *MultibyteStringLengthFactory() {
			return (Action*)new MultibyteStringLength;
		}
	Action *ORDFactory() {
			return (Action*)new ORD;
		}
	Action *CHRFactory() {
			return (Action*)new CHR;
		}
	Action *GetTimerFactory() {
			return (Action*)new GetTimer;
		}
	Action *MultibyteSubStringFactory() {
			return (Action*)new MultibyteSubString;
		}
	Action *MultibyteORDFactory() {
			return (Action*)new MultibyteORD;
		}
	Action *MultibyteCHRFactory() {
			return (Action*)new MultibyteCHR;
		}
	Action *DeleteFactory() {
			return (Action*)new Delete;
		}
	Action *DeleteAllFactory() {
			return (Action*)new DeleteAll;
		}
	Action *SetLocalVariableFactory() {
			return (Action*)new SetLocalVariable;
		}
	Action *CallFunctionFactory() {
			return (Action*)new CallFunction;
		}
	Action *ReturnFactory() {
			return (Action*)new Return;
		}
	Action *ModuloFactory() {
			return (Action*)new Modulo;
		}
	Action *NewFactory() {
			return (Action*)new New;
		}
	Action *DeclareLocalVariableFactory() {
			return (Action*)new DeclareLocalVariable;
		}
	Action *DeclareArrayFactory() {
			return (Action*)new DeclareArray;
		}
	Action *DeclareObjectFactory() {
			return (Action*)new DeclareObject;
		}
	Action *TypeOfFactory() {
			return (Action*)new TypeOf;
		}
	Action *GetTargetFactory() {
			return (Action*)new GetTarget;
		}
	Action *EnumerateFactory() {
			return (Action*)new Enumerate;
		}
	Action *AddTypedFactory() {
			return (Action*)new AddTyped;
		}
	Action *LessThanTypedFactory() {
			return (Action*)new LessThanTyped;
		}
	Action *EqualTypedFactory() {
			return (Action*)new EqualTyped;
		}
	Action *DefineNumberFactory() {
			return (Action*)new DefineNumber;
		}
	Action *DefineStringFactory() {
			return (Action*)new DefineString;
		}
	Action *DuplicateFactory() {
			return (Action*)new Duplicate;
		}
	Action *SwapFactory() {
			return (Action*)new Swap;
		}
	Action *GetMemberFactory() {
			return (Action*)new GetMember;
		}
	Action *SetMemberFactory() {
			return (Action*)new SetMember;
		}
	Action *IncrementFactory() {
			return (Action*)new Increment;
		}
	Action *DecrementFactory() {
			return (Action*)new Decrement;
		}
	Action *CallMethodFactory() {
			return (Action*)new CallMethod;
		}
	Action *NewMethodFactory() {
			return (Action*)new NewMethod;
		}
	Action *InstanceOfFactory() {
			return (Action*)new InstanceOf;
		}
	Action *EnumerateObjectFactory() {
			return (Action*)new EnumerateObject;
		}
	Action *ANDFactory() {
			return (Action*)new AND;
		}
	Action *ORFactory() {
			return (Action*)new OR;
		}
	Action *XORFactory() {
			return (Action*)new XOR;
		}
	Action *ShiftLeftFactory() {
			return (Action*)new ShiftLeft;
		}
	Action *ShiftRightFactory() {
			return (Action*)new ShiftRight;
		}
	Action *ShiftRightUnsignedFactory() {
			return (Action*)new ShiftRightUnsigned;
		}
	Action *StrictEqualFactory() {
			return (Action*)new StrictEqual;
		}
	Action *GreaterThanTypedFactory() {
			return (Action*)new GreaterThanTyped;
		}
	Action *StringGreaterThanFactory() {
			return (Action*)new StringGreaterThan;
		}
	Action *ExtendsFactory() {
			return (Action*)new Extends;
		}
	Action *GotoFrameFactory() {
			return (Action*)new GotoFrame;
		}
	Action *GetURLFactory() {
			return (Action*)new GetURL;
		}
	Action *StoreRegisterFactory() {
			return (Action*)new StoreRegister;
		}
	Action *DictionaryFactory() {
			return (Action*)new Dictionary;
		}
	Action *WaitForFrameFactory() {
			return (Action*)new WaitForFrame;
		}
	Action *SetTargetFactory() {
			return (Action*)new SetTarget;
		}
	Action *GotoLabelFactory() {
			return (Action*)new GotoLabel;
		}
	Action *WaitForFrameDynamicFactory() {
			return (Action*)new WaitForFrameDynamic;
		}
	Action *DeclareFunction2Factory() {
			return (Action*)new DeclareFunction2;
		}
	Action *TryFactory() {
			return (Action*)new Try;
		}
	Action *WithFactory() {
			return (Action*)new With;
		}
	Action *PushDataFactory() {
			return (Action*)new PushData;
		}
	Action *GetURL2Factory() {
			return (Action*)new GetURL2;
		}
	Action *DeclareFunctionFactory() {
			return (Action*)new DeclareFunction;
		}
	Action *BranchAlwaysFactory() {
			return (Action*)new BranchAlways;
		}
	Action *BranchIfTrueFactory() {
			return (Action*)new BranchIfTrue;
		}
	Action *CallFrameFactory() {
			return (Action*)new CallFrame;
		}
	Action *GotoExpressionFactory() {
			return (Action*)new GotoExpression;
		}
	template<> IdItem<Action>::Description IdItem<Action>::Registry[] = {
			{ -1, "UnknownAction", UnknownActionFactory },
			{ 0x00, "EndAction", EndActionFactory },
			{ 0x04, "NextFrame", NextFrameFactory },
			{ 0x05, "PreviousFrame", PreviousFrameFactory },
			{ 0x06, "Play", PlayFactory },
			{ 0x07, "Stop", StopFactory },
			{ 0x08, "ToggleQuality", ToggleQualityFactory },
			{ 0x09, "StopSound", StopSoundFactory },
			{ 0x0A, "AddCast", AddCastFactory },
			{ 0x0B, "Substract", SubstractFactory },
			{ 0x0C, "Mulitply", MulitplyFactory },
			{ 0x0D, "Divide", DivideFactory },
			{ 0x0E, "EqualCast", EqualCastFactory },
			{ 0x0F, "LessThanCast", LessThanCastFactory },
			{ 0x10, "LogicalAND", LogicalANDFactory },
			{ 0x11, "LogicalOR", LogicalORFactory },
			{ 0x12, "LogicalNOT", LogicalNOTFactory },
			{ 0x13, "StringEqual", StringEqualFactory },
			{ 0x14, "StringLength", StringLengthFactory },
			{ 0x15, "SubString", SubStringFactory },
			{ 0x17, "Pop", PopFactory },
			{ 0x18, "IntegralPart", IntegralPartFactory },
			{ 0x1C, "GetVariable", GetVariableFactory },
			{ 0x1D, "SetVariable", SetVariableFactory },
			{ 0x20, "SetTargetDynamic", SetTargetDynamicFactory },
			{ 0x21, "ConcatenateString", ConcatenateStringFactory },
			{ 0x22, "GetProperty", GetPropertyFactory },
			{ 0x23, "SetProperty", SetPropertyFactory },
			{ 0x24, "DuplicateSprite", DuplicateSpriteFactory },
			{ 0x25, "RemoveSprite", RemoveSpriteFactory },
			{ 0x26, "Trace", TraceFactory },
			{ 0x27, "StartDrag", StartDragFactory },
			{ 0x28, "StopDrag", StopDragFactory },
			{ 0x29, "StringLessThan", StringLessThanFactory },
			{ 0x2A, "Throw", ThrowFactory },
			{ 0x2B, "CastObject", CastObjectFactory },
			{ 0x2C, "Implements", ImplementsFactory },
			{ 0x30, "Random", RandomFactory },
			{ 0x31, "MultibyteStringLength", MultibyteStringLengthFactory },
			{ 0x32, "ORD", ORDFactory },
			{ 0x33, "CHR", CHRFactory },
			{ 0x34, "GetTimer", GetTimerFactory },
			{ 0x35, "MultibyteSubString", MultibyteSubStringFactory },
			{ 0x36, "MultibyteORD", MultibyteORDFactory },
			{ 0x37, "MultibyteCHR", MultibyteCHRFactory },
			{ 0x3A, "Delete", DeleteFactory },
			{ 0x3B, "DeleteAll", DeleteAllFactory },
			{ 0x3C, "SetLocalVariable", SetLocalVariableFactory },
			{ 0x3D, "CallFunction", CallFunctionFactory },
			{ 0x3E, "Return", ReturnFactory },
			{ 0x3F, "Modulo", ModuloFactory },
			{ 0x40, "New", NewFactory },
			{ 0x41, "DeclareLocalVariable", DeclareLocalVariableFactory },
			{ 0x42, "DeclareArray", DeclareArrayFactory },
			{ 0x43, "DeclareObject", DeclareObjectFactory },
			{ 0x44, "TypeOf", TypeOfFactory },
			{ 0x45, "GetTarget", GetTargetFactory },
			{ 0x46, "Enumerate", EnumerateFactory },
			{ 0x47, "AddTyped", AddTypedFactory },
			{ 0x48, "LessThanTyped", LessThanTypedFactory },
			{ 0x49, "EqualTyped", EqualTypedFactory },
			{ 0x4A, "DefineNumber", DefineNumberFactory },
			{ 0x4B, "DefineString", DefineStringFactory },
			{ 0x4C, "Duplicate", DuplicateFactory },
			{ 0x4D, "Swap", SwapFactory },
			{ 0x4E, "GetMember", GetMemberFactory },
			{ 0x4F, "SetMember", SetMemberFactory },
			{ 0x50, "Increment", IncrementFactory },
			{ 0x51, "Decrement", DecrementFactory },
			{ 0x52, "CallMethod", CallMethodFactory },
			{ 0x53, "NewMethod", NewMethodFactory },
			{ 0x54, "InstanceOf", InstanceOfFactory },
			{ 0x55, "EnumerateObject", EnumerateObjectFactory },
			{ 0x60, "AND", ANDFactory },
			{ 0x61, "OR", ORFactory },
			{ 0x62, "XOR", XORFactory },
			{ 0x63, "ShiftLeft", ShiftLeftFactory },
			{ 0x64, "ShiftRight", ShiftRightFactory },
			{ 0x65, "ShiftRightUnsigned", ShiftRightUnsignedFactory },
			{ 0x66, "StrictEqual", StrictEqualFactory },
			{ 0x67, "GreaterThanTyped", GreaterThanTypedFactory },
			{ 0x68, "StringGreaterThan", StringGreaterThanFactory },
			{ 0x69, "Extends", ExtendsFactory },
			{ 0x81, "GotoFrame", GotoFrameFactory },
			{ 0x83, "GetURL", GetURLFactory },
			{ 0x87, "StoreRegister", StoreRegisterFactory },
			{ 0x88, "Dictionary", DictionaryFactory },
			{ 0x8A, "WaitForFrame", WaitForFrameFactory },
			{ 0x8B, "SetTarget", SetTargetFactory },
			{ 0x8C, "GotoLabel", GotoLabelFactory },
			{ 0x8D, "WaitForFrameDynamic", WaitForFrameDynamicFactory },
			{ 0x8E, "DeclareFunction2", DeclareFunction2Factory },
			{ 0x8F, "Try", TryFactory },
			{ 0x94, "With", WithFactory },
			{ 0x96, "PushData", PushDataFactory },
			{ 0x9A, "GetURL2", GetURL2Factory },
			{ 0x9B, "DeclareFunction", DeclareFunctionFactory },
			{ 0x99, "BranchAlways", BranchAlwaysFactory },
			{ 0x9D, "BranchIfTrue", BranchIfTrueFactory },
			{ 0x9E, "CallFrame", CallFrameFactory },
			{ 0x9F, "GotoExpression", GotoExpressionFactory },
		{ 0, NULL }
	};
	template<> int IdItem<Action>::nRegistered = 101;
	template<> const char* IdItem<Action>::itemName = "action";
Filter *UnknownFilterFactory() {
			return (Filter*)new UnknownFilter;
		}
	Filter *DropShadowFactory() {
			return (Filter*)new DropShadow;
		}
	Filter *BlurFactory() {
			return (Filter*)new Blur;
		}
	Filter *GlowFactory() {
			return (Filter*)new Glow;
		}
	Filter *BevelFactory() {
			return (Filter*)new Bevel;
		}
	Filter *GradientGlowFactory() {
			return (Filter*)new GradientGlow;
		}
	Filter *ConvolutionFactory() {
			return (Filter*)new Convolution;
		}
	Filter *ColorMatrixFactory() {
			return (Filter*)new ColorMatrix;
		}
	Filter *GradientBevelFactory() {
			return (Filter*)new GradientBevel;
		}
	template<> IdItem<Filter>::Description IdItem<Filter>::Registry[] = {
			{ -1, "UnknownFilter", UnknownFilterFactory },
			{ 0x00, "DropShadow", DropShadowFactory },
			{ 0x01, "Blur", BlurFactory },
			{ 0x02, "Glow", GlowFactory },
			{ 0x03, "Bevel", BevelFactory },
			{ 0x04, "GradientGlow", GradientGlowFactory },
			{ 0x05, "Convolution", ConvolutionFactory },
			{ 0x06, "ColorMatrix", ColorMatrixFactory },
			{ 0x07, "GradientBevel", GradientBevelFactory },
		{ 0, NULL }
	};
	template<> int IdItem<Filter>::nRegistered = 9;
	template<> const char* IdItem<Filter>::itemName = "filter";
Style *SolidFactory() {
			return (Style*)new Solid;
		}
	Style *LinearGradientFactory() {
			return (Style*)new LinearGradient;
		}
	Style *RadialGradientFactory() {
			return (Style*)new RadialGradient;
		}
	Style *ShiftedRadialGradientFactory() {
			return (Style*)new ShiftedRadialGradient;
		}
	Style *TiledBitmapFactory() {
			return (Style*)new TiledBitmap;
		}
	Style *ClippedBitmapFactory() {
			return (Style*)new ClippedBitmap;
		}
	Style *TiledBitmap2Factory() {
			return (Style*)new TiledBitmap2;
		}
	Style *ClippedBitmap2Factory() {
			return (Style*)new ClippedBitmap2;
		}
	template<> IdItem<Style>::Description IdItem<Style>::Registry[] = {
			{ 0x00, "Solid", SolidFactory },
			{ 0x10, "LinearGradient", LinearGradientFactory },
			{ 0x12, "RadialGradient", RadialGradientFactory },
			{ 0x13, "ShiftedRadialGradient", ShiftedRadialGradientFactory },
			{ 0x40, "TiledBitmap", TiledBitmapFactory },
			{ 0x41, "ClippedBitmap", ClippedBitmapFactory },
			{ 0x42, "TiledBitmap2", TiledBitmap2Factory },
			{ 0x43, "ClippedBitmap2", ClippedBitmap2Factory },
		{ 0, NULL }
	};
	template<> int IdItem<Style>::nRegistered = 8;
	template<> const char* IdItem<Style>::itemName = "fill style";
StackItem *StackStringFactory() {
			return (StackItem*)new StackString;
		}
	StackItem *StackFloatFactory() {
			return (StackItem*)new StackFloat;
		}
	StackItem *StackNullFactory() {
			return (StackItem*)new StackNull;
		}
	StackItem *StackUndefinedFactory() {
			return (StackItem*)new StackUndefined;
		}
	StackItem *StackRegisterFactory() {
			return (StackItem*)new StackRegister;
		}
	StackItem *StackBooleanFactory() {
			return (StackItem*)new StackBoolean;
		}
	StackItem *StackDoubleFactory() {
			return (StackItem*)new StackDouble;
		}
	StackItem *StackIntegerFactory() {
			return (StackItem*)new StackInteger;
		}
	StackItem *StackDictionaryLookupFactory() {
			return (StackItem*)new StackDictionaryLookup;
		}
	StackItem *StackLargeDictionaryLookupFactory() {
			return (StackItem*)new StackLargeDictionaryLookup;
		}
	template<> IdItem<StackItem>::Description IdItem<StackItem>::Registry[] = {
			{ 0x00, "StackString", StackStringFactory },
			{ 0x01, "StackFloat", StackFloatFactory },
			{ 0x02, "StackNull", StackNullFactory },
			{ 0x03, "StackUndefined", StackUndefinedFactory },
			{ 0x04, "StackRegister", StackRegisterFactory },
			{ 0x05, "StackBoolean", StackBooleanFactory },
			{ 0x06, "StackDouble", StackDoubleFactory },
			{ 0x07, "StackInteger", StackIntegerFactory },
			{ 0x08, "StackDictionaryLookup", StackDictionaryLookupFactory },
			{ 0x09, "StackLargeDictionaryLookup", StackLargeDictionaryLookupFactory },
		{ 0, NULL }
	};
	template<> int IdItem<StackItem>::nRegistered = 10;
	template<> const char* IdItem<StackItem>::itemName = "stack item";
int StackString::id = 0x00;
int StackFloat::id = 0x01;
int StackNull::id = 0x02;
int StackUndefined::id = 0x03;
int StackRegister::id = 0x04;
int StackBoolean::id = 0x05;
int StackDouble::id = 0x06;
int StackInteger::id = 0x07;
int StackDictionaryLookup::id = 0x08;
int StackLargeDictionaryLookup::id = 0x09;
NamespaceConstant *PrivateNamespaceFactory() {
			return (NamespaceConstant*)new PrivateNamespace;
		}
	NamespaceConstant *NamespaceFactory() {
			return (NamespaceConstant*)new Namespace;
		}
	NamespaceConstant *PackageNamespaceFactory() {
			return (NamespaceConstant*)new PackageNamespace;
		}
	NamespaceConstant *PackageInternalNamespaceFactory() {
			return (NamespaceConstant*)new PackageInternalNamespace;
		}
	NamespaceConstant *ProtectedNamespaceFactory() {
			return (NamespaceConstant*)new ProtectedNamespace;
		}
	NamespaceConstant *ExplicitNamespaceFactory() {
			return (NamespaceConstant*)new ExplicitNamespace;
		}
	NamespaceConstant *MultinameLNamespaceFactory() {
			return (NamespaceConstant*)new MultinameLNamespace;
		}
	template<> IdItem<NamespaceConstant>::Description IdItem<NamespaceConstant>::Registry[] = {
			{ 5, "PrivateNamespace", PrivateNamespaceFactory },
			{ 8, "Namespace", NamespaceFactory },
			{ 22, "PackageNamespace", PackageNamespaceFactory },
			{ 23, "PackageInternalNamespace", PackageInternalNamespaceFactory },
			{ 24, "ProtectedNamespace", ProtectedNamespaceFactory },
			{ 25, "ExplicitNamespace", ExplicitNamespaceFactory },
			{ 26, "MultinameLNamespace", MultinameLNamespaceFactory },
		{ 0, NULL }
	};
	template<> int IdItem<NamespaceConstant>::nRegistered = 7;
	template<> const char* IdItem<NamespaceConstant>::itemName = "namespace constant";
MultinameConstant *QNameFactory() {
			return (MultinameConstant*)new QName;
		}
	MultinameConstant *QNameAFactory() {
			return (MultinameConstant*)new QNameA;
		}
	MultinameConstant *MultinameFactory() {
			return (MultinameConstant*)new Multiname;
		}
	MultinameConstant *MultinameAFactory() {
			return (MultinameConstant*)new MultinameA;
		}
	MultinameConstant *RTQNameFactory() {
			return (MultinameConstant*)new RTQName;
		}
	MultinameConstant *RTQNameAFactory() {
			return (MultinameConstant*)new RTQNameA;
		}
	MultinameConstant *MultinameLFactory() {
			return (MultinameConstant*)new MultinameL;
		}
	MultinameConstant *RTQNameLFactory() {
			return (MultinameConstant*)new RTQNameL;
		}
	MultinameConstant *RTQNameLAFactory() {
			return (MultinameConstant*)new RTQNameLA;
		}
	template<> IdItem<MultinameConstant>::Description IdItem<MultinameConstant>::Registry[] = {
			{ 7, "QName", QNameFactory },
			{ 13, "QNameA", QNameAFactory },
			{ 9, "Multiname", MultinameFactory },
			{ 14, "MultinameA", MultinameAFactory },
			{ 15, "RTQName", RTQNameFactory },
			{ 16, "RTQNameA", RTQNameAFactory },
			{ 27, "MultinameL", MultinameLFactory },
			{ 17, "RTQNameL", RTQNameLFactory },
			{ 18, "RTQNameLA", RTQNameLAFactory },
		{ 0, NULL }
	};
	template<> int IdItem<MultinameConstant>::nRegistered = 9;
	template<> const char* IdItem<MultinameConstant>::itemName = "multiname constant";
Trait *SlotFactory() {
			return (Trait*)new Slot;
		}
	Trait *ConstFactory() {
			return (Trait*)new Const;
		}
	Trait *MethodFactory() {
			return (Trait*)new Method;
		}
	Trait *GetterFactory() {
			return (Trait*)new Getter;
		}
	Trait *SetterFactory() {
			return (Trait*)new Setter;
		}
	Trait *ClassFactory() {
			return (Trait*)new Class;
		}
	Trait *FunctionFactory() {
			return (Trait*)new Function;
		}
	template<> IdItem<Trait>::Description IdItem<Trait>::Registry[] = {
			{ 0, "Slot", SlotFactory },
			{ 6, "Const", ConstFactory },
			{ 1, "Method", MethodFactory },
			{ 2, "Getter", GetterFactory },
			{ 3, "Setter", SetterFactory },
			{ 4, "Class", ClassFactory },
			{ 5, "Function", FunctionFactory },
		{ 0, NULL }
	};
	template<> int IdItem<Trait>::nRegistered = 7;
	template<> const char* IdItem<Trait>::itemName = "trait";
OpCode *OpBkPtFactory() {
			return (OpCode*)new OpBkPt;
		}
	OpCode *OpNopFactory() {
			return (OpCode*)new OpNop;
		}
	OpCode *OpThrowFactory() {
			return (OpCode*)new OpThrow;
		}
	OpCode *OpGetSuperFactory() {
			return (OpCode*)new OpGetSuper;
		}
	OpCode *OpSetSuperFactory() {
			return (OpCode*)new OpSetSuper;
		}
	OpCode *OpDXNsFactory() {
			return (OpCode*)new OpDXNs;
		}
	OpCode *OpDXNsLateFactory() {
			return (OpCode*)new OpDXNsLate;
		}
	OpCode *OpKillFactory() {
			return (OpCode*)new OpKill;
		}
	OpCode *OpLabelFactory() {
			return (OpCode*)new OpLabel;
		}
	OpCode *OpIfNltFactory() {
			return (OpCode*)new OpIfNlt;
		}
	OpCode *OpIfNleFactory() {
			return (OpCode*)new OpIfNle;
		}
	OpCode *OpIfNgtFactory() {
			return (OpCode*)new OpIfNgt;
		}
	OpCode *OpIfNgeFactory() {
			return (OpCode*)new OpIfNge;
		}
	OpCode *OpJumpFactory() {
			return (OpCode*)new OpJump;
		}
	OpCode *OpIfTrueFactory() {
			return (OpCode*)new OpIfTrue;
		}
	OpCode *OpIfFalseFactory() {
			return (OpCode*)new OpIfFalse;
		}
	OpCode *OpIfEqFactory() {
			return (OpCode*)new OpIfEq;
		}
	OpCode *OpIfNeFactory() {
			return (OpCode*)new OpIfNe;
		}
	OpCode *OpIfLtFactory() {
			return (OpCode*)new OpIfLt;
		}
	OpCode *OpIfLeFactory() {
			return (OpCode*)new OpIfLe;
		}
	OpCode *OpIfGtFactory() {
			return (OpCode*)new OpIfGt;
		}
	OpCode *OpIfGeFactory() {
			return (OpCode*)new OpIfGe;
		}
	OpCode *OpIfStrictEqFactory() {
			return (OpCode*)new OpIfStrictEq;
		}
	OpCode *OpIfStrictNeFactory() {
			return (OpCode*)new OpIfStrictNe;
		}
	OpCode *OpLookupSwitchFactory() {
			return (OpCode*)new OpLookupSwitch;
		}
	OpCode *OpPushWithFactory() {
			return (OpCode*)new OpPushWith;
		}
	OpCode *OpPopScopeFactory() {
			return (OpCode*)new OpPopScope;
		}
	OpCode *OpNextNameFactory() {
			return (OpCode*)new OpNextName;
		}
	OpCode *OpHasNextFactory() {
			return (OpCode*)new OpHasNext;
		}
	OpCode *OpPushNullFactory() {
			return (OpCode*)new OpPushNull;
		}
	OpCode *OpPushUndefinedFactory() {
			return (OpCode*)new OpPushUndefined;
		}
	OpCode *OpNextValueFactory() {
			return (OpCode*)new OpNextValue;
		}
	OpCode *OpPushByteFactory() {
			return (OpCode*)new OpPushByte;
		}
	OpCode *OpPushShortFactory() {
			return (OpCode*)new OpPushShort;
		}
	OpCode *OpPushTrueFactory() {
			return (OpCode*)new OpPushTrue;
		}
	OpCode *OpPushFalseFactory() {
			return (OpCode*)new OpPushFalse;
		}
	OpCode *OpPushNaNFactory() {
			return (OpCode*)new OpPushNaN;
		}
	OpCode *OpPopFactory() {
			return (OpCode*)new OpPop;
		}
	OpCode *OpDupFactory() {
			return (OpCode*)new OpDup;
		}
	OpCode *OpSwapFactory() {
			return (OpCode*)new OpSwap;
		}
	OpCode *OpPushStringFactory() {
			return (OpCode*)new OpPushString;
		}
	OpCode *OpPushIntFactory() {
			return (OpCode*)new OpPushInt;
		}
	OpCode *OpPushUIntFactory() {
			return (OpCode*)new OpPushUInt;
		}
	OpCode *OpPushDoubleFactory() {
			return (OpCode*)new OpPushDouble;
		}
	OpCode *OpPushScopeFactory() {
			return (OpCode*)new OpPushScope;
		}
	OpCode *OpPushNamespaceFactory() {
			return (OpCode*)new OpPushNamespace;
		}
	OpCode *OpHasNext2Factory() {
			return (OpCode*)new OpHasNext2;
		}
	OpCode *OpNewFunctionFactory() {
			return (OpCode*)new OpNewFunction;
		}
	OpCode *OpCallFactory() {
			return (OpCode*)new OpCall;
		}
	OpCode *OpConstructFactory() {
			return (OpCode*)new OpConstruct;
		}
	OpCode *OpCallMethodFactory() {
			return (OpCode*)new OpCallMethod;
		}
	OpCode *OpCallStaticFactory() {
			return (OpCode*)new OpCallStatic;
		}
	OpCode *OpCallSuperFactory() {
			return (OpCode*)new OpCallSuper;
		}
	OpCode *OpCallPropertyFactory() {
			return (OpCode*)new OpCallProperty;
		}
	OpCode *OpReturnVoidFactory() {
			return (OpCode*)new OpReturnVoid;
		}
	OpCode *OpReturnValueFactory() {
			return (OpCode*)new OpReturnValue;
		}
	OpCode *OpConstructSuperFactory() {
			return (OpCode*)new OpConstructSuper;
		}
	OpCode *OpConstructPropFactory() {
			return (OpCode*)new OpConstructProp;
		}
	OpCode *OpCallPropLexFactory() {
			return (OpCode*)new OpCallPropLex;
		}
	OpCode *OpCallSuperVoidFactory() {
			return (OpCode*)new OpCallSuperVoid;
		}
	OpCode *OpCallPropVoidFactory() {
			return (OpCode*)new OpCallPropVoid;
		}
	OpCode *OpNewObjectFactory() {
			return (OpCode*)new OpNewObject;
		}
	OpCode *OpNewArrayFactory() {
			return (OpCode*)new OpNewArray;
		}
	OpCode *OpNewActivationFactory() {
			return (OpCode*)new OpNewActivation;
		}
	OpCode *OpNewClassFactory() {
			return (OpCode*)new OpNewClass;
		}
	OpCode *OpGetDescendantsFactory() {
			return (OpCode*)new OpGetDescendants;
		}
	OpCode *OpNewCatchFactory() {
			return (OpCode*)new OpNewCatch;
		}
	OpCode *OpFindPropStrictFactory() {
			return (OpCode*)new OpFindPropStrict;
		}
	OpCode *OpFindPropertyFactory() {
			return (OpCode*)new OpFindProperty;
		}
	OpCode *OpFindDefFactory() {
			return (OpCode*)new OpFindDef;
		}
	OpCode *OpGetLexFactory() {
			return (OpCode*)new OpGetLex;
		}
	OpCode *OpSetPropertyFactory() {
			return (OpCode*)new OpSetProperty;
		}
	OpCode *OpGetLocalFactory() {
			return (OpCode*)new OpGetLocal;
		}
	OpCode *OpSetLocalFactory() {
			return (OpCode*)new OpSetLocal;
		}
	OpCode *OpGetGlobalScopeFactory() {
			return (OpCode*)new OpGetGlobalScope;
		}
	OpCode *OpGetScopeObjectFactory() {
			return (OpCode*)new OpGetScopeObject;
		}
	OpCode *OpGetPropertyFactory() {
			return (OpCode*)new OpGetProperty;
		}
	OpCode *OpInitPropertyFactory() {
			return (OpCode*)new OpInitProperty;
		}
	OpCode *OpDeletePropertyFactory() {
			return (OpCode*)new OpDeleteProperty;
		}
	OpCode *OpGetSlotFactory() {
			return (OpCode*)new OpGetSlot;
		}
	OpCode *OpSetSlotFactory() {
			return (OpCode*)new OpSetSlot;
		}
	OpCode *OpGetGlobalSlotFactory() {
			return (OpCode*)new OpGetGlobalSlot;
		}
	OpCode *OpSetGlobalSlotFactory() {
			return (OpCode*)new OpSetGlobalSlot;
		}
	OpCode *OpConvertSFactory() {
			return (OpCode*)new OpConvertS;
		}
	OpCode *OpEscXelemFactory() {
			return (OpCode*)new OpEscXelem;
		}
	OpCode *OpEscXattrFactory() {
			return (OpCode*)new OpEscXattr;
		}
	OpCode *OpConvertIFactory() {
			return (OpCode*)new OpConvertI;
		}
	OpCode *OpConvertUFactory() {
			return (OpCode*)new OpConvertU;
		}
	OpCode *OpConvertDFactory() {
			return (OpCode*)new OpConvertD;
		}
	OpCode *OpConvertBFactory() {
			return (OpCode*)new OpConvertB;
		}
	OpCode *OpConvertOFactory() {
			return (OpCode*)new OpConvertO;
		}
	OpCode *OpCheckFilterFactory() {
			return (OpCode*)new OpCheckFilter;
		}
	OpCode *OpCoerceFactory() {
			return (OpCode*)new OpCoerce;
		}
	OpCode *OpCoerceBFactory() {
			return (OpCode*)new OpCoerceB;
		}
	OpCode *OpCoerceAFactory() {
			return (OpCode*)new OpCoerceA;
		}
	OpCode *OpCoerceIFactory() {
			return (OpCode*)new OpCoerceI;
		}
	OpCode *OpCoerceDFactory() {
			return (OpCode*)new OpCoerceD;
		}
	OpCode *OpCoerceSFactory() {
			return (OpCode*)new OpCoerceS;
		}
	OpCode *OpAsTypeFactory() {
			return (OpCode*)new OpAsType;
		}
	OpCode *OpAsTypeLateFactory() {
			return (OpCode*)new OpAsTypeLate;
		}
	OpCode *OpCoerceUFactory() {
			return (OpCode*)new OpCoerceU;
		}
	OpCode *OpCoerceOFactory() {
			return (OpCode*)new OpCoerceO;
		}
	OpCode *OpNegateFactory() {
			return (OpCode*)new OpNegate;
		}
	OpCode *OpIncrementFactory() {
			return (OpCode*)new OpIncrement;
		}
	OpCode *OpIncLocalFactory() {
			return (OpCode*)new OpIncLocal;
		}
	OpCode *OpDecrementFactory() {
			return (OpCode*)new OpDecrement;
		}
	OpCode *OpDecLocalFactory() {
			return (OpCode*)new OpDecLocal;
		}
	OpCode *OpTypeOfFactory() {
			return (OpCode*)new OpTypeOf;
		}
	OpCode *OpNotFactory() {
			return (OpCode*)new OpNot;
		}
	OpCode *OpBitNotFactory() {
			return (OpCode*)new OpBitNot;
		}
	OpCode *OpAddFactory() {
			return (OpCode*)new OpAdd;
		}
	OpCode *OpSubtractFactory() {
			return (OpCode*)new OpSubtract;
		}
	OpCode *OpMultiplyFactory() {
			return (OpCode*)new OpMultiply;
		}
	OpCode *OpDivideFactory() {
			return (OpCode*)new OpDivide;
		}
	OpCode *OpModuloFactory() {
			return (OpCode*)new OpModulo;
		}
	OpCode *OpLShiftFactory() {
			return (OpCode*)new OpLShift;
		}
	OpCode *OpRShiftFactory() {
			return (OpCode*)new OpRShift;
		}
	OpCode *OpURShiftFactory() {
			return (OpCode*)new OpURShift;
		}
	OpCode *OpBitAndFactory() {
			return (OpCode*)new OpBitAnd;
		}
	OpCode *OpBitOrFactory() {
			return (OpCode*)new OpBitOr;
		}
	OpCode *OpBitXorFactory() {
			return (OpCode*)new OpBitXor;
		}
	OpCode *OpEqualsFactory() {
			return (OpCode*)new OpEquals;
		}
	OpCode *OpStrictEqualsFactory() {
			return (OpCode*)new OpStrictEquals;
		}
	OpCode *OpLessThanFactory() {
			return (OpCode*)new OpLessThan;
		}
	OpCode *OpLessEqualsFactory() {
			return (OpCode*)new OpLessEquals;
		}
	OpCode *OpGreaterThanFactory() {
			return (OpCode*)new OpGreaterThan;
		}
	OpCode *OpGreaterEqualsFactory() {
			return (OpCode*)new OpGreaterEquals;
		}
	OpCode *OpInstanceOfFactory() {
			return (OpCode*)new OpInstanceOf;
		}
	OpCode *OpIsTypeFactory() {
			return (OpCode*)new OpIsType;
		}
	OpCode *OpIsTypeLateFactory() {
			return (OpCode*)new OpIsTypeLate;
		}
	OpCode *OpInFactory() {
			return (OpCode*)new OpIn;
		}
	OpCode *OpIncrementIFactory() {
			return (OpCode*)new OpIncrementI;
		}
	OpCode *OpDecrementIFactory() {
			return (OpCode*)new OpDecrementI;
		}
	OpCode *OpIncLocalIFactory() {
			return (OpCode*)new OpIncLocalI;
		}
	OpCode *OpDecLocalIFactory() {
			return (OpCode*)new OpDecLocalI;
		}
	OpCode *OpNegateIFactory() {
			return (OpCode*)new OpNegateI;
		}
	OpCode *OpAddIFactory() {
			return (OpCode*)new OpAddI;
		}
	OpCode *OpSubtractIFactory() {
			return (OpCode*)new OpSubtractI;
		}
	OpCode *OpMultiplyIFactory() {
			return (OpCode*)new OpMultiplyI;
		}
	OpCode *OpGetLocal0Factory() {
			return (OpCode*)new OpGetLocal0;
		}
	OpCode *OpGetLocal1Factory() {
			return (OpCode*)new OpGetLocal1;
		}
	OpCode *OpGetLocal2Factory() {
			return (OpCode*)new OpGetLocal2;
		}
	OpCode *OpGetLocal3Factory() {
			return (OpCode*)new OpGetLocal3;
		}
	OpCode *OpSetLocal0Factory() {
			return (OpCode*)new OpSetLocal0;
		}
	OpCode *OpSetLocal1Factory() {
			return (OpCode*)new OpSetLocal1;
		}
	OpCode *OpSetLocal2Factory() {
			return (OpCode*)new OpSetLocal2;
		}
	OpCode *OpSetLocal3Factory() {
			return (OpCode*)new OpSetLocal3;
		}
	OpCode *OpDebugRegFactory() {
			return (OpCode*)new OpDebugReg;
		}
	OpCode *OpDebugLineFactory() {
			return (OpCode*)new OpDebugLine;
		}
	OpCode *OpDebugFileFactory() {
			return (OpCode*)new OpDebugFile;
		}
	OpCode *OpBkPtLineFactory() {
			return (OpCode*)new OpBkPtLine;
		}
	OpCode *OpTimestampFactory() {
			return (OpCode*)new OpTimestamp;
		}
	template<> IdItem<OpCode>::Description IdItem<OpCode>::Registry[] = {
			{ 0x01, "OpBkPt", OpBkPtFactory },
			{ 0x02, "OpNop", OpNopFactory },
			{ 0x03, "OpThrow", OpThrowFactory },
			{ 0x04, "OpGetSuper", OpGetSuperFactory },
			{ 0x05, "OpSetSuper", OpSetSuperFactory },
			{ 0x06, "OpDXNs", OpDXNsFactory },
			{ 0x07, "OpDXNsLate", OpDXNsLateFactory },
			{ 0x08, "OpKill", OpKillFactory },
			{ 0x09, "OpLabel", OpLabelFactory },
			{ 0x0C, "OpIfNlt", OpIfNltFactory },
			{ 0x0D, "OpIfNle", OpIfNleFactory },
			{ 0x0E, "OpIfNgt", OpIfNgtFactory },
			{ 0x0F, "OpIfNge", OpIfNgeFactory },
			{ 0x10, "OpJump", OpJumpFactory },
			{ 0x11, "OpIfTrue", OpIfTrueFactory },
			{ 0x12, "OpIfFalse", OpIfFalseFactory },
			{ 0x13, "OpIfEq", OpIfEqFactory },
			{ 0x14, "OpIfNe", OpIfNeFactory },
			{ 0x15, "OpIfLt", OpIfLtFactory },
			{ 0x16, "OpIfLe", OpIfLeFactory },
			{ 0x17, "OpIfGt", OpIfGtFactory },
			{ 0x18, "OpIfGe", OpIfGeFactory },
			{ 0x19, "OpIfStrictEq", OpIfStrictEqFactory },
			{ 0x1A, "OpIfStrictNe", OpIfStrictNeFactory },
			{ 0x1B, "OpLookupSwitch", OpLookupSwitchFactory },
			{ 0x1C, "OpPushWith", OpPushWithFactory },
			{ 0x1D, "OpPopScope", OpPopScopeFactory },
			{ 0x1E, "OpNextName", OpNextNameFactory },
			{ 0x1F, "OpHasNext", OpHasNextFactory },
			{ 0x20, "OpPushNull", OpPushNullFactory },
			{ 0x21, "OpPushUndefined", OpPushUndefinedFactory },
			{ 0x23, "OpNextValue", OpNextValueFactory },
			{ 0x24, "OpPushByte", OpPushByteFactory },
			{ 0x25, "OpPushShort", OpPushShortFactory },
			{ 0x26, "OpPushTrue", OpPushTrueFactory },
			{ 0x27, "OpPushFalse", OpPushFalseFactory },
			{ 0x28, "OpPushNaN", OpPushNaNFactory },
			{ 0x29, "OpPop", OpPopFactory },
			{ 0x2A, "OpDup", OpDupFactory },
			{ 0x2B, "OpSwap", OpSwapFactory },
			{ 0x2C, "OpPushString", OpPushStringFactory },
			{ 0x2D, "OpPushInt", OpPushIntFactory },
			{ 0x2E, "OpPushUInt", OpPushUIntFactory },
			{ 0x2F, "OpPushDouble", OpPushDoubleFactory },
			{ 0x30, "OpPushScope", OpPushScopeFactory },
			{ 0x31, "OpPushNamespace", OpPushNamespaceFactory },
			{ 0x32, "OpHasNext2", OpHasNext2Factory },
			{ 0x40, "OpNewFunction", OpNewFunctionFactory },
			{ 0x41, "OpCall", OpCallFactory },
			{ 0x42, "OpConstruct", OpConstructFactory },
			{ 0x43, "OpCallMethod", OpCallMethodFactory },
			{ 0x44, "OpCallStatic", OpCallStaticFactory },
			{ 0x45, "OpCallSuper", OpCallSuperFactory },
			{ 0x46, "OpCallProperty", OpCallPropertyFactory },
			{ 0x47, "OpReturnVoid", OpReturnVoidFactory },
			{ 0x48, "OpReturnValue", OpReturnValueFactory },
			{ 0x49, "OpConstructSuper", OpConstructSuperFactory },
			{ 0x4A, "OpConstructProp", OpConstructPropFactory },
			{ 0x4C, "OpCallPropLex", OpCallPropLexFactory },
			{ 0x4E, "OpCallSuperVoid", OpCallSuperVoidFactory },
			{ 0x4F, "OpCallPropVoid", OpCallPropVoidFactory },
			{ 0x55, "OpNewObject", OpNewObjectFactory },
			{ 0x56, "OpNewArray", OpNewArrayFactory },
			{ 0x57, "OpNewActivation", OpNewActivationFactory },
			{ 0x58, "OpNewClass", OpNewClassFactory },
			{ 0x59, "OpGetDescendants", OpGetDescendantsFactory },
			{ 0x5A, "OpNewCatch", OpNewCatchFactory },
			{ 0x5D, "OpFindPropStrict", OpFindPropStrictFactory },
			{ 0x5E, "OpFindProperty", OpFindPropertyFactory },
			{ 0x5F, "OpFindDef", OpFindDefFactory },
			{ 0x60, "OpGetLex", OpGetLexFactory },
			{ 0x61, "OpSetProperty", OpSetPropertyFactory },
			{ 0x62, "OpGetLocal", OpGetLocalFactory },
			{ 0x63, "OpSetLocal", OpSetLocalFactory },
			{ 0x64, "OpGetGlobalScope", OpGetGlobalScopeFactory },
			{ 0x65, "OpGetScopeObject", OpGetScopeObjectFactory },
			{ 0x66, "OpGetProperty", OpGetPropertyFactory },
			{ 0x68, "OpInitProperty", OpInitPropertyFactory },
			{ 0x6A, "OpDeleteProperty", OpDeletePropertyFactory },
			{ 0x6C, "OpGetSlot", OpGetSlotFactory },
			{ 0x6D, "OpSetSlot", OpSetSlotFactory },
			{ 0x6E, "OpGetGlobalSlot", OpGetGlobalSlotFactory },
			{ 0x6F, "OpSetGlobalSlot", OpSetGlobalSlotFactory },
			{ 0x70, "OpConvertS", OpConvertSFactory },
			{ 0x71, "OpEscXelem", OpEscXelemFactory },
			{ 0x72, "OpEscXattr", OpEscXattrFactory },
			{ 0x73, "OpConvertI", OpConvertIFactory },
			{ 0x74, "OpConvertU", OpConvertUFactory },
			{ 0x75, "OpConvertD", OpConvertDFactory },
			{ 0x76, "OpConvertB", OpConvertBFactory },
			{ 0x77, "OpConvertO", OpConvertOFactory },
			{ 0x78, "OpCheckFilter", OpCheckFilterFactory },
			{ 0x80, "OpCoerce", OpCoerceFactory },
			{ 0x81, "OpCoerceB", OpCoerceBFactory },
			{ 0x82, "OpCoerceA", OpCoerceAFactory },
			{ 0x83, "OpCoerceI", OpCoerceIFactory },
			{ 0x84, "OpCoerceD", OpCoerceDFactory },
			{ 0x85, "OpCoerceS", OpCoerceSFactory },
			{ 0x86, "OpAsType", OpAsTypeFactory },
			{ 0x87, "OpAsTypeLate", OpAsTypeLateFactory },
			{ 0x88, "OpCoerceU", OpCoerceUFactory },
			{ 0x89, "OpCoerceO", OpCoerceOFactory },
			{ 0x90, "OpNegate", OpNegateFactory },
			{ 0x91, "OpIncrement", OpIncrementFactory },
			{ 0x92, "OpIncLocal", OpIncLocalFactory },
			{ 0x93, "OpDecrement", OpDecrementFactory },
			{ 0x94, "OpDecLocal", OpDecLocalFactory },
			{ 0x95, "OpTypeOf", OpTypeOfFactory },
			{ 0x96, "OpNot", OpNotFactory },
			{ 0x97, "OpBitNot", OpBitNotFactory },
			{ 0xA0, "OpAdd", OpAddFactory },
			{ 0xA1, "OpSubtract", OpSubtractFactory },
			{ 0xA2, "OpMultiply", OpMultiplyFactory },
			{ 0xA3, "OpDivide", OpDivideFactory },
			{ 0xA4, "OpModulo", OpModuloFactory },
			{ 0xA5, "OpLShift", OpLShiftFactory },
			{ 0xA6, "OpRShift", OpRShiftFactory },
			{ 0xA7, "OpURShift", OpURShiftFactory },
			{ 0xA8, "OpBitAnd", OpBitAndFactory },
			{ 0xA9, "OpBitOr", OpBitOrFactory },
			{ 0xAA, "OpBitXor", OpBitXorFactory },
			{ 0xAB, "OpEquals", OpEqualsFactory },
			{ 0xAC, "OpStrictEquals", OpStrictEqualsFactory },
			{ 0xAD, "OpLessThan", OpLessThanFactory },
			{ 0xAE, "OpLessEquals", OpLessEqualsFactory },
			{ 0xAF, "OpGreaterThan", OpGreaterThanFactory },
			{ 0xB0, "OpGreaterEquals", OpGreaterEqualsFactory },
			{ 0xB1, "OpInstanceOf", OpInstanceOfFactory },
			{ 0xB2, "OpIsType", OpIsTypeFactory },
			{ 0xB3, "OpIsTypeLate", OpIsTypeLateFactory },
			{ 0xB4, "OpIn", OpInFactory },
			{ 0xC0, "OpIncrementI", OpIncrementIFactory },
			{ 0xC1, "OpDecrementI", OpDecrementIFactory },
			{ 0xC2, "OpIncLocalI", OpIncLocalIFactory },
			{ 0xC3, "OpDecLocalI", OpDecLocalIFactory },
			{ 0xC4, "OpNegateI", OpNegateIFactory },
			{ 0xC5, "OpAddI", OpAddIFactory },
			{ 0xC6, "OpSubtractI", OpSubtractIFactory },
			{ 0xC7, "OpMultiplyI", OpMultiplyIFactory },
			{ 0xD0, "OpGetLocal0", OpGetLocal0Factory },
			{ 0xD1, "OpGetLocal1", OpGetLocal1Factory },
			{ 0xD2, "OpGetLocal2", OpGetLocal2Factory },
			{ 0xD3, "OpGetLocal3", OpGetLocal3Factory },
			{ 0xD4, "OpSetLocal0", OpSetLocal0Factory },
			{ 0xD5, "OpSetLocal1", OpSetLocal1Factory },
			{ 0xD6, "OpSetLocal2", OpSetLocal2Factory },
			{ 0xD7, "OpSetLocal3", OpSetLocal3Factory },
			{ 0xEF, "OpDebugReg", OpDebugRegFactory },
			{ 0xF0, "OpDebugLine", OpDebugLineFactory },
			{ 0xF1, "OpDebugFile", OpDebugFileFactory },
			{ 0xF2, "OpBkPtLine", OpBkPtLineFactory },
			{ 0xF3, "OpTimestamp", OpTimestampFactory },
		{ 0, NULL }
	};
	template<> int IdItem<OpCode>::nRegistered = 152;
	template<> const char* IdItem<OpCode>::itemName = "opcode";
}
