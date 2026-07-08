//
// Created by tomnir on 08.07.26.
//
#include <iostream>
#include "../types/Vec4.h"
#include <cmath>
using namespace std;

void copyConstTestVec4()
{
    Vec4 vecA {1,1,1,1};
    Vec4 vecB {vecA};
    bool afterConstructionEqual = vecA == vecB;
    for (int i = 0; i < 4; ++i)
    {
        vecA(i) = 0;
    }
    bool afterAlterationEqual = vecA == vecB;
    if (afterConstructionEqual && !afterAlterationEqual)
    {
        cout << "OK - Copy-Constructor ok." << endl;
    } else
    {
        cout << "Copy-Constructor nicht ok." << endl;
    }
}

void equalsTestVec4()
{
    Vec4 vecA {1,1,1,1};
    Vec4 vecB {2,2,2,2};
    bool equal = vecA == vecA;
    bool nequal = vecA == vecB;
    if (equal && !nequal)
    {
        cout << "OK - Gleichheitsvergleich mit operator== ok." << endl;
    } else
    {
        cout << "Gleichheitsvergleich mit operator== nicht ok." << endl;
    }
}

void scalarMultTestVec4()
{
    Vec4 vecA {1,1,1,1};
    Vec4 vecB { vecA * 2 };
    if ( (vecB(0) == 2) && (vecB(1) == 2) && (vecB(2) == 2) && (vecB(3) == 2))
    {
        cout << "OK - Vektor-Skalar-Multiplikation ok." << endl;
    } else
    {
        cout << "Vektor-Skalar-Multiplikation nicht ok. Erwartet: 2 2 2 2. Erhalten: " << vecB(0) << " " << vecB(1) << " " << vecB(2) << " " << vecB(3) << endl;
    }
}

void assignmentTestVec4()
{
    Vec4 vecA {1,2,3,4};
    Vec4 vecB = vecA;
    for (int i = 0; i < 4; ++i)
    {
        vecA(i) = 0.0f;
    }
    if (vecB(0) == 1 && vecB(1) == 2 && vecB(2) == 3 && vecB(3) == 4)
    {
        cout << "OK - Tiefe Kopie bei Zuweisung mit operator= ok." << endl;
    } else
    {
        cout << "Tiefe Kopie bei Zuweisung mit operator= nicht ok. Erwartet: 1 2 3 4. Erhalten: " << vecB(0) << " " << vecB(1) << " " << vecB(2) << " " << vecB(3) << endl;
    }

}

void addSubtractTestVec4()
{
    Vec4 vecA {4,3,2,1};
    Vec4 vecB {1,2,3,4};
    Vec4 vecC { vecA+vecB }; // 5 5 5 5
    if ( (vecC(0) - 5 < 0.001) && (vecC(1)-5<0.0001) && (vecC(2) - 5 < 0.0001) )
    {
        cout << "OK - Addition per operator+ ok." << endl;
    } else
    {
        cout << "Addition per operator+ nicht ok. Erwartet: 5 5 5 5. Erhalten: " << vecC(0) << " " << vecC(1) << " " << vecC(2) << " " << vecC(3) << endl;
    }
    Vec4 vecD = vecA - vecB; // 3 1 -1 -3
    if ( (vecD(0) - 3 < 0.0001) && (vecD(1) - 1 < 0.0001) && (vecD(2) + 1 < 0.0001) && (vecD(3) + 3 < 0.0001) )
    {
        cout << "OK - Subtraktion per operator- ok. " << endl;
    } else
    {
        cout << "Subtraktion per operator- nicht ok. Erwartet: 3 1 -1 -3. Erhalten: " << vecD(0) << " " << vecD(1) << " " << vecD(2) << " " << vecD(3) <<endl;
    }
}

void lenTestVec4()
{
    Vec4 vecA {4,3,2,1}; // len: sqrt( 16+9+4+1=30 )
    GLfloat deviation = abs(vecA.getLength() - sqrt(30));
    if (deviation < 0.0001)
    {
        cout << "OK - Vec4.getLength() ok." << endl;
    } else
    {
        cout << "Vec4.getLength() nicht ok. Abweichung: " << deviation << endl;
    }
}

void scalarProdTestVec4()
{
    Vec4 vecA {4,3,2,1};
    Vec4 vecB {1,2,3,4};
    GLfloat scalarProduct {vecA*vecB}; // 4 + 3*2 + 2*3 + 4 = 20
    if (scalarProduct - 20 < 0.0001)
    {
        cout << "OK - Skalarprodukt per operator* ok." << endl;
    } else
    {
        cout << "Skalarprodukt per operator* nicht ok. Erwartet: 20. Erhalten: " << scalarProduct << endl;
    }
}

int main()
{
    scalarProdTestVec4();
    lenTestVec4();
    addSubtractTestVec4();
    assignmentTestVec4();
    scalarMultTestVec4();
    equalsTestVec4();
    copyConstTestVec4();

}

