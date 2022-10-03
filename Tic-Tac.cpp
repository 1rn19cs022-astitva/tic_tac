#include<bits/stdc++.h>
using namespace std;

int m=0;

void printmatrix(string a[3][3]){ //Prints the matrix
    int x,y,i,j;
    for(i=0;i<3;i++){
        if(i==0)
            cout<<"\n-------------\n";
        for(j=0;j<3;j++){
            if(j==0)
                cout<<"| ";
            cout<<a[i][j]<<" | ";
        }
        if(i!=2)
            cout<<"\n----+---+----";
        else
            cout<<"\n-------------";
        cout<<"\n";
        
    }
}
//------------------------------------------------------------------------------------
int check(string a[3][3], int num,string turn,int ai)
{
    char z;
    if(  a[0][0] == a[0][1] && a[0][1] == a[0][2] && a[0][0]==turn
          || a[1][0] == a[1][1] && a[1][1] == a[1][2] && a[1][0]==turn 
          || a[2][0] == a[2][1] && a[2][1] == a[2][2] && a[2][0]==turn 
          || a[0][0] == a[1][0] && a[1][0] == a[2][0] && a[0][0]==turn 
          || a[0][1] == a[1][1] && a[1][1] == a[2][1] && a[0][1]==turn 
          || a[0][2] == a[1][2] && a[1][2] == a[2][2] && a[0][2]==turn 
          || a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[0][0]==turn
          || a[2][0] == a[1][1] && a[1][1] == a[0][2] && a[2][0]==turn ){ //Checks if 3 continous cells have either O or X respectively
            if(ai==0){
            printmatrix(a);    
            cout<<"Player "<<num<<" wins!!\n";
            cout<<"Enter any key to exit\n";
            cin>>z;
            exit(0);
            }
            return 0;
    }
    else{
        return 1;
    }  
}
//--------------------------------------------------------------------------------------------
int verify(string a[3][3],int x,int y,string t, int ai)
{

    if(a[x-1][y-1]=="X" || a[x-1][y-1]=="O" || x>3 || y>3)  //Check if current cell is empty or not
    {
            if(ai==0){
            cout<<"\nInvalid move!!\nTry again.\n\n";
            }
            return 1;
    } 
    else
    {
        a[x-1][y-1]=t; //If current cell is empty, puts the respective character in it
        return 0;
    }  
}
//---------------------------------------------------------------------------------------------------
void player(string a[3][3],int num,string turn,int ai,int mode){
    int b=0,c=0,x,y,i,j,flag=1,flag2=0,emptycell=0,match1,match2;
    srand(time(0));
    if(ai==0){                                                     //Player's move
        while (flag)
        {
            cout<<"Player "<<num<<"'s turn\n";
            while(!(cin>>x>>y)){
                cout<<"Invalid input\n";
                cin.clear();
                cin.ignore();
            }
            flag=verify(a,x,y,turn,ai);
        }
    }

    else if(ai==1 && (mode==2 || mode==3)){   //AI's move
        m++;                      
        if((a[1][1]==" ") && mode==3 && m<=2 && !(verify(a,2,2,turn,ai))){ //Hard mode : Detects if middle cell is empty or not, if it is then puts an O in it, else puts O at 1st edge cell.

        }
        else if((a[1][1]=="X" || a[1][1]=="O")  && mode==3 && (m<=4) && a[0][2]==" "){
            if((verify(a,1,1,turn,ai)==1) ){
                a[0][2]=turn;
            }
                
        }
        else{                      // Medium mode and Hard mode after the first moves have been performed                             
            for(i=0;i<3;i++){
                for(j=0;j<3;j++){
                    if(turn=="O"){
                        emptycell=verify(a,i+1,j+1,"O",ai); //verifies if current cell is empty, puts an O if it is
                        if(emptycell==0){
                            match2=check(a,2,"O",0); //checks if the next move by ai results in a win 
                            if(match2==1){
                                a[i][j]=" "; //removes the O if ai wont win in next move
                            }
                        }
                        emptycell=verify(a,i+1,j+1,"X",ai); //verifies if current cell is empty, puts an X if it is
                        if(emptycell==0){
                            match1=check(a,1,"X",ai); //checks if the next move by the player results in a win
                            if(match1==0){
                                flag2=1;
                                a[i][j]="O"; //if the opponent wins in the next move, puts an X in the cell
                                break;
                            }
                            else if(match1==1){
                                a[i][j]=" "; //empties the cell if player doesn't win
                            }
                        }
                    }
                    else if(turn=="X"){
                        emptycell=verify(a,i+1,j+1,"X",ai); //verifies if current cell is empty, puts an X if it is
                        if(emptycell==0){
                            match2=check(a,2,"X",ai); //checks if the next move by ai results in a win 
                            if(match2==1){
                                a[i][j]=" "; //removes the O if ai wont win in next move
                            }
                        }
                        emptycell=verify(a,i+1,j+1,"O",ai); //verifies if current cell is empty, puts an /O if it is
                        if(emptycell==0){
                            match1=check(a,1,"O",ai); //checks if the next move by the player results in a win
                            if(match1==0){
                                flag2=1;
                                a[i][j]="X";
                                break; 
                            }
                            else if(match1==1){
                                a[i][j]=" "; //empties the cell if player doesn't win
                            }
                        }
                    }
                }
            if(flag2==1){
                break;
                }
            }
            flag=1;
            while (flag && !flag2)
            {
                b=rand()%3;
                c=rand()%3;
                flag=verify(a,b+1,c+1,turn,ai); //Puts an O or X at a random empty position
            }
        }
    }

    else if(ai==1 && mode==1){ //Easy mode
        flag=1;
        while (flag)
        {
            b=rand()%3;
            c=rand()%3;
            flag=verify(a,b+1,c+1,turn,ai); //Puts an O at a random empty position
        }

    }
    //cout << "\033[2J\033[1;1H";
    printmatrix(a);
    check(a,num,turn,0); //Checks if current player won
}

//------------------------------------------------------------------------------------------------------
void pvp(string a[3][3], int f){ //Player vs Player mode
    cout << "\033[2J\033[1;1H";
    printmatrix(a);
    while(1){
        player(a,1,"X",0,1); f++;
        if(f>=9){
            printmatrix(a);
            cout<<"Match draw!!";
            exit(0);
        }
        player(a,2,"O",0,1); f++;
    }
}

//------------------------------------------------------------------------------------------------------
void pveeasy(string a[3][3],int f,int v){ //Easy mode vs AI
    cout << "\033[2J\033[1;1H";
    int chance1,chance2;
    if(v==1){chance1=0;chance2=1;}
    else{chance1=1;chance2=0;}
    printmatrix(a);
    while(1){
        player(a,1,"X",chance1,1); f++;
        if(f>=9){
            printmatrix(a);
            cout<<"Match draw!!";
            exit(0);
        }
        player(a,2,"O",chance2,1); f++;
    }
}
//-------------------------------------------------------------------------------------------------------
void pvemedium(string a[3][3],int f,int v){ //Medium mode vs AI
    cout << "\033[2J\033[1;1H";
    int chance1,chance2;
    if(v==1){chance1=0;chance2=1;}
    else{chance1=1;chance2=0;}
    printmatrix(a);
    while(1){
        
        player(a,1,"X",chance1,2); f++;
        if(f>=9){
            cout<<"Match draw!!";
            exit(0);
        }
        player(a,2,"O",chance2,2); f++;
    }
}
//-------------------------------------------------------------------------------------------------------
void pvehard(string a[3][3],int f,int v){ //Hard mode vs AI
    char z;
    cout << "\033[2J\033[1;1H";
    int chance1,chance2;
    if(v==1){chance1=0;chance2=1;}
    else{chance1=1;chance2=0;}
    printmatrix(a);
    while(1){
        player(a,1,"X",chance1,3); f++;
        if(f>=9){
            cout<<"Match draw!!\n";
            cout<<"Enter any key to exit\n";
            cin>>z;
            exit(0);
        }
        player(a,2,"O",chance2,3); f++;
    }
}
//-------------------------------------------------------------------------------------------------------

void eveeasy(string a[3][3],int f){ //Easy mode AI vs AI
    //cout << "\033[2J\033[1;1H";
    int r;
    printmatrix(a);
    while(1){
        player(a,1,"X",1,1); f++;
        if(f>=9){
            printmatrix(a);
            cout<<"Match draw!! Press 1 to repeat, any other key to exit\n";
            cin>>r;
            if(r==1){
                f=0,m=0;
                string a[3][3]={{" "," "," "}, //Re-Initializing the matrix
                {" "," "," "},
                {" "," "," "}};
                eveeasy(a,f);
            }
            else{
                exit(0);
            }
            exit(0);
        }
        player(a,2,"O",1,1); f++;
    }
}
//-------------------------------------------------------------------------------------------------------

void evemedium(string a[3][3],int f){ //Medium mode AI vs AI
    //cout << "\033[2J\033[1;1H";
    int r;
    printmatrix(a);
    while(1){
        player(a,1,"X",1,2); f++;
        if(f>=9){
            printmatrix(a);
            cout<<"Match draw!! Press 1 to repeat\n";
            cin>>r;
            if(r==1){
                f=0,m=0;
                string a[3][3]={{" "," "," "}, //Re-Initializing the matrix
                {" "," "," "},
                {" "," "," "}};
                evemedium(a,f);
            }
            else{
                exit(0);
            }
            exit(0);
            
        }
        player(a,2,"O",1,2); f++;
    }
}
//-------------------------------------------------------------------------------------------------------

void evehard(string a[3][3],int f){ //Hard mode AI vs AI
    int r;
    //cout << "\033[2J\033[1;1H";
    printmatrix(a);
    while(1){
        player(a,1,"X",1,3); f++;
        
        if(f>=9){
            printmatrix(a);
            cout<<"Match draw!! Press 1 to repeat, any other key to exit\n";
            cin>>r;
            if(r==1){
                f=0;m=0;
                string a[3][3]={{" "," "," "}, //Re-Initializing the matrix
                {" "," "," "},
                {" "," "," "}};
                evehard(a,f);
            }
            else{
                exit(0);
            }
            exit(0);
        }
        player(a,2,"O",1,3); f++;
    }
}

//-------------------------------------------------------------------------------------------------------
int main(){
    string a[3][3]={{" "," "," "}, //Initializing the matrix
                {" "," "," "},
                {" "," "," "}}; 
    int b,c,f=0,v;
    cout<<"Choose your game mode\n1.PvP\n2.PvE\n3.EvE\n4.Exit\n\n";
    cin>>c;
    switch(c){  //Select gamemode
        case 1:pvp(a,f);
            break;
        case 2:cout<<"1.Easy\n2.Medium\n3.Hard\n\n";
                cin>>b;
                cout<<"1.Player first\n2.AI first\n\n";
                cin>>v;
                switch(b){
                    case 1:pveeasy(a,f,v);
                        break;
                    case 2:pvemedium(a,f,v);
                        break;
                    case 3:pvehard(a,f,v);
                        break;
                    default:cout<<"Invalid input\n";
                };
            break;
        case 3:cout<<"1.Easy\n2.Medium\n3.Hard\n\n";
                cin>>b;
                switch(b){
                    case 1:eveeasy(a,f);
                        break;
                    case 2:evemedium(a,f);
                        break;
                    case 3:evehard(a,f);
                        break;
                    default:cout<<"Invalid input\n";
                };
            break;
        case 4:exit(0);
        default:cout<<"Invalid input\n";
    }
    return 0;
    
}