#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include "malvader.h"

void enviarMenuFuncionario();
int consultarFuncionario(FILE *file, Funcionario funcionario);
int inserirFuncionario(FILE *file, Funcionario funcionario);
int alterarFuncionario(FILE *file, Funcionario funcionario_antigo, Funcionario funcionario_novo);
int excluirFuncionario(FILE *file, Funcionario funcionario);
void validarSenhaFuncionario(FILE *file, Funcionario funcionario);

#endif
