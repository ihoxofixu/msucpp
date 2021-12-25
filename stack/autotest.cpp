#ifndef AUTOTEST_CPP
#define AUTOTEST_CPP

#include "autotest.hpp"
#include "stack.hpp"

using namespace std;


void test1(){
  Stack tmp(100);
  string s = "test";
  for (int i = 0; i < 10; i++)
  {
    tmp.add_string(s);
  }
  int total = tmp.get_amount_of_elements();
  if (total == 10){
    cout << "Test 1: Correct\n";
  }
  else{
    cout << "Test 1: Wrong\n";
  }
}

void test2(){
  Stack tmp(100);
  string s = "test_string";
  tmp.add_string(s);
  int l = tmp.get_string_length();
  if (l == 11){
    cout << "Test 2: Correct\n";
  }
  else{
    cout << "Test 2: Wrong\n";
  }
}

void test3(){
  Stack tmp(100);
  string s = "test_string", s2;
  tmp.add_string(s);
  tmp.copy_string_to(&s2);
  if (s2 == "test_string"){
    cout << "Test 3: Correct\n";
  }
  else{
    cout << "Test 3: Wrong\n";
  }
}

void test4(){
  Stack tmp(100);
  vector<string> vs = {"test_string", "test-string"};
  for (auto s: vs){
    tmp.add_string(s);
  }
  tmp.delete_last();
  string s2;
  tmp.copy_string_to(&s2);
  if (s2 == "test_string"){
    cout << "Test 4: Correct\n";
  }
  else{
    cout << "Test 4: Wrong\n";
  }
}

void test5(){
  Stack tmp(100);
  vector<string> vs = {"test_string", "test-string"};
  for (auto s: vs){
    tmp.add_string(s);
  }
  tmp.save_stack_to_buffer();
  fstream buffer_file("buffer");
  int it = 0;
  string ss;
  while (getline(buffer_file, ss)){
    if (ss != vs[it]){
      break;
    }
    it += 1;
  }
  if (it == vs.size()){
    cout << "Test 5: Correct\n";
  }
  else{
    cout << "Test 5: Wrong\n";
  }
  buffer_file.close();
}

void test6(){
  Stack tmp(100);
  vector<string> vs = {"test_string", "test-string"};
  fstream buffer_file("buffer", ios::out);
  for (auto s: vs){
    buffer_file << s << endl;
  }
  buffer_file.close();
  tmp.load_stack_from_buffer();
  int it = 0;
  for (int i = 1; i >= 0; i--){
    string s2;
    tmp.copy_string_to(&s2);
    if (s2 != vs[i]){
      break;
    }
    it += 1;
    tmp.delete_last();
  }
  if (it == vs.size()){
    cout << "Test 6: Correct\n";
  }
  else{
    cout << "Test 6: Wrong\n";
  }
}

void test7(){
  Stack tmp(100);
  string s = "very_very_very_long_test";
  for (int i = 0; i < 10; i++)
  {
    tmp.add_string(s);
  }
  int total = tmp.get_amount_of_elements();
  if (total == 10){
    cout << "Test 7: Correct\n";
  }
  else{
    cout << "Test 7: Wrong\n";
  }
}

void test8(){
  Stack tmp(100);
  string s = "test_string";
  tmp.add_string(s);
  tmp.save_stack_to_buffer();
  int l = tmp.get_string_length();
  if (l == 11){
    cout << "Test 8: Correct\n";
  }
  else{
    cout << "Test 8: Wrong\n";
  }
}

void test9(){
  Stack tmp(100);
  string s = "test_string", s2;
  tmp.add_string(s);
  tmp.save_stack_to_buffer();
  tmp.copy_string_to(&s2);
  if (s2 == "test_string"){
    cout << "Test 9: Correct\n";
  }
  else{
    cout << "Test 9: Wrong\n";
  }
}

void test10(){
  Stack tmp(100);
  vector<string> vs = {"test_string", "test-string"};
  for (auto s: vs){
    tmp.add_string(s);
  }
  tmp.save_stack_to_buffer();
  tmp.delete_last();
  string s2;
  tmp.copy_string_to(&s2);
  if (s2 == "test_string"){
    cout << "Test 10: Correct\n";
  }
  else{
    cout << "Test 10: Wrong\n";
  }
}

void test11(){
  Stack tmp(100);
  string s = "very_very_very_long_test";
  for (int i = 0; i < 10; i++)
  {
    tmp.add_string(s);
  }
  tmp.clear_stack();
  int total = tmp.get_amount_of_elements();
  if (total == 0){
    cout << "Test 11: Correct\n";
  }
  else{
    cout << "Test 11: Wrong\n";
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
  test8();
  test9();
  test10();
  test11();
}

#endif
