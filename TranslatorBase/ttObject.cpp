#include "ttObject.h"
#include "ttMemoryManager.h"

using namespace TranslationTools;

ttObject::ttObject() : mRefCount(0), mAutoRelease(false), mMetaData(false)
{
	setAutoRelease(true);
}

ttObject::~ttObject()
{

}

void ttObject::retain()
{
	if (mRefCount == 0 && mAutoRelease)
		ttMemoryManager::getInstance()->removeFromDeleteList(this);
	mRefCount ++;
}

void ttObject::release()
{
	if (mRefCount)
		mRefCount --;
	if (mRefCount == 0 && mAutoRelease)
		ttMemoryManager::getInstance()->addToDeleteList(this);
}

void ttObject::setAutoRelease(bool pAutoRelease)
{
	mAutoRelease = pAutoRelease;
	if (mRefCount == 0)
		if (mAutoRelease)
			ttMemoryManager::getInstance()->addToDeleteList(this);
		else
			ttMemoryManager::getInstance()->removeFromDeleteList(this);
}

bool ttObject::getAutoRelease() const
{
	return mAutoRelease;
}

void ttObject::setMetaData(ttObject* pData)
{
	if (pData)
		pData->retain();
	if (mMetaData)
		mMetaData->release();
	mMetaData = pData;		
}

ttObject* ttObject::getMetaData() const
{
	return mMetaData;
}

void ttObject::print(std::ostream& stream)
{
};