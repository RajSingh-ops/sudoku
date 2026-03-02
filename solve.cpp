#include <iostream>
#include <vector>
using namespace std;

bool check(vector<vector<char>>& b,int row,int col,char ch){
    for(int i=0;i<9;i++){
        if(b[row][i]==ch) return false;
        if(b[i][col]==ch) return false;
    }

    int sr=(row/3)*3;
    int sc=(col/3)*3;

    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            if(b[sr+i][sc+j]==ch)
                return false;

    return true;
}

bool solve(vector<vector<char>>& b,int row,int col){
    if(row==9) return true;

    if(col==9) return solve(b,row+1,0);

    if(b[row][col]!='.')
        return solve(b,row,col+1);

    for(char ch='1';ch<='9';ch++){
        if(check(b,row,col,ch)){
            b[row][col]=ch;
            if(solve(b,row,col+1))
                return true;
            b[row][col]='.';
        }
    }
    return false;
}

int main(){

    vector<vector<char>> board(9,vector<char>(9));

    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
            cin>>board[i][j];

    if(solve(board,0,0)){
        for(auto &row:board){
            for(auto &c:row)
                cout<<c<<" ";
            cout<<endl;
        }
    }
    else{
        cout<<"No solution";
    }

    return 0;
}