
# Library Management System in C

A menu-driven, console-based Library Management System written in standard C. Designed as a reference implementation demonstrating structures, arrays, pointers, functions, and string handling.

## Features
* **Add New Book:** Stores ID, title, author, and price with duplicate ID checking.
* **Display Catalogue:** Displays all books or filters only currently issued books.
* **Search:** Search records by Book ID or exact Title.
* **Issue & Return:** Tracks borrower name and roll number; prevents double-issuing.
* **Delete Record:** Removes unissued books using array-shifting logic.
* **Sort:** Sorts the catalogue by price in ascending order using Bubble Sort.

## How to Compile and Run
Requires any standard C compiler (e.g., GCC, MinGW, Clang).

```bash
gcc -Wall -Wextra library_management.c -o library_management
./library_management        # On Windows, run: library_management.exe
