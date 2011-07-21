#pragma once
#ifndef ttNODE_H_
#define ttNODE_H_

#include "ttObject.h"

#include <vector>

namespace TranslationTools
{

class ttArray : public ttObject
{
	static ttObject*mNULL;
	ttDeclareRTTI;
	std::vector<ttObject*> mData;
public:
	ttArray();
	ttArray(ttObject* first,...);
	ttArray(const ttArray&);
	~ttArray();
	inline ttObject*& operator [](int i) 
	{
		return mData[i];
	}
	
	inline ttObject* const& operator [](int i) const
	{
		return mData[i];
	}
	
	inline ttObject*& operator ()(unsigned i)
	{
		if (i >= mData.size())
		{
			unsigned temp = mData.size();
			mData.resize(i+1);
			for(;temp < mData.size();temp++)
				mData[temp] = NULL;
		}
		return mData[i];
	}
	inline unsigned int objNum() const
	{
		return mData.size();
	}
	void addObject(ttObject* pEntry,int pos = -1);
	void removeObject(int pos = -1);
	void print(std::ostream& stream);
	
	void save(ttFileOManager&, void*) const;
	void load(ttFileIManager&, void*,int);
	int size()const;
	ttObject* clone() const;

	virtual bool operator ==(const ttObject& pRight) const;
};

}

#endif