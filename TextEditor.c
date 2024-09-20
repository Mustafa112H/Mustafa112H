// Heba Mustafa 122916
//Section 3 Dr. Radi Jarrar
//P2_1221916_HebaMustafa_3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//structure for both our stacks (they have the same exact characteristics
//so we can use the same  to save space and easier implementation throughout the code
typedef struct node
{
    char word[100];
    int index;
    char Operate[10]; //insert or remove op
    struct node* next;
} node;
//this will be used for both undo and redo stacks
typedef struct
{
    node *top;
} Stack;


//structure for the queue itself
typedef struct
{
    node *front;
    node *rear;
} Queue;

//Functions
node * CreateNode(char* word, char* operate, int index);
void enqueue(Queue *queue, node* QNode);
node *dequeue(Queue *queue);
void printQueue(Queue *queue);
void loadFile(char *text,char* load);
void insertStringintoQueue(Queue* queue,char* INFO);
void QueueToStack(Queue *queue,Stack *stack,char* INFO);
void push(Stack *stack, node *Node);
void printStack(Stack *stack);
node* POP(Stack* Stack);
void SavetoOutputFile(char* INFO);
void clearStack(Stack *stack);
void MainMenu();
void WordRemove(char* INFO, char* Remove, Stack* undo);
void RedoOperation(char* INFO,Stack* Undo, Stack* Redo);
void UndoOperation(char* INFO,Stack* Undo, Stack* Redo);
void InsertatIndex(char* INFO, char* word,int index);
void  RemoveFromIndex(char* INFO, char* word,int index);
void WordsToRemoveQueue(Queue *queue, char *INFO);
int GFlag=0;//will help when inserting half a word



int main()
{
    printf("*********************** Welcome To My Text Editor ****************************\n\n");
    Queue queue= {NULL,NULL};//initializing the front and rear to Null (Empty Queue)
    Stack undoStack= {NULL};//initializing the top of the stacks to NULL -Empty Stacks
    Stack redoStack= {NULL};
    char INFO[10000];
    char LoadInfo[10000];
    int choice=0;
    while(choice!=9)
    {
        MainMenu();//Function that displays the options
        scanf("%d", &choice);
        printf("--------------------------------------------------------------------------\n\n");
        switch(choice)
        {
        case 1: // load
            loadFile(INFO,LoadInfo);//Takes the text and puts it into a string
            strcpy(LoadInfo,INFO);//Make a copy for option 2
            break;
        case 2: //print the loaded info
            if(strcmp(LoadInfo,""))//checks to make sure there is text before printing
                printf("%s", LoadInfo);
            else
                printf("\nNO TEXT HAS NOT BEEN LOADED\n");
            break;
        case 3: //insert strings to text
            //case when we want to add to the end and case after a specific word
            insertStringintoQueue(&queue,INFO);// when adding a string it adds the words into a queue and inserts them one by one into the text
            printQueue(&queue);//prints the queue to confirm that we added the words in it successfully
            QueueToStack(&queue, &undoStack,INFO);//dequeues into the stack and also into the text
            break;
        case 4: //remove Strings from Text
            WordsToRemoveQueue(&queue,INFO);
            printQueue(&queue);//prints the queue to confirm that we added the words in it successfully
            QueueToStack(&queue, &undoStack,INFO);//dequeues into the stack and also into the text
            break;
        case 5: //Perform Undo Operation
            UndoOperation(INFO, &undoStack, &redoStack);//it undoes our last operation on the text
            break;
        case 6: //perform Redo Operation
            RedoOperation(INFO, &undoStack, &redoStack);//it redoes what we undid
            break;
        case 7: // print both
            printf("\n(it will print NewLine- to tell us there is a line here) *not part of the word\n\n");
            printf("Undo Stack: \n");
            printStack(&undoStack);
            printf("\nRedo Stack: \n");
            printStack(&redoStack);
            break;
        case 8: //save the text to output file and clear the stacks
            if(strcmp(INFO,""))//Makes sure there is text before saving
                SavetoOutputFile(INFO);//saves the text into a file
            else
                printf("\nNO TEXT TO SAVE\n");
            clearStack(&undoStack);
            clearStack(&redoStack);
            break;
        case 9: //exit case
            printf("\nThank you For Choosing my Text Editor! GoodBye!!\n");
            break;
        default:
            printf("\n**Error Invalid Option**\n\n");
            break;
        case 10:
            printf(" \n%s\n", INFO);
            break;
        }
    }
    return 0;
}




//this will create the node we will use for the stacks + queues
node * CreateNode(char* word, char* operate, int index)
{
    node * QNode=(node*)malloc(sizeof(node));//allocates a place in the memory for it
    if ( QNode== NULL)//makes sure it allocated
    {
        printf("Full Memory!\n");
        exit(0);
    }
//operations to initialize the data in the node
    strcpy(QNode->word, word);
    QNode->next=NULL;
    strcpy(QNode->Operate,operate);
    QNode->index=index;
    return QNode;
}
void enqueue(Queue *queue, node* QNode)//adds a string into the queue
{
    if (!queue->front)//if the queue is empty we make the front and rear point at the node
    {
        queue->front = QNode;
        queue->rear = QNode;
    }
    else//queue not empty
    {
        queue->rear->next=QNode;//we add the node to the rear and make it the new rear
        queue->rear =QNode ;
    }
}
node *dequeue(Queue *queue)//removing the node from the queue
{
    if(!queue-> front)
    {
        printf("\n**Queue is empty!**\n");
        return NULL;
    }

    node *temp = queue->front;
    if(!queue->front->next)//one node case we remove the element both the front and rear should point to null
    {
        queue->front=NULL;
        queue->rear=NULL;
    }
    else
    {
        queue->front = queue->front->next;//the new front will be after the one we want to remove
        temp->next=NULL;//we make the next null so it no longer has any connections to the queue
    }

    return temp;
}
//this function will print all the elements in the queue
void printQueue(Queue *queue)
{
    if (!queue-> front)//if the front points at Null that means it is empty
    {
        // printf("\n**Queue is empty!**\n");
        return;
    }
    node *pos=queue->front;
    printf("\nQueue Front: |");
    while (pos!=NULL)
    {
        if(pos->word[0]=='\n')
        {
            char copy[50];
            strcpy(copy,pos->word+1);
            printf(" NewLine-%s | ",copy);
        }
        else
            printf(" %s | ", pos->word);
        pos=pos ->next;
    }
    printf(":Rear\n");
}

//Function to load the text from a file into a string - char array

void loadFile(char *text,char* load)
{
    char Line[1000];
    FILE *file=fopen("input.txt", "r");
    if (file==NULL)
    {
        printf("Error opening file\n");
        return;
    }
    while(fgets(Line,1000, file))
    {
        if (Line[strlen(Line)-1]=='\n')
        {
            Line[strlen(Line)-1]=' ';
        }
        strcat(load,Line);
        strcat(load,"\n");


    }
    load[strlen(load)-1]='\0';
    text[strlen(load)-1]='\0';
    if(strcmp(text,""))//is the text not empty?
        strcat(text," ");

    strcat(text,load);
    fclose(file);
    printf("\n--FILE LOADED SUCCESSFULLY--\n");
}
//this will take the string piece it into words and insert it onto the queue
void insertStringintoQueue(Queue* queue,char* INFO)
{
    int flag=1;
    int index;
    char temp[1000];
    printf("\nWould you like to write the new text on a separate line? \nChoose 1 for Yes Zero for no\n");
    int line=0;
    scanf("%d",&line);
    printf("Enter the new text:\n");
    char toInsert[1000];
    scanf(" %[^\n]",toInsert);
    printf("\nWhere would you like to Insert this string?\n1. At the end of the Text?\n2. After a specific string\n\nYour Choice: ");
    int insertChoice=0;
    scanf("%d", &insertChoice);
    printf("_______________________________________________________\n");
    if(insertChoice==2)
    {
        char InsertAfter[50];
        printf("\nEnter the String you would like to insert the string after: \n");
        scanf(" %[^\n]", InsertAfter);
        if(InsertAfter[strlen(InsertAfter)-1]==' ')
            InsertAfter[strlen(InsertAfter)-1]='\0';//handles user inputs
        char* indexofInsertAfter=strstr(INFO, InsertAfter);// this will find the address of the first char of the word we want to insert the text after
        if(!indexofInsertAfter)
        {
            printf("\n**Word does not Exist!**\n");
            return;
        }
        index=indexofInsertAfter-INFO+1+strlen(InsertAfter);
        if(isalpha(INFO[index-1]))
        {
            printf("\nYOU ARE ATTEMPTING TO INSERT IN THE MIDDLE OF A WORD! THIS WILL COMBINE THE TWO WORDS\n Press one continue....\n");
            int choice=0;
            scanf("%d", &choice);
            if(choice!=1)
            {
                printf("**Insert Operation Failed**");
                return;
            }
            index--;
            flag=0;
        }

        //indexofafter-Info will give us the index of the word we want to insert after since it will minus their addresses and the addresses are sequential(after each other)
        //+ length of the word and +1(for space) will give us the index we want to insert at.
    }
    if(line==1)
    {
        temp[0]='\n';
        strcat(temp,toInsert);
        strcpy(toInsert,temp);
    }
    char *wordTemp=strtok(toInsert, " ");//piece at every space
    while (wordTemp!=NULL)//while it doesnt point at NULL
    {
        if(insertChoice==1)
            index=-1;
        else if(wordTemp[0]=='|')
        {
            wordTemp[0]=' ';
        }
        node* Tnode=CreateNode(wordTemp,"insert",index);//the function will always insert at the end so -1
        enqueue(queue,Tnode);//add the words one by one into the queue
        index+=strlen(wordTemp)+flag;
        wordTemp=strtok(NULL, " ");//takes the next word
    }
}


void WordsToRemoveQueue(Queue *queue, char *INFO)
{
    int index;
    printf("Enter what you would like to Remove:\n");
    char toRemove[1000];
    char wordLine[50]="";
    scanf(" %[^\n]",toRemove);
    char* indextoRemove=strstr(INFO, toRemove);// this will find the address of the first char of the word we want to Remove the text after
    if(!indextoRemove)
    {
        printf("\n**String does not Exist!**\n");
        return;
    }
    index=indextoRemove-INFO;

    if(INFO[index-1]=='\n')
    {
        int choice=0;
        printf("\nWould you like to Remove the New Line?\n1. Yes\n2. No\n");
        scanf("%d", &choice);
        if(choice==1)
        {
            wordLine[0] = '\n';
            index=index-1;
        }
    }
    if(isalpha(INFO[index-1])&&isalpha(INFO[index+1]))
    {
        printf("\nYou are removing from a word\n Press 1 to Continue\n");
        int choice2=0;
        scanf("%d", &choice2);
        if(choice2!=1)
            return;
    }
    char *wordTemp=strtok(toRemove, " ");//piece at every space
    strcat(wordLine,wordTemp);
    while (wordTemp!=NULL)//while it doesnt point at NULL
    {
        node* Tnode=CreateNode(wordLine,"Remove",index);//the function will always insert at the end so -1
        enqueue(queue,Tnode);//add the words one by one into the queue
        wordTemp=strtok(NULL, " ");//takes the next word
        if(wordTemp)
            strcpy(wordLine,wordTemp);
    }
}

//This will take whats into the queue one by one place it into the text and the undo stack
void QueueToStack(Queue *queue,Stack *stack,char* INFO)
{
    while(queue->front)
    {
        node *Temp=dequeue(queue);//dequeue the node
        if(strcmp(Temp->Operate,"insert")==0)
        {
            InsertatIndex(INFO,Temp->word,Temp->index);
        }
        else
        {
            RemoveFromIndex(INFO,Temp->word,Temp->index);
        }

        push(stack, Temp);//pushes the node into the undo stack
        //notice here we used the same node so we dont have to copy-free-malloc everytime
    }
}

//inserts a node into the stack
void push(Stack *stack, node *Node)
{
    Node->next=stack->top;//always place it on top regardless if its empty or not
    stack->top=Node;
}

//this function will print whats inside our stacks it wont update anything on it
void printStack(Stack *stack)
{
    if(stack->top==NULL)//if the top is Null then no elements empty
    {
        printf("Stack Empty!\n");
        return;
    }

    node *pos=stack->top;//to move through the elements of the stack without moving the head
    printf("______________________________________________________________\n");
    printf("| %-28s | %-10s | %-5s |\n", "Token","Operation","Index");
    printf("--------------------------------------------------------------\n");
    while(pos!=NULL)//while it still points at something print what its pointing at
    {
        if(pos->word[0]=='\n')
        {
            char copy[50];
            strcpy(copy,pos->word+1);
            printf("| NewLine-%-20s | %-10s | %-5d |\n", copy,pos->Operate,pos->index);
        }
        else
            printf("| %-28s | %-10s | %-5d |\n", pos->word,pos->Operate,pos->index);
        pos=pos->next;//this is what makes it move to the element next it
    }
}

//this is a function to take out the top node of the stack
node* POP(Stack* Stack)
{
    if(Stack->top==NULL) //if the top points at nothing then its empty
    {
        printf("Stack Empty!");
        return 0;

    }
    node *temp=Stack->top;//this is what we want
    Stack->top=temp->next;//update the top..
    temp->next=NULL;//remove the  we want from the stack (here we separated it from the stack) we remove the next that links them together
    return temp;//notice we returned the  and didnt free it (when it leaves the undo we want it to join the redo)
}

//we want to save to output file
void SavetoOutputFile(char* INFO)
{
    FILE* file=fopen("output.txt","w");
    if(!file)
    {
        printf("Error opening file for writing\n");
        return;
    }
    fprintf(file,"%s",INFO);
    fclose(file);
    printf("\n--Successfully saved to Output File--\n");
}

//Function to remove all the nodes in the stack
void clearStack(Stack *stack)
{

    if(!stack->top)//if stack is null then no elements
    {
        printf("The Stack is already empty!");
        return;

    }
    while(stack->top)//if it has a top keep removing this top until there is no top which means it is empty
    {
        node*temp=POP(stack);
        free(temp);//frees the prev reserved memory

    }
}

//the options to be displayed
void MainMenu()
{
    printf("\n\n-------------- MENU: Choose One of the Following operations -------------- \n");
    printf("1. Load the input file which contains the initial text.\n2. Print the loaded text.\n3. Insert strings to the text.");
    printf("\n4. Remove strings from the text. \n5. Perform Undo operation\n6. Perform Redo operation");
    printf("\n7. Print the Undo Stack and the Redo stack \n8. Save the updated text to the output file. \n9. Exit");
    printf("\n\nEnter your Choice:  ");
}

// The Undo Operation function (it will undo our most recent operation)
void UndoOperation(char* INFO,Stack* Undo, Stack* Redo)
{

    if(Undo->top==NULL)//if the top is Null then no elements empty
    {
        printf("No Operation to Undo!\n");
        return;
    }
    node *Temp=POP(Undo);//take out the most recent operation
    push(Redo, Temp);//put it into the redo
    if(strcmp(Temp->Operate,"Remove")==0)//if the operation we did was a remove then we want to reinsert this word
    {
        InsertatIndex(INFO,Temp->word,Temp->index);
    }
    else//else we want to remove what we added
        RemoveFromIndex(INFO,Temp->word, Temp->index);
    printf("\nUndo Operation Complete!\n");
}
// The Redo Operation function (it will redo our most recent undone operation)
void RedoOperation(char* INFO,Stack* Undo, Stack* Redo)
{

    if(Redo->top==NULL)//if the top is Null then no elements empty
    {
        printf("No Operation to Redo!\n");
        return;
    }
    node *Temp=POP(Redo);//take out the node that has the data of the operation we want to redo
    push(Undo, Temp);//replace it into the undo stack
    if(strcmp(Temp->Operate,"insert")==0)//if the original operation was insert and we undid it we want to now redo it so reinsert it
    {
        InsertatIndex(INFO,Temp->word,Temp->index);
    }
    else//the opposite
    {
        if(Temp->index!=-1)
        {
            char* info=strstr(INFO,Temp->word);
            Temp->index=info-INFO;
            if(INFO[strlen(Temp->word)+Temp->index+1]=='.')
                Temp->index=+1;
        }
        RemoveFromIndex(INFO,Temp->word,Temp->index);
    }

    printf("\nRedo Operation Complete!\n");
}
//This is for the undo and redo operation (It will insert the removed for the undo of the remove)
void InsertatIndex(char* INFO, char* word,int index)
{
    char copyWord[50]="";
    strcpy(copyWord,word);
    char temp[2]="";//make sure its empty because if we go into the function more than once it may give us undesired behavior
    int wordSize=strlen(word);
    int INFOSize=strlen(INFO);
    if(index==-1)//if we initially added at the end of the text
    {
        strcat(INFO, " ");
        strcat(INFO, word);
    }
    else
    {
        strcpy(copyWord,word);
        //shifting to make space for the word since we dont want to overwrite the other words
        int k=1;

        if((isalpha(INFO[index])&&index!=0&&isalpha(INFO[index-1]))||ispunct(INFO[index+wordSize]&&INFO[index+wordSize-1]=='\n')||GFlag||(isalpha(INFO[index-1])&&INFO[index]==' '))
        {
            k=0;//middle                                            beginning hw               end hw
        }

        if(ispunct(INFO[index-1])&&INFO[index]==' ')
            k=1;
        for (int i=INFOSize; i>=index; i--)
        {
            INFO[i+wordSize+k]=INFO[i];

        }
        if(!ispunct(INFO[index+wordSize+k])&&k)
            INFO[index+wordSize]=' ';
        //punctuation mark handling (Special Case)
        if(ispunct(INFO[index-1]))
        {
            temp[0]=INFO[index-1];
            INFO[index-1]=' ';
            strcat(copyWord,temp);
            wordSize++;
        }
        //Insert the New Word in its correct Position
        for (int  i=0; i<wordSize; i++)
        {
            INFO[index+i]=copyWord[i];
        }
    }
    //INFO[index-1]=' ';
}

//this one is more time efficient!
void  RemoveFromIndex(char* INFO, char* word,int index)
{
    int handle=0;
    int line=0;
    char copy[50]="";
    strcpy(copy,word);
    int wordSize=strlen(copy);
    int INFOSize=strlen(INFO);

    if(index==-1) //to deal with when we inserted at the end of the string.
    {
        index=INFOSize-wordSize;
    }
    int dst = 0;
    if(INFO[index-1]==' '&&!isalpha(INFO[index+wordSize]))//punctuation
    {
        dst = 1;
    }
    else if(index==0||INFO[index-1]=='\n')
    {
        if(INFO[index+wordSize]==' ')//the beginning of the line get rid of the space
        {
            index++;
        }

        else
        {
            handle=1;
            line=-1;
        }
        // Remove leading space after removing the first word
        dst =1;
    }

    else if(INFO[index]=='\n'&&!GFlag)//new line case
    {
        line=1;
    }
    // Move the characters after the word to be removed
    memmove(INFO+index-dst+handle,INFO+index+wordSize+line+handle,INFOSize-index-wordSize+dst);
    INFOSize-=wordSize-dst;
    INFO[INFOSize] ='\0';
}
