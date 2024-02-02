# ASTÉROÏDES


![Project Logo](/Ressources/image/ImageReadme.png)

Un vaisseau spatiale perdu dans l'espace se retrouve au beau milieu d'un nuage d'astéroïde. Naviguez à travers les obstacles ou utilisez votre blaster pour les détruire. 


## Table des Matières

- [Introduction](#introduction)
- [Explication du projet](#Explication-du-projet)
- [Strucutre des dossiers](#Structure-des-dossiers)
- [Définition des termes](#Définition-des-termes)
- [Getting Started](#getting-started)
  - [Pre-requis](#prerequisites)
  - [Lancement](#installation)
- [Remerciement](#remerciement)

## Introduction

Le projet a pour objectif de réaliser le célèbre jeu Asteroïds.
Le code est réalisé en C++ et utilise la librairie SFML.

## Features

- C++ and SFML
- 2D Game
- Hub Menu, Game Over et score
- Multiplayer(to be done)

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
- GameOverScreen : Malheureusement, chaque partie à sa fin. Cet écran est un menu qui apparait lors de la défaite du joueur. Il permet de voir son score, de pouvoir rejouer ou bien quitter le jeu.

Autres :
- Animation : Permet d'appliquer une ressource animée au dessus d'une entité afin d'obtenir une texture visuelle.

## Getting Started

### Pre-requis

Il faut installer la librairie SFML. Les chemins vers la librairie sont les chemins "classiques". Ils faut surement utiliser un gestionnaire de paquet pour avoir une installation cohérente. (brew sur mac)

### Lancement

Description des étapes pour lancer le jeu :
- Se placer dans le répertoire principale du dossier
- Dans le terminal : make
- Puis : ./main.exe









