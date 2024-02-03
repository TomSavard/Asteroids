# ASTÉROÏDES


![Project Logo](/Ressources/image/ImageReadmev3.png)

Un vaisseau spatiale perdu dans l'espace se retrouve au beau milieu d'un nuage d'astéroïde. Naviguez à travers les obstacles ou utilisez votre blaster pour les détruire. 

***
## Table des Matières

- [ASTÉROÏDES](#astéroïdes)
  - [Table des Matières](#table-des-matières)
  - [Introduction](#introduction)
  - [Features](#features)
  - [Structure des dossiers](#structure-des-dossiers)
  - [Définition des classes](#définition-des-classes)
  - [Getting Started](#getting-started)
    - [Pre-requis](#pre-requis)
    - [Lancement](#lancement)
    - [Contrôles :](#contrôles-)
      - [Mode Solo :](#mode-solo-)
      - [Mode Multijoueur](#mode-multijoueur)

## Introduction
Le projet a pour objectif de réaliser le célèbre jeu Asteroïds.
Le code est réalisé en C++ et utilise la librairie SFML.

## Features

- C++ and SFML
- 2D Game (done)
- Hub Menu, Game Over et score (done)
- Multiplayer (done)

## Structure des dossiers
- code : contient l'ensemble du code. Ce dernier est décomposé en plusieurs fichiers sources et headers afin d'obtenir une meilleur modularité et une capacité d'évolution performante.
- Ressources : contient toutes les ressources (image, audio, animation, police etc)

## Définition des classes

Afin de faire un code cohérent et construit il faut se mettre d'accord sur la nomenclature.


Objets :
- Entite : Classe de Base possédant les propriétés partagées par les différents objets.
- player : Classe dérivée de Entite. Elle correspond au vaisseau controlable par le joueur. 
- asteroide : Classe dérivée de Entite. Elle correspond aux astéroides qui apparaissent à l'écran.
- tir : Classe dérivée de Entire. Elle correspond aux lasers tirés par le vaisseau.

Interfaces :
- Menu : C'est le Menu d'accueil du jeu. Il permet de choisir le mode de jeu et de régler les paramètres avant de lancer une partie.
- TableauDesScores : Permet d'afficher tout au long de la partie le score actuel.
- GameOver : Malheureusement, chaque partie à sa fin. Cet écran est un menu qui apparait lors de la défaite du joueur. Il permet de voir son score, de pouvoir rejouer ou bien quitter le jeu.
- GameOverMulti : Une fois l'adversaire térassé, un écran avec le nom du gagnant s'affiche. Les options pour rejouer ou quitter le jeu sont également disponibles.

<u>Autres :</u>
- Animation : Permet d'appliquer une ressource animée au dessus d'une entité afin d'obtenir une texture visuelle.
- global_variables : Contient la definition des variables globales partagées entre les fichiers sources. Cela permet une centralisation et donc une limitation de la redondance. La modification est également grandement facilitée.

## Getting Started

### Pre-requis

Il faut installer la librairie SFML. Les chemins vers la librairie sont les chemins "classiques". Ils faut surement utiliser un gestionnaire de paquet pour avoir une installation cohérente. (brew sur mac)

### Lancement

Description des étapes pour lancer le jeu :
- Se placer dans le répertoire principale du dossier
- Dans le terminal : make
- Puis : ./main.exe


### Contrôles :
#### Mode Solo :
  - Boost = `↑ `  Gauche = `←`  Droite = `→`  Tir = `Barre espace`
#### Mode Multijoueur

- **Joueur 1 :**
  - Boost = `o`  Gauche = `k`  Droite = `m`  Tir = `;`
  
- **Joueur 2 :**
  - Boost = `z`  Gauche = `q`  Droite = `d`  Tir = `x`
  
  
  
 












