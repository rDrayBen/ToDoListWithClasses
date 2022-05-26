#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "di.hpp"
namespace di = boost::di;
using namespace std;

//абстрактний клас
class IToDoList {
protected:
	virtual void RemoveAllNotes() = 0;
	virtual vector <string> FindNotesWithWord(const string note_to_find) = 0;
	virtual void Show() = 0;
	virtual void RemoveOneNote(int your_choice) = 0;
};

//клас для роботи зі списком невиконаних справ
class UncomplitedList: public IToDoList {
public:
	UncomplitedList(string pathForUncomplited) {
		this->pathForUncomplited = pathForUncomplited;
	}
	vector <string> FindUncomplitedResults;
	vector <string> saveUncomplitedNotes;

	//функція очищення списку невиконаних справ
	void RemoveAllNotes() override;

	//функція додавання елементів в список невиконаних
	string AddNoteToUncomplited(string newnote);

	void Show() override;

	//функція, що знаходить всі нотатки із заданим словом
	vector <string> FindNotesWithWord(const string note_to_find) override;

	//функція для проміжного зберігання списку невиконаних справ
	vector <string> SaveAllUncomplitedNotes();

	//функція видалення елементу по його порядковому номеру зі списку невиконаних
	void RemoveOneNote(int your_choice) override;
private:
	//стрічка адреси файлу невиконаних справ
	string pathForUncomplited;
};

//клас для роботи зі списком виконаних справ
class ComplitedList : public IToDoList {
public: 
	ComplitedList(string pathForComplited) {
		this->pathForComplited = pathForComplited;
	}
	vector <string> FindComplitedResults;
	vector <string> saveComplitedNotes;

	//функція очищення списку виконаних справ
	void RemoveAllNotes() override; 

	//функція додавання елементів із невиконаних у виконані
	void AddNoteToComplited(int note_to_add, vector <string> savedUncomplitedNotes);

	void Show() override;

	//функція знаходження нотатків із заданим словом у списку виконаних справ
	vector <string> FindNotesWithWord(const string note_to_find) override;

	//функція проміжного зберігання виконаних справ
	vector <string> SaveAllComplitedNotes();

	//функція видалення нотатки по заданому порядковому номеру із виконаних
	void RemoveOneNote(int your_choice) override;
private:
	//стрічка адреси файлу виконаних справ
	string pathForComplited;
};

//клас реалізації програми
class ToDoList : public UncomplitedList, public ComplitedList {
public:
	ToDoList(): UncomplitedList(pathForUncomplited), ComplitedList(pathForComplited) {}

	//функція реалізації виклику всіх функцій по заданому запиту користувача
	void Print(int action);

private:
	//стрічки з адресами обох файлів
	string pathForUncomplited = "Notes for ToDoList(Uncompleted).txt";
	string pathForComplited = "Notes for ToDoList(Complited).txt";
};

