#pragma once
#include"ASK.fm.cpp"
#include <iostream>
#include<fstream>
#include<sstream>
#include<assert.h>
#include<vector>
#include<queue>
#include<set>
#include<map>


class Question
{
private:
	int ques_id;
	int parent_ques_id;
	int from_user_id;
	int to_user_id;
	
	int from_user_id;
	
	std::string  ques_text;
	std::string answer_text;

public:
	int is_anon_ques;
	Question()
	{
		ques_id = parent_ques_id = from_user_id = to_user_id = -1;
		is_anon_ques = 1;
	}

	Question(std::string line)
	{
		std::vector<std::string> substrs = SplitString(line);
		assert(substrs.size() == 7);

		ques_id = ToInt( substrs[0]);
		parent_ques_id = ToInt(substrs[1]);
		from_user_id = ToInt(substrs[2]);
		to_user_id = ToInt(substrs[3]);
		is_anon_ques = ToInt(substrs[4]);
		ques_text = substrs[5];
		answer_text = substrs[6];

	}

	std::string ToString()
	{
		ostringstream oss;
		oss << ques_id << ',' << parent_ques_id << ',' << from_user_id << ','
			<< to_user_id << ',' << is_anon_ques << ','
			<<ques_text << ',' << answer_text;

		return oss.str();
	}

	void PrintToQuestion()
	{
		std::string prefix = "";
		if (parent_ques_id != -1)
			prefix = "\tThread: ";
		std::cout << prefix << " Question Id ( " << ques_id << " )";
		if (!is_anon_ques)
			std::cout << "from user id: " << from_user_id << ")";
		std::cout << "\t Question: " << ques_text << '\n';

		if (answer_text !="")
		{
			std::cout << "\tAnswer: " << answer_text << '\n';
		}
		else
		{
			std::cout << "NOT Answered YET";
		}

	}

	void PrintFromQuestion()
	{	
		std::cout << "Question Id: (" << ques_id << ')';
		if (!is_anon_ques)
			cout << "!AQ";
		cout << "to user id(" << to_user_id << ")";
		cout << "\t Question: " << ques_text << '\n';

		if (answer_text != "")
			cout << "\tAnswer: " << answer_text << '\n';
		else
			cout << "\tNOT answered YET\n";
	} 

	void PrintFeedQuestion()
	{
		if (parent_ques_id != -1)
			cout << "Thread Parent Question ID (" << parent_ques_id << ")";
		cout << "Question ID (" << ques_id << ")";
		if (!is_anon_ques)
			cout << "from user id(" << ques_id << ")";

		cout << "To USer ID (" << to_user_id << ")";
		cout << "\tQuestion: " << ques_text << '\n';
		if (answer_text != "")
			cout << "\tAnswer: " << answer_text << '\n';
	}

	int GetQuestionId()
	{
		return ques_id;
	}
	void SetQuestionId(int quesId)
	{
		ques_id = quesId;
	}
	int GetParentId()
	{
		return parent_ques_id;
	}

	int GetFromUserId()
	{
		return from_user_id;
	}
	void SetFromUserId(int userFromID)
	{
		from_user_id = userFromID;
	}
	
	int GetToUserId()
	{
		return to_user_id;
	}
	void SetToUserId(int ToUserId)
	{
		to_user_id = ToUserId;
	}

	string GetQuesText()
	{
		return ques_text;
	}
	string GetAnswerText()
	{
		return answer_text;
	}

};

