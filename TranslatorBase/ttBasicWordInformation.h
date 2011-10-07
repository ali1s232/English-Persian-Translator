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
		bool operator == (const ttObject& pRight)const { return this->ttObject::operator== (pRight) && mID == dynamic_cast<const ttWordID*>(&pRight)->mID;};
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
		bool operator == (const ttObject& pRight)const { return this->ttObject::operator== (pRight) && mType == dynamic_cast<const ttWordType*>(&pRight)->mType;};
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
			pr_Unknown = 0,
			pr_Verb = 1,
			pr_Subject = 2,
			pr_Object = 3,
			pr_Adjective = 4,
			pr_Adverb = 5,
			pr_max
		};
		ttPhraseRole() : ttObject(), mRole(pr_Unknown) {};
		ttPhraseRole(PhraseRole pRole) : ttObject(), mRole(pRole) {};
		ttPhraseRole(const ttPhraseRole& pRole) : ttObject(pRole) { mRole = pRole.mRole;};
		
		ttPROPERTY_PROTECTED(PhraseRole,Role);
		bool operator == (const ttObject& pRight)const { return this->ttObject::operator== (pRight) && mRole == dynamic_cast<const ttPhraseRole*>(&pRight)->mRole;};
		bool operator == (const PhraseRole& pRight)const {return mRole == pRight;};
		virtual void save(ttFileOManager& buffer,void*)const;
		virtual void load(ttFileIManager& buffer,void*,int);
		virtual int size() const;
		virtual ttObject* clone()const;
	};
}

#endif