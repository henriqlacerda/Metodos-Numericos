// Testes com o gabarito do enunciado (dados padrão do Tema 1).
// Uso: make teste && ./teste   (ou: make run-teste)
// Enquanto os módulos não estiverem implementados, os testes aparecem como FALHOU.
#include <cmath>
#include <iostream>

#include "ldp.h"
#include "lu.h"
#include "matriz.h"

namespace {

int aprovados = 0;
int reprovados = 0;

void verificar(const char* nome, bool condicao) {
    if (condicao) {
        ++aprovados;
        std::cout << "[OK]     ";
    } else {
        ++reprovados;
        std::cout << "[FALHOU] ";
    }
    std::cout << nome << '\n';
}

bool proximo(double a, double b) { return std::fabs(a - b) <= 1e-9; }

bool proximoVetor(const Vetor& a, const Vetor& b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i)
        if (!proximo(a[i], b[i])) return false;
    return true;
}

bool proximoMatriz(const Matriz& a, const Matriz& b) {
    if (a.size() != b.size()) return false;
    for (std::size_t i = 0; i < a.size(); ++i)
        if (!proximoVetor(a[i], b[i])) return false;
    return true;
}

}  // namespace

int main() {
    // Sistema padrão do enunciado
    const Matriz A = {{3, -2, 1}, {1, -3, 4}, {9, 4, -5}};
    const Vetor  f = {8, 6, 11};

    // Gabarito (calculado à mão)
    const Matriz L_ref = {{1, 0, 0}, {1.0 / 3, 1, 0}, {3, -30.0 / 7, 1}};
    const Matriz U_ref = {{3, -2, 1}, {0, -7.0 / 3, 11.0 / 3}, {0, 0, 54.0 / 7}};
    const Vetor  D_ref = {3, -7.0 / 3, 54.0 / 7};
    const Matriz P_ref = {{1, -2.0 / 3, 1.0 / 3}, {0, 1, -11.0 / 7}, {0, 0, 1}};
    const Vetor  d_ref = {11.0 / 6, -7.0 / 6, 1.0 / 6};

    std::cout << "=== Fatoração LU (Max) ===\n";
    Matriz L, U;
    verificar("fatoracaoLU retorna true (sem pivô nulo)", fatoracaoLU(A, L, U));
    verificar("L igual ao gabarito", proximoMatriz(L, L_ref));
    verificar("U igual ao gabarito", proximoMatriz(U, U_ref));

    std::cout << "\n=== Resolução por LU (Max) ===\n";
    Vetor d1;
    verificar("resolveLU retorna true", resolveLU(A, f, d1));
    verificar("d = (11/6, -7/6, 1/6)", proximoVetor(d1, d_ref));
    verificar("resíduo max|Ad - f| < 1e-9", residuoMaximo(A, d1, f) < 1e-9);

    std::cout << "\n=== Fatoração LDP (Chimecho) ===\n";
    Matriz L2, P;
    Vetor D;
    verificar("fatoracaoLDP retorna true", fatoracaoLDP(A, L2, D, P));
    verificar("L igual à do LU", proximoMatriz(L2, L_ref));
    verificar("D = diag(3, -7/3, 54/7)", proximoVetor(D, D_ref));
    verificar("P igual ao gabarito", proximoMatriz(P, P_ref));

    std::cout << "\n=== Resolução por LDP (Chimecho) ===\n";
    Vetor d2;
    verificar("resolveLDP retorna true", resolveLDP(A, f, d2));
    verificar("d = (11/6, -7/6, 1/6)", proximoVetor(d2, d_ref));
    verificar("resíduo max|Ad - f| < 1e-9", residuoMaximo(A, d2, f) < 1e-9);

    std::cout << "\nResultado: " << aprovados << " OK, " << reprovados << " FALHOU\n";
    return reprovados == 0 ? 0 : 1;
}
