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
  Book(std::string _name, std::string _author, int _publicationYear,
       float _price);

  std::string getName() const;

  int setName(std::string _name);

  std::string getAuthor() const;

  int setAuthor(std::string _author);

  int getPublicationYear() const;

  int setPublicationYear(int _year);

  float getPrice() const;

  int setPrice(float _price);

  std::string to_string() const;
};

#endif // BOOK_H
