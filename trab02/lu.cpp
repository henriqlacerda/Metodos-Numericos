#include "lu.h"

// TODO (Max): implementar a fatoração de Doolittle, sem pivotamento.
bool fatoracaoLU(const Matriz& A, Matriz& L, Matriz& U) {
    (void)A; (void)L; (void)U;
    return false;
}

// TODO (Max): substituição progressiva.
Vetor substituicaoProgressiva(const Matriz& L, const Vetor& b) {
    (void)L; (void)b;
    return {};
}

// TODO (Max): substituição regressiva.
Vetor substituicaoRegressiva(const Matriz& U, const Vetor& y) {
    (void)U; (void)y;
    return {};
}

// TODO (Max): combinar fatoracaoLU com as duas substituições. Retornar false se a fatoração falhar.
bool resolveLU(const Matriz& A, const Vetor& f, Vetor& d) {
    (void)A; (void)f; (void)d;
    return false;
}
