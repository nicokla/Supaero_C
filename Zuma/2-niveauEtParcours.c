#include "zuma.h"

int condParam(int i){return (i>=1 && i<=9);}
int condChoix1(int i){return (i>=-1 && i<=5);}
/*à changer si on fini la fonction "creation de parcours", mettre
 * 6 au lieu de 5. */

void juxtaposer(char *a,char *b,char *c){
	int i,k;
		
	i=0;
	k=0;
	while( *(a+i)!='\0' ){
		c[i]=*(a+i);
		i++;
	}
	while( *(b+k)!='\0' ){
		c[i]=*(b+k);
		k++;
		i++;
	}
	c[i]='\0';
}


void AfficherNiveau(PNIVEAU pniv)
{ /* Sert à afficher les paramètres du niveau */
  printf("Voici les parametres actuels du niveau :\n\n");  
  printf("1) Nb Couleurs : %d\n",pniv->nbCouleurs);
  printf("2) Limite explosion : %d\n",pniv->limiteExplosion);
  printf("3) Taille file : %d\n",pniv->nbBallesTotal);
  printf("4) Vitesse file : %f\n",pniv->vFile);
  printf("5) Vitesse vol : %f\n",pniv->vVol);
  printf("6) Vitesse recul : %f\n",pniv->vRecul);
  printf("7) Nom niveau : %s\n",pniv->nomNiveau);
  printf("8) Nom joueur : %s\n",pniv->nomJoueur);
  printf("9) Nom parcours : %s\n\n",pniv->nomParcours);
}

void ChargerParcours(PPARCOURS ppar,char nomFichierParcours[] )
{ /* Charge le parcours dans le fichier demandé.*/
  FILE* f1;
  int i;
  char nomFichierTotal[39]="parcours/";
  /*--> 39 cases car "parcours/" a 9 caractères, et que
   * nomFichierParcours a maximum 30 cases, et qu'on le concatene dans nomFichierTotal
   * cf ligne suivante --> */
  
  f1 = fopen( strcat(nomFichierTotal,nomFichierParcours) , "r" );
  
  fscanf( f1, "%d", &(ppar->longueurParcours) );
  /*if((ppar->tabParcours)!=NULL) free(ppar->tabParcours);*/
  ( ppar->tabParcours ) = malloc( sizeof(SDL_Rect) * (ppar->longueurParcours) );
  /*if((ppar->abscisseCurviligne)!=NULL) free(ppar->abscisseCurviligne);*/
  ( ppar->abscisseCurviligne ) = malloc ( sizeof(float) *(ppar->longueurParcours) );
  
  for( i = 0 ; i < (ppar->longueurParcours) ; i++ )
  {
    fscanf ( f1 , "%hd %hd" , &((ppar->tabParcours)[i].x) , &((ppar->tabParcours)[i].y));
  }
  fclose(f1);
  /*--> Le %hd au lieu de %d signifie que c'est un short int 
   * au lieu d'un int normal : il est codé sur 2 octets et non 4.*/
  
  (ppar->abscisseCurviligne)[0]=0;
  for(i=1;i<(ppar->longueurParcours);i++){
    (ppar->abscisseCurviligne)[i] = (ppar->abscisseCurviligne)[i-1] + 
	Distance((ppar->tabParcours)+i-1,(ppar->tabParcours)+i);
  }
}

void InitialiserNiveauEtParcours(PNIVEAU pniv,PPARCOURS ppar)
{ /* Initialise le niveau et le parcours avec les param par défaut.
   * Attention veillez à ne pas supprimer le fichier "parcours_cercle"
   * présent dans le dossier parcours.*/
  pniv->nbCouleurs = NB_COULEURS_DEFAUT;
  pniv->limiteExplosion = LIMITE_EXPLOSION_DEFAUT;
  pniv->nbBallesTotal = TAILLE_FILE_DEFAUT;
  pniv->vFile = V_FILE_DEFAUT;
  pniv->vVol =RAPPORT_VITESSE_VOL_SUR_MAFILE * (pniv->vFile);
  pniv->vRecul = RAPPORT_VITESSE_ARRIERE_SUR_MAFILE * (pniv->vFile);
  /*strcpy((pniv->nomJoueur), NOM_JOUEUR_DEFAUT );*/ 
  /*-->l'utilisateur donne toujours son nom au début du programme,
   * l'initialisation est donc ici inutile*/
  strcpy((pniv->nomNiveau), NOM_NIVEAU_DEFAUT);
  strcpy((pniv->nomParcours), NOM_PARCOURS_DEFAUT);
  ChargerParcours(ppar, NOM_PARCOURS_DEFAUT);
}

void EnregistrerNiveau (PNIVEAU pniv)
{ /* Enregistre le niveau pointé dans un fichier s'appelant le nom du niveau.*/
  char nomFichierNiveau[20] = "";
  FILE* f;
  char nomFichierTotal[28]="niveaux/";
  
  printf("Quel est le nom du fichier ou enregistrer le niveau ? : ");
  /* --> on suppose raisonnablement qu'il ne dépasse pas 19 lettres, puisqu'on compte le \O.*/
  scanf("%s", nomFichierNiveau);
  strcpy(pniv->nomNiveau , nomFichierNiveau);
  strcat(nomFichierTotal,nomFichierNiveau); 
  f=fopen( nomFichierTotal , "w+" );
  
  fprintf(f,"%d\n",pniv->nbCouleurs);
  fprintf(f,"%d\n",pniv->limiteExplosion);
  fprintf(f,"%d\n",pniv->nbBallesTotal);
  fprintf(f,"%f\n",pniv->vFile);
  fprintf(f,"%f\n",pniv->vVol);
  fprintf(f,"%f\n",pniv->vRecul);
  fprintf(f,"%s\n",pniv->nomNiveau);
  fprintf(f,"%s\n",pniv->nomJoueur);
  fprintf(f,"%s\n",pniv->nomParcours);
  
  fclose(f);
}

void ChargerNiveauEtParcours (PNIVEAU pniv, char nomFichierNiveau[], PPARCOURS ppar)
{ /*Charge dans le fichier tous les param du niveau, dont le nom du parcours,
   * puis charge le parcours ayant ce nom.*/
  FILE* f1;
  char nomFichierTotal[50]="niveaux/";

  f1 = fopen( strcat(nomFichierTotal,nomFichierNiveau) , "r" );
  
  fscanf(f1, "%d", &(pniv->nbCouleurs));
  fscanf(f1, "%d", &(pniv->limiteExplosion));
  fscanf(f1, "%d", &(pniv->nbBallesTotal));
  fscanf(f1, "%f", &(pniv->vFile));
  fscanf(f1, "%f", &(pniv->vVol));
  fscanf(f1, "%f", &(pniv->vRecul));
  fscanf(f1, "%s", (pniv->nomNiveau));
  fscanf(f1, "%s", (pniv->nomJoueur));
  fscanf(f1, "%s", (pniv->nomParcours));
  memset(ppar,0,sizeof(PARCOURS));
  ChargerParcours(ppar, pniv->nomParcours);
  
  fclose(f1);
}

void SetPixel(SDL_Surface* ecran, SDL_Rect* p, Uint32 couleur)
{ /* Met le pixel (de l'écran) demandé à la couleur voulue */
  *((Uint32*)(ecran->pixels) + p->x + p->y * ecran->w) = couleur;
}

int estDeCetteCouleur(SDL_Surface* ecran, SDL_Rect* p, Uint32 couleur)
{
  return (*((Uint32*)(ecran->pixels) + p->x + p->y * ecran->w) == couleur);
}


void DessinerNouveauParcours(PPARCOURS ppar,SDL_Surface* ecran)
{ /* Dessin d'un nouveau parcours à mettre dans pniv, et
   * sauvegardé dans un fichier d'un nom demandé à l'utilisateur*/

/*A faire*/
}

int DecisionAvantProgramme(PPARCOURS ppar, PNIVEAU pniv, SDL_Surface*ecran)
{ /* Permet à l'utilisateur de choisir tous les paramètres du jeu,
   * dont le parcours. */
  int fini;
  int j=0;
  char nomFichier[50]="scores/";
  juxtaposer(nomFichier,pniv->nomJoueur,nomFichier);
  juxtaposer(nomFichier,"/",nomFichier);
  juxtaposer(nomFichier,pniv->nomNiveau,nomFichier);
  
  InitialiserNiveauEtParcours(pniv,ppar); /*on met les parametres par defaut*/
  
  while(fini != 0 && fini != -1){
    fini=2;
   
   printf("\n0 : Commencer la partie\n");
   printf("1 : charger un niveau\n");
   printf("2 : Visualiser les parametres actuels\n");
   printf("3 : Changer a la main un parametre\n");
   printf("4 : Sauvegarder les parametres dans un fichier\n");
   printf("5 : Afficher mes meilleurs scores pour ce niveau\n");
   /*printf("6 : Creer un parcours\n");*/
   printf("-1: Quitter\n");
	
    demanderEntier("\n", &fini, &condChoix1);
	
    switch(fini){
	
	case(-1):break;
	case(0):break;
    case 2:AfficherNiveau(pniv);break;

	case 3:
	demanderEntier("Quel est le numero du parametre a modifier ? (entre 1 et 9)",&j, &condParam);
        printf("\nRentrez le nouveau parametre :");
	  if(j==1)      scanf("%d", &(pniv->nbCouleurs));
	  else if(j==2) scanf("%d", &(pniv->limiteExplosion));
	  else if(j==3) scanf("%d", &(pniv->nbBallesTotal));
	  else if(j==4) scanf("%f", &(pniv->vFile));
	  else if(j==5) scanf("%f", &(pniv->vVol));
	  else if(j==6) scanf("%f", &(pniv->vRecul));
	  else if(j==7) scanf("%s", (pniv->nomNiveau));
	  else if(j==8) scanf("%s", (pniv->nomJoueur));
	  else if(j==9) {scanf("%s",(pniv->nomParcours));
	                 ChargerParcours(ppar, pniv->nomParcours);}
	break;
	
	case 1:
	printf("Quel niveau voulez-vous charger parmi ceux-ci ? Attention, le programme \
	ne gere pas les erreurs ici, et le nom doit faire moins de 20 lettres.\n");
	system("ls ./niveaux");
	scanf("%s",(pniv->nomNiveau));
	ecrire_nomjoueur(pniv->nomNiveau,pniv->nomJoueur);
	ChargerNiveauEtParcours(pniv, pniv->nomNiveau, ppar);
	break;
	
	case 4:
	EnregistrerNiveau(pniv);
	break;
	
	case 5:
	  /*AfficherScore(nomFichier);*/
	  afficher_high_score(pniv->nomJoueur);
	break;
	/*
	case 6:
	DessinerNouveauParcours(ppar,ecran);
	break;*/

	}
  }
  return fini;
}
