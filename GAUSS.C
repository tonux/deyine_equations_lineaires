


int     permutmat(float *mat,int dim,int etape,int* iter);
float*  GAUSS(float *M,float*b,int dim,char choix,int* iter);
void    PermutVect(float *b,int ligne1,int ligne2);
void    elimmat(float *A,float *b,int dim,int k,char koi,int* iter);
float*  remonte(float *mat,float *vect,int dim,int* iter);






void    PermutVect(float *b,int ligne1,int ligne2){
float   temp;
	temp=b[ligne1];
	b[ligne1]=b[ligne2];
	b[ligne2]=temp;
}



int permutmat(float *mat,int dim,int etape,int* iter)
{
 float temp;

 int line,i;
 int flag=0;

 if (mat[etape*dim+etape]==0)
   {
    for(i=etape;i<dim;i++)
     {(*iter)++;
      if (mat[i*dim+etape]!=0){
	line=i;
	flag=i;
	break;}
      else flag=-1;
     }

    if(flag!=-1)
      {
	for(i=0;i<dim;i++)
	 {
	   temp=mat[line*dim+i];
	   mat[line*dim+i]=mat[etape*dim+i];
	   mat[etape*dim+i]=temp;
	 }

     }
   }
   else flag=0;

 return flag;
}


float*   GAUSS(float * A,float * b,int dim,char choix,int *iter)
{int col=4,line=2;
 float *X=NULL;
 int k=0;
 int i;
 float*  tempA=affect_matrice(A,dim);
 float*  tempb=affect_Vect(b,dim);
 *iter=0;
 for (i=0;i<dim;i++)
	{
	k=permutmat(tempA,dim,i,&(*iter));
	if((k!=0)&&(k!=-1)) PermutVect(tempb,i,k);
	if( k==-1) {    if(choix=='o')
			info("ERREUR CRITIQUE","GAUSS INUTILISABLE",OR);
			break;
			}

	elimmat(tempA,tempb,dim,i,'g',&(*iter));
	(*iter)++;
	}
	if(choix=='o')
	if(k!=-1)
	{
		if (tempA[(dim-1)*dim+(dim-1)]!=0)
		{
			X=remonte(tempA,tempb,dim,&(*iter));
			if(X[0]>0) gotoxy(col+27,line+7);
			else  gotoxy(col+26,line+7);
			textcolor(GREEN);      //Affichage du vecteur X
			for( i=0 ; i<dim ; i++)
			{
			  cprintf("%.2f",X[i]);
			  if(X[i+1]<0)  gotoxy(wherex()-5,wherey()+1);
			  else gotoxy(wherex()-4,wherey()+1);
			  }

		 }
		 else {
		       info("ERREUR CRITIQUE","GAUSS INUTILISABLE",OR);
		       info("ERREUR CRITIQUE","Infinit‚ de solution",OR);
		}
	 }
afficher();
if(X) free(X);
if(choix=='n')
	return(tempA);
else{   X=remonte(tempA,tempb,dim,&(*iter));
	return(X);
	}
}


void    elimmat(float *A,float *b,int dim,int k,char koi,int* iter)
{
float piv;
int i,j;

for(i=k+1;i<dim;i++)
{
	piv=A[i*dim+k]/A[k*dim+k];
	if (koi=='g')
		b[i]=b[i]-(piv*b[k]);
	for (j=0;j<dim;j++)
	{       (*iter)++;
		A[i*dim+j]=A[i*dim+j]-piv*A[k*dim+j];
	}

}
}



float* remonte(float *mat,float *vect,int dim,int* iter)
{
int i=dim-1,j,k;
float *X=(float*)malloc(dim*sizeof(float));
X[i]=vect[i]/mat[i*dim+i];

for(j=i-1;j>=0;j--)
 {     X[j]=vect[j];
   for (k=dim-1;k>j;k--)
       {(*iter)++;
       X[j]-= mat[j*dim+k]*X[k];
       }
   X[j]=X[j]/mat[j*dim+k];
 }
return(X);
}
