#ifndef JEU_H
#define JEU_H
#include <iostream>
#include <sstream> // pour istringstream
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
static int nb_Mouvement;
std::string intToStr(int i);
void resetRand (int mode);
bool readCommande(char &c, std::string &arg);
bool getIntArgument(std::string s, unsigned int &val);
bool getStringArgument(std::string s, std::string &val);
///STRUCTURE DECRIVANT UNE VARIABLE D'UNE GRILLE POUR SON PARAMETRAGE
struct VARIABLE
{
    int* val;
    std::string nom;
    int minVal;
    int maxVal;
};
///STRUCTURE DE BASE DECRIVANT UNE GRILLE DE JEU
struct Grille{
    std::vector<std::vector<int> > grille;
    int cible=2048;
    int dimension=4;
    int proportion=9;
    int nbCase_Vide=0;
    int score=0;
};
///STRUCTURE GERANT UNE VERSION GRAPHIQUE D'UNE CASE JEU
///LES RENDANT AFFICHABLES A L'ECRAN
struct graph_case{
    sf::Sprite arriere;
    sf::Text chiffre;

    int* ptChiffre;
    int sizeChara;
    sf::Vector2f InitPos;
    int actualSize;
};
int rand_a_b(int a, int b);
int place(int n);
int nouvelle(int proportion);
bool load(Grille &g,std::string chemin);
bool save(Grille &g,std::string s);
int caseVide(const Grille &g);
void initialise(Grille &g,int dimension,int cible,int proportion);
void demarre(Grille &g);
bool place_nouvelle(Grille &g,int N,int nb);

int haut(Grille &g);
int bas(Grille &g);
int gauche(Grille &g);
int droite(Grille &g);

bool victoire(Grille &g);
void endOfGame(bool b,int score);
bool plusDeMouvement(Grille g);
void updateGrid(Grille g);


void affiche(const Grille &g);


    typedef std::vector<graph_case> graphGrille;
     static sf::Texture CASE_text;
     static sf::Font FONT;
     static std::vector<sf::Color> couleur;
void loadData();
void updateCase(graph_case &g);
void loadGrid(Grille &g,graphGrille &gg);
void drawCase(graph_case c,sf::RenderWindow &window);
void drawGrille(graphGrille &g);

void changeVariable(VARIABLE &v);
void menuSauvegarder(Grille g);
bool game(Grille &g,bool isAlReadyStarted);
void parametragePartie(Grille &g);
void menu();

#endif // JEU_H
