#include "var.h"

var::var()
{
	this->i = 0;
	this->d = 0;
	this->type = 0;
}
var::var(var &v)
{
	if (this == &v)
		return;
	this->i = v.i;
	this->d = v.d;
	if (v.type == 3)
		this->ms = v.ms;
	this->type = v.type;
}
var::var(int val)
{
	this->i = val;
	this->d = 0;
	this->type = 1;
}
var::var(double val)
{
	this->d = val;
	this->i = 0;
	this->type = 2;
}
var::var(myString &val)
{
	this->i = 0;
	this->d = 0;
	this->ms = val;
	this->type = 3;
}

var::var(char *s)
{
	this->i = 0;
	this->d = 0;
	this->ms = myString(s); 
	this->type = 3;
}

var::operator double()
{
	switch (this->type)
	{
	case 1:
		return (double) this->i;
		break;
	case 2:
		return this->d;
		break;
	case 3:
		return atof(this->ms.getString());
	break;
	}
}

var::~var()
{
	this->i = 0;
	this->d = 0;
	this->type = 0;
}

var & var::operator = (var &v)
{
	if (this == &v)
		return *this;
	this->i = v.i;
	this->d = v.d;
	if (v.type == 3)
		this->ms = v.ms;
	this->type = v.type;
	return *this;
}
var & var::operator = (int val)
{
	this->i = val;
	this->d = 0;
	if (this->type == 3)
		this->ms.~myString();
	this->type = 1;
	return *this;
}
var & var::operator = (double val)
{
	this->d = val;
	this->i = 0;
	if (this->type == 3)
		this->ms.~myString();
	this->type = 2;
	return *this;
}
var & var::operator = (myString &val)
{
	this->d = 0;
	this->i = 0;
	this->ms = val;
	this->type = 3;
	return *this;
}

var var::operator + (int v)
{
	var tmp = *this + var(v);
	return tmp;
}
var var::operator + (double v)
{
	var tmp = *this + var(v);
	return tmp;
}
var var::operator + (myString v)
{
	var tmp = *this + var(v);
	return tmp;
}

var var::operator + (var &v)
{
	var tmp;
	if (this->type == 1)
	{
		tmp.type = 1;
		if (v.type == 1)
			tmp.i = this->i + v.i;
		else if (v.type == 2)
			tmp.i = this->i + v.d;
		else if(v.type == 3)
			tmp.i = this->i + atoi(v.ms.getString());
	}
	else if (this->type == 2)
	{
		tmp.type = 2;
		if (v.type == 1)
			tmp.d = this->d + v.i;
		else if (v.type == 2)
			tmp.d = this->d + v.d;
		else if (v.type == 3)
			tmp.d = this->d + atof(v.ms.getString());
	}
	else if (this->type == 3)
	{
		tmp.type = 3;
		if (v.type == 1)
		{
			char *str = new char[10]{ '\0' };
			itoa(v.i, str, 10);
			myString s(str);
			tmp.ms = this->ms + s;
		}
		else if (v.type == 2)
		{
			char *str = new char[10]{ '\0' };
			_gcvt(v.d, 10, str);
			myString s(str);
			tmp.ms = this->ms + s;
		}
		else if (v.type == 3)
			tmp.ms = this->ms + v.ms;
	}
	return tmp;
}

var::operator int()
{
	switch (this->type)
	{
	case 1:
		return this->i;
		break;
	case 2:
		return (int)this->d;
		break;
	case 3:
		return atoi(this->ms.getString());
		break;
	}
}

var var::operator - (int v)
{
	var tmp = *this - var(v);
	return tmp;
}
var var::operator - (double v)
{
	var tmp = *this - var(v);
	return tmp;
}
var var::operator - (myString v)
{
	var tmp = *this - var(v);
	return tmp;
}

var var::operator - (var &v)
{
	var tmp;
	if (this->type == 1)
	{
		tmp.type = 1;
		if (v.type == 1)
			tmp.i = this->i - v.i;
		if (v.type == 2)
			tmp.i = this->i - v.d;
		else if (v.type == 3)
			tmp.i = this->i - atoi(v.ms.getString());
	}
	else if (this->type == 2)
	{
		tmp.type = 2;
		if (v.type == 1)
			tmp.d = this->d - v.i;
		else if(v.type == 2)
			tmp.d = this->d - v.d;
		else if (v.type == 3)
			tmp.d = this->d - atof(v.ms.getString());
	}
	else if(this->type == 3)
	{
		tmp.type = 3;
		if (v.type == 1)
		{
			char *str = new char[10]{ '\0' };
			itoa(v.i, str, 10);
			myString s(str);
			tmp.ms = this->ms - strlen(s.getString());
		}
		else if (v.type == 2)
		{
			char *str = new char[10]{ '\0' };
			_gcvt(v.d, 10, str);
			myString s(str);
			tmp.ms = this->ms - strlen(s.getString());
		}
		else if (v.type == 3)
			tmp.ms = this->ms - strlen(v.ms.getString());
	}
	return tmp;
}

var var::operator / (int v)
{
	var tmp = *this / var(v);
	return tmp;
}
var var::operator / (double v)
{
	var tmp = *this / var(v);
	return tmp;
}
var var::operator / (myString v)
{
	var tmp = *this / var(v);
	return tmp;
}

var var::operator / (var &v)
{
	var tmp;
	if (this->type == 1)
	{
		tmp.type = 1;
		if (v.type == 1)
			tmp.i = this->i / v.i;
		else if (v.type == 2)
			tmp.i = this->i / v.d;
		else if (v.type == 3)
			tmp.i = this->i / atoi(v.ms.getString());
	}
	else if (this->type == 2)
	{
		tmp.type = 2;
		if (v.type == 1)
			tmp.d = this->d / v.i;
		else if (v.type == 2)
			tmp.d = this->d / v.d;
		else if (v.type == 3)
			tmp.d = this->d / atof(v.ms.getString());
	}
	else if (this->type == 3)
	{
		tmp.type = 3;
		if (v.type == 1)
		{
			char *str = new char[10]{ '\0' };
			itoa(v.i, str, 10);
			myString s(str);
			tmp.ms = this->ms / s;
		}
		else if (v.type == 2)
		{
			char *str = new char[10]{ '\0' };
			_gcvt(v.d, 10, str);
			myString s(str);
			tmp.ms = this->ms / s;
		}
		else if (v.type == 3)
			tmp.ms = this->ms / v.ms;
	}
	return tmp;
}

var var::operator * (int v)
{
	var tmp = *this * var(v);
	return tmp;
}
var var::operator * (double v)
{
	var tmp = *this * var(v);
	return tmp;
}
var var::operator * (myString v)
{
	var tmp = *this * var(v);
	return tmp;
}

var var::operator * (var &v)
{
	var tmp;
	if (this->type == 1)
	{
		tmp.type = 1;
		if (v.type == 1)
			tmp.i = this->i * v.i;
		else if (v.type == 2)
			tmp.i = this->i * v.d;
		else if (v.type == 3)
			tmp.i = this->i * atoi(v.ms.getString());
	}
	else if (this->type == 2)
	{
		tmp.type = 2;
		if (v.type == 1)
			tmp.d = this->d * v.i;
		else if (v.type == 2)
			tmp.d = this->d * v.d;
		else if (v.type == 3)
			tmp.d = this->d * atof(v.ms.getString());
	}
	else if (this->type == 3)
	{
		tmp.type = 3;
		if (v.type == 1)
		{
			char *str = new char[10]{ '\0' };
			itoa(v.i, str, 10);
			myString s(str);
			tmp.ms = this->ms * s;
		}
		else if (v.type == 2)
		{
			char *str = new char[10]{ '\0' };
			_gcvt(v.d, 10, str);
			myString s(str);
			tmp.ms = this->ms * s;
		}
		else if (v.type == 3)
			tmp.ms = this->ms * v.ms;
	}
	return tmp;
}

var & var::operator += (int v)
{
	*this += var(v);
	return *this;
}
var & var::operator += (double v)
{
	*this += var(v);
	return *this;
}
var & var::operator += (myString v)
{
	*this += var(v);
	return *this;
}

var & var::operator += (var &v)
{
	{
		if (this->type == 1)
		{
			if (v.type == 1)
				this->i += v.i;
			else if (v.type == 2)
				this->i += v.d;
			else if (v.type == 3)
				this->i += atoi(v.ms.getString());
		}
		else if (this->type == 2)
		{
			if (v.type == 1)
				this->d += v.i;
			else if (v.type == 2)
				this->d += v.d;
			else if (v.type == 3)
				this->d += atof(v.ms.getString());
		}
		else if (this->type == 3)
		{
			if (v.type == 1)
			{
				char *str = new char[10]{ '\0' };
				itoa(v.i, str, 10);
				myString s(str);
				this->ms += s;
			}
			else if (v.type == 2)
			{
				char *str = new char[10]{ '\0' };
				_gcvt(v.d, 10, str);
				myString s(str);
				this->ms += s;
			}
			else if (v.type == 3)
				this->ms += v.ms;
		}
		return *this;
	}
}

var & var::operator -= (int v)
{
	*this -= var(v);
	return *this;
}
var & var::operator -= (double v)
{
	*this -= var(v);
	return *this;
}
var & var::operator -= (myString v)
{
	*this -= var(v);
	return *this;
}

var & var::operator -= (var &v)
{
	if (this->type == 1)
	{
		if (v.type == 1)
			this->i -= v.i;
		else if (v.type == 2)
			this->i -= v.d;
		else if (v.type == 3)
			this->i -= atoi(v.ms.getString());
	}
	else if (this->type == 2)
	{
		if (v.type == 1)
			this->d -= v.i;
		else if(v.type == 2)
			this->d -= v.d;
		else if (v.type == 3)
			this->d -= atof(v.ms.getString());
	}
	else if (this->type == 3)
	{
		if (v.type == 1)
		{
			char *str = new char[10]{ '\0' };
			itoa(v.i, str, 10);
			myString s(str);
			this->ms = this->ms - strlen(s.getString());
		}
		else if (v.type == 2)
		{
			char *str = new char[10]{ '\0' };
			_gcvt(v.d, 10, str);
			myString s(str);
			this->ms = this->ms - strlen(s.getString());
		} 
		else if (v.type == 3)
			this->ms = this->ms - strlen(v.ms.getString());
	}
	return *this;
}

var & var::operator /= (int v)
{
	*this /= var(v);
	return *this;
}
var & var::operator /= (double v)
{
	*this /= var(v);
	return *this;
}
var & var::operator /= (myString v)
{
	*this /= var(v);
	return *this;
}

var & var::operator /= (var &v)
{
	if (this->type == 1)
	{
		if (v.type == 1)
			this->i /= v.i;
		else if (v.type == 2)
			this->i /= v.d;
		else if (v.type == 3)
			this->i /= atoi(v.ms.getString());
	}
	else if (this->type == 2)
	{
		if (v.type == 1)
			this->d /= v.i;
		else if (v.type == 2)
			this->d /= v.d;
		else if (v.type == 3)
			this->d /= atof(v.ms.getString());
	}
	else if (this->type == 3)
	{
		if (v.type == 1)
		{
			char *str = new char[10]{ '\0' };
			itoa(v.i, str, 10);
			myString s(str);
			this->ms /= s;
		}
		else if (v.type == 2)
		{
			char *str = new char[10]{ '\0' };
			_gcvt(v.d, 10, str);
			myString s(str);
			this->ms /= s;
		} 
		else if (v.type == 3)
			this->ms /= v.ms;
	}
	return *this;
}

var & var::operator *= (int v)
{
	*this += var(v);
	return *this;
}
var & var::operator *= (double v)
{
	*this += var(v);
	return *this;
}
var & var::operator *= (myString v)
{
	*this += var(v);
	return *this;
}

var & var::operator *= (var &v)
{
	if (this->type == 1)
	{
		if (v.type == 1)
			this->i *= v.i;
		else if (v.type == 2)
			this->i *= v.d;
		else if (v.type == 3)
			this->i *= atoi(v.ms.getString());
	}
	else if (this->type == 2)
	{
		if (v.type == 1)
			this->d *= v.i;
		else if (v.type == 2)
			this->d *= v.d;
		else if (v.type == 3)
			this->d *= atof(v.ms.getString());
	}
	else if (this->type == 1)
	{
		if (v.type == 3)
		{
			char *str = new char[10]{ '\0' };
			itoa(v.i, str, 10);
			myString s(str);
			this->ms *= s;
		}
		else if (v.type == 2)
		{
			char *str = new char[10]{ '\0' };
			_gcvt(v.d, 10, str);
			myString s(str);
			this->ms *= s;
		}
		else if (v.type == 3)
			this->ms *= v.ms;
	}
	return *this;
}

bool var::operator == (var &v)
{
	return (this->i == v.i && this->d == v.d && this->ms == v.ms && this->type == this->type);
}
bool var::operator != (var &v)
{
	return (this->i != v.i || this->d != v.d || this->ms != v.ms || this->type != v.type);
}
bool var::operator > (var &v)
{
	return (this->i > v.i || this->d > v.d || strcmp(this->ms.getString(), v.ms.getString()) > 0);
}
bool var::operator < (var &v)
{
	return (this->i < v.i || this->d < v.d || strcmp(this->ms.getString(), v.ms.getString()) < 0);
}

ostream & operator << (ostream &os, var &v)
{
	if (v.type == 1)
		os << v.i;
	else if (v.type == 2)
		os << v.d;
	else if (v.type == 3)
		os << v.ms;
	return os;
}