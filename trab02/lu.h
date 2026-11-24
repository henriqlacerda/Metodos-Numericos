#ifndef LU_H
#define LU_H

#include "matriz.h"

// Fatoração LU de Doolittle, sem pivotamento: A = L U, com diag(L) = 1.
// Retorna false se algum pivô tiver |u_jj| < EPS.
bool fatoracaoLU(const Matriz& A, Matriz& L, Matriz& U);

// Resolve L y = b (L triangular inferior com diagonal unitária).
Vetor substituicaoProgressiva(const Matriz& L, const Vetor& b);

// Resolve U x = y (U triangular superior).
Vetor substituicaoRegressiva(const Matriz& U, const Vetor& y);

// Resolve A d = f pelo método LU. Retorna false se a fatoração falhar.
bool resolveLU(const Matriz& A, const Vetor& f, Vetor& d);

#endif
