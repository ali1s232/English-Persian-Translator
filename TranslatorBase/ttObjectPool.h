#pragma once
#ifndef ttOBJECTPOOL_H_
#define ttOBJECTPOOL_H_
#include <string>
#include <map>
#include <memory.h>

namespace TranslationTools
{
	class ttObject;
	class ttRTTI;

	class ttObjectPool
	{
		std::map <ttRTTI, ttObject*> objectSamples;
		static ttObjectPool* instance;
	public:
		inline static ttObjectPool* getInstance(){return (instance)?instance:instance=new ttObjectPool;}
		void registerNewSample(ttObject* sample);
		const ttObject* getObjectSample(ttRTTI&)const;
	};

	class ttRTTI
	{
	protected:
		std::string type;
	public:
		ttRTTI(){};
		ttRTTI(ttObject*sample, const char* name) : type(name) {	
			TranslationTools::ttObjectPool::getInstance()->registerNewSample(sample);
		};
		void load(void* pData,int size){type.assign((char*)pData);}
		void save(void* pTarget) const {memcpy(pTarget,type.c_str(),type.length()+1);}
		bool operator < (const ttRTTI& pRight) const {return type < pRight.type;}
		bool operator == (const ttRTTI& pRight) const {return type == pRight.type;}
		bool operator != (const ttRTTI& pRight) const {return type != pRight.type;}
		inline unsigned size() const{return type.length() + 1;};
	};


	struct ttObjectIntroducer
	{
		ttObjectIntroducer(ttObject* obj)
		{
		}
	};

};

#endif