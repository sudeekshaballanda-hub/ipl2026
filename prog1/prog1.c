/*The advantage of storing array of structures as binary files is that we can
use fseek to go to specific record and get the record. Write a program to store
n records in binary file. Write a function to get mth record and display. Use
fseek Write a function to delete a record. Deleting a record requires
thinking.*/
#include <stdio.h>
typedef struct {
  char name[50];
  int id;
  int salary;
} Employee;
void data(int n, Employee e[]) {
  for (int i = 0; i < n; i++) {
    printf("Enter details of Employee %d\n", i + 1);
    printf("Enter name:");
    scanf("%s", e[i].name);
    printf("Enter id:");
    scanf("%d", &e[i].id);
    printf("Enter salary:");
    scanf("%d", &e[i].salary);
  }
}
void write_to_file(int n, Employee e[]) {
  FILE *fp = fopen("Employee.dat", "wb");
  if (fp == NULL) {
    printf("File dosen't exists.");
  }
  for (int i = 0; i < n; i++) {
    fwrite(&e[i], sizeof(Employee), 1, fp);
  }
  fclose(fp);
}
void del_f(int n, Employee e[], int del) {
  Employee temp;
  FILE *fp = fopen("Employee.dat", "rb");
  FILE *fp1 = fopen("temp.dat", "wb");
  for (int i = 0; i < n; i++) {
    fread(&e[i], sizeof(Employee), 1, fp);
  }
  for (int i = 0; i < n; i++) {
    if (temp.id != del) {
      fwrite(&temp, sizeof(Employee), 1, fp1);
    } else
      printf("Record found deleted");
  }
}
void search_mth(int m, Employee e[]) {
  Employee temp;
  FILE *fp = fopen("Employee.dat", "rb");
  if (fp == NULL)
    return;
  fseek(fp, m * sizeof(Employee), SEEK_SET);
  if (fread(&temp, m * sizeof(Employee), 1, fp) == 1) {
    printf("mth record: %d\nID: %d\nName: %s\nSalary: %d\n", m, temp.id,
           temp.name, temp.salary);
  } else {
    printf("Invalid file");
  }
  fclose(fp);
}

int main() {
  int n;
  Employee e[100];
  int del;
  int m;
  FILE *fp;
  FILE *fp1;
  printf("Enter the number of records you want to store: ");
  scanf("%d", &n);
  data(n, e);
  write_to_file(n, e);
  printf("Which file you need to delete?");
  scanf("%d", &del);
  del_f(n, e, del);
  printf("Enter mth record to search: ");
  scanf("%d", &m);
  search_mth(m, e);
  fclose(fp);
}
