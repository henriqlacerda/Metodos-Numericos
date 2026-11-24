#include "entrada_saida.h"

#include <cmath>
#include <iomanip>
#include <iostream>

// TODO (Diego): ler n, A e f de stdin (ou arquivo), validar dimensões e tratar erros.
// Por enquanto carrega o exemplo padrão para o restante do sistema funcionar.
void lerSistema(Matriz& A, Vetor& f) {
    A = {{3, -2, 1}, {1, -3, 4}, {9, 4, -5}};
    f = {8, 6, 11};
}

// TODO (Diego): ajustar a formatação se o grupo preferir outro padrão de saída.
void imprimirResultado(const Vetor& d, double limite) {
    std::cout << std::fixed << std::setprecision(6);
    for (std::size_t i = 0; i < d.size(); ++i) {
        std::cout << "d" << i + 1 << " = " << d[i] << " cm";
        if (std::fabs(d[i]) > limite)
            std::cout << "   <-- ALERTA: passou de " << limite << " cm";
        std::cout << '\n';
    }
}
