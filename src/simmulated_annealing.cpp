#include "simulated_anneling.h"
#include "random.h"

void simulatedAnnealing(Solution &s, int max_iter){
    Random &r = Random::getRandomMotor();

    int T = T0;
    int deltaT = DELTAT0;

    int Riter = 0;
    int Rstep = 10 * s.p.n_entities;
    int Dstep = s.p.n_entities/2;
    int iter = 0;

    Solution s_new;

    while (iter < max_iter){

        s_new = s.getNeighborSolution();
        if (s.quality > s_new.quality){
            // swap(s, s_new);
            s = s_new;
        } else {
            if (T == 0){
                Riter++;

                if (Riter % Rstep == 0){
                    T = T0;
                    Riter = 0;
                }
            } else {
                float accept_prob = exp(-abs(s_new.quality - s.quality)/T);
                if (accept_prob > r.getProbability()){
                    // swap(s, s_new);
                    s = s_new;
                }
            }
        }

        iter++;

        if (iter % Dstep == 0){
            T -= deltaT;
        }

        if (T <= 0){
            T = T0;
        }
    }
}


