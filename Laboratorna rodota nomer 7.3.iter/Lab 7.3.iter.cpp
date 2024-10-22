// Lab 7.3.iter

#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High);
void Input(int** a, const int rowCount, const int colCount);
void Print(int** a, const int rowCount, const int colCount);
bool Part1_Count(int** a, const int rowCount, const int colCount, int& count);
void Part2_SaddlePoint(int** a, const int rowCount, const int colCount);
bool IsMaxInRowN(int** a, const int n, const int k, const int colCount);
bool IsMinInColK(int** a, const int n, const int k, const int rowCount);
void SortColumnsByCharacteristic(int** a, const int rowCount, const int colCount);
int SumColumnsWithNegative(int** a, const int rowCount, const int colCount);

int main() {
    srand((unsigned)time(NULL));
    int Low = -17;
    int High = 15;
    int rowCount, colCount;
    cout << "rowCount = "; cin >> rowCount;
    cout << "colCount = "; cin >> colCount;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    // Create(a, rowCount, colCount, Low, High);
    Input(a, rowCount, colCount);
    Print(a, rowCount, colCount);

    // Part 1: Count zero elements
    int count = 0;
    if (Part1_Count(a, rowCount, colCount, count))
        cout << "count = " << count << endl;
    else
        cout << "there are no zero elements" << endl;
    cout << endl;

    // Part 2: Saddle Point
    Part2_SaddlePoint(a, rowCount, colCount);
    cout << endl;

    // Sort columns by characteristic
    SortColumnsByCharacteristic(a, rowCount, colCount);
    cout << "Matrix after sorting columns by characteristic:" << endl;
    Print(a, rowCount, colCount);
    cout << endl;

    // Sum of columns with at least one negative element
    int sum = SumColumnsWithNegative(a, rowCount, colCount);
    cout << "Sum of elements in columns with at least one negative element: " << sum << endl;

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;
    return 0;
}

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High) {
    for (int i = 0; i < rowCount; i++)
        for (int j = 0; j < colCount; j++)
            a[i][j] = Low + rand() % (High - Low + 1);
}

void Input(int** a, const int rowCount, const int colCount) {
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            cout << "a[" << i << "][" << j << "] = ";
            cin >> a[i][j];
        }
        cout << endl;
    }
}

void Print(int** a, const int rowCount, const int colCount) {
    cout << endl;
    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++)
            cout << setw(4) << a[i][j];
        cout << endl;
    }
    cout << endl;
}

bool Part1_Count(int** a, const int rowCount, const int colCount, int& count) {
    bool result = false;
    count = 0;
    int k_zero;
    for (int j = 0; j < colCount; j++) {
        k_zero = 0;
        for (int i = 0; i < rowCount; i++)
            if (a[i][j] == 0) {
                result = true;
                k_zero++;
                break;
            }
        if (k_zero > 0) {
            for (int i = 0; i < rowCount; i++)
                if (a[i][j] > 0)
                    count++;
        }
    }

    return result;
}

bool IsMaxInRowN(int** a, const int n, const int k, const int colCount) {
    for (int j = 0; j < colCount; j++)
        if (a[n][j] > a[n][k]) {
            return false;
        }
    return true;
}

bool IsMinInColK(int** a, const int n, const int k, const int rowCount) {
    for (int i = 0; i < rowCount; i++)
        if (a[i][k] < a[n][k]) {
            return false;
        }
    return true;
}

void Part2_SaddlePoint(int** a, const int rowCount, const int colCount) {
    cout << "Saddle points: max in row & min in col" << endl;
    cout << setw(4) << "No" << setw(6) << "Row" << setw(6) << "Col" << endl;
    int No = 0;
    for (int n = 0; n < rowCount; n++)
        for (int k = 0; k < colCount; k++)
            if (IsMaxInRowN(a, n, k, colCount) && IsMinInColK(a, n, k, rowCount)) {
                cout << setw(4) << ++No << setw(6) << n << setw(6) << k << endl;
            }
}

void SortColumnsByCharacteristic(int** a, const int rowCount, const int colCount) {
    // Calculate characteristics
    int* characteristics = new int[colCount];
    for (int j = 0; j < colCount; j++) {
        characteristics[j] = 0;
        for (int i = 0; i < rowCount; i++) {
            if (a[i][j] < 0 && a[i][j] % 2 != 0) { // Negative odd elements
                characteristics[j] += abs(a[i][j]);
            }
        }
    }

    // Sort columns based on characteristics using bubble sort
    for (int j = 0; j < colCount - 1; j++) {
        for (int k = 0; k < colCount - j - 1; k++) {
            if (characteristics[k] > characteristics[k + 1]) {
                // Swap characteristics
                swap(characteristics[k], characteristics[k + 1]);

                // Swap columns
                for (int i = 0; i < rowCount; i++) {
                    swap(a[i][k], a[i][k + 1]);
                }
            }
        }
    }

    delete[] characteristics;
}

int SumColumnsWithNegative(int** a, const int rowCount, const int colCount) {
    int sum = 0;
    for (int j = 0; j < colCount; j++) {
        bool hasNegative = false;
        for (int i = 0; i < rowCount; i++) {
            if (a[i][j] < 0) {
                hasNegative = true;
                break;
            }
        }
        if (hasNegative) {
            for (int i = 0; i < rowCount; i++) {
                sum += a[i][j];
            }
        }
    }
    return sum;
}
