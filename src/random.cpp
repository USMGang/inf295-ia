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
    const auto& source_entities = Problem::getInstance().entities;
    vector<Entity> entities;
    entities.reserve(source_entities.size());
    for (const auto& e: source_entities){
        entities.push_back(*e);
    }

    shuffle(entities.begin(), entities.end(), gen);
    return entities;
}

vector<Room> Random::getRandRooms(){
    const auto& source_rooms = Problem::getInstance().rooms;
    vector<Room> rooms;
    rooms.reserve(source_rooms.size());
    for (const auto& r: source_rooms){
        rooms.push_back(*r);
    }

    shuffle(rooms.begin(), rooms.end(), gen);
    return rooms;
}
