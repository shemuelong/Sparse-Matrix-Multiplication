#include "matrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

sparse_matrix* create(int m_size)
// Function parameters require intended size of the node pointer array.
// Result: initializes sparse matrix and sets all of its pointers to NULL.
{
    sparse_matrix *sm;
    sm = new sparse_matrix;
    // creates a new sparse matrix.

    for ( int i = 0; i < m_size; i ++ )
    {
        (*sm).first_in_row[i] = nullptr;
        (*sm).first_in_column[i] = nullptr;
    }
    // sets all of the pointers in the sparse matrix to NULL.

    return sm;
}

void add_next_entry(sparse_matrix *m, int i, int j, float e)
// Function to be called when the file stream object in "void read_matrix" reads a value that is not equal to zero.
// Function also to be called in "void multiply".
// Function parameters require a sparse matrix, and the row (i), column (j), and element value (e) of the non zero matrix element.
// Result: Function creates a node and stores the corresponding column, row, and value.
// Result: Function will set the two pointers in the node to NULL.
// Result: Function will go through the sparse matrix and find the immediate, previous pointer in the respective row and column,
//         and set those pointers to the newly created node.
{
    node *a;
    a = new node;
    (*a).element = e;
    (*a).row = i;
    (*a).column = j;
    (*a).next_in_row = nullptr;
    (*a).next_in_column = nullptr;
    // initializes new node and stores the row, column, element values.
    // pointers in the new node are set to NULL.


    if((*m).first_in_column[j] == nullptr)         // if corresponding column pointer in sparse matrix is NULL,
        (*m).first_in_column[j] = a;              // set the pointer to the newly created node.
    else
    {
        node *current = (*m).first_in_column[j];  // intialize a pointer to the address of the node as that the sparse matrix
        // points to (in the respective column).
        while ((*current).next_in_column != nullptr) // Traverse the column to find the last pointer that is set to NULL.
            current = (*current).next_in_column;

        current->next_in_column = a;              // Sets that pointer to the address of the newly created node.
    }


    if ((*m).first_in_row[i] == nullptr)           // Same results as the if-else statement above, but deals with the "row" pointers.
        (*m).first_in_row[i] = a;
    else
    {
        node *current = (*m).first_in_row[i];
        while ((*current).next_in_row != nullptr)
            current = (*current).next_in_row;

        current->next_in_row = a;
    }
}

void read_matrix(sparse_matrix *m, int m_size, ifstream &inputFile)
// Function parameters require a sparse matrix, the size of the sparse matrix, and an input file stream object.
// Result: Uses file stream object to read in matrix values from example data.
// Result: If value is not equal to zero, the function will call "void add_next_entry" to intialize a new node.
{
    float e;
    for(int i=0; i < m_size;i++)
    {
        for(int j=0; j < m_size; j++)
        {
            inputFile >> e;
            if (e!=0)
            {
                add_next_entry(m,i,j,e);
            }
        }
    }
}

void printzeros (int lo, int hi)
// Function parameters requires two integers.
// Function will be used in "void write_matrix".
// Result: Print out a number of zeros based on the difference between the two parameters.
{
    cout << setprecision(2) << fixed;
    for (int i=0; i < (hi - lo); i++)
        cout << setw(8) << 0.00;
}

void write_matrix(sparse_matrix *m, int m_size)
// Function parameters require a sparse matrix and its size.
// Result: displays the contents of the sparse matrix.
{
    cout << setprecision(2) << fixed;

    for (int i=0; i < m_size; i++)
    {
        node *current =  (*m).first_in_row[i];       // intializes a pointer and sets it to the corresponding pointer in the sparse matrix
        for (int j=0; j < m_size; j++)
        {
            if (current != nullptr)
            {
                printzeros(j, (*current).column);       // will find the column value of the first node, and print the
                j = (*current).column;                  // corresponding amount of zeros.
                cout << setw(8) << (*current).element;  // will then print the element value.
                current = (*current).next_in_row;       // Will then advance the pointer to the next node in the row.
            }
            else
            {
                printzeros (j,m_size);                  // if the row pointer in the sparse matrix is null, will print 18 zeros for that row.
                j= m_size;
            }
        }
        cout << endl;
    }
}

void multiply(sparse_matrix *m1, sparse_matrix *m2, sparse_matrix *m, int m_size)
// Function parameters require three separate sparse matrixes, and the size of all three matrixes.
// Result: Multiplies the first two sparse matrixes together and stores its product in the third sparse matrix.
{
    for (int i=0; i < m_size; i++)
    {
        for (int j=0; j < m_size; j++)
        {
            node *row_node = (*m1).first_in_row[i];               // initializes two pointers and sets it equal to the address of the sparse matrix's pointer for that row and column
            node *column_node = (*m2).first_in_column[j];
            float total = 0;                                      // initialize a total value to assign to the resultant matrix.
            for (int k=0; k < m_size; k++)
            {
                if (row_node == nullptr || column_node == nullptr)        // Compares the row pointer to the sparse matrix's column pointer
                    k=m_size;                                         // Break from loop if both are null, meaning the multiplication will result in zero
                else if ((*row_node).column < (*column_node).row)   // Compares the index of the row and column pointers.
                    row_node = (*row_node).next_in_row;               // If one is less than the other, the lower one is advanced
                else if ((*column_node).row < (*row_node).column)
                    column_node = (*column_node).next_in_column;
                else
                {
                    total += (*row_node).element * (*column_node).element;  // When the indexes match, the element values are multipled and added to the total
                    column_node = (*column_node).next_in_column;            // Both column and row pointers are then advanced
                    row_node = (*row_node).next_in_row;
                }
            }
            add_next_entry(m,i,j,total);                                // The total value is then stored and added to the resultant matrix
        }
    }
}
