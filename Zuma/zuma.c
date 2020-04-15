#include "zuma.h"

/*int condNbCouleurs(int i){return(i>=2 && i<=9);}*/
int condVitesseTir(float x){ return (x>0. && x<10.);}

/*------------*/
/*Evolution*/

void Evoluer (PCONTEXTE pctxt)
{/* Réactualise les paramètres du jeu en vue de l'image suivante,
  * avant l'appel de la fonction de réaffichage.*/
  
  pctxt->chrono=SDL_GetTicks();
  /* pctxt->periode peut valoir :
   * -1 menu; 0 avanceNormale;
   *  1 tir; 2 entreeFile; 3 explosions; 4 victoire; 5 défaite; */
  if(pctxt->periode==0 || pctxt->periode ==1) 
    DeplacerFile(pctxt);
  if(pctxt->periode == 1)
    AvancerBalleDuTir(pctxt);
  if(pctxt->periode == 2)
    InsererBalleDuTir(pctxt);
    /* Les cas 0, 1 et 2 intègrent tous le cas 5 (défaite)
     * cf fonction DeplacerFileGeneral. */
  if(pctxt->periode == 3)
    Explosions(pctxt); 
    /* Integre le cas 4, ie Victoire.*/
  if(pctxt->periode == 6){
    if(Distance(&(pctxt->p2->prec->rect),&(pctxt->p2->rect))>32){
      DeplacerFileGeneralArriere(pctxt, pctxt->p2, pctxt->file.fin, pctxt->pniv->vRecul);
    }
    else pctxt->periode = 3;
  }
}


/*------------------------------------*/

void Jouer(PCONTEXTE pctxt)
{/*La boucle du jeu.*/
  InsererBalleDebutFile(pctxt->ppar->tabParcours,&(pctxt->file),pctxt->pniv->nbCouleurs,-1);

  ConseilYoda(pctxt);
  
  while (!(pctxt->quit) && SDL_WaitEvent (&(pctxt->event))) {
    switch (pctxt->event.type) {
    case SDL_QUIT:
      pctxt->quit=1;
      break;

    case SDL_MOUSEBUTTONDOWN:
      if (pctxt->event.button.button == SDL_BUTTON_LEFT && pctxt->periode == 0) {
		    Mix_PlayChannel (-1, son, 0);
      		pctxt->clic.x=pctxt->event.motion.x;
			pctxt->clic.y=pctxt->event.motion.y;
			pctxt->periode = 1;
			pctxt->dernierNbBallesTirees += 1;
			PreparerTir(pctxt);
      }
      break;

    case SDL_KEYDOWN:
      if (pctxt->event.key.keysym.sym == SDLK_SPACE) {
	   if(pctxt->pause==0){
	      pctxt->avantPause=SDL_GetTicks();
	   }
	   else{
	      pctxt->chrono=SDL_GetTicks();
	      origine+=SDL_GetTicks()-pctxt->avantPause;
	   }
	   pctxt->pause=1-pctxt->pause;
      }
      
      else if(pctxt->event.key.keysym.sym == SDLK_ESCAPE) {
	    pctxt->quit=1;
	  }
      break;

    case SDL_USEREVENT:
      if (pctxt->event.user.code == RENDER_UPDATE_CODE && !(pctxt->pause) && !(pctxt->quit)) {
      	ToutAfficher(pctxt);
      }
    
      if (pctxt->event.user.code == DYNAMIC_UPDATE_CODE && !(pctxt->pause) && !(pctxt->quit)){
        Evoluer(pctxt);
      }
      
      break;
    }
  }
  
  if(pctxt->periode == 4 || pctxt->periode == 5){
    ecrire_points(pctxt->pniv->nomJoueur,pctxt->pniv->nomParcours,pctxt->chrono,pctxt->dernierNbBallesTirees);
    /*EnregistrerScore(pctxt);*/
  }
}

/*----------------------*/

int main(int argc, char **argv)
{/* Regroupe les initialisations nécessaires,
  * le jeu proprement dit , puis la libération de 
  * la mémoire allouée et la fermeture de la SDL.*/

  NIVEAU niveau;
  PARCOURS parcours;
  CONTEXTE contexte;
  int x=2;
  
  contexte.pniv=&niveau;
  contexte.ppar=&parcours;
  
  srand(time(NULL));
  
  printf("\n*********************** ZUMA **************************");
  demanderMot30 ("\n\nVeuillez rentrer votre pseudo : ",
                 niveau.nomJoueur,
                 &condVraiMot);
  lire_profil(niveau.nomJoueur);
  printf("\n");
	  
  x=DecisionAvantProgramme(&parcours, &niveau, contexte.ecran);
  
  
  while(x==0){
  InitBiblios();
  InitialiserContexte(&contexte);
  Jouer(&contexte);
  Finir(&contexte);
  x=DecisionAvantProgramme(&parcours, &niveau,contexte.ecran);}
  
  printf("\n\n*************** A bientot %s ! *************\n\n",niveau.nomJoueur);
 
  return EXIT_SUCCESS;
}

