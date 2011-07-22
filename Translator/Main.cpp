﻿#include "../TranslatorBase/TranslatorTools.h"
#include "../EnglishParser/EnglishParser.h"
#include "../PersianParser/PersianParser.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace TranslationTools;

ttWord salam(L"salam");
ttWord salam2(L"salam");
ttWord hi(L"hi");


EnglishParser *ep;
PersianParser *pp;

void addtodic(wstring fa,wstring en,ttWordType type)
{
	ttWord *faW = new ttWord (fa);
	ttWord *enW = new ttWord (en);
	faW->attachMetaData(new ttWordType(type));
	enW->attachMetaData(new ttWordType(type));
	ttDictionary::addWord(*new ttArray(faW, enW, NULL),*new ttArray(pp->getDictionary(),ep->getDictionary(),NULL));
}

int main()
{
	ttWord::getStaticTypeInfo();
	ttWordType::getStaticTypeInfo();
	ttWordID::getStaticTypeInfo();
	ttPhraseRole::getStaticTypeInfo();
	ttDictionary::getStaticTypeInfo();
	ttArray::getStaticTypeInfo();
	pp = new PersianParser;
	ep = new EnglishParser;
	addtodic(L"من",L"I",ttWordType::wt_Noun);
	addtodic(L"علی",L"ali",ttWordType::wt_Noun);
	addtodic(L"قهرمان",L"champion",ttWordType::wt_Adjective);
	addtodic(L"هستم",L"am",ttWordType::wt_Verb);
	wstring scriptp(L"من علی قهرمان هستم.");
	ttArray* temp = pp->parse(scriptp);
	wcout << ep->translate(temp) <"\n";
//	while(true);
	return 0;
}
