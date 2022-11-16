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

Node* insertion(Node* head,string name, string type, string folderName) {
    
    Node *new_Node = new Node(name, type);    
    
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
            cout<<endl<<"File Inserted Successfully!";
        }
        
        // insertion of file inside particular folder
        else {
            Node *temp = head;
            Node *dummy;
            while (temp) {
                temp = temp->next;
                if (temp->Name == folderName) {
                    dummy = temp;
                }
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
        cout<<endl<<"Folder inserted successfully!";
    }
    return head;  
}
//display Total Files
void Display_Files(Node* head){
    while(head){
        if(head->subFiles){
            Node* dummy=head->subFiles;
            cout<<"Folder: "<<endl;
            while(dummy){
                cout<<dummy->Name<<endl;
                dummy=dummy->next;
            }
        }
        if(!head->subFiles){
            if(head->file){
                cout<<head->Name<<endl;
            }
        }
        head=head->next;
    }
}
//display Total Folders
void display_Folders(Node* head){
    cout<<"Folders"<<endl;
    while(head){
        if(!head->file){
            cout<<head->Name<<endl;
        }
        head=head->next;
    }
}
//displaying Total Files of Particular folder
void display_files_folders(Node* head,string folderName){
    cout<<"Files of this folder: "<<folderName<<endl;
    Node* dummy=head;
    while(dummy){
        if(dummy->Name!=folderName){
            dummy=dummy->next;
        }
        else break;
    }
    if(!dummy){
        cout<<"Error: Folder doesn't exist"<<endl;
    }
    else{
        //Printing Files of the Folder if exist
        head=dummy->subFiles;
        while (head) {
            cout << head->Name << endl;
            head=head->next;
        }
    }
}
//Searching Folders
bool findingFolders(Node* head,string folderName){
    while(head){
        if(head->Name!=folderName){
            head=head->next;
        }
        else break;
    }
}
//searching Files
bool findingFiles(Node* head,string fileName){
    Node* dummy;
    while(head){
        dummy=head->subFiles;
        if(head->subFiles){
            while (dummy) {
                if (dummy->Name != fileName) {
                    dummy = dummy->next;
                }
                else break;
            }
        }
        else{
            if(head->Name==fileName){
                return true;
            }
        }
        head=head->next;
    }
    if(!dummy){
        return false;
    }
    else{
        return true;
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
    return head;
}
//Delete files
Node* deleteFiles(Node* head,string fileName){
    
}
// Main function
int main(){
    Node * head=NULL;
    string fName;
    int i;
    cout<<"Press 1 to insert Folder."<<endl;
    cout<<"Press 2 to insert File."<<endl;
    cin>>i;
    switch(i){
        case 1:
            cout<<endl<<"Enter the name of the folder to be inserted: ";
            cin>>fName;
            insertion(head,fName,"folder","NULL");
            break;
        case 2:
            char ch;
            cout<<endl<<"Entre the name of the file to be inserted: ";
            cin>>fName;
            cout<<endl<<"Press a to insert a file directly.";
            cout<<endl<<"Press b to insert file inside any existing folder.";
            cin>>ch;
            switch(ch){
                case 'a':
                    insertion(head,fName,"file","NULL");
                    break;
                case 'b':
                    string folderName;
                    cout<<endl<<"Enter the folder name: ";
                    cin>>folderName;
                    insertion(head,fName,"file",folderName);
                    break;
            }
            break;
        default:
            cout<<endl<<"Invalid Input!";
        }     
    return 0;
}