#include "PersianParser.h"
#include <vector>
#include <iostream>

using namespace std;
using namespace TranslationTools;

void explode(const ttWord::wordType& input,const ttWord::wordType& delims, vector<ttWord::wordType>& output)
{
	unsigned last = 0;
	for (unsigned i=0;i<input.size();i++)
		if (delims.find(input[i]) != ttWord::wordType::npos)
		{
			if (i - last > 0)
				output.push_back(ttWord::wordType(input.c_str() + last ,i - last ));
			last = i + 1;
		}
	if (input.size() - last > 0)
		output.push_back(ttWord::wordType(input.c_str() + last,input.size() - last));
};

PersianParser::PersianParser(void)
{
}

TranslationTools::ttArray* PersianParser::parse(TranslationTools::ttWord::wordType script)
{
	//script = towlower(script)
	for(unsigned i=0;i<script.size();i++)
		script[i] = towlower(script[i]);
	vector<ttWord::wordType> paragraphs;
	explode(script,L"\n",paragraphs);
	for(unsigned i=0;i<paragraphs.size();i++)
	{
		vector<ttWord::wordType> senteces;
		explode(paragraphs[i],L".;!?,",senteces);
		wcout << L"Paragraph " << i << " : \n";
		for(unsigned j=0;j<senteces.size();j++)
			wcout << L"Sentence " << j << " : " << senteces[j] << "\n";
	}
	return NULL;
}

TranslationTools::ttWord::wordType PersianParser::translate(TranslationTools::ttArray* pRoot)
{
	return L"";
}

PersianParser::~PersianParser(void)
{
}
