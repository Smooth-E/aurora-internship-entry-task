#include "Book.h"
#include "BookStore.h"
#include <algorithm>
#include <cctype>
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

    int command;
    std::cin >> command;

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
  return 0;
}

int inputInteger(const std::string &message) {
  while (true) {
    try {
      std::size_t position;
      std::string input;
      std::getline(std::cin, input);
      int inetger = std::stoi(input, &position);

      if (input.length() == position) {
        return inetger;
      }
    } catch (std::invalid_argument &exception) {
      // Do nothing, wrong input
    } catch (std::out_of_range &exception) {
      // Do nothing, wrong input
    }
    std::cout << message << std::endl;
  }
}

float inputFloat(const std::string &message) {
  while (true) {
    try {
      std::size_t position;
      std::string input;
      std::getline(std::cin, input);
      float floating = std::stof(input, &position);

      if (input.length() == position) {
        return floating;
      }
    } catch (std::invalid_argument &exception) {
      // Do nothing, wrong input
    } catch (std::out_of_range &exception) {
      // Do nothing, wrong input
    }
    std::cout << message << std::endl;
  }
}

void discardLeftoverNewlines() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string trimmedString(const std::string &sequence) {
  auto start = std::find_if_not(
      sequence.begin(), sequence.end(),
      [sequence](unsigned char character) { return std::isspace(character); });

  auto end = std::find_if_not(sequence.rbegin(), sequence.rend(),
                              [sequence](unsigned char character) {
                                return std::isspace(character);
                              })
                 .base();

  if (start >= end) {
    return "";
  }

  return std::string(start, end);
}

std::string inputTrimmedLine() {
  std::string dirty;
  std::getline(std::cin, dirty);
  return trimmedString(dirty);
}

std::string inputNotEmptyTrimmedLine(const std::string &message) {
  std::string uncheckedString = "";
  while (true) {
    uncheckedString = inputTrimmedLine();

    if (uncheckedString.empty()) {
      std::cout << message << std::endl;
      continue;
    }

    return uncheckedString;
  }
}

std::string inputNotEmptyTrimmedLine() {
  return inputNotEmptyTrimmedLine("Поле не может быть пустым");
}

void addBook() {
  std::cout << "Добавление книги." << std::endl;

  std::cout << "Автор: ";
  discardLeftoverNewlines();
  std::string author = inputNotEmptyTrimmedLine();

  std::cout << "Название: ";
  std::string name = inputNotEmptyTrimmedLine();

  std::cout << "Год публикации: ";
  int year = inputInteger("Год публикации длжен быть цифрой");

  std::cout << "Цена: ";
  float price = inputFloat("Цена должна быть вещественным числом");

  std::shared_ptr<Book> book(new Book(name, author, year, price));
  if (bookStore.addBook(book) == 0) {
    std::cout << "Книга добавлена" << std::endl;
  } else {
    std::cout << "Книга с таким названием уже сущесвует" << std::endl;
  }
}

void removeBook() {
  std::cout << "Введите название книги, которую хотите удалить" << std::endl;
  std::string title = inputNotEmptyTrimmedLine();

  auto removed = bookStore.removeBook(title);
  if (removed != NULL) {
    std::cout << "Книга успешно удалена" << std::endl;
  } else {
    std::cout << "Такой книги в хранилище нет" << std::endl;
  }
}

void searchBook() {
  std::cout << "Введите название книги для поиска" << std::endl;
  std::string name = inputNotEmptyTrimmedLine();

  auto book = bookStore.findBook(name);
  if (book == NULL) {
    std::cout << "Ничего не найдено" << std::endl;
  } else {
    std::cout << "Что-то нашлось:" << std::endl
              << book->to_string() << std::endl;
  }
}

void listBooks() {
  int choice = -1;
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

  std::cout << "Отсортировнные книги:" << std::endl;
  for (auto book : sorted) {
    std::cout << book->to_string() << std::endl;
  }
}

void booksInPriceRange() {
  std::cout << "Введите диапозон цен на книги." << std::endl;

  std::cout << "Миинимальная цена: ";
  float minPrice =
      inputFloat("Минимальная цена должна быть вещественным числом");
  std::cout << "Максимальная цена: ";
  float maxPrice =
      inputFloat("Максимальная цена должна быть вещественным числом");

  auto sorted = bookStore.findBooksInPriceRange(minPrice, maxPrice);
  if (sorted.size() == 0) {
    std::cout << "Подходящих книг нет" << std::endl;
  } else {
    std::cout << "Подходящие книги:" << std::endl;
    for (auto book : sorted) {
      std::cout << book->to_string() << std::endl;
    }
  }
}
