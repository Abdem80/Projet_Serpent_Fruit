/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : main.CPP
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#include "Game.h"

int main()
{
	Game game(1200, 800, 25, 0.1);
	game.play();
}