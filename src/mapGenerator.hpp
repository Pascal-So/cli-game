#include<bits/stdc++.h>

#define ll long long
#define point std::pair<int, int>

#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

std::vector<std::pair<ll, std::pair<int, int> > > get_all_edges(std::vector<point> nodes); // -> {dist, {a, b}}

std::vector<int> vertex_cover_approximation(std::vector<std::pair<int, int> > edges, int n);

std::vector<std::vector<bool> > generate_map(int width, int height, int rooms);

std::vector<std::pair<int, int> > get_mst(std::vector<point> nodes);

ll sqDist(point a, point b);

point generate_point(int width, int height);

std::vector<point> relax_pointset(std::vector<point> pointset, ll minDist);

#endif
