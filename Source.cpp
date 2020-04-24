#include <conio.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <Windows.h>
using namespace std;

int main()
{
	short start = -1, end = -1, wslot, fslot;
	long long counter = 0;
	double cps, cps2 = -1;
	char ch, button, button2 = 'l';
	bool s = false;
	INPUT minput;
	INPUT kinput;
	ifstream fin("clicker.options");
	int prev = -1;
	fin >> start >> end >> cps2 >> button2;
	button = button2;
	cps = cps2;
button:
	cout << "Which button would you like to click?\nL(eft)\nM(iddle)\nR(ight)\n";
	ch = _getch();
	if (ch == 'l' || ch == 'L')
	{
		button = 'l';
	}
	else if (ch == 'm' || ch == 'M')
	{
		button = 'm';
	}
	else if (ch == 'r' || ch == 'R')
	{
		button = 'r';
	}
	else if (ch == 's' || ch == 'S')
	{
		system("CLS");
		Sleep(256);
		cout << "Enter weapon slot: ";
		while (true)
		{
			for (int i = 7; i < 255; i++)
			{
				if (GetAsyncKeyState(i) == -32768)
				{
					wslot = i;
					Sleep(256);
					system("CLS");
					cout << "Enter food slot: ";
					while (true)
					{
						for (int j = 7; j < 255; j++)
						{
							if (GetAsyncKeyState(j) == -32768)
							{
								fslot = j;
								goto place;
							}
						}
					}
				}
			}
		}
	place:
		button = 'l';
		cps = 1;
		kinput.type = INPUT_KEYBOARD;
		kinput.ki.wScan = 0;
		kinput.ki.time = 0;
		kinput.ki.dwExtraInfo = 0;
		kinput.ki.dwFlags = 0;
		kinput.ki.wVk = wslot;
		s = true;
	}
	system("CLS");
	minput.type = INPUT_MOUSE;
	minput.mi.mouseData = 0;
	if (button == 'l')
	{
		minput.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
	}
	else if (button == 'm')
	{
		minput.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MIDDLEDOWN | MOUSEEVENTF_MIDDLEUP);
	}
	else if (button == 'r')
	{
		minput.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN | MOUSEEVENTF_RIGHTUP);
	}
	minput.mi.dwExtraInfo = NULL;
	minput.mi.time = 0;
	if (s)
	{
		goto keys;
	}
cps:
	cout << "1. Change CPS (" << cps << ")\n2. Change time between clicks (" << 1000 / cps << " ms)\n3. Don't change" << endl;
	ch = _getch();
	if (ch == '1')
	{
		system("CLS");
		cout << "Enter new CPS: ";
		cin >> cps;
		system("CLS");
		cout << "New CPS: " << cps << endl;
		Sleep(1024);
	}
	else if (ch == '2')
	{
		system("CLS");
		cout << "Enter new time between clicks (ms): ";
		cin >> cps;
		cps = 1000 / cps;
		system("CLS");
		cout << "New time between clicks: " << 1000 / cps << endl;
		Sleep(1024);
	}
	if (cps <= 0)
	{
		system("CLS");
		goto cps;
	}
keys:
	system("CLS");
	Sleep(256);
	if (start != -1 && end != -1)
	{
		cout << "Start Key: " << start << "\nEnd Key: " << end << "\n\nWould you like to make any changes? (y/n)\n";
	yn:
		ch = _getch();
		if (ch != 'y' && ch != 'Y')
		{
			goto start;
		}
	}
	Sleep(512);
	system("CLS");
	cout << "Press the start key\n";
	while (true)
	{
		for (int i = 1; i < 255; i++)
		{
			if (GetAsyncKeyState(i) == -32768)
			{
				start = i;
				goto endstart;
			}
		}
	}
endstart:
	Sleep(512);
	system("CLS");
	cout << "Press the end key\n";
	while (true)
	{
		for (int i = 1; i < 255; i++)
		{
			if (GetAsyncKeyState(i) != 0)
			{
				end = i;
				goto start;
			}
		}
	}
start:
	ofstream fout("clicker.options");
	fout << start << " " << end;
	if (s)
	{
		fout << " " << cps2 << "  " << button2;
	}
	else
	{
		fout << " " << cps << " " << button;
	}
	system("CLS");
	Sleep(512);
	cout << "Press the start key to start" << endl;
	while (GetAsyncKeyState(start) == 0) {}
	system("CLS");
	cout << "Press the end key to end" << endl;
	Sleep(512);
	while (true)
	{
		double startt = clock();
		double curt = clock();
		while (curt - startt < 1000 / cps)
		{
			curt = clock();
			if (GetAsyncKeyState(end) != 0)
			{
				system("CLS");
				cout << "Press the start key to continue" << endl;
				Sleep(512);
				while (true)
				{
					if (GetAsyncKeyState(start) != 0)
					{
						break;
					}
				}
				system("CLS");
				cout << "Press the end key to end" << endl;
				Sleep(512);
			}
		}
		if (s && counter % 256 == 0)
		{
			kinput.ki.wVk = fslot;
			kinput.ki.dwFlags = 0;
			SendInput(1, &kinput, sizeof(INPUT));
			kinput.ki.dwFlags = KEYEVENTF_KEYUP;
			Sleep(64);
			SendInput(1, &kinput, sizeof(INPUT));
			minput.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_RIGHTDOWN);
			Sleep(64);
			SendInput(1, &minput, sizeof(INPUT));
			Sleep(2048);
			minput.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
			SendInput(1, &minput, sizeof(INPUT));
			minput.mi.dwFlags = (MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP);
			kinput.ki.dwFlags = 0;
			kinput.ki.wVk = wslot;
			Sleep(64);
			SendInput(1, &kinput, sizeof(INPUT));
			Sleep(64);
			kinput.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &kinput, sizeof(INPUT));
		}
		Sleep(64);
		SendInput(1, &minput, sizeof(INPUT));
		counter++;

	}
	system("CLS");
}