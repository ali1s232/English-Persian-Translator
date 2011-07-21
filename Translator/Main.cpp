#include "../TranslatorBase/TranslatorTools.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace TranslationTools;

ttWord salam(L"salam");
ttWord salam2(L"salam");
ttWord hi(L"hi");

int main()
{
	salam.retain();
	salam2.retain();
	salam2.attachMetaData(new ttObject);
	hi.retain();
	ttDictionary* dic = new ttDictionary;
	ttDictionary::addWord(ttArray(&salam,NULL),ttArray(dic,NULL));
	ttDictionary::addWord(ttArray(&salam2,NULL),ttArray(dic,NULL));
	ttDictionary::addWord(ttArray(&hi,NULL),ttArray(dic,NULL));

	wcout << dic->findWord(salam) << "\n";

	ttArray& x = dic->findNearestWords(salam);
	ttFileOManager saver;
	saver.initializeSave(dic);
	saver.flush("dictionary.srz");
	dic = (ttDictionary*)ttFileIManager::ttFileIManager().initializeLoad("dictionary.srz");
	for(unsigned i=0;i<x.objNum();i++)
		wcout << dynamic_cast<ttWord*>(x[i])->getWord() << "\n";

	return 0;
}
