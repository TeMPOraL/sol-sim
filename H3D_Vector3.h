#ifndef __H3D_VECTOR3_H__
#define __H3D_VECTOR3_H__

#pragma once

/*
Vector class created for Holodeck 3D Engine

Thanks to Mirko Teran-Ravnikar for his ideas with taking x,y,z into union->struct;

  Converted to new H3D Version.

  Last Update - 01.06.2003

  Programmer - Jacek "TeMPOraL" Zlydach

*/

/*
	TODO:
*/

#include <gl/gl.h>
#include <iostream>
#include <sstream>
#include <time.h>

#include "H3DMath.h"

namespace H3D
{

	namespace math{
/////////////////////////////////
//Vector Class
/////////////////////////////////
		class Vector3{
		public:
	
		/*
		This one is a nice trick to access variables;
		either by vector.x vector.y vector.z or pointer to
		float v[3] structure
		*/
	
			union{
				struct{
					float x;
					float y;
					float z;
				};
				float v[3];
			};

		public:

		//constructors
	
			inline Vector3(){}		//empty constructor
			inline Vector3(const float xx,const float yy,const float zz) : x(xx),y(yy),z(zz){}	//standart one (from component)
			inline Vector3(const float *arr)	//from array of floats
			{
				x=arr[0];
				y=arr[1];
				z=arr[2];
			}

			inline Vector3(const Vector3 & vec) : x(vec.x),y(vec.y),z(vec.z){}	//create from vector

			//basic math operations
			inline Vector3 operator+() const;	//positive
			inline Vector3 operator-() const;	//negative

			inline Vector3 &operator=(const Vector3 & vec);	//equals
			inline Vector3 &operator+=(const Vector3 & vec);//add
			inline Vector3 &operator-=(const Vector3 & vec);//substract
	
			inline Vector3 & operator*=(float scalar);	//scale by float
			inline Vector3 & operator/=(float scalar);	//scale by 1/float

			inline friend const Vector3 operator+(const Vector3 &v1, const Vector3 v2);	//add
			inline friend const Vector3 operator-(const Vector3 &v1, const Vector3 v2);	//substract
			inline friend const Vector3 operator*(const Vector3 &vec, const float scalar);	//multiply by scalar
			inline friend const Vector3 operator/(const Vector3 &vec, const float scalar);	//divide by scalar

			inline friend const Vector3 operator^(const Vector3 &v1, const Vector3 &v2);	//cross product
			inline friend const float operator%(const Vector3 &v1, const Vector3 &v2);	//dot product

		//	inline friend const Vector3 operator|(Vector3 &vec, const float lenght);	//sets lenght
		//	inline Vector3& operator|=(const float lenght);

			//basic comparision oprators
			inline friend bool operator==(const Vector3 &v1, const Vector3 &v2);	//is vector equal?
			inline friend bool operator!=(const Vector3 &v1, const Vector3 &v2);	//is vector not equal?
			inline friend bool operator>(const Vector3 &v1, const Vector3 &v2);		//is vector greater?
			inline friend bool operator<(const Vector3 &v1, const Vector3 &v2);		//is vector lesser?

			inline const bool IsZero() const;	//is vector zero?
	
			//various

			inline void Set(float xx, float yy, float zz);	//set by components
			inline void Set(float *components);	//set by pointer to components
			inline void Set(const Vector3 &vec);	//set by vector

			inline void Abs();	//set components to absolute

			inline void Zero();		//set all components to zero
	
			inline void NormalizeFast();	//reduce to unit-lenght
			inline void Normalize();	//reduce to unit-lenght (exact)

			//	inline void Reflect(const Vector3 &normal);	//reflects vector

			inline float Lenght() const;	//returns lenght of vector
			inline float LenghtSqr() const;

			//affects GL-Scene

			inline void Translate() const;	//translate for this vector
			inline void Rotate() const;		//rotate for this vector
			inline void Scale() const;		//scale for this vector
	
			//more various

			inline std::string ToString();			//string representation of vector

		};	//end of class CVector3

		////////////////////////////////////////////////////
		//operator + - return positive
		////////////////////////////////////////////////////
		inline Vector3 Vector3::operator+() const
		{
			return *this;
		}

		////////////////////////////////////////////////////
		//operator - - return negative
		////////////////////////////////////////////////////
		inline Vector3 Vector3::operator-() const
		{
			return Vector3(-x,-y,-z);
		}

		////////////////////////////////////////////////////
		//operator =
		////////////////////////////////////////////////////
		inline Vector3 & Vector3::operator=(const Vector3 &vec)
		{
			x=vec.x;
			y=vec.y;
			z=vec.z;
			return *this;
		}

		////////////////////////////////////////////////////
		//operator +=
		////////////////////////////////////////////////////
		inline Vector3 & Vector3::operator+=(const Vector3 &vec)
		{
			x+=vec.x;
			y+=vec.y;
			z+=vec.z;
			return *this;
		}

		////////////////////////////////////////////////////
		//operator -=
		////////////////////////////////////////////////////
		inline Vector3 & Vector3::operator-=(const Vector3 &vec)
		{
			x-=vec.x;
			y-=vec.y;
			z-=vec.z;
			return *this;
		}

		////////////////////////////////////////////////////
		//operator *= - scale by scalar
		////////////////////////////////////////////////////
		inline Vector3 & Vector3::operator*=(const float scalar)
		{
			x*=scalar;
			y*=scalar;
			z*=scalar;
			return *this;
		}	

		////////////////////////////////////////////////////
		//operator /= - scale by 1/scalar
		////////////////////////////////////////////////////
		inline Vector3 & Vector3::operator/=(const float scalar)
		{
			float sc = 1.0f/scalar;
	
			x*=sc;
			y*=sc;
			z*=sc;
			return *this;
		}

		////////////////////////////////////////////////////
		//operator +
		////////////////////////////////////////////////////
		inline const Vector3 operator+(const Vector3 &v1, const Vector3 v2)
		{
			return Vector3(v1.x + v2.x , v1.y + v2.y , v1.z + v2.z);
		}

		////////////////////////////////////////////////////
		//operator -
		////////////////////////////////////////////////////
		inline const Vector3 operator-(const Vector3 &v1, const Vector3 v2)
		{
			return Vector3(v1.x - v2.x , v1.y - v2.y , v1.z - v2.z);
		}

		////////////////////////////////////////////////////
		//operator *
		////////////////////////////////////////////////////
		inline const Vector3 operator*(const Vector3 &vec, const float scalar)
		{
			return Vector3(vec.x * scalar , vec.y * scalar , vec.z * scalar);
		}

		////////////////////////////////////////////////////
		//operator /
		////////////////////////////////////////////////////
		inline const Vector3 operator/(const Vector3 &vec, const float scalar)
		{
			float sc = 1.0f/scalar;
			return Vector3(vec.x * sc , vec.y * sc , vec.z * sc);
		}

		////////////////////////////////////////////////////
		//operator ^ - cross product
		////////////////////////////////////////////////////
		inline const Vector3 operator^(const Vector3 &v1,const Vector3 &v2)
		{
			Vector3 tmp;
			tmp.x =	v1.y * v2.z - v1.z * v2.y;
			tmp.y =	v1.z * v2.x - v1.x * v2.z;
			tmp.z =	v1.x * v2.y - v1.y * v2.x;

			return tmp;
		}

		////////////////////////////////////////////////////
		//operator % - dot product
		////////////////////////////////////////////////////
		inline const float operator%(const Vector3 &v1, const Vector3 &v2)
		{
			return (v1.x * v2.x)+(v1.y * v2.y)+(v1.z * v2.z);
		}
		/*
		////////////////////////////////////////////////////
		//operator | - changes lenght of the vector
		////////////////////////////////////////////////////
		inline friend const Vector3 operator|(const Vector3 & vec, const float lenght){
			return
		*/
		
		////////////////////////////////////////////////////
		//operator==
		////////////////////////////////////////////////////
		inline bool operator==(const Vector3 &v1, const Vector3 &v2)
		{
			return ( ( absf(v1.x - v2.x) < EPSILON ) &&	//x
					( absf(v1.y - v2.y) < EPSILON ) &&	//y
					( absf(v1.z - v2.z) < EPSILON ) );	//z
		}

		////////////////////////////////////////////////////
		//operator !=
		////////////////////////////////////////////////////
		inline bool operator!=(const Vector3 &v1, const Vector3 &v2)
		{
			return !(v1==v2);
		}

		////////////////////////////////////////////////////
		//operator >
		////////////////////////////////////////////////////
		inline bool operator>(const Vector3 &v1, const Vector3 &v2)
		{
			return (v1.LenghtSqr() > v2.LenghtSqr());
		}

		////////////////////////////////////////////////////
		//operator <
		////////////////////////////////////////////////////
		inline bool operator<(const Vector3 &v1, const Vector3 &v2)
		{
			return v1.LenghtSqr() < v2.LenghtSqr();
		}

		////////////////////////////////////////////////////
		//IsZero()
		////////////////////////////////////////////////////
		inline const bool Vector3::IsZero() const
		{
			return((x==0)&&(y==0)&&(z==0)) ? true : false;
		}

		////////////////////////////////////////////////////
		//Set(float,float,float)
		////////////////////////////////////////////////////
		inline void Vector3::Set(float xx, float yy, float zz)
		{
			x=xx;
			y=yy;
			z=zz;
		}

		////////////////////////////////////////////////////
		//Set(float*)
		////////////////////////////////////////////////////
		inline void Vector3::Set(float * arr)
		{
			x=arr[0];
			y=arr[1];
			z=arr[2];
		}

		////////////////////////////////////////////////////
		//Set(const Vector3 & vec)
		////////////////////////////////////////////////////
		inline void Vector3::Set(const Vector3 & vec)
		{
			x=vec.x;
			y=vec.y;
			z=vec.z;
		}

		////////////////////////////////////////////////////
		//Abs() - sets components to absolute
		////////////////////////////////////////////////////
		inline void Vector3::Abs()
		{
			x=absf(x);
			y=absf(y);
			z=absf(z);
		}

		////////////////////////////////////////////////////
		//Zero() - sets all components to 0
		////////////////////////////////////////////////////
		inline void Vector3::Zero(){
			x=0.0f;
			y=0.0f;
			z=0.0f;
		}

		////////////////////////////////////////////////////
		//NormalizeFast() - reduces vector to unit lenght;
		//	faster, but less accurate than standard one
		////////////////////////////////////////////////////
		inline void Vector3::NormalizeFast()
		{
			const float tmpLenght = RSqrt(x*x + y*y + z*z);
			x *= tmpLenght;
			y *= tmpLenght;
			z *= tmpLenght;
		}


		////////////////////////////////////////////////////
		//Normalize() - reduces vector to unit-lenght (exact)
		////////////////////////////////////////////////////
		inline void Vector3::Normalize()
		{
		const float tmpLenght = 1.0f/sqrtf(x*x + y*y + z*z);
			x *= tmpLenght;
			y *= tmpLenght;
			z *= tmpLenght;
		}

		////////////////////////////////////////////////////
		//Lenght() - returns lenght of the vector
		////////////////////////////////////////////////////
		inline float Vector3::Lenght() const
		{
			return sqrtf(x*x+y*y+z*z);
		}

		////////////////////////////////////////////////////
		//LenghtSqr() - returns squared vector lenght
		////////////////////////////////////////////////////
		inline float Vector3::LenghtSqr() const
		{
			return (x*x + y*y + z*z);
		}

		////////////////////////////////////////////////////
		//Translate() - translates GL Scene for this vector
		////////////////////////////////////////////////////
		inline void Vector3::Translate() const
		{
			glTranslatef(x,y,z);
		}

		////////////////////////////////////////////////////
		//Rotate() - rotates GL Scene for this vector
		////////////////////////////////////////////////////
		inline void Vector3::Rotate() const
		{
			glRotatef(x,1.0f,0.0f,0.0f);
			glRotatef(y,0.0f,1.0f,0.0f);
			glRotatef(z,0.0f,0.0f,1.0f);
		}

		////////////////////////////////////////////////////
		//Scale() - scales GL scene for this vector
		////////////////////////////////////////////////////
		inline void Vector3::Scale() const
		{
			glScalef(x,y,z);
		}

		////////////////////////////////////////////////////
		//ToString() - returns string representation of vector
		////////////////////////////////////////////////////
		inline std::string Vector3::ToString()
		{
			///////////////////////////////
			///FIXME - use iostream type///
			///////////////////////////////
			std::stringstream buff;
			buff << "V3(X: " << x <<" Y: "<< y <<" Z: " << z <<")";
			return buff.str();
		}
		
	}	//end of namespace Math

}	//end of namespace H3D

#endif //__H3D_VECTOR3_H__
