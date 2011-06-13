#include "tlAtomic.h"

using namespace std;

tlAtomic::tlAtomic(tlAtomic::wordType pWord): word(pWord)
{

}

void tlAtomic::print(ostream& stream)
{
	stream << word;
}

ostream& operator <<(ostream& stream,tlAtomic::wordType w)
{
	char* target = (char*)w.c_str();
	for (unsigned i=0;i<w.length();i++,target += 2)
		stream .put(target[0]).put(target[1]);
	return stream;
}