
#include "vecteurs.h"

/**-------------------------*/
/*Opérations sur les vecteurs*/

float Norme(SDL_Rect c)
{
float d=sqrt( pow( c.x , 2.0 ) + pow( c.y ,2.0 ) );
return(d);
}

SDL_Rect Moins(SDL_Rect* p1, SDL_Rect* p2)
{/*Le premier moins le second*/
  SDL_Rect c;
  c.x=p1->x-p2->x;
  c.y=p1->y-p2->y;
  return(c);
}

float Distance(SDL_Rect* p1, SDL_Rect* p2)
{ /* Calcul la distance entre deux points.
   * en supposant que le compilateur comprend qu'il faut convertir les int en float*/
  float d = Norme(Moins(p1,p2));
  return(d);
}

int ProduitScalaire(SDL_Rect v1,SDL_Rect v2)
{
  int x= v1.x * v2.x + v1.y * v2.y;
  /*--> conversion de short en int*/
  return x;
}
