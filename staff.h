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
	/** Vector of Notes in staff. No way to determine duration. */
	vector<Note> notes_;
public:
	/** CONSTRUCTORS */
	/** Nothing in notes_, is_treble_clef_ is true */
	Staff();
	/** Copy constructor */
	Staff(const Staff& s);
	Staff(bool is_treble_clef, vector<Note> notes);

	/** ACCESSORS */
	vector<Note> notes() const;
	bool is_treble_clef() const;

	void AddNote(Note note);
	void ChangeClef();
	int NumberOfNotes();

	/**
	 * Outputs Lilypond representation of notes_ to given ofstream
	 */
	void PrintStaffToFile(string filename, ofstream& fout);
	/** 
	 * Outputs initial Lilypond text to given ofstream
	 * Prints "failed to open file" to standard output if opening file failed
	 */
	void PrintBeginToFile(string filename, ofstream& fout); // move elsewhere?
	/**
	 * Outputs ending Lilypond text to given filename
	 * Prints "Successfully printed to file " + filename to standard output once complete
	 */
	void PrintEndToFile(string filename, ofstream& fout);	// move elsewhere?

	/** OPERATOR OVERLOADS */
	/** 
	 * Outputs all the Notes in staff.notes_
	 */
	friend ostream& operator<<(ostream& output, Staff& staff);
	/** 
	 * Returns the note at the given index in the notes_ vector
	 */
	const Note& operator[](int id) const;
};

#endif