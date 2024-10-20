#ifndef UTILS_H
#define UTILS_H

#include <string>

int inputInteger(const std::string &message);

float inputFloat(const std::string &message);

void discardLeftoverNewlines();

std::string trimmedString(const std::string &sequence);

std::string inputTrimmedLine();

std::string inputNotEmptyTrimmedLine(const std::string &message);

std::string inputNotEmptyTrimmedLine();

#endif // UTILS_H
