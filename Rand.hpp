#pragma once

#include <random>

class Rand {
private:
    std::mt19937 m_random_engine;
    std::uniform_int_distribution<int> m_dist;

public:
    Rand()
            : m_random_engine(std::random_device{}()),
              m_dist{1, 10} {}

    Rand(int min, int max)
            : m_random_engine(std::random_device{}()),
              m_dist{min, max} {}

    int get() {
        return m_dist(m_random_engine);
    }

    int get(int min, int max) {
        std::uniform_int_distribution dist(min, max);
        return dist(m_random_engine);
    }
};

// RepeatRand is a random number generator without a random device,
// to deliver the same sequence of numbers every time.
class RepeatRand {
private:
    unsigned int m_seed{5647};
    std::mt19937 m_random_engine;
    std::uniform_int_distribution<int> m_dist;

public:

    RepeatRand() :
              m_random_engine(m_seed),
              m_dist{1, 10} {}

    RepeatRand(int min, int max) :
              m_random_engine(m_seed),
              m_dist{min, max} {}


    void set_seed(unsigned int seed) {
        m_seed = seed;
        m_random_engine.seed(m_seed);
    }

    int get() {
        return m_dist(m_random_engine);
    }

    int get(int min, int max) {
        std::uniform_int_distribution dist(min, max);
        return dist(m_random_engine);
    }
};