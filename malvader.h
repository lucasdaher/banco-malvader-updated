#ifndef MALVADER_H
#define MALVADER_H

#define MAX_MENU_NAME 25
#define DEFAULT_PASS_SIZE 16

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <unistd.h>

#define ROWS 7
#define CHARACTERS 91

typedef struct
{
  int day;
  int month;
  int year;
} Date;

typedef struct
{
  char address[45];
  char cep[10];
  char city[20];
  char country[20];
  char state[3];
} Address;

typedef struct Employee
{
  char name[25];
  char cpf[14];
  int employeeCode;
  char role[25];
  Date birth;
  char phoneNumber[15];
  char password[16];
  Address address;
  char deleted;
  struct Employee *next;
} Employee;

Employee *createEmployee(char *name, char *cpf, int employeeCode, char *role, Date birth, char *phoneNumber, char *password, Address address);
void addEmployee(Employee **head, Employee *newEmployee);
void loadEmployees(Employee **head, const char *filename);
void saveEmployees(Employee *head, const char *filename);
void printEmployees(Employee *head);
void deleteEmployee(Employee *head, int employeeCode);
void modifyEmployee(Employee *head, int employeeCode);
int employeeCodeExists(Employee *head, int employeeCode);
Employee *getEmployeeDataFromUser();

void sendCenteredMessage(const char *format, ...);
void sendTitle();
void sendMenu();
void sendMenuEmployee();
void sendMenuCustomer();
int validateAdminPass(char *password);

#endif