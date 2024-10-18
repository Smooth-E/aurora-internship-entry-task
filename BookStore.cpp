#include "BookStore.h"
#include "Book.h"
#include <algorithm>
#include <string>
#include <vector>

BookStore::BookStore() { this->books = {}; }

// It would be better to use smart pointers because this does not enusre some
// books are not used outside of the store
BookStore::~BookStore() {
  for (Book *book : books) {
    delete book;
  }
}

int BookStore::addBook(Book *_book) {
  if (findBook(_book->getName()) != NULL) {
    return 1;
  }

  this->books.push_back(_book);
  return 0;
}

Book *BookStore::removeBook(std::string _title) {
  for (int i = 0; i < books.size(); i++) {
    if (books.at(i)->getName() == _title) {
      Book *removed = books.at(i);
      books.erase(books.begin() + i);
      return removed;
    }
  }

  return NULL;
}

Book *BookStore::findBook(std::string _title) const {
  for (int i = 0; i < books.size(); i++) {
    if (books.at(i)->getName() == _title) {
      return books.at(i);
    }
  }

  return NULL;
}

std::vector<Book *> BookStore::listBooks(SortType sortType) const {
  std::vector<Book *> sorted(books);

  std::sort(sorted.begin(), sorted.end(),
            [sortType](const Book *book1, const Book *book2) {
              switch (sortType) {
              case SortType::NY_NAME:
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

std::vector<Book *> BookStore::findBooksInPriceRange(float minPrice,
                                                     float maxPrice) const {
  std::vector<Book *> found = {};

  for (Book *book : books) {
    if (minPrice <= book->getPrice() && book->getPrice() <= maxPrice) {
      found.push_back(book);
    }
  }

  return found;
}
