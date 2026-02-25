/*====================================
AUTEUR : Abdoulaye Dembelé, Steve Marcel Mbiakop, Cathérine Guiléne Ngo Ebga
PROJET : Programmmation du jeu Snake en 2D
NOM DU FICHIER : Menu.cpp
DATE : 16/05/2025
BUT : Utilisation de la POO et SFLM
====================================*/
#include "Menu.h"

Menu::Menu()
{
    _fenetre.setSize(sf::Vector2f(1200.f, 800.f));

    if (!_textureFond.loadFromFile("mutimedia/backgroundMen.png"))
    {
        cout << "Impossible de charger l'image de fond." << endl;
        exit(0);
    }
    else
    {
        _spriteFond.setTexture(_textureFond);
        _spriteFond.setScale(
            _fenetre.getSize().x / _spriteFond.getLocalBounds().width,
            _fenetre.getSize().y / _spriteFond.getLocalBounds().height);
    }

    if (!_police.loadFromFile("polices/arial.ttf"))
    {
        cout << "Impossible de charger la _police." << endl;
        exit(3);
    }
    initialiseButton();
}


void Menu::draw(sf::RenderWindow& _fenetre)
{
    _fenetre.draw(_spriteFond);

    for (int i = 0; i < 4; ++i) 
    {
        _fenetre.draw(_boutons[i]);
        _fenetre.draw(_optionsMenu[i]); // ecrire le texte
    }
}

void Menu::gererEntree(sf::Event evenement, sf::RenderWindow& _fenetre) 
{
    if (evenement.type == sf::Event::KeyPressed) 
    {
        if (evenement.key.code == sf::Keyboard::Up) 
        {
            _optionSelectionnee = (_optionSelectionnee - 1 + 4) % 4;
        }
        else if (evenement.key.code == sf::Keyboard::Down) 
        {
            _optionSelectionnee = (_optionSelectionnee + 1) % 4;
        }
        else if (evenement.key.code == sf::Keyboard::Enter) 
        {
            if (_optionSelectionnee == 0) 
            { // Démarrer le jeu
                _fenetre.close();
            }
            else if (_optionSelectionnee == 1) { // Background
                alternerFond(); //pour changer de fond
            }
            else if (_optionSelectionnee == 2) { // TUTORIEL
                afficher_instructions(_fenetre);
            }
        }
    }

    // Met en surbrillance
    for (int i = 0; i < 4; ++i) 
    {
        if (i == _optionSelectionnee) 
        {
            _boutons[i].setFillColor(sf::Color::Black);
            _boutons[i].setOutlineColor(sf::Color::Yellow);
        }
        else {
            _boutons[i].setFillColor(sf::Color(139, 69, 19)); // Pour le boutton qui est pas sélectionné
            _boutons[i].setOutlineColor(sf::Color::Blue); // Contour
        }
    }
}

int Menu::obtenirOptionSelectionnee() const
{
    return _optionSelectionnee;
}

//Changer de fond
void Menu::alternerFond()
{
    string fonds[] = { "mutimedia/background.png", "mutimedia/background002.png", "mutimedia/background003.png" };

    _nbFond = (_nbFond + 1) % 3; // Passe au fond suivant
    changerFond(fonds[_nbFond]); // Charge le nouveau fond
}


bool Menu::AfficheMenu(sf::RenderWindow& _fenetre)
{
    while (_fenetre.isOpen()) 
    {
        sf::Event evenement;
        while (_fenetre.pollEvent(evenement)) 
        {
            if (evenement.type == sf::Event::Closed) 
            {
                _fenetre.close();

                return false;
            }

            if (evenement.type == sf::Event::KeyPressed) 
            {
                if (evenement.key.code == sf::Keyboard::Up) 
                {
                    _optionSelectionnee = (_optionSelectionnee - 1 + 4) % 4;
                }
                else if (evenement.key.code == sf::Keyboard::Down) {
                    _optionSelectionnee = (_optionSelectionnee + 1) % 4;
                }
                else if (evenement.key.code == sf::Keyboard::Enter) {
                    if (_optionSelectionnee == 0)
                    { // Démarrer le jeu
                        return true;
                    }
                    else if (_optionSelectionnee == 1) 
                    { // CONFIGURATION
                        alternerFond(); //pour changer de fond
                    }
                    else if (_optionSelectionnee == 2) { // TUTORIEL
                        afficher_instructions(_fenetre);
                    }
                }
            }

            // Met en surbrillance
            for (int i = 0; i < 4; ++i) {
                if (i == _optionSelectionnee) {
                    _boutons[i].setFillColor(sf::Color::Black); // Sélectionné
                    _boutons[i].setOutlineColor(sf::Color::Yellow); // Contour
                }
                else {
                    _boutons[i].setFillColor(sf::Color(139, 69, 19)); // Non sélectionné
                    _boutons[i].setOutlineColor(sf::Color::Blue); // Contour
                }
            }
        }

        _fenetre.clear();
        draw(_fenetre);
        _fenetre.display();
    }
    return false;
}

void Menu::initialiseButton()
{
    string libelles[4] = { "Débuter le jeu", "Background", "Tutoriel" ,"Accessibiliter" };
    _optionSelectionnee = 0; //donc le bouton sera selectionné des le debut

    // gerer les _boutons
    float largeurBouton = 300;
    float hauteurBouton = 80;
    float espaceEntre_boutons = 20;
    float centreX = (_fenetre.getSize().x - largeurBouton) / 2;
    float centreY = (_fenetre.getSize().y - (3 * hauteurBouton + 2 * espaceEntre_boutons)) / 2;

    for (int i = 0; i < 4; ++i)
    {
        _boutons[i].setSize(sf::Vector2f(largeurBouton, hauteurBouton));
        _boutons[i].setPosition(centreX, centreY + i * (hauteurBouton + espaceEntre_boutons));
        _boutons[i].setFillColor(sf::Color(139, 69, 19));
        _boutons[i].setOutlineThickness(3);
        _boutons[i].setOutlineColor(sf::Color::Blue);

        _optionsMenu[i].setFont(_police);
        _optionsMenu[i].setString(libelles[i]);
        _optionsMenu[i].setCharacterSize(40);
        _optionsMenu[i].setFillColor(sf::Color::White);
        _optionsMenu[i].setPosition(centreX + (largeurBouton - _optionsMenu[i].getGlobalBounds().width) / 2, // Centre le texte
            _boutons[i].getPosition().y + (hauteurBouton - _optionsMenu[i].getCharacterSize()) / 2);
    }
}

bool Menu::demarrerJeu() const 
{
    return _optionSelectionnee == 0;
}

void Menu::changerFond(const std::string& fichier) 
{
    if (!_textureFond.loadFromFile(fichier)) 
    {
        cout << "Impossible de charger " << fichier << endl;
        return;
    }
    _spriteFond.setTexture(_textureFond);
}

void Menu::afficher_instructions(sf::RenderWindow& _fenetre)
{
    while (true)
    {
        // Création du rectangle pour encadrer le texte
        sf::RectangleShape boiteInstructions(sf::Vector2f(700, 90)); // Largeur et hauteur
        boiteInstructions.setFillColor(sf::Color(139, 69, 19)); // Marron pour la couleur parce que je trouve pas 
        boiteInstructions.setOutlineThickness(3);
        boiteInstructions.setOutlineColor(sf::Color::Blue);
        boiteInstructions.setPosition((_fenetre.getSize().x - boiteInstructions.getSize().x) / 2, _fenetre.getSize().y / 2 - 20);

        // Crees les instructions
        sf::Text texteInstruction;
        texteInstruction.setFont(_police);
        texteInstruction.setCharacterSize(30);
        texteInstruction.setFillColor(sf::Color::White);
        texteInstruction.setString(_instructions[_NBinstruction]);

        // Position du texte qui sera dans les
        texteInstruction.setPosition(
            boiteInstructions.getPosition().x + (boiteInstructions.getSize().x - texteInstruction.getGlobalBounds().width) / 2,
            boiteInstructions.getPosition().y + (boiteInstructions.getSize().y - texteInstruction.getCharacterSize()) / 2);

        _fenetre.clear();
        _fenetre.draw(_spriteFond);
        _fenetre.draw(boiteInstructions);
        _fenetre.draw(texteInstruction);
        _fenetre.display();

        sf::Event event;
        while (_fenetre.waitEvent(event)) 
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) 
            {
                _NBinstruction++;
                if (_NBinstruction >= _instructions.size()) 
                {
                    _NBinstruction = 0; // Retour au menu après la derniere instruction
                    return;
                }
                break;
            }
            else if (event.type == sf::Event::Closed) {
                _fenetre.close();
                return;
            }
        }
    }
}

