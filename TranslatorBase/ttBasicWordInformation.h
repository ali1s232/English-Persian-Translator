#pragma once
#ifndef ttWORDINFORMATION_H_
#define ttWORDINFORMATION_H_

#include "ttObject.h"

namespace TranslationTools
{

	class ttWordID : public ttObject
	{
		ttDeclareRTTI;
	public:
		ttWordID() : ttObject(), mID (-1) {};
		ttWordID(int pID) : ttObject(), mID (pID) {};
		ttWordID(const ttWordID& pID) : ttObject(pID) { mID= pID.mID;};
		ttPROPERTY_PROTECTED(int, ID);
		bool operator == (const ttWordID& pRight)const { return mID == pRight.mID && this->ttObject::operator== (pRight);};
		bool operator == (const int& pRight)const {return mID == pRight;};
		virtual void save(ttFileOManager& buffer,void*)const;
		virtual void load(ttFileIManager& buffer,void*,int);
		virtual int size() const;
		virtual ttObject* clone()const;
	};

	class ttWordType : public ttObject
	{
		ttDeclareRTTI;
	public :
		enum WordType
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
		ttWordType() : ttObject(), mType (wt_Unknown){};
		ttWordType(WordType pType) : ttObject(), mType(pType) {};
		ttWordType(const ttWordType& pType) : ttObject(pType) { mType= pType.mType;};
		ttPROPERTY_PROTECTED(WordType,Type);
		bool operator == (const ttWordType& pRight)const { return mType == pRight.mType && this->ttObject::operator== (pRight);};
		bool operator == (const WordType& pRight)const {return mType == pRight;};
		virtual void save(ttFileOManager& buffer,void*)const;
		virtual void load(ttFileIManager& buffer,void*,int);
		virtual int size() const;
		virtual ttObject* clone()const;
	};

	class ttPhraseRole : public ttObject
	{
		ttDeclareRTTI;
	public :
		enum PhraseRole
		{
			pr_Unknown,
			pr_Verb,
			pr_Subject,
			pr_Object,
			pr_Adjective,
			pr_Adverb,
			pr_max
		};
		ttPhraseRole() : ttObject(), mRole(pr_Unknown) {};
		ttPhraseRole(PhraseRole pRole) : ttObject(), mRole(pRole) {};
		ttPhraseRole(const ttPhraseRole& pRole) : ttObject(pRole) { mRole = pRole.mRole;};
		
		ttPROPERTY_PROTECTED(PhraseRole,Role);
		bool operator == (const ttPhraseRole& pRight)const { return mRole == pRight.mRole && this->ttObject::operator== (pRight);};
		bool operator == (const PhraseRole& pRight)const {return mRole == pRight;};
		virtual void save(ttFileOManager& buffer,void*)const;
		virtual void load(ttFileIManager& buffer,void*,int);
		virtual int size() const;
		virtual ttObject* clone()const;
	};
}

#endif