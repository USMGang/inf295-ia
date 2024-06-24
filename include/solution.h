#ifndef SOLUTION_H
#define SOLUTION_H

#include "globals.h"
#include "problem.h"
#include <utility>

class Solution {
public:
    Problem& p = Problem::getInstance();

    vector<int> solution;
    vector<float> rooms_space;
    float unused_space;
    float overused_space;
    int hard_constraint_value;
    int soft_constraint_value;
    float quality; 

    Solution();
    Solution(const Solution& other);
    Solution& operator=(Solution other);
    ~Solution();

    bool verifyRoom(float needed_space, int rid);
    int nextRoomGreedy(int start, int neighbor, float needed_space, vector<Room> &rooms_shuffled);
    void addEntity(int eid, int rid);
    void deleteEntity(int eid, int rid);
    int verifyConstraints(int constraint_type);
    void getInitialSolution();
    void setSolutionQuality();
    Solution getNeighborSolution();

    friend void swap(Solution& first, Solution& second) noexcept;
};

// Implementación de la función swap
inline void swap(Solution& first, Solution& second) noexcept {
    using std::swap;
    swap(first.solution, second.solution);
    swap(first.rooms_space, second.rooms_space);
    swap(first.unused_space, second.unused_space);
    swap(first.overused_space, second.overused_space);
    swap(first.hard_constraint_value, second.hard_constraint_value);
    swap(first.soft_constraint_value, second.soft_constraint_value);
    swap(first.quality, second.quality);
}

// inline ostream& operator<<(ostream& os, const Solution& s){
//     Problem &_p = s.p;
//     vector<vector<Entity>> solution_rooms = vector<vector<Entity>>(_p.n_rooms);
//
//     for (int i=0; i<int(s.solution.size()); i++){
//         solution_rooms[s.solution[i]].push_back(_p.entities[i]);
//     }
//
//     for (int i=0; i<int(solution_rooms.size()); i++){
//         os << "Habitacion " << i << endl;
//         os << "Espacio original: " << _p.rooms[i].space << endl;
//         os << "Espacio restante: " << s.rooms_space[i] << endl;
//         os << "Entidades: ";
//         for (auto e: solution_rooms[i]){
//             os << "(id: " << e.eid << ", espacio: " << e.space << "), ";
//         }
//         os << endl << endl;
//     }
//
//
//     os << "Espacio Sobrante en habitaciones: " << s.unused_space << endl;
//     os << "Espacio Sobrante en habitaciones sobreocupadas: " << s.overused_space << endl;
//     os << "Valor restricciones duras: " << s.hard_constraint_value << endl;
//     os << "Valor restricciones blandas: " << s.soft_constraint_value << endl;
//     os << "Calidad: " << s.quality << endl;
//     return os;
// }

#endif
