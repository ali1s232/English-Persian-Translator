#pragma once
#ifndef ttOBJECTPOOL_H_
#define ttOBJECTPOOL_H_
#include <string>
#include <map>
#include <memory.h>

namespace TranslationTools
{
	class ttObject;
	class ttRTTI
	{
	protected:
		std::string type;
	public:
		ttRTTI(){};
		ttRTTI(const char*pName) : type(pName) {};
		void load(void* pData,int size){type.assign((char*)pData);}
		void save(void* pTarget){memcpy(pTarget,type.c_str(),type.length()+1);}
		bool operator < (const ttRTTI& pRight) const {return type < pRight.type;}
		bool operator == (const ttRTTI& pRight) const {return type == pRight.type;}
		bool operator != (const ttRTTI& pRight) const {return type != pRight.type;}
		inline unsigned size(){return type.length() + 1;};
	};

	class ttObjectPool
	{
		std::map <ttRTTI, ttObject*> objectSamples;
		static ttObjectPool* instance;
	public:
		inline static ttObjectPool* getInstance(){return (instance)?instance:instance=new ttObjectPool;}
		void registerNewSample(ttObject* sample);
		const ttObject* getObjectSample(ttRTTI&)const;
	};
};

#endif