

int clicline(int x1,int x2,int l);

int initmouse()
{
	union REGS reg;
	reg.x.ax=0;
	int86(0x33,&reg,&reg);
	if(reg.x.bx) return 1;
	return 0;
}

void afficher()
{
	union REGS reg;
	reg.x.ax=1;
	int86(0x33,&reg,&reg);
}

void masquer()
{
	union REGS reg;
	reg.x.ax=2;
	int86(0x33,&reg,&reg);
}

void position(int * x,int * y)
{
	union REGS reg;
	reg.x.ax=3;
	int86(0x33,&reg,&reg);
	*x=reg.x.cx;
	*y=reg.x.dx;
}

int bouton()
{
	union REGS reg;
	reg.x.ax=3;
	int86(0x33,&reg,&reg);
	return reg.x.bx;
}


int clicline(int x1,int x2,int l) //avec x1=x2 on a clicxy
{
	int x,y;
	position(&x,&y);
	return (((y/8)==(l-1)) && ((x/8)<=(x2-1)) && ((x/8)>=(x1-1))  && (bouton()==1));
}

void GetSourisXY(int *xs,int *ys,int *bg,int *bd)
{
union REGS rin,rout;
rin.x.ax=3;
int86(0x33,&rin,&rout);
*xs=rout.x.cx;
*ys=rout.x.dx;

*bg=(rout.x.bx & 1)==1;
*bd=(rout.x.bx & 2)==2;
return;
}


int appartenance (int xs,int ys,int x1,int y1,int x2,int y2)
   {
    return ( (x1<=xs)&&(xs<=x2)&&(y1<=ys)&&(ys<=y2) ) ? 1 : 0;
   }

int domaine(int xs,int ys,int x1,int y1,int x2,int y2)
   {
    return ( (x1<=xs/8)&&(xs/8<=x2)&&(y1<=ys/8)&&(ys/8<=y2) ) ? 1 : 0;
   }
