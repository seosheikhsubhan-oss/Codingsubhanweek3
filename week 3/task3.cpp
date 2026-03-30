#include <iostream>
using namespace std;

class Publication {
public:
    virtual void display() = 0;
};

class Book : public Publication {
private:
    string title;
    string author;
    int pages;

public:
    Book() {}

    Book(string t, string a, int p) {
        title = t;
        author = a;
        pages = p;
    }

    string getKey() {
        return title;
    }

    int getPages() {
        return pages;
    }

    void display() {
        cout << "Book: " << title << " | Author: " << author << " | Pages: " << pages << endl;
    }
};

class Newspaper : public Publication {
private:
    string name;
    string date;
    string edition;

public:
    Newspaper() {}

    Newspaper(string n, string d, string e) {
        name = n;
        date = d;
        edition = e;
    }

    string getKey() {
        return name;
    }

    string getEdition() {
        return edition;
    }

    void display() {
        cout << "Newspaper: " << name << " | Date: " << date << " | Edition: " << edition << endl;
    }
};
template<class T>
T* linearSearch(T arr[], int size, string key) {

    for (int i = 0; i < size; i++) {
        if (arr[i].getKey() == key)
            return &arr[i];
    }

    return NULL;
}

template<class T>
T* binarySearch(T arr[], int size, string key) {

    int low = 0;
    int high = size - 1;

    while (low <= high) {

        int mid = (low + high) / 2;

        if (arr[mid].getKey() == key)
            return &arr[mid];

        else if (arr[mid].getKey() < key)
            low = mid + 1;

        else
            high = mid - 1;
    }

    return NULL;
}

class Library {

private:

    Book books[10];
    Newspaper newspapers[10];

    int bookCount = 0;
    int newspaperCount = 0;

public:

    void addBook(Book b) {
        books[bookCount++] = b;
    }

    void addNewspaper(Newspaper n) {
        newspapers[newspaperCount++] = n;
    }

    void displayCollection() {

        cout << "\nBooks:\n";

        for (int i = 0; i < bookCount; i++)
            books[i].display();

        cout << "\nNewspapers:\n";

        for (int i = 0; i < newspaperCount; i++)
            newspapers[i].display();
    }

    void sortBooksByPages() {

        for (int i = 0; i < bookCount - 1; i++) {
            for (int j = i + 1; j < bookCount; j++) {

                if (books[i].getPages() > books[j].getPages()) {

                    Book temp = books[i];
                    books[i] = books[j];
                    books[j] = temp;
                }
            }
        }
    }

    void sortNewspapersByEdition() {

        for (int i = 0; i < newspaperCount - 1; i++) {
            for (int j = i + 1; j < newspaperCount; j++) {

                if (newspapers[i].getEdition() > newspapers[j].getEdition()) {

                    Newspaper temp = newspapers[i];
                    newspapers[i] = newspapers[j];
                    newspapers[j] = temp;
                }
            }
        }
    }

    Book* searchBookByTitle(string title) {
        return linearSearch(books, bookCount, title);
    }

    Newspaper* searchNewspaperByName(string name) {
        return linearSearch(newspapers, newspaperCount, name);
    }
};

int main() {

    Book book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book book2("To Kill a Mockingbird", "Harper Lee", 324);

    Newspaper newspaper1("Washington Post", "2024-10-13", "Morning Edition");
    Newspaper newspaper2("The Times", "2024-10-12", "Weekend Edition");

    Library library;


    library.addBook(book1);
    library.addBook(book2);

    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);

    cout << "Before Sorting:\n";
    library.displayCollection();

    library.sortBooksByPages();
    library.sortNewspapersByEdition();

    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    Book* foundBook = library.searchBookByTitle("The Catcher in the Rye");

    if (foundBook) {
        cout << "\nFound Book:\n";
        foundBook->display();
    }
    else {
        cout << "\nBook not found\n";
    }
    Newspaper* foundNewspaper = library.searchNewspaperByName("The Times");

    if (foundNewspaper) {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    }
    else {
        cout << "\nNewspaper not found\n";
    }

    return 0;
}