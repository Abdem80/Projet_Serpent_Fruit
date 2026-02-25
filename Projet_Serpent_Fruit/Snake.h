/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Snake.h
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Snake {
private:
    sf::Texture _texture;
    sf::Texture _textureTete, _textureCorps, _textureQueue; //c'est la texture a applique sur le les partie du serpent
    sf::Sprite _sprite;
    sf::Sprite _spriteTete;
    sf::Sprite _spriteCorps;
    sf::Sprite _spriteQueue;
    sf::Vector2i _direction;            
    std::vector<sf::Vector2i> _corps;   // Les positions du corps du serpent

    int _cellSize;                     
    bool _doitGrandir;  

public:
    // Constructeur
    Snake();

    // Contrôle
    void setDirection(const sf::Vector2i& nouvelleDirection);
    void move();                  
    void grow();     // Allonge le serpent (après avoir mangé)

    // Affichage
    void draw(sf::RenderWindow& window);

    // Accès à l’état du serpent
    sf::Vector2i getHeadPosition() const;
    std::vector<sf::Vector2i> getBody() const;
    bool hasSelfCollision() const;

    // Réinitialisation
    void reset();
    void initialiseSprite();
};
