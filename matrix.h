#ifndef INC_100B_SPARSE_MATRIX_ASSIGNMENT_MATRIX_H
#define INC_100B_SPARSE_MATRIX_ASSIGNMENT_MATRIX_H
/*
    Sparse Matrix Multiplication Assignment
*/

#include <fstream>
using namespace std;


const int MATRIX_SIZE = 18;
// Matrix size set to 18 after counting the columns and rows of the example data.

struct node
// Struct Node is defined in assignment handout.
// It is used to store non-zero values in the sparse matrix.
{
    float element;
    int row;
    int column;
    node *next_in_row;
    node *next_in_column;
};

struct sparse_matrix
// Struct Sparse matrix is defined in assignment handout.
// Uses two arrays to pointers to access the first non-zero nodes in the sparse matrix.
{
    node *first_in_row[MATRIX_SIZE];
    node *first_in_column[MATRIX_SIZE];
};


sparse_matrix *create(int m_size);
// Function parameters require intended size of the node pointer array.
// Result: initializes sparse matrix and sets all of its pointers to NULL.

void read_matrix(sparse_matrix *m, int m_size, ifstream &inputFile);
// Function parameters require a sparse matrix, the size of the sparse matrix, and an input file stream object.
// Result: Uses file stream object to read in matrix values from example data.
// Result: If value is not equal to zero, the function will initialize a node and store the row, column, and value.
// Result: Inside the node, the corresponding row and column pointers will be set to NULL.
// Result: The immediate, previous corresponding row and column pointers will be set to point to the newly created node.

void write_matrix(sparse_matrix *m, int m_size);
// Function parameters require a sparse matrix and its size.
// Result: displays the contents of the sparse matrix.

void multiply(sparse_matrix *m1, sparse_matrix *m2, sparse_matrix *m, int m_size);
// Function parameters require three separate sparse matrixes, and the size of all three matrixes.
// Result: Multiplies the first two sparse matrixes together and stores its product in the third sparse matrix.
#endif //INC_100B_SPARSE_MATRIX_ASSIGNMENT_MATRIX_H
