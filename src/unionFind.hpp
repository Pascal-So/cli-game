#include<vector>

#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP

int get_union_root(std::vector<int> &union_parents, int node);

bool is_union(std::vector<int> &union_parents, int nodeA, int nodeB);

void union_merge(std::vector<int> &union_parents, int nodeA, int nodeB);

std::vector<int> empty_union(int n);

#endif
