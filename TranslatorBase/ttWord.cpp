#include "ttWord.h"

using namespace std;
using namespace TranslationTools;

ttImplementRTTI(ttWord);

ttWord::ttWord(ttWord::wordType pWord): mWord(pWord)
{
//	abjad.i = 5;
}

ttWord::ttWord(const ttWord& input) : ttObject(*this), mWord(input.mWord)
{
}

void ttWord::print(ostream& stream)
{
	stream << mWord;
}

//void ttWord::save(ttFileOManager& buffer,void*){};
void ttWord::load(ttFileIManager& buffer,void* data,int size)
{
	buffer.loadParent<ttObject>();
	mWord.assign((wchar_t*)data,size);
}
//int ttWord::size() { return 0;};
ttObject* ttWord::clone() const
{
	ttWord* result = new ttWord;
	new (result)ttWord(*this);
	return result;
}

ostream& operator <<(ostream& stream,ttWord::wordType w)
{
	char* target = (char*)w.c_str();
	for (unsigned i=0;i<w.length();i++,target += 2)
		stream .put(target[0]).put(target[1]);
	return stream;
}