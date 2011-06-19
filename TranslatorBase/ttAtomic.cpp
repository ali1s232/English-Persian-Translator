#include "ttAtomic.h"

using namespace std;
using namespace TranslationTools;

ttAtomic::ttAtomic(ttAtomic::wordType pWord): word(pWord)
{

}

void ttAtomic::print(ostream& stream)
{
	stream << word;
}

ostream& operator <<(ostream& stream,ttAtomic::wordType w)
{
	char* target = (char*)w.c_str();
	for (unsigned i=0;i<w.length();i++,target += 2)
		stream .put(target[0]).put(target[1]);
	return stream;
}