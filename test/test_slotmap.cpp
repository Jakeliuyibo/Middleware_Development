#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <map>
#include <unordered_map>
#include <chrono>
#include <cstdlib> // for std::rand() and std::srand()
#include "slotmap.hpp"

using namespace std;
using namespace utility;

template <typename Container>
void test_insert_for_vec_and_list(size_t size, string type="vec_and_list") 
{
    Container c;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; ++i) {
        c.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Insertion into " << type << " of size " << size << " took " << elapsed.count() << " seconds." << std::endl;
}

template <typename Container>
void test_insert_for_slotmap(size_t size, string type="vec_and_list") 
{
    Container c;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; ++i) {
        auto k = c.Insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Insertion into " << type << " of size " << size << " took " << elapsed.count() << " seconds." << std::endl;
}


template <typename Container>
void test_insert_for_map(size_t size, string type="vec_and_list") 
{
    Container c;
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; ++i) {
        c.insert({i, i});
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Insertion into " << type << " of size " << size << " took " << elapsed.count() << " seconds." << std::endl;
}


template <typename Container>
void test_erase_for_vec_and_list(size_t size, string type="vec_and_list") 
{
    Container c;
    for (size_t i = 0; i < size; ++i) {
        c.push_back(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; ++i) {
        c.push_back(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Insertion into " << type << " of size " << size << " took " << elapsed.count() << " seconds." << std::endl;
}

template <typename Container>
void test_erase_for_slotmap(size_t size, string type="vec_and_list") 
{
    Container c;
    for (size_t i = 0; i < size; ++i) {
        auto k = c.Insert(i);
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; ++i) {
        auto k = c.Erase(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Insertion into " << type << " of size " << size << " took " << elapsed.count() << " seconds." << std::endl;
}

template <typename Container>
void test_erase_for_map(size_t size, string type="vec_and_list") 
{
    Container c;
    for (size_t i = 0; i < size; ++i) {
        c.insert({i, i});
    }
    auto start = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < size; ++i) {
        auto k = c.Insert(i);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Insertion into " << type << " of size " << size << " took " << elapsed.count() << " seconds." << std::endl;
}

int main()
{
    cout << "Start..." << endl;

    size_t size = 1000000; // 测试数据集大小

    {
        test_insert_for_vec_and_list<std::vector<int>>(size, "vec_and_list");
        test_insert_for_vec_and_list<std::list<int>>(size, "vec_and_list");
        test_insert_for_slotmap<SlotMap<int>>(size, "slotmap");
        test_insert_for_map<map<int, int>>(size, "map");
        test_insert_for_map<unordered_map<int, int>>(size, "map");
    }

    {
        test_erase_for_vec_and_list<std::vector<int>>(size, "vec_and_list");
        test_erase_for_vec_and_list<std::list<int>>(size, "vec_and_list");
        test_erase_for_slotmap<SlotMap<int>>(size, "slotmap");
        test_erase_for_map<map<int, int>>(size, "map");
        test_erase_for_map<unordered_map<int, int>>(size, "map");
    }

    cout << "end..." << endl;
    return 0;
}

