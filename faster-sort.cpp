// Hoang Nguyen
// TARRANT COUNTY COLLEGE
// COSC 2436-86002
// Program 3
// Written for GCC
#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace std::chrono;

const int ARRAY_SIZE = 10000;
const int RANGE = 100000;

// A class of creating random numbers and all kinds of sort function associated
// with it
class ArrayList {
   private:
    vector<int> arr;
    int nowayhome(int, int, int);

   public:
    ArrayList(int, int);
    void selectionSort();
    void insertionSort();
    void shellSort();
};

ArrayList::ArrayList(int sizeArr, int range) {
    for (int i = 0; i < sizeArr; i++) {
        int num = rand() % range + 1;
        arr.push_back(num);
    }
};

void ArrayList::selectionSort() {
    int tem;  // temporary variable holder;

    // Tranverse through all elements of the array
    for (int i = 0; i < arr.size(); i++) {
        // Find the minimum elements
        int minIndex = i;
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum elements to the current value at i
        tem = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = tem;
    }
};

void ArrayList::insertionSort() {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;  // the hold postion where the key is to be inserted

        // Move all elements below the key that are greater than the key to one
        // position ahead.
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];  // Make room
            j--;
        }

        arr[j + 1] = key;  // Insert the key to the current hole
    }
    cout << arr.size() << endl;
}

void ArrayList::shellSort() {
    for (int space = arr.size() / 2; space > 0; space /= 2) {
        // Start with a big size of space, and then reduced by 2 for each
        // loop
        for (int i = space; i < arr.size(); i += 1) {
            // Do an insertion sort for this space size.
            int key = arr[i];  // Save the next insertion in key and make room
                               // for position at i.
            int j;

            // Shift earlier space-sorted elements up until the correct
            // location for the key is found
            for (j = i; j >= space && arr[j - space] > key; j -= space) {
                arr[j] = arr[j - space];
            }

            //  Insert the key in its correct location
            arr[j] = key;
        }
    }
}

// calculateTime takes a pointer to member sort functions of ArrayList, a
// pointer to an instance of it as an implicit parameter, and a name of a sort
// function to calculate the performance time
void calculateTime(void (ArrayList::*sort)(), ArrayList *arr, string name) {
    // The starting timepoint
    auto start = high_resolution_clock::now();

    // Call the member sort function pointer toghether with the instance pointer
    (arr->*sort)();

    // The ending timepoint
    auto stop = high_resolution_clock::now();
    duration<float> duration = stop - start;  // Get duration in second

    // Fixed to 3 decimal places
    cout << fixed << setprecision(3);
    cout << "The time performance of " << name << " is: " << duration.count()
         << " sec" << endl;
}
int main() {
    int cao;
    cout << "Create 10,000 random numbers from 0 to 100,000" << endl;
    string input;  // User input
    cout << "What is the method you want to sort (Selection, Insertion, "
            "Shell,Quit)? ";

    // Get input from user
    getline(cin, input);

    // Loop until QUIT
    while (input != "Quit") {
        if (input == "Selection") {
            // Create an instance of ArrayList
            ArrayList arr(ARRAY_SIZE, RANGE);

            // Call calculateTime in which selectionSort's address, arr's
            // address and the name of the input method are passed.
            calculateTime(&ArrayList::selectionSort, &arr, "selection sort");
        } else if (input == "Insertion") {
            // Repeat the same as above but the arguments would be passed
            // corresponding to the input method.
            ArrayList arr(ARRAY_SIZE, RANGE);
            calculateTime(&ArrayList::insertionSort, &arr, "insertion sort");
        } else if (input == "Shell") {
            // Repeat the same as above but the arguments would be passed
            // corresponding to the input method.
            ArrayList arr(ARRAY_SIZE, RANGE);
            calculateTime(&ArrayList::shellSort, &arr, "shell sort");
        } else {
            // If diffrent input was passed, loop again.
            cout << "What is the method you want to sort (Selection, "
                    "Insertion, Shell, "
                    "Quit)? ";
            getline(cin, input);
        }
        cout << "What is the method you want to sort (Selection, Insertion, "
                "Shell, Quit)? ";
        getline(cin, input);
    }

    cout << "Good Bye" << endl;

    return 0;
}
