#include <iostream>

#include "entrada_saida.h"
#include "ldp.h"
#include "lu.h"
#include "matriz.h"

// Integração (Henrique): escolhe o método, resolve e mostra os resultados.
int main() {
    Matriz A;
    Vetor f;
    lerSistema(A, f);

    std::cout << "Método (1 = LU, 2 = LDP): ";
    int opcao = 0;
    std::cin >> opcao;

    Vetor d;
    bool ok = false;
    if (opcao == 1)
        ok = resolveLU(A, f, d);
    else if (opcao == 2)
        ok = resolveLDP(A, f, d);
    else {
        std::cerr << "Opção inválida.\n";
        return 1;
    }

    if (!ok) {
        std::cerr << "Falha: pivô nulo ou sistema não resolvido.\n";
        return 1;
    }

    imprimirResultado(d);
    std::cout << "maior |d_i| = " << maiorModulo(d) << " cm\n";
    std::cout << "resíduo max|Ad - f| = " << residuoMaximo(A, d, f) << '\n';
    return 0;
}
