#pragma once

#ifndef ttPARSER_H_
#define ttPARSER_H_

#include "ttArray.h"
#include "ttWord.h"
#include "ttDictionary.h"

namespace TranslationTools
{

class ttParser
{
protected:
	ttDictionary* mDictionary;
public:
	ttParser() : mDictionary(NULL) {};
	virtual ~ttParser() {};
	virtual ttArray* parse(ttWord::wordType script) = 0;
	virtual ttWord::wordType translate(ttArray* pRoot) = 0;
	virtual ttDictionary* getDictionary() {return mDictionary;};
};

}

#endif