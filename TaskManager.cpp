#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <cstring>
#include <cstdlib>

using namespace std;

class Task
{
public:
	string name;
	int priority;
	Task()
	{
		priority = 0;
		name = "";
	}
	Task(string str, int num)
	{
		name = str;
		priority = num;
	};
	string printTask()
	{
		return ("Priority: " + to_string(priority) + " | Task: " + name);
	}
};

class Manager
{
public:
	Manager()
	{
		packfile();
		startPage();
	}
	void packfile()
	{
		count = 1;
		fin.open("tasks.txt");
		int pri;
		string str;
		getline(fin, str);
		while (!fin.eof())
		{
			fin >> pri;
			getline(fin, str);
			tasks[count].name = str;
			tasks[count].priority = pri;
			count++;
		}
		count--;
		fin.close();
		sort();
	}
	void startPage()
	{
		cout << "\t\t\t\t\t\t   TaskManager " << endl;
		cout << "Write \"/help\" to open help page" << endl;

		expectation();
	}
	void expectation()
	{
		flag = true;
		string s;
		cout << "Write command: ";
		cin >> s;
		if (s == "/help") {
			system("cls");
			help();
		}
		else if (s == "/new") {
			system("cls");
			newTask();
		}
		else if (s == "/all") {
			system("cls");
			printTasks();
		} 
		else if (s == "/exit"){
			system("cls");
			exitt();
		}
		else if (s == "/del")
		{
			del();
		}
		else {
			cout << "Error" << endl;
			expectation();
		}
	}
	void help()
	{
		cout << "\t\t\t\t\t\t   TaskManager " << endl;
		cout << "Write \"/new\" to create task;" << endl;
		cout << "Write \"/all\" to see all tasks;" << endl;
		cout << "Write \"/del\" to delete some tasks;" << endl;
		cout << "Write \"/exit\" to close program." << endl;

		expectation();
	}
	void exitt()
	{
		system("cls");
		cout << "Bye-Bye :)" << endl;
		Sleep(1000);
		exit(0);
	}
	void newTask()
	{
		cout << "\t\t\t\t\t\t\t New task" << endl;
		cout << "Write task: ";
		ws(cin);
		getline(cin, str);
		cout << "And priority pls: ";
		cin >> priority;
		count++;
		tasks[count] = Task(str, priority);
		sort();
		repack();
		expectation();
	}
	void sort()
	{
		for (int i = 1; i <= count - 1; i++)
		{
			for (int j = 1; j <= count - i; j++)
			{
				if (tasks[j].priority > tasks[j + 1].priority)
				{
					tasks[0] = tasks[j];
					tasks[j] = tasks[j + 1];
					tasks[j + 1] = tasks[0];
				}
			}
		}
	}
	void printTasks()
	{
		cout << "\t\t\t\t\t\t\t Tasks: " << endl;
		if (count == 0) {
			cout << "There are no tasks" << endl;
		} 
		else
		{
			for (int i = 1; i <= count; i++)
			{
				if (tasks[i].name != "deleted")
				{
					cout << i << ". " << tasks[i].printTask() << endl;
				}
			}
		}

		expectation();
	}

	void del()
	{
		string str;
		string numbers = "0123456789";
		int pos;
		char c;
		cout << "Write tasks, which need to delete(all or 1,2..): ";
		ws(cin);
		getline(cin, str);
		if (str == "all")
		{
			count = 0;
			fout.open("tasks.txt");
			fout.close();
			expectation();
		}
		else for (int i = 0; i <= str.length(); i++)
		{
			for (int j = 0; j < numbers.length(); j++)
			{
				if (str[i] == numbers[j])
				{
					c = str[i];
					pos = c - '0';
					tasks[pos].name = "deleted";
				}
			}
		}
		repack();
		expectation();
	}
	void repack()
	{
		fout.open("tasks.txt");
		fout.close();
		fout.open("tasks.txt");
		for (int i = 1; i <= count; i++)
		{
			if (tasks[i].name != "deleted")
			{
				fout << endl <<tasks[i].priority << tasks[i].name;
			}
		}
		fout.close();
		packfile();
	}
private:
	int count = 1;
	bool flag = false;
	int priority;
	string str;
	Task tasks[15];
	ofstream fout;
	ifstream fin;
};


int main()
{	
	setlocale(LC_ALL, "rus");
	system("color 37");
	Manager manager;

	return 0;
}