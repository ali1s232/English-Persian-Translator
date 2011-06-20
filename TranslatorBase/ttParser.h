#pragma once

#ifndef ttPARSER_H_
#define ttPARSER_H_

#include "ttNode.h"
#include "ttWord.h"
#include "ttNode.h"

namespace TranslationTools
{

class ttParser
{
public:
	ttParser(ttWord::wordType scrpit);
	ttParser();
	virtual ttNode* parse(ttWord::wordType script) = 0;
	ttPROPERTY_NODEF_PROTECTED(ttNode*, root);
	virtual ttNode* translate(ttNode* pRoot) = 0;
};

}

#endif