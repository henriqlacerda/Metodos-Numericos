#include "matriz.h"

#include <algorithm>
#include <cmath>
#include <limits>

double residuoMaximo(const Matriz& A, const Vetor& x, const Vetor& f) {
    const std::size_t n = A.size();
    if (x.size() != n || f.size() != n) return std::numeric_limits<double>::infinity();
    for (const Vetor& linha : A)
        if (linha.size() != n) return std::numeric_limits<double>::infinity();

    double maximo = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        double soma = 0.0;
        for (std::size_t j = 0; j < n; ++j) soma += A[i][j] * x[j];
        maximo = std::max(maximo, std::fabs(soma - f[i]));
    }
    return maximo;
}

double maiorModulo(const Vetor& v) {
    double maximo = 0.0;
    for (double x : v) maximo = std::max(maximo, std::fabs(x));
    return maximo;
}
