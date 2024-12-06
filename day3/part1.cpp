#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void handleMultiplication(int num1, int num2);

// global sum of products
int prodSum = 0;

// Function to trim leading and trailing whitespace from a string
std::string trim(const std::string& str) {
    auto start = str.begin();
    // Trim leading whitespace
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }

    auto end = str.end();
    // Trim trailing whitespace
    do {
        --end;
    } while (std::distance(start, end) > 0 && std::isspace(*end));

    return std::string(start, end + 1);
}

// read the file and perform basic parsing
bool readFile(std::string filename, std::string& fileContents) {
  std::ifstream inputFile(filename);

  if (!inputFile) {
    std::cerr << "The file could not be read! " << filename << std::endl;
    return false;
  }

  std::stringstream buffer;
  buffer << inputFile.rdbuf();
  fileContents = buffer.str();

  inputFile.close();

  return true;
}


void handleRegex(const std::string& fileContents) {
    std::regex testRegex(R"(mul\((\d+),(\d+)\))");

    auto matchesBegin = std::sregex_iterator(fileContents.begin(), fileContents.end(), testRegex);
    auto matchesEnd = std::sregex_iterator();

    for (auto it = matchesBegin; it != matchesEnd; ++it) {
        try {
            std::string num1Str = (*it)[1];
            std::string num2Str = (*it)[2];

            // Trim whitespace or extra characters
            num1Str = trim(num1Str);
            num2Str = trim(num2Str);

            // Debugging: Print the cleaned-up numbers
            std::cout << "Cleaned numbers: '" << num1Str << "' and '" << num2Str << "'" << std::endl;

            int num1 = std::stoi(num1Str);
            int num2 = std::stoi(num2Str);

            handleMultiplication(num1, num2);

        } catch (const std::invalid_argument& e) {
            std::cerr << "Invalid argument: Could not convert match to integer: " << it->str() << std::endl;
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range: Match values are too large: " << it->str() << std::endl;
        }
    }
}

// handle multiplication of both integers, and the increment of prodSum
void handleMultiplication(int num1, int num2) {
  // std::cout << num1 * num2 << std::endl;
  prodSum += num1 * num2;
}

int main (int argc, char *argv[]) {
  const std::string filename = "input.txt";
  // const std::string filename = "test.txt";
  std::string fileContents = "";

  if (!readFile(filename, fileContents)) {
    std::cerr << "File couldn't be read " << filename << std::endl;
    return 1;
  }

  handleRegex(fileContents);

  std::cout << prodSum << std::endl;

  return 0;
}
