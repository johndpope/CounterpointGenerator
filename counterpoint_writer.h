#include "note.h"
#include "staff.h"
#include <set>
#include "tree.hh"
#include "tree_util.hh"
using namespace std;

#ifndef COUNTERPOINT_WRITER_H
#define COUNTERPOINT_WRITER_H

class CounterpointWriter 
{
private:
	Staff cantus_firmus_;
	Staff counterpoint_;
	int current_note_;  // index of current note on staff
	int current_interval_; // interval between cantus firmus and counterpoint
	bool is_perfect_consonance_;
	set<int> allowable_intervals_; // set of allowable intervals
	set<int> allowable_leaps_;
	set<int> allowable_steps_;
	tree<Note> possible_notes_;

public:
	CounterpointWriter(const Staff& cantus_firmus, const Staff& counterpoint);  // writes first note of counterpoint
	void NextNote();
	void GeneratePossibleNotes();

	// accessors
	Staff cantus_firmus() const { return cantus_firmus_; }
	Staff counterpoint() const { return counterpoint_; }
	int current_note() const { return current_note_; }
	int current_interval() const { return current_interval_; }
	bool is_perfect_consonance() const { return is_perfect_consonance_; }

	bool is_valid_interval(int interval) const;

	Note SimilarMotion();
	Note ContraryMotion();
	Note ObliqueMotion();
	Note ParallelMotion();
	
};

#endif