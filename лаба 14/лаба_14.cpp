#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <string>
#include <Windows.h>
#include <iomanip>
#include <string.h>
#include <fstream>

using namespace std;

const char UP = 72;
const char DOWN = 80;
const char ESC = 27;
const char ENTER = 13;

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

fstream Inform;

typedef struct student
{
	string fio;
	int info;
	student* Left, * Right;
};

student *Root;
void GoToXY(short x, short y);
void ConsoleCursorVisible(bool show, short size);
void Make();
void View(student* t, int level);
student* List(int info, string fio);
void printTree(student* root, int x, int y, int a, char c);
void Add_New();
student* Search(student* root, int key);
void Del(int key);
void Del_All(student** t);
void ActiveMenu();
int maxDepth(student* t);
int pairs(student* t);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	ConsoleCursorVisible(false, 100);
	ActiveMenu();
	_getch();
}

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}
void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

student* List(int info, string fio)
{
	student* t = new student;
	t->info = info;
	t->fio = fio;
	t->Left = t->Right = NULL;
	return t;
}
void  Make()
{
	student* prev = NULL, *t;
	int find, x = 90, y = 20;
	bool signal = false;

	if (Root != NULL)
	{
		GoToXY(x, y);
		cout << "Дерево уже созданно!";
		_getch();
		return;
	}
	else 
	{
		Root = new student;
		Root->Left = Root->Right = NULL;
		signal = false;

		while (signal == false)
		{
			GoToXY(x, y);
			cout << "Введите номер студенческого (корень): ";
			cin >> Root->info;

			if (cin.fail())
			{
				system("cls");
				cin.clear();
				cin.ignore(3000, '\n');
				GoToXY(x, y - 1);
				cout << "Повторите ввод!" ;
				GoToXY(x + 33, y);
				cout << "                   ";
			}
			else
			{
				signal = true;
			}
		}

		GoToXY(x, y + 1);
		cout << "Введите ФИО: ";
		getchar();
		getline(cin, Root->fio);
	}

	int info;
	string fio;
	y = 15;

	system("cls");
	while (1)
	{
		signal = false;
		y += 2;

		while (signal == false)
		{
			GoToXY(x, y);
			cout << "Введите номер студенческого (узлы): ";
			cin >> info;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore(3000, '\n');
				GoToXY(x, y + 1);
				cout << "Повторите ввод!";
				GoToXY(x + 31, y);
				cout << "                   ";
			}
			else
			{
				signal = true;
			}
		}

		if (info == 0)
		{
			break;
		}

		GoToXY(x, y + 1);
		cout << "                ";

		GoToXY(x, y + 1);
		cout << "Введите ФИО: ";
		getchar();
		getline(cin, fio);

		

		t = Root; 
		find = 0;

		while (t && !find)
		{
			prev = t;
			if (info == t->info)
			{
				find = 1; 
			}
			else
			{
				if (info < t->info)
				{
					t = t->Left;
				}
				else
				{
					t = t->Right;
				}
			}
		}

		if (!find) 
		{
			t = List(info, fio);

			if (info < prev->info) 
			{
				prev->Left = t;
			}
			else
			{
				prev->Right = t;
			}
		}
	}

	system("cls");
	GoToXY(90, 20);
	cout << "Дерево успешно создано!";
	_getch();
}
void printTree(student* root, int x, int y, int a, char c)
{
	if (root)
	{
		if (a > 0 && c != 'k')
		{
			if (c == 'l')
			{
				x -= 5;
				GoToXY(x, y + 1);
				cout << "/";
				x--;
				GoToXY(x, y + 2);
				cout << "/";
				x -= 4;
			}
			else
			{
				x += 7;
				GoToXY(x, y + 1);
				cout << "\\";
				x++;
				GoToXY(x, y + 2);
				cout << "\\";
				x += 2;
			}
		}
		else if (c != 'k')
				if (c == 'l')
				{
					
					GoToXY(x, y + 1);
					cout << "/";
					x--;
					GoToXY(x, y + 2);
					cout << "/";
					x -= 4;
				}
				else
				{
					x += 2;
					GoToXY(x+ 1, y + 1);
					cout << "\\";
					x++;
					GoToXY(x + 1, y + 2);
					cout << "\\";
					x += 2;
				}

		GoToXY(x, y += 3);

		if (c == 'k')
		{
			GoToXY(x - 3, y += 3);
		}
		a--;
		cout << root->fio << " ";
		cout <<"[" << root->info << "]";
		printTree(root->Left, x, y, a, 'l');
		printTree(root->Right, x, y, a, 'r');
	}
}
void Add_New() 
{
	student* prev = NULL, *t;
	int search, info;
	string fio;
	int x = 90, y = 20;

	if (Root == NULL)
	{
		GoToXY(90,20);
		cout <<"Дерево еще не создано!";
		return;
	}

	bool signal = false;
	while (signal == false)
	{
		GoToXY(x, y);
		cout << "Введите номер студенческого (узлы): ";
		cin >> info;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(3000, '\n');
			GoToXY(x, y + 1);
			cout << "Повторите ввод!";
			GoToXY(x + 31, y);
			cout << "                   ";
		}
		else
		{
			signal = true;
		}
	}

	GoToXY(x, y + 1);
	cout << "                ";

	GoToXY(x, y + 1);
	cout << "Введите ФИО: ";
	getchar();
	getline(cin, fio);


	t = Root;
	search = 0;
	while (t && !search)
	{
		prev = t;
		if (info == t->info)
		{
			search = 1;
		}
		else
		{
			if (info < (t->info))
			{
				t = t->Left;
			}
			else
			{
				t = t->Right;
			}
		}
	}
	if (!search)
	{
		t = List(info, fio);
		if (info < prev->info)
		{
			prev->Left = t;
		}
		else
		{
			prev->Right = t;
		}
	}
}
student* Search(student* root, int key)
{
	if (root == NULL)
	{
		return NULL;
	}
	if (root->info == key)
	{
		return root;
	}
	if (key < root->info)
	{
		if (root->Left != NULL)
		{
			return Search(root->Left, key);
		}
		else
			return NULL;
	}
	else
	{
		if (root->Right != NULL)
			return Search(root->Right, key);
		else
			return NULL;
	}
}
void Del(int key)
{
	student* Del, * Prev_Del, * R, * Prev_R;
	Del = Root;
	Prev_Del = NULL;
	while (Del != NULL && Del->info != key)
	{
		Prev_Del = Del;
		if (Del->info > key)
		{
			Del = Del->Left;
		}
		else
		{
			Del = Del->Right;
		}
	}
	if (Del == NULL) 
	{
		system("cls");
		GoToXY(90, 20);
		cout << "Нет узла с таким ключом!";
		return;
	}
	
	if (Del->Right == NULL)
	{
		R = Del->Left;
	}
	else
	{
		if (Del->Left == NULL)
		{
			R = Del->Right;
		}
		else
		{
			
			Prev_R = Del;
			R = Del->Left;
			while (R->Right != NULL)
			{
				Prev_R = R;
				R = R->Right;
			}
			
			if (Prev_R == Del)
			{
				R->Right = Del->Right;
			}
			else
			{
				R->Right = Del->Right;
				Prev_R->Right = R->Left;
				R->Left = Del->Left;
			}
		}
	}

	if (Del == Root)
	{
		Root = R; 
	}
	else 
	{
		if (Del->info < Prev_Del->info)
		{
			Prev_Del->Left = R;
		}
		else
		{
			Prev_Del->Right = R; 
		}
	}

	system("cls");
	GoToXY(90, 20);
	cout << "Элемент " << Del->info << " успешно удален" ;
	free(Del);
}
void FreeTree(student* t) {
	if (t->Left)   FreeTree(t->Left);
	if (t->Right)  FreeTree(t->Right);
	free(t);
}
int maxDepth(student* t)
{
	if (t == NULL)
	{
		return 0;
	}
	return max(maxDepth(t->Left), maxDepth(t->Right)) + 1;
}
//void View(student* t, int level) 
//{
//	Inform.open("Information.txt", ios_base::out);
//
//	int i;
//	if (t)
//	{
//		View(t->Right, level + 1); 
//		for (int i = 0; i < level; i++)
//		{
//			cout << ("    ");
//			Inform << ("    ");
//		}
//		cout << t->fio << " " << t->info << endl;
//		Inform << t->fio << " " << t->info << endl;
//		View(t->Left, level + 1);
//	}
//}
int pairs(student* t)
{
	if (t == NULL)
	{
		return 0;
	}
	int n = ((t->Left != NULL) && (t->Right != NULL)); 
	
	if (t->Left != NULL)
		n += pairs(t->Left);

	if (t->Right != NULL)
		n += pairs(t->Right);

	return n;
}
void ActiveMenu()
{
	system("cls");
	string firstMenu[] = { "Создать дерево", "Добавить узел дерева", "Удалить узел из дерева", "Вывести дерево на экран", "Удалить дерево", "Поиск по дереву", "Глубина дерева", "Определить число узлов в дереве, имеющих двух потомков", "Выход из программы"};
	int active_menu = 0;

	char ch;
	while (true)
	{
		int x = 90, y = 20;
		GoToXY(x, y);

		for (int i = 0; i < size(firstMenu); i++)
		{
			if (i == active_menu)
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			else
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			GoToXY(x, y++);
			cout << firstMenu[i];
		}

		ch = _getch();
		if (ch == -32) ch = _getch();
		switch (ch)
		{
		case ESC:
			exit(0);

		case UP:
			if (active_menu != 0)
				--active_menu;
			break;

		case DOWN:
			if (active_menu < size(firstMenu) - 1)
				++active_menu;
			break;

		case ENTER:
			system("cls");

			switch (active_menu)
			{
			case 0:
			{
				Make();
				system("cls");
				break;
			}

			case 1:
			{
				if(Root != NULL)
				{
				Add_New();
				system("cls");
				GoToXY(90, 20);
				cout << "Узел успешно добавлен!";
				_getch();
				system("cls");
				}
				else
				{
					GoToXY(90,20);
					cout << "Дерево не создано!";
					_getch();
					system("cls");
				}
				break;
			}

			case 2:
			{
				if(Root != NULL)
				{
				int key;
				x = 90, y = 20;
				bool signal = false;
				while (signal == false)
				{
					GoToXY(x, y);
					cout << "Введите узел, который хотите удалить: ";
					cin >> key;
					if (cin.fail())
					{
						cin.clear();
						cin.ignore(3000, '\n');
						GoToXY(x, y + 1);
						cout << "Повторите ввод!";
						GoToXY(x + 31, y);
						cout << "                   ";
					}
					else
					{
						signal = true;
					}
				}
				Del(key);
				_getch();
				system("cls");
				}
				else
				{
					GoToXY(90, 20);
					cout << "Дерево не создано!";
					_getch();
					system("cls");
				}
				break;
			}

			case 3:
			{
				if(Root != NULL)
				{
				printTree(Root, 90, 15, 2, 'k');
				_getch();
				system("cls");	
				}
				else
				{
					GoToXY(90, 20);
					cout << "Дерево не создано!";
					_getch();
					system("cls");
				}
				break;
			}

			case 4:
			{
				if (Root != NULL)
				{
				FreeTree(Root);
				Root = NULL;
				GoToXY(90, 20);
				cout << "Дерево удалено!";
				_getch();
				}
				else
				{
					GoToXY(90, 20);
					cout << "Дерево не создано!";
					_getch();
					system("cls");
				}
				break;
			}

			case 5:
			{
				if (Root != NULL)
				{
					int key;
					x = 90, y = 20;
					bool signal = false;
					while (signal == false)
					{
						GoToXY(x, y);
						cout << "Введите ключ узла, который хотите найти: ";
						cin >> key;
						if (cin.fail())
						{
							cin.clear();
							cin.ignore(3000, '\n');
							GoToXY(x, y + 1);
							cout << "Повторите ввод!";
							GoToXY(x + 41, y);
							cout << "                   ";
						}
						else
						{
							signal = true;
						}
					}
					student *temp = Search(Root, key);

					system("cls");
					if (temp != NULL)
					{
						GoToXY(90, 20);
						cout << "Результат поиска: " << temp->fio << " [" << temp->info << "]";
						_getch();
						system("cls");
					}
					else
					{
						GoToXY(90, 20);
						cout << "Узел с таким ключом не найден!";
						_getch();
						system("cls");
					}

				}
				else
				{
					GoToXY(90, 20);
					cout << "Дерево не создано!";
					_getch();
					system("cls");
				}
				break;
			}

			case 6:
			{
				if (Root != NULL)
				{
					GoToXY(90, 20);
					cout << "Глубина дерева: " << maxDepth(Root);
					_getch();
					system("cls");
				}
				else
				{
					GoToXY(90, 20);
					cout << "Дерево не создано!";
					_getch();
					system("cls");
				}
				break;
			}

			case 7:
			{
				if (Root != NULL)
				{
					GoToXY(90, 20);
					cout << "Количество узлов, ищеющих 2 потомков: " << pairs(Root);
					_getch();
					system("cls");
				}
				else
				{
					GoToXY(90, 20);
					cout << "Дерево не создано!";
					_getch();
					system("cls");
				}
				break;
			}
			case 8:
				exit(0);
			}
			break;
		}
	}

}