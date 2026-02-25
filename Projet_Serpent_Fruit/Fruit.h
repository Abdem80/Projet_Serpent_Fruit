/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Fruit.h
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include<iostream>
#include<fstream>
#include<cassert>

class Fruit
{
private:
    int _cellSize;                
    int _nombreMange;            
    int _nombreRecord;

    sf::CircleShape _shape;       
    sf::Vector2i _position;       
    sf::Texture _texturePomme;
    sf::Font _police;
    sf::Text _texteScore;
    sf::Texture _textureFond;
    sf::Text _texteMeilleur;
    sf::Text _texteFond;
    sf::RectangleShape _fondRectangle;
    sf::Text _titreStats;

public:
    // Constructeur
    Fruit();
    void setNombreMange(const int nb);
    // Méthodes principales
    void repositionner(const std::vector<sf::Vector2i>& serpent);
    void draw(sf::RenderWindow& window) const;
    void drawStats(sf::RenderWindow& window)const;
    // Accès à la position
    sf::Vector2i getPosition() const;
    void sauvegarderStats(const std::string& nomFichier) const; // A appeler dans Game.cpp(play())
    void afficherStatsDepuisFichier(const std::string& nomFichier) const;
    // Compteur de fruits mangés
    void afficherStatsConsole() const; // A appeler dans Game.cpp(play())
    void incrementer();               // +1 fruit mangé
    int getNombreMange() const;       // Lire le nombre total
    void resetCompteur();             // Remet à zéro si besoin
    void lireRecord();
    void initialiseTexte();
};
