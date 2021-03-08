#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Directory {
	string sure_name;
	string name;
	string middle_name;
	string birth_data;
	unsigned long long int phone_number;
};
int ReadFile(Directory book[], ifstream& file) {
	string CurrentLine;
	int index = 0;
	while (!file.eof()) {
		getline(file, CurrentLine);
		book[index].sure_name = CurrentLine;
		getline(file, CurrentLine);
		book[index].name = CurrentLine;
		getline(file, CurrentLine);
		book[index].middle_name = CurrentLine;
		getline(file, CurrentLine);
		book[index].birth_data = CurrentLine;
		getline(file, CurrentLine);
		book[index].phone_number = stoll(CurrentLine);
		getline(file, CurrentLine);
		index++;
	}
	return index;
};
void WriteDirectory(Directory book[], int N) {
	for (int i = 0; i < N; i++) {
		cout << book[i].sure_name << " " << book[i].name << " " << book[i].middle_name << " " << book[i].birth_data << " " << book[i].phone_number << endl;
	}
};
void LineSearch(Directory book[], int N, unsigned long long int key) {
	bool otvet = false;
	for (int i = 0; i < N; i++) {
		if (book[i].phone_number == key) {
			cout << "\nРезультат поиска:\n" << book[i].sure_name << " " << book[i].name << " " << book[i].middle_name << " " << book[i].birth_data << " " << book[i].phone_number << endl;
			otvet = true;
		}
	}
	if (otvet == false) {
		cout << "\nПоиск не принес результатов!\nТакого номера нет в массиве!\n";
	}
};
void SortDirectory(Directory book[], int N) {
	Directory replace;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (book[i].phone_number > book[j].phone_number) {
				replace = book[i];
				book[i] = book[j];
				book[j] = replace;
			}
		}
	}
};
void InterpolSearch(Directory book[], int N, unsigned long long int key) {
	int mid, left = 0, right = N - 1;
	bool otvet = false;
	while ((book[left].phone_number <= key) && (book[right].phone_number >= key) && (otvet == false)) {
		mid = left + (((key - book[left].phone_number) * (right - left)) / (book[right].phone_number - book[left].phone_number));
		if (book[mid].phone_number < key) {
			left = mid + 1;
		}
		else if (book[mid].phone_number > key) {
			right = mid - 1;
		}
		else {
			cout << "\nРезультат поиска:\n" << book[mid].sure_name << " " << book[mid].name << " " << book[mid].middle_name << " " << book[mid].birth_data << " " << book[mid].phone_number << endl;
			otvet = true;
		}
	}
	if (book[left].phone_number == key) {
		cout << "\nРезультат поиска:\n" << book[left].sure_name << " " << book[left].name << " " << book[left].middle_name << " " << book[left].birth_data << " " << book[left].phone_number << endl;
	}
	else if (otvet == false){
		cout << "\nПоиск не принес результатов!\nТакого номера нет в массиве!\n";
	}
};
void SwitchSearchMetod(int quantity, Directory book[]) {
	int MethodNumber = -1, index = 0;
	unsigned long long int key;
	while ((MethodNumber < 0) || (MethodNumber > 4)) {
		cout << "\nВведите номер метода поиска\n\n0 - метод линейного поиска\n1 - метод интерполяционного поиска\n\nВаш выбор: ";
		cin >> MethodNumber;
		switch (MethodNumber) {
		case (0):
			cout << "\nВы выбрали метод линейного поиска\n";
			cout << "\nВведите номер искомого телефона: ";
			cin >> key;
			LineSearch(book, quantity, key);
			break;
		case (1):
			cout << "\nОтсортированый массив данных:\n";
			SortDirectory(book, quantity);
			cout << endl;
			WriteDirectory(book, quantity);
			cout << endl;
			cout << "Вы выбрали метод интерполяционного поиска\n";
			cout << "\nВведите номер искомого телефона: ";
			cin >> key;
			InterpolSearch(book, quantity, key);
			break;
		default: cout << "\nВведён не номер метода поиска!\n";
			break;
		}
	}
};
int main()
{
	system("chcp 1251");
	ifstream inputfile("F1.txt");
	if (inputfile.is_open()) {
		Directory book[100];
		int quantity = ReadFile(book, inputfile);
		cout << "\nМассив данных:\n\n";
		WriteDirectory(book, quantity);
		inputfile.close();
		SwitchSearchMetod(quantity, book);
	}
	else {
		cout << "Ошибка! Не удалось открыть файл F1.txt.\n";
	}
	system("pause");
	return 0;
}