#include "ttObjectPool.h"
#include "ttObject.h"

using namespace std;
using namespace TranslationTools;

ttObjectPool* ttObjectPool::instance = NULL;

void ttObjectPool::registerNewSample(ttObject* obj) 
{
	ttRTTI sampleType = obj->getTypeInfo();
	if (objectSamples.find(sampleType) == objectSamples.end())
		objectSamples[sampleType] = obj;
}

const ttObject* ttObjectPool::getObjectSample(ttRTTI& sampleRTTI) const
{
	if (objectSamples.find(sampleRTTI) != objectSamples.end())
		return objectSamples.find(sampleRTTI)->second;
	else
		return NULL;
}