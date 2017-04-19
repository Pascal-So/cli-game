#include<bits/stdc++.h>
#include <curses.h>
#include "unionFind.hpp"
#include "mapGenerator.hpp"

#define ll long long
#define point std::pair<int, int>

std::vector<std::vector<bool> > generate_map(int width, int height, int rooms){
    
}


std::vector<std::pair<int, int> > get_mst(std::vector<point> nodes){
    int n = nodes.size();

    std::vector<std::pair<ll, std::pair<int, int> > > distances;
    for(int i = 0; i < n; ++i){
	for(int j = 0; j < i; ++j){
	    distances.push_back({sqDist(nodes[i], nodes[j]), {j, i}});
	}
    }

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

std::vector<point> relaxPointset(std::vector<point> pointset, ll minDist){
    bool ok = false;
}

ll sqDist(point a, point b){
    ll dx = b.first - a.first;
    ll dy = b.second - a.second;

    return dx*dx + dy*dy;
}

point generate_point(int width, int height){
    return {rand() % width, rand() % height};
}
