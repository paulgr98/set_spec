#include "gtest/gtest.h"
#include "../../cunits.hpp"
#include "../../specSet.hpp"


TEST(specSetTests, default_constructor) {
    std::set<cunits<int>> s{};
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(specSetTests, initializer_list_constructor) {
    std::set<cunits<int>> s = {{1, 2}, {3, 4}, {5, 6}};
    EXPECT_FALSE(s.empty());
    EXPECT_NE(s.size(), 0);
}

TEST(specSetTests, copy_constructor) {
    std::set<cunits<int>> s = {{1, 2}, {3, 4}, {5, 6}};
    const std::set<cunits<int>>& s_copy = s;
    EXPECT_FALSE(s_copy.empty());
    EXPECT_NE(s_copy.size(), 0);
}

TEST(specSetTests, copy_assignment) {
    std::set<cunits<int>> s = {{1, 2}, {3, 4}, {5, 6}};
    const std::set<cunits<int>>& s_copy = s;
    EXPECT_FALSE(s_copy.empty());
    EXPECT_NE(s_copy.size(), 0);
}

TEST(specSetTests, begin) {
    std::set<cunits<int>> s = {{1, 2}, {3, 4}, {5, 6}};
    EXPECT_FALSE(s.empty());
    EXPECT_NE(s.size(), 0);
    EXPECT_EQ(s.begin()->min(), 1);
    EXPECT_EQ(s.begin()->max(), 2);
}

TEST(specSetTests, end) {
    std::set<cunits<int>> s = {{1, 2}, {3, 4}, {5, 6}};
    EXPECT_FALSE(s.empty());
    EXPECT_NE(s.size(), 0);
    EXPECT_EQ((--s.end())->min(), 5);
    EXPECT_EQ((--s.end())->max(), 6);
}

TEST(specSetTests, insert) {
    std::set<cunits<int>> s{{1, 2}, {5, 6}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 2);

    s.insert({2, 5});
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);
}

TEST(specSetTests, erase_cu) {
    std::set<cunits<int>> s{{1, 6}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1);

    s.erase(cunits(2, 5));
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 2);
}

TEST(specSetTests, erase_iterator) {
    std::set<cunits<int>> s{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    auto it = s.begin();
    std::advance(it, 2);
    s.erase(it);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 2);
}

TEST(specSetTests, clear) {
    std::set<cunits<int>> s{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
}

TEST(specSetTests, inlcudes_cunit) {
    std::set<cunits<int>> s{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    EXPECT_TRUE(s.includes(cunits(1, 2)));
    EXPECT_TRUE(s.includes(cunits(4, 6)));
    EXPECT_TRUE(s.includes(cunits(8, 10)));
    EXPECT_TRUE(s.includes(cunits(4, 5)));

    EXPECT_FALSE(s.includes(cunits(1, 3)));
    EXPECT_FALSE(s.includes(cunits(4, 7)));
    EXPECT_FALSE(s.includes(cunits(8, 11)));
}

TEST(specSetTests, inlcudes_base_type) {
    std::set<cunits<int>> s{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    std::set<cunits<int>> s2{{4, 6}};
    EXPECT_TRUE(s.includes(s2));

    std::set<cunits<int>> s3{{1, 2}, {4, 6}};
    EXPECT_TRUE(s.includes(s3));

    std::set<cunits<int>> s4{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_TRUE(s.includes(s4));

    std::set<cunits<int>> s5{{4,5}};
    EXPECT_TRUE(s.includes(s5));

    std::set<cunits<int>> s6{{1, 3}, {4, 7}, {8, 11}};
    EXPECT_FALSE(s.includes(s6));

    std::set<cunits<int>> s7{{1, 2}, {4, 7}, {8, 11}};
    EXPECT_FALSE(s.includes(s7));
}

TEST(specSetTests, equals_operator) {
    std::set<cunits<int>> s{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    std::set<cunits<int>> s2{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_TRUE(s == s2);

    std::set<cunits<int>> s3{{1, 2}, {4, 6}, {8, 11}};
    EXPECT_FALSE(s == s3);

    std::set<cunits<int>> s4{{1, 2}, {4, 6}};
    EXPECT_FALSE(s == s4);

    std::set<cunits<int>> s5{{1, 2}, {4, 6}, {8, 10}, {11, 12}};
    EXPECT_FALSE(s == s5);
}

TEST(specSetTests, not_equals_operator) {
    std::set<cunits<int>> s{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    std::set<cunits<int>> s2{{1, 2}, {4, 6}, {8, 10}};
    EXPECT_FALSE(s != s2);

    std::set<cunits<int>> s3{{1, 2}, {4, 6}, {8, 11}};
    EXPECT_TRUE(s != s3);

    std::set<cunits<int>> s4{{1, 2}, {4, 6}};
    EXPECT_TRUE(s != s4);

    std::set<cunits<int>> s5{{1, 2}, {4, 6}, {8, 10}, {11, 12}};
    EXPECT_TRUE(s != s5);
}

TEST(specSetTests, set_set_intersection) {
    std::set<cunits<int>> expected{{5, 10}};

    std::set<cunits<int>> s1{{1, 10}};
    std::set<cunits<int>> s2{{5, 15}};

    auto result = std::intersection(s1, s2);
    EXPECT_EQ(result, expected);

    result = std::intersection(s2, s1);
    EXPECT_EQ(result, expected);

    result = std::intersection(s1, s1);
    EXPECT_EQ(result, s1);

    result = std::intersection(s2, s2);
    EXPECT_EQ(result, s2);

    result = std::intersection(s1, std::set<cunits<int>>{});
    EXPECT_EQ(result, std::set<cunits<int>>{});

    result = std::intersection(std::set<cunits<int>>{}, s1);
    EXPECT_EQ(result, std::set<cunits<int>>{});

    result = std::intersection(std::set<cunits<int>>{}, std::set<cunits<int>>{});
    EXPECT_EQ(result, std::set<cunits<int>>{});
}

TEST(specSetTests, cunits_set_intersection) {
    std::set<cunits<int>> expected1{{5, 10}};
    std::set<cunits<int>> expected2{{1, 5}};

    std::set<cunits<int>> s{{1, 10}};
    cunits cu1{5, 15};
    cunits cu2{1, 5};

    auto result = std::intersection(cu1, s);
    EXPECT_EQ(result, expected1);

    result = std::intersection(s, cu1);
    EXPECT_EQ(result, expected1);

    result = std::intersection(cu2, s);
    EXPECT_EQ(result, expected2);

    result = std::intersection(s, cu2);
    EXPECT_EQ(result, expected2);
}

TEST(specSetTests, cunit_cunit_intersection) {
    cunits cu1{5, 15};
    cunits cu2{1, 5};
    cunits cu3{5, 10};

    std::set<cunits<int>> expected1{{5, 10}};
    std::set<cunits<int>> expected2{};

    auto result = std::intersection(cu1, cu3);
    EXPECT_EQ(result, expected1);

    result = std::intersection(cu3, cu1);
    EXPECT_EQ(result, expected1);

    result = std::intersection(cu1, cu2);
    EXPECT_EQ(result, expected2);

    result = std::intersection(cu2, cu1);
    EXPECT_EQ(result, expected2);

    result = std::intersection(cu1, cu1);
    EXPECT_EQ(result, std::set<cunits<int>>{cu1});

    result = std::intersection(cu2, cu2);
    EXPECT_EQ(result, std::set<cunits<int>>{cu2});

    result = std::intersection(cu3, cu3);
    EXPECT_EQ(result, std::set<cunits<int>>{cu3});

    result = std::intersection(cu1, cunits<int>());
    EXPECT_EQ(result, std::set<cunits<int>>{});

    result = std::intersection(cunits<int>(), cu1);
    EXPECT_EQ(result, std::set<cunits<int>>{});

    result = std::intersection(cunits<int>(), cunits<int>());
    EXPECT_EQ(result, std::set<cunits<int>>{});
}

TEST(specSetTests, find_cunit) {
    std::set<cunits<int>> s{{1, 2},
                            {4, 6},
                            {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    auto to_find = cunits{4, 6};
    auto result = s.find(to_find);
    EXPECT_NE(result, s.end());
    EXPECT_EQ(*result, to_find);

    to_find = cunits{4, 5};
    auto expected = cunits{4, 6};
    result = s.find(to_find);
    EXPECT_NE(result, s.end());
    EXPECT_EQ(*result, expected);
}

TEST(specSetTests, contains_cunit) {
    std::set<cunits<int>> s{{1, 2},
                            {4, 6},
                            {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    auto to_find = cunits{4, 6};
    EXPECT_TRUE(s.contains(to_find));

    to_find = cunits{4, 5};
    EXPECT_TRUE(s.contains(to_find));

    to_find = cunits{4, 7};
    EXPECT_FALSE(s.contains(to_find));
}

TEST(specSetTests, find_value) {
    std::set<cunits<int>> s{{1, 2},
                            {4, 6},
                            {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    auto expected = cunits{4, 6};
    auto result = s.find(5);
    EXPECT_NE(result, s.end());
    EXPECT_EQ(*result, expected);

    result = s.find(4);
    EXPECT_NE(result, s.end());
    EXPECT_EQ(*result, expected);

    result = s.find(6);
    EXPECT_EQ(result, s.end());
}

TEST(specSetTests, contains_value) {
    std::set<cunits<int>> s{{1, 2},
                            {4, 6},
                            {8, 10}};
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 3);

    EXPECT_TRUE(s.contains(5));
    EXPECT_TRUE(s.contains(4));
    EXPECT_FALSE(s.contains(6));
}

TEST(specSetTests, from_vector_to_set) {

    std::vector<int> v{1, 2, 3, 4, 6, 7, 8, 12, 14, 15, 16, 17, 18, 19, 20};
    std::set<cunits<int>> expected{{1, 5},
                                   {6, 9},
                                   {12, 13},
                                   {14, 21}};

    auto result = std::set<cunits<int>>::from_vector(v);
    EXPECT_EQ(result, expected);

    v = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    expected = {{1, 10}};

    result = std::set<cunits<int>>::from_vector(v);
    EXPECT_EQ(result, expected);
}

TEST(specSetTests, from_set_of_int_to_set) {
    std::set<int> s{1, 2, 3, 4, 6, 7, 8, 12, 14, 15, 16, 17, 18, 19, 20};
    std::set<cunits<int>> expected{{1, 5},
                                   {6, 9},
                                   {12, 13},
                                   {14, 21}};

    auto result = std::set<cunits<int>>::from_set_of(s);
    EXPECT_EQ(result, expected);

    s = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    expected = {{1, 10}};

    result = std::set<cunits<int>>::from_set_of(s);
    EXPECT_EQ(result, expected);
}

TEST(specSetTests, to_vector) {
    std::set<cunits<int>> s{{1, 5},
                            {6, 9},
                            {12, 13},
                            {14, 21}};
    std::vector<int> expected{1, 2, 3, 4, 6, 7, 8, 12, 14, 15, 16, 17, 18, 19, 20};

    auto result = s.to_vector();
    EXPECT_EQ(result, expected);

    s = {{1, 10}};
    expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    result = s.to_vector();
    EXPECT_EQ(result, expected);
}

TEST(specSetTests, to_set_of_int) {
    std::set<cunits<int>> s{{1, 5},
                            {6, 9},
                            {12, 13},
                            {14, 21}};
    std::set<int> expected{1, 2, 3, 4, 6, 7, 8, 12, 14, 15, 16, 17, 18, 19, 20};

    auto result = s.to_set_of();
    EXPECT_EQ(result, expected);

    s = {{1, 10}};
    expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    result = s.to_set_of();
    EXPECT_EQ(result, expected);
}