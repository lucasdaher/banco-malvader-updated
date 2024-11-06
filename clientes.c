#include "clientes.h"
#include "malvader.h"
#include "funcionarios.h"
#include "transacoes.h"

void enviarMenuCliente(FILE *file, Cliente cliente)
{
  enviarTitulo();
  int opcao;

  do
  {
    printf("Escolha uma opcao do menu de clientes: \n\n");
    printf("1) Saldo\n");
    printf("2) Deposito\n");
    printf("3) Saque\n");
    printf("4) Extrato\n");
    printf("5) Consultar limite\n");
    printf("6) Sair\n\n");
    scanf("%d", &opcao);
    system("cls");

    switch (opcao)
    {
    case 1:
      saldo(cliente);
      break;

    case 2:
      depositar(cliente);
      break;

    case 3:
      sacar(cliente);

      break;

    case 4:
      enviarTitulo();
      printf("Realizando abertura do extrato da sua conta.\n");
      printf("Pressione qualquer tecla para voltar ao menu...\n");

      system("start excel.exe extrato.xlsx");
      getch();
      system("cls");

      enviarMenuCliente(file, cliente);
      break;

    case 5:
      enviarTitulo();

      if (strcmp(cliente.tipoConta, "CC") == 0)
      {
        printf("Seu limite atual: %.2f\n\n", cliente.limiteDaConta);
        printf("Pressione qualquer tecla para retornar ao menu...\n");
      }
      else if (strcmp(cliente.tipoConta, "CP") == 0)
      {
        printf("Consultando os limites de %s\n\n", cliente.nome);
        printf("O seu tipo de conta nao possui limites.\n");
        printf("Solicite uma alteracao para conta corrente em caso de interesse.\n\n");
        printf("Pressione qualquer tecla para retornar ao menu...\n");
      }
      getch();
      system("cls");

      enviarMenuCliente(file, cliente);
      break;

    case 6:
      enviarMenuPrincipal();
      break;

    default:
      enviarTitulo();
      printf("Voce selecionou uma opcao invalida.\n");
      printf("Pressione qualquer tecla para tentar novamente...\n");
      getch();
      system("cls");

      enviarMenuCliente(file, cliente);
      break;
    }
  } while (opcao <= 0 || opcao > 6);
}

int consultarCliente(FILE *file, Cliente cliente)
{
  Cliente cliente_lido;

  int posicao;

  if (file != NULL)
  {
    fseek(file, 0L, SEEK_SET);
    posicao = 0;

    while (fread(&cliente_lido, sizeof(cliente_lido), 1, file))
    {
      if (strcmpi(cliente_lido.nome, cliente.nome) == 0 &&
          (cliente_lido.excluido == 0))

        return posicao;
      posicao++;
    };
  }
  return -1;
}

int inserirCliente(FILE *file, Cliente cliente)
{
  Cliente cliente_lido;

  int posicao;

  if (file != NULL)
  {
    posicao = 0;

    if (consultarCliente(file, cliente))
    {
      fseek(file, 0L, SEEK_SET);

      while (fread(&cliente_lido, sizeof(cliente_lido), 1, file))
      {
        if (cliente_lido.excluido == 1)
          break;
        posicao++;
      };

      fseek(file, posicao * sizeof(cliente), SEEK_SET);

      cliente.excluido = 0;

      fwrite(&cliente, sizeof(cliente), 1, file);

      enviarTitulo();
      printf("O(a) cliente foi cadastrado(a) com sucesso.\n");
      printf("Pressione qualquer tecla para concluir e salvar...\n");
      getch();
      system("cls");

      fclose(file);

      enviarMenuFuncionario();
      return 0;
    }
  }
  return -1;
}

int alterarCliente(FILE *file, Cliente cliente_antigo, Cliente cliente_novo)
{
  int posicao;

  if (file != NULL)
  {
    if ((posicao = consultarCliente(file, cliente_antigo)) != -1)
    {
      fseek(file, posicao * sizeof(Cliente), SEEK_SET);

      fread(&cliente_antigo, sizeof(cliente_antigo), 1, file);

      strcpy(cliente_antigo.nome, cliente_novo.nome);
      cliente_antigo.agencia = cliente_novo.agencia;
      cliente_antigo.numDaConta = cliente_novo.numDaConta;
      strcpy(cliente_antigo.cpf, cliente_novo.cpf);
      cliente_antigo.nascimento.dia = cliente_novo.nascimento.dia;
      cliente_antigo.nascimento.mes = cliente_novo.nascimento.mes;
      cliente_antigo.nascimento.ano = cliente_novo.nascimento.ano;
      cliente_antigo.vencimento.dia = cliente_novo.vencimento.dia;
      cliente_antigo.vencimento.mes = cliente_novo.vencimento.mes;
      cliente_antigo.vencimento.ano = cliente_novo.vencimento.ano;

      strcpy(cliente_antigo.telefone, cliente_novo.telefone);
      strcpy(cliente_antigo.endereco.endereco, cliente_novo.endereco.endereco);
      strcpy(cliente_antigo.endereco.cep, cliente_novo.endereco.cep);
      strcpy(cliente_antigo.endereco.bairro, cliente_novo.endereco.bairro);
      strcpy(cliente_antigo.endereco.cidade, cliente_novo.endereco.cidade);
      strcpy(cliente_antigo.endereco.estado, cliente_novo.endereco.estado);

      cliente_antigo.saldo = cliente_novo.saldo;

      strcpy(cliente_antigo.senha, cliente_novo.senha);
      strcpy(cliente_antigo.tipoConta, cliente_novo.tipoConta);

      fseek(file, posicao * sizeof(Cliente), SEEK_SET);

      fwrite(&cliente_antigo, sizeof(cliente_novo), 1, file);

      enviarTitulo();
      printf("Os dados deste cliente foram alterados com sucesso.\n\n");
      printf("Pressione qualquer tecla para finalizar.\n");
      getch();
      system("cls");

      fclose(file);

      enviarMenuFuncionario();
      return 0;
    }
  }
  return -1;
}

int excluirCliente(FILE *file, Cliente cliente)
{
  int posicao;

  if (file != NULL)
  {
    if ((posicao = consultarCliente(file, cliente)) != -1)
    {
      fseek(file, posicao * sizeof(cliente), SEEK_SET);

      cliente.excluido = 1;

      fwrite(&cliente, sizeof(cliente), 1, file);

      enviarTitulo();
      printf("Voce excluiu o cliente %s dos registros com sucesso.\n", cliente.nome);
      printf("Pressione qualquer tecla para finalizar e salvar...\n");
      getch();
      system("cls");

      fclose(file);

      enviarMenuFuncionario();
      return 0;
    }
  }
  return -1;
}

void validarSenhaCliente(FILE *file, Cliente cliente)
{
  int acesso;
  int posicao;

  char password[DEFAULT_PASS_SIZE];

  do
  {
    acesso = 0;

    if ((posicao = consultarCliente(file, cliente)) != -1)
    {
      fseek(file, posicao * sizeof(cliente), SEEK_SET);

      fread(&cliente, sizeof(cliente), 1, file);

      enviarTitulo();
      printf("Digite a senha: \n");
      fflush(stdin);
      gets(password);
      system("cls");

      if (strcmp(password, cliente.senha) == 0)
      {
        acesso = 1;
        enviarTitulo();
        printf("Autenticado com sucesso. \n");
        system("cls");

        enviarMenuCliente(file, cliente);
      }
      else
      {
        acesso = 0;
        enviarTitulo();
        printf("A senha digitada esta incorreta.\n");
        exit(1);
      }
    }
  } while (acesso == 0);
}

void saldo(Cliente cliente)
{
  FILE *file = fopen("clientes.txt", "r+");

  if (file == NULL)
  {
    printf("O arquivo de clientes nao foi encontrado. Tentando gerar um novo...\n");
    file = fopen("clientes.txt", "w+");
  }

  int posicao;

  if ((posicao = consultarCliente(file, cliente)) != -1)
  {
    fseek(file, posicao * sizeof(cliente), SEEK_SET);
    fread(&cliente, sizeof(cliente), 1, file);

    enviarTitulo();
    printf("Saldo atual em sua conta R$%.2f\n\n", cliente.saldo);
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch();
    system("cls");

    enviarMenuCliente(file, cliente);
  }
}

void depositar(Cliente cliente)
{
  FILE *file = fopen("clientes.txt", "r+");

  if (file == NULL)
  {
    printf("O arquivo de clientes nao foi encontrado, tentando gerar um novo...\n");
    file = fopen("clientes.txt", "w+");
  }

  float valor;

  int posicao;

  enviarTitulo();
  printf("Seu saldo atual R$%.2f\n", cliente.saldo);
  printf("Digite o valor que deseja depositar: \n");
  printf("R$");
  scanf("%f", &valor);
  system("cls");

  if ((posicao = consultarCliente(file, cliente)) == -1)
  {
    enviarTitulo();
    printf("A sua conta esta com problema, tente novamente mais tarde.\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch();
    system("cls");

    enviarMenuCliente(file, cliente);
    return;
  }

  if (valor < 0)
  {
    enviarTitulo();
    printf("O valor deve ser maior que 0.\n");
    printf("Pressione qualquer tecla para tentar novamente...\n");
    getch();
    system("cls");
    enviarMenuCliente(file, cliente);
    return;
  }

  cliente.saldo += valor;

  fseek(file, posicao * sizeof(cliente), SEEK_SET);

  fwrite(&cliente, sizeof(cliente), 1, file);

  fclose(file);

  criarMovimento(cliente, "Deposito", valor);
  enviarTitulo();
  printf("Voce realizou um deposito no valor de R$%.2f com sucesso.\n", valor);
  printf("Seu saldo atualizado: R$%.2f\n\n", cliente.saldo);
  printf("Pressione qualquer tecla para retornar ao menu...\n");
  getch();
  system("cls");

  enviarMenuCliente(file, cliente);
}

void sacar(Cliente cliente)
{
  FILE *file = fopen("clientes.txt", "r+");

  if (file == NULL)
  {
    printf("O arquivo de clientes nao foi encontrado. Tentando gerar um novo...\n");
    file = fopen("clientes.txt", "w+");
  }

  float valor;

  int posicao;

  enviarTitulo();
  printf("Seu saldo atual R$%.2f\n", cliente.saldo);
  printf("Digite o valor que deseja sacar: \n");
  printf("R$");
  scanf("%f", &valor);
  system("cls");

  if ((posicao = consultarCliente(file, cliente)) == -1)
  {
    enviarTitulo();
    printf("A sua conta esta com problema, tente novamente mais tarde.\n");
    printf("Pressione qualquer tecla para voltar ao menu...\n");
    getch();
    system("cls");

    enviarMenuCliente(file, cliente);
    return;
  }

  if (valor < 0)
  {
    enviarTitulo();
    printf("O valor deve ser maior que 0.\n");
    printf("Pressione qualquer tecla para tentar novamente...\n");
    getch();
    system("cls");
    enviarMenuCliente(file, cliente);
    return;
  }

  if (valor > cliente.saldo)
  {
    enviarTitulo();
    printf("Voce nao possui saldo suficiente para sacar.\n");
    printf("Pressione qualquer tecla para tentar novamente...\n");
    getch();
    system("cls");
    enviarMenuCliente(file, cliente);
    return;
  }

  cliente.saldo -= valor;

  fseek(file, posicao * sizeof(cliente), SEEK_SET);

  fwrite(&cliente, sizeof(cliente), 1, file);

  fclose(file);

  criarMovimento(cliente, "Saque", valor);
  enviarTitulo();
  printf("Voce realizou um saque no valor de R$%.2f com sucesso.\n", valor);
  printf("Seu saldo atualizado: R$%.2f\n\n", cliente.saldo);
  printf("Pressione qualquer tecla para retornar ao menu...\n");
  getch();
  system("cls");

  enviarMenuCliente(file, cliente);
}