#include <iostream>
#include <vector>
#include <windows.h>
#include "functions.h"
using namespace std;

bool start_again () {
    char go_back; 
    cout<<"Do you want to go back to the home menu? (Y/N): ";
    cin>>go_back;
    if (go_back == 'y' || go_back == 'Y'){
        return true; 
    }
    return false; 
}

int main () {
    vector <book> books;
    vector <member> members;

    // sample file for books

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

    // sample file for members

    member temp2; 
    borrowing_history tempp; 

    temp2.ID = 1; 
    temp2.name = "sosi"; 
    temp2.status = "active"; 
    tempp.borrowed_date = "01-01-2025"; 
    tempp.book_id = 1; 
    temp2.borrowed.push_back(tempp); 
    members.push_back(temp2); 

    temp2.ID = 2; 
    temp2.name = "senpair"; 
    temp2.status = "active"; 
    tempp.borrowed_date = "01-02-2025"; 
    tempp.book_id = 2; 
    temp2.borrowed.push_back(tempp); 
    members.push_back(temp2); 

    temp2.ID = 3; 
    temp2.name = "selam"; 
    temp2.status = "active"; 
    tempp.borrowed_date = "05-01-2025"; 
    tempp.book_id = 3; 
    temp2.borrowed.push_back(tempp); 
    members.push_back(temp2);     

    int managment;
    int option; 
    label5:
    cout<<" to manage books press 1 \n to manage members press 2 \n to issuing and returning books press 3: ";
    cin>>managment; 
    
    if (managment == 1) {
        Sleep(1000); 
        system("cls"); 
        cout<<" to update books press 1 \n to add books press 2 \n to delete books press 3: ";
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
        } else {
            cout<<"Invalid input!"<<endl; 
        }
        // display book will be added

        // let the user to go back to the menu
        Sleep(2000);
        system("cls");
        if(start_again()) {
            Sleep(1000);
            system("cls");
            goto label5; 
        } else {
            cout<<"Thank you for using our service!"; 
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

        // let the user to go back to the menu
        Sleep(2000);
        system("cls");
        if(start_again()) {
            goto label5; 
        } else {
            cout<<"Thank you for using our service!"; 
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

        // let the user to go back to the menu
        Sleep(2000);
        system("cls");
        if(start_again()) {
            goto label5; 
        } else {
            cout<<"Thank you for using our service!"; 
        }

    } else {
        cout<<"Invalid input. Please try again!"<<endl; 
        goto label5; 
    }

    return 0; 
}