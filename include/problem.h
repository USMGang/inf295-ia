#ifndef PROBLEM_H
#define PROBLEM_H

#include "globals.h"
#include <memory.h>

class Problem {
public:
    static void initInstance(int dataset, int index);
    static Problem& getInstance();

    Problem(const Problem&) = delete;
    void operator=(const Problem&) = delete;
    ~Problem();
    void destroyInstance();

    int n_entities;
    int n_rooms;
    int n_floors;
    int n_constraints;
    int n_hard_constraints;
    int n_soft_constraints;
    float total_space;

    vector<unique_ptr<Entity>> entities;
    vector<unique_ptr<Room>> rooms;
    vector<vector<map<int, unique_ptr<Constraint>>>> constraints;

private:
    Problem(int dataset, int index);
    static inline Problem* instance = nullptr;
    static inline bool initialized = false;

};

#endif
