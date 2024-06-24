#include "problem.h"

void Problem::initInstance(int dataset, int index){
    if (!initialized){
        instance = new Problem(dataset, index);
        initialized = true;
    }
}

Problem& Problem::getInstance(){
    if (!initialized){
        cerr << "El problema aun no ha sido inicializado." << endl;
    }
    return *instance;
}

string getInstanceName(int dataset, int index, string path){
    char buffer[14];
    string dataset_name;

    int n = index % 6;
    int m = index / 6;

    switch (dataset){
        case PNe150:
            sprintf(buffer, "p%03d_n%03d.txt", 5 * m, 5 * n);
            dataset_name = path + "/PNe150/" + buffer;
            break;
        case SVe150:
            sprintf(buffer, "s%03d_v%03d.txt", 20 * m, 20 * n);
            dataset_name = path + "/SVe150/" + buffer;
            break;
            break;
        default:
            sprintf(buffer, "s%03d_v%03d.txt", 20 * m, 20 * n);
            dataset_name = path + "/SVe150/" + buffer;
            break;
    }

    return dataset_name;
}

Problem::Problem(int dataset, int index){

    // Abrir el archivo
    string file_name = getInstanceName(dataset, index, "./instances");
    ifstream file(file_name);
    if (!file){
        cerr << "File not found" << endl;
    }

    string line;

    // Definir los atributos principales del problema
    int* p_start = &n_entities;
    for (int i=0; i<6; i++){
        getline(file, line);

        istringstream iss(line);
        iss.ignore(numeric_limits<streamsize>::max(), ':');
        iss >> *(p_start + i);
    }

    // Definir las listas para las entidades y restricciones
    entities.resize(n_entities);
    rooms.resize(n_rooms);

    // Definir las entidades
    getline(file, line);
    getline(file, line);
    for (int i=0; i<n_entities; i++){
        getline(file, line);
        int eid, gid;
        float space;

        istringstream iss(line);
        iss >> eid >> gid >> space;
        entities[i] = make_unique<Entity>();
        entities[i]->eid = eid;
        entities[i]->gid = gid;
        entities[i]->space = space;
    }

    // Definir las habitaciones
    getline(file, line);
    getline(file, line);
    for (int i=0; i<n_rooms; i++){
        getline(file, line);
        int rid, fid;
        float space;

        istringstream iss(line);
        iss >> rid >> fid >> space;

        rooms[i] = make_unique<Room>();
        rooms[i]->rid = rid;
        rooms[i]->fid = fid;
        rooms[i]->space = space;

        int aux;
        int n; iss >> n;
        for (int j=0; j<n; j++){
            iss >> aux;
            rooms[i]->adj_list.push_back(aux);
        }
    }

    // Definir las restricciones
    getline(file, line);
    getline(file, line);
    constraints.resize(2);
    for (int i=0; i<2; i++){
        constraints[i].resize(10);
        for (int j=0; j<10; j++){
            for (int k=0; k<n_entities; k++){
                constraints[i][j][k] = nullptr;
            }
        }
    }

    for (int i=0; i<n_constraints; i++){
        getline(file, line);
        
        int cid, c1, c2, type, is_hard;
        istringstream iss(line);
        iss >> cid >> type >> is_hard >> c1 >> c2;

        constraints[is_hard][type][c1] = make_unique<Constraint>();
        constraints[is_hard][type][c1]->cid = cid;
        constraints[is_hard][type][c1]->c1 = c1;
        constraints[is_hard][type][c1]->c2 = c2;
    }

    // Calcular el espacio total que tiene disponible las habitaciones
    total_space = 0;
    for (int i=0; i<n_rooms; i++){
        total_space += rooms[i]->space;
    }
}

void Problem::destroyInstance(){
    delete instance;
    instance = nullptr;
}

Problem::~Problem(){
    entities.clear();
    rooms.clear();
    for (auto& row : constraints) {
        for (auto& m : row) {
            m.clear();
        }
        row.clear();
    }
    constraints.clear();
}
