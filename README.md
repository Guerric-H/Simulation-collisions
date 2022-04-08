# Simulation-collisions

Evenements potentiels :

-debut d'emission
-fin d'emission (validé = reception)
-debut d'init

-collision = 1 debut d'emission avant précédente fin d'emission

debut d'init -> debut emission , t + exp(init)
fin d'emission -> debut d'emission, t + exp(init)

debut attente -> debut emission t + exp(mu)

File : taille 1

collision -> deux paquets réessaient ~max 7 fois
si 7 fois et encore collision -> perdu

Lors de collision :
paquet1 -> Exp(mu)
paquet2 -> Exp(mu)

Début de simulation :

K capteurs -> ajout evenement loi exp(init) // init = 0.1

----------|
paquet    |--- exp(lambda) ------
----------|
    ^
    |
paquet -> pas de temps

paquet collisioné -> on ajoute

collision -> 2 capteurs = exp(mu) attente

                            ----------|
paquet ---- exp(mu) ---->   paquet    |--- exp(lambda) ----- fin d'emission
                            ----------|
