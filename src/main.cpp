#include "globals.h"
#include "problem.h"
#include "random.h"
#include "greedy.h"
#include "simulated_anneling.h"

#define SEED 6911

int main(){
    // Inicializar las variables necesarias
    Problem::initInstance(PNe150, 0);
    Random::initSeed(SEED);
    Solution s = Solution();

    // Obtener una solucion inicial con enfoque greedy
    // int neighbors = s.p.n_entities/2;
    int neighbors = 10;
    getInitialSolution(s, neighbors);

    // cout << s << endl;
    cout << s.quality << endl;

    // Mejorar nuestra solucion inicial con simulated annealing
    // simulatedAnnealing(s, 1000);
    // cout << s.quality << endl;

    return 0;
}
