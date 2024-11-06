#ifndef MALVADER_H
#define MALVADER_H

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>

#define DEFAULT_PASS_SIZE 16

typedef struct
{
  int dia;
  int mes;
  int ano;
} Data;

typedef struct
{
  char endereco[45];
  char cep[10];
  char bairro[20];
  char cidade[20];
  char estado[2];
} Endereco;

typedef struct
{
  char nome[25];
  int agencia;
  int numDaConta;
  float limiteDaConta;
  char cpf[15];
  Data nascimento;
  Data vencimento;
  char telefone[14];
  Endereco endereco;
  char senha[DEFAULT_PASS_SIZE];
  float saldo;
  char tipoConta[4];
  char excluido;
} Cliente;

typedef struct
{
  char nomeFuncionario[25];
  char cpf[14];
  int codigoFuncionario;
  char cargo[25];
  Data nascimento;
  char telefoneContato[15];
  char senhaFuncionario[DEFAULT_PASS_SIZE];
  Endereco endereco;
  char excluido;
} Funcionario;

typedef struct
{
  char nome[25];
  char tipo[15];
  float valor;
} Transacao;

void enviarTitulo();
void enviarMenuPrincipal();
int validarSenhaAdmin(char *senhaDigitada);
void enviarMenuAberturaConta();
void formatarTipoConta(Cliente cliente);

#endif
