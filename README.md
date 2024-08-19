# Manga Book Management System

Welcome to the **Manga Book Management System** project! This advanced C++ application allows you to efficiently manage a collection of manga books, with features such as adding new books, viewing the collection, searching by title, author, or volume, taking out and returning books, and removing books from the system.

## Table of Contents
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Code Overview](#code-overview)
- [Advanced Features](#advanced-features)
- [Contributing](#contributing)
- [License](#license)

## Features

- **Add New Books**: Add new manga books to the library with details such as title, author, volume number, and the number of copies available.
- **View Collection**: Display all books currently available in the library.
- **Search Books**: Search for books by title, author, or volume number. The search is case-insensitive.
- **Take Out Books**: Decrease the number of available copies when a book is taken out.
- **Return Books**: Increase the number of available copies when a book is returned.
- **Remove Books**: Remove a book from the library using its unique ID.
- **Persistent Storage**: Save and load the library data to and from a file (`library_manga_books.txt`), ensuring that the library's state is preserved between sessions.

## Installation

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/sanvega9/manga-book-management-system.git
   cd manga-book-management-system
