#include <iostream>
using namespace std;

// Structure of Node
class Node{
public:
    string Name;//insertion name
    Node* next;//outer boundary
    Node* subFiles;//location of files in folder
    bool file;//check weather inserted Node is representing file or folder
    //constructor
    Node(string name,string type) {
        this->Name=name;
        this->next=NULL;
        this->subFiles=NULL;
        if(type=="file" || type=="File"){
            this->file=true;
        }
        else{
            this->file=false;
        }
    }
};

//Searching Folders
bool findingFolders(Node* head){
    string folderName;
    cout<<"Enter folderName to find:"<<endl;        
    cin>>folderName;
        while(head){
        if(head->Name!=folderName){
            head=head->next;
        }
        else return true;
    }
    return false;
}
//searching Files
bool findingFiles(Node* head){
    string fileName;
    Node* dummy=NULL;
    cout<<"Enter file name to find"<<endl;
    cin>>fileName;
    while(head){
        dummy=head->subFiles;
        if(head->subFiles){
            while (dummy) {
                if (dummy->Name != fileName) {
                    dummy = dummy->next;
                }
                else return true;
            }
        }
        else{
            if(head->Name==fileName && head->file){
                return true;
            }
        }
        head=head->next;
    }
    return false;
}

// Inssertion
Node* insertion(Node* head,string name, string type, string folderName) {
    
    Node *new_Node = new Node(name, type);    
    // if(new_Node->file){
    //     if(findingFiles(head)){
    //         cout<<"File already exist: "<<endl;
    //         return head;
    //     }
    // }
    // else{
    //     if(findingFolders(head)){
    //         cout<<"Folder already exist: "<<endl;
    //         return head;
    //     }
    // }
    // direct file insertion
    if (new_Node->file==true) {
        if(folderName == "NULL"){
            if (!head) {
                head = new_Node;
            } 
            else {
                new_Node->next = head;
                head = new_Node;
            }
        }
        
        // insertion of file inside particular folder
        else {
            Node *temp = head;
            Node *dummy=NULL;
            while (temp) {
                if (temp->Name == folderName) {
                    dummy = temp;
                    break;
                }
                temp = temp->next;
            }
            if(dummy==NULL){
                cout<<"OOPS! "<<folderName<<" does not exist in the Directory: "<<endl;
                return head;
            }
            if (!dummy->subFiles) {
                dummy->subFiles = new_Node;
                // return dummy->subFiles;
            }   
            else {
                new_Node->next = dummy->subFiles;
                dummy->subFiles = new_Node;
                // return dummy->subFiles;
            }
        }
        system("cls");
        cout<<endl<<"File Inserted Successfully!";
    }
    // folder insertion
    else{
        if(!head){
            head=new_Node;
        }
        else{
            new_Node->next=head;
            head=new_Node;
        }
        system("cls");
        cout<<endl<<"Folder inserted successfully!";
    }
    return head;  
}


//display Total Files
void Display_Files(Node* head){
    while(head){
        Node* dummy=head->subFiles;
        cout<<head->Name<<endl;
        if(head->subFiles){
            while(dummy){
                cout<<"\t"<<dummy->Name<<endl;
                dummy=dummy->next;
            }
        }
        head=head->next;
    }
}

//Delete Folder
Node* deleteFolder(Node* head,string folderName){
    if(head->Name==folderName){
        head=head->next;
    }
    else{
        Node* prev=head;
        Node* temp=head->next;
        while(temp){
            if(temp->Name!=folderName){
                temp=temp->next;
                prev=prev->next;
            }
            else{
                break;
            }
        }
        prev->next=temp->next;
    }
    cout<<"Folder deleted successfully: "<<endl;
    return head;
}
//Delete files
Node* deleteFiles(Node* head,string fileName){
    if(head->file && head->Name==fileName){
        head=head->next;
        cout<<"File deleted successfully: "<<endl;
        return head;
    }
    Node* temp=head;
    while(temp){
        Node *prev,*dummy;
        if(!temp->file){
            if(head->subFiles->Name==fileName){
                head->subFiles=head->subFiles->next;
                cout<<"File deleted successfully: "<<endl;
                return head;
            }
            prev=head->subFiles;
            dummy=head->subFiles->next;
            while(dummy){
                if(dummy->Name==fileName){
                    prev->next=dummy->next;
                    cout<<"File deleted successfully: "<<endl;
                    return head;
                }
                prev=prev->next;
                dummy=dummy->next;
            }
        }
        else{
            prev=temp;
            dummy=temp->next;
            while(dummy){
                if(dummy->Name==fileName){
                    prev->next=dummy->next;
                    cout<<"File deleted successfully: "<<endl;
                    return head;
                }
                prev=prev->next;
                dummy=dummy->next;
            }
        }
    }
}
// Main function
int main(){
    Node * head=NULL;
    string fName;
    int i,options;
    char ans;
    
    do{
    cout<<endl<<" Press '1' to insert..";
    cout<<endl<<" Press '2' to search file or folder..";
    cout<<endl<<" Press '3' to Display..";
    cout<<endl<<" Press '4' to Delete..";
    cout<<endl<<"Enter your choice here :) ";
    cin>>options;
    switch (options){
    case 1:
    do {
        system("cls");
        cout<<endl<<"Great! You have chosen INSERTION Operation. "<<endl;
        cout <<endl<< "Press 1 to insert Folder." << endl;
        cout << "Press 2 to insert File." << endl;
        cout<<"Enter your choice :) ";
        cin >> i;
        switch (i) {
            case 1:
                cout << endl << "Enter the name of the folder to be inserted: ";
                cin >> fName;
                head = insertion(head, fName, "folder", "NULL");
                break;
            case 2:
                char ch;
                cout << endl << "Entre the name of the file to be inserted: ";
                cin >> fName;
                cout << endl << "Press a to insert a file directly.";
                cout << endl << "Press b to insert file inside any existing folder.";
                cout<<endl<<"Enter your choice :) ";
                cin >> ch;
                switch (ch) {
                    case 'a':
                        head = insertion(head, fName, "file", "NULL");
                        break;
                    case 'b':
                        string folderName;
                        cout << endl << "Enter the folder name in which you want to insert "<<"'"<<fName<<"': ";
                        cin >> folderName;
                        head = insertion(head, fName, "file", folderName);
                        break;
                }
                break;
             default: 
                cout << endl << "Invalid Input!";
        }
        cout<<endl<<"Press 'Y' if you want to insert More: ";
        cin>>ans;
    }while(ans == 'y' || ans == 'Y');
    break;

    case 2:
    char ch;
        system("cls");
        cout<<endl<<"Great! You have chosen SEARCHING Operation. "<<endl;
        cout<<endl<<"Press a to search any File: ";
        cout<<endl<<"Press b to search any Foler: ";
        cout<<endl<<"Enter your choice: ";
        cin>>ch;
        switch(ch){
            case 'a':           
                if(findingFiles(head)){
                    cout<<"File exist: "<<endl;
                }
                else {
                    cout << "File doesn't exist: " << endl;
                }
                break;

            case 'b':
                if(findingFolders(head)){
                    cout<<"folder exist: "<<endl;
                }
                else{
                    cout<<"folder doesn't exist: "<<endl;
                }
                break;
        }
        break;

    case 3:
        system("cls");
        cout<<endl<<"Great! You have chosen DISPLAY Operation. "<<endl;
        Display_Files(head);
        break;

    // case 4:
    //     system("cls");
    //     cout<<endl<<"Great! you have chosen DELETION Operation. ";
        
    //     break;
    default: 
        cout<<endl<<" Invalid input! ";
}
cout<<endl<<"Press 'Y' if you want to continue: ";
cin>>ans;
}while(ans == 'y' || ans == 'Y');
    return 0;
}       