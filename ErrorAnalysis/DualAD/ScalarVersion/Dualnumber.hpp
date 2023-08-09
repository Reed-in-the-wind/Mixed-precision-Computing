// cite from https://blog.demofox.org/2014/12/30/dual-numbers-automatic-differentiation/
#include <cmath>
#include <iostream>
using namespace std;
 
#define PI 3.14159265359f
 
// In production code, this class should probably take a template parameter for
// it's scalar type instead of hard coding to float
template <class T>
class CDualNumber
{
public:
    CDualNumber (T real = 0.0f, T dual = 0.0f)
        : m_real(real)
        , m_dual(dual)
    {
    }
 
    T Real () const { return m_real; }
    T Dual () const { return m_dual; }
 
private:
    T m_real;
    T m_dual;
};
 
//----------------------------------------------------------------------
// Math Operations
//----------------------------------------------------------------------
template <class T>
inline CDualNumber<T> operator + (const CDualNumber<T> &a, const CDualNumber<T> &b)
{
    return CDualNumber<T>(a.Real() + b.Real(), a.Dual() + b.Dual());
}

template<class T>
inline CDualNumber<T> operator - (const CDualNumber<T> &a, const CDualNumber<T> &b)
{
    return CDualNumber<T>(a.Real() - b.Real(), a.Dual() - b.Dual());
}

template<class T>
inline CDualNumber<T> operator * (const CDualNumber<T> &a, const CDualNumber<T> &b)
{
    return CDualNumber<T>(
        a.Real() * b.Real(),
        a.Real() * b.Dual() + a.Dual() * b.Real()
    );
}

template<class T>
inline CDualNumber<T> operator / (const CDualNumber<T> &a, const CDualNumber<T> &b)
{
    return CDualNumber<T>(
        a.Real() / b.Real(),
        (a.Dual() * b.Real() - a.Real() * b.Dual()) / (b.Real() * b.Real())
    );
}

template<class T>
inline CDualNumber<T> sqrt (const CDualNumber<T> &a)
{
    T sqrtReal = sqrt(a.Real());
    return CDualNumber<T>( sqrtReal, 0.5f * a.Dual() / sqrtReal );
}

template<class T>
inline CDualNumber<T> pow (const CDualNumber<T> &a, T y)
{
    return CDualNumber<T>( pow(a.Real(), y), y * a.Dual() * pow(a.Real(), y - 1.0f)
    );
}

template<class T>
inline CDualNumber<T> sin (const CDualNumber<T> &a)
{
    return CDualNumber<T>( sin(a.Real()), a.Dual() * cos(a.Real()) );
}

template<class T>
inline CDualNumber<T> cos (const CDualNumber<T> &a)
{
    return CDualNumber<T>( cos(a.Real()), -a.Dual() * sin(a.Real()) );
}

template<class T>
inline CDualNumber<T> tan (const CDualNumber<T> &a)
{
    return CDualNumber<T>( tan(a.Real()), a.Dual() / (cos(a.Real()) * cos(a.Real())) );
}

template<class T>
inline CDualNumber<T> atan (const CDualNumber<T> &a)
{
    return CDualNumber<T>( atan(a.Real()), a.Dual() / (1.0f + a.Real() * a.Real()) );
}

template<class T>
inline CDualNumber<T> SmoothStep (CDualNumber<T> x)
{
    // f(x) = 3x^2 - 2x^3
    // f'(x) = 6x - 6x^2
    return x * x * (CDualNumber<T>(3) - CDualNumber<T>(2) * x);
}

template<class T>
inline CDualNumber<T> SmoothStepv( CDualNumber<T> &x )
{
    // the vector version of SmoothStep function.
    // f(x) = 3x^2 - 2x^3
    // f'(x) = 6x - 6x^2

}
