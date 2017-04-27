#include<bits/stdc++.h>

#define ll long long
#define point std::pair<int, int>

#ifndef MAPGENERATOR_HPP
#define MAPGENERATOR_HPP

std::vector<std::pair<ll, std::pair<int, int> > > get_all_edges(std::vector<point> nodes); // -> {dist, {a, b}}

std::vector<int> vertex_cover_approximation(std::vector<std::pair<int, int> > edges, int n);

void draw_line(std::vector<std::vector<bool> > & map, point start, point end, int line_width);

void draw_circle(std::vector<std::vector<bool> > & map, point origin, double radius);

std::vector<std::vector<bool> > generate_map(int width, int height, int rooms);

std::vector<point> generate_relaxed_pointset(int width, int height, int max_points, int min_dist);

std::vector<std::pair<int, int> > get_mst(std::vector<point> nodes);

std::vector<point> relax_pointset(std::vector<point> pointset, ll minDist);

#endif
