#include "instance.h"

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

Problem getInstance(int dataset, int index){

    // Definir el struct del problema
    Problem p;

    // Abrir el archivo
    string file_name = getInstanceName(dataset, index, "./instances");
    ifstream file(file_name);
    if (!file){
        cerr << "File not found" << endl;
        return Problem {};
    }

    string line;

    // Definir los atributos principales del problema
    int* p_start = &p.n_entities;
    for (int i=0; i<6; i++){
        getline(file, line);

        istringstream iss(line);
        iss.ignore(numeric_limits<streamsize>::max(), ':');
        iss >> *(p_start + i);
    }

    // Definir las listas para las entidades y restricciones
    p.entities.resize(p.n_entities);
    p.rooms.resize(p.n_rooms);

    // Definir las entidades
    getline(file, line);
    getline(file, line);
    for (int i=0; i<p.n_entities; i++){
        Entity e;
        getline(file, line);

        istringstream iss(line);
        iss >> e.eid >> e.gid >> e.space;
        p.entities[i] = e;
    }

    // Definir las habitaciones
    getline(file, line);
    getline(file, line);
    for (int i=0; i<p.n_rooms; i++){
        Room r;
        getline(file, line);

        istringstream iss(line);
        iss >> r.rid >> r.fid >> r.space;
        int aux;
        int n; iss >> n;
        for (int j=0; j<n; j++){
            iss >> aux;
            r.adj_list.push_back(aux);
        }
        p.rooms[i] = r;
    }

    // Definir las restricciones
    getline(file, line);
    getline(file, line);
    p.constraints = vector<vector<map<int, Constraint>>>(2, vector<map<int, Constraint>>(10));
    for (int i=0; i<p.n_constraints; i++){
        Constraint c;
        getline(file, line);
        
        int type, is_hard;
        istringstream iss(line);
        iss >> c.cid >> type >> is_hard >> c.c1 >> c.c2;

        p.constraints[is_hard][type][c.c1] = c;
    }

    return p;
}
