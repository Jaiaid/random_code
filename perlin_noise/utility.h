#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <cstdlib>
#include <cmath>

#define DEGTORAD(ang) ang*M_PI/180

class Vector
{
public:
	double x;
	double y;
	double z;

	Vector(){}

	Vector(double x, double y, double z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	double mag()
	{
		return sqrt(x*x + y*y + z*z);
	}
	
	Vector norm()
	{
		double mag = this->mag();
		return Vector(this->x/mag, this->y/mag, this->z/mag);
	}

	Vector operator+(Vector &op)
	{
		Vector tmp;
		tmp.x = x + op.x;
		tmp.y = y + op.y;
		tmp.z = z + op.z;

		return tmp;
	}

	Vector operator-(const Vector &op)
	{
		Vector tmp;
		tmp.x = x - op.x;
		tmp.y = y - op.y;
		tmp.z = z - op.z;

		return tmp;
	}

	Vector crossproduct(const Vector &op)
	{
		Vector tmp;
		
		tmp.x = y*op.z - z*op.y;;
		tmp.y = -x*op.z + z*op.x;
		tmp.z = x*op.y - y*op.x;
		
		return tmp;
	}

	void rotate(const Vector &axis, double angle)
	{
		angle = DEGTORAD(angle);
		double orthoX = y*axis.z - z*axis.y;
		double orthoY = -x*axis.z + z*axis.x;
		double orthoZ = x*axis.y - y*axis.x;
		double c2 = cos(angle), c3 = -sin(angle);

		double det = axis.x * (y*orthoZ - z*orthoY) - axis.y * (x*orthoZ - z*orthoX)
			+ axis.z * (x*orthoY - y*orthoX);
		
		double tmpX, tmpY, tmpZ;

		if(det==0) {
			std::cout<<x<<' '<<y<<' '<<z<<std::endl;
			std::cout<<"zero divide error"<<std::endl;
			exit(0);
		}

		tmpX = (-c2 * (axis.y*orthoZ - axis.z*orthoY) + c3 * (axis.y*z - axis.z*y)) / det ;
		tmpY = (c2 * (axis.x*orthoZ - axis.z*orthoX) - c3 * (axis.x*z - axis.z*x)) / det ;
		tmpZ = (-c2 * (axis.x*orthoY - axis.y*orthoX) + c3 * (axis.x*y - axis.y*x)) / det ;

		x = tmpX, y = tmpY, z = tmpZ;
		
		double mag = this->mag();
		if(mag > 1 || mag < 1){
			x /= mag, y /= mag, z /= mag; 
		}
	}
	
	friend std::ostream & operator<<(std::ostream &stream, Vector &obj);
};

std::ostream & operator<<(std::ostream &stream, Vector &obj)
{
	stream<<'('<<obj.x<<' '<<obj.y<<' '<<obj.z<<')';
	return stream;
}

#endif
