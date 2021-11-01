#include <iostream>
#include <windows.h>
using namespace std;
HANDLE mutex;
HANDLE sobit[4];
HANDLE zak_sobit;

DWORD WINAPI Employee(LPVOID lpParam) {
	int mes;
	WaitForSingleObject(mutex, INFINITE);
	if (WaitForSingleObject(zak_sobit, 10) == WAIT_TIMEOUT) {
		cout << "���� ����������� ������� �0�, �1�, �2�, �3�: \n";
		cin >> mes;
		cout << "�������: " << mes << ".\n";
		if (mes < 0 || mes > 3) {
			cout << "�������� ����. ������ �0�, �1�, �2�, �3�\n";
		}

		else SetEvent(sobit[(unsigned int)(mes - 0)]);
		ReleaseMutex(mutex);
		return 0;
	}
	else {
		ReleaseMutex(mutex);
		return 1;
	}

}

int main(int argc, char* argv[]) {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int kol = 0;

	cout << "���������� ��������� Employee: ";
	cin >> kol;

	cout << "������� " << kol << " ��������� Employee:\n";
	for (int i = 0; i < 4; i++) {
		sobit[i] = CreateEventA(0, 0, 0, 0);
	}
	zak_sobit = CreateEventA(0, 1, 0, 0);
	mutex = CreateMutexA(0, 1, 0);

	HANDLE* Threads = new HANDLE[kol];
	for (int i = 0; i < kol; i++) {
		Threads[i] = CreateThread(0, 0, Employee, 0, 0, 0);
	}
	ReleaseMutex(mutex);
	for (int i = 0; i < 3; i++) {
		WaitForMultipleObjects(4, sobit, 0, INFINITE);
		cout << "��������� " << i + 1 << " �������!\n";
	}
	cout << "����������� �������� ��������� ����������� � ������� mutex.";
	SetEvent(zak_sobit);
	WaitForSingleObject(mutex, INFINITE);
	ResetEvent(zak_sobit);
	delete[] Threads;
	ExitProcess(0);
}