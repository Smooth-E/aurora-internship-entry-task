#include <algorithm>
#include <cctype>
#include <iostream>
#include <limits>

int inputInteger(const std::string &message) {
  while (true) {
    try {
      std::size_t position;
      std::string input;
      std::getline(std::cin, input);
      int integer = std::stoi(input, &position);

      if (input.length() == position) {
        return integer;
      }
    } catch (std::invalid_argument &exception) {
      // Do nothing, wrong input
    } catch (std::out_of_range &exception) {
      // Do nothing, wrong input
    }
    std::cout << message << std::endl;
  }
}

float inputFloat(const std::string &message) {
  while (true) {
    try {
      std::size_t position;
      std::string input;
      std::getline(std::cin, input);
      float floating = std::stof(input, &position);

      if (input.length() == position) {
        return floating;
      }
    } catch (std::invalid_argument &exception) {
      // Do nothing, wrong input
    } catch (std::out_of_range &exception) {
      // Do nothing, wrong input
    }
    std::cout << message << std::endl;
  }
}

void discardLeftoverNewlines() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string trimmedString(const std::string &sequence) {
  auto start = std::find_if_not(
      sequence.begin(), sequence.end(),
      [sequence](unsigned char character) { return std::isspace(character); });

  auto end = std::find_if_not(sequence.rbegin(), sequence.rend(),
                              [sequence](unsigned char character) {
                                return std::isspace(character);
                              })
                 .base();

  if (start >= end) {
    return "";
  }

  return std::string(start, end);
}

std::string inputTrimmedLine() {
  std::string dirty;
  std::getline(std::cin, dirty);
  return trimmedString(dirty);
}

std::string inputNotEmptyTrimmedLine(const std::string &message) {
  std::string uncheckedString;
  while (true) {
    uncheckedString = inputTrimmedLine();

    if (uncheckedString.empty()) {
      std::cout << message << std::endl;
      continue;
    }

    return uncheckedString;
  }
}

std::string inputNotEmptyTrimmedLine() {
  return inputNotEmptyTrimmedLine("Поле не может быть пустым");
}
