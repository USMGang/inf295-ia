#include "globals.h"
#include "problem.h"
#include "random.h"
#include "greedy.h"
#include "simulated_anneling.h"

#define SEED 6911

int main(){
    // Inicializar las variables necesarias

    ofstream outfile("SVe150.csv");
    outfile << "initial_solution,final_solution\n";

    for (int i=0; i<36; i++){
        Problem::initInstance(SVe150, i);
        Random::initSeed(SEED);
        Solution s = Solution();

        // Obtener una solucion inicial con enfoque greedy
        int neighbors = s.p.n_entities/4;
        getInitialSolution(s, neighbors);
        outfile << s.quality << ",";

        // Mejorar nuestra solucion inicial con simulated annealing
        simulatedAnnealing(s, 10000);
        outfile << s.quality << "\n";
    }

    outfile.close();

    return 0;
}
