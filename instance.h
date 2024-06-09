#include <bits/stdc++.h>
using namespace std;

// ========== Dataset ==========
#define PNe150 1
#define SVe150 2

// ========== Entidades ==========
struct Entity {
    int eid;
    int gid;
    float space;
};

inline ostream& operator<<(ostream& os, const Entity& e) {
    os << "[" << e.eid << "]: " << "Grupo: " << e.gid << ", Espacio: " << e.space << endl;
    return os;
}

// ========== Habitaciones ==========
struct Room {
    int rid;
    int fid;
    float space;
    vector<int> adj_list;
};

inline ostream& operator<<(ostream& os, const Room& r) {
    os << "[" << r.rid << "]: " << "Piso: " << r.fid << ", Espacio: " << r.space;;
    os << ", Adjacency List: [";
    for (size_t i = 0; i < r.adj_list.size(); ++i) {
        os << r.adj_list[i];
        if (i != r.adj_list.size() - 1) {
            os << ", ";
        }
    }
    os << "]" << endl;
    return os;
}

// ========== Restricciones ==========
#define HARD 1
#define SOFT 0

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

struct Constraint {
    int cid;
    int c1;
    int c2;
};

// inline ostream& operator<<(ostream& os, const Constraint& c) {
//     string type;
//     switch (c.type) {
//         case ALLOCATION_CONSTRAINT: type = "Allocation"; break;
//         case NONALLOCATION_CONSTRAINT: type = "Nonallocation"; break;
//         case ONEOF_CONSTRAINT: type = "OneOf"; break;
//         case CAPACITY_CONSTRAINT: type = "Capacity"; break;
//         case SAMEROOM_CONSTRAINT: type = "SameRoom"; break;
//         case NOTSAMEROOM_CONSTRAINT: type = "NotSameRoom"; break;
//         case NOTSHARING_CONSTRAINT: type = "NotSharing"; break;
//         case ADJACENCY_CONSTRAINT: type = "Adjacency"; break;
//         case NEARBY_CONSTRAINT: type = "Nearby"; break;
//         case AWAYFROM_CONSTRAINT: type = "AwayFrom"; break;
//         default: type = "Unknown"; break;
//     }
//
//     string is_hard = c.is_hard ? "Hard" : "Soft";
//
//     os << "[" << c.cid << "]: " << "Type: " << type << ", Hard: " << is_hard;
//     os << ", C1: " << c.c1 << ", C2: " << c.c2 << endl;
//     return os;
// }

// ========== Problem ==========
struct Problem {
    int n_entities;
    int n_rooms;
    int n_floors;
    int n_constraints;
    int n_hard_constraints;
    int n_soft_constraints;

    vector<Entity> entities;
    vector<Room> rooms;
    vector<vector<map<int, Constraint>>> constraints;
};

inline ostream& operator<<(ostream& os, const Problem& p) {
    os << "Entities: " << p.n_entities << endl;
    os << "Rooms: " << p.n_rooms << endl;
    os << "Floors: " << p.n_floors << endl;
    os << "Constraints: " << p.n_constraints << endl;
    os << "Hard Constraints: " << p.n_hard_constraints << endl;
    os << "Soft Constraints: " << p.n_soft_constraints << endl;
    return os;
}

// En esta funcion, el index 0 para el dataset PNe150 es p000_n000.txt y para SVe150 es s000_v000.txt
Problem getInstance(int dataset, int index);
