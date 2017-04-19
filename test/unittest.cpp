#include "gtest/gtest.h"
#include "mapGenerator.hpp"
#include "unionFind.hpp"
#include <vector>


TEST(UnionFindTest, emptyUnion){
    int n = 4;
    
    auto u = empty_union(n);

    ASSERT_EQ(n, u.size());
    
    for(int i = 0; i < n; ++i){
	EXPECT_EQ(i, u[i]);
    }
}

TEST(UnionFindTest, getUnionRoot){
    int n = 5;

    auto u = empty_union(n);

    for(int i = 0; i < n; ++i){
	EXPECT_EQ(u[i], get_union_root(u, i));
    }

    u[0] = 1;
    u[1] = 2;

    EXPECT_EQ(2, get_union_root(u, 0));
    EXPECT_EQ(2, u[0]);
}

TEST(UnionFindTest, unionMerge){
    int n = 5;

    auto u = empty_union(n);

    union_merge(u, 1, 2);
    union_merge(u, 2, 3);

    EXPECT_EQ(get_union_root(u, 1), get_union_root(u, 3));
}

TEST(UnionFindTest, isUnion){
    int n = 6;

    auto u = empty_union(n);

    union_merge(u, 1, 2);
    union_merge(u, 2, 3);

    EXPECT_TRUE(is_union(u, 1, 3));

    union_merge(u, 4, 5);

    EXPECT_FALSE(is_union(u, 1, 4));

    union_merge(u, 1, 5);

    EXPECT_TRUE(is_union(u, 3, 4));
}


TEST(MapGeneratorTest, generatePoint){
    int width = 10, height = 20;

    for(int i = 0; i < 10; ++i){
	auto p = generate_point(width, height);

	EXPECT_LT(p.first, width);
	EXPECT_LT(p.second, height);

	EXPECT_GE(p.first, 0);
	EXPECT_GE(p.second, 0);
    }
}

TEST(MapGeneratorTest, sqDist){
    point a = {4, 6};
    point b = {1, 10};

    EXPECT_EQ(sqDist(a, b), 9+16);
}

TEST(MapGeneratorTest, getMST){
    std::vector<point> points;

    points.push_back({1, 1});
    points.push_back({1, 2});
    points.push_back({1, 3});
    points.push_back({2, 2});
    points.push_back({0, 3});

    //  Arrangement:
    //  y
    //  # # .
    //  . # #
    //  . # .
    //  0 . . x
    
    auto mst = get_mst(points);

    EXPECT_EQ(mst.size(), points.size()-1);

    EXPECT_EQ(mst[0], std::make_pair(0, 1));
    EXPECT_EQ(mst[1], std::make_pair(1, 2));
    EXPECT_EQ(mst[2], std::make_pair(1, 3));
    EXPECT_EQ(mst[3], std::make_pair(2, 4));
}
