// SourceLine class member-function definitions.

#include <iostream>
using std::cout;

#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine() : sourceLine()
{
}

void SourceLine::assign( const char *s, size_t n )
{
   sourceLine.assign( s, n );
}

void SourceLine::delComments()
{
	size_t pos = sourceLine.find('/', 0);

	while (sourceLine[pos + 1] != '/' && pos != npos)
		pos = sourceLine.find('/', pos+1);
	if (pos == npos)
		return;
	sourceLine.erase(pos, sourceLine.size());
}// delete the comment beginning with "//" in sourceLine
void SourceLine::delStrConst()
{
	while (sourceLine.find('"', 0) != npos)
	{
		size_t start = sourceLine.find('"', 0);
		size_t end = sourceLine.find('"', start + 1);
		sourceLine.erase(start, end - start + 1);
	}

} // deletes all string constants from sourceLine
void SourceLine::delCharConst()
{
	while (sourceLine.find('\'', 0) != npos)
	{
		size_t start = sourceLine.find('\'', 0);
		//size_t end = sourceLine.find('\'', start + 1);
		sourceLine.erase(start, 3);
	}
}// deletes all character constants from sourceLine

					 // delete the first identifier from sourceLine, and then return the identifier
string SourceLine::delFirstIdentifier()
{
	string str;
	if (sourceLine.size() == 0)
		return str;
	size_t start = 0;
	while (!((sourceLine[start]  >= 'A' && sourceLine[start] <= 'Z') || (sourceLine[start] >= 'a' && sourceLine[start] <= 'z')) && start < sourceLine.size())
		start++;

	size_t end = start;
	while (((sourceLine[end] >= '0' && sourceLine[end] <= '9') || (sourceLine[end] >= 'A' && sourceLine[end] <= 'Z') || (sourceLine[end] >= 'a' && sourceLine[end] <= 'z') || sourceLine[end] == '_' || sourceLine[end] == '.') && end < sourceLine.size())
		end++;

	// check. If pattern is a object trying to use member data
	str = sourceLine.substr(start, end - start);
	for (size_t i = 0; i < str.size(); i++)
		if (str[i] == '.') {
			str = str.substr(i + 1, str.size() - i - 1);
			break;
		}
	sourceLine.erase(0, end);
	return str;
}