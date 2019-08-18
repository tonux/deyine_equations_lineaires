
#define BLEU 1
#define NOIR 0
#define BLANC 7
#include<process.h>

void horloge();
void afficherBouton(char *,int,int,int,int);
void afficherBouton2(char * libelle,int col,int ligne,int couleurFond,int couleurTexte,int couleurOmbre);
void initialiserEcran(int);
void Zone_texte(int,int,int,int,int);
void Fenetre_principale();
void Eff_fin_ligne(int,int,int);
void info(char* chaine1,char* chaine2,int couleur);
void curseur();
void nocurseur();
void Button(char * libelle,int col,int ligne,int couleurFond,int couleurTexte,int couleurOmbre);




void     matrice_barre(int dim,int x,int y,char * form,char color)
{	int i;
	//Affichage de la barre ouvrante
	if(color=='N')
	textattr(15);
	else
	textattr(31);
	for( i = 0 ; i<dim+2 ; i++)
		{gotoxy(x,y+i);
		 if(i==0)
			(strcmpi(form,"OUVRANTE")==0)? cprintf("ฺ"):cprintf("ฟ");
			else
			    if(i==dim+1)
				(strcmpi(form,"OUVRANTE")==0)? cprintf("ภ"):cprintf("ู");
				else
					cprintf("ณ");
		 }
  }



void horloge()
{
   struct date d;
   struct  time t;

   window(1,1,80,25);
   getdate(&d);
   gettime(&t);
   gotoxy(59,24); printf("%2d:%02d:%02d\n",t.ti_hour, t.ti_min, t.ti_sec);
   gotoxy(70,24); printf("%d/%d/%d", d.da_day, d.da_mon, d.da_year);
}

void nocurseur()
{_setcursortype(_NOCURSOR);
}

void curseur()
{_setcursortype(_NORMALCURSOR);
}


void Eff_fin_ligne(int x1,int y1,int x2)
  {int i;
  textbackground(NOIR); textcolor(BLANC);
  gotoxy(x1,y1);
  for(i=x1;i<=x2;i++)
    cprintf(" ");	      // Permet d'effacer la fin d'une ligne
  gotoxy(x1,y1);
    }

void initialiserEcran(int couleur)
{
	textmode(2);
	textbackground(couleur);
	clrscr();
}


void  Fenetre_principale()     //Permet de revenir sur la fenetre principale
{ window(1,1,80,25);}

void  Zone_texte(int coldeb,int colfin,int ligne,int largeur,int
couleurfond)
  {
  window(coldeb,ligne,colfin,ligne+largeur);
  textbackground(couleurfond);clrscr();
  }



void afficherBouton2(char * libelle,int col,int ligne,int couleurFond,int couleurTexte,int couleurOmbre)
{
	int i;
	window(col,ligne,col+ strlen(libelle)+1,ligne);
	textbackground(couleurFond);
	textcolor(couleurTexte);
	clrscr();
	printf(" %s",libelle);
	window(1,1,80,25); //rinitialiser
	textcolor(couleurOmbre);
	textbackground(BLANC);
	for(i=col+1;i<=(col+ strlen(libelle)+2);i++)
	{
		gotoxy(i,ligne+1);cprintf("฿");        //code('฿')=223
	}
	gotoxy(col+strlen(libelle)+2,ligne);cprintf("Ü");  //code('Ü')=220
}

void    Button(char * libelle,int col,int ligne,int couleurFond,int couleurTexte,int couleurOmbre)
{
	int i;
	window(col,ligne,col+ strlen(libelle)+1,ligne);
	textbackground(couleurFond);
	textcolor(couleurTexte);
	clrscr();
	printf(" %s",libelle);
	window(1,1,80,25); //rinitialiser
	textcolor(couleurOmbre);
	textbackground(BLUE);
	for(i=col+1;i<=(col+ strlen(libelle)+2);i++)
	{
		gotoxy(i,ligne+1);cprintf("฿");        //code('฿')=223
	}
	gotoxy(col+strlen(libelle)+2,ligne);cprintf("Ü");  //code('Ü')=220
}



void afficherBouton(char * libelle,int col,int ligne,int couleurFond,int couleurTexte)
{
	window(col,ligne,col+ strlen(libelle)+1,ligne);
	textbackground(couleurFond);
	textcolor(couleurTexte);
	clrscr();
	printf(" %s",libelle);
}

void info(char* chaine1,char* chaine2,int couleur)
{
unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
int i,j,k,x,y,col=22,line=9;  //pour centrer la boite de dialogue
char * boite[7];
int m=0,n=0;
char * surface;


boite[0]=" ษอ[ ]ออออInfoออออออออออออออออออออออป ";
boite[1]=" บ                                  บ ";
boite[2]=" บ  Type :                          บ ";
boite[3]=" บ                                  บ ";
boite[4]=" บ  Indication :                    บ ";
boite[5]=" บ                                  บ ";
boite[6]=" ศออออออออออออออออออออออออออออออออออผ ";

copier_surface(&surface,ecran,col,line,col+strlen(boite[0])+1,line + 7,&n,&m);
	//affichage de la boite
for(i=0;i<7;i++)
{
	k=0;
	for(j=col;j<=(col-1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("%c",boite[i][k++]);
	}
}
for(i=1;i<7;i++)       //ombre
{
	for(j=(col-1+strlen(boite[0]))+1;j<(col-1+strlen(boite[0]))+3;j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û");
	}
}
	for(j=col+2;j<=(col+1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û"); //car en brique
	}

	//affichage du contenu
for(i=0;i<strlen(chaine1);i++)
{
	gotoxy(col+11+i,line+2);
	textattr(couleur);
	cprintf("%c",chaine1[i]);
}
for(i=0;i<strlen(chaine2);i++)
{
	gotoxy(col+16+i,line+4);
	textattr(couleur);
	cprintf("%c",chaine2[i]);
}
textcolor(116);
gotoxy(col+4,line);
cprintf("þ");
afficher();
do {}
while(!(clicline(col+4,col+4,line)));
masquer();
coller_surface(&surface,ecran,col,line,&n,&m);
afficher();
}
	  //Modification de la matrice



float* modif(int ligne,int colonne,char *nom)
{

unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
int i,j,k,x,y,col=22,line=12;  //pour centrer la boite de dialogue
char * boite[5];
int m=0,n=0;
char * surface;//pour une copie totale ou partielle de l'ecran (les caracteres)

float *X;

boite[0]=" ษอ[Modification]ออออออป ";
boite[1]=" บ                     บ ";
boite[2]=" บ                     บ ";
boite[3]=" บ                     บ ";
boite[4]=" ศอออออออออออออออออออออผ ";

copier_surface(&surface,ecran,col,line,col+strlen(boite[0])+1,line + 5,&n,&m);
	//affichage de la boite
for(i=0;i<5;i++)
{
	k=0;
	for(j=col;j<=(col-1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("%c",boite[i][k++]);
	}
}
for(i=1;i<5;i++)       //ombre
{
	for(j=(col-1+strlen(boite[0]))+1;j<(col-1+strlen(boite[0]))+3;j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û");
	}
}
	for(j=col+2;j<=(col+1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û"); //car en brique
	}
 if(colonne==1)
 {
    X=alloc_vecteur(ligne);
    for( i=0; i<ligne ; i++)
	{
	 gotoxy(col+2,line+2);
	 textattr(112);
	 cprintf("%s[%d] : ",nom,i+1);
	 textattr(112);
	 cprintf("ÛÛÛÛÛÛÛÛ");
	 gotoxy(wherex()-8,wherey());
	 textattr(15); scanf("%f",&X[i]);
	 }
    }
     else
	{
	X=alloc_matrice(ligne);
	 for( i=0; i<ligne ; i++)
		{
		for ( j=0; j<colonne ; j++)
			{
			gotoxy(col+2,line+2);
			textattr(112);
			cprintf("%s[%d][%d] : ",nom,i+1,j+1);
			textattr(112);
			cprintf("ÛÛÛÛÛÛÛÛ");
			gotoxy(wherex()-8,wherey());
			textattr(15); scanf("%f",&X[i*ligne+j]);
			}
		}
	 }


coller_surface(&surface,ecran,col,line,&n,&m);
return(X);
}



//              inverse de matrice
void inver(float *A,int dim)
{
unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
int i,j,k,x,y,col=22,line=9;  //pour centrer la boite de dialogue
char * boite[9];
int m=0,n=0;
char * surface;


boite[0]=" ษอ[ ]ออออInverseอออออออออออออออออออป ";
boite[1]=" บ                                  บ ";
boite[2]=" บ                                  บ ";
boite[3]=" บ                                  บ ";
boite[4]=" บ                                  บ ";
boite[5]=" บ                                  บ ";
boite[6]=" บ                                  บ ";
boite[7]=" บ                                  บ ";
boite[8]=" ศออออออออออออออออออออออออออออออออออผ ";

copier_surface(&surface,ecran,col,line,col+strlen(boite[0])+1,line + 9,&n,&m);
	//affichage de la boite
for(i=0;i<9;i++)
{
	k=0;
	for(j=col;j<=(col-1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("%c",boite[i][k++]);
	}
}
for(i=1;i<9;i++)       //ombre
{
	for(j=(col-1+strlen(boite[0]))+1;j<(col-1+strlen(boite[0]))+3;j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û");
	}
}
	for(j=col+2;j<=(col+1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û"); //car en brique
	}

matrice_barre(dim,col+3,line+1,"OUVRANTE",'B');
matrice_barre(dim,col+19,line+1,"FERMANTE",'B');

for ( i=0;i<dim;i++)
	{
	gotoxy(col+5,line+2+i);
	for(j=0;j<dim;j++)
	{
		if(j!=dim-1)
		{
		       if(A[i*dim+j]>0)
				printf("%.1f  ",A[i*dim+j]);
		       else
				printf("%.1f ",A[i*dim+j]);
		}
		else{
		       if(A[i*dim+j]>0)	printf("%.1f",A[i*dim+j]);
		       else             printf("%.1f  ",A[i*dim+j]);
		     }
	}


	 }


textattr(116);
gotoxy(col+4,line);
cprintf("þ");

afficher();
do {}
while(!(clicline(col+4,col+4,line)));
masquer();
coller_surface(&surface,ecran,col,line,&n,&m);
afficher();
}


//     Determinant

void determ(float det)
{
unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
int i,j,k,x,y,col=22,line=9;  //pour centrer la boite de dialogue
char * boite[4];
int m=0,n=0;
char * surface;

boite[0]=" ษอ[ ]ออออDeterminantอออออออออออป ";
boite[1]=" บ                              บ ";
boite[2]=" บ                              บ ";
boite[3]=" ศออออออออออออออออออออออออออออออผ ";

copier_surface(&surface,ecran,col,line,col+strlen(boite[0])+1,line + 4,&n,&m);
	//affichage de la boite
for(i=0;i<4;i++)
{
	k=0;
	for(j=col;j<=(col-1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("%c",boite[i][k++]);
	}
}
for(i=1;i<4;i++)       //ombre
{
	for(j=(col-1+strlen(boite[0]))+1;j<(col-1+strlen(boite[0]))+3;j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û");
	}
}
	for(j=col+2;j<=(col+1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û"); //car en brique
	}

gotoxy(col+3,line+2);

//         POUR L'AFFICHAGE DU DETERMINANT
printf(" DETERMINANT :%g",det);



textattr(116);
gotoxy(col+4,line);
cprintf("þ");

afficher();
do {}
while(!(clicline(col+4,col+4,line)));
masquer();
coller_surface(&surface,ecran,col,line,&n,&m);
afficher();
}
void   traite(char *chemin,char* fx,int binf,int bsup){
FILE *F;
		if((F=fopen(chemin,"w"))==NULL)
		{
			perror("Erreur d'ouverture");
			getch();
			exit(0);
		}
	////////////TRAITEMENT////////////
		fprintf(F,"float f(float x)\n{\nreturn (%s);\n}\n",fx);
//		fprintf(F,"int sup()\n{\nreturn (%d);\n}\n",bsup);
//		fprintf(F,"int inf()\n{\nreturn (%d);\n}\n",binf);
		close(F);
}



void   courbe(){
unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
int i,j,k,x,y,col=22,line=9;  //pour centrer la boite de dialogue
char * boite[10];
int m=0,n=0;
char * surface;
char *fx;
int  born_sup=1,born_inf=0;


boite[0]=" ษอ[ ]ออFonctionออออออออออออออออออออป ";
boite[1]=" บ                                  บ ";
boite[2]=" บ F(x) =                           บ ";
boite[3]=" บ                                  บ ";
boite[4]=" บ Inf  =                           บ ";
boite[5]=" บ                                  บ ";
boite[6]=" บ Sup  =                           บ ";
boite[7]=" บ                                  บ ";
boite[8]=" บ                                  บ ";
boite[9]=" ศออออออออออออออออออออออออออออออออออผ ";

copier_surface(&surface,ecran,col,line,col+strlen(boite[0])+1,line + 10,&n,&m);
	//affichage de la boite
for(i=0;i<10;i++)
{
	k=0;
	for(j=col;j<=(col-1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("%c",boite[i][k++]);
	}
}
for(i=1;i<10;i++)       //ombre
{
	for(j=(col-1+strlen(boite[0]))+1;j<(col-1+strlen(boite[0]))+3;j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û");
	}
}
	for(j=col+2;j<=(col+1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("Û"); //car en brique
	}
	Zone_texte(col+12,col+35,line+2,0,NR);
	Zone_texte(col+12,col+19,line+4,0,NR);
	Zone_texte(col+12,col+19,line+6,0,NR);
	afficherBouton2("Tracer",col+27,line+7,OR,NR,NR);         //Bouton GAUSS

	Fenetre_principale();
textattr(116);
gotoxy(col+4,line);
cprintf("þ");
	i=0;

ecr:
	afficher();
	do {}
	while(!(clicline(col+4,col+4,line)||clicline(col+27,col+33,line+7)||clicline(col+12,col+35,line+2)||clicline(col+12,col+19,line+4)||clicline(col+12,col+25,line+6)));
	delay(100);
	if(clicline(col+12,col+35,line+2))
	{
		Zone_texte(col+12,col+35,line+2,0,NR);
		Eff_fin_ligne(col+12,line+2,col+35);
		curseur();
		fflush(stdin);
		scanf("%s",fx);
		i=1;
		Fenetre_principale();
		nocurseur();
		masquer();
		goto ecr;
	}
	if(clicline(col+12,col+19,line+4))
	{
inf:		Zone_texte(col+12,col+19,line+4,0,NR);
		Eff_fin_ligne(col+12,line+4,col+19);
		fflush(stdin);
		curseur();
		scanf("%d",&born_inf);
		Fenetre_principale();
		if(born_inf>=born_sup)
		{
			info("ERREUR CRITIQUE","born_inf<born_sup",OR);
			goto inf;
		}
		nocurseur();
		masquer();
		goto ecr;
	}
	if(clicline(col+12,col+19,line+6))
	{
Sup:		Zone_texte(col+12,col+19,line+6,0,NR);
		Eff_fin_ligne(col+12,line+6,col+19);
		fflush(stdin);
		curseur();
		scanf("%d",&born_sup);
		Fenetre_principale();
		if(born_inf>=born_sup)
		{
			info("ERREUR CRITIQUE","born_inf<born_sup",OR);
			goto Sup;
		}
		nocurseur();
		masquer();
		goto ecr;
	}


if(clicline(col+27,col+33,line+7))
{       if(i==1)
	{
		masquer();
		coller_surface(&surface,ecran,col,line,&n,&m);
		traite("fonction.h",fx,born_inf,born_sup);
		system("d:\\tc\\bin\\tcc courbe.c graphics.lib");
		system("courbe.exe");
		afficher();
	}
	if(i==0)
	{
		info("ERREUR CRITIQUE","Saisir fonction",OR);
		delay(200);
		masquer();
		goto ecr;
	}
}
if(clicline(col+4,col+4,line))
{
	masquer();
	coller_surface(&surface,ecran,col,line,&n,&m);
	afficher();
}
}