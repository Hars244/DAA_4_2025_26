#include <bits/stdc++.h>
using namespace std;
using namespace chrono;

long long operations = 0;
int maxDepth = 0;

void complexRec(int n, int depth) {
    maxDepth = max(maxDepth, depth);

    if (n <= 2) {
        operations++;
        return;
    }

    int p = n;
    while (p > 0) {
        vector<int> temp(n);
        for (int i = 0; i < n; i++) {
            temp[i] = i ^ p;
            operations++;
        }
        p >>= 1;
        operations++;
    }

    vector<int> small(n);
    for (int i = 0; i < n; i++) {
        small[i] = i * i;
        operations++;
    }

    if (n % 3 == 0) {
        reverse(small.begin(), small.end());
        operations += n;
    } else {
        reverse(small.begin(), small.end());
        operations += n;
    }

    complexRec(n / 2, depth + 1);
    complexRec(n / 2, depth + 1);
    complexRec(n / 2, depth + 1);
}

int main() {
    vector<int> inputs = {16, 32, 64, 128};

    for (int n : inputs) {
        operations = 0;
        maxDepth = 0;

        auto start = high_resolution_clock::now();

        complexRec(n, 1);

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);

        cout << "Operations = " << operations << endl;
        cout << "Max Depth = " << maxDepth << endl;
        cout << "Time: " << duration.count() << " microseconds" << endl;
        
    
    }
    cout<<"recurence relation: T(n) = 3T(n/2) + O(nlogn)"<<endl;
    cout<<"By Master theorem, T(n) = Θ(n^log2(3)) = Θ(n^1.585)"<<endl;

    return 0;
}
