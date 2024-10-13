#include <iostream>
#include <iomanip>
#include <time.h>
using namespace std;

void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i = 0, int j = 0);
void Print(int** a, const int rowCount, const int colCount, int i = 0, int j = 0);
void Sort(int** a, const int rowCount, const int colCount, int i0 = 0, int i1 = 0);
void ChangeColumns(int** a, const int col1, const int col2, const int rowCount, int i = 0);
void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int i = 0, int j = 0);

int main() {
    srand((unsigned)time(NULL));

    int Low = 18;
    int High = 74;
    const int rowCount = 9;
    const int colCount = 6;

    int** a = new int* [rowCount];
    for (int i = 0; i < rowCount; i++)
        a[i] = new int[colCount];

    Create(a, rowCount, colCount, Low, High);

    cout << "Initial matrix:" << endl;
    Print(a, rowCount, colCount);

    Sort(a, rowCount, colCount);

    cout << "Sorted matrix:" << endl;
    Print(a, rowCount, colCount);

    int S = 0, k = 0;
    Calc(a, rowCount, colCount, S, k);
    cout << "Sum of elements (even, not divisible by 7): " << S << endl;
    cout << "Count of elements: " << k << endl;

    cout << "Modified matrix after calculations:" << endl;
    Print(a, rowCount, colCount);

    for (int i = 0; i < rowCount; i++)
        delete[] a[i];
    delete[] a;

    return 0;
}


void Create(int** a, const int rowCount, const int colCount, const int Low, const int High, int i, int j) {
    if (i >= rowCount) return;
    if (j >= colCount) {
        Create(a, rowCount, colCount, Low, High, i + 1, 0);
        return;
    }
    a[i][j] = Low + rand() % (High - Low + 1);
    Create(a, rowCount, colCount, Low, High, i, j + 1);
}


void Print(int** a, const int rowCount, const int colCount, int i, int j) {
    if (i >= rowCount) return;
    if (j >= colCount) {
        cout << endl;
        Print(a, rowCount, colCount, i + 1, 0);
        return;
    }
    cout << setw(4) << a[i][j];
    Print(a, rowCount, colCount, i, j + 1);
}


void Sort(int** a, const int rowCount, const int colCount, int i0, int i1) {
    if (i0 >= colCount - 1) return;
    if (i1 >= colCount - i0 - 1) {
        Sort(a, rowCount, colCount, i0 + 1, 0);
        return;
    }
    if ((a[0][i1] > a[0][i1 + 1])
        || (a[0][i1] == a[0][i1 + 1] && a[1][i1] < a[1][i1 + 1])
        || (a[0][i1] == a[0][i1 + 1] && a[1][i1] == a[1][i1 + 1] && a[2][i1] < a[2][i1 + 1])) {
        ChangeColumns(a, i1, i1 + 1, rowCount);
    }
    Sort(a, rowCount, colCount, i0, i1 + 1);
}


void ChangeColumns(int** a, const int col1, const int col2, const int rowCount, int i) {
    if (i >= rowCount) return;
    int tmp = a[i][col1];
    a[i][col1] = a[i][col2];
    a[i][col2] = tmp;
    ChangeColumns(a, col1, col2, rowCount, i + 1);
}


void Calc(int** a, const int rowCount, const int colCount, int& S, int& k, int i, int j) {
    if (i >= rowCount) return;
    if (j >= colCount) {
        Calc(a, rowCount, colCount, S, k, i + 1, 0);
        return;
    }
    if (a[i][j] % 2 == 0 && a[i][j] % 7 != 0) {
        S += a[i][j];
        k++;
        a[i][j] = 0; 
    }
    Calc(a, rowCount, colCount, S, k, i, j + 1);
}
