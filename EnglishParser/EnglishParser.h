#include "../TranslatorBase/TranslatorTools.h"

#pragma once
#ifndef PERSIANPARSER_H_

class EnglishParser : public TranslationTools::ttParser
{
public:
	EnglishParser(void);
	virtual TranslationTools::ttArray* parse(TranslationTools::ttWord::wordType script);
	virtual TranslationTools::ttWord::wordType translate(TranslationTools::ttArray* pRoot);
	~EnglishParser(void);
};

#endif

