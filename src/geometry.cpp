#include<bits/stdc++.h>
#include "geometry.hpp"

std::vector<point> point_circle(int radius){
    std::vector<point> points;
    
    for(int y = -radius; y <= radius; ++y){
	for(int x = -radius; x <= radius; ++x){
	    if(sq_dist({0, 0}, {x, y}) <= radius * radius){
		points.push_back({x, y});
	    }
	}
    }

    return points;
}

ll sq_dist(point a, point b){
    ll dx = b.first - a.first;
    ll dy = b.second - a.second;

    return dx*dx + dy*dy;
}

point generate_point(int width, int height){
    return {rand() % width, rand() % height};
}

