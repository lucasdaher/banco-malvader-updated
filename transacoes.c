#include "transacoes.h"

int criarMovimento(Cliente cliente, char tipo[15], double valor)
{
  Transacao transacao;
  FILE *file;

  // Cria a pasta de movimentações caso ela não exista.
  mkdir("movimentos");

  // Salva o arquivo com o nome informado a cima em uma pasta movimento.
  char path[256];
  snprintf(path, 256, "movimentos/%s.txt", cliente.nome);

  // Tenta abrir o arquivo.
  file = fopen(path, "a+");

  // Verifica se o arquivo NÃO existe e tenta criar um.
  if (file == NULL)
  {
    // Tenta gerar um novo arquivo para o cliente caso ele não exista.
    file = fopen(path, "a+");
  }

  // Recebe o valor da transação.
  transacao.valor = valor;

  // Define o tipo de transação para saque
  strcpy(transacao.tipo, tipo);

  // Define o nome do cliente da transação com o nome do cliente que realizou a ação.
  strcpy(transacao.nome, cliente.nome);

  // Insere os dados no arquivo
  fprintf(file, "%s ", transacao.nome);
  fprintf(file, "%s ", transacao.tipo);
  fprintf(file, "%.2lf", transacao.valor);
  fprintf(file, "\n");

  // Fecha e salva os dados informados.
  fclose(file);

  // Declaração dos arquivos de origem e destino.
  FILE *origem, *destino;

  // Tenta abrir o arquivo de origem no modo de leitura.
  origem = fopen(path, "r");

  // Verifica se o arquivo NÃO EXISTE.
  if (origem == NULL)
  {
    printf("Nao foi possível abrir o arquivo de origem.\n");
    return -1;
  }

  // Tenta abrir o arquivo de destino no modo de reset.
  destino = fopen("extrato.txt", "w");

  // Verifica se o arquivo NÃO EXISTE.
  if (destino == NULL)
  {
    printf("Nao foi possível abrir o arquivo de destino.\n");
    return -1;
  }

  // Declaração da variável que receberá a linha que será copiada.
  char line[256];

  // Laço que irá receber todas as linhas do arquivo.
  while (fgets(line, sizeof(line), origem))
  {
    // Recebe todos os dados que estão inseridos na linha do arquivo.
    sscanf(line, "%s %s %f", transacao.nome, transacao.tipo, &transacao.valor);

    // Insere os dados recebidos no arquivo de origem para o arquivo de destino.
    fprintf(destino, "%s %s %.2f\n", transacao.nome, transacao.tipo, transacao.valor);
  }

  // Fecha os arquivos
  fclose(origem);
  fclose(destino);

  // Retorna 0 em caso de sucesso.
  return 0;
}
