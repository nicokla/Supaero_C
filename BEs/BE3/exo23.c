#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAX 400
//#define EPSILON 0.01
//#define PI (4*atan(1))
#define PI M_PI

/*Exercice 23
sinus */

float sinus_iter (float x, int max);
void ramene (float *x);
float sinus_epsilon (float x, float precision, int max);
void ramene2 (float *x);

int
main (void)
{  
  int max=MAX;
  float x, resultat_iter, resultat_epsilon, vrai_resultat, epsilon;
  printf ("Exercice 23 : sinus\n");
  printf ("Rentrez la valeur de x\n");
  scanf ("%f", &x);
  ramene (&x);
  printf
    ("Combien de termes voulez vous dans le dvt de Taylor? (au moins 1)\n");
  scanf ("%d", &max);
  printf ("Quel precision désirez-vous dans le calcul du sinus ?\n");
  scanf ("%f", &epsilon);
  vrai_resultat = sin (x);
  resultat_iter = sinus_iter (x, max);
  resultat_epsilon = sinus_epsilon (x, epsilon, 100);
  printf ("\nSinus(x) vaut environ %f d'apres la fonction sinus_iter.\n",
	  resultat_iter);
  printf ("\nSinus(x) vaut environ %f d'apres la fonctio\
n sinus_epsilon.\n", resultat_epsilon);
  printf ("\nLe resultat de la bibliothèque math.h est %f.\n",
	  vrai_resultat);
  return 1;
}


float
sinus_iter (float x, int max)
{
  int i = 1;
  float var = x, resultat = x, x_carre = x * x;
  for (i = 1; i < max; i++)
    {
      var = var * (-x_carre / ((2 * i) * (2 * i + 1)));
      resultat = resultat + var;
    }
  return resultat;
}

void
ramene (float *x)
{
  float deux_pi = 2 * PI;
  if (*x > 0)
    deux_pi = (-deux_pi);
  while (fabs (*x) > 3.0)
    (*x) += deux_pi;
}

void
ramene2 (float *x)
{
  int n = floor(fabs(*x /(2.0 * PI)));
  if (*x < 0.0)
    *x += (n * 2.0 *PI);
  else
    *x -= (n * 2.0 *PI);
}

float
sinus_epsilon (float x, float epsilon, int max)
// max sert de sécurité.
{
  int i = 1;
  float var = x, resultat = x, x_carre = x * x;
  do
    {
      var = var * (-x_carre) / ((2 * i) * (2 * i + 1));
      resultat = resultat + var;
      i++;
    }
  while (i < max && fabs (var) > epsilon);
  return resultat;
}
