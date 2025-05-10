#include <iostream> 
#include "functions.h"
#include <vector> 
using namespace std; 


int main () {
    vector <member> members; 

    member temp; 
    borrowing_history tempp; 

    temp.ID = 1; 
    temp.name = "sosi"; 
    temp.status = "active"; 
    tempp.borrowed_date = "01-01-2025"; 
    tempp.book_id = 1; 
    temp.borrowed.push_back(tempp); 
    members.push_back(temp); 

    temp.ID = 2; 
    temp.name = "senpair"; 
    temp.status = "active"; 
    tempp.borrowed_date = "01-02-2025"; 
    tempp.book_id = 2; 
    temp.borrowed.push_back(tempp); 
    members.push_back(temp); 

    temp.ID = 3; 
    temp.name = "selam"; 
    temp.status = "active"; 
    tempp.borrowed_date = "05-01-2025"; 
    tempp.book_id = 3; 
    temp.borrowed.push_back(tempp); 
    members.push_back(temp); 
    

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
