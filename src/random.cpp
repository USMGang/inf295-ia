#include "random.h"
#include "problem.h"

void Random::initSeed(unsigned seed_aux){
    if (!initialized){
        instance = new Random(seed_aux);
        initialized = true;
    }
}

Random& Random::getRandomMotor(){
    if (!initialized){
        cerr << "El motor de numeros random aun no ha sido inicializado." << endl;
    }
    return *instance;
}

Random::Random(unsigned seed_aux){
    seed = seed_aux;
    gen = mt19937(seed);

    probability = uniform_real_distribution<float>(0.0, 1.0);
    entity = uniform_int_distribution<int>(0, Problem::getInstance().n_entities - 1);
    room = uniform_int_distribution<int>(0, Problem::getInstance().n_rooms - 1);
}

float Random::getProbability(){
    return probability(gen);
}

int Random::getRandomEntity(){
    return entity(gen);
}

int Random::getRandomRoom(){
    return room(gen);
}

vector<Entity> Random::getRandEntities(){
    vector<Entity> entities = Problem::getInstance().entities;
    shuffle(entities.begin(), entities.end(), gen);
    return entities;
}

vector<Room> Random::getRandRooms(){
    vector<Room> rooms = Problem::getInstance().rooms;
    shuffle(rooms.begin(), rooms.end(), gen);
    return rooms;
}
