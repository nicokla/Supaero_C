#include "zuma.h"

/*-------------*/
/*Insertion*/

void InsererBalleApresCelleLa(PBALLE p, PMAFILE pf, PBALLE pDejaLa)
{
  p->prec = pDejaLa;
  p->suiv = pDejaLa->suiv;
  pDejaLa->suiv=p;
  if(p->suiv!=NULL){
    p->suiv->prec=p;
  }
  if(pf->fin == pDejaLa){pf->fin=p;}
}

void AvancerToutApresEtAttendre(PBALLE premiere ,PCONTEXTE pc)
{
	pc->pause = 1;
	DeplacerFileGeneralAvant(pc,premiere,(pc->file.fin),34);
	ToutAfficher(pc);
	SDL_Delay(100);
	origine += 100;
	pc->pause=0;
}

void InsererBalleDuTir(PCONTEXTE pc)
{
  PBALLE pbAncien;
  PBALLE pbNew=malloc(sizeof(BALLE));
  
  if (pc->pBalleTouchee == pc->file.debut->suiv &&
      !(pc->commentTouche)){
    InsererBalleDebutFile(pc->ppar->tabParcours,&(pc->file),pc->pniv->nbCouleurs,pc->balleDuTir.couleur);
    pbNew=pc->file.debut->suiv;
    pc->pBalleTouchee = pbNew->suiv;/*ne sert à priori à rien mais au cas où*/
  }
  
  else {/*si on ne doit pas l'insérer au début*/
	  if(pc->commentTouche){pbAncien=pc->pBalleTouchee;}
	  else{pbAncien = pc->pBalleTouchee->prec;}
	  
      pbNew->couleur = pc->balleDuTir.couleur;
      pbNew->rect.w=32;
      pbNew->rect.h=32;
      pbNew->pos = pbAncien->pos + 32;
      pbNew->rect.x = (pc->ppar->tabParcours[pbNew->pos]).x;
      pbNew->rect.y = (pc->ppar->tabParcours[pbNew->pos]).y;
      pbNew->dist = pc->ppar->abscisseCurviligne[pbNew->pos];

	  AvancerToutApresEtAttendre(pbAncien->suiv,pc);
	  InsererBalleApresCelleLa(pbNew,&(pc->file),pbAncien);
  }
  
  InitialiserBalleDuTir(&(pc->balleDuTir),&(pc->pniv->nbCouleurs),&(pc->file));
  
  pc->pBalleTouchee = pbNew;/*--> Pour la période des explosions on a besoin de 
  connaitre la balle qui vient d'entrer, donc on la met là.*/
  pc->periode = 3;
}
