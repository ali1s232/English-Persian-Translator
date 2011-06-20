#include "ttWord.h"

using namespace std;
using namespace TranslationTools;

ttWord::ttWord(ttWord::wordType pWord): word(pWord)
{

}

void ttWord::print(ostream& stream)
{
	stream << word;
}

ostream& operator <<(ostream& stream,ttWord::wordType w)
{
	char* target = (char*)w.c_str();
	for (unsigned i=0;i<w.length();i++,target += 2)
		stream .put(target[0]).put(target[1]);
	return stream;
}