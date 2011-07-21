#include "ttObject.h"
#include "ttMemoryManager.h"
#include "ttObjectPool.h"

using namespace std;
using namespace TranslationTools;

ttImplementRTTI(ttObject);
//struct ttObjectIntoducer{ttObjectIntoducer(){TranslationTools::ttObjectPool::getInstance()->registerNewSample(new ttObject);}}ttObjectIntroducerVariable;

ttObject::ttObject() : mRefCount(0), mAutoRelease(false)
{
	setAutoRelease(true);
}

ttObject::ttObject(const ttObject& pObject) : mRefCount(0), mAutoRelease(pObject.mAutoRelease)
{
	for(map <ttRTTI,ttObject*>::const_iterator i = pObject.mMetaData.cbegin();i!=pObject.mMetaData.cend();i++)
		attachMetaData(i->second);
}

ttObject::~ttObject()
{
	for (map<ttRTTI,ttObject*> ::iterator i=mMetaData.begin(); i != mMetaData.end();i++)
		i->second->release();
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
	{
		if (mAutoRelease)
			ttMemoryManager::getInstance()->addToDeleteList(this);
		else
			ttMemoryManager::getInstance()->removeFromDeleteList(this);
	}
}

bool ttObject::getAutoRelease() const
{
	return mAutoRelease;
}

void ttObject::attachMetaData(ttObject* pData)
{
	std::map<ttRTTI, ttObject*>::iterator temp = mMetaData.find(pData->getTypeInfo());
	if (temp == mMetaData.end())
	{
		pData->retain();
		mMetaData[pData->getTypeInfo()] = pData;
	}
	else
		if(temp->second != pData)
		{
			temp->second->release();
			pData->retain();
			mMetaData[pData->getTypeInfo()] = pData;
		}
}

ttObject* ttObject::getMetaData(const ttRTTI& t)
{
	if (mMetaData.find(t) != mMetaData.end())
		return mMetaData[t];
	else
		return NULL;
}

void ttObject::detachMetaData(const ttRTTI& t)
{
	std::map<ttRTTI, ttObject*>::iterator temp = mMetaData.find(t);
	if (temp != mMetaData.end())
	{
		temp->second->release();
		mMetaData.erase(temp);
	}
}

void ttObject::detachAllMetaData()
{
	while (mMetaData.size())
		detachMetaData(mMetaData.begin()->first);
}

void ttObject::save(ttFileOManager& pFileManager,void* pBuffer)const
{
	ttObject** target = (ttObject**)pBuffer;
	for(map<ttRTTI,ttObject*>::const_iterator i = mMetaData.cbegin();i!=mMetaData.cend();i++)
	{
		pFileManager.addObject(i->second);
		*target=i->second;
		target ++;
	}

}

void ttObject::load(ttFileIManager& pFileManager,void* pBuffer,int pBufferSize)
{
	detachAllMetaData();
	int objectNum = pBufferSize / 4;
	ttObject** meta = (ttObject**)pBuffer;
	for(int i=0;i<objectNum;i++)
		this->attachMetaData(pFileManager.renewPointer(meta[i]));
}

int ttObject::size() const
{
	return mMetaData.size() * 4;
}

ttObject* ttObject::clone() const
{
	ttObject* result = new ttObject;
	new (result)ttObject(*this);
	return result;
}

bool ttObject::operator == (const ttObject& pRight) const
{
	if (getTypeInfo() != pRight.getTypeInfo())
		return false;
	if (mMetaData.size() != pRight.mMetaData.size())
		return false;
	map<ttRTTI, ttObject*>::const_iterator i = mMetaData.cbegin();
	map<ttRTTI, ttObject*>::const_iterator j = pRight.mMetaData.cbegin();
	for(; i!=mMetaData.cend() && j!=pRight.mMetaData.cend();i++,j++)
		if (i->first != j->first)
			return false;
		else
			if(i->second != j->second)
				if(!i->second->operator==(*j->second))
					return false;
	return true;
}

void ttObject::print(std::ostream& stream)
{
};
