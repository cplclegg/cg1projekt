//
// Created by tomnir on 02.08.26.
//

#include <iostream>
#include <cmath>
#include "../../include/types.h"
using namespace std;

int determinantTest()
{
    Mat3 a {};

    a(0,0) = 1;
    a(1,0) = 2;
    a(2,0) = 1;

    a(0,1) = 0;
    a(1,1) = 1;
    a(2,1) = 3;

    a(0,2) = 0;
    a(1,2) = 0;
    a(2,2) = 1;

    auto det {a.determinant()};
    if (fabs(det - 1) < 0.00001)
    {
        cout << "OK - Determinante korrekt." << endl;
        return 0;
    } else
    {
        cout << "Determinante nicht korrekt. Erwartet: " << 15 << " Erhalten: " << det << endl;
        return 1;
    }

}

int equalsTest()
{
    Mat3 a {};
    Mat3 b {};

    bool selfEqual = a == a;
    bool otherEqual = a == b;
    if (selfEqual && otherEqual)
    {
        cout << "OK - gleichheitspruefung korrekt." << endl;
        return 0;
    } else
    {
        cout << "Gleichheitspruefung nicht korrekt." << endl;
        return 1;
    }
}

int isInvertibleTest()
{
    Mat3 a {};

    a(0,0)  = 1;
    a(1,0)  = 2;
    a(2,0)  = 1;

    a(0,1)  = 0;
    a(1,1)  = 1;
    a(2,1)  = 3;

    a(0,2)  = 0;
    a(1,2)  = 0;
    a(2,2)  = 1;


    bool invertibleCorrect = a.isInvertible(); // expect true
    for (size_t k = 0; k < 3; ++k)
    {
        a(k, 0) = 0.0f;
    }
    bool notInvertibleCorrect = a.isInvertible(); // expect false
    bool result = invertibleCorrect && !notInvertibleCorrect;
    if (result)
    {
        cout << "OK - invertierbarkeitspruefung korrekt." << endl;
        return 0;
    } else
    {
        cout << "Invertierbarkeitspruefung nicht korrekt." << endl;
        return 1;
    }
}

int invertTest()
{
    Mat3 a {};

    a(0,0)  = 1;
    a(1,0)  = 2;
    a(2,0)  = 1;

    a(0,1)  = 0;
    a(1,1)  = 1;
    a(2,1)  = 3;

    a(0,2)  = 0;
    a(1,2)  = 0;
    a(2,2)  = 1;

    Mat3 b {};

    b(0,0)  = 1;
    b(1,0)  = -2;
    b(2,0)  = 5;

    b(0,1)  = 0;
    b(1,1)  = 1;
    b(2,1)  = -3;

    b(0,2)  = 0;
    b(1,2)  = 0;
    b(2,2)  = 1;

    a.invert();

    if (a == b)
    {
        cout << "OK - invert() liefert korrekt inverse matrix." << endl;
        return 0;
    } else
    {
        cout << "Matrix-inverse per invert() nicht korrekt. Erwartet: " << endl;
        b.directPrint();
        cout << endl << "Erhalten: " << endl;
        a.directPrint();
        cout << endl;
        return 1;
    }
}

int transposeTest()
{
    Mat3 a {};
    Mat3 b {};

    a(0,0)  = 1;
    a(1,0)  = 2;
    a(2,0)  = 1;

    a(0,1)  = 0;
    a(1,1)  = 1;
    a(2,1)  = 3;

    a(0,2)  = 0;
    a(1,2)  = 0;
    a(2,2)  = 1;


    b(0,0)  = 1;
    b(1,0)  = 0;
    b(2,0)  = 0;

    b(0,1)  = 2;
    b(1,1)  = 1;
    b(2,1)  = 0;

    b(0,2)  = 1;
    b(1,2)  = 3;
    b(2,2)  = 1;

    a.transpose();
    if (a == b)
    {
        cout << "OK - transposition korrekt." << endl;
        return 0;
    } else
    {
        cout << "Transposition nicht korrekt. Erwartet: " << endl;
        b.directPrint();
        cout << endl << "Erhalten: " << endl;
        a.directPrint();
        cout << endl;
        return 1;
    }
}

int mat3Tests()
{
    cout << "Running tests for class Mat3" << endl << endl;
    int result = 0;
    result += isInvertibleTest();
    result += invertTest();
    result += transposeTest();
    result += equalsTest();
    result += determinantTest();
    cout << endl << "End of test results for class Mat3" << endl;
    return result;
}