#include "ttNode.h"

using namespace std;
using namespace TranslationTools;

ttNode::ttNode()
{

}

ttNode::ttNode(ttObject* first, ...)
{
	while (first)
	{
		first->retain();
		children.push_back(first);
		first ++;
	}
}

void ttNode::attachChild(ttObject* pEntry,int pos)
{
	pEntry->retain();
	if (pos < 0 || pos >= (int)children.size())
		children.push_back(pEntry);
	else
		children.insert(children.begin()+pos,pEntry);
}

void ttNode::removeChild(int pos)
{
	if (pos>=0 && pos < (int)children.size())
	{
		children[pos]->release();
		children.erase(children.begin()+pos);
	}
}

void ttNode::print(ostream& stream)
{
	for(unsigned i=0;i<children.size()-1;i++)
	{
		children[i]->print(stream);
		stream << ' ' << '\0';
	}
	children.back()->print(stream);
}