#include<bits/stdc++.h>
#include "unionFind.hpp"
#include "mapGenerator.hpp"
#include "utils.hpp"
#include "geometry.hpp"

#define ll long long
#define point std::pair<int, int>



void print_map(std::vector<std::vector<bool> > map){
    for(auto &row:map){
	for(auto e:row){
	    std::cout<< (e ? "#" : " ") << " ";
	}
	std::cout<<"\n";
    }
}

// line_width has to be odd
void draw_line(std::vector<std::vector<bool> > & map, point start, point end, int line_width){
    int height = map.size();
    int width = height > 0 ? map[0].size() : 0;

    assert(start.first == end.first || start.second == end.second);
    
    enum {horizontal, vertical} direction = start.first == end.first ? vertical : horizontal;

    int startX, endX, startY, endY;

    if(direction == horizontal){
	startX = std::min(start.first, end.first);
	endX = std::max(start.first, end.first);
	startY = start.second - line_width/2;
	endY = start.second + line_width/2;
    }else{
	startX = start.first - line_width/2;
	endX = start.first + line_width/2;
	startY = std::min(start.second, end.second);
	endY = std::max(start.second, end.second);
    }

    for(int x = std::max(startX, 0); x <= std::min(endX, width-1); ++x){
	for(int y = std::max(startY, 0); y <= std::min(endY, height-1); ++y){
	    map[y][x] = true;
	}
    }
}

void draw_circle(std::vector<std::vector<bool> > & map, point origin, double radius){
    int height = map.size();
    int width = height > 0 ? map[0].size() : 0;

    auto points = point_circle(radius);

    for(auto p:points){
	int x = p.first + origin.first;
	int y = p.second + origin.second;
	if(x >= 0 && y >= 0 && x < width && y < height){
	    map[y][x] = true;
	}
    }
}

std::vector<std::vector<bool> > generate_map(int width, int height, int max_rooms){ // [bool walkable]
    double roomGap = 0.5;
    int min_dist = 6;
    int corridor_width = 3;

    auto points = generate_relaxed_pointset(width, height, max_rooms, min_dist);

    int n = points.size();
    
    auto mst = get_mst(points);

    std::vector<std::vector<int> > adj_mst (n);

    for(auto e:mst){
	adj_mst[e.first].push_back(e.second);
	adj_mst[e.second].push_back(e.first);
    }

    std::vector<std::vector<bool> > map (height, std::vector<bool> (width, false)); // [y][x]

    // draw rooms
    
    for(int i = 0; i < n; ++i){
	auto p = points[i];
	double max_radius = width;
	for(auto j:adj_mst[i]){
	    auto o = points[j];
	    max_radius = std::min(max_radius, sqrt(sq_dist(p, o)));
	}
	max_radius = std::max((max_radius - roomGap) / 2, 1.0);

	draw_circle(map, p, max_radius);
    }

    // draw corridors

    for(int i = 0; i < n; ++i){
	auto p = points[i];
	for(int j:adj_mst[i]){
	    auto o = points[j];

	    bool horizontal_first = rand()%2; // go across and then vertical?

	    point middle_point =
		horizontal_first
		? std::make_pair(o.first, p.second)
		: std::make_pair(p.first, o.second);

	    draw_line(map, p, middle_point, corridor_width);
	    draw_line(map, o, middle_point, corridor_width);
	}
    }
    
    return map;
}

std::vector<point> generate_relaxed_pointset(int width, int height, int max_points, int min_dist){
    std::vector<point> points;

    for(int i = 0; i < max_points; ++i){
	points.push_back(generate_point(width, height));
    }

    points = relax_pointset(points, min_dist);

    if(points.empty()){
	points.push_back(generate_point(width, height));
    }
    
    return points;
}

std::vector<std::pair<ll, std::pair<int, int> > > get_all_edges(std::vector<point> nodes){ // -> {dist, {a, b}}
    int n = nodes.size();

    std::vector<std::pair<ll, std::pair<int, int> > > distances;
    for(int i = 0; i < n; ++i){
	for(int j = 0; j < i; ++j){
	    distances.push_back({sq_dist(nodes[i], nodes[j]), {j, i}});
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
	    int v1 = edges[i].first;
	    int v2 = edges[i].second;

	    int vertex = edges_by_vertex[v1].size() > edges_by_vertex[v2].size() ? v1 : v2;
	    
	    vertex_cover.push_back(vertex);
	    for(auto e:edges_by_vertex[vertex]){
		covered[e] = true;
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

std::vector<point> relax_pointset(std::vector<point> pointset, ll min_dist){
    min_dist *= min_dist;
    
    int n = pointset.size();
    
    auto edges = get_all_edges(pointset);

    std::vector<std::pair<int, int> > shortEdges;
    
    for(auto e:edges){
	if(e.first < min_dist){
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


/*int main(){
    srand(time(0));
    print_map(generate_map(135, 71, 24));
}
*/
