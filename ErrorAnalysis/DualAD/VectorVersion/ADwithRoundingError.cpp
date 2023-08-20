#include <iostream>
#include <vector>
#include <Dualnumber.hpp>
using namespace std;

// define precision
using WORKING_PRECISION=double;
using BASE_PRECISION=float;

template<class Th, class T>
DualNumber<Th, T> quadfuncAD(DualNumber<Th, T> x) {
    // get the differentiation of quadratic function: f(x) = x + x^2.
    DualNumber<Th, T> DN(x);
    DN = x + x.pow( (size_t)2 );
    //DN = x + x + x;
    return DN;
}

int main (int argc, char **argv)
{
    vector<BASE_PRECISION> real(3,0);
    vector<BASE_PRECISION> dual(3,0);
    //DualNumber<WORKING_PRECISION, BASE_PRECISION> DN(real, dual);
    DualNumber<WORKING_PRECISION, BASE_PRECISION> DN(3, 10.0);
    DualNumber<WORKING_PRECISION, BASE_PRECISION> DN1(3, 15.0);
    DualNumber<WORKING_PRECISION, BASE_PRECISION> DN2;
    DN2 = DN - DN1;
    cout << "DN2:" << endl;
    for( auto i = 0; i < 3; ++i )
    {
        cout << (DN2.Real())[i] << endl;
    }
    vector<BASE_PRECISION> V1, V2;
    vector<WORKING_PRECISION> V;
    //V = DN.Get_Abs<WORKING_PRECISION, BASE_PRECISION>( );
    V = DN.Get_Abs();
    V1 = DN.Real();
    V2 = DN.Dual();
    cout << "Dual Number Vector Size: " << DN.Size() << endl;
    cout << "Dual Number Vector Initial Value: " << DN.InitV() << endl;
    for( auto i = 0; i < 3; ++i )
    {
        cout << V1[i] << "+" << V2[i] << "epsilon" << endl;
    }
    for( auto i = 0; i < 3; ++i )
    {
        cout << "Absolute value:" << V[i] << endl;
    }
    // test AD.
    vector<BASE_PRECISION> real_AD = {1.0, 2.0, 3.0, 4.0, 5.0};
    vector<BASE_PRECISION> dual_AD(5,1.0);
    DualNumber<WORKING_PRECISION, BASE_PRECISION> DN_1(real_AD, dual_AD);
    DualNumber<WORKING_PRECISION, BASE_PRECISION> DN_AD;
    DN_AD = quadfuncAD(DN_1);
    cout << "Value:    " << ", Differentiation:    " << endl;
    cout << "f(x) = x + x^2" << endl;
    for( auto i = 0; i < 5; ++i )
    {
        cout << "x=" << i << ": " << (DN_AD.Real())[i] << ",  " << (DN_AD.Dual())[i] << endl;
    }
    return 0;
}
