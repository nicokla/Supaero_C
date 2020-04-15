/*Exercice 25
fichier numeroter ligne */
//___________________________________

//http://www.cplusplus.com/reference/clibrary/cstdio/fopen/
//http://www.cplusplus.com/reference/clibrary/cstdio/fprintf/
//http://www.siteduzero.com/tutoriel-3-14052-lire-et-ecrire-dans-des-fichiers.html

// __________________________________

#include <stdio.h>
#define TAILLE_MAX 1000
#define FICHIER1 "test1.txt"
#define FICHIER2 "test2.txt"

int main()
{   printf("Ex.25 : Numerote les lignes du fichier1, deja existant.\n");

    FILE* fichier1 = fopen(FICHIER1 , "r");
    FILE* fichier2 = fopen(FICHIER2 ,"w");
    char chaine[TAILLE_MAX] = "";
    int i=1;

    if (fichier1 != NULL)
    {

//____________________________________________________________

while (fgets(chaine, TAILLE_MAX, fichier1) != NULL)
        {
            fprintf(fichier2,"%d %s",i,chaine); i++;
        }

//______________________________________________________________
        fclose(fichier1); fclose(fichier2);     
    }
remove(FICHIER1);
rename(FICHIER2,FICHIER1);
    return 0;
}
