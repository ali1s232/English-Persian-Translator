#pragma once
#ifndef TLATOMIC_H_
#define TLATOMIC_H_

#include "tlObject.h"
#include <string>

class tlAtomic : public tlObject
{
public:
	typedef std::basic_string<wchar_t> wordType;
private:
	wordType word;
public:
	tlAtomic(wordType pWord = L"");
	virtual void print(std::ostream& stream);
};

std::ostream& operator <<(std::ostream& stream, tlAtomic::wordType);

#endif