#ifndef ENTRADA_SAIDA_H
#define ENTRADA_SAIDA_H

#include "matriz.h"

// Lê n, A (n×n) e f (n) do sistema a resolver, validando as dimensões.
// TODO (Diego): hoje carrega o exemplo padrão; trocar pela leitura da entrada.
void lerSistema(Matriz& A, Vetor& f);

// Imprime d_1 ... d_n com 6 casas decimais e marca cada |d_i| > limite (2 cm no enunciado).
void imprimirResultado(const Vetor& d, double limite = 2.0);

#endif
