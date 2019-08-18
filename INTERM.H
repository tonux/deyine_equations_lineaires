float * affect_matrice(float *a,int dim);
float * affect_Vect(float *b,int dim);
float * alloc_vecteur(int n);
float * alloc_matrice(int n);


float * affect_Vect(float *a,int dim){
int i;
float *b=(float*)malloc(dim*sizeof(float));
for(i=0;i<dim;i++)
	b[i]=a[i];
return b;
}




float * affect_matrice(float *a,int dim){
int i,j;
float *b=(float*)malloc(dim*dim*sizeof(float));
for(i=0;i<dim;i++)
	for(j=0;j<dim;j++)
		b[i*dim+j]=a[i*dim+j];
return b;
}




float * alloc_vecteur(int n)
{  float * a=(float*)malloc(n*sizeof(float));
      if (a==NULL)
	   {printf("Allocation memoire impossible\n");
	   exit(0);
	   }
     return a;
}

float * alloc_matrice(int n)
{  float * a=(float*)malloc(n*n*sizeof(float));
      if (a==NULL)
	   {printf("Allocation memoire impossible\n");
	   exit(0);
	   }
     return a;
}


