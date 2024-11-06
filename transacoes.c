#include "clientes.h"
#include "malvader.h"
#include "funcionarios.h"
#include "transacoes.h"

int criarMovimento(Cliente cliente, char tipo[15], double valor)
{
  Transacao transacao;
  FILE *file;

  mkdir("movimentos");

  char path[256];
  snprintf(path, 256, "movimentos/%s.txt", cliente.nome);

  file = fopen(path, "a+");

  if (file == NULL)
  {
    file = fopen(path, "a+");
  }

  transacao.valor = valor;

  strcpy(transacao.tipo, tipo);

  strcpy(transacao.nome, cliente.nome);

  fprintf(file, "%s ", transacao.nome);
  fprintf(file, "%s ", transacao.tipo);
  fprintf(file, "%.2lf", transacao.valor);
  fprintf(file, "\n");

  fclose(file);

  FILE *origem, *destino;

  origem = fopen(path, "r");

  if (origem == NULL)
  {
    printf("Nao foi possível abrir o arquivo de origem.\n");
    return -1;
  }

  destino = fopen("extrato.txt", "w");

  if (destino == NULL)
  {
    printf("Nao foi possível abrir o arquivo de destino.\n");
    return -1;
  }

  char line[256];

  while (fgets(line, sizeof(line), origem))
  {
    sscanf(line, "%s %s %f", transacao.nome, transacao.tipo, &transacao.valor);

    fprintf(destino, "%s %s %.2f\n", transacao.nome, transacao.tipo, transacao.valor);
  }

  fclose(origem);
  fclose(destino);

  return 0;
}
