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
    std::unordered_map<point, point, pointhash> parent;

    int height = map.size();
    int width = (height > 0) ? map[0].size() : 0;
    
    std::vector<std::vector<int> > distance (height, std::vector<int> (width, width*height));
    
    parent[startpoint] = startpoint;
    
    std::priority_queue<std::pair<ll, std::pair<int, point>> > candidates;

    candidates.push({0, {0, startpoint} });

    while( ! candidates.empty()){
	ll current_distance;
	point current_point;
	std::tie(current_distance, current_point) = candidates.top().second;
	candidates.pop();

	//std::cout << current_point.first << ", " << current_point.second << std::endl;

	if(distance[current_point.second][current_point.first] < current_distance){
	    continue;
	}
	distance[current_point.second][current_point.first] = current_distance;

	if(current_point == endpoint){
	    while( ! candidates.empty()){
		candidates.pop();
	    }
	}else{
	    ll new_distance = current_distance + 1;
	    
	    for(auto p:valid_destinations(map, radius, current_point)){
		if(distance[p.second][p.first] > new_distance){ // not discovered yet
		    distance[p.second][p.first] = new_distance;
		    parent[p] = current_point;
		    ll heuristic = manhattan_dist(endpoint, p);

		    candidates.push( { -(new_distance*4 + heuristic), { new_distance, p } });
		}
	    }
	}
    }

    std::vector<point> path;

    point iterate = endpoint;
    path.push_back(iterate);

    while(iterate != startpoint){
	iterate = parent[iterate];
	path.push_back(iterate);
    }

    std::reverse(path.begin(), path.end());
    
    return path;
}
