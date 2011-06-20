#include "../TranslatorBase/TranslatorTools.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace TranslationTools;

int main()
{
	ofstream fileOut("out.txt",ios::binary);
	fileOut.put(0xff).put(0xfe);
	ttWord a(L"ali"),b(L"Gholi"),c(L"vali");
	ttNode d,e;
	a.attachMetaData(new ttNode(new ttWord(L"ha"),new ttWord(L"ha"),NULL));
	a.attachMetaData(new ttWord(L"Salam"));
	e.attachChild(&a);
	e.attachChild(&d);
	e.attachChild(&c);
	d.attachChild(&b);
	e.print(fileOut);
	fileOut.put('\n').put(0);
	a.getMetaData<ttNode>()->print(fileOut);
	fileOut.put('\n').put(0);
	a.getMetaData<ttWord>()->print(fileOut);
	return 0;
}