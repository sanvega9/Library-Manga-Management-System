#include <iostream>
#include <vector>
#include <string>
#include <algorithm> //Required for find_if 
#include <fstream>
#include <limits>
#include <unordered_map>

using namespace std;
string tolowerfunction(const string& str){
    string lowercaseStr = str;
    transform(lowercaseStr.begin(), lowercaseStr.end(), lowercaseStr.begin(), ::tolower);
    return lowercaseStr;

}
// Class represent books 
class Book{
public:
    int id; // id of the book to identify
    string title; // Title books 
    string authorname; // Author books
    int volume; // Volume number in a series
    int copies; // Number of Copies available 
    // Constructor to initialize a book object 
    Book(int IDbook, const string& title_book, const string& author_name, int vol, int num_copies)
        :id(IDbook), title(title_book), authorname(author_name), volume(vol), copies(num_copies){}
        // Display the book inform 
    void display() const{
        cout<<"ID: "<<id <<", Title: "<< title << ", Author: " << authorname 
        << ", Volume: "<<volume<<", Copies: "<< copies<<endl;
    }
    // Taking out a book 
    void takeOut(){
        if(copies > 0){
            copies--;
            cout<< "Book take out successfully! Remaining copies: "<< copies <<endl;
        }else{
            cout<< "No copies available to take out.\n";
        }
    }
    void bookreturn(){
        copies++;
        cout<< "Book returned successfully! Total copies: "<< copies << endl;
    }

};
class LibraryClass{
    private:
        vector<Book> books;
        int IDNew;
        const string filename = "library_manga_books.txt";

    public:
        // Constructor to  initialize the library and load books within the file 
        LibraryClass() : IDNew(1){
            loadFromFile();
            for(const auto& book: books){
                if (book.id >= IDNew){
                    IDNew = book.id +1;
                }
            }

        }
        // Destructor to save books to file 
        ~LibraryClass(){
            saveToFile();
        }
        // Allow to add the new book to the library 
    void addingBooks(const string& title, const string& authorname, int volume, int copies){
        Book newbook(IDNew,title, authorname, volume, copies);
        books.push_back(newbook);
        IDNew++;
        cout<< "Book added successfully!\n";
    }
    // Display the book in the library 
    void viewBooks() const { 
        if(books.empty()) {
            cout<< "No books available in the library.\n";
            return;
        }
        for(const auto& book : books){
            book.display();
        }
    }
    // Search for book by author, title, or volume
    void searchBooks(const string& query) const{
        string lowerquery = tolowerfunction(query);
        unordered_map<string, vector<Book>> series_map; // Map to group books by title
        bool found = false;

        for(const auto& book : books){
            string lowerTitlename = tolowerfunction(book.title);
            string LowerAuthername = tolowerfunction(book.authorname);
            string volumeString = to_string(book.volume);
            // Check if the query matches the titles, author, or volume 
        if(lowerTitlename.find(lowerquery) != string::npos || 
           LowerAuthername.find(lowerquery) !=string::npos || volumeString == lowerquery){
            series_map[book.title].push_back(book); // Add books to series map 
            found= true;
            }
        }
        if(found) {
            for(const auto& series : series_map) {
                cout<< "\nSeries: "<< series.first<<"\n";
                for (const auto& book : series.second){
                    book.display();//Display all volumes of the series 
                }
            }
        } else {
        cout<< "No book found with given title, author, or volume.\n ";
        }
    }
    // Remove a book by ID 
    void removeBooks(int bookID) {
        auto it = find_if(books.begin(),books.end(),[bookID] (const Book& book){
            return book.id == bookID;
    });
     if(it != books.end()){
        books.erase(it);
        cout<< "Book removed sucessfully!\n";
     } else{
        cout << "Book not found!";
        }    
    }
    // Take out a book by ID 

    void takeOutBook(int bookID) {
        auto it = find_if(books.begin(),books.end(),[bookID](const Book& book){
            return book.id == bookID;
        });
        if(it != books.end()){
            it->takeOut();
        } else{
            cout<< "Book not found!\n";
        }
    }
    // Return a book by ID 
    void returnbooks(int bookID){
        auto it = find_if(books.begin(), books.end(), [bookID](const Book& book){
            return book.id == bookID;
        });
        if (it != books.end()){
            it->bookreturn();
        } else{
            cout<< "Book not found!\n";
        }
    }
    //save the books to a file 
    // filename is library_manga_books.txt  
    void saveToFile() const{
        ofstream file(filename);
        if(file.is_open()){
            for (const auto& book : books){
                file << book.id << ","<< book.title<<","<<book.authorname<< ","<<book.volume<< ","<< book.copies <<"\n";
            }
            file.close();
        }else{
            cout<<"Unable to open file for saving.\n";
        }
    }
    void loadFromFile() {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                int id, volume,copies;
                string title, authorname;
                size_t pos = 0;
                
                pos = line.find(",");
                id= stoi(line.substr(0,pos));
                line.erase(0,pos+1);

                pos = line.find(",");
                title= line.substr(0,pos);
                line.erase(0,pos+1);

                pos = line.find(",");
                authorname= line.substr(0,pos);
                line.erase(0,pos+1);

                pos = line.find(",");
                volume= stoi(line.substr(0,pos));
                line.erase(0,pos+1);
                
                copies =stoi(line);
                books.emplace_back(id,title,authorname,volume, copies);
            }
            file.close();
        }else{
            cout<<"Unable to open file for loading. Starting with an empty library.\n";
        }
    }
};

int main(){
    LibraryClass library;
    int userchoice;
    string title, authorname, query; 
    int bookID, volume, copies;

    do {
        cout << "\nLibrary Manga Management System\n";
        cout <<"1. Add Books\n";
        cout<< "2. View Books\n";
        cout <<"3. Search Books\n";
        cout<< "4. Remove Books\n";
        cout<< "5. Take Out Book\n";
        cout<< "6. Return Book\n";
        cout<< "7.Exit\n";
        cout<<"Enter your choice: ";
        cin >> userchoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    switch (userchoice){
        case 1:
            cout<<"Enter book title: ";
            getline(cin,title);
            cout<<"Enter book author: ";
            getline(cin,authorname);
            cout<<"Enter volume number: ";
            cin >> volume;
            cout << "Enter number of copies: ";
            cin >> copies;
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            library.addingBooks(title, authorname, volume, copies);
            break;
        
        case 2: 
            library.viewBooks();
            break;
        case 3:
            cout<<"Enter title, volume or author to search: ";
            getline(cin,query);
            library.searchBooks(query);
            break;
        case 4:
            cout<<"Enter book ID to remove: ";
            cin >> bookID;
            library.removeBooks(bookID);
            break;
        case 5: 
            cout<<"Enter book ID to take out";
            cin >> bookID;
            library.takeOutBook(bookID);
            break;

        case 6: 
            cout<<"Enter book ID to return";
            cin >> bookID;
            library.returnbooks(bookID);
            break;
        case 7: 
            cout<< "Exiting the program.\n";
            break;
        default:
            cout<< "Invaild choice.Please try again.\n";
    }
  } while (userchoice !=7);

    return 0;
}