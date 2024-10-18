#include "Book.h"
#include "BookStore.h"
#include <iostream>

int main() {
  BookStore bookStore;
  Book something("Something", "Someone", 1999, 100.5);
  Book somethingElse("Something else", "Someone else", 2000, 100.2);
  bookStore.addBook(&something);
  bookStore.addBook(&somethingElse);
  std::cout << bookStore.findBook("Something")->getName();
  return 0;
}
