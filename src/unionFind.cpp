#include<vector>
#include "unionFind.hpp"

int get_union_root(std::vector<int> &union_parents, int node){
    if(union_parents[node] == node){
	return node;
    }

    union_parents[node] = get_union_root(union_parents, union_parents[node]);

    return union_parents[node];
}

bool is_union(std::vector<int> &union_parents, int nodeA, int nodeB){
    return get_union_root(union_parents, nodeA) == get_union_root(union_parents, nodeB);
}

void union_merge(std::vector<int> &union_parents, int nodeA, int nodeB){
    nodeA = get_union_root(union_parents, nodeA);
    nodeB = get_union_root(union_parents, nodeB);

    union_parents[nodeA] = nodeB;
}

std::vector<int> empty_union(int n){
    std::vector<int> out;
    for(int i = 0; i < n; ++i){
	out.push_back(i);
    }
    return out;
}
