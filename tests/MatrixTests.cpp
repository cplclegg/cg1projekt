//
// Created by tomnir on 09.07.26.
//
#include <iostream>
#include "../types/types.h"
using namespace std;

void accessorTest()
{
    Mat4 test {};

	for (size_t col = 0; col < 4; ++col) {
		for (size_t row = 0; row < 4; ++row) {
			test(col, row) = (double)(col+1)/(double)(row+1);
		}
	}
	test.directPrint();
}

void translationTest()
{
    Mat4 test {};
    Vec3 translator { 1,2,3 };
    Mat4 translatedCopy= test.translateCopy(translator);
    test.translate(translator);
    bool translateOK = true;
    bool translateCopyOK = true;
    for (size_t i = 0; i < 3; ++i)
    {
        translateOK = translateOK && test(3,i) == i+1;
        translateCopyOK = translateCopyOK && translatedCopy(3,i) == i+1;
    }
    for (size_t j = 0; j < 4; ++j)
    {
        translateOK = translateOK && test(j,j) == 1;
        translateCopyOK = translateCopyOK && translatedCopy(j,j) == 1;
    }
    if (translateOK && translateCopyOK)
    {
        cout << "OK - Translation und Translation von Kopie ok." << endl;
    } else
    {
        cout << "Translation nicht ok. Matrix:" << endl;
        test.directPrint();
        cout << "Kopiematrix: " << endl;
        translatedCopy.directPrint();
        cout << endl;
    }
}

void accessorParenthesesTest()
{
    Mat4 test {};
    cout << "Mat4test operator(). Constructor output: " << endl << test << endl;
    test(3,2) = 32;
    test(0,3) = 3;
    cout << "Altered Matrix: " << endl << test << endl;
}

void scaleTest()
{
    Mat4 test {};
    Vec3 sVector {2,3,4};
    Mat4 copy {test.scaleCopy(sVector)};
    test.scale(sVector);
    bool testOK = true;
    bool copyOK = true;
    for (size_t i = 0; i<3; ++i)
    {
        testOK = testOK && test(i,i) == sVector(i);
        copyOK = copyOK && copy(i,i) == sVector(i);
    }
    testOK = testOK && test(3,3) == 1;
    copyOK = copyOK && copy(3,3) == 1;
    if (testOK && copyOK)
    {
        cout << "OK - scale und scaleCopy ok." << endl;
    } else
    {
        cout << "scale und scaleCopy nicht ok. Matrix: " << endl;
        test.directPrint();
        cout << "Kopie: " << endl;
        copy.directPrint();
    }
}

void rotationTests()
{
    bool xRotationOK;
    bool yRotationOK;
    bool zRotationOK;
}

void mat4Tests()
{
    cout << "Running tests for class Mat4" << endl << endl;
	translationTest();
    scaleTest();
    cout << endl << "End of test results for class Mat4" << endl;
}