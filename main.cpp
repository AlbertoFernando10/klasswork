#include <iostream>
#include <cstring>
#include "pe-vector.hpp"
using knk::Vector;

bool testConstructAndDestruct(const char ** pname) {
  *pname = __func__;
  knk::Vector< int > v;
  return true;
}
bool testDefaultVectorIsEmpty(const char ** pname) {
  *pname = __func__;
  Vector< int > v;
  return v.isEmpty();
}
bool testSizeOfEmptyVector(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  return !v.getSize();
}
bool testSizeOfNonEmptyVector(const char** pname) {
  *pname = __func__;
  constexpr size_t size = 2;
  Vector< int > v(size, 5);
  return v.getSize() == size;
}
bool testElementCheckedAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  try {
    int& r = v.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}
bool testElementCheckedConstAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  v.pushBack(2);
  const Vector< int >& rv = v;
  try {
    const int& r = rv.at(0);
    return r == 2;
  } catch (...) {
    return false;
  }
}
bool testElementCheckedOutOfBoundAccess(const char** pname) {
  *pname = __func__;
  Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char* text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}
bool testElementCheckedOutOfBoundConstAccess(const char** pname) {
  *pname = __func__;
  const Vector< int > v;
  try {
    v.at(0);
    return false;
  } catch (const std::out_of_range& e) {
    const char* text = e.what();
    return !std::strcmp("id out of bound", text);
  } catch (...) {
    return false;
  }
}
bool testCopyConstructor(const char** pname) {
  *pname = __func__;
  Vector< int > v{1, 2};
  Vector< int > yav = v;
  if (v.isEmpty() || yav.isEmpty()) {
    throw std::logic_error("Vectors expected to be non-empty");
  }
  bool isEqual = yav.getSize() == v.getSize();
  for (size_t i = 0; isEqual && i < v.getSize(); ++i) {
    try {
      isEqual = v.at(i) == yav.at(i);
    } catch (...) {
      return false;
    }
  }
  return isEqual;
}

int main() {
  using test_t = bool(*)(const char **);
  using case_t = std::pair< test_t, const char * >;
  case_t tests[] = {
    { testConstructAndDestruct,
      "Vector must be default"
      " constructable" },
    { testDefaultVectorIsEmpty,
      "Default constructed"
      " vector must be empty" },
    { testSizeOfEmptyVector,
      "Size of empty vector"
      " must be zero" },
    { testSizeOfNonEmptyVector,
      "Size of non-empty vector"
      " must be greater than zero" },
    { testElementCheckedAccess, "Inbound access must return lvalue reference to indexed value" },
    { testElementCheckedOutOfBoundAccess, "Out of bound access must generate exception with specific text" },
    { testElementCheckedConstAccess, "Same as inbound access but const" },
    { testElementCheckedOutOfBoundConstAccess, "Same as out of bound but const" },
    { testCopyConstructor, "Copied vector must be equal to original" }
  };
  constexpr size_t count = sizeof(tests) / sizeof(case_t);
  size_t failed = 0;
  for (size_t i = 0; i < count; ++i) {
    const char * testName = nullptr;
    bool r = false;
    try {
      r = tests[i].first(&testName);
    } catch (const std::logic_error& e) {
      std::cout << "[NOT RUN] " << testName << "\n";
      std::cout << "\t" << "Reason: " << e.what() << "\n";
      ++failed;
      continue;
    }
    if (!r) {
      ++failed;
      std::cout << "[FAIL] " << testName << "\n";
      std::cout << "\t" << tests[i].second << "\n";
    }
  }
  std::cout << "Summary:\n\t" << (count - failed) << " passed\n";
  std::cout << "\t" << count << " total\n";
}