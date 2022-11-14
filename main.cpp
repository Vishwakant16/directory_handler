#include <iostream>
using namespace std;
class node{
public:
    string Name;//insertion name
    node* next;//outer boundary
    node* subFiles;//location of files in folder
    bool files;//check weather inserted node is representing file or folder
    //constructor
    node(string name,string type) {
        this->Name=name;
        this->next=NULL;
        this->subFiles=NULL;
        if(type=="files" || type=="Files"){
            this->files=true;
        }
        else{
            this->files=false;
        }
    }
};
node* inserting_folder(node* head,string name){
    node* new_node=new node(name,"folder");
    if(!head){
        head=new_node;
    }
    else{
        new_node->next=head;
        head=new_node;
    }
    return head;
}
node* insertion(node* head,string name,string folderName) {
    //folderName is files(no folder)
    if (folderName == "no folder" || folderName == "No folder") {
        node *new_node = new node(name, "files");
        if (!head) {
            head = new_node;
        } else {
            new_node->next = head;
            head = new_node;
        }
        return head;
    }
    //insertion of file in folder
    else {
        node *temp = head;
        node *dummy;
        while (temp) {
            temp = temp->next;
            if (temp->Name == folderName) {
                dummy = temp;
            }
        }
        node *new_node = new node(name, "files");
        if (!dummy) {
            dummy->subFiles = new_node;
            return dummy->subFiles;
        } else {
            new_node->next = dummy->subFiles;
            dummy->subFiles = new_node;
            return dummy->subFiles;
        }
    }
}
int main(){
    return 0;
}
