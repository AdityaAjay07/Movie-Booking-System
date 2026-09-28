# Movie Ticket Booking System

A **DSA mini project in C** that demonstrates the practical use of multiple data structures in a Movie Ticket Booking System.

## Project Overview

The system allows users to:

- Add and search movies
- Display available movies
- Display cinema seat layout
- Book movie tickets
- Search bookings using Booking ID
- Cancel bookings
- View booking history in both directions
- View cancelled bookings
- View the most recently cancelled booking

The project is designed specifically to demonstrate different data structures and their real-world applications.

---

## Data Structures Used

| Data Structure | Used For | Why? |
|---|---|---|
| **Binary Search Tree (BST)** | Movie management/search | Movies can be searched using Movie ID |
| **2D Array** | Cinema seats | Naturally represents rows and columns of seats |
| **Hash Table** | Booking lookup | Fast average-case search using Booking ID |
| **Doubly Linked List** | Booking history | Supports forward and backward traversal |
| **Array Stack** | Cancelled bookings | Demonstrates LIFO behavior |

### Important mapping to remember

```text
BST              → Movies
Hash Table       → Bookings
2D Array         → Seats
Doubly Linked List → Booking History
Stack            → Cancelled Bookings
```

There is intentionally **no waiting-list queue** in the final version.

---

## System Workflow

### Booking

```text
Search Movie
     ↓
BST
     ↓
Select Seat
     ↓
2D Array
     ↓
Create Booking
     ↓
Hash Table
     ↓
Booking History
     ↓
Doubly Linked List
```

### Cancellation

```text
Cancel Booking
      ↓
Hash Table
      ↓
Free Seat in 2D Array
      ↓
Update Booking Status
      ↓
Doubly Linked List
      ↓
Push Cancelled Booking
      ↓
Stack
```

---

## Project Structure

```text
movie-ticket-booking-system/
│
├── dsa.c
├── README.md
└── .gitignore
```

---

## How to Run

### 1. Clone the repository

```bash
git clone <your-github-repository-url>
cd movie-ticket-booking-system
```

### 2. Compile

On macOS/Linux:

```bash
gcc dsa.c -o dsa
```

### 3. Run

```bash
./dsa
```

On Windows with MinGW:

```bash
gcc dsa.c -o dsa.exe
dsa.exe
```

---

## Example Features

### 1. Movie Search

The Movie ID is used as the key in a Binary Search Tree.

Example:

```text
Enter Movie ID: 103

Movie found:
Movie ID: 103
Title: Interstellar
Genre: Sci-Fi
Ticket Price: Rs. 250.00
```

### 2. Seat Layout

The cinema contains:

- 5 rows: A-E
- 10 seats per row

Example:

```text
      1  2  3  4  5  6  7  8  9 10
 A    O  O  O  O  O  O  O  O  O  O
 B    O  O  X  O  O  O  O  O  O  O
 C    O  O  O  O  O  O  O  O  O  O
 D    O  O  O  O  O  O  O  O  O  O
 E    O  O  O  O  O  O  O  O  O  O

O = Available
X = Booked
```

### 3. Booking Search

Booking IDs are stored in a hash table using **linear probing** for collision handling.

Average-case search complexity:

```text
O(1)
```

### 4. Booking History

Every successful booking is added to a doubly linked list.

The history can be displayed:

```text
Forward:  Oldest → Newest
Backward: Newest → Oldest
```

### 5. Cancellation Stack

When a booking is cancelled, it is pushed onto the stack.

This follows:

```text
LIFO
Last In, First Out
```

The most recent cancellation can therefore be viewed using `peek`.

---

## Data Structure Details

### Binary Search Tree

Each BST node contains:

```c
typedef struct MovieNode {
    Movie movie;
    struct MovieNode *left;
    struct MovieNode *right;
} MovieNode;
```

BST rule:

```text
Smaller Movie ID → Left
Larger Movie ID  → Right
```

Average search complexity:

```text
O(log n)
```

Worst case:

```text
O(n)
```

The implementation is a normal BST, not a self-balancing tree.

---

### Hash Table

Booking IDs are converted into hash table indexes using:

```c
bookingID % HASH_SIZE
```

If a collision occurs, **linear probing** is used:

```text
index
index + 1
index + 2
...
```

Average search complexity:

```text
O(1)
```

Worst case:

```text
O(n)
```

Cancelled bookings remain in the hash table with their status changed to `Cancelled`. This allows the system to still find an old booking and display its status.

---

### 2D Array

Seats are represented as:

```c
int seats[ROWS][SEATS_PER_ROW];
```

Where:

```text
0 → Available
1 → Booked
```

This gives direct O(1) access to a particular seat.

---

### Doubly Linked List

Each history node contains:

```text
Previous ← Node → Next
```

This allows traversal in both directions.

The project demonstrates:

```text
Forward traversal
Backward traversal
```

Adding a booking to the end of the history is O(1) because the list maintains a tail pointer.

---

### Stack

Cancelled bookings are stored in an array-based stack.

Operations include:

```text
push()
pop()
peek()
```

Each operation is O(1).

The stack demonstrates the **LIFO** principle.

---

## Complexity Summary

| Operation | Data Structure | Average Complexity |
|---|---|---:|
| Search Movie | BST | O(log n) |
| Insert Movie | BST | O(log n) |
| Search Booking | Hash Table | O(1) |
| Insert Booking | Hash Table | O(1) |
| Access Seat | 2D Array | O(1) |
| Add History | Doubly Linked List | O(1) |
| Traverse History | Doubly Linked List | O(n) |
| Push Cancellation | Stack | O(1) |
| Pop Cancellation | Stack | O(1) |
| Peek Cancellation | Stack | O(1) |

BST and hash-table complexities are average-case values; their worst cases can be O(n).

---

# Presentation Cheat Sheet

## 30-Second Introduction

> "Our project is a Movie Ticket Booking System implemented in C. The main purpose of the project is to demonstrate how different data structures can be applied to a real-world application. We use a Binary Search Tree for movie search, a Hash Table for booking search, a 2D Array for seats, a Doubly Linked List for booking history, and a Stack for cancelled bookings."

---

## If Asked: Why BST?

Say:

> "We use a BST because each movie has a unique Movie ID. The Movie ID acts as the key, so we can efficiently search and insert movies according to the BST property."

---

## If Asked: Why Hash Table?

Say:

> "Booking IDs are unique, so a hash table is suitable for quickly locating a booking. We use the Booking ID as the key and linear probing for collision handling."

---

## If Asked: Why 2D Array?

Say:

> "A cinema naturally has rows and seats, so a 2D array directly represents the seating arrangement. Each position stores whether the seat is available or booked."

---

## If Asked: Why Doubly Linked List?

Say:

> "Booking history may need to be viewed from oldest to newest or newest to oldest. A doubly linked list allows traversal in both directions using previous and next pointers."

---

## If Asked: Why Stack?

Say:

> "Cancelled bookings are pushed onto a stack so that the most recently cancelled booking can be accessed first. This demonstrates the LIFO principle."

---

## Most Important Flow to Remember

```text
MOVIE SEARCH
    ↓
   BST
    ↓
SEAT SELECTION
    ↓
 2D ARRAY
    ↓
BOOKING CREATED
    ↓
HASH TABLE
    ↓
BOOKING HISTORY
    ↓
DOUBLY LINKED LIST
```

For cancellation:

```text
BOOKING
   ↓
HASH TABLE
   ↓
FREE SEAT
   ↓
STACK
```

---

## GitHub Upload

After creating the three files:

```bash
git init
git add .
git commit -m "Initial Movie Ticket Booking System"
git branch -M main
git remote add origin <your-github-repository-url>
git push -u origin main
```

Replace `<your-github-repository-url>` with the URL of your GitHub repository.

---

## Future Improvements

Possible future additions:

- User login
- Online payment simulation
- Multiple theatres/screens
- Movie ratings
- Date and show-time selection
- Persistent file/database storage
- Graphical user interface
- Waiting-list queue

These are not required for the current DSA implementation.

---

## Authors

**B.Tech CSE – DSA Mini Project**

Team members:

- [Your Name]
- Aditya

---

## Technologies

- Language: **C**
- Compiler: **GCC**
- Version Control: **Git / GitHub**
- Concepts: **BST, Hash Table, 2D Array, Doubly Linked List, Stack**
