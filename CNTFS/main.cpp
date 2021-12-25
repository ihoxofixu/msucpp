#include "CNTFS.hpp"
#include "autotest.hpp"
#include <iostream>

using namespace std;


int main(){
	Autotest();
	int capacity = 1024;
	while (true){
    cout << "Please enter the capactiy of your system(default 1024 bytes): ";
    string s_num = "";
    getline(cin, s_num);
    int tmp_num = 0;
    bool correct_num = true;
    for (int i = 0; i < s_num.size(); i++){
      if (s_num[i] - '0' >= 0 && '9' - s_num[i] >= 0){
        tmp_num *= 10;
        tmp_num += s_num[i] - '0';
      }
      else{
        correct_num = false;
      }
    }
    if (correct_num){
      if (s_num.size() > 0){
				capacity = tmp_num;
			}
      break;
    }
    else{
      cout << "Invalid number \'" << s_num << "\', please try again\nTo set the capacity to default press enter\n";
    }
  }
	cout << "Capacity is set to " << capacity << " bytes\n";
  CNTFS FS(capacity);
  cout << "Hello, user\nFor help use command \'-help\'\n";
  while (true){
    cout << "Please, enter your command: ";
    string current_command;
    getline(cin, current_command);
    if (current_command == "-help"){
      cout << "List of commands:\n    \'-help\' to get help\n    \'-quit\' to quit the programm\n    \'-list\' to see the list of all files\n    \'-makefile\' to make a new file\n    \'-rename\' to change the name of a file\n    \'-delete\' to delete a file\n    \'-filesize\' to get size of a file\n    \'-write\' to write to file\n    \'-read\' to read from file\n";
    }
    else if (current_command == "-quit"){
      break;
    }
    else if(current_command == "-list"){
      FS.listfiles();
    }
    else if(current_command == "-makefile"){
			cout << "Please enter the name of a file: ";
			string filename;
			getline(cin, filename);
			bool correct_result = FS.makefile(filename);
			if (correct_result){
				cout << "done\n";
			}
    }
    else if(current_command == "-rename"){
			cout << "Please enter the name of a file you want to rename: ";
			string oldname;
			getline(cin, oldname);
			cout << "Please enter new name: ";
			string newname;
			getline(cin, newname);
			bool correct_result = FS.renamefile(oldname, newname);
			if (correct_result){
				cout << "done\n";
			}
    }
    else if(current_command == "-delete"){
			cout << "Please enter the name of a file you eant to delete: ";
			string filename;
			getline(cin, filename);
			bool correct_result = FS.deletefile(filename);
			if (correct_result){
				cout << "done\n";
			}
    }
		else if(current_command == "-filesize"){
			cout << "Please enter the name of a file: ";
			string filename;
			getline(cin, filename);
			int correct_result = FS.getfilelength(filename);
			if (correct_result != -1){
				cout << "Size of this file is " << correct_result << " bytes\n";
			}
    }
		else if(current_command == "-write"){
			cout << "Please enter the name of a file you want to write to: ";
			string filename;
			getline(cin, filename);
			cout << "Please enter data: ";
			string data;
			getline(cin, data);
			cout << "Please enter shift(default 0): ";
			string sshift;
			getline(cin, sshift);
			int shift = 0;
			for (int i = 0; i < sshift.size(); i++){
				shift *= 10;
				shift += int(sshift.at(i)) - int('0');
			}
			FS.writefile(filename, data, shift);
    }
		else if(current_command == "-read"){
			cout << "Please enter the name of a file you want to read from: ";
			string filename;
			getline(cin, filename);
			cout << "Please enter size you want to read: ";
			string sdatasize;
			getline(cin, sdatasize);
			int datasize = 0;
			for (int i = 0; i < sdatasize.size(); i++){
				datasize *= 10;
				datasize += int(sdatasize.at(i)) - int('0');
			}
			cout << "Please enter shift(default 0): ";
			string sshift;
			getline(cin, sshift);
			int shift = 0;
			for (int i = 0; i < sshift.size(); i++){
				shift *= 10;
				shift += int(sshift.at(i)) - int('0');
			}
			cout << FS.readfile(filename, datasize, shift) << endl;
    }
    else{
      cout << "Unrecognised command \'" << current_command << "\', please enter \'-help\' for help\n";
    }
  }
	return 0;
}
