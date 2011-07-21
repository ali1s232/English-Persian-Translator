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
	public:
		ttPROPERTY(wordType,Word);
		ttWord(wordType pWord = L"");
		ttWord(const ttWord&);
		virtual void print(std::ostream& stream);
		virtual void save(ttFileOManager& buffer,void*)const;
		virtual void load(ttFileIManager& buffer,void* ,int size); 
		virtual int size() const;
		virtual ttObject* clone() const;
		virtual bool operator ==(const ttObject& pRight) const;
	};

}

std::ostream& operator <<(std::ostream& stream, TranslationTools::ttWord::wordType);

#endif