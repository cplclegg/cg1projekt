//
// Created by tomnir on 08.07.26.
//
#include <iostream>
#include "../types/Vec3.h"
#include <cmath>
using namespace std;

void scalarProdTest()
{
    Vec3 vecA {3,2,1};
    Vec3 vecB {1,2,3};
    GLfloat vecC { vecA.scalarProduct(vecB) };
    if (vecC - 10 < 0.000000001)
    {
        cout << "Skalarprodukt per operator* ok." << endl;
    } else
    {
        cout << "Skalarprodukt per operator* nicht ok. Erwartet: 343. Erhalten: " << vecC << endl;
    }
}

void lenTest()
{
    Vec3 vecA {3,2,1}; // len: sqrt( 9+4+1=14 )
    GLfloat deviation = abs(vecA.getLength() - sqrt(14));
    if (deviation < 0.0001)
    {
        cout << "Vec3.getLength() ok." << endl;
    } else
    {
        cout << "Vec3.getLength() nicht ok. Abweichung: " << deviation << endl;
    }

}

void vectorProductTest()
{
    Vec3 vecA {3,2,1};
    Vec3 vecB {1,2,3};
    Vec3 vecC { vecA*vecB };
    GLfloat vecC1 = vecC(0);
    GLfloat vecC2 = vecC(1);
    GLfloat vecC3 = vecC(2);
    if ( abs(vecC(0)+4) < 0.0001 && abs(vecC(1)-8) < 0.0001 && abs(vecC(2)+4) < 0.0001)
    {
        cout << "Vektorprodukt per operator* ok." <<endl;
    } else
    {
        cout << "Vektorprodukt per operator* nicht ok. Erwartet: -4 / 8 / -4. Erhalten: " << vecC1 << " / " << vecC2 << " / " << vecC3 << endl;
    }
}

int main()
{
    scalarProdTest();
    lenTest();
    vectorProductTest();
}

