#include <iostream>
#include "specVec.hpp"
//#include "specSet.hpp"
#include "Rand.hpp"
#include <chrono>
#include <format>

auto get_random_cunit(int max_value, int size) {
    Rand random{};

    int lower = random.get(1, max_value);
    int upper = random.get(lower, lower + size);

    return cunits{lower, upper};
}

auto get_random_size(int max_size) {
    Rand random{};
    return random.get(1, max_size);
}

auto get_random_number(int min, int max) {
    Rand random{};
    return random.get(min, max);
}

template<template<typename> typename C, typename T>
void print_found(const C<T>& container, const std::vector<int>& numbers) {
    std:: cout << "Searching in: ";
    for (auto item: container) {
        std::cout << item << ' ';
    }
    std::cout << '\n';
    for(auto number: numbers) {
        auto it = container.find(number);
        if (it != container.end()) {
            std::cout << "Searching: " << number << " || Found: " << *it << '\n';
        }
        else {
            std::cout << "Searching: " << number << " || Not found\n";
        }
    }
}

void test() {
    std::set<cunits<int>> range{};

    // ============================= CONFIG =============================
    const int NUM_OF_CUNITS = 1000;
    const int MAX_SINGLE_CUNIT_SIZE = 10;
    const int MAX_SINGLE_CUNIT_VALUE = 1000;

    const int NUM_OF_NUMBERS_TO_FIND = 1000000;
    const int MAX_RANDOM_NUMBER_TO_FIND = MAX_SINGLE_CUNIT_VALUE * 2;

    const bool PRINT_FOUND = false;
    // =============================--------=============================

    for (int i = 0; i < NUM_OF_CUNITS; ++i) {
        auto size = get_random_size(MAX_SINGLE_CUNIT_SIZE);
        auto cu = get_random_cunit(MAX_SINGLE_CUNIT_VALUE, size);
        range.insert(cu);
    }

//    range = {{1, 100000}};

    auto set = range.to_set_of();

    std::cout << "Range size: " << range.size() << '\n';
    std::cout << "Set size: " << set.size() << '\n';
    std::cout << '\n';

    std::vector<int> numbers{};
    for (int i = 0; i < NUM_OF_NUMBERS_TO_FIND; ++i) {
        numbers.push_back(get_random_number(1, MAX_RANDOM_NUMBER_TO_FIND));
    }

    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "INITIALIZATION TIME: " << duration << " ms\n\n";

    // searching for random numbers in set
    int found{};
    start = std::chrono::high_resolution_clock::now();
    for(auto number: numbers) {
        auto it = set.find(number);
        if (it != set.end()) {
            found++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "SET\n";
    std::cout << "==========================================================\n";
    std::cout <<  "Found: " << found << '\n';
    std::cout <<  "Time: " << duration << " ms\n\n";

    if(PRINT_FOUND) {
        print_found<std::set>(set, numbers);
        std::cout << "\n\n";
    }

    // searching for random numbers in specialization of set
    found = 0;
    start = std::chrono::high_resolution_clock::now();
    for(auto number: numbers) {
        auto it = range.find(number);
        if (it != range.end()) {
            found++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "SPECIALIZATION\n";
    std::cout << "==========================================================\n";
    std::cout <<  "Found: " << found << '\n';
    std::cout <<  "Time: " << duration << " ms\n\n";

    if (PRINT_FOUND)
        print_found<std::set>(range, numbers);
}

void generator() {
    std::set<cunits<int>> range{};
    range.insert({1, 3});
    range.insert({5, 7});
    range.insert({9, 11});

    auto ids_vec = range.to_vector();

    auto ids_set = std::set<cunits<int>>::from_vector(ids_vec);

    for(auto rng: ids_set) {
        std::string query = std::format("UPDATE tab SET column = value "
                                        "WHERE id BETWEEN {} AND {};", rng.min(), rng.max());
        std::cout << query << '\n';
    }

}


int main() {

    test();
}
