#include "tlMemoryManager.h"

using namespace std;

tlMemoryManager* tlMemoryManager::instance = NULL;

tlMemoryManager::tlMemoryManager()
{
}

void tlMemoryManager::addToDeleteList(tlObject* pEntry)
{
	if (pEntry)
		deleteList.insert(pEntry);
}

void tlMemoryManager::removeFromDeleteList(tlObject* pEntry)
{
	deleteList.erase(pEntry);
}

void tlMemoryManager::cleanUp()
{
	for (set<tlObject*>::iterator i=deleteList.begin(); i != deleteList.end();i++)
		delete *i;
	deleteList.clear();
}