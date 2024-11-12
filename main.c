/*
   Author: Vaishnavi Ajay Aher
   Date: 25/09/2024
   Description: This program allows users to manage contacts by providing functionality to add, delete, edit, and list contacts. The data is saved and retrieved from a CSV file.
*/
#include <stdio.h>
#include "contact.h"//Include the custom header file that defines the AddressBook and related contact management functions

int main() {
    int choice;//Variable to store the user's menu choice
    AddressBook addressBook;//Declare an AddressBook structure to store the contacts
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\nAddress Book Menu:\n");
        printf("1. Create contact\n");//Option to create a new contact
        printf("2. Search contact\n");// Option to search for an existing contact
        printf("3. Edit contact\n");// Option to edit an existing contact
        printf("4. Delete contact\n");// Option to delete a contact
        printf("5. List all contacts\n");// Option to list all contacts in the address book
        printf("6. Save and exit\n");// Option to save contacts to a file and exit the program
        //printf("7. Exiting\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        
        switch (choice) // Use a switch statement to handle the user's menu choice
		{
            case 1: // If the user selects "1", call the function to create a new contact
                createContact(&addressBook);
                break;
            case 2: // If the user selects "2", call the function to search for a contact
                searchContact(&addressBook);
                break;
            case 3:// If the user selects "3", call the function to edit an existing contact
                editContact(&addressBook);
                break;
            case 4:// If the user selects "4", call the function to delete a contact
                deleteContact(&addressBook);
                break;
            case 5:// If the user selects "5", call the function to list all contacts
                listContacts(&addressBook);
                break;
            case 6:// If the user selects "6", save the contacts to a file and exit the program
                saveContactsToFile(&addressBook); // Call the function to save contacts to a file
                printf("Saving and existing.. \n");// Print a message indicating that the program is saving and exiting
                break;
            default:// If the user enters an invalid choice, print an error message
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);// Continue displaying the menu until the user selects the "Save and exit" option
    
       return 0;// Return 0 to indicate successful completion of the program
}
