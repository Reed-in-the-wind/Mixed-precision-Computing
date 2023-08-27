#include <cmath>
#include <iostream>
using namespace std;
 
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
    DualNumber ( const vector<T> &A, const vector<T> &B )
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
        this->m_Abs(A.Abs);
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
    vector<T> Real () const { return m_real; }
    vector<T> Dual () const { return m_dual; }
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
    DualNumber<Th, T> pow(size_t y) const;
    //
    // operator overloading.
    DualNumber<Th, T> operator + (const DualNumber<Th, T> &A) const;
    DualNumber<Th, T> operator - (const DualNumber<Th, T> &A) const;
    DualNumber<Th, T> operator * (const DualNumber<Th, T> &A) const;
    DualNumber<Th, T> operator / (const DualNumber<Th, T> &A) const;
    void operator += (const DualNumber<Th, T> &A);
    void operator -= (const DualNumber<Th, T> &A);
    void operator *= (const DualNumber<Th, T> &A);
    void operator /= (const DualNumber<Th, T> &A);
};
//
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
        m_real0.push_back( (T)(this->m_real[i] - A.m_real[i]) );
        m_dual0.push_back( (T)(this->m_dual[i] - A.m_dual[i]) );
    }
    return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline DualNumber<Th, T> DualNumber<Th, T>::operator * (const DualNumber<Th, T> &A) const {
    vector<T> m_real0;
    vector<T> m_dual0;
    for ( auto i = 0; i < A.Size(); ++i ) {
        m_real0.push_back( (T)(this->m_real[i] * A.m_real[i]) );
        m_dual0.push_back( (T)(this->m_real[i] * A.m_dual[i] + this->m_dual[i] * A.m_real[i]) );
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
inline void DualNumber<Th, T>::operator += (const DualNumber<Th, T> &A) {
    for ( auto i = 0; i < A.Size(); ++i ) {
        this->m_real[i] += A.m_real[i];
        this->m_dual[i] += A.m_dual[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline void DualNumber<Th, T>::operator -= (const DualNumber<Th, T> &A) {
    for ( auto i = 0; i < A.Size(); ++i ) {
        this->m_real[i] -= A.m_real[i];
        this->m_dual[i] -= A.m_dual[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline void DualNumber<Th, T>::operator *= (const DualNumber<Th, T> &A) {
    
    for ( auto i = 0; i < A.Size(); ++i ) {
        //this->m_real[i] *= A.m_real[i];
        this->m_dual[i] *= A.m_real[i];
        this->m_dual[i] += this->m_real[i] * A.m_dual[i];
        this->m_real[i] *= A.m_real[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline void DualNumber<Th, T>::operator /= (const DualNumber<Th, T> &A) {
    for ( auto i = 0; i < A.Size(); ++i ) {
        this->m_real[i] /= A.m_real[i];
        this->m_dual[i] /= A.m_dual[i];
    }
    //return DualNumber<Th, T>( m_real0, m_dual0);
}
template<class Th, class T>
inline DualNumber<Th, T> DualNumber<Th, T>::pow( size_t y) const {
    DualNumber<Th, T> pow_DN(this->m_real, this->m_dual);
    for ( auto i = 1; i < y; ++i ) {
        pow_DN *= *this;
    }
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
