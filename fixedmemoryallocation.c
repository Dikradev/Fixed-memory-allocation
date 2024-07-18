#include <stdio.h>
#include <stdlib.h> 

typedef struct PDT // Partition description table
{
    int name;    // Name or ID (you can provide a more descriptive name)
    char state; // F = FREE, A = ALLOCATED
    float size;  // Size of the partition
} PDT;

typedef struct Queue // Waiting zone
{
    int id;
    float size;
    struct Queue *next;
} Queue;

Queue *head = NULL;

// Function to add a process to the waiting zone
Queue *ins_e(int a, float x, Queue *head)
{
    Queue *new, *p;
    new = (Queue *)malloc(sizeof(Queue)); 
    new->id = a;
    new->size = x;
    new->next = NULL; // Initialize the next pointer

    if (head == NULL)
        head = new;
    else 
    {
        p = head;
        while (p->next != NULL)
        {
            p = p->next;
        }
        new->next=NULL;
        p->next = new; // Add the new node to the end of the list
    }
    return head;
}

// Function to read process details
void read(PDT p[],int n)
{
    for(int i = 0;i<n;i++){
    printf("Enter Partition %d size: ",i+1);
        scanf("%f", &p[i].size);
        p[i].state='F';
        }
    int a;
    float b;
    char choice = 'N';
    do
    {
        printf("Enter process ID: ");
        scanf("%d", &a);
        printf("Enter process size: ");
        scanf("%f", &b);
        head = ins_e(a, b, head);
        printf("Wanna add another process? (Y/N): "); 
        scanf(" %c", &choice); // Note the space before %c to consume the newline character
    }while (choice == 'Y' || choice == 'y');
}
void displayPDT(PDT Q[], int n)
{
    printf("Partition Description Table (PDT):\n");
    printf("+--------------+------+-----------+\n");
    printf("|     Num      | Size | State     |\n");
    printf("+--------------+------+-----------+\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %-12d | %.2f | %-9s |\n", Q[i].name, Q[i].size, Q[i].state == 'F' ? "Free" : "Allocated");
    }
    printf("+--------------+------+-----------+\n");
}
// Function to display the waiting zone
void displayQueue(Queue *head)
{
    Queue *p;
    if (head == NULL)
        printf("The Waiting Queue is empty.\n");
    else
    {
        printf("Waiting zone:\n");
        p = head;
        while (p != NULL)
        {
            printf("Size: %.2f, ID: %d\n", p->size, p->id);
            p = p->next;
        }
    }
}
void firstfit(Queue *head, PDT Q[], int n)
{
    float IF, EF = 0;
    Queue *p,*q;
    p = head;
    int a;
    int j=0;
    q=head;
    while (p != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            if (p->size <= Q[i].size && Q[i].state != 'A')
            {
                a=0;
                j=+1;
                Q[i].name = p->id;
                IF = Q[i].size - p->size;
                EF += IF;
                Q[i].state = 'A';
                printf("Internal fragmentation of partition %d = %.2f\n", i + 1, IF);
                a=p->id;
                if (q == NULL)
                head = p->next;
                else
                q->next = p->next;
                free(p);
                printf("Process ID %d removed from the waiting zone.\n", a);
                break;
                 // Process allocated, move to the next waiting process
            }
        }
        q=p;
        p = p->next;
        if(j>=n)
        break;
    }
    printf("External fragmentation = %.2f\n", EF);
}
/*void sortDescending(Queue *head)
{
    int swapped;
    Queue *ptr1;
    Queue *lptr = NULL;
    if (head == NULL)
        return;
    do
    {
        swapped = 0;
        ptr1 = head;

        while (ptr1->next != lptr)
        {
            if (ptr1->size < ptr1->next->size)
            {
                // Swap data
                int tempSize = ptr1->size;
                int tempid = ptr1->id;
                ptr1->size = ptr1->next->size;
                ptr1->id = ptr1->next->id;
                ptr1->next->size = tempSize;
                ptr1->next->id = tempid;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}*/

void bestfit(Queue *head, PDT Q[], int n)
{
    float IF, EF = 0;
    /*sortDescending(head);*/
    Queue *p,*q;
    p = head;
    q = head;
    int a;
    int j=0;
    int bestIdx;
    while (p != NULL)
    {
        int bestIdx = -1;
		for (int i = 0; i < n; i++)
		{
			if (p->size <= Q[i].size && Q[i].state != 'A')
			{
				if (bestIdx == -1)
					bestIdx = i;
                if(p->size == Q[i].size)
                    break;
				else if (Q[bestIdx].size > Q[i].size)
					bestIdx = i;
			}
		}
            if(bestIdx  != -1){
                a=0;
                Q[bestIdx].name = p->id;
                IF = Q[bestIdx].size - p->size;
                EF += IF;
                Q[bestIdx].state = 'A';
                printf("Internal fragmentation of partition %d = %.2f\n", bestIdx + 1, IF);
                a=p->id;
                if (q == NULL)
                head = p->next;
                else
                q->next = p->next;
                free(p);
                printf("Process ID %d removed from the waiting zone.\n", a);
                j=+1;
                 // Process allocated, move to the next waiting process
        }
        q=p;
        p = p->next;
        if(j>=n)
        break;
    }
    printf("External fragmentation = %.2f\n", EF);
}
void deallocation(PDT P[],int n)
{
    int z;
    printf("Enter the number of partition that you want to delete: ");
    scanf("%d", &z);
    if(z>n || z<=0)
    printf("Wrong Number.\n");
    if(P[z-1].state != 'F') {
        P[z-1].state = 'F';
        P[z-1].name = 0;
        printf("Deleted \n");

    } else {
        printf("Partition is already free.\n");
    }
}
void addprogram()
{
    int a;
    float b;
    char choice = 'N';
    do
    {
        printf("Enter process ID: ");
        scanf("%d", &a);
        printf("Enter process size: ");
        scanf("%f", &b);
        head = ins_e(a, b, head);
        printf("Wanna add another process? (Y/N): ");
        scanf(" %c", &choice); // Note the space before %c to consume the newline character
    } while (choice == 'Y' || choice == 'y');
}
int main()
{
    int n=1;
    do
    {
        if(n <= 0)
        printf("Eror again !!\n");
        printf("How many partition you need ? :");
        scanf("%d",&n);
    }while(n <= 0 );
    PDT P[n];
    read(P,n);
    int choice;
    do{
    printf("\n\n\n");
    printf("  __  __ ______ _   _ _    _ \n");
    printf(" |  \\/  |  ____| \\ | | |  | |\n");
    printf(" | \\  / | |__  |  \\| | |  | |\n");
    printf(" | |\\/| |  __| | . ` | |  | |\n");
    printf(" | |  | | |____| |\\  | |__| |\n");
    printf(" |_|  |_|______|_| \\_|\\____/\n");
    printf("---------------------------------------------\n");
    printf("[1]. FirsFit\n");
    printf("[2]. BestFit\n");
    printf("[3]. Display Waiting Queue\n");
    printf("[4]. Display PDT \n");
    printf("[5]. Deallocate Partition\n");
    printf("[6]. Add Programh\n");
    printf("[7]. Exit\n");
    printf("Enter your choise : \n");
    scanf(" %d",&choice);
    switch(choice)
    {
        case 1:
            firstfit(head,P,n);
            break;
            case 2:
                bestfit(head,P,n);
                break;
            case 3:
                displayQueue(head);
                break;
            case 4:
                displayPDT(P,n);
                break;
            case 5:
                deallocation(P,n);
                break;
            case 6:
            addprogram();
            default:
                exit(0);
    }
    }while(1);
    return 0;
}
