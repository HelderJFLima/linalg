// Various functions used in Linear Algebra and matrix operations.
//


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "linalg.h"

#define ERRMSS01 "memory allocation error!"                     // Common error messages
#define ERRMSS02 "NULL array informed!"
#define ERRMSS03 "error opening file!"
#define ERRMSS04 "NULL matrix informed!"
#define ERRMSS05 "incompatible dimensions for overwriting!"
// Last function number: 46

struct array
{
	int len;

	double *a;
};

struct matrix
{
	int row;

	int col;

	double **m;
};

// In-Out functions:

Array* create_array(int len)        // Creates an array with a given length.
{
    Array *ar;

    if (len <= 0)
    {
        error_message_la(1, "incompatible dimension for an array!");

        return NULL;
    }

    ar = malloc(sizeof(Array));

    if (ar == NULL)
    {
        error_message_la(1, ERRMSS01);

        exit(1);
    }

    ar->a = calloc(len, sizeof(double));

    if (ar->a == NULL)
    {
        error_message_la(1, ERRMSS01);

        exit(1);
    }

    ar->len = len;

    return ar;
}

void free_array(Array *arr)         // Deallocates memory previously used for an array.
{
    if (arr != NULL)
    {
        free(arr->a);

        free(arr);
    }
}

int length_of_array(Array *arr)     // Gives the length of an array.
{
    if (arr == NULL)
        return 0;
    else
        return arr->len;
}

void insert_in_array(double a, Array *arr, int pos)     // Inserts a value in an array in a given position.
{
    if (arr == NULL)
    {
        error_message_la(2, ERRMSS02);

        return;
    }
    else if (pos < 0 || pos >= arr->len)
    {
        error_message_la(2, "inexistent position in the array!");

        return;
    }

    arr->a[pos] = a;
}

double get_from_array(Array *arr, int pos)      // Gets a value in an array from a given position.
{
    if (arr == NULL)
    {
        error_message_la(3, ERRMSS02);

        return 0;
    }
    else if (pos < 0 || pos >= arr->len)
    {
        error_message_la(3, "inexistent position in the array!");

        return 0;
    }

    return arr->a[pos];
}

Array* get_array(char *name)        // Get an array from a 'txt' file.
{
    register int i;
    int len;

    FILE *filin;
    Array *ar;

    filin = fopen(name, "r");

    if (filin == NULL)
    {
        error_message_la(4, ERRMSS03);

        exit(4);
    }

    fscanf(filin, "%d", &len);

    ar = create_array(len);

    for (i = 0; i < len; i++)
        fscanf(filin, " %lf", &ar->a[i]);

    fclose(filin);

    return ar;
}

void print_array(Array *arr)        // Shows an array on the screen.
{
    register int i;

    if (arr == NULL)
    {
        printf("\n\nNULL array informed to print!\n");

        return;
    }

    printf("\n\n");

    for (i = 0; i < arr->len; i++)
        printf("%lf\t", arr->a[i]);

    printf("\n");
}

Matrix* create_matrix(int m, int n)         // Creates a matrix with given dimensions.
{
    register int i;

    Matrix *mat;

    if (m <= 0 || n <= 0)
    {
        error_message_la(5, "incompatible dimensions for a matrix!");

        return NULL;
    }

    mat = malloc(sizeof(Matrix));

    if (mat == NULL)
    {
        error_message_la(5, ERRMSS01);

        exit(5);
    }

    mat->row = m;

    mat->col = n;

    mat->m = calloc(m, sizeof(double*));

    if (mat->m == NULL)
    {
        error_message_la(5, ERRMSS01);

        exit(5);
    }

    for (i = 0; i < m; i++)
    {
        mat->m[i] = calloc(n, sizeof(double));

        if (mat->m[i] == NULL)
        {
            error_message_la(5, ERRMSS01);

            exit(5);
        }
    }

    return mat;
}

Matrix* create_identity_matrix(int ord)     // Creates an identity matrix of a given order.
{
    register int i, j;

    Matrix *mat;

    if (ord <= 0)
    {
        error_message_la(6, "invalid order value informed for a matrix!");

        return NULL;
    }

    mat = create_matrix(ord, ord);

    for (i = 0; i < ord; i++)
    {
        for (j = 0; j < ord; j++)
        {
            if (i == j)
                mat->m[i][j] = 1;
            else
                mat->m[i][j] = 0;
        }
    }

    return mat;
}

void free_matrix(Matrix *mat)       // Deallocates memory previously used for a matrix.
{
    if (mat != NULL)
    {
        register int i;

        for (i = 0; i < mat->row; i++)
            free(mat->m[i]);

        free(mat->m);

        free(mat);
    }
}

int matrix_row_number(Matrix *mat)      // Gives the number of rows of a matrix.
{
    if (mat == NULL)
        return 0;
    else
        return mat->row;
}

int matrix_column_number(Matrix *mat)   // Gives the number of columns of a matrix.
{
    if (mat == NULL)
        return 0;
    else
        return mat->col;
}

void insert_in_matrix(double a, Matrix *mat, int i, int j)      // Inserts a value in a matrix in a given position.
{
    if (mat == NULL)
    {
        error_message_la(7, ERRMSS04);

        return;
    }
    else if (i < 0 || i >= mat->row || j < 0 || j >= mat->col)
    {
        error_message_la(7, "inexistent position in the matrix!");

        return;
    }

    mat->m[i][j] = a;
}

double get_from_matrix(Matrix *mat, int i, int j)           // Gets a value in a matrix from a given position.
{
    if (mat == NULL)
    {
        error_message_la(8, ERRMSS04);

        return 0;
    }
    else if (i < 0 || i >= mat->row || j < 0 || j >= mat->col)
    {
        error_message_la(8, "inexistent position in the matrix!");

        return 0;
    }

    return mat->m[i][j];
}

Matrix* get_matrix(char *name)      // Get a matrix from a 'txt' file.
{
    register int i, j;
    int m, n;

    Matrix *mat;
    FILE *filin;

    filin = fopen(name, "r");

    if (filin == NULL)
    {
        error_message_la(9, ERRMSS03);

        exit(9);
    }

    fscanf(filin, "%dx%d", &m, &n);

    mat = create_matrix(m, n);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            fscanf(filin, " %lf", &mat->m[i][j]);
    }

    fclose(filin);

    return mat;
}

void print_matrix(Matrix *mat)      // Shows a matrix on the screen.
{
    register int i, j;

    if (mat == NULL)
    {
        printf("\n\nNULL matrix informed to print!\n");

        return;
    }

    printf("\n\n");

    for (i = 0; i < mat->row; i++)
    {
        for (j = 0; j < mat->col; j++)
            printf("%lf\t", mat->m[i][j]);

        printf("\n");
    }
}

static void error_message_la(int nmbr, char *mssg)  // Shows an error message indicating the function from where it came.
{
    if (mssg == NULL)
    {
        error_message_la(0, "NULL string informed!");

        return;
    }

    printf("\n\n** Error **\n** [LA%04d]: %s **\n\a", nmbr, mssg);
}

// Copy functions:

Array* copy_array(Array *arr)       // Copies an array as a new one.
{
    register i;
    Array *arrcp;

    if (arr == NULL)
    {
        error_message_la(10, ERRMSS02);

        return NULL;
    }

    arrcp = create_array(arr->len);

    for (i = 0; i < arr->len; i++)
        arrcp->a[i] = arr->a[i];

    return arrcp;
}

void over_copy_array(Array *cpy, Array *pst)        // Copies an array in a pre-existing one, overwriting it.
{
    register i;

    if (cpy == NULL || pst == NULL)
    {
        error_message_la(11, ERRMSS02);

        return;
    }
    else if (cpy->len != pst->len)
    {
        error_message_la(11, ERRMSS05);

        printf("\nThe destination array must have the same number of elements of the original one.\n");

        exit(11);
    }

    for (i = 0; i < cpy->len; i++)
        pst->a[i] = cpy->a[i];
}

Matrix* copy_matrix(Matrix *mat)        // Copies a matrix as a new one.
{
    register i, j;
    Matrix *matcp;

    if (mat == NULL)
    {
        error_message_la(12, ERRMSS04);

        return NULL;
    }

    matcp = create_matrix(mat->row, mat->col);

    for (i = 0; i < mat->row; i++)
    {
        for (j = 0; j < mat->col; j++)
            matcp->m[i][j] = mat->m[i][j];
    }

    return matcp;
}

void over_copy_matrix(Matrix *cpy, Matrix *pst)     // Copies a matrix in a pre-existing one, overwriting it.
{
    register i, j;

    if (cpy == NULL || pst == NULL)
    {
        error_message_la(13, ERRMSS04);

        return;
    }
    else if (cpy->row != pst->row || cpy->col != pst->col)
    {
        error_message_la(13, ERRMSS05);

        printf("\nThe destination matrix must have the same number of rows and columns of the original one.\n");

        exit(13);
    }

    for (i = 0; i < cpy->row; i++)
    {
        for (j = 0; j < cpy->col; j++)
            pst->m[i][j] = cpy->m[i][j];
    }
}

// Arithmetic operation functions:

Array* sum_array(Array *a, Array *b)            // Sums two arrays and saves the result as a new one.
{
    register int i;

    Array *ar;

    if (a == NULL || b == NULL)
    {
        error_message_la(14, ERRMSS02);

        return NULL;
    }

    if (a->len != b->len)                           // Tests the compatibility of dimensions.
    {
        error_message_la(14, "incompatible dimensions for an array sum!");

        return NULL;
    }

    ar = create_array(a->len);

    for (i = 0; i < ar->len; i++)
        ar->a[i] = a->a[i] + b->a[i];

    return ar;
}

Array* subtract_array(Array *a, Array *b)       // Subtracts two arrays and saves the result as a new one.
{
    register int i;

    Array *ar;

    if (a == NULL || b == NULL)
    {
        error_message_la(15, ERRMSS02);

        return NULL;
    }

    if (a->len != b->len)                           // Tests the compatibility of dimensions.
    {
        error_message_la(15, "incompatible dimensions for an array subtraction!");

        return NULL;
    }

    ar = create_array(a->len);

    for (i = 0; i < ar->len; i++)
        ar->a[i] = a->a[i] - b->a[i];

    return ar;
}

Array* rnumber_times_array(double num, Array *arr)  // Multiplies a real number by an array and saves the result as a new array.
{
    register int i;

    Array *ar;

    if (arr == NULL)
    {
        error_message_la(16, ERRMSS02);

        return NULL;
    }

    ar = create_array(arr->len);

    for (i = 0; i < ar->len; i++)
        ar->a[i] = num * arr->a[i];

    return ar;
}

Array* array_times_matrix(Array *arr, Matrix *mat)      // Multiplies an array by a matrix and saves the result as a new array.
{
    register int i, j;

    Array *ar;

    if (arr == NULL)
    {
        error_message_la(17, ERRMSS02);

        return NULL;
    }
    else if (mat == NULL)
    {
        error_message_la(17, ERRMSS04);

        return NULL;
    }

    if (arr->len != mat->row)                               // Tests the compatibility of dimensions.
    {
        error_message_la(17, "incompatible dimensions for an array-matrix multiplication!");

        return NULL;
    }

    ar = create_array(mat->col);

    for (j = 0; j < mat->col; j++)
    {
        ar->a[j] = 0;

        for (i = 0; i < mat->row; i++)
            ar->a[j] += arr->a[i] * mat->m[i][j];     
    }

    return ar;
}

Array* matrix_times_array(Matrix *mat, Array *arr)      // Multiplies a matrix by an array and saves the result as a new array.
{
    register int i, j;

    Array *ar;

    if (arr == NULL)
    {
        error_message_la(18, ERRMSS02);

        return NULL;
    }
    else if (mat == NULL)
    {
        error_message_la(18, ERRMSS04);

        return NULL;
    }

    if (mat->col != arr->len)                               // Tests the compatibility of dimensions.
    {
        error_message_la(18, "incompatible dimensions for a matrix-array multiplication!");

        return NULL;
    }

    ar = create_array(mat->row);

    for (i = 0; i < mat->row; i++)
    {
        ar->a[i] = 0;

        for (j = 0; j < mat->col; j++)
            ar->a[i] += mat->m[i][j] * arr->a[j];
    }

    return ar;
}

void over_sum_array(Array *a, Array *b)     // Sums two arrays and overwrites the result in the first one.
{
    register int i;

    if (a == NULL || b == NULL)
    {
        error_message_la(19, ERRMSS02);

        return;
    }

    if (a->len != b->len)                       // Tests the compatibility of dimensions.
    {
        error_message_la(19, "incompatible dimensions for an array sum!");

        return;
    }

    for (i = 0; i < a->len; i++)
        a->a[i] += b->a[i];
}

void over_subtract_array(Array *a, Array *b)        // Subtracts two arrays and overwrites the result in the first one.
{
    register int i;

    if (a == NULL || b == NULL)
    {
        error_message_la(20, ERRMSS02);

        return NULL;
    }

    if (a->len != b->len)                               // Tests the compatibility of dimensions.
    {
        error_message_la(20, "incompatible dimensions for an array subtraction!");

        return;
    }

    for (i = 0; i < a->len; i++)
        a->a[i] -= b->a[i];
}

void over_rnumber_times_array(double num, Array *arr)       // Multiplies a real number by an array and overwrites the result in the original array.
{
    register int i;

    if (arr == NULL)
    {
        error_message_la(21, ERRMSS02);

        return;
    }

    for (i = 0; i < arr->len; i++)
        arr->a[i] *= num;
}

void over_array_times_matrix(Array *arr, Matrix *mat)       // Multiplies an array by a matrix and overwrites the result in the first one.
{
    register int i, j;

    Array *tempar;

    if (arr == NULL)
    {
        error_message_la(22, ERRMSS02);

        return;
    }
    else if (mat == NULL)
    {
        error_message_la(22, ERRMSS04);

        return;
    }

    if (arr->len != mat->row)                   // Tests the compatibility of dimensions.
    {
        error_message_la(22, "incompatible dimensions for an array-matrix multiplication!");

        return;
    }
    else if (mat->row != mat->col)                  // Only works if the matrix is square.
    {
        error_message_la(22, ERRMSS05);

        printf("\nThe matrix must have the same number of rows and columns.\n");

        return;
    }

    tempar = create_array(arr->len);

    for (j = 0; j < mat->col; j++)              // Multiplication
    {
        tempar->a[j] = 0;

        for (i = 0; i < mat->row; i++)
            tempar->a[j] += arr->a[i] * mat->m[i][j];
    }

    over_copy_array(tempar, arr);               // Overwriting

    free_array(tempar);
}

void over_matrix_times_array(Matrix *mat, Array *arr)   // Multiplies a matrix by an array and overwrites the result in the second one.
{
    register int i, j;

    Array *tempar;

    if (arr == NULL)
    {
        error_message_la(23, ERRMSS02);

        return;
    }
    else if (mat == NULL)
    {
        error_message_la(23, ERRMSS04);

        return;
    }

    if (mat->col != arr->len)                   // Tests the compatibility of dimensions.
    {
        error_message_la(23, "incompatible dimensions for a matrix-array multiplication!");

        return;
    }
    else if (mat->row != mat->col)                  // Only works if the matrix is square.
    {
        error_message_la(23, ERRMSS05);

        printf("\nThe matrix must have the same number of rows and columns.\n");

        return;
    }

    tempar = create_array(arr->len);

    for (i = 0; i < mat->row; i++)              // Multiplication
    {
        tempar->a[i] = 0;

        for (j = 0; j < mat->col; j++)
            tempar->a[i] += mat->m[i][j] * arr->a[j];
    }

    over_copy_array(tempar, arr);               // Overwriting

    free_array(tempar);
}

Matrix* sum_matrix(Matrix *a, Matrix *b)            // Sums two matrixes and saves the result as a new one.
{
    register int i, j;

    Matrix *mat;

    if (a == NULL || b == NULL)
    {
        error_message_la(24, ERRMSS04);

        return NULL;
    }

    if (a->row != b->row || a->col != b->col)           // Tests the compatibility of dimensions.
    {
        error_message_la(24, "incompatible dimensions for a matrix sum!");

        return NULL;
    }

    mat = create_matrix(a->row, a->col);

    for (i = 0; i < mat->row; i++)
    {
        for (j = 0; j < mat->col; j++)
            mat->m[i][j] = a->m[i][j] + b->m[i][j];
    }

    return mat;
}

Matrix* subtract_matrix(Matrix *a, Matrix *b)       // Subtracts two matrixes and saves the result as a new one.
{
    register int i, j;

    Matrix *mat;

    if (a == NULL || b == NULL)
    {
        error_message_la(25, ERRMSS04);

        return NULL;
    }

    if (a->row != b->row || a->col != b->col)           // Tests the compatibility of dimensions.
    {
        error_message_la(25, "incompatible dimensions for a matrix subtraction!");

        return NULL;
    }

    mat = create_matrix(a->row, a->col);

    for (i = 0; i < mat->row; i++)
    {
        for (j = 0; j < mat->col; j++)
            mat->m[i][j] = a->m[i][j] - b->m[i][j];
    }

    return mat;
}

Matrix* rnumber_times_matrix(double num, Matrix *mat)       // Multiplies a real number by a matrix and saves the result as a new matrix.
{
    register int i, j;

    Matrix *m;

    if (mat == NULL)
    {
        error_message_la(26, ERRMSS04);

        return NULL;
    }

    m = create_matrix(mat->row, mat->col);

    for (i = 0; i < m->row; i++)
    {
        for (j = 0; j < m->col; j++)
            m->m[i][j] = num * mat->m[i][j];
    }

    return m;
}

Matrix* matrix_times_matrix(Matrix *a, Matrix *b)   // Multiplies two matrixes and saves the result as a new one.
{
    register int i, j, k;

    Matrix *mat;

    if (a == NULL || b == NULL)
    {
        error_message_la(27, ERRMSS04);

        return NULL;
    }

    if (a->col != b->row)                               // Tests the compatibility of dimensions.
    {
        error_message_la(27, "incompatible dimensions for a matrix multiplication!");

        return NULL;
    }

    mat = create_matrix(a->row, b->col);

    for (i = 0; i < mat->row; i++)
    {
        for (j = 0; j < mat->col; j++)
        {
            mat->m[i][j] = 0;

            for (k = 0; k < b->row; k++)
                mat->m[i][j] += a->m[i][k] * b->m[k][j];
        }
    }

    return mat;
}

Matrix* transpose_matrix(Matrix *mat)               // Transposes a matrix and saves the result as a new one.
{
    register int i, j;

    Matrix *m;

    if (mat == NULL)
    {
        error_message_la(28, ERRMSS04);

        return NULL;
    }

    m = create_matrix(mat->col, mat->row);

    for (i = 0; i < m->row; i++)
    {
        for (j = 0; j < m->col; j++)
            m->m[i][j] = mat->m[j][i];
    }

    return m;
}

void over_sum_matrix(Matrix *a, Matrix *b)          // Sums two matrixes and overwrites the result in the first one.
{
    register int i, j;

    if (a == NULL || b == NULL)
    {
        error_message_la(29, ERRMSS04);

        return;
    }

    if (a->row != b->row || a->col != b->col)           // Tests the compatibility of dimensions.
    {
        error_message_la(29, "incompatible dimensions for a matrix sum!");

        return;
    }

    for (i = 0; i < a->row; i++)
    {
        for (j = 0; j < a->col; j++)
            a->m[i][j] += b->m[i][j];
    }
}

void over_subtract_matrix(Matrix *a, Matrix *b)     // Subtracts two matrixes and overwrites the result in the first one.
{
    register int i, j;

    if (a == NULL || b == NULL)
    {
        error_message_la(30, ERRMSS04);

        return;
    }

    if (a->row != b->row || a->col != b->col)           // Tests the compatibility of dimensions.
    {
        error_message_la(30, "incompatible dimensions for a matrix subtraction!");

        return;
    }

    for (i = 0; i < a->row; i++)
    {
        for (j = 0; j < a->col; j++)
            a->m[i][j] -= b->m[i][j];
    }
}

void over_rnumber_times_matrix(double num, Matrix *mat)     // Multiplies a real number by a matrix and overwrites the result in the original matrix.
{
    register int i, j;

    if (mat == NULL)
    {
        error_message_la(31, ERRMSS04);

        return;
    }

    for (i = 0; i < mat->row; i++)
    {
        for (j = 0; j < mat->col; j++)
            mat->m[i][j] *= num;
    }
}

void over_matrix_times_matrix(Matrix *a, Matrix *b)     // Multiplies two matrixes and overwrites the result in the first one.
{
    register int i, j, k;

    Matrix *tempmat;

    if (a == NULL || b == NULL)
    {
        error_message_la(32, ERRMSS04);

        return;
    }

    if (a->col != b->row)                   // Tests the compatibility of dimensions.
    {
        error_message_la(32, "incompatible dimensions for a matrix multiplication!");

        return;
    }
    else if (b->row != b->col)                  // Only works if the second matrix is square.
    {
        error_message_la(32, ERRMSS05);

        printf("\nThe second matrix must have the same number of rows and columns.\n");

        return;
    }

    tempmat = create_matrix(a->row, a->col);

    for (i = 0; i < a->row; i++)            // Multiplication
    {
        for (j = 0; j < a->col; j++)
        {
            tempmat->m[i][j] = 0;

            for (k = 0; k < b->row; k++)
                tempmat->m[i][j] += a->m[i][k] * b->m[k][j];
        }
    }

    over_copy_matrix(tempmat, a);           // Overwriting

    free_matrix(tempmat);
}

void over_transpose_matrix(Matrix *mat)         // Transposes a matrix and overwrites the result in the original one.
{
    register int i, j;

    Matrix *tempmat;

    if (mat == NULL)
    {
        error_message_la(33, ERRMSS04);

        return;
    }

    if (mat->row != mat->col)                       // Only works if the matrix is square.
    {
        error_message_la(33, ERRMSS05);

        printf("\nThe matrix must have the same number of rows and columns.\n");

        return;
    }

    tempmat = create_matrix(mat->col, mat->row);

    for (i = 0; i < mat->row; i++)                  // Transposition
    {
        for (j = 0; j < mat->col; j++)
            tempmat->m[i][j] = mat->m[j][i];
    }

    over_copy_matrix(tempmat, mat);                 // Overwriting

    free_matrix(tempmat);
}

// Other operations:

double scalar_product(Array *a, Array *b)   // Calculates the scalar product of two vectors (arrays).
{
    register int i;

    double spro = 0;

    if (a == NULL || b == NULL)
    {
        error_message_la(34, ERRMSS02);

        return 0;
    }
    else if (a->len != b->len)                  // Tests the compatibility of dimensions.
    {
        error_message_la(34, "incompatible dimensions for scalar product!");

        return 0;
    }

    for (i = 0; i < a->len; i++)                // Scalar product
        spro += a->a[i] * b->a[i];

    return spro;
}

Array* vector_product(Array *a, Array *b)   // Calculates the vector product of two vectors (arrays).
{
    Array *prod;

    if (a == NULL || b == NULL)
    {
        error_message_la(46, ERRMSS02);

        return NULL;
    }
    if (a->len != 3 || b->len != 3)             // Vector product is defined only for three-dimensional vectors.
    {
        error_message_la(46, "incompatible dimensions for vector product!");

        return NULL;
    }

    prod = create_array(3);

    prod->a[0] = a->a[1] * b->a[2] - a->a[2] * b->a[1];

    prod->a[1] = a->a[2] * b->a[0] - a->a[0] * b->a[2];

    prod->a[2] = a->a[0] * b->a[1] - a->a[1] * b->a[0];

    return prod;
}

double euclidean_norm(Array *arr)       // Calculates the euclidean norm of a vector (array).
{
    register int i;

    double norm = 0;

    if (arr == NULL)
    {
        error_message_la(35, ERRMSS02);

        return 0;
    }

    for (i = 0; i < arr->len; i++)          // Euclidean norm
        norm += arr->a[i] * arr->a[i];

    norm = sqrt(norm);

    return norm;
}

double cosine_similarity(Array *a, Array *b)    // Determines the cosine of the angle between two vectors (arrays).
{
    double anrm, bnrm, co;

    if (a == NULL || b == NULL)
    {
        error_message_la(36, ERRMSS02);

        return 100000;
    }

    anrm = euclidean_norm(a);       // Calculates the euclidean norm of the two vectors.

    bnrm = euclidean_norm(b);

    if (anrm == 0 || bnrm == 0)
    {
        error_message_la(36, "vector with zero length informed!");

        printf("\nThere is no cosine value available.\n");

        return 100000;
    }
    else
        co = scalar_product(a, b) / (anrm * bnrm);      // Cosine similarity

    return co;
}

void swap_rows(Matrix *mat, int a, int b)           // Swaps two rows of a matrix.
{
    register int j;
    double temp;

    if (mat == NULL)
    {
        error_message_la(37, ERRMSS04);

        exit(37);
    }
    else if (a >= mat->row || a < 0 || b >= mat->row || b < 0)  // Tests if the rows exist.
    {
        error_message_la(37, "invalid row number!");

        exit(37);
    }

    for (j = 0; j < mat->col; j++)                              // Swaps the rows.
    {
        temp = mat->m[a][j];

        mat->m[a][j] = mat->m[b][j];

        mat->m[b][j] = temp;
    }
}

int gaussian_elimination(Matrix *mat)   // Transforms a square matrix into an upper triangular matrix, if it is possible.
{
    register i, j, k;
    int correction = 1;                     // This can be used for a correction in the calculation of a determinant if necessary.
    double fctr;

    if (mat == NULL)
    {
        error_message_la(38, ERRMSS04);

        return NULL;
    }

    for (i = 0; i < mat->row; i++)
    {
        if (mat->m[i][i] == 0 && i < mat->row - 1)  // Swaps rows, if necessary, to better organize the matrix.
        {
            for (k = i + 1; k < mat->row; k++)
            {
                if (mat->m[k][i] != 0)
                {
                    swap_rows(mat, i, k);

                    correction = - correction;

                    break;
                }
            }
        }

        if (mat->m[i][i] != 0 && i < mat->row - 1)
        {
            for (k = i + 1; k < mat->row; k++)      // Transforms into a triangular matrix.
            {
                if (mat->m[k][i] == 0)
                    continue;
                
                fctr = - mat->m[k][i] / mat->m[i][i];
                
                for (j = i + 1; j < mat->col; j++)
                    mat->m[k][j] += fctr * mat->m[i][j];

                mat->m[k][i] = 0;
            }
        }
    }

    return correction;
}

double determinant(Matrix *mat)         // Calculates the determinant of a square matrix.
{
    register i;
    int corr;
    double det = 1;
    Matrix *tempmat;

    if (mat == NULL)
    {
        error_message_la(39, ERRMSS04);

        exit(39);
    }
    else if (mat->row != mat->col)          // Tests if the matrix is square.
    {
        error_message_la(39, "incompatible dimensions to calculate a determinant!");

        printf("\nThe matrix must have the same number of rows and columns.\n");

        exit(39);
    }

    tempmat = copy_matrix(mat);

    corr = gaussian_elimination(tempmat);   // Transforms the matrix into an upper triangular one.

    for (i = 0; i < tempmat->row; i++)      // Calculates the determinant.
    {
        det *= tempmat->m[i][i];

        if (tempmat->m[i][i] == 0)
            break;
    }

    det *= corr;                            // Corrects the signal.

    free_matrix(tempmat);

    return det;
}

double over_determinant(Matrix *mat)    // Calculates the determinant of a square matrix, overwriting the operations in it.
{
    register i;
    int corr;
    double det = 1;

    if (mat == NULL)
    {
        error_message_la(40, ERRMSS04);

        exit(40);
    }
    else if (mat->row != mat->col)          // Tests if the matrix is square.
    {
        error_message_la(40, "incompatible dimensions to calculate a determinant!");

        printf("\nThe matrix must have the same number of rows and columns.\n");

        exit(40);
    }

    corr = gaussian_elimination(mat);       // Transforms the matrix into an upper triangular one.

    for (i = 0; i < mat->row; i++)          // Calculates the determinant.
    {
        det *= mat->m[i][i];

        if (mat->m[i][i] == 0)
            break;
    }

    det *= corr;                            // Corrects the signal.

    return det;
}

Matrix* inverse_matrix(Matrix *mat)             // Returns the inverse of a matrix if it exists.
{
    register i, j, k;
    double fctr;

    Matrix *tempmat, *inv;

    if (mat == NULL)
    {
        error_message_la(41, ERRMSS04);

        return NULL;
    }
    else if (mat->row != mat->col)                  // Tests if the matrix is square.
    {
        error_message_la(41, "incompatible dimensions to do an inversion!");

        printf("\nThe matrix must have the same number of rows and columns.\n");

        return NULL;
    }

    tempmat = copy_matrix(mat);

    inv = create_identity_matrix(mat->row);         // All operations made in 'tempmat' will be made equally in 'inv'.

    for (i = 0; i < tempmat->row; i++)
    {
        if (tempmat->m[i][i] == 0)                  // Tests if the element of main diagonal is null.
        {
            if (i < tempmat->row - 1)
            {
                int swap = 0;

                for (k = i + 1; k < tempmat->row; k++)  // Searches for another row with no null element in that position.
                {
                    if (tempmat->m[k][i] != 0)              // Swaps the rows.
                    {
                        swap_rows(tempmat, i, k);

                        swap_rows(inv, i, k);

                        swap++;

                        break;
                    }
                }

                if (swap == 0)                          // This implies a matrix with null determinant, wich has no inverse.
                {
                    printf("\n\nThe matrix has no inverse!\n");

                    return NULL;
                }
            }
            else
            {
                printf("\n\nThe matrix has no inverse!\n");

                return NULL;
            }
        }

        fctr = tempmat->m[i][i];

        for (j = 0; j < tempmat->col; j++)          // Divides all elements by the first non-null one in the row.
        {
            tempmat->m[i][j] /= fctr;

            inv->m[i][j] /= fctr;
        }

        for (k = 0; k < tempmat->row; k++)          // The elements that are not in the main diagonal are turned null.
        {
            if (k == i)
                continue;

            fctr = - tempmat->m[k][i];

            for (j = 0; j < tempmat->col; j++)
            {
                if(tempmat->m[i][j] != 0)               // Jumps some inutile operations.
                    tempmat->m[k][j] += fctr * tempmat->m[i][j];

                inv->m[k][j] += fctr * inv->m[i][j];
            }
        }
    }

    free_matrix(tempmat);

    return inv;
}

double polynomial_function(double x, Array *coef)   // Evaluates a polynomial for a given 'x' value.
{
    register int i;
    double fx;

    if (coef == NULL)
    {
        error_message_la(42, ERRMSS02);

        return 0;
    }

    if (coef->len == 1)
        return coef->a[0];
                                                                // Horner's method for polynomials
    fx = coef->a[coef->len - 1] * x + coef->a[coef->len - 2];

    if (coef->len > 2)                                              // If the polynomial's degree is higher than 1
    {
        for (i = coef->len - 2; i >= 1; i--)
            fx = fx * x + coef->a[i - 1];
    }

    return fx;
}

// Functions for systems of equations:

Matrix* get_system(char *name)          // Get an augmented matrix of a system of equations from a 'txt' file.
{
    register int i, j;
    int m, n;

    Matrix *sys;
    FILE *filin;

    filin = fopen(name, "r");

    if (filin == NULL)
    {
        error_message_la(43, ERRMSS03);

        exit(43);
    }

    fscanf(filin, "%dx%d", &m, &n);

    if (n != m + 1)                         // Tests the system dimensions.
    {
        error_message_la(43, "invalid system dimensions!");

        printf("\nThe number of equations and variables must be the same.\n");

        return NULL;
    }

    sys = create_matrix(m, n);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            fscanf(filin, " %lf", &sys->m[i][j]);
    }

    fclose(filin);

    return sys;
}

int independent_system(Matrix *mat)         // Tests if the system is independent or not.
{
    register int i;

    if (mat == NULL)
    {
        error_message_la(44, ERRMSS04);

        exit(44);
    }

    for (i = 0; i < mat->row; i++)              // Walks through the main diagonal of the superior triangular matrix of coefficients.
    {
        if (mat->m[i][i] == 0)
            return 0;                               // Returns '0' if the product of the elements is null.
    }

    return 1;                                       // Returns '1' otherwise.
}

Array* solve_system(Matrix *mat)                    // Solves a system of 'n' equations and 'n' variables.
{
    register int i, j;

    Array *sol;
    Matrix *tempmat;

    if (mat == NULL)
    {
        error_message_la(45, ERRMSS04);

        return NULL;
    }
    else if (mat->col != mat->row + 1 || mat->row < 1)  // Tests the coherence of the numbers of equations and variables.
    {
        error_message_la(45, "incompatible dimensions to solve the system of equations!");

        return NULL;
    }

    tempmat = copy_matrix(mat);

    gaussian_elimination(tempmat);

    if (!independent_system(tempmat))                   // Tests if the system is independent.
    {
        printf("\n\nNo solution!\n\nThe system of equations is dependent or inconsistent!\n\a");

        return NULL;
    }
    else                                                    // Calculates the solution if it is independent.
    {
        sol = create_array(mat->row);

        for (i = sol->len - 1; i >= 0; i--)                     // Solves the system by simple substitution.
        {
            sol->a[i] = tempmat->m[i][tempmat->col - 1];

            for (j = i + 1; j < tempmat->col - 1; j++)
                sol->a[i] -= tempmat->m[i][j] * sol->a[j];

            sol->a[i] /= tempmat->m[i][i];
        }
    }

    free_matrix(tempmat);

    return sol;
}
