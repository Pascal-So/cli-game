#include <curses.h>
#include <bits/stdc++.h>
#include "mapGenerator.hpp"
#include "pathfinder.hpp"

template<typename T>
bool contains(T needle, const std::vector<T> & haystack){
    for(auto e:haystack){
	if(e == needle){
	    return true;
	}
    }
    return false;
}

int main(){
    //initscr(); // Initialize the window
    //noecho(); // Don't echo any keypresses
    //curs_set(FALSE); // Don't display a cursor
    
    srand(time(0));
    
    int width = 120;
    int height = 60;
    auto map = generate_map(width, height, 20);

    point undefined = {-1, -1};
    
    point first_free = undefined;
    point last_free = undefined;
    
    for(int y = 0; y < height; ++y){
	for(int x = 0; x < width; ++x){
	    if(map[y][x]){
		if(first_free == undefined){
		    first_free = {x, y};
		}
		last_free = {x, y};
	    }
	}
    }

    print_map(map);

    auto path = pathfinder(map, 3, first_free, last_free);
    
    for(int y = 0; y < height; ++y){
	for(int x = 0; x < width; ++x){
	    if(contains(std::make_pair(x, y), path)){
		std::cout<<"# ";
	    }else{
		std::cout<< (map[y][x] ? "  " : ". ");
	    }
	}
	std::cout<<"\n";
    }

}

