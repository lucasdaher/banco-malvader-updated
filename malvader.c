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