#include <iostream>
using namespace std; 

class books {
    public: 
        int ID;
        string title; 
        string author;
        int publication_year; 
};

void getBook (books book[], int size) {
    for (int i=0; i<size; i++) {
        cout<<"enter book id: ";
        cin>>book[i].ID;
        cout<<"enter book title: ";
        cin.ignore(1000, '\n'); 
        getline(cin, book[i].title); 
        cout<<"enter book author: ";
        getline(cin, book[i].author);
        cout<<"enter book publication year: ";
        cin>>book[i].publication_year;
    }
}

void updateBook (books book[], int size) {
    int book_id; 
    int index; // holds the position for the book to be updated
    bool id_found = false; // to check if the book id is valid 

    while (!id_found) {
        cout<<"enter the id of the book you want to update: "; 
        cin>>book_id; 
    
        for(int i=0; i<size; i++) {
            if (book[i].ID == book_id) {
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
        cout<<"enter the new id: ";
        cin>>book[index].ID; 

    } else if (option == 2) {
        cout<<"enter the new title: ";
        cin.ignore(1000, '\n'); 
        getline(cin, book[index].title);  
        
    } else if (option == 3) {
        cout<<"enter the new author: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, book[index].author);  

    } else if (option == 4) {
        cout<<"enter the new publication year: "; 
        cin>>book[index].publication_year; 
    } else {
        cout<<"invalid input! please try again. "<<endl; 
        goto label; 
    }
}

int main () {
    int size = 5;
    books book[size];
    getBook(book, size); 

    // updating the books
    int option; 
    cout<<"if you want to update the books press 1, if you don't press any other key: ";
    cin>>option; 

    if (option == 1) {
        updateBook(book, size); 
    }

    return 0; 
}