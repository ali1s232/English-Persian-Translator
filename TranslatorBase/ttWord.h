#pragma once
#ifndef ttWord_H_
#define ttWord_H_

#include "ttObject.h"
#include <string>

namespace TranslationTools
{

	class ttWord : public ttObject
	{
		ttDeclareRTTI;
	public:
		typedef std::basic_string<wchar_t> wordType;
	private:
		wordType mWord;
	public:
		ttWord(wordType pWord = L"");
		ttWord(const ttWord&);
		virtual void print(std::ostream& stream);
		virtual void save(ttFileOManager& buffer,void*){};
		virtual void load(ttFileIManager& buffer,void* ,int size); 
		virtual int size() { return 0;};
		virtual ttObject* clone() const;
	};

}

std::ostream& operator <<(std::ostream& stream, TranslationTools::ttWord::wordType);

#endif