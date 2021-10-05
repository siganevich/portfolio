#pragma once
#include <iostream>
using namespace std;
class myString
{
private:
	char *p;
public:
	myString();
	myString(char *str);
	myString(myString &c);
	~myString();
	myString & operator = (myString &c);   // ����������� �����
	myString & operator = (const myString &c);
	myString operator + (myString &a);     // ��������� �����
	myString & operator += (myString &a);  // ��������� �����
	myString operator -(int number);   //�������� ����� ������ �� number ��������
	myString operator * (myString &a);
	myString operator / (myString &a);
	myString & operator *= (myString &a);
	myString & operator /= (myString &a);
	bool operator == (myString &a);
	bool operator != (myString &a);
	bool operator > (myString &a);
	bool operator < (myString &a);
	char *getString();
	void setString(char *str);
	void deleteField();
};
ostream & operator << (ostream &os, myString &c);
istream & operator >> (istream &is, myString &c);