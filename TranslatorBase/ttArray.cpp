#include "ttArray.h"
#include <stdarg.h>
#include <iostream>

using namespace std;
using namespace TranslationTools;

ttImplementRTTI(ttArray);

ttArray::ttArray()
{

}

ttArray::~ttArray()
{
	cout << "man delete shodam alan!\n";
}

ttArray::ttArray(ttObject* first, ...)
{
	int i = _INTSIZEOF(ttObject*);
	va_list list;
	va_start(list,first);
	while (first)
	{
		first->retain();
		children.push_back(first);
		first = va_arg(list,ttObject*);
	}
}

void ttArray::attachChild(ttObject* pEntry,int pos)
{
	pEntry->retain();
	if (pos < 0 || pos >= (int)children.size())
		children.push_back(pEntry);
	else
		children.insert(children.begin()+pos,pEntry);
}

void ttArray::removeChild(int pos)
{
	if (pos>=0 && pos < (int)children.size())
	{
		children[pos]->release();
		children.erase(children.begin()+pos);
	}
}

void ttArray::print(ostream& stream)
{
	for(unsigned i=0;i<children.size()-1;i++)
	{
		children[i]->print(stream);
		stream << ' ' << '\0';
	}
	children.back()->print(stream);
}