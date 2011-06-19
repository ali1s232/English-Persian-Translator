#pragma once
#ifndef ttNODE_H_
#define ttNODE_H_

#include "ttObject.h"

#include <vector>

namespace TranslationTools
{

class ttNode : public ttObject
{
	std::vector<ttObject*> children;
public:
	ttNode();
	ttNode(ttObject* first,...);
	inline ttObject* operator [](int i) const
	{
		return children[i];
	}
	void attachChild(ttObject* pEntry,int pos = -1);
	void removeChild(int pos = -1);
	void print(std::ostream& stream);
};

}

#endif