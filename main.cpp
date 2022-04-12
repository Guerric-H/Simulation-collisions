#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <vector>
#include <chrono>
#include <algorithm>

// Nombre de messages émis avec succès par chaque capteur
#define MAX 1000

// Nombre de capteurs
int K = 5;

// Paramètres de loi exponentielle
#define LAMBDA 10
#define MU 0.25
#define INIT 0.1

// Paramètres émission / collision
#define EMISSION_MAX 7
#define COLLISION_MAX 6

// Loi exponentielle
double expo(double param)
{
    static std::mt19937 generator(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    static std::uniform_real_distribution<double> distrib(0, 1);

    return -log(distrib(generator)) / param;
}

// Différents types d'events
enum EventType
{
    BeginEmission,
    EndEmission,
};

// Event
struct Event
{
    EventType type; // Type de l'évènement
    int id_sensor;  // Id du capteur affecté
    double time;    // Temps au départ de l'évènement

    Event(EventType ty, int id, double t) : type(ty), id_sensor(id), time(t) {}
};

struct Sensor
{
    int current_state; // Etat actuel du capteur (i, e1, w1, ...)
    int transmitted;   // Nombre de paquets transmits depuis le départ

    Sensor() : current_state(0), transmitted(0) {}
};

// Variables de la simulation :
std::vector<Event> echeancier; // Structure de stockage des évènements
std::vector<Sensor> sensors;   // Structure de stockage des capteurs
int current_emiting = -1;      // Id du capteur en cours de transmission (-1 si le canal est libre)
double global_time = 0.0;      // Temps de la simulation
std::vector<bool> finished;    // Tableau des fin de transmission (idée)

// Variables de statistiques :
std::vector<int> collisions;         // Nombre de collisions dans chaque état
std::vector<int> trials;             // Nombre de tentatives de transmission
double begin_date_e1, begin_date_e2; // Stockage des dates de début d'émission dans les états e1 et e2
bool write_e1, write_e2;             // Indique si il y a besoin d'écrire le temps d'émission de e1 ou e2

// Retourne l'indice du tableau en fonction de l'état du capteur
int eff_id(int id)
{
    return (id - 1) / 2;
}

void insert_echeancier(Event &&event)
{
    if (echeancier.empty())
    {
        echeancier.emplace_back(event);
        return;
    }

    auto it = echeancier.begin();
    while (event.time < it->time and it != echeancier.end())
        it++;
    echeancier.insert(it, event);
}

void traitement_collision(Event &e)
{

    // Incrémentation des compteurs de collision par sommet
    collisions[eff_id(sensors[e.id_sensor].current_state)]++;
    collisions[eff_id(sensors[current_emiting].current_state)]++;

    // Recherche dans la liste et suppresion de l'evènement EndEmission envoyé par le capteur utilisant le canal
    for (auto it = echeancier.begin(); it != echeancier.end(); ++it)
    {
        if (it->type == EventType::EndEmission)
        {
            echeancier.erase(it);
            break;
        }
    }

    // Si le capteur n'est pas dans l'état e7
    if (sensors[e.id_sensor].current_state < EMISSION_MAX + COLLISION_MAX)
    {
        sensors[e.id_sensor].current_state++; // Passage en w_x
    }
    else
        sensors[e.id_sensor].current_state = 0;

    insert_echeancier(Event(EventType::BeginEmission, e.id_sensor, e.time + expo(MU))); // Le capteur passe en attente pour exp(mu)

    // Si le capteur n'est pas l'état e7
    if (sensors[current_emiting].current_state < EMISSION_MAX + COLLISION_MAX)
    {
        sensors[current_emiting].current_state++; // Passage en w_x
    }
    else
        sensors[current_emiting].current_state = 0;

    insert_echeancier(Event(EventType::BeginEmission, current_emiting, e.time + expo(MU))); // Le capteur passe en attente pour exp(mu)

    // Les deux capteurs passent en attente, le canal est donc libéré
    current_emiting = -1;
}

void traitement_event(Event &e)
{

    // Mise à jour du temps
    global_time = e.time;

    // Début de transmission
    if (e.type == BeginEmission)
    {

        sensors[e.id_sensor].current_state++;                 // Peut importe le statut (collision ou non), c'est une tentative d'émission, donc passage en e_x
        trials[eff_id(sensors[e.id_sensor].current_state)]++; // Incrémentation du nombre de tentatives d'émission

        // Si le canal est déja occupé par une transmission, on gère la collision
        if (current_emiting != -1)
            traitement_collision(e);

        // Le canal est libre donc le capteur l'occupe et prévois une fin de transmission après exp(lambda)
        else
        {
            current_emiting = e.id_sensor;
            insert_echeancier(Event(EventType::EndEmission, e.id_sensor, global_time + expo(LAMBDA)));

            if (sensors[e.id_sensor].current_state == 1) // Capteur en état e1
                begin_date_e1 = global_time;
            if (sensors[e.id_sensor].current_state == 3) // Capteur en état e2
                begin_date_e2 = global_time;
        }
    }

    // Fin de transmission
    else if (e.type == EndEmission)
    {

        // Si les capteurs avant reset sont dans les états e1 ou e2, il faut écrire les temps de transmission dans les fichiers
        if (sensors[e.id_sensor].current_state == 1)
            write_e1 = true;
        else if (sensors[e.id_sensor].current_state == 3)
            write_e2 = true;

        current_emiting = -1;                   // Libération du canal
        sensors[e.id_sensor].current_state = 0; // Ràz du capteur
        sensors[e.id_sensor].transmitted++;     // Incrémentation du nombre de paquets transmits

        if (sensors[e.id_sensor].transmitted >= MAX)
        {
            finished[e.id_sensor] = true; // Si le capteur a transmit ses MAX paquets, il l'indique
        }

        insert_echeancier(Event(EventType::BeginEmission, e.id_sensor, global_time + expo(INIT))); // Ajout de la prochaine transmission à l'échéancier
    }

    else
    {
        std::cout << "Unknown event type, exiting ..." << std::endl;
        exit(-1);
    }
}

enum SimulatorMode
{
    Standard,
    Confiance,
    Histogram,
    Collision,
};

void reset_simulator()
{
    echeancier.clear();
    echeancier.reserve(K + 1);

    sensors.clear();
    sensors.reserve(K + 1);

    current_emiting = -1;
    global_time = 0.0;

    finished.clear();
    finished.reserve(K + 1);

    for (auto &c : collisions)
        c = 0;
    for (auto &t : trials)
        t = 0;

    begin_date_e1 = begin_date_e2 = 0.0;
    write_e1 = write_e2 = false;
}

void simulateur(SimulatorMode mode)
{
    bool run = true;

    // Initialisation variables simulation
    for (int i = 0; i < K; i++)
    {
        sensors.emplace_back(Sensor());
        finished.push_back(false);
        insert_echeancier(Event(EventType::BeginEmission, i, global_time + expo(INIT)));
    }

    // Initialisation variables statistiques
    for (int i = 0; i < EMISSION_MAX; i++)
    {
        collisions.push_back(0);
        trials.push_back(0);
    }

    // Fichiers
    std::ofstream file_standard;
    std::ofstream file_histogram_e1;
    std::ofstream file_histogram_e2;

    // Ouverture en fonction du mode
    if (mode == SimulatorMode::Standard)
    {
        file_standard.open("standard.txt");
        if (not file_standard)
        {
            std::cout << "Erreur lors de l'ouverture du fichier de collisions, fin du programme" << std::endl;
            exit(-2);
        }
    }
    else if (mode == SimulatorMode::Histogram)
    {
        file_histogram_e1.open("hist1.txt");
        if (not file_histogram_e1)
        {
            std::cout << "Erreur lors de l'ouverture du fichier d'histogramme e1, fin du programme" << std::endl;
            exit(-2);
        }
        file_histogram_e2.open("hist2.txt");
        if (not file_histogram_e2)
        {
            std::cout << "Erreur lors de l'ouverture du fichier d'histogramme e2, fin du programme" << std::endl;
            exit(-2);
        }
    }

    // Boucle de la simulation
    while (run)
    {

        // On prend le premier évènement et on le traite
        traitement_event(echeancier.back());
        echeancier.pop_back();

        // Si tous les capteurs n'ont pas émis au moins MAX paquets, on continue
        run = false;
        for (auto f : finished)
        {
            if (not f)
            {
                run = true;
                break;
            }
        }

        // Enregistrement fichier
        if (mode == SimulatorMode::Standard)
        {
            file_standard << global_time << " ";
            for (int i = 0; i < EMISSION_MAX; i++)
            {
                if (trials[i] > 0)
                    file_standard << (double)collisions[i] / (double)trials[i] << " ";
                else
                    file_standard << 0 << " ";
            }
            file_standard << std::endl;
        }
        else if (mode == SimulatorMode::Histogram)
        {
            if (write_e1)
            {
                file_histogram_e1 << global_time - begin_date_e1 << std::endl;
                write_e1 = false;
            }
            if (write_e2)
            {
                file_histogram_e2 << global_time - begin_date_e2 << std::endl;
                write_e2 = false;
            }
        }
    }

    if (mode == SimulatorMode::Standard)
        file_standard.close();

    else if (mode == SimulatorMode::Histogram)
    {
        file_histogram_e1.close();
        file_histogram_e2.close();
    }
}

void run(const std::string &mode)
{
    /* List of simulation modes :
        - standard : 7 courbes proba de collision
        - confiance : intervalle de confiance (90%) e2 sur 50 sim
        - histogramme : temps d'émission e1 et e2
        - collision : moyenne de collisions sur chaque état avec K de 1 à 100
    */

    if (mode == "standard")
    {
        std::cout << "Simulation en mode standard ..." << std::endl;
        std::cout << "Enregistrement des probabilites de collision dans chaque etat en fonction du temps." << std::endl;
        simulateur(Standard);
        reset_simulator();
        std::cout << "Resultats sauvegardes dans le fichier \"standard.txt\"." << std::endl;
    }

    else if (mode == "confiance")
    {
        std::cout << "Simulation en mode confiance ..." << std::endl;
        std::cout << "Enregistrement des probabilites de collision dans e2 sur 50 executions." << std::endl;

        std::ofstream file_confiance("confiance.txt");
        if (not file_confiance)
        {
            std::cout << "Erreur lors de l'ouverture du fichier de confiance, fin du programme" << std::endl;
            exit(-2);
        }

        for (int i = 0; i < 50; i++)
        {
            simulateur(Confiance);
            file_confiance << (double)collisions[0] / (double)trials[0] << std::endl;
            reset_simulator();
        }

        file_confiance.close();

        std::cout << "Resultats sauvegardes dans le fichier \"confiance.txt\"" << std::endl;
    }

    else if (mode == "histogramme")
    {
        std::cout << "Simulation en mode histogramme ..." << std::endl;
        std::cout << "Enregistrement des temps d'emission dans les etats e1 et e2." << std::endl;
        simulateur(Histogram);
        reset_simulator();
        std::cout << R"(Resultats sauvegardes dans le fichier "hist1.txt" et "hist2.txt".)" << std::endl;
    }

    else if (mode == "collision")
    {
        std::cout << "Simulation en mode collision ..." << std::endl;
        std::cout << "Enregistrement des probabilites de collision moyenne sur tous les etats avec K variant de 1 a 100." << std::endl;

        std::ofstream file_collisions("collisions.txt");
        if (not file_collisions)
        {
            std::cout << "Erreur lors de l'ouverture du fichier de collisions, fin du programme" << std::endl;
            exit(-2);
        }

        for (int i = 1; i <= 100; i++)
        {
            // std::cout << "K = " << i << std::endl;
            K = i;

            simulateur(Collision);

            int total_collisions = 0, total_trials = 0;
            for (int j = 0; j < EMISSION_MAX; j++)
            {
                total_collisions += collisions[j];
                total_trials += trials[j];
            }

            file_collisions << (double)total_collisions / (double)total_trials << std::endl;

            reset_simulator();
        }

        file_collisions.close();

        std::cout << "Resultats sauvegardes dans le fichier \"collisions.txt\"." << std::endl;
    }

    else
    {
        std::cout << "Mode non reconnu, sortie du programme." << std::endl
                  << std::endl;
        std::cout << "Options disponibles : " << std::endl;
        std::cout << "standard => " << std::endl;
        std::cout << "confiance => " << std::endl;
        std::cout << "histogramme => " << std::endl;
        std::cout << "collision => " << std::endl;
    }
}

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cout << "Veuillez fournir un mode de simulation." << std::endl;
        exit(-3);
    }

    std::string arg(argv[1]);

    if (arg == "all")
    {
        run("standard");
        std::cout << std::endl;
        run("confiance");
        std::cout << std::endl;
        run("histogramme");
        std::cout << std::endl;
        run("collision");
    }
    else
        run(arg);

    return 0;
}