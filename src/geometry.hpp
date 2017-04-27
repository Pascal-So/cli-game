#include<bits/stdc++.h>

#ifndef GEOMETRY_HPP
#define GEOMETRY_HPP

#define ll long long
#define point std::pair<int, int>

ll sq_dist(point a, point b);

point generate_point(int width, int height);

std::vector<point> point_circle(int radius);

#endif
