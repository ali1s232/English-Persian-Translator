#pragma once

#ifndef ttPARSER_H_
#define ttPARSER_H_

#include "ttArray.h"
#include "ttWord.h"

namespace TranslationTools
{

class ttParser
{
public:
	ttParser(ttWord::wordType scrpit);
	ttParser();
	virtual ttArray* parse(ttWord::wordType script) = 0;
	ttPROPERTY_NODEF_PROTECTED(ttArray*, root);
	virtual ttArray* translate(ttArray* pRoot) = 0;
};

}

#endif