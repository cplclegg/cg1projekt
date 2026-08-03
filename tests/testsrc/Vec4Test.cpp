//
// Created by tomnir on 08.07.26.
//
#include <iostream>
#include "../../include/Vec4.h"
#include <cmath>
using namespace std;

int parallel4Test()
{
    Vec4 a {1,2,3,4};
    Vec4 b {2,4,6,8};
    Vec4 c {1,3,2,4};
    bool parallelOK = a.isParallelTo(b);
    parallelOK = parallelOK && b.isParallelTo(a);
    bool notParallelOK = !(a.isParallelTo(c));
    notParallelOK = notParallelOK && !(c.isParallelTo(a));
    if (parallelOK && notParallelOK)
    {
        cout << "OK - isParallelTo() working correctly" << endl;
        return 0;
    } else
    {
        cout << "isParallelTo() not returning correct results" << endl;
        return 1;
    }
}

int copyConstTestVec4()
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
        return 0;
    } else
    {
        cout << "Copy-Constructor nicht ok." << endl;
        return 1;
    }
}

int equalsTestVec4()
{
    Vec4 vecA {1,1,1,1};
    Vec4 vecB {2,2,2,2};
    bool equal = vecA == vecA;
    bool nequal = vecA == vecB;
    bool equal2 = vecA != vecA; // should be false
    bool nequal2 = vecA != vecB; // should be true
    if (equal && !nequal && !equal2 && nequal2)
    {
        cout << "OK - Gleichheitsvergleich mit operator== ok." << endl;
        return 0;
    } else
    {
        cout << "Gleichheitsvergleich mit operator== nicht ok." << endl;
        return 1;
    }
}

int scalarMultTestVec4()
{
    Vec4 vecA {1,1,1,1};
    Vec4 vecB { vecA * 2 };
	Vec4 vecC { 3 * vecA };
	bool scalarRightOK = (vecB(0) == 2) && (vecB(1) == 2) && (vecB(2) == 2) && (vecB(3) == 2);
	bool scalarLeftOK  = (vecC(0) == 3) && (vecC(1) == 3) && (vecC(2) == 3) && (vecC(3) == 3);
    if (scalarRightOK && scalarLeftOK)
    {
        cout << "OK - Vektor-Skalar-Multiplikation ok." << endl;
        return 0;
    } else
    {
		cout << "Vektor-Skalar-Multiplikation nicht ok. Erwartet: 2 2 2 2. Erhalten: "
			 << vecB(0) << " " << vecB(1) << " " << vecB(2) << " " << vecC(3) << endl
	 		 << "Vektor-Skalar-Multiplikation nicht ok. Erwartet: 3 3 3 3. Erhalten: "
	 		 << vecC(0) << " " << vecC(1) << " " << vecC(2) << " " << vecC(3) << endl;
        return 1;
    }
}

int assignmentTestVec4()
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
        return 0;
    } else
    {
        cout << "Tiefe Kopie bei Zuweisung mit operator= nicht ok. Erwartet: 1 2 3 4. Erhalten: " << vecB(0) << " " << vecB(1) << " " << vecB(2) << " " << vecB(3) << endl;
        return 1;
    }

}

int addSubtractTestVec4()
{
    Vec4 vecA {4,3,2,1};
    Vec4 vecB {1,2,3,4};
    Vec4 vecC { vecA+vecB }; // 5 5 5 5
    int result = 0;
    if ( (vecC(0) - 5 < 0.001) && (vecC(1)-5<0.0001) && (vecC(2) - 5 < 0.0001) )
    {
        cout << "OK - Addition per operator+ ok." << endl;
    } else
    {
        cout << "Addition per operator+ nicht ok. Erwartet: 5 5 5 5. Erhalten: " << vecC(0) << " " << vecC(1) << " " << vecC(2) << " " << vecC(3) << endl;
        ++result;
    }
    Vec4 vecD = vecA - vecB; // 3 1 -1 -3
    if ( (vecD(0) - 3 < 0.0001) && (vecD(1) - 1 < 0.0001) && (vecD(2) + 1 < 0.0001) && (vecD(3) + 3 < 0.0001) )
    {
        cout << "OK - Subtraktion per operator- ok. " << endl;
    } else
    {
        cout << "Subtraktion per operator- nicht ok. Erwartet: 3 1 -1 -3. Erhalten: " << vecD(0) << " " << vecD(1) << " " << vecD(2) << " " << vecD(3) <<endl;
        ++result;
    }
    return result;
}

int lenTestVec4()
{
    Vec4 vecA {4,3,2,1}; // len: sqrt( 16+9+4+1=30 )
    GLfloat deviation = abs(vecA.getLength() - sqrt(30));
    if (deviation < 0.0001)
    {
        cout << "OK - Vec4.getLength() ok." << endl;
        return 0;
    } else
    {
        cout << "Vec4.getLength() nicht ok. Abweichung: " << deviation << endl;
        return 1;
    }
}

int scalarProdTestVec4()
{
    Vec4 vecA {4,3,2,1};
    Vec4 vecB {1,2,3,4};
    GLfloat scalarProduct {vecA*vecB}; // 4 + 3*2 + 2*3 + 4 = 20
    if (scalarProduct - 20 < 0.0001)
    {
        cout << "OK - Skalarprodukt per operator* ok." << endl;
        return 0;
    } else
    {
        cout << "Skalarprodukt per operator* nicht ok. Erwartet: 20. Erhalten: " << scalarProduct << endl;
        return 1;
    }
}

int operatorMinusTestVec4()
{
    Vec4 test { 1, 2, 3, 4};
    Vec4 negative = -test;
    bool correctResult = (negative(0) == -1 && negative(1) == -2 && negative(2) == -3 && negative(3) == -4);
    if (correctResult)
    {
        cout << "OK - operator- returns correct negative vector." << endl;
        return 0;
    } else
    {
        cout << "Negation with operator- not returning correct result. Vector: " << negative(0) << " " << negative(1) << " " << negative(2) << " " << negative(3) << endl;
        return 1;
    }
}

int normalizeTestVec4()
{
    Vec4 test {2, 2, 2, 2};
    test.normalize();
    bool normalizationCorrect = ( abs(test(0) - 0.5) < 0.0001 && abs(test(1) - 0.5) < 0.0001 && abs(test(2) - 0.5) < 0.0001 && abs(test(3) - 0.5) < 0.0001 );
    if (normalizationCorrect)
    {
        cout << "OK - normalize() correctly normalizing vector components." << endl;
        return 0;
    } else
    {
        cout << "normalize() not correctly normalizing vector component. Vector: " << test(0) << " " << test(1) << " " << test(2) << " " << test(3) << endl;
        return 1;
    }
}

int vec4Tests()
{
    cout << "Running tests for Class Vec4" << endl << endl;
    int result = 0;
    result += scalarProdTestVec4();
    result += lenTestVec4();
    result += addSubtractTestVec4();
    result += assignmentTestVec4();
    result += scalarMultTestVec4();
    result += equalsTestVec4();
    result += copyConstTestVec4();
    result += operatorMinusTestVec4();
    result += normalizeTestVec4();
    result += parallel4Test();
    cout << endl << "End of test results for Class Vec4" << endl << endl;
    return result;
}

