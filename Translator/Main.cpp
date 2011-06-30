#include "../TranslatorBase/TranslatorTools.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace TranslationTools;

int main()
{
	ttFileIManager loader;
	ttObject* o = loader.initializeLoad("test.srz");
	o->getMetaData<ttObject>()->print(cout);
	return 0;
}