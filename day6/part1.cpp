#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <string>
#include <tuple>

using namespace std;

struct Position {
    int x, y;
    bool operator<(const Position& other) const {
        return tie(x, y) < tie(other.x, other.y);
    }
};

int main() {
    // File input
    ifstream infile("input.txt");
    if (!infile) {
        cerr << "Error: Unable to open file!" << endl;
        return 1;
    }

    vector<string> map;
    string line;
    while (getline(infile, line)) {
        map.push_back(line);
    }
    infile.close();

    // Directions: {up, right, down, left}
    vector<pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    int dir = 0; // Start facing up
    int rows = map.size();
    int cols = map[0].size();
    int start_x = 0, start_y = 0;

    // Find the starting position and direction
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (map[i][j] == '^') {
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    set<Position> visited;
    int x = start_x, y = start_y;

    while (x >= 0 && x < rows && y >= 0 && y < cols) {
        visited.insert({x, y});
        int next_x = x + directions[dir].first;
        int next_y = y + directions[dir].second;

        if (next_x >= 0 && next_x < rows && next_y >= 0 && next_y < cols &&
            map[next_x][next_y] == '#') {
            // Turn right
            dir = (dir + 1) % 4;
        } else {
            // Move forward
            x = next_x;
            y = next_y;
        }
    }

    cout << "Distinct positions visited: " << visited.size() << endl;
    return 0;
}
