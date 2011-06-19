#pragma once
#ifndef ttMEMORYMANAGER_H_
#define ttMEMORYMANAGER_H_

#include <set>
#include "ttObject.h"

namespace TranslationTools
{

class ttMemoryManager
{
	static ttMemoryManager* instance;
	std::set<ttObject*> deleteList;
public:
	ttMemoryManager();
	
	static inline ttMemoryManager* getInstance()
	{
		if (instance == NULL)
			instance = new ttMemoryManager;
		return instance;
	}

	void addToDeleteList(ttObject* pEntry);
	void removeFromDeleteList(ttObject* pEntry);

	void cleanUp();
};

}

#endif