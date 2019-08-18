


float *e(int j,int dim)
{float *x=(float*)malloc(dim*sizeof(dim));
int i;
for (i=0;i<dim;i++)
     x[i]=((i==j)?1:0);
return x;
}


void  inverse(float *a,int dim)
{	float *a1,*inv=(float*)malloc(dim*dim*sizeof(float));
	float *x,*b;
	int i,j,k;
	a1=affect_matrice(a,dim);
	if(determinant(a1,dim)!=0)
	{
		for (j=0;j<dim;j++)
		{       b=e(j,dim);
			x=GAUSS(a1,b,dim,'e',&k);
			for (i=0;i<dim;i++)
				inv[i*dim+j]=x[i];
			free(b);
			free(x);
		}
		inver(inv,dim);
	}
	else {
		info("INFORMATION","NON INVERSIBLE",OR);

		}
}
