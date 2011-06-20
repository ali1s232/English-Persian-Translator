#pragma once
#ifndef ttDICTIONARY_H_

#include "ttObject.h"
#include "ttWord.h"
#include "ttWordInformation.h"

namespace TranslationTools
{
	class ttDictionary : public ttObject
	{
	public:
		ttDictionary(void);
		virtual void load(ttFileIOManager& buffer);
		virtual void save(ttFileIOManager& buffer);
		virtual void addWord(ttWord* pObject);
		virtual void getWord(ttWordInformation* pWI);
		virtual ~ttDictionary(void);
	};

}

#endif