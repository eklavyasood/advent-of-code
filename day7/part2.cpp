#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>

// Function to concatenate two numbers
long long concatenate(long long a, long long b) {
  long long bDigits = std::log10(b) + 1;
  return a * std::pow(10, bDigits) + b;
}

// Function to evaluate an equation given numbers and operators
long long evaluateEquation(const std::vector<long long>& numbers, const std::vector<char>& operators) {
  long long result = numbers[0];
  for (size_t i = 0; i < operators.size(); ++i) {
    if (operators[i] == '+') {
      result += numbers[i + 1];
    } else if (operators[i] == '*') {
      result *= numbers[i + 1];
    } else if (operators[i] == '|') { // Represent concatenation as '|'
      result = concatenate(result, numbers[i + 1]);
    }
  }
  return result;
}

// Function to generate all possible operator combinations recursively
void generateOperatorCombinations(int n, std::vector<char>& current, std::vector<std::vector<char>>& allCombinations) {
  if (current.size() == n) {
    allCombinations.push_back(current);
    return;
  }

  current.push_back('+');
  generateOperatorCombinations(n, current, allCombinations);
  current.pop_back();

  current.push_back('*');
  generateOperatorCombinations(n, current, allCombinations);
  current.pop_back();

  current.push_back('|'); // Include concatenation operator
  generateOperatorCombinations(n, current, allCombinations);
  current.pop_back();
}

// Function to check if an equation is valid
bool isEquationValid(long long testValue, const std::vector<long long>& numbers) {
  size_t numOperators = numbers.size() - 1;
  if (numOperators == 0) return false; // Single number cannot be valid

  std::vector<std::vector<char>> allCombinations;
  std::vector<char> current;

  generateOperatorCombinations(numOperators, current, allCombinations);

  for (const auto& operators : allCombinations) {
    if (evaluateEquation(numbers, operators) == testValue) {
      return true;
    }
  }

  return false;
}

// Function to parse the input file and process equations
long long calculateTotalCalibrationResult(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return -1;
  }

  std::string line;
  long long total = 0;

  while (std::getline(file, line)) {
    if (line.empty()) continue; // Skip empty lines

    std::stringstream ss(line);
    long long testValue;
    char colon;
    ss >> testValue >> colon;

    if (ss.fail() || colon != ':') {
      std::cerr << "Error: Failed to parse test value or colon in line: \"" << line << "\"" << std::endl;
      continue;
    }

    std::vector<long long> numbers;
    long long num;
    while (ss >> num) {
      numbers.push_back(num);
    }

    if (numbers.empty()) {
      std::cerr << "Error: No numbers found in line: \"" << line << "\"" << std::endl;
      continue;
    }

    if (isEquationValid(testValue, numbers)) {
      total += testValue;
    }
  }

  file.close();
  return total;
}

int main() {
  std::string filename = "input.txt";
  long long result = calculateTotalCalibrationResult(filename);

  if (result != -1) {
    std::cout << "Total calibration result: " << result << std::endl;
  }

  return 0;
}
