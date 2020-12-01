#ifndef BODIX_HPP
#define BODIX_HPP

#include <array>
#include <vector>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <iostream>

// структура данных - ребро
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

// структура данных - Система непересекающихся множеств
// или раскрашенное множество
template<typename T>
struct DisjointSet
{
    // элемент подмножества, заданного значенем ранга (числом)
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

    // создание N элементов в структуре
    DisjointSet(size_t N)
    {
        for(int i = 0; i < N; ++i)
            vals.push_back(Set{i, i});
    }

    // поиск по значению
    Set Find(const T &elem) const
    {
        for(int i = 0; i < vals.size(); ++i)
            if (elem == vals[i].elem) return vals[i];
        return {T {}, -1};
    }

    // обьединение двух подмножеств
    void Union(const Set &a, const Set &b)
    {
        const auto newrank = a.rank;
        for(int i = 0; i < vals.size(); ++i) {
            auto &val = vals[i];
            if (val.rank == b.rank) val.rank = newrank;
        }
    }
};

// Матрица N на N
template<typename T, size_t N>
using Matrix = T[N][N];

// Массив ребер
template<typename T>
using EdgeVec = std::vector<Edge<T>>;

// Вспомогательные функции__________________________________
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
//__________________________________________________________

namespace Utils {
    // из матрицы инцидентности выбираем все ребра
    template<typename T, size_t N>
    EdgeVec<T> make_vec(const Matrix<T, N> &mat)
    {
        EdgeVec<T> retval;
        for(int i = 0; i < N; ++i)
            for(int j = 0; j < N; ++j)
                if (i > j && mat[j][i] != 0) retval.push_back(Edge<T>{j, i, mat[j][i]});
        return retval;
    }
    // Сортируем ребра по возрастанию
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
    // Матрица размера 10
    typedef Matrix<int, 10> LabMatrix;

    // сам алгоритм
    template<typename T, size_t N>
    std::pair<EdgeVec<T>, T> invoke_alg(const Matrix<T,N> &mat)
    {
        EdgeVec<T> retval;
        T sum {};
        DisjointSet<T> set(N);
        // Выбираем ребра из матрицы
        const auto UnsortedEdges = Utils::make_vec(mat);
        // сортируем ребра
        const auto SortedEdges = Utils::sort(UnsortedEdges);
        // идем по всем отсортированным вершинам
        for(const auto &elem: SortedEdges) {
            // находим элемент из которого пришли в ребро
            const auto elem1 = set.Find(elem.from);
            // находим элемент в который приходим из ребра
            const auto elem2 = set.Find(elem.to);
            // если они из разных подмножеств, разных "цветов"
            if (elem1.rank != elem2.rank) {
                // то добавляем ребро к остовному дереву
                retval.push_back(elem);
                // "перекрашиваем" структуру
                set.Union(elem1, elem2);
                // вычисляем сумму ребра
                sum += elem.val;
            }
        }
        return std::make_pair(retval, sum);
    }
}

#endif // BODIX_HPP
