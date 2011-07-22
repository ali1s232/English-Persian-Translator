#include "../TranslatorBase/TranslatorTools.h"
#include "../EnglishParser/EnglishParser.h"
#include <iostream>
#include <fstream>

using namespace std;
using namespace TranslationTools;

ttWord salam(L"salam");
ttWord salam2(L"salam");
ttWord hi(L"hi");

int main()
{
	wstring script = L"hi, I am Ali. This is test number 1!\n it a big test to check explode function!\n";
	EnglishParser ep;
	ep.parse(script);
	return 0;
}
