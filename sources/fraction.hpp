#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <numeric>
#include <iomanip>
#include <cmath>

namespace ariel
{
    class Fraction
    {
    private:
        int numerator;
        int denominator;

    public:
        Fraction();
        Fraction(int numerator, int denominator);
        Fraction(float fraction1);
        int getNumerator() const;
        int getDenominator() const;
        void reduction();
        Fraction operator+(Fraction fraction1) const;
        Fraction operator+(float fraction1) const;
        Fraction operator-(Fraction fraction1) const;
        Fraction operator-(float fraction1) const;
        Fraction operator*(Fraction fraction1) const;
        Fraction operator*(float fraction1) const;
        Fraction operator/(Fraction fraction1) const;
        Fraction operator/(float fraction1) const;
        bool operator==(Fraction fraction1) const;
        bool operator==(float fraction1) const;
        bool operator>(Fraction fraction1) const;
        bool operator>(float fraction1) const;
        bool operator<(Fraction fraction1) const;
        bool operator<(float fraction1) const;
        bool operator>=(Fraction fraction1) const;
        bool operator>=(float fraction1) const;
        bool operator<=(Fraction fraction1) const;
        bool operator<=(float fraction1) const;
        // i++
        const Fraction operator++(int);
        // ++i
        Fraction &operator++();
        // i--
        const Fraction operator--(int);
        //--i
        Fraction &operator--();

        friend std::ostream &operator<<(std::ostream &ostream, const Fraction &fraction);
        friend std::istream &operator>>(std::istream &istream, Fraction &fraction);

        friend Fraction operator+(float fraction1, Fraction fraction2);
        friend Fraction operator-(float fraction1, Fraction fraction2);
        friend Fraction operator*(float fraction1, Fraction fraction2);
        friend Fraction operator/(float fraction1, Fraction fraction2);
        friend bool operator==(float fraction1, Fraction fraction2);
        friend bool operator>(float fraction1, Fraction fraction2);
        friend bool operator<(float fraction1, Fraction fraction2);
        friend bool operator>=(float fraction1, Fraction fraction2);
        friend bool operator<=(float fraction1, Fraction fraction2);
    };
    int _gcd(int number1, int number2);

}

#endif