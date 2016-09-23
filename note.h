#include <iostream>
#include <string>
using namespace std;

#ifndef NOTE_H
#define NOTE_H

const int C = 0, CIS = 1, D = 2, DIS = 3, E = 4, F = 5, FIS = 6, G = 7, GIS = 8, A = 9, AIS = 10, B = 11;

class Note
{
private:
	int pitch_; // 0 = C
	int octave_;
public:
	int pitch() const;
	int octave() const;
	void set_pitch(int pitch);
	void set_octave(int octave);

	int absolute_pitch() const { return octave_ * 12 + pitch_; }

	string NoteName() const;
	string LilyPondNoteName() const;
	
	Note();
	Note(int pitch);
	Note(int pitch, int octave);

	Note operator++();
	Note operator--();
	Note operator++(int);
	Note operator--(int);

	friend ostream& operator<<(ostream& output, const Note& note);
	friend Note operator+(Note note, int interval);
	friend Note operator+(int interval, const Note& note);
	friend Note operator+(const Note& note1, const Note& note2);

	Note& operator+=(int interval);

	friend Note operator-(Note note, int interval);
	friend Note operator-(int interval, const Note& note);
	friend Note operator-(const Note& note1, const Note& note2);
	Note& operator-=(int interval);

	friend bool operator== (const Note& note1, const Note& note2);
	friend bool operator>(const Note& note1, const Note& note2);
	friend bool operator<(const Note& note1, const Note& note2);

};

#endif