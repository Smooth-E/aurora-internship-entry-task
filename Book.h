#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
private:
  static const int CURRENT_YEAR;

  std::string name;
  std::string author;
  int publicationYear;
  float price;

public:
  Book(std::string name, std::string author, int publicationYear, float price);

  std::string getName() const;

  int setName(std::string name);

  std::string getAuthor() const;

  int setAuthor(std::string author);

  int getPublicationYear() const;

  int setPublicationYear(int year);

  float getPrice() const;

  int setPrice(float price);

  std::string to_string() const;
};

#endif // BOOK_H
