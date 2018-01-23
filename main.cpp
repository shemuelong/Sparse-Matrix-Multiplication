#include <iostream>
#include "matrix.h"
using namespace std;

int main() {
    sparse_matrix *m1 = nullptr;  // 2D array to store matrix m1
    sparse_matrix *m2 = nullptr;  // 2D array to store matrix m2
    sparse_matrix *m = nullptr;
    ifstream datafile;   // input file stream object



    // initialize the matrices m1,m2 to 0.0
    m1 = create(MATRIX_SIZE);
    m2 = create(MATRIX_SIZE);

    // print out m1 in the matrix format and it should be 0
    cout << "m1 after initialization" << endl;
    write_matrix(m1,MATRIX_SIZE);
    cout << endl;

    // print out m2 in the matrix format and it should be 0
    cout << "m2 after initialization" << endl;
    write_matrix(m2,MATRIX_SIZE);
    cout << endl;

    // open the data file to input the matrices
    datafile.open("C:\\Users\\ongsh\\CLionProjects\\110B_Sparse Matrix Assignment\\data");

    // populate the 2D array with matrix data, m1, from the file
    read_matrix(m1,MATRIX_SIZE,datafile);
    cout << "m1 after populated from data file" << endl;
    write_matrix(m1,MATRIX_SIZE);
    cout << endl;

    // populate the 2D array with matrix data, m2, from the file
    read_matrix(m2,MATRIX_SIZE,datafile);
    cout << "m2 after populated from data file" << endl;
    write_matrix(m2,MATRIX_SIZE);
    cout << endl;

    // close the data file
    datafile.close();

    // create the resultant matrix
    m = create(MATRIX_SIZE);

    // m = m1 * m2
    multiply(m1, m2, m, MATRIX_SIZE);

    cout << "m after multiplication between m1 and m2" << endl;
    write_matrix(m,MATRIX_SIZE);
    cout << endl;

    return 0;
}
