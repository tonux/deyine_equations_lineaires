//#include<stdio.h>
//#include<stdlib.h>
//#include<conio.h>
//#include<dos.h>



void changerCoulCar(unsigned char far * ecran, int x, int y, int col);
void changerCar(unsigned char far * ecran, int x, int y, char car);
unsigned int ind_carxy(int x, int y);
unsigned int ind_coulxy(int x, int y);
void enreg_ecran(char *tempon);
void retablir_ecran(char *tempon);
/***** PROCEDURE DE COPIE/COLLER D'UN RECTANGLE QULELCONQUE DE L'ECRAN****/
void copier_surface1(char ** surface_car, char ** surface_coul, unsigned char far *ecran, int x1, int y1, int x2, int y2,int * n, int * m);
//char ** parce que nous devons allouer les surfaces dans la fonction c'est a dire modifier leur valeur
void coller_surface1(char ** surface_car, char ** surface_coul, unsigned char far *ecran,int x1, int y1, int * n, int * m);
//char ** parce que nous devons liberer les surfaces apres les avoir colles a l'ecran donc modifier leur valeur
/***************************************************************************/
void changemode( int mode);







void changerCoulCar(unsigned char far * ecran, int x, int y, int col)
{
	*(ecran+160*(y-1)+ 2*x - 1) = col;
}

void changerCar(unsigned char far * ecran, int x, int y, char car)
{
	*(ecran+160*(y-1)+ 2*x - 2) = car;
}

unsigned int ind_carxy(int x, int y)
{
	return (160*(y-1)+ 2*x - 2);
}

unsigned int ind_coulxy(int x, int y)
{
	return (160*(y-1)+ 2*x - 1);
}

void enreg_ecran(char *tempon)
{
   movedata(0xB800, 160, _DS, (unsigned)tempon, 80*25*2);
}

void retablir_ecran(char *tempon)
{
   movedata(_DS, (unsigned)tempon,0xB800, 0000, 80*25*2);
}
void copier_surface1(char ** surface_car, char ** surface_coul, unsigned char far *ecran, int x1, int y1, int x2, int y2,int * n, int * m)
{
	int i,j;
	*n = y2 - y1 + 1;
	*m = x2 - x1 + 1;
	//Allocation dynamique
	*surface_car = (char *)malloc((*m)*(*n)*sizeof(char));
	*surface_coul = (char *)malloc((*m)*(*n)*sizeof(char));
	//Remplissage
	for(i = y1; i <= y2; i++)
		for(j = x1; j <= x2; j++)
		{
		      *((*surface_car)+(i-y1)*(*n)+(j-x1)) = ecran[ind_carxy(j,i)];
		      *((*surface_coul)+(i-y1)*(*n)+(j-x1)) = ecran[ind_coulxy(j,i)];
		 }
}


void coller_surface1(char ** surface_car, char ** surface_coul, unsigned char far *ecran,int x1, int y1, int *n, int *m)
{
	int i,j,x2,y2;
	y2 = *n + y1 - 1;
	x2 = *m + x1 - 1;
	for(i = y1; i <= y2; i++)
		for(j = x1; j <= x2; j++)
		{
		      ecran[ind_carxy(j,i)] = *((*surface_car)+(i-y1)*(*n)+(j-x1));
		      ecran[ind_coulxy(j,i)] = *((*surface_coul)+(i-y1)*(*n)+(j-x1));
		 }
	//Liberation des surfaces
	free(*surface_car);
	free(*surface_coul);
	//Reinitialisation de la taille des surfaces
	*n = 0;
	*m = 0;
}



void changemode(int mode)
{
  asm{
   mov ax,mode
   int 10h
  }
}

