#include "edges.h"
#include <unordered_set>
#include <unordered_map>

// From a list of triangle indices into some vertex set V, determine the
// set of unique undirected edges.
//
// Inputs:
//   F  #F by 3 list of triangles indices into some vertex set V
// Returns E  #E by 2 list of undirected edge indices into V
Eigen::MatrixXi edges(const Eigen::MatrixXi &F)
{
	Eigen::MatrixXi E;
	// ADD YOUR CODE HERE // OKAY I DID, STOP YELLING

	std::unordered_map< int, std::unordered_set<int> > undirectedEdges;
	// undirectedEdges.reserve( f.rows() * 3 );
	int count = 0;
	for( int f = 0; f < F.rows(); ++f ){
		for( int m = 0; m < 3; ++m ){
			int min = std::min( F(f, m), F(f, (m+1) % 3 ) );
			int max = std::max( F(f, m), F(f, (m+1) % 3 ) );
			std::pair< std::unordered_set<int>::iterator,bool> success = undirectedEdges[min].insert( max );
			if( success.second ) ++count;
		}
	}

	E.resize( count, 2 );
	int e = 0;
	for( auto mit = undirectedEdges.begin(); mit != undirectedEdges.end(); ++mit ){
		for( auto sit = mit->second.begin(); sit != mit->second.end(); ++sit ){
			E.block<1,2>( e, 0 ) = Eigen::Vector2i( mit->first, *sit );
		}
	}

	return E;
}
