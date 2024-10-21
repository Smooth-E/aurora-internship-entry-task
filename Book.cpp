#include "Book.h"
#include <string>

const int Book::CURRENT_YEAR = 2024;

Book::Book(const std::string &_name, const std::string &_author,
           int _publicationYear, float _price) {
  this->name = _name;
  this->author = _author;
  this->publicationYear = _publicationYear;
  this->price = _price;
}

std::string Book::getName() const { return this->name; }

int Book::setName(const std::string &_name) {
  if (_name.empty()) {
    return 1;
  }

  this->name = _name;
  return 0;
}

std::string Book::getAuthor() const { return this->author; }

int Book::setAuthor(const std::string &_author) {
  if (_author.empty()) {
    return 1;
  }

  this->author = _author;
  return 0;
}

int Book::getPublicationYear() const { return this->publicationYear; }

int Book::setPublicationYear(int _year) {
  if (_year > CURRENT_YEAR) {
    return 1;
  }

  this->publicationYear = _year;
  return 0;
}

float Book::getPrice() const { return this->price; }

int Book::setPrice(float _price) {
  if (_price <= 0) {
    return 1;
  }

  this->price = _price;
  return 0;
}

std::string Book::to_string() const {
  return "Книга(Название: " + name + ", Автор: " + author +
         ", Год публикации: " + std::to_string(publicationYear) +
         ", Цена: " + std::to_string(price) + " у.е.)";
}
