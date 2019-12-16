#include <iostream>
#include <cstdlib>


#define BOUND 256

class vector
{
public:
	double x,y,z;
	vector(double x,double y,double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};


int perlin_random[BOUND];

void init_random();
double perlin_noise(const vector &pos,int repeat);
double pseudorandom_dot(int seed,const vector &pos);
int rr_inc(int n);
double fade(double x);
double avg(double max,double min,double frac);


int main()
{
	init_random();
	
	for(int x=0;x<512;x++)
	{
		for(int y=0;y<512;y++)
		{
			std::cout<<10.0*perlin_noise(vector(x+(rand()*1.0)/RAND_MAX,y+(1.0*rand())/RAND_MAX,0),BOUND)<<std::endl;
		}
	}
	
	return 0;
}


void init_random()
{
	for(int l=0;l<BOUND;l++)
	{
		perlin_random[l] = rand()%BOUND;
	}
}


double perlin_noise(const vector &pos, int repeat)
{
	int xi = (int)(pos.x);
	int yi = (int)(pos.y);
	int zi = (int)(pos.z);

	double xf = pos.x-xi;
	double yf = pos.y-yi;
	double zf = pos.z-zi;
	
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
		pseudorandom_dot(h000,vector(xf,yf,zf)),
		pseudorandom_dot(h001,vector(xf-1,yf,zf)),
		u
	);
	x2 = avg
	(
		pseudorandom_dot(h011,vector(xf,yf-1,zf)),
		pseudorandom_dot(h010,vector(xf-1,yf-1,zf)),
		u
	);
	y1 = avg(x1,x2,v);
	
	x1 = avg
	(
		pseudorandom_dot(h100,vector(xf,yf,zf-1)),
		pseudorandom_dot(h101,vector(xf-1,yf,zf-1)),
		u
	);
	x2 = avg
	(
		pseudorandom_dot(h111,vector(xf,yf-1,zf-1)),
		pseudorandom_dot(h110,vector(xf-1,yf-1,zf-1)),
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
double pseudorandom_dot(int seed,const vector &pos)
{
	double x = pos.x;
	double y = pos.y;
	double z = pos.z;
	
	switch(seed&0xf)
	{
		case 0: return x+y;
		case 1: return x-y;
		case 2: return -x-y;
		case 3: return -x+y;
		case 4: return y+z;
		case 5: return y-z;
		case 6: return -y-z;
		case 7: return -y+z;
		case 8: return x+z;
		case 9: return x-z;
		case 0xa: return -x-z;
		case 0xb: return -x+z;
		case 0xc: return x+y+z;
		case 0xd: return x-y+z;
		case 0xe: return x+y-z;
		case 0xf: return -x+y+z;
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
