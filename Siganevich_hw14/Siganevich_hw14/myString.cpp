#include "myString.h"

myString::myString()
{
	this->p = nullptr;
}
myString::myString(char *str)
{
	size_t len = strlen(str) + 1;
	this->p = new char[len];
	strcpy_s(this->p, len, str);
}
myString::myString(myString &c)
{
	size_t len = strlen(c.p) + 1;
	this->p = new char[len];
	strcpy_s(this->p, len, c.p);
}
myString::~myString()
{
	if(p)
		delete[] this->p;
	this->p = nullptr;
}
myString & myString::operator = (myString &c)
{
	if (&c == this)
		return *this;
	if (this->p)
		delete[] this->p;
	size_t len = strlen(c.p) + 1;
	this->p = new char[len];
	strcpy_s(this->p, len, c.p);
	return *this;
}
myString & myString::operator = (const myString &c)
{
	if (&c == this) 
		return *this;
	if (this->p)
		delete[] this->p;
	size_t len = strlen(c.p) + 1;
	this->p = new char[len];
	strcpy_s(this->p, len, c.p);
	
	return *this;
}
myString myString::operator + (myString &a)
{
	if (!a.p) return *this;
	myString S;
	size_t len = strlen(this->p) + strlen(a.p) + 1;
	S.p = new char[len];
	strcpy_s(S.p, len, this->p);
	strcat_s(S.p, len, a.p); //Concat
	return S;
}
myString & myString::operator += (myString &a)
{
	size_t len = strlen(this->p) + strlen(a.p) + 1;
	char *x = new char[len];
	strcpy_s(x, len, this->p);
	strcat_s(x, len, a.p); //Concat
	delete[] this->p;
	this->p = x;
	return *this;
}
myString myString::operator - (int number)
{
	size_t len = strlen(this->p);
	if (number < len)
		number = 0;
	myString S;
	S.p = new char[len - number + 1];
	strncpy(S.p, this->p, (len - number));
	S.p[(len - number)] = 0;
	return S;
}

myString myString::operator * (myString &a)
{
	int count = 0;
	for (int i = 0; i < strlen(this->p); i++)
	{
		for (int j = 0; j < strlen(a.p); j++)
		{
			if (this->p[i] == a.p[j])
			{
				count++;
				break;
			}
		}
	}
	char *str = new char[count + 1]{ '\0' };
	int size = 0;
	for (int i = 0; i <= strlen(this->p); i++)
	{
		for (int j = 0; j <= strlen(a.p); j++)
		{
			if (this->p[i] == a.p[j])
			{
				str[size++] = p[i];
				break;
			}
		}
	}
	myString tmp(str);
	delete[] str;
	return tmp;
}
myString myString::operator / (myString &a)
{
	bool flag;
	int count = 0;
	for (int i = 0; i < strlen(this->p); i++)
	{
		for (int j = 0; j < strlen(a.p); j++)
		{
			flag = true;
			if (this->p[i] == a.p[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
			count++;
	}
	char *str = new char[count + 1]{ '\0' };
	int size = 0;
	for (int i = 0; i < strlen(this->p); i++)
	{
		for (int j = 0; j < strlen(a.p); j++)
		{
			flag = true;
			if (this->p[i] == a.p[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
			str[size++] = this->p[i];
	}
	myString tmp(str);
	return tmp;
}
myString & myString::operator *= (myString &a)
{
	int count = 0;
	for (int i = 0; i < strlen(this->p); i++)
	{
		for (int j = 0; j <= strlen(a.p); j++)
		{
			if (this->p[i] == a.p[j])
			{
				count++;
				break;
			}
		}
	}
	char *str = new char[count + 1]{ '\0' };
	int size = 0;
	for (int i = 0; i < strlen(this->p); i++)
	{
		for (int j = 0; j <= strlen(a.p); j++)
		{
			if (this->p[i] == a.p[j])
			{
				str[size++] = p[i];
				break;
			}
		}
	}
	delete[] this->p;
	this->p = str;
	return *this;
}
myString & myString::operator /= (myString &a)
{

	bool flag;
	int count = 0;
	for (int i = 0; i < strlen(this->p); i++)
	{
		for (int j = 0; j < strlen(a.p); j++)
		{
			flag = true;
			if (this->p[i] == a.p[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
			count++;
	}
	char *str = new char[count + 1]{ '\0' };
	int size = 0;
	for (int i = 0; i < strlen(this->p); i++)
	{
		for (int j = 0; j < strlen(a.p); j++)
		{
			flag = true;
			if (this->p[i] == a.p[j])
			{
				flag = false;
				break;
			}
		}
		if (flag)
			str[size++] = this->p[i];
	}
	delete[] this->p;
	this->p = str;
	return *this;
}

bool myString::operator == (myString &a)
{
	if (!(this->p) && !(a.p))
		return true;
	else if (!this->p || (!a.p))
		return false;
	return strcmp(this->p, a.p) == 0;
}
bool myString::operator != (myString &a)
{
	if (!(this->p) && !(a.p))
		return false;
	else if (!this->p || (!a.p))
		return true;
	return strcmp(this->p, a.p) != 0;
}
bool myString::operator > (myString &a)
{
	if (!(this->p) && !(a.p))
		return false;
	else if (!(this->p) && a.p)
		return false;
	else if (this->p && !(a.p))
		return true;
	return strcmp(this->p, a.p) > 0;
}
bool myString::operator < (myString &a)
{
	return !(*this > a) && (*this != a);
}
char *myString::getString()
{
	return this->p;
}
void myString::setString(char *str)
{
	delete[] this->p;
	size_t len = strlen(str) + 1;
	this->p = new char[len];
	strcpy_s(this->p, len, str);
}
void myString::deleteField()
{
	if (this->p)
	delete[] this->p;
}

ostream & operator << (ostream &os, myString &c)
{
	os << c.getString();
	return os;
}
istream & operator >> (istream &is, myString &c)
{
	char tmp[200];
	is >> tmp;
	c.setString(tmp);
	return is;
}