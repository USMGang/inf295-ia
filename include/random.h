#ifndef RANDOM_H
#define RANDOM_H

#include "globals.h"

class Random {
public:
    static void initSeed(unsigned seed);
    static Random& getRandomMotor();

    Random(const Random&) = delete;
    void operator=(const Random&) = delete;

    float getProbability();
    int getRandomEntity();
    int getRandomRoom();
    int getRandomIndex(int max);

    vector<Entity> getRandEntities();
    vector<Room> getRandRooms();

private:
    Random(unsigned seed);

    unsigned seed;
    mt19937 gen;
    uniform_real_distribution<float> probability;
    uniform_int_distribution<int> entity;
    uniform_int_distribution<int> room;

    static inline Random* instance = nullptr;
    static inline bool initialized = false;
};

#endif
