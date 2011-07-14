#pragma once
#ifndef ttNODE_H_
#define ttNODE_H_

#include "ttObject.h"

#include <vector>

namespace TranslationTools
{

class ttArray : public ttObject
{
	ttDeclareRTTI;
	std::vector<ttObject*> mData;
public:
	ttArray();
	ttArray(ttObject* first,...);
	ttArray(const ttArray&);
	~ttArray();
	inline ttObject* operator [](int i) const
	{
		return mData[i];
	}
	inline ttObject& operator ()(int i) const
	{
		return *mData[i];
	}
	void addObject(ttObject* pEntry,int pos = -1);
	void removeObject(int pos = -1);
	void print(std::ostream& stream);
	
	void save(ttFileOManager&, void*);
	void load(ttFileIManager&, void*,int);
	int size();
	ttObject* clone() const;
};

}

#endif