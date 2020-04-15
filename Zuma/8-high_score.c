#include "zuma.h"

/*chercher un mot dans une fichier*/
void chercher_mot(FILE *f,char *mot){
	char *temp;	
	
	temp=malloc(sizeof(char)*MAXCAR);
	fscanf(f,"%s",temp);
	while( strcmp(temp,mot)!=0 ){
		fscanf(f,"%s",temp);
	}
}

/*Afficher les meilleurs scores*/
void afficher_high_score(char *nomjoueur){
	FILE *f;
	char *joueur,*temp,*temp1;
	int stock;

	stock=0;
	joueur=malloc(sizeof(char)*MAXCAR);
	temp=malloc(sizeof(char)*MAXCAR);
	temp1=malloc(sizeof(char)*MAXCAR);
	juxtaposer("joueurs/",nomjoueur,joueur);
	f=fopen(joueur,"r");
	printf("\n");
	
	/*On affiche les meilleurs scores suivant les niveaux*/
	printf("*****************debutant***********\n");
	/*On fait deux fscanf de suite car le premier ne nous intéresse pas*/	
	fscanf(f,"%s",temp);
	fscanf(f,"%s",temp);
	printf("score : %s\n",temp);
	printf("*****************intermédiaire***********\n");
	fscanf(f,"%s",temp);
	fscanf(f,"%s",temp);
	printf("score : %s\n",temp);
	printf("*****************expert***********\n");
	fscanf(f,"%s",temp);
	fscanf(f,"%s",temp);
	printf("score : %s\n",temp);

	printf("\nTappez sur 1 puis enter pour continuer\n");
	while( stock!=1 ){
		scanf("%d",&stock);
	}
	free(joueur);
	free(temp);
	free(temp1);
	fclose(f);
}

/*Calcul des points du score*/
int calcul_points(int temps,int nb_balles){
	/*On divise le temps par 1000 car il est en ms*/	
	return (coeff_note*(1000/(float)temps)*(1/(float)nb_balles));
}


/*Ecriture des scores dans le fichier du joueur*/
void ecrire_points(char *nomjoueur,char *nomniveau,int temps,int nb_balles){
	FILE *f,*f1;
	int note,score;
	char *joueur,*joueur1,*temp,*temp1;

	/*Initialisation des variables*/	
	note=calcul_points(temps,nb_balles);
	joueur=malloc(sizeof(char)*MAXCAR);
	temp=malloc(sizeof(char)*MAXCAR);
	
	/*Ouverture du fichier*/
	juxtaposer("joueurs/",nomjoueur,joueur);
	f=fopen(joueur,"r");
	
	/*On cherche le score à modifier dans le fichier*/
	chercher_mot(f,nomniveau);
	fscanf(f,"%d",&score);
	if( score<note ){
		fseek(f,0,SEEK_SET);
	
		/*Ouverture d'un nouveau fichier*/
		joueur1=malloc(sizeof(char)*MAXCAR);
		temp1=malloc(sizeof(char)*MAXCAR);
		juxtaposer(nomjoueur,"1",temp1);
		juxtaposer("joueurs/",temp1,joueur1);
		f1=fopen(joueur1,"w");

		/*On recopie tout dans le fichier f1 jusqu'à trouver le bon niveau*/
		fscanf(f,"%s",temp);
		while( strcmp(temp,nomniveau)!=0 ){
			fprintf(f1,"%s\n",temp);			
			fscanf(f,"%s",temp);
		}
		fprintf(f1,"%s\n",temp);
	
	
		/*On met dans le fichier f1 le nouveau score et on recopie le reste du fichier f*/
		fscanf(f,"%d",&score);
		fprintf(f1,"%d\n",note);
		while( fscanf(f,"%s",temp)!=EOF ){
			fprintf(f1,"%s\n",temp);
		}

		/*Enfin, on supprime le fichier f et on renomme le fichier f1*/
		remove(joueur);
		rename(joueur1,joueur);
		free(joueur1);
		free(temp1);
		fclose(f1);
	}
	free(joueur);
	free(temp);
	fclose(f);
}

/*Ecrire le nom du joueur dans le fichier du niveau*/
void ecrire_nomjoueur(char *nomniveau,char *nomjoueur){
	FILE *f,*fcpy;
	char *temp,*temp1,*nomniveau1;
	int i;

	temp=malloc(sizeof(char)*MAXCAR);
	temp1=malloc(sizeof(char)*MAXCAR);
	nomniveau1=malloc(sizeof(char)*MAXCAR);
	juxtaposer("niveaux/",nomniveau,temp);
	juxtaposer(nomniveau,"1",temp1);
	juxtaposer("niveaux/",temp1,nomniveau1);

	f=fopen(temp,"r");
	fcpy=fopen(nomniveau1,"w");

	/*On recopie dans le fichier fcpy les données présente dans f jusqu'au nom du joueur*/ 
	for(i=0;i<7;i++){
		fscanf(f,"%s",temp1);
		fprintf(fcpy,"%s\n",temp1);
	}

	/*On écrit le nom du joueur dans fcpy*/ 
	fscanf(f,"%s",temp1);
	fprintf(fcpy,"%s\n",nomjoueur);
	fscanf(f,"%s",temp1);
	fprintf(fcpy,"%s\n",temp1);
	
	/*On renome le fichier fcpy du nom du fichier f et on supprime fcpy*/
	remove(temp);
	rename(nomniveau1,temp);
	free(temp);
	free(temp1);
	free(nomniveau1);
	fclose(fcpy);
	fclose(f);
}

/*Création d'un fichier joueur*/
void creer_fichier_joueur(char *nomjoueur){
	FILE *f;
	char *temp;

	temp=malloc(sizeof(char)*MAXCAR);
	juxtaposer("joueurs/",nomjoueur,temp);
	f=fopen(temp,"w");

	fprintf(f,"cercle_debutant\n");
	fprintf(f,"0\n");
	fprintf(f,"cercle_intermediaire\n");
	fprintf(f,"0\n");
	fprintf(f,"cercle_expert\n");
	fprintf(f,"0\n");

	free(temp);
	fclose(f);
}

/*lecture du fichier "fichier_profil" à la recherche du pseudo du joueur
Si le pseudo n'est pas présent on le rajoute dans "fichier_profil"*/
void lire_profil(char *nomjoueur){
	FILE *f;
	int test;
	char *temp;

	temp=malloc(sizeof(char)*MAXCAR);
	test=1;
	f=fopen("joueurs/fichier_profil","r");

	
	while( (fscanf(f,"%s",temp)!=EOF) ){
		if( strcmp(temp,nomjoueur)==0 ){
			test=0;
		}
	}

	fclose(f);
	if(test!=0){
		f=fopen("joueurs/fichier_profil","a");
		fprintf(f,"%s\n",nomjoueur);		
		creer_fichier_joueur(nomjoueur);
		fclose(f);
	}
	free(temp);
}
	
	

