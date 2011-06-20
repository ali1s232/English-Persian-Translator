#pragma once
#ifndef ttOBJECT_H_
#define ttOBJECT_H_
#include "ttMacros.h"
#include "ttFileIOManager.h"
#include <ostream>
#include <map>

namespace TranslationTools
{
	class ttObject
	{
	public:
		/*struct typeinfo
		{
		private :
			
		public:
			typeinfo(){};
			typeinfo(typeinfo& pInfo){};
			bool operator == (const typeinfo& right) {return this == &right;};
			bool operator != (const typeinfo& right) {return this == &right;};
			bool operator < (typeinfo right) const {return ((unsigned)this) < ((unsigned)&right);}
			template <class T> static typeinfo& get(T& data=T())
			{
				static struct derieved:public typeinfo {} t;
				return t;
			}
			
		};*/
		
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
		};
		unsigned mRefCount;
		std::map<typeinfowrapper, ttObject*> mMetaData;
	public:
		ttObject();
		virtual ~ttObject ();

		void retain();
		void release();
		ttPROPERTY_NODEF(bool ,AutoRelease);
		void attachMetaData(ttObject* pData);
		template <class T> inline typename std::enable_if<std::is_base_of<ttObject,T>::value,T*>::type getMetaData()
		{
			if (mMetaData.find(typeid(T)) != mMetaData.end())
				return (T*)mMetaData[typeid(T)];
			else
				return NULL;
		}
		template <class T> inline typename std::enable_if<std::is_base_of<ttObject,T>::value,void>::type detachMetaData()
		{
			std::map<typeinfowrapper, ttObject*>::iterator temp = mMetaData.find(typeid(T));
			if (temp != mMetaData.end())
			{
				temp->second->release();
				mMetaData.erase(temp);
			}
		}
		virtual void print(std::ostream& stream);
		virtual void save(ttFileIOManager& buffer){};
		virtual void load(ttFileIOManager& buffer){};
		virtual int getSize() {return 0;};
	};
}

//bool operator < (const TranslationTools::ttObject::typeinfo& left, const TranslationTools::ttObject::typeinfo& right){return ((unsigned) &left) < ((unsigned) &right);};

#endif