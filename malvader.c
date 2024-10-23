#include "malvader.h"

void sendCenteredMessage(const char *format, ...)
{
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

  if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
  {
    perror("Erro ao obter o tamanho da janela do terminal.\n");
    return;
  }

  int terminalSize = csbi.srWindow.Right - csbi.srWindow.Left + 1;

  char message[1024];

  va_list args;
  va_start(args, format);

  vsnprintf(message, sizeof(message), format, args);

  va_end(args);

  int textSize = strlen(message);

  int leftSpaces = (terminalSize - textSize) / 2;
  if (leftSpaces < 0)
    leftSpaces = 0;

  for (int i = 0; i < leftSpaces; i++)
  {
    printf(" ");
  }

  printf("%s", message);
}

void sendTitle()
{
  char title[ROWS][CHARACTERS] = {
      "::::     ::::     :::     :::    :::     :::     :::     :::::::::  :::::::::: :::::::::  ",
      "+:+:+: :+:+:+   :+: :+:   :+:    :+:     :+:   :+: :+:   :+:    :+: :+:        :+:    :+: ",
      "+:+ +:+:+ +:+  +:+   +:+  +:+    +:+     +:+  +:+   +:+  +:+    +:+ +:+        +:+    +:+ ",
      "+#+  +:+  +#+ +#++:++#++: +#+    +#+     +:+ +#++:++#++: +#+    +:+ +#++:++#   +#++:++#:  ",
      "+#+       +#+ +#+     +#+ +#+     +#+   +#+  +#+     +#+ +#+    +#+ +#+        +#+    +#+ ",
      "#+#       #+# #+#     #+# #+#      #+#+#+#   #+#     #+# #+#    #+# #+#        #+#    #+# ",
      "###       ### ###     ### ########## ###     ###     ### #########  ########## ###    ### "};

  char subtitle[ROWS][CHARACTERS] = {
      "                     :::::::::      :::     ::::    ::: :::    :::                        ",
      "                     :+:    :+:   :+: :+:   :+:+:   :+: :+:   :+:                         ",
      "                     +:+    +:+  +:+   +:+  :+:+:+  +:+ +:+  +:+                          ",
      "                     +#++:++#+  +#++:++#++: +#+ +:+ +#+ +#++:++                           ",
      "                     +#+    +#+ +#+     +#+ +#+  +#+#+# +#+  +#+                          ",
      "                     #+#    #+# #+#     #+# #+#   #+#+# #+#   #+#                         ",
      "                     #########  ###     ### ###    #### ###    ###                        "};

  sendCenteredMessage("------------------------------------------------------------------------------------------\n\n");
  sendCenteredMessage("\n");

  for (int i = 0; i < ROWS; i++)
  {
    sendCenteredMessage("%s\n", title[i]);
  }
  sendCenteredMessage("\n");

  for (int i = 0; i < ROWS; i++)
  {
    sendCenteredMessage("%s\n", subtitle[i]);
  }
  sendCenteredMessage("\n");
  sendCenteredMessage("------------------------------------------------------------------------------------------\n\n");
}

void sendMenu()
{
  int option, position;

  FILE *employeeFile;
  Employee employee;

  employeeFile = fopen("employees.txt", "r+");

  if (employeeFile == NULL)
  {
    sendTitle();
    sendCenteredMessage("Nao foi possivel realizar leitura da base de dados dos funcionarios.\n");
    sendCenteredMessage("Pressione qualquer tecla para criar uma nova base de dados\n\n");
    getch();
    system("cls");
    employeeFile = fopen("employees.txt", "w+");
  }

  do
  {
    sendTitle();
    sendCenteredMessage("Escolha uma opcao do menu principal: \n\n");
    sendCenteredMessage("1. Funcionario\n");
    sendCenteredMessage("2. Cliente\n");
    sendCenteredMessage("3. Sair\n\n");
    sendCenteredMessage("> ");
    scanf("%d", &option);
    system("cls");

    switch (option)
    {
    case 1:
      sendTitle();
      sendCenteredMessage("Digite o nome do funcionario: \n");
      sendCenteredMessage("> ");
      fflush(stdin);
      gets(employee.name);
      system("cls");

      if (strcmp(employee.name, "admin") == 0)
      {
        char password[DEFAULT_PASS_SIZE];

        sendTitle();
        sendCenteredMessage("Digite a senha de administrador: \n");
        sendCenteredMessage("> ");
        fflush(stdin);
        gets(password);
        system("cls");

        if (validateAdminPass(password) == 0)
        {
          sendMenuEmployee();
        }
        else if (validateAdminPass(password) != 0)
        {
          sendTitle();
          sendCenteredMessage("A senha informada esta incorreta.\n\n");
          sendCenteredMessage("Pressione qualquer tecla para voltar ao menu...\n");
          getch();
          system("cls");

          sendMenuEmployee();
        }

        return;
      }

      break;

    case 2:
      sendMenuCustomer();
      break;

    case 3:
      exit(EXIT_SUCCESS);
      break;

    default:
      break;
    }
  } while (option <= 0 || option > 3);
}

void sendMenuEmployee()
{
  int option;
  Employee *employeeList = NULL;
  sendTitle();
  sendCenteredMessage("Escolha uma opcao do menu de funcionarios: \n\n");
  sendCenteredMessage("1. Abertura de Conta\n");
  sendCenteredMessage("2. Encerramento de Conta\n");
  sendCenteredMessage("3. Consultar Dados\n");
  sendCenteredMessage("4. Alterar Dados\n");
  sendCenteredMessage("5. Cadastro de Funcionarios\n");
  sendCenteredMessage("6. Voltar ao menu principal\n");
  sendCenteredMessage("7. Sair\n\n");
  sendCenteredMessage("> ");
  scanf("%d", &option);
  system("cls");

  switch (option)
  {
  case 1:
    break;

  case 2:
    break;

  case 3:
    loadEmployees(&employeeList, "employees.txt");
    printEmployees(employeeList);
    break;

  case 4:
    break;

  case 5:

    loadEmployees(&employeeList, "employees.txt");

    Employee *newEmployee = getEmployeeDataFromUser(employeeList);
    addEmployee(&employeeList, newEmployee);

    saveEmployees(newEmployee, "employees.txt");

    sendTitle();
    sendCenteredMessage("O novo funcionario foi adicionado com sucesso!\n");
    system("cls");
    break;

  case 6:
    sendMenu();
    system("cls");
    break;

  case 7:
    exit(EXIT_SUCCESS);
    break;

  default:
    break;
  }
}

void sendMenuCustomer()
{
  int option;
  sendTitle();
  sendCenteredMessage("Escolha uma opcao do menu de clientes: \n\n");
  sendCenteredMessage("1. Saldo\n");
  sendCenteredMessage("2. Deposito\n");
  sendCenteredMessage("3. Saque\n");
  sendCenteredMessage("4. Extrato\n");
  sendCenteredMessage("5. Consultar limite\n");
  sendCenteredMessage("6. Voltar ao menu principal\n");
  sendCenteredMessage("7. Sair\n\n");
  sendCenteredMessage("> ");
  scanf("%d", &option);
  system("cls");

  switch (option)
  {
  case 1:
    break;

  case 2:
    break;

  case 3:
    break;

  case 4:
    break;

  case 5:
    break;

  case 6:
    sendMenu();
    system("cls");
    break;

  case 7:
    exit(EXIT_SUCCESS);
    break;

  default:
    break;
  }
}

int validateAdminPass(char *password)
{
  const char *adminPassword = "malvo";

  if (strcmp(password, adminPassword) != 0)
  {
    return 1;
  }

  return 0;
}

Employee *createEmployee(char *name, char *cpf, int employeeCode, char *role, Date birth, char *phoneNumber, char *password, Address address)
{
  Employee *newEmployee = (Employee *)malloc(sizeof(Employee));
  strcpy(newEmployee->name, name);
  strcpy(newEmployee->cpf, cpf);
  newEmployee->employeeCode = employeeCode;
  strcpy(newEmployee->role, role);
  newEmployee->birth = birth;
  strcpy(newEmployee->phoneNumber, phoneNumber);
  strcpy(newEmployee->password, password);
  newEmployee->address = address;
  newEmployee->deleted = 0;
  newEmployee->next = NULL;
  return newEmployee;
}

void addEmployee(Employee **head, Employee *newEmployee)
{
  if (*head == NULL)
  {
    *head = newEmployee;
  }
  else
  {
    Employee *temp = *head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    temp->next = newEmployee;
  }
}

void loadEmployees(Employee **head, const char *filename)
{
  FILE *file = fopen(filename, "r+");
  if (file == NULL)
  {
    return;
  }
  Employee tempEmployee;
  while (fread(&tempEmployee, sizeof(Employee), 1, file))
  {
    if (tempEmployee.deleted == 0)
    {
      Employee *newEmployee = createEmployee(
          tempEmployee.name, tempEmployee.cpf, tempEmployee.employeeCode,
          tempEmployee.role, tempEmployee.birth, tempEmployee.phoneNumber,
          tempEmployee.password, tempEmployee.address);
      addEmployee(head, newEmployee);
    }
  }
  fclose(file);
}

void saveEmployees(Employee *head, const char *filename)
{
  FILE *file = fopen(filename, "a+");
  if (file == NULL)
  {
    sendTitle();
    sendCenteredMessage("Erro ao tentar ler a base de dados de funcionarios.\n");
    return;
  }
  Employee *temp = head;
  while (temp != NULL)
  {
    fwrite(temp, sizeof(Employee), 1, file);
    temp = temp->next;
  }
  fclose(file);
}

void printEmployees(Employee *head)
{
  Employee *temp = head;
  while (temp != NULL)
  {
    sendTitle();
    sendCenteredMessage("Nome: %s\n", temp->name);
    sendCenteredMessage("CPF: %s\n", temp->cpf);
    sendCenteredMessage("Codigo: %d\n", temp->employeeCode);
    sendCenteredMessage("Cargo: %s\n", temp->role);
    sendCenteredMessage("Data de nascimento: %02d/%02d/%04d\n", temp->birth.day, temp->birth.month, temp->birth.year);
    sendCenteredMessage("Numero de telefone: %s\n", temp->phoneNumber);
    sendCenteredMessage("Endereco: %s, %s, %s, %s, %s\n", temp->address.address, temp->address.cep, temp->address.city, temp->address.state, temp->address.country);

    temp = temp->next;

    if (temp != NULL)
    {
      sendCenteredMessage("\n");
      sendCenteredMessage("Pressione qualquer tecla para ver o proximo funcionario...\n\n");
      getch();
      system("cls");
    }
  }

  sendCenteredMessage("\n");
  sendCenteredMessage("Todos os funcionarios foram exibidos.\n");
  sendCenteredMessage("Pressione qualquer tecla para voltar ao menu...\n\n");
  getch();
  system("cls");
  sendMenuEmployee();
}

void deleteEmployee(Employee *head, int employeeCode)
{
  Employee *temp = head;
  while (temp != NULL)
  {
    if (temp->employeeCode == employeeCode)
    {
      temp->deleted = 1;
      return;
    }
    temp = temp->next;
  }
}

void modifyEmployee(Employee *head, int employeeCode)
{
  Employee *temp = head;
  while (temp != NULL)
  {
    if (temp->employeeCode == employeeCode && temp->deleted == 0)
    {
      sendCenteredMessage("Alterando dados do funcionario %s (Codigo: %d)\n", temp->name, temp->employeeCode);
      sendCenteredMessage("Digite o novo nome: ");
      scanf("%s", temp->name);
      sendCenteredMessage("Digite o novo CPF: ");
      scanf("%s", temp->cpf);
      sendCenteredMessage("Digite o novo numero de telefone: ");
      scanf("%s", temp->phoneNumber);
      return;
    }
    temp = temp->next;
  }
}

int employeeCodeExists(Employee *head, int employeeCode)
{
  Employee *temp = head;
  while (temp != NULL)
  {
    if (temp->employeeCode == employeeCode && temp->deleted == 0)
    {
      return 1;
    }
    temp = temp->next;
  }
  return 0;
}

Employee *getEmployeeDataFromUser(Employee *employeeList)
{
  char name[25], cpf[14], role[25], phoneNumber[15], password[16], addressLine[45], cep[10], city[20], country[20], state[3];
  int employeeCode, day, month, year;

  sendTitle();
  sendCenteredMessage("Digite o codigo que sera atribuido ao funcionario: ");
  scanf("%d", &employeeCode);
  system("cls");

  if (employeeCodeExists(employeeList, employeeCode) == 1)
  {
    sendTitle();
    sendCenteredMessage("O codigo %d ja foi atribuido a outro funcionario.\n", employeeCode);
    sendCenteredMessage("Pressione qualquer tecla para retornar ao menu e tentar novamente...\n");
    getch();
    system("cls");
    sendMenuEmployee();
    return NULL;
  }

  sendTitle();
  sendCenteredMessage("Digite o nome completo: ");
  scanf("%s", name);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite o CPF: ");
  scanf("%s", cpf);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite o cargo: ");
  scanf("%s", role);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite a data de nascimento (dia mes ano): ");
  scanf("%d %d %d", &day, &month, &year);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite o numero de telefone: ");
  scanf("%s", phoneNumber);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite a senha de acesso: ");
  scanf("%s", password);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite o endereco: ");
  scanf(" %[^\n]", addressLine);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite o CEP: ");
  scanf("%s", cep);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite a cidade de residencia do funcionario: ");
  scanf(" %[^\n]", city);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite o pais de residencia do funcionario: ");
  scanf(" %[^\n]", country);
  system("cls");

  sendTitle();
  sendCenteredMessage("Digite o estado de residencia do funcionario (2 caracteres somente): ");
  scanf("%s", state);
  system("cls");

  Date birth = {day, month, year};

  Address address;
  strcpy(address.address, addressLine);
  strcpy(address.cep, cep);
  strcpy(address.city, city);
  strcpy(address.country, country);
  strcpy(address.state, state);

  return createEmployee(name, cpf, employeeCode, role, birth, phoneNumber, password, address);
}