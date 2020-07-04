#include <iostream>
using namespace std;
class Node {
  public:
    long left;
    long right;
    long val;
    long laz;
};
void set(Node nodes[], long ind, long left, long right) {
  nodes[ind].left=left;
  nodes[ind].right=right;
  long m=(left+right)/2;
  if (left!=right) {
    set(nodes,2*ind+1,left,m);
    set(nodes,2*ind+2,m+1,right);
  }
  nodes[ind].val=nodes[ind].laz=0;
}
void add(Node ns[], long ind, long l, long r, long v) {
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
long get(Node ns[], long i, long l, long r, long lz, long qn) {
  long m, newlz=lz;
  m=(l+r)/2;
  if(l==r) {
    ns[i].val=(ns[i].val+lz)%1000000007;
    return ns[i].val;
  }
  newlz=(newlz+ns[i].laz)%1000000007;
  ns[i].laz=0;
  ns[i].val=(ns[i].val+newlz*(r-l+1))%1000000007;
  if (qn<=m) {
    add(ns,2*i+2,m+1,r,newlz);
    return get(ns,2*i+1,l,m,newlz,qn);
  }
  else {
    add(ns,2*i+1,l,m,newlz);
    return get(ns,2*i+2,m+1,r,newlz,qn);
  }
}
#define cin strin
#include <sstream>
#include <cstdlib>
#include <ctime>
int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(NULL);
  string ii="5\n";
  srand(time(nullptr));
  for(int i=0;i<5;i++) {
    // int n = rand()%(1000000)+1;
    // int k = rand()%(100000)+1;
    int n = rand()%(100)+1;
    int k = rand()%(10)+1;
    ii+=(to_string(n)+' '+to_string(k)+'\n');
    for(int j=0;j<k;j++) {
      if (rand()%2==0) {
        int ss = rand()%n+1;
        int ee = rand()%n+1;
        int vv = rand()%1000+1;
        if(ss>ee) {
          int temp;
          temp=ss;
          ss=ee;
          ee=temp;
        }
        ii+=("i "+to_string(ss)+' '+to_string(ee)+' '+to_string(vv)+'\n');
      }
      else {
        int gl = rand()%n+1;
        ii+=("q "+to_string(gl)+'\n');
      }
    }
    ii+='\n';
  }
  cout << ii;
  istringstream strin(ii);

  int t;
  cin >> t;
  for(int i=1;i<=t;i++) {
    long n,k;
    long res = 0;
    cin >> n >> k;
    Node* nodes = new Node[3*n];
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
    delete[] nodes;
    cout << "Case #" << i << ": " << res << "\n";
  }
}