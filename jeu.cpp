#include "jeu.h"
using namespace std;

void resetRand (int mode) { srand(mode ? time(0) : 1); }
/* Essaie de lire tout une ligne au clavier, stocke dans le parametre c le
 * premier caractere qui n'est pas un espace (qu'on pourra interprete comme
 * designant une commande); elimine les espaces qui suivent et stocke dans le
 * parametre arg ce qui reste (eventuellement) de la ligne et qu'on pourra
 * interprete comme les possibles arguments de la commande.
 * S'il n'y a plus de lecture possible, met 0 dans c, la chaine vide dans args
 * et retourne true;
 * Si la ligne lue etait vide ou ne contenait que des espaces, et qu'on
 * n'est pas en fin de fichier, renvoie false pour indiquer que l'utilisateur
 * n'a pas fourni de commande du tout.
 */
bool readCommande(char &c, string &arg) {
  size_t i;
  string s;        // initialise (par defaut) a la chaine vide.
  getline(cin, s); // essaye de lire une ligne et la stocke dans s.
  i = 0;
  while (i < s.size() and isspace(s[i])) { i = i+1; }
  if (i == s.size()) {
    if ( not cin.eof()) {
      // eof() renvoie true si la derniere lecture a echoue car il n'y
      // avait plus rien a lire. Si ce n'est pas le cas et qu'on a juste
      // lu une ligne vide ou avec que des espaces, on renvoie false apres
      // avoir mis un message d'erreur.
      // sinon, pas la peine que la fonction appelante reessaye, ca ne va pas
      // s'arranger. On stocke 0 dans le parametre c pour le signaler.
      return false;
    } else {  c = 0; arg.clear(); return true; }
  } else { c = s[i]; } // le caractere qui identifie la commande a executer
  i = i+1;
  while (i < s.size() and isspace(s[i])) { i = i+1; }
  s.erase(0, i); // supprime tout ce qui precede le ou les arguments.
  arg = s;
  return true;
}
/* Utile pour les commandes qui prennent un entier en argument.
 * Verifie qu'un entier debute bien la chaine s et le stocke dans val.
 * Rale si s ne contient rien ou ne debute pas par un entier.
 * Ne se preoccupe pas qu'il reste ou non des choses a lire dans la
 * chaine a la suite de l'entier.
 * Renvoie true s'il y avait bien un entier a lire, false sinon
 */
bool getIntArgument(string s, unsigned int &val) {
  istringstream args(s); // lire dans une chaine plutot que dans un "stream"
  unsigned int target;
  // Attention, l'operateur ">>" lit un entier qu'il soit signe ou non.
  // donc is on tape -1, la lecture reussit mais donnera une valeur "bizarre"
  // quand on l'interpretera comme un unsigned int.
  // On pourrait le lire dans une variable entiere avant de tester le signe
  // et de le convertir en "unsigned" (en esperant rester dans les bonnes
  // plages de valeurs)
  args >> target;
  if (args.fail()) {
    args.clear();
    string erreur = args.str();
    if (erreur.size() == 0) {
      cerr << "Argument manquant !" << endl;
    } else {
      cerr << "Argument incorrect: " << erreur << endl;
    }
    return false;
  } else { val = (int) target; return true; }
}


/* Principe similaire pour les commandes qui attendent une string en argument.
 * Attention on considere comme l'argument cherche la plus longue sequence
 * de caracteres sans espaces.
 * Donc si s contient "abc def", la fonction stockera seulement "abc" dans val.
 * Si s contient "123 abc", la fonction stockera "123" dans val.
 * Si s est vide ou ne contient que des espaces, rale.
 */
bool getStringArgument(string s, string &val) {
  istringstream args(s); string name;
  args >> name;
  if (args.fail()) {
    args.clear();
    string erreur = args.str();
    if (erreur.size() == 0) {
      cerr << "Argument manquant !" << endl;
    } else { // A priori pas possible quand on a essaye de lire une string.
      cerr << "Argument incorrect: " << erreur << endl;
    }
    return false;
  } else { val = name; return true; }
}

string intToStr(int i)
{
        std::ostringstream f;
f << i;
string s(f.str());
    return s;
}


//FONCTION GERANT UNE GRILLE ET LE DEROULEMENT D'UNE PARTIE
///retourne un entier de fa�on al�atoire situ� dans l'intervalle [a,b]
int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}
///retourne un nouveau chiffre de fa�on al�atoire en fonction des proportions
int nouvelle(int proportion) {
  return ((rand() % 10) + 1) <= proportion ? 2 : 4;
}
///renvoi la position de la futur case, N nombre de case vide
int place(int n) {
if(n>0)
return rand() % n;
return 0;
 }
 ///sauvegarde une grille g dans un fichier s
bool save(Grille &g,string s)
{
        ofstream data("data/"+s, ios::out | ios::trunc);
        if(data)
        {
            data << g.dimension << endl << g.cible
             << endl << g.proportion << endl << g.score
              << endl << g.nbCase_Vide << endl;
            for(int i=0;i<g.dimension;i++)
            {
                for(int j=0;j<g.dimension;j++)
                {
                    data << g.grille[i][j] << " ";
                }
                data << endl;
            }
            return true;
        }
        else
            cerr << "impossible d'ouvrir le fichier de destination" << endl;
            return false;




}
///charge une sauvegarde, et initialise une grille g avec ces donn�es
bool load(Grille &g,string chemin)
{
    ifstream data(chemin,ios::in);
    if(data)
    {
        int size=0;
        int cible=0;
        int proportion=9;
        int score =0;
        int nbCase_Vide=0;
        vector<vector<int> >grille;
        vector<int> tempInt;
        int temp;

        data >> size;
        if(size==0)
        {
            data.close();
            return false;
        }
        data>> cible >> proportion >> score>>nbCase_Vide;
        for(int e=0;e<size;e++)
        {
            grille.push_back(tempInt);
            for(int r=0;r<size;r++)
            {
                data>>temp;
                grille[e].push_back(temp);
            }
        }
        data.close();
    g.dimension=size;
    g.cible = cible;
    g.proportion=proportion;
    g.nbCase_Vide=nbCase_Vide;
    g.grille=grille;
    return true;
    }
    data.close();
    return false;
}
///renvoi le nombre de case vide dans une grille
int caseVide(const Grille &g)
{
    return g.nbCase_Vide;
}
///place un nouveau chiffre nb, � la case vide N, renvoi si cela est possible
bool place_nouvelle(Grille &g,int N,int nb)
{
    int j=-1;
    for(int e =0;e<g.dimension;e++)
    {
        for(int i=0;i<g.dimension;i++)
        {
            if(g.grille[i][e]==0)
                j++;
            if(j==N)
            {
                g.grille[i][e]=nb;
                g.nbCase_Vide--;
                return true;
            }
        }
    }
    return false;
}
///initialise une grille
void initialise(Grille &g,int dimension,int cible,int proportion){

        for(int e = 0;e<dimension;e++)
        {
            g.grille.push_back(vector<int>());
            for(int i =0;i<dimension;i++)
            {
             g.grille[g.grille.size()-1].push_back(0);
            }
        }
        g.proportion = proportion;
        g.dimension = dimension;
        g.cible = cible;
        g.nbCase_Vide=g.dimension*g.dimension;


}
///place les premi�res cases
void demarre(Grille &g)
{
    for(int i=0;i<2;i++)
        place_nouvelle(g,place(caseVide(g)),nouvelle(g.proportion));
}
int haut(Grille &g)
{
    for(int i =0;i<g.dimension;i++)
    {
        for(int j=0;j<g.dimension;j++)
        {
            if(g.grille[j][i]!=0)
            {
                int limite=0;
                for(int h=j-1;h>=limite;h--)
                {
                        if(g.grille[h][i]!=0)
                        {
                            if(g.grille[h][i] == g.grille[j][i])
                            {
                                nb_Mouvement++;
                                limite++;
                                g.grille[h][i]*=2;
                                g.score+=g.grille[h][i];
                                g.grille[j][i]=0;
                                j=h;
                                g.nbCase_Vide++;
                                break;
                            }
                            else
                            {
                                limite++;
                                break;
                            }
                        }
                        else
                        {
                            nb_Mouvement++;
                            g.grille[h][i]=g.grille[j][i];
                            g.grille[j][i]=0;
                            j=h;
                        }
                }

            }
        }
    }
    return g.nbCase_Vide;
}
int bas(Grille &g)
{
    for(int i =0;i<g.dimension;i++)
    {
        for(int j=g.dimension-1;j>=0;j--)
        {
            if(g.grille[j][i]!=0)
            {
                    int limite = 0;
                    for(int h=j+1;h<g.dimension-limite;h++)
                    {
                        if(g.grille[h][i]!=0)
                        {
                            if(g.grille[h][i] == g.grille[j][i])
                            {
                                nb_Mouvement++;
                                limite++;
                                g.grille[h][i]*=2;
                                g.score+=g.grille[h][i];
                                g.grille[j][i]=0;
                                j=h;
                                g.nbCase_Vide++;
                                break;
                            }
                            else
                            {
                                limite++;
                                break;
                            }
                        }
                        else
                        {
                            nb_Mouvement++;
                            g.grille[h][i]=g.grille[j][i];
                            g.grille[j][i]=0;
                            j=h;
                        }
                    }
                }
            }
        }
    return g.nbCase_Vide;
}
int gauche (Grille &g)   ///OK///
{

    ///Vecteur temporaire
    vector < vector <bool> > fusion;
    for (int k=0; k<g.dimension; k++)
    {
        fusion.push_back(vector<bool>(g.dimension));
    }

    for (int i=0; i<g.dimension; i++)
    {
        for ( int j=0; j<g.dimension; j++)
        {
            fusion[i][j]=false;
        }
    }



    for (int i=0; i<g.dimension; i++)
    {
        for (int j=0; j<g.dimension; j++)
        {
            if (j>0 and g.grille[i][j]!=0)
            {
                while( j>0 and g.grille[i][j-1]==0 )    //on d�cale � gauche
                {
                    nb_Mouvement++;
                    g.grille[i][j-1]=g.grille[i][j];
                    g.grille[i][j]=0;
                    j--;
                }

                if (g.grille[i][j]==g.grille[i][j-1] and fusion[i][j-1]==false)        // on fusionne
                {
                    nb_Mouvement++;
                    g.grille[i][j-1]=2*g.grille[i][j];
                    g.grille[i][j]=0;
                    fusion[i][j-1]=true;
                    g.nbCase_Vide++;
                    g.score=g.score+g.grille[i][j-1];


                }
            }
        }
    }

    return g.nbCase_Vide;
}
int droite (Grille &g)   ///OK///
{

    ///Vecteur temporaire
    vector < vector <bool> > fusion;
    for (int k=0; k<g.dimension; k++)
    {
        fusion.push_back(vector<bool>(g.dimension));
    }

    for (int i=0; i<g.dimension; i++)
    {
        for ( int j=0; j<g.dimension; j++)
        {
            fusion[i][j]=false;
        }
    }



    for (int i=0; i<g.dimension; i++)
    {
        for (int j=g.dimension-1; j>=0; j--)
        {
            if (j<g.dimension-1 and g.grille[i][j]!=0)
            {
                while(j<g.dimension-1 and g.grille[i][j+1]==0 )    //on d�cale � droite

                {
                    nb_Mouvement++;
                    g.grille[i][j+1]=g.grille[i][j];
                    g.grille[i][j]=0;
                    j++;
                }

                if (g.grille[i][j]==g.grille[i][j+1] and fusion[i][j+1]==false)        // on fusionne
                {
                    nb_Mouvement++;
                    g.grille[i][j+1]=2*g.grille[i][j];
                    g.grille[i][j]=0;
                    fusion[i][j+1]=true;
                    g.nbCase_Vide++;
                    g.score=g.score+g.grille[i][j+1];


                }
            }
        }
    }
    return g.nbCase_Vide;
}
bool victoire(Grille &g)
{
    for(int e = 0;e<g.dimension;e++)
    {
        for(int r=0;r<g.dimension;r++)
        {
            if(g.cible<=g.grille[e][r])
                return true;
        }
    }
    return false;
}
bool plusDeMouvement(Grille g)
{
    int temp = g.nbCase_Vide;
    int mouv;
    mouv=haut(g);
    if(mouv != temp)
        return false;

    mouv=bas(g);
    if(mouv != temp)
        return false;

    mouv=gauche(g);
    if(mouv != temp)
        return false;

    mouv=droite(g);
    if(mouv != temp)
        return false;

    return true;
}
//FIN FONCTION GERANT UNE GRILLE ET LE DEROULEMENT D'UNE PARTIE



//FONCTION RELATIVE A L'AFFICHAGE CONSOLE
///affiche une grille
void affiche (const Grille &g)   ///OK///
{
    int dimension=g.dimension;
    int largeur=(dimension*5)+(dimension+1);
    //int hauteur=(2*dimension)+1;

    for ( int i=0; i<dimension; i++)
    {

        for ( int k=0; k<largeur; k++)
        {
            cout << "*";

        }
        cout<<endl;

        for ( int j=0; j<dimension; j++)
        {


            if (g.grille[i][j]!=0)
            {
                printf("*%3d  ",g.grille[i][j]);
            }
            else
            {
                printf("*     ");
            }

        }
        cout <<"*";
        cout<<endl;
    }

    for ( int u=0; u<largeur; u++)
    {
        cout << "*";

    }
    cout<<endl<<endl;


}
//FIN FONCTION RELATIVE A L'AFFICHAGE CONSOLE



//FONCTION RELATIVE A L'AFFICHAGE GRAPHIQUE
///CHARGE LES RESSOURCES GRAPHIQUES
void loadData()
{
    CASE_text.loadFromFile("data/Image/case.png");
    FONT.loadFromFile("data/Font/sansation.ttf");
    for(int e=0;e<10;e++)
        couleur.push_back(sf::Color::White);
    couleur[1]=sf::Color(223,242,255);
    couleur[2]=sf::Color(116,208,241);
    couleur[3]=sf::Color(115,194,251);
    couleur[4]=sf::Color(119,181,254);
    couleur[5]=sf::Color(49,140,231);
    couleur[6]=sf::Color(53,122,183);
    couleur[7]=sf::Color(30,127,203);
    couleur[8]=sf::Color(21,96,189);
    couleur[9]=sf::Color(255,127,0);
    couleur[10]=sf::Color(217,1,21);
    couleur[11]=sf::Color(225,1,21);

}
///CHARGE UNE GRILLE DANS UNE GRILLE GRAPHIQUE
void loadGrid(Grille &g,graphGrille &gg)
{
    int av=1;
    for(int i=0;i<g.grille.size();i++)
    {
        for(int j=0;j<g.grille[i].size();j++)
        {
            graph_case temp;
            temp.sizeChara=CASE_text.getSize().x;
            temp.arriere.setTexture(CASE_text);
            temp.arriere.setColor(couleur[0]);
            temp.ptChiffre=&(g.grille[i][j]);
            temp.chiffre.setFont(FONT);
            temp.chiffre.setString("0");
            temp.chiffre.setColor(sf::Color::Black);
            temp.chiffre.setCharacterSize(temp.sizeChara);
            temp.chiffre.setOrigin(temp.sizeChara/2,temp.sizeChara/2);

            temp.arriere.setPosition(j*CASE_text.getSize().x,i*CASE_text.getSize().x);
            temp.chiffre.setPosition(j*temp.sizeChara+temp.sizeChara/2,i*temp.sizeChara+temp.sizeChara/2);
            temp.InitPos = temp.chiffre.getPosition();
            gg.push_back(temp);
        }
    }
}
///MET A JOUR UNE CASE D'UNE GRILLE GRAPHIQUE
void updateCase(graph_case &g)
{
    float chiffre=*(g.ptChiffre);
    int teinte=1;
    if(chiffre == 0 )
    {
        g.chiffre.setString("");
        g.arriere.setColor(couleur[0]);
    }
    else
    {
    g.chiffre.setString(intToStr(chiffre));
    g.chiffre.setCharacterSize(g.sizeChara/g.chiffre.getString().getSize());
    g.chiffre.setOrigin(sf::Vector2f(g.sizeChara/(g.chiffre.getString().getSize()+1)
                                     ,g.sizeChara/(g.chiffre.getString().getSize()+1)));

    g.chiffre.setPosition(g.InitPos);

    while( (chiffre=chiffre/2)>1)
        teinte++;
    if(teinte<couleur.size())
    g.arriere.setColor(couleur[teinte]);
    else
    g.arriere.setColor(couleur[couleur.size()]);
    }
}
///MET A JOUR UNE GRILLE GRAPHIQUE PAR RAPPORT A SA GRILLE
void updateGrid(graphGrille &g)
{
    for(int e =0;e<g.size();e++)
        updateCase(g[e]);
}
///AFFICHE UNE CASE c DANS LA FENETRE
void drawCase(graph_case c,sf::RenderWindow &window)
{
    window.draw(c.arriere);
    window.draw(c.chiffre);
}
///AFFICHE UNE GRILLE GRAPHIQUE
void drawGrille(graphGrille &g,sf::RenderWindow &window)
{
    for(int e=0;e<g.size();e++)
    {
        drawCase(g[e],window);
    }
}
//FIN FONCTION RELATIVE A L'AFFICHAGE GRAPHIQUE



//FONCTION CONCERNANT LE COTE UTILISATEUR
void endOfGame(bool b,int score)
{
    if(b)
    {
        cout << "Bravo vous avez gagne !! Votre score est de : "<< score<< endl;
    }
    else
    {
        cout << "Vous avez perdu, votres score est de : "<< score << endl;
    }
}
///LANCE UN MENU POUR SAUVEGARDER UNE GRILLE g
void menuSauvegarder(Grille g)
{

    string s="";
    cout << "Entrez le nom de la sauvegarde ou n pour annuler : ";
    cin >>s;
    if(s=="n")
    {
        cout<< "Annulation de la sauvegarde"<< endl;
    }
    else
    {
        if(save(g,s))
        cout <<"La partie a ete sauvegardee"<<endl;
        else
        cout <<"La partie n'a pas pu etre sauvegardee"<<endl;
    }

    cout << "Appuyez sur une touche pour continuer" << endl;
    getchar();



}
void changeVariable(VARIABLE &v)
{
    long int s=-2;
    bool changeValeur=false;
    while(s==-2)
    {
        cout << "Vous voulez changer la valeur de : " << v.nom << " sa plage de valeur est de " << v.minVal << " a " << v.maxVal << endl;
        cout << "Sa valeur actuelle est de : " << *(v.val)<<endl;
        cout << "Tapez -1 pour annuler"<<endl;
        cout << "Votre choix : ";
        cin >> s;
        if(s==-1)
            break;
        system("cls");
        if(s<v.minVal || s>v.maxVal)
        {
            s=-2;
            changeValeur=false;
            cout << "Erreur,entrez une valeur valide"<<endl;
        }
        else
            changeValeur=true;

    }
    if(s!=-1 && changeValeur==true)
        *(v.val) = s;
}
void parametragePartie(Grille &g)
{
        vector<VARIABLE> grille_champ;
        grille_champ.push_back({&(g.cible),"CIBLE",2,99999});
        grille_champ.push_back({&(g.dimension),"DIMENSION",2,12});
        grille_champ.push_back({&(g.proportion),"PROPORTION",1,10});
        int i=1;
        while(i!=4)
        {
            cout << "La grille est parametre a : CIBLE = " << g.cible << " , DIMENSION = " << g.dimension << " et PROPORTION = "<<g.proportion<<endl;
            cout << "Entrez le numero de la variable � modifier pour la modifier : "<< endl;
            cout << "1: CIBLE\n2:DIMENSION\n3:PROPORTION\n4:LANCER LA PARTIE\n";
            cout << "Votre choix : ";
            cin >>i;
            if(i==4)
                break;
            else if(i <1 || i>3)
            {
                system("cls");
                cout << "Veuillez entrer une commande valide !" << endl;
                i=1;
            }
            else
            {
                changeVariable(grille_champ[i-1]);
            }

        }
        system("cls");
        initialise(g,g.dimension,g.cible,g.proportion);
        grille_champ.clear();

}
///GERE LE DEROULEMENT D'UNE PARTIE
bool game(Grille &g,bool isAlReadyStarted)
{

    nb_Mouvement=0;
        string c;
        string s;

        graphGrille grid;
    loadGrid(g,grid);

        bool isGraphique=false;
    cout << "Une version Graphique de la Grille existe, voulez vous l'utiliser ? (o=oui,n=non ):";
    cin >>c;
    while(c!="o" && c!= "n")
    {
        cout <<"commande incorrecte ! \n";
     cout << "Une version Graphique de la Grille existe, voulez vous l'utiliser ? (o=oui,n=non ):";
    cin >>c;
    }
    if(c=="o")
    {
        isGraphique=true;
    }
    c="0";

        system("cls");
        bool out=0;
        if(!isAlReadyStarted)
        demarre(g);
        while(!out)
        {
            cout << "\n";
            if(!isGraphique)///lance la version console
            {//VERSION CONSOLE
                affiche(g);

                while(c=="0")///recuperation d'une commande
                {
                cout<<"   [h]"<<endl;
                cout <<"[g][b][d]"<<endl<<endl;
                cin >> c;
                getStringArgument(c,s);
                        if(c == "g")
                        {
                            gauche(g);
                        c="o";
                        }
                        else if( c=="d")
                        {
                            droite(g);
                        c="o";
                        }
                        else if(c=="b")
                        {
                            bas(g);
                        c="o";
                        }
                        else if(c== "h")
                        {
                        haut(g);
                        c="o";
                        }
                        else if(c=="q")
                        {
                            c="o";
                            out = true;
                            return true;
                        }
                        else if(c=="s")
                        {
                            menuSauvegarder(g);
                            c="0";
                            system("CLS");
                            affiche(g);
                        }
                        else
                        {
                            c="0";
                            system("CLS");
                            cout << "Commande incorrecte ! "<<endl;
                            affiche(g);

                        }


                }
                    c="0";

                if(!out && nb_Mouvement >0)///etape suivante
                {
                place_nouvelle(g,place(caseVide(g)),nouvelle(g.proportion));///place une nouvelle
                    if(g.nbCase_Vide == 0)
                    {
                        if(plusDeMouvement(g))///test les mouvements possible
                        {
                        endOfGame(false,g.score);///lance la fin de la partie
                        out = true;
                        affiche(g);
                       }
                    }
                    if(victoire(g))///verification de l'�tat du jeu
                    {
                        affiche(g);
                        endOfGame(true,g.score);
                        out = true;
                        return false;
                    }
                    system("cls");
                    nb_Mouvement=0;
                }
            }       //VERSION GRAPHIQUE
            else   ///lance la version graphique
            {
                float timeTemp=0.2;
                float sizeVX=2.0/3.0;
                float sizeHX=1.0/3.0;
                bool nextStep=false;

                sf::Texture BACK;
                sf::Sprite Back;
                BACK.loadFromFile("data/Image/BACK.png");
                Back.setTexture(BACK);

                sf::Clock keyClock;

                   sf::RenderWindow window(sf::VideoMode(500*1.5, 500), "2048");
                   window.setFramerateLimit(60);

                   ///DECLARATION DES DIFFERENTE VUE DE LA FENETRE
                   ///VUE DE LA GRILLE
                   sf::View v(sf::FloatRect( 0,0, CASE_text.getSize().x*g.dimension,CASE_text.getSize().x*g.dimension));
                   v.setViewport(sf::FloatRect(0,0,sizeVX,1));
                   ///VUE DE L'IMAGE D'AIDE
                   sf::View help(sf::FloatRect( 0,0,250,500));
                   help.setViewport(sf::FloatRect( sizeVX,0,sizeHX,1));



            updateGrid(grid);
             while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                    {
                        window.close();
                        return true;
                    }
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)==true
                    && keyClock.getElapsedTime().asSeconds()>timeTemp)
                {
                    haut(g);
                    keyClock.restart();
                    nextStep=true;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)==true
                        && keyClock.getElapsedTime().asSeconds()>timeTemp)
                {
                    bas(g);
                    keyClock.restart();
                    nextStep=true;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)==true
                        && keyClock.getElapsedTime().asSeconds()>timeTemp)
                {
                      gauche(g);
                        keyClock.restart();
                      nextStep=true;
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)==true
                        && keyClock.getElapsedTime().asSeconds()>timeTemp)
                {
                    droite(g);
                    keyClock.restart();
                    nextStep=true;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)==true
                   &&keyClock.getElapsedTime().asSeconds()>timeTemp)
                {
                    cout << "Partie sauvegardee sous le nom : data.txt" << endl;
                    save(g,"data.txt");
                    keyClock.restart();
                }
                 if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                 {
                        window.close();
                        return true;
                 }
                if(nextStep && nb_Mouvement >0)
                {
                place_nouvelle(g,place(caseVide(g)),nouvelle(g.proportion));
                    if(g.nbCase_Vide == 0)
                    {
                        if(plusDeMouvement(g))
                        {
                        endOfGame(false,g.score);
                        out = true;
                        affiche(g);
                       }
                    }
                    updateGrid(grid);
                    if(victoire(g))
                    {
                        endOfGame(true,g.score);
                        out = true;
                    }
                    nextStep=false;
                    nb_Mouvement=0;
                }
                if(out)
                {
                    window.close();
                    return false;
                }

                window.clear();
                window.setView(v);
                drawGrille(grid,window);
                window.setView(help);
                window.draw(Back);
                window.display();
            }
            }
        }
        return false;
}
///FONCTION DU MENU PRINCIPAL
void menu()
{
    loadData();
    resetRand(false);

    ///VARIABLES DE CONTROLE DU MENU
    bool quit=false;
    bool off=false;
    char rep='0';
    string s;
    string r="0";
    string base="data/";
    cout << "Bienvenue dans 2048 ! " << endl;
    Grille savedGrid;
    Grille g;
    while(!quit)
    {

                while(r=="0")
                {
                    cout << "Voulez vous charger une partie ?"<<
                     "(entrer le nom de la sauvegarde, n=non) :";
                    cin>>r;
                getStringArgument(r,s);
                    if(r=="n")
                    {
                        r="out";
                        break;
                    }
                    else
                    {
                            r=base+r;
                            bool savedGame = load(savedGrid,r);
                            if(!savedGame)
                            {
                                r="0";
                            cout <<"commande incorrect ou fichier inexistant"<<endl;
                            }
                            else
                            {
                                r="o";
                                cout << "C'est partie" << endl;
                                break;
                            }
                    }

                }

        if(r=="o")
        {

            off=game(savedGrid,true);
        }
        else
            {

            parametragePartie(g);
        cout << "La grille est parametre a : CIBLE = " << g.cible
         << " , DIMENSION = " << g.dimension << " et PROPORTION = "<<g.proportion<<endl;
             off = game(g,false);
            }

        if(off)
        {
            cout << "Bye Bye !" << endl;
            quit=true;
            break;
        }
            rep='0';
            s="";
            while(rep=='0'&& off==false)
            {
            cout << "Voulez-vous retenter votre chance ?(o pour oui, n pour non) : ";
            cin.clear();
            cin >> rep;
                switch(rep)
                {
                case 'o':
                    cout <<"On y retourne !"<<endl;
                    break;
                case 'n':
                    cout<<"Bye Bye !"<<endl;
                    quit=true;
                    break;
                default:
                    rep='0';
                    cout <<"commande incorrect !"<<endl;
                }

            }
            rep='0';
    }
}
//FIN FONCTION CONCERNANT LE COTE UTILISATEUR
