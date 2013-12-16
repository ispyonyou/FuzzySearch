#include "FuzzySearch.h"
#include <map>
#include <vector>
#include <iostream>
#include <algorithm>

class FuzzySearchPrivate
{
public:
  bool IsMatch( const std::string& searchInStr, const std::string& searchWhatStr, std::vector< unsigned int >& maxWeightSequence );

private:
  void findMatchedSequences();
  void appendNextLetter( std::vector< unsigned int >& accumulator );
  unsigned int calcWeight( const std::vector< unsigned int >& sequence );

private:
  std::map< char, std::vector< unsigned int > > LetterIndexes;
  std::string SearchWhatStr;
  std::vector< std::vector< unsigned int > > MatchedSequences;
};

bool FuzzySearchPrivate::IsMatch( const std::string& searchInStr, const std::string& searchWhatStr, std::vector< unsigned int >& maxWeightSequence )
{
  MatchedSequences.clear();
  LetterIndexes.clear();
  SearchWhatStr = searchWhatStr;

  for( unsigned int i = 0; i < searchInStr.size(); i++ )
  {
    for each( const char c in SearchWhatStr )
    {
      if( searchInStr[ i ] == c )
      {
        LetterIndexes[ c ].push_back( i );
        break;
      }

      if( searchInStr[ i ] == ' ' || searchInStr[ i ] == '\\' )
      {
        // all separators store as ' '
        LetterIndexes[ ' ' ].push_back( i );
        break;
      }
    }
  }

  for each( const char c in SearchWhatStr )
    if( LetterIndexes[ c ].empty() )
      return false;

  findMatchedSequences();

  if( !MatchedSequences.size() )
    return false;

  unsigned int maxWeight = 0;
  unsigned int maxWeightSeqIndex = 0;
  for( unsigned int i = 0; i < MatchedSequences.size(); i++ )
  {
    unsigned int weight = calcWeight( MatchedSequences[ i ] );
    if( weight > maxWeight )
    {
      maxWeight = weight;
      maxWeightSeqIndex = i;
    }
  }

  maxWeightSequence = MatchedSequences[ maxWeightSeqIndex ];

  return true;
}

void FuzzySearchPrivate::findMatchedSequences()
{
  std::vector< unsigned int > accumulator;
  appendNextLetter( accumulator );
}

void FuzzySearchPrivate::appendNextLetter( std::vector< unsigned int >& accumulator )
{
  _ASSERT( accumulator.size() < SearchWhatStr.length() );

  const char letter = SearchWhatStr[ accumulator.size() ];
  const std::vector< unsigned int >& curletterIndexes = LetterIndexes[ letter ];

  for( unsigned int i = 0; i < curletterIndexes.size(); i++ )
  {
    if( ( accumulator.size() > 0 ) && ( curletterIndexes[ i ] <= accumulator.back() ) )
      continue;

    if( accumulator.size() == SearchWhatStr.size() - 1 ) // last charcter in searching sequence
    {
      accumulator.push_back( curletterIndexes[ i ] );
      MatchedSequences.push_back( accumulator );
      accumulator.pop_back();

      continue;
    }

    accumulator.push_back( curletterIndexes[ i ] );
    appendNextLetter( accumulator );
    accumulator.pop_back();
  }
}

unsigned int FuzzySearchPrivate::calcWeight( const std::vector< unsigned int >& sequence )
{
  unsigned int weight = 0;
  const std::vector< unsigned int >& separatorIndexes = LetterIndexes[ ' ' ];

  for( unsigned int i = 0; i < sequence.size(); i++ )
  {
    unsigned int index = sequence[ i ];
    unsigned int prevIndex = i > 0 ? sequence[ i - 1 ] : -1;
    if( index == 0 )
    {
      weight += 2;
      continue;
    }

    if( prevIndex + 1 == index )
    {
      weight += 2;
      continue;
    }

    // if previous symbol is separator
    if( std::binary_search( separatorIndexes.begin(), separatorIndexes.end(), index - 1 ) )
    {
      weight += 2;
      continue;
    }
  }

  return weight;
}

FuzzySearch::FuzzySearch()
{
  d = new FuzzySearchPrivate();
}

FuzzySearch::~FuzzySearch()
{
  delete d;
}

bool FuzzySearch::IsMatch( const std::string& str, const std::string& searchStr, std::vector< unsigned int >& maxWeightSequence )
{
	std::string clearedSearchStr;
	for( unsigned int i = 0; i < searchStr.size(); i++ )
		if( searchStr[ i ] != ' ' && searchStr[ i ] != '\\' )
			clearedSearchStr += searchStr[ i ];

	if( clearedSearchStr.empty() )
		return true;

  std::string searchInStr = str;

  std::transform( searchInStr.begin(), searchInStr.end(), searchInStr.begin(), ::tolower );
  std::transform( clearedSearchStr.begin(), clearedSearchStr.end(), clearedSearchStr.begin(), ::tolower );

  return d->IsMatch( searchInStr, clearedSearchStr, maxWeightSequence );
}
