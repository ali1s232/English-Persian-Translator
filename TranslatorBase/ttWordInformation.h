#pragma once
#ifndef ttWORDINFORMATION_H_
#define ttWORDINFORMATION_H_

#include "ttObject.h"

namespace TranslationTools
{

	class ttWordInformation : public ttObject
	{
	public:
		enum ttWordType
		{
			wt_Unknown = 0,
			wt_Noun = 1,
			wt_Verb = 2,
			wt_Adjective = 3,
			wt_Adverb = 4,
			wt_Pronoun = 5,
			wt_Preposition = 6,
			wt_Conjuction = 7,
			wt_Interjunction = 8,
			wt_max
		};
		ttPROPERTY_PROTECTED(int, WordID);
		ttPROPERTY_PROTECTED(ttWordType, WordType);
	};

}

#endif