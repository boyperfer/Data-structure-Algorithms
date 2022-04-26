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
    bool binarySearchDiagonal(vector<Point>, int, int, int, int &, int &, int,
                              int);

   public:
    Matrix(vector<vector<int>>);
    bool elementSearch(int, int, int, int, int, int, int);
    void displayMatrix();
    void verifyCornerElements();
    void verifyAllSearchedElements();
    void verifyFoundWrongElements(int, int, int);
};

bool Matrix::binarySearchDiagonal(vector<Point> arr, int val, int left,
                                  int right, int &smallerV, int &largerV,
                                  int rowV, int colV) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        // If the value is at the middle
        if (arr[mid].val == val && arr[mid].row == rowV &&
            arr[mid].col == colV) {
            return true;
        }

        // If the value is smaller than mid, then it can only be in left
        // subarray
        if (arr[mid].val > val)
            return binarySearchDiagonal(arr, val, left, mid - 1, smallerV,
                                        largerV, rowV, colV);

        // Else the value can only be present in right subarray
        return binarySearchDiagonal(arr, val, mid + 1, right, smallerV, largerV,
                                    rowV, colV);
    }
    // Because the loop end after left > right. So there would be two numbers.
    // One is largen than the value, which would return to the very end right,
    // and the other is larger than the value, which would return to the very
    // end left

    // Assign the left to the larger and the right to the
    //  smaller.
    if (left >= 0 && right >= 0) {
        largerV = left;
        smallerV = right;
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
    // If the number of row is larger than the number of col. The diagonal would
    // be based on the number of col.
    if (endRow - startRow > endCol - startCol) {
        for (int i = 0; i <= endCol - startCol; i++) {
            Point p1 = {startRow + i, startCol + 1,
                        matrix[startRow + i][startCol + i]};
            diagonal.push_back(p1);
        }
        // Else the diagonal would be based on the number of row.
    } else {
        for (int i = 0; i <= endRow - startRow; i++) {
            Point p1 = {startRow + i, startCol + 1,
                        matrix[startRow + i][startCol + i]};
            diagonal.push_back(p1);
        }
    }

    int smallerV = 0;  // the smaller of the value
    int largerV = 0;   // the larger of the value

    // Search the value on the diagonal. if found return true. if not, there
    // will be two values and assign it to smallerV and largerV.
    if (binarySearchDiagonal(diagonal, val, 0, diagonal.size() - 1, smallerV,
                             largerV, rowV, colV)) {
        return true;
    } else {
        // Create two points with value corresspoding to its row and col
        Point smallerPoint;
        Point largerPoint;

        // if the smallerPoint is in the matrix in which its row and col do not
        // excess the max col and max row of the matrix.
        if (startCol + smallerV <= MAXCOL - 1 &&
            startRow + smallerV <= MAXROW - 1) {
            smallerPoint = {startRow + smallerV, startCol + smallerV,
                            matrix[startRow + smallerV][startCol + smallerV]};
        }

        // if the largerPoint is in the matrix in which its row and col do not
        // excess the max col and max row of the matrix.
        if (startCol + largerV <= MAXCOL - 1 &&
            startRow + largerV <= MAXROW - 1) {
            largerPoint = {startRow + largerV, startCol + largerV,
                           matrix[startRow + largerV][startCol + largerV]};
        }
        // for matrix 2x2 and the largerPoint's col would excess the max
        // col of the matrix, which is on the top right matrix 2x2.
        else if (startCol + largerV >= MAXCOL - 1 && startRow == 0 &&
                 endRow == 1 && startCol + 1 == endCol) {
            smallerPoint = {startRow + smallerV, startCol,
                            matrix[startRow + smallerV][startCol]};
            largerPoint = {startRow + smallerV, endCol,
                           matrix[startRow + smallerV][endCol]};
        }
        // the largerPoint would be present on the next col of the smaller
        // point.
        else {
            largerPoint = {smallerPoint.row, smallerPoint.col + 1,
                           matrix[smallerPoint.row][smallerPoint.col + 1]};
        }

        // if the largerPoint's value is equal to the value
        if (largerPoint.val == val) {
            // return true if its row and col match the value's col and row
            if (largerPoint.row == rowV && largerPoint.col == colV) {
                return true;
            }
        }

        // if the smaller's value is equal to the value
        if (smallerPoint.val == val) {
            // return true if its row and col match the value's col and row
            if (smallerPoint.row == rowV && smallerPoint.col == colV) {
                return true;
            }
            // To this matrix. As there are some elements that have the same
            // value. So the value, which is on top of the smaller, value
            // would never be inspected. So if there is a difference by one row
            // between the two. Return true
            // Let m - is the value.
            /* x x x 2 2 2
               x x m 2 2 2
               x x S 2 2 2
               1 1 1 L x x
               1 1 1 x x x */
            else if (smallerPoint.col == colV &&
                     abs(smallerPoint.row - rowV) == 1) {
                return true;
            }
        }

        // Search the
        // Let L - is the larger of the value. and S - is the smaller of the
        // value
        // we would rule out everything that is smaller than S and largen than L
        // (marked by x)
        //  so we inspect a rectangle which goes below of S's row and the left
        //  of L's col (marked by 1) and a rectangle which goes on top of L's
        //  row and the right of S's col (marked by 2)
        /* x x x 2 2 2
           x x x 2 2 2
           x x S 2 2 2
           1 1 1 L x x
           1 1 1 x x x */
        if (elementSearch(val, smallerPoint.row + 1, endRow, startCol,
                          largerPoint.col - 1, rowV, colV)) {
            return true;
        }
        return elementSearch(val, startRow, largerPoint.row - 1,
                             smallerPoint.col + 1, endCol, rowV, colV);
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
    } else {
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
        {3, 5, 9, 10, 17, 29, 31, 31},
        {6, 7, 9, 13, 22, 36, 68, 99},
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