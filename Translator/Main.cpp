#include "../TranslatorBase/TranslatorTools.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace TranslationTools;

struct ttWordIntoducer{
	ttWordIntoducer()
	{
		TranslationTools::ttObjectPool::getInstance()->registerNewSample(new ttWord);
	}
	int i;
}a;


int main()
{
	ttFileIManager loader;
	ttObject* o = loader.initializeLoad("test.srz");
	o->getMetaData<ttWord>()->print(cout);
	return 0;
}