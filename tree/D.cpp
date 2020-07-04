#include <iostream>
#include <vector>
using namespace std;
class Node {
  public:
    int left;
    int right;
    int val;
};
int set(vector<Node> &ns, vector<int> &vdepth, int ind, int left, int right) {
  ns[ind].left=left;
  ns[ind].right=right;
  if (left==right) {
    ns[ind].val=vdepth[left];
    return ns[ind].val;
  }
  int m=(left+right)/2;
  int minl, minr;
  if (left!=right) {
    minl=set(ns,vdepth,2*ind+1,left,m);
    minr=set(ns,vdepth,2*ind+2,m+1,right);
  }
  ns[ind].val=min(minl,minr);
  return ns[ind].val;
}
int find(vector<Node> &ns, int ind, int l, int r, int ql, int qr) {
  if((ql==l) && (qr==r)) {
    return ns[ind].val;
  }
  int m=(l+r)/2;
  if(qr<=m) {
    return find(ns,2*ind+1,l,m,ql,qr);
  }
  else if(ql>m) {
    return find(ns,2*ind+2,m+1,r,ql,qr);
  }
  else {
    int r1,r2;
    r1=find(ns,2*ind+1,l,m,ql,m);
    r2=find(ns,2*ind+2,m+1,r,m+1,qr);
    return min(r1,r2);
  }
}
void trav(vector<vector<int>> &adj, vector<int> &rmq, vector<int> &vdepth, vector<int> &ersterbesuch, int c, int depth) {
  ersterbesuch[c]=rmq.size();
  rmq.push_back(c);
  vdepth.push_back(depth);
  vector<int> cv = adj[c];
  for(int i=0;i<cv.size();i++) {
    trav(adj,rmq,vdepth,ersterbesuch,cv[i]-1,depth+1);
    rmq.push_back(c);
    vdepth.push_back(depth);
  }
}
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  vector<Node> nodes;
  vector<vector<int>> adj;
  for(int i=1;i<=t;i++) {
    int n;
    cin >> n;
    for(int j=0;j<n;j++) {
      int d;
      cin >> d;
      vector<int> adjv;
      int adjt;
      for(int k=0;k<d;k++) {
        cin >> adjt;
        adjv.push_back(adjt);
      }
      adj.push_back(adjv);
    }
    vector<int> rmq;
    vector<int> vdepth;  
    vector<int> ersterbesuch(n,-1);  
    trav(adj,rmq,vdepth,ersterbesuch,0,0);
    int rmqsize=rmq.size();
    for(int j=0;j<3*rmqsize;j++)
      nodes.push_back(Node());
    set(nodes,vdepth,0,0,rmqsize-1);
    long total=0;

    int cb=1, e1=ersterbesuch[0], e2, mine, maxe;
    int nb;
    cin >> nb;
    int tb;
    int lca;
    for(int j=0;j<nb;j++) {
      cin >> tb;
      e2=ersterbesuch[tb-1];
      mine=min(e1,e2);
      maxe=max(e1,e2);
      lca=find(nodes,0,0,rmqsize-1,mine,maxe);
      total+=((vdepth[e1]-lca)+(vdepth[e2]-lca));
      cb=tb;
      e1=e2;
    }
    cout << "Case #" << i << ": " << total << '\n';
    adj.clear();
    nodes.clear();
  }
}