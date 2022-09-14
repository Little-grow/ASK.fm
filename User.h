#pragma once
#include <iostream>
#include<fstream>
#include<sstream>
#include<assert.h>
#include<vector>
#include<queue>
#include<set>
#include<map>
#include"Question.h"
#include"ASK.fm.cpp"


using namespace std;

class User
{
private:
	int user_id;
	string user_name;
	string password;
	string name;
	string email;
	int allow_anon_ques;

	
public:

	vector<int> question_id_from_me;
	map<int, vector<int>> questionId_questionIdsThread_to_map;

	User()
	{
		user_id = allow_anon_ques = -1;
	}

	User(string line)
	{
		vector<string> substrs = SplitString(line);
		assert(substrs.size() == 6);

		user_id = ToInt(substrs[0]);
		user_name = substrs[1];
		password = substrs[2];
		name = substrs[3];
		email = substrs[4];
		allow_anon_ques = ToInt(substrs[5]);
	}

	string ToString()
	{
		ostringstream oss;
		oss << user_id << ',' << user_name << ',' << password << ',' << name << ','
			<< email << ',' << '\n';
		return oss.str();
	}

	void print()
	{
		cout << "User " << user_id << "," << user_name << " " << password << "," << name << "," << email << '\n';
	}

	int GetUserId()
	{
		return user_id;
	}
};

