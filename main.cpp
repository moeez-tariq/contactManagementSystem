//include relevant libraries and .h files
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>
#include "contact.h"
#include "contactbst.h"
#include "vector.h"

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"del <key>          :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markfv <key>       :Mark as favourite"<<endl
		<<"umarkfv <key>      :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}

string toUpper(string input) //upper cases the parameter
{
	string upper = "";
	for (int i = 0; i < input.length(); i++) //go over the input using its length
	{
		upper += toupper(input[i]); //lower each character and concatenate with previous ones
	}
	return upper;
}
//=========================================================
int main(void)
{
	ContactBST myContactBST;
	string user_input;
	string option;
	string para1;
	while(true)
	{
		Node* rootptr = myContactBST.getRoot();
		listCommands();
		cout<<">";

		getline(cin, user_input);
		stringstream sstr(user_input); // parse userinput into command and parameter
		getline(sstr, option, ' ');
		getline(sstr, para1, '\n');
		if (option == "add")
		{
			string fname, lname, email, phone, city, country, favorite, upper;
			bool isFav = false;
			cout << "Please enter the details of the contact:\n";
			cout << "First Name: ";
			cin >> fname;
			fname = toUpper(fname); //uppercasing all names to ensure uniformity of key and overlapping data
			cout << "Last Name: ";
			cin >> lname;
			lname = toUpper(lname);
			cout << "Email: ";
			cin >> email;
			cout << "Phone#: ";
			cin >> phone;
			cout << "City: ";
			cin >> city;
			cout << "Country: ";
			cin >> country;
			while (true) //make sure the input is valid
			{
				cout << "Do you want to add the contact in your favourites (y/n): ";
				cin >> favorite;
				if (favorite == "y")
				{
					isFav = true;
					break;
				}
				else if (favorite == "n")
				{
					isFav = false;
					break;
				}
				else
				{
					cout << "Invalid Input. Please enter y or n!\n";
					cout << endl;
				}

			}
			//email = "abc"; phone = "abc"; city = "abc"; country = "abc"; isFav = true;

			string key = "";
			key = fname + " " + lname; //making key with first name space last name

			Contact* newContact = new Contact(fname, lname, email, phone, city, country, isFav); //making a new contact
			myContactBST.insert_helper(key, newContact); //adding it to the binary search tree

			cout << "Contact " << key << " has successfully been added!\n";

		}
		else if (option == "import")
		{
			string path_provided = para1;
			//path_provided = "contact_examples.csv"; //just in case path does not work and so use this to check the import and export functions
			int contactNum = myContactBST.importCSV(rootptr, path_provided); //returns the number of contacts imported
			if (contactNum == -1)
			{
				cout << "Path: " << path_provided << endl;
				cout << "Wrong Path Provided! Please Try Again!\n";
				cout << endl;
			}
			else
			{
				cout << contactNum << " Contacts Imported!\n";
			}
		}
		else if (option == "export")
		{
			string path_provided = para1;
			//path_provided = "contact_examples.csv";
			int contactNum = myContactBST.exportCSV(rootptr, path_provided); //returns the number of contacts exported
			if (contactNum == -1)
			{
				cout << "Path: " << path_provided << endl;
				cout << "Wrong Path Provided! Please Try Again!\n";
				cout << endl;
			}
			else
			{
				cout << contactNum << " Contacts Exported!\n";
			}
		}
		else if (option == "searchFor")
		{
			string key_input = toUpper(para1); //uppercases the input key as well
			Node* ptr_to_contact = myContactBST.search(rootptr, key_input);
			if (ptr_to_contact == nullptr)
			{
				cout << "Key Not Found!\n";
			}
			else
			{
				cout << "Key Found!\n";
				int records_found = ptr_to_contact->getData()->size(); //checks to see how many contacts in a key
				cout << "Records Found: " << records_found << endl;
				for (int i = 0; i < records_found; i++)
				{
					cout << (i + 1) << ". ";
					ptr_to_contact->getData()->at(i).printParaContact(); //print all the contacts associated with a key
					cout << endl;
				}
			}

			cout << endl;
		}
		else if (option == "del") //deletes a contact
		{
			string key_input = toUpper(para1);
			myContactBST.remove_helper(key_input);
		}
		else if (option == "edit") //edits the attributes of a contact
		{
			string key_input = toUpper(para1);
			Node* temp = myContactBST.update(rootptr, key_input);
			if (temp == nullptr)
			{
				cout << "Contact Not Found!\n";
			}
		}
		else if (option == "markfv") //marks a contact favourite
		{
			string key_input = toUpper(para1);
			bool temp = myContactBST.markFav(rootptr, key_input);
			if (temp == false)
			{
				cout << "Key Not Found! Mark Fav Unsuccessful!\n";
			}
		}
		else if (option == "umarkfv") //unamrks a contact from favourite
		{
			string key_input = toUpper(para1);
			bool flag = myContactBST.unmarkFav(rootptr, key_input);
			if (flag == false)
			{
				cout << "Key Not Found! Unmark Fav Unsuccessful!\n";
			}
		}
		else if (option == "printASC") //prints the contacts in ascending order
		{
			myContactBST.printASC(rootptr);
		}
		else if (option == "printDES") //prints the contacts in descending order
		{
			myContactBST.printDES(rootptr);
		}
		else if (option == "printfv") //prints all the favourite contacts
		{
			myContactBST.printFav(rootptr);
		}
		else if (option == "help") //outputs the command list
		{
			listCommands();
		}
		else if (option == "exit") //breaks the loop
		{
			break;
		}
		else
		{
			cout << "Invalid Input! Please Enter A Valid Command!\n";
		}
		
		cout << endl;
		//cin.clear(); cin.ignore(1000, '\n');
	}

	return 0;
}




