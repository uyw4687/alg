#include <iostream>
#include <cstring>
#include <deque>
#include <algorithm>
using namespace std;

//c++11
int lcs(char* x, deque<char> y, int lenx, int leny){
  int result[251][251]={0};
  int plus;

  for(int i=1;i<=lenx;i++) {
    for(int j=1;j<=leny;j++) {
      plus=(x[i-1]==y[j-1])?1:0;
      //c++11
      result[i][j] = max({result[i-1][j-1]+plus, result[i-1][j], result[i][j-1]});
    }
  }
  return result[lenx][leny];
}

int lcsring(char* x, char* y, int lenx, int leny){
  int maxval=0;
  deque<char> dequey(y,y+strlen(y));
  int result;
  for(int i=0;i<leny;i++) {
    result=lcs(x, dequey, lenx, leny);
    if(result==leny)
      return leny;
    if(result>maxval)
      maxval=result;
    dequey.push_back(dequey.front());
    dequey.pop_front();
  };
  reverse(dequey.begin(), dequey.end());
  for(int i=0;i<leny;i++) {
    result=lcs(x, dequey, lenx, leny);
    if(result==leny)
      return leny;
    if(result>maxval)
      maxval=result;
    dequey.push_back(dequey.front());
    dequey.pop_front();
  }
  return maxval;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  cin >> t;
  for(int i=0;i<t;i++) {
    char a[250], b[250];
    cin >> a >> b;
    int lena=strlen(a), lenb=strlen(b);
    int result;
    if(lena>=lenb)
      result=lcsring(a,b,lena,lenb);
    else
      result=lcsring(b,a,lenb,lena);
    cout << "Case #" << i+1 << ": " << result << "\n";
  }
}