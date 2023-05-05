#include "Fraction.hpp"
#include <limits>

using namespace ariel;
using namespace std;

int max_int = numeric_limits<int>::max();
int min_int = numeric_limits<int>::min();

void checkOverflow(double numerator, double denominator)
{
    if (numerator > max_int || numerator < min_int || denominator > max_int || denominator < min_int)
    {
        throw overflow_error("Overflow error");
    }
}

// constructor for fraction
Fraction::Fraction()
{
    this->numerator = 0;
    this->denominator = 1;
}
Fraction::Fraction(int numerator, int denominator)
{
    if (denominator == 0)
    {
        throw invalid_argument("Denominator can't be 0");
    }

    this->numerator = numerator;
    this->denominator = denominator;
    this->reduction();
}

// convert float to fraction
ariel::Fraction::Fraction(float fraction1)
{
    int numerator = round(fraction1 * 1000.0);
    int denominator = 1000;
    this->numerator = numerator;
    this->denominator = denominator;
    reduction();
}

// basic GCD function
int ariel::_gcd(int number1, int number2)
{
    if (number2 == 0)
        return number1;
    return _gcd(number2, number1 % number2);
}

// reduction function so we will get the fraction in reduced form
void ::ariel::Fraction::reduction()
{
    int mygcd = _gcd(this->numerator, this->denominator);
    this->numerator /= mygcd;
    this->denominator /= mygcd;
    if (this->denominator < 0 && this->numerator > 0) // if the denominator is negative, move the negative sign to the numerator
    {
        this->denominator = -this->denominator;
        this->numerator = -this->numerator;
    }
}

int Fraction::getNumerator() const
{
    return this->numerator;
}

int Fraction::getDenominator() const
{
    return this->denominator;
}

// all the needed operators (+,-,*,/...) between two fraction numbers and fraction float (in that order)
Fraction Fraction::operator+(Fraction fraction1) const
{
    double n1 = (double)this->numerator;
    double n2 = (double)fraction1.numerator;
    double d1 = (double)this->denominator;
    double d2 = (double)fraction1.denominator;

    double commonNumerator = n1 * d2 + n2 * d1;
    double commonDenominator = d1 * d2;

    checkOverflow(commonNumerator, commonDenominator);

    Fraction newfraction((int)commonNumerator, (int)commonDenominator);
    return newfraction;
}

Fraction Fraction::operator+(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return *this + floatFraction;
}

Fraction Fraction::operator-(Fraction fraction1) const
{
    double n1 = (double)this->numerator;
    double n2 = (double)fraction1.numerator;
    double d1 = (double)this->denominator;
    double d2 = (double)fraction1.denominator;

    double commonNumerator = n1 * d2 - n2 * d1;
    double commonDenominator = d1 * d2;

    checkOverflow(commonNumerator, commonDenominator);

    Fraction newfraction((int)commonNumerator, (int)commonDenominator);
    return newfraction;
}
Fraction Fraction::operator-(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return *this - floatFraction;
}
Fraction Fraction::operator*(Fraction fraction1) const
{
    double n1 = (double)this->numerator;
    double n2 = (double)fraction1.numerator;
    double d1 = (double)this->denominator;
    double d2 = (double)fraction1.denominator;

    double commonNumerator = n1 * n2;
    double commonDenominator = d1 * d2;

    checkOverflow(commonNumerator, commonDenominator);

    Fraction newfraction((int)commonNumerator, (int)commonDenominator);
    return newfraction;
}
Fraction Fraction::operator*(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return *this * floatFraction;
}

Fraction Fraction::operator/(Fraction fraction1) const
{
    if (fraction1.numerator == 0)
    {
        throw runtime_error("can't divide by 0");
    }
    double n1 = (double)this->numerator;
    double n2 = (double)fraction1.numerator;
    double d1 = (double)this->denominator;
    double d2 = (double)fraction1.denominator;

    double commonNumerator = n1 * d2;
    double commonDenominator = d1 * n2;

    checkOverflow(commonNumerator, commonDenominator);

    Fraction newfraction((int)commonNumerator, (int)commonDenominator);
    return newfraction;
}
Fraction Fraction::operator/(float fraction1) const
{
    if (fraction1 == 0.0)
    {
        throw runtime_error("can't divide by 0");
    }
    Fraction floatFraction(fraction1);
    return *this / floatFraction;
}
bool Fraction::operator==(Fraction fraction1) const
{
    if (this->numerator == 0 && fraction1.numerator == 0)
    {
        return true;
    }
    fraction1.reduction();
    return this->numerator == fraction1.numerator && this->denominator == fraction1.denominator;
}
bool Fraction::operator==(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return *this == floatFraction;
}
bool Fraction::operator>(Fraction fraction1) const
{
    Fraction result = *this - fraction1;
    return result.numerator > 0 && result.denominator > 0;
}
bool Fraction::operator>(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return (*this > floatFraction);
}
bool Fraction::operator<(Fraction fraction1) const
{
    Fraction result = *this - fraction1;
    return result.numerator < 0 || result.denominator < 0;
}
bool Fraction::operator<(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return (*this < floatFraction);
}
bool Fraction::operator>=(Fraction fraction1) const
{
    return *this > fraction1 || *this == fraction1;
}
bool Fraction::operator>=(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return (*this >= floatFraction);
}
bool Fraction::operator<=(Fraction fraction1) const
{
    return *this < fraction1 || *this == fraction1;
}
bool Fraction::operator<=(float fraction1) const
{
    Fraction floatFraction(fraction1);
    return (*this <= floatFraction);
}
// prefix ++
Fraction &Fraction::operator++()
{
    numerator += denominator;
    reduction();
    return *this;
}
// postfix ++
const Fraction Fraction::operator++(int)
{
    Fraction fraction1 = *this;
    numerator += denominator;
    reduction();
    return fraction1;
}
// prefix --
Fraction &Fraction::operator--()
{
    numerator -= denominator;
    reduction();
    return *this;
}
// postfix --
const Fraction Fraction::operator--(int)
{
    Fraction fraction1 = *this;
    numerator -= denominator;
    reduction();
    return fraction1;
}

ostream &ariel::operator<<(ostream &ostream, const Fraction &fraction)
{
    ostream << fraction.numerator << "/" << fraction.denominator;
    return ostream;
}

istream &ariel::operator>>(istream &istream, Fraction &fraction)
{
    int numerator, denominator;
    if (!(istream >> numerator >> denominator))
    {
        throw runtime_error("Can't get only one number");
    }
    if (denominator == 0)
    {
        throw runtime_error("Denominator can't be zero");
    }
    fraction.numerator = numerator;
    fraction.denominator = denominator;
    fraction.reduction();
    return istream;
}
// all the needed operators (+,-,*,/...)  float and fraction numbers (in that order)
Fraction ariel::operator+(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction + fraction2;
}
Fraction ariel::operator-(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction - fraction2;
}
Fraction ariel::operator*(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction * fraction2;
}
Fraction ariel::operator/(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction / fraction2;
}
bool ariel::operator==(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction == fraction2;
}
bool ariel::operator>(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction > fraction2;
}
bool ariel::operator<(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction < fraction2;
}
bool ariel::operator>=(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction >= fraction2;
}
bool ariel::operator<=(float fraction1, Fraction fraction2)
{
    Fraction floatFraction(fraction1);
    return floatFraction <= fraction2;
}
