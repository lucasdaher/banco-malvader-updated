#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

#include "malvader.h"

void enviarMenuFuncionario();
int consultarFuncionarioPorCodigo(FILE *file, int codigoFuncionario);
int inserirFuncionario(FILE *file, Funcionario funcionario);
int alterarFuncionario(FILE *file, Funcionario funcionario_antigo, Funcionario funcionario_novo);
void mostrarDadosFuncionario(FILE *file, int posicao);
int excluirFuncionario(FILE *file, Funcionario funcionario);
void validarSenhaFuncionario(FILE *file, Funcionario funcionario);

#endif
