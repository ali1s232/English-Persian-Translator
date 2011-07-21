#pragma once
#ifndef ttOBJECT_H_
#define ttOBJECT_H_
#include "ttMacros.h"
#include <ostream>
#include <map>
#include "ttObjectPool.h"

namespace TranslationTools
{
	class ttFileIManager;
	class ttFileOManager;
	class ttObject
	{
		ttDeclareRTTI;
	protected:
		unsigned mRefCount;
		std::map<ttRTTI, ttObject*> mMetaData;
	public:
		ttPROPERTY_NODEF(bool ,AutoRelease);

		ttObject();
		ttObject(const ttObject&);
		virtual ~ttObject ();

		void retain();
		void release();

		void attachMetaData(ttObject* pData);
		ttObject* getMetaData(const ttRTTI& t);
		void detachMetaData(const ttRTTI& t);
		void detachAllMetaData();
		template <class T> inline typename std::enable_if<std::is_base_of<ttObject,T>::value,T*>::type getMetaData()
		{
			return (T*)getMetaData(T::getStaticTypeInfo());
		}
		template <class T> inline typename std::enable_if<std::is_base_of<ttObject,T>::value,void>::type detachMetaData()
		{
			detachMetaData(T::getStaticTypeInfo());
		}
		
		virtual void print(std::ostream& stream);
		virtual void save(ttFileOManager& buffer,void*)const;
		virtual void load(ttFileIManager& buffer,void*,int);
		virtual int size() const;
		virtual ttObject* clone()const;
		virtual bool operator == (const ttObject& pRight) const;
		inline bool operator != (const ttObject& pRight) const
		{
			return !(*this==pRight);
		}
	};
}

#include "ttFileIOManager.h"


#endif