MiniRT (Mini RayTracer) est un projet de programmation graphique qui vise à créer un moteur de rendu 3D simplifié en utilisant le ray tracing. Ce projet est écrit en C et utilise la bibliothèque MiniLibX pour l'affichage, offrant une introduction pratique aux principes de base de la synthèse d'images par lancer de rayons et à la programmation graphique. Le but est de générer des images photoréalistes en traçant le parcours de la lumière et en simulant ses interactions avec des objets virtuels dans une scène 3D.
Caractéristiques principales :

    Rendu 3D basé sur le ray tracing : utilise l'algorithme de lancer de rayons pour calculer les couleurs des pixels en fonction de la lumière et des matériaux dans la scène.
    Gestion de différentes formes géométriques : supporte le rendu de sphères, plans et cylindres comme objets primitifs de la scène.
    Illumination et ombres : intègre un modèle d'illumination simple pour simuler les effets de lumière diffuse, spéculaire et ambiante, ainsi que les ombres portées par les objets.
    Gestion de la caméra : permet de positionner et d'orienter la caméra dans la scène pour contrôler la perspective de vue.
    Chargement de scène depuis un fichier : lit une description textuelle de la scène à partir d'un fichier .rt, qui spécifie les objets, leurs propriétés et la configuration de la caméra et de l'éclairage.

Technologies utilisées :

    Langage C : choix du C pour sa proximité avec le système, ses performances et son contrôle sur la mémoire, essentiels pour un moteur de rendu.
    MiniLibX : une bibliothèque graphique développée à l'École 42, utilisée pour créer des fenêtres et dessiner des pixels à l'écran sous des environnements Unix/Linux.

Défis et apprentissages :

    Mathématiques pour la 3D : approfondissement des connaissances en géométrie 3D, vecteurs et algèbre linéaire nécessaires pour le calcul des intersections rayon-objet et des effets d'illumination.
    Optimisation des performances : exploration des techniques d'optimisation pour améliorer la vitesse de rendu, essentielle dans le ray tracing qui est naturellement gourmand en calculs.
    Compréhension des principes de la lumière : étude des interactions entre la lumière et les matériaux pour produire des images réalistes.

MiniRT représente une étape fondamentale dans l'apprentissage de la synthèse d'images et de la programmation graphique, fournissant une base solide pour explorer des techniques de rendu plus avancées.
