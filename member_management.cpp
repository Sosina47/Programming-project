#include <iostream> 
#include "functions.h"
#include <vector> 
using namespace std; 

class borrowing_history {
    public: 
        vector <string> borrowed_date;  
        vector <int> book_id;
};

class member {
    public: 
        int ID; 
        string name; 
        string status; 
        borrowing_history borrowed; 
};


int main () {
    vector <member> members; 

    int l_option; 
    label4: 
    cout<<" to add new member press 1 \n to update an existing member info press 2 \n to remove members from the list press 3 \n to see members information press 4: "; 
    cin>> l_option; 

    if (l_option == 1) {
        addMember(members); 
    } else if (l_option == 2) {
        updateMember(members); 
    } else if (l_option == 3) {
        removeMember(members); 
    } else if (l_option == 4) {
        displayMember(members);
    } else {
        cout<<"Invalid input. Please try again. "<<endl; 
        goto label4;    
    }

    return 0; 
}