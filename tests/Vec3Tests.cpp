//
// Created by tomnir on 08.07.26.
//
#include <iostream>
#include "../types/Vec3.h"
#include <cmath>
using namespace std;

void copyConstTestVec3()
{
    Vec3 vecA {1,1,1};
    Vec3 vecB {vecA};
    bool afterConstructionEqual = vecA == vecB;
    for (int i = 0; i < 3; ++i)
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

void equalsTestVec3()
{
    Vec3 vecA {1,1,1};
    Vec3 vecB {2,2,2};
    bool equal = vecA == vecA;
    bool nequal = vecA == vecB;
    bool equal2 = vecA != vecA; // should be false
    bool nequal2 = vecA != vecB; // should be true
    if (equal && !nequal && !equal2 && nequal2)
    {
        cout << "OK - Gleichheitsvergleich mit operator== ok." << endl;
    } else
    {
        cout << "Gleichheitsvergleich mit operator== nicht ok." << endl;
    }
}

void scalarMultTestVec3()
{
    Vec3 vecA {1,1,1};
    Vec3 vecB { vecA * 2 };
	Vec3 vecC { 3 * vecA };
	bool scalarRightOK = (vecB(0) == 2) && (vecB(1) == 2) && (vecB(2) == 2);
	bool scalarLeftOK  = (vecC(0) == 3) && (vecC(1) == 3) && (vecC(2) == 3);
    if (scalarRightOK && scalarLeftOK)
    {
        cout << "OK - Vektor-Skalar-Multiplikation ok." << endl;
    } else
    {
        cout << "Vektor-Skalar-Multiplikation nicht ok. Erwartet: 2 2 2. Erhalten: "
			 << vecB(0) << " " << vecB(1) << " " << vecB(2) << endl
			 << "Vektor-Skalar-Multiplikation nicht ok. Erwartet: 3 3 3. Erhalten: "
			 << vecC(0) << " " << vecC(1) << " " << vecC(2) << endl;
    }
}

void assignmentTestVec3()
{
    Vec3 vecA {1,2,3};
    Vec3 vecB = vecA;
    for (int i = 0; i < 3; ++i)
    {
        vecA(i) = 0.0f;
    }
    if (vecB(0) == 1 && vecB(1) == 2 && vecB(2) == 3)
    {
        cout << "OK - Tiefe Kopie bei Zuweisung mit operator= ok." << endl;
    } else
    {
        cout << "Tiefe Kopie bei Zuweisung mit operator= nicht ok. Erwartet: 1 2 3. Erhalten: " << vecB(0) << " " << vecB(1) << " " << vecB(2) << endl;
    }

}

void addSubtractTestVec3()
{
    Vec3 vecA {3,2,1};
    Vec3 vecB {1,2,3};
    Vec3 vecC { vecA+vecB };
    if ( (vecC(0) - 4 < 0.001) && (vecC(1)-4<0.0001) && (vecC(2) - 4 < 0.0001) )
    {
        cout << "OK - Addition per operator+ ok." << endl;
    } else
    {
        cout << "Addition per operator+ nicht ok. Erwartet: 4 4 4. Erhalten: " << vecC(0) << " " << vecC(1) << " " << vecC(2) << endl;
    }
    Vec3 vecD = vecA - vecB;
    if ( (vecD(0) - 2 < 0.0001) && (vecD(1) < 0.0001) && (vecD(2) + 2 < 0.0001) )
    {
        cout << "OK - Subtraktion per operator- ok. " << endl;
    } else
    {
        cout << "Subtraktion per operator- nicht ok. Erwartet: 2 0 -2. Erhalten: " << vecD(0) << " " << vecD(1) << " " << vecD(2) << endl;
    }
}

void scalarProdTestVec3()
{
    Vec3 vecA {3,2,1};
    Vec3 vecB {1,2,3};
    GLfloat vecC { vecA.scalarProduct(vecB) };
    if (vecC - 10 < 0.000000001)
    {
        cout << "OK - Skalarprodukt per Vec3.scalarMult() ok." << endl;
    } else
    {
        cout << "Skalarprodukt per Vec3.scalarMult() nicht ok. Erwartet: 343. Erhalten: " << vecC << endl;
    }
}

void lenTestVec3()
{
    Vec3 vecA {3,2,1}; // len: sqrt( 9+4+1=14 )
    GLfloat deviation = abs(vecA.getLength() - sqrt(14));
    if (deviation < 0.0001)
    {
        cout << "OK - Vec3.getLength() ok." << endl;
    } else
    {
        cout << "Vec3.getLength() nicht ok. Abweichung: " << deviation << endl;
    }
}

void vectorProductTestVec3()
{
    Vec3 vecA {3,2,1};
    Vec3 vecB {1,2,3};
    Vec3 vecC { vecA*vecB };
    GLfloat vecC1 = vecC(0);
    GLfloat vecC2 = vecC(1);
    GLfloat vecC3 = vecC(2);
    if ( abs(vecC(0)+4) < 0.0001 && abs(vecC(1)-8) < 0.0001 && abs(vecC(2)+4) < 0.0001)
    {
        cout << "OK - Vektorprodukt per operator* ok." <<endl;
    } else
    {
        cout << "Vektorprodukt per operator* nicht ok. Erwartet: -4 / 8 / -4. Erhalten: " << vecC1 << " / " << vecC2 << " / " << vecC3 << endl;
    }
}

void operatorMinusTestVec3()
{
    Vec3 test { 1, 2, 3};
    Vec3 negative = -test;
    bool correctResult = (negative(0) == -1 && negative(1) == -2 && negative(2) == -3);
    if (correctResult)
    {
        cout << "OK - operator- returns correct negative vector." << endl;
    } else
    {
        cout << "Negation with operator- not returning correct result. Vector: " << negative(0) << " " << negative(1) << " " << negative(2) << endl;
    }
}

void normalizeTestVec3()
{
    Vec3 test {2, 2, 1};
    test.normalize();
    bool normalizationCorrect = ( abs(test(0) - 2.0/3.0) < 0.0001 && abs(test(1) - 2.0/3.0) < 0.0001 && abs(test(2) - 1.0/3.0) < 0.0001 );
    if (normalizationCorrect)
    {
        cout << "OK - normalize() correctly normalizing vector components." << endl;
    } else
    {
        cout << "normalize() not correctly normalizing vector component. Vector: " << test(0) << " " << test(1) << " " << test(2) << endl;
    }
}

void vec3Tests()
{
    cout << "Running tests for Class Vec3" << endl << endl;
    scalarProdTestVec3();
    lenTestVec3();
    vectorProductTestVec3();
    addSubtractTestVec3();
    assignmentTestVec3();
    scalarMultTestVec3();
    equalsTestVec3();
    copyConstTestVec3();
    operatorMinusTestVec3();
    normalizeTestVec3();
    cout << endl << "End of test results for Class Vec3" << endl << endl;
}

