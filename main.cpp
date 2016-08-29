#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "note.h"
#include "staff.h"
#include "counterpoint_writer.h"
#include "tree.hh"
#include <vector>
using namespace std;


int main() {
	srand(time(0));

	Note j(D, 3), k(D, 3), l(A, 3), m(F, 3), n(E, 3),
		p(D, 3), q(F, 3), r(C, 3), s(D, 3), t(A, 3), u(D, 3);

	vector<Note> cantus_firmus_notes;
	cantus_firmus_notes.insert(cantus_firmus_notes.end(), { j, k, l, m, n, p, q, r, s, t, u });
	Staff cantus_firmus(cantus_firmus_notes), counterpoint;
	cantus_firmus.ChangeClef();

	cout << cantus_firmus << endl;

	CounterpointWriter c(cantus_firmus, counterpoint);

	// beginning the counterpoint
	for (int i = 1; i < c.cantus_firmus().NumberOfNotes(); i++) { // start at 1 - 0th note initialized in constructor
		c.NextNote();
	}

	cout << c.counterpoint() << endl;

	ofstream fout;
	c.cantus_firmus().PrintBeginToFile("test.ly", fout);
	c.counterpoint().PrintStaffToFile("test.ly", fout);
	c.cantus_firmus().PrintStaffToFile("test.ly", fout);
	c.cantus_firmus().PrintEndToFile("test.ly", fout);
}