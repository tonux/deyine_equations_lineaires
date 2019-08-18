void    cholesky(float *B,float* Bt,float *b,int dim,int* iter);
float   determinant(float *a,int dim);


float determinant(float *a,int dim)
{
float det,*a1,*b=(float*)malloc(dim*sizeof(float));
int i,j;
for (i=0;i<dim;i++)
   b[i]=1;
a1=affect_matrice(a,dim);
a1=GAUSS(a1,b,dim,'n',&j);
det=1;

for (i=0;i<dim;i++)
	   det*=a1[i*dim+i];
free(a1);
free(b);
return det;
}




float * B(float *U,int dim,int*iter)
{float *m=(float*)malloc(dim*dim*sizeof(float));
      int i,j;
      for (i=0;i<dim;i++)
	       for (j=0;j<dim;j++)
	       {
		    if (j<=i)
			m[i*dim+j]=U[j*dim+i]/sqrt(U[j*dim+j]);
		    else
			m[i*dim+j]=0;
		    (*iter)++;
	       }
      return m;
}

float * Bt(float *B,int dim)
{int i,j;
float *m=(float*)malloc(dim*dim*sizeof(float));
	 for (i=0;i<dim;i++)
	       for (j=0;j<dim;j++)
		    m[i*dim+j]=B[j*dim+i];
      return m;
}
int symetrique(float *a,int dim)
{int i,j;
for (i=0;i<dim;i++)
	 for (j=0;j<dim;j++)
		   if (a[i*dim+j]!=a[j*dim+i])
			   return 0;
return 1;
}

float *M(int k,float *a,int dim)
{float *t;
int i,j;
if (k<=dim)
{
t=(float*)malloc(k*k*sizeof(float));
if (t!=NULL)
   {
    for (i=0;i<k;i++)
	   for(j=0;j<k;j++)
		    t[i*k+j]=a[i*dim+j];
    }
return t;
}
else
return NULL;
}

int definie_positive(float *a,int dim)
{int k;
 float *t;
 for (k=1;k<=dim;k++)
    {t=M(k,a,dim);
	 if (determinant(t,k)<=0)
		return 0;
     free(t);
     }
return 1;
}

int sdp (float *a,int dim)
{return ((symetrique(a,dim))&&(definie_positive(a,dim)));
}





void   chol(float *A,float*b,int dim,int* iter){
	float *U,*B1,*B2,*x;
	int i;
	float*  tempA=affect_matrice(A,dim);
	float*  tempb=affect_Vect(b,dim);
	*iter=0;
	if (sdp(tempA,dim))
		{
		U=LU(tempA,tempb,dim,'n',&(*iter));
		B1=B(U,dim,&(*iter));
		B2=Bt(B1,dim);
		cholesky(B1,B2,tempb,dim,&(*iter));
		 }
	else
	info("ERREUR Cholesky","Non SDP",OR);
	}

void    cholesky(float *B,float* Bt,float *b,int dim,int* iter){
	unsigned char far *ecran = (unsigned char far*)MK_FP(0xB800,0000); //La premiere  page de la memoire video soit l'ecran
	int i,j,k,x,y,col=15,line=4;  //pour centrer la boite de dialogue
	char * Zone[15];
	int m=0,n=0;
	char * surface;
	float * X=(float*)(dim*sizeof(float));

	Zone[0]= "ีออออออออออออออออออออออออออออออออออออออออออ[Fermer]อธ";
	Zone[1]= "ณ                                                   ณ";
	Zone[2]= "ณ                                                   ณ";
	Zone[3]= "ณ                                                   ณ";
	Zone[4]= "ณ                                                   ณ";
	Zone[5]= "ณ                                                   ณ";
	Zone[6]= "ณ                                                   ณ";
	Zone[7]= "ณ                                                   ณ";
	Zone[8]= "ณ                                                   ณ";
	Zone[9]= "ณ                                                   ณ";
	Zone[10]="ณ                                                   ณ";
	Zone[11]="ณ                                                   ณ";
	Zone[12]="ณ                                                   ณ";
	Zone[13]="ณ                                                   ณ";
	Zone[14]="ิอออออออออออออออออออออออออออออออออออออออออออออออออออพ";
	copier_surface(&surface,ecran,col,line,col+strlen(Zone[0])+1,line + 15,&n,&m);
		for(i=0;i<15;i++)
		{
		k=0;
		for(j=col;j<=(col-1+strlen(Zone[0]));j++)
			{
			gotoxy(j,i+line);
			textattr(31);
			cprintf("%c",Zone[i][k++]);
			}
		}
	matrice_barre(dim,17,8,"OUVRANTE",'B');
	matrice_barre(dim,36,8,"FERMANTE",'B');

	matrice_barre(dim,38,8,"OUVRANTE",'B');
	matrice_barre(dim,55,8,"FERMANTE",'B');

	Button("Continuer",55,16,OR,NR,NR);

	for( i=0 ; i<dim ; i++)
		{
		gotoxy(18,i+9);
		for( j=0 ; j<dim ; j++)
		       if(j!=dim-1){
		       if(B[i*dim+j]>0)	printf("%.1f  ",B[i*dim+j]);
		       else             printf("%.1f ",B[i*dim+j]);}
		       else{
		       if(B[i*dim+j]>0)	printf("%.1f",B[i*dim+j]);
		       else             printf("%.1f  ",B[i*dim+j]);}
		printf("\n");
		}

	for( i=0 ; i<dim ; i++)
		{
		gotoxy(39,i+9);
		for( j=0 ; j<dim ; j++)
		       if(j!=dim-1){
		       if(Bt[i*dim+j]>0)printf("%.1f  ",Bt[i*dim+j]);
		       else             printf("%.1f ",Bt[i*dim+j]);}
		       else{
		       if(Bt[i*dim+j]>0)printf("%.1f",Bt[i*dim+j]);
		       else             printf("%.1f",Bt[i*dim+j]);}
		printf("\n");
		}
	afficher();
	do{

	   }
	while(!(clicline(55,65,16)||clicline(col+44,col+50,line)));
	delay(100);
	      //pour patienter
	if(clicline(55,65,16))
	{
		X=resolution(B,Bt,b,dim,&(*iter));
		masquer();
		coller_surface(&surface,ecran,col,line,&n,&m);

		if(X[0]>0) gotoxy(col+27-11,line+7-2);
		else  gotoxy(col+26-11,line+7-2);
		textattr(GREEN);

		for( i=0 ; i<dim ; i++)
			{
			  cprintf("%.2f",X[i]);
			  if(X[i+1]<0)  gotoxy(wherex()-5,wherey()+1);
			  else gotoxy(wherex()-4,wherey()+1);
			  }
	}
	else{masquer();
	     coller_surface(&surface,ecran,col,line,&n,&m);
	     }
afficher();
}



