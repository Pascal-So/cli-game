#include <bits/stdc++.h>

#include "geometry.hpp"

#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

std::vector<point> valid_destinations(const std::vector<std::vector<bool> > & map,
				      int radius, const point & startpoint);

std::vector<point> pathfinder(const std::vector<std::vector<bool> > & map,
			      int radius, const point & startpoint, const point & endpoint);

#endif
