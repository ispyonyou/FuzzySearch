#include <string>

class FuzzySearch
{
public:
	static bool IsMatch( const std::string& str, const std::string& searchStr, long& weight );
};
