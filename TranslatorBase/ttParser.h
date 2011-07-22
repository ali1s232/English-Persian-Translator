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
	ttParser(){};
	virtual ~ttParser(){};
	virtual ttArray* parse(ttWord::wordType script) = 0;
	virtual ttWord::wordType translate(ttArray* pRoot) = 0;
};

}

#endif