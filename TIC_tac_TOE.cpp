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

void TicTacToe()
{
    string player1,player2;
    cout<<"Enter the name of player 1 : ";
    cin.ignore();
    cin>>player1;
    cout<<"Enter the name of player 2 : ";
    cin.ignore();
    cin>>player2;
    x:
        cout<<"who will play first ,"<<player1<<" or "<<player2<<" : ";
        string p;
        cin>>p;
    if(p!=player1 && p!=player2)
    {
        cout<<p<<" is not a registered player"<<endl;
        goto x;
    }
    if(p!=player1)
    {
        swap(player1,player2);
    }
    char Board[SIDE][SIDE];
    initialise(Board);
    showInstruction();
    char ch1='X';
    int moveIndex=0;    
    p=player1;
    while(gameOver(Board) == false && moveIndex!=SIDE*SIDE)
    {
        showBoard(Board);
        
        cout<<"CURRENT TURN : "<<p<<endl;   
        cout<<"\nYou can insert at the following position : \n";
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
        int n,x,y;
        cin>>n;
        n--;
        x=n/SIDE;
        y=n%SIDE;
        if(Board[x][y]!='*' && n<9 && n>=0)
        {
            cout<<"\nTHE POSITION IS ALREADY OCCUPIED .."<<endl<<"Enter a VALID position : "<<endl;
        }
        else if(Board[x][y]=='*' && n<9 && n>=0)
        {
            Board[x][y]=ch1;
            if(ch1=='X')
            {
                p=player2;
                ch1='O';
            }
            else{
                p=player1;
                ch1='X';
            }
            moveIndex++;
        }
        else
        {
            cout<<"Enter A Valid Position ..."<<endl;
        }
        
    }
    if(gameOver(Board)==false && moveIndex==SIDE*SIDE)
    {
        cout<<"IT IS A DRAW "<<endl;
    }
    else
    {
        showBoard(Board);
        if(ch1=='O')
        {
            cout<<"\n"<<player1<<" WON !!!!!!"<<endl;

        }
        else
        {
            cout<<"\n"<<player2<<" WON !!!!!!!"<<endl;
        }
    }
    
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
            cout<<"\nEnter the position you want : ";
            cin>>n;
            n--;
            x=n/SIDE;
            y=n%SIDE;
            if(Board[x][y] !='*' && n<9 && n>=0)
            {
                printf("\nPosition is already occupied!! \n PLEASE ENTER A SUITABLE POSITION : ");

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
        printf("\nIt is a DRAW !!!! \n\a");
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
    int x,ch;
    int choice;
    while(true)
    {   
           y:
            cout<<"\nPress 1 for Player VS AI\nPress 2 for Player VS Player :\n";
            cin>>choice;
        switch(choice)
        {
            case 1:
                int ch;
                cout<<"\nEnter who will play first chance\nPress 1 for human\nPress 2 for AI :1\n ";
                cin>>ch;
                while(ch!=1 && ch!=2)
                {
                    cout<<"Invalid Option Please Enter a Valid Choice"<<endl;
                    cout<<"\nEnter 1 for Human\nEnter 2 for AI"<<endl;
                    cin>>ch;
                }
                if(ch==1)
                {

                    playTicTacToe(human);
                    break;
                }
                else
                {
                    playTicTacToe(computer);
                    break;
                }
                break;
            case 2:
                TicTacToe();
                    break;
            default:
                goto y;
        }
        char x;
        z:
            cout<<"\nDo you want to play again? (y/n): ";
            cin>>x;
        if(x=='n' || x=='N')
        {
            cout<<"\nTHANKS FOR PLAYING\n";
            return 0;
        }
        else if(x!='Y' && x!='y')
        {
            cout<<"\nEnter a valid choice "<<endl;
            goto z;
        }
        cout<<"\n\n\n";
    }
    return 0;
}