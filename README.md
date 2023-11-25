# Contact Management System

A simple Contact Management System implemented in C++ using a Binary Search Tree (BST). This system allows users to manage their contacts efficiently through a variety of commands.

## Features

- **Import/Export Contacts**: Import contacts from a CSV file or export contacts to a CSV file.

- **Add New Contact**: Add a new contact with details such as first name, last name, email, phone number, city, and country. Optionally, mark the contact as a favorite.

- **Edit Contact**: Update the details of a contact by providing its key (combination of first name and last name).

- **Delete Contact**: Remove a contact from the system by specifying its key.

- **Search Contacts**: Search for contacts based on a key (combination of first name and last name).

- **Mark/Unmark Favorite**: Mark or unmark a contact as a favorite.

- **Print Contacts**: Print contacts in ascending or descending order. Also, print all favorite contacts.

- **Command List**: Display the available commands to guide the user.

## Getting Started

1. **Compilation**: Compile the program using the provided makefile.

    ```bash
    make
    ```

2. **Run the Program**:

    ```bash
    ./output
    ```

3. **Available Commands**:

    - `import <path>`: Import contacts from a CSV file.
    - `export <path>`: Export contacts to a CSV file.
    - `add`: Add a new contact.
    - `edit <key>`: Update a contact's details.
    - `del <key>`: Delete a contact.
    - `searchFor <key>`: Search for a contact.
    - `markfv <key>`: Mark as favorite.
    - `umarkfv <key>`: Unmark as favorite.
    - `printASC`: Print contacts in ascending order.
    - `printDES`: Print contacts in descending order.
    - `printfv`: Print all favorite contacts.
    - `help`: Display the available commands.
    - `exit`: Exit the program.

## Example Usage

```bash
./output

## Academic Use Notice

Kindly be aware that this project was created as part of an educational assignment within a course offered by NYU Abu Dhabi's Computer Science department. It is intended for educational and learning purposes. Using this code for academic submissions or assignments is strictly prohibited. I encourage students to use this repository as a learning resource and to write their own code for assignments to uphold academic integrity.