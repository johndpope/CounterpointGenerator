#include "counterpoint_writer.h"
#include "note.h"
#include "staff.h"
#include "tree.hh"
#include "tree_util.hh"
#include <ctime>
#include <set>
#include <cstdlib>
using namespace std;

CounterpointWriter::CounterpointWriter(const Staff& cantus_firmus, const Staff& counterpoint)  {
	cantus_firmus_ = cantus_firmus;  // calls copy constructor?
	counterpoint_ = counterpoint;	 // calls copy constructor?
	current_note_ = 0;
	Note first_note = cantus_firmus[current_note_];
	Note first_counterpoint = first_note + 7;
	counterpoint_.AddNote(first_counterpoint); // starts on a P5
	
	current_interval_ = 12;
	is_perfect_consonance_ = true;
	allowable_intervals_ = { 3,4/*,7,8,9,12,15,16 */}; // m3, M3, P4, P5, m6, M6, P8, m10, M10
	allowable_leaps_ = { /*-9, -8, -7, -6, -5,*/ -4, -3, -2, /*-1, 0, 1,*/ 2, 3, 4/*, 5, 7, 8, 9*/ }; // not aug4/dim5, maj7, min7
	allowable_steps_ = { 0, 1, 2 };
}

bool CounterpointWriter::is_valid_interval(int interval) const {
	set<int>::iterator it = allowable_intervals_.find(interval);
	if (it != allowable_intervals_.end()) {
		//cout << "Valid Interval " << interval << endl;
		return true;
	}
	else {
		//cout << "Invalid Interval " << interval << endl;
		return false;
	}
}

void CounterpointWriter::NextNote() {
	// find interval
	int pitch1 = cantus_firmus_[current_note_].pitch();
	int pitch2 = counterpoint_[current_note_].pitch();
	int interval = pitch2 - pitch1;
	int motion;

	current_note_++;

	// find direction of cantus firmus
	if (cantus_firmus_[current_note_].pitch() - pitch1 > 0)
		cout << "moving up" << endl;
	else if (cantus_firmus_[current_note_].pitch() - pitch1 < 0) 
		cout << "moving down" << endl;
	else
		cout << "staying the same" << endl;

	Note next_note;
	do {
		if (cantus_firmus_[current_note_].pitch() - pitch1 == 0)
			motion = 3;
		else
			motion = rand() % 4;
		cout << motion << endl;

		switch (motion) {
		case 0: next_note = ParallelMotion(); cout << "parallel" << endl; break;
		case 1: next_note = SimilarMotion(); cout << "similar" << endl; break;
		case 2: next_note = ContraryMotion(); cout << "contrary" << endl; break;
		case 3: next_note = ObliqueMotion(); cout << "oblique" << endl; break;
		}
		
		current_interval_ = next_note.absolute_pitch() - cantus_firmus_[current_note_].absolute_pitch();

	} while (current_interval_ < 0 || current_interval_ > 16 || is_valid_interval(current_interval_) == false); 
	// counterpoint is below cantus firmus or interval is greater than a 10th or interval is not valid

	counterpoint_.AddNote(next_note);

	current_interval_ = counterpoint_[current_note_].pitch() - cantus_firmus_[current_note_].pitch();
	switch (current_interval_) {
	case 0:  // P1
	case 5:  // P4
	case 7:  // P5
	case 12: // P8
		is_perfect_consonance_ = true; break;
	default: 
		is_perfect_consonance_ = false;
	}

}

void CounterpointWriter::GeneratePossibleNotes() {
	tree<Note>::iterator top, next;
	top = possible_notes_.begin();
	next = possible_notes_.insert(top, counterpoint_[0]);
	bool can_leap = true;

	tree<Note>::breadth_first_queued_iterator tree_iter = next;
	for (tree_iter; tree_iter != possible_notes_.end_breadth_first(); ++tree_iter) {
		int current_depth = possible_notes_.depth(tree_iter);
		cout << current_depth << " " << possible_notes_.size() << " ";

		tree<Note>::breadth_first_queued_iterator tree_iter_parent = possible_notes_.parent(tree_iter);
		if (tree_iter_parent != possible_notes_.end_breadth_first()) { // if this is not the first note, i.e. no parent
			int last_pitch = (*tree_iter_parent).absolute_pitch();
			int this_pitch = (*tree_iter).absolute_pitch();
			can_leap = (abs(last_pitch - this_pitch) < 3); // you can leap if the last interval was a step
			cout << can_leap << " ";
		}
		bool before_last_note = (current_depth < cantus_firmus_.NumberOfNotes());
		cout << before_last_note << " ";
		if (before_last_note) {
			set<int>::iterator leap_iter_begin = can_leap ? allowable_leaps_.begin() : allowable_steps_.begin();
			set<int>::iterator leap_iter_end = can_leap ? allowable_leaps_.end() : allowable_steps_.end();
			for (set<int>::iterator leap_iter = leap_iter_begin; leap_iter != leap_iter_end; ++leap_iter) {
				Note possible_note = *tree_iter + *leap_iter;
				//cout << possible_note << " ";
				next = possible_notes_.append_child(tree_iter, possible_note);
			}
		}
		else {
			break;
		}
		cout << endl;
		//kptree::print_tree_bracketed(possible_notes_);
		cout << endl;
	}

	cout << endl;
	cout << "======================" << endl;
}

Note CounterpointWriter::ParallelMotion() {
	int interval = cantus_firmus_[current_note_].pitch() - cantus_firmus_[current_note_ - 1].pitch();
	Note next_note = counterpoint_[current_note_ - 1] + interval;
	return next_note;
}

Note CounterpointWriter::SimilarMotion() {
	int interval = cantus_firmus_[current_note_].pitch() - cantus_firmus_[current_note_ - 1].pitch();
	int jump = rand() % abs(interval) + 1; // between 1 half-step and the cantus firmus jump
	Note next_note;
	if (interval < 0)
		next_note = counterpoint_[current_note_ - 1] - jump;
	else if (interval > 0)
		next_note = counterpoint_[current_note_ - 1] + jump;
	cout << next_note << endl;
	return next_note;
}

Note CounterpointWriter::ContraryMotion() {
	int interval = cantus_firmus_[current_note_].pitch() - cantus_firmus_[current_note_ - 1].pitch();
	int jump = rand() % abs(interval) + 1; // between 1 half-step and the cantus firmus jump
	Note next_note;
	if (interval < 0)
		next_note = counterpoint_[current_note_ - 1] + jump;
	else if (interval > 0)
		next_note = counterpoint_[current_note_ - 1] - jump;
	return next_note;
}

Note CounterpointWriter::ObliqueMotion() {
	int interval = cantus_firmus_[current_note_].pitch() - cantus_firmus_[current_note_ - 1].pitch();
	int jump;
	if (interval == 0)
		jump = rand() % 12 + 1;
	else
		jump = 0;
	Note next_note = counterpoint_[current_note_ - 1] + jump;
	return next_note;
}