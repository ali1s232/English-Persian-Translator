#pragma once
#ifndef TLMEMORYMANAGER_H_
#define TLMEMORYMANAGER_H_

#include <set>
#include "tlObject.h"

class tlMemoryManager
{
	static tlMemoryManager* instance;
	std::set<tlObject*> deleteList;
public:
	tlMemoryManager();
	
	static inline tlMemoryManager* getInstance()
	{
		if (instance == NULL)
			instance = new tlMemoryManager;
		return instance;
	}

	void addToDeleteList(tlObject* pEntry);
	void removeFromDeleteList(tlObject* pEntry);

	void cleanUp();
};

#endif