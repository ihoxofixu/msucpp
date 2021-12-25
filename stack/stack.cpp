#ifndef STACK_CPP
#define STACK_CPP

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "stack.hpp"

using namespace std;


Stack::Stack(int maxi){
  max_capacity = maxi;
  total_current_length = 0;
  stack_buffer.clear();

  fstream buffer_file("buffer", ios::out);
  buffer_file.close();
}


void Stack::clear_stack(){
  total_current_length = 0;
  stack_buffer.clear();

  fstream buffer_file("buffer", ios::out);
  buffer_file.close();
}

int Stack::get_amount_of_elements(){
  int local_amount = stack_buffer.size();
  fstream buffer_file("buffer");
  string tmp;
  int buffer_amount = 0;
  while (getline(buffer_file, tmp)){
    buffer_amount += 1;
  }
  return local_amount + buffer_amount;
}

void Stack::save_stack_to_buffer(){
  fstream buffer_file("buffer", ios::app);
  for (auto s: stack_buffer){
    buffer_file << s << endl;
  }
  buffer_file.close();
  total_current_length = 0;
  stack_buffer = {};
}

bool Stack::add_string(const string tmp){
  if (total_current_length + tmp.size() <= max_capacity){
    total_current_length += tmp.size();
    stack_buffer.push_back(tmp);
    return true;
  }
  else if (tmp.size() <= max_capacity) {
    save_stack_to_buffer();
    total_current_length = tmp.size();
    stack_buffer.push_back(tmp);
    return true;
  }
  else{
    cout << "Sorry, but length of a string is more than the capacity of the stack\n";
    return false;
  }
}

void Stack::load_stack_from_buffer(){
  while (stack_buffer.size() < get_amount_of_elements()){
    fstream buffer_file("buffer");
    fstream new_buffer_file("new_buffer", ios::out);
    string tmp, tmp_prev = "\0";
    while (getline(buffer_file,tmp)){
      if (tmp_prev != "\0"){
        new_buffer_file << tmp_prev << endl;
      }
      tmp_prev = tmp;
    }
    buffer_file.close();
    new_buffer_file.close();
    remove("buffer");
    rename("new_buffer", "buffer");
    if (total_current_length + tmp_prev.size() <= max_capacity){
      total_current_length += tmp_prev.size();
      stack_buffer.push_back(tmp_prev);
    }
    else{
      buffer_file.open("buffer", ios::app);
      buffer_file << tmp_prev << endl;
      buffer_file.close();
      break;
    }
  }
  reverse(stack_buffer.begin(), stack_buffer.end());
}

int Stack::get_string_length(){
  if (total_current_length != 0){
    return stack_buffer.back().size();
  }
  else if (get_amount_of_elements() == 0){
    cout << "Your stack is empty\n";
    return 0;
  }
  else{
    load_stack_from_buffer();
    return get_string_length();
  }
}

void Stack::copy_string_to(string* s){
  if (stack_buffer.size() != 0){
    s->assign(stack_buffer.back());
  }
  else if (get_amount_of_elements() == 0){
      cout << "Your stack is empty\n";
      s->assign("");
  }
  else {
    load_stack_from_buffer();
    copy_string_to(s);
  }
}

bool Stack::delete_last(){
  if (total_current_length != 0){
    total_current_length -= stack_buffer.back().size();
    stack_buffer.pop_back();
    return true;
  }
  else if (get_amount_of_elements() == 0){
      cout << "Your stack is empty\n";
      return false;
  }
  else {
    load_stack_from_buffer();
    return delete_last();
  }
}

Stack::~Stack(){
  clear_stack();
}

#endif
