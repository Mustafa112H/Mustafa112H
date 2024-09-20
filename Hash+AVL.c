//Heba Mustafa 1221916
//Dr. Radi Jarrar Section 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int TableSize=0;
int Hashcount=0;
int AvlCount=0;
typedef struct AVLnode* AVLPTR;
struct AVLnode
{
    char word[50];
    AVLPTR Left;
    AVLPTR Right;
    int Height; //Balance information
    int Frequency;
};
struct HashNode
{
    char word[50];
    int frequency;
};
typedef struct HashNode HashNode;
typedef struct HashNode* HashPTR;

//Prototypes

//different functions
int isPrime(int n);
void MainMenu();
void FilterWord(char* word);
void ReadFromFile(char* text);

//HashFunctions
//Notice here we pass HashPTR* thats because in my code I implemented the HashTable as a pointer thats going to point to an array of pointers
//this is so that i don't need to allocate memory for unused cells and also when i want to rehash i can simply make this pointer point to the
//new array of pointers, otherwise i would allocate or would have to use an if the rehash is not empty then insert into rehash making the code
//harder to manage and less understandable :)
HashPTR FindHash(char* word, HashPTR* hashTable, int tableSize, int* ind);
void InsertToHash(char* word, int frequency, HashPTR* hashTable, int tableSize);
void DeleteFromHash(char* word,HashPTR* Table, int size);
void AVLtoHash(AVLPTR T, HashPTR* hash,int size);
int hash(char* word, int TableSize);
HashPTR RehashTable(HashPTR* hashTable, int tableSize);
int hash2(char* word,int size);
void printHashTable(HashPTR* hashTable, int tableSize);
void MostFreqHash(HashPTR* hashTable, int tableSize);
int ThresholdHash(HashPTR* hashTable, int tableSize, int threshold);
int FreqCountHash(HashPTR* hashTable,int num);
void DeleteHashTable(HashPTR* hashTable, int tableSize);

//AVLFunctions
int ThresholdAVL(AVLPTR T, int threshold);
AVLPTR MakeEmpty(AVLPTR T);
int Height(AVLPTR P);
AVLPTR SingleRotateWithLeft(AVLPTR Node2);
AVLPTR SingleRotateWithRight(AVLPTR Node1);
AVLPTR DoubleRotateWithLeft(AVLPTR Node3);
AVLPTR DoubleRotateWithRight(AVLPTR Node1);
AVLPTR InsertAVL(char* X, AVLPTR T);
AVLPTR FindMin(AVLPTR T);
void PrintInOrder( AVLPTR t);
AVLPTR DeleteAVL(char* X, AVLPTR T);
AVLPTR TexttoAvl(char* Text, AVLPTR T);
void MostFreqAVL(AVLPTR T,int maxFreq);
int MaxFreqAVL(AVLPTR T);
int FreqCountAVL(AVLPTR T, int count);
AVLPTR Find( char* X, AVLPTR T );

int main()
{
    char Text[100000];
    char wordIn[50];
    int opt=0;
    int treecreatedFlag=0;
    int HashCreatedFlag=0;
    int choice=0;
    while(choice!=11)
    {
        MainMenu();//Function that displays the options
        scanf("%d", &choice);
        printf("--------------------------------------------------------------------------\n\n");
        switch(choice)
        {
        case 2://Create Avl
            printf("Create an AVL: \n");
            AVLPTR T;
            if(treecreatedFlag)
            {
                printf("Tree already created!\n");
                printf("Would you like to Delete it and Create a new One? (yes(1)/no(0))\n");
                int ans=-1;
                scanf("%d", &ans);
                if(ans==0){
                break;}
                MakeEmpty(T);
                AvlCount=0;

            }
            printf("Creating an Avl tree...\n");
            T =NULL;
            T=MakeEmpty(T);//
            treecreatedFlag=1;
            if(Text[0]!='\0')
            {
                printf("Would you like to Insert the info you read from the file into the AVL?(yes(1)/no(0))\n");
                scanf("%d",&opt);
                if(opt)
                    T=TexttoAvl(Text,T);
            }
            break;
        case 1: // load
            ReadFromFile(Text);
            printf("Loaded Info: %s", Text);
            if(treecreatedFlag)
                T=TexttoAvl(Text,T);
            break;

        case 3: // InsertAVL a Word
            if(!treecreatedFlag)
                printf("No Tree! Choose option 2 to create a tree first!");
            else
            {
                printf("Enter the word you would like to Insert into the Tree: \n");
                scanf("%s", wordIn);
                T=InsertAVL(wordIn,T);
            }
            break;
        case 4://DeleteAVL
            if(!treecreatedFlag)
                printf("No Tree! Choose option 2 to create a tree first!");
            else
            {
                printf("Enter the word you would like to Delete from the Tree: \n");
                scanf("%s", wordIn);
                T=DeleteAVL(wordIn,T);
            }
            break;
        case 5:
            if(!treecreatedFlag)
                printf("No Tree! Choose option 2 to create a tree first!");
            else
                PrintInOrder(T);
            break;
        case 6://make the hash table
            printf("Create HashTable: \n");
            HashPTR* hashTable;
            if(HashCreatedFlag)
            {
                printf("Hash Table already Created!\n");
                printf("Would you like to Delete it and Create a new One? (yes(1)/no(0))\n");
                int ans=-1;
                scanf("%d", &ans);
                if(!AvlCount)
                printf("NO AVL TREE!\nWould you like to continue and create an empty table? (yes(1)/no(0))\n");
                scanf("%d", &ans);
                if(ans==0){
                break;}
                free(*hashTable);
                DeleteHashTable(hashTable,TableSize);
                Hashcount=0;
            }
           else if(!AvlCount)
            {
                printf("NO AVL TREE!\nWould you like to continue and create an empty table? (yes(1)/no(0))\n");
                int ans=-1;
                scanf("%d", &ans);
                if(ans==0)
                    break;

                TableSize=13;//initializing table on random number since we have no data from the tree
            }
            else
                TableSize=AvlCount*2+1;
            HashCreatedFlag=1;
            while(!isPrime(TableSize))
                TableSize++;
            printf("Creating Hash Table.....");
            //hashTable is a pointer thats going to point to table of pointers
            hashTable=(HashPTR*)malloc(TableSize* sizeof(HashPTR));//initialize an area in the memory the size of every pointer for every index
            if (hashTable== NULL)
            {
                printf("Memory FULL!\n");
                break;
            }
            for(int i=0; i<TableSize; i++)
            {
                hashTable[i]=NULL;
            }
            Hashcount=0;
            if(AvlCount)
                AVLtoHash(T,hashTable,TableSize);
            break;
        case 12:
            if(!HashCreatedFlag)
            {
                printf("Hash Table Not Created!\n");
                break;
            }
            printf("\nHash Table with Size %d\n",TableSize);
            printHashTable(hashTable,TableSize);
            break;
        case 7://InsertAVL into Hash
            if(!HashCreatedFlag)
            {
                printf("Hash Table Not Created! Choose option 6 First!\n");
                break;
            }
            printf("Enter the word you would like to Insert into the Hash:\n");
            scanf(" %s", wordIn);
            InsertToHash(wordIn,1,hashTable,TableSize);
            if(Hashcount>(TableSize*.7)) //if the hash table is 70 percent full
            {
                printf("Rehashing the table.........\n");
                HashPTR newHashTable=RehashTable(hashTable,TableSize);
                if (newHashTable!=NULL)
                {
                    *hashTable=newHashTable;
                }
                else
                {
                    printf("Rehashing failed!\n");
                }
            }
            break;
        case 8://DeleteAVL Word From Hash
            if(!HashCreatedFlag)
            {
                printf("Hash Table Not Created! Choose option 6 First!\n");
                break;
            }
            printf("Enter the word you would like to Delete from the Hash:\n");
            scanf("%s", wordIn);
            DeleteFromHash(wordIn,hashTable,TableSize);
            break;
        case 9://search and print frequency
            if(!HashCreatedFlag)
            {
                printf("Hash Table Not Created! Choose option 6 First!\n");
                break;
            }
            printf("Enter the word that you would like to know the frequency of:\n");
            scanf("%s", wordIn);
            int z;
            HashPTR Temp=FindHash(wordIn,hashTable,TableSize,&z);
            printf("The Frequency of %s is %d\n",Temp->word, Temp->frequency);
            break;
        case 10://print word stats
            //i was unsure if it meant the different words we have or the frequency of one word so i did both
            printf("Number of Unique Words in AVL:  %d\n",AvlCount);
            printf("Number of Unique Words in Hash:  %d\n",Hashcount);
            printf("Number of words with the frequency of one in AVL: %d",FreqCountAVL(T,1));
            printf("\nNumber of words with the frequency of one in Hash: %d\n",FreqCountHash(hashTable,1));
            printf("\n-----------------------------------------------------\n");
            printf("\n-----------------------------------------------------\n");
            int max=MaxFreqAVL(T);
            printf("\n%d Most Frequent word(s) in the AVL with the Frequency %d:\n",FreqCountAVL(T,max),max);
            MostFreqAVL(T,max);
            MostFreqHash(hashTable,TableSize);
            printf("\n-----------------------------------------------------\n\n");
            int threshold;
            printf("Enter the frequency threshold: \n");
            scanf("%d", &threshold);
            printf("Word(s) with frequency above %d in AVL:\n", threshold);
            int holdAvl=ThresholdAVL(T, threshold);
            printf("----(%d) Word(s)----\n\n",holdAvl);
            printf("Word(s) with frequency above %d in Hash Table:\n", threshold);
            int holdHash=ThresholdHash(hashTable, TableSize, threshold);
            printf("----(%d) Word(s)----\n\n",holdHash);
            break;

        case 11:
            printf("Exit Successful!");
            break;
        default:
            printf("INVALID CHOICE!");
        }
    }
    return 0;

}

AVLPTR TexttoAvl(char* Text, AVLPTR T)
{
    char* word;
    char TextCopy[100000];
    strcpy(TextCopy,Text);
    word=strtok(TextCopy, " ");
    while(word)
    {
        T=InsertAVL(word,T);
        word=strtok(NULL," ");
    }
    return T;

}

HashPTR RehashTable(HashPTR* hashTable, int tableSize)// this function will rehash the table when the size gets too small
{
    int index, IndexCol, i ;
    int newSize=tableSize*2+1; // New size for the hash table
    while (!isPrime(newSize))//the new table size should be the first prime number larger than twice the prev size
    {
        newSize++;
    }
    HashPTR* newTable=(HashPTR*)malloc(newSize* sizeof(HashPTR));//initialize an area in the memory the size of every pointer for every index
    if(newTable==NULL)
    {
        printf("**MEMORY FULL**!\n");
        return NULL;
    }
    for(int j=0; j<newSize; j++)
    {
        newTable[j]=NULL;
    }

    for(int j=0; j<tableSize; j++)
        if (hashTable[j]!= NULL)
        {
            if(!strcmp(hashTable[j]->word,"*"))//the previous DeleteAVL collision handling cases wont be needed anymore
            {
                free(hashTable[j]);
                hashTable[j]=NULL;
                continue;
            }
            index=hash(hashTable[j]->word,newSize);
            IndexCol=index;
            i=1;//probing var
            while(i<newSize)
            {
                if(newTable[IndexCol]==NULL)//if the index is empty
                {
                    newTable[IndexCol]=hashTable[j];
                    break;
                }
                IndexCol=(index+i*hash2(hashTable[j]->word,newSize))% newSize;//cases of collision
                i++;
            }
        }
    TableSize= newSize;//update the size of the hash table
    free(hashTable);//free prev memory clears the mem of the table
    return *newTable;//so we can make the pointer point to this instead

}

void MainMenu()
{
    printf("\n\n-------------- MENU: Choose One of the Following operations -------------- \n");
    printf("1. Load data from the file.\n2. Create the AVL tree.\n3. Insert a word to the AVL tree.\n4. Delete a word from the AVL tree.");
    printf("\n5. Print the words as sorted in the AVL tree.\n6. Create the Hash Table.\n7. Insert a word to the Hash table.\n8. Delete a word from the hash table.");
    printf("\n9. Search for a word in the hash table and print its frequency.\n10. Print words statistics.\n11. Exit the application.\n12. Print the Hash Table");
    printf("\n\nEnter your Choice:  ");
}

void InsertToHash(char* word, int frequency, HashPTR* hashTable, int tableSize)
{
    FilterWord(word);
    if(word[0]=='\0')
    {
        printf("Invalid");
        return;
    }
    HashPTR Exist=NULL;
    int z;
    Exist= FindHash(word,hashTable,tableSize,&z);
    if(Exist!=NULL)
    {
        Exist->frequency++;
        return;
    }
    int index=hash(word,tableSize);
    // Create a new node
    HashPTR InsertAVL = malloc(sizeof(HashNode));
    if (InsertAVL == NULL)
    {
        printf("**MEMORY FULL!\n");
        return;
    }
    strcpy(InsertAVL->word,word);
    InsertAVL->frequency=frequency;
    int hash2val= hash2(word,tableSize);
    int IndexCol=index;
    int i = 1;
    while (i<tableSize)
    {
        if (hashTable[IndexCol]==NULL||!strcmp(hashTable[IndexCol]->word,"*"))
        {
            if (hashTable[IndexCol]!=NULL&&strcmp(hashTable[IndexCol]->word,"*")==0)
            {
                free(hashTable[IndexCol]);
            }
            hashTable[IndexCol]=InsertAVL;//empty at index (No Collision)
            Hashcount++;//keeps track of the unique and number of full cells which will later help us know when we want to rehash
            return;
        }
        IndexCol=(index+i*hash2val)%tableSize;//when there is collision it will enter here
        i++;
    }
    // If the loop exits without finding an empty slot, the hash table is full
    //since we have a rehashing when the table is .7 full we should never reach here but i will keep this incase
    printf("Hash table is full. Unable to InsertAVL %s with frequency %d.\n", word, frequency);
    free(InsertAVL);
}

void PrintInOrder(AVLPTR t)//Prints the elements in order (Left Root Right)
{
    if( t != NULL)
    {
        PrintInOrder(t->Left);
        printf("%s: ",t->word);
        printf(" %d\n",t->Frequency);
        PrintInOrder(t->Right);
    }
}

void FilterWord(char* word)
{
    int index=0;
    for(int i=0; word[i]!='\0'; i++)
    {
        if (isalpha(word[i]))
        {
            word[index]=tolower(word[i]);
            index++;
        }
    }
    word[index]='\0';

}

void ReadFromFile( char* text)
{
    char word[100];
    FILE *file=fopen("input2.txt","r");
    if (file==NULL)
    {
        printf("Error opening file\n");
        return;
    }
    text[0]='\0';
    while (fscanf(file,"%s",word)!=EOF)
    {
        strcat(text,word);
        strcat(text," ");
    }
    fclose(file);
}

void DeleteFromHash(char* word,HashPTR* Table, int size )
{
    HashPTR Exist=NULL;
    int index;
    Exist=FindHash(word,Table,size,&index);
    if(Exist==NULL)
    {
        printf("WORD NOT FOUND!!");
        return;
    }
    else if(Exist->frequency>1)
    {
        printf("The Frequency is %d, Would you like to update the frequency(1) or Remove the Full word(0):\n",Exist->frequency);//The case where it has a frequncy of 1 or if we want to DeleteAVL the full word
        int choice=-1;
        scanf("%d",&choice);
        if (choice==1)
        {
            Exist->frequency--;
            return;
        }
    }
    Hashcount--;//the number of full hash cells is decremented
    strcpy(Table[index]->word,"*");
    Table[index]->frequency=0;
    //make it so that it has a character which tells us that there was something here so when we look for a different word that collided with it we find it with
    //ease and less time complexity
}

void AVLtoHash(AVLPTR T, HashPTR* hash,int size)//we iterate through the AVL like we do for the print to InsertAVL everything into the hash
{
    //here i chose to do it inorder however you can use any of the three methods you like
    if (T==NULL)
        return;
    AVLtoHash(T->Left,hash,size);
    InsertToHash(T->word,T->Frequency,hash,size);
    AVLtoHash(T->Right,hash,size);
}

AVLPTR MakeEmpty(AVLPTR T)
{
    if(T!=NULL)
    {
        MakeEmpty(T->Left);
        MakeEmpty(T->Right);
        free(T);
    }
    return NULL;
}


int Height(AVLPTR P)
{
    if(P==NULL)
        return -1;
    else
        return P->Height;
}

int Max(int Lhs,int Rhs)
{
    //if left is greater than right return left otherwise right
    return Lhs>Rhs?Lhs:Rhs;
}

AVLPTR SingleRotateWithLeft(AVLPTR Node2)
{
    AVLPTR  Node1;
    Node1=Node2->Left;
    Node2->Left=Node1->Right;
    Node1->Right=Node2;
    Node2->Height=Max(Height(Node2->Left),Height(Node2->Right))+ 1;
    Node1->Height=Max(Height(Node1->Left),Node2->Height)+1;
    return Node1;
}

AVLPTR SingleRotateWithRight( AVLPTR Node1 )//must have a right child rotate node with right and update
{
    AVLPTR Node2;
    Node2=Node1->Right;
    Node1->Right=Node2->Left;
    Node2->Left=Node1;
    Node1->Height=Max(Height(Node1->Left),Height(Node1->Right))+1;
    Node2->Height=Max(Height(Node2->Right),Node1->Height)+1;

    return Node2;  //new root
}

AVLPTR DoubleRotateWithLeft(AVLPTR Node3)//must have a left child left-right rotate and update the height
{
    // Rotate between Node1 and Node2
    Node3->Left = SingleRotateWithRight(Node3->Left);
    //Rotate between Node3 and Node2
    return SingleRotateWithLeft(Node3);
}

AVLPTR DoubleRotateWithRight(AVLPTR Node1)//has a right child that has a left child right left rotation and update height
{
    /* Rotate between Node3 and Node2 */
    Node1->Right = SingleRotateWithLeft(Node1->Right);
    /* Rotate between Node1 and Node2 */
    return SingleRotateWithRight(Node1);
}

AVLPTR InsertAVL( char* X, AVLPTR T )
{
    FilterWord(X);
    if(X[0]=='\0')
        return T;
    if(T==NULL)
    {
        T=malloc(sizeof(struct AVLnode));
        if(T==NULL)
            printf("**MEMORY FULL!!**");
        else
        {
            strcpy(T->word,X);
            T->Height=0;
            T->Left=T->Right=NULL;
            T->Frequency=1;
            AvlCount++;
        }
    }
    else if(strcmp(X,T->word)<0)
    {
        T->Left=InsertAVL(X,T->Left);
        if(Height(T->Left)-Height(T->Right)==2){//balancing
            if (strcmp(X, T->word) < 0)
            {
                T=SingleRotateWithLeft(T);
            }
            else{
                T=DoubleRotateWithLeft(T);}}
    }
    else if(strcmp(X,T->word)>0)
    {
        T->Right=InsertAVL(X,T->Right);
        if(Height(T->Right)-Height(T->Left)==2){//balancing
            if (strcmp(X, T->word) > 0){
                T=SingleRotateWithRight(T);}
            else
            {
                T=DoubleRotateWithRight(T);
            }}
    }
    else
    {
        //already exists
        T->Frequency++;
    }


    T->Height=Max(Height(T->Left),Height(T->Right ))+1;

    return T;
}

int hash(char* word, int tableSize)
{
    unsigned int x= 0;
    while(*word!='\0')
    {
        x= (x<<5)+*word++;//times 5
    }
    return (x%tableSize);
}

HashPTR FindHash(char* word, HashPTR* hashTable, int tableSize, int* ind)
{
    FilterWord(word);
    if (word[0]=='\0')
    {
        printf("Invalid\n");
        return NULL;
    }
    int index=hash(word,tableSize);
    int hash2val=hash2(word, tableSize);
    int IndexCol=index;
    HashPTR Find=NULL;
    int i=1;
    while (hashTable[IndexCol]!=NULL)//if the first index it should have been in is empty then its not in the hash table  unless it has the special var
        //* that means there was collision!
    {
        if (strcmp(hashTable[IndexCol]->word,word)==0)
        {
            Find=hashTable[IndexCol];
            break;  // Exit the loop once the word is found
        }
        IndexCol=(index+i*hash2val)%tableSize;
        i++;
    }
    *ind=IndexCol;
    return Find;
}

int hash2(char* word,int size)
{
    //this will help make the indexing more random to avoid clustering
    unsigned int x=0;
    while (*word!='\0')
    {
        x=*word++;
    }
    int primeless=size-1;
    while(!isPrime(primeless))
        primeless--;
    return (primeless-(x%primeless));
}

void printHashTable(HashPTR* hashTable, int tableSize)
{
    printf("Hash Table:\n");
    printf("---------------------------------------------\n");
    printf("|  Index   |        Word        | Frequency |\n");
    printf("---------------------------------------------\n");
    for (int i=0; i<tableSize; i++)
    {
        if (hashTable[i]!=NULL&&hashTable[i]->word[0]!='\0')
        {
            printf("| %-8d | %-18s | %-9d |\n", i,hashTable[i]->word,hashTable[i]->frequency);
        }
        else
        {
            printf("| %-8d |                    |           |\n", i);
        }
    }
    printf("---------------------------------------------\n");
    printf("NOTE:We treat the cells that have (*) as empty cells but I printed them to show Collision Handling");
}

int MaxFreqAVL(AVLPTR T)
{
    if (T==NULL)
        return 0;
    int leftMax=MaxFreqAVL(T->Left);//its going to keep iterating the left side dividing it left right left right every time returning the max value
    int rightMax=MaxFreqAVL(T->Right);//it will check the node we are at with the max of the nodes of the left and right
    int currentMax=T->Frequency;
    if (leftMax>currentMax)
        currentMax=leftMax;
    if (rightMax>currentMax)
        currentMax=rightMax;

    return currentMax;
}

void MostFreqAVL(AVLPTR T,int maxFreq)
{
    if(T==NULL)
        return;
    if(T->Frequency==maxFreq)
    {
        printf("%s ", T->word);
    }
    MostFreqAVL(T->Left,maxFreq);
    MostFreqAVL(T->Right,maxFreq);
}
int FreqCountAVL(AVLPTR T,int count)
{
    if(T==NULL)
        return 0;
    if(T->Frequency==count)
    {
        return 1+FreqCountAVL(T->Left,count)+FreqCountAVL(T->Right,count);
    }
    else
        return FreqCountAVL(T->Left,count)+FreqCountAVL(T->Right,count);
}
void MostFreqHash(HashPTR* hashTable,int tableSize)
{
    int count=0;
    if(hashTable==NULL)
        return;
    int maxFreq=0;
    for(int i=0; i<tableSize; i++) //looking for the maximum frequency
    {
        if(hashTable[i]!=NULL)
        {
            if(hashTable[i]->frequency>maxFreq)
            {
                count=1;
                maxFreq=hashTable[i]->frequency;
            }
            else if(hashTable[i]->frequency==maxFreq)
                count++;
        }
    }
    printf("\n%d Most Frequent word(s) in the Hash with the Frequency %d:\n",count, maxFreq);
    for(int i=0; i<tableSize; i++) //print the words that have this max frequency
    {
        if(hashTable[i]!=NULL)
        {
            if(hashTable[i]->frequency==maxFreq)
            {
                printf("%s ",hashTable[i]->word);
            }
        }
    }
    printf("\n");
}

int ThresholdAVL(AVLPTR T, int threshold)
{
    if (T==NULL)
        return 0;
//go through the tree in any order here we are doing it in in order and everytime print if the freq is higher than the threshold
    if(T->Frequency>threshold&&T->Frequency>0)
    {
        printf("%s: %d\n",T->word,T->Frequency);
        return 1+ThresholdAVL(T->Left,threshold)+ThresholdAVL(T->Right,threshold);
    }
    else
        return ThresholdAVL(T->Left,threshold)+ThresholdAVL(T->Right,threshold);
}

int ThresholdHash(HashPTR* hashTable, int tableSize, int threshold)
{
    int count=0;
    for(int i=0; i<tableSize; i++)
    {
        if(hashTable[i]!=NULL)
        {
            if(hashTable[i]->frequency>threshold&&hashTable[i]->frequency>0)
            {
                count++;
                printf("%s: %d\n",hashTable[i]->word,hashTable[i]->frequency);
            }
        }
    }
    return count;
}
int FreqCountHash(HashPTR* hashTable, int num)
{
    int count=0;
    for(int i=0; i<TableSize; i++)
    {
        if(hashTable[i]!=NULL)
        {
            if(hashTable[i]->frequency==num)
            {
                count++;
            }
        }
    }
    return count;
}
int isPrime(int n)
{
    if(n<=2)
    {
        return 0;
    }
    for(int i=2; i<=n/2; i++)
    {
        if(n%i==0)
        {
            return 0;
        }
    }
    return 1;
}

AVLPTR DeleteAVL(char* X,AVLPTR T)
{
    FilterWord(X);
    if(X[0]=='\0')
        return T;

    if(T==NULL)
    {
        printf("Word Does not Exist!!");
        return NULL;
    }
    //this will search for the word while maintaining the balance after deleting the word
    else if(strcmp(X, T->word)<0 )
    {
        T->Left=DeleteAVL(X,T->Left);
        if(Height(T->Left)-Height(T->Right )==2){//check balance
            if(strcmp(X, T->word)<0){
                T=SingleRotateWithLeft(T);}
            else{
                T =DoubleRotateWithLeft(T);}}
    }
    else if(strcmp(X, T->word)>0)
    {
        T->Right =DeleteAVL( X, T->Right );
        if(Height(T->Right)-Height( T->Left)== 2){
            if(strcmp(X, T->word)>0)
                T=SingleRotateWithRight(T);
            else
                T=DoubleRotateWithRight(T );
    }}
    else if (T->Left!=NULL&&T->Right!= NULL)
    {
        if(T->Frequency>1)  //word is repeated more than once
        {
            printf("The Frequency is %d, Would you like to update the frequency(1) or Remove the Full word(0):\n",T->Frequency);
            int choice=-1;
            scanf("%d",&choice);
            if (choice==1)
            {
                --(T->Frequency);
                return T;
            }
        }
        AVLPTR temp=FindMin(T->Right);//will find the minimum on the right of the node we want to DeleteAVL and put it in the place
        strcpy(T->word,temp->word);//of what we want to DeleteAVL
        T->Frequency=temp->Frequency; // Update frequency
        T->Right = DeleteAVL(T->word,T->Right);//DeleteAVL the right (temp)
        if(Height(T->Left)-Height(T->Right)== 2)//balance
        {
            if (Height(T->Left->Right)<=Height(T->Left->Left))
                T=SingleRotateWithLeft(T);
            else
                T=DoubleRotateWithLeft(T);
        }
    }
    else
    {
        if(T->Frequency>1)  //word is repeated more than once
        {
            printf("The Frequency is %d, Would you like to update the frequency(1) or Remove the Full word(0):\n",T->Frequency);
            int choice=-1;
            scanf("%d", &choice);
            if (choice==1)
            {
                --(T->Frequency);
                return T;
            }
        }
        //DeleteAVL one or no nodes
        AVLPTR temp=T;
        if (T->Left==NULL)//left or no
            T=T->Right;//make T the right
        else if(T->Right==NULL)//right node
            T=T->Left;
        free(temp);
        AvlCount--;
    }
    if (T!=NULL)

        T->Height = Max( Height( T->Left ), Height( T->Right ) ) + 1;

    return T;
}

AVLPTR FindMin( AVLPTR T )
{
    if(T==NULL)
        return NULL;
    else if( T->Left ==NULL)
        return T;
    else
        return FindMin(T->Left );
}

AVLPTR Find( char* X, AVLPTR T )
{
    strlwr(X);

    if(T ==NULL )
        return NULL;
    if(strcmp(X, T->word)<0)
        return Find( X, T->Left );
    else if( strcmp(X, T->word)>0)
        return Find(X, T->Right );
    else
        return T;
}
void DeleteHashTable(HashPTR* hashTable, int tableSize) {
    for(int i = 0; i < tableSize; i++) {
        if (hashTable[i] != NULL) {
            free(hashTable[i]); //free the nodes in the full cell
        }
    }

    free(hashTable); // Free the memory we saved for the table of pointers
    printf("Hash Table Deleted Successfully!\n");
    TableSize=13;//reinitialize the table size
}

