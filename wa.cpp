#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N;
struct Node{
    double x,y;
};
Node n[MAXN];
bool cmp(Node &n1,Node &n2){
    return n1.x <= n2.x;
}
double calDis(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
int cnt;
Node tn[MAXN];
int idx[MAXN];
int tmp[MAXN];

void myMerge(int l,int r){
    int mid = (l+r)/2;
    memcpy(tmp,idx+l,(r-l+1)*sizeof(int));
    int idx1 = 0,idx2 = mid+1-l;
    while(idx1!=mid+1-l||idx2!=r+1-l){
        if(idx1==mid+1-l){
            idx[idx2+l] = tmp[idx2];
            idx2++;
        }else if(idx2==r+1-l){
            idx[idx1+l] = tmp[idx1];
            idx1++;
        }else if(n[tmp[idx1]].y>=n[tmp[idx2]].y){
            idx[idx1+l] = tmp[idx1];
            idx1++;
        }else{
            idx[idx2+l] = tmp[idx2];
            idx2++;
        }
    }
}

double solve(int l,int r){
    if(r-l==1){
        return calDis(n[l].x,n[l].y,n[r].x,n[r].y);
    }
    if(r==l)return DBL_MAX;
    int mid = (l+r)/2;
    double d1 = solve(l,mid);
    double d2 = solve(mid+1,r);
    double ret = min(d1,d2);
    myMerge(l,r);
    cnt = 0;
    for(int i=l;i<=r;i++){
        if(abs(n[idx[i]].x-n[mid].x)<=ret){
            tn[cnt++] = {n[idx[i]].x,n[idx[i]].y};
        }
    }
    
    for(int i=0;i<cnt;i++){
        for(int j=i+1;j<cnt;j++){
            if(tn[i].y-tn[j].y>ret)break;
            if(abs(tn[i].x-tn[j].x)>ret)continue;
            ret = min(ret,calDis(tn[i].x,tn[i].y,tn[j].x,tn[j].y));
        }
    }
    return ret;
}
int main(){
    scanf("%d",&N);
    for(int i=0;i<N;i++){
        scanf("%lf %lf",&n[i].x,&n[i].y);
    }
    sort(n,n+N,cmp);
    for(int i=0;i<MAXN;i++){
        idx[i] = i;
    }

    double ret = solve(0,N-1);
    printf("%.8lf\n",ret);
}