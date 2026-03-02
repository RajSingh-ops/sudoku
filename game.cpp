#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <ctime>
using namespace std;

bool check(vector<vector<char>>& b, int row, int col, char ch) {
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

bool fillBoard(vector<vector<char>>& b,int row,int col){
    if(row==9) return true;

    if(col==9) return fillBoard(b,row+1,0);

    if(b[row][col]!='.')
        return fillBoard(b,row,col+1);

    vector<char> nums={'1','2','3','4','5','6','7','8','9'};
    random_shuffle(nums.begin(),nums.end());

    for(char ch:nums){
        if(check(b,row,col,ch)){
            b[row][col]=ch;
            if(fillBoard(b,row,col+1))
                return true;
            b[row][col]='.';
        }
    }
    return false;
}

void removeCells(vector<vector<char>>& b,int removeCount){
    while(removeCount>0){
        int r=rand()%9;
        int c=rand()%9;
        if(b[r][c]!='.'){
            b[r][c]='.';
            removeCount--;
        }
    }
}

int main(){
    srand(time(0));

    vector<vector<char>> board(9,vector<char>(9,'.'));

    fillBoard(board,0,0);
    removeCells(board,40);

    for(auto &row:board){
        for(auto &c:row)
            cout<<c<<" ";
        cout<<endl;
    }

    return 0;
}