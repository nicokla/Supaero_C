#ifndef DEF_mafile
#define DEF_mafile

/*pre=précédent, sui=suivant*/
typedef struct cellule
{
  int val;
  struct cellule *sui;
  struct cellule *pre;
} CELLULE, *PCELLULE;


/*deb=début*/
typedef struct mafile
{
  PCELLULE deb;
  PCELLULE fin;
} MAFILE, *PMAFILE;

void INIT_FILE (PMAFILE pf);
void RAZ (PMAFILE pf);
int VIDE (MAFILE f);
void ENFILER_A_DROITE (PMAFILE pf, int x);
void DEFILER_A_GAUCHE (PMAFILE pf);
int DEB(MAFILE f);
void AFFICHER_FILE (MAFILE f);

#endif
