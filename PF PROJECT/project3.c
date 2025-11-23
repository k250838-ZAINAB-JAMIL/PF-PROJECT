#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <ctype.h>

// Global variable
char ans = 0;

// Function Declarations
void Welcomescreen(void);
void Title(void);
void Mainmenu(void);
void Loginscreen(void);
void Add_rec(void);
void func_list(void);
void Search_rec(void);
void Edit_rec(void);
void Del_rec(void);
void ex_it(void);
void gotoxy(short x, short y);

struct pet
{
    int age;
    char Gender;
    int bodyweight;
    char name[100];
    char Doctor[100];
    char Problem[100];
    char breed[100];
    char phoneNumber[20];
    char ownername[100];
};

struct pet p;

// gotoxy Function
void gotoxy(short x, short y)
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// MAIN FUNCTION
int main(void)
{
    Welcomescreen();
    Title();
    Loginscreen();
    return 0;
}

// Welcome Screen
void Welcomescreen(void)
{
    printf("\n------------------------------------------------\n");
    printf("\nWELCOME TO PET CARE MANAGEMENT SYSTEM\n");
    printf("\n------------------------------------------------\n");
    printf("Press any key to continue...");
    getch();
    system("cls");
}

// Title Screen
void Title(void)
{
    printf("\t\t\t-------Pet Care--------\n");
}

// Login Screen
void Loginscreen(void)
{
    int e = 0;
    char Username[25], Password[25];
    char original_UserName[25] = "MaryamZainab";
    char original_Password[25] = "1234";

    do
    {
        system("cls");
        Title();
        printf("\n\n\n\t\t----Login Screen------\n");
        printf("\n\tEnter your Username: ");
        scanf("%s", Username);
        printf("\n\tEnter your Password: ");
        scanf("%s", Password);

        if (strcmp(Username, original_UserName) == 0 && strcmp(Password, original_Password) == 0)
        {
            printf("\n\n\t...Login Successful...");
            getch();
            Mainmenu();
            return;
        }
        else
        {
            printf("\nLogin Failed! Try again.\n");
            e++;
            getch();
        }

    } while (e < 3);

    printf("\nYou entered login info incorrectly 3 times.\nYou can't login again!");
    getch();
    ex_it();
}

// Main Menu
void Mainmenu(void)
{
    int opt = 0;
    do
    {
        system("cls");
        Title();
        printf("\n1. Add pet record");
        printf("\n2. List all pet records");
        printf("\n3. Search pet record");
        printf("\n4. Edit pet record");
        printf("\n5. Delete pet record");
        printf("\n6. Exit");
        printf("\nChoose your option (1-6): ");
        scanf("%d", &opt);

        switch (opt)
        {
        case 1:
            Add_rec();
            break;
        case 2:
            func_list();
            break;
        case 3:
            Search_rec();
            break;
        case 4:
            Edit_rec();
            break;
        case 5:
            Del_rec();
            break;
        case 6:
            ex_it();
            break;
        default:
            printf("\nInvalid option! Press any key to try again.");
            getch();
        }

    } while (opt != 6);
}

// Add Record
void Add_rec(void)
{
    FILE *ek = fopen("Patients.txt", "a");
    if (!ek)
    {
        printf("Cannot open file!\n");
        getch();
        return;
    }

    system("cls");
    Title();

    printf("\nEnter pet's name: ");
    scanf("%s", p.name);
    p.name[0] = toupper(p.name[0]);

    printf("Enter age: ");
    scanf("%d", &p.age);

    do
    {
        printf("Enter gender (M/F): ");
        scanf(" %c", &p.Gender);
        p.Gender = toupper(p.Gender);
    } while (p.Gender != 'M' && p.Gender != 'F');

    printf("Enter breed: ");
    fflush(stdin);
    fgets(p.breed, sizeof(p.breed), stdin);
    p.breed[strcspn(p.breed, "\n")] = 0;

    printf("Enter bodyweight (kg): ");
    scanf("%d", &p.bodyweight);

    printf("Enter owner's name: ");
    fflush(stdin);
    fgets(p.ownername, sizeof(p.ownername), stdin);
    p.ownername[strcspn(p.ownername, "\n")] = 0;

    printf("Enter owner's phone number: ");
    scanf("%s", p.phoneNumber);

    printf("Enter problem faced: ");
     fflush(stdin);
   fgets(p.Problem, sizeof(p.Problem), stdin);
    p.Problem[strcspn(p.Problem, "\n")] = 0; 
    p.Problem[0] = toupper(p.Problem[0]);

    printf("Enter doctor's name: ");
    scanf("%s", p.Doctor);

    fprintf(ek, "%s %d %c %s %d %s %s %s %s\n", p.name, p.age, p.Gender, p.breed, p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor);

    fclose(ek);
    printf("\nRecord added successfully!\nPress any key to continue...");
    getch();
}

// List Records
void func_list(void)
{
    FILE *ek = fopen("Patients.txt", "r");
    if (!ek)
    {
        printf("Cannot open file!\n");
        getch();
        return;
    }
    system("cls");
    Title();
    printf("\n\nName\tAge\tGender\tBreed\tWeight\tOwner\tPhone\tProblem\tDoctor\n");
    printf("--------------------------------------------------------------------------\n");

    while (fscanf(ek, "%s %d %c %s %d %s %s %s %s", p.name, &p.age, &p.Gender, p.breed, &p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor) != EOF)
    {
        printf("%s\t%d\t%c\t%s\t%d\t%s\t%s\t%s\t%s\n", p.name, p.age, p.Gender, p.breed, p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor);
    }

    fclose(ek);
    printf("\nPress any key to continue...");
    getch();
}

// Search Record
void Search_rec(void)
{
    char name[100];
    int found = 0;
    FILE *ek = fopen("Patients.txt", "r");
    if (!ek)
    {
        printf("Cannot open file!\n");
        getch();
        return;
    }

    system("cls");
    Title();
    printf("\nEnter pet's name to search: ");
    scanf("%s", name);
    name[0] = toupper(name[0]);

    while (fscanf(ek, "%s %d %c %s %d %s %s %s %s", p.name, &p.age, &p.Gender, p.breed, &p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor) != EOF)
    {
        if (strcmp(p.name, name) == 0)
        {
            printf("\nRecord Found!\n");
            printf("%s\t%d\t%c\t%s\t%d\t%s\t%s\t%s\t%s\n", p.name, p.age, p.Gender, p.breed, p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nRecord not found!\n");

    fclose(ek);
    printf("\nDo you want to search more? (Y/N): ");
    scanf(" %c", &ans);
    if (toupper(ans) == 'Y')
        Search_rec();
    else
        Mainmenu();
}

// Edit Record
void Edit_rec(void)
{
    char name[100];
    int found = 0;
    FILE *ek = fopen("Patients.txt", "r");
    FILE *ft = fopen("Temp.txt", "w");
    if (!ek || !ft)
    {
        printf("Cannot open file!\n");
        getch();
        return;
    }

    system("cls");
    Title();
    printf("\nEnter pet's name to edit: ");
    scanf("%s", name);
    name[0] = toupper(name[0]);

    while (fscanf(ek, "%s %d %c %s %d %s %s %s %s", p.name, &p.age, &p.Gender, p.breed, &p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor) != EOF)
    {
        if (strcmp(p.name, name) == 0)
        {
            found = 1;
            printf("\nEditing record for %s\n", p.name);
            printf("Enter new name: ");
            scanf("%s", p.name);
            printf("Enter new age: ");
            scanf("%d", &p.age);
            printf("Enter new gender (M/F): ");
            scanf(" %c", &p.Gender);
            printf("Enter new breed: ");
            scanf("%s", p.breed);
            printf("Enter new bodyweight: ");
            scanf("%d", &p.bodyweight);
            printf("Enter new owner's name: ");
            scanf("%s", p.ownername);
            printf("Enter new phone: ");
            scanf("%s", p.phoneNumber);
            printf("Enter new problem: ");
            scanf("%s", p.Problem);
            printf("Enter new doctor: ");
            scanf("%s", p.Doctor);
        }
        fprintf(ft, "%s %d %c %s %d %s %s %s %s\n", p.name, p.age, p.Gender, p.breed, p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor);
    }

    fclose(ek);
    fclose(ft);

    remove("Patients.txt");
    rename("Temp.txt", "Patients.txt");

    if (!found)
        printf("\nRecord not found!\n");
    else
        printf("\nRecord updated successfully!\n");

    getch();
}

// Delete Record
void Del_rec(void)
{
    char name[100];
    int found = 0;
    FILE *ek = fopen("Patients.txt", "r");
    FILE *ft = fopen("Temp.txt", "w");
    if (!ek || !ft)
    {
        printf("Cannot open file!\n");
        getch();
        return;
    }

    system("cls");
    Title();
    printf("\nEnter pet's name to delete: ");
    scanf("%s", name);
    name[0] = toupper(name[0]);

    while (fscanf(ek, "%s %d %c %s %d %s %s %s %s", p.name, &p.age, &p.Gender, p.breed, &p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor) != EOF)
    {
        if (strcmp(p.name, name) != 0)
        {
            fprintf(ft, "%s %d %c %s %d %s %s %s %s\n", p.name, p.age, p.Gender, p.breed, p.bodyweight, p.ownername, p.phoneNumber, p.Problem, p.Doctor);
        }
        else
        {
            found = 1;
        }
    }

    fclose(ek);
    fclose(ft);

    remove("Patients.txt");
    rename("Temp.txt", "Patients.txt");

    if (!found)
        printf("\nRecord not found!\n");
    else
        printf("\nRecord deleted successfully!\n");

    getch();
}

// Exit Function
void ex_it(void)
{
    system("cls");
    Title();
    printf("\n\nThank you for visiting!\n");
    getch();
    exit(0);
}
