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

	/* 
	 * Gets the highest note on the branch of possible_notes_ the child_note is a part of.
	 * Assumes the child_note is the latest note in this particular branch.
	 */
	Note GetMaxNote(tree<Note>::breadth_first_queued_iterator child_note);
	/*
	 * Gets the lowest note on the branch of possible_notes_ the child_note is a part of.
	 * Assumes the child_note is the latest note in this particular branch.
	 */
	Note GetMinNote(tree<Note>::breadth_first_queued_iterator child_note);
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