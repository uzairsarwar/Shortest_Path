#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>


/* here are our X variables */
Display *displays_ptr;
char *displayName = NULL;
int screen_num;
Window win;
GC gc, gc_blue;
XGCValues gc_blue_values, gc_values;
int clicks = 0;
int xx;
int yx;
XColor color1, color2;
Colormap color_map;
unsigned int width = 300, height = 300;
XEvent report;
int o = 0;
int a, b, c, d, i=1;
int z;
int another;
int finale;
int st;
int aa;
int bb;
int cc;
int dd;
int ee;
int ff;
int gg;
int hh;
int dist_1;
int dist_2;

struct graph
{
	int m;
	int n;
	int pomn;

};

struct visit{
	int vis;
};
struct cost{
	int dist;
};

int thereisEdge(struct graph *v,int w,int another,struct visit *m){


	   if(m[another].vis==0){
		   aa=v[w].m;
		   bb=v[w].n;
		   cc=v[another].m;
		   dd=v[another].n;

		for(finale=1;finale<25;finale+=2){
			ee= v[finale].m;
			ff=v[finale].n;
			gg=v[finale+1].m;
			hh=v[finale+1].n;

			int abcdef= aa*dd+cc*ff+ee*bb-bb*cc-dd*ee-ff*aa;
			int abcdgh= aa*dd+cc*hh+gg*bb-bb*cc-dd*gg-hh*aa;
			int abefgh= ee*hh+gg*bb+aa*ff-ff*gg-hh*aa-bb*ee;
			int cdefgh= ee*hh+gg*dd+cc*ff-ff*gg-hh*cc-dd*ee;

			if(((abcdef>0)&&(abcdgh<0))&&((abefgh>0)&&(cdefgh<0))){
				return 0;
			}
		}
	}
	else{
		return 0;
	}
	return 1;
}
void rec(struct graph *v,int index){

}



int main(int argc, char *argv[]){
	 	struct graph *v = (struct graph *)malloc(sizeof(struct graph)*1000);
		struct visit *mark = (struct visit *)malloc(sizeof(struct visit)*1000);
		struct cost *cst=(struct cost *)malloc(sizeof(struct cost)*1000);

	FILE *f;
	f = fopen(argv[1], "r");
	if(f!=NULL){

		 v[0].n = 0; v[0].m = 0; v[0].pomn = 0; mark[0].vis = 0;
		// reading the file and inserting the elements.
		while(!feof(f)){
			fscanf(f, "S (%d,%d) (%d,%d)\n", &a, &b, &c, &d);
			mark[i].vis=0;
			mark[i+1].vis=0;
			v[i].pomn=i;
			v[i+1].pomn=i+1;
			v[i].m = a;
			v[i].n = b;
			v[i+1].m = c;
			v[i+1].n = d;
			i = i+2;
		}
		fclose(f);
	}
	else{
		printf("Name you entered is %s",argv[1]);
		printf("The file does not exist");
		exit(0);
	}

	displays_ptr=XOpenDisplay(displayName);
   	screen_num=DefaultScreen(displays_ptr);
	color_map  = XDefaultColormap( displays_ptr, screen_num );
   	win=XCreateSimpleWindow(displays_ptr,RootWindow(displays_ptr, screen_num),0,0,
		width, height, 5,BlackPixel(displays_ptr,screen_num), WhitePixel(displays_ptr, screen_num));
	XMapWindow(displays_ptr, win);
	XSetStandardProperties(displays_ptr,win,"Window | 1.0","1.0",None,NULL,0,NULL);
	XSelectInput(displays_ptr, win, ExposureMask|ButtonPressMask|StructureNotifyMask);
        gc=XCreateGC(displays_ptr, win, 0,&gc_values);
	gc_blue = XCreateGC(displays_ptr, win, 0, &gc_blue_values);
	XAllocNamedColor( displays_ptr, color_map, "blue", &color1, &color2 );
	XSetLineAttributes(displays_ptr, gc_blue, 1, LineSolid, CapRound, JoinRound);
	XSetBackground(displays_ptr,gc,WhitePixel(displays_ptr, screen_num));
	XSetForeground(displays_ptr,gc,BlackPixel(displays_ptr,screen_num));
	XSetForeground(displays_ptr,gc_blue, color1.pixel);
	XClearWindow(displays_ptr, win);
	XMapRaised(displays_ptr, win);

	while(1)
	{

		XNextEvent(displays_ptr, &report);

		switch(report.type)
		{
			case Expose:
				for(o=1;o<24;o+=2){
					XDrawLine(displays_ptr,win,gc,v[o].m,v[o].n,v[o+1].m,v[o+1].n);
				}
				break;
			case ConfigureNotify:
				width = report.xconfigure.width;
				height = report.xconfigure.height;
				break;
			case ButtonPress:
				if(report.xbutton.button == Button1)
				{
					int x=report.xbutton.x,
			    		y=report.xbutton.y;
//v[0].n=x;
					if(clicks%2 == 0)
					{
						xx = x; yx = y; clicks++;
						for(o=1;o<24;o+=2){
						XDrawLine(displays_ptr,win,gc,v[o].m,v[o].n,v[o+1].m,v[o+1].n);
										}
						for(z=0;z<26;z++){
							v[z].pomn=z;
							cst[z].dist=1000;
							mark[z].vis=0;
						}
					}
					else
					{
						XDrawLine(displays_ptr,win,gc_blue,xx,yx,x,y);
						v[0].m=xx;
						v[0].n=yx;
						v[25].m=x;
						v[25].n=y;

						clicks = 0;
						int walker=0;
						cst[walker].dist=0;
						for(st=0;st<26;st++){
							mark[walker].vis=1;
							for(another=1;another<25;another+=2){
								int ex=v[walker].m-v[another].m;
								int ey=v[walker].n-v[another].n;
								int fx=v[walker].m-v[another+1].m;
								int fy=v[walker].n-v[another+1].n;
								if(ex!=0&& ey!=0 && fx!=0 && fy!=0){
									if(thereisEdge(v,walker,another,mark)==1){
										dist_1 = sqrt(pow(v[another].n-v[walker].n,2)+(pow(v[another].m-v[walker].m,2)));
									if(cst[walker].dist+dist_1 < cst[another].dist){
									cst[another].dist = cst[walker].dist+dist_1;
									v[another].pomn=walker;
									}
									}
									if(thereisEdge(v,walker,another+1, mark)==1){
										dist_2=sqrt(pow(v[another+1].n-v[walker].n,2)+(pow(v[another+1].m-v[walker].m,2)));
										if(cst[walker].dist+dist_2<cst[another+1].dist){
										cst[another+1].dist=cst[walker].dist+dist_1;
										v[another+1].pomn=walker;
										}


									}

								}
							}
						}
					}
					rec(v,25);




				}


				else if(report.xbutton.button == Button3)
				{
					XFreeGC(displays_ptr, gc);
					XDestroyWindow(displays_ptr,win);
					XCloseDisplay(displays_ptr);
					exit(1);
				}else
				{
					//do nothing
				}
				break;
			 default:
			  	/* this is a catch-all for other events; it does not do anything.
             			One could look at the report type to see what the report was */
          			break;
		}
	}
	return 0;
}


