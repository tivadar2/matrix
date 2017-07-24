#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>

/**
 * \file   matrix.h
 * \Author Pongó Tivadar
 * \date   2014 December
 * \brief  A mátrix struktúra és a mátrixkönyvtár függvényei.
 *
 */

 /** \mainpage Mátrixfüggvénykönyvtár
 *
 * Programozta: Pongó Tivadar (IWOZY3)
 *
 * \section Függvények
 * \li \c InitMat(int width, int height, DefaultMatrixType type);
 * \li \c FreeMat(Matrix *mat);
 * \li \c CopyMat(Matrix *src, Matrix *dst);
 * \li \c PrintMat(Matrix *mat);
 * \li \c ReadMatFromFile(const char* path, Matrix *mat);
 * \li \c WriteMatToFile(const char* path, Matrix *mat);
 * \li \c AddMat(Matrix *a, Matrix *b, Matrix *res);
 * \li \c ScalarMulMat(double a, Matrix *mat, Matrix *res);
 * \li \c MulMat(Matrix *a, Matrix *b, Matrix *res);
 * \li \c InverseMat(Matrix *mat, Matrix *inv);
 *
 */

typedef enum {NULL_MATRIX, IDENTITY_MATRIX, UNDECLARED} DefaultMatrixType;

typedef struct {
    unsigned int width;
    unsigned int height;
    double **data;
} Matrix;
/** \struct Matrix matrix.h "matrix.h"
 *  \brief Mátrix struktúra
 *
 * Eltárolja a mátrix szélességét, magasságát és az elemeire mutató pointert.
 * A data pointer egy olyan tömbre mutat, amelyben a sorokra mutató pointerek vannak.
 */

/* Mátrix programozási mûveletei */

/** \brief Inicializálja a mátrixot
 * \details A mátrixot többféleképpen is inicializálhatjuk
 * ezek: NULL_MATRIX, IDENTITY_MATRIX, UNDECLARED, az alapértelmezett
 * az UNDECLARED
 *
 * \param width A mátrix kívánt szélessége, 0-nál nagyobb szám.
 * \param height A mátrix kívánt magassága, 0-nál nagyobb szám.
 *
 * \return A lefoglalt és inicializált mátrixot adja vissza, NULL pointert-t ha
 * a width vagy height 1-nél kisebb.
 */
Matrix* InitMat(int width, int height, DefaultMatrixType type);

/** \brief Felszabadítja a mátrixot
 * \details Használata hasonló a könyvtári free()-hez
 *
 * \param mat A felszabadítandó mátrixra mutató pointer.
 *
 * \return 0-val tér vissza
 */
int FreeMat(Matrix *mat);

/** \brief Mátrixot másol
 *
 * \param src Forrásmátrix
 * \param dst Célmátrix, előtte inicializálni kell InitMat()-al
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 A forrásmátrix üres(NULL)
 * \retval -2 A célmátrix üres(NULL)
 */
int CopyMat(Matrix *src, Matrix *dst);

/** \brief Kiírja a mátrixot a standard kimenetre
 *
 * \param mat A kiírandó mátrixra mutató pointer.
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 A kiírandó mátrix üres.
 */
int PrintMat(Matrix *mat);

/** \brief Mátrixot olvas be fájlból
 *
 * \param path Elérési útvonal, úgy kell megadni, mint a fopen()-nek.
 * \param mat A mátrix, amibe beolvassa a fájlból az adatokat.
 * Muszáj inicializálni előtte az InitMat()-al
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 Az célmátrix üres.
 */
int ReadMatFromFile(const char* path, Matrix *mat);

/** \brief Mátrixot fájlba ír
 *
 * \param path Elérési útvonal, úgy kell megadni, mint a fopen()-nek.
 * \param mat A mátrix, amit kiír a fájlba.
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 A kiírandó mátrix üres.
 */
int WriteMatToFile(const char* path, Matrix *mat);


/* Mátrixmûveletek */

/** \brief Két mátrixot összead
 *
 * \param a Egyik mátrix
 * \param b Másik mátrix
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 Valamelyik argumentumban szereplő mátrix  üres(NULL) volt.
 * \retval -2 Két különböző méretű mátrixot próbáltál összeadni.
 */
int AddMat(Matrix *a, Matrix *b, Matrix *res);

/** \brief Mátrixot skalárral szoroz
 *
 * \param a A skalár, amivel szorozni fogja a mátrixot.
 * \param mat A szorzandó mátrix.
 * \param res Az eredményre mutató pointer, előtte muszáj
 * inicializálni InitMat()-tal, de nem feltétlenül, úgyanolyan méretűre.
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 Az egyik mátrix üres.
 */
int ScalarMulMat(double a, Matrix *mat, Matrix *res);

/** \brief Két mátrixot összeszoroz
 *
 * \param a Egyik mátrix.
 * \param mat Másik mátrix.
 * \param res Az eredményre mutató pointer, előtte muszáj
 * inicializálni InitMat()-tal, de nem feltétlenül, a megfelelő méretűre.
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 Az egyik mátrix üres.
 * \retval -2 A két mátrixot nem lehetett összeszorozni, mert
 * az a matrix szélessége nem volt egyenlő a b mátrix magasságával.
 */
int MulMat(Matrix *a, Matrix *b, Matrix *res);

/** \brief Determináns számoló
 *
 * \details Gauss-eliminációval számolja ki a determinánst.
 *
 * \param mat A megadott négyzetmátrix
 *
 * \return A kiszámolt determináns, hiba esetén -1. Az stderr-be írja a hiba okát.
 *
 */
double DetMat(Matrix *mat);

/** \brief Inverzmátrix számító
 *
 * \details Gauss-eliminációs módszerrel számol inverzet.
 *
 * \param mat Az invertálandó négyzetmátrix
 * \param inv Az eredményre mutató pointer, előtte muszáj
 * inicializálni InitMat()-tal, de nem feltétlenül a megfelelő méretűre.
 *
 * \return Hiba esetén nem nulla.
 *
 * \retval 0 Nem történt hiba.
 * \retval -1 Az egyik mátrix üres.
 * \retval -2 A mátrix nem négyzetmátrix.
 * \retval -3 A mátrix determinánsa 0, tehát nem létezik inverze.
 */
int InverseMat(Matrix *mat, Matrix *inv);

#endif // MATRIX_H
