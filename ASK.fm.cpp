#include <iostream>
#include<fstream>
#include<sstream>
#include<assert.h>
#include<vector>
#include<queue>
#include<set>
#include<map>

using namespace std;

vector<string> ReadFileLines(string path)
{
	vector <string> lines;
	fstream file_handler(path.c_str());

	if (file_handler.fail())
	{
		std::cout << "\n\nERROR: can't open the file\n\n";
		return lines;
	}

	string line; 
	while (getline(file_handler,line))
	{
		if (line.size() == 0)
			continue;
		lines.push_back(line);
	}


	file_handler.close();
	return lines;
}

void WriteFileLines(string path, vector<string> lines, bool append = true)
{
	auto status = ios::in | ios::out | ios::app;

	if (!append)
		status = ios::in | ios::out | ios::trunc;

	fstream file_handler(path.c_str(), status);
	if (file_handler.fail())
	{
		std::cout << "\n\nERROR: Can't Open the file\n\n";
		return;
	}

	for (auto line : lines)
		file_handler << line << '\n';
	file_handler.close();
}

vector <string> SplitString(string s, string delimeter = ",")
{
	vector<string>strs;
	
	int pos = 0;
	string substr;

	while ( (pos = (int) s.find(delimeter)) != -1)
	{
		substr = s.substr(0, pos);
		strs.push_back(substr);
		s.erase(0, pos + delimeter.length());
	}
	strs.push_back(s);
	return strs;
}

int ToInt(string str)
{
	istringstream iss(str);
	int num;
	iss >> num;
	return num;
}

int ReadInt(int low, int high)
{
	std::cout << "Enter number in range " << low << " - " << high << " : ";
	int value;
	std::cin >> value;

	if (low <= value && value <= high)
		return value;
	std::cout << "ERROR: invalid number... Try again\n";
	return ReadInt(low, high);
}


int main()
{
  
}

