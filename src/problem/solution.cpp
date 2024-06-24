#include "solution.h"
#include "globals.h"
#include "random.h"

Solution::Solution(){
    unused_space = 0;
    overused_space = 0;
    hard_constraint_value = 0;
    soft_constraint_value = 0;
    quality = 0;

    solution.assign(p.n_entities, -1);

    for (int i=0; i<p.n_rooms; i++){
        rooms_space.push_back(p.rooms[i]->space);
    }
}

Solution::Solution(const Solution& other)
    :   p(other.p), solution(other.solution), rooms_space(other.rooms_space),
        unused_space(other.unused_space), overused_space(other.overused_space), hard_constraint_value(other.hard_constraint_value),
        soft_constraint_value(other.soft_constraint_value), quality(other.quality) {}

Solution& Solution::operator=(const Solution& other) {
    if (this != &other) {
        solution = other.solution;
        rooms_space = other.rooms_space;
        unused_space = other.unused_space;
        overused_space = other.overused_space;
        hard_constraint_value = other.hard_constraint_value;
        soft_constraint_value = other.soft_constraint_value;
        quality = other.quality;
    }
    return *this;
}

bool Solution::verifyRoom(float needed_space, int rid){
    if (rooms_space[rid] - needed_space <= 0){
        return false;
    }
    return true;
}

int Solution::nextRoomGreedy(int start, int neighbor, float needed_space, vector<Room> &rooms_shuffled){
    Random &r = Random::getRandomMotor();
    int n_rooms = rooms_shuffled.size();
    start = (start + neighbor) % n_rooms;

    for (int i=0; i<n_rooms; i++){
        if (rooms_space[rooms_shuffled[start].rid] - needed_space >= 0){
            return start;
        }
        start = (start + 1) % n_rooms;
    }

    while(true){
        int rid = r.getRandomRoom();
        auto it = find_if(rooms_shuffled.begin(), rooms_shuffled.end(), [rid](Room &r){
            return r.rid == rid;
        });

        if (it != rooms_shuffled.end()){
            return rid;
        }
    }
}

void Solution::addEntity(int eid, int rid){
    solution[eid] = rid;
    rooms_space[rid] -= p.entities[eid]->space;
}

void Solution::deleteEntity(int eid, int rid){
    solution[eid] = -1;
    rooms_space[rid] += p.entities[eid]->space;
}

int Solution::verifyConstraints(int constraint_type){
    int weight = 0;
    bool violated_constraint = false;
    int type_factor = (constraint_type == HARD) ? VIOLATED_HARD_FACTOR : 1;

    // Revisar por los distintos tipos de restricciones
    for (int i=0; i<10; i++){
        for (auto &m: p.constraints[constraint_type][i]){
            if (m.second == nullptr){ continue; }

            const Constraint& c = *m.second;

            switch(i){
                case ALLOCATION_CONSTRAINT:
                    if (solution[c.c1] != c.c2 && solution[c.c1] != -1){ violated_constraint = true; } 
                    break;

                case NONALLOCATION_CONSTRAINT:
                    if (solution[c.c1] == c.c2 && solution[c.c1] != -1){ violated_constraint = true; }
                    break;

                case CAPACITY_CONSTRAINT:
                    if (rooms_space[c.c1] < 0){ violated_constraint = true; }
                    break;

                case SAMEROOM_CONSTRAINT:
                    if (solution[c.c1] == -1 || solution[c.c2] == -1){ break; }
                    if (solution[c.c1] != solution[c.c2]){ violated_constraint = true; }
                    break;

                case NOTSAMEROOM_CONSTRAINT:
                    if (solution[c.c1] == -1 || solution[c.c2] == -1){ break; }
                    if (solution[c.c1] == solution[c.c2]){ violated_constraint = true; }
                    break;

                case NOTSHARING_CONSTRAINT: {
                    for (int j=0; j<p.n_entities; j++){
                        if (solution[j] == solution[c.c1] && solution[c.c1] != -1 && j != c.c1){
                            violated_constraint = true;
                            break;
                        }
                    }
                    break;
                }

                case ADJACENCY_CONSTRAINT: {
                    if (solution[c.c1] == -1 || solution[c.c2] == -1){ break; }
                    const Room& r1 = *p.rooms[solution[c.c1]];
                    const Room& r2 = *p.rooms[solution[c.c2]];

                    auto it = find(r1.adj_list.begin(), r1.adj_list.end(), r2.rid);
                    if (it == r1.adj_list.end()){ violated_constraint = true; }
                    break;
                }

                default:
                    break;
            }

            if (violated_constraint){
                weight += CONSTRAINT_WEITGHTS[i] * type_factor;
                violated_constraint = false;
            }                
        }
    }

    return weight;
}

void Solution::setSolutionQuality(){
    // Resetear los valores de espacio y restricciones
    unused_space = 0; 
    overused_space= 0;
    hard_constraint_value = 0;
    soft_constraint_value = 0;

    // Calcular el espacio utilizado
    for (int i=0; i<p.n_rooms; i++){
        if (rooms_space[i] >= 0 && rooms_space[i] != p.rooms[i]->space){
            unused_space += rooms_space[i];
        }

        if (rooms_space[i] < 0){
            overused_space += rooms_space[i];
        }
    }

    // Revisar si se rompen las restricciones
    hard_constraint_value += verifyConstraints(HARD);
    soft_constraint_value += verifyConstraints(SOFT);

    // float _space = QUALITY_SPACE * (unused_space + (-2 * overused_space));
    float _space = 0;
    for (int i=0; i<p.n_rooms; i++){
        int aux = (rooms_space[i] != p.rooms[i]->space) ? rooms_space[i] : 0;
        _space += max((p.rooms[i]->space - aux), (2*(aux - p.rooms[i]->space)));
    }

    // Calcular la calidad de la solucion.
    quality = (QUALITY_SPACE * _space) + (QUALITY_CONSTRAINTS * soft_constraint_value) + hard_constraint_value;
}

Solution Solution::getNeighborSolution(){
    Random &r = Random::getRandomMotor();

    Solution s = Solution(*this);

    // Poner la entidad
    // int eid = r.getRandomEntity();
    // int rid = r.getRandomRoom();
    //
    // s.deleteEntity(eid, solution[eid]);
    // s.addEntity(eid, rid);

    // Swap
    int eid1 = r.getRandomEntity();
    int eid2 = r.getRandomEntity();
    int rid1 = solution[eid1];
    int rid2 = solution[eid2];

    s.deleteEntity(eid1, rid1);
    s.deleteEntity(eid2, rid2);
    s.addEntity(eid1, rid2);
    s.addEntity(eid2, rid1);

    s.setSolutionQuality();

    return s;
}
