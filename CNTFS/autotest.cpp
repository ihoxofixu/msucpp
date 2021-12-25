#ifndef AUTOTEST_CPP
#define AUTOTEST_CPP

#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include "CNTFS.hpp"

using namespace std;


void test1(){
  CNTFS FS;
  FS.makefile("tmpfile");
  ifstream tmp("$MFT", ifstream::binary);
  string line;
  getline(tmp, line);
  if (line.compare("tmpfile\r") == 0){
    cout << "Test 1 correct\n";
  }
  else{
    cout << "Test 1 wrong\n";
  }
}

void test2(){
  CNTFS FS;
  FS.makefile("tmpfile");
  bool flag = FS.such_file_exist("tmpfile");
  if (flag){
    cout << "Test 2 correct\n";
  }
  else{
    cout << "Test 2 wrong\n";
  }
}

void test3(){
  CNTFS FS;
  bool flag = FS.such_file_exist("tmpfile");
  if (!flag){
    cout << "Test 3 correct\n";
  }
  else{
    cout << "Test 3 wrong\n";
  }
}

void test4(){
  CNTFS FS;
  FS.makefile("tmpfile");
  FS.deletefile("tmpfile");
  bool flag = FS.such_file_exist("tmpfile");
  if (!flag){
    cout << "Test 4 correct\n";
  }
  else{
    cout << "Test 4 wrong\n";
  }
}

void test5(){
  CNTFS FS;
  FS.makefile("tmpfile");
  FS.renamefile("tmpfile", "tmpfile2");
  bool flag = FS.such_file_exist("tmpfile");
  bool flag2 = FS.such_file_exist("tmpfile2");
  if (!flag and flag2){
    cout << "Test 5 correct\n";
  }
  else{
    cout << "Test 5 wrong\n";
  }
}

void test6(){
  CNTFS FS;
  FS.makefile("tmpfile");
  FS.writefile("tmpfile", "test");
  int flag = FS.getfilelength("tmpfile");
  if (flag == 4){
    cout << "Test 6 correct\n";
  }
  else{
    cout << "Test 6 wrong\n";
  }
}

void test7(){
  CNTFS FS;
  FS.makefile("tmpfile");
  FS.writefile("tmpfile", "test");
  FS.renamefile("tmpfile", "tmpfile2");
  int flag = FS.getfilelength("tmpfile2");
  if (flag == 4){
    cout << "Test 7 correct\n";
  }
  else{
    cout << "Test 7 wrong\n";
  }
}

void Autotest(){
  test1();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
}

#endif
