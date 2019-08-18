#include   <conio.h>
#include   <stdio.h>
#include   <stdlib.h>
#include   <string.h>
#include   <dos.h>
#include   <math.h>


#define  BL  15
#define  NR  0
#define  OR  6


//#include   "matrice.c"
#include   "masouris.h"
#include   "mem_vid.h"
#include   "interm.h"
#include   "outils.h"
#include   "Gauss.c"
#include   "LuT.c"
#include   "Cholesky.c"
#include   "Gradient.c"
#include   "Inverser.c"







void     saisie_donn(float *,float*);
void     acc();



void   acc()
{       float  *M,*b;
	M=NULL;
	b=NULL;
	textmode(2);
	saisie_donn(M,b);
}





void   saisie_donn(float  *M,float *b)
{ 	int dim=0,valid_gauch,valid_bas,valid_modif,valid_close;
	//int  espacement;
	float  *U,*L;
	unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
	int i,j,k,x,y,col=4,line=2;  //pour centrer la boite de dialogue
	char * Zone[22];
	int m=0,n=0;
	char * surface;
	int   iter=0;



	Zone[0]= "ีอออออออออออออออออออออออออออออออออออออออออออออออออออออออออออ[Fermer]อธ";
	Zone[1]= "ณ                                                                    ณ";
	Zone[2]= "ณ   Dimension :                                                      ณ";
	Zone[3]= "ณ                                                                    ณ";
	Zone[4]= "ณ                                                                    ณ";
	Zone[5]= "ณ                                                                    ณ";
	Zone[6]= "ณ                                                                    ณ";
	Zone[7]= "ณ                                                                    ณ";
	Zone[8]= "ณ                                                                    ณ";
	Zone[9]= "ณ                                                                    ณ";
	Zone[10]="ณ                                                                    ณ";
	Zone[11]="ณ                                                                    ณ";
	Zone[12]="ณ                                                                    ณ";
	Zone[13]="ณ                                                                    ณ";
	Zone[14]="ณ                                                                    ณ";
	Zone[15]="ณ                                                                    ณ";
	Zone[16]="ณ                                                                    ณ";
	Zone[17]="ณ                                                                    ณ";
	Zone[18]="ณ                                                                    ณ";
	Zone[19]="ณ                                                                    ณ";
	Zone[20]="ณ                                                                    ณ";
	Zone[21]="ิออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออออพ";
	copier_surface(&surface,ecran,col,line,col+strlen(Zone[0])+1,line + 22,&n,&m);
	//affichage de la boite


	for(i=0;i<22;i++)
		{
		k=0;
		for(j=col;j<=(col-1+strlen(Zone[0]));j++)
			{
			gotoxy(j,i+line);
			textattr(127);
			cprintf("%c",Zone[i][k++]);
			}
		}
	for(i=1;i<22;i++)       //ombre
	{
	for(j=(col-1+strlen(Zone[0]))+1;j<(col-1+strlen(Zone[0]))+3;j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û");
	}
}
	for(j=col+2;j<=(col+1+strlen(Zone[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û"); //car en brique
	}



	       //BOUTON EN BAS DE PAGE
	afficherBouton2("GAUSS",7,21,OR,NR,NR);         //Bouton GAUSS
	afficherBouton2("LU",17,21,OR,NR,NR);           //Bouton LU
	afficherBouton2("CHOLESKY",24,21,OR,NR,NR);     //Bouton CHOLESKY
	afficherBouton2("GRADIENT",37,21,OR,NR,NR);     //Bouton GRADIANT
	afficherBouton2("G.CONJUGUE",50,21,OR,NR,NR);   //Bouton GRADIANT CONJUGUE
	       //BOUTON DE MODIFICATION
	afficherBouton2("  A  ",col+10,line+4,OR,NR,NR);
	afficherBouton2("  b  ",col+38,line+4,OR,NR,NR);


	       //BOUTON A GAUCHE
	afficherBouton2("  INVERSE  ",58,13,OR,NR,NR);  //Bouton INVERSE
	afficherBouton2("DETERMINANT",58,17,OR,NR,NR);  //Bouton DETERMINANT

ecran:	Fenetre_principale();
	iter=0;
	Zone_texte(col+18,col+25,line+2,0,NR);  //DIMENSION
	Eff_fin_ligne(col+18,line+2,col+25);
	printf("%d",dim);

	Fenetre_principale();
	gotoxy(col+55,line+5);
	printf("N๘iterations");


	Zone_texte(col+3,col+3+dim+37,line+6,dim+1,NR);  //ECRAN DE SAISIE
	matrice_barre(dim,1,1,"OUVRANTE",'N');
	matrice_barre(dim,20,1,"FERMANTE",'N');
	if(dim>0&&M)
		{

		for( i=0 ; i<dim ; i++)
			{
			gotoxy(2,i+2);
			for( j=0 ; j<dim ; j++)
				printf(" %g",M[i*dim+j]);
			printf("\n");
			}
		}
	Fenetre_principale();       //Revenir … la fentre principale
	matrice_barre(dim,col+25,line+6,"OUVRANTE",'N');
	matrice_barre(dim,col+31,line+6,"FERMANTE",'N');

	gotoxy(col+27,line+7);                  //Affichage du vecteur X
	for( i=1 ; i<=dim ; i++)
		{
		  cprintf("X%d",i);
		  gotoxy(wherex()-2,wherey()+1);
		  }
	gotoxy(wherex()+6,wherey()-(dim/2)-1);  cprintf("=");

	matrice_barre(dim,col+35,line+6,"OUVRANTE",'N');
	matrice_barre(dim,col+41,line+6,"FERMANTE",'N');
	if(dim>0&&b)
		for( i=0 ; i<dim ; i++)
		{
		      gotoxy(col+36,line+7+i);
		      printf(" %g\n",b[i]);
		}

ecran1:

	Zone_texte(col+55,col+64,line+6,0,NR);  //Nombre d'iterations
	Eff_fin_ligne(col+55,line+6,col+64);
	printf(" %d",iter);
	Fenetre_principale();


	afficher();
	do{
	    valid_bas=clicline(7,13,21)||clicline(17,20,21)||clicline(24,33,21)||clicline(37,46,21)||clicline(50,61,21);
	    valid_gauch=clicline(58,70,13)||clicline(58,70,17);
	    valid_modif=clicline(col+10,col+16,line+4)||clicline(col+38,col+44,line+4)||clicline(col+18,col+25,line+2);
	    valid_close=clicline(col+61,col+67,2);
	   }
	while(!(valid_gauch||valid_bas||valid_modif||valid_close));
	delay(100);        //pour patienter


	if(valid_modif)
	{
		 if(clicline(col+10,col+16,line+4))
		 {
			if(dim<=0)
			    info("ERREUR CRITIQUE","Saisir dimension",OR);

			else
			{
			    if(M)
			    {
			      free(M);
			      M=NULL;
			    }
			    M=modif(dim,dim,"A");
			}
		 }
		 if(clicline(col+38,col+44,line+4))
		 {
			if(dim<=0)
			    info("ERREUR CRITIQUE","Saisir dimension",OR);

			else
			{
			    if(b)
			    {
				free(b);
				b=NULL;
			    }
			    b=modif(dim,1,"B");
			}
		  }

		 if(clicline(col+18,col+25,line+2))
		 {      i=dim;
			Zone_texte(col+18,col+25,line+2,0,NR);  //DIMENSION
			Eff_fin_ligne(col+18,line+2,col+25);
			fflush(stdin);
			scanf("%d",&dim);
			Zone_texte(col+3,col+3+i+37,line+6,i+1,BL); //Rtablir l'cran
			Fenetre_principale();       //Revenir … la fentre principale

			if(dim<=0){
			    info("ERREUR CRITIQUE","Dimension positive!!",OR);
			    dim=0;
			    }

			if(b)
			  {
			    free(b);
			    b=NULL;
			  }
			 if(M)
			  {
			    free(M);
			    M=NULL;
			  }
		 }
		 masquer();
		 goto ecran;
	}
	if(valid_gauch)
	{
	  if(clicline(58,70,13))
	  {   if(M)
	      inverse(M,dim);
	  }
	  if(clicline(58,70,17))
	  {  if(M)
	     determ(determinant(M,dim));

	  }
	 masquer();
	 goto ecran1;

	}
	if(valid_bas)
	{
		if(clicline(7,13,21))
		{
		      if(dim==0)
			    info("ERREUR CRITIQUE","Saisir dimension",OR);
		      else
			if(M&&b)
			    GAUSS(M,b,dim,'o',&iter);

		}
		if(clicline(17,20,21))
		{
		      if(dim==0)
			    info("ERREUR CRITIQUE","Saisir dimension",OR);
		      else
			if(M&&b)
			    LU(M,b,dim,'o',&iter);

		}
		if(clicline(24,33,21))
		{
		      if(dim==0)
			    info("ERREUR CRITIQUE","Saisir dimension",OR);
		      else
			if(M&&b)
			    chol(M,b,dim,&iter);

		}

		if(clicline(37,46,21))
		{
		      if(dim==0)
			    info("ERREUR CRITIQUE","Saisir dimension",OR);
		      else
			if(M&&b)
			    m_gradient(M,b,dim,&iter);
		}
		if(clicline(50,61,21))
		{
		      if(dim==0)
			    info("ERREUR CRITIQUE","Saisir dimension",OR);
		      else
			if(M&&b)
			    m_gradient_conj(M,b,dim,&iter);
		}

	masquer();
	 goto ecran1;
	}
	masquer();

	coller_surface(&surface,ecran,col,line,&n,&m);
}

int    longue(float *M,int dim)
{
	int i,j,max=0,temp;
	for(i=0;i<dim;i++)
	{
		temp=0;
		for(j=0;j<dim;j++)
			if(M[i*dim+j]!=0.0)
				temp+=(int)(log10(fabs(M[i*dim+j])))+1;
			else
				temp++;
		if(max<temp)
			max=temp;
	}
	return(max);
}


