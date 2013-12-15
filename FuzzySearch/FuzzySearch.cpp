#include "FuzzySearch.h"
#include <map>
#include <vector>
#include <memory>

class IndexesTreeItem
{
public:
	unsigned int Index;
	std::vector< std::shared_ptr< IndexesTreeItem > > Childs;

public:
	bool initChilds( unsigned int lettreNum, const std::string& search );
};

bool IndexesTreeItem::initChilds( unsigned int lettreNum, const std::string& search )
{
	char c = search[ lettreNum ];

	return true;
}

class IndexesTreeCreator
{
public:
	bool createIndexesTree( const std::string& str, const std::string& searchStr );

private:
	bool initChildIndexes( IndexesTreeItem& item, unsigned int searchLetterIndex );

private:
	std::string SearcStr;
	std::map< char, std::vector< unsigned int > > SearchLetterIndexes;
};

bool IndexesTreeCreator::createIndexesTree( const std::string& str, const std::string& searchStr )
{
	SearchLetterIndexes.clear();
	SearcStr = searchStr;

	for( unsigned int i = 0; i < str.size(); i++ )
	{
		for each( const char c in SearcStr )
		{
			if( str[ i ] == c )
			{
				SearchLetterIndexes[ c ].push_back( i );
				break;
			}
		}
	}

	for each( const char c in SearcStr )
		if( SearchLetterIndexes[ c ].empty() )
			return false;

	IndexesTreeItem root;
	root.Index = -1;
	
	if( !initChildIndexes( root, 0 ) )
		return false;

	return true;
}

bool IndexesTreeCreator::initChildIndexes( IndexesTreeItem& item, unsigned int searchLetterIndex )
{
	const char letter = SearcStr[ searchLetterIndex ];
	const std::vector< unsigned int >& letterIndexes = SearchLetterIndexes[ letter ];

	for( unsigned int i = 0; i < letterIndexes.size(); i++ )
	{
		if( letterIndexes[ i ] <= item.Index )
			continue;

		std::shared_ptr< IndexesTreeItem > child( new IndexesTreeItem() );
		child->Index = letterIndexes[ i ];

		if( searchLetterIndex == SearcStr.size() - 1 )
		{
			item.Childs.push_back( child );
			continue;
		}

		if( initChildIndexes( *child.get(), searchLetterIndex + 1 ) )
			item.Childs.push_back( child );
	}

	return ( item.Childs.size() > 0 );
}

bool FuzzySearch::IsMatch( const std::string& str, const std::string& searchStr, long& weight )
{
	std::string clearedSearchStr;
	for( unsigned int i = 0; i < searchStr.size(); i++ )
		if( searchStr[ i ] != ' ' && searchStr[ i ] != '\\' )
			clearedSearchStr += searchStr[ i ];

	if( clearedSearchStr.empty() )
		return true;

	IndexesTreeCreator().createIndexesTree( str, clearedSearchStr );

	std::map< char, std::vector< unsigned int > > searchLetterIndexes;
	for( unsigned int i = 0; i < str.size(); i++ )
	{
		for each( const char c in clearedSearchStr )
		{
			if( str[ i ] == c )
			{
				searchLetterIndexes[ c ].push_back( i );
				break;
			}
		}
	}

	for each( const char c in clearedSearchStr )
		if( searchLetterIndexes[ c ].empty() )
			return false;

	IndexesTreeItem root;
	root.Index = -1;
	root.initChilds( 0, clearedSearchStr );

	return true;
}
