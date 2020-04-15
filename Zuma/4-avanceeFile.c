#include "zuma.h"
/*Avancée de la file*/

void InsererBalleDebutFile(SDL_Rect*tabParcours,PMAFILE pf, int nbCouleurs,int couleurImposee)
{
	PBALLE pb=malloc(sizeof(BALLE));
	
	if(couleurImposee<0 && pf->nbBallesASortir==0){}
	/* si il ne reste aucune balle à sortir et qu'on  veut rajouter 
	 * une balle par le début, on a pas le droit.  */
	
	else{ 
	  if(pf->debut->suiv == NULL){
	    pb->dist=0;
	    pb->pos=0;}
	  else {
		pb->dist=pf->debut->suiv->dist - 32;
		if (pb->dist<0) pb->dist=0;
		  pb->pos = pf->debut->suiv->pos - 32;
		if (pb->pos <0) pb->pos = 0;}
	  
	  pb->rect.x=tabParcours[pb->pos].x;
	  pb->rect.y=tabParcours[pb->pos].y; 
		
	  if(couleurImposee>=0 && couleurImposee<9)pb->couleur=couleurImposee;
	  else pb->couleur=rand()%nbCouleurs;

	  pb->prec = pf->debut;
	  pb->suiv = pf->debut->suiv; /*marche même si c'est le pointeur NULL.*/
	  if(pf->debut->suiv != NULL){
		  pf->debut->suiv->prec = pb;/* Ce qu'il y a avant l'ancienne 1ere boule est la new 1ere boule.*/
	  }
	  pf->debut->suiv = pb;
	  
	  if(pb->suiv == NULL){pf->fin = pb;}
	  if(couleurImposee<0)(pf->nbBallesASortir) --;}
}

void DeplacerFileGeneralAvant(PCONTEXTE p,PBALLE premiere, PBALLE derniere, float d)
{
	PBALLE pb;

	pb = (premiere);
	
	if(p->file.debut==p->file.fin || p->file.debut->suiv->dist > 34){
		InsererBalleDebutFile(p->ppar->tabParcours,&(p->file),p->pniv->nbCouleurs,-1);
	}

	while(pb!=(derniere)->suiv && pb!=NULL){
			/*on fait avancer la boule*/
			if(pb != premiere) pb->dist = pb->prec->dist + 34;
			else pb->dist += d;

			while( (pb->dist - (p->ppar->abscisseCurviligne)[pb->pos])>0 ){
				(pb->pos)++;
			}
			
			  if(pb->pos > 0) {
				(pb->pos) --;}
			  pb->rect.x = (p->ppar->tabParcours)[pb->pos].x;
			  pb->rect.y = (p->ppar->tabParcours)[pb->pos].y;
			  if(pb->suiv!=NULL && pb->suiv->dist - pb->dist <= 34.1)
			    pb = pb->suiv;
			  else 
			    pb=NULL;
	}
	
   if(derniere->pos >= p->ppar->longueurParcours) {
	          p->quit =1;
			  p->periode = 5;
			  EcranDefaite(p);
			  /* Remarque : c'est le seul endroit du jeu où on peut
			   * perdre, car si on fait avancer une balle de la file
			   * on passe forcément par ici. */
   }
   	 
}

void DeplacerFile(PCONTEXTE p)
{
  DeplacerFileGeneralAvant(p,p->file.debut->suiv,p->file.fin,p->pniv->vFile);
}

void DeplacerFileGeneralArriere(PCONTEXTE p,PBALLE premiere, PBALLE derniere, float d)
{
  PBALLE pb;

	pb=derniere;
	
	while(pb!= (premiere->prec) && pb!=NULL){
			if(pb!=derniere) pb->dist = pb->suiv->dist - 32;
			else pb->dist -= d;

			while( (pb->dist - (p->ppar->abscisseCurviligne)[pb->pos])<0 ){
				(pb->pos)--;
			}
		      (pb->pos) ++;
		      
			  pb->rect.x = (p->ppar->tabParcours)[pb->pos].x;
			  pb->rect.y = (p->ppar->tabParcours)[pb->pos].y;
			  if(pb->prec!=NULL && pb->dist- pb->prec->dist <= 32.1)
			    pb = pb->prec;
			  else 
			    pb=NULL;
	}
}
