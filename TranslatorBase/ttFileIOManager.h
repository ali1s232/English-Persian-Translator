#pragma once
#ifndef ttFILEIOMANAGER_H_
#define ttFILEIOMANAGER_H_

#include <fstream>
#include <map>
#include <vector>
#include "ttObject.h"
#include "ttObjectPool.h"

namespace TranslationTools
{
	class ttFileIManager 
	{
		char* mDataBuffer;
		std::map<ttObject*, int> mObjectDictionary;
		std::vector<std::pair<std::pair<unsigned,unsigned> ,ttObject*> > mNewedMemmory;
	public:
		ttFileIManager() : mDataBuffer(NULL) 
		{
		
		}

		ttObject* initializeLoad(const char* pPath)
		{
			std::ifstream s(pPath,std::ios::binary);
			s.seekg(std::ios::beg);
			unsigned objectNum;
			s.read((char*)&objectNum,4);
			unsigned totalDataSize = 0;
			ttObject* root;
			mNewedMemmory.resize(objectNum);
			for (unsigned i=0;i<objectNum;i++)
			{
				ttObject* x;
				s.read((char*)&x,4);
				if (i == 0)
					root = x;
				s.read((char*)&mNewedMemmory[i].first.second,4);
				mObjectDictionary[x] = i;
				mNewedMemmory[i].first.first = totalDataSize;
				mNewedMemmory[i].second = NULL;
				totalDataSize += mNewedMemmory[i].first.second;
			}
			mDataBuffer = new char[totalDataSize];
			//for(unsigned i=0;i<objectNum;i++)
			s.read(mDataBuffer, totalDataSize);
			root = renewPointer(root);
			delete []mDataBuffer;
			mNewedMemmory.clear();
			mObjectDictionary.clear();
			return root;
		}

		template <class T> typename std::enable_if<std::is_base_of<ttObject,T>::value, T* >::type renewPointer(T* pOld)
		{
			if (mObjectDictionary.find(pOld) == mObjectDictionary.end())
				return NULL;
			int i = mObjectDictionary[pOld];
			if (mNewedMemmory[i].second)
				return dynamic_cast<T*>(mNewedMemmory[i].second);
			ttRTTI rtti;
			unsigned rttiSize;
			memcpy(&rttiSize,mDataBuffer + mNewedMemmory[i].first.first,4);
			rtti.load(mDataBuffer + mNewedMemmory[i].first.first + 4,rttiSize);
			ttObject* result = ttObjectPool::getInstance()->getObjectSample(rtti)->clone();
			mNewedMemmory[i].second = result;
			result->load(*this,mDataBuffer + mNewedMemmory[i].first.first + 4 + rttiSize,mNewedMemmory[i].first.second - 4 - rttiSize);
			return result;
		}

	};

	class ttFileOMAnager
	{
		
	public:
		void initializeSave(const char* pPath){};
		template <class T> void addObject(T* object){};
		void flush(){};
	};

}

#endif