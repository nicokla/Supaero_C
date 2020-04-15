#include "zuma.h"

/*-------------*/
/* Explosions */

PMAFILE DoitFaireCycle(PBALLE pb, PNIVEAU pniv)
{
	int n=1;
	PMAFILE pm = malloc(sizeof(MAFILE));
	
	  pm->debut = pb;
	  pm->fin=pb;
	
	  while(pm->debut->prec != NULL && pm->debut->couleur == pm->debut->prec->couleur){
	    pm->debut = pm->debut->prec;
	    n++;
	  }
	
      while(pm->fin->suiv != NULL && pm->fin->couleur == pm->fin->suiv->couleur){
	    pm->fin = pm->fin->suiv;
	    n++;
	  }
	
	  if(n >= pniv->limiteExplosion)return pm;
	  else return NULL;
}

void CinematiqueCycle(PCONTEXTE pc,PNIVEAU pniv, PMAFILE pfDebutFin, PMAFILE pf)
{/*pfDebutFin pointe vers la premiere et la derniere balle à exploser.*/
	PBALLE p1=pfDebutFin->debut->prec;
	PBALLE p2=pfDebutFin->fin->suiv;
    /*p1 et p2 sont les balles à rapprocher de part et d'autre de l'explosion.*/
    
	PBALLE p=pfDebutFin->debut;
	PBALLE temp;
	
    if(pfDebutFin->fin == pf->fin){
	/*Si la derniere a exploser est la derniere de la file,
	 * la derniere de la file est à present p1.*/
	  pf->fin = p1;
	
	/*si en fait il ne reste plus rien et que d'autres balles doivent arriver
	 * on commence à en sortir une.*/
    if(pf->debut == pf->fin && pf->nbBallesASortir >0)
      InsererBalleDebutFile(pc->ppar->tabParcours,pf,pniv->nbCouleurs,-1);
	}

    /*On libere les boules supprimees*/
	while(p!=NULL && p!=p2){
	  temp = p->suiv;
	  free(p);
	  p=temp;
	}
	
	/*on lie les deux boules autour du trou dans la structure*/
	if(p1!=NULL){p1->suiv = p2;}
	if(p2 != NULL){p2->prec = p1;}
    
    if(!(p1==pf->debut && p2==NULL && pf->nbBallesASortir ==0)){
/* si on est pas dans le cas où (tout a explosé et il ne reste aucune balle à rajouter) 
 * c-a-d si on est pas à la fin du jeu*/
	InitialiserBalleDuTir(&(pc->balleDuTir),&(pc->pniv->nbCouleurs),&(pc->file));
    }
    
    if(p1 !=NULL && p2 != NULL && p1->couleur == p2->couleur){
	    pc->p2 = p2;
	    pc->periode=6;
	    pc->pBalleTouchee=p1; 
	    /*p2, ça fonctionnerait aussi car ils ont la mm couleur 
	     * donc on les contera tous les 2 de toutes façon*/
    }
    else pc->pBalleTouchee = NULL;
}

void Explosions(PCONTEXTE pc)
{
	PMAFILE autreCycleNecessaire=DoitFaireCycle(pc->pBalleTouchee,pc->pniv);
	/* ceci vaut car on a mis la balle qui vient d'arriver dans pBalleTouchee,
	 * cf fin de "InsererBalleDuTir" */
	
	while(autreCycleNecessaire!=NULL && pc->periode == 3){
	  CinematiqueCycle(pc,pc->pniv,autreCycleNecessaire,&(pc->file));
	  if(pc->pBalleTouchee != NULL)
	    autreCycleNecessaire = DoitFaireCycle(pc->pBalleTouchee,pc->pniv);
	  else autreCycleNecessaire = NULL;
	}
	
  if(pc->periode == 3){	
	if(pc->file.debut==pc->file.fin && pc->file.nbBallesASortir==0){
	  pc->periode = 4;
	  /* Remarque : c'est le seul endroit du jeu où des balles disparaissent,
	   * donc où on peut gagner.*/
	  EcranVictoire(pc);
	}
	
	else{
	  pc->periode=0;
    }
  }
}
