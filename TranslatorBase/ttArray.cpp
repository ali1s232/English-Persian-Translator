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
	va_list list;
	va_start(list,first);
	while (first)
	{
		first->retain();
		mData.push_back(first);
		first = va_arg(list,ttObject*);
	}
}

ttArray::ttArray(const ttArray& pArray) : ttObject(pArray)
{
	mData.resize(pArray.mData.size());
	for(unsigned i=0;i<pArray.mData.size();i++)
	{
		mData[i] = pArray.mData[i];
		mData[i]->retain();
	}
}

void ttArray::addObject(ttObject* pEntry,int pos)
{
	pEntry->retain();
	if (pos < 0 || pos >= (int)mData.size())
		mData.push_back(pEntry);
	else
		mData.insert(mData.begin()+pos,pEntry);
}

void ttArray::removeObject(int pos)
{
	if (pos>=0 && pos < (int)mData.size())
	{
		mData[pos]->release();
		mData.erase(mData.begin()+pos);
	}
}

void ttArray::save(ttFileOManager& pFileManager, void* pBuffer)
{
	pFileManager.saveParent<ttObject>();
	ttObject** data = (ttObject**) pBuffer;
	for(unsigned i=0;i<mData.size();i++)
		pFileManager.addObject(data[i] = mData[i]);
}

void ttArray::load(ttFileIManager& pFileManager,void* pBuffer,int dataSize)
{
	int objectNum = dataSize / 4;
	pFileManager.loadParent<ttObject>();
	for(unsigned i = 0;i < mData.size();i++)
		mData[i]->release();
	mData.resize(objectNum);
	ttObject** data = (ttObject**) pBuffer;
	for(unsigned i=0;i<mData.size();i++)
		mData[i] = pFileManager.renewPointer(data[i]);
}

int ttArray::size()
{
	return mData.size() * 4;
}

ttObject* ttArray::clone() const
{
	return new ttArray(*this);
}

void ttArray::print(ostream& stream)
{
	for(unsigned i=0;i<mData.size()-1;i++)
	{
		mData[i]->print(stream);
		stream << ' ' << '\0';
	}
	mData.back()->print(stream);
}
