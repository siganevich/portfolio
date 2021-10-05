#pragma once
#include "myString.h"

class var
{
private:
	int i;
	double d;
	myString ms;
	int type; // 1 - int, 2 - double, 3 - myString
public:
	var();
	var(var &v);
	var(int val);
	var(double val);
	var(myString &val);
	var(char *s);
	~var();

	var & operator = (var &v);
	var & operator = (int val);
	var & operator = (double val);
	var & operator = (myString &val);

	var operator + (var &v);
	var operator + (int v);
	var operator + (double v);
	var operator + (myString v);

	var operator - (var &v);
	var operator - (int v);
	var operator - (double v);
	var operator - (myString v);

	var operator / (var &v);
	var operator / (int v);
	var operator / (double v);
	var operator / (myString v);

	var operator * (var &v);
	var operator * (int v);
	var operator * (double v);
	var operator * (myString v);

	var & operator += (var &v);
	var & operator += (int v);
	var & operator += (double v);
	var & operator += (myString v);

	var & operator -= (var &v);
	var & operator -= (int v);
	var & operator -= (double v);
	var & operator -= (myString v);

	var & operator /= (var &v);
	var & operator /= (int v);
	var & operator /= (double v);
	var & operator /= (myString v);

	var & operator *= (var &v);
	var & operator *= (int v);
	var & operator *= (double v);
	var & operator *= (myString v);

	bool operator == (var &v);
	bool operator != (var &v);
	bool operator > (var &v);
	bool operator < (var &v);

	explicit operator double();
	explicit operator int();

	friend ostream & operator << (ostream &os, var &v);
};