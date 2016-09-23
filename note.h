#include <iostream>
#include <string>
using namespace std;

#ifndef NOTE_H
#define NOTE_H

const int C = 0, CIS = 1, D = 2, DIS = 3, E = 4, F = 5, FIS = 6, G = 7, GIS = 8, A = 9, AIS = 10, B = 11;

class Note
{
private:
	/** The pitch of the Note, where 0 is C and 11 is B */
	int pitch_; // 0 = C
	/** The octave of the Note, from 0 to 8 */
	int octave_;
public:
	/** ACCESSORS */
	int pitch() const;
	int octave() const;

	/** MUTATORS */
	void set_pitch(int pitch);
	void set_octave(int octave);

	/**
	 * Returns the absolute pitch of the note as an int
	 * e.g., pitch_ = 1 and octave_ = 4 will return 49
	 */
	int absolute_pitch() const { return octave_ * 12 + pitch_; }

	/** 
	 * Returns the name of the Note
	 * e.g., pitch_ = 1 and octave_ = 4 will return "C#4"
	 */
	string NoteName() const;
	/** 
	 * Returns the name of the Note as preferred by Lilypond
	 * e.g., pitch_ = 1 and octave_ = 4 will return "cis"
	 */
	string LilyPondNoteName() const;
	
	/** CONSTRUCTORS */
	/** Default constructor. Initializes pitch_ to 0 and octave_ to 4 (C4) */
	Note();
	/** Initializes octave_ to 4 and ensures pitch is between 0 and 11 inclusive. */
	Note(int pitch);
	/** Ensures pitch is between 0 and 11 and octave is between 0 and 8 (both inclusive). */
	Note(int pitch, int octave);

	/** OPERATOR OVERLOADS */
	Note operator++();
	Note operator--();
	Note operator++(int);
	Note operator--(int);

	/** Outputs Note.NoteName() */
	friend ostream& operator<<(ostream& output, const Note& note);

	/*
	 * Returns result of adding interval to note. 
	 * Intervals are passed as an int specifying number of half-steps. 
	 */
	friend Note operator+(Note note, int interval);
	friend Note operator+(int interval, const Note& note);
	friend Note operator+(const Note& note1, const Note& note2);
	Note& operator+=(int interval);

	friend Note operator-(Note note, int interval);
	friend Note operator-(int interval, const Note& note);
	friend Note operator-(const Note& note1, const Note& note2);
	Note& operator-=(int interval);

	friend bool operator==(const Note& note1, const Note& note2);
	friend bool operator>(const Note& note1, const Note& note2);
	friend bool operator<(const Note& note1, const Note& note2);
	friend bool operator>=(const Note& note1, const Note& note2);
	friend bool operator<=(const Note& note1, const Note& note2);
	friend bool operator!=(const Note& note1, const Note& note2);

};

#endif