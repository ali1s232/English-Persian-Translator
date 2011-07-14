#include "../TranslatorBase/TranslatorTools.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace TranslationTools;

int main()
{
	/*ttFileIManager loader;
	ttWord::getStaticTypeInfo();
	ttArray::getStaticTypeInfo();*/
	ttObject* x  = new ttObject();
	ttWord* y = new ttWord(L"salam");
	ttArray* z = new ttArray(new ttWord(L"babat"), new ttWord(L"amat"),NULL);
	x->attachMetaData(y);
	x->attachMetaData(z);
	x->retain();
	ttMemoryManager::getInstance()->cleanUp();
	ttFileOManager k;
	k.initializeSave(x);
	k.flush("test2.srz");
	x->release();
	ttMemoryManager::getInstance()->cleanUp();
	ttFileIManager kk;
	x = kk.initializeLoad("test2.srz");
	y = x->getMetaData<ttWord>();
	z = x->getMetaData<ttArray>();
	x->retain();
	ttMemoryManager::getInstance()->cleanUp();
	x->release();
	ttMemoryManager::getInstance()->cleanUp();
	return 0;
}
