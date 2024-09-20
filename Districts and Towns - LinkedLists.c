//Heba Mustafa 1221916
//Section 3
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Node
typedef struct District
{
    struct District* next;
    struct District* prev;
    struct Town* townsHead;
    struct Town* townsTail;
    char DistrictName[50];
} District;

typedef struct Town
{
    struct Town* prev;
    struct Town* next;
    int population;
    char TownName[50];
} Town;
//List
struct DistrictLinkedList
{
    District* head;
    District* tail;
};
//Function Prototypes
District* createDistrictNode( char* name);
District* searchDistrict(struct DistrictLinkedList* list,char* Newname);
void InsertDistrict(struct DistrictLinkedList* list,char* name);
Town* searchTown(District* district, char* Newname);
void InsertTown(struct DistrictLinkedList* list,char* DistrictName,char* TownName,int population);
void DeleteTown(struct DistrictLinkedList* list,char* DistrictName,char* TownName);
void DeleteDistrict(struct DistrictLinkedList* list,char* DistrictName);
void TrimString(char *str);
void LoadFile(struct DistrictLinkedList* list);
int getMaxStringLength(struct DistrictLinkedList* list);
void radixSort(struct DistrictLinkedList* list);
struct DistrictLinkedList DuplicateUnsorted(struct DistrictLinkedList* list);
void PrintList(struct DistrictLinkedList* list);
void SaveToOutputFile(struct DistrictLinkedList* list);
void printDistrictsTotalPopulation(struct DistrictLinkedList* list);
int getDistrictPopulation(District* district);
void changePopulation(struct DistrictLinkedList* list,char* DistrictName,char* TownName,int newPopulation);
void CalculatePalestinesPopulation(struct DistrictLinkedList* list);
void sortTownsByPopulation(struct DistrictLinkedList* list);
Town* merge(Town* left,Town* right) ;
Town* mergeSort(Town* head);



int main()
{
    struct DistrictLinkedList list= {NULL, NULL};
    struct DistrictLinkedList newList= {NULL,NULL};
    int choice=0;
    char Distname[50];
    char TName[50];
    int population=0;


    printf("*******************PALESTINE'S DISTRICTS AND TOWNS***************************\n\n");
    while (choice != 14)
    {
        printf("\n\n-------------- MENU: Choose One of the Following operations -------------- \n");
        printf("1. Load an input file\n");
        printf("2. Print the loaded information before sorting\n");
        printf("3. Sort the districts alphabetically\n");
        printf("4. Sort the towns for each district based on population\n");
        printf("5. Print the sorted information\n");
        printf("6. Add a new district\n");
        printf("7. Add a new town to a certain district\n");
        printf("8. Delete a town from a specific district\n");
        printf("9. Delete a complete district\n");
        printf("10. Calculate the population of Palestine, the max and min town population\n");
        printf("11. Print the districts and their total population\n");
        printf("12. Change the population of a town\n");
        printf("13. Save to output file\n");
        printf("14. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("----------------------------------------------------------------------------\n\n");

        switch (choice)
        {
        case 1:
            LoadFile(&list);
            newList=DuplicateUnsorted(&list);
            break;
        case 2:
            PrintList(&newList);
            break;
        case 3:
            if(!list.head)
            {
                printf("**Empty List**\n");

            }
            else
            {
                radixSort(&list);
                printf("\n--Successfully Sorted Districts in Alphabetical Order--\n");
            }
            break;
        case 4:
            if(!list.head)
            {
                printf("**Empty List**\n");
            }
            else
            {
                sortTownsByPopulation(&list);
                printf("\n--Successfully Sorted Towns by Population--\n");
            }  // Sort the towns for each district based on population ***MERGE SORT FOR TIME COMPLEXITY
            break;
        case 5:
            if(!list.head)
            {
                printf("**Empty List**\n");
                break;
            }
            radixSort(&list);
            sortTownsByPopulation(&list);
            PrintList(&list);  // Print the sorted information
            break;

        case 6://Insert DIstrict+Sort
            printf("Enter the New Districts Name: ");
            scanf(" %[^\n]", Distname);
            if(searchDistrict(&list,Distname)!=NULL)
                printf("\n**Already Exists!**\n");
            else
            {
                InsertDistrict(&list,Distname);
                radixSort(&list);
                printf("\n--Inserted Successfully--\n");
            }
            break;
        case 7://InsertTown
            printf("Enter the Districts Name: ");
            scanf(" %[^\n]", Distname);
            if(searchDistrict(&list,Distname)==NULL)
                printf("\n**District Does Not Exist!**\n");
            else
            {
                printf("Enter the Town name: ");
                scanf(" %[^\n]", TName);
                printf("Enter towns population: ");
                scanf("%d",&population);
                InsertTown(&list,Distname,TName,population);
            }
            break;
        case 8://DeleteTown
            printf("Enter the Districts Name: ");
            scanf(" %[^\n]", Distname);
            printf("Enter the Town name: ");
            scanf(" %[^\n]", TName);
            DeleteTown(&list,Distname,TName);
            break;
        case 9://Delete DIstrict
            printf("Enter the Districts Name: ");
            scanf(" %[^\n]", Distname);
            DeleteDistrict(&list,Distname ); // Delete a complete district
            break;
        case 10:
            CalculatePalestinesPopulation(&list); // Calculate the population of Palestine, the max and min town population
            break;
        case 11:
            printDistrictsTotalPopulation(&list); // Print the districts and their total population
            break;
        case 12:
            printf("Enter the Districts Name: ");
            scanf(" %[^\n]", Distname);
            if(searchDistrict(&list,Distname)==NULL)
                printf("\n**District Does Not Exist!**\n");
            else
            {
                printf("Enter the Town name: ");
                scanf(" %[^\n]", TName);
                printf("Enter the towns new population: ");
                scanf("%d",&population);
                changePopulation(&list,Distname, TName, population);
            } // Change the population of a town
            break;
        case 13:
            SaveToOutputFile(&list); // Save to output file
            break;
        case 14:
            printf("Exit Success");
            break;
        default:
            printf("Invalid Option");
            break;
        }
    }
    return 0;
}
//Functions
District* createDistrictNode(char* name)
{
    TrimString(name);
    District* newNode=(District*)malloc(sizeof(District));
    if (!newNode)
    {
        printf("**Memory Full!**\n");
        exit(0);
    }
    strcpy(newNode->DistrictName, name);
    newNode->next=NULL;
    newNode->prev=NULL;
    newNode->townsHead=NULL;
    return newNode;
}
District* searchDistrict(struct DistrictLinkedList* list,char* Newname)
{
    TrimString(Newname);
    District* head=list->head;
    District* tail=list->tail;

    while (head!=NULL &&head!=tail &&head->prev!= tail)
    {
        if (strcasecmp(head->DistrictName,Newname)==0) //found
        {
            return head;
        }
        else if(strcasecmp(tail->DistrictName,Newname)==0)
            return tail;//found
        head=head->next;
        tail=tail->prev;
    }
    if(head!=NULL&&strcasecmp(head->DistrictName,Newname)==0)//we check once more because it stops at the middle odd
        return head;
    else
        return NULL;
}

void InsertDistrict(struct DistrictLinkedList* list,char* name)
{
    if(searchDistrict(list,name)!=NULL)
        return;
    District* newNode=createDistrictNode(name);
    if(newNode==NULL)
        return;
    if(!list->head)
    {
        list->head=newNode;
        list->tail= newNode;
    }
    else
    {
        newNode->prev=list->tail;
        list->tail-> next= newNode;
        list-> tail=newNode;
    }
}
Town* searchTown(District* district,char* Newname) //i used strcasecmp which is not case sensitive so if the user enters lower rather than capital
{
    TrimString(Newname);//it wont say it doesnt exist
    Town* head=district->townsHead;
    Town* tail=district->townsTail;
    while ( head!=NULL&&head !=tail &&head->prev!= tail)
    {
        if (strcasecmp(head->TownName,Newname)==0) //found
        {
            return head;
        }
        else if(strcasecmp(tail->TownName,Newname)==0)
            return tail;//found
        head=head->next;
        tail=tail->prev;
    }
    if (head!=NULL && strcasecmp(head->TownName,Newname)==0)//odd middle
        return head;//Basically here the head and tail will be pointing at this node
    else
        return NULL;
}
void InsertTown(struct DistrictLinkedList* list,char* DistrictName,char* TownName,int population)
{
    District* district=searchDistrict(list,DistrictName);
    if (district==NULL)
    {
        printf("**District Does not Exist!**\n");
        return;
    }
    Town* town=searchTown(district,TownName);
    if(town!=NULL)
    {
        printf("**This town already Exists**\n");
        return;
    }
    // Create a new town node
    struct Town* newTown=(struct Town*)malloc(sizeof(struct Town));
    if (newTown==NULL)
    {
        printf("No Memory\n");
        return;
    }
    strcpy(newTown->TownName,TownName);
    newTown->population=population;
    newTown->next=NULL;
    newTown->prev= NULL;
    // If empty the pointer in the district will point at it
    if (district->townsHead==NULL)
    {
        district->townsHead=newTown;
        district->townsTail=newTown;
    }
    else
    {
        newTown->next= district->townsHead;//Update the pointers
        district->townsHead->prev= newTown;
        district->townsHead= newTown;

    }

}
void DeleteTown(struct DistrictLinkedList* list,char* DistrictName,char* TownName)
{
    District* district=searchDistrict(list,DistrictName);
    if (!district)
    {
        printf("**District not found!**\n");
        return;
    }
    Town* town=searchTown(district,TownName);
    if(!town)
    {
        printf("**Town not found in %s!**\n",DistrictName);
        return;
    }
    if(district->townsHead==town) //if we are deleting the firstnode
    {
        district->townsHead=town->next;
        if(town->next) //If it has a next the next will be the head and the previous will be null
        {
            town->next->prev=NULL;
        }
    }
    else
    {
        if (town->prev)
        {
            town->prev->next=town->next;
        }
        if(town->next)
            town->next->prev=town->prev;
    }
    if(town==district->townsTail)
    {
        district->townsTail=town->prev;
    }
    town->next=NULL;
    town->prev=NULL;
    free(town);
    printf("\n--Town Deleted Successfully!--\n");
}
void DeleteDistrict(struct DistrictLinkedList* list,char* DistrictName)
{
    TrimString(DistrictName);
    District* district =searchDistrict(list,DistrictName);
    if(!district)
    {
        printf("**District not found!**\n");
        return;
    }
    Town* townHead=district->townsHead;
    Town* townTail=district->townsTail;
    //delete the towns (MAKES THE TOWN LIST EMPTY)
    while(townHead!=NULL&&townHead!=townTail)
    {
        if (townHead->next!=NULL)
        {
            district->townsHead=townHead->next;
            townHead->next->prev=NULL;
            townHead->next=NULL;
            free(townHead);
        }
        if(townTail->prev !=NULL)
        {
            district->townsTail= townTail->prev;
            townTail->prev->next =NULL;
            townTail->prev= NULL;
            free(townTail);
        }
        townHead =district->townsHead ;
        townTail= district->townsTail;
    }
    if(townHead!=NULL) //This will handle the last node when the head and tail point to the same place(When the head next is null and the tail previous is null)
    {
        district->townsHead=NULL;
        townHead->prev =NULL;
        free(townHead) ;
    }
    // Remove the district from the linked list
    if(list->head==district)
    {
        list->head=district->next;
        if(list->head)
            list->head->prev=NULL;
    }
    if(list->tail==district)
    {
        list->tail=district->prev;
        if(list->tail)
            list->tail->next=NULL;
    }
    else
    {
        if(district->prev)
        {
            district->prev->next=district->next;
        }
        if (district->next)
        {
            district->next->prev=district->prev;
        }
    }
    district->prev=NULL;// Set prev and next pointers to NULL before freeing
    district->next=NULL;
    free(district);
    printf("\n--District Deleted Successfully--\n");
}
// This function will remove the extra whitespaces added before and after each name,so we can effectively
//compare if we have this name or not
void TrimString(char *str) // This function will remove the extra whitespaces added before and after each name,so we can effectively compare if we have this name
{
    char *ptr=str;// Remove leading spaces
    while(*ptr==' ')
    {
        ++ptr;
    }
    memmove(str,ptr,strlen(ptr)+1); // Move the remaining string to the beginning +1 is to include the Null terminator
    // Remove the spaces after
    ptr =str+strlen(str)-1;
    while(ptr>=str&&*ptr ==' ')
    {
        *ptr-- = '\0';
    }
}
void LoadFile(struct DistrictLinkedList* list)
{
    FILE *file= fopen("districts.txt", "r");
    if(file ==NULL)
    {
        printf("Error opening file\n");
        return;
    }
    char line[50];
    char DistName[30],TName[30],populationS[30];

    while (fgets(line,sizeof(line), file))
    {
        strcpy(DistName,strtok(line, "|"));
        strcpy(TName,strtok(NULL, "|"));
        strcpy(populationS, strtok(NULL, "|"));
        int Population1=atoi(populationS);// Convert population string to integer
//printf("District: %s      Town: %s        Population: %d\n", DistName, TName, Population1);
        InsertDistrict(list,DistName);
        InsertTown(list,DistName,TName,Population1);
    }
    fclose(file);
    printf("\n--File Loaded Successfully--\n");
}

int getMaxStringLength(struct DistrictLinkedList* list)
{
    int maxLength =0;
    struct District* head=list->head;
    struct District* tail=list->tail;
    while(head!=tail&&head->prev!=tail)
    {
        int headLength=strlen(head->DistrictName);
        int tailLength=strlen(tail->DistrictName);
        if(headLength>maxLength)
            maxLength= headLength;
        if(tailLength>maxLength)
            maxLength=tailLength;
        head= head->next;
        tail= tail->prev;
        if(head==tail)
        {
            int midtown = strlen(head->DistrictName);
            if (midtown>maxLength)
            {
                maxLength=midtown;
            }
        }
    }
    return maxLength;
}


void radixSort(struct DistrictLinkedList* list)
{
    int max=getMaxStringLength(list);
    struct District* pointer;
    struct District* output=NULL;
    for(int i=max-1; i>-1; --i) //greater than or equal to zero for time complexity we put greater than -1
    {//let the max be a constsnt m
        struct District* alphabet[27]= {NULL}; // 0 for non-alphabetic characters, 1-26 for alphabetic characters
        output=NULL;
        pointer=list->head;
        while (pointer)
        {// the number of elements n
            char c=pointer->DistrictName[i];
            int index = 0; //Here what i will do is see if its an alphabet and if it is assign it to the
            if(isalpha(c)) //array from index 1-26 1 being a and 26 being z
            {
                index=tolower(c)-'a'+1; // index zero is anything else(Spaces nulls etc) this way there is no need to make it longer
            }//we dont need to make the strings that are not the max length longer since here it will be handled
            struct District* temp=pointer->next;// Here we will start inserting each word into the array at the correct location
            pointer->next =alphabet[index];//first it will point at the place it will go if there is an existing node it will become the head
            alphabet[index]=pointer;//then the index will point at it
            pointer =temp;//finally we make the pointer point to the next node in the linked list
        }
        for(int j= 26; j>=0; --j) // this will start putting the list back together
        {
            District* ptr= alphabet[j];
            while (ptr)
            {
                District* temp=ptr->next;//save the next node
                ptr->next=output;//makes it the head of the output(cause we are starting from the end up we add to the head
                ptr->prev= NULL; // Set the prev ptr of the current node to NULL since it's now the head
                if (output )
                {
                    output-> prev = ptr;
                }
                output= ptr;
                ptr= temp;
            }
        }
        list->head= output;
        list->tail=output;
        while(list->tail&&list->tail->next)
        {
            list->tail=list->tail->next ;
        }
    }
}

struct DistrictLinkedList DuplicateUnsorted(struct DistrictLinkedList* list)
{
    struct DistrictLinkedList newList= {NULL,NULL};
    District* DistrictPos=list->head;
    while(DistrictPos!=NULL)
    {
        InsertDistrict(&newList,DistrictPos->DistrictName);

        struct Town* TownPos =DistrictPos->townsHead;
        while (TownPos!= NULL)
        {
            InsertTown(&newList, DistrictPos->DistrictName, TownPos->TownName, TownPos->population);
            TownPos= TownPos->next ;
        }
        DistrictPos=DistrictPos->next;
    }
    return newList;
}

void PrintList(struct DistrictLinkedList* list)
{
    if(!list->head)
    {
        printf("**Empty List**\n");
        return;
    }
    struct District* pointer= list->head ;
    while (pointer)
    {
        Town* town=pointer->townsHead;
        if(!town)
            printf("%s |has no Towns|\n",pointer->DistrictName);
        else
            while(town)
            {
                printf("%s | %s | %d\n", pointer->DistrictName,town->TownName,town->population) ;
                town=town->next;
            }
        pointer=pointer->next;
    }
}
void SaveToOutputFile(struct DistrictLinkedList* list)
{
    FILE* file=fopen("sorted_districts.txt","w");
    if(!file)
    {
        printf("Error opening file for writing\n");
        return;
    }
    District* DistrictPos=list->head;
    while(DistrictPos!=NULL)
    {
        fprintf(file,"%s District, Population = %d\n",DistrictPos->DistrictName,getDistrictPopulation(DistrictPos));

        Town* TownPos=DistrictPos->townsHead ;
        while(TownPos) //current town is not NULL
        {
            fprintf(file, "%s, %d\n", TownPos->TownName,TownPos->population);
            TownPos=TownPos->next;
        }
        fprintf(file,"\n") ; // Add a newline to separate districts
        DistrictPos=DistrictPos->next;
    }
    fclose(file);
    printf("\n--Successfully saved to Output File--\n");
}
void printDistrictsTotalPopulation(struct DistrictLinkedList* list)
{
    // Print the district information with total population
    District* DistrictPos=list->head;
    if(!DistrictPos)
    {
        printf("\n**Empty List**\n");
        return;
    }
    while(DistrictPos!=NULL)
    {
        printf("%s District, Population = %d\n", DistrictPos->DistrictName,getDistrictPopulation(DistrictPos)) ;
        DistrictPos=DistrictPos->next;
    }
}
int getDistrictPopulation(District* district)
{
    int totalPopulation=0 ;
    Town* LeftTown= district->townsHead;
    Town* RightTown= district->townsTail;
    if(LeftTown==NULL)
        return 0;
    while(LeftTown!=RightTown&&LeftTown->prev!=RightTown)
    {
        totalPopulation+= LeftTown->population;
        totalPopulation+=RightTown->population;
        LeftTown= LeftTown->next;
        RightTown=RightTown->prev;
    }
    if(LeftTown== RightTown)
    {
        totalPopulation+=LeftTown->population;
    }
    return totalPopulation;
}
void CalculatePalestinesPopulation(struct DistrictLinkedList* list)
{
    if(!list->head)
    {
        printf("**Empty List**");
        return;
    }
    int totalPopulation=0;
    int maxPopulation =0;
    int minPopulation=1000000000; // initializing with a large value
    char MinTown[50], MaxTown[50];
    char MinTownDistrict[50], MaxTownDistrict[50];
    District* headDistrict=list->head;
    District* tailDistrict=list->tail;
    Town* headTown, *tailTown;
    while(headDistrict!=tailDistrict&&headDistrict->prev!=tailDistrict)
    {
        headTown=headDistrict->townsHead;
        while(headTown!=NULL)
        {
            totalPopulation+=headTown->population;
            if(headTown->population>maxPopulation)
            {
                strcpy(MaxTown,headTown->TownName);
                strcpy(MaxTownDistrict,headDistrict->DistrictName);
                maxPopulation=headTown->population;
            }
            if(headTown->population<minPopulation)
            {
                strcpy(MinTown,headTown->TownName);
                strcpy(MinTownDistrict,headDistrict->DistrictName);
                minPopulation=headTown->population;
            }
            headTown=headTown->next;
        }
        tailTown=tailDistrict->townsHead;
        while(tailTown!=NULL)
        {
            totalPopulation+=tailTown->population;
            if (tailTown->population>maxPopulation)
            {
                strcpy(MaxTown,tailTown->TownName);
                strcpy(MaxTownDistrict,tailDistrict->DistrictName);
                maxPopulation=tailTown->population;
            }
            if(tailTown->population<minPopulation)
            {
                strcpy(MinTown,tailTown->TownName);
                strcpy(MinTownDistrict,tailDistrict-> DistrictName);
                minPopulation=tailTown->population;
            }
            tailTown=tailTown->next;
        }
        headDistrict=headDistrict->next;
        tailDistrict=tailDistrict->prev;
    }
    if(headDistrict==tailDistrict)
    {
        Town* town=headDistrict->townsHead;
        while(town!= NULL)
        {
            totalPopulation+=town->population;
            if(town->population>maxPopulation)
            {
                strcpy(MaxTown,town->TownName);
                strcpy(MaxTownDistrict,headDistrict->DistrictName);
                maxPopulation=town->population;
            }
            if(town->population<minPopulation)
            {
                strcpy(MinTown,town->TownName);
                strcpy(MinTownDistrict,headDistrict->DistrictName);
                minPopulation =town->population;
            }
            town= town->next;
        }
    }
    printf("----Total population of Palestine: %d----  \n\n", totalPopulation);
    printf("--Maximum town: %s   |   is in District: %s   |    population: %d--\n", MaxTown,MaxTownDistrict,maxPopulation);
    printf("--Minimum town: %s   |   is in District: %s   |    population: %d--\n", MinTown,MinTownDistrict,minPopulation);
}
void changePopulation(struct DistrictLinkedList* list,char* DistrictName,char* TownName,int newPopulation)
{
    District* district=searchDistrict(list, DistrictName);
    if(district==NULL)
    {
        printf("**District not found!**\n");
        return;
    }
    Town* town=searchTown(district,TownName);
    if(town==NULL)
    {
        printf("**Town not found in %s!**\n", DistrictName);
        return;
    }
    town->population=newPopulation;
    printf("\n--Population of town %s in district %s updated to %d--\n",TownName,DistrictName,newPopulation);
}
//To sort the towns i will use a MergeSort O(nlogn) **Best Option for time Complexity**
//The list is divided in half log n times
Town* merge(Town* left,Town* right)
{
    if(left==NULL) //cases were there is nothing to merge we only have one list(base cases)
        return right;
    if(right==NULL)
        return left;
    Town* HeadMerge = NULL;
    if(left->population<=right->population)
    {
        HeadMerge=left;//if the left is less assign the left to the head(the head of the left is less than the right (we know that the head has the smallest value
        HeadMerge->next= merge(left->next,right);//recursive function so we can merge all the other nodes in the left with the right
        HeadMerge->next->prev= HeadMerge;
    }
    else
    {
        HeadMerge= right;
        HeadMerge->next= merge(left,right->next);
        HeadMerge->next->prev= HeadMerge;//keeping the doubly structure
    }
    return HeadMerge;
}
Town* mergeSort(Town* head)
{
    //if the list is empty or contains only one element, it is already sorted
    if(head==NULL||head->next==NULL)//the base case
        return head;
    // Split the list into two halves
    Town* One=head;
    Town* two=head->next;
    while(two!=NULL&&two->next!=NULL)
    {
        One=One->next;
        two=two->next->next;
    }
    Town* right=One->next;
    One->next=NULL;
    // SOrt each half by using recursions
    Town* leftSorted= mergeSort(head);
    Town* rightSorted= mergeSort(right);
    //Merge the halves together
    return merge(leftSorted,rightSorted) ;
}
void sortTownsByPopulation(struct DistrictLinkedList* list)
{
    District* DistrictPos=list->head;
    while(DistrictPos!=NULL)
    {
        DistrictPos->townsHead=mergeSort(DistrictPos->townsHead);
        DistrictPos=DistrictPos->next;
    }
}
