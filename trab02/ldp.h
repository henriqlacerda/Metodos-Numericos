#ifndef LDP_H
#define LDP_H

#include "matriz.h"

// Fatoração LDP: A = L D P, com L a mesma triangular inferior do LU,
// D = diag(U) e P = D⁻¹ U (triangular superior com diagonal unitária).
// Retorna false se houver pivô nulo.
bool fatoracaoLDP(const Matriz& A, Matriz& L, Vetor& D, Matriz& P);

// Resolve A d = f por LDP: L y = f, D z = y, P d = z.
bool resolveLDP(const Matriz& A, const Vetor& f, Vetor& d);

#endif
