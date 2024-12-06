#include <vector>
#include <iostream>
#include <fstream>
#include <iostream>

int searchGrid(const std::vector<std::vector<char>>& grid, std::string search, int row, int col, const std::vector<std::vector<int>> & movePos) {
    int count = 0;
    for (const auto& m : movePos) {
        int idx = 0;
        int new_row = row;
        int new_col = col;

        for (; idx < search.size(); ++idx) {
            if (new_row < 0 || new_col < 0 || new_row >= grid.size() || new_col >= grid[0].size()) break;

            if (grid[new_row][new_col] != search[idx]) break;
            new_row += m[0];
            new_col += m[1];
        }

        if (idx >= search.size()) count++;
    }
    return count;
}

int checkXmas(const std::vector<std::vector<char>>& grid) {
    const std::vector<std::vector<int>> movePos = {{0,1},{0,-1},{1,0},{-1,0},{-1,-1},{1,1},{-1,1},{1,-1}};
    int count = 0;
    for (int r=0; r<grid.size(); ++r) {
        for (int c=0; c<grid[0].size(); ++c) {
            count += searchGrid(grid, "XMAS", r, c, movePos);
        }
    }
    return count;
}

int main() {
  std::fstream file("input.txt");
  std::string line;
  std::vector<std::vector<char>> grid;
    while (getline(file, line)) {
      std::vector<char> row (line.begin(), line.end());
        grid.emplace_back(row);
    }

    std::cout << checkXmas(grid) << std::endl;
}
