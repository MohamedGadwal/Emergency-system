#pragma once
#include <string>
#include "Hospital.h"
using namespace std;
enum Mode {
	Interactive = 1,
	Silent,
};
class Request;
class Car;
class Hospital;
class Organizer;
class UI
{
	// I totally Don't have any idea of what this bro is doing.😂😂😂
private:
	string Infile;
	string Outfile;
	Mode Currentmode;
	Organizer* organizer;
public :
	UI(Mode mode, Organizer* org);
	string GetInfile()const;
	void SetInFile(string infile);
	string GetOutFile() const;
	void SetOutFile(string outfile);
	Mode GetMode() const;
	void SetMode(int mode);
	void Print();
	~UI();
	
};


