#include <iostream>
#include <vector>
#include <Dualnumber.hpp>
using namespace std;

// define precision
using WORKING_PRECISION=double;
using BASE_PRECISION=float;

int main (int argc, char **argv)
{
    vector<BASE_PRECISION> real(3,0);
    vector<BASE_PRECISION> dual(3,0);
    //DualNumber<WORKING_PRECISION, BASE_PRECISION> DN(real, dual);
    DualNumber<WORKING_PRECISION, BASE_PRECISION> DN(3, 10.0);
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
    return 0;
}
