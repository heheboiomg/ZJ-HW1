#include <bits/stdc++.h>
using namespace std;

int M=0,P=0;

map<int,map<int,int>> maze;
map<int,map<int,int>> visited;
vector<pair<int,int>> now;
vector<pair<int,int>> finish;

int c_right[] = {1,0}; //往右走一個column
int r_down[] = {0,1};  //往下走一個row

//由北開始順時鐘方向依序搜八個方向
int c_any[] = {0,1,1,1,0,-1,-1,-1};
int r_any[] = {-1,-1,0,1,1,1,0,-1};

//只往右跟往下找的函式
bool DFS_RightAndDown(int r , int c){
    //如果成功走到底了就結束
    if(r==M && c==P){
        now.push_back({r,c});
        finish = now;
        now.pop_back();
        return true;
    }

    //把現在的位置變成visited(檢查"已造訪的位置不得再次進入"時會用到) 跟 目前的路徑
    visited[r][c]=true;
    now.push_back({r,c});

    //走兩個方向(先右再下)
    for(int i=0;i<2;++i){
        int new_c=c+c_right[i];
        int new_r=r+r_down[i];
    
    //檢查是否還在迷宮的範圍內
    if(new_r>=1 && new_r<=M && new_c>=1 && new_c <=P){
        //檢查格子是不是0且還沒走過    
        if(maze[new_r][new_c]==0 && !visited[new_r][new_c]){
            if(DFS_RightAndDown(new_r,new_c)){ //用遞迴來重複這個函式，一直探索可以走到哪裡
                now.pop_back();
                return true;    //如果找到就一路回傳true
                }
            }
        }
    }

    //如果此路不通就往回退，之後就要採用任意方向(往回退的同時把不通的路徑刪掉)
    now.pop_back();
    return false;
}

bool DFS_Any(int r , int c){
    if(r==M && c==P){
        now.push_back({r,c});
        finish = now;
        now.pop_back();
        return true;
    }

    visited[r][c]=true;
    now.push_back({r,c});

    for(int i=0;i<8;++i){
        int new_c=c+c_any[i];
        int new_r=r+r_any[i];
    
    if(new_r>=1 && new_r<=M && new_c>=1 && new_c <=P){ 
        if(maze[new_r][new_c]==0 && !visited[new_r][new_c]){
            if(DFS_Any(new_r,new_c)){
                now.pop_back();
                return true;
                }
            }
        }
    }

    //如果任意方向再不通，那就是兩種方式都無法抵達出口
    now.pop_back();
    return false;
}


int main(){

    if(!(cin>>M>>P)){
        return 0;
    }

    //讀取迷宮資料、存到maze裡面
    for(int i=1;i<=M;++i){
        for(int j=1;j<=P;++j){
            int value;
            cin>>value;
            maze[i][j]=value;
        }
    }

    if(maze[1][1]==1 || maze[M][P]==1){
        cout<<"No path"<<endl;
        return 0;
    }

    //先把那些map跟vector都先clear、順便重置visited
    now.clear();
    finish.clear();
    for(int i=1;i<=M;++i){
        for(int j=1;j<=P;++j){
            visited[i][j]=false;
        }
    }

    //開始先嘗試直角前進
    if(DFS_RightAndDown(1,1)){
        cout<<"Forward:"<<finish.size()<<endl;

        for(int i=(int)finish.size()-1;i>=0;--i){
            cout<<"("<<finish[i].first<<","<<finish[i].second<<")";
            if(i>0){
                cout<<"<-";
            }
        }
        cout<<endl;
        return 0; //找到就提早結束程式
    }

    //直角前進失敗，全部重新來並改用任意方向搜尋
    now.clear();
    finish.clear();
    for(int i=1;i<=M;++i){
        for(int j=1;j<=P;++j){
            visited[i][j]=false;
        }
    }

    //改以八方向任意搜尋
    if(DFS_Any(1,1)){
        cout<<"Any:"<<finish.size()<<endl;

        for(int i=(int)finish.size()-1;i>=0;--i){
            cout<<"("<<finish[i].first<<","<<finish[i].second<<")";
            if(i>0){
                cout<<"<-";
            }
        }
        cout<<endl;
        return 0; 
    }

    //如果都失敗就no path
    cout<<"No path"<<endl;

    return 0;
}
