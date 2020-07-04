#include <iostream>
#include <vector>
using namespace std;
class Node {
  public:
    long left;
    long right;
    long val;
    long laz;
};
void set(vector<Node> &ns, long ind, long left, long right) {
  ns[ind].left=left;
  ns[ind].right=right;
  long m=(left+right)/2;
  if (left!=right) {
    set(ns,2*ind+1,left,m);
    set(ns,2*ind+2,m+1,right);
  }
  ns[ind].val=ns[ind].laz=0;
}
void add(vector<Node> &ns, long ind, long l, long r, long v) {
  if(ns[ind].left==l && ns[ind].right==r) {
    if (l!=r)
      ns[ind].laz+=v;
    else
      ns[ind].val+=v;
  }
  else {
    long m=(ns[ind].left+ns[ind].right)/2;
    ns[ind].val=(ns[ind].val+(r-l+1)*v)%1000000007;
    if(r<=m) {
      add(ns,2*ind+1,l,r,v);
    }
    else if(l>m) {
      add(ns,2*ind+2,l,r,v);
    }
    else {
      add(ns,2*ind+1,l,m,v);
      add(ns,2*ind+2,m+1,r,v);
    }
  } 
}
long get(vector<Node> &ns, long ind, long l, long r, long lz, long qn) {
  long m, newlz=lz;
  m=(l+r)/2;
  if(l==r) {
    ns[ind].val=(ns[ind].val+lz)%1000000007;
    return ns[ind].val;
  }
  newlz=(newlz+ns[ind].laz)%1000000007;
  ns[ind].laz=0;
  ns[ind].val=(ns[ind].val+newlz*(r-l+1))%1000000007;
  if (qn<=m) {
    add(ns,2*ind+2,m+1,r,newlz);
    return get(ns,2*ind+1,l,m,newlz,qn);
  }
  else {
    add(ns,2*ind+1,l,m,newlz);
    return get(ns,2*ind+2,m+1,r,newlz,qn);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  vector<Node> nodes;
  for(int i=1;i<=t;i++) {
    long n,k;
    long res = 0;
    cin >> n >> k;
    for(int j=0;j<3*n;j++)
      nodes.push_back(Node());
    set(nodes,0,1,n);

    for(int j=0;j<k;j++) {
      char q;
      cin >> q;
      if (q=='i') {
        long l, r, v;
        cin >> l >> r >> v;
        add(nodes,(long)0,l,r,v);
      }
      else {
        long qn;
        cin >> qn;
        res=(get(nodes,(long)0,(long)1,n,(long)0,qn)%1000000007+res)%1000000007;
      }
    }
    nodes.clear();
    cout << "Case #" << i << ": " << res << "\n";
  }
}