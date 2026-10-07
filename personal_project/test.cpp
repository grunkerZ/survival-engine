#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream inFile; 
    inFile.open("C:\\git\\personal_project\\prefabs\\x_path.txt");
    if (!inFile) { cout << "Failed to open" << endl; return 1; }
    int val;
    inFile >> val;
    cout << val << endl;
    return 0;
}
