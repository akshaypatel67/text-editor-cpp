/* 

Roll No.: 21BCE515
Name: Akshay Patel

Text editor using Linked List and Stack

*/

#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>

using namespace std;

struct undoredoCmd{
	int lineNumber;
	string text;
	int commandNumber;
	int mLine;
	int nLine;
    struct undoredoCmd *next;
};

struct node{
	string data;
	struct node *next;
};

node *head;
node *tail;
int numOfLines = 0;
int next = 1;
undoredoCmd *undoTop;
undoredoCmd *redoTop;

//push into undo or redo stack
void push(int operation, int cmdNo, int lineNo=0, string data="", int nLine=0, int mLine=0) {
    struct undoredoCmd *cmd;
    cmd = new undoredoCmd();
    cmd->commandNumber = cmdNo;
    cmd->lineNumber = lineNo;
    cmd->mLine = mLine;
    cmd->nLine = nLine;
    cmd->text = data;

    if (operation == 1) {
        cmd->next = undoTop;
        undoTop = cmd;
    } else if(operation == 2) {
        cmd->next = redoTop;
        redoTop = cmd;
    }
    
}

//pop from undo or redo stack
void pop(int operation) {
    struct undoredoCmd *temp;
    if(operation == 1) {
        temp = undoTop;
        undoTop = undoTop->next;
    } else if(operation == 2) {
        temp = redoTop;
        redoTop = redoTop->next;
    }

    temp->next = NULL;
    delete(temp);
    cout<<"pop";
}

//add node to head
void addToHead(string data) {
    if (head == NULL)					//no node, empty linked list
    {
        node *temp;
        temp = new node;
        temp->data = data;
        temp->next = NULL;
        head = temp;
        tail = head;
    }
    else 								//one or more than one node
    {
        node *temp;
        temp = new node;
        temp->data = data;
        temp->next = head;
        head = temp;
    }
    numOfLines++;
    // struct undoredoCmd *adddedToHead;
    // adddedToHead->lineNumber = 1;
    // adddedToHead->commandNumber = 1;
    // adddedToHead->nLine = 0;
    // adddedToHead->mLine = 0;
    // adddedToHead->text = "";
    
}

//add node to tail
void addToTail(string data){
    node *temp;
    temp = new node;
    temp->data = data;
    	
    if (head == NULL) {
        temp->next = NULL;
        head = temp;
        tail = head;
    } else {
        temp->next = NULL;
        tail->next = temp;
        tail = temp;
    }

    numOfLines++;
    // undoCmd addedToTail;
    // addedToTail.lineNumber = 1;
    // addedToTail.commandNumber = 8;
    
}

//add node in between
void insertInBetween(int line, string data) {
    if (line == 0)
    {
        cout<<"There's no line 0, did you mean 1 (cough...Google suggestions...cough)"<<endl;
    }
    else if (line == 1)
    {
        addToHead(data);
    }
    else{
        node *prevNode = head;
        node *nextNode = head;
        node *temp = new node;
        temp->data = data;
        temp->next = NULL;
        int iterator = 2;
        while(iterator <= line)
        {
            prevNode = nextNode;
            nextNode = nextNode->next;
            iterator++;
        }
        prevNode->next = temp;
        temp->next = nextNode;
        numOfLines++;
        // undoCmd insertedInBetween;
        // insertedInBetween.lineNumber = line;
        // insertedInBetween.commandNumber = 6;
        // push(1, 3, line);
    }
}

//delete head node
void deleteHead() {
    cout<<"called";
    string backup = head->data;
    node *temp = head;
    head = head->next;
    free(temp);
    numOfLines--;
}

//delete tail node
void deleteTail() {
    node *temp = head;
    while (temp->next != NULL && temp->next->next != NULL)
    {
        temp = temp->next;
    }
    tail = temp;
    string backup = temp->next->data;
    delete temp->next;
    temp->next = NULL;
    numOfLines--;
}

//delete node from between
string deleteLine(int line) {
    string backup;
    if(line == 0){
        cout<<"There's no line 0, did you mean 1?"<<endl;
    }
    else if (line > numOfLines)
    {
        cout<<"Entered line number is greater than existing lines..."<<endl;
    }
    else if(head == tail) {
        backup=head->data;
        node *temp = head;
        delete(temp);
        head = NULL;
        tail = NULL;
        numOfLines--;
    }
    else if(line == 1) {
        backup=head->data;
        deleteHead();
        
        // undoCmd headRemoved;
        // headRemoved.text = backup;
        // headRemoved.lineNumber = 1;
        // headRemoved.commandNumber = 12;
        // undoStack.push(headRemoved);
    }
    else if(line == numOfLines){
        backup=tail->data;
        deleteTail();
        // undoCmd deletedLine;
        // deletedLine.commandNumber = 11;
        // deletedLine.text = backup;
        // deletedLine.lineNumber = line;
        // undoStack.push(deletedLine);
    }
    else if (line < numOfLines)
    {
        node *prevNode = head;
        node *nextNode = head;
        node *temp = head;
        int iterator = 2;
        while(iterator <= line)
        {
            prevNode = nextNode;
            nextNode = nextNode->next;
            iterator++;
        }
        temp = nextNode;
        nextNode = nextNode->next;
        prevNode->next = nextNode;
        backup = temp->data;
        delete(temp);
        numOfLines--;
        // undoCmd deletedLine;
        // deletedLine.commandNumber = 10;
        // deletedLine.text = backup;
        // deletedLine.lineNumber = line;
        // undoStack.push(deletedLine);
        
    }
    return backup;
}

//insert further to end
int insertFurther(int line, string data) {
    int lineNo = 0;
    while(numOfLines < line-1) {
        addToTail("\n");
        lineNo++;
    }
    addToTail(data);
    push(1, 2, lineNo);
}

//insert in between
void insertLine(string data, int line) {
    if (line == 1)
    {
        addToHead(data);
        push(1, 1, line);
    }
    else if (line > numOfLines)
    {
        insertFurther(line, data);
    }
    else if (line <= numOfLines)
    {
        insertInBetween(line, data);
        push(1, 1, line);
    }
}

int insertFur(int line, string data) {
    int lineNo = 0;
    while(numOfLines < line-1) {
        addToTail("\n");
        lineNo++;
    }
    addToTail(data);
    push(2, 2, lineNo);
}

void insertLn(string data, int line) {
    if (line == 1)
    {
        addToHead(data);
        push(2, 1, line);
    }
    else if (line > numOfLines)
    {
        insertFur(line, data);
    }
    else if (line <= numOfLines)
    {
        insertInBetween(line, data);
        push(2, 1, line);
    }
}

//delete N line and add to M line
void moveNtoM(int lineN, int lineM) {
    if (lineN == 1)
    {
        string data = head->data;
        deleteHead();
        insertInBetween(lineM, data);
    }
    else
    {
        node *temp = head;
        int iterator = 1;
        while(iterator < lineN)
        {
            temp = temp -> next;
            iterator++;
        }
        string data = temp->data;
        deleteLine(lineN);
        insertInBetween(lineM, data);
    }
    // undoCmd moveHeadToM;
    // moveHeadToM.commandNumber = 2;
    // moveHeadToM.nLine = nLineGiven;
    // moveHeadToM.mLine= mLineGiven;
    // undoStack.push(moveHeadToM);
}

//update node
string replaceText(int line, string data) {
    
    if (line == 0)
    {
        cout<<"There's no line 0, did you mean 1?"<<endl;
    }
    else if (numOfLines >= line)
    {
        node *temp = head;
        int goToLine = 1;
        while(goToLine < line)
        {
            temp = temp->next;
            goToLine++;
        }
        string backup = temp->data;
        temp->data = data;		//change what is inside the node number that has been given as line parameter
        // undoCmd replacedLine;
        // replacedLine.lineNumber = lineGiven;
        // replacedLine.text = backup;
        // replacedLine.commandNumber = 4;
        // undoStack.push(replacedLine);
        return backup;
    }
}

//print linked list
void printall(){						//function used to print the whole linked list
    node *temp = head;
    int linePrinted = 1;
    int choice;
    if (head == NULL)
    {
        cout<<"no data!"<<endl;
    }
    else{
        while(temp!=NULL)
        {
            cout<<linePrinted<<") "<<temp->data<<endl;
            temp = temp->next;
            linePrinted++;
        }
    }
}

//add lines from file to linked list
void openFile() {
    string fileName;
    cout<<"Enter the file name : ";
    cin>>fileName;
    fileName+=".txt";
    ifstream myfile;
    myfile.open(fileName);
    string s;
    while(getline(myfile,s))
    {
        addToTail(s);
    }
    myfile.close();
}

//save text file
void saveTxt() {
    ofstream outfile;

    node *temp = head;
    string fileName;
    cout<<"Enter the file name : ";
    cin>>fileName;
    fileName+=".txt";
    outfile.open(fileName, ios_base::app);
    while(temp!=NULL)
    {
        outfile<<temp->data;
        temp = temp->next;
    }
    outfile.flush();
    outfile.close();
}

//undo operations
void undo(int operation) {
    int cmdNo, lineNo, lineN, lineM;
    string text, backup;

    if(operation == 1) {
        if(undoTop == NULL) {
            cout<<"Nothing to undo!"<<endl;
            return;
        }
        cmdNo = undoTop->commandNumber;
        lineNo = undoTop->lineNumber;
        text = undoTop->text;
        lineN = undoTop->nLine;
        lineM = undoTop->mLine;
    }
    

    switch (cmdNo)
    {
    case 1:
        pop(operation);
        backup = deleteLine(lineNo);
        push(2, 3, lineNo, backup);
        break;

    case 2:
        pop(operation);
        backup = tail->data;
        push(2, 3, numOfLines, backup);

        while(lineNo>=0) {
            deleteTail();
            lineNo--;
        }
        break;

    case 3:
        pop(operation);
        insertLn(text, lineNo);
        break;

    case 4:
        pop(operation);
        moveNtoM(lineM, lineN);
        push(2, 4, 0, "", lineM, lineN);
        break;

    case 5:
        pop(operation);
        backup = replaceText(lineNo, text);
        push(2, 5, lineNo, backup);
        break;
    
    default:
        break;
    }
}

//redo operations
void redo(int operation) {
    int cmdNo, lineNo, lineN, lineM;
    string text, backup;

    if(operation == 2) {
        if(redoTop == NULL) {
            cout<<"Nothing to redo!"<<endl;
            return;
        }
        cmdNo = redoTop->commandNumber;
        lineNo = redoTop->lineNumber;
        text = redoTop->text;
        lineN = redoTop->nLine;
        lineM = redoTop->mLine;
    }

    switch (cmdNo)
    {
    case 1:
        pop(operation);
        backup = deleteLine(lineNo);
        push(1, 3, lineNo, backup);
        break;

    case 2:
        pop(operation);
        push(1, 3, lineNo+numOfLines, backup);

        while(lineNo>=0) {
            deleteTail();
            lineNo--;
        }
        break;

    case 3:
        pop(operation);
        insertLine(text, lineNo);
        break;

    case 4:
        pop(operation);
        moveNtoM(lineM, lineN);
        push(1, 4, 0, "", lineM, lineN);
        break;

    case 5:
        pop(operation);
        backup = replaceText(lineNo, text);
        push(1, 5, lineNo, backup);
        break;
    
    default:
        break;
    }
}

//main method
int main(int argc, char const *argv[]) {
    int choice = -1;
    head = NULL;
    tail = NULL;
    system("Color 2");

    while(choice != 0){
        system("cls");
        cout<<"\t-------------------------------\n"<<endl;
        cout<<"\t||||||    TEXT EDITOR    ||||||\n"<<endl;
        cout<<"\t-------------------------------\n"<<endl;
        cout<<"\tPlease choose what you want to do\n\t1. Insert text into Line N"<<endl;
        cout<<"\t2. Delete line N\n\t3. Move line N into line M\n\t4. Replace text in Line N"<<endl;
        cout<<"\t5. Print all\n\t6. Undo\n\t7. Redo\n\t8. Open a .txt file\n\t9. Save into a .txt file"<<endl<<"\n\t";
        cout<<"Enter your choice : ";
        cin>>choice;
        cout<<endl;

        int line;
        string data;

        switch (choice)
        {
            case 1:
                cout<<"\tEnter line you want the text to be placed into : ";
                cin >> line;
                cout<<"\tEnter text : ";
                cin.ignore(1);
                getline(cin,data);
                data+="\n";
                insertLine(data, line);
                break;

            case 2:
                if (head == NULL) {
                    cout<<"\tThere is no line delete!"<<endl;
                } else {
                    int line;
                    cout<<"\tEnter the line number you want to delete : ";
                    cin>>line;
                    string backup = deleteLine(line);
                    push(1,3,line,backup);
                }
                break;

            case 3:
                int lineN;
				int lineM;
				cout<<"\tEnter line number you want to move : ";
				cin>>lineN;
				cout<<"\tEnter new line number you want to move to : ";
				cin>>lineM;
				moveNtoM(lineN, lineM);
                push(1, 4, 0, "", lineN, lineM);
                break;

            case 4:
				cout<<"\tEnter line you want to change the content of : ";
				cin>>line;
				if (line > numOfLines)
				{
					cout<<"\tThe line you entered exceeds the existing number of lines..."<<endl;
				}
				else{
					cout<<"\tEnter the new text : ";
					cin.ignore(1);
                    getline(cin,data);
					data+="\n";
					string backup = replaceText(line, data);
                    push(1, 5, line, backup);
				}
                break;

            case 5:
                system("cls");
                printall();
                break;

            case 6:
                undo(1);
                break;

            case 7:
                redo(2);
                break;

            case 8:
                head=NULL;
                openFile();
                break;

            case 9:
                saveTxt();
                break;
            
            default:
                break;
        }
        cout<<"\t";
        system("pause");
    }

    return 0;
}