#include <iostream>
#include <Windows.h>
#include <set>

using namespace std;

struct letter {
	char let;
	int i;
	int j;
};

char balda[5][5];
set<letter*> letters;
set<string> usedWords;

void printLetters() {
	for (set<letter*>::iterator ik = letters.begin(); ik != letters.end(); ++ik)
		cout << (*ik)->let << ": " << (*ik)->i << ' ' << (*ik)->j << "\n";
}

void makeGrid() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			balda[i][j] = '_';
}
void printGrid() {
	cout << " |0|1|2|3|4\n";
	for (int i = 0; i < 5; i++) {
		cout << i << '|';
		for (int j = 0; j < 4; j++)
			cout << balda[i][j] << '|';
		cout << balda[i][4] << '\n';
	}
}

const char* withoutFirstLetter(const char* word, int size) {
	char* newWord = new char[size-1];
	for (int i = 0; i < size - 1; i++)
		newWord[i] = word[i + 1];
	return newWord;
}

void findLetter(const char* word, int size, int i, int j, letter* l) {
	if (i >= 0 && i < 5 && j >= 0 && j < 5) {
		if (size > 0) {
			if (balda[i][j] == word[0]) {
				const char* newWord = withoutFirstLetter(word, size);
				findLetter(newWord, size - 1, i + 1, j, l);
				findLetter(newWord, size - 1, i, j + 1, l);
				findLetter(newWord, size - 1, i - 1, j, l);
				findLetter(newWord, size - 1, i, j - 1, l);
			}
			if (l->i == -1 && balda[i][j] == '_') {
				const char* newWord = withoutFirstLetter(word, size);
				letter* nl = new letter{ word[0], i, j };
				findLetter(newWord, size - 1, i + 1, j, nl);
				findLetter(newWord, size - 1, i, j + 1, nl);
				findLetter(newWord, size - 1, i - 1, j, nl);
				findLetter(newWord, size - 1, i, j - 1, nl);
			}
		}
		else {
			if (l->i > -1) {
				letters.insert(l);
			}
		}
	}
};
void findLetter(const char* word, int size) {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			findLetter(word, size, i, j, new letter{ '_',-1,-1 });
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	makeGrid();
	printGrid();

	string word;
	do {
		cout << "Введите слово из 5 букв: ";
		cin >> word;
	} while (word.size() != 5);
	cout << endl;
	for (int i = 0; i < 5; i++)
		balda[2][i] = word.c_str()[i];
	usedWords.insert(word);
	printGrid();

	for (int k=0; k<20;) {
		cout << "Введите слово, которое хотите найти: ";
		cin >> word;
		cout << endl;

		auto wt = usedWords.find(word);
		if (wt!=usedWords.end()) {
			cout << "Слово уже было найдено" << endl;
			continue;
		}

		findLetter(word.c_str(), word.size());
		if (letters.size() == 0)
			cout << "Слово не найдено. Попробуйте снова.\n";
		if (letters.size() == 1) {
			letter* l = (*letters.begin());
			balda[l->i][l->j] = l->let;
			k++;
		}
		if (letters.size() > 1) {
			cout << "Куда и какую вы хотите добавить букву?\n";
			printLetters();
			char l; int i, j;
			cout << "Буква: "; cin >> l;
			cout << "i: "; cin >> i;
			cout << "j: "; cin >> j;
			cout << endl;
			for (set<letter*>::iterator ik = letters.begin(); ik != letters.end(); ++ik) {
				if ((*ik)->let == l && (*ik)->i == i && (*ik)->j == j) {
					balda[i][j] = (*ik)->let;
					usedWords.insert(word);
					k++;
					continue;
				}
			}			
		}
		letters.clear();

		printGrid();
	}
}
