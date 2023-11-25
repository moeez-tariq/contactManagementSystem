#ifndef CONTACT_H
#define CONTACT_H //definitions

#include<iostream> //include relevant libraries
#include<sstream>
#include<fstream>
//#include "vector.h"
using namespace std;

class Contact
{
	private: //define all private attributes
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		bool isFav;

	//include public functions
	public:
		Contact();
		Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav);
		void printLineContact();
		void printParaContact();
		void updateContact();
		void setisFav(bool flag);
		bool getisFav();
		string getEmail();
		string getfname();
		string getlname();
		string getPhone();
		string getCity();
		string getCountry();
		void printCSVContact(fstream& fout);
		
};

#endif