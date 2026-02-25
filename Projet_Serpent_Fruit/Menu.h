/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Menu.h
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

class Menu {
private:
    sf::Texture _textureFond;
    sf::Sprite _spriteFond;
    sf::Font _police;
    sf::Text _optionsMenu[4];
    sf::RectangleShape _boutons[4];
    sf::RectangleShape _fenetre;
    sf::Music _musiqueAccueil;
    
    int _NBinstruction = 0; // je definie les options du menu par des chiffres allant de 0 a 2
    int _optionSelectionnee;
    //Instructions a suivre
    //Je le gere juste mieux pour l'affichage
    std::vector<std::string> _instructions =
    {
        "Utilisez les flèches pour déplacer le serpent.",
        "Mangez les fruits pour grandir.",
        "Évitez de toucher les murs et votre propre corps." 
    };

    int _nbFond = 0;
public:
    Menu();
    void draw(sf::RenderWindow& fenetre);
    void gererEntree(sf::Event evenement, sf::RenderWindow& fenetre);
    int obtenirOptionSelectionnee() const;
    bool demarrerJeu() const;
    void changerFond(const std::string& fichier);
    void afficher_instructions(sf::RenderWindow& fenetre);
    void alternerFond();
    bool AfficheMenu(sf::RenderWindow& fenetre);
    void initialiseButton();
};