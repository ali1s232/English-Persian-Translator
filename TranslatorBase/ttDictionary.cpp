#include "ttDictionary.h"

using namespace std;
using namespace TranslationTools;


ttDictionary::ttDictionary(void)
{
	mWordList = new ttArray;
	mWordList->retain();
}

void ttDictionary::addWord(const ttWord& pWord,int pID)
{
	mWordList->operator()(pID) = pWord.clone();
	mWordList->operator[](pID)->retain();
	map <ttWord*,vector<int>,ttWordPtrLess >::iterator wordPos = mLookupTable.find(static_cast<ttWord*>(mWordList->operator[](pID)));
	if (wordPos == mLookupTable.end())
	{
		mLookupTable[static_cast<ttWord*>(mWordList->operator[](pID))].push_back(pID);	
		return;
	}
	for(unsigned i=0;i<wordPos->second.size();i++)
	{
		if (mLookupTable[static_cast<ttWord*>(mWordList->operator[](pID))][i] == pID)
			return;
	}
	wordPos->second.push_back(pID);
}

bool ttDictionary::addWord(const ttArray& pWords,ttArray& dictionaries)
{
	if (pWords.objNum() != dictionaries.objNum())
		return false;
	int wID = -1,dID = 0;
	for(unsigned i=0;i<pWords.objNum();i++)
		if (dynamic_cast<ttWord*>(pWords[i]) == NULL)
			return false;
	for(unsigned i=0;i<pWords.objNum();i++)
		if (dynamic_cast<ttWord*>(pWords[i]) == NULL)
			return false;
	for (unsigned i=0;i<pWords.objNum();i++)
		if(wID == -1)
		{
			if ((wID = static_cast<ttDictionary*>(dictionaries[i])->findWord(*static_cast<ttWord*>(pWords[i]))) != -1)
				dID = i;
		}
		else
			if (static_cast<ttDictionary*>(dictionaries[i])->findWord(*static_cast<ttWord*>(pWords[i])) != wID)
				return false;
	bool needNewSlot = false;
	if (wID == -1)
		needNewSlot = true;
	else
		for(unsigned i=0;i<pWords.objNum() && needNewSlot == false;i++)
			if (wID != i)
				if (static_cast<ttDictionary*>(dictionaries[i])->mWordList->operator[](wID) != NULL)
					//if (*static_cast<ttDictionary*>(dictionaries[i])->mWordList->operator[](wID) != (*static_cast<ttWord*>(pWords[i])))
						needNewSlot = true;
	if (needNewSlot)
	{
		unsigned int minFree = 0;
		for(unsigned i=0;i<pWords.objNum();i++)
			minFree = max(static_cast<ttDictionary*>(dictionaries[i])->mWordList->objNum(), minFree);
		wID = minFree;
	}
	for(unsigned i=0;i<pWords.objNum();i++)
		static_cast<ttDictionary*>(dictionaries[i])->addWord(*static_cast<ttWord*>(pWords[i]),wID);
	return true;
}

int ttDictionary::findWord(const ttWord& pWord)
{
	map <ttWord*,vector<int>,ttWordPtrLess >::iterator wordPos = mLookupTable.find(const_cast<ttWord*>(&pWord));
	if (wordPos == mLookupTable.end())
		return -1;
	for(unsigned i=0;i<wordPos->second.size();i++)
		if (static_cast<ttWord*>(mWordList->operator[](wordPos->second[i]))->operator==(pWord))
			return wordPos->second[i];
	return -1;
}

ttWord* ttDictionary::getWord(int pID)const
{
	if (((unsigned)pID) < mWordList->objNum())
		return static_cast<ttWord*>(mWordList->operator[](pID)->clone());
	else
		return NULL;
}

ttArray& ttDictionary::findNearestWords(const ttWord& pWord)
{
	map <ttWord*,vector<int>,ttWordPtrLess >::iterator wordPos = mLookupTable.find(const_cast<ttWord*>(&pWord));
	ttArray& result = *new ttArray;
	if (wordPos != mLookupTable.end())
		for(unsigned i=0;i<wordPos->second.size();i++)
			result.addObject(mWordList->operator[](wordPos->second[i])->clone());
	return result;
}

void ttDictionary::load(ttFileIManager& pFileManager,void* data,int dataSize)
{
	for(unsigned i=0;i<mWordList->objNum();i++)
		mWordList->operator[](i)->release();
	mWordList->release();
	mWordList = static_cast<ttArray*>(pFileManager.renewPointer(*static_cast<ttObject**>(data)));
	for (unsigned i=0;i<mWordList->objNum();i++)
	{
		mWordList->operator[](i)->retain();
		mLookupTable[static_cast<ttWord*>(mWordList->operator[](i))].push_back(i);
	}

}

void ttDictionary::save(ttFileOManager& pFileManager,void* buffer) const
{
	pFileManager.addObject(mWordList);
	memcpy(buffer,&mWordList,sizeof(ttObject*));
}

int ttDictionary::size() const
{
	return sizeof(ttObject*);
}

ttDictionary::~ttDictionary(void)
{
}
