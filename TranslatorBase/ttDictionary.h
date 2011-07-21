#pragma once
#ifndef ttDICTIONARY_H_

#include "ttObject.h"
#include "ttWord.h"
#include "ttArray.h"

namespace TranslationTools
{
	class ttDictionary : public ttObject
	{
		struct ttWordPtrLess
		{
			bool operator ()(const ttWord* pLeft,const ttWord*pRight)
			{
				return pLeft->getWord() < pRight->getWord();
			}
		};
		std::map<ttWord*,std::vector<int>,ttWordPtrLess> mLookupTable; 
		ttArray *mWordList;
		void addWord(const ttWord& pWord,int id);
	public:
		ttDictionary(void);
		ttDictionary(const ttDictionary& pDictionary) : mWordList(static_cast<ttArray*>(pDictionary.mWordList->clone()))
		{
			mWordList->retain();
			for(unsigned i =0 ;i<mWordList->objNum();i++)
			{
				mLookupTable[static_cast<ttWord*>(mWordList->operator[](i))].push_back(i);
				mWordList->operator[](i)->retain();
			}
		}
		static bool addWord(const ttArray& pWord,ttArray& dictionaries);
		virtual int findWord(const ttWord& pWord);
		virtual ttWord* getWord(int pID) const;
		virtual ttArray& findNearestWords(const ttWord& pWord);
		virtual ~ttDictionary(void);
		
		virtual void load(ttFileIManager& pFileManager, void* pData, int pDataLen);
		virtual void save(ttFileOManager& pFileManager, void* pBuffer )const;
		virtual int size() const;
		inline virtual ttObject* clone() const
		{
			return new ttDictionary(*this);
		}
	};

}

#endif