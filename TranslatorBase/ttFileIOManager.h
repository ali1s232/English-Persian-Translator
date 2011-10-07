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
#define TTFILEMANAGER_INHERITENBIT (1<<31)

namespace TranslationTools
{
	class ttFileIManager 
	{
		char* mDataBuffer;
		std::map<ttObject*, int> mObjectDictionary;
		std::vector<std::pair<std::list<std::pair<unsigned,unsigned> > ,ttObject*> > mNewedMemmory;
		std::stack<unsigned> mLoadStack;
	public:
		ttFileIManager() : mDataBuffer(NULL)
		{
		
		}

		~ttFileIManager()
		{
			delete []mDataBuffer;
		}

		void clear()
		{
			if (mDataBuffer)
				delete []mDataBuffer;
			mDataBuffer = NULL;
			mNewedMemmory.clear();
			mObjectDictionary.clear();
		}

		ttObject* initializeLoad(const char* pPath)
		{
			clear();
			std::ifstream s(pPath,std::ios::binary);
			if (!s.is_open())
				return NULL;
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
					totalDataSize += temp.second & ~TTFILEMANAGER_INHERITENBIT;
					mNewedMemmory[i].first.push_back(temp);
					mNewedMemmory[i].first.back().second &= ~TTFILEMANAGER_INHERITENBIT;
					mNewedMemmory[i].second = NULL;
				}
				while((temp.second & TTFILEMANAGER_INHERITENBIT) != 0);
			}
			mDataBuffer = new char[totalDataSize];
			s.read(mDataBuffer, totalDataSize);
			root = renewPointer(root);
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
			std::list<std::pair<unsigned,unsigned> >::iterator hierarchyList = mNewedMemmory[mLoadStack.top()].first.begin();
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

	class ttFileOManager
	{
		std::map<ttObject*, int> mObjectDictionary;
		std::vector<std::pair<std::list<std::pair<unsigned,char*> > ,ttObject*> > mMemmory;
		std::stack<unsigned> mSaveStack;
	public:
		~ttFileOManager()
		{
			clear();
		}
		void clear()
		{
			for(unsigned i=0;i<mMemmory.size();i++)
				for(std::list<std::pair<unsigned,char*> >::iterator j = mMemmory[i].first.begin();j!=mMemmory[i].first.end();j++)
					delete []j->second;
			mObjectDictionary.clear();
			mMemmory.clear();
		}
		void initializeSave(ttObject* obj)
		{
			clear();
			addObject(obj);
		};
		void addObject(ttObject* object)
		{
			if (mObjectDictionary.find(object) != mObjectDictionary.end())
				return;
			const ttRTTI rtti = object->getTypeInfo();
			int objSize = object->size();
			if (objSize < 0)
				return;
			mMemmory.resize(mMemmory.size() + 1);
			mMemmory.back().second = object;
			int rttiSize = rtti.size();
			mMemmory.back().first.push_back(std::pair<unsigned,char*> (objSize + rttiSize + 4,new char[objSize + rttiSize + 4]));
			memcpy(mMemmory.back().first.back().second,&rttiSize,4);
			rtti.save(mMemmory.back().first.back().second + 4);
			mSaveStack.push(mMemmory.size() - 1);
			object->save(*this,mMemmory.back().first.back().second + rttiSize + 4);
			mSaveStack.pop();
		};
		template <class T> typename std::enable_if<std::is_base_of<ttObject,T>::value, void>::type saveParent()
		{
			ttRTTI rtti = T::getStaticTypeInfo();
			for(std::list<std::pair<unsigned,char*> >::iterator i = mMemmory[mSaveStack.top()].first.begin(); i != mMemmory[mSaveStack.top()].first.end();i++)
			{
				ttRTTI tempRTTI;
				tempRTTI.load(i->second,i->first);
				if(tempRTTI == rtti)
					return;
			}
			mMemmory[mSaveStack.top()].first.back().first |= TTFILEMANAGER_INHERITENBIT;
			int size = mMemmory[mSaveStack.top()].second->T::size();
			int rttiSize = rtti.size();
			mMemmory[mSaveStack.top()].first.push_back(std::pair<unsigned,char*>(size + rttiSize + 4,new char[size + rttiSize + 4]));
			memcpy(mMemmory.back().first.back().second,&rttiSize,4);
			rtti.save(mMemmory[mSaveStack.top()].first.back().second + 4);
			mMemmory[mSaveStack.top()].second->T::save(*this,mMemmory[mSaveStack.top()].first.back().second + rttiSize + 4);
		};
		bool flush(const char* pPath)
		{
			std::ofstream out(pPath,std::ios::binary);
			if (!out.is_open())
				return false;
			int objNum = mMemmory.size();
			out.write((char*)&objNum,4);
			for(int i=0;i<objNum;i++)
			{
				out.write((char*)&mMemmory[i].second,4);
				for(std::list<std::pair<unsigned,char*> >::iterator j = mMemmory[i].first.begin(); j != mMemmory[i].first.end();j++)	
					out.write((char*)&j->first,4);
			}
			for(int i=0;i<objNum;i++)
				for(std::list<std::pair<unsigned,char*> >::iterator j = mMemmory[i].first.begin(); j != mMemmory[i].first.end();j++)	
					out.write(j->second,j->first & ~TTFILEMANAGER_INHERITENBIT);
			out.flush();
			out.close();
			return true;
		}
	};

}

#endif
