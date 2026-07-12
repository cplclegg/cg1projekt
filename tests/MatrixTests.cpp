//
// Created by tomnir on 09.07.26.
//
#include <iostream>
#include <cmath>
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
    Mat4 xtest {};
    Mat4 ytest {};
    Mat4 ztest {};
    auto angle = (GLfloat) M_PI_2;
    Mat4 xcopy {xtest.rotateCopyX(angle)};
    Mat4 ycopy {ytest.rotateCopyY(angle)};
    Mat4 zcopy {ztest.rotateCopyZ(angle)};
    xtest.rotateX(angle);
    ytest.rotateY(angle);
    ztest.rotateZ(angle);

    bool xRotationOK = xtest(1,1) == cos(angle) && xtest(1,2) == sin(angle) && xtest(2,1) == -sin(angle) && xtest(2,2) == cos(angle);
    bool xRotCopyOK  = xcopy(1,1) == cos(angle) && xcopy(1,2) == sin(angle) && xcopy(2,1) == -sin(angle) && xcopy(2,2) == cos(angle);
    bool yRotationOK = ytest(0,0) == cos(angle) && ytest(2,0) == sin(angle) && ytest(0,2) == -sin(angle) && ytest(2,2) == cos(angle);
    bool yRotCopyOK  = ycopy(0,0) == cos(angle) && ycopy(2,0) == sin(angle) && ycopy(0,2) == -sin(angle) && ycopy(2,2) == cos(angle);
    bool zRotationOK = ztest(0,0) == cos(angle) && ztest(0,1) == sin(angle) && ztest(1,0) == -sin(angle) && ztest(1,1) == cos(angle);
    bool zRotCopyOK  = zcopy(0,0) == cos(angle) && zcopy(0,1) == sin(angle) && zcopy(1,0) == -sin(angle) && zcopy(1,1) == cos(angle);

    if (xRotationOK && xRotCopyOK && yRotationOK && yRotCopyOK && zRotationOK &&zRotCopyOK)
    {
        cout << "OK - Rotationsmatrizen ok." << endl;
    } else
    {
        cout << "Rotationsmatrizen nicht ok. x und xcopy: " << endl;
        xtest.directPrint();
        xcopy.directPrint();
        cout << endl << " y und ycopy: " << endl;
        ytest.directPrint();
        ycopy.directPrint();
        cout << endl << " z und zcopy: " << endl;
        ztest.directPrint();
        zcopy.directPrint();
        cout << endl;
    }

}

void lookAtTest ()
{
    Mat4 test {};
    Vec3 eye {2,1,3};
    Vec3 center {1,2,3};
    Vec3 up {1,1,1};
    Vec3 n {eye-center};
    Vec3 u {up*n};
    Vec3 v {n*u};
    n.normalize();
    u.normalize();
    v.normalize();
    Mat4 mrt {test.lookAtCopy(eye, center, up)};
    bool rotationOK = true;
    for (int i = 0; i < 3; ++i)
    {
        rotationOK = rotationOK && mrt(i,0) - u(i) < 0.001;
        rotationOK = rotationOK && mrt(i,1) - v(i) < 0.001;
        rotationOK = rotationOK && mrt(i,2) - n(i) < 0.001;
    }
    bool translationOK = u.scalarProduct(-eye) - 1.224 < 0.001;
    translationOK = translationOK && v.scalarProduct(-eye) - 3.462 < 0.001;
    translationOK = translationOK && n.scalarProduct(-eye) - 0.707 < 0.001;
    if (translationOK && rotationOK)
    {
        cout << "OK - lookAt() erstellt korrekte view-matrix." << endl;
    } else
    {
        cout << "lookAt() erzeugt falsche view-matrix. Matrix: " << endl;
        mrt.directPrint();
        cout << endl;
    }
}
void mat4Tests()
{
    cout << "Running tests for class Mat4" << endl << endl;
	translationTest();
    scaleTest();
    rotationTests();
    lookAtTest();
    cout << endl << "End of test results for class Mat4" << endl;
}