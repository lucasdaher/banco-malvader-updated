#include "clientes.h"
#include "malvader.h"
#include "funcionarios.h"
#include "transacoes.h"

#define DEFAULT_PASS_SIZE 16

void enviarMenuFuncionario()
{
  FILE *file, *fileClientes;

  Funcionario funcionario, funcionario_alterado;

  Cliente cliente, cliente_alterado;

  int option, posicao, acesso;

  file = fopen("funcionarios.txt", "r+");

  fileClientes = fopen("clientes.txt", "r+");

  if (file == NULL)
  {
    printf("Arquivo de funcionarios nao encontrado, recriando o arquivo...");

    file = fopen("funcionarios.txt", "w+");
  }

  if (fileClientes == NULL)
  {
    printf("Arquivo de clientes nao encontrado, recriando o arquivo...");

    fileClientes = fopen("clientes.txt", "w+");
  }

  enviarTitulo();

  do
  {
    printf("Menu funcionario:\n\n");
    printf("1) Abertura de Conta\n");
    printf("2) Encerramento de Conta\n");
    printf("3) Consultar Dados\n");
    printf("4) Alterar Dados\n");
    printf("5) Cadastro de Funcionarios\n");
    printf("6) Sair\n\n");
    scanf("%d", &option);
    system("cls");

    fflush(file);
    fflush(fileClientes);

    switch (option)
    {
    case 1:
      enviarMenuAberturaConta();
      break;

    case 2:
      do
      {
        enviarTitulo();
        printf("Encerramento de conta\n\n");
        printf("1) Funcionario\n");
        printf("2) Cliente\n");
        printf("3) Voltar\n\n");
        scanf("%d", &option);
        system("cls");

        switch (option)
        {
        case 1:
          enviarTitulo();
          printf("Digite o codigo do funcionario que tera a conta encerrada: \n");
          scanf("%d", &funcionario.codigoFuncionario);
          system("cls");

          if ((posicao = consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario)) == -1)
          {
            enviarTitulo();
            printf("O funcionario informado nao existe...\n");
            printf("Pressione qualquer tecla para voltar ao menu...\n");
            getch();
            system("cls");

            enviarMenuFuncionario();
            return;
          }

          excluirFuncionario(file, funcionario);
          break;

        case 2:
          enviarTitulo();
          obterEntrada("Digite o nome do cliente que tera a conta encerrada: \n", cliente.nome, sizeof(cliente.nome));

          if ((posicao = consultarClientePorCodigo(fileClientes, cliente.numDaConta)) == -1)
          {
            enviarTitulo();
            printf("O cliente informado nao existe...\n");
            printf("Pressione qualquer tecla para voltar ao menu...\n");
            getch();
            system("cls");

            enviarMenuFuncionario();
            return;
          }

          excluirCliente(fileClientes, cliente);
          break;

        case 3:
          enviarMenuFuncionario();
          break;

        default:
          break;
        }
      } while (option <= 0 || option > 3);
      break;

    case 3:
      do
      {
        enviarTitulo();
        printf("Consultar dados: \n\n");
        printf("1) Funcionario\n");
        printf("2) Cliente\n\n");
        scanf("%d", &option);
        system("cls");

        switch (option)
        {
        case 1:
          enviarTitulo();
          printf("Digite o codigo do funcionario desejado: \n");
          scanf("%d", &funcionario.codigoFuncionario);
          system("cls");

          if ((posicao = consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario)) == -1)
          {
            enviarTitulo();
            printf("O funcionario nao foi encontrado.\n");
            printf("Pressione qualquer tecla para voltar ao menu.\n");
            getch();
            system("cls");
            enviarMenuFuncionario();
          }

          if ((posicao = consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario)) != -1)
          {
            fseek(file, posicao * sizeof(funcionario), SEEK_SET);

            fread(&funcionario, sizeof(funcionario), 1, file);

            enviarTitulo();

            fflush(stdin);
            printf("Mostrando informacoes do(a) funcionario(a) %s:\n\n", funcionario.nomeFuncionario);
            printf("Codigo: %d\n", funcionario.codigoFuncionario);
            printf("Cargo: %s\n", funcionario.cargo);
            printf("CPF: %s\n", funcionario.cpf);
            printf("Data de Nascimento: %d/%d/%d\n", funcionario.nascimento.dia, funcionario.nascimento.mes,
                   funcionario.nascimento.ano);
            printf("Telefone: %s\n", funcionario.telefoneContato);
            printf("Endereco: %s, %s, %s, %s, %s\n", funcionario.endereco.endereco, funcionario.endereco.cep,
                   funcionario.endereco.bairro, funcionario.endereco.cidade,
                   funcionario.endereco.estado);

            if (funcionario.excluido == 0)
            {
              printf("Status: Conta ativa\n");
            }
            else if (funcionario.excluido == 1)
            {
              printf("Status: Conta desativada.\n");
            }
            else
            {
              printf("Status: Erro.\n");
            }
            printf("Senha: %s\n", funcionario.senhaFuncionario);

            printf("\nPressione qualquer tecla para voltar ao menu...\n");
            getch();
            system("cls");
            enviarMenuFuncionario();
          }
          break;

        case 2:
          enviarTitulo();
          printf("Digite o numero da conta do cliente desejado: \n");
          fflush(stdin);
          scanf("%d", &cliente.numDaConta);
          system("cls");

          if ((posicao = consultarClientePorCodigo(fileClientes, cliente.numDaConta)) == -1)
          {
            enviarTitulo();
            printf("O cliente especificado nao foi encontrado...\n");
            printf("Pressione qualquer tecla para retornar ao menu.\n");
            getch();
            system("cls");

            enviarMenuFuncionario();
            return;
          }

          if ((posicao = consultarClientePorCodigo(fileClientes, cliente.numDaConta)) != -1)
          {
            fseek(fileClientes, posicao * sizeof(cliente), SEEK_SET);

            fread(&cliente, sizeof(cliente), 1, fileClientes);

            enviarTitulo();
            printf("Mostrando informacoes da conta numero %d:\n\n", cliente.numDaConta);
            printf("Nome do Cliente: %s\n", cliente.nome);
            formatarTipoConta(cliente);
            printf("Agencia: %d\n", cliente.agencia);
            printf("Numero da Conta: %d\n", cliente.numDaConta);
            if (strcmp(cliente.tipoConta, "CC") == 0)
            {
              printf("Limite da Conta: R$%.2f\n", cliente.limiteDaConta);
            }
            printf("CPF: %s\n", cliente.cpf);

            printf("Data de Nascimento: %d/%d/%d\n", cliente.nascimento.dia, cliente.nascimento.mes,
                   cliente.nascimento.ano);
            if (strcmp(cliente.tipoConta, "CC") == 0)
            {
              printf("Data de Vencimento: %d/%d/%d\n", cliente.nascimento.dia, cliente.nascimento.mes,
                     cliente.nascimento.ano);
            }
            printf("Telefone: %s\n", cliente.telefone);
            printf("Endereco: %s, %s, %s, %s, %s\n", cliente.endereco.endereco, cliente.endereco.cep,
                   cliente.endereco.bairro, cliente.endereco.cidade,
                   cliente.endereco.estado);
            printf("Saldo: R$%.2f\n", cliente.saldo);

            if (cliente.excluido == 0)
            {
              printf("Status: Conta ativa\n");
            }
            else if (cliente.excluido == 1)
            {
              printf("Status: Conta desativada.\n");
            }
            else
            {
              printf("Status: Erro.\n");
            }
            printf("Senha: %s\n\n", cliente.senha);

            printf("Pressione qualquer tecla para retornar ao menu...\n");
            getch();
            system("cls");
            enviarMenuFuncionario();
          }
          break;

        default:
          enviarTitulo();
          printf("Voce selecionou uma opcao invalida.\n");
          printf("Pressione qualquer tecla para tentar novamente...\n");
          getch();
          system("cls");

          enviarMenuFuncionario();
          break;
        }
      } while (option <= 0 || option > 3);

      getch();
      break;

    case 4:
      do
      {
        enviarTitulo();
        printf("Alterar dados: \n\n");
        printf("1) Alterar Conta\n");
        printf("2) Alterar Funcionario\n");
        printf("3) Alterar Cliente\n");
        printf("4) Voltar\n\n");
        scanf("%d", &option);
        system("cls");

        fflush(stdin);
        char password[DEFAULT_PASS_SIZE];

        switch (option)
        {
        case 1:
          printf("Esta funcionalidade está em desenvolvimento.\n");
          break;

        case 2:
          do
          {
            acesso = 0;

            enviarTitulo();
            obterEntrada("Digite a senha de administrador: \n", password, sizeof(password));

            if (validarSenhaAdmin(password) != 0)
            {
              enviarTitulo();
              printf("A senha digitada esta incorreta\n\n");
              printf("Pressione qualquer tecla para retornar ao menu...\n");
              getch();
              system("cls");

              enviarMenuFuncionario();
            }

            if (validarSenhaAdmin(password) == 0)
            {
              acesso = 1;

              enviarTitulo();
              scanf("%d", &funcionario.codigoFuncionario);
              system("cls");
              // obterEntrada("Digite o nome do funcionario que tera os dados alterados: \n", funcionario.nomeFuncionario, sizeof(funcionario.nomeFuncionario));

              if ((posicao = consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario)) == -1)
              {
                enviarTitulo();
                printf("O funcionario especificado nao foi encontrado.\n");
                printf("Pressione qualquer tecla para voltar ao menu...\n");
                getch();
                system("cls");

                enviarMenuFuncionario();
                return;
              }

              enviarTitulo();
              obterEntrada("Digite o novo nome do funcionario: \n", funcionario_alterado.nomeFuncionario, sizeof(funcionario_alterado.nomeFuncionario));

              enviarTitulo();
              obterEntrada("Digite o novo CPF do funcionario: \n", funcionario_alterado.cpf, sizeof(funcionario_alterado.cpf));

              enviarTitulo();
              printf("Digite o novo codigo do funcionario: \n");
              scanf("%d", &funcionario_alterado.codigoFuncionario);
              system("cls");

              enviarTitulo();
              obterEntrada("Digite o novo cargo do funcionario: \n", funcionario_alterado.cargo, sizeof(funcionario_alterado.cargo));

              enviarTitulo();
              printf("Digite o dia, mes e ano novo do funcionario - 11 22 3333: \n");
              scanf("%d %d %d", &funcionario_alterado.nascimento.dia, &funcionario_alterado.nascimento.mes, &funcionario_alterado.nascimento.ano);
              system("cls");

              enviarTitulo();
              obterEntrada("Digite o novo numero de telefone do funcionario: \n", funcionario_alterado.telefoneContato, sizeof(funcionario_alterado.telefoneContato));

              enviarTitulo();
              obterEntrada("Digite a nova senha do funcionario: \n", funcionario_alterado.senhaFuncionario, sizeof(funcionario_alterado.senhaFuncionario));

              enviarTitulo();
              obterEntrada("Digite o novo endereco do funcionario: \n", funcionario_alterado.endereco.endereco, sizeof(funcionario_alterado.endereco.endereco));

              enviarTitulo();
              obterEntrada("Digite o novo CEP do funcionario: \n", funcionario_alterado.endereco.cep, sizeof(funcionario_alterado.endereco.cep));

              enviarTitulo();
              obterEntrada("Digite o novo bairro do funcionario: \n", funcionario_alterado.endereco.bairro, sizeof(funcionario_alterado.endereco.bairro));

              enviarTitulo();
              obterEntrada("Digite a nova cidade do funcionario: \n", funcionario_alterado.endereco.cidade, sizeof(funcionario_alterado.endereco.cidade));

              enviarTitulo();
              obterEntrada("Digite o novo estado do funcionario: \n", funcionario_alterado.endereco.estado, sizeof(funcionario_alterado.endereco.estado));

              alterarFuncionario(file, funcionario, funcionario_alterado);
            }
          } while (acesso == 0);
          break;

        case 3:
          do
          {
            acesso = 0;

            enviarTitulo();
            obterEntrada("Digite a senha de administrador: \n", password, sizeof(password));

            if (validarSenhaAdmin(password) != 0)
            {
              enviarTitulo();
              printf("A senha digitada esta incorreta.\n");
              printf("Pressione qualquer tecla para tentar novamente.\n");
              getch();
              system("cls");
              enviarMenuFuncionario();
            }

            if (validarSenhaAdmin(password) == 0)
            {
              enviarTitulo();
              obterEntrada("Digite o nome do cliente que tera os dados alterados: \n", cliente.nome, sizeof(cliente.nome));

              if ((posicao = consultarClientePorCodigo(fileClientes, cliente.numDaConta)) == -1)
              {
                enviarTitulo();
                printf("O cliente especificado nao foi encontrado.\n");
                printf("Pressione qualquer tecla para voltar ao menu...\n");
                getch();
                system("cls");

                enviarMenuFuncionario();
                return;
              }

              fseek(fileClientes, posicao * sizeof(cliente), SEEK_SET);
              fread(&cliente, sizeof(cliente), 1, fileClientes);

              enviarTitulo();
              obterEntrada("Digite o novo nome do cliente: \n", cliente_alterado.nome, sizeof(cliente_alterado.nome));

              enviarTitulo();
              printf("Digite o novo numero da agencia: \n");
              scanf("%d", &cliente_alterado.agencia);
              system("cls");

              enviarTitulo();
              printf("Digite o novo numero da conta: \n");
              scanf("%d", &cliente_alterado.numDaConta);
              system("cls");

              if (strcmp(cliente.tipoConta, "CC") == 0)
              {
                enviarTitulo();
                printf("Digite o novo limite da conta: \n");
                scanf("%f", &cliente_alterado.limiteDaConta);
                system("cls");
              }

              enviarTitulo();
              obterEntrada("Digite o novo numero de CPF do cliente: \n", cliente_alterado.cpf, sizeof(cliente_alterado.cpf));

              enviarTitulo();
              printf("Digite o dia, mes e ano da nova data de nascimento do cliente - 11 22 3333: \n");
              scanf("%d %d %d", &cliente_alterado.nascimento.dia, &cliente_alterado.nascimento.mes, &cliente_alterado.nascimento.ano);
              system("cls");

              if (strcmp(cliente.tipoConta, "CC") == 0)
              {
                enviarTitulo();
                printf("Digite o dia, mes e ano da data de vencimento nova do cliente - 11 22 3333: \n");
                scanf("%d %d %d", &cliente_alterado.vencimento.dia, &cliente_alterado.vencimento.mes, &cliente_alterado.vencimento.ano);
                system("cls");
              }

              enviarTitulo();
              obterEntrada("Digite o novo numero de telefone do cliente: \n", cliente_alterado.telefone, sizeof(cliente_alterado.telefone));

              enviarTitulo();
              obterEntrada("Digite o novo endereco do cliente: \n", cliente_alterado.endereco.endereco, sizeof(cliente_alterado.endereco.endereco));

              enviarTitulo();
              obterEntrada("Digite o novo CEP do cliente: \n", cliente_alterado.endereco.cep, sizeof(cliente_alterado.endereco.cep));

              enviarTitulo();
              obterEntrada("Digite o novo bairro do cliente: \n", cliente_alterado.endereco.bairro, sizeof(cliente_alterado.endereco.bairro));

              enviarTitulo();
              obterEntrada("Digite a nova cidade do cliente: \n", cliente_alterado.endereco.cidade, sizeof(cliente_alterado.endereco.cidade));

              enviarTitulo();
              obterEntrada("Digite o novo estado do cliente: \n", cliente_alterado.endereco.estado, sizeof(cliente_alterado.endereco.estado));

              enviarTitulo();
              printf("O cliente possui R$%.2f em sua conta, digite o mesmo valor para manter ou outro valor para alterar: \n", cliente.saldo);
              scanf("%f", &cliente_alterado.saldo);
              system("cls");

              enviarTitulo();
              obterEntrada("Digite a nova senha do cliente: \n", cliente_alterado.senha, sizeof(cliente_alterado.senha));

              enviarTitulo();
              printf("Digite o novo tipo de conta do cliente: \n");
              obterEntrada("Utilize as siglas: Conta Poupanca (CP) e Conta Corrente (CC): \n", cliente_alterado.tipoConta, sizeof(cliente_alterado.tipoConta));

              alterarCliente(fileClientes, cliente, cliente_alterado);
            }

          } while (acesso == 0);
          break;

        case 4:
          enviarMenuFuncionario();
          break;

        default:
          enviarTitulo();
          printf("Voce selecionou uma opcao invalida.\n");
          printf("Pressione qualquer tecla para tentar novamente...\n");
          getch();
          system("cls");

          enviarMenuFuncionario();
        }
      } while (option <= 0 || option >= 5);

      break;

    case 5:
      enviarTitulo();
      obterEntrada("Digite o nome do funcionario: \n", funcionario.nomeFuncionario, sizeof(funcionario.nomeFuncionario));

      enviarTitulo();
      printf("Digite o codigo do funcionario: \n");
      scanf("%d", &funcionario.codigoFuncionario);
      system("cls");

      enviarTitulo();
      obterEntrada("Digite o cargo do funcionario: \n", funcionario.cargo, sizeof(funcionario.cargo));

      enviarTitulo();
      obterEntrada("Digite o CPF do funcionario no formato (000.000.000-00): \n", funcionario.cpf, sizeof(funcionario.cpf));

      enviarTitulo();
      printf("Digite o dia, mes e ano - 11 22 3333: \n");
      scanf("%d %d %d", &funcionario.nascimento.dia, &funcionario.nascimento.mes, &funcionario.nascimento.ano);
      system("cls");

      enviarTitulo();
      obterEntrada("Digite o telefone para contato: \n", funcionario.telefoneContato, sizeof(funcionario.telefoneContato));

      enviarTitulo();
      obterEntrada("Digite o endereco do funcionario (Maximo de 45 caracteres): \n", funcionario.endereco.endereco, sizeof(funcionario.endereco.endereco));

      enviarTitulo();
      obterEntrada("Digite o CEP do funcionario no formato (00000-000): \n", funcionario.endereco.cep, sizeof(funcionario.endereco.cep));

      enviarTitulo();
      obterEntrada("Digite o bairro do funcionario: \n", funcionario.endereco.bairro, sizeof(funcionario.endereco.bairro));

      enviarTitulo();
      obterEntrada("Digite a cidade do funcionario: \n", funcionario.endereco.cidade, sizeof(funcionario.endereco.cidade));

      enviarTitulo();
      obterEntrada("Digite o estado do funcionario (Coloque em sigla: ex: DF): \n", funcionario.endereco.estado, sizeof(funcionario.endereco.estado));

      do
      {
        enviarTitulo();
        obterEntrada("Digite a senha do funcionario (Maximo de 16 caracteres): \n", funcionario.senhaFuncionario, sizeof(funcionario.senhaFuncionario));

        if (strlen(funcionario.senhaFuncionario) == 0)
        {
          printf("Voce deve digitar uma senha para continuar.\n");
          system("cls");
        }
        else if (strlen(funcionario.senhaFuncionario) > 16)
        {
          printf("A senha excede o limite de 16 caracteres.\n");
          printf("Pressione qualquer tecla para tentar novamente...\n");
          system("cls");
        }
      } while (strlen(funcionario.senhaFuncionario) == 0 || strlen(funcionario.senhaFuncionario) > 16);

      inserirFuncionario(file, funcionario);
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

      enviarMenuFuncionario();
      break;
    }

  } while (option <= 0 || option > 7);

  fclose(file);
}

int consultarFuncionarioPorCodigo(FILE *file, int codigoFuncionario)
{
  Funcionario funcionario_lido;
  int posicao = 0;

  fseek(file, 0L, SEEK_SET);
  while (fread(&funcionario_lido, sizeof(Funcionario), 1, file))
  {
    if (funcionario_lido.codigoFuncionario == codigoFuncionario && funcionario_lido.excluido == 0)
      return posicao;

    posicao++;
  }
  return -1;
}

int inserirFuncionario(FILE *file, Funcionario funcionario)
{
  if (consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario) != -1)
  {
    printf("Funcionario com este codigo ja existe.\n");
    return -1;
  }

  fseek(file, 0, SEEK_END);
  funcionario.excluido = 0; // Garante que o campo "excluido" seja 0 para novos registros
  fwrite(&funcionario, sizeof(Funcionario), 1, file);
  printf("Funcionario cadastrado com sucesso.\n");
  return 0;
}

void mostrarDadosFuncionario(FILE *file, int posicao)
{
  Funcionario funcionario;

  fseek(file, posicao * sizeof(Funcionario), SEEK_SET);
  fread(&funcionario, sizeof(Funcionario), 1, file);

  printf("Codigo: %d\nNome: %s\nCargo: %s\nCPF: %s\nData de Nascimento: %d/%d/%d\nTelefone: %s\nEndereco: %s\nCEP: %s\nBairro: %s\nCidade: %s\nEstado: %s\n",
         funcionario.codigoFuncionario, funcionario.nomeFuncionario, funcionario.cargo, funcionario.cpf,
         funcionario.nascimento.dia, funcionario.nascimento.mes, funcionario.nascimento.ano,
         funcionario.telefoneContato, funcionario.endereco.endereco, funcionario.endereco.cep,
         funcionario.endereco.bairro, funcionario.endereco.cidade, funcionario.endereco.estado);
}

int excluirFuncionario(FILE *file, Funcionario funcionario)
{
  int posicao = consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario);

  if (posicao == -1)
  {
    printf("Funcionario nao encontrado.\n");
    return -1;
  }

  fseek(file, posicao * sizeof(Funcionario), SEEK_SET);
  funcionario.excluido = 1;
  fwrite(&funcionario, sizeof(Funcionario), 1, file);
  printf("Funcionario excluido com sucesso.\n");
  return 0;
}

void validarSenhaFuncionario(FILE *file, Funcionario funcionario)
{
  int acesso;
  int posicao;

  char password[DEFAULT_PASS_SIZE];
  const char *passwordAdm = "adm";

  do
  {
    acesso = 0;

    if ((posicao = consultarFuncionarioPorCodigo(file, funcionario.codigoFuncionario)) != -1)
    {
      fseek(file, posicao * sizeof(Funcionario), SEEK_SET);
      fread(&funcionario, sizeof(Funcionario), 1, file);

      obterEntrada("Digite a senha: \n", password, sizeof(password));

      if (strcmp(password, funcionario.senhaFuncionario) == 0)
      {
        acesso = 1;
        printf("Autenticado(a) com sucesso.\n");
        system("cls");
        // Chamar função de menu de funcionário aqui, se necessário
        return;
      }
      else if (strcmp(password, passwordAdm) == 0)
      {
        acesso = 1;
        printf("Autenticado(a) utilizando a senha de administrador.\n");
        system("cls");
        // Chamar função de menu de funcionário aqui, se necessário
        return;
      }
      else
      {
        printf("A senha digitada esta incorreta.\n");
        printf("Pressione qualquer tecla para tentar novamente...\n");
        getch();
        system("cls");
        // Redirecionar ao menu principal, se necessário
      }
    }
  } while (acesso == 0);
}

int alterarFuncionario(FILE *file, Funcionario funcionario_antigo, Funcionario funcionario_novo)
{
  int posicao;

  if (file != NULL)
  {
    if ((posicao = consultarFuncionarioPorCodigo(file, funcionario_antigo.codigoFuncionario)) != -1)
    {
      fseek(file, posicao * sizeof(Funcionario), SEEK_SET);

      fread(&funcionario_antigo, sizeof(funcionario_antigo), 1, file);

      strcpy(funcionario_antigo.nomeFuncionario, funcionario_novo.nomeFuncionario);
      strcpy(funcionario_antigo.cpf, funcionario_novo.cpf);
      funcionario_antigo.codigoFuncionario = funcionario_novo.codigoFuncionario;
      strcpy(funcionario_antigo.cargo, funcionario_novo.cargo);
      funcionario_antigo.nascimento.dia = funcionario_novo.nascimento.dia;
      funcionario_antigo.nascimento.mes = funcionario_novo.nascimento.mes;
      funcionario_antigo.nascimento.ano = funcionario_novo.nascimento.ano;
      strcpy(funcionario_antigo.telefoneContato, funcionario_novo.telefoneContato);
      strcpy(funcionario_antigo.senhaFuncionario, funcionario_novo.senhaFuncionario);
      strcpy(funcionario_antigo.endereco.endereco, funcionario_novo.endereco.endereco);
      strcpy(funcionario_antigo.endereco.cep, funcionario_novo.endereco.cep);
      strcpy(funcionario_antigo.endereco.bairro, funcionario_novo.endereco.bairro);
      strcpy(funcionario_antigo.endereco.cidade, funcionario_novo.endereco.cidade);
      strcpy(funcionario_antigo.endereco.estado, funcionario_novo.endereco.estado);

      fseek(file, posicao * sizeof(Funcionario), SEEK_SET);

      fwrite(&funcionario_antigo, sizeof(funcionario_novo), 1, file);

      enviarTitulo();
      printf("Os dados deste funcionario foram alterados com sucesso.\n");
      getch();
      system("cls");

      fclose(file);

      enviarMenuFuncionario();
      return 1;
    }
  }
  return 0;
}