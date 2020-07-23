#include<iostream.h>
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>

unsigned int x[16],y[16],direction=4,cnt=0,ch=1;
/*
    direction values:-

	2 - Up
	4 - Left
	6 - Right
	8 - Down

*/

// Bresenham's Line Algorithm
void BLine(int x1,int y1,int x2,int y2,int c)
{
	int x,y,p,dx,dy,xend,yend,flag=0;
	dx=abs(x2-x1);
	dy=abs(y2-y1);
	if(dx>dy)
	{
		if(x2>x1)
		{
			x=x1;
			y=y1;
			xend=x2;
			if(y1>y2)
				flag=1;
		}
		else
		{
			x=x2;
			y=y2;
			xend=x1;
			if(y2>y1)
				flag=1;
		}
		putpixel(x,y,c);
		p=2*dy-dx;
		while(x<=xend)
		{
			x++;
			if(p<0)
				p=p+2*dy;
			else
			{
				if(flag==0)
					y++;
				else
					y--;
				p=p+2*dy-2*dx;
			}
			putpixel(x,y,c);
		}
	}
	else
	{
		if(y2>y1)
		{
			x=x1;
			y=y1;
			yend=y2;
			if(x1>x2)
				flag=1;
		}
		else
		{
			x=x2;
			y=y2;
			yend=y1;
			if(x2>x1)
				flag=1;
		}
		putpixel(x,y,c);
		p=2*dx-dy;
		while(y<=yend)
		{
			y++;
			if(p<0)
				p=p+2*dx;
			else
			{
				if(flag==0)
					x++;
				else
					x--;
				p=p+2*dx-2*dy;
			}
			putpixel(x,y,c);
		}
	}
}

// draw rectangle
void rect(int tx,int ty,int bx,int by,int c){
	BLine(bx,by,bx,ty,c);
	BLine(bx,by,tx,by,c);
	BLine(bx,ty,tx,ty,c);
	BLine(tx,by,tx,ty,c);
}

// draw tesseract
void drawTesseract(int c){
	int i,t=0,r;
	while(t<15){
		for(i=0;i<3;i++,t++)
			BLine(x[t],y[t],x[t+1],y[t+1],c);
		BLine(x[t],y[t],x[t-3],y[t-3],c);
		t++;
	}

	for(r=0;r<4;r++){
		for(i=0,t=r;i<3;i++,t+=4)
			BLine(x[t],y[t],x[t+4],y[t+4],c);
		BLine(x[r],y[r],x[t],y[t],c);
	}
}

// draw tesseract from a single point
void intialstage(){
	int t,i,bx=getmaxx(),by=getmaxy(),c=15;

	x[0]=(int)(bx/2);  // point
	y[0]=(int)(by/2);
	delay(150);
	cleardevice();
	putpixel(x[0],y[0],c);
	delay(150);
	putpixel(x[0],y[0]-1,c);
	delay(150);
	putpixel(x[0],y[0]+1,c);
	delay(150);
	putpixel(x[0]-1,y[0],c);
	delay(150);
	putpixel(x[0]+1,y[0],c);
	delay(150);
	putpixel(x[0]-1,y[0]-1,c);
	delay(150);
	putpixel(x[0]+1,y[0]-1,c);
	delay(150);
	putpixel(x[0]-1,y[0]+1,c);
	delay(150);
	putpixel(x[0]+1,y[0]+1,c);
	delay(150);

	x[2]=x[0];                // line
	y[2]=y[0];
	t=16;
	delay(1000);
	while(t){
		x[0]-=5;
		x[2]+=5;
		delay(150);
		clearviewport();
		BLine(x[0],y[0],x[2],y[2],c);
		t--;
	}

	t=16;                     // square
	delay(1000);
	c=4;
	while(t){
		y[0]-=5;
		y[2]+=5;
		delay(150);
		clearviewport();
		rect(x[0],y[0],x[2],y[2],c);
		t--;
	}
	x[1]=x[0];
	y[1]=y[2];
	x[3]=x[2];
	y[3]=y[0];

	for(i=4;i<8;i++){         // 3D cube
		x[i]=x[i-4];
		y[i]=y[i-4];
	}
	t=4;
	delay(1000);
	c=3;
	while(t){
		x[0]-=5;
		y[0]-=5;
		x[1]-=5;
		y[1]+=5;
		x[2]+=5;
		y[2]+=5;
		x[3]+=5;
		y[3]-=5;
		x[4]+=5;
		y[4]+=5;
		x[5]+=5;
		y[5]-=5;
		x[6]-=5;
		y[6]-=5;
		x[7]-=5;
		y[7]+=5;
		delay(200);
		clearviewport();
		rect(x[0],y[0],x[2],y[2],c);
		BLine(x[0],y[0],x[4],y[4],c);
		BLine(x[1],y[1],x[5],y[5],c);
		BLine(x[2],y[2],x[6],y[6],c);
		BLine(x[3],y[3],x[7],y[7],c);
		rect(x[4],y[4],x[6],y[6],c);
		t--;
	}

	t=16;                     // rotation cube
	delay(1000);
	c=1;
	while(t){
		for(i=0;i<4;i++){
			x[i]-=2;
			y[i]+=2;
		}
		for(;i<8;i++){
			x[i]+=2;
			y[i]-=2;
		}
		delay(150);
		clearviewport();
		rect(x[0],y[0],x[2],y[2],c);
		BLine(x[0],y[0],x[4],y[4],c);
		BLine(x[1],y[1],x[5],y[5],c);
		BLine(x[2],y[2],x[6],y[6],c);
		BLine(x[3],y[3],x[7],y[7],c);
		rect(x[4],y[4],x[6],y[6],c);
		t--;
	}

	t=8;                      // resize cube
	delay(1000);
	c=2;
	while(t){
		x[4]-=5;
		y[4]-=5;
		x[5]-=5;
		y[5]+=5;
		x[6]+=5;
		y[6]+=5;
		x[7]+=5;
		y[7]-=5;
		delay(100);
		clearviewport();
		rect(x[0],y[0],x[2],y[2],c);
		BLine(x[0],y[0],x[4],y[4],c);
		BLine(x[1],y[1],x[5],y[5],c);
		BLine(x[2],y[2],x[6],y[6],c);
		BLine(x[3],y[3],x[7],y[7],c);
		rect(x[4],y[4],x[6],y[6],c);
		t--;
	}

	for(i=8;i<12;i++){        // tesseract
		x[i]=x[i-4];
		y[i]=y[i-4];
	}
	for(i=12;i<16;i++){
		x[i]=x[i-12];
		y[i]=y[i-12];
	}
	t=12;
	delay(1000);
	c=6;
	while(t){
		x[8]+=5;
		y[8]+=5;
		x[9]+=5;
		y[9]-=5;
		x[10]-=5;
		y[10]-=5;
		x[11]-=5;
		y[11]+=5;
		x[12]+=5;
		y[12]+=5;
		x[13]+=5;
		y[13]-=5;
		x[14]-=5;
		y[14]-=5;
		x[15]-=5;
		y[15]+=5;
		delay(150);
		clearviewport();
		drawTesseract(c);
		t--;
	}

	t=4;                      // resize inner cube
	delay(1000);
	c=5;
	while(t){
		x[8]-=5;
		y[8]+=5;
		x[9]-=5;
		y[9]+=5;
		x[10]-=5;
		y[10]+=5;
		x[11]-=5;
		y[11]+=5;
		x[12]+=5;
		y[12]-=5;
		x[13]+=5;
		y[13]-=5;
		x[14]+=5;
		y[14]-=5;
		x[15]+=5;
		y[15]-=5;
		delay(200);
		clearviewport();
		drawTesseract(c);
		t--;
	}

	delay(1000);
}

// animation of tesseract
void tesseract(){

	int i,c;

	if(cnt>=4){                                    // for pattern switch
		cnt=0;
		ch=(ch+1)%4;
	}

	switch(ch){                                     // for pattern
		case 0: if(x[8]-10<=x[0]&&direction==4){
				direction=6;
				cnt+=3;
			}
			else if(x[10]+10>=x[2]&&direction==6){
				direction=8;
				cnt++;
			}
			else if(y[10]+10>=y[2]&&direction==8){
				direction=2;
				cnt+=3;
			}
			else if(y[8]-10<=y[0]&&direction==2){
				direction=4;
				cnt++;
			}

			c=3;
			break;

		case 1: if(x[8]-10<=x[0]&&direction==4){
				direction=2;
				cnt++;
			}
			else if(x[10]+10>=x[2]&&direction==6){
				direction=8;
				cnt++;
			}
			else if(y[10]+10>=y[2]&&direction==8){
				direction=4;
				cnt++;
			}
			else if(y[8]-10<=y[0]&&direction==2){
				direction=6;
				cnt++;
			}

			c=4;
			break;

		case 2: if(x[8]-10<=x[0]&&direction==4){
				direction=6;
				cnt+=2;
			}
			else if(x[10]+10>=x[2]&&direction==6){
				direction=4;
				cnt++;
			}
			else if(y[10]+10>=y[2]&&direction==8){
				direction=2;
				cnt+=2;
			}
			else if(y[8]-10<=y[0]&&direction==2){
				direction=8;
				cnt++;
			}

			c=1;
			break;

		case 3: if(x[8]-10<=x[0]&&direction==4){
				direction=8;
				cnt++;
			}
			else if(x[10]+10>=x[2]&&direction==6){
				direction=2;
				cnt++;
			}
			else if(y[10]+10>=y[2]&&direction==8){
				direction=6;
				cnt++;
			}
			else if(y[8]-10<=y[0]&&direction==2){
				direction=4;
				cnt++;
			}

			c=6;
			break;
	}


	switch(direction){                                 // for translation
		case 2: for(i=4;i<8;i++)
				y[i]-=5;
			for(i=8;i<12;i++)
				y[i]-=4;
			for(i=12;i<16;i++)
				y[i]-=2;
			break;

		case 4: for(i=4;i<8;i++)
				x[i]-=5;
			for(i=8;i<12;i++)
				x[i]-=4;
			for(i=12;i<16;i++)
				x[i]-=2;
			break;

		case 6: for(i=4;i<8;i++)
				x[i]+=5;
			for(i=8;i<12;i++)
				x[i]+=4;
			for(i=12;i<16;i++)
				x[i]+=2;
			break;

		case 8: for(i=4;i<8;i++)
				y[i]+=5;
			for(i=8;i<12;i++)
				y[i]+=4;
			for(i=12;i<16;i++)
				y[i]+=2;
			break;
	}

	delay(150);
	clearviewport();
	drawTesseract(c);

}

// main
int main()
{
	int gdriver = DETECT, gmode, errorcode;
	int y;

	initgraph(&gdriver, &gmode, "c:\\turboc3\\bgi");
	errorcode = graphresult();
	if(errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);
	}

	y=(getmaxy()/2)-150;
	setcolor(1);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(50,y,"NATIONAL INSTITUTE OF SCIENCE & TECHNOLOGY");

	y=(getmaxy()/2)-50;
	setcolor(6);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,4);
	outtextxy(90,y,"COMPUTER GRAPHICS PROJECT");

	setcolor(4);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(180,300,"3D SCREENSAVER (TESSERACT)");

	setcolor(3);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,3);
	outtextxy(200,400,"BY:- ASHUTOSH BHARTI");
	rect(1,1,getmaxx()-1,getmaxy()-1,3);
	delay(5000);

	intialstage();
	while(!kbhit())
		tesseract();
	delay(2000);
	getch();

	clearviewport();
	setcolor(4);
	settextstyle(TRIPLEX_FONT,HORIZ_DIR,5);
	outtextxy(200,y,"THANK YOU");
	delay(4000);

	closegraph();
	getch();

	return 0;
}