#include "Book.h"
#include "BookStore.h"
#include <iostream>
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

void addBook() {
  std::string author;
  std::string name;
  int year;
  float price;

  std::cout
      << "Введите имя автора книги, название книги, год публикации и её цену:"
      << std::endl;
  std::cin >> author >> name >> year >> price;

  std::shared_ptr<Book> book(new Book(name, author, year, price));
  if (bookStore.addBook(book) == 0) {
    std::cout << "Книга добавлена" << std::endl;
  } else {
    std::cout << "Книга с таким названием уже сущесвует" << std::endl;
  }
}

void removeBook() {
  std::string title;
  std::cout << "Введите название книги, которую хотите удалить" << std::endl;
  std::cin >> title;

  auto removed = bookStore.removeBook(title);
  if (removed != NULL) {
    std::cout << "Книга успешно удалена" << std::endl;
  } else {
    std::cout << "Такой книги в хранилище нет" << std::endl;
  }
}

void searchBook() {
  std::cout << "Введите название книги для поиска" << std::endl;
  std::string name;
  std::cin >> name;

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
    std::cin >> choice;

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

  float minPrice, maxPrice;
  std::cout << "Миинимальная цена: ";
  std::cin >> minPrice;
  std::cout << "Максимальная цена: ";
  std::cin >> maxPrice;

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
