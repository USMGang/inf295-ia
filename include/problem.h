#ifndef PROBLEM_H
#define PROBLEM_H

#include "globals.h"

class Problem {
public:
    static void initInstance(int dataset, int index);
    static Problem& getInstance();

    Problem(const Problem&) = delete;
    void operator=(const Problem&) = delete;

    int n_entities;
    int n_rooms;
    int n_floors;
    int n_constraints;
    int n_hard_constraints;
    int n_soft_constraints;
    float total_space;

    vector<Entity> entities;
    vector<Room> rooms;
    vector<vector<map<int, Constraint>>> constraints;

private:
    Problem(int dataset, int index);
    static inline Problem* instance = nullptr;
    static inline bool initialized = false;

};

#endif
