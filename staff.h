#include "note.h"
#include <vector>
#include <string>
#include <vector>
using namespace std;

#ifndef STAFF_H
#define STAFF_H

class Staff
{
private:
	bool is_treble_clef_;
	vector<Note> notes_;
public:
	Staff();
	Staff(const Staff& s);
	Staff(bool is_treble_clef, vector<Note> notes) : notes_(notes) { is_treble_clef_ = is_treble_clef; }

	vector<Note> notes() const;
	bool is_treble_clef() const;

	void AddNote(Note note);
	void ChangeClef();
	int NumberOfNotes();

	void PrintStaffToFile(string filename, ofstream& fout);
	void PrintBeginToFile(string filename, ofstream& fout); // move elsewhere?
	void PrintEndToFile(string filename, ofstream& fout);	// move elsewhere?

	friend ostream& operator<<(ostream& output, Staff& staff);
	const Note& operator[](int id) const;
};

#endif