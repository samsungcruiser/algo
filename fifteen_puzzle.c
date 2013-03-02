#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>

struct data{
    char name[30];
    int time;
};

void displayTable(int m, int box[m][m]);
void moveDown(int n, int box[n][n]);
void moveUp(int n, int box[n][n]);
void moveLeft(int n, int box[n][n]);
void moveRight(int n, int box[n][n]);
void findSpace(int n, int box[n][n], int *x, int *y);
void randomeyez(int n, int box[n][n]);
int checkCompletion(int n, int box[n][n]);
void play();
void hof();
void sortName(struct data *ent, int n, int ch);
void printRecords(struct data *th, int n);
void printRecordsReverse(struct data *th, int n);
void sortTime(struct data *ent, int n, int ch);

time_t start;     //declare time variables used to count/time how long it takes to play the game till completion
time_t end;
float duration;
char name[20];



int main(){
    system("color 1b");
    char ch='X';
    while(ch != 27){

        if(ch==49)play();
        if(ch==50)hof();
        system("cls");
        printf("Press 1 to play the game\n"
               "Press 2 to display Records\n"
               "Press ESC to quit");
        ch = getch();

    }
    return 0;
}

void displayTable(int n, int box[n][n]){
    int i,j;
    for(i = 0; i < n; i++){
                 for(j = 0; j < n; j++){
                        if(box[i][j] == 0){
                             printf("   ");
                             continue;
                        }
                        printf("%2d ", box[i][j]);
                  }
                  printf("\n");
    }
}

void findSpace(int n, int box[n][n], int *x, int *y){
    int i, j;
    for(i = 0; i < n; i++){
       for(j = 0; j < n; j++){
             if(box[i][j] == 0){
                 *x = i;
                 *y = j;
                 break;
             }
       }
    }
}

void moveDown(int n, int box[n][n]){
    int x, y;
    findSpace(n, box, &x, &y);
    if(x == 0) return;
    box[x][y] = box[x-1][y];
    box[x-1][y] = 0;
}

void moveUp(int n, int box[n][n]){
    int x, y;
    findSpace(n, box, &x, &y);
    if(x == n-1) return;
    box[x][y] = box[x+1][y];
    box[x+1][y] = 0;
}

void moveLeft(int n, int box[n][n]){
    int x, y;
    findSpace(n, box, &x, &y);
    if(y == n-1) return;
    box[x][y] = box[x][y+1];
    box[x][y+1] = 0;
}

void moveRight(int n, int box[n][n]){
    int x, y;
    findSpace(n, box, &x, &y);
    if(y == 0) return;
    box[x][y] = box[x][y-1];
    box[x][y-1] = 0;
}

void randomeyez(int n, int box[n][n]){
    srand ( time(NULL) );
    int i = 2501, x;
    while (i>0){
        x = rand() % 4;
        if ( x == 0 )
            moveUp(n, box);
        else if ( x == 1 )
            moveDown(n, box);
        else if ( x == 2 )
            moveLeft(n, box);
        else if ( x == 3 )
            moveRight(n, box);
        i--;
    }
}

int checkCompletion(int n, int box[n][n]){
    int i, j, z=1;
    int last = n*n - 1;
    for(i = 0; i < n; i++){
        for(j = 0; j < n; j++){
            if(box[i][j] == z){
                if(z == last){
                    z = 0;
                    continue;
                }
                z++;
                continue;
            }
            return 0;
        }
    }

    time(&end);    //get the time at which he completes the game
	duration = difftime(end, start);  //calculate the duration of gameplay
    printf("Puzzle solved!!!\nTime taken: %.2f seconds",duration);

    printf("\nEnter you name: ");  //prompt for player's name
	scanf("%s", name);             //save the name
	FILE *fptr=NULL;               //create a file pointer
	fptr = fopen("HighScores.txt", "a" );  //open HighScores.txt to add details of the game
	fprintf(fptr, "%s,%.0f\n", name, duration); //save player's info in the HighScores.txt file
	fclose(fptr);                 //close the file pointer
	system("pause");
	hof();
    return 1;
}

void play(){
    system("cls");
    int n;
    printf("Enter puzzle size: ");
    scanf("%d", &n);
    int box[n][n];
    int i, j, sum = 1;
    for(i = 0; i < n; i++){
          for(j = 0; j < n; j++){
                if(i == n-1 && j == n-1){
                     box[i][j] = 0;
                     continue;
                }
                box[i][j] = sum;
                sum++;
          }

    }
    randomeyez(n, box);
    displayTable(n, box);
	time(&start);    //get the time at which he starts playing the game

    printf("\n\n");
    char choice;
    int done = 0;
    do{
    printf("\nEnter move: ");
    choice = getch();
    int x,y,pos;
    for(i = 0; i < n; i++){
       for(j = 0; j < n; j++){
             if(box[i][j] == 0){
                 x = i;
                 y = j;
                 break;
             }
       }
    }

    system("cls");
    printf("\n");
    switch(choice){
        case 's':
        case 'S':
             moveDown(n, box);
             displayTable(n, box);
             break;
        case 'd':
        case 'D':
          moveRight(n, box);
             displayTable(n, box);
             break;
        case 'w':
        case 'W':
           moveUp(n, box);
             displayTable(n, box);
             break;
        case 'a':
        case 'A':
            moveLeft(n, box);
             displayTable(n, box);
             break;
        default:
             printf("Wrong move!\n");

             }
        done = checkCompletion(n, box);
        } while(done == 0);
 //   getch();
}

void hof(){
    char ch;
	int i, x;
	char *result;
	int n=0, m = 0;
	FILE *fptr; //create file pointer
	fptr = fopen("HighScores.txt", "r");  //open HighScores.txt
	while  ( ( ch = fgetc( fptr ) ) != EOF ){ //determine the number of lines in the file
		if(ch==10)n++;                        //we need that to know how big to make the array later
	}                                         //returns n which is the number of lines
	rewind(fptr);
	struct data entry[n];          //create a data array to hold the records from the HighScores.txt file
	for(i=0; i<n; i++){            //loop n to read all records from the file
		char info[50];
		fscanf(fptr, "%s", &info); //read a line from the file
		result = strtok(info, ",");
		strcpy(entry[i].name,result); //store name
		result = strtok(NULL, ",");
		entry[i].time=atoi(result);  //store time from the file
	}
	fclose(fptr);         //close the file after reading all records
	ch = 'p';
	while(ch!=27){
        if(ch==49)sortName(entry, n, 1); //call the required sort method based on user's choice
        if(ch==50)sortTime(entry, n, 1);
        if(ch==51)sortName(entry, n, 0);
        if(ch==52)sortTime(entry, n, 0);
        system("cls");
        printf("\nPress 1 to sort by Name (Ascending)\nPress 2 to sort by Time (Ascending)");
	    printf("\nPress 3 to sort by Name (Descending)\nPress 4 to sort by Time (Descending)");
		printf("\nPress ESC to exit\n");
        ch = getch();
	}
	return;
}

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

void printRecords(struct data *th, int n){
	int i;
	printf("\n\t  High Scores\n\t===============\n");
	printf("\nName\t\tTime(s)\n=====\t\t======\n");
    for(i=0;i<n;i++){    //prints from first to last(ascending)
		printf("%s\t\t%d\n", th[i].name, th[i].time);
	}
	system("pause");
}

//prints the Records from the hall of fame file in descending order
void printRecordsReverse(struct data *th, int n){
	printf("\n\t  High Scores\n\t===============\n");
	printf("\nName\t\tTime(s)\n=====\t\t======\n");
    for(n;n>0;n--){     //prints from last to first(descending)
		printf("%s\t\t%d\n", th[n-1].name, th[n-1].time);
	}
	system("pause");
}

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
