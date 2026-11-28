#ifndef ENTRADA_SAIDA_H
#define ENTRADA_SAIDA_H

#include "matriz.h"

// lê n, A(n×n) e f(n) do sistema a resolver, validando as dimensões
// oferece o exemplo padrão ou a digitação dos dados
void lerSistema(Matriz& A, Vetor& f);

// imprime d_1 ... d_n com 6 casas decimais e marca cada |d_i| > limite (2cm)
void imprimirResultado(const Vetor& d, double limite = 2.0);

#endif
