#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
using namespace std;

struct borrowing_history {
    string borrowed_date; 
    int book_id; 
};

class member {
public: 
    int ID; 
    string name; 
    string status; 
    vector<borrowing_history> borrowed; 
};

class book {
public: 
    int ID;
    string title; 
    string author;
    int publication_year; 
};

// File handling 
void saveBooksToFile(const vector<book>& books, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& b : books) {
        outFile << b.ID << "," << b.title << "," << b.author << "," << b.publication_year << "\n";
    }
    outFile.close();
}

vector<book> loadBooksFromFile(const string& filename) {
    vector<book> books;
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No existing book file found. Starting with empty list." << endl;
        return books;
    }

    string line;
    while (getline(inFile, line)) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);

        if (pos1 != string::npos && pos2 != string::npos && pos3 != string::npos) {
            book b;
            b.ID = stoi(line.substr(0, pos1));
            b.title = line.substr(pos1 + 1, pos2 - pos1 - 1);
            b.author = line.substr(pos2 + 1, pos3 - pos2 - 1);
            b.publication_year = stoi(line.substr(pos3 + 1));
            books.push_back(b);
        }
    }
    inFile.close();
    return books;
}

void saveMembersToFile(const vector<member>& members, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing: " << filename << endl;
        return;
    }

    for (const auto& m : members) {
        outFile << m.ID << "," << m.name << "," << m.status;
        for (const auto& bh : m.borrowed) {
            outFile << "," << bh.book_id << "," << bh.borrowed_date;
        }
        outFile << "\n";
    }
    outFile.close();
}

vector<member> loadMembersFromFile(const string& filename) {
    vector<member> members;
    ifstream inFile(filename);
    if (!inFile) {
        cout << "No existing member file found. Starting with empty list." << endl;
        return members;
    }

    string line;
    while (getline(inFile, line)) {
        vector<string> tokens;
        size_t start = 0;
        size_t end = line.find(',');
        
        while (end != string::npos) {
            tokens.push_back(line.substr(start, end - start));
            start = end + 1;
            end = line.find(',', start);
        }
        tokens.push_back(line.substr(start));

        if (tokens.size() >= 3) {
            member m;
            m.ID = stoi(tokens[0]);
            m.name = tokens[1];
            m.status = tokens[2];
            
            for (size_t i = 3; i + 1 < tokens.size(); i += 2) {
                borrowing_history bh;
                bh.book_id = stoi(tokens[i]);
                bh.borrowed_date = tokens[i + 1];
                m.borrowed.push_back(bh);
            }
            members.push_back(m);
        }
    }
    inFile.close();
    return members;
}

void addBook (vector <book> &books) {
    int size; 
    cout<<"how many books do you want to add: "; 
    cin>>size; 
    for (int i=0; i<size; i++) {
        book temp; 
        while (true) {
            bool found = false; 
            cout<<"enter book "<<i+1<<" id: ";
            cin>>temp.ID;

            for (int i=0; i<books.size(); i++) {
                if(books[i].ID == temp.ID) {
                    found = true; 
                    break; 
                }
            }
            if(!found) {
                break; 
            }
            cout<<"The ID is already taken. Please try again. "<<endl; 
        }
         
        cout<<"enter book title: ";
        cin.ignore(1000, '\n'); 
        getline(cin, temp.title); 
        cout<<"enter book author: ";
        getline(cin, temp.author);
        cout<<"enter book publication year: ";
        cin>>temp.publication_year;

        books.push_back(temp); 
    }
    cout<<"Book is added successfully!"<<endl; 
    
}

void updateBook (vector <book>& books) {
    int book_id; 
    int index; // holds the position for the book to be updated
    bool id_found = false; // to check if the book id is valid 

    while (!id_found) {
        cout<<"enter the id of the book you want to update: "; 
        cin>>book_id; 
    
        for(int i=0; i<books.size(); i++) {
            if (books[i].ID == book_id) {
                id_found = true; 
                index = i;
            }
        }
        if (!id_found) {
            cout<<"you have entered invalid book id. please try again."<<endl;  
        }
    }

    int option; 
    label: 
    cout<<" to update id press 1 \n to update title press 2 \n to update author press 3 \n to update publication year press 4: "; 
    cin>>option; 

    if (option == 1) {
        int new_id;
        while (true) {
            bool found = false;  
            cout<<"enter the new id: ";
            cin>>new_id; 

            for (int i=0; i<books.size(); i++) {
                if(books[i].ID == new_id) {
                    found = true; 
                    break; 
                }
            }
            if (!found) {
                break; 
            }
            cout<<"The ID is already taken. Please try again"<<endl; 
        }
        
        books[index].ID = new_id; 

    } else if (option == 2) {
        cout<<"enter the new title: ";
        cin.ignore(1000, '\n'); 
        getline(cin, books[index].title);  
        
    } else if (option == 3) {
        cout<<"enter the new author: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, books[index].author);  

    } else if (option == 4) {
        cout<<"enter the new publication year: "; 
        cin>>books[index].publication_year; 
    } else {
        cout<<"invalid input! please try again. "<<endl; 
        goto label; 
    }
}

void removeBook (vector <book>& books) {
    int ID; 
    char confirmation; 
    bool id_found = false; 
    int index; 

    while(!id_found) {
        cout<<"enter the book ID you want to delete: "; 
        cin>> ID;
        for (int i=0; i<books.size(); i++) {
            if(books[i].ID == ID) {
                id_found = true; 
                index = i; 
            }
        }
        if(!id_found) {
            cout<<"Invalid ID. Please try again."<<endl; 
        }
    }

    cout<<"Are you sure you want to delete the book with ID "<<ID<<" ? "<<endl; 
    cout<<"Press y for yes and any other key for no: "; 
    cin>>confirmation; 

    if(confirmation == 'Y' || confirmation == 'y') {
        books.erase(books.begin() + index); 
        cout<<"You've deleted the book successfully!"; 
    } else {
        cout<<"No book is deleted. "<<endl; 
    }
}

// search book

void searchBooks(const vector<book>& books) {
    int choice;
    cout << "Search by:\n1. Title\n2. ID\nEnter choice: ";
    cin >> choice;

    if (choice == 1) {
        // Search by title
        cin.ignore(1000, '\n');
        string searchTerm;
        cout << "Enter book title (or part of it): ";
        getline(cin, searchTerm);

        bool found = false;
        for (const auto& b : books) {
            if (b.title.find(searchTerm) != string::npos) {  // Case-sensitive partial match
                cout << "ID: " << b.ID << "\nTitle: " << b.title 
                     << "\nAuthor: " << b.author << "\nYear: " << b.publication_year 
                     << "\n-----------------\n";
                found = true;
            }
        }
        if (!found) cout << "No books found with that title.\n";

    } else if (choice == 2) {
        // Search by ID
        int id;
        cout << "Enter book ID: ";
        cin >> id;

        bool found = false;
        for (const auto& b : books) {
            if (b.ID == id) {
                cout << "ID: " << b.ID << "\nTitle: " << b.title 
                     << "\nAuthor: " << b.author << "\nYear: " << b.publication_year 
                     << "\n-----------------\n";
                found = true;
                break;
            }
        }
        if (!found) cout << "Book ID not found.\n";

    } else {
        cout << "Invalid choice.\n";
    }
}


// member managment

template<typename T>
bool idExists (vector<T>books, int id, int& index) {
    // checks if the id is valid
    bool id_found = false; 
    for (int i=0; i<books.size(); i++) {
        if (books[i].ID == id) {
            index = i; 
            id_found = true; 
            break;  
        }
    }
    return id_found; 

}

// add new members
void addMember (vector<member>& members) {
    int size; 
    bool found;
    cout<<"how many members do you want to add: ";
    cin>>size; 

    for (int i=0; i<size; i++) {
        member temp;

        do {
            found = false; 
            cout<<"enter member "<<i+1<<" ID: "; 
            cin>>temp.ID; 
            for(int i=0; i<members.size(); i++) {
                if (members[i].ID == temp.ID) {
                    cout<<"ID already exists. Please insert another ID."<<endl; 
                    found = true; 
                    break; 
                }
            }
        } while(found); 

        cout<<"member "<<i+1<<" name: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, temp.name); 

        do {
            cout<<"enter member "<<i+1<<" status(active/inactive): "; 
            cin>>temp.status; 
        } while(temp.status != "active" && temp.status != "inactive"); 

        borrowing_history tempp; 

        cout<<"enter the date a member "<<i+1<<" borrowed a book: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, tempp.borrowed_date); 

        cout<<"enter the ID of a book the member "<<i+1<<" borrowed: "; 
        cin>>tempp.book_id; 

        temp.borrowed.push_back(tempp); 

        members.push_back(temp); 
        cout<<"Member is added successfully. "<<endl; 
    }
}


// updates members information 
void updateMember(vector<member>& members) {
    int mbr_id; 
    int index; 

    while (true) {
        cout<<"Enter the members id you want to make changes: ";
        cin>>mbr_id;

        if (idExists<member>(members, mbr_id, index)) {
            break; 
        } else {
            cout<<"Invalid Id. Please try again."<<endl; 
        }
    }

    int option; 
    label2:
    cout<<" to update members ID press 1 \n to update members name press 2 \n to update members status press 3 \n to update the date a member borrowed a book press 4: ";
    cin>>option; 

    if (option == 1) {
        int new_id, new_index;  
        // checks if the id is assigned to another member
        while (true) {
            cout<<"Enter the new ID: "; 
            cin>>new_id;
            if (!idExists<member>(members, new_id, new_index)) {
                members[index].ID = new_id; 
                break; 
            } else {
                cout<<"The ID is already taken. Please choose another ID."<<endl;
            }
        }
        
        
    } else if (option == 2) {
        cout<<"Enter the new name: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, members[index].name); 

    } else if (option == 3) {
        cout<<"Enter new status (active/inactive): ";
        cin>>members[index].status; 

    } else if (option == 4) {
        int ID, bk_index;
        while(true) { 
            bool br_bK_found = false; 
            cout<<"enter borrowed book ID to update the date: "; 
            cin>>ID; 
            for (int i=0; i < members[index].borrowed.size(); i++) {
                if (members[index].borrowed[i].book_id == ID) {
                    bk_index = i; 
                    br_bK_found = true; 
                    break; 
                }
            }
            if (br_bK_found) {
                break; 
            } 
            cout<<"invalid borrowed book ID. please try again."<<endl; 
        }

        cout<<"Enter new borrowed book date: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, members[index].borrowed[bk_index].borrowed_date);  

    } else {
        cout<<"Invalid input. Please try again."<<endl;
        goto label2;
    }
}

// remove member
void removeMember (vector<member>& members) {
    int size; 
    while (true) {
        cout<<"How many members do you want to remove: "; 
        cin>>size; 

        if (size <= members.size()) {
            break; 
        } else {
            cout<<"please enter valid number of members"<<endl; 
        }
    }

    for (int i=0; i<size; i++) {
        int ID, index; 

        while (true) {
            cout<<"enter member "<<i+1<<" ID you want to remove: ";
            cin>>ID; 

            if (idExists<member>(members, ID, index)) {
                break;
            } else {
                cout<<"Please enter a valid member ID."<<endl; 
            }
        }

        char confirmation;
        cout<<"Are you sure you want to delete the member with id "<<ID<<endl;
        cout<<"press y to delete and any other key to terminate: "; 
        cin>>confirmation; 

        if (confirmation == 'y' || confirmation == 'Y') {
            members.erase(members.begin() + index); // deletes the member at index index in the vector
            cout<<"Member is deleted successfully."<<endl;
        } else {
            cout<<"No member is deleted."<<endl; 
        }        
    }
}


// displays members information 
void displayMember (vector<member>members) {
    int ID, index;

    while (true) {
        cout<<"Enter members ID you want to see history of: "; 
        cin>>ID; 

        if (idExists<member>(members, ID, index)) {
            break; 
        } else {
            cout<<"Invalid ID! Please try again."<<endl;
        }
    }

    cout<<"ID       NAME        STATUS      BORROWED BOOK"<<endl; 
    cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
    cout<<members[index].ID<<"      "<<members[index].name<<"       "<<members[index].status<<"     "<<members[index].borrowed.size()<<endl;
    cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
}

// book return and borrow functions

void borrow (vector <member>& members, int bk_id, int m_index) {
    borrowing_history temp; 
    temp.book_id = bk_id; 
    
    cout<<"enter the date today: ";
    cin.ignore(1000, '\n'); // cleans the buffer 
    getline(cin, temp.borrowed_date); 
    members[m_index].borrowed.push_back(temp);

    cout<<"you borrowed the book with id "<<bk_id<<" successfully."<<endl; 
}

void bk_return (vector <member>& members, int m_index, int bk_index) {
       members[m_index].borrowed.erase(members[m_index].borrowed.begin() + bk_index); // removes the book from borrowed history
       
       cout<<"You have returned the book successfully."<<endl; 
} 


bool start_again () {
    char go_back; 
    cout<<"Do you want to go back to the home menu? (Y/N): ";
    cin>>go_back;
    if (go_back == 'y' || go_back == 'Y'){
        return true; 
    }
    return false; 
}


// main function
int main() {
    const string BOOKS_FILE = "library_books.txt";
    const string MEMBERS_FILE = "library_members.txt";
    
    // Load data from files
    vector<book> books = loadBooksFromFile(BOOKS_FILE);
    vector<member> members = loadMembersFromFile(MEMBERS_FILE);

    // If no data loaded, create sample data
    if (books.empty()) {
        cout<<"file is empty."; 
    }

    if (members.empty()) {
        cout<<"file is empty!"; 
    }

    int managment;
    int option; 
    label5:
    cout<<" to manage books press 1 \n to manage members press 2 \n to issuing and returning books press 3 \n to exit press 4: ";
    cin>>managment; 
    
    if (managment == 1) {

        Sleep(1000); 
        system("cls"); 
        cout<<" to update books press 1 \n to add books press 2 \n to delete books press 3 \n to search books press 4: ";
        cin>>option; 

        if (option == 1) {
            Sleep(1000); 
            system("cls"); 
            updateBook(books); 
        } else if (option == 2) {
            Sleep(1000); 
            system("cls"); 
            addBook(books); 
        } else if(option == 3) {
            Sleep(1000); 
            system("cls"); 
            removeBook(books); 
        } else if (option == 4) {  
            Sleep(1000);
            system("cls");
            searchBooks(books);  
        } else {
            cout<<"Invalid input!"<<endl; 
        }

        // save to file
        saveBooksToFile(books, BOOKS_FILE);

        // go back to the menu
        Sleep(2000);
        system("cls");
        if(start_again()) {
            Sleep(1000);
            system("cls");
            goto label5; 
        } else {
            cout<<"Thank you for using our service!"; 
            return 0; 
        }
        
    } else if (managment == 2) {
        // member managment  

        int l_option; 
        label4: 
        Sleep(1000);
        system("cls");
        cout<<" to add new member press 1 \n to update an existing member info press 2 \n to remove members from the list press 3 \n to see members information press 4: "; 
        cin>> l_option; 

        if (l_option == 1) {
            Sleep(1000);
            system("cls"); 
            addMember(members); 
        } else if (l_option == 2) {
            Sleep(1000);
            system("cls"); 
            updateMember(members); 
        } else if (l_option == 3) {
            Sleep(1000);
            system("cls");
            removeMember(members); 
        } else if (l_option == 4) {
            Sleep(1000);
            system("cls");
            displayMember(members);
        } else {
            cout<<"Invalid input. Please try again. "<<endl; 
            goto label4;    
        }

        // save to file
        saveMembersToFile(members, MEMBERS_FILE);

        // let the user to go back to the menu
        Sleep(2000);
        system("cls");
        if(start_again()) {
            goto label5; 
        } else {
            cout<<"Thank you for using our service!";
            return 0;  
        }

        
        
    } else if (managment == 3) {
        // book borrowing and returning

        int br_option, m_index, bk_index, bk_id; 

        label3: 
        Sleep(1000);
        system("cls");
        cout<<" to borrow book press 1 \n to return book press 2: "; 
        cin>>br_option; 

        string borrow_return;
        if (br_option == 1) {
            borrow_return = "borrow";
        } else {
            borrow_return = "return"; 
        }

        while (true) { 
            int mbr_id;
            Sleep(2000);
            system("cls");
            cout<<"enter your id: "; 
            cin>>mbr_id; 

            if (idExists<member>(members, mbr_id, m_index)) {
                break;
            } else {
                cout<<"Invalid ID. Please enter a valid ID."<<endl; 
            }
        } 

        while (true) {
            Sleep(1000);
            system("cls");
            cout<<"Enter the book ID you want to "<<borrow_return<<": "; 
            cin>>bk_id; 

            if (idExists<book> (books, bk_id, bk_index)) { // checks if the book id is valid and returns true
                if (borrow_return == "return") {
                    // checks if the member have borrowed the book 
                    bool is_id_found = false;

                    for (int i=0; i<members[m_index].borrowed.size(); i++) {
                        if (members[m_index].borrowed[i].book_id == bk_id) {
                            bk_index = i; // holds the index of the book in the members borrowed history to delete it later 
                            is_id_found = true; 
                            break;
                        }
                    }

                    if (!is_id_found) {
                        cout<<"You have not borrowed a book with ID "<<bk_id<<" please try again."<<endl; 
                    } else {
                        break; 
                    }
                } else {
                    break; 
                }
            } else {
                cout<<"Invalid book ID. please try again"<<endl; 
            }
        }

        if (br_option == 1) {
            borrow(members, bk_id, m_index); 

        } else if (br_option == 2) {
            bk_return(members, m_index, bk_index);   
        }
        // save members to file
        saveMembersToFile(members, MEMBERS_FILE);

        // let the user to go back to the menu
        Sleep(2000);
        system("cls");
        if(start_again()) {
            goto label5; 
        } else {
            cout<<"Thank you for using our service!"; 
            return 0; 
        }

        
        
    } else if (managment == 4) {
        // Save data before exiting
        saveBooksToFile(books, BOOKS_FILE);
        saveMembersToFile(members, MEMBERS_FILE);
        cout << "Data saved. Goodbye!" << endl;
        return 0;
    } else {
        cout<<"Invalid input. Please try again!"<<endl; 
        goto label5; 
    }

    // Let the user to go back to the menu
    Sleep(2000);
    system("cls");
    if(start_again()) {
        Sleep(1000);
        system("cls");
        goto label5; 
    } else {
        // Save data before exiting
        saveBooksToFile(books, BOOKS_FILE);
        saveMembersToFile(members, MEMBERS_FILE);
        cout<<"Thank you for using our service!"; 
    }

    return 0; 
}