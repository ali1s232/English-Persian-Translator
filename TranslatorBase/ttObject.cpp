#include "ttObject.h"
#include "ttMemoryManager.h"

using namespace TranslationTools;

ttObject::ttObject() : mRefCount(0), mAutoRelease(false)
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

void ttObject::attachMetaData(ttObject* pData)
{
	std::map<typeinfowrapper, ttObject*>::iterator temp = mMetaData.find(typeid(*pData));
	if (temp == mMetaData.end())
	{
		pData->retain();
		mMetaData[typeid(*pData)] = pData;
	}
	else
		if(temp->second != pData)
		{
			temp->second->release();
			pData->retain();
			mMetaData[typeid(*pData)] = pData;
		}
}

void ttObject::print(std::ostream& stream)
{
};