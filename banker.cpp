// banker.cpp
// Compile: g++ -std=c++17 banker.cpp -o banker
// Usage: ./banker input.txt

#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string infile = (argc >= 2) ? argv[1] : "input/input.txt";
    ifstream fin(infile);
    if (!fin.is_open()) {
        cerr << "Error: cannot open input file: " << infile << "\n";
        return 1;
    }

    int nProcesses, nResources;
    fin >> nProcesses >> nResources;
    if (!fin) {
        cerr << "Error: failed to read number of processes/resources.\n";
        return 1;
    }

    vector<long long> total(nResources);
    for (int j = 0; j < nResources; ++j) fin >> total[j];

    vector<vector<long long>> alloc(nProcesses, vector<long long>(nResources));
    vector<vector<long long>> maxi(nProcesses, vector<long long>(nResources));
    // Read Allocation matrix
    for (int i = 0; i < nProcesses; ++i) {
        for (int j = 0; j < nResources; ++j) fin >> alloc[i][j];
    }
    // Read Max matrix
    for (int i = 0; i < nProcesses; ++i) {
        for (int j = 0; j < nResources; ++j) fin >> maxi[i][j];
    }

    // Compute Available = Total - sum(Allocation)
    vector<long long> available(nResources, 0);
    for (int j = 0; j < nResources; ++j) {
        long long sumAlloc = 0;
        for (int i = 0; i < nProcesses; ++i) sumAlloc += alloc[i][j];
        available[j] = total[j] - sumAlloc;
    }

    // Compute Need = Max - Allocation
    vector<vector<long long>> need(nProcesses, vector<long long>(nResources));
    for (int i = 0; i < nProcesses; ++i)
        for (int j = 0; j < nResources; ++j)
            need[i][j] = maxi[i][j] - alloc[i][j];

    // Output initial data summary
    cout << "Processes: " << nProcesses << ", Resources: " << nResources << "\n";
    cout << "Total resources: ";
    for (auto v : total) cout << v << " ";
    cout << "\nAvailable: ";
    for (auto v : available) cout << v << " ";
    cout << "\n\nAllocation matrix:\n";
    for (int i = 0; i < nProcesses; ++i) {
        cout << "P" << i << ": ";
        for (int j = 0; j < nResources; ++j) cout << alloc[i][j] << " ";
        cout << "\n";
    }

    cout << "\nMax matrix:\n";
    for (int i = 0; i < nProcesses; ++i) {
        cout << "P" << i << ": ";
        for (int j = 0; j < nResources; ++j) cout << maxi[i][j] << " ";
        cout << "\n";
    }

    cout << "\nNeed matrix:\n";
    for (int i = 0; i < nProcesses; ++i) {
        cout << "P" << i << ": ";
        for (int j = 0; j < nResources; ++j) cout << need[i][j] << " ";
        cout << "\n";
    }

    // Safety algorithm
    vector<bool> finish(nProcesses, false);
    vector<long long> work = available;
    vector<int> safeSeq;
    bool progress = true;

    while (progress) {
        progress = false;
        for (int i = 0; i < nProcesses; ++i) {
            if (finish[i]) continue;
            bool canRun = true;
            for (int j = 0; j < nResources; ++j) {
                if (need[i][j] > work[j]) { canRun = false; break; }
            }
            if (canRun) {
                // Simulate finishing: release resources
                for (int j = 0; j < nResources; ++j)
                    work[j] += alloc[i][j];
                finish[i] = true;
                safeSeq.push_back(i);
                progress = true;
            }
        }
    }

    bool safe = all_of(finish.begin(), finish.end(), [](bool v) { return v; });

    cout << "\nResult: ";
    if (safe) {
        cout << "System is in a SAFE state.\nSafe sequence: ";
        for (size_t k = 0; k < safeSeq.size(); ++k) {
            cout << "P" << safeSeq[k];
            if (k + 1 < safeSeq.size()) cout << " -> ";
        }
        cout << "\n";
    } else {
        cout << "System is NOT in a safe state.\n";
    }

    fin.close();
    return 0;
}
