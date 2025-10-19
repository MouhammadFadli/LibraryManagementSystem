# 📚 Library Management System (C++)

A simple *Library Management System* built in C++ that allows users to:
- Add new books  
- Borrow and return books  
- Display available and borrowed books  
- Save all data in a local text file

---

## 🧠 Project Overview

This project is a *console-based application* for managing a small library.  
It helps keep track of books — whether they are available or borrowed — using struct data structures and file handling for persistent storage.

---

## 🧩 Features

- ✅ Add new books with unique IDs  
- 🔍 View all books with status (Available / Borrowed)  
- 📖 Borrow and return books easily  
- 💾 Data persistence using Books.txt file  
- 🖥️ User-friendly console interface  

---

🧑‍💻 Technologies Used

C++ Standard Library

fstream → for file handling

iomanip → for formatted output

vector → for dynamic data storage

---

## 🗂️ Data Structure

```cpp
struct stBook {
    int BookID;
    string BookTitle;
    string BookAuthor;
    bool IsBoroowed = true;
    int BookCount = 0;
};

---

🖥️ How to Run

1. Open the project in any C++ IDE (e.g., Code::Blocks, Visual Studio, Dev-C++, etc.)


2. Make sure the file Books.txt exists in the same directory (it will be created automatically if not).


3. Compile and run the program.


4. From the main menu, you can:

(1) Add a new book

(2) Display all books

(3) Borrow a book

(4) Return a book

(5) Exit the system




---

📋 Sample Output

- - -   Library Management System   - - -

1. Add a new book
2. Display all books
3. Borrow a book
4. Return a book
5. Exit
================================================
Choose an option : 2

Example of displayed books:

| Book ID         | Book Title                             | Author Name     | Is Borrowed |
-----------------------------------------------------------------------------------------
| 1                | The Great Gatsby                       | F. Scott        | Available   ✅
| 2                | 1984                                   | George Orwell   | Borrowed    ❌
-----------------------------------------------------------------------------------------
Total Books = 2

---

🏷️ Project Info

👨‍💻 Developer: [Mouhammad Al-Fadli]

📧 Email: fadlysyria@gmail.com

🌐 GitHub: github.com/MouhammadFadli

💡 Language: C++

📁 Type: Console Application

---

⭐ If you like this project, give it a star on GitHub! ❤️

---

📄 License

This project is open-source and available under the MIT License.

---