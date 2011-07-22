#include "ttBasicWordInformation.h"

using namespace std;
using namespace TranslationTools;

ttImplementRTTI(ttWordID);
ttImplementRTTI(ttWordType);
ttImplementRTTI(ttPhraseRole);

void ttWordID::save(ttFileOManager& buffer,void*target)const
{
	buffer.saveParent<ttObject>();
	*(int*)target = mID;
}

void ttWordID::load(ttFileIManager& buffer,void*origin,int)
{
	buffer.loadParent<ttObject>();
	mID = *(int*)origin;
}

int ttWordID::size() const
{
	return sizeof(int);
}

ttObject* ttWordID::clone()const
{
	return new ttWordID(*this);
}

void ttWordType::save(ttFileOManager& buffer,void*target)const
{
	buffer.saveParent<ttObject>();
	*(WordType*)target = mType;
}

void ttWordType::load(ttFileIManager& buffer,void*origin,int)
{
	buffer.loadParent<ttObject>();
	mType = *(WordType*)origin;
}

int ttWordType::size() const
{
	return sizeof(WordType);
}

ttObject* ttWordType::clone()const
{
	return new ttWordType(*this);
}

void ttPhraseRole::save(ttFileOManager& buffer,void*target)const
{
	buffer.saveParent<ttObject>();
	*(PhraseRole*)target = mRole;
}

void ttPhraseRole::load(ttFileIManager& buffer,void*origin,int)
{
	buffer.loadParent<ttObject>();
	mRole = *(PhraseRole*)origin;
}

int ttPhraseRole::size() const
{
	return sizeof(PhraseRole);
}

ttObject* ttPhraseRole::clone()const
{
	return new ttPhraseRole(*this);
}
