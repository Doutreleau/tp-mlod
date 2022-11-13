#Description du projet
Le but du projet est de créer une base pour un mini jeu de simulation de vie type 100 years ou Bitlife, où l'utilisateur.rice.x peut faire des choix pour un personnage. Ce jeu est basé seulement sur du texte.

#Comment exécuter
./main

#Comment utiliser le projet
Le jeu s'ouvre sur une page d'accueil. En tapant sur la barre d'espace, on commence à jouer.
Un évènement s'affiche à l'écran, il y a plusieus choix que l'utilisateur.rice peut faire. Le premier choix est accessible via la touche flèche vers la gauche, le deuxième choix avec la flèche vers la droite, le troisième choix avec la flèche vers le haut, et le quatrième choix avec la flèche vers le bas.

#lien de la vidéo
https://drive.google.com/file/d/1EhHA_js48YxGqlN0AGrpVm0nfxN5zLLj/view?usp=sharing

#Quelques détails sur l'implémentation
Ce jeu est basé sur la navigation dans un arbre des possibilités des évènements qui peuvent arriver au personnage. De l'aléatoire a été ajouté à l'arbre, ainsi, un choix de l'utilisateur.rice.x peut avoir des conséquences diverses (donc si l'on joue au jeu plusieurs fois, et que l'on fait les mêmes choix, alors on obtiendra des évènements différents).
Ainsi, une struct node a été créée pour modéliser les évènements du jeu. Chaque node possède le texte de l'évènement qu'il modélise, sa probabilité d'apparition, et ses enfants. Il y a quatre options possibles au maximum, et chaque option peut avoir jusqu'à trois évènements.

#Extensions, améliorations possibles
On pourrait améliorer le jeu en rajoutant un menu pour sélectionner différents évènements. On ne naviguerait alors pas sur un arbre, mais on choisirait les évènements que l'on veut déclencher. C'est le type de fonctionnement du jeu Bitlife.
J'ai essayé d'implémenter cette amélioration, mais je n'ai pas pu finir par manque de temps, car cette amélioration nécessite de nombreux changements (par exemple il faut créer un menu, qui demande d'utiliser les clics de souris pour naviguer dans le menu au lieu des flèches du clavier, et les menus pouvaient avoir des longueurs variables (par exemple, on ne connaît pas à l'avance la taille du menu des relations du personnage, puisque le personnage peut se faire des relations tout au long de sa vie, et que donc leur nombre n'est pas connut à l'avance)).
