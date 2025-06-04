#include <iostream>
#include <vector>
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
        vector<borrowing_history>borrowed; 
};

class book {
    public: 
        int ID;
        string title; 
        string author;
        int publication_year; 
};

// functions for book managment

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


// functions for member managment

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
            cout<<"enter member "<<i+1<<" status(active/passive): "; 
            cin>>temp.status; 
        } while(temp.status != "active" && temp.status != "passive"); 

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
        cout<<"Enter new status (active/passive): ";
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