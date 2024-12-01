// part 1: sort two lists, find the total difference between their values
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <vector>

// sort the elements of both lists
void bubbleSort(std::vector<int>& arr) {
  size_t n = arr.size();
  for (size_t step = 0; step < n - 1; ++step) {
    for (size_t i = 0; i < n - step - 1; ++i) {
      if (arr[i] > arr[i+1]) {
        int temp = arr[i];
        arr[i] = arr[i+1];
        arr[i+1] = temp;
      }
    }
  }
}

// compare the differences for each list tier
void compareDifference(std::vector<int> list1, std::vector<int> list2, std::vector<int>& diff) {
  size_t n = list1.size();
  diff.resize(n);
  for (int i = 0; i < n; i++) {
    if (list1[i] >= list2[i])
      diff[i] = list1[i] - list2[i];
    else 
      diff[i] = list2[i] - list1[i];
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

  std::vector<int> array1;
  std::vector<int> array2;

  if (!readLists(filename, array1, array2)) {
    std::cout << "unable to read lists from the file" << std::endl;
    return 1;
  }

  // sorting both the lists
  bubbleSort(array1);
  bubbleSort(array2);

  std::vector<int> diff;
  compareDifference(array1, array2, diff);

  int32_t total = 0;
  for (size_t i = 0; i < diff.size(); i++) {
    total += diff[i];
  }

  std::cout << "Total difference = " << total << std::endl;

  return 0;

}
