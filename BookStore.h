#ifndef BookStore_H
#define BookStore_H

#include "Book.h"
#include <memory>
#include <string>
#include <vector>

enum class SortType { BY_NAME, BY_AUTHOR, BY_PUBLICATION_YEAR };

class BookStore {
private:
  std::vector<std::shared_ptr<Book>> books;

public:
  BookStore();

  int addBook(const std::shared_ptr<Book> &_book);

  std::shared_ptr<Book> removeBook(const std::string &_title);

  std::shared_ptr<Book> findBook(const std::string &_title) const;

  std::vector<std::shared_ptr<Book>> listBooks(SortType sortType) const;

  std::vector<std::shared_ptr<Book>>
  findBooksInPriceRange(float minPrice, float maxPrice) const;
};

#endif
