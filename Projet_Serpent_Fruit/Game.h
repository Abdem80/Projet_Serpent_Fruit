/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Game.h
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Snake.h"
#include "Fruit.h"
#include "Menu.h"
class Game
{
private:
	//Attribut composé
	Snake _serpent;
	Fruit _pomme;
	Menu _menuPrincipale;
	sf::RenderWindow _window;
	sf::Texture _textureFond;
	sf::RectangleShape _fond;
	sf::Clock _clock;
	sf::Font _font;                
	sf::Text _scoreText;          
	sf::Text _highScoreText;       
	sf::SoundBuffer _bufferExplosion;
	sf::SoundBuffer _bufferFruit;
	sf::Sound _sonExplosion;
	sf::Sound _sonFruit;
	sf::SoundBuffer _bufferDirection;
	sf::Sound _sonDirection;
	sf::Music _musiqueFond;
	sf::Music _musiqueAccueil;
	//Attribut primaire
	int _score;
	int _width;
	int _height;
	int _tailleCellule;
	int _highScore;                // Score le plus élevé
	float _delaiMiseAJour;
	//Methodes privées
	void gererEvenements();       // Gérer les entrées clavier
	void mettreAJour();           // Logique du jeu
	void draw();              // Affichage
	void reinitialiser();         // Reset de la partie
	void verifierCollisions();    // Collision avec pomme ou soi-même
	void initializeText();
	void initializeAudio();
	bool demanderRejouer();

public:
	Game();
	Game(int width,int height, int tailleCellule, float delaiMiseAJour);
	void play();
};

