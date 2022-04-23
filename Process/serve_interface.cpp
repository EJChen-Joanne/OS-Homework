#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

#define MAX_LINE 80

using namespace std;

int execArg(vector<string> &A)
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        cout << "Error.\n";
        return 0;
    }
    else if (pid == 0)
    {
        if (A.size() == 2)//2 parameters
        {
            char *arg[3] = { strdup(A[0].c_str()),strdup(A[1].c_str()),NULL};
            if ((execvp(arg[0],arg)) < 0)
                cout << "process failed.\n";
            exit(0);
        }
        else if (A.size() == 1)//1 parameter
        {
            char *arg[3] = {strdup(A[0].c_str()),NULL,NULL};
            if ((execvp(arg[0],arg)) < 0)
                cout << "process failed.\n";
            exit(0);
        }
    }
    else//pid > 0
        wait(NULL);

    return 1;
}

int main(void)
{
	//char *arg[MAX_LINE/2+1]; /*command line arguments*/
	int should_run = 1; /*flag to determine when to exit program*/
	stringstream ss;
	vector<string> A;

	while(should_run)
    {
		cout << "osh>";
		fflush(stdout);
		string str;
		getline(cin,str);
		ss.str("");
		ss.clear();
        ss.str(str);
        str = "";

		while(!ss.eof())
        {
            string temp;
            ss >> std::skipws >> temp;
            A.push_back(temp);
        }

        if (A.size() != 0)
        {
            if (A[0] == "exit")
            {
                should_run = 0;
            }
            else
            {
                should_run = execArg(A);
            }
        }
        else
            cout << "No command input, please try again.\n";

        A.clear();
	}

	return 0;
}
