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
bool findingFolders(Node* head,string folderName){
    while(head){
        if(head->Name!=folderName){
            head=head->next;
        }
        else return true;
    }
    return false;
}
//searching Files
bool findingFiles(Node* head,string fileName){
    Node* dummy=NULL;
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
Node* insertion(Node* head,string name, string type, string folderName) {
    
    Node *new_Node = new Node(name, type);    
    if(new_Node->file){
        if(findingFiles(head,new_Node->Name)){
            cout<<"File already exist: "<<endl;
            return head;
        }
    }
    else{
        if(findingFolders(head,new_Node->Name)){
            cout<<"Folder already exist: "<<endl;
            return head;
        }
    }
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
        if(head->subFiles){
            Node* dummy=head->subFiles;
            cout<<"Folder: "<<head->Name<<endl;
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
    int i;
    char ans;
    do {
        cout << "Press 1 to insert Folder." << endl;
        cout << "Press 2 to insert File." << endl;
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
                cin >> ch;
                switch (ch) {
                    case 'a':
                        head = insertion(head, fName, "file", "NULL");
                        break;
                    case 'b':
                        string folderName;
                        cout << endl << "Enter the folder name: ";
                        cin >> folderName;
                        head = insertion(head, fName, "file", folderName);
                        break;
                }
                break;
            default:
                cout << endl << "Invalid Input!";
        }
        cout<<endl<<"Do you want to insert More ?";
        cin>>ans;
    }while(ans == 'y' || ans == 'Y');
    return 0;
}