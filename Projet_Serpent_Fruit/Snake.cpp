/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Snake.cpp
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#include "Snake.h"

using namespace std;
using namespace sf;

Snake::Snake()
{
	_cellSize = 25;
	_doitGrandir = false;
	_direction = { 1, 0 };

	_corps = { {5, 5}, {4, 5}, {3, 5} };
	initialiseSprite();
}

void Snake::setDirection(const sf::Vector2i& nouvelleDirection)
{
	if (nouvelleDirection.x + _direction.x == 0 &&
		nouvelleDirection.y + _direction.y == 0) {
		return; // demi-tour détecte
	}
	_direction = nouvelleDirection;
}

void Snake::move()
{
	sf::Vector2i nouvelleTete = _corps.front() + _direction;
	_corps.insert(_corps.begin(), nouvelleTete);

	if (_doitGrandir) {
		_doitGrandir = false;
	}
	else {
		_corps.pop_back();
	}
}

void Snake::grow()
{
	_doitGrandir = true;
}

void Snake::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < _corps.size(); ++i)
	{
		sf::Vector2f pos(
			static_cast<float>(_corps[i].x * _cellSize),
			static_cast<float>(_corps[i].y * _cellSize)
		);

		if (i == 0) {
			_spriteTete.setPosition(pos);
			window.draw(_spriteTete);
		}
		else if (i == _corps.size() - 1) {
			_spriteQueue.setPosition(pos);
			window.draw(_spriteQueue);
		}
		else {
			_spriteCorps.setPosition(pos);
			window.draw(_spriteCorps);
		}
	}
}

sf::Vector2i Snake::getHeadPosition() const
{
	return _corps.front();
}

std::vector<sf::Vector2i> Snake::getBody() const
{
	return _corps;
}

bool Snake::hasSelfCollision() const
{
	sf::Vector2i tete = getHeadPosition();
	for (int i = 1; i < _corps.size(); ++i) 
	{
		if (_corps[i] == tete) 
		{
			return true;
		}
	}
	return false;
}

void Snake::reset()
{
	_corps.clear();
	_corps.push_back({ 5, 5 }); 
	_corps.push_back({ 4, 5 });
	_corps.push_back({ 3, 5 });

	_direction = { 1, 0 };
	_doitGrandir = false;
}

void Snake::initialiseSprite()
{
	// Charger chaque sprite séparément
	if (!_textureTete.loadFromFile("mutimedia/serpentTete.png")) {
		cout << "érreur chargement serpentTete.png";
	}
	if (!_textureCorps.loadFromFile("mutimedia/serpentCorps.png")) {
		cout << "érreur chargement serpentCorps.png";
	}
	if (!_textureQueue.loadFromFile("mutimedia/serpentQueue.png")) {
		cout << "érreur chargement serpentQueue.png";
	}
	_spriteTete.setTexture(_textureTete);
	_spriteCorps.setTexture(_textureCorps);
	_spriteQueue.setTexture(_textureQueue);
	_spriteCorps.setColor(sf::Color::Green);
	_spriteQueue.setColor(sf::Color::Green);
}
