#include "zuma.h"

/**------------------*/
/*Fin du jeu.*/

void PreparerTexteCentreEcran(PTEXTE_SDL pt)
{
  PreparerTexteCentreEnCePoint(pt, centreEcran.x, centreEcran.y);
}

void EcranVictoire(PCONTEXTE pc)
{/*Attention message d'au max 29 caractères.*/
  pc->quit = 1;
  pc->pause=1;
  SDL_BlitSurface(victoire, NULL, pc->ecran, &pointHautGauche);
  SDL_Flip(pc->ecran);
  SDL_Delay(1000);/*1 seconde, + le temps de fermer la SDL.*/
  Mix_PlayChannel(-1,sonGagne,0);
  SDL_Delay(8000);
}

void EcranDefaite(PCONTEXTE pc)
{/*Attention message d'au max 29 caractères.*/
  pc->quit = 1;
  pc->pause=1;
  pc->pause=1;
  SDL_BlitSurface(defaite, NULL, pc->ecran, &pointHautGauche);
  SDL_Flip(pc->ecran);
  SDL_Delay(1000);/*1 seconde, + le temps de fermer la SDL.*/
  Mix_PlayChannel(-1,sonDefaite,0);
  SDL_Delay(6000);
}

void Finir(PCONTEXTE p)
{
  int i;
  for (i = 0; i < 9; i++) {
    SDL_FreeSurface(images[i]);
  }
  SDL_FreeSurface(p->ecran);
  SDL_FreeSurface(p->nomNiveau.surface);
  SDL_FreeSurface(p->nomJoueur.surface);
  SDL_FreeSurface(p->texteChrono.surface);
  Mix_FreeChunk(son);
  Mix_CloseAudio();
  TTF_CloseFont(police);
  SDL_RemoveTimer (render_timer);

#if (1 <= SDL_MIXER_MAJOR_VERSION) && (2 <= SDL_MIXER_MINOR_VERSION) && (10 <= SDL_MIXER_PATCHLEVEL)
  Mix_Quit();
#endif
#if (1 <= SDL_IMAGE_MAJOR_VERSION) && (2 <= SDL_IMAGE_MINOR_VERSION) && (8 <= SDL_IMAGE_PATCHLEVEL)
  IMG_Quit();
#endif
  TTF_Quit();
  SDL_Quit();
}
