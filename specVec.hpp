#pragma once

#include <vector>
#include <set>
#include <numeric>
#include <initializer_list>
#include <algorithm>
#include "cunits.hpp"

namespace std {
    template<typename T>
    class set<cunits<T>> {
    private:
        using data_type = cunits<T>;
        using adapted_type = vector<data_type>;
        using size_type = T;
        using value_type = T;

        struct data_type_cmp {
            bool operator()(const data_type &lhs, const data_type &rhs) const {
                return lhs.max() <= rhs.min();
            }
        };

        adapted_type m_cus;

        bool verify()
        {
            if (auto i = begin(); i != end())
                for (auto p = i; ++i != end(); ++p)
                    if (p->max() > i->min())
                        return false;

            return true;
        }

    public:
        // ============================= CONSTRUCTORS =============================

        set() = default;

        set(std::initializer_list<data_type> initializer_list) {
            for (const auto &i: initializer_list) {
                insert(i);
            }
        }

        // ============================= OPERATORS =============================

        set &operator=(const set &) = default;

        bool operator < (const set<cunits<T>> &rhs) const {
            return static_cast<adapted_type>(*this) < static_cast<adapted_type>(rhs);
        }

        bool operator()(const data_type &lhs, const data_type &rhs) const {
            return lhs.max() <= rhs.min();
        }

        bool operator == (const set<cunits<T>> &rhs) const {
            if (size() != rhs.size()) {
                return false;
            }

            for(auto i = begin(), j = rhs.begin(); i != end(); ++i, ++j) {
                if(*i != *j) {
                    return false;
                }
            }

            return true;
        }

        // ============================= ITERATORS =============================

        auto begin() const {
            return m_cus.begin();
        }

        auto end() const {
            return m_cus.end();
        }

        // ============================= CAPACITY =============================

        [[nodiscard]] bool empty() const {
            return m_cus.empty();
        }

        auto size() const {
            return m_cus.size();
        }

        // ============================= MODIFIERS =============================

        void clear() {
            m_cus.clear();
        }

        void insert(const data_type &new_cu) {
            auto min = new_cu.min();
            auto max = new_cu.max();
            auto i = std::ranges::upper_bound(m_cus, new_cu, data_type_cmp());
            auto j = i;

            // check if the new unit already exists
            if (std::ranges::find(m_cus, new_cu) != end()) {
                return;
            }

            // look for overlapping intervals on the left
            // and merge them
            if (auto i2 = i; i2 != begin() && (--i2)->max() >= new_cu.min()) {
                --i;
                min = i->min();
            }

            // look for overlapping intervals on the right
            // and merge them
            if (j != end() && new_cu.max() >= j->min()) {
                max = j->max();
                ++j;
            }

            j = m_cus.erase(i, j);
            data_type insert_cu(min, max);
            auto pos = m_cus.insert(j, insert_cu);

            assert(*pos == insert_cu);
            assert(verify());
        }

        void erase(const data_type &new_cu) {
            // find the unit from which we erase
            auto i = std::ranges::lower_bound(m_cus, new_cu, data_type_cmp());

            // check if the unit exists
            assert(i != end());

            const auto erase_cu = *i;
            assert(erase_cu.includes(new_cu));

            i = m_cus.erase(i);

            // check if we need to split the unit

            // check if we need to add a new unit on the right
            if (new_cu.max() < erase_cu.max()) {
                i = m_cus.insert(i, data_type(new_cu.max(), erase_cu.max()));
            }

            // check if we need to add a new unit on the left
            if (erase_cu.min() < new_cu.min()) {
                m_cus.insert(i, data_type(erase_cu.min(), new_cu.min()));
            }

            assert(verify());
        }

        void erase(const typename adapted_type::const_iterator &it) {
            erase(*it);
        }

        bool includes(const data_type &cu) const {
            auto i = std::ranges::upper_bound(m_cus, cu, data_type_cmp());
            return i != begin() && (--i)->includes(cu);
        }

        bool includes(const set<cunits<T>> &cus) const {
            return std::ranges::all_of(cus, [this](const auto &cu) {
                return this->includes(cu);
            });
        }

        // ============================= LOOKUP =============================

        auto find(const data_type &cu) const {
            auto i = std::ranges::upper_bound(m_cus, cu, data_type_cmp());
            return i != begin() && (--i)->includes(cu) ? i : end();
        }

        auto find(const value_type &value) const {
            return find(data_type(value, value + 1));
        }

        bool contains(const data_type &cu) const {
            return find(cu) != end();
        }

        bool contains(const value_type &value) const {
            return find(value) != end();
        }

        auto lower_bound(const data_type &cu) const {
            return std::ranges::lower_bound(m_cus, cu, data_type_cmp());
        }

        auto upper_bound(const data_type &cu) const {
            return std::ranges::upper_bound(m_cus, cu, data_type_cmp());
        }

        // ============================= CONVERSIONS =============================

        static std::set<data_type> from_vector(const std::vector<value_type> &values) {
            std::set<data_type> result;
            auto first = values.begin();
            auto last = values.end();
            while (first != last) {
                auto min_value = *first;
                auto max_value = min_value;
                while (++first != last && *first == max_value + 1) {
                    max_value = *first;
                }
                result.insert(cunits(min_value, max_value + 1));
            }
            return result;
        }

        static std::set<data_type> from_set_of(const std::set<value_type> &values) {
            auto vec = std::vector<value_type>(values.begin(), values.end());
            auto result = from_vector(vec);
            return result;
        }

        std::vector<value_type> to_vector() const {
            std::vector<value_type> result;
            for (const auto &cu: m_cus) {
                for (auto value = cu.min(); value < cu.max(); ++value) {
                    result.push_back(value);
                }
            }
            return result;
        }

        std::set<value_type> to_set_of() const {
            auto vec = to_vector();
            std::set<value_type> result(vec.begin(), vec.end());
            return result;
        }

    };

    // ============================= NON-MEMBER FUNCTIONS =============================

    template<typename T>
    bool operator==(const set<cunits<T>> &lhs, const set<cunits<T>> &rhs) {
        return std::ranges::equal(lhs, rhs);
    }

    template<typename T>
    bool operator!=(const set<cunits<T>> &lhs, const set<cunits<T>> &rhs) {
        return !(lhs == rhs);
    }

    template<typename T>
    std::ostream &operator<<(std::ostream &os, const set<cunits<T>> &cus) {
        os << "{";
        for (auto it = cus.begin(); it != cus.end(); ++it) {
            os << *it;
            if (std::next(it) != cus.end()) {
                os << ", ";
            }
        }
        os << "}";
        return os;
    }

    template<typename T>
    std::istream &operator>>(std::istream &is, set<cunits<T>> &cus) {
        char c;

        is >> c;
        assert(!is.fail() && c == '{');

        for (cunits<T> cu; is >> cu;) {
            cus.insert(cu);
            is >> c;
            if (c == '}') {
                break;
            }
        }

        return is;
    }

    template<typename T>
    set<cunits<T>> intersection(const set<cunits<T>> &lhs, const set<cunits<T>> &rhs) {
        set<cunits<T>> ret;

        auto i = lhs.begin();
        auto j = rhs.begin();

        while (i != lhs.end() && j != rhs.end()) {
            if (i->max() <= j->min()) {
                ++i;
                continue;
            }

            if (j->max() <= i->min()) {
                ++j;
                continue;
            }

            auto min = std::max(i->min(), j->min());
            auto max = std::min(i->max(), j->max());
            ret.insert({min, max});

            if (i->max() < j->max()) {
                ++i;
            } else {
                ++j;
            }
        }

        return ret;
    }

    template<typename T>
    set<cunits<T>> intersection(const cunits<T> &lhs, const set<cunits<T>> &rhs) {
        return intersection(set<cunits<T>>{lhs}, rhs);
    }

    template<typename T>
    set<cunits<T>> intersection(const set<cunits<T>> &lhs, const cunits<T> &rhs) {
        return intersection(lhs, set<cunits<T>>{rhs});
    }

    template<typename T>
    set<cunits<T>> intersection(const cunits<T> &lhs, const cunits<T> &rhs) {
        return intersection(set<cunits<T>>{lhs}, set<cunits<T>>{rhs});
    }

}