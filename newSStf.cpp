#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int shortestSeekTimeFirst(const vector<int>& request, int head) {
    int seekCount = 0;
    vector<bool> visited(request.size(), false);
    vector<int> seekSequence;

    for (int i = 0; i < request.size(); ++i) {
        int minDistance = INT_MAX;
        int index = -1;

        for (int j = 0; j < request.size(); ++j) {
            if (!visited[j] && abs(request[j] - head) < minDistance) {
                index = j;
                minDistance = abs(request[j] - head);
            }
        }

        visited[index] = true;
        seekCount += minDistance;
        head = request[index];
        seekSequence.push_back(head);
    }

    cout << "Total number of seek operations = " << seekCount << endl;
    cout << "Seek sequence is: ";
    for (int i : seekSequence) {
        cout << i << " ";
    }
    cout << endl;

    return seekCount;
}

int main() {
    vector<int> request = {176, 79, 34, 60, 92, 11, 41, 114};
    int head = 50;

    shortestSeekTimeFirst(request, head);

    return 0;
}
