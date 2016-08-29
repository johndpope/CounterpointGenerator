#include "staff.h"
#include "note.h"
#include <vector>
#include <string>
#include <fstream>
using namespace std;

Staff::Staff() {
	is_treble_clef_ = true;
}

Staff::Staff(const Staff& s) : notes_(s.notes()) {
	is_treble_clef_ = s.is_treble_clef();
}

vector<Note> Staff::notes() const {
	return notes_;
}

bool Staff::is_treble_clef() const {
	return is_treble_clef_;
}

void Staff::AddNote(Note note) {
	notes_.push_back(note);
}

void Staff::ChangeClef() {
	is_treble_clef_ = !is_treble_clef_;
}

void Staff::PrintBeginToFile(string filename, ofstream& fout) {
	fout.open(filename);
	if (fout.fail()) {
		cout << "failed to open file" << endl;
		return;
	}

	fout << "{\n";			// {
	fout << "  <<\n";		//   <<
}

void Staff::PrintStaffToFile(string filename, ofstream& fout) {
	

	fout << "    \\new Staff { ";		// \new Staff {

	if (is_treble_clef_)
		fout << "\\clef \"treble\" ";	//   \clef "treble"
	else								//		OR
		fout << "\\clef \"bass\" ";		//   \clef "bass"

	for (int i = 0; i < this->NumberOfNotes(); i++) {
		Note current_note = this->notes_[i];
		fout << current_note.LilyPondNoteName() << "1 ";
	}

	fout << "}\n";						// }

}

void Staff::PrintEndToFile(string filename, ofstream& fout) {
	fout << "  >>\n";		//   >>
	fout << "}";			// }

	fout.close();

	cout << "Successfully printed to file " << filename << endl;
}

int Staff::NumberOfNotes() {
	return notes_.size();
}

ostream& operator<<(ostream& output, Staff& staff) {
	for (int i = 0; i < staff.NumberOfNotes(); i++)
		output << staff.notes()[i] << " ";
	return output;
}

const Note& Staff::operator[](int id) const {
	return notes_[id];
}