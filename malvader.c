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

void enviarMenuPrincipal()
{
  // Inicialização do arquivo e do registro.
  FILE *file;
  Funcionario funcionario;

  // Inicialização do arquivo e do registro.
  FILE *fileCliente;
  Cliente cliente;

  // Variáveis de ação do programa.
  int option, posicao;

  // Tenta realizar a abertura do arquivo de funcionários e de clientes no modo leitura/escrita.
  file = fopen("funcionarios.txt", "r+");
  fileCliente = fopen("clientes.txt", "r+");

  // Verifica se o arquivo de funcionários não existe.
  if (file == NULL)
  {
    printf("Arquivo de funcionarios nao foi encontrado, recriando o arquivo...\n");
    file = fopen("funcionarios.txt", "w+");
  }

  // Verifica se o arquivo de clientes não existe.
  if (fileCliente == NULL)
  {
    printf("Arquivo de clientes nao foi encontrado, recriando o arquivo...\n");
    fileCliente = fopen("clientes.txt", "w+");
  }

  do
  {
    enviarTitulo();
    printf("Escolha uma opcao do menu principal: \n\n");
    printf("1) Funcionario\n");
    printf("2) Cliente\n");
    printf("3) Sair\n\n");
    scanf("%d", &option);
    system("cls");

    switch (option)
    {
    case 1:

      // Recebe o nome do funcionário para comparação no arquivo.
      enviarTitulo();
      printf("Digite o nome do funcionario: \n");
      // Limpa o buffer do teclado
      fflush(stdin);
      // Recebe a string digitada pelo usuário contendo o nome do funcionário.
      gets(funcionario.nomeFuncionario);
      // Limpa as últimas mensagens enviadas.
      system("cls");

      // Verifica se o nome do funcionário informado é "admin". Usuário administrativo.
      if (strcmp(funcionario.nomeFuncionario, "admin") == 0)
      {
        // Envia o menu de funcionários sem senha caso o usuário seja administrador.
        char password[DEFAULT_PASS_SIZE];

        enviarTitulo();
        printf("Digite a senha de administrador: \n");
        // Limpa o buffer do teclado.
        fflush(stdin);
        // Recebe a senha digitada pelo usuário.
        gets(password);
        system("cls");

        // Verifica se caso a senha foi digitada corretamente.
        if (validarSenhaAdmin(password) == 0)
        {
          // O acesso é liberado e o usuário será direcionado ao menu de funcionário.
          enviarMenuFuncionario();
        }
        // Verifica se caso a senha foi digitada incorretamente.
        else if (validarSenhaAdmin(password) != 0)
        {
          enviarTitulo();
          printf("A senha informada nao e valida.\n\n");
          printf("Pressione qualquer tecla para voltar ao menu...\n");
          getch();
          system("cls");

          // Ao pressionar qualquer tecla o usuário é movido para o menu principal novamente.
          enviarMenuPrincipal();
        }

        return;
      }

      // Verifica a existência do funcionário dentro do arquivo.
      if ((posicao = consultarFuncionario(file, funcionario)) == -1)
      {
        enviarTitulo();
        printf("O funcionario informado nao existe.\n");
        printf("Pressione qualquer tecla para tentar novamente...\n");
        // Realiza uma pausa até que o usuário pressione qualquer tecla.
        getch();
        system("cls");

        // Ao pressionar qualquer tecla o usuário será movido de volta ao menu principal.
        enviarMenuPrincipal();
        return;
      }

      // Requisita a função para validação da senha do funcionário.
      validarSenhaFuncionario(file, funcionario);
      break;

    case 2:
      enviarTitulo();
      printf("Digite o nome do cliente: \n");
      // Limpa o buffer do teclado
      fflush(stdin);
      // Recebe o nome do cliente em string.
      gets(cliente.nome);
      system("cls");

      // Verifica a existência do cliente nos arquivos.
      if ((posicao = consultarCliente(fileCliente, cliente)) == -1)
      {
        // Envia a resposta do programa para o usuário.
        enviarTitulo();
        printf("O cliente informado nao existe.\n");
        printf("Pressione qualquer tecla para tentar novamente...\n");
        getch();
        system("cls");

        // Ao pressionar qualquer tecla o usuário será movido de volta ao menu principal.
        enviarMenuPrincipal();
        return;
      }

      // Requisita a função para validação da senha do cliente.
      validarSenhaCliente(fileCliente, cliente);
      break;

    case 3:
      enviarTitulo();
      printf("Saindo do programa...");
      // Encerra o programa retornando 1.
      exit(1);
      system("cls");
      break;

      // Caso o usuario digite algo que não seja aceito ou que não exista
    default:
      enviarTitulo();
      printf("Voce selecionou uma opcao invalida.\n");
      printf("Pressione qualquer tecla para tentar novamente...\n");
      getch();
      system("cls");

      // Ao pressionar qualquer tecla o usuário será redirecionado ao menu principal.
      enviarMenuPrincipal();
      break;
    }

    // Fecha os arquivos que foram abertos anteriormente.
    fclose(file);
    fclose(fileCliente);
    // O bloco de código acima será executado enquanto a opção não for (1, 2 ou 3)
  } while (option <= 0 || option > 3);

  fclose(file);
  fclose(fileCliente);
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

void enviarMenuAberturaConta()
{
  FILE *file = fopen("clientes.txt", "r+");

  Cliente cliente;

  if (file == NULL)
  {
    printf("Arquivo nao encontrado, tentando gerar um novo...\n");
    file = fopen("clientes.txt", "w+");
  }

  int option;

  if (file != NULL)
  {
    do
    {
      enviarTitulo();
      printf("Menu funcionario:\n\n");
      printf("1) Conta Poupanca\n");
      printf("2) Conta Corrente\n");
      printf("3) Voltar\n\n");
      scanf("%d", &option);
      system("cls");

      switch (option)
      {
      case 1:
        enviarTitulo();
        printf("Informe o nome do cliente: \n");
        fflush(stdin);
        fgets(cliente.nome, sizeof(cliente.nome), stdin);
        system("cls");

        enviarTitulo();
        printf("Informe o numero da agencia do cliente: \n");
        scanf("%d", &cliente.agencia);
        system("cls");

        enviarTitulo();
        printf("Informe o numero da conta do cliente: \n");
        scanf("%d", &cliente.numDaConta);
        system("cls");

        enviarTitulo();
        printf("Informe o numero do CPF do cliente: \n");
        fflush(stdin);
        gets(cliente.cpf);
        system("cls");

        enviarTitulo();
        printf("Informe a data de nascimento do cliente seguindo o padrao: 30 10 2000\n");
        scanf("%d %d %d", &cliente.nascimento.dia, &cliente.nascimento.mes, &cliente.nascimento.ano);
        system("cls");

        enviarTitulo();
        printf("Informe o numero de telefone do cliente: \n");
        fflush(stdin);
        gets(cliente.telefone);
        system("cls");

        enviarTitulo();
        printf("Informe o endereco do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.endereco);
        system("cls");

        enviarTitulo();
        printf("Informe o CEP do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.cep);
        system("cls");

        enviarTitulo();
        printf("Informe o bairro do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.bairro);
        system("cls");

        enviarTitulo();
        printf("Informe a cidade do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.cidade);
        system("cls");

        enviarTitulo();
        printf("Informe o estado do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.estado);
        system("cls");

        enviarTitulo();
        printf("Informe o saldo inicial do cliente: \n");
        scanf("%f", &cliente.saldo);
        system("cls");

        enviarTitulo();
        printf("Confirme que esta criando uma conta poupanca \n");
        printf("Digite 'CP' no campo abaixo para continuar: \n");
        fflush(stdin);
        gets(cliente.tipoConta);
        system("cls");

        enviarTitulo();
        printf("Informe a senha do cliente: \n");
        fflush(stdin);
        gets(cliente.senha);
        system("cls");

        inserirCliente(file, cliente);
        break;

      case 2:
        enviarTitulo();
        printf("Informe o nome do cliente: \n");
        fflush(stdin);
        gets(cliente.nome);
        system("cls");

        enviarTitulo();
        printf("Informe o numero da agencia do cliente: \n");
        scanf("%d", &cliente.agencia);
        system("cls");

        enviarTitulo();
        printf("Informe o numero da conta do cliente: \n");
        scanf("%d", &cliente.numDaConta);
        system("cls");

        enviarTitulo();
        printf("Informe o limite da conta do cliente: \n");
        scanf("%f", &cliente.limiteDaConta);
        system("cls");

        enviarTitulo();
        printf("Informe o numero do CPF do cliente: \n");
        fflush(stdin);
        gets(cliente.cpf);
        system("cls");

        enviarTitulo();
        printf("Informe a data de nascimento do cliente seguindo o padrao: 30 10 2000\n");
        scanf("%d %d %d", &cliente.nascimento.dia, &cliente.nascimento.mes, &cliente.nascimento.ano);
        system("cls");

        enviarTitulo();
        printf("Informe a data de vencimento da conta do cliente seguindo o padrao: 30 10 2000\n");
        scanf("%d %d %d", &cliente.vencimento.dia, &cliente.vencimento.mes, &cliente.vencimento.ano);
        system("cls");

        enviarTitulo();
        printf("Informe o numero de telefone do cliente: \n");
        fflush(stdin);
        gets(cliente.telefone);
        system("cls");

        enviarTitulo();
        printf("Informe o endereco do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.endereco);
        system("cls");

        enviarTitulo();
        printf("Informe o CEP do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.cep);
        system("cls");

        enviarTitulo();
        printf("Informe o bairro do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.bairro);
        system("cls");

        enviarTitulo();
        printf("Informe a cidade do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.cidade);
        system("cls");

        enviarTitulo();
        printf("Informe o estado do cliente: \n");
        fflush(stdin);
        gets(cliente.endereco.estado);
        system("cls");

        enviarTitulo();
        printf("Informe o saldo inicial do cliente: \n");
        scanf("%f", &cliente.saldo);
        system("cls");

        enviarTitulo();
        printf("Confirme que esta criando uma conta corrente \n");
        printf("Digite 'CC' no campo abaixo para continuar: \n");
        fflush(stdin);
        gets(cliente.tipoConta);
        system("cls");

        enviarTitulo();
        printf("Informe a senha do cliente: \n");
        fflush(stdin);
        gets(cliente.senha);
        system("cls");

        inserirCliente(file, cliente);
        break;

      case 3:
        enviarMenuFuncionario();
        break;

      default:
        enviarTitulo();
        printf("Voce selecionou uma opcao invalida.\n");
        printf("Pressione qualquer tecla para tentar novamente...\n");
        getch();
        system("cls");

        enviarMenuAberturaConta();
      }
    } while (option <= 0 || option > 3);
  }
}

void formatarTipoConta(Cliente cliente)
{
  if (strcmp(cliente.tipoConta, "CP") == 0)
  {
    printf("Tipo de conta: Conta Poupanca\n");
  }
  else if (strcmp(cliente.tipoConta, "CC") == 0)
  {
    printf("Tipo de conta: Conta Corrente\n");
  }
  else
  {
    printf("Tipo de conta: Indefinida\n");
  }
}
