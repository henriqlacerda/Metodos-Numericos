#ifndef METNUMERICOS_NEWTONRAPHSON_H
#define METNUMERICOS_NEWTONRAPHSON_H

#include <cmath>

#include "funcoes.h" // Pega f(x) e f'(x)
#include "estruturas.h" // Pega o modelo de respostas

// função do metodo Newton Raphson
inline ResultadoMetodo newtonRaphson(double a, double dInicial, double epsilon) {
    // elementos que vão ser retornados depois
    int iteracoes = 0;
    double dAtual = dInicial;
    double erro = INFINITY;
    bool convergiu = true;

    // número máximo de iterações para caso o algoritmo não convirja
    int maxIteracoes = 1000;

    // loop de aproximação da raiz
    while (erro > epsilon && iteracoes < maxIteracoes) {
        double valorF = f(a, dAtual);
        double valorDF = df(a, dAtual);

        // prevenir divisão por zero
        if (valorDF == 0) {
            convergiu = false;
            break;
        }

        double dAnterior = dAtual;
        dAtual -= (valorF/valorDF);
        iteracoes++;

        erro = std::abs(dAnterior - dAtual);
    }

    /*
     * caso o loop pare por chegar no limite de iterações,
     * e o erro não for menor que a tolerância, então
     * não convergiu
     */
    if (erro > epsilon) {
        convergiu = false;
    }

    // cria a instancia da struct e retorna
    ResultadoMetodo resultado = {};
    resultado.raiz = dAtual;
    resultado.iteracoes = iteracoes;
    resultado.erroFinal = erro;
    resultado.convergiu = convergiu;

    return resultado;
}
#endif //METNUMERICOS_NEWTONRAPHSON_H
