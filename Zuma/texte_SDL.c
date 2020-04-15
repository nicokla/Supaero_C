
#include "texte_SDL.h"

/*----------------------*/

void InitialiserVarGlobalesTTF(void)
{/**/
  /*police = TTF_OpenFont("constantes/comic.ttf", 42);*/
  police = TTF_OpenFont("constantes/star_wars/Starjedi.ttf",42);
  
  noirPourTexte.r = 0;
  noirPourTexte.g = 0;
  noirPourTexte.b = 0;
  
  blancPourTexte.r=255;
  blancPourTexte.g=255;
  blancPourTexte.b=255;
  
  jaunePourTexte.r=255;
  jaunePourTexte.g=255;
  jaunePourTexte.b=0;
  
  couleurTexte=jaunePourTexte;
}

void PreparerTexte(PTEXTE_SDL pt,int x, int y)
{ /*Colle le texte dans la surface et met à jour les coord.*/
  pt->surface = TTF_RenderText_Blended(police, pt->texte, couleurTexte);
  pt->rect.x = x;
  pt->rect.y = y;
  /*pt->rect.w = pt->surface.w;
  pt->rect.h = pt->surface.h;*/
}

void PreparerTexteCentreEnCePoint(PTEXTE_SDL pt, int x, int y)
{
  pt->surface = TTF_RenderText_Blended(police, pt->texte, couleurTexte);
  pt->rect.x = x - ((pt->surface->w) / 2);
  pt->rect.y = y - ((pt->surface->h) / 2);
}

void AfficherTexte(PTEXTE_SDL pt, SDL_Surface* ecran)
{/* Blit le texte à l'écran. */
  SDL_BlitSurface(pt->surface, NULL, ecran, &(pt->rect));
}
