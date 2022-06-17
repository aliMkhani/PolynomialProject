#pragma once
#include <iostream>
#include <string>
using namespace std;
class Term
{
public:
	Term(float c, int p);
	Term();
	~Term();
	void SetC(float c) { this->c = c; }
	void SetP(int p) { this->p = p; }
	float GetC() { return this->c; }
	int GetP() { return this->p; }
	Term operator+(Term term);
	Term operator+(float x);
	Term operator-(Term term);
	Term operator-(float x);
	Term operator*(Term term);
	Term operator*(float x);
	Term operator/(Term term);
	Term operator/(float x);
	void operator+=(Term term);
	void operator-=(Term term);
	void operator*=(Term term);
	void operator/=(Term term);
	void operator=(Term term);
	bool operator>(Term term);
	bool operator>(float x);
	bool operator<(Term term);
	bool operator<(float x);
	bool operator>=(Term term);
	bool operator>=(float x);
	bool operator<=(Term term);
	bool operator<=(float x);
	bool operator==(Term term);
	bool operator==(float x);
	bool operator!=(Term term);
	bool operator!=(float x);
	Term operator~();
	void operator++();
	void operator--();
	float operator()(float x);
	friend ostream& operator<<(ostream& os, Term term);
	friend istream& operator>>(istream& os, Term* term);
	bool IsSymmetric(Term term);
	string ToString();
private:
	float c;
	int p;
};
ostream& operator<<(ostream& os, Term term)
{
	if (term.c == 0)
	{
		return os;
	}
	if (term.c < 0)
	{
		os << term.c << "x^" << term.p;
	}
	else
	{
		os << "+" << term.c << "x^" << term.p;
	}
	return os;
}
istream& operator>>(istream& is, Term* term)
{
	float c;
	int p;
	is >> c >> p;
	term->SetC(c);
	term->SetP(p);
	return is;
}
Term::Term(float c, int p)
{
	this->c = c;
	this->p = p;
}
Term::Term()
{
}
Term::~Term()
{
}
Term Term::operator+(Term term)
{
	if (this->p != term.p)
	{
		throw invalid_argument("the powers must be equal");
	}
	return Term(this->c + term.c, this->p);
}
Term Term::operator+(float x)
{
	if (this->p != 0)
	{
		throw invalid_argument("the powers must be equal");
	}
	return Term(this->c + x, this->p);
}
Term Term::operator-(Term term)
{
	if (this->p != term.p)
	{
		throw invalid_argument("the powers must be equal");
	}
	return Term(this->c - term.c, this->p);
}
Term Term::operator-(float x)
{
	if (this->p != 0)
	{
		throw invalid_argument("the powers must be equal");
	}
	return Term(this->c - x, this->p);
}
Term Term::operator*(Term term)
{
	return Term(this->c * term.c, this->p + term.p);
}
Term Term::operator*(float x)
{
	return Term(this->c * x, this->p);
}
Term Term::operator/(Term term)
{
	if (term.c <= 0)
	{
		throw invalid_argument("the coef can't be <= 0");
	}
	return Term(this->c / term.c, this->p - term.p);
}
Term Term::operator/(float x)
{
	if (x <= 0)
	{
		throw invalid_argument("the coef can't be <= 0");
	}
	return Term(this->c / x, this->p);
}
void Term::operator+=(Term term)
{
	if (this->p != term.p)
	{
		throw invalid_argument("the powers must be equal");
	}
	*this = Term(this->c + term.c, this->p);
}
void Term::operator-=(Term term)
{
	if (this->p != term.p)
	{
		throw invalid_argument("the powers must be equal");
	}
	*this = Term(this->c - term.c, this->p);
}
void Term::operator*=(Term term)
{
	*this = Term(this->c * term.c, this->p + term.p);
}
void Term::operator/=(Term term)
{
	if (term.c <= 0)
	{
		throw invalid_argument("the coef can't be <= 0");
	}
	*this = Term(this->c / term.c, this->p - term.p);
}
void Term::operator=(Term term)
{
	this->p = term.p;
	this->c = term.c;
}
bool Term::operator>(Term term)
{
	if (this->p > term.p)
	{
		return true;
	}
	else
	{
		return false;
	}
	return this->c > term.c;
}
bool Term::operator>(float x)
{
	if (this->p > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	return this->c > x;
}
bool Term::operator<(Term term)
{
	if (this->p < term.p)
	{
		return true;
	}
	else
	{
		return false;
	}
	return this->c < term.c;
}
bool Term::operator<(float x)
{
	if (this->p < 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	return this->c < x;
}
bool Term::operator>=(Term term)
{
	return *this > term || *this == term;
}
bool Term::operator>=(float x)
{
	return *this > x || *this == x;
}
bool Term::operator<=(Term term)
{
	return *this < term || *this == term;
}
bool Term::operator<=(float x)
{
	return *this < x || *this == x;
}
bool Term::operator==(Term term)
{
	return this->p == term.p && this->c == term.c;
}
bool Term::operator==(float x)
{
	return this->p == 0 && this->c == x;
}
bool Term::operator!=(Term term)
{
	return !(*this == term);
}
bool Term::operator!=(float x)
{
	return !(*this == x);
}
Term Term::operator~()
{
	return Term(this->c * this->p, this->p - 1);
}
void Term::operator++()
{
	*this = *this + 1;
}
void Term::operator--()
{
	*this = *this - 1;
}
float Term::operator()(float x)
{
	return pow(x, this->p) * this->c;
}
bool Term::IsSymmetric(Term term)
{
	if (this->c == -1 * term.c && this->p == term.p)
	{
		return true;
	}
	return false;
}
string Term::ToString()
{
	string term;
	if (this->c < 0)
	{
		term += to_string(this->c);
		term += "x^";
		term += to_string(this->p);
	}
	else
	{
		term += "+";
		term += to_string(this->c);
		term += "x^";
		term += to_string(this->p);
	}
	return term;
}

