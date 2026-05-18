/* 
Write a program that stores array of structures in ascii format in a file.
Write a function to create an array of seek positions of the beginning of the each record(structure) in the file
Write a function to display the record given the position.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Structure Definition
struct Student
{
    int id;
    char name[50];
    float marks;
};

// Function to write array of structures into ASCII file
void writeToFile(struct Student s[], int n, char filename[])
{
    FILE *fp;

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d %s %f\n",
                s[i].id,
                s[i].name,
                s[i].marks);
    }

    fclose(fp);
}

// Function to create array of seek positions
void createSeekPositions(long positions[], int *count, char filename[])
{
    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    int i = 0;

    while (1)
    {
        // Store beginning position of current record
        positions[i] = ftell(fp);

        struct Student temp;

        // Try reading one record
        int result = fscanf(fp,
                            "%d %s %f",
                            &temp.id,
                            temp.name,
                            &temp.marks);

        // Stop if record not read properly
        if (result != 3)
        {
            break;
        }

        i++;
    }

    *count = i;

    fclose(fp);
}

// Function to display record using seek position
void displayRecord(long position, char filename[])
{
    FILE *fp;

    fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Move file pointer to required position
    fseek(fp, position, SEEK_SET);

    struct Student s;

    if (fscanf(fp,
               "%d %s %f",
               &s.id,
               s.name,
               &s.marks) == 3)
    {
        printf("\nRecord Found:\n");
        printf("ID    : %d\n", s.id);
        printf("Name  : %s\n", s.name);
        printf("Marks : %.2f\n", s.marks);
    }
    else
    {
        printf("Invalid position!\n");
    }

    fclose(fp);
}

int main()
{
    struct Student students[MAX];

    int n;

    printf("Enter number of students: ");
    scanf("%d", &n);

    // Input student details
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter details of student %d\n", i + 1);

        printf("Enter ID: ");
        scanf("%d", &students[i].id);

        printf("Enter Name: ");
        scanf("%s", students[i].name);

        printf("Enter Marks: ");
        scanf("%f", &students[i].marks);
    }

    char filename[] = "students.txt";

    // Store records into file
    writeToFile(students, n, filename);

    printf("\nRecords stored successfully in file.\n");

    // Array to store seek positions
    long positions[MAX];

    int count;

    // Create seek position array
    createSeekPositions(positions, &count, filename);

    printf("\nSeek Positions:\n");

    for (int i = 0; i < count; i++)
    {
        printf("Record %d starts at byte position %ld\n",
               i + 1,
               positions[i]);
    }

    int choice;

    printf("\nEnter record number to display: ");
    scanf("%d", &choice);

    if (choice >= 1 && choice <= count)
    {
        displayRecord(positions[choice - 1], filename);
    }
    else
    {
        printf("Invalid record number!\n");
    }

    return 0;
}
