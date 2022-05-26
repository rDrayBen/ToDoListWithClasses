#include "FubctionsHeader.h"
#include <vector>
#include <string>
#include <fstream>
#include "di.hpp"
namespace di = boost::di;
using namespace std;

void UncomplitedList::RemoveAllNotes() {
	ofstream UncompitedFile;

	UncompitedFile.open(pathForUncomplited);
	UncompitedFile.close();

	cout << "All notes deleted succesfully" << endl;
}

string UncomplitedList::AddNoteToUncomplited(string newnote) {

	fstream WriteInUncomplitedFile;

	WriteInUncomplitedFile.open(pathForUncomplited, ios::app);

	if (WriteInUncomplitedFile.is_open()) {
		WriteInUncomplitedFile << newnote << endl;
	}

	WriteInUncomplitedFile.close();
	return "Note added!";
}

void UncomplitedList::Show()
{
	ifstream ReadFromUncomplitedFile;

	ReadFromUncomplitedFile.open(pathForUncomplited);

	string tempNote;
	for (int i = 1; !ReadFromUncomplitedFile.eof(); i++) {
		getline(ReadFromUncomplitedFile, tempNote);
		if (tempNote.empty()) {
			continue;
		}
		cout << "[" << i << "]" << tempNote << endl;
	}

	ReadFromUncomplitedFile.close();
}

vector <string> UncomplitedList::FindNotesWithWord(const string note_to_find)
{
	FindUncomplitedResults.clear();

	ifstream ReadFromUncompletedFile;

	ReadFromUncompletedFile.open(pathForUncomplited);

	string tempNote;

	while (!ReadFromUncompletedFile.eof()) {
		getline(ReadFromUncompletedFile, tempNote);

		if (tempNote.find(note_to_find) != string::npos) {
			FindUncomplitedResults.push_back(tempNote);
		}
	}

	ReadFromUncompletedFile.close();
	return FindUncomplitedResults;
}

vector <string> UncomplitedList::SaveAllUncomplitedNotes() {
	saveUncomplitedNotes.clear();

	ifstream ReadFromUncompletedFile;

	ReadFromUncompletedFile.open(pathForUncomplited);

	string tempNote;

	while (!ReadFromUncompletedFile.eof()) {
		getline(ReadFromUncompletedFile, tempNote);
		if (tempNote.empty()) {
			continue;
		}

		saveUncomplitedNotes.push_back(tempNote);
	}

	ReadFromUncompletedFile.close();

	return saveUncomplitedNotes;
}

void UncomplitedList::RemoveOneNote(int your_choice)
{
	vector <string> savedUncomplitedNotes = SaveAllUncomplitedNotes();
	if (your_choice == 0) return;

	saveUncomplitedNotes.erase(saveUncomplitedNotes.begin() + your_choice - 1);

	ofstream WriteInUncompletedFile;

	WriteInUncompletedFile.open(pathForUncomplited);

	for (int i = 0; i < saveUncomplitedNotes.size(); i++) {
		WriteInUncompletedFile << saveUncomplitedNotes[i] << endl;
	}
	WriteInUncompletedFile.close();
}








void ComplitedList::RemoveAllNotes() {
	ofstream ComplitedFile;

	ComplitedFile.open(pathForComplited);
	ComplitedFile.close();

	cout << "All notes deleted succesfully" << endl;
}

void ComplitedList::AddNoteToComplited(int note_to_add, vector <string> savedUncomplitedNotes) {

	fstream WriteInComplitedFile;

	WriteInComplitedFile.open(pathForComplited, ios::app);

	if (WriteInComplitedFile.is_open()) {
		WriteInComplitedFile << savedUncomplitedNotes[note_to_add - 1] << endl;
	}

	WriteInComplitedFile.close();
	cout << "This task is now done!" << endl;

}

void ComplitedList::Show() {
	ifstream ReadFromComplitedFile;

	ReadFromComplitedFile.open(pathForComplited);

	string tempNote;
	for (int i = 1; !ReadFromComplitedFile.eof(); i++) {
		getline(ReadFromComplitedFile, tempNote);
		if (tempNote.empty()) {
			continue;
		}
		cout << "[" << i << "]" << tempNote << endl;
	}

	ReadFromComplitedFile.close();
}

vector <string> ComplitedList::FindNotesWithWord(const string note_to_find) {

	FindComplitedResults.clear();

	ifstream ReadFromCompletedFile;

	ReadFromCompletedFile.open(pathForComplited);

	string tempNote;

	while (!ReadFromCompletedFile.eof()) {
		getline(ReadFromCompletedFile, tempNote);

		if (tempNote.find(note_to_find) != string::npos) {
			FindComplitedResults.push_back(tempNote);
		}
	}

	ReadFromCompletedFile.close();
	return FindComplitedResults;
}

vector <string> ComplitedList::SaveAllComplitedNotes() {
	saveComplitedNotes.clear();

	ifstream ReadFromCompletedFile;

	ReadFromCompletedFile.open(pathForComplited);

	string tempNote;

	while (!ReadFromCompletedFile.eof()) {
		getline(ReadFromCompletedFile, tempNote);
		if (tempNote.empty()) {
			continue;
		}

		saveComplitedNotes.push_back(tempNote);
	}

	ReadFromCompletedFile.close();

	return saveComplitedNotes;
}

void ComplitedList::RemoveOneNote(int your_choice) {
	vector <string> savedComplitedNotes = SaveAllComplitedNotes();
	if (your_choice == 0) return;

	saveComplitedNotes.erase(saveComplitedNotes.begin() + your_choice - 1);

	ofstream WriteInCompletedFile;

	WriteInCompletedFile.open(pathForComplited);

	for (int i = 0; i < saveComplitedNotes.size(); i++) {
		WriteInCompletedFile << saveComplitedNotes[i] << endl;
	}
	WriteInCompletedFile.close();
}





void ToDoList::Print(int action) {

	//IoC контейнери
	auto injector1 = di::make_injector(
		di::bind<string>.to<>(pathForUncomplited)
	);

	auto injector2 = di::make_injector(
		di::bind<string>.to<>(pathForComplited)
	);

	auto uncomplitedMember = injector1.create<UncomplitedList>();
	auto complitedMember = injector2.create<ComplitedList>();


	if (action == 1) {
		string your_note;
		getline(cin, your_note);
		cout << "Write your note here: " << endl;
		getline(cin, your_note);
		cout << uncomplitedMember.AddNoteToUncomplited(your_note) << endl;
	}
	else if (action == 2) {
		string note_to_find;
		getline(cin, note_to_find);
		cout << "Enter your note: ";
		getline(cin, note_to_find);
		vector<string> results;
		results.clear();

		results = uncomplitedMember.FindNotesWithWord(note_to_find);

		if (results.size() != 0) {
			cout << "Found notes: " << endl;
			for (int i = 0; i < results.size(); i++) {
				cout << "[" << i + 1 << "]" << results[i] << endl;
			}
		}
		else {
			cout << "No such notes" << endl;
		}
		
	}
	else if (action == 3) {
		cout << "All notes: " << endl;
		uncomplitedMember.Show();
		cout << endl;
		cout << "Which note you want to remove(if you want to go back print 0): ";
		int your_choice;
		cin >> your_choice;
		if (your_choice != 0) {
			uncomplitedMember.RemoveOneNote(your_choice);
			cout << "This note is removed" << endl;
		}
		else {
			cout << "Returning to menu..." << endl;
		}
	}
	else if (action == 4) {
		uncomplitedMember.RemoveAllNotes();
	}
	else if (action == 5) {
		uncomplitedMember.Show();
		int number;
		cout << "Which note you want to mark as done: ";
		cin >> number;
		complitedMember.AddNoteToComplited(number, uncomplitedMember.SaveAllUncomplitedNotes());

		uncomplitedMember.RemoveOneNote(number);
	}
	else if (action == 7) {
		cout << "All notes: " << endl;
		complitedMember.Show();
		cout << endl;
		cout << "Which note you want to remove(if you want to go back print 0): ";
		int your_choice;
		cin >> your_choice;
		if (your_choice != 0) {
			complitedMember.RemoveOneNote(your_choice);
			cout << "This note is removed" << endl;
		}
		else {
			cout << "Returning to menu..." << endl;
		}
		
	}
	else if (action == 6) {
		string note_to_find;
		getline(cin, note_to_find);
		cout << "Enter your note: ";
		getline(cin, note_to_find);
		vector<string> results;
		results.clear();

		results = complitedMember.FindNotesWithWord(note_to_find);

		if (results.size() != 0) {
			cout << "Found notes: " << endl;
			for (int i = 0; i < results.size(); i++) {
				cout << "[" << i + 1 << "]" << results[i] << endl;
			}
		}
		else {
			cout << "No such notes" << endl;
		}
	}
	else if (action == 8) {
		complitedMember.RemoveAllNotes();
	}
	else if (action == 10) {
		uncomplitedMember.Show();
	}
	else if (action == 11) {
		complitedMember.Show();
	}

}