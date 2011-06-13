#pragma once
#ifndef TLOBJECT_H_
#define TLOBJECT_H_
#include "tlMacros.h"
#include <ostream>

class tlObject
{
	unsigned refCount;
public:
	tlObject();
	virtual ~tlObject ();

	void retain();
	void release();
	tlPROPERTY_NODEF(bool,AutoRelease);
	virtual void print(std::ostream& stream);
};

#endif