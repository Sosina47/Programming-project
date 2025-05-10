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
        vector <borrowing_history> borrowed; 
};

class book {
    public: 
        int ID;
        string title; 
        string author;
        int publication_year; 
};

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
       
       cout<<"The book is added to your history successfully."<<endl; 
}


template <typename T>
bool bookMatchingId (vector <T> books, int id, int& index) {
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

int main() {
    vector <member> members;
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
    

    member temp1; 
    borrowing_history tempp1; 

    temp1.ID = 1; 
    temp1.name = "sosi"; 
    temp1.status = "active"; 
    tempp1.borrowed_date = "01-01-2025"; 
    tempp1.book_id = 1; 
    temp1.borrowed.push_back(tempp1); 
    members.push_back(temp1); 

    temp1.ID = 2; 
    temp1.name = "senpair"; 
    temp1.status = "active"; 
    tempp1.borrowed_date = "01-02-2025"; 
    tempp1.book_id = 2; 
    temp1.borrowed.push_back(tempp1); 
    members.push_back(temp1); 

    temp1.ID = 3; 
    temp1.name = "selam"; 
    temp1.status = "active"; 
    tempp1.borrowed_date = "05-01-2025"; 
    tempp1.book_id = 3; 
    temp1.borrowed.push_back(tempp1); 
    members.push_back(temp1); 


    int br_option, m_index, bk_index, bk_id; 
    bool is_id_found = false; 

    label3: 
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
        cout<<"enter your id: "; 
        cin>>mbr_id; 

        if (bookMatchingId <member>(members, mbr_id, m_index)) {
            break;
        } else {
            cout<<"Invalid ID. Please enter a valid ID."<<endl; 
        }

        // for (int i=0; i<members.size(); i++) {
        //     if (members[i].ID == mbr_id) {
        //         m_index = i; 
        //         is_id_found = true; 
        //     }
        // }
    } 

    while (true) {
        cout<<"Enter the book ID you want to "<<borrow_return<<": "; 
        cin>>bk_id; 

        if (bookMatchingId <book> (books, bk_id, bk_index)) { // checks if the book id is valid and returns true
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
    return 0;
}

