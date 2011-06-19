#pragma once

#ifndef ttPARSER_H_
#define ttPARSER_H_

#include "ttNode.h"
#include "ttAtomic.h"

namespace TranslationTools
{

class ttParser
{
protected:
	ttNode* root;
public:
	void parse(ttAtomic::wordType script);
	
};

}

#endif