#include "zuma.h"

/*-------------*/
/* Tir */

void PreparerTir(PCONTEXTE p)
{
  float distance;
  SDL_Rect fleche;
  
  fleche = Moins(&(p->clic),&(centreEcran));
  distance=Norme(fleche);
  
  p->balleDuTir.vx = (fleche.x*(p->pniv->vVol))/distance ;
  p->balleDuTir.vy = (fleche.y*(p->pniv->vVol))/distance ;
}

int EstDansEcran(PBALLEDUTIR p)
{
  int dansEcran = 
  (p->rect.x- 16  > 0 && 
  p->rect.x + 16 < LARGEUR_ECRAN &&
  p->rect.y -16> 0 && 
  p->rect.y +16< HAUTEUR_ECRAN);
  return(dansEcran);
}

void DetectionChoc(PBALLEDUTIR pb, PMAFILE pf, PCONTEXTE pc)
{
	PBALLE p;
	int cond;
	
	p=pf->debut->suiv;
	cond=0;
	
	while(p!=NULL && !cond){
		cond = ( Distance(&(pb->rect),&(p->rect)) <= 32 );
		if(!cond) p=p->suiv;
		/*La condition permet d'avoir en sortie la balle touchée
		 *si on touche, et pas la suivante. On aurait pu faire p->prec ensuite, 
		 * mais on a un pb si la balle touchée est la dernière (on a NULL->prec). */
	}
	
	if(cond) { /*Si on a touché une balle, on passe à l'insertion. */
		pc->periode=2;
		pc->pBalleTouchee=p;	
		pc->commentTouche = 
		  ProduitScalaire(Moins(&(p->rect),&(pb->rect)),
		                  Moins(&((pc->ppar->tabParcours)[p->pos+3]),
		                        &((pc->ppar->tabParcours)[p->pos]))) < 0;
	}
}

void AvancerBalleDuTir(PCONTEXTE p)
{
  p->balleDuTir.x += p->balleDuTir.vx;
  p->balleDuTir.y += p->balleDuTir.vy;
  p->balleDuTir.rect.x = p->balleDuTir.x;
  p->balleDuTir.rect.y = p->balleDuTir.y;
  
  if( ! EstDansEcran(&(p->balleDuTir)) ){
	  InitialiserBalleDuTir(&(p->balleDuTir),&(p->pniv->nbCouleurs),&(p->file));
	  p->periode=0;
  }
  
  DetectionChoc(&(p->balleDuTir),&(p->file),p);
}
