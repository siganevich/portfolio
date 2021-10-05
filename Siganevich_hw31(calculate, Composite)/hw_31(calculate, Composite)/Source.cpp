#include <iostream>
#include <string>
#include <vector>
using namespace std;

int calculateValue(string str)
{
	int val1 = 0, val2 = 0, val3 = 0; 
	char sym1 = 0, sym2 = 0, sym3 = 0;
	char c;
	for (int index = 0; index < str.length() || (index == str.length() && val2 != 0) ; index++)
	{
		c = str[index];
		if (c == '(' || c == ')')
			continue;
		if (val1 == 0)
			while (isdigit(c))
			{
				val1 = val1 * 10 + c - '0';
				c = str[++index];
			}
		else if (val2 == 0)
			while (isdigit(c))
			{
				val2 = val2 * 10 + c - '0';
				c = str[++index];
			}
		else
			while (isdigit(c))
			{
				val3 = val3 * 10 + c - '0';
				c = str[++index];
			}
		if (!isdigit(c) && c != 0)
		{
			if (sym1 == 0)
				sym1 = c;
			else if (sym2 == 0)
				sym2 = c;
			else if (sym3 == 0)
				sym3 = c;
		}
		if ((sym2 == '*' || sym2 == '/') && val3 != 0)
		{
			val2 = ((sym2 == '*') ? (val2 * val3) : val2 / val3);
			sym2 = sym3;
			val3 = 0;
			sym3 = 0;
		}
		if ((sym1 == '*' || sym1 == '/') && val2 != 0)
		{
			val1 = ((sym1 == '*') ? (val1 * val2) : val1 / val2);
			val2 = 0;
			sym1 = sym2;
			sym2 = 0;
		}
		else if ((sym1 == '-' || sym1 == '+') && ((sym2 == '+' || sym2 == '-') || sym2 == ')' || c == 0))
		{
			val1 = ((sym1 == '-') ? (val1 - val2) : val1 + val2);
			val2 = 0;
			sym1 = sym2;
			sym2 = 0;
		}

	}

	return val1;
}

class Component
{
public:
	virtual string getName() = 0;
	virtual int getValue() = 0;
	virtual void edit() = 0;
};

class Node : public Component
{
private:
	int value;
	string name;	// Выражение
public:
	Node(string name)
	{
		this->name = name;
	}
	string getName()
	{
		return this->name;
	}
	int getValue()
	{
		return this->value;
	}
	void edit()
	{
		this->value = calculateValue(this->name);
	}
};

class Composite : public Component
{
private:
	string name;	// Название элемента
	int value;
	vector<Component *> children;	// Коллекция дочерних узлов
public:
	Composite() {};
	Composite(string n) 
	{
		this->name = n;
	}
	void setName(string n)
	{
		this->name = n;
	}
	void addChild(Component *c)
	{
		this->children.push_back(c);
	}
	void removeChild(Component *c)
	{
		vector<Component *>::iterator p = find(children.begin(), children.end(), c);
		if (p != children.end())
			children.erase(p);
	}
	string getName()
	{
		return this->name;
	}
	int getValue()
	{
		return this->value;
	}
	void edit()
	{
		string n = this->getName();
		for (int i = 0; i < this->children.size(); i++)
		{
			this->children[i]->edit();
			string m = this->children[i]->getName();
			size_t pos = n.find(m, 0);
			char *str = new char[5]{ 0 };
			itoa(this->children[i]->getValue(), str, 10);
			n.replace(pos, this->children[i]->getName().length(), str);
			delete[] str;
		}
		this->value = calculateValue(n);
	}
};

const int STATE_OPEN_BRACKET = 0;
const int STATE_CLOSE_BRACKET = 1;
const int STATE_CALCULATE_VALUE = 2;

Component *makeComposite(string str, int &index)
{
	Component *p = NULL;
	int state = STATE_CALCULATE_VALUE;
	string a;
	while (true)
	{
		if (index >= str.length() && state != 1)
			break;

		char c = str[index];

		if (c == ' ')
		{
			index++;
			continue;
		}

		switch (state)
		{
		case STATE_CALCULATE_VALUE:
		{
			if (c == '(')
				state = STATE_OPEN_BRACKET;
			else if (c == ')')
				state = STATE_CLOSE_BRACKET;
			else
				a += c;
		}
		break;
		case STATE_OPEN_BRACKET:
		{
			Component *child = makeComposite(str, index);
			if (p == NULL)
				p = new Composite();
			((Composite *)p)->addChild(child);
			a += child->getName();
			state = STATE_CALCULATE_VALUE;
		}
		break;
		case STATE_CLOSE_BRACKET:
		{
			a += ')';
			index--;
			if (a.find('(') != string::npos)
			{
				a.insert(0, "(");
				goto M1;
			}
			a.insert(0, "(");
			p = new Node(a);
			return p;
		}
		break;
		}
		index++;
	}
	M1:
	((Composite *)p)->setName(a);
	return p;
}

int main()
{
	string str = "280 - (48 *7 -23 *(24-7*(1+1)))+ 5 - 6*(35-33)";
	//string str = "(35 - (15*2 +(9 -4/2 - (5*1))) + 7) *(5*2)-1";
	int index = 0;
	Component *p = makeComposite(str, index);
	p->edit();
	int rezult = p->getValue();
	cout << str << " = " << rezult << endl;

	return 0;
}