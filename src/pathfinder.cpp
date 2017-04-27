#include<bits/stdc++.h>

#include "geometry.hpp"
#include "pathfinder.hpp"

std::vector<point> valid_destinations(const std::vector<std::vector<bool> > & map,
				      int radius, const point & startpoint){
    std::vector<point> valid;
    int height, width;
    
    height = map.size();
    if(height == 0){
	return valid;
    }
    width = map[0].size();
    
    auto movements = point_circle(radius);

    for(auto p:movements){
	int x = p.first + startpoint.first;
	int y = p.second + startpoint.second;

	if(x >= 0 && y >= 0 && x < width && y < height){ // is in range?
	    if(map[y][x]){ // is walkable?
		valid.push_back({x, y});
	    }
	}
    }

    return valid;
}

std::vector<point> pathfinder(const std::vector<std::vector<bool> > & map,
			      int radius, const point & startpoint, const point & endpoint){
    std::vector<point> path;
    
    std::priority_queue<std::pair<ll, point> > candidates;

    std::unordered_map<std::>
    
    candidates.push({0, startpoint});

    while( ! candidates.empty()){
	
    }

    return path;
}
