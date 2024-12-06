#include <regex>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

void handleMultiplication(int num1, int num2);

// global sum of products
int prodSum = 0;

// global to check whether mul is enabled or not
bool isMulEnabled = true;

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
  std::regex mulRegex(R"(mul\((\d+),(\d+)\))");
  std::regex doRegex(R"(do\(\))");
  std::regex dontRegex(R"(don't\(\))");

  bool insideDoBlock = false; // Tracks whether we're inside a `do()` block

  // Iterators for all matches of `do()`, `don't()`, and `mul()`
  auto doMatchesBegin = std::sregex_iterator(fileContents.begin(), fileContents.end(), doRegex);
  auto doMatchesEnd = std::sregex_iterator();
  auto dontMatchesBegin = std::sregex_iterator(fileContents.begin(), fileContents.end(), dontRegex);
  auto dontMatchesEnd = std::sregex_iterator();
  auto matchesBegin = std::sregex_iterator(fileContents.begin(), fileContents.end(), mulRegex);
  auto matchesEnd = std::sregex_iterator();

  // Process `do()` matches to start processing `mul()`
  for (auto it = doMatchesBegin; it != doMatchesEnd; ++it) {
    insideDoBlock = true;
    std::cout << "do() found: mul instructions enabled" << std::endl;
  }

  // Process `don't()` matches to stop processing `mul()`
  for (auto it = dontMatchesBegin; it != dontMatchesEnd; ++it) {
    insideDoBlock = false;
    std::cout << "don't() found: mul instructions disabled" << std::endl;
  }

  // Process `mul()` matches based on the state of `insideDoBlock`
  for (auto it = matchesBegin; it != matchesEnd; ++it) {
    if (insideDoBlock) {
      try {
        std::string num1Str = (*it)[1];
        std::string num2Str = (*it)[2];

        // Trim whitespace or extra characters
        num1Str = trim(num1Str);
        num2Str = trim(num2Str);

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
}


// void handleRegex(const std::string& fileContents) {
//   std::regex mulRegex(R"(mul\((\d+),(\d+)\))");
//
//   // regex patterns for do() and don't()
//   std::regex doRegex(R"(do\(\))");
//   std::regex dontRegex(R"(don't\(\))");
//
//
//   // Process do() and don't()
//   auto doMatchesBegin = std::sregex_iterator(fileContents.begin(), fileContents.end(), doRegex);
//   auto doMatchesEnd = std::sregex_iterator();
//
//   for (auto it = doMatchesBegin; it != doMatchesEnd; ++it) {
//     isMulEnabled = true;
//     std::cout << "do() found: mul instructions enabled" << std::endl;
//   }
//
//   auto dontMatchesBegin = std::sregex_iterator(fileContents.begin(), fileContents.end(), dontRegex);
//   auto dontMatchesEnd = std::sregex_iterator();
//
//   for (auto it = dontMatchesBegin; it != dontMatchesEnd; ++it) {
//     isMulEnabled = false;
//     std::cout << "don't() found: mul instructions disabled" << std::endl;
//   }
//   auto matchesBegin = std::sregex_iterator(fileContents.begin(), fileContents.end(), mulRegex);
//   auto matchesEnd = std::sregex_iterator();
//
//   for (auto it = matchesBegin; it != matchesEnd; ++it) {
//     if (isMulEnabled) {
//       try {
//         std::string num1Str = (*it)[1];
//         std::string num2Str = (*it)[2];
//
//         // Trim whitespace or extra characters
//         num1Str = trim(num1Str);
//         num2Str = trim(num2Str);
//
//         // Debugging: Print the cleaned-up numbers
//         // std::cout << "Cleaned numbers: '" << num1Str << "' and '" << num2Str << "'" << std::endl;
//
//         int num1 = std::stoi(num1Str);
//         int num2 = std::stoi(num2Str);
//
//         handleMultiplication(num1, num2);
//
//       } catch (const std::invalid_argument& e) {
//         std::cerr << "Invalid argument: Could not convert match to integer: " << it->str() << std::endl;
//       } catch (const std::out_of_range& e) {
//         std::cerr << "Out of range: Match values are too large: " << it->str() << std::endl;
//       }
//     }
//   }
// }

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
