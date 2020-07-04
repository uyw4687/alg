#include <iostream>
#include <vector>
using namespace std;
class Node {
  public:
    int left;
    int right;
    int val;
    int laz;
};
void set(vector<Node> &ns, int ind, int left, int right) {
  ns[ind].left=left;
  ns[ind].right=right;
  int m=(left+right)/2;
  if (left!=right) {
    set(ns,2*ind+1,left,m);
    set(ns,2*ind+2,m+1,right);
  }
  ns[ind].val=ns[ind].laz=0;
}
void update(vector<Node> &ns, int ind, int left, int right, int l, int r, int v) {
  if(left==l && right==r) {
    if (l!=r)
      ns[ind].laz=max(v,ns[ind].laz);
    else
      ns[ind].val=max(v,ns[ind].val);
  }
  else {
    int m=(left+right)/2;
    ns[ind].val=max(v,ns[ind].val);
    if(r<=m) {
      update(ns,2*ind+1,left,m,l,r,v);
    }
    else if(l>m) {
      update(ns,2*ind+2,m+1,right,l,r,v);
    }
    else {
      update(ns,2*ind+1,left,m,l,m,v);
      update(ns,2*ind+2,m+1,right,m+1,r,v);
    }
  } 
}
int find(vector<Node> &ns, int ind, int l, int r, int ql, int qr, int lz) {
  if((ql==l) && (qr==r)) {
    if(l==r) {
      ns[ind].val=max(lz,ns[ind].val);
      return ns[ind].val;
    }
    else {
      ns[ind].laz=max(lz,ns[ind].laz);
      return max(ns[ind].laz,ns[ind].val);
    }
  }
  int newlz=max(lz,ns[ind].laz);
  ns[ind].laz=0;
  ns[ind].val=max(newlz,ns[ind].val);
  int m=(l+r)/2;
  if(qr<=m) {
    find(ns,2*ind+2,m+1,r,m+1,r,newlz);
    return find(ns,2*ind+1,l,m,ql,qr,newlz);
  }
  else if(ql>m) {
    find(ns,2*ind+1,l,m,l,m,newlz);
    return find(ns,2*ind+2,m+1,r,ql,qr,newlz);
  }
  else {
    int r1,r2;
    r1=find(ns,2*ind+1,l,m,ql,m,newlz);
    r2=find(ns,2*ind+2,m+1,r,m+1,qr,newlz);
    return max(r1,r2);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  vector<Node> nodes;
  for(int i=1;i<=t;i++) {
    int n,k;
    int highest = 0;
    int res;
    cin >> n >> k;
    for(int j=0;j<3*n;j++)
      nodes.push_back(Node());
    set(nodes,0,0,n-1);
    cout << "Case #" << i << ":";
    for(int j=0;j<k;j++) {
      int w, h, p;
      cin >> w >> h >> p;
      res=find(nodes,0,0,n-1,p,p+w-1,0);
      update(nodes,0,0,n-1,p,p+w-1,res+h);
      if(res+h>highest)
        highest=res+h;
      cout << " " << highest;

    }
    nodes.clear();
    cout << "\n";
  }
}