#ifndef VECTEURS_CTE
#define VECTEURS_CTE

#include <math.h>
#include <SDL/SDL.h>

float Norme(SDL_Rect c);
SDL_Rect Moins(SDL_Rect* p1, SDL_Rect* p2);
float Distance(SDL_Rect* p1, SDL_Rect* p2);
int ProduitScalaire(SDL_Rect v1,SDL_Rect v2);

#endif
