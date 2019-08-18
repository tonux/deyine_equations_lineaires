

float * resolution(float *L,float * U ,float * b, int dim,int*iter);
float*  LU(float *a,float *b,int dim,char choix,int* iter);


void    res(float *l,float *u,float *b,int dim,int* iter){
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
		       if(l[i*dim+j]>0)	printf("%.2f  ",l[i*dim+j]);
		       else             printf("%.2f ",l[i*dim+j]);}
		       else{
		       if(l[i*dim+j]>0)	printf("%.2f",l[i*dim+j]);
		       else             printf("%.2f",l[i*dim+j]);}
		printf("\n");
		}

	for( i=0 ; i<dim ; i++)
		{
		gotoxy(39,i+9);
		for( j=0 ; j<dim ; j++)
		       if(j!=dim-1){
		       if(u[i*dim+j]>0)	printf("%.2f  ",u[i*dim+j]);
		       else             printf("%.2f ",u[i*dim+j]);}
		       else{
		       if(u[i*dim+j]>0)	printf("%.2f",u[i*dim+j]);
		       else             printf("%.2f",u[i*dim+j]);}
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
		X=resolution(l,u,b,dim,&(*iter));
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
	else{masquer();coller_surface(&surface,ecran,col,line,&n,&m);}
afficher();
}



float * resolution(float *L,float * U ,float * b, int dim,int *iter)
{       int i,j;
	float s;
	float *y=(float*)malloc(dim*sizeof(float));
	float *x=(float*)malloc(dim*sizeof(float));
	for(i=0;i<dim;i++)
		{
		s=0;
		for(j=0;j<i;j++)
		{
			s=s+L[i*dim+j]*y[j]; //Voir la resolution de LU
			(*iter)++;
		}
		y[i]=(b[i]-s)/L[i*dim+i];
		}

	for(i=dim-1;i>=0;i--)
		{
		s=0;
		for(j=i+1;j<dim;j++)
		{
			s=s+U[i*dim+j]*x[j];
			(*iter)++;
		}
		x[i]=(y[i]-s)/U[i*dim+i];
		}

	return x;
	}


float* LU(float *a,float *b,int n,char choix,int* iter)
{
       int m,i,j,k,flag=1;
       float   s;
       float  *l=(float*)malloc(n*n*sizeof(float));
       float  *u=(float*)malloc(n*n*sizeof(float));
       float*  tempa=affect_matrice(a,n);
       float*  tempb=affect_Vect(b,n);
       *iter=0;
       for (i=0;i<n;i++)
		for (j=0;j<n;j++)
		{
			l[i*n+j]=0;
			u[i*n+j]=0;
		}

      for (i=0;i<n;i++)
		l[i*n+i]=1;

	for (m=0;m<n;m++)
		{
		for (j=m;j<n;j++)
			{
			s=0;
			for (k=0;k<m;k++)
			{
				s=s+l[m*n+k]*u[k*n+j];
				(*iter)++;
			}
			u[m*n+j]=tempa[m*n+j]-s;
			}
		for (i=m+1;i<n;i++)
			{
			s=0;
			for (k=0;k<m;k++)
			{
				s=s+l[i*n+k]*u[k*n+m];
				(*iter)++;
			}
			if (u[m*n+m]!=0)
			l[i*n+m]=(tempa[i*n+m]-s)/u[m*n+m];
			else
			{
			  flag=0;
			  break;
			  }
			}
		  }



      if(flag!=0)
      { if(choix=='o')
		res(l,u,tempb,n,&(*iter));
	return u;}
      else{
	info("ERREUR LU","Non Factorisable",OR);
	return NULL;
	}
}



