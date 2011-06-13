#include "tlObject.h"
#include "tlMemoryManager.h"

tlObject::tlObject() : refCount(0), AutoRelease(false)
{
	setAutoRelease(true);
}

tlObject::~tlObject()
{

}

void tlObject::retain()
{
	if (refCount == 0 && AutoRelease)
		tlMemoryManager::getInstance()->removeFromDeleteList(this);
	refCount ++;
}

void tlObject::release()
{
	if (refCount)
		refCount --;
	if (refCount == 0 && AutoRelease)
		tlMemoryManager::getInstance()->addToDeleteList(this);
}

void tlObject::setAutoRelease(bool pAutoRelease)
{
	AutoRelease = pAutoRelease;
	if (refCount == 0)
		if (AutoRelease)
			tlMemoryManager::getInstance()->addToDeleteList(this);
		else
			tlMemoryManager::getInstance()->removeFromDeleteList(this);
}

bool tlObject::getAutoRelease() const
{
	return AutoRelease;
}

void tlObject::print(std::ostream& stream)
{
};