/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Fruit.cpp
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#include "Fruit.h"

Fruit::Fruit()
{
    _cellSize = 25;
    _nombreMange = 0;
    _nombreRecord = 0;
    lireRecord();
   _shape.setRadius(_cellSize);
   _shape.setOrigin(_cellSize / 2.f, _cellSize / 2.f);
   _position = sf::Vector2i(10, 5);
   _shape.setPosition(_position.x * _cellSize, _position.y * _cellSize);

    if (!_texturePomme.loadFromFile("mutimedia/pomme.png")) {
        _shape.setFillColor(sf::Color::Red); 
    }
    else {
        _shape.setTexture(&_texturePomme);
    }

    _fondRectangle.setSize(sf::Vector2f(400, 800)); 
    _fondRectangle.setPosition(800, 0);

    if (_textureFond.loadFromFile("mutimedia/fond.png")) {
        _fondRectangle.setTexture(&_textureFond);

    }
    else {
        _fondRectangle.setFillColor(sf::Color(50, 50, 50)); 
    }
    // Police
    initialiseTexte();
}

void Fruit::setNombreMange(const int nb)
{
    assert(nb >= 0);

    _nombreMange = nb;
}


void Fruit::repositionner(const std::vector<sf::Vector2i>& serpent)
{
    bool positionValide = false;
    sf::Vector2i nouvellePosition;

    // Boucle jusqu'à ce qu'on trouve une position libre
    while (!positionValide) {
        // Choisir une position aléatoire
        nouvellePosition.x = 2 + rand() % (26);
        nouvellePosition.y = 3 + rand() % (24);

        positionValide = true;

        // Vérifier que le fruit ne tombe pas sur le corps du serpent
        for (const auto& segment : serpent) {
            if (segment == nouvellePosition) {
                positionValide = false;
                break;
            }
        }
    }
    // Appliquer la nouvelle position
    _position = nouvellePosition;
    _shape.setPosition((_position.x * 25),(_position.y * 25));
}

void Fruit::draw(sf::RenderWindow& window) const
{
    window.draw(_shape);
}

void Fruit::drawStats(sf::RenderWindow& window) const
{
    window.draw(_fondRectangle);
    window.draw(_titreStats);
    window.draw(_texteScore);
    window.draw(_texteMeilleur);
}

sf::Vector2i Fruit::getPosition() const
{
    return _position;
}

void Fruit::sauvegarderStats(const std::string& nomFichier) const
{
    std::ofstream fichier(nomFichier);
    if (fichier.is_open()) {
        fichier << "Partie terminee avec un meilleur score de  : " << _nombreRecord << " pommes mangees" << std::endl;
        fichier.close();
    }
}

void Fruit::afficherStatsDepuisFichier(const std::string& nomFichier) const
{
    std::ifstream fichier(nomFichier);
    if (fichier.is_open()) {
        std::string ligne;
        while (std::getline(fichier, ligne)) {
            std::cout << ligne << std::endl;
        }
        fichier.close();
    }
    else {
        std::cout << "Impossible d'ouvrir le fichier : " << nomFichier << std::endl;
    }
}

void Fruit::afficherStatsConsole() const
{
    std::cout << "Partie terminee avec un meilleur score de  : " << _nombreRecord << " pommes mangees" << std::endl;
}

void Fruit::incrementer()
{
   _nombreMange++;
   _texteScore.setString(" Score actuel : " + std::to_string(_nombreMange));
   if (_nombreMange > _nombreRecord)
   {
       _nombreRecord = _nombreMange;
       _texteMeilleur.setString("Meilleur score : " + std::to_string(_nombreRecord));
   }
   
}

int Fruit::getNombreMange() const
{
    return _nombreMange;
}

void Fruit::resetCompteur()
{
    _nombreMange = 0;
}

void Fruit::lireRecord()
{
    std::string mot;
    std::ifstream fichier("statistique.txt");

    if (fichier.is_open()) {
        while (!fichier.eof()) {
            for (int i = 0; i < 8; i++)
            {
                fichier >> mot;
            }
            fichier >> _nombreRecord;
        }
        fichier.close();
    }
    else {
        std::cout << "Impossible d'ouvrir le fichier : " << "statistique.txt" << std::endl;
    }
}

void Fruit::initialiseTexte()
{
    if (_police.loadFromFile("mutimedia/arial.ttf")) {


        // le grand titre
        _titreStats.setFont(_police);
        _titreStats.setCharacterSize(18);
        _titreStats.setFillColor(sf::Color::White);
        _titreStats.setStyle(sf::Text::Bold | sf::Text::Underlined);
        _titreStats.setString("STATISTIQUES DU JEU");
        float Center = (2000 - _titreStats.getLocalBounds().width) / 2.f;
        _titreStats.setPosition(Center, 50);


        // le score
        _texteScore.setFont(_police);
        _texteScore.setCharacterSize(20);
        _texteScore.setFillColor(sf::Color::White);
        _texteScore.setPosition(900, 200);
        _texteScore.setString(" Score actuel : " + std::to_string(_nombreMange));

        // meilleur score
        _texteMeilleur.setFont(_police);
        _texteMeilleur.setString("Meilleur score : " + std::to_string(_nombreRecord));
        _texteMeilleur.setCharacterSize(20);
        _texteMeilleur.setFillColor(sf::Color::Yellow);
        _texteMeilleur.setPosition(900, 300);
    }
}
