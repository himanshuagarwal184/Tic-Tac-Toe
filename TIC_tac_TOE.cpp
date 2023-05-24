#include<iostream>
#include<windows.h>
using namespace std;

#define computer 1
#define human 2

#define computerMove 'O'
#define humanMove 'X'

#define SIDE 3

void showBoard(char Board[][SIDE]) // SHOWS THE CONTENT IN TIC TAC TOE
{
    printf("\t\t\t %c | %c | %c\n",Board[0][0],Board[0][1],Board[0][2]);
    printf("\t\t\t ---------\n");
    printf("\t\t\t %c | %c | %c\n",Board[1][0],Board[1][1],Board[1][2]);
    printf("\t\t\t ---------\n");
    printf("\t\t\t %c | %c | %c\n",Board[2][0],Board[2][1],Board[2][2]);
    printf("\n\n");
}

void initialise(char Board[][SIDE]) // INITIALISE ALL THE CONTENT WITH *
{
    char c='*';
    for(int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
        {
            Board[i][j]=c;
        }
    }
}

void winnerDeclare(int whoseTurn) // DECLARE THE WINNER OF GAME
{
    if(whoseTurn==computer)
    {
        cout<<"COMPUTER WON THE GAME !!!!!!!!!!!!\n\n\a\a";
    }
    if(whoseTurn==human)
    {
        cout<<"HUMAN WON THE GAME !!!!!!!!!!!!\n\n\a\a";
    }
}

void showInstruction() // SHOWS THE INSTRUCTIONS TO PLAY THE GAME 
{
    printf("choose a block from 1 to 9 as below and play \n\n");
    
    printf("\t\t\t 1 | 2 | 3\t\n");
    printf("\t\t\t ---------\t\n");
    printf("\t\t\t 4 | 5 | 6\t\n");
    printf("\t\t\t ---------\t\n");
    printf("\t\t\t 7 | 8 | 9\n");
    printf("\n\n");
}

bool rowCrossed(char Board[][SIDE]) // CHECKS IF ANY OF THE ROWS IN TIC TAC TOE IS MATCHED
{
    for(int i=0;i<SIDE;i++)
    {
        if(Board[i][0] == Board[i][1] && Board[i][1] == Board[i][2] && Board[i][0]!='*')
        {
            return true;
        }
    }
    return false;
}
bool columnCrossed(char Board[][SIDE]) // CHECKS IF ANY OF THE ROWS IN TIC TAC TOE IS MATCHED
{
    for(int i=0;i<SIDE;i++)
    {
        if(Board[0][i] == Board[1][i] && Board[1][i] == Board[2][i] && Board[0][i]!='*')
        {
            return true;
        }
    }
    return false;
}

bool diagonalCrossed(char Board[][SIDE]) // CHECKS IF ANY OF THE ROWS IN TIC TAC TOE IS MATCHED
{
    if(Board[0][0] == Board[1][1] && Board[1][1] == Board[2][2] && Board[0][0]!='*')
    {
        return true;
    }
    else if(Board[0][2] == Board[1][1] && Board[1][1] == Board[2][0] && Board[2][0]!='*')
    {
        return true;
    }
    return false;
}

bool gameOver(char Board[][SIDE])
{
    return (rowCrossed(Board) || columnCrossed(Board) || diagonalCrossed(Board));
}

int minimax(char Board[][SIDE],int depth,bool AI)
{
    int score=0,bestScore=0;
    if(gameOver(Board) == true)     // TERMINATION CONDITION
    {
        if(AI == true)
        {
            return -10;
        }
        if(AI == false)
        {
            return 10;
        }
    }
    else
    {
        if(depth < 9)
        {
            if(AI == true)
            {
                bestScore=-999;
                for(int i=0;i<SIDE;i++)
                {
                    for(int j=0;j<SIDE;j++)
                    {
                        if(Board[i][j]=='*')
                        {
                            Board[i][j]=computerMove;
                            score = minimax(Board,depth+1,false);
                            Board[i][j]='*';
                            if(score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        
            else
            {
                bestScore=999;
                for(int i=0;i<SIDE;i++)
                {
                    for(int j=0;j<SIDE;j++)
                    {
                        if(Board[i][j] == '*')
                        {
                            Board[i][j]=humanMove;
                            score = minimax(Board,depth+1,true);
                            Board[i][j]='*';
                            if(score < bestScore)
                            {
                                bestScore=score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        
    }
    return 0;
}


int bestMove(char Board[][SIDE],int moveIndex)
{
    int x=-1,y=-1;
    int score=0,bestScore=-999;
    
    for(int i=0;i<SIDE;i++)
    {
        for(int j=0;j<SIDE;j++)
        {
            if(Board[i][j] == '*')
            {
                Board[i][j]=computerMove;
                score = minimax(Board,moveIndex+1,false);
                Board[i][j]='*';
                
                if(score > bestScore)
                {
                    bestScore = score;
                    x=i;
                    y=j;
                }
            }
        }
    }
    return (x*3+y);
}

void playTicTacToe(int whoseTurn)
{
    char Board[SIDE][SIDE];
    int moveIndex=0,x=0,y=0;
    initialise(Board);
    showInstruction();
    

    while(gameOver(Board) == false && moveIndex!= SIDE * SIDE)
    {
        int n;
        if(whoseTurn == computer)
        {
            cout<<"hj";
            n=bestMove(Board,moveIndex);
            x=n/SIDE;
            y=n%SIDE;
            Board[x][y]=computerMove;
            showBoard(Board);
            cout<<"\n\n";
            moveIndex++;
            whoseTurn = human;
        }
        else if(whoseTurn == human)
        {
            cout<<"You can insert at the following position : \n";
            for(int i=0;i<SIDE;i++)
            {
                for(int j=0;j<SIDE;j++)
                {
                    if(Board[i][j] == '*')
                    {
                        cout<< (i*3+j)+1 <<" ";
                    }
                }
            }
            cout<<"Enter the position you want : ";
            scanf("%d",&n);
            n--;
            x=n/SIDE;
            y=n%SIDE;
            if(Board[x][y] !='*' && n<9 && n>=0)
            {
                printf("Position is already occupied!! \n PLEASE ENTER A SUITABLE POSITION : ");

            }
            else if(Board[x][y] =='*' && n<9 && n>=0)
            {
                Board[x][y]=humanMove;
                
                showBoard(Board);
                moveIndex++;
                whoseTurn=computer;
            }
            else
            {
                printf("PLEASE ENTER A VALID POSITION !!\a\a");
            }
        }
    }
    if(gameOver(Board)==false && moveIndex==SIDE*SIDE)
    {
        printf("It is a DRAW !!!! \n\a");
    }
    else
    {
        if(whoseTurn==human)
        {
            whoseTurn=computer;
        }
        else{
            whoseTurn=human;
        }
        winnerDeclare(whoseTurn);
    }
}

int main()
{
    int x,ch='a';
    // while(ch=='q' || ch=='Q')
    // {
    //     cout<<"Press Y to start first or N to start second: ";
    //     scanf("%c",&x);
    //     if(x=='Y' || x=='y')
    //     {
    //         playTicTacToe(human);
    
    //     }
    //     else if(x=='N' || x=='n')
    //     {
    //         playTicTacToe(computer);
    //     }
    //     else
    //     {
    //         printf("Enter a valid choice Y or N\n");
    //     }
    //     printf("Press Q to quit : ");
    //     scanf("%c",&ch);
        
    // }
    playTicTacToe(human);
   // playTicTacToe(computer);
    return 0;
}