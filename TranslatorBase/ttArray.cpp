#include "ttArray.h"
#include <stdarg.h>
#include <iostream>

using namespace std;
using namespace TranslationTools;

ttImplementRTTI(ttArray);

ttObject* ttArray::mNULL;

ttArray::ttArray()
{

}

ttArray::~ttArray()
{
}

ttArray::ttArray(ttObject* first, ...)
{
	va_list list;
	va_start(list,first);
	while (first)
	{
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
	}
}

void ttArray::addObject(ttObject* pEntry,int pos)
{

	if (pos < 0 || pos >= (int)mData.size())
		mData.push_back(pEntry);
	else
		mData.insert(mData.begin()+pos,pEntry);
}

void ttArray::removeObject(int pos)
{
	if (pos>=0 && pos < (int)mData.size())
	{
		mData.erase(mData.begin()+pos);
	}
}

void ttArray::save(ttFileOManager& pFileManager, void* pBuffer)const
{
	pFileManager.saveParent<ttObject>();
	ttObject** data = (ttObject**) pBuffer;
	for(unsigned i=0;i<mData.size();i++)
		pFileManager.addObject(data[i] = mData[i]);
}

void ttArray::load(ttFileIManager& pFileManager,void* pData,int dataSize)
{
	int objectNum = dataSize / 4;
	pFileManager.loadParent<ttObject>();
	mData.resize(objectNum);
	ttObject** data = (ttObject**) pData;
	for(unsigned i=0;i<mData.size();i++)
		mData[i] = pFileManager.renewPointer(data[i]);
}

int ttArray::size()const
{
	return mData.size() * 4;
}

ttObject* ttArray::clone() const
{
	return new ttArray(*this);
}

bool ttArray::operator==(const ttObject& pRight) const
{
	if (ttObject::operator==(pRight) == false)
		return false;
	const ttArray* right = dynamic_cast<const ttArray*>(&pRight);
	if (right)
	{
		if (mData.size() != right->mData.size())
			return false;
		for (unsigned i=0;i<mData.size();i++)
			if (mData[i] != right->mData[i])
				if (!mData[i]->operator==(*right->mData[i]))
					return false;
	}
	else
		return false;
	return true;
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
