#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 101
#define ROWS 5
#define SEATS_PER_ROW 10
#define STACK_SIZE 100

/* -------------------- DATA STRUCTURES -------------------- */

typedef struct {
    int movieID;
    char title[100];
    char genre[50];
    float ticketPrice;
} Movie;

/* BST node for movies */
typedef struct MovieNode {
    Movie movie;
    struct MovieNode *left;
    struct MovieNode *right;
} MovieNode;

/* Booking record */
typedef struct {
    int bookingID;
    int movieID;
    char customerName[100];
    int row;
    int seat;
    int status; /* 1 = Active, 0 = Cancelled */
} Booking;

/* Hash table entry */
typedef struct {
    Booking booking;
    int occupied;
} HashEntry;

/* Doubly linked list node for booking history */
typedef struct BookingNode {
    Booking booking;
    struct BookingNode *prev;
    struct BookingNode *next;
} BookingNode;

/* Array stack for cancelled bookings */
typedef struct {
    Booking items[STACK_SIZE];
    int top;
} CancelledStack;

/* -------------------- GLOBAL VARIABLES -------------------- */

MovieNode *movieRoot = NULL;

HashEntry hashTable[HASH_SIZE];

BookingNode *historyHead = NULL;
BookingNode *historyTail = NULL;

CancelledStack cancelledStack;

int seats[ROWS][SEATS_PER_ROW];

/* -------------------- COMMON HELPERS -------------------- */

void initializeSeats(void) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            seats[i][j] = 0;
        }
    }
}

void initializeHashTable(void) {
    for (int i = 0; i < HASH_SIZE; i++) {
        hashTable[i].occupied = 0;
    }
}

void initializeStack(void) {
    cancelledStack.top = -1;
}

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

/* -------------------- BST: MOVIES -------------------- */

MovieNode *createMovieNode(Movie movie) {
    MovieNode *newNode = (MovieNode *)malloc(sizeof(MovieNode));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->movie = movie;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

MovieNode *insertMovie(MovieNode *root, Movie movie) {
    if (root == NULL) {
        return createMovieNode(movie);
    }

    if (movie.movieID < root->movie.movieID) {
        root->left = insertMovie(root->left, movie);
    } else if (movie.movieID > root->movie.movieID) {
        root->right = insertMovie(root->right, movie);
    } else {
        printf("Movie ID already exists.\n");
    }

    return root;
}

Movie *searchMovie(MovieNode *root, int movieID) {
    if (root == NULL) {
        return NULL;
    }

    if (movieID == root->movie.movieID) {
        return &root->movie;
    }

    if (movieID < root->movie.movieID) {
        return searchMovie(root->left, movieID);
    }

    return searchMovie(root->right, movieID);
}

void displayMovies(MovieNode *root) {
    if (root == NULL) {
        return;
    }

    displayMovies(root->left);

    printf("Movie ID: %d | Title: %s | Genre: %s | Price: Rs. %.2f\n",
           root->movie.movieID,
           root->movie.title,
           root->movie.genre,
           root->movie.ticketPrice);

    displayMovies(root->right);
}

void addMovie(void) {
    Movie movie;

    printf("\nEnter Movie ID: ");
    scanf("%d", &movie.movieID);
    clearInputBuffer();

    printf("Enter Movie Title: ");
    fgets(movie.title, sizeof(movie.title), stdin);
    movie.title[strcspn(movie.title, "\n")] = '\0';

    printf("Enter Genre: ");
    fgets(movie.genre, sizeof(movie.genre), stdin);
    movie.genre[strcspn(movie.genre, "\n")] = '\0';

    printf("Enter Ticket Price: ");
    scanf("%f", &movie.ticketPrice);

    if (searchMovie(movieRoot, movie.movieID) != NULL) {
        printf("Movie ID already exists.\n");
        return;
    }

    movieRoot = insertMovie(movieRoot, movie);
    printf("Movie added successfully.\n");
}

/* -------------------- 2D ARRAY: SEATS -------------------- */

void displaySeats(void) {
    printf("\n========== SEAT LAYOUT ==========\n");
    printf("     ");

    for (int j = 0; j < SEATS_PER_ROW; j++) {
        printf("%2d ", j + 1);
    }

    printf("\n");

    for (int i = 0; i < ROWS; i++) {
        printf(" %c   ", 'A' + i);

        for (int j = 0; j < SEATS_PER_ROW; j++) {
            if (seats[i][j] == 0) {
                printf(" O  ");
            } else {
                printf(" X  ");
            }
        }

        printf("\n");
    }

    printf("\nO = Available    X = Booked\n");
}

int getRowIndex(char rowChar) {
    if (rowChar >= 'a' && rowChar <= 'e') {
        rowChar = rowChar - 'a' + 'A';
    }

    if (rowChar < 'A' || rowChar > 'E') {
        return -1;
    }

    return rowChar - 'A';
}

/* -------------------- HASH TABLE: BOOKINGS -------------------- */

int hashFunction(int bookingID) {
    return bookingID % HASH_SIZE;
}

int insertBooking(Booking booking) {
    int index = hashFunction(booking.bookingID);

    for (int i = 0; i < HASH_SIZE; i++) {
        int probeIndex = (index + i) % HASH_SIZE;

        if (!hashTable[probeIndex].occupied) {
            hashTable[probeIndex].booking = booking;
            hashTable[probeIndex].occupied = 1;
            return 1;
        }
    }

    return 0;
}

Booking *searchBooking(int bookingID) {
    int index = hashFunction(bookingID);

    for (int i = 0; i < HASH_SIZE; i++) {
        int probeIndex = (index + i) % HASH_SIZE;

        if (!hashTable[probeIndex].occupied) {
            return NULL;
        }

        if (hashTable[probeIndex].booking.bookingID == bookingID) {
            return &hashTable[probeIndex].booking;
        }
    }

    return NULL;
}

/* -------------------- DLL: BOOKING HISTORY -------------------- */

void addToHistory(Booking booking) {
    BookingNode *newNode = (BookingNode *)malloc(sizeof(BookingNode));

    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    newNode->booking = booking;
    newNode->prev = historyTail;
    newNode->next = NULL;

    if (historyHead == NULL) {
        historyHead = newNode;
        historyTail = newNode;
    } else {
        historyTail->next = newNode;
        historyTail = newNode;
    }
}

void updateHistoryStatus(int bookingID, int status) {
    BookingNode *current = historyHead;

    while (current != NULL) {
        if (current->booking.bookingID == bookingID) {
            current->booking.status = status;
            return;
        }

        current = current->next;
    }
}

void displayBooking(Booking booking) {
    printf("Booking ID: %d | Movie ID: %d | Customer: %s | Seat: %c%d | Status: %s\n",
           booking.bookingID,
           booking.movieID,
           booking.customerName,
           'A' + booking.row,
           booking.seat + 1,
           booking.status ? "Active" : "Cancelled");
}

void displayHistoryForward(void) {
    BookingNode *current = historyHead;

    printf("\n========== BOOKING HISTORY (FORWARD) ==========\n");

    if (current == NULL) {
        printf("No booking history.\n");
        return;
    }

    while (current != NULL) {
        displayBooking(current->booking);
        current = current->next;
    }
}

void displayHistoryBackward(void) {
    BookingNode *current = historyTail;

    printf("\n========== BOOKING HISTORY (BACKWARD) ==========\n");

    if (current == NULL) {
        printf("No booking history.\n");
        return;
    }

    while (current != NULL) {
        displayBooking(current->booking);
        current = current->prev;
    }
}

/* -------------------- STACK: CANCELLED BOOKINGS -------------------- */

int pushCancelledBooking(Booking booking) {
    if (cancelledStack.top == STACK_SIZE - 1) {
        return 0;
    }

    cancelledStack.items[++cancelledStack.top] = booking;
    return 1;
}

Booking *peekCancelledBooking(void) {
    if (cancelledStack.top == -1) {
        return NULL;
    }

    return &cancelledStack.items[cancelledStack.top];
}

Booking popCancelledBooking(void) {
    Booking emptyBooking = {0};

    if (cancelledStack.top == -1) {
        return emptyBooking;
    }

    return cancelledStack.items[cancelledStack.top--];
}

void displayCancelledBookings(void) {
    printf("\n========== CANCELLED BOOKINGS (STACK) ==========\n");

    if (cancelledStack.top == -1) {
        printf("No cancelled bookings.\n");
        return;
    }

    for (int i = cancelledStack.top; i >= 0; i--) {
        displayBooking(cancelledStack.items[i]);
    }
}

/* -------------------- BOOKING OPERATIONS -------------------- */

void makeBooking(void) {
    int bookingID;
    int movieID;
    char rowChar;
    int row;
    int seatNumber;
    Movie *movie;

    Booking booking;

    printf("\n========== MAKE BOOKING ==========\n");

    printf("Enter Booking ID: ");
    scanf("%d", &bookingID);

    if (searchBooking(bookingID) != NULL) {
        printf("Booking ID already exists.\n");
        return;
    }

    printf("Enter Movie ID: ");
    scanf("%d", &movieID);

    movie = searchMovie(movieRoot, movieID);

    if (movie == NULL) {
        printf("Movie not found.\n");
        return;
    }

    displaySeats();

    printf("Enter Row (A-E): ");
    scanf(" %c", &rowChar);

    row = getRowIndex(rowChar);

    if (row == -1) {
        printf("Invalid row.\n");
        return;
    }

    printf("Enter Seat Number (1-10): ");
    scanf("%d", &seatNumber);

    if (seatNumber < 1 || seatNumber > SEATS_PER_ROW) {
        printf("Invalid seat number.\n");
        return;
    }

    if (seats[row][seatNumber - 1] == 1) {
        printf("Seat is already booked.\n");
        return;
    }

    clearInputBuffer();

    printf("Enter Customer Name: ");
    fgets(booking.customerName, sizeof(booking.customerName), stdin);
    booking.customerName[strcspn(booking.customerName, "\n")] = '\0';

    booking.bookingID = bookingID;
    booking.movieID = movieID;
    booking.row = row;
    booking.seat = seatNumber - 1;
    booking.status = 1;

    if (!insertBooking(booking)) {
        printf("Booking could not be stored. Hash table is full.\n");
        return;
    }

    seats[row][seatNumber - 1] = 1;
    addToHistory(booking);

    printf("\nBooking successful!\n");
    printf("Movie: %s\n", movie->title);
    printf("Ticket Price: Rs. %.2f\n", movie->ticketPrice);
    displayBooking(booking);
}

void viewBooking(void) {
    int bookingID;
    Booking *booking;

    printf("\nEnter Booking ID: ");
    scanf("%d", &bookingID);

    booking = searchBooking(bookingID);

    if (booking == NULL) {
        printf("Booking not found.\n");
        return;
    }

    printf("\nBooking found:\n");
    displayBooking(*booking);
}

void cancelBooking(void) {
    int bookingID;
    Booking *booking;

    printf("\nEnter Booking ID to cancel: ");
    scanf("%d", &bookingID);

    booking = searchBooking(bookingID);

    if (booking == NULL) {
        printf("Booking not found.\n");
        return;
    }

    if (booking->status == 0) {
        printf("Booking is already cancelled.\n");
        return;
    }

    /* Free the seat */
    seats[booking->row][booking->seat] = 0;

    /* Update booking status in hash table */
    booking->status = 0;

    /* Keep DLL history consistent */
    updateHistoryStatus(bookingID, 0);

    /* Push cancelled booking onto stack */
    if (!pushCancelledBooking(*booking)) {
        printf("Warning: cancellation stack is full.\n");
    }

    printf("Booking cancelled successfully.\n");
}

/* -------------------- DEFAULT MOVIES -------------------- */

void loadDefaultMovies(void) {
    Movie movies[] = {
        {103, "Interstellar", "Sci-Fi", 250.00f},
        {101, "Inception", "Sci-Fi", 220.00f},
        {105, "Avengers", "Action", 280.00f},
        {102, "The Dark Knight", "Action", 240.00f},
        {104, "Parasite", "Thriller", 200.00f}
    };

    int count = sizeof(movies) / sizeof(movies[0]);

    for (int i = 0; i < count; i++) {
        movieRoot = insertMovie(movieRoot, movies[i]);
    }
}

/* -------------------- MEMORY CLEANUP -------------------- */

void freeMovieTree(MovieNode *root) {
    if (root == NULL) {
        return;
    }

    freeMovieTree(root->left);
    freeMovieTree(root->right);
    free(root);
}

void freeHistory(void) {
    BookingNode *current = historyHead;

    while (current != NULL) {
        BookingNode *next = current->next;
        free(current);
        current = next;
    }
}

/* -------------------- MAIN MENU -------------------- */

void displayMenu(void) {
    printf("\n========================================\n");
    printf("       MOVIE TICKET BOOKING SYSTEM\n");
    printf("========================================\n");
    printf("1. Add Movie\n");
    printf("2. Display Movies\n");
    printf("3. Search Movie by Movie ID\n");
    printf("4. Display Seat Layout\n");
    printf("5. Make Booking\n");
    printf("6. Search Booking by Booking ID\n");
    printf("7. Cancel Booking\n");
    printf("8. Display Booking History (Forward)\n");
    printf("9. Display Booking History (Backward)\n");
    printf("10. Display Cancelled Bookings (Stack)\n");
    printf("11. View Most Recent Cancellation\n");
    printf("12. Exit\n");
    printf("========================================\n");
}

int main(void) {
    int choice;
    int movieID;
    Movie *movie;
    Booking *recentCancellation;

    initializeSeats();
    initializeHashTable();
    initializeStack();
    loadDefaultMovies();

    printf("Welcome to the Movie Ticket Booking System!\n");

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMovie();
                break;

            case 2:
                printf("\n========== MOVIES ==========\n");
                displayMovies(movieRoot);
                break;

            case 3:
                printf("\nEnter Movie ID: ");
                scanf("%d", &movieID);

                movie = searchMovie(movieRoot, movieID);

                if (movie == NULL) {
                    printf("Movie not found.\n");
                } else {
                    printf("\nMovie found:\n");
                    printf("Movie ID: %d\n", movie->movieID);
                    printf("Title: %s\n", movie->title);
                    printf("Genre: %s\n", movie->genre);
                    printf("Ticket Price: Rs. %.2f\n", movie->ticketPrice);
                }
                break;

            case 4:
                displaySeats();
                break;

            case 5:
                makeBooking();
                break;

            case 6:
                viewBooking();
                break;

            case 7:
                cancelBooking();
                break;

            case 8:
                displayHistoryForward();
                break;

            case 9:
                displayHistoryBackward();
                break;

            case 10:
                displayCancelledBookings();
                break;

            case 11:
                recentCancellation = peekCancelledBooking();

                if (recentCancellation == NULL) {
                    printf("No cancelled bookings.\n");
                } else {
                    printf("\nMost Recent Cancellation:\n");
                    displayBooking(*recentCancellation);
                }
                break;

            case 12:
                freeMovieTree(movieRoot);
                freeHistory();

                printf("Thank you for using the Movie Ticket Booking System!\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
