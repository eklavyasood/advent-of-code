#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <queue>
#include <tuple>
#include <map>

using namespace std;

struct Position {
    int x, y, dir; // x, y, and direction
    bool operator<(const Position& other) const {
        return tie(x, y, dir) < tie(other.x, other.y, other.dir);
    }
};

// Simulate the guard's path and return the visited positions
set<pair<int, int>> simulatePath(vector<string>& map, int start_x, int start_y, vector<pair<int, int>>& directions) {
    set<pair<int, int>> visited;
    int rows = map.size();
    int cols = map[0].size();
    int x = start_x, y = start_y, dir = 0;

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
    return visited;
}

bool createsLoop(vector<string>& map, int start_x, int start_y, vector<pair<int, int>>& directions) {
    set<Position> visitedStates;
    int rows = map.size();
    int cols = map[0].size();
    int x = start_x, y = start_y, dir = 0;

    while (x >= 0 && x < rows && y >= 0 && y < cols) {
        Position current = {x, y, dir};
        if (visitedStates.count(current)) {
            return true; // Loop detected
        }
        visitedStates.insert(current);

        int next_x = x + directions[dir].first;
        int next_y = y + directions[dir].second;

        if (next_x >= 0 && next_x < rows && next_y >= 0 && next_y < cols &&
            map[next_x][next_y] == '#') {
            dir = (dir + 1) % 4;
        } else {
            x = next_x;
            y = next_y;
        }
    }
    return false; // No loop
}

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
    int start_x = 0, start_y = 0;

    // Find the starting position
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if (map[i][j] == '^') {
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    // Simulate the guard's path to find reachable positions
    set<pair<int, int>> reachable = simulatePath(map, start_x, start_y, directions);

    int loopCount = 0;

    // Test each reachable position
    for (const auto& pos : reachable) {
        int i = pos.first, j = pos.second;
        if (!(i == start_x && j == start_y)) { // Skip the starting position
            // Place obstruction
            map[i][j] = '#';
            if (createsLoop(map, start_x, start_y, directions)) {
                loopCount++;
            }
            // Remove obstruction
            map[i][j] = '.';
        }
    }

    cout << "Number of positions causing a loop: " << loopCount << endl;
    return 0;
}
