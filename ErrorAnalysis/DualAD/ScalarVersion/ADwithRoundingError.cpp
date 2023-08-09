#include <iostream>
#include <vector>
#include <Dualnumber.hpp>
using namespace std;
//----------------------------------------------------------------------
// Test Functions
//----------------------------------------------------------------------
template<class T>
void TestSmmothStepv( T &x )
{ 
}


template<class T>
void TestSmoothStep (T x)
{
    CDualNumber<T> y = SmoothStep(CDualNumber<T>(x, 1.0f));
    printf("smoothstep 3x^2-2x^3(%0.4f) = %0.4f\n", x, y.Real());
    printf("smoothstep 3x^2-2x^3'(%0.4f) = %0.4f\n\n", x, y.Dual());
}

template<class T>
void TestTrig (T x)
{
    CDualNumber<T> y = sin(CDualNumber<T>(x, 1.0f));
    printf("sin(%0.4f) = %0.4f\n", x, y.Real());
    printf("sin'(%0.4f) = %0.4f\n\n", x, y.Dual());

    y = cos(CDualNumber<T>(x, 1.0f));
    printf("cos(%0.4f) = %0.4f\n", x, y.Real());
    printf("cos'(%0.4f) = %0.4f\n\n", x, y.Dual());

    y = tan(CDualNumber<T>(x, 1.0f));
    printf("tan(%0.4f) = %0.4f\n", x, y.Real());
    printf("tan'(%0.4f) = %0.4f\n\n", x, y.Dual());

    y = atan(CDualNumber<T>(x, 1.0f));
    printf("atan(%0.4f) = %0.4f\n", x, y.Real());
    printf("atan'(%0.4f) = %0.4f\n\n", x, y.Dual());
}

template<class T>
void TestSimple (T x)
{
    CDualNumber<T> y = CDualNumber<T>(3.0f) / sqrt(CDualNumber<T>(x, 1.0f));
    printf("3/sqrt(%0.4f) = %0.4f\n", x, y.Real());
    printf("3/sqrt(%0.4f)' = %0.4f\n\n", x, y.Dual());

    y = pow(CDualNumber<T>(x, 1.0f) + CDualNumber<T>(1.0f), 1.337f);
    printf("(%0.4f+1)^1.337 = %0.4f\n", x, y.Real());
    printf("(%0.4f+1)^1.337' = %0.4f\n\n", x, y.Dual());
}

int main (int argc, char **argv)
{
    TestSmoothStep(0.5f);
    TestSmoothStep(0.75f);
    TestTrig(PI * 0.25f);
    TestSimple(3.0f);
    return 0;
}
