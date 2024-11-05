#ifndef CLIENTES_H
#define CLIENTES_H

#include "malvader.h"

void menuCliente();
int consultarCliente(FILE *file, Cliente cliente);
int inserirCliente(FILE *file, Cliente cliente);
int alterarCliente(FILE *file, Cliente cliente_antigo, Cliente cliente_novo);
int excluirCliente(FILE *file, Cliente cliente);
void validarSenhaCliente(FILE *file, Cliente cliente);
void saldo(Cliente cliente);
void depositar(Cliente cliente);
void sacar(Cliente cliente);

#endif
