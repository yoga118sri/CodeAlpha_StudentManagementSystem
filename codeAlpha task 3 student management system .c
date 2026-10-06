#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }
    struct Student s;
    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);
    printf("Student record added successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("\nNo records found!\n");
        return;
    }
    struct Student s;
    printf("\n--- Student Records ---\n");
    printf("Roll No\t%-20s\tMarks\n", "Name");
    printf("----------------------------------------\n");
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("%d\t%-20s\t%.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("\nNo records found!\n");
        return;
    }
    int roll, found = 0;
    struct Student s;
    printf("\nEnter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found!\nRoll: %d\nName: %s\nMarks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("Student with Roll Number %d not found.\n", roll);
    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    if (!fp) {
        printf("\nNo records found!\n");
        return;
    }
    int roll, found = 0;
    struct Student s;
    printf("\nEnter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);
            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) printf("Student not found!\n");
    fclose(fp);
}

void deleteStudent() {
    FILE *fp = fopen("students.dat", "rb");
    if (!fp) {
        printf("\nNo records found!\n");
        return;
    }
    FILE *temp = fopen("temp.dat", "wb");
    int roll, found = 0;
    struct Student s;

    printf("\nEnter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }
    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) printf("Record deleted successfully!\n");
    else printf("Student not found!\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n=== Student Management System ===\n");
        printf("1. Add Record\n2. Display All Records\n3. Search Record\n4. Update Record\n5. Delete Record\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
 }   
    