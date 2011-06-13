#pragma once
#ifndef TLNODE_H_
#define TLNODE_H_

#include "tlObject.h"

#include <vector>

class tlNode : public tlObject
{
	std::vector<tlObject*> children;
public:
	tlNode();
	tlNode(tlObject* first,...);
	inline tlObject* operator [](int i) const
	{
		return children[i];
	}
	void attachChild(tlObject* pEntry,int pos = -1);
	void removeChild(int pos = -1);
	void print(std::ostream& stream);
};



#endif