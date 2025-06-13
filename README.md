# Project description

## Project Overview
The objective of this project was to design and implement a robust Library Management System using Object-Oriented Programming principles in C++.
The system models real-world library operations through three core classes: Book, Member, and Library. The Book class maintains information such as title, author, ISBN, available and total copies, with support for multiple constructors (including copy constructors and default arguments) and data validation to prevent logical inconsistencies (like negative book counts).
## Class Definitions
1. **`Book`** - Represents a book in the library.
 - **Attributes**:
   - `title` (public, `string`): Title of the book
   - `author` (public, `string`): Author of the book
   - `isbn` (private, `string`): Unique identifier for the book
   - `copiesAvailable` (private, `int`): Number of available copies
   - `totalCopies` (private, `int`): Total copies of the book in the library
- **Methods**:
    
  Constructors:  
  1. Create a parameterized constructor to initialize all the attributes.  
  2. A constructor with default arguments for title, author, isbn, copiesAvailable, totalCopies ("UnknownTitle", "UnknownAuthor", “ISBN”, 0, 5).  
  3. One copy constructor to initialize a book using another book instance. Also pass another argument (a new isbn) to this constructor and assign the isbn of the copied book to this new isbn.
      
  Getters and Setters:  
  1. Getters for isbn, copiesAvailable, and totalCopies.
  2. A setter updateCopies(count): increases or decreases the available and the total count of the book ensuring that neither available count or total count becomes less than zero. If the condition is violated then ignore the request and print the statement “Invalid request! Count becomes negative”.
     
  Utility Methods:  
  1. `bool borrowBook()`: Decreases `copiesAvailable` if a copy is available; returns true if successful and false otherwise (print the message `“Invalid request! Copy of book not available”` for this case).
  2. `bool returnBook()`: Increases `copiesAvailable` up to `totalCopies` (if the method is called such that the copiesAvailable exceeds totalCopies then the request should be ignored, an error message should be printed stating `“Invalid request! Copy of book exceeds total copies”` and the copiesAvailable should not be changed ). If return book was successful then return true. Else return false.
  3. `void printDetails()`: Prints all details of the book. The format should be  `“title author”` (the entities are separated by a single space).
     
- **Book Constraints**:
  1. No two books can have the same isbn. If the constraint is violated then the book which is being entered into the system later is removed from the system (i.e. only the first book which was present in the system persists and all the later books are not added to the system).
  2. A book's `copiesAvailable` should never exceed `totalCopies` or fall below zero.
 
2. **`Member`** – Represents a member of the library.
 - **Attributes**:  
   - `memberID` (private, `string`)
   - `name` (public, `string`)
   - `borrowedBooks` (private, `map<string, int>`) — maps ISBN to borrowed count
   - `borrowLimit` (private, `int`) — default: `3`
 	
- **Methods**:  
  Constructors:
  1. A parameterized constructor to initialize `memberID`, `name`, and `borrowLimit`.
  2. A constructor with a default argument for borrowLimit (default value: 3). The other two fields are passed as parameters to the constructor.  
  Utility Methods:  
  1. `bool borrowBook(isbn)`: Should allow the member to borrow a book if they haven’t exceeded their borrow limit. If the constraint is violated then the request is ignored and a message is printed stating `“Invalid request! Borrow limit exceeded”`. Returns true is the book was successfully borrowed. Else returns false.
  2. `bool returnBook(isbn)`: Must allow the member to return a book if they’ve borrowed it. If they haven’t borrowed it then ignore the request and print a message stating `“Invalid request! Book not borrowed”`. If return book was successful then return true. Else return false.
  3. `void printDetails()`: Prints member details, including a list of borrowed books and their quantities. The format should be `“memberID name isbnOfBook numberOfBorrowedCopies”` (the entities are separated by a single space). For each book that is borrowed by the member the same format should be followed on a new line. If the member has not borrowed any book then print nothing.
 
- **Member Constraints**:  
i. A member cannot borrow more than their `borrowLimit`.  
ii. A member can borrow the same book multiple times if additional copies are available.
 
4. **`Library`** – Represents a library
- **Attributes**:  
  - `vector<Book>` books
  - `vector<Member>` members
- **Methods**:  
  Utility Methods:
  1. `bool addBook(Book&)`: Adds a new book to the library (ensures unique isbn). If the unique isbn constraint is violated then the request is ignored and a message is printed stating `“Invalid request! Book with same isbn already exists”`. Return true or false respectively if the book was added or not.
  2. `bool registerMember(Member&)`: Registers a new member (ensures unique memberID). If the unique memberID constraint is violated then the request is ignored and a message is printed stating `“Invalid request! Member with same id already exists”`. Return true or false respectively if the book was added or not.
  3. `bool borrowBook(string memberID, string isbn)`: Allows a member to borrow a book. First check if the book is available or not. Then check if the borrow limit of the member is within limit or not. Check and print the corresponding error statements in this order only. The error statements are the same as mentioned in the method descriptions of the Book and Member classes above (see public test case 2 for an example).
  4. `bool returnBook(string memberID, string isbn)`: Allows a member to return a book. First check if the copies after returning will exceed the total copies or not. Then check if the member ever borrowed that book or not. Check and print the corresponding error statements in this order only. The error statements are the same as mentioned in the method descriptions of the Book and Member classes above (see public test case 3 for an example).
  5. `void printLibraryDetails()`: Prints details of all books and members. First the details of the books should be printed with each one on a newline in the format `“title author copiesAvailable”` (the entities are separated by a single space). Then the details of the members are printed with each one on a newline in the format `“memberID name”` (the entities are separated by a single space).
     
- **Constraints**:  
   Max books: 50  
   Max members: 150  
   Max copies per book: 15  
   Max books borrowed by a member at a time: 15  
 
## Input Format
The system processes a series of command-based inputs to manage the state of the library. Input begins with keywords such as Book, Member, Borrow, Return, PrintBook, PrintMember, and PrintLibrary, followed by the necessary details for each command. Books can be added in three ways: using all parameters, default parameters, or a copy constructor with a new ISBN. Book copies can be updated using the UpdateCopiesCount command. Members can be added either with a specified borrowing limit or with the default limit using keywords like Member or NoBorrowLimit. Borrowing and returning books requires specifying the member ID and ISBN. Information retrieval commands allow printing the status of a specific book, a specific member, or the entire library. The command sequence ends with the keyword Done, indicating the end of input. This structure allows dynamic and modular management of library operations through clear and consistent syntax.

## Output Format
The output is generated based on the execution of the commands provided in the input. When printing book details using the PrintBook command, the output consists of the book’s title and author in a single line. For PrintMember, the system displays the member’s ID and name, followed by the ISBN and number of copies borrowed for each borrowed book, each on a new line. If a member has not borrowed any books, nothing is printed. The PrintLibrary command first outputs all books with their title, author, and available copies, followed by all registered members with their IDs and names. Error messages are printed when constraints are violated, such as attempting to borrow more books than allowed, returning unborrowed books, or exceeding available book copies. These errors are communicated with descriptive messages like “Invalid request! Copy of book not available” or “Invalid request! Borrow limit exceeded”, ensuring clear user feedback for invalid actions.
