#include "Book.h"
#include "BookStore.h"
#include "utils.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <memory>

BookStore bookStore;

// Since this is a relatively simple program, we do not pre-define an extra
// header file and just define functions here
void addBook();
void removeBook();
void searchBook();
void listBooks();
void booksInPriceRange();

int main() {
  while (true) {
    std::cout << "1. Добавить книгу" << std::endl;
    std::cout << "2. Удалить книгу" << std::endl;
    std::cout << "3. Найти книгу по названию" << std::endl;
    std::cout
        << "4. Показать все книги (сортировка по названию/автору/году издания)"
        << std::endl;
    std::cout << "5. Найти книги в ценовом диапазоне" << std::endl;
    std::cout << "6. Выйти" << std::endl;

    int command = inputInteger("Команда должна быть цифрой");

    switch (command) {
    case 1:
      addBook();
      break;
    case 2:
      removeBook();
      break;
    case 3:
      searchBook();
      break;
    case 4:
      listBooks();
      break;
    case 5:
      booksInPriceRange();
      break;
    case 6:
      return 0;
    default:
      std::cout << "Неправильная команда!" << std::endl;
      break;
    }
  }
}

void addBook() {
  std::cout << "Добавление книги." << std::endl;

  std::cout << "Автор: ";
  std::string author = inputNotEmptyTrimmedLine();

  std::cout << "Название: ";
  std::string name = inputNotEmptyTrimmedLine();

  std::cout << "Год публикации: ";
  int year = inputInteger("Год публикации должен быть цифрой");

  std::cout << "Цена: ";
  float price = inputFloat("Цена должна быть вещественным числом");

  std::shared_ptr<Book> book(new Book(name, author, year, price));
  if (bookStore.addBook(book) == 0) {
    std::cout << "Книга добавлена" << std::endl;
  } else {
    std::cout << "Книга с таким названием уже существует" << std::endl;
  }
}

void removeBook() {
  std::cout << "Введите название книги, которую хотите удалить" << std::endl;
  std::string title = inputNotEmptyTrimmedLine();

  auto removed = bookStore.removeBook(title);
  if (removed != nullptr) {
    std::cout << "Книга успешно удалена" << std::endl;
  } else {
    std::cout << "Такой книги в хранилище нет" << std::endl;
  }
}

void searchBook() {
  std::cout << "Введите название книги для поиска" << std::endl;
  std::string name = inputNotEmptyTrimmedLine();

  auto book = bookStore.findBook(name);
  if (book == nullptr) {
    std::cout << "Ничего не найдено" << std::endl;
  } else {
    std::cout << "Что-то нашлось:" << std::endl
              << book->to_string() << std::endl;
  }
}

void listBooks() {
  int choice;
  SortType sortType;

  while (true) {
    std::cout << "Как вы хотите отсортировать список книг для вывода?"
              << std::endl;
    std::cout << "1. По названию" << std::endl;
    std::cout << "2. По имени автора" << std::endl;
    std::cout << "3. По году публикации" << std::endl;
    choice = inputInteger("Номер способа сортировки должен быть цифрой");

    bool validChoice = true;
    switch (choice) {
    case 1:
      sortType = SortType::BY_NAME;
      break;
    case 2:
      sortType = SortType::BY_AUTHOR;
      break;
    case 3:
      sortType = SortType::BY_PUBLICATION_YEAR;
      break;
    default:
      std::cout << "Нет такого варианта" << std::endl;
      validChoice = false;
      break;
    }

    if (validChoice) {
      break;
    }
  }

  auto sorted = bookStore.listBooks(sortType);

  std::cout << "Отсортированные книги:" << std::endl;
  for (const auto &book : sorted) {
    std::cout << book->to_string() << std::endl;
  }
}

void booksInPriceRange() {
  std::cout << "Введите диапазон цен на книги." << std::endl;

  std::cout << "Минимальная цена: ";
  float minPrice =
      inputFloat("Минимальная цена должна быть вещественным числом");
  std::cout << "Максимальная цена: ";
  float maxPrice =
      inputFloat("Максимальная цена должна быть вещественным числом");

  auto sorted = bookStore.findBooksInPriceRange(minPrice, maxPrice);
  if (sorted.empty()) {
    std::cout << "Подходящих книг нет" << std::endl;
  } else {
    std::cout << "Подходящие книги:" << std::endl;
    for (const auto &book : sorted) {
      std::cout << book->to_string() << std::endl;
    }
  }
}
