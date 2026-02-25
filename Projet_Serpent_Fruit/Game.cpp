/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Game.cpp
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#include "Game.h"

void Game::gererEvenements()
{
	sf::Event event;
	while (_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			_window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			switch (event.key.code) {
			case sf::Keyboard::Escape:
				_window.close();
				break;

			case sf::Keyboard::Up:
				_serpent.setDirection({ 0, -1 });
				_sonDirection.play();
				break;

			case sf::Keyboard::Down:
				_serpent.setDirection({ 0, 1 });
				_sonDirection.play();
				break;

			case sf::Keyboard::Left:
				_serpent.setDirection({ -1, 0 });
				_sonDirection.play();
				break;

			case sf::Keyboard::Right:
				_serpent.setDirection({ 1, 0 });
				_sonDirection.play();
				break;

			default:
				break;
			}
		}
	}
}

void Game::mettreAJour()
{
	_serpent.move();
}

void Game::draw()
{
	_window.clear();
	_window.draw(_fond);
	// 2. Serpent
	_serpent.draw(_window);
	// 3. Fruit
	_pomme.draw(_window);
	_pomme.drawStats(_window);

	_window.display();
}

void Game::reinitialiser()
{
	// Réinitialiser le serpent
	_serpent.reset();

	// Repositionner une nouvelle pomme
	_pomme.repositionner(_serpent.getBody());

	_score = 0;
	_pomme.setNombreMange(0);
	// Redémarrer l'horloge pour éviter un mouvement instantané
	_musiqueAccueil.play();
	_clock.restart();
}

void Game::verifierCollisions()
{
	// 1. Collision avec le fruit
	if (_serpent.getHeadPosition() == _pomme.getPosition()) {
		_serpent.grow();      // Le serpent s’allonge
		_score++;           // On ajoute 1 point
		_pomme.repositionner(_serpent.getBody());
		_pomme.incrementer();
		_sonFruit.play();
	}

	// 2. Collision avec soi-même
	if (_serpent.hasSelfCollision()) 
	{
		_sonExplosion.play();
		_musiqueAccueil.pause();
		if (demanderRejouer()) {
			reinitialiser(); // remet tout à zéro
			_pomme.sauvegarderStats("statistique.txt");
			_pomme.afficherStatsConsole();
		}
		else {
			_window.close();
		}
	}
	// 3.Collision avec les murs
	sf::Vector2i head = _serpent.getHeadPosition();
	int maxX = (800/ _tailleCellule) - 2;
	int maxY = (800 / _tailleCellule) - 3;
	if (head.x < 2 || head.y < 3 || head.x >= maxX || head.y >= maxY) {
		_sonExplosion.play();
		_musiqueAccueil.pause();
		if (demanderRejouer()) {
			reinitialiser(); 
			_pomme.sauvegarderStats("statistique.txt");
			_pomme.afficherStatsConsole();
		}
		else {
			_window.close();
		}
	}
}

void Game::initializeText()
{
	// Charger la police
	if (!_font.loadFromFile("mutimedia/arial.ttf")) {
		_scoreText.setString("Erreur police");
		_highScoreText.setString("Erreur police");
	}

	// Texte du score
	_scoreText.setFont(_font);
	_scoreText.setCharacterSize(20);
	_scoreText.setFillColor(sf::Color::White);
	_scoreText.setPosition(sf::Vector2f(_width + 10.f, 10.f));
	/*_fenetre.setSize(sf::Vector2f(1200.f, 800.f));*/
	// Texte du high score
	_highScoreText.setFont(_font);
	_highScoreText.setCharacterSize(20);
	_highScoreText.setFillColor(sf::Color::Yellow);
	_highScoreText.setPosition(sf::Vector2f(_width + 10.f, 40.f));

	// Valeurs initiales
	_scoreText.setString("Score: 0");
	_highScoreText.setString("High Score: 0");
}

void Game::initializeAudio()
{
	if (!_musiqueAccueil.openFromFile("mutimedia/menuaudio.wav"))
	{
		std::cout << "Impossible de charger la musique" << std::endl;
	}
	else
	{
		_musiqueAccueil.setLoop(true); // La musique tourne en boucle
		_musiqueAccueil.setVolume(30);
		_musiqueAccueil.play(); // Lancer la musique
	}

	if (!_musiqueFond.openFromFile("mutimedia/musique_douce_loop.wav")) {
		std::cout << "Impossible de charger la musique de fond" << std::endl;
	}
	else {
		_musiqueFond.setLoop(true);    
		_musiqueFond.setVolume(40);    
	}
	if (!_bufferExplosion.loadFromFile("mutimedia/collision_cartoon.wav")) {
		std::cout << "[Erreur] Chargement explosion" << std::endl;;
	}
	_sonExplosion.setBuffer(_bufferExplosion);

	if (!_bufferFruit.loadFromFile("mutimedia/fruit_eat.wav")) {
		std::cout << "Chargement son fruit erreur" << std::endl;
	}
	_sonFruit.setBuffer(_bufferFruit);

	if (!_bufferDirection.loadFromFile("mutimedia/tick_direction.wav")) {
		std::cout << "Son direction non chargé" << std::endl;
	}
	_sonDirection.setBuffer(_bufferDirection);
}

bool Game::demanderRejouer()
{
	// === Boîte de fond ===
	sf::RectangleShape boite(sf::Vector2f(350, 200));
	boite.setFillColor(sf::Color(30, 30, 30, 240));
	boite.setPosition((_width - 350) / 2.f, (_height - 200) / 2.f);

	// === Texte du message ===
	sf::Text message;
	message.setFont(_font);
	message.setCharacterSize(24);
	message.setFillColor(sf::Color::White);
	message.setString("Rejouer une partie ?");
	message.setPosition(boite.getPosition().x + 50, boite.getPosition().y + 30);

	// === Bouton OUI ===
	sf::RectangleShape boutonOui(sf::Vector2f(100, 40));
	boutonOui.setFillColor(sf::Color(0, 150, 0));
	boutonOui.setPosition(boite.getPosition().x + 40, boite.getPosition().y + 120);

	sf::Text texteOui("OUI", _font, 20);
	texteOui.setFillColor(sf::Color::White);
	texteOui.setPosition(boutonOui.getPosition().x + 30, boutonOui.getPosition().y + 5);

	// === Bouton NON ===
	sf::RectangleShape boutonNon(sf::Vector2f(100, 40));
	boutonNon.setFillColor(sf::Color(150, 0, 0));
	boutonNon.setPosition(boite.getPosition().x + 200, boite.getPosition().y + 120);

	sf::Text texteNon("NON", _font, 20);
	texteNon.setFillColor(sf::Color::White);
	texteNon.setPosition(boutonNon.getPosition().x + 25, boutonNon.getPosition().y + 5);

	// === Boucle d’attente du clic ===
	while (_window.isOpen()) {
		sf::Event event;
		while (_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				_window.close();
				return false;
			}

			if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2f clickPos(event.mouseButton.x, event.mouseButton.y);

				if (boutonOui.getGlobalBounds().contains(clickPos)) {
					return true;
				}
				if (boutonNon.getGlobalBounds().contains(clickPos)) {
					return false;
				}
			}
		}

		// === Effet de survol de la souris ===
		sf::Vector2i souris = sf::Mouse::getPosition(_window);
		sf::Vector2f sourisF(sf::Vector2f(souris.x, souris.y));

		if (boutonOui.getGlobalBounds().contains(sourisF)) {
			boutonOui.setFillColor(sf::Color(0, 200, 0)); 
		}
		else {
			boutonOui.setFillColor(sf::Color(0, 150, 0));
		}

		if (boutonNon.getGlobalBounds().contains(sourisF)) {
			boutonNon.setFillColor(sf::Color(200, 0, 0)); 
		}
		else {
			boutonNon.setFillColor(sf::Color(150, 0, 0));
		}

		// === Affichage ===
		_window.clear();
		_window.draw(_fond);
		_serpent.draw(_window);
		_pomme.draw(_window);
		_window.draw(boite);
		_window.draw(message);
		_window.draw(boutonOui);
		_window.draw(boutonNon);
		_window.draw(texteOui);
		_window.draw(texteNon);
		_window.display();
	}

	return false;
}

Game::Game()
{
	_score = 0;
	_width = 0;
	_height = 0;
	_tailleCellule = 0;
	_delaiMiseAJour = 0;
	_highScore = 0;
}

Game::Game(int width, int height, int tailleCellule, float delaiMiseAJour)
{
	_width = width;
	_height = height;
	_tailleCellule = tailleCellule;
	_delaiMiseAJour = delaiMiseAJour;
	_window.create(sf::VideoMode(_width, _height), "Fruit Chase - Snake Game");
	_window.setFramerateLimit(60); // Limite à 60 FPS pour plus de stabilité

	if (!_textureFond.loadFromFile("mutimedia/background.png")) {
		// En cas d'erreur, fond blanc
		_fond.setFillColor(sf::Color::White);
	}
	else {
		_fond.setTexture(&_textureFond);
	}

	_fond.setSize(sf::Vector2f(800, 800));

	initializeText();
	initializeAudio();
	
}

void Game::play()
{
	if (_menuPrincipale.AfficheMenu(_window))
	{
		while (_window.isOpen())
		{
			// Gérer les entrées clavier
			gererEvenements();
			// Avancer le serpent à intervalle régulier
			if (_clock.getElapsedTime().asSeconds() >= _delaiMiseAJour) 
			{
				_musiqueFond.play();            // lancer la musique
				mettreAJour();            // Avance le serpent
				verifierCollisions();  // verifie si une pomme mangée ou il se cogne?
				_clock.restart();    // Remet l’horloge à zéro
			}
			// Afficher tous les éléments comme il faut sur la fénètre
			draw();
		}
	}
	else{
		_window.close();
	}
}
