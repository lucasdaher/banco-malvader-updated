#include "clientes.h"
#include "malvader.h"
#include "funcionarios.h"
#include "transacoes.h"

void enviarTitulo()
{
  char title[7][91] = {
      "::::     ::::     :::     :::    :::     :::     :::     :::::::::  :::::::::: :::::::::  ",
      "+:+:+: :+:+:+   :+: :+:   :+:    :+:     :+:   :+: :+:   :+:    :+: :+:        :+:    :+: ",
      "+:+ +:+:+ +:+  +:+   +:+  +:+    +:+     +:+  +:+   +:+  +:+    +:+ +:+        +:+    +:+ ",
      "+#+  +:+  +#+ +#++:++#++: +#+    +#+     +:+ +#++:++#++: +#+    +:+ +#++:++#   +#++:++#:  ",
      "+#+       +#+ +#+     +#+ +#+     +#+   +#+  +#+     +#+ +#+    +#+ +#+        +#+    +#+ ",
      "#+#       #+# #+#     #+# #+#      #+#+#+#   #+#     #+# #+#    #+# #+#        #+#    #+# ",
      "###       ### ###     ### ########## ###     ###     ### #########  ########## ###    ### "};

  char subtitle[7][91] = {
      "                     :::::::::      :::     ::::    ::: :::    :::                        ",
      "                     :+:    :+:   :+: :+:   :+:+:   :+: :+:   :+:                         ",
      "                     +:+    +:+  +:+   +:+  :+:+:+  +:+ +:+  +:+                          ",
      "                     +#++:++#+  +#++:++#++: +#+ +:+ +#+ +#++:++                           ",
      "                     +#+    +#+ +#+     +#+ +#+  +#+#+# +#+  +#+                          ",
      "                     #+#    #+# #+#     #+# #+#   #+#+# #+#   #+#                         ",
      "                     #########  ###     ### ###    #### ###    ###                        "};

  printf("------------------------------------------------------------------------------------------\n\n");
  printf("\n");

  for (int i = 0; i < 7; i++)
  {
    printf("%s\n", title[i]);
  }
  printf("\n");

  for (int i = 0; i < 7; i++)
  {
    printf("%s\n", subtitle[i]);
  }
  printf("\n");
  printf("------------------------------------------------------------------------------------------\n\n");
}

void obterEntrada(char *mensagem, char *buffer, int buffer_size)
{
  enviarTitulo();
  printf("%s", mensagem);
  fflush(stdin);
  fgets(buffer, buffer_size, stdin);
  buffer[strcspn(buffer, "\n")] = 0;
  system("cls");
}

FILE *verificarOuCriarArquivo(const char *filename)
{
  FILE *file = fopen(filename, "r+");
  if (file == NULL)
  {
    printf("Arquivo %s nao foi encontrado, recriando o arquivo...\n", filename);
    file = fopen(filename, "w+");
  }
  return file;
}

int validarSenhaAdmin(char *senhaDigitada)
{
  const char *passAdmin = "adm";

  if (strcmp(senhaDigitada, passAdmin) != 0)
  {
    return 1;
  }

  return 0;
}

void enviarMenuPrincipal()
{
  Funcionario funcionario;
  Cliente cliente;
  int option;
  FILE *file = verificarOuCriarArquivo("funcionarios.txt");
  FILE *fileCliente = verificarOuCriarArquivo("clientes.txt");

  do
  {
    enviarTitulo();
    printf("Escolha uma opcao do menu principal:\n\n");
    printf("1) Funcionario\n");
    printf("2) Cliente\n");
    printf("3) Sair\n\n");
    scanf("%d", &option);
    system("cls");

    switch (option)
    {
    case 1:
      obterEntrada("Digite o nome do funcionario: \n", funcionario.nomeFuncionario, sizeof(funcionario.nomeFuncionario));

      if (strcmp(funcionario.nomeFuncionario, "admin") == 0)
      {
        char password[DEFAULT_PASS_SIZE];
        obterEntrada("Digite a senha de administrador: \n", password, sizeof(password));

        if (validarSenhaAdmin(password) == 0)
        {
          enviarMenuFuncionario();
        }
        else
        {
          enviarTitulo();
          printf("A senha informada nao e valida.\n\n");
          printf("Pressione qualquer tecla para voltar ao menu...\n");
          getch();
          system("cls");
        }
      }
      else if (consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario) != -1)
      {
        validarSenhaFuncionario(file, funcionario);
      }
      else
      {
        enviarTitulo();
        printf("O funcionario informado nao existe.\n");
        printf("Pressione qualquer tecla para tentar novamente...\n");
        getch();
        system("cls");
      }
      break;

    case 2:
      enviarTitulo();
      printf("Digite o numero da conta: \n");
      scanf("%d", &cliente.numDaConta);
      system("cls");

      if (consultarClientePorCodigo(fileCliente, cliente.numDaConta) != -1)
      {
        validarSenhaCliente(fileCliente, cliente);
      }
      else
      {
        enviarTitulo();
        printf("O cliente informado nao existe.\n");
        printf("Pressione qualquer tecla para tentar novamente...\n");
        getch();
        system("cls");
      }
      break;

    case 3:
      enviarTitulo();
      perror("Saindo do programa...");
      exit(EXIT_FAILURE);
      break;

    default:
      enviarTitulo();
      perror("Opcao invalida. Tente novamente.\n");
      getch();
      system("cls");
    }

  } while (option != 3);

  fclose(file);
  fclose(fileCliente);
}

void enviarMenuAberturaConta()
{
  FILE *file = verificarOuCriarArquivo("clientes.txt");
  Cliente cliente;
  int option;

  do
  {
    enviarTitulo();
    printf("Menu funcionario:\n\n");
    printf("1) Conta Poupanca\n");
    printf("2) Conta Corrente\n");
    printf("3) Voltar\n\n");
    scanf("%d", &option);
    system("cls");

    if (option == 1 || option == 2)
    {
      obterEntrada("Informe o nome do cliente: \n", cliente.nome, sizeof(cliente.nome));
      printf("Informe o numero da agencia do cliente:\n");
      scanf("%d", &cliente.agencia);
      printf("Informe o numero da conta do cliente:\n");
      scanf("%d", &cliente.numDaConta);

      if (option == 2)
      {
        printf("Informe o limite da conta do cliente:\n");
        scanf("%f", &cliente.limiteDaConta);
        printf("Informe a data de vencimento da conta no formato DD MM AAAA:\n");
        scanf("%d %d %d", &cliente.vencimento.dia, &cliente.vencimento.mes, &cliente.vencimento.ano);
      }

      obterEntrada("Informe o numero do CPF do cliente: \n", cliente.cpf, sizeof(cliente.cpf));
      printf("Informe a data de nascimento do cliente no formato DD MM AAAA:\n");
      scanf("%d %d %d", &cliente.nascimento.dia, &cliente.nascimento.mes, &cliente.nascimento.ano);

      obterEntrada("Informe o telefone do cliente: \n", cliente.telefone, sizeof(cliente.telefone));
      obterEntrada("Informe o endereco do cliente: \n", cliente.endereco.endereco, sizeof(cliente.endereco.endereco));
      obterEntrada("Informe o CEP do cliente: \n", cliente.endereco.cep, sizeof(cliente.endereco.cep));
      obterEntrada("Informe o bairro do cliente: \n", cliente.endereco.bairro, sizeof(cliente.endereco.bairro));
      obterEntrada("Informe a cidade do cliente: \n", cliente.endereco.cidade, sizeof(cliente.endereco.cidade));
      obterEntrada("Informe o estado do cliente: \n", cliente.endereco.estado, sizeof(cliente.endereco.estado));

      printf("Informe o saldo inicial do cliente:\n");
      scanf("%f", &cliente.saldo);

      const char *tipoConta = (option == 1) ? "CP" : "CC";
      strncpy(cliente.tipoConta, tipoConta, sizeof(cliente.tipoConta));

      obterEntrada("Informe a senha do cliente: \n", cliente.senha, sizeof(cliente.senha));
      inserirCliente(file, cliente);
    }
    else if (option == 3)
    {
      enviarMenuFuncionario();
      break;
    }
    else
    {
      enviarTitulo();
      printf("Opcao invalida. Tente novamente.\n");
      getch();
      system("cls");
    }
  } while (option != 3);

  fclose(file);
}

void formatarTipoConta(Cliente cliente)
{
  const char *tipo = (strcmp(cliente.tipoConta, "CP") == 0) ? "Conta Poupanca" : (strcmp(cliente.tipoConta, "CC") == 0) ? "Conta Corrente"
                                                                                                                        : "Indefinida";
  printf("Tipo de conta: %s\n", tipo);
}
