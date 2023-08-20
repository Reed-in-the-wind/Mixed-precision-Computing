// cite from https://blog.demofox.org/2014/12/30/dual-numbers-automatic-differentiation/
#include <cmath>
#include <iostream>
using namespace std;
 
#define PI 3.14159265359f
 
// it's vector type.
template <class Th, class T>
class DualNumber
{
private:
    T InitValue;
    size_t m_size;
    vector<T> m_real;
    vector<T> m_dual;
    vector<Th> m_abs;

public:
    // initialize.
    // Constructor 1.
    // define the vector size and InitValue.
    DualNumber (size_t size = 0, T value = (T)0.0): InitValue(value), m_size(size),
                              m_real(m_size, InitValue), m_dual(m_size, InitValue)
    {
    }
    // Constructor 2.
    // construct the class using input real and dual part vectors.
    DualNumber ( vector<T> &A, vector<T> &B )
    {
        for ( auto i = 0; i < A.size(); ++i ) {
            m_real.push_back(A[i]);
            m_dual.push_back(B[i]);
        }
        m_size = A.size();
        InitValue = (T)0.0;
    }
    /*
    DualNumber (DualNumber<Th, T> &A)
    {
        this->m_real(A.m_real);
        this->m_dual(A.m_dual);
        this->m_size = A.m_size;
        this->InitValue = A.InitValue;
        this->m_Abs
    }
    */
    // Constructor 3.
    // construct the class by spliting the initial high-precision vectors
    /*DualNumber ( vector<Th> C )
    {
        m_real = C;
        m_dual = C - m_real;
        m_size = C.size();
        InitValue = (T)0.0;
    }
    */
    // basic function
    vector<T> Real () { return m_real; }
    vector<T> Dual () { return m_dual; }
    size_t Size () const { return m_size; }
    T InitV() const { return InitValue; }
    //
    vector<Th> Get_Abs( ) {
        vector<Th> m_abs(m_size);
        for ( auto i = 0; i < m_size; ++i ) {
            m_abs[i] = (Th)m_real[i] + (Th)m_dual[i];
        }
        return m_abs;
    }
    vector<T> InitDualNumber( vector<Th> &A );
    DualNumber<Th, T> pow(size_t y);
    //
    // operator overloading.
    DualNumber<Th, T> operator + (const DualNumber<Th, T> &A) const;
    DualNumber<Th, T> operator - (const DualNumber<Th, T> &A) const;
    DualNumber<Th, T> operator * (const DualNumber<Th, T> &A) const;
    DualNumber<Th, T> operator / (const DualNumber<Th, T> &A) const;
    void operator += (const DualNumber<Th, T> &A) const;
    void operator -= (const DualNumber<Th, T> &A) const;
    void operator *= (const DualNumber<Th, T> &A) const;
    void operator /= (const DualNumber<Th, T> &A) const;
}; 
//----------------------------------------------------------------------
// Math Operations
//----------------------------------------------------------------------
template<class Th, class T>
inline DualNumber<Th, T> DualNumber<Th, T>::operator + (const DualNumber<Th, T> &A) const {
    vector<T> m_real0;
    vector<T> m_dual0;
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real0.push_back( (T)(m_real[i] + A.m_real[i]) );
        m_dual0.push_back( (T)(m_dual[i] + A.m_dual[i]) );
    }
    return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline DualNumber<Th, T> DualNumber<Th, T>::operator - (const DualNumber<Th, T> &A) const {
    vector<T> m_real0;
    vector<T> m_dual0;
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real0.push_back( (T)(m_real[i] - A.m_real[i]) );
        m_dual0.push_back( (T)(m_dual[i] - A.m_dual[i]) );
    }
    return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline DualNumber<Th, T> DualNumber<Th, T>::operator * (const DualNumber<Th, T> &A) const {
    vector<T> m_real0;
    vector<T> m_dual0;
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real0.push_back( (T)(m_real[i] * A.m_real[i]) );
        m_dual0.push_back( (T)(m_real[i] * A.m_dual[i] + m_dual[i] * A.m_dual[i]) );
    }
    return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline DualNumber<Th, T> DualNumber<Th, T>::operator / (const DualNumber<Th, T> &A) const {
    vector<T> m_real0;
    vector<T> m_dual0;
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real0.push_back( (T)(m_real[i] / A.m_real[i]) );
        m_dual0.push_back( (T)((m_dual[i]*A.m_real[i] - m_real[i]*A.m_dual[i]) / std::pow(A.m_real[i],2)) );
    }
    return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline void DualNumber<Th, T>::operator += (const DualNumber<Th, T> &A) const {
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real[i] += A.m_real[i];
        m_dual[i] += A.m_dual[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline void DualNumber<Th, T>::operator -= (const DualNumber<Th, T> &A) const {
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real[i] -= A.m_real[i];
        m_dual[i] -= A.m_dual[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline void DualNumber<Th, T>::operator *= (const DualNumber<Th, T> &A) const {
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real[i] *= A.m_real[i];
        m_dual[i] *= A.m_real[i];
        m_dual[i] += m_real[i] * A.m_dual[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline void DualNumber<Th, T>::operator /= (const DualNumber<Th, T> &A) const {
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real[i] /= A.m_real[i];
        m_dual[i] /= A.m_dual[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline DualNumber<Th, T> DualNumber<Th, T>::pow( size_t y)
{
    DualNumber<Th, T> pow_DN(this->m_real, this->m_dual);
    for ( auto i = 0; i < y; ++i ) {
        pow_DN *= this;
    }
    /*
    vector<T> m_real0;
    vector<T> m_dual0;
    for ( auto i = 0; i < m_size; ++i ) {
        m_real0.push_back( std::pow(m_real[i], y) );
        m_dual0.push_back( std::pow(m_dual[i], y) );
    }
    */
    //return DualNumber<Th, T>(m_real0, m_dual0);
    return pow_DN;
}
// addition of Dual Number Vectors
template <class Th, class T>
inline vector<T> DualNumber<Th, T>::InitDualNumber( vector<Th> &A ) {
    // input: a high precision vector A, do variable splitting ops.
    vector<T> temp(A.size());
    return temp;
}
//
template <class T>
inline vector<T> operator - ( const vector<T> &A, const vector<T> &B )
{
    vector<T> DualPart;
    for ( auto i = 0; i < A.size(); ++i ) {
        DualPart.push_back( A[i] - B[i] );
    }
    return DualPart;
}
template <class T>
inline vector<T> operator + ( const vector<T> &A, const vector<T> &B )
{
    vector<T> DualPart;
    for ( auto i = 0; i < A.size(); ++i ) {
        DualPart.push_back( A[i] + B[i] );
    }
    return DualPart;
}

//
/*
template <class Th, class T>
inline friend vector<T> operator = ( const vector<T> &A, const vector<Th> &B )
{
    for ( auto i = 0; i < A.size(); ++i ) {
        A[i] = (T)B[i];
    }
    return A;
}
*/
/*
//
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
