#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <bodix.hpp>

typedef Matrix<int,4> TestMatrix;
typedef EdgeVec<int> TestEdgeVec;
typedef DisjointSet<int> TestDisjointSet;
typedef TestDisjointSet::Set TestSet;

TEST_CASE( "Utils make_vec", "[Matrix]" ) {
    const TestMatrix in {
        {0, 1, 2, 3},
        {0, 0, 4, 5},
        {0, 0, 0, 6},
        {0, 0, 0, 0}
    };
    const TestEdgeVec exp {
        {0, 1, 1},
        {0, 2, 2},
        {1, 2, 4},
        {0, 3, 3},
        {1, 3, 5},
        {2, 3, 6}
    };
    const auto out = Utils::make_vec(in);
    REQUIRE(exp == out);
}

TEST_CASE( "Utils sort", "[Matrix]" ) {
    const TestEdgeVec in {
        {0, 1, 1},
        {0, 2, 2},
        {0, 3, 3},
        {1, 2, 4},
        {1, 3, 5},
        {2, 3, 6}
    };
    const EdgeVec<int> exp {
        {0, 1, 1},
        {0, 2, 2},
        {0, 3, 3},
        {1, 2, 4},
        {1, 3, 5},
        {2, 3, 6}
    };
    const auto out = Utils::sort(in);
    REQUIRE(exp == out);
}

TEST_CASE( "DisjointSet creation", "[DisjointSet]" ) {
    const TestDisjointSet in(4);
    const TestDisjointSet exp {
        TestSet{0, 0},
        TestSet{1, 1},
        TestSet{2, 2},
        TestSet{3, 3}
    };
    REQUIRE(in == exp);
}

TEST_CASE( "DisjointSet Find", "[DisjointSet]" ) {
    const TestDisjointSet in(4);
    const TestSet exp {3, 3};
    const auto out = in.Find(3);
    REQUIRE(exp == out);
}

TEST_CASE( "DisjointSet Union", "[DisjointSet]" ) {
    const TestDisjointSet in(4);
    const TestDisjointSet exp {
        TestSet{0, 0},
        TestSet{1, 1},
        TestSet{2, 2},
        TestSet{3, 2}
    };
    const TestSet help1 {2, 2};
    const TestSet help2 {3, 3};
    TestDisjointSet out(in);
    out.Union(help1, help2);
    REQUIRE(exp == out);
}

TEST_CASE( "FullTest", "[Matrix]" ) {
    const Matrix<int, 5> in {
        {0, 0, 0, 1, 10},
        {0, 0, 5, 0, 4},
        {0, 0, 0, 2, 3},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    const TestEdgeVec exp {
        {0, 3, 1},
        {2, 3, 2},
        {2, 4, 3},
        {1, 4, 4}
    };
    const auto [outVec, outSum] = Kraskal::invoke_alg(in);
    CHECK(exp == outVec);
    CHECK(outSum == 10);
}

TEST_CASE( "FullTestBodix", "[Matrix]" ) {
     const Kraskal::LabMatrix in {
         {0, 6,  10,  6,  4,  0,  8,  0,  0,  6},
         {0, 0,  4,   0,  0,  0,  0,  0,  0,  8},
         {0, 0,  0,   9,  0,  0,  0,  0,  0,  0},
         {0, 0,  0,   0,  7,  0,  0,  0,  0,  0},
         {0, 0,  0,   0,  0,  8,  5,  0,  0,  0},
         {0, 0,  0,   0,  0,  0,  10, 15, 0,  0},
         {0, 0,  0,   0,  0,  0,  0,  8,  15, 9},
         {0, 0,  0,   0,  0,  0,  0,  0,  19, 0},
         {0, 0,  0,   0,  0,  0,  0,  0,  0,  12},
         {0, 0,  0,   0,  0,  0,  0,  0,  0,  0}
     };
     const TestEdgeVec exp {
         {0, 3, 1},
         {2, 3, 2},
         {2, 4, 3},
         {1, 4, 4}
     };
     const auto [outVec, outSum] = Kraskal::invoke_alg(in);
     CHECK(exp == outVec);
     CHECK(outSum == 59);
 }
