#ifndef TEXTE_SDL_CTE
#define TEXTE_SDL_CTE

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

typedef struct
{ /*Cette structure contient tout ce qui permet de gérer un texte à afficher en SDL.*/
  char texte[30];
  SDL_Surface *surface;
  SDL_Rect rect;
} TEXTE_SDL, *PTEXTE_SDL;

  TTF_Font *police;
  SDL_Color noirPourTexte;
  SDL_Color jaunePourTexte;
  SDL_Color blancPourTexte;
  SDL_Color couleurTexte;

void InitialiserVarGlobalesTTF(void);
void PreparerTexte(PTEXTE_SDL pt,int x, int y);
void PreparerTexteCentreEnCePoint(PTEXTE_SDL pt, int x, int y);
void PreparerTexteCentreEcran(PTEXTE_SDL pt);
void AfficherTexte(PTEXTE_SDL pt, SDL_Surface* ecran);

#endif
