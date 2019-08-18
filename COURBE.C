#include <graphics.h>
#include <math.h>
#include "fonction.h"


#define u 30

void initialise();
void tracer();
void repere();

int main()
{
	tracer();
	getch();
	return(0);
}

void repere()
{
setfillstyle(1,BLUE);
bar(0,0,getmaxx(),getmaxy());
setfillstyle(1,15);
line(0,(getmaxy())/2,(getmaxx()),(getmaxy())/2);
line((getmaxx())/2,0,(getmaxx()/2),(getmaxy()));
rectangle(0,0,getmaxx(),getmaxy());
}

void tracer()
{
   float i,z,z1,temp;
   int debx,finx;

   initialise();
   repere();
   setbkcolor(BLACK);
   setcolor(WHITE);
   setlinestyle(SOLID_LINE,1,2);
   setcolor(RED);
   debx=(int)((-10)*u)+getmaxx()/2;
   finx=(int)((10)*u)+getmaxx()/2;
  for(i=debx;(i+1)<=finx;i++)
    {
    temp=(i-(getmaxx()/2))/u;
    z=f(temp)*u;
    z=(getmaxy()/2)-z;
    temp=(i+1-(getmaxx()/2))/u;
    z1=f(temp)*u;
    z1=(getmaxy()/2)-z1;
    if (((z>=0) && (z<=getmaxy())) && (z>=0) && (z<=getmaxy())) { delay(10); line(i,z,i+1,z1);}
    }
   getch();
   closegraph();
}


void initialise()
{
   int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode,"BGI");
   errorcode = graphresult();

   if (errorcode != grOk)
   {
      printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
      getch();
      exit(1);
   }
}

