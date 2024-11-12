#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
// creating contact structure
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;
//creating Adressbook structure along with using contact structure inside its a nested structure
typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;//count to keep track of number of contacts entered.
} AddressBook;

//Function prototypes
//Function declaration to create contact
void createContact(AddressBook *addressBook);

// Function declaration to create contact
void searchContact(AddressBook *addressBook);

//Function declaration to search contact
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *addressBook);
//void saveContactsToFile(AddressBook *AddressBook);

#endif
