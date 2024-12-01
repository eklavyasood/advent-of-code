// part2: count occurences of every list1 element in list2 and calculate a similarity score
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

// count occurences of list1 elements in list2
std::vector<int> countOccurences(std::vector<int>& vec1, std::vector<int>& vec2) {
  std::vector<int> occurences;
  size_t n = vec1.size();
  for (size_t i = 0; i < n; i++) {
    int count = 0;
    for (size_t j = 0; j < n; j++) {
      if (vec1[i] == vec2[j])
        ++count;
    }
    occurences.push_back(count);
  }
  return occurences;
}

int calculateScore(std::vector<int> vec1, std::vector<int> occurences) {
  size_t n = vec1.size();
  int similarityScore = 0;

  for (size_t i = 0; i < n; i++) {
    similarityScore += (vec1[i] * occurences[i]);
  }

  return similarityScore;
}

// sort the elements of both lists
void bubbleSort(std::vector<int>& vec) {
  size_t n = vec.size();
  for (size_t step = 0; step < n - 1; ++step) {
    for (size_t i = 0; i < n - step - 1; ++i) {
      if (vec[i] > vec[i+1]) {
        int temp = vec[i];
        vec[i] = vec[i+1];
        vec[i+1] = temp;
      }
    }
  }
}

// read both lists and create two vector arrays out of them
bool readLists(const std::string& filename, std::vector<int>& array1, std::vector<int>& array2) {
  std::ifstream inputFile(filename);
  if (!inputFile) {
    std::cerr << "Error: the file could not be opened " << filename << std::endl;
    return false;
  }

  int num1, num2;
  while (inputFile >> num1 >> num2) {
    array1.push_back(num1);
    array2.push_back(num2);
  }

  inputFile.close();
  return true;
}

int main (int argc, char *argv[]) {

  const std::string filename = "inputs1.txt";

  std::vector<int> vec1;
  std::vector<int> vec2;

  if (!readLists(filename, vec1, vec2)) {
    std::cout << "unable to read lists from the file" << std::endl;
    return 1;
  }

  std::vector<int> occurences = countOccurences(vec1, vec2);

  int similarityScore = calculateScore(vec1, occurences);
  std::cout << similarityScore << std::endl;

  return 0;

}
