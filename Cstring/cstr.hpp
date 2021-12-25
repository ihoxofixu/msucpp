#ifndef CSTR_HPP_INCLUDED
#define CSTR_HPP_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class CString {
private:
  int length;
  char* stroka;
public:
  void set_str(int len);

  void set_element(int pos, char el);

  char get_element(int pos);

  int get_length();

  CString(char* tmp, int len);

  CString(CString &tmp);

  CString();

  ~CString();

  CString& operator= (const CString& a);

  CString& operator= (const string& a);

  const CString operator+ (const CString a);

};

#endif
