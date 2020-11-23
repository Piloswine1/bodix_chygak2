#ifndef BODIX_HPP
#define BODIX_HPP

#include <array>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <iostream>

#include "bodix_global.h"

template<typename T>
struct Edge
{
    int from, to;
    T val;

    bool operator==(const Edge &e) const
    {
        return from == e.from &&
               to == e.to &&
               val == e.val;
    }
};

template<typename T>
struct DisjointSet
{
    struct Set
    {
        T elem;
        int rank;

        bool operator==(const Set &s) const
        {
            return elem == s.elem&& rank == s.rank;
        }
    };

    std::vector<Set> vals;

    bool operator==(const DisjointSet &s) const
    {
        return std::equal(vals.begin(), vals.end(), s.vals.begin());
    }

    template<typename V>
    DisjointSet(std::initializer_list<V> list):
        vals(list)
    {}

    DisjointSet(const std::vector<Set> &vec):
        vals(vec)
    {}

    DisjointSet(size_t N)
    {
        for(int i = 0; i < N; ++i)
            vals.emplace_back(i, i);
    }

    Set Find(const T &elem) const
    {
        for(int i = 0; i < vals.size(); ++i)
            if (elem == vals[i].elem) return vals[i];
        return {T {}, -1};
    }

    void Union(const Set &a, const Set &b)
    {
        const auto newrank = a.rank;
        for(int i = 0; i < vals.size(); ++i) {
            auto &val = vals[i];
            if (val.rank == b.rank) val.rank = newrank;
        }
    }
};

template<typename T, size_t N>
using Matrix = std::array<std::array<T, N>, N>;

template<typename T>
using EdgeVec = std::vector<Edge<T>>;

template<typename T>
std::ostream& operator<<(std::ostream& os, const Edge<T> &e)
{
    return os<<"{from: "<<e.from<<", to: "<<e.to<<", val: "<<e.val<<'}';
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const EdgeVec<T> &e)
{
    os<<"{\n";
    for(const auto &elem: e)
        os<<'\t'<<elem<<'\n';
    return os<<"}\n";
}

template<typename T>
bool operator==(const EdgeVec<T> &a, const EdgeVec<T> &b) {
    return std::equal(a.begin(), a.end(), b.begin());
}

template<typename T, size_t N>
bool operator==(const Matrix<T,N> &a, const Matrix<T,N> &b)
{
    return std::equal(a.begin(), a.end(), b.begin());
}

namespace Utils {
    template<class T, size_t N>
    EdgeVec<T> make_vec(const Matrix<T, N> &mat)
    {
        EdgeVec<T> retval;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if (i > j && mat[j][i] != 0) retval.emplace_back(j, i, mat[j][i]);
        return retval;
    }

    template<typename T>
    EdgeVec<T> sort(const EdgeVec<T> &vec)
    {
        EdgeVec<T> retval{vec};
        std::sort(retval.begin(), retval.end(),
            [](const Edge<T> &a, const Edge<T> &b){
                return a.val < b.val;
            }
        );
        return retval;
    }
};


namespace Kraskal
{
    typedef Matrix<int, 10> LabMatrix;

    template<typename T, size_t N>
    std::pair<EdgeVec<T>, T> invoke_alg(const Matrix<T,N> &mat)
    {
        EdgeVec<T> retval;
        T sum {};
        DisjointSet<T> set(N);
        const auto UnsortedEdges = Utils::make_vec(mat);
        const auto SortedEdges = Utils::sort(UnsortedEdges);
        for(const auto &elem: SortedEdges) {
            const auto elem1 = set.Find(elem.from);
            const auto elem2 = set.Find(elem.to);
            if (elem1.rank != elem2.rank) {
                retval.emplace_back(elem);
                set.Union(elem1, elem2);
                sum += elem.val;
            }
        }
        return {retval, sum};
    }
}

#endif // BODIX_HPP
