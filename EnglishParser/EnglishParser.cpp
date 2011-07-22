#include "EnglishParser.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace TranslationTools;

EnglishParser::EnglishParser(void)
{
	ttFileIManager inputfile;
	mDictionary = dynamic_cast<ttDictionary*>(inputfile.initializeLoad("EnglishDictionary.srz"));
	if (mDictionary == NULL)
		mDictionary = new ttDictionary;
	mDictionary->retain();
}

TranslationTools::ttArray* EnglishParser::parse(TranslationTools::ttWord::wordType script)
{
	//script = towlower(script)
	for(unsigned i=0;i<script.size();i++)
		script[i] = towlower(script[i]);
	vector<ttWord::wordType> paragraphs;
	explode(script,L"\n",paragraphs);
	for(unsigned i=0;i<paragraphs.size();i++)
	{
		vector<ttWord::wordType> senteces;
		explode(paragraphs[i],L".;!?,",senteces);
		wcout << L"Paragraph " << i << " : \n";
		for(unsigned j=0;j<senteces.size();j++)
			wcout << L"Sentence " << j << " : " << senteces[j] << "\n";
	}
	return NULL;
}

TranslationTools::ttWord::wordType EnglishParser::translate(TranslationTools::ttArray* pRoot)
{
	wstring result;
	ttPhraseRole* needed[3] = {new ttPhraseRole(ttPhraseRole::pr_Subject), new ttPhraseRole(ttPhraseRole::pr_Verb), new ttPhraseRole(ttPhraseRole::pr_Object)};
	for(unsigned i=0;i<pRoot->objNum();i++)
	{
		if(ttArray* paragraph = dynamic_cast<ttArray*>(pRoot->operator[](i)))
		{
			for(unsigned j = 0; j < paragraph->objNum();j++)
				if (ttArray* sentence = dynamic_cast<ttArray*>(paragraph->operator[](j)))
				{
					for(unsigned found = 0;found < 3;found ++)
						for(unsigned k=0;k<sentence->objNum();k++)
							if (sentence->operator[](k)->getMetaData<ttPhraseRole>() && sentence->operator[](k)->getMetaData<ttPhraseRole>()->operator== (*needed[found]))
							{
								if (ttArray* words = dynamic_cast<ttArray*>(sentence->operator[](k)))
								{
									for(unsigned l = 0;l < words->objNum();l ++)
									{
										words->operator[](l) = mDictionary->getWord(static_cast<ttWordID*>(words->operator[](l))->getID());
										if (!words->operator[](l)->getMetaData<ttWordType>()->operator == (ttWordType::wt_Noun) &&
											!words->operator[](l)->getMetaData<ttWordType>()->operator == (ttWordType::wt_Verb))
											result += static_cast<ttWord*>(words->operator[](l))->getWord() + L" ";
									}
									for(unsigned l = 0;l < words->objNum();l ++)
										if (words->operator[](l)->getMetaData<ttWordType>()->operator == (ttWordType::wt_Noun) ||
											words->operator[](l)->getMetaData<ttWordType>()->operator == (ttWordType::wt_Verb))
											result += static_cast<ttWord*>(words->operator[](l))->getWord() + L" ";
								}
							}
					result += L'.';
				}
			result += L'\n';
		}
	}
	return result;
}

EnglishParser::~EnglishParser(void)
{
	if (mDictionary == NULL)
		return;
	ttFileOManager outputfile;
	outputfile.initializeSave(mDictionary);
	outputfile.flush("EnglishDictionary.srz");
	mDictionary->release();
}
