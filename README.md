# Movie Ticket Booking System

## Project Overview

The Movie Ticket Booking System is a console-based application developed in C to demonstrate the practical implementation of Data Structures and Algorithms (DSA).

The system manages movies, cinema seats, customer bookings, booking history, and cancelled bookings using different data structures. Each data structure is selected according to the type of operation it supports efficiently.

## Objectives

- Manage movie details efficiently.
- Search movies using Movie ID.
- Display and manage cinema seat availability.
- Create and search customer bookings.
- Maintain booking history.
- Manage cancelled bookings.
- Demonstrate the practical use of multiple DSA concepts in a single application.

## Features

- Add new movies.
- Display all available movies.
- Search for a movie by Movie ID.
- Display the cinema seat layout.
- Book an available seat.
- Search for a booking using Booking ID.
- Cancel an existing booking.
- Display booking history in forward order.
- Display booking history in backward order.
- Display cancelled bookings.
- View the most recently cancelled booking.

## Data Structures Used

| Data Structure | Application |
|---|---|
| Binary Search Tree (BST) | Movie management and searching by Movie ID |
| Hash Table | Booking management and searching by Booking ID |
| 2D Array | Cinema seat management |
| Doubly Linked List | Booking history |
| Stack | Cancelled bookings |

## System Architecture

```text
Movie Ticket Booking System
│
├── Movie Management
│   └── Binary Search Tree
│       ├── insertMovie()
│       ├── searchMovie()
│       └── displayMovies()
│
├── Seat Management
│   └── 2D Array
│       ├── displaySeats()
│       ├── bookSeat()
│       └── cancelSeat()
│
├── Booking Management
│   └── Hash Table
│       ├── insertBooking()
│       ├── searchBooking()
│       └── deleteBooking()
│
├── Booking History
│   └── Doubly Linked List
│       ├── addBooking()
│       ├── displayForward()
│       └── displayBackward()
│
└── Cancellation
    └── Stack
        ├── push()
        ├── pop()
        └── peek()
```

## Data Structure Implementation

### 1. Binary Search Tree

The Binary Search Tree stores movie information using Movie ID as the key.

It supports:
- Adding movies.
- Searching for a movie by Movie ID.
- Displaying movies in sorted order.

### 2. Hash Table

The Hash Table stores booking records using Booking ID.

Linear probing is used to handle collisions. This provides efficient average-case access to booking information.

### 3. 2D Array

The cinema seating arrangement is represented using a two-dimensional array.

The rows and seats are mapped directly to array positions:
- `0` represents an available seat.
- `1` represents a booked seat.

This allows direct access to a particular seat.

### 4. Doubly Linked List

The Doubly Linked List maintains the booking history.

Each booking record contains links to both the previous and next booking. This allows the history to be displayed in both forward and backward directions.

### 5. Stack

The Stack stores cancelled bookings.

Cancelled bookings are inserted using the push operation and can be accessed according to the Last-In, First-Out (LIFO) principle. The most recently cancelled booking can also be viewed using the peek operation.

## Booking Workflow

1. The user selects the movie using its Movie ID.
2. The system searches for the movie in the Binary Search Tree.
3. Available seats are displayed.
4. The user selects an available seat.
5. Booking details are entered.
6. The booking is inserted into the Hash Table.
7. The selected seat is marked as booked.
8. The booking is added to the Doubly Linked List.
9. The booking is stored as part of the system's booking history.

## Cancellation Workflow

1. The user enters the Booking ID.
2. The system searches for the booking in the Hash Table.
3. The booking status is checked.
4. The selected seat is released.
5. The booking status is changed to cancelled.
6. The booking history is updated.
7. The cancelled booking is pushed onto the Stack.

## Program Menu

```text
1. Add Movie
2. Display Movies
3. Search Movie by Movie ID
4. Display Seat Layout
5. Make Booking
6. Search Booking by Booking ID
7. Cancel Booking
8. Display Booking History Forward
9. Display Booking History Backward
10. Display Cancelled Bookings
11. View Most Recent Cancellation
12. Exit
```

## Complexity Analysis

| Operation | Data Structure | Average / Typical Complexity |
|---|---|---|
| Movie Search | BST | O(log n) |
| Movie Insertion | BST | O(log n) |
| Booking Search | Hash Table | O(1) average |
| Booking Insertion | Hash Table | O(1) average |
| Seat Access | 2D Array | O(1) |
| Add Booking History | Doubly Linked List | O(1) |
| History Traversal | Doubly Linked List | O(n) |
| Stack Push | Stack | O(1) |
| Stack Pop | Stack | O(1) |
| Stack Peek | Stack | O(1) |

For the Binary Search Tree and Hash Table, worst-case performance can be O(n), depending on the structure of the tree and the number of hash collisions.

## Project Structure

```text
Movie-Booking-System/
│
├── dsa.c
├── README.md
└── .gitignore
```

## Compilation and Execution

### Linux / macOS

```bash
gcc dsa.c -o dsa
./dsa
```

### Windows using MinGW

```bash
gcc dsa.c -o dsa.exe
dsa.exe
```

## Sample Movies

The program contains the following default movies:

| Movie ID | Movie | Genre | Ticket Price |
|---:|---|---|---:|
| 101 | Inception | Sci-Fi | Rs. 220 |
| 102 | The Dark Knight | Action | Rs. 240 |
| 103 | Interstellar | Sci-Fi | Rs. 250 |
| 104 | Parasite | Thriller | Rs. 200 |
| 105 | Avengers | Action | Rs. 280 |

## Seat Configuration

The cinema contains:

- 5 rows
- 10 seats per row
- 50 seats in total

The seat layout is represented using a 5 × 10 two-dimensional array.

## Technologies Used

- **Programming Language:** C
- **Concepts:** Data Structures and Algorithms
- **Interface:** Console-based application
- **Compiler:** GCC / MinGW

## Future Enhancements

- Add customer login and authentication.
- Add multiple cinema screens.
- Add movie deletion and update operations.
- Add persistent file storage for bookings.
- Add payment processing.
- Add a graphical user interface.
- Add date and show-time management.

## Team Members

- Jeswin
- Aditya
