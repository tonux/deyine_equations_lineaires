#include  <conio.h>
#include  <stdio.h>
#include  <stdlib.h>

#define N 5
#define N1 4


#include  "meth.c"



void  fenetre();
void initmenu();
void environnement();
void selectionMenu(int num);
void deselectionMenu(int num);
void affichermenu(int num,int nbline);
void masquermenu(int num,int nbline);
void choixmenu();
void choixsmprec(int mc,int * smc);
void choixsmsuivant(int mc,int * smc);
void selectsm(int mc,int smc);
void choixsm(int mc,int smc);
void choixm(char * chaine,int mc);
void ombre(int num,int nbline);
void masquerombre(int num,int nbline);
void apropos();


unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
char * surface_car;//pour une copie totale ou partielle de l'ecran (les caracteres)
char * surface_coul;//pour une copie totale ou partielle de l'ecran (les couleurs)

char * menu="  Options     M‚thodes      Courbe    Aide     A Propos                                     ";
char * baretache="    Projet Calcul Numerique                                                     ";
int i,j,k,debut[N]= {3,15,28,39,48};
int         fin[N]= {9,22,33,42,55};
int      nbline[N]= {3,4,3,3,3};

char *  sm[N][N1];


void choixsmsuivant(int mc,int * smc)
{
    int j=(*smc)+1;

    while(sm[mc][j][4]=='Ä')   //Les lignes encadrant et separant les options
    {
	j++;
	if(j>=nbline[mc])
	    j=1;
    }
    *smc = j;
}

void choixsmprec(int mc,int * smc)
{
    int j=(*smc)-1;

    while(sm[mc][j][4]=='Ä')
    {
	j--;
	if(j<=0)
	    j=nbline[mc]-2;
    }
    *smc = j;
}


void selectsm(int mc,int smc)
{
    int i, k=debut[mc]+1;
    for(i=2; i<(strlen(sm[mc][0])-2);i++)
    {
	gotoxy(k,smc+2);
	textattr(32); //noir sur vert A REVOIR
	cprintf("%c",sm[mc][smc][i]);
	k++;
    }
}

void deselectsm(int mc,int smc)
{
    int i, k=debut[mc]+1;
    for(i=2; i<(strlen(sm[mc][0])-2);i++)
    {
	gotoxy(k,smc+2);
	textattr(112); //noir sur vert
	cprintf("%c",sm[mc][smc][i]);
	k++;
    }
}


void choixmenu()
{
    int i,mc=0,smc=1,ouvert=0,num,xs,ys,bg,bd;
    int n=0,m=0; //pour les limites effectives des surfaces
    char touche;
    do
    {
	afficher();
	do
	{
	    GetSourisXY(&xs,&ys,&bg,&bd);
	    if(bg && ((ys/8)==0)) //si on a clique sur la premiere ligne
	    {
		for(i=0;i<N;i++)
		    if((debut[i]-1<=(xs/8)) && ((xs/8)<=fin[i]))
		    {
			if(mc==(i+1))
			    break;
			deselectionMenu(mc);
			if(ouvert) coller_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,&n,&m);
			else
			    ouvert=1;
			mc=i+1;
			smc=1;
			masquer();
			selectionMenu(mc);
			afficher();
			copier_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,debut[mc-1]+strlen(sm[mc-1][0]),nbline[mc-1]+2,&n,&m);//marche bien
			affichermenu(mc-1,nbline[mc-1]);
			selectsm(mc-1,smc);
		    }
	    }
	    else
		if(bg && ouvert)
		{
		    num=mc-1;
		    smc=ys/8-1;
		    if((domaine(xs,ys,debut[num],1,debut[num]-4+strlen(sm[num][0]),nbline[num]))
			    && (sm[num][smc][4]!='Ä'))
			if((num==0) && (smc==1))//num == 0 et non 1 car il y a avant mnum = mc -1
			    exit(0); //quitter
			else
			{
			    masquer();
			    deselectionMenu(num+1);
			    coller_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,&n,&m);
			    choixsm(num,smc);
			    ouvert=0;
			    smc=1;
			    mc=0;
			    afficher();
			}
		}
	}
	while(!kbhit());
	masquer();
	selectionMenu(mc);
	touche=getch();
	if(mc==0)
	    mc=1; //La cause des mc-1
	switch(touche)
	{
	    case 72:
	    if(ouvert)
	    {
		deselectsm(mc-1,smc);
		choixsmprec(mc-1,&smc);
		selectsm(mc-1,smc);
	    }
	    break;
	    case 75: //GAUCHE faire un teste
	    deselectionMenu(mc);
	    coller_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,&n,&m);
	    //masquermenu(mc-1,nbline[mc-1]);
	    mc--;
	    smc=1;
	    if(mc==0)
		mc=N;
	    if(ouvert)
	    {
		copier_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,debut[mc-1]+strlen(sm[mc-1][0]),nbline[mc-1]+2,&n,&m);
		//opier_surface(&surface_car,&surface_coul,ecran,debut[mc]-2,2,debut[mc]+strlen(sm[mc][0]),nbline[mc-1]+3,&n,&m);
		affichermenu(mc-1,nbline[mc-1]);
		selectsm(mc-1,smc);
	    }
	    break;
	    case 77:
	    deselectionMenu(mc);
	    coller_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,&n,&m);
	    //masquermenu(mc-1,nbline[mc-1]);
	    mc++;
	    smc=1;
	    if(mc==N+1)
		mc=1;
	    if(ouvert)
	    {
		//copier_surface(&surface_car,&surface_coul,ecran,debut[mc]-2,2,debut[mc]+strlen(sm[mc][0]),nbline[mc-1]+3,&n,&m);
		copier_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,debut[mc-1]+strlen(sm[mc-1][0]),nbline[mc-1]+2,&n,&m);
		affichermenu(mc-1,nbline[mc-1]);
		selectsm(mc-1,smc);
	    }
	    break;
	    case 80:
	    if(!ouvert)
	    {
		ouvert=1;
		//copier_surface(&surface_car,&surface_coul,ecran,debut[mc]-2,2,debut[mc]+strlen(sm[mc][0]),nbline[mc-1]+3,&n,&m);
		copier_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,debut[mc-1]+strlen(sm[mc-1][0]),nbline[mc-1]+2,&n,&m);
		affichermenu(mc-1,nbline[mc-1]);//utiliser un switch()
	    }
	    else
	    {

		deselectsm(mc-1,smc);
		choixsmsuivant(mc-1,&smc);

	    }
	    selectsm(mc-1,smc);
	    break;
	    case 27:
	    if(ouvert)
	    {
		coller_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,&n,&m);
		//masquermenu(mc-1,nbline[mc-1]);
		touche=65; //pris arbitrairement differant de Echap(27)
		ouvert=0;
	    }
	    break;
	}
	selectionMenu(mc);
	if(!((touche==13) && (ouvert) && (mc==1) && (smc==1)))
	    if((touche==13) && (ouvert)) //13 pour dire la touche entree
	    {
		coller_surface1(&surface_car,&surface_coul,ecran,debut[mc-1]-1,2,&n,&m);
		choixsm(mc-1,smc);
		ouvert=0;
		smc=1;
		deselectionMenu(mc);
		mc=0;
	    }
    }
    while(!((touche==13) && (ouvert) && (mc==1) && (smc==1))); //quitter
}

void selectionMenu(int num)
{
    int i;
    for(i=(debut[num-1]);i<=fin[num-1];i++)
    {
	gotoxy(i,1);
	    textattr(32); //noir sur vert
	    cprintf("%c",menu[i-1]);
    }
}

void deselectionMenu(int num)
{
    int i;
    for(i=(debut[num-1]);i<=fin[num-1];i++)
    {
	gotoxy(i,1);
	    textattr(112); //noir sur vert
	    cprintf("%c",menu[i-1]);
    }
}

void environnement()
{
    textmode(2);
    textbackground(7); //pour gerer car(80,25)
    clrscr();
    _setcursortype(_NOCURSOR); //cacher le curseur text
    for(i=1;i<=80;i++)
    {
	gotoxy(i,1);
	    textattr(112); //noir sur blanc
	if(menu[i-1]==';')
	    cprintf("%c",240); //240 = code du car compos‚ des 3 tir‚s
	else
	    cprintf("%c",menu[i-1]);
    }
    for(i=2;i<=24;i++)
	for(j=1;j<=80;j++)
	{
	    gotoxy(j,i);
	    textattr(16);//Couleur du rectangle interne
	    cprintf("%c",' ');//178); //car brique
	}
    for(i=1;i<=79;i++)
    {
	gotoxy(i,25);
	    textattr(112);
	if(baretache[i-1]==';')
	    cprintf("%c",179);
	else
	    cprintf("%c",baretache[i-1]);
    }
}

void affichermenu(int num,int nbline)
{
    for(i=0;i<nbline;i++)
    {
	k=0;
	for(j=debut[num]-1;j<=(debut[num]-2+strlen(sm[num][0]));j++)
	{
	    gotoxy(j,i+2);
	    textattr(112);
	    cprintf("%c",sm[num][i][k++]);
	}
    }
    ombre(num,nbline);
}

void choixsm(int mc,int smc)
{
	switch(mc)
	{
		case 1 : if(smc==1)
		{       initialiserEcran(BLUE);
			acc();
			fenetre();
		}
			 if(smc==2)
		{       initialiserEcran(BLUE);
			acc();
			fenetre();
		}
			break;
		case 2 : if(smc==1)
			{
			//masquer();
			courbe();
			fenetre();
			}
			break;
		case 3 : if(smc==1) //Afficher_Index_();
			break;
		case 4 : if(smc==1)apropos();
			break;
	}
}


void ombre(int num,int nbline)
{
    for(i=1;i<=nbline;i++)
    {
	for(j=debut[num]-2+strlen(sm[num][0])+1;j<debut[num]-2+strlen(sm[num][0])+3;j++)
	{
	    gotoxy(j,i+2);
	    textattr(112);
	    cprintf("Û");
	}
    }
    i=nbline+1;
    for(j=debut[num]+1;j<=(debut[num]-2+strlen(sm[num][0]));j++)
    {
	gotoxy(j,i+1);
	textattr(112);
	cprintf("Û"); //car en brique
    }
}


void apropos()
{
unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
int i,j,k,x,y,col=22,line=7;  //pour centrer la boite de dialogue
int m=0,n=0;
char * boite[11];
char * surface_car;//pour une copie totale ou partielle de l'ecran (les caracteres)
char * surface_coul;//pour une copie totale ou partielle de l'ecran (les couleurs)

 boite[0]=" ÉÍ[ ]Í A propos CAL.NUMERIQUE ÍÍÍÍÍ» ";
 boite[1]=" º                                  º ";
 boite[2]=" º  Auteur : Mouhamed M. DEYINE     º ";
 boite[3]=" º                                  º ";
 boite[4]=" º                                  º ";
 boite[5]=" º  Emails : deyine@programmer.net  º ";
 boite[6]=" º           dey210@hotmail.com     º ";
 boite[7]=" º                                  º ";
 boite[8]=" º  Propos‚ par: Dr Samuel OUYA     º ";
 boite[9]=" º                                  º ";
boite[10]=" ÈÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍÍ¼ ";

copier_surface1(&surface_car,&surface_coul,ecran,col,line,col+strlen(boite[0])+1,line + 11,&n,&m);
	//affichage de la boite
for(i=0;i<11;i++)
{
	k=0;
	for(j=col;j<=(col-1+strlen(boite[0]));j++)
	{
	    gotoxy(j,i+line);
	    textattr(112);
	    cprintf("%c",boite[i][k++]);
	}
}
for(i=1;i<11;i++)       //ombre
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
textcolor(4);
gotoxy(col+4,line);
cprintf("þ");
afficher();
do {}
while(!(clicline(col+4,col+4,line))); // Attendre la fin du clic
masquer();
coller_surface1(&surface_car,&surface_coul,ecran,col,line,&n,&m);
}


void initmenu()
{
    //OPTION
    sm[0][0]=" ÚÄÄÄÄÄÄÄÄÄ¿ ";
    sm[0][1]=" ³ Quitter ³ ";
    sm[0][2]=" ÀÄÄÄÄÄÄÄÄÄÙ ";

    //METHODE

    sm[1][0]=" ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿ ";
    sm[1][1]=" ³ Directes   ³ ";
    sm[1][2]=" ³ Indirecte  ³ ";
    sm[1][3]=" ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ ";

    //SIMULA

    sm[2][0]=" ÚÄÄÄÄÄÄÄÄÄÄÄÄ¿ ";
    sm[2][1]=" ³ Courbe     ³ ";
    sm[2][2]=" ÀÄÄÄÄÄÄÄÄÄÄÄÄÙ ";

    //AIDE

    sm[3][0]=" ÚÄÄÄÄÄÄÄÄ¿ ";
    sm[3][1]=" ³ Aide   ³ ";
    sm[3][2]=" ÀÄÄÄÄÄÄÄÄÙ ";

    //A PROPOS

    sm[4][0]=" ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ ";
    sm[4][1]=" ³ A propos de C.Num‚rique ³ ";
    sm[4][2]=" ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ ";
}


void  fenetre()
{
 initmenu();
 environnement();
 choixmenu();
 }

void  main(){
fenetre();
}

