#ifndef GLOBALS_H
#define GLOBALS_H

#include <bits/stdc++.h>
using namespace std;

// ========== Dataset ==========
#define PNe150 1
#define SVe150 2

// ========== Restricciones ==========
#define HARD 1
#define SOFT 0

#define VIOLATED_HARD_FACTOR 100

#define ALLOCATION_CONSTRAINT		0 // C1 represents the room that the entity should be allocated to. C2 unused (-1)
#define NONALLOCATION_CONSTRAINT	1 // C1 represents the room that the entity should not be allocated to. C2 unused (-1)
#define ONEOF_CONSTRAINT			2 // Not used in these instances
#define CAPACITY_CONSTRAINT			3 // C1 represents the room that should not be overused. C2 unused (-1)
#define SAMEROOM_CONSTRAINT			4 // C1 and C2 represent two entities that should be in the same room
#define NOTSAMEROOM_CONSTRAINT		5 // C1 and C2 represent two entities that should not be in the same room
#define NOTSHARING_CONSTRAINT		6 // C1 represents the entity that should not share the room. C2 unused (-1)
#define ADJACENCY_CONSTRAINT		7 // C1 and C2 represent two entities that should be in adjacent rooms
#define NEARBY_CONSTRAINT			8 // C1 and C2 represent two entities that should be in near rooms (same floor)
#define AWAYFROM_CONSTRAINT			9 // C1 and C2 represent two entities that should not be in near rooms (different floors)

inline vector<int> CONSTRAINT_WEITGHTS = {20, 10, 10, 10, 10, 10, 50, 10, 10, 10};

#define QUALITY_SPACE 0.6
#define QUALITY_CONSTRAINTS 0.4

// ========== Structs  ==========
struct Entity {
    int eid;
    int gid;
    float space;
};

struct Room {
    int rid;
    int fid;
    float space;
    vector<int> adj_list;
};

struct Constraint {
    int cid;
    int c1;
    int c2;
};

inline ostream& operator<<(ostream& os, const Constraint& c) {
    os << "cid: " << c.cid << ", c1: " << c.c1 << ", c2: " << c.c2;
    return os;
}

#endif
