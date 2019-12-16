#include <iostream>
#include <cstdlib>

#include "utility.h"

#define BOUND 256


int perlin_random[BOUND*2];

void init_random();
double perlin_noise(const Vector &pos,double freq,int repeat);
double pseudorandom_dot(int seed,const Vector &pos);
int rr_inc(int n);
double fade(double x);
double avg(double max,double min,double frac);


void init_random()
{
	for(int l=0;l<BOUND*2;l++)
	{
		perlin_random[l] = rand()%BOUND;
	}
}


double perlin_noise(const Vector &pos,double freq, int repeat)
{
	double lambda = 1/freq; 
	
	double xf = pos.x/lambda;
	double yf = pos.y/lambda;
	double zf = pos.z/lambda;
	
	int xi = (int)(xf);
	int yi = (int)(yf);
	int zi = (int)(zf);

	xf -= xi;
	yf -= yi;
	zf -= zi;
	
	//xf-=(int)xf;
	//yf-=(int)yf;
	//zf-=(int)zf;
	
	if(repeat){
		xi%=repeat;
		yi%=repeat;
		zi%=repeat;
	}
	xi%=BOUND;
	yi%=BOUND;
	zi%=BOUND;
	
	int h000,h001,h011,h010,h100,h101,h111,h110;
	
	
	/*
	 * 8 perlin hash value for 8 corner, will be used to choose among 8 gradient vector;
	 */
	h000 = perlin_random[perlin_random[perlin_random[    xi ]+    yi ]+    zi ];
	h001 = perlin_random[perlin_random[perlin_random[    xi ]+rr_inc(yi)]+    zi ];
	h011 = perlin_random[perlin_random[perlin_random[    xi ]+    yi ]+rr_inc(zi)];
	h010 = perlin_random[perlin_random[perlin_random[    xi ]+rr_inc(yi)]+rr_inc(zi)];
	h100 = perlin_random[perlin_random[perlin_random[rr_inc(xi)]+    yi ]+    zi ];
	h101 = perlin_random[perlin_random[perlin_random[rr_inc(xi)]+rr_inc(yi)]+    zi ];
	h111 = perlin_random[perlin_random[perlin_random[rr_inc(xi)]+    yi ]+rr_inc(zi)];
	h110 = perlin_random[perlin_random[perlin_random[rr_inc(xi)]+rr_inc(yi)]+rr_inc(zi)];
	
	double u = fade(xf);
	double v = fade(yf);
	double w = fade(zf);
	
	double x1,x2,y1,y2;
	
	x1 = avg
	(
		pseudorandom_dot(h000,Vector(xf,yf,zf)),
		pseudorandom_dot(h001,Vector(xf-1,yf,zf)),
		u
	);
	x2 = avg
	(
		pseudorandom_dot(h011,Vector(xf,yf-1,zf)),
		pseudorandom_dot(h010,Vector(xf-1,yf-1,zf)),
		u
	);
	y1 = avg(x1,x2,v);
	
	x1 = avg
	(
		pseudorandom_dot(h100,Vector(xf,yf,zf-1)),
		pseudorandom_dot(h101,Vector(xf-1,yf,zf-1)),
		u
	);
	x2 = avg
	(
		pseudorandom_dot(h111,Vector(xf,yf-1,zf-1)),
		pseudorandom_dot(h110,Vector(xf-1,yf-1,zf-1)),
		u
	);
	y2 = avg(x1,x2,v);
	
	return (avg(y1,y2,w)+1)/2;
}


/*
 * depends on seed it will choose among following 16 vector and return dot(random_vec,pos)
 * (1,1,0),(1,-1,0),(-1,-1,0),(-1,1,0),
 * (0,1,1),(0,1,-1),(0,-1,-1),(0,-1,1),
 * (1,0,1),(1,0,-1),(-1,0,-1),(-1,0,1),
 * (1,1,1),(1,-1,1),(1,1,-1),(-1,1,1)
 */
double pseudorandom_dot(int seed,const Vector &pos)
{
	double x = pos.x;
	double y = pos.y;
	double z = pos.z;
	const double constant1 = 0.707107;
	const double constant2 = 0.577350;
	
	switch(seed&0xf)
	{
		case 0: return constant1*(x+y);
		case 1: return constant1*(x-y);
		case 2: return constant1*(-x-y);
		case 3: return constant1*(-x+y);
		case 4: return constant1*(y+z);
		case 5: return constant1*(y-z);
		case 6: return constant1*(-y-z);
		case 7: return constant1*(-y+z);
		case 8: return constant1*(x+z);
		case 9: return constant1*(x-z);
		case 0xa: return constant1*(-x-z);
		case 0xb: return constant1*(-x+z);
		case 0xc: return constant2*(x+y+z);
		case 0xd: return constant2*(x-y+z);
		case 0xe: return constant2*(x+y-z);
		case 0xf: return constant2*(-x+y+z);
	}

	return 0;
}


int rr_inc(int n)
{
	n++;
	if(n>BOUND) n-=BOUND;
	return n;
}


double fade(double x)
{
	return x*x*x*(x*(x*6-15)+10);
}


double avg(double min,double max,double frac)
{
	return min+frac*(max-min);
}
