#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

//Structure to act as the stacks
struct col{
	int size;
	struct col *next;
	};

//structure to hold HallofFame data before it is sorted
struct data{
	char name[20];
	int diff;
	int moves;
	int time;
};

//function prototypes
struct col *initLLNode(int N);
void push(int N, struct col *head);
int pop(struct col *curr);
void towers(int n, struct col *stackA, struct col *stackC, struct col *stackB);
void printStacks();
void Demo();
void fillA(int n);
void emptyStacks();
void play();
void wait ( float sec );
int countNodes();
void emptyArrays();
void filla(struct col *curr);
void fillb(struct col *curr);
void fillc(struct col *curr);
void disp(int N);
void hof();
void sortDiff(struct data *ent, int n, int ch);
void sortMoves(struct data *ent, int n, int ch);
void sortTime(struct data *ent, int n, int ch);
void sortName(struct data *ent, int n, int ch);
void printRecords(struct data *th, int n);
void printRecordsReverse(struct data *th, int n);

//initialize global variables
//===============================
	struct col *headA;
	struct col *tailA;
	struct col *headB;
	struct col *tailB;
	struct col *headC;
	struct col *tailC;
	int a[10] = {0};
	int b[10] = {0};
	int c[10] = {0};
 	float playback;
//==============================

int main(){
    int ch='X';
//Creates the 3 stacks; initially empty (head points to tail)
    headA=initLLNode(100);
	tailA=initLLNode(100);
	headA->next=tailA;
	headB=initLLNode(101);
	tailB=initLLNode(101);
	headB->next=tailB;
	headC=initLLNode(102);
	tailC=initLLNode(102);
	headC->next=tailC;

//repeat the prompt until the user enters the ESC key.
//(esc corresponds to ASCII value 27, so we repeat while ch is not equal to 27)
	while(ch!=27){
		if(ch==49)play(); //if 1 entered, start play mode
		if(ch==50)Demo(); //if 2 entered, demo mode
		if(ch==51)hof();  //if 3 entered, go to hall of face
		system("cls");    //this clears the screen
		printf("Tower of Hanoi\n"
			"==============================\n"
			"Press 1 to go to Game Mode.\n"
			"Press 2 to go to Demo Mode.\n"
			"Press 3 to go to Hall of Fame.\n"
			"Press ESC to Exit.\n");
        emptyStacks();    //initalizes the stacks (explained at function definition)
		ch = getch();     //gets user input
	}
	return 0;
}

//creates a new node
struct col *initLLNode(int N){
	struct col *temp;
	temp=(struct col *)malloc(sizeof(struct col));
	temp->size=N;
	temp->next=NULL;
	return(temp);
}

//pushes a disc of size N onto the specified stack
void push(int N, struct col *head){
		struct col *temp;
		temp=initLLNode(N);
		temp->next=head->next;
		head->next=temp;
		return;
}

//pops a disc from specified stack. Returns the size of the disc popped
int pop(struct col *curr){
	struct col *temp;
	int N;
	N=curr->next->size;
	temp=curr->next;
	curr->next=curr->next->next;
	free(temp);
	return(N);
}

//recursive algorithm to solve the towers of hanoi problem. Used in demo mode
void towers(int n, struct col *stackA, struct col *stackC, struct col *stackB){
	
	int val;
	char from, to;
	/* If only 1 disk, make the move and return */
	if(n==1){
		val = pop(stackA);        //pop from Stack A and
		push(val, stackC);        //push onto Stack C
		system("cls");
		if(stackA->size==100) from='A';
		else if(stackA->size==101) from='B';
		else from='C';
		if(stackC->size==100) to='A';
		else if(stackC->size==101) to='B';
		else to='C';
		printStacks();
		printf("\nMove disk %d from %c to %c",n, from, to);
		wait(playback);  //waits for the amount of time specified by the user. this is what determines the playback speed.
		return;
	}
	/* Move top n-1 disks from A to B, using C as auxiliary */
	towers(n-1,stackA,stackB,stackC);
	/* Move remaining disks from A to C */
	val = pop(stackA);
	push(val, stackC);
	system("cls");
	if(stackA->size==100) from='A';
	else if(stackA->size==101) from='B';
	else from='C';
	if(stackC->size==100) to='A';
	else if(stackC->size==101) to='B';
	else to='C';
	printStacks();
	printf("\nMove disk %d from %c to %c",n, from, to);
	wait(playback);
	/* Move n-1 disks from B to C using A as auxiliary */
	towers(n-1,stackB,stackC,stackA);
}

void Demo(){
	system("cls"); //clear screen
	printf("How many discs(1-10) do you want to solve?\n>>");
	int n;
	float m;
	scanf("%d", &n); //get the number of discs the user wants
	fillA(n);        //fill stack A with the specified number
	printf("What is you preferred playback speed:1(fast)-10(slow)\n>>");
	scanf("%f", &m); // get the preferred playback speed
	playback = m/5;  //scale it down to usable value
	towers(n, headA, headC, headB); //solve the towers of hanoi problem
	printf("\nReturning to main menu...");
	wait(2);    //wait for 2 seconds then return to the main menu
	return;
}

//this functions fills Stack A with any number of discs.
//it starts by pushing the largest disc in first, then
//continues until disc 1 is put at the top
void fillA(int n){
	for(n;n>=1;n--)
		push(n, headA);
}

//this pops out all nodes from all stacks leaving them empty
void emptyStacks(){
	int val;
	while(headA->next != tailA)  //while there is a node
		val=pop(headA);          //remove it
	while(headB->next != tailB)
		val=pop(headB);
	while(headC->next != tailC)
		val=pop(headC);
}

//play mode
void play(){
	system("cls");
	printf("How many discs do you want to solve?\n>>");
	int n, val, moves=0;
	char choice;
	char name[15];
	scanf("%d", &n);  //get number of discs to solve from user
	fillA(n);         //fill stack A with the number, n
	time_t start;     //declare time variables used to count/time how long it takes to play the game till completion
	time_t end;
	float duration;
	time(&start);    //get the time at which he starts playing the game
	while(countNodes() != n){   //loops play for as long as stack C is not yet full. Game ends when Stack C is full
        int p = 1;
        while(p==1){
			system("cls");
			printStacks();     //print the stacks on the screen
			printf("\nPress A to pop from Stack A\nPress B to pop from Stack B\nPress C to pop from Stack C\n>>");
			choice = getch();
		
			switch(choice){
				case 'A':      //if he enters 'a' or 'A', pop disc from stack A
				case 'a':
					if(headA->next==tailA)break; //if stack A is empty, don't pop
					printf("popping from A");
                    val = pop(headA);            //pop node from stack A
					p--;
					break;
				case 'B':     //if he enters 'b' or 'B', pop disc from stack B
				case 'b':
					if(headB->next==tailB)break;   //if stack B is empty, don't pop
            	    printf("popping from B");
					val = pop(headB);              //pop node from stack B
					p--;
					break;
				case 'C':     //if he enters 'c' or 'C', pop disc from stack C
				case 'c':
					if(headC->next==tailC)break;  //if stack C is empty, don't pop
            	    printf("popping from C");
					val = pop(headC);             //pop node from stack C
					p--;
					break;
				default:
					printf("\b"); //if any other input is entered, delete it
					break;
			}
		}
		p=1;
		while(p==1){
			system("cls");    //clear the screen
  			printStacks();    //print the current state of the stacks
			printf("\nPress A to push to Stack A\nPress B to push to Stack B\nPress C to push to Stack C\n>>");
			choice = getch();
			switch(choice){
				case 'A':     //if he enter 'A' or 'a', push disc onto Stack A
				case 'a':
					if(val>headA->next->size)break; //prevent the user from pushing a bigger disc onto the one on stack A
					push(val, headA);               //push disc onto stack A
					p--;
					break;
				case 'B':     //if he enters 'B' or  'b', push disc onto stack B
				case 'b':
                    if(val>headB->next->size)break; //prevent the user from pushing a bigger disc onto the one on stack B
					push(val, headB);               //push disc onto stack B
					p--;
					break;
				case 'C':      //if he enter 'C' or 'c', push disc onto stack C
				case 'c':
                    if(val>headC->next->size)break; //prevent the user from pushing a bigger disc onto the one on stack C
					push(val, headC);               //push disc onto stack C
					p--;
					break;
				default:
					printf("\b"); //if any invalid input is entered, delete it
					break;
			}
		}
		moves++;
	}
	printStacks(); //print the current state of the stacks
	time(&end);    //get the time at which he completes the game
	duration = difftime(end, start);  //calculate the duration of gameplay
	printf("\nCongratulations!!\nCompleted in %d moves! (%.0f seconds)\n", moves, duration);
	printf("\nEnter you name: ");  //prompt for player's name
	scanf("%s", name);             //save the name
	FILE *fptr=NULL;               //create a file pointer
	fptr = fopen("HallofFame.txt", "a" );  //open HallofFame.txt to add details of the game
	fprintf(fptr, "%s,%d,%d,%.0f\n", name, n, moves, duration); //save player's info in the HallofFame.txt file
	fclose(fptr);                 //close the file pointer
	system("pause");
}

//this function counts and returns the nodes in Stack C
int countNodes(){
	struct col *curr;
	int num=0;
	curr = headC;
	while(curr->next != tailC){
		num++;
		curr=curr->next;
	}
	return num;
}

//function to generate a delay
void wait ( float sec )
	{
		clock_t end_wait;
		end_wait = clock () + sec * CLK_TCK ;

		while (clock() < end_wait) {}
	}

//function to convert Stack A into an array a[]. we use arrays for printing the stacks
void filla(struct col *curr){
	int i = 0, n = 0, m;
	
	while(curr->next!=tailA){  //while there are still nodes in the stack, copy the node's value into the array
		a[i]=curr->next->size;
		curr=curr->next;
		i++;
	}
	
	while(a[n]!=0)n++;
	m=9-n;
	for(n;n>0;n--){
		a[m+n]=a[n-1];
		a[n-1]=0;
	}
	return;
}

//function to convert stack B into array b[]
void fillb(struct col *curr){
	int i = 0, n = 0, m;
	while(curr->next!=tailB){
		b[i]=curr->next->size;
		curr=curr->next;
		i++;
	}
	while(b[n]!=0)n++;
	m=9-n;
	for(n;n>0;n--){
		b[m+n]=b[n-1];
		b[n-1]=0;
	}
	return;
}

//convert stack C into array c[]
void fillc(struct col *curr){
	int i = 0, n = 0, m;
	while(curr->next!=tailC){
		c[i]=curr->next->size;
		curr=curr->next;
		i++;
	}
	while(c[n]!=0)n++;
	m=9-n;
	for(n;n>0;n--){
		c[m+n]=c[n-1];
		c[n-1]=0;
	}
	return;
}

//function to empty the arrays before copying new Stack values into them
void emptyArrays(){
	int i;
	for(i=0;i<10;i++)   //for loop to write zeros into all positions in the arrays, effectively emptying them
		a[i]=b[i]=c[i]=0;
}

//prints the stacks on the screen
void printStacks(){
	int j;
	emptyArrays();
	filla(headA); //first convert eack stack into its
	fillb(headB); //corresponding array
	fillc(headC);
	for(j=0;j<10;j++){ //then use the for loop to print the values in the arrays
		disp(a[j]);
		disp(b[j]);
		disp(c[j]);
		printf("\n");
    }
    printf("*************\t\t*************\t\t*************\nStack A\t\t\tStack B\t\t\tStack C\n");
}

//formats/organizes the Stack display on the screen
void disp(int N){
	int k, j;
	j=N;
    if(N==0)printf("\t");
	if(N!=0){
		printf("%d ", N);
		for(N;N>0;N--)
		    printf("=");
        for(k=10; k>j; k--)
        	printf(" ");
	}
	printf("\t\t");
	return;
}

//hall of fame mode
void hof(){
    char ch;
	int i, x;
	char *result;
	int n=0, m = 0;
	FILE *fptr; //create file pointer
	fptr = fopen("HallofFame.txt", "r");  //open HallofFame.txt
	while  ( ( ch = fgetc( fptr ) ) != EOF ){ //determine the number of lines in the file
		if(ch==10)n++;                        //we need that to know how big to make the array later
	}                                         //returns n which is the number of lines
	rewind(fptr);
	struct data entry[n];          //create a data array to hold the records from the HallofFame.txt file
	for(i=0; i<n; i++){            //loop n to read all records from the file
		char info[50];
        fscanf(fptr, "%s", &info); //read a line from the file
		result = strtok(info, ",");
		strcpy(entry[i].name,result); //store name
        result = strtok(NULL, ",");
		entry[i].diff=atoi(result);   //store level
		result = strtok(NULL, ",");
		entry[i].moves=atoi(result); //store steps
		result = strtok(NULL, ",");
		entry[i].time=atoi(result);  //store time from the file
	}
	fclose(fptr);         //close the file after reading all records
	ch = 'p';
	while(ch!=27){
        if(ch==49)sortName(entry, n, 1); //call the required sort method based on user's choice
        if(ch==50)sortDiff(entry, n, 1);
        if(ch==51)sortMoves(entry, n, 1);
        if(ch==52)sortTime(entry, n, 1);
        if(ch==53)sortName(entry, n, 0);
        if(ch==54)sortDiff(entry, n, 0);
        if(ch==55)sortMoves(entry, n, 0);
        if(ch==56)sortTime(entry, n, 0);
        system("cls");
        printf("\nPress 1 to sort by Name (Ascending)\nPress 2 to sort by Level (Ascending)\nPress 3 to sort by Steps (Ascending)\nPress 4 to sort by Time (Ascending)");
	    printf("\nPress 5 to sort by Name (Descending)\nPress 6 to sort by Level (Descending)\nPress 7 to sort by Steps (Descending)\nPress 8 to sort by Time (Descending)");
		printf("\nPress ESC to exit\n");
        ch = getch();
	}
	return;
}

//function to sort by level
//it employs selection sort
void sortDiff(struct data *ent, int n, int ch){
	int i, j, k;
	int min;
	struct data curr;
	for(j=0;j<n;j++){
		min=ent[j].diff;
		for(k=j;k<n;k++)
			if(ent[k].diff<ent[min].diff)
			min=k;
		memcpy(&curr, &ent[min], sizeof(struct data));  //memcpy is used to copy structures
		memcpy(&ent[min], &ent[j], sizeof(struct data));
		memcpy(&ent[j], &curr, sizeof(struct data));
	}
	if(ch)printRecords(ent, n);       //if input was 1, print ascending
	else printRecordsReverse(ent, n); //if input was 0, print descending
}

//function to sort by number of steps
//it employs selection sort
void sortMoves(struct data *ent, int n, int ch){
	int i, j, k;
	int min;
	struct data curr;
	for(j=0;j<n;j++){
		min=ent[j].moves;
		for(k=j;k<n;k++)
			if(ent[k].moves<ent[min].moves)
			min=k;
		memcpy(&curr, &ent[min], sizeof(struct data));
		memcpy(&ent[min], &ent[j], sizeof(struct data));
		memcpy(&ent[j], &curr, sizeof(struct data));
	}
	if(ch)printRecords(ent, n);
	else printRecordsReverse(ent, n);
}

//function to sort by time taken to complete the game
//it employs insertion sort
void sortTime(struct data *ent, int n, int ch){
	struct data curr;
	int j,k;
	for(j=0;j<n;j++){
		memcpy(&curr,&(ent[j]), sizeof(struct data));
		for(k=j;k>0;k--){
			if(ent[k-1].time<=curr.time)
			break;
			memcpy(&ent[k], &ent[k-1], sizeof(struct data));
		}
	memcpy(&ent[k], &curr, sizeof(struct data));
	}
	if(ch)printRecords(ent, n);
	else printRecordsReverse(ent, n);
}

//function to sort by name
//it employs insertion sort
void sortName(struct data *ent, int n, int ch){
    struct data curr;
	int j,k;
	for(j=0;j<n;j++){
		memcpy(&curr,&(ent[j]), sizeof(struct data));
		for(k=j;k>0;k--){
			if(strcmp(ent[k-1].name,curr.name)<=0) //strcmp is used compare the strings
			break;
			memcpy(&ent[k], &ent[k-1], sizeof(struct data));
		}
	memcpy(&ent[k], &curr, sizeof(struct data));
	}
	if(ch)printRecords(ent, n);
	else printRecordsReverse(ent, n);
}

//prints the Records from the hall of fame file in ascending order
void printRecords(struct data *th, int n){
	int i;
	printf("\n\tHall of Fame\n\t===============\n");
	printf("\nName\t\tLevel\t\tSteps\t\tTime(s)\n=====\t\t======\t\t======\t\t========\n");
    for(i=0;i<n;i++){    //prints from first to last(ascending)
		printf("%s\t\t%d\t\t%d\t\t%d\n", th[i].name, th[i].diff, th[i].moves, th[i].time);
	}
	system("pause");
}

//prints the Records from the hall of fame file in descending order
void printRecordsReverse(struct data *th, int n){
	printf("\n\tHall of Fame\n\t===============\n");
	printf("\nName\t\tLevel\t\tSteps\t\tTime(s)\n=====\t\t======\t\t======\t\t========\n");
    for(n;n>0;n--){     //prints from last to first(descending)
		printf("%s\t\t%d\t\t%d\t\t%d\n", th[n-1].name, th[n-1].diff, th[n-1].moves, th[n-1].time);
	}
	system("pause");
}
