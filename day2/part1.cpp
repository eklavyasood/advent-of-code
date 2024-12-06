#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

void checkSafety(std::vector<int> line);

int safeCount = 0;

bool readFile(std::string filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "The input file could not be read: " << filename << std::endl;
    return false;
  }

  std::vector<std::vector<int>> allLines;

  std::string line;
  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::vector<int> numbers;
    int number;

    while (iss >> number)
      numbers.push_back(number);

    allLines.push_back(numbers);
  }

  // check for every line
  for (size_t i = 0; i < allLines.size(); i++) {
    checkSafety(allLines[i]);
  }

  file.close();
  return true;
}

void checkSafety(std::vector<int> line) {
  // ascending order lines
  if (std::is_sorted(line.begin(), line.end())) {
    for (size_t i = 0; i < line.size() - 1; i++) {
      if (line[i] + 3 < line[i+1] || line[i] == line[i+1]) {
        std::cout << "Unsafe: Ascending" << std::endl;
        return;
      }
    }
    safeCount++;
    std::cout << "Safe: Ascending" << std::endl;
  }

  // descending order lines
  else if (std::is_sorted(line.rbegin(), line.rend())) {
    for (size_t i = 0; i < line.size() - 1; i++) {
      if (line[i] > line[i+1] + 3 || line[i] == line[i+1]) {
        std::cout << "Unsafe: Descending" << std::endl;
        return;
      }
    }
    safeCount++;
    std::cout << "Safe: Descending" << std::endl;
  }

  // unordered lines
  else {
   std::cout << "Unsafe: Unordered" << std::endl;
   return;
  }
}

int main() {
  const std::string filename = "input.txt";

  if (!readFile(filename)) {
    std::cout << "the file wasn't read: " << filename << std::endl;
    return 1;
  }

  std::cout << safeCount << std::endl;

  return 0;
}
