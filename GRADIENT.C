#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<conio.h>
#define eps 0.000001

float * image(float * A, float * X, int n)
{
	float * Y =(float *)malloc(n*sizeof(float));
	int i,j;
	for (i=0;i<n;i++)
		  {Y[i]=0;
			 for (j=0;j<n;j++)
			      Y[i]+=A[i*n+j]*X[j];
		  }
		  return Y;
}


float prod_scal(float * X, float * Y, int n)
{
	float res=0;
	int i;
	for(i=0; i<n; i++) res += X[i]*Y[i];
	return res;
}

float * prod_vect_scal(float c, float * X, int n)
{
	float * Y =(float *)malloc(n*sizeof(float));
	int i;
	for(i=0; i<n ; i++) Y[i] = c * X[i];
	return Y;
}

float * add_vect(float * X, float * Y, int n)
{
	int i;
	float * Z =(float *)malloc(n*sizeof(float));
	for(i = 0; i<n ; i++) Z[i] = X[i] + Y[i];
	return Z;
}

float * init_zero(int n)
{
	int i;
	float * Y =(float *)malloc(n*sizeof(float));
	for(i = 0; i<n ; i++) Y[i] = 0.0;
	return Y;
}

float * affect_vect(float * X, int n)
{
	int i;
	float * Y =(float *)malloc(n*sizeof(float));
	for(i = 0; i<n ; i++) Y[i] = X[i];
	return Y;
}

float * gradient_conjugue(float * A,float *B ,int n,int* iter)
{
	float * r1, *r2, * d1, * d2, t, * x,* x1,* x2,* img,* pvs;
	r1 = affect_vect(B,n);
	d1 = affect_vect(r1,n);
	x = init_zero(n);
	do
	{       (*iter)++;
		img=image(A,d1,n);
		t = prod_scal(r1,d1,n)/prod_scal(img,d1,n);
		pvs=prod_vect_scal(t,d1,n);
		x1=x;
		x = add_vect(x,pvs,n); free(pvs);
		free(x1);
		pvs=prod_vect_scal(-t,img,n);
		r2 = add_vect(r1,pvs,n); free(pvs);
		d2 =affect_vect(d1,n);
		free(d1);
		pvs=prod_vect_scal(prod_scal(r2,r2,n)/prod_scal(r1,r1,n),d2,n);
		d1 = add_vect(r2,pvs,n);
		free(d2); free(r1);
		r1 = affect_vect(r2,n);
		free(r2);free(img);free(pvs);
	}while(!(prod_scal(r1,r1,n)<eps));
	free(d1);
	return x;
}

float * gradient(float *A,float *B,int n,int* iter)
{
	float * r1, *r2, t, * x,* x1,* img,* pvs;
	r1 = affect_vect(B,n);
	x = init_zero(n);
	do
	{       (*iter)++;
		img=image(A,r1,n);
		t = prod_scal(r1,r1,n)/prod_scal(img,r1,n);
		pvs=prod_vect_scal(t,r1,n);
		x1=x;
		x = add_vect(x,pvs,n); free(pvs);
		free(x1);
		pvs=prod_vect_scal(-t,img,n);
		r2=r1;
		r1=add_vect(r1,pvs,n);
		free(r2);free(img);free(pvs);
	}while(!(prod_scal(r1,r1,n)<eps));
	free(r1);
	return x;
}

void    m_gradient(float*A,float*b,int dim,int *iter)
{       int col=4,line=2,i;
	float*  tempA=affect_matrice(A,dim);
	float*  tempb=affect_Vect(b,dim);
	float*  X=NULL;
	*iter=0;
	if (sdp(tempA,dim))
		{
		 X=gradient(tempA,tempb,dim,&(*iter));
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
	else
	info("ERREUR Gradient","Non SDP",OR);

if(X) free(X);
}


void    m_gradient_conj(float*A,float*b,int dim,int* iter)
{       int col=4,line=2,i;
	float*  tempA=affect_matrice(A,dim);
	float*  tempb=affect_Vect(b,dim);
	float*  X=NULL;
	*iter=0;
	if (sdp(tempA,dim))
		{
		 X=gradient_conjugue(tempA,tempb,dim,&(*iter));
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
	else
	info("ERREUR Gradient","Non SDP",OR);

if(X) free(X);
}
