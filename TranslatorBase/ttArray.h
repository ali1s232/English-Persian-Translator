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
	std::vector<ttObject*> children;
public:
	ttArray();
	ttArray(ttObject* first,...);
	ttArray(ttArray& pNode) : ttObject(pNode)
	{
		children.resize(pNode.children.size());
		for(unsigned i=0;i<pNode.size();i++)
			children[i] = pNode.children[i];
	}
	~ttArray();
	inline ttObject* operator [](int i) const
	{
		return children[i];
	}
	inline ttObject& operator ()(int i) const
	{
		return *children[i];
	}
	void attachChild(ttObject* pEntry,int pos = -1);
	void removeChild(int pos = -1);
	void print(std::ostream& stream);
	
	void 
};

}

#endif