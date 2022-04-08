#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <queue>

// Nombre de messages émis avec succès par chaque capteur
#define def_MAX 1e3

// Nombre de capteurs
#define def_K 5

// Paramètres de loi exponentielle
#define def_lambda 10
#define def_mu 0.25
#define def_init 0.1

// Event
struct event
{
};

// Echeancier
std::queue<event> echeancier;

// Loi exponentielle
double
expo(double param)
{
    double tmp = (double)random() / RAND_MAX;
    return -log(tmp) / param;
}

void traitement_event()
{
}

void traitement_collision()
{
}

void simulateur()
{
}

int main(int argc, char **argv)
{
    return 0;
}
