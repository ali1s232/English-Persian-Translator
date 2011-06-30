#pragma once
#ifndef ttOBJECT_H_
#define ttOBJECT_H_
#include "ttMacros.h"
#include <ostream>
#include <map>

namespace TranslationTools
{
	class ttFileIManager;
	class ttFileOManager;
	class ttObject
	{
		ttDeclareRTTI;
	protected:
		struct typeinfowrapper
		{
		private :
			const std::type_info& info;
		public:
			typeinfowrapper() : info(typeid(void))
			{
			}
			typeinfowrapper(const std::type_info& pInfo) : info (pInfo)
			{
			}

			bool operator == (const typeinfowrapper& right) const {return info == right.info;}
			bool operator < (const typeinfowrapper& right) const {return strcmp(info.name(),right.info.name()) < 0;};
			operator const std::type_info&(){return info;};
		};
		unsigned mRefCount;
		std::map<typeinfowrapper, ttObject*> mMetaData;
	public:
		ttPROPERTY_NODEF(bool ,AutoRelease);

		ttObject();
		ttObject(const ttObject&);
		virtual ~ttObject ();

		void retain();
		void release();

		void attachMetaData(ttObject* pData);
		ttObject* getMetaData(const std::type_info& t);
		void detachMetaData(const std::type_info& t);
		void detachAllMetaData();
		template <class T> inline typename std::enable_if<std::is_base_of<ttObject,T>::value,T*>::type getMetaData()
		{
			return (T*)getMetaData(typeid(T));
		}
		template <class T> inline typename std::enable_if<std::is_base_of<ttObject,T>::value,void>::type detachMetaData()
		{
			detachMetaData(typeid(T));
		}
		
		virtual void print(std::ostream& stream);
		virtual void save(ttFileOManager& buffer,void*){};
		virtual void load(ttFileIManager& buffer,void*,int);
		virtual int size() {return 0;};
		virtual ttObject* clone()const;
	};
}

#include "ttFileIOManager.h"


#endif