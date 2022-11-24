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

bool isEmpty(Node* head){
    if(!head)
        return true;
    else 
        return false;
}

//Searching Folders
bool findingFolders(Node* head,string folderName){
    // cout<<"Enter folderName to Search: "<<endl;        
    // cin>>folderName;
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
    // cout<<"Enter file name to find"<<endl;
    // cin>>fileName;
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

bool Update_folders(Node* head){
    string OldFolderName;
    string NewFolderName;
    cout<<"Which folder you want to Update? "<<endl;        
    cin>>OldFolderName;
        while(head){
        if(head->Name!=OldFolderName){
            head=head->next;
        }
        else{
            cout<< endl << "Enter the new name of "<<OldFolderName<<": ";
            cin>>NewFolderName;
            head->Name = NewFolderName; 
            return true;

        }
    }
    return false;
}

bool Update_files(Node* head){
    Node* dummy=NULL;
    string OldFileName;
    string NewFileName;
    cout<<"Which File you want to Update: "<<endl;
    cin>>OldFileName;
    while(head){
        dummy=head->subFiles;
        if(head->subFiles){
            while (dummy) {
                if (dummy->Name != OldFileName) {
                    dummy = dummy->next;
                }
                else {
                    cout<< endl << "Enter the new name of "<<OldFileName<<": ";
                    cin>>NewFileName;
                    dummy->Name=NewFileName;
                    return true;
                }
            }
        }
        else{
            if(head->Name==OldFileName && head->file){
                cout<< endl << "Enter the new name of "<<OldFileName<<": ";
                cin>>NewFileName;
                return true;
            }
        }
        head=head->next;
    }
    return false;
}

// Inssertion
Node* insertion(Node* head, string name,string type, string folderName) {
    Node *new_Node = new Node(name, type);    
    if(new_Node->file){
        if(findingFiles(head,name)){
            cout<<"Cannot Insert! File already exist "<<endl;
            return head;
        }
    }
    else{
        if(findingFolders(head,name)){
            cout<<"Cannot Insert! Folder already exist "<<endl;
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
        cout<<endl<<"File Inserted Successfully!"<<endl;
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
        cout<<endl<<"Folder inserted successfully!"<<endl;
    }
    return head;  
}


//display Total Files
void Display_Files(Node* head){
    if(!head){
        cout<<endl<<"Directory is Empty.";
    }
    else{
        while(head){
        Node* dummy=head->subFiles;
        cout<<endl;
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
}

//Delete Folder
// Node* deleteFolder(Node* head,string folderName){
//     if(head->Name==folderName){
//         head=head->next;
//     }
//     else{
//         Node* prev=head;
//         Node* temp=head->next;
//         while(temp){
//             if(temp->Name!=folderName){
//                 temp=temp->next;
//                 prev=prev->next;
//             }
//             else{
//                 break;
//             }
//         }
//         prev->next=temp->next;
//         delete temp;
//     }
//     cout<<"Folder deleted successfully: "<<endl;
//     return head;
// }
//Delete files
Node* deleteFiles(Node* head,string fileName){
    
    bool chk = isEmpty(head);
    if(chk){
        cout<<endl<<"Directory is Empty";
        return head;
    }
    // cout<<endl<<" Enter the name of the file or folder to delete: ";
    // cin>>fileName;
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
            if(temp->Name==fileName){
                temp=temp->next;
            }
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
// Node* updateFileLocation(Node* head,string oldFolder,string newFolder){
    //    head=       
// }

// Main function
int main(){
    Node * head=NULL;
    int options;
    char ans;
    string DeleteFileName;
    string InsertFileName;
    string SearchfileName;
    do{
        system("cls");
        // cout<<endl<<"\t\t\t\t\t*******************";
        cout<<endl<<"\t\t\t\t\t LIST OF CHOICES";
        cout<<endl<<"\t\t\t\t\t*****************";
        cout<<endl<<"--------------------------------------------------------------------------------------------------------------------------------------";
        cout<<endl<<"\t\t\t\t\t Press '1' to insert..";
        cout<<endl<<"\t\t\t\t\t Press '2' to search file or folder..";
        cout<<endl<<"\t\t\t\t\t Press '3' to Delete..";
        cout<<endl<<"\t\t\t\t\t Press '4' to Display..";
        cout<<endl<<"\t\t\t\t\t Press '5' to Update..";
        cout<<endl<<"--------------------------------------------------------------------------------------------------------------------------------------";
        cout<<endl<<"Enter your choice here :) ";
        cin>>options;
        
        switch (options){
        case 1:
            system("cls");
            cout<<endl<<"Great! You have chosen INSERTION Operation. "<<endl;
            char ans;
            int i;
            do {
                cout <<endl<< "Press 1 to insert Folder in the Directory." << endl;
                cout << "Press 2 to insert File in the Directory." << endl;
                cout<<"Enter your choice :) ";
                cin >> i;
                switch (i) {
                    case 1:
                        cout << endl << "Enter the name of the Folder to be inserted: ";
                        cin >> InsertFileName;
                        head = insertion(head, InsertFileName,"folder", "NULL");
                        break;
                    case 2:
                        cout << endl << "Enter the name of the File to be inserted: ";
                        cin >> InsertFileName;
                        char ch;
                        cout << endl << "Press a to insert a file directly.";
                        cout << endl << "Press b to insert file inside any existing folder.";
                        cout<<endl<<"Enter your choice :) ";
                        cin >> ch;
                        switch (ch) {
                            case 'a':
                                head = insertion(head,InsertFileName,"file", "NULL");
                                break;
                            case 'b':
                                string folderName;
                                cout << endl << "Enter the folder name in which you want to insert the file: ";
                                cin >> folderName;
                                head = insertion(head, InsertFileName,"file", folderName);
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
        system("cls");
        cout<<endl<<"Great! You have chosen SEARCHING Operation. "<<endl;
        char ch;
        
        do{
            cout<<endl<<"Press a to search any File: ";
            cout<<endl<<"Press b to search any Folder: ";
            cout<<endl<<"Enter your choice: ";
            cin>>ch;
            switch(ch){
                case 'a':     
                    cout<<endl<<"Enter the file name to Search: ";
                    cin>>SearchfileName;      
                    if(findingFiles(head,SearchfileName)){
                        cout<<"File exist :) "<<endl;
                    }
                    else {
                        cout <<SearchfileName<< " is not present in the Directory. " << endl;
                    }
                    break;

                case 'b':
                    cout<<endl<<"Enter the folder name to Search: ";
                    cin>>SearchfileName;
                    if(findingFolders(head,SearchfileName)){
                        cout<<"folder exist :) "<<endl;
                    }
                    else{
                        cout<<SearchfileName<<" is not present in the Directory. "<<endl;
                    }
                    break;
                default:
                    cout << endl << "Invalid Input!"; 
            }
            cout<<endl<<"Press 'Y' if you want to Search More Files and folders: ";
            cin>>ans;
        }while(ans == 'y' || ans == 'Y');
        break;

        case 3:
            system("cls");
            cout<<endl<<"Great! You have chosen DELETION Operation. "<<endl;
        do{
            cout<<endl<<"Press a to delete Files..";
            cout<<endl<<"press b to delete Folders.. ";
            cin>>ch;
            switch(ch){
                case 'a':
                    cout<<endl<<"Enter the File name to Delete: ";
                    cin>>DeleteFileName;
                    head = deleteFiles(head,DeleteFileName);
                    break;
                case 'b':
                    cout<<endl<<"Enter the Folder name to Delete: ";
                    cin>>DeleteFileName;
                    head = deleteFiles(head,DeleteFileName);
            }
            cout<<endl<<"Press 'Y' if you want to Delete More Files and folders: ";
            cin>>ans;
        }while(ans == 'y' || ans == 'Y');
        break;

        case 4:
            system("cls");
            cout<<endl<<"Great! you have chosen DISPLAY Operation. "<<endl;
            do{                
                Display_Files(head);
                cout<<endl<<"Press 'Y' if you want to Display again. "<<endl;
                cin>>ans;
                }while(ans == 'y' || ans == 'Y');
            break;

        case 5:
            system("cls");
            cout<<endl<<"Great! you have chosen UPDATION Operation. ";
            do{
                cout<<endl<<"Press a to update any File: ";
                cout<<endl<<"Press b to update any Folder: ";
                cout<<endl<<"Enter your choice: ";
                cin>>ch;
                switch(ch){
                    case 'a':           
                        if(Update_files(head)){
                            cout<<"Updated Successfully. "<<endl;
                        }
                        else {
                            cout << "File doesn't exist: " << endl;
                        }
                        break;

                    case 'b':
                        if(Update_folders(head)){
                            cout<<"Update successfully. "<<endl;
                        }
                        else{
                            cout<<"folder doesn't exist: "<<endl;
                        }
                        break;
                    default:
                        cout << endl << "Invalid Input!"; 
                }
                cout<<endl<<"Press 'Y' if you want to Update More Files and folders: ";
                cin>>ans;
            }while(ans == 'y' || ans == 'Y');
        break;

        default: 
            cout<<endl<<" Invalid input! ";
        }

        cout<<endl<<"Press 'Y' if you want to continue: ";
        cin>>ans;
    }while(ans == 'y' || ans == 'Y');
    return 0;
}