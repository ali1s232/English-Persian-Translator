#include "../TranslatorBase/SharedObjects.h"
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream fileOut("out.txt",ios::binary);
	fileOut.put(0xff).put(0xfe);
	tlAtomic a(L"ali"),b(L"Gholi"),c(L"vali");
	tlNode d,e;
	e.attachChild(&a);
	e.attachChild(&d);
	e.attachChild(&c);
	d.attachChild(&b);
	e.print(fileOut);
	return 0;
}