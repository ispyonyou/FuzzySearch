#include <string>
#include <vector>

class FuzzySearchPrivate;

class FuzzySearch
{
public:
  FuzzySearch();
  ~FuzzySearch();

	bool IsMatch( const std::string& str, const std::string& searchStr, std::vector< unsigned int >& maxWeightSequence );

private:
  FuzzySearchPrivate* d;
};
