#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <queue>
#include <vector>

// Nombre de messages émis avec succès par chaque capteur
#define def_MAX 1e3

// Nombre de capteurs
#define def_K 5

// Paramètres de loi exponentielle
#define def_lambda 10
#define def_mu 0.25
#define def_init 0.1

// Résultats de simulation nécessaires (TODO)

// Loi exponentielle
double expo(double param)
{
    double tmp = (double)random() / RAND_MAX;
    return -log(tmp) / param;
}

// Event
struct Event
{
    // 0 = debut_emission ; 1 = fin_emission ; 2 = debut_init ;
    int type;
    int id_sensor;
    double time;
};
struct Event_comp
{
    bool operator()(const Event &lhs, const Event &rhs) { return lhs.time < rhs.time; }
};

struct Sensor
{
    int current_state;
    int transmitted;
};

std::vector<Sensor> sensors;

// Echeancier
int current_emiting = -1;

// TODO adapter l'écheancier
std::priority_queue<Event, std::vector<Event>, Event_comp> echeancier;

// TODO : actualiser temps ;
//        stats
void traitement_event(Event &e)
{
    if (e.type == 0)
        if (current_emiting != -1)
            traitement_collision(e);
        else
        {
            sensors[e.id_sensor].current_state++;
            current_emiting = event.id_sensor;
            ajouter(fin_emission, t + expo(lambda))
        }

    else if (e.type == 1)
    {
        current_emiting = -1;
        sensors[e.id_sensor].transmitted++;
        sensors[e.id_sensor].current_state = 0;
        ajouter(debut_emission, t + expo(init));
    }

    else
    {
        ajouter(debut_emission, t + expo(init));
    }
}

void traitement_collision(Event &e)
{
    time = t.collision;
    supprimer(fin_emission);

    if (sensors[e.id_sensor].current_state < 13)
    {
        sensors[e.id_sensor].current_state++;
        ajouter(debut_emission, t + expo(mu));
    }

    if (sensors[current_emiting].current_state < 13)
    {
        sensors[current_emiting].current_state++;
        ajouter(debut_emission, t + expo(mu));
    }
    current_emiting = -1;
}

void simulateur()
{
    double time = 0.0;
    // Init simulation
    for (int i = 0; i < def_K; i++)
    {
        sensors.push_back(0);
        // ajouter(debut_init, time);
    }
}

int main(int argc, char **argv)
{
    simulateur();
    return 0;
}
