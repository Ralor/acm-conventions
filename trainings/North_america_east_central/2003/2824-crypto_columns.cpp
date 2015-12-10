#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

char grid[100][100];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    string key, cipher;
    while (cin >> key >> cipher) {
        int n = (int)key.length();
        int rows = (int)cipher.length() / n;
        for (int i = 0; i < n; i++) {
            string::iterator it = min_element(key.begin(), key.end());
            int col = it - key.begin();
            //cout << *it << '\n';
            *it = char('Z' + 1);
            for (int row = 0; row < rows; row++)
                grid[row][col] = cipher[i * rows + row]/*, cout << grid[row][col]*/;
            //cout << '\n';
        }
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < n; j++)
                cout << grid[i][j];
        cout << '\n';
    }
}
