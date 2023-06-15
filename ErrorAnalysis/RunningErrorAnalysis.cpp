#include <iostream>
#include <vector>
#include <cmath>
#include <random>
using namespace std;
//
template<typename T>
void GenVec( vector<T> &q )
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    for ( auto i = 0; i < q.size(); ++i )
    {
        q[i] = dis(gen);
    }
}
//
template<typename T>
void InnerProduct( T *Results, vector<T> &A, vector<T> &B )
{
    auto N = A.size();
    *Results = 0.0;
    for( auto i = 0; i < A.size(); ++i )
    {
        *Results += A[i] * B[i];
    }
}
template<typename T>
void RunningErrorBoundofInnerProduct( T *RunningErrorBound, vector<T> &A, vector<T> &B, T URF )
{
    T s = 0.0;
    T miu = 0.0;
    T z = 0.0;
    //
    for ( auto i = 0; i < A.size(); ++i )
    {
        z = A[i] * B[i];
        s += z;
        miu += abs( s ) + abs( z );
    }
    *RunningErrorBound = miu * URF;
}
//
using float_type = float;
//
int main()
{
    auto N = 100; // vec length
    vector<float_type> A(N), B(N);
    //
    // initialize vector A and B.
    GenVec( A );
    GenVec( B );
    for ( auto i = 0; i < A.size(); ++i )
    {
        cout << A[i] << " " << endl;
    }
    //
    // standard solution.
    float_type Results = 0.0;
    InnerProduct( &Results, A, B );
    // running error bound.
    float_type RunningErrorBound = 0.0;
    /*if ( typeid(Results) == typeid(float) )
    {
        float_type URF = 5.96e-8;
    }
    else if( typeid(Results) == typeid(double) )
    {
        float_type URF = 1.11e-16;
    }
    */
    float_type URF = 5.96e-8;
    RunningErrorBoundofInnerProduct( &RunningErrorBound, A, B, URF );
    //
    // print.
    //cout << "For floating point type: " << typeid(Results) << endl;
    cout << "Standard Solution: " << Results << endl;
    cout << "Running Error Bound: " << RunningErrorBound << endl;
    cout << "Priori Error Bound: " << Results * N * URF << endl;
    return 0;
}
