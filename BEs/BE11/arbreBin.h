#ifndef DEF_ARBREBIN
#define DEF_ARBREBIN

/*On identifie un arbre et un pointeur vers une cellule*/

typedef struct cellule
{
  int val;
  struct cellule *ga;
  struct cellule *dr;
} CELLULE, *PCELLULE;

void SUPPRIME (PCELLULE pc);
void INSERER(PCELLULE *pc, int a);

void PARCOURS(PCELLULE pc);
void PREFIXE(PCELLULE pc);
void POSTFIXE(PCELLULE pc);

#endif
