#include <iostream>
#include <vector>
using namespace std; 

class book {
    public: 
        int ID;
        string title; 
        string author;
        int publication_year; 
};

void addBook (vector <book> &books) {
    int size; 
    cout<<"how many books do you want to add: "; 
    cin>>size; 
    for (int i=0; i<size; i++) {
        book temp; 
        while (true) {
            bool found = false; 
            cout<<"enter book id: ";
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



int main () {
    vector <book> books;

    book temp;
    temp.ID = 1; 
    temp.title = "english"; 
    temp.author = "sosina"; 
    temp.publication_year = 2004; 
    books.push_back(temp); 

    temp.ID = 2; 
    temp.title = "math"; 
    temp.author = "sara"; 
    temp.publication_year = 2003;
    books.push_back(temp); 

    temp.ID = 3; 
    temp.title = "biology"; 
    temp.author = "saron"; 
    temp.publication_year = 2005;
    books.push_back(temp); 
    

    int option; 

    cout<<" to update books press 1 \n to add books press 2 \n to delete books press 3: ";
    cin>>option; 

    if (option == 1) {
        updateBook(books); 
    } else if (option == 2) {
        addBook(books); 
    } else if(option == 3) {
        removeBook(books); 
    } else {
        cout<<"Invalid input!"<<endl; 
    }

    // display book will be added

    return 0; 
}
