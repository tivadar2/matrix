#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/**
 * \file   test.c
 * \Author Pongó Tivadar
 * \date   2014 December
 * \brief  A mátrixfüggvénykönyvtár függvényeinek bemutatása
 *
 * \details Minden függvényt kipróbál/bemutat
 *
 */

int main(int argc, char *argv[])
{
    int i;
    /* 1 széles, 1 magas mátrixot adunk meg, mert
    nem tudjuk, milyen lesz a beolvasott mátrix mérete */
    Matrix *mat = InitMat(1, 1, UNDECLARED);
    Matrix *inverse = InitMat(1, 1, UNDECLARED);
    Matrix *res = InitMat(1, 1, UNDECLARED);
    Matrix *osszeg = InitMat(1, 1, UNDECLARED);
    Matrix *id = NULL;

    printf("Teszt\n\n");

    ReadMatFromFile("matrix.txt", mat);
    printf("Beolvasott matrix:\n");
    PrintMat(mat);

    printf("\nA beolvasott matrix determinansa: %f\n", DetMat(mat));

    InverseMat(mat, inverse);
    printf("\nA beolvasott matrix inverze:\n");
    PrintMat(inverse);

    AddMat(mat, inverse, res);
    printf("\nA ket matrix osszege:\n");
    CopyMat(res, osszeg);
    PrintMat(osszeg);

    MulMat(mat, inverse, res);
    printf("\nA ket matrix szorzata:\n");
    PrintMat(res);

    printf("\nMilyen nagy legyen az identitasmatrix: ");
    scanf("%d", &i);
    id = InitMat(i, i, IDENTITY_MATRIX);
    printf("Az adott meretu identitasmatrixot megszorozzuk 3.14-el:\n");
    ScalarMulMat(3.14, id, res);
    PrintMat(res);

    FreeMat(mat);
    FreeMat(inverse);
    FreeMat(res);
    FreeMat(osszeg);
    FreeMat(id);
    scanf("%d", &i);
    return 0;
}
