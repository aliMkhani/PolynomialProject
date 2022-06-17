#pragma once
#include <fstream>
#include <vector>
#include "Term.h"


int GetFirstSignIndex(string poly)
{
	int pos = poly.find("+");
	int neg = poly.find("-");
	if (pos == -1 && neg != -1)
	{
		return neg;
	}
	else if (neg == -1 && pos != -1)
	{
		return pos;
	}
	else if (pos > neg)
	{
		return neg;
	}
	else if (neg > pos)
	{
		return pos;
	}
	else
	{
		return -1;
	}
}
void GettNodes(string poly, vector<string>* nodes)
{
	if (poly.length() == 0)
	{
		return;
	}
	int first = GetFirstSignIndex(poly);
	string newPoly = poly.substr(first + 1, poly.length() - first - 1);
	int last = GetFirstSignIndex(newPoly);
	if (last == -1)
	{
		nodes->push_back(poly);
		return;
	}
	nodes->push_back(poly.substr(first, last + 1));
	poly = poly.substr(last + 1, poly.length() - last - 1);
	GettNodes(poly, nodes);
}

class Polynomial
{
public:
	Polynomial(vector<Term> terms);
	Polynomial();
	~Polynomial();
	int termsCount()
	{
		return terms.size();
	}
	int Degree()
	{
		int res = terms[0].GetP();
		for (int i = 1; i < terms.size(); i++)
		{
			if (terms[i].GetP() > res)
			{
				res = terms[i].GetP();
			}
		}
		return res;
	}
	void AddTerm(Term term) {
		terms.push_back(term);
	}
	Polynomial operator+(Polynomial polynomial);
	Polynomial operator+(Term term);
	Polynomial operator+(float x);
	Polynomial operator-(Polynomial polynomial);
	Polynomial operator-(Term term);
	Polynomial operator-(float x);
	Polynomial operator*(Polynomial polynomial);
	Polynomial operator*(Term term);
	Polynomial operator*(float x);
	void operator+=(Polynomial polynomial);
	void operator-=(Polynomial polynomial);
	void operator*=(Polynomial polynomial);
	void operator=(Polynomial polynomial);
	bool operator>(Polynomial polynomial);
	bool operator>(Term term);
	bool operator>(float x);
	bool operator<(Polynomial polynomial);
	bool operator<(Term term);
	bool operator<(float x);
	bool operator>=(Polynomial polynomial);
	bool operator>=(Term term);
	bool operator>=(float x);
	bool operator<=(Polynomial polynomial);
	bool operator<=(Term term);
	bool operator<=(float x);
	bool operator==(Polynomial polynomial);
	bool operator==(Term term);
	bool operator==(float x);
	bool operator!=(Polynomial polynomial);
	bool operator!=(Term term);
	bool operator!=(float x);
	Polynomial operator~();
	void operator++();
	void operator--();
	float operator()(float x);
	Term operator[](int index);
	string Tostring();
	void FillByString(string polyString);
	friend ostream& operator<<(ostream& os, Polynomial term);
	friend istream& operator>>(istream& os, Polynomial* term);
private:
	vector<Term> terms;
};
ostream& operator<<(ostream& os, Polynomial pol)
{
	if (pol.termsCount() == 0)
	{
		cout << "0";
	}
	for (int i = 0; i < pol.termsCount(); i++)
	{
		cout << pol[i];
	}
	return os;
}
istream& operator>>(istream& is, Polynomial* pol)
{
	string poly;
	cin >> poly;
	int powIndex = poly.find("^");
	if (powIndex == -1)
	{
		pol->AddTerm(Term(stoi(poly), 0));
		return is;
	}

	vector<string> nodes;
	GettNodes(poly, &nodes);
	for (int i = 0; i < nodes.size(); i++)
	{
		Term term = Term();
		string sign = nodes[i].substr(0, 1);
		int powIndex = nodes[i].find("^");
		if (sign == "-")
		{
			term.SetC(stoi(nodes[i].substr(0, powIndex)));
			term.SetP(stoi(nodes[i].substr(powIndex + 1, nodes[i].length() - powIndex - 1)));
		}
		else
		{
			term.SetC(stoi(nodes[i].substr(1, powIndex)));
			term.SetP(stoi(nodes[i].substr(powIndex + 1, nodes[i].length() - powIndex - 1)));
		}
		pol->AddTerm(term);
	}
	return is;
}
Polynomial::Polynomial(vector<Term> terms)
{
	this->terms = terms;
}
Polynomial::Polynomial()
{
}
Polynomial::~Polynomial()
{
}
Polynomial Polynomial::operator+(Polynomial b)
{
	if (this->terms.size() == 0)
	{
		return b;
	}
	if (b.terms.size() == 0)
	{
		return *this;
	}
	if (this->terms.size() == 0 && b.terms.size() == 0)
	{
		return Polynomial();
	}
	Polynomial polynomial = Polynomial();

	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i];
		for (int j = 0; j < b.termsCount(); j++)
		{
			try
			{
				newTerm += b.terms[j];
			}
			catch (const std::exception&)
			{

			}
		}
		polynomial.AddTerm(newTerm);
	}

	for (int i = 0; i < b.termsCount(); i++)
	{
		Term newTerm = b.terms[i];
		for (int j = 0; j < this->termsCount(); j++)
		{
			try
			{
				newTerm += this->terms[j];
			}
			catch (const std::exception&)
			{

			}
		}
		bool exist = false;
		for (int j = 0; j < polynomial.termsCount(); j++)
		{
			if (polynomial[j] == newTerm)
			{
				exist = true;
			}
		}
		if (!exist)
		{
			polynomial.AddTerm(newTerm);
		}
	}
	return polynomial;

}
Polynomial Polynomial::operator+(Term term)
{
	if (this->terms.size() == 0)
	{
		this->AddTerm(term);
		return *this;
	}
	Polynomial polynomial = Polynomial();
	bool done = false;
	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i];
		try
		{
			newTerm += term;
			done = true;
		}
		catch (const std::exception&)
		{

		}
		polynomial.AddTerm(newTerm);
	}
	if (!done)
	{
		polynomial.AddTerm(term);
	}
	return polynomial;
}
Polynomial Polynomial::operator+(float x)
{
	if (this->terms.size() == 0)
	{
		this->AddTerm(Term(x, 0));
		return *this;
	}
	Polynomial polynomial = Polynomial();
	bool done = false;
	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i];
		try
		{
			newTerm = newTerm + x;
			done = true;
		}
		catch (const std::exception&)
		{

		}
		polynomial.AddTerm(newTerm);
	}
	if (!done)
	{
		polynomial.AddTerm(Term(x, 0));
	}
	return polynomial;
}
Polynomial Polynomial::operator-(Polynomial b)
{
	if (this->terms.size() == 0)
	{
		for (int i = 0; i < b.termsCount(); i++)
		{
			b.terms[i] = Term(b.terms[i].GetC() * -1, b.terms[i].GetP());
		}
		return b;
	}
	if (b.terms.size() == 0)
	{
		return *this;
	}
	if (this->terms.size() == 0 && b.terms.size() == 0)
	{
		return Polynomial();
	}
	Polynomial polynomial = Polynomial();

	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i];
		for (int j = 0; j < b.termsCount(); j++)
		{
			try
			{
				newTerm -= b.terms[j];
			}
			catch (const std::exception&)
			{

			}
		}
		polynomial.AddTerm(newTerm);
	}

	for (int i = 0; i < b.termsCount(); i++)
	{
		Term newTerm = b.terms[i];
		for (int j = 0; j < this->termsCount(); j++)
		{
			try
			{
				newTerm -= this->terms[j];
			}
			catch (const std::exception&)
			{

			}
		}
		bool exist = false;
		for (int j = 0; j < polynomial.termsCount(); j++)
		{
			if (polynomial[j].IsSymmetric(newTerm))
			{
				exist = true;
			}
		}
		if (!exist)
		{
			polynomial.AddTerm(Term(-1 * newTerm.GetC(), newTerm.GetP()));
		}
	}
	return polynomial;
}
Polynomial Polynomial::operator-(Term term)
{
	if (this->terms.size() == 0)
	{
		this->AddTerm(Term(-1 * term.GetC(), term.GetP()));
		return *this;
	}

	Polynomial polynomial = Polynomial();
	bool done = false;
	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i];
		try
		{
			newTerm -= term;
		}
		catch (const std::exception&)
		{

		}
		polynomial.AddTerm(newTerm);
	}
	if (!done)
	{
		polynomial.AddTerm(Term(-1 * term.GetC(), term.GetP()));
	}
	return polynomial;
}
Polynomial Polynomial::operator-(float x)
{
	if (this->terms.size() == 0)
	{
		this->AddTerm(Term(-1 * x, 0));
		return *this;
	}
	Polynomial polynomial = Polynomial();
	bool done = false;
	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i];
		try
		{
			newTerm = newTerm - x;
			done = true;
		}
		catch (const std::exception&)
		{

		}
		polynomial.AddTerm(newTerm);
	}
	if (!done)
	{
		polynomial.AddTerm(Term(-1 * x, 0));
	}
	return polynomial;
}
Polynomial Polynomial::operator*(Polynomial polynomial)
{
	Polynomial newpolynomial = Polynomial();
	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm;
		for (int j = 0; j < polynomial.termsCount(); j++)
		{
			newTerm = this->terms[i] * polynomial[j];
			newpolynomial = newpolynomial + newTerm;
		}
	}
	return newpolynomial;
}
Polynomial Polynomial::operator*(Term term)
{
	Polynomial newpolynomial = Polynomial();
	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i] * term;
		newpolynomial = newpolynomial + newTerm;
	}
	return newpolynomial;
}
Polynomial Polynomial::operator*(float x)
{
	Polynomial newpolynomial = Polynomial();
	for (int i = 0; i < this->termsCount(); i++)
	{
		Term newTerm = this->terms[i] * x;
		newpolynomial = newpolynomial + newTerm;
	}
	return newpolynomial;
}
void Polynomial::operator+=(Polynomial polynomial)
{
	*this = *this + polynomial;
}
void Polynomial::operator-=(Polynomial polynomial)
{
	*this = *this - polynomial;

}
void Polynomial::operator*=(Polynomial polynomial)
{
	*this = *this * polynomial;
}
void Polynomial::operator=(Polynomial polynomial)
{
	this->terms = polynomial.terms;
}
bool Polynomial::operator>(Polynomial polynomial)
{
	Term term = polynomial.terms[0];
	if (this->terms[0].GetP() > term.GetP())
	{
		return true;
	}
	return false;
}
bool Polynomial::operator>(Term term)
{
	Term term1 = term;
	if (this->terms[0].GetP() > term1.GetP())
	{
		return true;
	}
	return false;
}
bool Polynomial::operator>(float x)
{
	if (this->terms[0].GetP() > x)
	{
		return true;
	}
	return false;
}
bool Polynomial::operator<(Polynomial polynomial)
{
	return !(*this > polynomial);
}
bool Polynomial::operator<(Term term)
{
	return !(*this > term);
}
bool Polynomial::operator<(float x)
{
	return !(*this > x);
}
bool Polynomial::operator>=(Polynomial polynomial)
{
	return *this > polynomial || *this == polynomial;
}
bool Polynomial::operator>=(Term term)
{
	return *this > term || *this == term;
}
bool Polynomial::operator>=(float x)
{
	return *this > x || *this == x;
}
bool Polynomial::operator<=(Polynomial polynomial)
{
	return *this < polynomial || *this == polynomial;
}
bool Polynomial::operator<=(Term term)
{
	return *this < term || *this == term;
}
bool Polynomial::operator<=(float x)
{
	return *this < x || *this == x;
}
bool Polynomial::operator==(Polynomial polynomial)
{
	Term term = polynomial.terms[0];
	if (this->terms[0].GetP() == term.GetP())
	{
		return true;
	}
	return false;
}
bool Polynomial::operator==(Term term)
{
	Term term1 = term;
	if (this->terms[0].GetP() == term1.GetP())
	{
		return true;
	}
	return false;
}
bool Polynomial::operator==(float x)
{
	if (this->terms[0].GetP() == x)
	{
		return true;
	}
	return false;
}
bool Polynomial::operator!=(Polynomial polynomial)
{
	return !(*this == polynomial);
}
bool Polynomial::operator!=(Term term)
{
	return !(*this == term);
}
bool Polynomial::operator!=(float x)
{
	return !(*this == x);
}
Polynomial Polynomial::operator~()
{
	vector<Term> terms;
	for (size_t i = 0; i < this->terms.size(); i++)
	{
		terms.push_back(~this->terms[i]);
	}
	return Polynomial(terms);
}
void Polynomial::operator++()
{
	for (size_t i = 0; i < this->terms.size(); i++)
	{
		if (this->terms[i].GetP() == 0)
		{
			this->terms[i] = this->terms[i] + 1;
		}
	}
}
void Polynomial::operator--()
{
	for (size_t i = 0; i < this->terms.size(); i++)
	{
		if (this->terms[i].GetP() == 0)
		{
			this->terms[i] = this->terms[i] - 1;
		}
	}
}
float Polynomial::operator()(float x)
{
	float resultl = 0;
	for (size_t i = 0; i < this->terms.size(); i++)
	{
		resultl += this->terms[i](x);
	}
	return resultl;
}
Term Polynomial::operator[](int index) {
	return this->terms[index];
}
string Polynomial::Tostring()
{
	string polynomial;
	for (int i = 0; i < terms.size(); i++)
	{
		polynomial += terms[i].ToString();
	}
	return polynomial;
}
void Polynomial::FillByString(string polyString)
{
	this->terms = vector<Term>();
	int powIndex = polyString.find("^");
	if (powIndex == -1)
	{
		this->AddTerm(Term(stoi(polyString), 0));
		return;
	}
	vector<string> nodes;
	GettNodes(polyString, &nodes);
	for (int i = 0; i < nodes.size(); i++)
	{
		Term term = Term();
		string sign = nodes[i].substr(0, 1);
		int powIndex = nodes[i].find("^");
		if (sign == "-")
		{
			term.SetC(stoi(nodes[i].substr(0, powIndex)));
			term.SetP(stoi(nodes[i].substr(powIndex + 1, nodes[i].length() - powIndex - 1)));
		}
		else
		{
			term.SetC(stoi(nodes[i].substr(1, powIndex)));
			term.SetP(stoi(nodes[i].substr(powIndex + 1, nodes[i].length() - powIndex - 1)));
		}
		this->AddTerm(term);
	}
}

