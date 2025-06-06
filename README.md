# 📚 BookStore-AVL

A Windows console-based bookstore inventory and sales management system built in C. It uses an **AVL Tree** for managing the book catalog and **queues** for handling customer purchases and demand records. The system supports both customer and admin roles with a full suite of features for managing books, selling inventory, tracking purchases, and handling out-of-stock requests.

---

## 🔧 Features

### 🧑‍💼 Admin Mode:
- Add new books to the system
- View the entire inventory (cost price, stock)
- Refill stock quantities
- Search for books by ID or title
- View demand list (out-of-stock requests)
- View and log all purchases
- Save updated book inventory to a CSV file

### 🛍️ Customer Mode:
- View available books (name, author, selling price)
- Buy books (if in stock)
- Search for a book
- Submit a demand request for out-of-stock books

---

## 🧰 Technologies Used

| Component        | Details                                     |
|------------------|---------------------------------------------|
| Language         | C                                           |
| Data Structures  | AVL Tree (for inventory), Queues (for logs) |
| File I/O         | CSV read/write (`bookList.csv`)             |
| Interface        | Windows console with `conio.h`, `getch()`   |
| Compiler         | GCC / TDM-GCC on Windows                    |

---


## 🖥️ How to Compile and Run

### 🧱 Prerequisites

- A Windows system with a C compiler that supports `conio.h`
- Recommended: TDM-GCC or Turbo C++

### 💻 Compilation

```bash
gcc main.c -o bookstore
./bookstore


