#include<bits/stdc++.h>
#include <curses.h>
#include "unionFind.hpp"
#include "mapGenerator.hpp"
#include "utils.hpp"

#define ll long long
#define point std::pair<int, int>

std::vector<std::vector<bool> > generate_map(int width, int height, int rooms){
    
}

std::vector<std::pair<ll, std::pair<int, int> > > get_all_edges(std::vector<point> nodes){ // -> {dist, {a, b}}
    int n = nodes.size();

    std::vector<std::pair<ll, std::pair<int, int> > > distances;
    for(int i = 0; i < n; ++i){
	for(int j = 0; j < i; ++j){
	    distances.push_back({sqDist(nodes[i], nodes[j]), {j, i}});
	}
    }

    return distances;
}


// approximation up to factor 2, but hey, it's in linear time!
std::vector<int> vertex_cover_approximation(std::vector<std::pair<int, int> > edges, int n){
    int m = edges.size();
    
    std::vector<bool> covered (m, false);

    std::vector<std::vector<int> > edges_by_vertex (n);
    
    for(int i = 0; i < m; ++i){
	edges_by_vertex[edges[i].first].push_back(i);
	edges_by_vertex[edges[i].second].push_back(i);
    }

    std::vector<int> vertex_cover;
    
    for(int i = 0; i < m; ++i){
	if(! covered[i]){	    
	    for(auto vertex:pair_to_vector(edges[i])){
		vertex_cover.push_back(vertex);
		for(auto e:edges_by_vertex[vertex]){
		    covered[e] = true;
		}
	    }
	}
    }

    return vertex_cover;
}

std::vector<std::pair<int, int> > get_mst(std::vector<point> nodes){
    int n = nodes.size();

    auto distances = get_all_edges(nodes);
    
    std::sort(distances.begin(), distances.end());

    auto union_parents = empty_union(n);

    std::vector<std::pair<int, int> > edgesInMst;

    int nrEdges = 0;
    for(auto e:distances){
	int nodeA = e.second.first;
	int nodeB = e.second.second;

	if( ! is_union(union_parents, nodeA, nodeB)){
	    union_merge(union_parents, nodeA, nodeB);

	    ++nrEdges;
	    edgesInMst.push_back({nodeA, nodeB});
	}
    }

    return edgesInMst;
}

std::vector<point> relax_pointset(std::vector<point> pointset, ll minDist){
    int n = pointset.size();
    
    auto edges = get_all_edges(pointset);

    std::vector<std::pair<int, int> > shortEdges;
    
    for(auto e:edges){
	if(e.first < minDist){
	    shortEdges.push_back(e.second);
	}
    }

    auto vertex_cover = vertex_cover_approximation(shortEdges, n);

    std::sort(vertex_cover.begin(), vertex_cover.end());

    std::vector<point> relaxed;

    int coverSize = vertex_cover.size();
    
    int pos = 0;
    for(int i = 0; i < n; ++i){
	while(pos < coverSize && vertex_cover[pos] < i){
	    ++pos;
	}

	if(pos < coverSize && i != vertex_cover[pos]){
	    relaxed.push_back(pointset[i]);
	}
    }

    return relaxed;
}

ll sqDist(point a, point b){
    ll dx = b.first - a.first;
    ll dy = b.second - a.second;

    return dx*dx + dy*dy;
}

point generate_point(int width, int height){
    return {rand() % width, rand() % height};
}
