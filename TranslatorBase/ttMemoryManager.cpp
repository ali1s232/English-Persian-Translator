#include "ttMemoryManager.h"

using namespace std;
using namespace TranslationTools;

ttMemoryManager* ttMemoryManager::instance = NULL;

ttMemoryManager::ttMemoryManager()
{
}

void ttMemoryManager::addToDeleteList(ttObject* pEntry)
{
	if (pEntry)
		deleteList.insert(pEntry);
}

void ttMemoryManager::removeFromDeleteList(ttObject* pEntry)
{
	deleteList.erase(pEntry);
}

void ttMemoryManager::cleanUp()
{
	for (set<ttObject*>::iterator i=deleteList.begin(); i != deleteList.end();i++)
		delete *i;
	deleteList.clear();
}