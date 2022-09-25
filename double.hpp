#include <iostream>
#include <cmath>

class Double
{
private:
    constexpr static double EPS = 1e-7;
    double cx;
public:
    Double(double x) : cx(x) {}

    Double operator*=(Double right) { return cx *= right.cx; }
    Double operator+=(Double right) { return cx += right.cx; }
    Double operator-=(Double right) { return cx += right.cx; }
    Double operator*(Double right) const;
    Double operator+(Double right) const;
    Double operator-(Double right) const;
    Double operator^(int deg) const;

    bool operator==(Double right) { return std::abs(cx - right.cx) < EPS; }
    bool operator<=(Double right) { return cx <= right.cx; }

    friend std::ostream& operator<<(std::ostream& out, const Double& num) { return out << num.cx; }
};

inline Double Double::operator*(Double right) const
{   
    Double result = *this;
    result *= right;
    return result;
}

inline Double Double::operator+(Double right) const
{   
    Double result = *this;
    result += right;
    return result;
}

inline Double Double::operator-(Double right) const
{   
    Double result = *this;
    result -= right;
    return result;
}

inline Double Double::operator^(int deg) const
{
    const Double& self = *this;

    if (deg == 0) return Double(1); 
    if ((deg & 1) != 0) return (self ^ (deg - 1)) * self;
    
    Double y = self ^ (deg / 2);

    return y * y;
}

