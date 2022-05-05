// Hoang Nguyen
// TARRANT COUNTY COLLEGE
// COSC 2436-86002
// Program 4
// Written for GCC
#include <algorithm>
#include <iostream>
#include <vector>  // for 2D vector
using namespace std;

// GLOBAL VARIABLES
const int MAXCOL = 8;
const int MAXROW = 10;

struct Point {
    int row;
    int col;
    int val;
};

class Matrix {
   private:
    vector<vector<int>> matrix;
    bool binarySearchDiagonal(vector<Point>, int, int, int, Point &, Point &,
                              int, int);

   public:
    Matrix(vector<vector<int>>);
    bool elementSearch(int, int, int, int, int, int, int);
    void displayMatrix();
    void verifyCornerElements();
    void verifyAllSearchedElements();
    void verifyFoundWrongElements(int, int, int);
};

bool Matrix::binarySearchDiagonal(vector<Point> arr, int val, int left,
                                  int right, Point &smallerV, Point &largerV,
                                  int rowV, int colV) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        // If the value is at the middle
        if (arr[mid].val == val && arr[mid].col == colV) {
            return true;
        }

        // If the value is smaller than or equal to mid, and its col or row is
        // different than mid. Then loop the leftside subarray
        if (arr[mid].val >= val &&
            (arr[mid].col != colV || arr[mid].row != rowV)) {
            return binarySearchDiagonal(arr, val, left, mid - 1, smallerV,
                                        largerV, rowV, colV);
        }
        // // Else the value can only be present in right subarray
        else {
            return binarySearchDiagonal(arr, val, mid + 1, right, smallerV,
                                        largerV, rowV, colV);
        }
    }
    // Because the loop end after left > right. So there would be two numbers.
    // One is largen than the value, which would return to the very end right,
    // and the other is larger than the value, which would return to the very
    // end left

    // Assign the left to the larger and the right to the smaller.
    if (left >= 0 && right >= 0) {
        largerV = arr[left];
        smallerV = arr[right];
        // if the value is larger than the largest value of arr, then the
        // smaller would be the next to the last, and the larger would be the
        // last.
        if (left > arr.size() - 1) {
            smallerV = arr[right - 1];
            largerV = arr[right];
        }
    }
    // return false if not found
    return false;
}

Matrix::Matrix(vector<vector<int>> arr2D) { matrix = arr2D; }

// Display Matrix
void Matrix::displayMatrix() {
    cout << "The array is: \n" << endl;
    // Iterator of rows
    for (vector<vector<int>>::iterator it1 = matrix.begin();
         it1 != matrix.end(); ++it1) {
        // Iterator of column
        for (vector<int>::iterator it2 = (*it1).begin(); it2 != (*it1).end();
             ++it2) {
            cout << (*it2) << " ";
        }
        cout << endl;
    }
}

// elementSearch takes a value, its row and col position, and a specific area on
// a matrix to search
bool Matrix::elementSearch(int val, int startRow, int endRow, int startCol,
                           int endCol, int rowV, int colV) {
    // Base case
    if (startRow > endRow || startCol > endCol || startRow >= matrix.size() ||
        startCol >= matrix[0].size() || endCol < 0 || endRow < 0 ||
        endCol > matrix[0].size() || endRow > matrix.size()) {
        return false;
    }
    vector<Point> diagonal;
    // if a matrix is 1xn or mx1 then diagonal would be on that col or row.
    if (startCol == endCol) {
        for (int i = 0; i <= endRow - startRow; i++) {
            Point p1 = {startRow + i, startCol, matrix[startRow + i][startCol]};
            diagonal.push_back(p1);
        }
    } else if (startRow == endRow) {
        for (int i = 0; i <= endCol - startCol; i++) {
            Point p1 = {startRow, startCol + i, matrix[startRow][startCol + i]};
            diagonal.push_back(p1);
        }
    } else {
        // If the number of row is larger than the number of col. The diagonal
        // would be based on the number of col.
        if (endRow - startRow > endCol - startCol) {
            for (int i = 0; i <= endCol - startCol; i++) {
                Point p1 = {startRow + i, startCol + i,
                            matrix[startRow + i][startCol + i]};
                diagonal.push_back(p1);
            }
            // }
            // Else the diagonal would be based on the number of row.
        } else {
            for (int i = 0; i <= endRow - startRow; i++) {
                Point p1 = {startRow + i, startCol + i,
                            matrix[startRow + i][startCol + i]};
                diagonal.push_back(p1);
            }
        }
    }
    // the smaller of the value
    // the larger of the value
    Point smallerPoint = {0, 0, 0};
    Point largerPoint = {0, 0, 0};

    // Search the value on the diagonal. if found return true. if not, there
    // will be two values and assign it to smallerV and largerV.
    if (binarySearchDiagonal(diagonal, val, 0, diagonal.size() - 1,
                             smallerPoint, largerPoint, rowV, colV)) {
        return true;
    }
    // if the largerpoint's value found is smaller than the value and its col is
    // equal to the value's col
    else if (largerPoint.val <= val && largerPoint.col == colV) {
        // then diagonal would be any number which has the same largerpoint's
        // col but below rows.
        for (int i = 1; i <= endRow - largerPoint.row; i++) {
            Point p1 = {largerPoint.row + i, largerPoint.col,
                        matrix[largerPoint.row + i][largerPoint.col]};
            diagonal.push_back(p1);
        }

        // do binary search on the diagonal.
        if (binarySearchDiagonal(diagonal, val, 0, diagonal.size() - 1,
                                 smallerPoint, largerPoint, rowV, colV)) {
            return true;
        };
    } else {
        // for the matrix, not 1d, below the largest number of diagonal, and the
        // total of its colums is larger than the size of diagonal
        if (largerPoint.row == MAXROW - 1 && startRow != endRow &&
            endCol - startCol > diagonal.size() && largerPoint.val <= val) {
            // jumps 3 colums to the right, making matrix smaller, until finding
            // out the proper largerpoint.
            return elementSearch(val, startRow, endRow,
                                 startCol + diagonal.size(), endCol, rowV,
                                 colV);

        } else {
            return elementSearch(val, smallerPoint.row + 1, endRow, startCol,
                                 largerPoint.col - 1, rowV, colV) ||
                   elementSearch(val, startRow, largerPoint.row - 1,
                                 smallerPoint.col + 1, endCol, rowV, colV);
        }
    }

    return false;
}

void Matrix::verifyCornerElements() {
    if (elementSearch(matrix[0][0], 0, MAXROW - 1, 0, MAXCOL - 1, 0, 0)) {
        cout << "Found data [0][0] is true" << endl;
    }

    if (elementSearch(matrix[0][MAXCOL - 1], 0, MAXROW - 1, 0, MAXCOL - 1, 0,
                      MAXCOL - 1)) {
        cout << "Found data [0][MAXCOL-1] is true" << endl;
    }

    if (elementSearch(matrix[MAXROW - 1][0], 0, MAXROW - 1, 0, MAXCOL - 1,
                      MAXROW - 1, 0)) {
        cout << "Found data [MAXROWS-1][0] is true" << endl;
    }

    if (elementSearch(matrix[MAXROW - 1][MAXCOL - 1], 0, MAXROW - 1, 0,
                      MAXCOL - 1, MAXROW - 1, MAXCOL - 1)) {
        cout << "Found data [MAXROWS-1][MAXCOLS-1] is true" << endl;
    }
}

void Matrix::verifyAllSearchedElements() {
    int totalElementsFound = 0;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (elementSearch(matrix[i][j], 0, MAXROW - 1, 0, MAXCOL - 1, i,
                              j)) {
                totalElementsFound++;
            }
        }
    }
    cout << "Verify that we can find every data value in the array" << endl;
    if (totalElementsFound == MAXROW * MAXCOL) {
        cout << "Found them all!\n" << endl;
        cout << totalElementsFound << endl;
    } else {
        cout << totalElementsFound << endl;
        cout << "There are something wrongs\n" << endl;
    }
};

void Matrix::verifyFoundWrongElements(int value, int rowV, int colV) {
    cout << "Verify that we don't find anything that isn't in the array"
         << endl;
    if (!elementSearch(value, 0, MAXROW - 1, 0, MAXCOL - 1, rowV, colV)) {
        cout << "Everything Worked!\n" << endl;
    } else {
        cout << "There are something wrongs\n" << endl;
    }
}

int main() {
    vector<vector<int>> arr2D = {
        {1, 5, 7, 9, 17, 22, 27, 31},
        {3, 5, 9, 9, 17, 29, 31, 31},
        {6, 7, 9, 11, 22, 36, 68, 99},
        {10, 13, 16, 30, 55, 100, 171, 270},
        {18, 22, 24, 33, 63, 105, 171, 278},
        {24, 26, 33, 40, 69, 110, 172, 281},
        {27, 32, 40, 46, 69, 119, 178, 286},
        {28, 41, 44, 55, 77, 123, 184, 287},
        {30, 43, 47, 55, 79, 129, 186, 292},
        {31, 52, 55, 56, 81, 132, 186, 292},
    };
    Matrix matrix(arr2D);

    matrix.displayMatrix();
    matrix.verifyCornerElements();

    matrix.verifyAllSearchedElements();
    matrix.verifyFoundWrongElements(298, 1, 2);

    return 0;
}