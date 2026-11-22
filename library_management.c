#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

// Book record structure based on video attributes
struct Book {
    int id;
    char title[50];
    char author[50];
    float price;
    int isIssued;            // 0 = Available, 1 = Issued
    char issuedTo[50];       // Student name
    int issuedRoll;          // Student roll number
};

// Function prototypes
void addBook(struct Book b[], int *count);
void displayBooks(const struct Book b[], int count);
void displayIssuedBooks(const struct Book b[], int count);
void searchById(const struct Book b[], int count);
void searchByTitle(const struct Book b[], int count);
void issueBook(struct Book b[], int count);
void returnBook(struct Book b[], int count);
void removeBook(struct Book b[], int *count);
void sortBooksByPrice(struct Book b[], int count);
void clearInputBuffer();

int main() {
    struct Book library[MAX_BOOKS];
    int count = 0;
    int choice;

    do {
        printf("\n=========================================\n");
        printf("        LIBRARY MANAGEMENT SYSTEM        \n");
        printf("=========================================\n");
        printf("1. Add New Book\n");
        printf("2. Display All Books (Catalogue)\n");
        printf("3. Display Issued Books List\n");
        printf("4. Search Book by ID\n");
        printf("5. Search Book by Title\n");
        printf("6. Issue a Book\n");
        printf("7. Return a Book\n");
        printf("8. Remove / Delete a Book\n");
        printf("9. Sort Books by Price (Ascending)\n");
        printf("0. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice (0-9): ");
        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("[Error] Please enter a valid number.\n");
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addBook(library, &count);
                break;
            case 2:
                displayBooks(library, count);
                break;
            case 3:
                displayIssuedBooks(library, count);
                break;
            case 4:
                searchById(library, count);
                break;
            case 5:
                searchByTitle(library, count);
                break;
            case 6:
                issueBook(library, count);
                break;
            case 7:
                returnBook(library, count);
                break;
            case 8:
                removeBook(library, &count);
                break;
            case 9:
                sortBooksByPrice(library, count);
                break;
            case 0:
                printf("\nExiting Library Management System. Have a nice day!\n");
                break;
            default:
                printf("\n[Error] Invalid choice! Select between 0 and 9.\n");
        }
    } while (choice != 0);

    return 0;
}

// Clears leftover newlines from input buffer to prevent skipping prompts
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// 1. Add Book
void addBook(struct Book b[], int *count) {
    if (*count >= MAX_BOOKS) {
        printf("\n[Error] Catalogue full! Cannot add more records.\n");
        return;
    }

    printf("\n--- Add New Book ---\n");
    printf("Enter Book ID: ");
    scanf("%d", &b[*count].id);
    clearInputBuffer();

    // Prevent duplicate IDs
    for (int i = 0; i < *count; i++) {
        if (b[i].id == b[*count].id) {
            printf("[Error] A book with ID %d already exists.\n", b[*count].id);
            return;
        }
    }

    printf("Enter Book Title: ");
    scanf(" %49[^\n]", b[*count].title);
    clearInputBuffer();

    printf("Enter Author Name: ");
    scanf(" %49[^\n]", b[*count].author);
    clearInputBuffer();

    printf("Enter Price: ");
    scanf("%f", &b[*count].price);
    clearInputBuffer();

    b[*count].isIssued = 0;
    strcpy(b[*count].issuedTo, "N/A");
    b[*count].issuedRoll = 0;
    (*count)++;

    printf("[Success] Book added successfully!\n");
}

// 2. Display All Books
void displayBooks(const struct Book b[], int count) {
    if (count == 0) {
        printf("\n[Notice] No books in the library.\n");
        return;
    }

    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("%-6s %-26s %-20s %-10s %-12s %-15s %-8s\n", "ID", "Title", "Author", "Price", "Status", "Student Name", "Roll No");
    printf("------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        printf("%-6d %-26s %-20s %-10.2f %-12s %-15s %-8d\n",
               b[i].id,
               b[i].title,
               b[i].author,
               b[i].price,
               (b[i].isIssued == 1) ? "Issued" : "Available",
               b[i].issuedTo,
               b[i].issuedRoll);
    }
    printf("------------------------------------------------------------------------------------------------------\n");
}

// 3. Display Only Issued Books
void displayIssuedBooks(const struct Book b[], int count) {
    int issuedCount = 0;
    printf("\n------------------------------------------------------------------------------\n");
    printf("%-6s %-26s %-20s %-15s %-8s\n", "ID", "Title", "Author", "Issued To", "Roll No");
    printf("------------------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) {
        if (b[i].isIssued == 1) {
            printf("%-6d %-26s %-20s %-15s %-8d\n",
                   b[i].id, b[i].title, b[i].author, b[i].issuedTo, b[i].issuedRoll);
            issuedCount++;
        }
    }

    if (issuedCount == 0) {
        printf("[Notice] There are currently no issued books.\n");
    }
    printf("------------------------------------------------------------------------------\n");
}

// 4. Search by ID
void searchById(const struct Book b[], int count) {
    if (count == 0) {
        printf("\n[Notice] Library catalogue is empty.\n");
        return;
    }

    int targetId, found = 0;
    printf("\nEnter Book ID to search: ");
    scanf("%d", &targetId);
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (b[i].id == targetId) {
            printf("\n--- Book Found ---\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nPrice: Rs. %.2f\nStatus: %s\n",
                   b[i].id, b[i].title, b[i].author, b[i].price,
                   (b[i].isIssued == 1) ? "Issued" : "Available");
            if (b[i].isIssued == 1) {
                printf("Issued To: %s (Roll No: %d)\n", b[i].issuedTo, b[i].issuedRoll);
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("[Notice] Book with ID %d not found.\n", targetId);
    }
}

// 5. Search by Title
void searchByTitle(const struct Book b[], int count) {
    if (count == 0) {
        printf("\n[Notice] Library catalogue is empty.\n");
        return;
    }

    char targetTitle[50];
    int found = 0;
    printf("\nEnter Book Title to search: ");
    scanf(" %49[^\n]", targetTitle);
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (strcmp(b[i].title, targetTitle) == 0) {
            printf("\n--- Book Found ---\n");
            printf("ID: %d | Title: %s | Author: %s | Status: %s\n",
                   b[i].id, b[i].title, b[i].author,
                   (b[i].isIssued == 1) ? "Issued" : "Available");
            if (b[i].isIssued == 1) {
                printf("Issued To: %s | Roll No: %d\n", b[i].issuedTo, b[i].issuedRoll);
            }
            found = 1;
        }
    }

    if (!found) {
        printf("[Notice] No book found with title: %s\n", targetTitle);
    }
}

// 6. Issue Book
void issueBook(struct Book b[], int count) {
    if (count == 0) {
        printf("\n[Notice] Library catalogue is empty.\n");
        return;
    }

    int targetId, found = 0;
    printf("\nEnter Book ID to issue: ");
    scanf("%d", &targetId);
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (b[i].id == targetId) {
            found = 1;
            if (b[i].isIssued == 1) {
                printf("[Warning] Book is already issued to %s (Roll No: %d)!\n",
                       b[i].issuedTo, b[i].issuedRoll);
            } else {
                printf("Enter Student Name: ");
                scanf(" %49[^\n]", b[i].issuedTo);
                clearInputBuffer();

                printf("Enter Student Roll No: ");
                scanf("%d", &b[i].issuedRoll);
                clearInputBuffer();

                b[i].isIssued = 1;
                printf("[Success] Book '%s' (ID: %d) successfully issued to %s.\n",
                       b[i].title, b[i].id, b[i].issuedTo);
            }
            break;
        }
    }

    if (!found) {
        printf("[Notice] Book with ID %d not found.\n", targetId);
    }
}

// 7. Return Book
void returnBook(struct Book b[], int count) {
    if (count == 0) {
        printf("\n[Notice] Library catalogue is empty.\n");
        return;
    }

    int targetId, found = 0;
    printf("\nEnter Book ID to return: ");
    scanf("%d", &targetId);
    clearInputBuffer();

    for (int i = 0; i < count; i++) {
        if (b[i].id == targetId) {
            found = 1;
            if (b[i].isIssued == 0) {
                printf("[Notice] Book ID %d is already in the library (not issued).\n", targetId);
            } else {
                printf("[Success] Book '%s' (ID: %d) returned by %s (Roll No: %d) successfully.\n",
                       b[i].title, b[i].id, b[i].issuedTo, b[i].issuedRoll);
                b[i].isIssued = 0;
                strcpy(b[i].issuedTo, "N/A");
                b[i].issuedRoll = 0;
            }
            break;
        }
    }

    if (!found) {
        printf("[Notice] Book with ID %d not found.\n", targetId);
    }
}

// 8. Remove Book (Shift logic)
void removeBook(struct Book b[], int *count) {
    if (*count == 0) {
        printf("\n[Notice] Library catalogue is empty. Nothing to remove.\n");
        return;
    }

    int targetId, found = 0;
    printf("\nEnter Book ID to remove: ");
    scanf("%d", &targetId);
    clearInputBuffer();

    for (int i = 0; i < *count; i++) {
        if (b[i].id == targetId) {
            found = 1;

            if (b[i].isIssued == 1) {
                printf("[Warning] Cannot delete this book because it is currently issued to %s!\n", b[i].issuedTo);
                return;
            }

            // Shift elements to the left to delete the record
            for (int j = i; j < *count - 1; j++) {
                b[j] = b[j + 1];
            }
            (*count)--;
            printf("[Success] Book with ID %d has been removed from the library.\n", targetId);
            break;
        }
    }

    if (!found) {
        printf("[Notice] Book with ID %d not found.\n", targetId);
    }
}

// 9. Sort Books by Price
void sortBooksByPrice(struct Book b[], int count) {
    if (count <= 1) {
        printf("\n[Notice] Not enough records to sort.\n");
        return;
    }

    struct Book temp;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - 1 - i; j++) {
            if (b[j].price > b[j + 1].price) {
                temp = b[j];
                b[j] = b[j + 1];
                b[j + 1] = temp;
            }
        }
    }

    printf("\n[Success] Books sorted by price in ascending order successfully!\n");
    displayBooks(b, count);
}