#include "instance.h" 

struct Solution {
    vector<int> solution;
    vector<int> rooms_space;
    int space;
    int constraint_value;

    Solution(Problem p){
        space = 0;
        constraint_value = 0;

        solution.resize(p.n_entities);

        for (int i=0; i<p.n_rooms; i++){
            rooms_space.push_back(p.rooms[i].space);
        }
    }

    int verifyRoom(int needed_space, int rid){
        if (rooms_space[rid] - needed_space < 0){
            return 0;
        }

        return 1;
    }

    int addEntity(int eid, int rid, Problem p){
        if (rooms_space[rid] - p.entities[eid].space < 0){
            return 0;
        }

        solution[eid] = rid;
        rooms_space[rid] -= p.entities[eid].space;
        return 1;
    }

    void getInitialSolution(Problem p){
        
        // Agregar las entidades segun las restricciones duras.
        vector<map<int, Constraint>> &c_hard = p.constraints[HARD];

        for (auto &c : c_hard[ALLOCATION_CONSTRAINT]){
            addEntity(c.second.c1, c.second.c2, p);
        }

        for (auto &c : c_hard[SAMEROOM_CONSTRAINT]){
            addEntity(c.second.c1, c.second.c2, p);
        }

    }

    void setSolutionQuality(Problem p){

        // Calcular el espacio utilizado
        for (int i=0; i<p.n_rooms; i++){
            space += p.rooms[i].space - rooms_space[i];
        }
    }

};

