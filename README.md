# Projet_Serpent_Fruit
# 🐍 Serpent Fruit – Jeu Snake 2D en C++ (SFML)

## 📌 Description

Serpent Fruit est une implémentation du jeu classique Snake développée en C++ en utilisant la bibliothèque graphique **SFML**.

Le projet a été réalisé dans le cadre du cours de programmation orientée objet, avec pour objectif principal de mettre en pratique :

- La programmation orientée objet (POO)
- La gestion d’une boucle de jeu
- La manipulation d’événements clavier
- La gestion de collisions
- L’utilisation d’une bibliothèque graphique (SFML)

---

## 👥 Équipe de développement

Projet réalisé en collaboration avec :

- **Abdoulaye Dembélé**
- Steve Marcel Mbiakop
- Cathérine Guiléne Ngo Ebga

Date : 16 mai 2025

---

## 🎯 Objectifs pédagogiques

- Structurer un projet en plusieurs classes
- Séparer la logique du jeu et l'affichage
- Gérer les entrées utilisateur
- Implémenter un système de score
- Gérer la croissance du serpent
- Implémenter la génération aléatoire de fruits
- Gérer les collisions (mur / corps du serpent)

---

## 🛠 Technologies utilisées

- C++
- SFML (Simple and Fast Multimedia Library)
- Programmation orientée objet
- Visual Studio

---

## 📂 Architecture du projet

```
/
├── main.cpp          // Point d’entrée du programme
├── Game.h / Game.cpp // Gestion globale du jeu
├── Snake.h / Snake.cpp // Logique du serpent
├── Fruit.h / Fruit.cpp // Gestion des fruits
├── Menu.h / Menu.cpp // Menu principal
```

Le projet est structuré selon une approche orientée objet :

- `Game` : gère la boucle principale et les états du jeu
- `Snake` : gère le mouvement et la croissance
- `Fruit` : gère l’apparition des fruits
- `Menu` : interface utilisateur initiale

---

## 🎮 Fonctionnalités

- Déplacement du serpent avec les touches directionnelles
- Croissance du serpent après consommation d’un fruit
- Détection de collision avec :
  - Les murs
  - Le corps du serpent
- Système de score
- Menu principal
- Affichage graphique en 2D via SFML

---

## 🚀 Installation et exécution

### 1️⃣ Prérequis

- Visual Studio
- SFML installée et configurée

### 2️⃣ Compilation

Ouvrir le fichier solution :

```
Projet_Serpent_Fruit.sln
```

Puis compiler en mode Debug ou Release.

---

## 🧠 Concepts techniques démontrés

- Encapsulation
- Séparation des responsabilités (Single Responsibility Principle)
- Gestion d’une boucle de jeu en temps réel
- Gestion d’événements clavier
- Manipulation d’objets graphiques SFML
- Utilisation de vecteurs dynamiques pour le corps du serpent

---

## 🔮 Améliorations possibles

- Ajout de niveaux de difficulté
- Sauvegarde du meilleur score
- Ajout d’effets sonores
- Optimisation des collisions
- Ajout d’animations

---

## 📌 Conclusion

Ce projet démontre la capacité à :

- Structurer un projet C++ en architecture orientée objet
- Utiliser une bibliothèque graphique externe
- Implémenter une logique de jeu complète
- Travailler efficacement en équipe

Projet académique réalisé dans le cadre du DEC en Techniques de l’informatique.
