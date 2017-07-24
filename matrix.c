#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * \file   matrix.c
 * \Author Pongó Tivadar
 * \date   2014 December
 * \brief  A mátrixkönyvtár függvényeinek definíciói.
 *
 */

Matrix* InitMat(int width, int height, DefaultMatrixType type)
{
    unsigned int i, j;

    if(width < 0 || height < 0)
    {
        fprintf(stderr, "A matrix szelessege es magassaga sem nem lehet kisebb, mint 1!\n");
        return NULL;
    }

    /* Memóriaterület lefoglalása a mátrix számára */
    Matrix *mat = (Matrix*)malloc(sizeof(Matrix));
    mat->data = (double**)malloc(height*sizeof(double*));
    for(i = 0;i < height;i++)
    {
        mat->data[i] = (double*)malloc(width*sizeof(double));
    }
    mat->width = width;
    mat->height = height;

    /* A mátrix alapértékének beállítása */
    switch(type)
    {
    case NULL_MATRIX:
        for(i = 0;i < height;i++)
        {
            for(j = 0;j < width;j++)
            {
                mat->data[i][j] = 0;
            }
        }
        break;
    case IDENTITY_MATRIX:
        /* Ha a mátrix nem négyzetmátrix, akkor a visszaadott mátrix a nullmátrix lesz! */
        for(i = 0;i < height;i++)
        {
            for(j = 0;j < width;j++)
            {
                mat->data[i][j] = 0;
            }
        }
        if(width == height)
        {
            for(i = 0;i < width;i++)
            {
                mat->data[i][i] = 1;
            }
        }
        else
        {
            /* A mátrix elemei nullákkal lesznek feltöltve */
            fprintf(stderr, "A matrix nem negyzetmatrix, ezert nem lehet egysegmatrix!\n");
        }
        break;
    case UNDECLARED:
        /* A mátrix elemei memóriaszeméttel lesznek megtöltve */
        break;
    default:
        /* Más alapérték is megadható */
        break;
    }
    return mat;
}

int FreeMat(Matrix *mat)
{
    if(mat == NULL)
        return 0;
    if(mat->data != NULL)
    {
        int i;
        for(i = 0;i < mat->height;i++)
        {
            free(mat->data[i]);
            mat->data[i] = NULL;
        }
        free(mat->data);
        mat->data = NULL;
    }
    free(mat);
    return 0;
}

int PrintMat(Matrix *mat)
{
    /* Ha a matrix ures */
    if(mat == NULL)
    {
        fprintf(stderr, "A matrix ures!\n");
        return -1;
    }

    int i, j;
    for(i = 0;i < mat->height;i++)
    {
        for(j = 0;j < mat->width;j++)
        {
            printf("%f ", mat->data[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int AddMat(Matrix *a, Matrix *b, Matrix *res)
{
    /* Ha az egyik mátrix üres */
    if(a == NULL || b == NULL || res == NULL)
    {
        fprintf(stderr, "Valamelyik argumentumban szereplo matrix  ures(NULL)!\n");
        return -1;
    }

    /* Ha a két mátrix nem ugyanolyan méretű */
    if(a->width != b->width || a->height != b->height)
    {
        fprintf(stderr, "Ket kulonbozo meretu matrixot nem lehet osszeadni!\n");
        return -2;
    }

    /* Ha az eredménymátrix nem ugyanolyan méretű, mint az összeadandóak */
    if(a->width != res->width || a->height != res->height)
    {
        int i, j;
        if(res->data != NULL)
        {
            for(i = 0;i < res->height;i++)
            {
                free(res->data[i]);
                res->data[i] = NULL;
            }
            free(res->data);
            res->data = NULL;
        }

        res->data = (double**)malloc(a->height*sizeof(double*));
        for(i = 0;i < a->height;i++)
        {
            res->data[i] = (double*)malloc(a->width*sizeof(double));
        }
        res->width = a->width;
        res->height = a->height;
    }

    int i, j;
    for(i = 0;i < a->height;i++)
    {
        for(j = 0;j < a->width;j++)
        {
            res->data[i][j] = a->data[i][j] + b->data[i][j];
        }
    }
    return 0;
}

int ScalarMulMat(double a, Matrix *mat, Matrix *res)
{
    if(mat == NULL || res == NULL)
    {
        fprintf(stderr, "Az egyik matrix ures!\n");
        return -1;
    }

    /* Ha az eredménymátrix nem ugyanolyan méretű, mint a szorzandó */
    if(mat->width != res->width || mat->height != res->height)
    {
        int i, j;
        if(res->data != NULL)
        {
            for(i = 0;i < res->height;i++)
            {
                free(res->data[i]);
                res->data[i] = NULL;
            }
            free(res->data);
            res->data = NULL;
        }

        res->data = (double**)malloc(mat->height*sizeof(double*));
        for(i = 0;i < mat->height;i++)
        {
            res->data[i] = (double*)malloc(mat->width*sizeof(double));
        }

        res->width = mat->width;
        res->height = mat->height;
    }

    unsigned int i, j;
    for(i = 0;i < mat->height;i++)
    {
        for(j = 0;j < mat->width;j++)
        {
            res->data[i][j] = a*mat->data[i][j];
        }
    }
    return 0;
}

int MulMat(Matrix *a, Matrix *b, Matrix *res)
{
    /* Ha az egyik mátrix üres */
    if(a == NULL || b == NULL || res == NULL)
    {
        fprintf(stderr, "Az egyik matrix ures!\n");
        return -1;
    }

    /* Ha a két mátrix nem szorozható össze */
    if(a->width != b->height)
    {
        fprintf(stderr, "A ket matrix nem szorozhato ossze, mert az a matrix szelessege nem egyenlo a b matrix magassagaval!\n");
        return -2;
    }

    /* Ha az eredménymátrix nem megfelelő méretű */
    if(res->width != b->width || res->height != a->height)
    {
        int i, j;
        if(res->data != NULL)
        {
            for(i = 0;i < res->height;i++)
            {
                free(res->data[i]);
                res->data[i] = NULL;
            }
            free(res->data);
            res->data = NULL;
        }

        res->data = (double**)malloc(a->height*sizeof(double*));
        for(i = 0;i < a->height;i++)
        {
            res->data[i] = (double*)malloc(b->width*sizeof(double));
        }
        for(i = 0;i < a->height;i++)
        {
            for(j = 0;j < b->width;j++)
            {
                res->data[i][j] = 0;
            }
        }
        res->width = b->width;
        res->height = a->height;
    }

    int i, j, k;
    for(i = 0;i < res->height;i++)
    {
        for(j = 0;j < res->width;j++)
        {
            for(k = 0;k < a->width;k++)
            {
                res->data[i][j] += a->data[i][k]*b->data[k][j];
            }
        }
    }
    return 0;
}

double DetMat(Matrix *mat)
{
    /* Ha a matrix ures */
    if(mat == NULL)
    {
        fprintf(stderr, "A matrix ures!\n");
        return -1;
    }
    /* Ha a matrix nem negyzetmatrix */
    if(mat->width != mat->height)
    {
        fprintf(stderr, "Csak negyzetmatrixnak van determinansa!\n");
        return -1;
    }

    double det;
    int i, j, n, k;
    double diff;   /* diff - az előző sor hányszorosát kell kivonni az adott sorból */
    Matrix *temp = InitMat(mat->width, mat->height, UNDECLARED);
    CopyMat(mat, temp);
    n = mat->width;
    for(k = 0;k < n-1;k++)
    {
        for(i = k+1;i < n;i++)
        {
            /* Ha a főátló adott eleme 0 */
            if(temp->data[k][k] == 0)
            {
                int lehetcsere = 0;
                int t;
                for(t = k+1;t < n;t++)
                {
                    if(temp->data[t][k] != 0)
                    {
                        double *tmp = temp->data[k];
                        temp->data[k] = temp->data[t];
                        temp->data[t] = tmp;
                        lehetcsere = 1;
                    }
                }
                if(!lehetcsere)
                    continue;
            }
            diff = temp->data[i][k]/temp->data[k][k];
            for(j = 0;j < n;j++)
            {
                temp->data[i][j] -= diff*temp->data[k][j];
            }
        }
    }
    det = 1;
    for(i = 0;i < n;i++)
    {
        det *= temp->data[i][i];
    }
    FreeMat(temp);
    return det;
}

int CopyMat(Matrix *src, Matrix *dst)
{
    int i;
    /* Ha a másolandó mátrix üres (NULL) */
    if(src == NULL)
    {
        fprintf(stderr, "A masolando matrix ures (NULL)!\n");
        return -1;
    }

    /* Ha a célmátrix üres (NULL) */
    if(dst == NULL)
    {
        fprintf(stderr, "A celmatrix ures (NULL), a matrixot inicializalnod kell!\n");
        return -2;
    }

    /* Ha a másolandó és a célmátrix mérete nem egyezik meg */
    if(src->width != dst->width || src->height != dst->height)
    {
        int i, j;
        if(dst->data != NULL)
        {
            for(i = 0;i < dst->height;i++)
            {
                free(dst->data[i]);
                dst->data[i] = NULL;
            }
            free(dst->data);
            dst->data = NULL;
        }

        dst->data = (double**)malloc(src->height*sizeof(double*));
        for(i = 0;i < src->height;i++)
        {
            dst->data[i] = (double*)malloc(src->width*sizeof(double));
        }

        dst->width = src->width;
        dst->height = src->height;
    }

    for(i = 0;i < src->height;i++)
    {
        memcpy(dst->data[i], src->data[i], src->width*sizeof(double));
    }
    return 0;
}

int ReadMatFromFile(const char* path, Matrix *mat)
{
    FILE *file;
    int i, j;
    int width, height;
    /* Ha célmátrix üres */
    if(mat == NULL)
    {
        fprintf(stderr, "A celmatrix ures(NULL)!\n");
        return -1;
    }

    file = fopen(path, "r+");
    fscanf(file, "%d %d", &width, &height);

    if(mat->width != width || mat->height != height)
    {
        int i, j;
        if(mat->data != NULL)
        {
            for(i = 0;i < mat->height;i++)
            {
                free(mat->data[i]);
                mat->data[i] = NULL;
            }
            free(mat->data);
            mat->data = NULL;
        }

        mat->data = (double**)malloc(height*sizeof(double*));
        for(i = 0;i < height;i++)
        {
            mat->data[i] = (double*)malloc(width*sizeof(double));
        }

        mat->width = width;
        mat->height = height;
    }

    for(i = 0;i < height;i++)
    {
        for(j = 0;j < width;j++)
        {
            fscanf(file, "%lf", &mat->data[i][j]);
        }
    }
    fclose(file);
    return 0;
}

int WriteMatToFile(const char* path, Matrix *mat)
{
    /* Ha a mátrix üres */
    if(mat == NULL)
    {
        fprintf(stderr, "A matrix ures(NULL)!\n");
        return -1;
    }

    FILE *file;
    int i, j;
    file = fopen(path, "w+");
    fprintf(file, "%d %d\n", mat->width, mat->height);
    for(i = 0;i < mat->height;i++)
    {
        for(j = 0;j < mat->width;j++)
        {
            fprintf(file, "%lf ", mat->data[i][j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
    return 0;
}

int InverseMat(Matrix *mat, Matrix *inv)
{
    /* Ha az egyik mátrix üres */
    if(mat == NULL || inv == NULL)
    {
        fprintf(stderr, "Az egyik matrix ures!\n");
        return -1;
    }

    /* Ha a matrix nem negyzetmatrix */
    if(mat->width != mat->height)
    {
        fprintf(stderr, "Csak negyzetmatrixnak van determinansa!\n");
        return -2;
    }

    /* Van-e egyáltalán inverze */
    if(DetMat(mat) == 0)
    {
        fprintf(stderr, "A matrixnak nincs inverze!\n");
        return -3;
    }
    /* Ha az inverzmátrix mérete nem egyezik a invertálandó mátrix méretével */
    if(mat->width != inv->width || mat->height != inv->height)
    {
        int i, j;
        if(inv->data != NULL)
        {
            for(i = 0;i < inv->height;i++)
            {
                free(inv->data[i]);
                inv->data[i] = NULL;
            }
            free(inv->data);
            inv->data = NULL;
        }

        inv->data = (double**)malloc(mat->height*sizeof(double*));
        for(i = 0;i < mat->height;i++)
        {
            inv->data[i] = (double*)malloc(mat->width*sizeof(double));
        }
        for(i = 0;i < mat->height;i++)
        {
            for(j = 0;j < mat->width;j++)
            {
                inv->data[i][j] = 0;
            }
        }
        for(i = 0;i < mat->width;i++)
        {
            inv->data[i][i] = 1;
        }
        inv->width = mat->width;
        inv->height = mat->height;
    }
    else /* Ha a mátrix mérete megegyezik az inverzmátrixéval */
    {
        int i, j;
        for(i = 0;i < inv->height;i++)
        {
            for(j = 0;j < inv->width;j++)
            {
                inv->data[i][j] = 0;
            }
        }
        for(i = 0;i < inv->width;i++)
        {
            inv->data[i][i] = 1;
        }
    }
    int i, j, n, k;
    double diff;   /* diff - az előző sor hányszorosát kell kivonni az adott sorból */
    Matrix *temp = InitMat(mat->width, mat->height, UNDECLARED);
    CopyMat(mat, temp);
    n = mat->width;

    /* Lépcsős alakra hozás */
    for(k = 0;k < n-1;k++)
    {
        for(i = k+1;i < n;i++)
        {
            /* Ha a főátló adott eleme 0 */
            if(temp->data[k][k] == 0)
            {
                int lehetcsere = 0;
                int t;
                for(t = k+1;t < n;t++)
                {
                    if(temp->data[t][k] != 0)
                    {
                        double *tmp = temp->data[k];
                        temp->data[k] = temp->data[t];
                        temp->data[t] = tmp;

                        tmp = inv->data[k];
                        inv->data[k] = inv->data[t];
                        inv->data[t] = tmp;
                        lehetcsere = 1;
                    }
                }
                if(!lehetcsere)
                    continue;
            }
            diff = temp->data[i][k]/temp->data[k][k];
            for(j = 0;j < n;j++)
            {
                temp->data[i][j] -= diff*temp->data[k][j];
                inv->data[i][j] -= diff*inv->data[k][j];
            }
        }
    }

    /* Redukált lépcsős alakra hozás */
    for(i = 0;i < n;i++)
    {
        double oszto = temp->data[i][i];
        for(j = 0;j < n && oszto != 1;j++)
        {
            temp->data[i][j] /= oszto;
            inv->data[i][j] /= oszto;
        }
    }

    /* Identitásmátrixra eliminálás */
    for(k = n-1;k > 0;k--)
    {
        for(i = 0;i < k;i++)
        {
            diff = temp->data[i][k]/temp->data[k][k];
            for(j = 0;j < n;j++)
            {
                temp->data[i][j] -= diff*temp->data[k][j];
                inv->data[i][j] -= diff*inv->data[k][j];
            }
        }
    }

    FreeMat(temp);
    return 0;
}
