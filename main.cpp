#include <bodix.hpp>

int main(int argc, char *argv[])
{
    const Kraskal::LabMatrix in {
        0, 6,  10,  6,  4,  0,  8,  0,  0,  6,
        0, 0,  4,   0,  0,  0,  0,  0,  0,  8,
        0, 0,  0,   9,  0,  0,  0,  0,  0,  0,
        0, 0,  0,   0,  7,  0,  0,  0,  0,  0,
        0, 0,  0,   0,  0,  8,  5,  0,  0,  0,
        0, 0,  0,   0,  0,  0,  10, 15, 0,  0,
        0, 0,  0,   0,  0,  0,  0,  8,  15, 9,
        0, 0,  0,   0,  0,  0,  0,  0,  19, 0,
        0, 0,  0,   0,  0,  0,  0,  0,  0,  12,
        0, 0,  0,   0,  0,  0,  0,  0,  0,  0
    };
    const auto [outVec, outSum] = Kraskal::invoke_alg(in);

    std::cout<<"Минимальная длинна кабеля: "<<outSum<<'\n';
    std::cout<<"Остовное дерево: "<<outVec;
    return 0;
}
