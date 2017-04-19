#include<bits/stdc++.h>

#define ll long long
#define point std::pair<int, int>

#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

std::vector<std::vector<bool> > generate_map(int width, int height, int rooms);

std::vector<std::pair<int, int> > get_mst(std::vector<point> nodes);

ll sqDist(point a, point b);

point generate_point(int width, int height);

#endif
