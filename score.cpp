#include "score.hpp"

void checkScore(int score, float *taux_spawn)
{
    // Modifie la difficulte en fonction du score
    if (score > 14000)
    {
        *taux_spawn = 0.5;
    }
    else if (score > 12000)
    {
        *taux_spawn = 0.6;
    }
    else if (score > 10000)
    {
        *taux_spawn = 0.7;
    }
    else if (score > 8000)
    {
        *taux_spawn = 0.8;
    }
    else if (score > 6000)
    {
        *taux_spawn = 0.9;
    }
    else if (score > 4000)
    {
        *taux_spawn = 1.0;
    }
    else if (score > 2000)
    {
        *taux_spawn = 1.1;
    }
    else
    {
        *taux_spawn = 1.2;
    }
}
