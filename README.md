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

---

## 📂 Sample Book Inventory (bookList.csv)

The application reads from and writes to a CSV file named `bookList.csv` which stores the book inventory using the following format:

| BookId | BookName      | Author       | Quantity | Cost (₹) | Sell (₹) | Shelf No |
|--------|---------------|--------------|----------|----------|----------|-----------|
| 101    | AtomicHabits  | JamesClear   | 20       | 150      | 200      | 3         |
| 102    | ZeroToOne     | PeterThiel   | 15       | 120      | 180      | 4         |

Each row contains:
- A unique `BookId`
- Book name and author
- Number of copies in stock (`Quantity`)
- `Cost` (internal purchase price)
- `Sell` (customer price)
- `Shelf No` for physical arrangement

Ensure this file exists in the same directory as the executable for the app to load properly.

You can add more entries manually or through the Admin mode in the program.

---



