// cite from https://blog.demofox.org/2014/12/30/dual-numbers-automatic-differentiation/
#include <cmath>
#include <iostream>
using namespace std;
 
#define PI 3.14159265359f
 
// it's vector type.
template <class T>
class DualNumber
{
private:
    T InitValue;
    size_t m_size;
    vector<T> m_real;
    vector<T> m_dual;
    vector<T> m_abs;

public:
    // initialize.
    // Constructor.
    DualNumber (size_t size = 0, T value = (T)0.0): InitValue(value), m_size(size), m_real(m_size, InitValue), m_dual(m_size, InitValue)
    {}
    
    // basic function
    vector<T> Real () { return m_real; }
    vector<T> Dual () { return m_dual; }
    size_t Size () const { return m_size; }
    T InitV() const { return InitValue; }
};
 
//----------------------------------------------------------------------
// Math Operations
//----------------------------------------------------------------------
template <class Th, class T>
inline vector<Th> Abs( DualNumber<T> &A ) {
    vector<Th> Abs(A.Size());
    vector<T> V1, V2;
    V1 = A.Real();
    V2 = A.Dual();
    for ( auto i = 0; i < Abs.size(); ++i ) {
        Abs[i] = (Th)V1[i] + (Th)V2[i];
    }
    return Abs;
}

/*
template <class T>
inline DualNumber<T> operator + (const DualNumber<T> &a, const DualNumber<T> &b)
{
    return DualNumber<T>(a.Real() + b.Real(), a.Dual() + b.Dual());
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
*/
/*
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
*/
/*
template<class T>
inline CDualNumber<T> SmoothStep (CDualNumber<T> x)
{
    // f(x) = 3x^2 - 2x^3
    // f'(x) = 6x - 6x^2
    return x * x * (CDualNumber<T>(3) - CDualNumber<T>(2) * x);
}

template<class T>
inline CDualNumber<T> SmoothStepv( CDualNumber<T> x )
{
    // the vector version of SmoothStep function.
    // f(x) = 3x^2 - 2x^3
    // f'(x) = 6x - 6x^2

}
*/
