#ifndef SVG_TRANSFORMPARSER_H
#define SVG_TRANSFORMPARSER_H

#include <string>
#include <vector>
#include <iostream>
#include <libxml/tree.h>
#include "Geom.h"
#include "Parser.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846264338328
#endif

namespace SWF {

class TransformParser : public Parser {
	public:
		TransformParser() :
			Parser('(', ')', ',') {
		}
		Matrix getMatrix() { return transformMatrix; }
		void parse(const char* str) { doParse(str); }

	private:
		Matrix transformMatrix;

		void handleData(const std::string& transformType, const std::vector<std::string>& params);
		void printWarning(const std::string& transformType);
};

}

#endif
