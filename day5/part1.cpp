#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

using list_t = std::vector<int>;
using rules_t = std::map<int, list_t>;
using pages_t = std::vector<list_t>;

struct manual_t {
  rules_t rules;
  pages_t pages;
};

manual_t load_input(const std::string& file) {
  manual_t ret;
  int mode = 0;
  std::ifstream fs(file);
  std::string line;
  while (std::getline(fs, line)) {
    if(line.empty()) {
      mode = 1;
      continue;
    }
    if(mode == 0) {
      ret.rules[std::stoi(line.substr(3,2))].push_back(std::stoi(line.substr(0,2)));
    } else {
      ret.pages.push_back(list_t());
      std::stringstream ss(line);
      std::string str;
      while (std::getline(ss, str, ',')) {
        ret.pages.back().push_back(std::stoi(str));
      }
    }
  }
  return ret;
}

bool ordered(int a, int b, const rules_t& rules) {
  auto rule = rules.find(a); 
  if(rule != rules.end()) {
    if(std::find(rule->second.begin(), rule->second.end(), b) != rule->second.end()){
      return false;
    }
  }
  return true;
}

bool correct_order(const list_t& pages, const rules_t& rules) {
  for(int p=0; p<pages.size(); ++p) {
    for(int q=p+1; q<pages.size(); ++q) {
      if(!ordered(pages[p], pages[q], rules)) {
        return false;
      }
    }
  }
  return true;
};

int part1(const manual_t& manual) {
  int sum = 0;
  for(auto& pages : manual.pages){
    if(correct_order(pages, manual.rules)) {
      sum += pages[pages.size()/2];
    }
  }
  return sum;
}

int main() {
  auto test_values = load_input("test.txt");
  auto actual_values = load_input("input.txt");

  std::cout << "part1: " << part1(test_values) << std::endl;
  std::cout << "part1: " << part1(actual_values) << std::endl;

}
