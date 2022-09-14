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
#include"User.h"
#include<algorithm>
#include <string>
class QuestionManager
{
private:
	map<int, vector<int>> questionId_questionThread_to_map;
	map<int, Question> qusrionId_questionObject_to_map;

	int last_id = 0;
public:
	QuestionManager()
	{
		last_id = 0;
	}

	void LoadDatabase()
	{
		last_id = 0;
		questionId_questionThread_to_map.clear();
		qusrionId_questionObject_to_map.clear();

		vector<string> lines = ReadFileLines("Questions.txt");
		for (auto &line : lines )
		{
			Question ques(line);
			last_id = max(last_id, ques.GetQuestionId());

			qusrionId_questionObject_to_map[ques.GetQuestionId()] = ques;

			if (ques.GetParentId() == -1)
				questionId_questionThread_to_map[ques.GetQuestionId()].push_back(ques.GetQuestionId());
			else
				questionId_questionThread_to_map[ques.GetParentId()].push_back(ques.GetQuestionId());
		
		}
	}

	void FillUserQuestion(User& user)
	{
		user.question_id_from_me.clear();
		user.questionId_questionIdsThread_to_map.clear();

		for (auto& pair : questionId_questionThread_to_map)
		{
			for (auto& ques_id : pair.second)
			{
				Question& ques = qusrionId_questionObject_to_map[ques_id];

				if (ques.GetFromUserId() == user.GetUserId())
				{
					if (ques.GetParentId() == -1)
						user.questionId_questionIdsThread_to_map[ques.GetQuestionId()].push_back(ques.GetQuestionId());
					else
						user.questionId_questionIdsThread_to_map[ques.GetParentId()].push_back(ques.GetQuestionId());
				}
			}
		}

		
	}

	void PrintUserFromQuestion(User &user)
	{
		cout << '\n';

		if (user.question_id_from_me.size() == 0)
			cout << "No Questions";

		for (auto& ques_id : user.question_id_from_me)
		{
			Question& ques = qusrionId_questionObject_to_map[ques_id];
			ques.PrintFromQuestion();
		}
		cout << '\n';
	}

	int ReadQuestionIdAny(User& user)
	{
		int ques_id;
		cin >> ques_id;

		if (ques_id == -1)
			return -1;
		if (!qusrionId_questionObject_to_map.count(ques_id))
		{
			cout << "\nERROR: NO question with such ID. Try again\n\n";
			return ReadQuestionIdAny(user);
		}

		Question& ques = qusrionId_questionObject_to_map[ques_id];

		if (ques.GetToUserId() != user.GetUserId())
		{
			cout << "\nERROR: Invalid question ID. Try again\n\n";
			return ReadQuestionIdAny(user);
		}
		return ques_id;
	}

	int ReadQuestionIdThread(User& user)
	{
		int ques_id;
		cout << "for thread question: Enter question id or -1 to new question:\n";
		cin >> ques_id;

		if (ques_id == -1)
			return -1;
		if (!questionId_questionThread_to_map.count(ques_id))
		{
			cout << "No thread Question with such ID. Try Again\n";
			return ReadQuestionIdAny(user);
		}
		return ques_id;
	}

	void AnswerQuestion(User& user)
	{
		int ques_id = ReadQuestionIdAny(user);
		if (ques_id == -1)
			return;
		Question& ques = qusrionId_questionObject_to_map[ques_id];
		ques.PrintToQuestion();

		if (ques.GetAnswerText() !="")
		{
			cout << "\nWarning: Already answered. Answer will be updated\n";
		}

		cout << "Enter answer: ";
		string ans = ques.GetAnswerText();
		getline(cin, ans);

	}

	void DeleteQuestion(User& user)
	{
		int ques_id = ReadQuestionIdAny(user);
		if (ques_id == -1)
			return;
		vector<int> ids_to_remove;
		if (questionId_questionThread_to_map.count(ques_id))
		{
			ids_to_remove = questionId_questionThread_to_map[ques_id];
			questionId_questionThread_to_map.erase(ques_id);
		}
		else
		{
			ids_to_remove.push_back(ques_id);
		}

		for (auto& pair : questionId_questionThread_to_map)
		{
			vector<int>& vec = pair.second;
			for (size_t pos = 0; pos < (int)vec.size(); pos++)
			{
				if (ques_id == vec[pos])
				{
					vec.erase(vec.begin() + pos);
					break;
				}
			}
		}
		for (auto& id : ids_to_remove)
		{
			qusrionId_questionObject_to_map.erase(id);
		}
	}

	void AskQuestion(User& user, pair<int, int> to_user_pair)
	{
		Question ques;
		if (!to_user_pair.second)
		{
			cout << "Note: Anon question aren't allowed for this user\n";
			ques.is_anon_ques = 0;
		}
		else
		{
			cout << "Is Anon Ques?: (0 or 1)";
			cin >> ques.is_anon_ques;
		}

		cout << "Enter question text: \n";
		string que = ques.GetQuesText();
		getline(cin, que);
		getline(cin, que);

		ques.SetFromUserId(user.GetUserId());
		ques.SetToUserId(to_user_pair.first);

		ques.SetQuestionId(++last_id);
		qusrionId_questionObject_to_map[ques.GetQuestionId()] = ques;

		if (ques.GetParentId() == -1)
		{
			questionId_questionThread_to_map[ques.GetQuestionId()].push_back(ques.GetQuestionId());
		}
		else 
			questionId_questionThread_to_map[ques.GetParentId()].push_back(ques.GetQuestionId());

	}

	void ListFeed()
	{
		for (auto& pair : qusrionId_questionObject_to_map)
		{
			Question& ques = pair.second;
			if (ques.GetAnswerText() == "")
				continue;
			ques.PrintFeedQuestion();
		}
	}

	void UpdateDataBase()
	{
		vector<string> lines;
		for (auto& pair : qusrionId_questionObject_to_map)
		{
			lines.push_back(pair.second.ToString());
		}
		WriteFileLines("questions.txt", lines, false);
	}
};

