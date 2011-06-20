#pragma once
#ifndef ttWord_H_
#define ttWord_H_

#include "ttObject.h"
#include <string>

namespace TranslationTools
{

	class ttWord : public ttObject
	{
	public:
		typedef std::basic_string<wchar_t> wordType;
	private:
		wordType word;
	public:
		ttWord(wordType pWord = L"");
		virtual void print(std::ostream& stream);
	};

}

std::ostream& operator <<(std::ostream& stream, TranslationTools::ttWord::wordType);

#endif