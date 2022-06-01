#include <iostream>
#include <iomanip>
#include <string>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <QList>

using namespace std;

struct coordonnees{
    int X;
    int Y;
};

enum cases{
    VIDE,
    ARGENT,
    TETE
};

enum direction{
    NORD,
    SUD,
    EST,
    OUEST
};

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const int LARGEUR = 200;
const int HAUTEUR = 50;

cases plateauJeu[HAUTEUR][LARGEUR];

int randRange(int numberMin, int numberMax);
void afficheRectangle(int score);
void placeArgent();
void initialiseRectangle();
void mouvement(direction direction, coordonnees& tete, bool& mort, int& score,QList<coordonnees>& liste);
direction associeDirection(char caracterePresse);
void ajusteTailleSnake(int score, QList<coordonnees>& liste);


int main(){

    srand(time(0));
    initialiseRectangle();
    plateauJeu[HAUTEUR/2][LARGEUR/2] = TETE;
    coordonnees tete {HAUTEUR/2,LARGEUR/2};
    bool mort = false;
    QList<coordonnees> listeCoordonnees;
    listeCoordonnees.append(tete);
    int score = 0;
    char caractere = 0;
    placeArgent();
    do{
        afficheRectangle(score);
        Sleep(200/(score+1));
        if(kbhit()){
            do{
                caractere = getch();
            }while (caractere!=97&&caractere!=100&&caractere!=115&&caractere!=119);
        }
        system("cls");
        mouvement(associeDirection(caractere),tete,mort,score,listeCoordonnees);
        ajusteTailleSnake(score,listeCoordonnees);
    }while(mort == false);
    cout << "PERDU !!! Vous avez fait " << score << " points. NUL!" << endl << endl << endl << endl << endl;
}



int randRange(int numberMin, int numberMax){
    //calcule le nombre aléatoire
    int randomNumber = rand() % (numberMax - numberMin + 1) + numberMin;
    return randomNumber;
}

void initialiseRectangle(){
    for (int a=0; a<LARGEUR; a++) {
        for (int b=0; b<HAUTEUR; b++) {
            plateauJeu[a][b] = VIDE;
        }
    }
}

void placeArgent(){
    int tempL = 0;
    int tempH = 0;
    do{
        tempL = randRange(0,LARGEUR-1);
        tempH = randRange(0,HAUTEUR-1);
    }while(plateauJeu[tempL][tempH] != VIDE);
    plateauJeu[tempH][tempL] = ARGENT;
}

void afficheRectangle(int score){
    cout << "|SNAKE GAME by Nicolas Charpie|" << endl;
    SetConsoleTextAttribute(hConsole, 12);
    cout << " -----------------------------" << endl << endl;
    cout << " ";
    for(int i=0; i<LARGEUR;i++){
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-";
    }
    cout << endl;
    for(int i=0; i<HAUTEUR;i++){
        SetConsoleTextAttribute(hConsole, 12);
        cout << "|";
        for(int j=0;j<LARGEUR;j++){
            if(plateauJeu[i][j]==VIDE)
                cout << " ";
            if(plateauJeu[i][j]==ARGENT){
                SetConsoleTextAttribute(hConsole, 14);
                cout << "$";
            }
            if(plateauJeu[i][j]==TETE){
                SetConsoleTextAttribute(hConsole, 10);
                cout << "O";
            }
        }
        SetConsoleTextAttribute(hConsole, 12);
        cout << "|" << endl;
    }
    cout << " ";
    for(int i=0; i<LARGEUR;i++){
        SetConsoleTextAttribute(hConsole, 12);
        cout << "-";
    }
    cout << endl;
    SetConsoleTextAttribute(hConsole, 7);
    cout << "Votre score est de : " << score << endl << endl << endl;
}

bool estMort(coordonnees tete){
    bool mort = false;
    if(tete.X < 0 || tete.X > LARGEUR -1 || tete.Y < 0 || tete.Y > HAUTEUR -1 ||
            plateauJeu[tete.X][tete.Y] == TETE){
        mort = true;
    }else{
        mort = false;
    }
    return mort;
}

void mouvement(direction direction, coordonnees& tete, bool& mort, int& score,QList<coordonnees>& liste){
        switch(direction){
        case NORD:
            tete.X--;
            if(plateauJeu[tete.X][tete.Y]!=VIDE && plateauJeu[tete.X][tete.Y]!=ARGENT){
                mort = true;
            }else{
                if(plateauJeu[tete.X][tete.Y]==ARGENT){
                    score++;
                    placeArgent();
                }
                plateauJeu[tete.X][tete.Y] = TETE;
                liste.append(tete);
            }
            break;
        case SUD:
            tete.X++;
            if(plateauJeu[tete.X][tete.Y]!=VIDE && plateauJeu[tete.X][tete.Y]!=ARGENT){
                mort = true;
            }else{
                if(plateauJeu[tete.X][tete.Y]==ARGENT){
                    score++;
                    placeArgent();
                }
                plateauJeu[tete.X][tete.Y] = TETE;
                liste.append(tete);
            }
            break;
        case OUEST:
            tete.Y--;
            if(plateauJeu[tete.X][tete.Y]!=VIDE && plateauJeu[tete.X][tete.Y]!=ARGENT){
                mort = true;
            }else{
                if(plateauJeu[tete.X][tete.Y]==ARGENT){
                    score++;
                    placeArgent();
                }
                plateauJeu[tete.X][tete.Y] = TETE;
                liste.append(tete);
            }
            break;
        case EST:
            tete.Y++;
            if(plateauJeu[tete.X][tete.Y]!=VIDE && plateauJeu[tete.X][tete.Y]!=ARGENT){
                mort = true;
            }else{
                if(plateauJeu[tete.X][tete.Y]==ARGENT){
                    score++;
                    placeArgent();
                }
                plateauJeu[tete.X][tete.Y] = TETE;
                liste.append(tete);
            }
            break;
        }
}

direction associeDirection(char caracterePresse){
    direction directionFinale = NORD;
    switch(caracterePresse){
    case 97 :
        directionFinale = OUEST;
        break;
    case 100 :
        directionFinale = EST;
        break;
    case 115 :
        directionFinale = SUD;
        break;
    case 119 :
        directionFinale = NORD;
        break;
    default:
        break;
    }
    return directionFinale;
}

void ajusteTailleSnake(int score, QList<coordonnees>& liste){
    while(score+3<liste.count()){
        plateauJeu[liste[0].X][liste[0].Y]=VIDE;
        liste.pop_front();
    }
}
