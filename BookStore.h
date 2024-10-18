#ifndef BookStore_H
#define BookStore_H

#include "Book.h"
#include <string>
#include <vector>

enum class SortType { NY_NAME, BY_AUTHOR, BY_PUBLICATION_YEAR };

class BookStore {
private:
  std::vector<Book *> books;

public:
  BookStore();

  ~BookStore();

  int addBook(Book *_book);

  Book *removeBook(std::string _title);

  Book *findBook(std::string _title) const;

  std::vector<Book *> listBooks(SortType sortType) const;

  std::vector<Book *> findBooksInPriceRange(float minPrice,
                                            float maxPrice) const;
};

#endif
