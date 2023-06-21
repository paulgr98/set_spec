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

    // CLOCK INITIALIZATION TIME
    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto duration_sum = (end - start);
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "INITIALIZATION TIME: " << duration << " ms\n\n";

    // SPECIALIZATION INSERTION TIME
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < NUM_OF_CUNITS; ++i) {
        auto size = get_random_size(MAX_SINGLE_CUNIT_SIZE);
        auto cu = get_random_cunit(MAX_SINGLE_CUNIT_VALUE, size);
        range.insert(cu);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    auto spec_insert_time = duration;

//    range = {{1, 100000}};

    auto to_insert = range.to_set_of();

    // INSERTION TIME FOR STANDARD SET
    auto set = std::set<int>{};
    start = std::chrono::high_resolution_clock::now();
    for (auto item: to_insert) {
        set.insert(item);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "SET INSERTION TIME\n";
    std::cout << "==========================================================\n";
    std::cout << "Time: " << duration << " ms\n\n";


    std::cout << "SPECIALIZATION INSERTION TIME\n";
    std::cout << "==========================================================\n";
    std::cout << "Time: " << spec_insert_time << " ms\n\n";

    std::cout << "Range size: " << range.size() << '\n';
    std::cout << "Set size: " << set.size() << '\n';
    std::cout << '\n';

    std::vector<int> numbers{};
    for (int i = 0; i < NUM_OF_NUMBERS_TO_FIND; ++i) {
        numbers.push_back(get_random_number(1, MAX_RANDOM_NUMBER_TO_FIND));
    }

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

    std::cout << "SET SEARCHING TIME\n";
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
    duration = std::chrono::duration_cast<std::chrono::milliseconds>( end - start).count();

    std::cout << "SPECIALIZATION SEARCHING TIME\n";
    std::cout << "==========================================================\n";
    std::cout <<  "Found: " << found << '\n';
    std::cout <<  "Time: " << duration << " ms\n\n";

    // SET DELETION TIME
    start = std::chrono::high_resolution_clock::now();
    for (auto item: to_insert) {
        set.erase(item);
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "SET DELETION TIME\n";
    std::cout << "==========================================================\n";
    std::cout << "Time: " << duration << " ms\n\n";

    // SPECIALIZATION DELETION TIME
    start = std::chrono::high_resolution_clock::now();
    for (auto item: to_insert) {
        range.erase({item, item + 1});
    }
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "SPECIALIZATION DELETION TIME\n";
    std::cout << "==========================================================\n";
    std::cout << "Time: " << duration << " ms\n\n";

    set.clear();
    range.clear();

    set.insert(1);
    range.insert({1, 2});


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
