#include <stdio.h>
#include <stdlib.h>

struct student
{
    int id;
    char name[40];
    float marks;
};

void writeRecords(struct student *s);
void getRecord(int m);
void deleteRecord(int deleteId);

int main()
{
    struct student s[3] = {
        {1, "abc_1", 40.6},
        {2, "abc_2", 50.8},
        {3, "abc_3", 60.9}
    };

    writeRecords(s);

    printf("\nThe 2nd Record :- \n");
    getRecord(2);

    printf("\nDeleting Record with ID = 2\n");
    deleteRecord(2);

    printf("\nRecords After Deletion:\n");

    FILE *fp;
    struct student temp;

    fp = fopen("student.bin", "rb");

    while (fread(&temp, sizeof(struct student), 1, fp))
    {
        printf("ID : %d\n", temp.id);
        printf("Name : %s\n", temp.name);
        printf("Marks : %.2f\n\n", temp.marks);
    }

    fclose(fp);

    return 0;
}

void writeRecords(struct student *s)
{
    FILE *fp;

    fp = fopen("student.bin", "wb");

    for (int i = 0; i < 3; i++)
    {
        fwrite(s + i, sizeof(struct student), 1, fp);
    }

    fclose(fp);

    printf("Records written successfully\n");
}

void getRecord(int m)
{
    FILE *fp;
    struct student temp;

    fp = fopen("student.bin", "rb");

    // Move pointer to m-th record
    fseek(fp, (m - 1) * sizeof(struct student), SEEK_SET);

    fread(&temp, sizeof(struct student), 1, fp);

    printf("ID : %d\n", temp.id);
    printf("Name : %s\n", temp.name);
    printf("Marks : %.2f\n", temp.marks);

    fclose(fp);
}

void deleteRecord(int deleteId)
{
    FILE *fp, *tempFile;

    struct student temp;

    fp = fopen("student.bin", "rb");
    tempFile = fopen("temp.bin", "wb");

    while (fread(&temp, sizeof(struct student), 1, fp))
    {
        if (temp.id != deleteId)
        {
            fwrite(&temp, sizeof(struct student), 1, tempFile);
        }
    }

    fclose(fp);
    fclose(tempFile);

    remove("student.bin");

    rename("temp.bin", "student.bin");
}
