#pragma once
#ifndef ttOBJECT_H_
#define ttOBJECT_H_
#include "ttMacros.h"
#include <ostream>

namespace TranslationTools
{
	class ttObject
	{
		unsigned mRefCount;
	public:
		ttObject();
		virtual ~ttObject ();

		void retain();
		void release();
		ttPROPERTY_NODEF(bool ,AutoRelease);
		ttPROPERTY_NODEF(ttObject*,MetaData);
		virtual void print(std::ostream& stream);
	};
}

#endif