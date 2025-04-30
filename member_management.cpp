#include <iostream> 
using namespace std; 

class borrowing_history {
    public: 
        static const int max = 15; // this belongs to the class itself not to individual objects
        int quantity; 
        int book_id[max];
};

class members {
    public: 
        int ID; 
        string name; 
        string status; 
        borrowing_history borrowed; 
};

void getMember (members member[], int size) {
    for (int i=0; i<size; i++) {
        cout<<"Enter id of member 1: "; 
        cin>>member[i].ID; 
        cout<<"Enter name of member: "; 
        cin.ignore(1000, '\n'); 
        getline(cin, member[i].name); 
        cout<<"Enter status of member: "; 
        cin>>member[i].status; 
        cout<<"Enter the number of books a member borrowed: "; 
        cin>>member[i].borrowed.quantity;

        int n = member[i].borrowed.quantity;

        for (int j=0; j<n; j++) {
            cout<<"Enter the id of books the member borrowed: ";
            cin>>member[i].borrowed.book_id[j];
        }
    }
}

// updates members information 
void updateMember(members member[], int index) {
    int option; 
        label2:
        cout<<" to update members ID press 1 \n to update members name press 2 \n to update members status press 3 \n to update the number of books a member borrowed press 4: ";
        cin>>option; 

        if (option == 1) {
            cout<<"Enter the new ID: "; 
            cin>>member[index].ID; 
            
        } else if (option == 2) {
            cout<<"Enter the new name: "; 
            cin.ignore(1000, '\n'); 
            getline(cin, member[index].name); 

        } else if (option == 3) {
            cout<<"Enter new status: ";
            cin>>member[index].status; 

        } else if (option == 4) {
            cout<<"Enter new borrowed books quantity: "; 
            cin>>member[index].borrowed.quantity; 

        } else {
            cout<<"Invalid input. Please try again."<<endl;
            goto label2;
        }
}

// displays members information 
void displayMember (members member[], int index) {
    cout<<"ID       NAME        STATUS      BORROWED BOOK"<<endl; 
    cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
    cout<<member[index].ID<<"      "<<member[index].name<<"       "<<member[index].status<<"     "<<member[index].borrowed.quantity<<endl;
    cout<<"_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ "<<endl;
}

int main () {
    int size = 3; 
    members member[size]; 

    getMember(member, size); 

    // update, see history or remove members 

    int option_members; 
    label1:
    cout<<" to update members info. press 1 \n to see their information press 2 \n to remove members from the list press 3: "; 
    cin>>option_members; 

    int mbr_id; 
    bool id_found = false; 
    int index; 

    while (!id_found) {
        cout<<"Enter the members id you want to make changes: ";
        cin>>mbr_id;

        for (int i=0; i<size; i++) {
            if (member[i].ID == mbr_id) {
                index = i; 
                id_found = true; 
            }
        }
        if (!id_found) {
            cout<<"Invalid Id. Please try again."<<endl; 
        }
    }

    if (option_members == 1) {
        updateMember(member, index);

    } else if (option_members == 2) {
        displayMember(member, index); 

    } else if (option_members == 3) {

    } else {
        cout<<"Invalid input. Please try again ";
        goto label1; 
    }

    

    return 0; 
}