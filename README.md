# Simulation-collisions

Le projet est composé des fichiers suivants :

Makefile : fichier permettant d'automatiser le processus de compilation et d'exécution du projet, il permet d'effectuer les commandes suivantes :

    run : commande par défaut, produit un exécutables effectue l'ensemble des simulations possibles listées ci-dessous. Produit l'ensemble des .pdf résultats des simulations.

    clean : nettoie l'ensemble des fichiers résultants d'une exécution sauf les fichiers au format pdf.
    
    clean_w_pdf : identique à clean en supprimant aussi les pdf.

    compile : compile le projet et produit un exécutable "main"

    standard : 
        exécute le programme avec l'argument standard, permettant de produire un fichier standard.txt. 

        exécute le script standard.R produisant un fichier standard.pdf
        Utiliser cette commande pour ne pas effectuer les autres simulations inutilement.

    confiance, histogramme, collision se comportent de la même manière que standard.

    clean_stand / conf / histo / collis : supprime chaque fichier résultant du mode sélectionné.

main.cpp : le fichier contenant le code de la simulation

standard.R : produit un fichier pdf en utilisant les résultats obtenus par la simulation dans le mode standard (une simulation, pas de changement de paramètre).

confiance.R : produit un fichier pdf en utilisant les résultats obtenus par la simulation dans le mode confiance (50 simulations, pas de changement de paramètre).

histogramme.R : produit un fichier pdf en utilisant les résultats obtenus par la simulation dans le mode histogramme (1 simulation, pas de changement de paramètre).

collision.R : produit un fichier pdf en utilisant les résultats obtenus par la simulation dans le mode collision (100 simulations, le nombre de capteur augmente de 1 à chaque simulation (1 : 100)).

e2_90succes.R : produit un fichier pdf en utilisant les résultats obtenus par la simulation dans le mode collision (100 simulations, le nombre de capteur augmente de 1 à chaque simulation (1 : 100)). Permet de répondre à la dernière question du projet de façon visuelle.

README.md : le fichier que vous lisez actuellement.
