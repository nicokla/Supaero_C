#include "zuma.h"

 Uint32 push_event_callback (Uint32 interval, void *param)
{ /*fonction utile pour créer un évènement périodique servant à la réactualisation de l'affichage*/
  SDL_Event *event = (SDL_Event *) param;
  SDL_PushEvent (event);
  return interval;
}

int condOuiOuNon(int x){return(x==0 || x==1);}

void ConseilYoda(PCONTEXTE p)
{
  p->pause=1;
  p->avantPause=SDL_GetTicks();
  
  AffichageImageCentreeSurEcran(grandYoda, p->ecran);
  SDL_Flip(p->ecran);
  Mix_PlayChannel (-1, sonConseilYoda, 0);
  SDL_Delay(2500);
  
  p->chrono=SDL_GetTicks();
  origine+=SDL_GetTicks()-p->avantPause;
  p->pause=0;
}

void InitBiblios()
{
  SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
  TTF_Init();
  
#if (1 <= SDL_IMAGE_MAJOR_VERSION) && (2 <= SDL_IMAGE_MINOR_VERSION) && (8 <= SDL_IMAGE_PATCHLEVEL)
  int img_flags = IMG_INIT_PNG;
  int img_initted = IMG_Init(img_flags);
  if((img_initted & img_flags) != img_flags) 
    {
      fprintf(stderr, "IMG_Init failed : %s\n", IMG_GetError());
      exit(EXIT_FAILURE);
    }
#endif
  
#if (1 <= SDL_MIXER_MAJOR_VERSION) && (2 <= SDL_MIXER_MINOR_VERSION) && (10 <= SDL_MIXER_PATCHLEVEL)
  int mix_flags = MIX_INIT_OGG;
  int mix_initted = Mix_Init(mix_flags);
  if((mix_initted & mix_flags) != mix_flags) 
    {
      fprintf(stderr, "Mix_Init failed : %s\n", Mix_GetError());
      exit(EXIT_FAILURE);
    }
#endif
}

void InitialiserVarGlobales(SDL_Surface* ecran)
{/* A appeler après l'initialisation des biblio sdl, 
    * elle-même après l'utilisation de la console 
    * pour rentrer les paramètres du niveau. */
  origine=SDL_GetTicks();
  
  InitialiserVarGlobalesTTF();
  
  centreEcran.x=ORIGINE_X;
  centreEcran.y=ORIGINE_Y;
    
  pointHautGauche.x=0;
  pointHautGauche.y=0;
  pointHautGauche.w=LARGEUR_ECRAN;
  pointHautGauche.h=HAUTEUR_ECRAN_AVEC_BARRE_EN_BAS;
  
  render_timer= SDL_AddTimer (render_timer_interval_ms, push_event_callback, (void *) &render_event);  
  dynamic_timer= SDL_AddTimer(dynamic_timer_interval_ms, push_event_callback, (void *)&dynamic_event);
  
  Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
  Mix_AllocateChannels(32);
  son = Mix_LoadWAV("constantes/bell.ogg");
  sonConseilYoda = Mix_LoadWAV("constantes/star_wars/sons/May the Force be with you.ogg");
  sonGagne = Mix_LoadWAV("constantes/star_wars/sons/gagne.ogg");
  sonDefaite = Mix_LoadWAV("constantes/star_wars/sons/your father.ogg");;
  blanc = SDL_MapRGB(ecran->format, 255, 255, 255);  /*Format pour le fond d'écran*/
  noir = SDL_MapRGB(ecran->format, 0,0,0); 

/*
  images[0] = IMG_Load("constantes/ball.png");
  images[1] = IMG_Load("constantes/sphere_DarkKhaki.png");
  images[2] = IMG_Load("constantes/sphere_DimGrey.png");
  images[3] = IMG_Load("constantes/sphere_IndianRed.png");
  images[4] = IMG_Load("constantes/sphere_MediumOrchid.png");
  images[5] = IMG_Load("constantes/sphere_OliveDrab.png");
  images[6] = IMG_Load("constantes/sphere_PaleVioletRed.png");
  images[7] = IMG_Load("constantes/sphere_RoyalBlue.png");
  images[8] = IMG_Load("constantes/sphere_SandyBrown.png");
*/
  
  images[0] = IMG_Load("constantes/star_wars/Coruscant_balle.png");
  images[1] = IMG_Load("constantes/star_wars/Hoth_balle.png");
  images[2] = IMG_Load("constantes/star_wars/Tatooine_balle.png");
  images[3] = IMG_Load("constantes/star_wars/Planete_balle.png");
  images[4] = IMG_Load("constantes/star_wars/Naboo_balle.png");
  
  fondCielNocturne = IMG_Load("constantes/star_wars/background.bmp");
  yoda=IMG_Load("constantes/star_wars/yoda.bmp");
  darkMaul = IMG_Load("constantes/star_wars/darkMaul.bmp");
  victoire = IMG_Load("constantes/star_wars/victoire.png");
  defaite  = IMG_Load("constantes/star_wars/defaite.png");
  grandYoda = IMG_Load("constantes/star_wars/yoda_grand.jpg");
  
  }

int HazardCouleurParmiFile(PMAFILE pf)
{
 	int tab1[9]={0};
 	int tab2[9]={0};
	int i=0, k=0, nbCoul=0;
	PBALLE p=pf->debut->suiv;
	
	while(p!=NULL){
		if (tab1[p->couleur]==0){
	      nbCoul++; 
	      tab1[p->couleur]=1;
	    }
	    p=p->suiv;
	}
	
	for(i=0;i<9;i++){if(tab1[i]==1){tab2[k]=i; k++;}}
	
	return(tab2[rand()%nbCoul]);
}
 
void InitialiserBalleDuTir(PBALLEDUTIR pbt, int* pNbCouleurs, PMAFILE pf)
{ /*Remplis les champs de la balle du tir comme il faut en début de partie.*/
  (pbt->x) = ORIGINE_X; /** conversions */
  (pbt->y) = ORIGINE_Y; /** implicites en float*/
  (pbt->rect).x=pbt->x;
  (pbt->rect).y=pbt->y;
  pbt->vx=0; /*on suppose que le compilateur comprends que le 0 est un float*/
  pbt->vy=0; /*idem*/
  if(pf->nbBallesASortir > 0){
    pbt->couleur = rand()%(*pNbCouleurs); }
  else {
	pbt->couleur = HazardCouleurParmiFile(pf);
  }
}

void InitialiserFile(PMAFILE pf,PNIVEAU pniv)
{ /* Transforme la file pointée en file vide,
   * mais sans libérer la memoire d'éventuelles balles.*/
	pf->debut=malloc(sizeof(BALLE));
	pf->fin=pf->debut;
	pf->nbBallesASortir=pniv->nbBallesTotal;

	pf->debut->suiv=NULL;/* elle permet juste de modéliser la file vide.*/
	pf->debut->prec=NULL;
	pf->debut->dist=0;
	pf->debut->couleur=-1;/* ce n'est pas une vrai balle, donc elle n'a pas de vrai couleur.*/
}

void ReinitialiserChrono(PCONTEXTE p)
{  /*on suppose que le sdl_getTicks a déjà été fait, il reste la préparation du texte et 
    * le blittage. */
  sprintf(p->texteChrono.texte, "%ld", (p->chrono - origine)/1000);
  p->texteChrono.surface = TTF_RenderText_Blended(police, p->texteChrono.texte, couleurTexte);
  p->texteChrono.rect.x=LARGEUR_ECRAN - p->texteChrono.surface->w;
  p->texteChrono.rect.y=HAUTEUR_ECRAN_AVEC_BARRE_EN_BAS - TTF_FontHeight(police);
  AfficherTexte(&(p->texteChrono),p->ecran);
}

void InitialiserContexte(PCONTEXTE pcontexte)
{  /*Initialise le contexte.*/
  pcontexte->ecran = SDL_SetVideoMode(LARGEUR_ECRAN, HAUTEUR_ECRAN_AVEC_BARRE_EN_BAS, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
  
  pcontexte->chrono=SDL_GetTicks();
  
  pcontexte->pause = 0;
  
  pcontexte->quit=0;
  
  InitialiserVarGlobales(pcontexte->ecran);
  
  pcontexte->periode = 0;
  
  pcontexte->commentTouche = 0;

  (pcontexte->clic).x=ORIGINE_X;
  (pcontexte->clic).y=ORIGINE_Y;
  
  ReinitialiserChrono(pcontexte);
  
  strcpy(pcontexte->nomJoueur.texte,pcontexte->pniv->nomJoueur);
  PreparerTexteCentreEnCePoint(&(pcontexte->nomJoueur),LARGEUR_ECRAN/2,HAUTEUR_ECRAN_AVEC_BARRE_EN_BAS - (TTF_FontHeight(police)/2));
  
  strcpy(pcontexte->nomNiveau.texte, pcontexte->pniv->nomNiveau);
  PreparerTexte(&(pcontexte->nomNiveau),0,HAUTEUR_ECRAN_AVEC_BARRE_EN_BAS - TTF_FontHeight(police));
  
  pcontexte->dernierNbBallesTirees = 0;
  pcontexte->texte_nb_balles_sorties = malloc(4*sizeof(char));
  sprintf(pcontexte->texte_nb_balles_sorties,"%d",pcontexte->dernierNbBallesTirees);
  pcontexte->surface_nb_balles_sorties = TTF_RenderText_Blended(police, pcontexte->texte_nb_balles_sorties, couleurTexte);
  
  InitialiserFile(&(pcontexte->file), pcontexte->pniv);
  
  InitialiserBalleDuTir(&(pcontexte->balleDuTir), &(pcontexte->pniv->nbCouleurs),&(pcontexte->file)); 
}
