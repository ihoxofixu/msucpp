#include <iostream>
#include <string>
#include "cstr.cpp"
//#include "autotest.hpp"

using namespace std;

int main(){
  //Autotest();
  int n;
  cin >> n;
  char* a = new char[n];
  for (int i = 0; i < n; i++){
    cin >> a[i];
  }
  CString s1(a, n);
  int m;
  cin >> m;
  char* b = new char[m];
  for (int i = 0; i < m; i++){
    cin >> b[i];
  }
  CString s2(b, m);
  CString s3;
  s3 = s1 + s2;
  for (int i = 0; i < s3.get_length(); i++){
    cout << s3.get_element(i);
  }
  cout << endl;
  string ss;
  cin >> ss;
  s3 = ss;
  for (int i = 0; i < s3.get_length(); i++){
    cout << s3.get_element(i);
  }
  cout << endl;
  delete []a;
  delete []b;
}
