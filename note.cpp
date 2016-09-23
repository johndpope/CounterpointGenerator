#include "note.h"
#include <iostream>
#include <string>
using namespace std;

Note::Note() {
	pitch_ = 0;
	octave_ = 4;  // default note C4
}

Note::Note(int pitch) { 
	if (pitch > 11)  // pitch should not be > 11 or < 0
		pitch = 11;
	else if (pitch < 0)
		pitch = 0;
	pitch_ = pitch;
	octave_ = 4;
}

Note::Note(int pitch, int octave) {
	if (pitch > 11)  // pitch should not be > 11 or < 0
		pitch = 11;
	else if (pitch < 0)
		pitch = 0;

	if (octave > 8)  // octave should not be > 8 or < 0
		octave = 8;
	else if (octave < 0)
		octave = 0;
	pitch_ = pitch;
	octave_ = octave;
}

int Note::pitch() const {
	return pitch_;
}

int Note::octave() const {
	return octave_;
}

void Note::set_pitch(int pitch) {
	pitch_ = pitch;
}

void Note::set_octave(int octave) {
	octave_ = octave;
}

string Note::NoteName() const {
	string pitch_letter;
	switch (pitch_) {	// convert integer to letter notation
	case 0: pitch_letter = "C"; break;
	case 1: pitch_letter = "C#"; break;
	case 2: pitch_letter = "D"; break;
	case 3: pitch_letter = "D#"; break;
	case 4: pitch_letter = "E"; break;
	case 5: pitch_letter = "F"; break;
	case 6: pitch_letter = "F#"; break;
	case 7: pitch_letter = "G"; break;
	case 8: pitch_letter = "G#"; break;
	case 9: pitch_letter = "A"; break;
	case 10: pitch_letter = "A#"; break;
	case 11: pitch_letter = "B"; break;
	}
	pitch_letter += to_string(octave_); // concatenate with octave
	return pitch_letter;
}

string Note::LilyPondNoteName() const {
	string pitch_letter, octave_letter;
	switch (pitch_) {	// convert integer pitch to lily pond notation
	case 0: pitch_letter = "c"; break;
	case 1: pitch_letter = "cis"; break; // is = sharp, es = flat
	case 2: pitch_letter = "d"; break;
	case 3: pitch_letter = "dis"; break;
	case 4: pitch_letter = "e"; break;
	case 5: pitch_letter = "f"; break;
	case 6: pitch_letter = "fis"; break;
	case 7: pitch_letter = "g"; break;
	case 8: pitch_letter = "gis"; break;
	case 9: pitch_letter = "a"; break;
	case 10: pitch_letter = "ais"; break;
	case 11: pitch_letter = "b"; break;
	}
	switch (octave_) { // convert integer octave to lily pond notation (absolute)
	case 0: octave_letter = ",,,"; break;
	case 1: octave_letter = ",,"; break;
	case 2: octave_letter = ","; break;
	case 3: break;
	case 4: octave_letter = "'"; break;
	case 5: octave_letter = "''"; break;
	case 6: octave_letter = "'''"; break;
	case 7: octave_letter = "''''"; break;
	case 8: octave_letter = "'''''"; break;
	}
	return pitch_letter + octave_letter;
}

Note Note::operator++() {
	if (pitch_ == 0 && octave_ == 8)  // do not increment if note is C8
		cout << "Highest note on piano reached" << endl;
	else if (pitch_ == 11) {  // if note is B
		pitch_ = 0;			  // note is now C
		octave_++;			  // increment octave
	}
	else pitch_++;			  // else increment pitch by 1
	return *this;			  // return self
}

Note Note::operator--() {
	if (pitch_ == 9 && octave_ == 0)  // do not decrement if note is A0
		cout << "Lowest note on piano reached" << endl;
	else if (pitch_ == 0) {  // if note is C 
		pitch_ = 11;		 // note is now B
		octave_--;			 // decrement octave
	}
	else pitch_--;			 // else decrement pitch by 1
	return *this;			 // return self
}

Note Note::operator++(int) {
	Note current_note(pitch_, octave_);  // store current state of Note
	++(*this);							 // increment Note
	return current_note;				 // return Note before increment
}

Note Note::operator--(int) {
	Note current_note(pitch_, octave_);  // see implementation of postfix increment operator
	--(*this);
	return current_note;
}

Note operator+(Note note, int interval) {
	note += interval;
	int pitch = note.pitch();
	int octave = note.octave();
	while (pitch < 0) {		// out of one-octave range
		octave--;			// decrease new note by one octave - FIX: octave too low?
		pitch += 12;		// increase new pitch by one octave
	}
	note.set_pitch(pitch);
	note.set_octave(octave);
	return note;
}

Note operator+(int interval, const Note& note) {
	return note + interval;
}

Note operator+(const Note& note1, const Note& note2) {
	int interval;
	if (note1.pitch() > note2.pitch())
		interval = note1.pitch() - note2.pitch();
	else
		interval = note2.pitch() - note1.pitch();
	return note1 + interval;	
}

Note& Note::operator+=(int interval) {
	int new_pitch = pitch_ + interval;
	int new_octave = octave_;
	while (new_pitch > 11) {	// out of one-octave range
		new_octave++;			// increase new note by one octave
		new_pitch -= 12;		// lower new pitch by one octave
	}
	pitch_ = new_pitch;
	octave_ = new_octave;
	return *this;
}

Note operator-(Note note, int interval) {
	note -= interval;
	int pitch = note.pitch();
	int octave = note.octave();
	while (pitch > 11) {	// out of one-octave range
		octave++;			// increase new note by one octave - FIX: octave too high?
		pitch -= 12;		// decrease new pitch by one octave
	}
	note.set_pitch(pitch);
	note.set_octave(octave);
	return note;
}

Note operator-(int interval, const Note& note) {
	return note - interval;
}

Note operator-(const Note& note1, const Note& note2) {
	int interval;
	if (note1.pitch() > note2.pitch())
		interval = note1.pitch() - note2.pitch();
	else
		interval = note2.pitch() - note1.pitch();
	return note1 - interval;
}

Note& Note::operator-=(int interval) {
	int new_pitch = pitch_ - interval;
	int new_octave = octave_;
	while (new_pitch < 0) {	// out of one-octave range
		new_octave--;			// decrease new note by one octave - FIX: octave too low?
		new_pitch += 12;		// increase new pitch by one octave
	}
	pitch_ = new_pitch;
	octave_ = new_octave;
	return *this;
}

ostream& operator<<(ostream& output, const Note& note) {
	output << note.NoteName();
	return output;
}

bool operator== (const Note& note1, const Note& note2) {
	return (note1.absolute_pitch() == note2.absolute_pitch());
}

bool operator>(const Note& note1, const Note& note2) {
	return (note1.absolute_pitch() > note2.absolute_pitch());
}

bool operator<(const Note& note1, const Note& note2) {
	return (note1.absolute_pitch() < note2.absolute_pitch());
}

bool operator>=(const Note& note1, const Note& note2) {
	return (note1 > note2 || note1 == note2);
}

bool operator<=(const Note& note1, const Note& note2) {
	return (note1 < note2 || note1 == note2);
}

bool operator!=(const Note& note1, const Note& note2) {
	return !(note1 == note2);
}