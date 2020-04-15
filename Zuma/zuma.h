#ifndef ZUMA_CTE
#define ZUMA_CTE

/**----------------*/
/*includes*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <malloc.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#include "io_console.h"
#include "vecteurs.h"
#include "texte_SDL.h"

/**---------------------------------*/
/*Defines*/

#define RAPPORT_VITESSE_VOL_SUR_MAFILE 10
#define RAPPORT_VITESSE_ARRIERE_SUR_MAFILE 3
#define NB_COULEURS_DEFAUT 4
#define V_FILE_DEFAUT 1
#define TAILLE_FILE_DEFAUT 20
#define LIMITE_EXPLOSION_DEFAUT 3
#define NOM_NIVEAU_DEFAUT "debutant"
#define NOM_PARCOURS_DEFAUT "cercle_debutant" /*nb de lettres = 15 < 29, OK*/
#define NOM_JOUEUR_DEFAUT "Anonyme"

#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define HAUTEUR_ECRAN_AVEC_BARRE_EN_BAS 650
#define ORIGINE_X (LARGEUR_ECRAN / 2)
#define ORIGINE_Y (HAUTEUR_ECRAN / 2)

#define DYNAMIC_UPDATE_CODE 0
#define RENDER_UPDATE_CODE 1

#define MAXCAR 30
#define coeff_note 100000

/**-------------------*/
/*Variables globales*/

  time_t origine; /*origine des temps*/
  SDL_TimerID render_timer;
  SDL_TimerID dynamic_timer;

  Mix_Chunk  *son;
  Mix_Chunk  *sonConseilYoda;
  Mix_Chunk *sonGagne;
  Mix_Chunk *sonDefaite;
  Uint32 noir; /*pour pixels*/
  Uint32 blanc; /*pour pixels*/
  
  SDL_Surface *images[9];
  SDL_Surface *fondCielNocturne;
  SDL_Surface *victoire;
  SDL_Surface *defaite;
  SDL_Surface *yoda;
  SDL_Surface *darkMaul;
  SDL_Surface *grandYoda;
    
  SDL_Rect centreEcran;
  SDL_Rect pointHautGauche;  
  
  static const Uint32 dynamic_timer_interval_ms = 16; 
static const SDL_Event dynamic_event = {.user.type=SDL_USEREVENT, .user.code=DYNAMIC_UPDATE_CODE, .user.data1=0};

static const Uint32 render_timer_interval_ms = 20;
static const SDL_Event render_event={
.user.type = SDL_USEREVENT,
.user.code = RENDER_UPDATE_CODE,
.user.data1 = 0};
/**----------------------*/
/** structures */

typedef struct balleType
{ /*Le type d'une balle du parcours.*/
  SDL_Rect rect;
  int couleur; /*compris entre 0 et 8*/
  float dist;
  int pos; /*dans le tableau abscisseCurviligne*/
  struct balleType *prec;
  struct balleType *suiv;
} BALLE, *PBALLE;

typedef struct
{ /*Le type de la balle tirée. 
  On utilise des float pour modéliser la direction du tir*/
  float x; /* Attention il s'agit non du centre mais du point en*/
  float y; /* haut à gauche de la surface de la balle */
  SDL_Rect rect;
  float vx;
  float vy;
  int couleur;
} BALLEDUTIR, *PBALLEDUTIR;

typedef struct
{ /*La file. nbBallesSorties ne représente PAS le nombre de balle actuellement visible à l'écran,
  mais juste le nombre de balles sorties du début du parcours depuis le début.*/
  PBALLE debut;
  PBALLE fin;
  int nbBallesASortir; /* Nombre de balles sorties depuis le début. Ne peut dépasser nbBallesTotal de NIVEAU.*/
} MAFILE, *PMAFILE;

typedef struct 
 { /*Cette structure contient le parcours*/
 int longueurParcours;
 SDL_Rect* tabParcours; /*cette variable et la suivante sont des tableaux alloues dynamiquement*/
 float* abscisseCurviligne;
 } PARCOURS, *PPARCOURS;

typedef struct
{  /*Cette structure contient tout les paramètres du niveau, sauf le parcours lui même*/
 int nbCouleurs;
 int limiteExplosion;
 int nbBallesTotal;
 float vFile;
 float vVol;
 float vRecul;
 char nomNiveau[30];
 char nomJoueur[30];
 char nomParcours[30];/*Il faut que ce mot soit le nom
                      * exact du fichier contenant le parcours,
                      * situé dans le dossier "parcours". */
 } NIVEAU, *PNIVEAU;

typedef struct
{/*Cette structure regroupe absolument tout ce qu'il faut pour le jeu*/

  PNIVEAU pniv; /*parametres du niveau, hors parcours*/
  PPARCOURS ppar; /*parcours*/
  
  TEXTE_SDL nomJoueur;/*Attention pas juste une chaine de caractères comme dans la struct NIVEAU*/
  TEXTE_SDL nomNiveau;
  
  TEXTE_SDL texteChrono;
  time_t chrono; /*temps actuel, en ms.*/
  time_t avantPause;
  char pause;
  char quit;
  char periode;	      /*0 avanceNormale;
                1 tir; 2 entreeFile; 3 explosions; 4 victoire; 5 défaite; */
  
  SDL_Surface* ecran;
  SDL_Event event;
  
  MAFILE file;
  PBALLE p2;/*utilisé pour le recul des
  balles apres des explosions, c'est la balle la plus en arriere
  parmi celles qui reculent*/ 
  
  BALLEDUTIR balleDuTir;
  SDL_Rect clic;
  int commentTouche; /* vrai si avant, faux si arrière */
  PBALLE pBalleTouchee;
  
  int dernierTemps;
  int dernierScore;
  
  int dernierNbBallesTirees;
  SDL_Surface* surface_nb_balles_sorties;
  char* texte_nb_balles_sorties;
} CONTEXTE, *PCONTEXTE; /*En mettant un PCONTEXTE en param, on a acces a tout*/

/**----------------------*/

/**-------------------------*/
/*1-initialisations.c*/
Uint32 push_event_callback (Uint32 interval, void *param);
int condOuiOuNon(int x);
void InitBiblios();
void ConseilYoda(PCONTEXTE p);
void InitialiserVarGlobales(SDL_Surface* ecran);
int HazardCouleurParmiFile(PMAFILE pf);
void InitialiserBalleDuTir(PBALLEDUTIR pbt, int* pNbCouleurs, PMAFILE pf);
void InitialiserFile(PMAFILE pf,PNIVEAU pniv);
void ReinitialiserChrono(PCONTEXTE p);
void InitialiserContexte(PCONTEXTE pcontexte);

/**-------------------------*/
/*2-niveau et parcours . c*/
void juxtaposer(char *a,char *b,char *c);
void AfficherNiveau(PNIVEAU pniv);
void ChargerParcours(PPARCOURS ppar,char nomFichierParcours[] );
void InitialiserNiveauEtParcours(PNIVEAU pniv,PPARCOURS ppar);
void EnregistrerNiveau (PNIVEAU pniv);
void ChargerNiveauEtParcours (PNIVEAU pniv, char nomFichierNiveau[], PPARCOURS ppar);
void SetPixel(SDL_Surface* ecran, SDL_Rect* p, Uint32 couleur);
int estDeCetteCouleur(SDL_Surface* ecran, SDL_Rect* p, Uint32 couleur);
void DessinerNouveauParcours(PPARCOURS ppar,SDL_Surface* ecran);
int DecisionAvantProgramme(PPARCOURS ppar, PNIVEAU pniv, SDL_Surface*ecran);

/**-------------------------*/
/*3-affichage.c*/
void AfficherImageCentree(SDL_Surface* pSurf, SDL_Rect* pr, SDL_Surface* ecran);
void AffichageImageCentreeSurEcran(SDL_Surface* pSurf, SDL_Surface* ecran);
void AfficherAvantBalles(PCONTEXTE pctxt, PPARCOURS ppar);
void AfficherBalleNormale(PBALLE p, SDL_Surface* ecran);
void ColorierParcours(SDL_Surface* ecran, PPARCOURS ppar);
void FondCiel(PCONTEXTE pc);
void AfficherApresBalles(PCONTEXTE pctxt, PNIVEAU pniv );
void CollerFile(PMAFILE pf, SDL_Surface *ecran);
void AfficherBalleDuTir(PBALLEDUTIR p, SDL_Surface*ecran);
void ToutAfficher(PCONTEXTE pctxt);

/**-------------------------*/
/*4-avancee File*/
void InsererBalleDebutFile(SDL_Rect*tabParcours,PMAFILE pf, int nbCouleurs,int couleurImposee);
void DeplacerFileGeneralAvant(PCONTEXTE p,PBALLE premiere, PBALLE derniere, float d);
void DeplacerFile(PCONTEXTE p);
void DeplacerFileGeneralArriere(PCONTEXTE p,PBALLE premiere, PBALLE derniere, float d);

/**-------------------------*/
/*5-tir.c*/
void PreparerTir(PCONTEXTE p);
int EstDansEcran(PBALLEDUTIR p);
void DetectionChoc(PBALLEDUTIR pb, PMAFILE pf, PCONTEXTE pc);
void AvancerBalleDuTir(PCONTEXTE p);

/**-------------------------*/
/*6-insertion.c*/
void InsererBalleApresCelleLa(PBALLE p, PMAFILE pf, PBALLE pDejaLa);
void AvancerToutApresEtAttendre(PBALLE premiere ,PCONTEXTE pc);
void InsererBalleDuTir(PCONTEXTE pc);

/**-------------------------*/
/*7-explosions.c*/
PMAFILE DoitFaireCycle(PBALLE pb, PNIVEAU pniv);
void CinematiqueCycle(PCONTEXTE pc,PNIVEAU pniv, PMAFILE pfDebutFin, PMAFILE pf);
void Explosions(PCONTEXTE pc);

/**-------------------------*/
/*8-high scores*/
int calcul_points(int temps,int nb_balles);
void ecrire_points(char *nomjoueur,char *nomniveau,int temps,int nb_balles);
void chercher_mot(FILE *f,char *mot);
void afficher_high_score(char *nomjoueur);
void ecrire_nomjoueur(char *nomniveau,char *nomjoueur);
void creer_fichier_joueur(char *nomjoueur);
void lire_profil(char *nomjoueur);

/**-------------------------*/
/*9-fin.c*/
void PreparerTexteCentreEcran(PTEXTE_SDL pt);
void EcranVictoire(PCONTEXTE pc);
void EcranDefaite(PCONTEXTE pc);
void Finir(PCONTEXTE p);

#endif

