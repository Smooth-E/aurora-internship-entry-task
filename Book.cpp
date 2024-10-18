#include "Book.h"
#include <iostream>
#include <string>

const int Book::CURRENT_YEAR = 2024;

Book::Book(std::string name, std::string author, int publicationYear,
           float price) {
  this->name = name;
  this->author = author;
  this->publicationYear = publicationYear;
  this->price = price;
}

std::string Book::getName() const { return this->name; }

int Book::setName(std::string name) {
  if (name.empty()) {
    return 1;
  }

  this->name = name;
  return 0;
}

std::string Book::getAuthor() const { return this->author; }

int Book::setAuthor(std::string author) {
  if (author.empty()) {
    return 1;
  }

  this->author = author;
  return 0;
}

int Book::getPublicationYear() const { return this->publicationYear; }

int Book::setPublicationYear(int year) {
  if (year > CURRENT_YEAR) {
    return 1;
  }

  this->publicationYear = year;
  return 0;
}

float Book::getPrice() const { return this->price; }

int Book::setPrice(float price) {
  if (price <= 0) {
    return 1;
  }

  this->price = price;
  return 0;
}
