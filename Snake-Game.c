#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include<ctype.h>
#include <windows.h>
#include <process.h>

/// Direction keys
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

///Global variables
int length;
int life;
int bend_no;
int len;
char key;

///Functions declaration
void Welcome();
void load();
void gotoxy(int x, int y); // coordinates change inside the console
void FoodCoord ();
void BordersFoodDisplay();
void Move();
void Delay();
int Score();
void Left();
void Right();
void Up();
void Down();
void Bend();
void ExitGame();
void Record();
int Scoreonly();



struct coordinate
{
    int x;
    int y;
    int direction;
};
typedef struct coordinate coordinate;
coordinate head, food, body[100], bend[100];


int main()
{
    Welcome(); // display welcome & instructions
    system("cls"); // clear screen
    load(); // loading bar

    // initial length, coordinates & direction of the snake
    length=5;
    head.x=25;
    head.y=20;
    head.direction= RIGHT;

    life =3; //number of lives
    bend[0]=head;

    FoodCoord(); // generate food coordinates randomly
    BordersFoodDisplay(); //display borders and food
    Move();


}


void Welcome()
{

    printf("\tWelcome to the CRAVING SNAKE game.(press any key to continue)\n");
    getch();
    system("cls");
    printf("\tGame instructions:\n");
    printf("\n-> Use arrow keys to move the snake.\n\n-> You will be provided foods at the several coordinates of the screen which you have to eat. Everytime you eat a food the length of the snake will be increased by 1 element and thus the score.\n\n-> Here you are provided with three lives. Your life will decrease as you hit the wall or snake's body.\n\n-> You can pause the game in its middle by pressing any key. To resume press any other key once again\n\n-> If you want to exit press Esc. \n");
    printf("\n\nPress any key to play game...");
    if(getch()==27)
        exit(0);
}


void load()
{
     int row,col,r,c,q;
    gotoxy(36,14);
    printf("Loading...");
    gotoxy(30,15);
    for(r=1; r<=20; r++)
    {
        for(q=0; q<=100000000; q++); //to display the character slowly
        printf("%c",177);
    }
    gotoxy(30,16);
    printf ("Press any key to continue.");
    getch();
}

void gotoxy(int x, int y)
{

    COORD destination;
    HANDLE depart;

    destination.X = x;

    destination.Y = y;

    depart =GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition (depart , destination);

}

void FoodCoord()
{
    if(head.x==food.x&&head.y==food.y) // when the snake eat the food
    {
        length++;
        time_t a;
        a=time(0);
        srand(a);

        food.x=rand()%70;
        if(food.x<=10)food.x+=11;

        food.y=rand()%30;
        if(food.y<=10) food.y+=11;


    }
    else if(food.x==0)  // to create food for the first time because global variable are initialized with 0
    {
        food.x=rand()%70;
        if(food.x<=10) food.x+=11;

        food.y=rand()%30;
        if(food.y<=10) food.y+=11;

    }
}

void BordersFoodDisplay()
{
    system("cls");
    int i;
    gotoxy (food.x,food.y);
    printf("F"); // display food

    for(i=10; i<71; i++)
    {
        gotoxy (i,10);
        printf("!");
        gotoxy (i,30);
        printf("!");
    }

    for(i=10; i<31; i++)
    {
        gotoxy (10,i);
        printf("!");
        gotoxy (70,i);
        printf("!");
    }
}

void Move()
{
    int a,i;
    do
    {
        FoodCoord();
        fflush(stdin);
        len=0;

        for(i=0; i<30; i++)
        {
            body[i].x=0;
            body[i].y=0;
            if(i==length) break;
        }
        Delay(length);
        BordersFoodDisplay();

        if(head.direction==RIGHT)    Right();
        else if(head.direction==LEFT)    Left();
        else if(head.direction==DOWN)    Down();
        else if(head.direction==UP)     Up();

        ExitGame();
    }
    while(!kbhit());


    a=getch();
    if(a==27) /// if the player press esc
    {
        system("cls");
        exit(0);
    }


    key=getch();
    if((key==RIGHT&&head.direction!=LEFT&&head.direction!=RIGHT)||(key==LEFT&&head.direction!=RIGHT&&head.direction!=LEFT)||(key==UP&&head.direction!=DOWN&&head.direction!=UP)||(key==DOWN&&head.direction!=UP&&head.direction!=DOWN))
    {
        bend_no++;
        bend[bend_no]=head;
        head.direction=key;
        if(key==UP)      head.y--;
        if(key==DOWN)    head.y++;
        if(key==RIGHT)   head.x++;
        if(key==LEFT)    head.x--;
        Move();
    }

    else if(key==27)
    {
        system("cls");
        exit(0);
    }

    else
    {
        printf("\a");
        Move();
    }
}



void Delay(long double k)
{
    Score();
    long double i;
    for(i=0; i<=(1000000); i++);
}
int Score()
{
    int score;
    gotoxy(20,8);
    score=length-5;
    printf("SCORE : %d",score);
    gotoxy(50,8);
    printf("Life : %d",life);
    return score;
}

void Left()
{
    int i;
    for(i=0; i<=(bend[bend_no].x-head.x)&&len<length; i++)
    {
        gotoxy((head.x+i),head.y);
        {
            if(len==0)  printf("<");
            else        printf("*");
        }
        body[len].x=head.x+i;
        body[len].y=head.y;
        len++;
    }
    Bend();
    if(!kbhit()) head.x--;
}

void Right()
{
    int i;
    for(i=0; i<=(head.x-bend[bend_no].x)&&len<length; i++)
    {
        body[len].x=head.x-i;
        body[len].y=head.y;
        gotoxy (body[len].x,body[len].y);
        {
            if(len==0)  printf(">");
            else        printf("*");
        }
        len++;
    }
    Bend();
    if(!kbhit()) head.x++;
}

void Up()
{
    int i;
    for(i=0; i<=(bend[bend_no].y-head.y)&&len<length; i++)
    {
        gotoxy(head.x,head.y+i);
        {
            if(len==0)   printf("^");
            else         printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y+i;
        len++;
    }
    Bend();
    if(!kbhit())    head.y--;
}

void Down()
{
    int i;
    for(i=0; i<=(head.y-bend[bend_no].y)&&len<length; i++)
    {
        gotoxy(head.x,head.y-i);
        {
            if(len==0)  printf("v");
            else   printf("*");
        }
        body[len].x=head.x;
        body[len].y=head.y-i;
        len++;
    }
    Bend();
    if(!kbhit()) head.y++;
}

void Bend()
{
    int i,j,diff;
    for(i=bend_no; i>=0&&len<length; i--)
    {
        if(bend[i].x==bend[i-1].x)
        {
            diff=bend[i].y-bend[i-1].y;
            if(diff<0)
                for(j=1; j<=(-diff); j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y+j;
                    gotoxy(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length) break;
                }

            else if(diff>0)
                for(j=1; j<=diff; j++)
                {
                    body[len].x=bend[i].x;
                    body[len].y=bend[i].y-j;
                    gotoxy(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length) break;
                }
        }

        else if(bend[i].y==bend[i-1].y)
        {
            diff=bend[i].x-bend[i-1].x;
            if(diff<0)
                for(j=1; j<=(-diff)&&len<length; j++)
                {
                    /*gotoxy((bend[i].x+j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x+j;
                    body[len].y=bend[i].y;
                    gotoxy(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)  break;
                }
            else if(diff>0)
                for(j=1; j<=diff&&len<length; j++)
                {
                    /*gotoxy((bend[i].x-j),bend[i].y);
                    printf("*");*/
                    body[len].x=bend[i].x-j;
                    body[len].y=bend[i].y;
                    gotoxy(body[len].x,body[len].y);
                    printf("*");
                    len++;
                    if(len==length)  break;
                }
        }
    }
}

void ExitGame()
{
    int i,check=0;
    for(i=4; i<length; i++) //starts with 4 because it needs minimum 4 element to touch its own body
    {
        if(body[0].x==body[i].x&&body[0].y==body[i].y)  check++;    //check's value increases as the coordinates of head is equal to any other body coordinate
        if(i==length||check!=0)  break;
    }

    if(head.x<=10||head.x>=70||head.y<=10||head.y>=30||check!=0)
    {
        life--;
        if(life>=0)
        {
            head.x=25;
            head.y=20;
            bend_no=0;
            head.direction=RIGHT;
            Move();
        }
        else
        {
            system("cls");
            printf("All lives completed\nBetter Luck Next Time!!!\nPress any key to quit the game\n");
            Record();
            exit(0);
        }
    }
}

void Record()
{
    char plname[20],nplname[20],cha,c;
    int i,j,px;
    FILE *info;
    info=fopen("record.txt","a+");
    getch();
    system("cls");
    printf("Enter your name\n");
    scanf("%[^\n]",plname);


    for(j=0; plname[j]!='\0'; j++) ///to convert the first letter after space to capital
    {
        nplname[0]=toupper(plname[0]);
        if(plname[j-1]==' ')
        {
            nplname[j]=toupper(plname[j]);
            nplname[j-1]=plname[j-1];
        }
        else nplname[j]=plname[j];
    }
    nplname[j]='\0';
    fprintf(info,"Player Name :%s\n",nplname);


    time_t mytime;
    mytime = time(NULL);
    fprintf(info,"Played Date:%s",ctime(&mytime));

    fprintf(info,"Score:%d\n",px=Scoreonly()); //call score to display score

    for(i=0; i<=50; i++)
        fprintf(info,"%c",'_');
    fprintf(info,"\n");
    fclose(info);
    printf("Wanna see records ? Press y \n :");
    cha=getch();
    system("cls");
    if(cha=='y')
    {
        info=fopen("record.txt","r");
        do
        {
            putchar(c=getc(info));
        }
        while(c!=EOF);
    }
    fclose(info);
}

int Scoreonly()
{
    int score=Score();
    system("cls");
    return score;
}
