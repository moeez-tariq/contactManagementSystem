#include "contact.h"

Contact::Contact() //constructor (empty)
{
	this->fname = "";
	this->lname = "";
	this->email = "";
	this->primaryPhone = "";
	this->city = "";
	this->country = "";
	this->isFav = false;
}

Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav) //constructor
{
	this->fname = fname;
	this->lname = lname;
	this->email = email;
	this->primaryPhone = primaryPhone; 
	this->city = city;
	this->country = country;
	this->isFav = isFav; 
}

void Contact::printLineContact() //print the contact in a line in the terminal
{

	cout << fname << " " << lname << ", " << email << ", " << primaryPhone << ", " << city << ", " << country << ", " << isFav << endl;
}

void Contact::printCSVContact(fstream& fout) //print the contact in the file
{

	fout << fname << ", " << lname << ", " << email << ", " << primaryPhone << ", " << city << ", " << country << ", " << isFav << endl;
}

void Contact::printParaContact() //print the contact in the paragraph form in the terminal
{
	cout << "Name: " << fname << " " << lname << endl;
	cout << "Email: " << email << endl;
	cout << "Phone#: " << primaryPhone << endl;
	cout << "City: " << city << endl;
	cout << "Country: " << country << endl;
	cout << endl;
}

void Contact::updateContact() //update contact details
{
	bool more_changes = true;
	while (more_changes == true) //keep looping till the user doesnt say "n"
	{
		cout << "1) First Name\n";
		cout << "2) Last Name\n";
		cout << "3) Email\n";
		cout << "4) Primary Phone\n";
		cout << "5) City\n";
		cout << "6) Country\n";
		string option = "";
		//cin >> option;
		string newinput = "";
		bool correct_option = false;
		string y_or_n = "";

		while (correct_option == false)
		{
			cout << endl << "Please enter the number of the field you want to edit [1 - 6]: ";
			getline(cin, option);
			correct_option = true;

			if (option == "1")
			{
				cout << "Please Enter the new First Name: ";
				cin >> newinput;
				string fupper = "";
				for (int i = 0; i < newinput.length(); i++) //go over the input using its length
				{
					fupper += toupper(newinput[i]); //lower each character and concatenate with previous ones
				}
				this->fname = fupper;
			}
			else if (option == "2")
			{
				cout << "Please Enter the new Last Name: ";
				cin >> newinput;
				string lupper = "";
				for (int i = 0; i < newinput.length(); i++) //go over the input using its length
				{
					lupper += toupper(newinput[i]); //lower each character and concatenate with previous ones
				}
				this->lname = lupper;
			}
			else if (option == "3")
			{
				cout << "Please Enter the new Email: ";
				cin >> newinput;
				this->email = newinput;
			}
			else if (option == "4")
			{
				cout << "Please Enter the new Phone Number: ";
				cin >> newinput;
				this->primaryPhone = newinput;
			}
			else if (option == "5")
			{
				cout << "Please Enter the new City: ";
				cin >> newinput;
				this->city = newinput;
			}
			else if (option == "6")
			{
				cout << "Please Enter the new Country: ";
				cin >> newinput;
				this->country = newinput;
			}
			else
			{
				correct_option = false;
				cout << "Invalid Input! Please Try Again!\n";
			}
		}

		while (true) //loop till valid input
		{
			cout << "Do you want to make more changes [y/n]: "; 
			cin >> y_or_n;
			if (y_or_n == "y")
			{
				more_changes = true;
				break;
			}
			else if (y_or_n == "n")
			{
				more_changes = false;
				break;
			}
			else
			{
				cout << "Invalid Input. Please enter either y or n!\n";
				cout << endl;
			}
		}
	}
}

//getter and setter methods
void Contact::setisFav(bool flag)
{
	this->isFav = flag;
}

bool Contact::getisFav()
{
	return isFav;
}

string Contact::getEmail()
{
	return email;
}

string Contact::getfname()
{
	return fname;
}

string Contact::getlname()
{
	return lname;
}

string Contact::getPhone()
{
	return primaryPhone;
}

string Contact::getCity()
{
	return city;
}

string Contact::getCountry()
{
	return country;
}
