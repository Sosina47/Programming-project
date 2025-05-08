#include <iostream>
#include <vector>
using namespace std; 

void addMember (vector <member>& members) {
    int size; 
    bool found;
    cout<<"how many members do you want to add: ";
    cin>>size; 

    for (int i=0; i<size; i++) {
        member temp;

        do {
            found = true; 
            cout<<"enter member "<<i+1<<" ID: "; 
            cin>>temp.ID; 
            for(int i=0; i<members.size(); i++) {
                if (members[i].ID == temp.ID) {
                    cout<<"ID already exists. Please insert another ID."<<endl; 
                    found = false; 
                    break; 
                }
            }
        } while(!found); 

        cout<<"member "<<i+1<<" name: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, temp.name); 

        do {
            cout<<"enter member "<<i+1<<" status(active/passive): "; 
            cin>>temp.status; 
        } while(temp.status != "active" && temp.status != "passive"); 

        cout<<"enter the date a member "<<i+1<<" borrowed a book: "; 
        cin.ignore(1000, '\n'); 
        string date; 
        getline(cin, date); 
        temp.borrowed.borrowed_date.push_back(date); 

        cout<<"enter the ID of a book the member "<<i+1<<" borrowed: "; 
        int ID; 
        cin>>ID; 
        temp.borrowed.book_id.push_back(ID); 

        members.push_back(temp); 
        cout<<"Member is added successfully. "<<endl; 
    }
}


// updates members information 
void updateMember(vector <member>& members) {
    int mbr_id; 
    bool id_found = false; 
    int index; 

    while (!id_found) {
        cout<<"Enter the members id you want to make changes: ";
        cin>>mbr_id; 

        for (int i=0; i<members.size(); i++) {
            if (members[i].ID == mbr_id) {
                index = i; 
                id_found = true; 
            }
        }
        if (!id_found) {
            cout<<"Invalid Id. Please try again."<<endl; 
        }
    }

    int option; 
    label2:
    cout<<" to update members ID press 1 \n to update members name press 2 \n to update members status press 3 \n to update the date a member borrowed a book press 4: ";
    cin>>option; 

    if (option == 1) {
        cout<<"Enter the new ID: "; 
        cin>>members[index].ID; 
        
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
            cout<<"enter borrowed book ID: "; 
            cin>>ID; 
            for (int i=0; i<members.size(); i++) {
                if (members[i].ID == ID) {
                    bk_index = i; 
                    break;
                }
            }
            cout<<"invalid borrowed book ID. please try again."<<endl; 
        }

        cout<<"Enter new borrowed book date: "; 
        cin>>members[index].borrowed.borrowed_date[bk_index]; 

    } else {
        cout<<"Invalid input. Please try again."<<endl;
        goto label2;
    }
}


void removeMember (vector <member>& members) {
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
        bool id_found = false; 

        while(!id_found) {
            cout<<"enter member "<<i+1<<" ID you want to remove: ";
            cin>>ID;

            for (int j=0; j<members.size(); j++) {
                if (members[j].ID == ID) {
                    index = j; 
                    id_found = true; 
                    break;
                }
            }
            if (!id_found) {
                cout<<"Please enter a valid members input."<<endl; 
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
void displayMember (vector <member> members) {
    int ID, index;
    bool id_found = false; 

    while (!id_found) {
        cout<<"Enter members ID you want to see history of: "; 
        cin>>index; 
        for(int i=0; i<members.size(); i++) {
            if (members[i].ID == ID) {
                index = i; 
                id_found = true;
                break; 
            }
            if (i == members.size() - 1) {
                cout<<"Invalid ID! Please try again."<<endl; 
            }
        }
    }

    cout<<"ID       NAME        STATUS      BORROWED BOOK"<<endl; 
    cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
    cout<<members[index].ID<<"      "<<members[index].name<<"       "<<members[index].status<<"     "<<members[index].borrowed.book_id.size()<<endl;
    cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
}