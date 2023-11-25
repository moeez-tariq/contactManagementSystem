#include <iostream>
#include<sstream>
#include<fstream>
#include "contactbst.h"

using namespace std;

Node::Node(string key, MyVector<Contact>* contactVector)
{
	this->key = key;
	this->contactVector = contactVector;
	this->left = nullptr;
	this->right = nullptr;
}

Node::~Node()
{
	cout << this->key << " has been successfully deleted!" << endl;
}
ContactBST::ContactBST()
{
	this->root=nullptr;
}

ContactBST::~ContactBST()
{
	//Keep removing the root of the tree until it becomes empty
	while(root)
	{
		root=del(root,root->key);	
	}
}
Node* ContactBST::getRoot() //returns the pointer to the root
{
    return this->root; 
}

Node* ContactBST::add(Node* ptr,string key, Contact* data) //adds a contact
{
	if (root != nullptr) //making sure the tree isnt empty to avoid segmentation fault when searching
	{
		Node* found = search(ptr, key); //check to see if the key already exists
		// if (found != nullptr)
		// {
		// 	cout << found->getKey() << endl;
		// }
		if (found != nullptr)
		{
			found->contactVector->push_back(*data); //push back the contact into the vector
			return ptr;
		}
	}

	if (ptr == nullptr) //if the ptr is null then make a new vector and then push back the data in the new vector and make a new node
    {
    	MyVector<Contact>* dataVector = new MyVector<Contact>;
		dataVector->push_back(*data);
    	return new Node(key, dataVector); //base case
    }
    else if (key < ptr->key)
    {
    	ptr->left = add(ptr->left, key, data); //go left till base case reached
    	return ptr;
    }
    else if (key > ptr->key)
    {
    	ptr->right = add(ptr->right, key, data); //go right till base case reached
    	return ptr;
    }
}

void ContactBST::insert_helper(string key, Contact* data)
{	
	root = add(root,key, data);
}

void ContactBST::remove_helper(string key)
{
	root = del(root, key);
}

Node* ContactBST::search(Node* ptr,string key)
{
	if (ptr == nullptr) //if the tree is empty
	{
		return nullptr;
	}
	if (ptr->key == key) //base case
    {
    	return ptr;
    }
    
    if (key < ptr->key && ptr->left != nullptr) //recursive case to go left if key smaller than ptr->key
    {
    	return search(ptr->left, key);
    }
    else if (key > ptr->key && ptr->right != nullptr)
    {
    	return search(ptr->right, key); //recursive case to go right if key smaller than ptr->key
    }
    else
    {
    	return nullptr; //if key not found till pointer reaches nullptr
    }	
}


Node* ContactBST::update(Node* ptr, string key) //update contact details
{
	Node* found = search(ptr, key);
	if (found == nullptr) //if key not found
	{
		return nullptr;
	}
	else
	{
		int records_found = 0;
		records_found = found->getData()->size();
		cout << "Records Found: " << records_found << endl;
		for (int i = 0; i < records_found; i++)
		{
			cout << (i + 1) << ". ";
			found->contactVector->at(i).printLineContact(); //print all the contacts in a key
			cout << endl;
		}
		int option = 0;
		string option2 = "";
		while (true)
		{
			cout << "Please Select the Record you want to edit: "; //get user input
			cin >> option;
			if (option <= records_found && option > 0) //make sure the input is valid
			{
				break;
			} 
			else
			{
				cout << "Invalid Input. Please Try Again!\n";
				cout << endl;
			}
		}

		//found->contactVector->at(option - 1).printLineContact();
		found->contactVector->at(option - 1).updateContact(); //update the contact
		//found->contactVector->at(option - 1).printLineContact();
		cout << key << "(" << found->contactVector->at(option - 1).getEmail() << ") has been successfully updated!\n";
		string new_fname = found->contactVector->at(option - 1).getfname();
		string new_lname = found->contactVector->at(option - 1).getlname();
		string new_key = new_fname + " " + new_lname; //form the new key
		if (new_key != key) //check to see if the first or the last name has been changed
		{
			cout << "Contact Directory Has Been Updated!\n";
			string new_email = found->contactVector->at(option - 1).getEmail(); //get all the remaining information and store in new variables
			string new_primaryPhone = found->contactVector->at(option - 1).getPhone();
			string new_city = found->contactVector->at(option - 1).getCity();
			string new_country = found->contactVector->at(option - 1).getCountry();
			bool new_isFav = found->contactVector->at(option - 1).getisFav();
			//cout << new_fname << " " << new_lname << " " << new_email << endl;
			found->contactVector->erase(option - 1); //delete the current contact with changed name
			Contact* newContact = new Contact(new_fname, new_lname, new_email, new_primaryPhone, new_city, new_country, new_isFav); //create a new contact with new name and same rest of the information
			insert_helper(new_key, newContact); //insert it in the binary tree
		}
		return found;
	}
}

bool ContactBST::markFav(Node* ptr, string key) //marks a contact favourite
{
	Node* found = search(ptr, key); //same as mentioned before
	if (found == nullptr)
	{
		return false;
	}
	else
	{
		int records_found = 0;
		records_found = found->getData()->size();
		cout << "Records Found: " << records_found << endl;
		for (int i = 0; i < records_found; i++)
		{
			cout << (i + 1) << ". ";
			found->contactVector->at(i).printLineContact();
			cout << endl;
		}

		int option = 0;
		while (true)
		{
			cout << "Please Select the Record you want to mark as Favourite: ";
			cin >> option;
			if (option <= records_found)
			{
				break;
			} 
			else
			{
				cout << "Invalid Input. Please Try Again!\n";
				cout << endl;
			}
		}

		//found->contactVector->at(option - 1).printLineContact();
		found->contactVector->at(option - 1).setisFav(true); //sets the contact as favourite
		//found->contactVector->at(option - 1).printLineContact();
		cout << key << "(" << found->contactVector->at(option - 1).getEmail() << ") has been successfully marked favourite!\n";
		return true;
	}

}

bool ContactBST::unmarkFav(Node* ptr, string key) //same methodology as markfv to unmark the contact as favourite
{
	Node* found = search(ptr, key);
	if (found == nullptr)
	{
		return false;
	}
	else
	{
		int records_found = 0;
		records_found = found->getData()->size();
		cout << "Records Found: " << records_found << endl;
		for (int i = 0; i < records_found; i++)
		{
			cout << (i + 1) << ". ";
			found->contactVector->at(i).printLineContact();
			cout << endl;
		}

		int option = 0;
		while (true)
		{
			cout << "Please Select the Record you want to mark as Unfavourite: ";
			cin >> option;
			if (option <= records_found)
			{
				break;
			} 
			else
			{
				cout << "Invalid Input. Please Try Again!\n";
				cout << endl;
			}
		}

		//found->contactVector->at(option - 1).printLineContact();
		found->contactVector->at(option - 1).setisFav(false);
		//found->contactVector->at(option - 1).printLineContact();
		cout << key << "(" << found->contactVector->at(option - 1).getEmail() << ") has been successfully marked unfavourite!\n";
		return true;
	}
}

void ContactBST::printASC(Node* ptr) //prints in ascending order
{
	if (ptr == nullptr)
	{
		return;
	}
	else
	{
		printASC(ptr->left); //all left, then root
		for (int i = 0; i < ptr->getData()->size(); i++)
		{
			ptr->contactVector->at(i).printLineContact();
		}
		printASC(ptr->right); //then right
	}
}

void ContactBST::printDES(Node* ptr) //prints in descending order
{
	if (ptr == nullptr)
	{
		return;
	}
	else
	{
		printDES(ptr->right); //first right, then root
		for (int i = 0; i < ptr->getData()->size(); i++)
		{
			ptr->contactVector->at(i).printLineContact();
		}
		printDES(ptr->left); //then left
		
	}
}

void ContactBST::printFav(Node* ptr)
{
	if (ptr == nullptr)
	{
		return;
	}
	else
	{
		printFav(ptr->left); //all left, then root
		for (int i = 0; i < ptr->getData()->size(); i++)
		{
			if (ptr->contactVector->at(i).getisFav() == true) //only print if the contact is a favourite
			{
				ptr->contactVector->at(i).printLineContact();
			}
		}
		printFav(ptr->right); //then right
	}
}

Node* ContactBST::findMin(Node *ptr) //finds minimum
{
    if (ptr->left == nullptr) //base case in case left most leaf is reached
    {
    	return ptr;
    }
    else
    {
    	return findMin(ptr->left); //keep going left
    }
}

int ContactBST::height(Node *ptr) //gives height of the tree
{
    if (ptr == nullptr)
    {
    	return -1; //incase empty
    }
    else
    {
    	return 1 + max(height(ptr->right), height(ptr->left)); //max function returns larger of the two
    }
}

//  This two methods print a Binary Tree in 2D format
//  Created by Saurabh Ray 
//  Copyright © 2020 Saurabh Ray. All rights reserved.
//were only used for testing purposes
void ContactBST::printTree(){
   char *space = (char *) "  ";
   int d = height(this->getRoot());
   int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

   string *A = new string[n];
   bool *B = new bool[n];
   for(int i=0; i<n; ++i) 
   	  B[i]=false;

   printTreeHelper(A,B,root,n);

   cout<<"\nTree:"<<endl;
   for(int t=(n+1)/2; t>0; t=t/2){
        for(int j=0; j<n; j++){
            if( ((j+1)%t == 0) && B[j]){
                cout<<A[j];
                B[j] = false;
            }
            else{
                cout<<space;
            }
        }
        cout<<endl;
   }
   cout<<endl;
   delete [] A;
   delete [] B;
}

void ContactBST::printTreeHelper(string *A,bool *B, Node *ptr, int n){
    if(ptr!=nullptr){
        int mid = (n-1)/2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTreeHelper(A,B,ptr->left,mid);
        printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
    }
}

int ContactBST::importCSV(Node* ptr, string path) //imports contacts from a csv file
{
	int count = 0;
	ifstream fin(path); //opens file
	string line;
	if (!fin.is_open()) //checks to see if the path provided is correct
	{
		return -1;
	}
	while (getline(fin, line)) //gets one line at a time, keeps looping till the end of file
	{
		string f_name = "";
		string l_name = "";
		string email_add = "";
		string primary_Phone = "";
		string city_ = "";
		string country_ = "";
		bool is_Fav = false;
		int new_index = 0;
		int comma_count = 0;
		
		while (line.length() != 0)
		{
			for (int i = 0; i < line.length(); i++)
			{
				if (line[i] == ',') //if a comma is encountered means an individual value is present before it
				{
					comma_count++;
					new_index = i;
					break;
				}
			}

			if (comma_count == 1)
			{
				f_name = line.substr(0, new_index); //using the index of comma, get the right value
				string upperfname = "";
				for (int i = 0; i < f_name.length(); i++) //go over the input using its length
				{
					upperfname += toupper(f_name[i]); //lower each character and concatenate with previous ones
				}
				f_name = upperfname;
				line = line.substr(new_index + 2, line.length() - new_index - 1); //remove that specific part from the input and the comma and now only the others remain
			}
			else if (comma_count == 2)
			{
				l_name = line.substr(0, new_index);
				string upperlname = "";
				for (int i = 0; i < l_name.length(); i++) //go over the input using its length
				{
					upperlname += toupper(l_name[i]); //lower each character and concatenate with previous ones
				}
				l_name = upperlname;
				line = line.substr(new_index + 2, line.length() - new_index - 1);
			}
			else if (comma_count == 3)
			{
				email_add = line.substr(0, new_index);
				line = line.substr(new_index + 2, line.length() - new_index - 1);
			}
			else if (comma_count == 4)
			{
				primary_Phone = line.substr(0, new_index);
				line = line.substr(new_index + 2, line.length() - new_index - 1);
			}
			else if (comma_count == 5)
			{
				city_ = line.substr(0, new_index);
				line = line.substr(new_index + 2, line.length() - new_index - 1);
			}
			else if (comma_count == 6)
			{
				country_ = line.substr(0, new_index);
				line = line.substr(new_index + 1, line.length() - new_index - 1);
				string last = line.substr(0, line.length() + 1);
				//cout << last << endl;
				line = "";
				last = last[1];
				//cout << last << endl;
				if (last == "1")
				{
					is_Fav = true;
				}
				else
				{
					is_Fav = false;
				}
			}
		}
		string key = "";
		key = f_name + " " + l_name; //form another key
		Contact* newContact = new Contact(f_name, l_name, email_add, primary_Phone, city_, country_, is_Fav);
		insert_helper(key, newContact); //add the newly made contact in the tree
		cout << "Contact " << key << " has successfully been added!\n";
		count++; //count each time a contact is imported
	}
	cout << endl;
	fin.close(); //close file
	return count; //return the number of contacts imported
}

int ContactBST::exportCSV(Node* ptr, string path) //exports all contacts to a csv file
{
	fstream fout(path);
	if (!fout.is_open()) //check to see if the path is correct
	{
		return -1;
	}
	else
	{
		int count = 0;
		printLineCSV(ptr, fout, count);
		fout.close();
		return count;
	}
}

void ContactBST::printLineCSV(Node* ptr, fstream& fout, int& count)
{
	if (ptr == nullptr)
	{
		return;
	}
	else
	{
		printLineCSV(ptr->left, fout, count); //first left, then root
		for (int i = 0; i < ptr->getData()->size(); i++)
		{
			ptr->contactVector->at(i).printCSVContact(fout); //prints the contacts in ascending order using fout
			count++;
		}
		printLineCSV(ptr->right, fout, count); //then right
		
	}
}

Node* ContactBST::del(Node* ptr,string key) //deletes a contact
{
	if (ptr == nullptr)
	{
		return nullptr; //empty or after leaf
	}

	Node* found = search(ptr, key);
	if (found == nullptr)
	{
		cout << "Deletion Unsuccessful! The Name Doesnot Exist!\n";
		return nullptr;
	}
	else
	{
		if (ptr->key == key) //if a match is found
		{	
			if (found->getData()->size() >= 2) //check to see if the key has more than one contact
			{
				int records_found = 0;
				records_found = found->getData()->size();
				cout << "Records Found: " << records_found << endl;
				for (int i = 0; i < records_found; i++)
				{
					cout << (i + 1) << ". ";
					found->contactVector->at(i).printLineContact(); 
					cout << endl;
				}

				int option = 0;
				while (true)
				{
					cout << "Please Select the Record you want to delete: "; //if yes then ask the user which data they want to delete
					cin >> option;
					if (option <= records_found)
					{
						break;
					} 
					else
					{
						cout << "Invalid Input. Please Try Again!\n";
						cout << endl;
					}
				}
				string email_add = found->contactVector->at(option - 1).getEmail();
				found->contactVector->erase(option - 1); //delete that data
				cout << key << "(" << email_add << ") has been successfully deleted!\n";
				return found;
			}
			else //if there is only 1 contact in a key, then simply remove the node
			{
				if (ptr->right == nullptr) //if the ptr does not have a right subtree
				{
					Node* temp1 = ptr->left;
					delete ptr;
					return temp1; //return left ptr to replace the ptr with left
				}
				else if (ptr->left == nullptr) //if ptr does not have a left subtree
				{
					Node* temp2 = ptr->right;
					delete ptr;
					return temp2;
				}
				else if (ptr->right == nullptr && ptr->left == nullptr) //if its a leaf
				{
					return nullptr; //simply return nullptr to remove it
				}
				else //if it has both a right subtree and a left subtree
				{	
					ptr->key = (findMin(ptr->right))->key; //ptr->key is now the minimum of the right subtree
					ptr->right = del(ptr->right, ptr->key); //now go to the right of the pointer and then remove the minimum value (kind of like switching)
				}
			}
		}
		else if (ptr->key > key) //if the key is smaller than ptr->key
		{
			ptr->left = del(ptr->left, key); //keep removing from the left of the ptr
		}
		else if (ptr->key < key) //if the key is greater than ptr->key
		{
			
			ptr->right = del(ptr->right, key); //keep removing from the right
		}
		return ptr;
	}
}