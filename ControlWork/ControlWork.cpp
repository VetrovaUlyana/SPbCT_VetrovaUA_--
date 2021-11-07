#include <iostream>
#include <vector>
#include "windows.h"
#include <fstream>
#include <locale.h>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	HANDLE kr;
	DWORD a;
	int len = 0;
	int size = 0;
	char cBuffer[1026] = { 0 };
	string text;
	fstream file("passwd/rabota.txt");
	kr = CreateFile(L"CONIN$", GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
	ReadFile(kr, cBuffer, sizeof(cBuffer), &a, NULL);
	text = cBuffer;
	len = text.length() - 2;
	cout << "Размер текста: ";
	if (len < 1024) cout << len << " байт" << endl;
	else cout << 1024 << " байт" << endl;

	file.seekg(0, ios::end);
	size = file.tellg();
	cout << "Размер файла: " << size << " байт" << endl;
	file.close();

	return 0;
}
