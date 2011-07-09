#pragma once
#ifndef ttFILEIOMANAGER_H_
#define ttFILEIOMANAGER_H_

#include <fstream>
#include <map>
#include <vector>
#include <list>
#include <stack>

#include "ttObject.h"
#include "ttObjectPool.h"


namespace TranslationTools
{
	class ttFileIManager 
	{
		char* mDataBuffer;
		std::map<ttObject*, int> mObjectDictionary;
		std::vector<std::pair<std::list<std::pair<unsigned,unsigned> > ,ttObject*> > mNewedMemmory;
		std::stack<unsigned> mLoadStack;
		const int inheritebit;
	public:
		ttFileIManager() : mDataBuffer(NULL) , inheritebit(1<<31)
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
				mObjectDictionary[x] = i;
				std::pair<unsigned,unsigned> temp;
				do
				{
					s.read((char*)&temp.second,4);
					temp.first = totalDataSize;
					totalDataSize += temp.second & ~inheritebit;
					mNewedMemmory[i].first.push_back(temp);
					mNewedMemmory[i].first.back().second &= ~inheritebit;
					mNewedMemmory[i].second = NULL;
				}
				while((temp.second & inheritebit) != 0);
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
			memcpy(&rttiSize,mDataBuffer + mNewedMemmory[i].first.begin()->first,4);
			rtti.load(mDataBuffer + mNewedMemmory[i].first.begin()->first + 4,rttiSize);
			const ttObject* sample = ttObjectPool::getInstance()->getObjectSample(rtti);
			
			ttObject* result = sample->clone();
			mNewedMemmory[i].second = result;
			mLoadStack.push(i);
			result->load(*this,mDataBuffer + mNewedMemmory[i].first.begin()->first + 4 + rttiSize,mNewedMemmory[i].first.begin()->second - 4 - rttiSize);
			mLoadStack.pop();
			return result;
		}


		template <class T> typename std::enable_if<std::is_base_of<ttObject,T>::value, void >::type loadParent()
		{
			ttRTTI targetRTTI = T::getStaticTypeInfo();
			list<pair<unsigned,unsigned> >::iterator hierarchyList = mNewedMemmory[mLoadStack.top()].first.begin();
			while (hierarchyList != mNewedMemmory[mLoadStack.top()].first.end())
			{
				ttRTTI rtti;
				unsigned rttiSize;
				memcpy(&rttiSize,mDataBuffer + hierarchyList->first,4);
				rtti.load(mDataBuffer + hierarchyList->first + 4,rttiSize);
				if (rtti == targetRTTI)
				{
					mNewedMemmory[mLoadStack.top()].second->T::load(*this,mDataBuffer + hierarchyList->first + 4 + rttiSize,hierarchyList->second - 4 - rttiSize);
					return;
				}
				hierarchyList++;
			}
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