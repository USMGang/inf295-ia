#include "greedy.h"
#include "globals.h"
#include "random.h"

void satisfyHardConstraints(Solution &s, vector<Entity> &entities_shuffled, vector<Room> &rooms_shuffled){
    Problem &p = s.p;
    vector<int> banned_entities;
    vector<int> banned_rooms = vector<int>(p.n_rooms, -1);

    //Agregar las entidades que tienen restricciones de alojamiento
    for (auto &m: p.constraints[HARD][ALLOCATION_CONSTRAINT]){
        if (m.second == nullptr){ continue; }
        const Constraint &c = *m.second;

        s.addEntity(c.c1, c.c2);
        banned_entities.push_back(c.c1);
    }

    for (auto &m: p.constraints[HARD][NOTSHARING_CONSTRAINT]){
        if (m.second == nullptr){ continue; }

        int aux_space;
        const Constraint &c = *m.second;


        int best_rid = 0;
        int best_room = 1000000;
        bool found_first_room = false;
        for (int i = 0; i < p.n_rooms; i++) {
            banned_entities.push_back(c.c1);
            if (s.verifyRoom(p.entities[c.c1]->space, i)) {
                aux_space = s.rooms_space[i] - p.entities[c.c1]->space;

                if (!found_first_room && banned_rooms[i] == -1) {
                    // Si aún no se ha encontrado la primera habitación adecuada y no está prohibida
                    best_rid = i;
                    best_room = aux_space;
                    found_first_room = true;
                } else if (banned_rooms[i] == -1) {
                    // Continuar buscando la mejor habitación después de encontrar la primera adecuada
                    if (p.constraints[HARD][NONALLOCATION_CONSTRAINT][c.c1] != nullptr) {
                        if (aux_space > 0 && aux_space < best_room && p.constraints[HARD][NONALLOCATION_CONSTRAINT][c.c1]->c2 != i) {
                            best_rid = i;
                            best_room = aux_space;
                        }
                    }
                }
            }
        }

        banned_rooms[best_rid] = c.c1;
        s.addEntity(c.c1, best_rid);
    }

    // Eliminar las entidades y habitaciones prohibidas
    for (auto eid: banned_entities){
        auto it = find_if(entities_shuffled.begin(), entities_shuffled.end(), [eid](Entity &e){
            return e.eid == eid;
        });

        if (it != entities_shuffled.end()){
            entities_shuffled.erase(it);
        }
    }

    for (auto rid: banned_rooms){
        if (rid != -1){
            auto it = find_if(rooms_shuffled.begin(), rooms_shuffled.end(), [rid](Room &r){
                return r.rid == rid;
            });

            if (it != rooms_shuffled.end()){
                rooms_shuffled.erase(it);
            }
        }
    }

    s.setSolutionQuality();
}

void getInitialSolution(Solution &s, int neighbors){
    // Obtener las entidades y habitaciones mezcladas aleatoriamente
    Random &r = Random::getRandomMotor();
    vector<Entity> entities_shuffled = r.getRandEntities();
    vector<Room> rooms_shuffled = r.getRandRooms();

    // Agregar la primera entidad.
    bool finded_room;
    int room_selected;
    satisfyHardConstraints(s, entities_shuffled, rooms_shuffled); 
    vector<Solution> aux_solutions = vector<Solution>(neighbors, s);

    //Colocar cada entidad en una habitacion
    for (auto &e: entities_shuffled){

        // Por solucion, intentar colocar la entidad en una habitacion
        for (int j=0; j<neighbors; j++){

            finded_room = false;
            for (int i=0; i<int(rooms_shuffled.size()); i++){
                room_selected = (j + i) % rooms_shuffled.size();
                if (aux_solutions[j].verifyRoom(e.space, rooms_shuffled[room_selected].rid)){
                    break;
                }
            }

            if (!finded_room){
                room_selected = r.getRandomIndex(rooms_shuffled.size());
            }

            // cout << "Vecino " << j << " - Entidad " << eid << " - Habitacion " << rooms_shuffled[room_selected].rid << endl;
            aux_solutions[j].addEntity(e.eid, rooms_shuffled[room_selected].rid);
            aux_solutions[j].setSolutionQuality();

        }

        // Buscar la solucion con mejor calidad para el siguiente paso
        sort(aux_solutions.begin(), aux_solutions.end(), [](Solution &a, Solution &b){
            return a.quality < b.quality;
        });

        s = aux_solutions[0];
    }
}
