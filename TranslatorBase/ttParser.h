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
	void explode(const ttWord::wordType& input,const ttWord::wordType& delims, std::vector<ttWord::wordType>& output)
	{
		unsigned last = 0;
		for (unsigned i=0;i<input.size();i++)
			if (delims.find(input[i]) != ttWord::wordType::npos)
			{
				if (i - last > 0)
					output.push_back(ttWord::wordType(input.c_str() + last ,i - last ));
				last = i + 1;
			}
		if (input.size() - last > 0)
			output.push_back(ttWord::wordType(input.c_str() + last,input.size() - last));
	};
public:
	ttParser() : mDictionary(NULL) {};
	virtual ~ttParser() {};
	virtual ttArray* parse(ttWord::wordType script) = 0;
	virtual ttWord::wordType translate(ttArray* pRoot) = 0;
	virtual ttDictionary* getDictionary() {return mDictionary;};
};

}

#endif