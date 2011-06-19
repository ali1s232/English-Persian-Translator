#pragma once
#ifndef ttATOMIC_H_
#define ttATOMIC_H_

#include "ttObject.h"
#include <string>

namespace TranslationTools
{

class ttAtomic : public ttObject
{
public:
	typedef std::basic_string<wchar_t> wordType;
private:
	wordType word;
public:
	ttAtomic(wordType pWord = L"");
	virtual void print(std::ostream& stream);
};

}

std::ostream& operator <<(std::ostream& stream, TranslationTools::ttAtomic::wordType);

#endif