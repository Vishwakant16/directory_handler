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