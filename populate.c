#include "contact.h"
// Dummy contact data
static Contact dummyContacts[] = {
    {"John Doe", "1234567890", "john@example.com"},
    {"Alice Smith", "0987654321", "alice@example.com"},
    {"Bob Johnson", "1112223333", "bob@company.com"},
    {"Carol White", "4445556666", "carol@company.com"},
    {"David Brown", "7778889999", "david@example.com"},
    {"Eve Davis", "6665554444", "eve@example.com"},
    {"Frank Miller", "3334445555", "frank@example.com"},
    {"Grace Wilson", "2223334444", "grace@example.com"},
    {"Hannah Clark", "5556667777", "hannah@example.com"},
    {"Ian Lewis", "8889990000", "ian@example.com"}
};

void populateAddressBook(AddressBook* addressBook)
{
    int numDummyContacts = sizeof(dummyContacts) / sizeof(dummyContacts[0]);//Calculate the number of dummy contacts in the array using sizeof
    for (int i = 0; i < numDummyContacts && addressBook->contactCount < MAX_CONTACTS; ++i)//Iterate through the dummy contacts array
     {
        addressBook->contacts[addressBook->contactCount++] = dummyContacts[i];//Increment the contact count to track the number of contacts added
    }
}
