#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>


typedef struct book
{
    int quantity;
    int cost;
    int sell;
    int shelf;
    int id;
    char Name[50];
    char Author[50];
}BOOK;


// structure for each book and the quantity of book present    ()
typedef struct bookStock
{
    int bookQuantity;
    int bookCP;
    int bookSP;
    int bookId;
    int shelfNo;
    char bookName[50];
    char bookAuthor[50];
    int factor;
    struct bookStock *llink;
    struct bookStock *rlink;
}STOCK;

// global reference book stock for accessing to all the function
STOCK* startBook = NULL;


typedef struct Category
{
    char name[50];
    STOCK* root;
    struct Category *left;
    struct Category *right;
    int factor;
   
}CATEGORY;

CATEGORY *categoryRoot = NULL;

// structure for purchase record   (QUEUE)
typedef struct bookNode
{
    char bookName[50];
    int bookID;
    int quantity;
    int sell;
    int profit;
    int total;
    struct bookNode *next;
    struct bookNode *prev;
}NODE;

//global reference for purchase node
NODE *top = NULL;

// to put each purchase in the queue
void push(STOCK * temp, int n)
{
    NODE *newNode;
    newNode =(NODE*)malloc(sizeof(NODE));
    strcpy(newNode->bookName,temp->bookName);
    newNode->bookID = temp->bookId;
    newNode->quantity = n;
    newNode->sell = temp->bookSP;
    newNode->total = n*(temp->bookSP);
    newNode->profit =(n*(temp->bookSP - temp->bookCP));
    if(top == NULL)
    {
        top = newNode;
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    else
    {
        newNode->prev = top;
        newNode->next = NULL;
        top->next = newNode;
        top = newNode;
    }
    return;
}

// to display the purchase record
void display_record()
{
    NODE *temp;
    NODE *nodeTemp;
    temp = top;
    if(top == NULL)
    {
        printf("\nNo Record Found\n");
        return;
    }
    else
    {
        printf("\nID    BOOKS     QUANTITY     PRICE      TOTAL     PROFIT\n");
        while(temp->prev != NULL)
        {
            printf("\n%d   %s    %d    %d     %d    %d\n",temp->bookID,temp->bookName,temp->quantity,temp->sell,temp->total,temp->profit);
            nodeTemp = temp;
            temp = temp->prev;
            free(nodeTemp);
        }
        printf("\n%d   %s   %d    %d    %d    %d\n",temp->bookID,temp->bookName,temp->quantity,temp->sell,temp->total,temp->profit);
        free(temp);
        return;
    }
   
}

int max(int a, int b)
{
    if( a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int height(STOCK* head)
{
    if(head == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + max(height(head ->llink),height(head->rlink));
    }
}


int balence(STOCK* head)
{
    if(head == NULL)
    {
        return 0;
    }
    else
    {
        return (height(head->llink) - height(head->rlink));
    }
}


STOCK* putInOrder(STOCK* head, BOOK* node)
{
   if(head->factor == 2)
   {
     if(head->llink->bookId > node->id)
     {
        STOCK* Y=head->llink->rlink;
        STOCK* X=head->llink;
        X->rlink=head;
        head->llink=Y;
        X->factor=balence(X);
        head->factor=balence(head);
        return X;
     }
     else if(head->llink->bookId < node->id)
     {
        // not working
        STOCK* Y=head->llink->rlink;
        STOCK* X=head->llink;
        STOCK* K=Y->llink;
        STOCK* L=Y->rlink;
        X->rlink=K;
        head->llink=L;
        Y->llink=X;
        Y->rlink=head;

        Y->factor=balence(Y);
        head->factor=balence(head);
        X->factor=balence(X);
        return Y;        
     }
   }
   else if(head->factor == -2)
   {
     if(head->rlink->bookId < node->id)
     {
        STOCK* Y=head->rlink->llink;
        STOCK* X=head->rlink;
        X->llink=head;
        head->rlink=Y;
        X->factor=balence(X);
        head->factor=balence(head);
        return X;
     }
     else if(head->rlink->bookId > node->id)
     { 
        STOCK* Y=head->rlink->llink;
        STOCK* X=head->rlink;
        STOCK* K=Y->rlink;
        STOCK* L=Y->llink;
        X->llink=K;
        head->rlink=L;
        Y->rlink=X;
        Y->llink=head;

        Y->factor=balence(Y);
        head->factor=balence(head);
        X->factor=balence(X);
        return Y;
     }
   }
}


STOCK* insertNode(STOCK* head, BOOK* node)
{
    if(head == NULL)
    {
        STOCK* newNode = (STOCK*)malloc(sizeof(STOCK));
        newNode->bookId = node->id;
        newNode->bookCP = node->cost;
        newNode->bookSP = node->sell;
        newNode->bookQuantity = node->quantity;
        newNode->shelfNo = node->shelf;
        strcpy(newNode->bookName,node->Name);
        strcpy(newNode->bookAuthor,node->Author);
        newNode->llink = NULL;
        newNode->rlink = NULL;
        return newNode;
    }
    else
    {
        if( node->id < head->bookId)
        {
            head->llink = insertNode(head->llink,node);
            head->factor = balence(head);
            if(head->factor == 2 || head->factor == -2)
            {
                head = putInOrder(head,node);
            }
        }
        else if(node->id > head->bookId)
        {
            head->rlink = insertNode(head->rlink,node);
            head->factor = balence(head);
            if(head->factor == 2 || head->factor == -2)
            {
                head = putInOrder(head,node);
            }
        }
        else
        {
            printf("duplicate\n");
        }
        return head;
    }
    

}


// linked list insert of each book in book list 
void createBook()
{
    char name[50];
    char author[50];
    int number;
    int cost;
    int sell;
    int id;
    int shelf;
    printf("\nEnter Book ID : ");
    scanf("%d",&id);
    printf("\nEnter Book Name : ");
    scanf("%s",name);
    printf("\nEnter Author Name : ");
    scanf("%s",author);
    printf("\nEnter Shelf Number : ");
    scanf("%d",&shelf);
    printf("\nEnter Cost Price of book : ");
    scanf("%d",&cost);
    printf("\nEnter Selling Price of book : ");
    scanf("%d",&sell);
    printf("\nEnter the number of book : ");
    scanf("%d",&number);

    BOOK book1;
    book1.id = id;
    book1.cost = cost;
    book1.quantity = number;
    book1.shelf = shelf;
    book1.sell = sell;
    strcpy(book1.Author,author);
    strcpy(book1.Name,name);
    startBook = insertNode(startBook,&book1);
    
}

void displayCustomer(STOCK* head)
{
    if(head!=NULL)
    {
        displayCustomer(head->llink);
        printf("\n%d         %s       %s      %d        %d      %d\n",head->bookId,head->bookName,head->bookAuthor,head->bookQuantity,head->bookSP,head->shelfNo);
        displayCustomer(head->rlink);
    }
}


void displayAdmin(STOCK* head)
{
    if(head!=NULL)
    {
        displayAdmin(head->llink);
        printf("\n%d         %s       %s      %d        %d      %d\n",head->bookId,head->bookName,head->bookAuthor,head->bookQuantity,head->bookCP,head->shelfNo);
        displayAdmin(head->rlink);
    }
}


// it will insert the book list from bookList.csv to the linked list
// so that initially the book store is not empty
void addFileBook()
{
    char name[50];
    char author[50];
    int number;
    int cost;
    int sell;
    int id;
    int shelf;

    FILE* fp = fopen("bookList.csv","r");
    if(!fp)
    {
        printf("Cant open file\n");
    }
    else
    {
        char buffer[1024];
        int row = 0;
        int column = 0;

        while(fgets(buffer,1024,fp))
        {
            column = 0;
            row++;

            if(row == 1)
            {
                continue;
            }

            char* value = strtok(buffer,", ");

            while(value)
            {
                if(column == 0)
                {
                    id = atoi(value);
                }

                if(column == 1)
                {
                    strcpy(name,value);
                }

                if(column == 2)
                {
                    strcpy(author,value);
                }

                if( column == 3)
                {
                     number= atoi(value);
                }

                if(column == 4)
                {
                     cost = atoi(value);  
                }

                if(column == 5)
                {
                     sell = atoi(value);  
                }

                if(column == 6)
                {
                     shelf = atoi(value);  
                }
                value = strtok(NULL,", ");
                column++;
            }

                BOOK book1;
                book1.id = id;
                book1.cost = cost;
                book1.quantity = number;
                book1.shelf = shelf;
                book1.sell = sell;
                strcpy(book1.Author,author);
                strcpy(book1.Name,name);
                startBook = insertNode(startBook,&book1);
        }
        fclose(fp);
    }
}


STOCK* search(STOCK* root, int key ) 
{
    if (root == NULL || root->bookId == key)
        return root;

    if (key < root->bookId)
        return search(root->llink, key);
    else
        return search(root->rlink, key);
}


STOCK* searchName(STOCK* root , char *name)
{
    if (root == NULL || !(strcmp(root->bookName,name)) )
    {
        return root;
    }

    if(strcmp(root->bookName,name))
    {
        return searchName(root->llink, name);
    }
    else
    {
        return searchName(root->rlink, name);
    }
}



// search for a book based on id and name of book
STOCK* searchBook()
{
    STOCK* temp;
    char name[50];
    int id;
    int choice = 0;
    printf("\n1. Search on Id\n");
    printf("\n2. Search on Book Name\n\n");
    printf("=> ");
    scanf("%d",&choice);
   if(choice == 2)
   {
        printf("\nEnter the book name : ");
        scanf("%s",name);
        temp = searchName(startBook,name);
   }

   if(choice == 1)
   {
       
        printf("\nEnter the Id of Book : ");
        scanf("%d",&id);
        temp = search(startBook,id);
   }

   return temp;
   
}


// display book for customer
void displayBookCustomer(STOCK* node3)
{
    printf("\n ID : %d\n",node3->bookId);
    printf("\n Title : %s\n",node3->bookName);
    printf("\n Author : %s\n",node3->bookAuthor);
    printf("\n Shelf No : %d\n",node3->shelfNo);
    printf("\n Quantity : %d\n",node3->bookQuantity);
    printf("\n Price : %d\n",node3->bookSP);
}

// display book for Admin
void displayBookAdmin(STOCK* node2)
{
    printf("\n ID : %d\n",node2->bookId);
    printf("\n Title : %s\n",node2->bookName);
    printf("\n Author : %s\n",node2->bookAuthor);
    printf("\n Shelf No : %d\n",node2->shelfNo);
    printf("\n Quantity : %d\n",node2->bookQuantity);
    printf("\n Price : %d\n",node2->bookCP);
}

void refill()
{
    int q;
    STOCK *temp1;
    temp1=searchBook();
    displayBookAdmin(temp1);
    printf("\n\nEnter Quantity To Add : ");
    scanf("%d",&q);
    temp1->bookQuantity=temp1->bookQuantity+q;
    printf("\nCurrent quantity : %d",temp1->bookQuantity);
}

int sellBook(STOCK* temp)
{
    int number;
    printf("\n Enter Number of Books : ");
    scanf("%d",&number);
    if(temp->bookQuantity == 0)
    {
        printf("\n Stock is not Available\n");
        return 0;
    }
    else if(number > (temp->bookQuantity))
    {
        printf("\nStock Not Sufficient\n");
        return 0;
    }
    else
    {
        temp->bookQuantity = temp->bookQuantity - number;
        push(temp,number);
        printf("\nBooks sold successfully\n");
        return 0;
    }
}


//main file deemand list or function
typedef struct deemandList
{
    char phoneNo[20];
    int noBook;
    char customerName[50];
    char bookName[50];
    struct deemandList* link;
}DEEMAND;

typedef struct queue
{
    DEEMAND *front;
    DEEMAND *rear;
}QUEUE;

QUEUE* createQueue()
{
    QUEUE* node = (QUEUE*)malloc(sizeof(QUEUE));
    node->front = NULL;
    node->rear = NULL;
    return node;
}

void insertQueue(QUEUE* q)
{
    
    char cName[50];
    char bName[50];
    int nBook;
    char pNum[20];
    DEEMAND *newNode = (DEEMAND*)malloc(sizeof(DEEMAND));
    newNode->link = NULL;
    printf("\nEnter the name of Customer : ");
    scanf("%s",cName);
    printf("\nEnter the Book Name : ");
    scanf("%s",bName);
    printf("\nEnter the Number of books required : ");
    scanf("%d",&nBook);
    printf("\nEnter your contact number : ");
    scanf("%s",pNum);

    strcpy(newNode->customerName,cName);
    strcpy(newNode->bookName,bName);
    newNode->noBook = nBook;
    strcpy(newNode->phoneNo,pNum);

    if( q->rear == NULL)
    {
        q->front = newNode;
        q->rear = newNode;
    }
    else
    {
        q->rear->link = newNode;
        q->rear = newNode;
    }
   
}

void displayDeemand(QUEUE *q)
{
   DEEMAND *nodeTemp;
   nodeTemp = q->front;
   printf("\nNAME        BOOK        CONTACT\n");
   while(nodeTemp!=NULL)
   {
    printf("\n%s         %s           %s\n",nodeTemp->customerName,nodeTemp->bookName,nodeTemp->phoneNo);
    nodeTemp = nodeTemp->link;
   }
   return;
}


void exitBookList(STOCK* head , FILE *fp)
{
    if( head != NULL)
    {
        exitBookList(head->llink,fp);
        fprintf(fp,"%d, %s, %s, %d, %d, %d, %d\n",head->bookId,head->bookName,head->bookAuthor,head->bookQuantity,head->bookCP,head->bookSP,head->shelfNo);
        exitBookList(head->rlink,fp);
    }
}

int main()
{
    addFileBook();
    QUEUE* qQ = createQueue();
    int choise = 0;
    int user = 0;
    while(user != 3)
    {
        system("cls");
        printf("\n 1. Customer\n");
        printf("\n 2. Admin\n");
        printf("\n 3. Exit \n\n");
        printf("=> ");
        scanf("%d",&user);

        switch(user)
        {

            case 1:
            {

                    while(choise != 5)
                    {
                        system("cls");
                        printf("\n 1. Display all Book\n");
                        printf("\n 2. Buy a Book\n");
                        printf("\n 3. Search a Book\n");
                        printf("\n 4. Deemand for a Book\n");
                        printf("\n 5. Exit for store\n\n");
                        printf("=> ");
                        scanf("%d",&choise);
                        switch(choise)
                        {
                            case 1:
                            {
                                system("cls");
                                printf("\nID     Name     Shelf No    Author       Quantity       sell Price      ShelfNo\n");
                                displayCustomer(startBook);
                                printf("\nPress to Continue\n");
                                getch();
                            }
                            break;

                            case 2:
                            {
                                system("cls");
                                // this case is used to sell a book available in the book store using sell function
                                STOCK* temp = searchBook();
                                if(temp != NULL)
                                {
                                    sellBook(temp);
                                }
                                else
                                {
                                    printf("\n The Book is not available in store\n");
                                }
                                printf("\nPress to Continue\n");
                                getch();
                            }
                            break;

                            case 3:
                                {
                                system("cls");
                                    // this case is used to search a book in the store
                                    // we need to make changes in the book management
                                STOCK* temp = searchBook();
                                if(temp != NULL)
                                {
                                    displayBookCustomer(temp);
                                }
                                else
                                {
                                    printf("\nBook is not there in stock\n");
                                }
                                printf("\nPress to Continue\n");
                                getch();
                                }
                            break;

                            case 4:
                            {
                                system("cls");
                                insertQueue(qQ);
                                printf("\nPress to Continue\n");
                                getch();          
                            }
                            break;

                        }

                }

                system("cls");
                printf("\nThank you visit again.................\n");
            
                getch();
            }
            break;

            case 2:
            {
                system("cls");
                char password[20];
                printf("Enter the Admin Password : ");
                scanf("%s",password);
                
                if(!strcmp(password,"@pesu"))
                {
                while(choise != 9)
                    {
                        system("cls");
                        printf("\n 1. Display all Book\n");
                        printf("\n 2. Insert a Book\n");
                        printf("\n 3. Refill a Book\n");
                        printf("\n 4. Sell a Book\n");
                        printf("\n 5. Search a Book\n");
                        printf("\n 6. Deemand List\n");
                        printf("\n 7. Purchase Record\n");
                        printf("\n 8. Insert a Purchase\n");
                        printf("\n 9. Exit from store\n\n");
                        printf("=> ");
                        scanf("%d",&choise);
                        switch(choise)
                        {
                            case 1:
                            {
                                system("cls");
                                printf("\nID     Name     Shelf No    Author       Quantity       Cost Price      ShelfNo\n");
                                displayAdmin(startBook);
                                printf("\nPress to Continue\n");
                                getch();
                            }
                            break;

                            case 2:
                            {
                                // this case is used to create a single book using createBook() function
                                createBook();
                                printf("\nPress to Continue\n");
                                getch();
                            }
                            break;

                            case 3:
                            {
                                refill();
                                printf("\nPress to Continue\n");
                                getch();
                            }
                            break;

                            case 4:
                            {
                                 system("cls");
                                // this case is used to sell a book available in the book store using sell function
                                STOCK* temp = searchBook();
                                if(temp != NULL)
                                {
                                    sellBook(temp);
                                }
                                else
                                {
                                    printf("\n The Book is not available in store\n");
                                }
                                printf("\nPress to Continue\n");
                                getch();
                            }
                            break;

                            case 5:
                                {
                                    system("cls");
                                    // this case is used to search a book in the store
                                    // we need to make changes in the book management
                                    STOCK* temp = searchBook();
                                    if(temp != NULL)
                                    {
                                        displayBookAdmin(temp);
                                    }
                                    else
                                    {
                                        printf("\nBook is not there in stock\n");
                                    }
                                    printf("\n Press to Continue\n");
                                    getch();
                                }
                            break;

                            case 6:
                                {
                                    displayDeemand(qQ);
                                    printf("\nPress to Continue\n");
                                    getch();
                                }
                            break;

                            case 7:
                                {
                                    system("cls");
                                    display_record();
                                    printf("\n\n\t\t\t\t\t\tPress to Continue");
                                    getch();
                                }
                           
                            break;

                            case 8:
                               {
                                    system("cls");
                                    int noBook;
                                    STOCK *var = searchBook();
                                    printf("\nEnter the number of book required : ");
                                    scanf("%d",&noBook);
                                    if(var != NULL)
                                    {
                                        push(var,noBook);
                                    }
                                    else
                                    {
                                        printf("\nStock is not there \n");
                                    }
                                    printf("\n Press to Continue \n");
                                    getch();
                               }
                            break;
                        }
                    }
                    system("cls");
                    printf("\nThank You Admin\n");

                }
                else
                {
                    system("cls");
                    printf("\nPassword doesnt match\n\n");
                    printf("\n\nPlease login through correct pasword\n");
                }

                
                getch();
            }
            break;
        }

    }
    FILE* fp = fopen("bookList.csv","w");
    fprintf(fp,"BookId,BookName,Author,Quantity,Cost,Sell,Shelf No\n");
    fclose(fp);
    FILE* fp1 = fopen("bookList.csv","a");
    exitBookList(startBook,fp1);
    fclose(fp1);
    return 0;

}





