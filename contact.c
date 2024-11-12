#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
#include <ctype.h>

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0; // Initializes the number of contacts in the address book to zero.
    //populateAddressBook(addressBook);

    FILE *fp; //Declares a file pointer to read the contact data from a file.
    fp=fopen("contacts.csv","r"); //Checks if the file was opened successfully.
    if(!fp)
    {
        perror("Unable to open file");
        return; //Exits the function if the file cannot be opened.
    }
    //int i = 0;

    
    while(fscanf(fp," %49[^,], %14[^,], %49[^\n] ",
                      addressBook->contacts[addressBook->contactCount].name,
                      addressBook->contacts[addressBook->contactCount].phone,
                      addressBook->contacts[addressBook->contactCount].email)==3)
    {
        addressBook->contactCount++; //Increments the contact count after successfully reading a contact.
    }                  
    fclose(fp); //Closes the file after reading all the contacts.
}


int name_validate(char *name)
{
    //Fetch one by one character till null character
    int i = 0;
    while(name[i] != '\0') //Iterates through each character of the name string until the null terminator is reached.
    {
        if(!(isalpha(name[i]) || name[i] == ' ')) // Checks if the current character is either a letter or a space. If not, it's invalid.
        {
            return 1; //Returns 1 if the name contains invalid characters (non-alphabet).
            //check the character is alphabet or not
            //yes->move to next character, No-> stop the process.
        }
        i++; //Moves to the next character in the name string.
    }
    return 0; //Returns 0 if the name is valid 
}

int number_validate(char *number)
{
    int i = 0;//Initializes an index variable to traverse through the phone number string.
    while(number[i] != '\0') // Loops through each character of the phone number string.
    {
        if(!(isdigit(number[i])) || strlen(number) != 10) //Checks if the character is a digit and if the phone number length is 10. If not, it's invalid.
        {
            return 1;//Returns 1 if the phone number is invalid.
        }
        i++;//Moves to the next character in the phone number string.
    }
    return 0;//Returns 0 if the phone number is valid.
}

int Email_validate(char *mail_id)
{
    if(!(strstr(mail_id , "@gmail.com")))//Checks if the email contains the string "@gmail.com". If not, it's invalid.
    {
         return 1;//Returns 1 if the email is invalid.
    
    }
    return 0;//Returns 0 if the email is valid (contains "@gmail.com").
}

int is_phone_duplicate(AddressBook *addressBook, char *phone)
{
    for(int i = 0; i<addressBook->contactCount; i++)//Loops through all the existing contacts in the address book.
    {
        if(strcmp(addressBook->contacts[i].phone,phone) == 0)//Compares the current contact's phone number with the input phone number.
        {
            return 1; //phone number is duplicate
        }
    }
    return 0; //Phone number is unique
}

int is_email_duplicate(AddressBook *addressBook, char *email)
{
    for(int i = 0; i<addressBook->contactCount; i++)//Loops through all the existing contacts in the address book.
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)//Compares the current contact's email with the input email.
        {
            return 1; //Email is duplicate
        }
    }
    return 0; //Email is unique
}


void createContact(AddressBook *addressBook)
{
    
    char name[20];//Declares a string to store the name.
    //step 1: Read a name from user
    printf("Enter the name: ");//Prompts the user to enter the name.
    //__fpurge(STDIN);
    scanf(" %[^\n]",name);//Reads the name, allowing spaces in the input.

    // step 2: Validate the name -> alphabts
    while(name_validate(name) == 1)//Validates the name by calling name_validate(). If invalid, prompts the user again.
    {
        printf("INFO: Name validation not done, please enter valid name...\n");//Prints an error message if the name is invalid.
        printf("Enter the name: ");
        scanf(" %[^\n]",name); //if we dont give space then it will be a buffer.
        //True-> Goto Step3, False -> print erro, Goto Step1
    }

    char phone[50];//Declares a string to store the phone number.
    //step 3: Read a number from user
    printf("Enter the number: ");
    scanf(" %[^\n]", phone);
    
    //Step 4: Validate the phone -> number
    while(number_validate(phone) == 1 || is_phone_duplicate(addressBook,phone) == 1)//Validates the phone number and checks if it is a duplicate.
    {
        if(number_validate(phone) == 1)
        {
            printf("INFO: phone number validation not done, please enter valid number...\n");//Prints an error message if the phone number is invalid.
        }
        else
        {
            printf("INFO: phone number already exists. please enter a unqiue number...\n");
        }
        printf("Enter the number: ");
        scanf(" %[^\n]",phone);
    }
   

    char email[20];//Declares a string to store the email.
    printf("Enter mail_id : ");
    scanf(" %[^\n]",email);
    while(Email_validate(email) == 1 || is_email_duplicate(addressBook,email) == 1)//Validates the email and checks if it is a duplicate.
    {
        if(Email_validate(email) == 1)
        {
            printf("INFO: Email validation not done, please enter a valid Gmail address...\n");//Prints an error message if the email is invalid.
        }
        else
        {
            printf("INFO: Email already exists. please enter a unique email...\n");
        }
        printf("Enter mail_id: ");
        scanf(" %[^\n]",email);
    }
   
	
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);//Copies the valid name into the contacts array.
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);//Copies the valid phone number into the contacts array.
    strcpy(addressBook->contacts[addressBook->contactCount].email,email);//Copies the valid email into the contacts array.
    printf("Contact add successfully.");//Prints a message indicating that the contact was added successfully.
    addressBook->contactCount++;//Increments the contact count after adding the new contact.
}

int search_name(AddressBook *addressBook,char *name)
{
    for(int i = 0; i<addressBook->contactCount; i++)//Loop through all contacts in the address book
    {
        if(strncasecmp(addressBook->contacts[i].name,name,2)==0)//Compare the first two characters of each contact's name with the input name
        {
            return i;//If found, return the index of the matching contact
        }
    }
    return 1;// If no match is found
}

int search_phone(AddressBook *addressBook,char *phone)
{
    for(int i = 0; i<addressBook->contactCount; i++)//Loop through all contacts in the address book
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0)//Compare the phone number of each contact with the input phone number
        {
            return i;//If found, return the index of the matching contact
        }
    }
    return 1;//If no match is found
}

int search_email(AddressBook *addressBook,char *email)
{
    for(int i = 0; i<addressBook->contactCount; i++)//Loop through all contacts in the address book
    {
        if(strcmp(addressBook->contacts[i].email,email)==0)// Compare the email of each contact with the input email
        {
            return i;//If found, return the index of the matching contact
        }
    }
    return 1;//If no match is found
}

void searchContact(AddressBook *addressBook) 
{
    int choice;
    int j; //variable to store search result index
    //Step 1: Print the menu based on what searching
    do{
        //Display search options
       printf("\nSerach by:\n");
       printf("1. Name\n");
       printf("2. phone number\n");
       printf("3. Email\n");
       printf("4. Exit\n");

       printf("Enter your choice: ");

       //Get the user choice
       scanf("%d",&choice); 

       switch(choice)//Execute based on user's choice
       {
           case 1:
           char name[20];
           printf("Enter the name: ");
           scanf(" %[^\n]",name); //Read name input

           j = search_name(addressBook,name);//Search contact by name
           if(j == -1)
           {
             printf("contact not found");
           }
           else
           {
            //If found, display contact details
             printf("Name : %s\n",addressBook->contacts[j].name);
             printf("Mobile : %s\n",addressBook->contacts[j].phone);
             printf("Email : %s\n",addressBook->contacts[j].email);
           }
           break;

           case 2:
           char phone[11];
           printf("Enter the phone number : ");
           scanf(" %[^\n]",phone);// Read phone number input

           //Search contact by phone number
           j = search_phone(addressBook,phone);
           if(j == -1)
           {
             printf("contact not found");
           }
           else
           {
            //If found, display contact details
             printf("Name : %s\n",addressBook->contacts[j].name);
             printf("Mobile : %s\n",addressBook->contacts[j].phone);
             printf("Email : %s\n",addressBook->contacts[j].email);
           }
           break;

           case 3:
           char email[20];
           printf("Enter the Email: ");
           scanf(" %[^\n]",email);//Read email input

           //Search contact by email
           j = search_email(addressBook,email);
           if(j == -1)
           {
             printf("contact not found");
           }
           else
           {
            //If found, display contact details
             printf("Name : %s\n",addressBook->contacts[j].name);
             printf("Mobile : %s\n",addressBook->contacts[j].phone);
             printf("Email : %s\n",addressBook->contacts[j].email);
           }
           break;

           case 4:
           printf("exit...\n");
           break;

           default:
            printf("Invalid choice, please try again: ");
       }
    }
    while(choice != 4);//Loop until the user selects exit
} 

void editContact(AddressBook *addressBook)
{
   
    char name[20];
    printf("Enter the name of the contact to edit: ");
    scanf(" %[^\n]", name);//Read name input for editing

    // Array to store indices of matching contacts
    int matchedIndices[100];
    int matchCount = 0;

    // Search for contacts matching the first two characters
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strncasecmp(addressBook->contacts[i].name, name, 2) == 0)
        {
            matchedIndices[matchCount] = i;  // Store matching contact index
            matchCount++;
        }
    }

    // If no contacts match
    if (matchCount == 0) 
    {
        printf("Contact not found!\n");
        return;
    }

    // Handle multiple matches
    int index = -1; // Initialize the index
    if (matchCount > 1) //If multiple matches are found, prompt user to choose a specific contact
    {
        printf("Multiple contacts found:\n");
        for (int i = 0; i < matchCount; i++) 
        {
            printf("%d. %s\n", i + 1, addressBook->contacts[matchedIndices[i]].name);
        }
        int selectedIndex;
        printf("Select a contact number to edit: ");
        scanf("%d", &selectedIndex);

        if (selectedIndex < 1 || selectedIndex > matchCount) 
        {
            printf("Invalid selection.\n");
            return;
        }
        index = matchedIndices[selectedIndex - 1];  // Get the selected contact index
    } 
    else 
    {
        index = matchedIndices[0];  // Only one match found
    }

    // Display current contact details
    printf("\nContact details:\n");
    printf("Name: %s\n", addressBook->contacts[index].name);
    printf("Phone: %s\n", addressBook->contacts[index].phone);
    printf("Email: %s\n", addressBook->contacts[index].email);

    // Ask the user what they want to edit
    int choice;
    do
    {
        //Present editing options
        printf("\nWhat would you like to edit?\n");
        printf("1. Name\n");
        printf("2. Phone\n");
        printf("3. Email\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        //Edit the selected field
        switch (choice)
        {
            case 1:
            {
                char newName[20];
                printf("Enter the new name: ");
                scanf(" %[^\n]", newName);//Get new name input

                // Validate the new name
                while (name_validate(newName) == 1) 
                {
                    printf("INFO: Name validation failed, please enter a valid name...\n");
                    printf("Enter the new name: ");
                    scanf(" %[^\n]", newName);
                }

                // Update the contact's name
                strcpy(addressBook->contacts[index].name, newName);
                printf("Name updated successfully.\n");
                break;
            }

            case 2:
            {
                char newPhone[11];
                printf("Enter the new phone number: ");
                scanf(" %[^\n]", newPhone);//Get new phone number input

                // Validate the new phone number
                while (number_validate(newPhone) == 1) 
                {
                    printf("INFO: Phone number validation failed, please enter a valid number...\n");
                    printf("Enter the new phone number: ");
                    scanf(" %[^\n]", newPhone);
                }

                // Update phone number
                strcpy(addressBook->contacts[index].phone, newPhone);
                printf("Phone number updated successfully.\n");
                break;
            }

            case 3:
            {
                char newEmail[30];
                printf("Enter the new email: ");
                scanf(" %[^\n]", newEmail);//Get new email input

                // Validate the new email
                while (Email_validate(newEmail) == 1) 
                {
                    printf("INFO: Email validation failed, please enter a valid email...\n");
                    printf("Enter the new email: ");
                    scanf(" %[^\n]", newEmail);
                }

                // Update email
                strcpy(addressBook->contacts[index].email, newEmail);
                printf("Email updated successfully.\n");
                break;
            }

            case 4:
                printf("Exiting edit menu...\n");
                break;

            default:
                printf("Invalid choice, please try again.\n");
        }
    }
    while (choice != 4); //Loop until the user selects exit

    // Save the updated contacts to the file
    saveContactsToFile(addressBook);
    printf("Contact updated and saved successfully.\n");

}


void deleteContact(AddressBook *addressBook)
{

    char name[20];
    printf("Enter the first two characters of the contact's name to delete: ");//Prompts the user to enter the first two characters of the contact name they wish to delete.
    scanf(" %[^\n]", name);

    // Array to store indices of matching contacts
    int matchedIndices[100];//Declares an array matchedIndices to store the indices of the matching contacts.
    int matchCount = 0;//Initializes matchCount to track how many contacts match the given name.

    // Search for contacts matching the first two characters
    for (int i = 0; i < addressBook->contactCount; i++)// Iterates through each contact in the address book.
    {
        if (strncasecmp(addressBook->contacts[i].name, name, 2) == 0)//Compares the first two characters of the contact's name with the input name, ignoring case. If they match, the code proceeds.
        {
            matchedIndices[matchCount] = i;//Stores the index of the matching contact in the matchedIndices array.
            matchCount++;//Increments the matchCount when a match is found.
        }
    }

    if (matchCount == 0)//Checks if no contacts were found with the matching name. If matchCount is still 0, it means no match was found.
    {
        printf("Contact not found!\n");//Prints an error message if no matching contact was found.
        return;//Exits the function since no contact matched the search criteria.
    }

    // If multiple matches, prompt user to select a contact to delete
    int index; //Declares a variable index to store the index of the contact to delete.
    if (matchCount > 1)//Checks if more than one contact matched the search.
    {
        printf("Multiple contacts found:\n");//If multiple contacts were found, it prints out a list of them.
        for (int i = 0; i < matchCount; i++)//Iterates through the matchedIndices array to list each matched contact.
        {
            printf("%d. %s\n", i + 1, addressBook->contacts[matchedIndices[i]].name);//Displays the matched contact's name along with an index number.
        }
        int choice;
        printf("Select a contact number to delete: ");//Prompts the user to select which contact they wish to delete.
        scanf("%d", &choice);
        index = matchedIndices[choice - 1];//Converts the user's choice to the actual index of the selected contact.
    }
    else//If there was only one match, the else block runs.
    {
        index = matchedIndices[0];//Automatically selects the first matched contact for deletion.
    }

    // Shift the remaining contacts to "delete" the selected contact
    for (int i = index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1];//Copies the next contact's details to the current position to fill the gap.
    }

    // Reduce contact count
    addressBook->contactCount--;

    // Save updated contacts to file
    saveContactsToFile(addressBook);
    printf("Contact deleted successfully.\n");
}

void listContacts(AddressBook *addressBook) 
{
    // Check if there are any contacts to display
    //initialize(addressBook);
    if (addressBook->contactCount == 0) //Checks if there are any contacts to display. If there are no contacts, it prints a message and exits.
    {
        printf("No contacts available.\n");//Prints a message if there are no contacts.
        return;
    }

    // Temporary structure for sorting
    Contact temp;

    // Bubble sort to sort contacts alphabetically by name
    for (int i = 0; i < addressBook->contactCount; i++)//Outer loop for the bubble sort algorithm.
     {
        for (int j = i+1; j < addressBook->contactCount;j++)//Inner loop to compare contacts.
         {
            // Compare names, use strcasecmp for case-insensitive sorting
            if (strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name) > 0) 
            {
                // Swap the contacts
                temp = addressBook->contacts[i];//Swaps the two contacts if they are out of order.
                addressBook->contacts[i] = addressBook->contacts[j];//Assigns contact j to position i.
                addressBook->contacts[j] = temp;//Assigns the contact from i to j.
            }
        }
    }

    // Display the sorted contacts
    printf("List of Contacts\n");//Prints a header for the list of contacts.
    printf("                                              \n");
    printf("Sr.no\tName\t\t\tPhone\t\t\t\tEmail\n");//Prints the column headers for the contact list.
    for (int i=0;i<addressBook->contactCount;i++) //Iterates through the contacts to display them.
    {
        printf("%d.\t",i+1);//Prints the serial number of the contact.
        printf("%s\t\t",addressBook->contacts[i].name);//Prints the name of the contact.
        printf("%s\t\t",addressBook->contacts[i].phone);//Prints the phone number of the contact.
        printf("%s",addressBook->contacts[i].email);//Prints the email address of the contact.
        printf("\n");//Moves to the next line for the next contact.
    }
}

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fp;//Declares a file pointer fp.
    fp=fopen("contacts.csv", "w+");//Opens the file contacts.csv in write mode, creating it if it doesn't exist.
    
    if (fp == NULL) //Checks if the file could not be opened.
    {
        perror("Could not open file for writing.\n");//Prints an error message if the file could not be opened.
        return;//Exits the function if the file could not be opened.
    }
    
    for (int i = 0; i < addressBook->contactCount; i++)//Writes each contact's name, phone number, and email to the file in CSV format.
   {
        fprintf(fp,"%s,%s,%s\n",
                                addressBook->contacts[i].name, 
                                addressBook->contacts[i].phone, 
                                addressBook->contacts[i].email);
    }
    
    fclose(fp);//Closes the file after saving all contacts.
}
