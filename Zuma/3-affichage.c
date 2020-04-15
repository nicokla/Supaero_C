#include "zuma.h"

/* Affichage */

void AfficherImageCentree(SDL_Surface* pSurf, SDL_Rect* pr, SDL_Surface* ecran)
{
	pr->x-=pSurf->w /2;
	pr->y-=pSurf->h /2;
	SDL_BlitSurface(pSurf, NULL, ecran, pr);
	pr->x+=pSurf->w /2;
	pr->y+=pSurf->h /2;
}

void AffichageImageCentreeSurEcran(SDL_Surface* pSurf, SDL_Surface* ecran){
  AfficherImageCentree(pSurf,&centreEcran,ecran);
}

void AfficherBalleNormale(PBALLE p, SDL_Surface* ecran)
{ /* Affiche la balle pointée (pas celle du tir, mais une du parcours).*/
	AfficherImageCentree(images[p->couleur],&(p->rect),ecran);
}

void ColorierParcours(SDL_Surface* ecran, PPARCOURS ppar)
{ /* Colorie le parcours. */
  int i;
  SDL_Rect* pr=ppar->tabParcours;
  
  for(i=0;i<(ppar->longueurParcours);i++){
    SetPixel(ecran, pr+i, blanc);
  }
  
  AfficherImageCentree(yoda, pr, ecran);
  AfficherImageCentree(darkMaul,pr+(--i), ecran);
}

void FondCiel(PCONTEXTE pc)
{
  /*SDL_FillRect(pctxt->ecran, NULL, blanc);*//* Le fond blanc. */
  SDL_BlitSurface(fondCielNocturne, NULL, pc->ecran, &pointHautGauche);	
}

void AfficherAvantBalles(PCONTEXTE pctxt, PPARCOURS ppar)
{ /* Fait ce qu'il faut avant de blitter les balles. */
  FondCiel(pctxt);
  
  ColorierParcours(pctxt->ecran, ppar); /* Le parcours*/
}

void AfficherApresBalles(PCONTEXTE pctxt, PNIVEAU pniv )
{ /* Fait ce qu'il faut après le blittage des balles.*/
  ReinitialiserChrono(pctxt); /* Le chrono*/
  
  AfficherTexte(&(pctxt->nomNiveau),pctxt->ecran);  /*Le niveau*/
  AfficherTexte(&(pctxt->nomJoueur), pctxt->ecran); /* Le nom du joueur*/
  
  sprintf(pctxt->texte_nb_balles_sorties,"%d",pctxt->dernierNbBallesTirees);
  pctxt->surface_nb_balles_sorties = TTF_RenderText_Blended(police, pctxt->texte_nb_balles_sorties, couleurTexte);
  SDL_BlitSurface(pctxt->surface_nb_balles_sorties, NULL, pctxt->ecran, &pointHautGauche);
}

void CollerFile(PMAFILE pf, SDL_Surface *ecran)
{ /* Blit les balles de la file. */
  PBALLE p;

  p=(pf->debut)->suiv;
  while(p!=NULL)
  {
    AfficherBalleNormale(p,ecran);
    p=p->suiv;
  }
}

void AfficherBalleDuTir(PBALLEDUTIR p, SDL_Surface*ecran)
{ /*Blit la balle du tir.*/  
  (p->rect).x = p->x-16; /*conversion en int fait automatiquement par le compilateur*/
  (p->rect).y = p->y-16;
  SDL_BlitSurface(images[p->couleur], NULL, ecran, &(p->rect));
  p->rect.x += 16;
  p->rect.y += 16;
}

void ToutAfficher(PCONTEXTE pctxt)
{ /* Blit tout ce qu'il faut, dans le bon ordre, puis l'affiche avec SDL_Flip. */
  AfficherAvantBalles(pctxt, pctxt->ppar);
  
  CollerFile(&(pctxt->file), pctxt->ecran);
  AfficherBalleDuTir(&(pctxt->balleDuTir),pctxt->ecran);
  
  AfficherApresBalles(pctxt, pctxt->pniv);
  
  SDL_Flip(pctxt->ecran);
}
