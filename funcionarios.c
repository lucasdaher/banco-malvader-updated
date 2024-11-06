#include "clientes.h"
#include "malvader.h"
#include "funcionarios.h"
#include "transacoes.h"

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

      // Encerramento de contas
    case 2:
      do
      {
        // Recebe a opção informada pelo usuário
        enviarTitulo();
        printf("Encerramento de conta\n\n");
        printf("1) Funcionario\n");
        printf("2) Cliente\n");
        printf("3) Voltar\n\n");
        scanf("%d", &option);
        system("cls");

        switch (option)
        {
          // Encerrar uma conta de funcionário
        case 1:
          enviarTitulo();
          printf("Digite o nome do funcionario que tera a conta encerrada: \n");
          fflush(stdin);
          gets(funcionario.nomeFuncionario);
          system("cls");

          if ((posicao = consultarFuncionario(file, funcionario)) == -1)
          {
            // Envia a resposta da consulta para o usuário.
            enviarTitulo();
            printf("O funcionario informado nao existe...\n");
            printf("Pressione qualquer tecla para voltar ao menu...\n");
            getch();
            system("cls");

            // Ao pressionar qualquer tecla o usuário voltará ao menu de funcionários
            enviarMenuFuncionario();
            return;
          }

          // Requisita a função que exclui um funcionário
          excluirFuncionario(file, funcionario);
          break;

        // Encerrar uma conta de cliente
        case 2:
          enviarTitulo();
          printf("Digite o nome do cliente que tera a conta encerrada: \n");
          fflush(stdin);
          gets(cliente.nome);
          system("cls");

          if ((posicao = consultarCliente(fileClientes, cliente)) == -1)
          {
            // Envia a resposta da consulta para o usuário.
            enviarTitulo();
            printf("O cliente informado nao existe...\n");
            printf("Pressione qualquer tecla para voltar ao menu...\n");
            getch();
            system("cls");

            // Ao pressionar qualquer tecla o usuário voltará ao menu de funcionários
            enviarMenuFuncionario();
            return;
          }

          // Requisita a função que exclui um cliente
          excluirCliente(fileClientes, cliente);
          break;

        case 3:
          // Retorna o usuário para o menu de funcionários.
          enviarMenuFuncionario();
          break;

        default:
          break;
        }
      } while (option <= 0 || option > 3);
      break;

      // Consulta de dados
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
          fflush(stdin);
          printf("Digite o nome do funcionario desejado: \n");
          // Recebe o nome do funcionário que foi informado.
          gets(funcionario.nomeFuncionario);
          system("cls");

          // Verifica se o funcionário existe.
          if ((posicao = consultarFuncionario(file, funcionario)) == -1)
          {
            // Envia a resposta do programa para o usuário.
            enviarTitulo();
            printf("O funcionario nao foi encontrado.\n");
            printf("Pressione qualquer tecla para voltar ao menu.\n");
            getch();
            system("cls");
            enviarMenuFuncionario();
          }

          if ((posicao = consultarFuncionario(file, funcionario)) != -1)
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

          if ((posicao = consultarCliente(fileClientes, cliente)) == -1)
          {
            enviarTitulo();
            printf("O cliente especificado nao foi encontrado...\n");
            printf("Pressione qualquer tecla para retornar ao menu.\n");
            getch();
            system("cls");

            enviarMenuFuncionario();
            return;
          }

          if ((posicao = consultarCliente(fileClientes, cliente)) != -1)
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
          // Criar funcionalidade que altera o tipo de conta de um cliente.
          // Conta Poupança = CP | Conta Corrente = CC
          break;

          // Alterar dados de um funcionário.
        case 2:

          do
          {
            // Acesso bloqueado enquanto o usuário não se autenticar.
            acesso = 0;

            enviarTitulo();
            printf("Digite a senha de administrador: \n");
            fflush(stdin);
            gets(password);
            system("cls");

            // Faz a verificação se a senha digitada é válida como (Admin || Funcionário)
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
              printf("Digite o nome do funcionario que tera os dados alterados: \n");
              fflush(stdin);
              gets(funcionario.nomeFuncionario);
              system("cls");

              if ((posicao = consultarFuncionario(file, funcionario)) == -1)
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
              printf("Digite o novo nome do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.nomeFuncionario);
              system("cls");

              enviarTitulo();
              printf("Digite o novo CPF do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.cpf);
              system("cls");

              enviarTitulo();
              printf("Digite o novo codigo do funcionario: \n");
              scanf("%d", &funcionario_alterado.codigoFuncionario);
              system("cls");

              enviarTitulo();
              printf("Digite o novo cargo do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.cargo);
              system("cls");

              enviarTitulo();
              printf("Digite o dia, mes e ano novo do funcionario - 11 22 3333: \n");
              scanf("%d %d %d", &funcionario_alterado.nascimento.dia, &funcionario_alterado.nascimento.mes, &funcionario_alterado.nascimento.ano);
              system("cls");

              enviarTitulo();
              printf("Digite o novo numero de telefone do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.telefoneContato);
              system("cls");

              enviarTitulo();
              printf("Digite a nova senha do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.senhaFuncionario);
              system("cls");

              enviarTitulo();
              printf("Digite o novo endereco do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.endereco.endereco);
              system("cls");

              enviarTitulo();
              printf("Digite o novo CEP do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.endereco.cep);
              system("cls");

              enviarTitulo();
              printf("Digite o novo bairro do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.endereco.bairro);
              system("cls");

              enviarTitulo();
              printf("Digite a nova cidade do funcionario: \n");
              fflush(stdin);
              gets(funcionario_alterado.endereco.cidade);
              system("cls");

              enviarTitulo();
              printf("Digite o novo estado do funcionario (Ex.: DF): \n");
              fflush(stdin);
              gets(funcionario_alterado.endereco.estado);
              system("cls");

              // Requisita a função que altera os dados de um funcionário.
              alterarFuncionario(file, funcionario, funcionario_alterado);
            }
          } while (acesso == 0);
          break;

        // Alterar dados de um cliente.
        case 3:
          do
          {
            acesso = 0;

            enviarTitulo();
            printf("Digite a senha de administrador: \n");
            fflush(stdin);
            gets(password);
            system("cls");

            // Faz a verificação se a senha digitada é válida como (Admin || Funcionário)
            if (validarSenhaAdmin(password) != 0)
            {
              enviarTitulo();
              printf("A senha digitada esta incorreta.\n");
              printf("Pressione qualquer tecla para tentar novamente.\n");
              getch();
              system("cls");
              enviarMenuFuncionario();
            }

            // Se a senha digitada for a senha correta, o usuario recebe o menu de funcionários.
            if (validarSenhaAdmin(password) == 0)
            {
              enviarTitulo();
              printf("Digite o nome do cliente que tera os dados alterados: \n");
              fflush(stdin);
              gets(cliente.nome);
              system("cls");

              if ((posicao = consultarCliente(fileClientes, cliente)) == -1)
              {
                enviarTitulo();
                printf("O cliente especificado nao foi encontrado.\n");
                printf("Pressione qualquer tecla para voltar ao menu...\n");
                getch();
                system("cls");

                // Enviar o menu de funcionários.
                enviarMenuFuncionario();
                return;
              }

              fseek(fileClientes, posicao * sizeof(cliente), SEEK_SET);
              fread(&cliente, sizeof(cliente), 1, fileClientes);

              // Dados do cliente que serão alterados devem estar abaixo dessa linha.
              enviarTitulo();
              printf("Digite o novo nome do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.nome);
              system("cls");

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
              printf("Digite o novo numero de CPF: \n");
              fflush(stdin);
              gets(cliente_alterado.cpf);
              system("cls");

              enviarTitulo();
              printf("Digite o dia, mes e ano da data de nascimento nova do cliente - 11 22 3333: \n");
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
              printf("Digite o novo numero de telefone do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.telefone);
              system("cls");

              enviarTitulo();
              printf("Digite o novo endereco do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.endereco.endereco);
              system("cls");

              enviarTitulo();
              printf("Digite o novo CEP do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.endereco.cep);
              system("cls");

              enviarTitulo();
              printf("Digite o novo bairro do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.endereco.bairro);
              system("cls");

              enviarTitulo();
              printf("Digite o novo cidade do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.endereco.cidade);
              system("cls");

              enviarTitulo();
              printf("Digite o novo estado do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.endereco.estado);
              system("cls");

              enviarTitulo();
              printf("O cliente possui R$%.2f em sua conta, digite o mesmo valor para manter ou outro valor para alterar: \n", cliente.saldo);
              scanf("%f", &cliente_alterado.saldo);
              system("cls");

              enviarTitulo();
              printf("Digite a nova senha do cliente: \n");
              fflush(stdin);
              gets(cliente_alterado.senha);
              system("cls");

              enviarTitulo();
              printf("Digite o novo tipo de conta do cliente: \n");
              printf("Utilize as siglas: Conta Poupanca (CP) e Conta Corrente (CC): \n");
              fflush(stdin);
              gets(cliente_alterado.tipoConta);
              system("cls");

              // Envia os dados coletados para a função que altera os dados de um cliente.
              alterarCliente(fileClientes, cliente, cliente_alterado);
            }

          } while (acesso == 0);
          break;

        default:
          enviarTitulo();
          printf("Voce selecionou uma opcao invalida.\n");
          printf("Pressione qualquer tecla para tentar novamente...\n");
          getch();
          system("cls");

          enviarMenuFuncionario();
        }
      } while (option <= 0 || option > 4);

      break;

      // Cadastrar funcionário
    case 5:
      enviarTitulo();
      printf("Digite o nome do funcionario: \n");
      fflush(stdin);
      gets(funcionario.nomeFuncionario);
      system("cls");

      enviarTitulo();
      printf("Digite o codigo do funcionario: \n");
      fflush(stdin);
      scanf("%d", &funcionario.codigoFuncionario);
      system("cls");

      enviarTitulo();
      printf("Digite o cargo do funcionario: \n");
      fflush(stdin);
      gets(funcionario.cargo);
      system("cls");

      enviarTitulo();
      printf("Digite o CPF do funcionario no formato (000.000.000-00): \n");
      fflush(stdin);
      gets(funcionario.cpf);
      system("cls");

      enviarTitulo();
      printf("Digite o dia, mes e ano - 11 22 3333: \n");
      scanf("%d %d %d", &funcionario.nascimento.dia, &funcionario.nascimento.mes, &funcionario.nascimento.ano);
      system("cls");

      enviarTitulo();
      printf("Digite o telefone para contato: \n");
      fflush(stdin);
      gets(funcionario.telefoneContato);
      system("cls");

      enviarTitulo();
      printf("Digite o endereco do funcionario (Maximo de 45 caracteres): \n");
      fflush(stdin);
      gets(funcionario.endereco.endereco);
      system("cls");

      enviarTitulo();
      printf("Digite o CEP do funcionario no formato (00000-000): \n");
      fflush(stdin);
      gets(funcionario.endereco.cep);
      system("cls");

      enviarTitulo();
      printf("Digite o bairro do funcionario: \n");
      fflush(stdin);
      gets(funcionario.endereco.bairro);
      system("cls");

      enviarTitulo();
      printf("Digite a cidade do funcionario: \n");
      fflush(stdin);
      gets(funcionario.endereco.cidade);
      system("cls");

      enviarTitulo();
      printf("Digite o estado do funcionario (Coloque em sigla: ex: DF): \n");
      fflush(stdin);
      gets(funcionario.endereco.estado);
      system("cls");

      do
      {
        enviarTitulo();
        printf("Digite a senha do funcionario (Maximo de 16 caracteres): \n");
        fflush(stdin);
        gets(funcionario.senhaFuncionario);
        system("cls");

        if (strlen(funcionario.senhaFuncionario) == 0)
        {
          printf("Voce deve digitar uma senha para continuar.\n");
          system("cls");
        }
        else if (strlen(funcionario.senhaFuncionario) > 16)
        {
          printf("A senha excede o limite de 16 caracteres.\n");
          printf("Pressione qualquer tecla para tentar novamente...\n");
          fflush(stdin);
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

int consultarFuncionario(FILE *file, Funcionario funcionario)
{
  Funcionario funcionario_lido;

  int posicao;

  if (file != NULL)
  {
    fseek(file, 0L, SEEK_SET);

    posicao = 0;

    while (fread(&funcionario_lido, sizeof(funcionario_lido), 1, file))
    {
      if (strcmpi(funcionario_lido.nomeFuncionario, funcionario.nomeFuncionario) == 0 &&
          (funcionario_lido.excluido == 0))
        return posicao;
      posicao++;
    };
  }
  return -1;
}

int inserirFuncionario(FILE *file, Funcionario funcionario)
{
  Funcionario funcionario_lido;

  int posicao;

  if (file != NULL)
  {
    posicao = 0;

    if (consultarFuncionario(file, funcionario))
    {
      fseek(file, 0L, SEEK_SET);

      while (fread(&funcionario_lido, sizeof(funcionario_lido), 1, file))
      {
        if (funcionario_lido.excluido == 1)
          break;
        posicao++;
      };

      fseek(file, posicao * sizeof(funcionario), SEEK_SET);

      funcionario.excluido = 0;

      fwrite(&funcionario, sizeof(funcionario), 1, file);

      enviarTitulo();
      printf("O(a) funcionario(a) foi cadastrado(a) com sucesso.\n");
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

int alterarFuncionario(FILE *file, Funcionario funcionario_antigo, Funcionario funcionario_novo)
{
  int posicao;

  if (file != NULL)
  {
    if ((posicao = consultarFuncionario(file, funcionario_antigo)) != -1)
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

int excluirFuncionario(FILE *file, Funcionario funcionario)
{
  int posicao;

  if (file != NULL)
  {
    if ((posicao = consultarFuncionario(file, funcionario)) != -1)
    {
      fseek(file, posicao * sizeof(funcionario), SEEK_SET);

      funcionario.excluido = 1;

      fwrite(&funcionario, sizeof(funcionario), 1, file);

      enviarTitulo();
      printf("Voce excluiu este funcionario dos registros com sucesso.\n");
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

void validarSenhaFuncionario(FILE *file, Funcionario funcionario)
{
  int acesso;
  int posicao;

  char password[DEFAULT_PASS_SIZE];
  char passwordAdm[DEFAULT_PASS_SIZE] = "adm";

  do
  {
    acesso = 0;

    if ((posicao = consultarFuncionario(file, funcionario)) != -1)
    {
      fseek(file, posicao * sizeof(funcionario), SEEK_SET);

      fread(&funcionario, sizeof(funcionario), 1, file);

      enviarTitulo();
      printf("Digite a senha: \n");
      fflush(stdin);
      gets(password);
      system("cls");

      if (strcmp(password, funcionario.senhaFuncionario) == 0)
      {
        acesso = 1;
        enviarTitulo();
        printf("Autenticado(a) com sucesso.\n");
        system("cls");

        enviarMenuFuncionario();
        return;
      }

      else if (strcmp(password, passwordAdm) == 0)
      {
        acesso = 1;
        enviarTitulo();
        printf("Autenticado(a) utilizando a senha de administrador.\n");
        system("cls");

        enviarMenuFuncionario();
        return;
      }
      else
      {
        acesso = 0;
        enviarTitulo();
        printf("A senha digitada esta incorreta.\n");
        printf("Pressione qualquer tecla para tentar novamente...\n");
        getch();
        system("cls");

        enviarMenuPrincipal();
        return;
      }
    }

  } while (acesso == 0);
}