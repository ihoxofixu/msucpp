#ifndef CNTFS_CPP
#define CNTFS_CPP


#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <string>
#include "CNTFS.hpp"

using namespace std;


string CNTFS::inttostr(const int x){
	if (x == 0){
    return "0";
  }
  string str_x = "";
  int xx = x;
  while (xx > 0){
  	str_x = char(int('0') + xx % 10) + str_x;
    	xx /= 10;
  }
  return str_x;
}


int CNTFS::strtoint(const string x){
	int xx = 0;
	for (int i = 0; i < x.size(); i++){
		xx *= 10;
		xx += int(x.at(i)) - int('0');
	}
	return xx;
}


void CNTFS::replacefile(string oldfilename, string newfilename){
	char tmp_old[oldfilename.size()+1];
  for (int i = 0; i < oldfilename.size(); i++){
		tmp_old[i] = oldfilename.at(i);
	}
	tmp_old[oldfilename.size()] = '\0';
	char tmp_new[newfilename.size()+1];
  for (int i = 0; i < newfilename.size(); i++){
		tmp_new[i] = newfilename.at(i);
	}
	tmp_new[newfilename.size()] = '\0';
  remove(tmp_old);
  rename(tmp_new, tmp_old);
}


CNTFS::CNTFS(const int capacity, const string filename){
  	MFT_name = filename;
  	MFT_reserved = MFT_name + "_reserved";
  	capacity_bytes = capacity;
  	for (int i = 0; i < capacity; i++){
    	blocks.push_back(true);
  	}
  	ofstream MFT(filename, ifstream::binary);
  	MFT.close();
}


bool CNTFS::such_file_exist(const string filename){
 	ifstream MFT(MFT_name, ifstream::binary);
	string current_line;
	while (getline(MFT, current_line)){
		if (current_line.back() == '\r'){
			current_line.pop_back();
		}
  	current_line += ",";
    string current_file = "";
    for (int i = 0; i < current_line.size(); i++){
      if (current_line.compare(i, 1, ",") == 0){
      	break;
      }
      current_file += current_line[i];
    }
    if (current_file == filename){
    	return true;
    }
  }
  return false;
}


bool CNTFS::makefile(const string filename){
	if (filename[0] == '$'){
		cout << "Sorry, this name is reversed, pleasy try again\n";
    return false;
  }
  if (such_file_exist(filename)){
  	cout << "Such file already exist, please try again\n";
  	return false;
  }
  ofstream MFT(MFT_name, ofstream::app);
  MFT << filename << endl;
  return true;
}


bool CNTFS::deletefile(const string filename){
  if (filename[0] == '$'){
  	cout << "Sorry, this name is reversed, pleasy try again\n";
  	return false;
  }
  if (!such_file_exist(filename)){
  	cout << "Such file does not exist, please try again\n";
  	return false;
  }
  ifstream MFT(MFT_name, ifstream::binary);
  ofstream tmp_MFT(MFT_reserved, ofstream::binary);
  string current_line;
  while (getline(MFT, current_line)){
  	if (current_line.back() == '\r'){
			current_line.pop_back();
		}
    string current_file = "";
    for (int i = 0; i < current_line.size(); i++){
    	if (current_line.compare(i, 1, ",") == 0){
      	break;
    	}
      current_file += current_line.at(i);
    }
    if (current_file != filename){
    	tmp_MFT << current_line << endl;
    }
    else{
    	int cnt = 0;
    	current_line += ",";
    	current_file = "";
    	for (int i = 0; i < current_line.size(); i++){
    		if (current_line.compare(i, 1, ",") == 0){
      		cnt += 1;
      		if (cnt != 1){
      			char tmp_block_name[current_file.size() + 2];
      			tmp_block_name[0] = '$';
		  			for (int j = 1; j <= current_file.size(); j++){
		     			tmp_block_name[j] = current_file.at(j-1);
						}
						tmp_block_name[current_file.size() + 1] = '\0';
						blocks[strtoint(current_file)] = true;
						remove(tmp_block_name);
					}
					current_file = "";
        }
        else{
        	current_file += current_line.at(i);
	  		}
    	}
		}
  }
  MFT.close();
  tmp_MFT.close();
	replacefile(MFT_name, MFT_reserved);
  return true;
}


bool CNTFS::renamefile(const string oldfilename, const string newfilename){
	if (newfilename[0] == '$' || oldfilename[0] == '$'){
      	cout << "Sorry, this name is reversed, pleasy try again\n";
      	return false;
    	}
	if (!such_file_exist(oldfilename)){
  	cout << "Such file does not exist, please try again\n";
  	return false;
	}
  if (such_file_exist(newfilename)){
  	cout << "Such file already exist, please try again\n";
  	return false;
	}
	ifstream MFT(MFT_name, ifstream::binary);
	ofstream tmp_MFT(MFT_reserved, ofstream::binary);
	string current_line;
	while (getline(MFT, current_line)){
		if (current_line.back() == '\r'){
			current_line.pop_back();
		}
    string current_file = "";
    for (int i = 0; i < current_line.size(); i++){
        if (current_line.compare(i, 1, ",") == 0){
          break;
        }
        current_file += current_line.at(i);
    }
    if (current_file != oldfilename){
      tmp_MFT << current_line << endl;
  	}
    else{
      int cnt = 0;
      current_file = "";
      for (int i = 0; i < current_line.size(); i++){
        if (current_line.compare(i, 1, ",") == 0){
          cnt += 1;
          if (cnt == 1){
            current_file = newfilename;
					}
		  	}
		  	current_file += current_line.at(i);
      }
			if (cnt != 0){
				tmp_MFT << current_file << endl;
			}
			else{
				tmp_MFT << newfilename << endl;
			}
		}
  }
  MFT.close();
  tmp_MFT.close();
	replacefile(MFT_name, MFT_reserved);
  return true;
}


void CNTFS::listfiles(){
	ifstream MFT(MFT_name, ifstream::binary);
	string current_line;
	while (getline(MFT, current_line)){
		if (current_line.back() == '\r'){
			current_line.pop_back();
		}
  	string current_file = "";
  	for (int i = 0; i < current_line.size(); i++){
    	if (current_line.compare(i, 1, ",") == 0){
      	break;
    	}
    	current_file += current_line.at(i);
  	}
  	cout << current_file << endl;
	}
}


int CNTFS::getfilelength(const string filename){
	if (filename[0] == '$'){
  	cout << "Sorry, this name is reversed, pleasy try again\n";
  	return -1;
  }
  if (!such_file_exist(filename)){
  	cout << "Such file does not exist, please try again\n";
  	return -1;
  }
  ifstream MFT(MFT_name, ifstream::binary);
  string current_line;
  while (getline(MFT, current_line)){
  	if (current_line.back() == '\r'){
			current_line.pop_back();
		}
    current_line += ",";
    string current_file = "";
    for (int i = 0; i < current_line.size(); i++){
    	if (current_line.compare(i, 1, ",") == 0){
    		break;
    	}
    	current_file += current_line.at(i);
    }
    if (current_file == filename){
    	int cnt = -1;
    	for (int i = 0; i < current_line.size(); i++){
     		if (current_line.compare(i, 1, ",") == 0){
       		cnt += 1;
     		}
      }
      MFT.close();
      return cnt;
		}
  }
  MFT.close();
  cout << "Unexpected error, file not found\n";
  return -1;
}


int CNTFS::get_free_byte_pos(){
	int byte_pos = -1;
	for (int i = 0; i < blocks.size(); i++){
    if (blocks[i]){
     	byte_pos = i;
     	blocks[i] = false;
     	break;
    }
  }
  return byte_pos;
}


bool CNTFS::writefile(const string filename, const string data, int shift){
  	if (filename[0] == '$'){
  		cout << "Sorry, this name is reversed, pleasy try again\n";
  		return false;
  	}
  	if (!such_file_exist(filename)){
    	cout << "Sorry, such file does not exist\n";
    	return false;
  	}
  	int already_in_use = -1;
  	vector<int> bytes_pos = {};
  	ifstream MFT(MFT_name, ifstream::binary);
  	ofstream tmp_MFT(MFT_reserved, ofstream::binary);
  	string current_line;
  	while (getline(MFT, current_line)){
  		if (current_line.back() == '\r'){
				current_line.pop_back();
			}
      string current_file = "";
      for (int i = 0; i < current_line.size(); i++){
      	if (current_line.compare(i, 1, ",") == 0){
        		break;
      	}
        current_file += current_line.at(i);
      }
      if (current_file == filename){
      	string new_line = current_file;
      	current_line += ",";
      	current_file = "";
      	for (int i = 0; i < current_line.size(); i++){
          if (current_line.compare(i, 1, ",") == 0){
           	already_in_use += 1;
            if (already_in_use != 0){
            	bytes_pos.push_back(strtoint(current_file));
						}
						current_file = "";
          }
          else{
          	current_file += current_line.at(i);
		  		}
      	}
				for (int i = already_in_use; i < data.size() + shift; i++){
        	bytes_pos.push_back(get_free_byte_pos());
        	if (bytes_pos.back() == -1){
          	cout << "Sorry, there is not enough memory\n";
          	return false;
        	}
    		}
        for (int i = 0; i < bytes_pos.size(); i++){
         	string block_name = inttostr(bytes_pos[i]);
         	new_line += "," + block_name;
        }
        tmp_MFT << new_line << endl;
			}
			else{
				tmp_MFT << current_line << endl;
			}
    }
    MFT.close();
    tmp_MFT.close();
		replacefile(MFT_name, MFT_reserved);
		for (int i = 0; i < shift; i++){
			if (i >= already_in_use){
				string block_name = inttostr(bytes_pos[i]);
        block_name = "$" + block_name;
        ofstream block_stream(block_name, ofstream::binary);
        block_stream.close();
			}
  	}
		for (int i = shift; i < data.size() + shift; i++){
  		string block_name = inttostr(bytes_pos[i]);
  		block_name = "$" + block_name;
  		ofstream block_stream(block_name, ofstream::binary);
  		block_stream << int(data[i - shift]) << endl;
  		block_stream.close();
		}
		return true;
}


string CNTFS::readfile(const string filename, int datasize, int shift){
  if (filename[0] == '$'){
    cout << "Sorry, this name is reversed, pleasy try again\n";
    return "";
  }
  if (!such_file_exist(filename)){
    cout << "Sorry, such file does not exist\n";
    return "";
  }
  vector<string> bytes_pos = {};
  ifstream MFT(MFT_name, ifstream::binary);
  string current_line;
  while (getline(MFT, current_line)){
    if (current_line.back() == '\r'){
      current_line.pop_back();
    }
    current_line += ",";
    string current_file = "";
    for (int i = 0; i < current_line.size(); i++){
      if (current_line.compare(i, 1, ",") == 0){
          break;
      }
      current_file += current_line.at(i);
    }
    if (current_file == filename){
      int cnt = -1;
    	current_file = "$";
    	for (int i = 0; i < current_line.size(); i++){
     		if (current_line.compare(i, 1, ",") == 0){
          if (cnt >= 0){
            bytes_pos.push_back(current_file);
          }
       		cnt += 1;
          current_file = "$";
     		}
        else{
          current_file += current_line[i];
        }
      }
      MFT.close();
    }
    string result = "";
    for (int i = shift; i < bytes_pos.size() && i < shift + datasize; i++){
      ifstream pos_stream(bytes_pos.at(i), ifstream::binary);
      int value = 32;
      pos_stream >> value;
      result += (value + '\0');
      pos_stream.close();
    }
    if (shift + datasize > bytes_pos.size()){
      cout << "An attempt to read after the EOF\nThe data ofter EOF will not be returned\n";
    }
    return result;
  }
  cout << "Unexpected error, file not found\n";
  return "";
}

#endif
