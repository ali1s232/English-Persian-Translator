#include "PersianParser.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace TranslationTools;

PersianParser::PersianParser(void)
{
	ttFileIManager inputfile;
	mDictionary = dynamic_cast<ttDictionary*>(inputfile.initializeLoad("PersianDictionary.srz"));
	if (mDictionary == NULL)
		mDictionary = new ttDictionary;
	mDictionary->retain();
}

TranslationTools::ttArray* PersianParser::parse(TranslationTools::ttWord::wordType script)
{
	//script = towlower(script)
	for(unsigned i=0;i<script.size();i++)
		script[i] = towlower(script[i]);
	vector<ttWord::wordType> paragraphs;
	explode(script,L"\n",paragraphs);
	ttArray* root = new ttArray;
	for(unsigned i=0;i<paragraphs.size();i++)
	{
		vector<ttWord::wordType> senteces;
		explode(paragraphs[i],L".;!?,",senteces);
		ttArray* paragraph = new ttArray;
		//wcout << L"Paragraph " << i << " : \n";
		for(unsigned j=0;j<senteces.size();j++)
		{
			vector<ttWord::wordType> words;
			explode (senteces[j],L" ", words);
			int shift = 0;
			for(unsigned k=0;k + shift<words.size();k++)
			{
				words[k] = words[k+shift];
				if (words[k] == L"می")
				{
					words[k] += words[k+shift+1];
					shift ++;
				}
			}
			words.resize(words.size() - shift);
			ttArray& sentence = *new ttArray;
			for(unsigned i=0;i<words.size();i++)
				sentence(i) = & mDictionary->findNearestWords(words[i]);
			
			/*for(unsigned i=0;i<words.size();i++)
			{
				if (dynamic_cast<ttArray*>(sentence[i])->objnum() == 0))
					sentence[i] = new ttWord(words[i]);
				if (dynamic_cast<ttArray*>(sentence[i])->objnum() == 1))
					sentence[i] = dynamic_cast<ttArray*>(sentence[i])->operator[](0);
			}*/

			pair<ttWordType*,ttPhraseRole*> needed [3];
			needed[0].first = new ttWordType(ttWordType::wt_Noun);
			needed[1].first = new ttWordType(ttWordType::wt_Noun);
			needed[2].first = new ttWordType(ttWordType::wt_Verb);
			needed[0].second = new ttPhraseRole(ttPhraseRole::pr_Subject);
			needed[1].second = new ttPhraseRole(ttPhraseRole::pr_Object);
			needed[2].second = new ttPhraseRole(ttPhraseRole::pr_Verb);
			int neededFound = 0;
			ttArray* result = new ttArray(new ttArray,new ttArray,new ttArray,NULL);
			for(unsigned i=0;i<words.size() && neededFound < 3;i++)
			{
				if (dynamic_cast<ttArray*>(sentence[i]))
				{
					unsigned j;
					for(j=0;j<static_cast<ttArray*>(sentence[i])->objNum();j++)
						if (static_cast<ttArray*>(sentence[i])->operator[](j)->getMetaData<ttWordType>())
							if ((*static_cast<ttArray*>(sentence[i])->operator[](j)->getMetaData<ttWordType>()) == *needed[neededFound].first)
							{
								static_cast<ttArray*>(result->operator ()(neededFound))->operator()(static_cast<ttArray*>(result->operator ()(neededFound))->objNum()) = 
									new ttWordID(mDictionary->findWord(*static_cast<ttWord*>(static_cast<ttArray*>(sentence[i])->operator[](j))));
								//result->operator ()(neededFound) = new ttArray(new ttWordID(mDictionary->findWord(
								//	*static_cast<ttWord*>(static_cast<ttArray*>(sentence[i])->operator[](j)))));
								result->operator ()(neededFound)->attachMetaData(needed[neededFound].second);
								neededFound ++;
								break;
							}
					if (j < static_cast<ttArray*>(sentence[i])->objNum())
						continue;
					if (neededFound == 1 || neededFound == 2)
					for(j=0;j<static_cast<ttArray*>(sentence[i])->objNum();j++)
						if (static_cast<ttArray*>(sentence[i])->operator[](j)->getMetaData<ttWordType>())
							if (*static_cast<ttArray*>(sentence[i])->operator[](j)->getMetaData<ttWordType>() == ttWordType::wt_Adjective)
							{
								static_cast<ttArray*>(result->operator ()(neededFound - 1))->operator()(static_cast<ttArray*>(result->operator ()(neededFound - 1))->objNum()) = 
									new ttWordID(mDictionary->findWord(*static_cast<ttWord*>(static_cast<ttArray*>(sentence[i])->operator[](j))));
							}
					if (neededFound == 1 || neededFound == 2)
					for(j=0;j<static_cast<ttArray*>(sentence[i])->objNum();j++)
						if (static_cast<ttArray*>(sentence[i])->operator[](j)->getMetaData<ttWordType>())
							if (*static_cast<ttArray*>(sentence[i])->operator[](j)->getMetaData<ttWordType>() == ttWordType::wt_Adverb)
							{
								static_cast<ttArray*>(result->operator ()(2))->operator()(static_cast<ttArray*>(result->operator ()(2))->objNum()) = 
									new ttWordID(mDictionary->findWord(*static_cast<ttWord*>(static_cast<ttArray*>(sentence[i])->operator[](j))));
							}
				}
				
			}
			paragraph->operator()(paragraph->objNum()) = result;
		}
		root ->operator()(root->objNum()) = paragraph;
	}
	return root;
}

TranslationTools::ttWord::wordType PersianParser::translate(TranslationTools::ttArray* pRoot)
{
	return L"";
}

PersianParser::~PersianParser(void)
{
	if (mDictionary == NULL)
		return;
	ttFileOManager outputfile;
	outputfile.initializeSave(mDictionary);
	outputfile.flush("PersianDictionary.srz");
	mDictionary->release();
}
