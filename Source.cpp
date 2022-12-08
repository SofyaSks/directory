#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <Windows.h>
#include <stdio.h>
#include <io.h>
#include <direct.h>

using namespace std;

// stdio.h - переименование и удаление 
// io.h - поиск


//rename (old_name, new_name)
//remove
//_findfirst(files, "path")

// cd path - перейти в директорию путь которой вы указываете
// cd .. - подняться на уровень вверх в родительский каталог
// cd. - показывает содержимое директории в котором сейчас
// exit
// root - переход в корневой каталог


void DirRename();
void DirRemove();
void CreateDir();
bool showDir(char path[]);
void ShowCurrentDirect(char path[], char info[]);

int main() {
	

	char path[MAX_PATH];
	char tmp[MAX_PATH];
	char action[MAX_PATH];
	GetCurrentDirectory(sizeof(path), (LPWSTR)path);
	bool flag = true;
	showDir(path);
    do
    {
        cin.getline(action, MAX_PATH);
        if (!_strcmpi(action, "root"))
        {
            path[2] = '\0';
            ShowDir(path);
        }
        else if (!_strcmpi(action, "exit"))
        {
            flag = false;
        }
        else if (!_strnicmp(action, "cd", 2))
        {
            if (!_strcmpi(action, "cd"))
            {
                ShowDir(path);
            }
            else if (!_strnicmp(action, "cd", 3))
            {
                int index = strspn(action + 2, " ");
                if (index)
                {
                    if (strchr(action + index + 2, ':'))
                    {
                        if (ShowDir(action + index + 2))
                        {
                            strcpy(path, action + index + 2);
                        }
                        else
                        {
                            ShowCurrentDirect(path, tmp);
                        }
                    }
                    else if (!strcmp(action + index + 2, ".."))
                    {
                        char* res = strrchr(path, '\\');
                        if (res)
                        {
                            int del = res - path;
                            strncpy(tmp, path, del);
                            tmp[del] = '\0';
                        }
                        else
                        {
                            strcpy(tmp, path);
                        }
                        if (ShowDir(tmp))
                        {
                            strcpy(path, tmp);
                        }
                        else
                        {
                            ShowCurrentDirect(path, tmp);
                        }
                    }
                    else if (!strcmp(action + index + 2, "."))
                    {
                        ShowDir(path);
                    }
                    else if (!strcmp(action + index + 2, "/"))
                    {
                        ShowDir(path);
                    }
                    else
                    {
                        cout << "ERROR" << endl;
                    }
                }
                else
                {
                    cout << "Error" << endl;
                }
            }
            else
            {
                cout << "ERROR" << endl;
            }
        }
        else
        {
            ShowDir(path);
        }
    } while (flag);
    return 0;
}


	


void DirRename() {
	char old_name[50], new_name[50];
	cout << "Enter old_name" << endl;
	cin >> old_name;
	cout << "Enter new_name" << endl;
	cin >> new_name;

	if (rename(old_name, new_name) != 0) {
		cout << "Error" << endl;
	}
	else
		cout << "OK" << endl;
}

void DirRemove() {
	char name[50];
	cout << "Enter old_name" << endl;
	cin >> name;
	if (_rmdir(name) != 0) {
		cout << "Error" << endl;
	}
	else
		cout << "OK" << endl;
}

void CreateDir() {
	char path[50];
	cout << "Enter path" << endl;
	cin >> path;

	if (_mkdir(path) == -1)
		cout << "Error.\n";
	else
		cout << "OK\n";
}

bool ShowDir(char path[]) {
	_finddata_t find;
	char pathfind[MAX_PATH];
	strcpy(pathfind, path);
	strcat(pathfind, "\\*.*");
	char info[MAX_PATH];

	int res = _findfirst(pathfind, &find);

	system("clc");
	int flag = res;

	if (flag == -1) {
		strcpy(info, "No directory\n");
		printf("%s\n", info);
		return false;
	}
	else {
		while (flag != -1) {
			if (strcmp(find.name, ".") && strcmp(find.name, "..")) {
				find.attrib& _A_SUBDIR ? strcpy(info, "Direct \n") : strcpy(info, "File\n");
				printf("%30s %10s \n", find.name, info);
			}
			flag = _findnext(res, &find);
		}
		ShowCurrentDirect(path, info);
		_findclose(res);
		return true;
	}
}

void ShowCurrentDirect(char path[], char info[]) {
	CharToOem((LPCWSTR)path, info);
	printf("%s", info);
}