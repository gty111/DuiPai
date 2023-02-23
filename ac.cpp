#include <bits/stdc++.h>
using namespace std;
// #define DEBUG
int N,curN;
struct Node{
    double minlen;
    vector<double> vecx,vecy;
};

#ifdef DEBUG
void printNode(Node *n,int curN){
    printf("begin\n");
    for(int i=0;i<curN;i++){
        printf("-------------------\n");
        for(int j=0;j<n[i].vecx.size();j++){
            printf("%lf %lf %lf\n",n[i].vecx[j],n[i].vecy[j],n[i].minlen);
        }
    }
    printf("end\n");
}
#endif

bool cmp(Node &n1,Node &n2){
    return n1.vecx[0] <= n2.vecx[0];
}

double calDis(double x1,double y1,double x2,double y2){
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void MergeVec(Node &n1,Node &n2,Node &dest){
    vector<double> tvecx,tvecy;
    int idx1=0,idx2=0;
    while(idx1!=n1.vecy.size()||idx2!=n2.vecy.size()){
        if(idx1==n1.vecy.size()){
            tvecy.push_back(n2.vecy[idx2]);
            tvecx.push_back(n2.vecx[idx2]);
            idx2++;
        }else if(idx2==n2.vecy.size()){
            tvecy.push_back(n1.vecy[idx1]);
            tvecx.push_back(n1.vecx[idx1]);
            idx1++;
        }else if(n1.vecy[idx1]>=n2.vecy[idx2]){
            tvecy.push_back(n1.vecy[idx1]);
            tvecx.push_back(n1.vecx[idx1]);
            idx1++;
        }else{
            tvecy.push_back(n2.vecy[idx2]);
            tvecx.push_back(n2.vecx[idx2]);
            idx2++;
        }
    }
    dest.vecx = tvecx;
    dest.vecy = tvecy;
}

double Nearest(Node &n,double x,double y,double h){
    double ret = h;
    for(int i=0;i<n.vecx.size();i++){
        if(abs(x - n.vecx[i]) > h) continue;
        if(n.vecy[i]-y > h) continue;
        else if(y - n.vecy[i] > h)break;
        ret = min(ret,calDis(x,y,n.vecx[i],n.vecy[i]));
    }
    return ret;
}

double Nearest(Node &n1,Node &n2,double h){
    double ret = h;
    double xm = n1.vecx[0];
    // set B
    vector<double>tx,ty;
    for(int i=1;i<n1.vecx.size();i++){
        xm = max(xm,n1.vecx[i]);
    }
    int idx1 = 0, idx2 = 0;
    while(abs(xm-n1.vecx[idx1])>h&&idx1!=n1.vecx.size())idx1++;
    while(abs(xm-n2.vecx[idx2])>h&&idx2!=n2.vecx.size())idx2++;
    while(idx1!=n1.vecx.size()||idx2!=n2.vecx.size()){
        if(idx1==n1.vecx.size()){
            tx.push_back(n2.vecx[idx2]);
            ty.push_back(n2.vecy[idx2]);
            idx2++;
            while(abs(xm-n2.vecx[idx2])>h&&idx2!=n2.vecx.size())idx2++;
        }else if(idx2==n2.vecx.size()){
            tx.push_back(n1.vecx[idx1]);
            ty.push_back(n1.vecy[idx1]);
            idx1++;
            while(abs(xm-n1.vecx[idx1])>h&&idx1!=n1.vecx.size())idx1++;
        }else if(n1.vecy[idx1]>n2.vecy[idx2]){
            tx.push_back(n1.vecx[idx1]);
            ty.push_back(n1.vecy[idx1]);
            idx1++;
            while(abs(xm-n1.vecx[idx1])>h&&idx1!=n1.vecx.size())idx1++;
        }else{
            tx.push_back(n2.vecx[idx2]);
            ty.push_back(n2.vecy[idx2]);
            idx2++;
            while(abs(xm-n2.vecx[idx2])>h&&idx2!=n2.vecx.size())idx2++;
        }
    }

    for(int i=0;i<tx.size();i++){
        for(int j=i+1;j<tx.size();j++){
            if(ty[i]-ty[j]>h)break;
            if(abs(tx[i]-tx[j])>h)continue;
            ret = min(ret,calDis(tx[i],ty[i],tx[j],ty[j]));
        }
    }

    return ret;
}

void Mymerge(Node &n1,Node &n2,Node &dest){
    double h,minlen;
    if(n1.minlen==-1&&n2.minlen==-1){
        #ifdef DEBUG
        assert(n1.vecx.size()==1&&n2.vecy.size()==1);
        assert(n2.vecx.size()==1&&n2.vecy.size()==1);
        #endif
        minlen = calDis(n1.vecx[0],n1.vecy[0],n2.vecx[0],n2.vecy[0]);
    }else if(n1.minlen==-1&&n2.minlen!=-1){
        #ifdef DEBUG
        assert(n1.vecx.size()==1||n1.vecy.size()==1);
        #endif
        h = n2.minlen;
        minlen = Nearest(n2,n1.vecx[0],n1.vecy[0],h);
    }else if(n1.minlen!=-1&&n2.minlen==-1){
        #ifdef DEBUG
        assert(n2.vecx.size()==1||n2.vecy.size()==1);
        #endif
        h = n1.minlen;
        minlen = Nearest(n1,n2.vecx[0],n2.vecy[0],h);
    }else{
        h = min(n1.minlen,n2.minlen);
        minlen = min(h,Nearest(n1,n2,h));
    }

    dest.minlen = minlen;
    MergeVec(n1,n2,dest);
}

void reduce(Node *n,int len){
    #ifdef DEBUG
    assert(len%2==0);
    #endif

    for(int i=0;i<len;i+=2){
        Mymerge(n[i],n[i+1],n[i/2]);
    }

}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    setiosflags(ios::fixed);

    cin >> N;
    curN = N;
    Node n[N];
    for(int i=0;i<N;i++){
        double tx,ty;
        cin >> tx >> ty;
        n[i].vecx.push_back(tx);
        n[i].vecy.push_back(ty);
        n[i].minlen = -1;
    }

    // sort by dimx
    sort(n,n+N,cmp);
    
    
    // reduce
    while(curN!=1){
        #ifdef DEBUG
        printNode(n,curN);
        #endif
        if(curN%2!=0){
            reduce(&n[1],curN-1);
            curN = (curN+1)/2;
        }else{
            reduce(&n[0],curN);
            curN /= 2;
        }
    }
    cout << setiosflags(ios::fixed) << setprecision(8) << n[0].minlen << '\n';
}
