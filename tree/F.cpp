#include <iostream>
#include <vector>
using namespace std;
class Node {
  public:
    int left;
    int right;
    long val;
    bool clr;
};
void set(vector<Node> &ns, int ind, int left, int right) {
  ns[ind].left=left;
  ns[ind].right=right;
  int m=(left+right)/2;
  if (left!=right) {
    set(ns,2*ind+1,left,m);
    set(ns,2*ind+2,m+1,right);
  }
  ns[ind].val=0;
  ns[ind].clr=false;
}
void add(vector<Node> &ns, int ind, int left, int right, int p, bool clr) {
  if (ns[ind].clr) {
    clr=true;
    ns[ind].clr=false;
  }
  if (clr) {
    ns[ind].val=0;
  }
  (ns[ind].val)++;
  if(left==right) {
    return;
  }
  int m=(left+right)/2;
  if(p<=m) {
    if (clr)
      ns[2*ind+2].clr=true;
    add(ns,2*ind+1,left,m,p,clr);
  }
  else {
    if (clr)
      ns[2*ind+1].clr=true;
    add(ns,2*ind+2,m+1,right,p,clr);
  }
}
long get(vector<Node> &ns, int ind, int l, int r, int ql, int qr) {
  if (ns[ind].clr) {
    return 0;
  }
  if((ql==l) && (qr==r)) {
    ns[ind].clr=true;
    return ns[ind].val;
  }
  int m=(l+r)/2;
  if(qr<=m) {
    long r1;
    r1 = get(ns,2*ind+1,l,m,ql,qr);
    ns[ind].val-=r1;
    return r1;
  }
  else if(ql>m) {
    long r1;
    r1 = get(ns,2*ind+2,m+1,r,ql,qr);
    ns[ind].val-=r1;
    return r1;
  }
  else {
    long r1,r2;
    r1=get(ns,2*ind+1,l,m,ql,m);
    r2=get(ns,2*ind+2,m+1,r,m+1,qr);
    ns[ind].val-=(r1+r2);
    return r1+r2;
  }
}
long del(vector<Node> &ns, int ind, int left, int right, int p) {
  if (ns[ind].clr==true) {
    return 0;
  }
  long ret=0;
  if(left==right) {
    if(ns[ind].clr) {
      ns[ind].val=0;
      ns[ind].clr=false;
    }
    if(ns[ind].val > 0)
      ret=1;
  }
  else {
    int m=(left+right)/2;
    if(p<=m) {
      ret=del(ns,2*ind+1,left,m,p);
    }
    else{
      ret=del(ns,2*ind+2,m+1,right,p);
    }
  }
  ns[ind].val-=ret;
  return ret;
}
int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  int t;
  cin >> t;
  vector<Node> nodes;
  for(int i=1;i<=t;i++) {
    int n,k;
    cin >> n >> k;
    for(int j=0;j<3*n;j++)
      nodes.push_back(Node());
    set(nodes,0,1,n);
    long total = 0;
    char op;
    int sp, ca, cb, dp;
    for(int j=0;j<k;j++) {
      cin >> op;
      if (op=='s') {
        cin >> sp;
        add(nodes,0,1,n,sp,false);
      }
      else if (op=='c') {
        cin >> ca >> cb;
        total+=get(nodes,0,1,n,ca,cb);
      }
      else {
        cin >> dp;
        del(nodes,0,1,n,dp);
      }
    }
    nodes.clear();
    cout << "Case #" << i << ": " << total << '\n';
  }
}