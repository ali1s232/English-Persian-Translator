#include "../TranslatorBase/TranslatorTools.h"

#pragma once
#ifndef PERSIANPARSER_H_

class PersianParser : public TranslationTools::ttParser
{
	TranslationTools::ttDictionary *mDictionary;
public:
	PersianParser(void);
	virtual TranslationTools::ttArray* parse(TranslationTools::ttWord::wordType script);
	virtual TranslationTools::ttWord::wordType translate(TranslationTools::ttArray* pRoot);
	~PersianParser(void);
};

#endif

