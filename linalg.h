// Various functions used in Linear Algebra and matrix operations.
//


// Type exported for arrays
//
typedef struct array Array;

// Type exported for matrixes
//
typedef struct matrix Matrix;


//
// In-Out functions:
//


// Creates an array with a given length.
// Returns NULL if 'len' is equal zero or negative.
//
Array* create_array(int len);

// Deallocates memory previously used for an array.
//
void free_array(Array *arr);

// Gives the length of an array.
// A NULL array returns '0'.
//
int length_of_array(Array *arr);

// Inserts a value in an array in a given position.
//
void insert_in_array(double a, Array *arr, int pos);

// Gets a value in an array from a given position.
// If the position does not exist or the array is
// NULL, the function returns '0'.
//
double get_from_array(Array *arr, int pos);

// Get an array from a 'txt' file.
//
Array* get_array(char *name);

// Shows an array on the screen.
//
void print_array(Array *arr);

// Creates a matrix with given dimensions.
// Returns NULL if 'm' or 'n' are equal zero or negative.
//
Matrix* create_matrix(int m, int n);

// Creates an identity matrix of a given order.
// Returns NULL if 'ord' is equal zero or negative.
//
Matrix* create_identity_matrix(int ord);

// Deallocates memory previously used for a matrix.
//
void free_matrix(Matrix *mat);

// Gives the number of rows of a matrix.
// A NULL matrix returns '0'.
//
int matrix_row_number(Matrix *mat);

// Gives the number of columns of a matrix.
// A NULL matrix returns '0'.
//
int matrix_column_number(Matrix *mat);

// Inserts a value in a matrix in a given position.
//
void insert_in_matrix(double a, Matrix *mat, int i, int j);

// Gets a value in a matrix from a given position.
// If the position does not exist or the matrix is
// NULL, the function returns '0'.
//
double get_from_matrix(Matrix *mat, int i, int j);

// Get a matrix from a 'txt' file.
//
Matrix* get_matrix(char *name);

// Shows a matrix on the screen.
//
void print_matrix(Matrix *mat);

// Shows an error message indicating the function from where it came.
//
static void error_message_la(int nmbr, char *mssg);


//
// Copy functions:
//


// Copies an array as a new one.
// Returns NULL if 'arr' is NULL.
//
Array* copy_array(Array *arr);

// Copies an array in a pre-existing one, overwriting it.
//
void over_copy_array(Array *cpy, Array *pst);

// Copies a matrix as a new one.
// Returns NULL if 'mat' is NULL.
//
Matrix* copy_matrix(Matrix *mat);

// Copies a matrix in a pre-existing one, overwriting it.
//
void over_copy_matrix(Matrix *cpy, Matrix *pst);


//
// Arithmetic operation functions:
//


// Sums two arrays and saves the result as a new one.
// Returns NULL if the dimensions are incompatible with a sum
// or if one or two of given arrays are NULL.
//
Array* sum_array(Array *a, Array *b);

// Subtracts two arrays and saves the result as a new one.
// Returns NULL if the dimensions are incompatible with a subtraction
// or if one or two of given arrays are NULL.
//
Array* subtract_array(Array *a, Array *b);

// Multiplies a real number by an array and saves the result as a new array.
// Returns NULL if the given array is NULL.
//
Array* rnumber_times_array(double num, Array *arr);

// Multiplies an array by a matrix and saves the result as a new array.
// Returns NULL if the array or the matrix informed are NULL or
// if the dimensions are incompatible with a multiplication.
//
Array* array_times_matrix(Array *arr, Matrix *mat);

// Multiplies a matrix by an array and saves the result as a new array.
// Returns NULL if the array or the matrix informed are NULL or
// if the dimensions are incompatible with a multiplication.
//
Array* matrix_times_array(Matrix *mat, Array *arr);

// Sums two arrays and overwrites the result in the first one.
//
void over_sum_array(Array *a, Array *b);

// Subtracts two arrays and overwrites the result in the first one.
//
void over_subtract_array(Array *a, Array *b);

// Multiplies a real number by an array and overwrites the result in the original array.
//
void over_rnumber_times_array(double num, Array *arr);

// Multiplies an array by a matrix and overwrites the result in the first one.
// Only works if the matrix is square.
//
void over_array_times_matrix(Array *arr, Matrix *mat);

// Multiplies a matrix by an array and overwrites the result in the second one.
// Only works if the matrix is square.
//
void over_matrix_times_array(Matrix *mat, Array *arr);

// Sums two matrixes and saves the result as a new one.
// Returns NULL if the dimensions are incompatible with a sum
// or if one or two of given matrices are NULL.
//
Matrix* sum_matrix(Matrix *a, Matrix *b);

// Subtracts two matrixes and saves the result as a new one.
// Returns NULL if the dimensions are incompatible with a subtraction
// or if one or two of given matrices are NULL.
//
Matrix* subtract_matrix(Matrix *a, Matrix *b);

// Multiplies a real number by a matrix and saves the result as a new matrix.
// Returns NULL if the given matrix is NULL.
//
Matrix* rnumber_times_matrix(double num, Matrix *mat);

// Multiplies two matrixes and saves the result as a new one.
// Returns NULL if the dimensions are incompatible with a multiplication
// or if one or two of given matrices are NULL.
//
Matrix* matrix_times_matrix(Matrix *a, Matrix *b);

// Transposes a matrix and saves the result as a new one.
// Returns NULL if the given matrix is NULL.
//
Matrix* transpose_matrix(Matrix *mat);

// Sums two matrixes and overwrites the result in the first one.
//
void over_sum_matrix(Matrix *a, Matrix *b);

// Subtracts two matrixes and overwrites the result in the first one.
//
void over_subtract_matrix(Matrix *a, Matrix *b);

// Multiplies a real number by a matrix and overwrites the result in the original matrix.
//
void over_rnumber_times_matrix(double num, Matrix *mat);

// Multiplies two matrixes and overwrites the result in the first one.
// Only works if the second matrix is square.
//
void over_matrix_times_matrix(Matrix *a, Matrix *b);

// Transposes a matrix and overwrites the result in the original one.
// Only works if the matrix is square.
//
void over_transpose_matrix(Matrix *mat);


//
// Other operations:
//


// Calculates the scalar product of two vectors (arrays).
// Returns '0' if one or both arrays are NULL
// or if their dimensions are incompatible.
//
double scalar_product(Array *a, Array *b);

// Calculates the vector product of two vectors (arrays).
// Returns NULL if one or both arrays are NULL
// or if their dimensions are incompatible.
//
Array* vector_product(Array *a, Array *b);

// Calculates the euclidean norm of a vector (array).
// Returns '0' if 'arr' is NULL.
//
double euclidean_norm(Array *arr);

// Determines the cosine of the angle between two vectors (arrays).
// Returns '100' if one or both arrays are NULL
// or have a zero length.
//
double cosine_similarity(Array *a, Array *b);

// Changes two rows of a matrix.
//
void swap_rows(Matrix *mat, int a, int b);

// Transforms a square matrix into an upper triangular matrix, if it is possible.
// Also works with a matrix that is not square, but only with elements that
// have indices i > j.
// Returns a value that can be used for correction in the calculation of a
// determinant if necessary, by means of multiplication.
//
int gaussian_elimination(Matrix *mat);

// Calculates the determinant of a square matrix.
//
double determinant(Matrix *mat);

// Calculates the determinant of a square matrix, overwriting the operations in it.
// The original matrix is lost.
//
double over_determinant(Matrix *mat);

// Returns the inverse of a matrix if it exists.
// If the inverse do not exist, returns NULL.
//
Matrix* inverse_matrix(Matrix *mat);

// Evaluates a polynomial for a given 'x' value.
// The array must have the coefficients of the polynomial ordered by degree.
// Returns '0' if 'coef' is NULL.
//
double polynomial_function(double x, Array *coef);


//
// Functions for systems of equations:
//


// Get an augmented matrix of a system of equations from a 'txt' file.
//
Matrix* get_system(char *name);

// Tests if the system is independent or not.
// Returns '1' or '0' in each case.
//
int independent_system(Matrix *mat);

// Solves a system of 'n' equations and 'n' variables.
// Returns NULL if the system has no single solution.
//
Array* solve_system(Matrix *mat);