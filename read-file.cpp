// Hoang Nguyen
// TARRANT COUNTY COLLEGE
// COSC 2436-86002
// Program 2
// Written for GCC
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

void displayList(vector<float> arr) {
    vector<float>::iterator ptr;

    cout << fixed << setprecision(1);
    cout << "[";
    for (ptr = arr.begin(); ptr < arr.end(); ptr++) {
        if ((ptr != arr.end()) && (next(ptr) == arr.end())) {
            cout << *ptr;
        } else {
            cout << *ptr << " ";
        }
    }
    cout << "]" << endl;
}

float computeAverage(vector<float> arr) {
    vector<float>::iterator ptr;
    float sum;
    for (ptr = arr.begin(); ptr < arr.end(); ptr++) {
        sum += *ptr;
    }
    cout << fixed << setprecision(4);
    return sum / arr.size();
}

float computeDeviation(vector<float> arr) {
    vector<float>::iterator ptr;
    float average = computeAverage(arr);
    // Compute sum squared differences with average.
    float sqDiff = 0;
    for (ptr = arr.begin(); ptr < arr.end(); ptr++) {
        sqDiff += pow(*ptr - average, 2);
    }
    cout << fixed << setprecision(4);
    return sqrt(sqDiff / (arr.size() - 1));
}

// Remove values with more than two standard deviation away from average
void removeTheVal(vector<float> &arr) {
    vector<float>::iterator ptr;
    float average = computeAverage(arr);
    float deviation = computeDeviation(arr);
    float theLowest = average - 2 * deviation;
    float theHighest = average + 2 * deviation;
    cout << "Removing values outside the range " << theLowest << " to "
         << theHighest << endl;
    for (ptr = arr.begin(); ptr < arr.end(); ptr++) {
        if (*ptr < theLowest || *ptr > theHighest) {
            cout << fixed << setprecision(1);
            cout << "Removed Value " << noshowpoint << *ptr << endl;
            ptr = arr.erase(ptr);
        }
    }
}

int main() {
    ifstream ifile;               // an object to read a file
    string line;                  // to read a line
    float val;                    // to convert string to float
    vector<float> arr;            // a vector
    vector<float>::iterator ptr;  // an iterator to a vector

    ifile.open("data2.txt");
    cout << "The data is:" << endl;
    while (ifile >> line) {
        cout << line << " ";
        // read the data of the file into the vector
        stringstream in(line);
        // Read the data from the stringstream object and steam it into float
        in >> val;
        arr.push_back(val);
    }
    cout << endl;

    ifile.close();
    cout << "Finished reading line" << endl;
    cout << "The list is originally: ";
    displayList(arr);
    cout << "The average is: " << computeAverage(arr) << endl;
    cout << "The standard Deviation: " << computeDeviation(arr) << endl;
    removeTheVal(arr);
    displayList(arr);
    cout << "The average with extreme values removed is: "
         << computeAverage(arr) << endl;
    cout << "The standard Deviation with extreme values removed is: "
         << computeDeviation(arr) << endl;

    return 0;
}