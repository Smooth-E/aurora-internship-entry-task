#include "BookStore.h"
#include "Book.h"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

BookStore::BookStore() { this->books = {}; }

int BookStore::addBook(const std::shared_ptr<Book>& _book) {
  if (findBook(_book->getName()) != nullptr) {
    return 1;
  }

  this->books.push_back(_book);
  return 0;
}

std::shared_ptr<Book> BookStore::removeBook(const std::string& _title) {
  for (int i = 0; i < books.size(); i++) {
    if (books.at(i)->getName() == _title) {
      std::shared_ptr<Book> removed = books.at(i);
      books.erase(books.begin() + i);
      return removed;
    }
  }

  return nullptr;
}

std::shared_ptr<Book> BookStore::findBook(const std::string& _title) const {
  for (const auto & book : books) {
    if (book->getName() == _title) {
      return book;
    }
  }

  return nullptr;
}

std::vector<std::shared_ptr<Book>>
BookStore::listBooks(SortType sortType) const {
  std::vector<std::shared_ptr<Book>> sorted(books);

  std::sort(sorted.begin(), sorted.end(),
            [sortType](const std::shared_ptr<Book>& book1,
                       const std::shared_ptr<Book>& book2) {
              switch (sortType) {
              case SortType::BY_NAME:
                return book1->getName() < book2->getName();
              case SortType::BY_AUTHOR:
                return book1->getAuthor() < book2->getAuthor();
              case SortType::BY_PUBLICATION_YEAR:
                return book1->getPublicationYear() <
                       book2->getPublicationYear();
              }

              return false; // Never reached
            });

  return sorted;
}

std::vector<std::shared_ptr<Book>>
BookStore::findBooksInPriceRange(float minPrice, float maxPrice) const {
  std::vector<std::shared_ptr<Book>> found = {};

  for (const std::shared_ptr<Book>& book : books) {
    if (minPrice <= book->getPrice() && book->getPrice() <= maxPrice) {
      found.push_back(book);
    }
  }

  return found;
}
