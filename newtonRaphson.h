#ifndef METNUMERICOS_NEWTONRAPHSON_H
#define METNUMERICOS_NEWTONRAPHSON_H

#include <cmath>
#include "funcoes.h"   // Pega f(x) e f'(x)
#include "estruturas.h" // Pega o modelo de respostas

// Função do método Newton-Raphson
inline ResultadoMetodo newtonRaphson(double a, double dInicial, double epsilon) {
    ResultadoMetodo resultado = {0.0, 0, 0.0, false};

    int iteracoes = 0;
    double dAtual = dInicial;
    double dAnterior = dAtual;
    double erro = INFINITY;
    bool convergiu = false;

    int maxIteracoes = 1000;

    // Validação do domínio do logaritmo ln(d > 0)
    if (dAtual <= 0) {
        resultado.raiz = dAtual;
        resultado.erroFinal = INFINITY;
        resultado.convergiu = false;
        return resultado;
    }

    while (iteracoes < maxIteracoes) {
        double valorF = f(a, dAtual);
        double valorDF = df(a, dAtual);

        // Previne divisão por zero ou derivadas quase nulas
        if (std::abs(valorDF) < 1e-15) {
            break;
        }

        // Teste de paragem se f(d) já atingiu a precisão
        if (std::abs(valorF) <= epsilon) {
            convergiu = true;
            erro = std::abs(valorF);
            break;
        }

        dAnterior = dAtual;
        double proximoD = dAtual - (valorF / valorDF);

        // Proteção para não sair do domínio do ln(d)
        if (proximoD <= 0) {
            proximoD = dAtual / 2.0;
        }

        dAtual = proximoD;
        iteracoes++;

        erro = std::abs(dAtual - dAnterior);

        // Critério de paragem pela variação do passo
        if (erro <= epsilon) {
            convergiu = true;
            break;
        }
    }

    if (std::abs(f(a, dAtual)) == 0.0) {
        erro = 0.0;
    }

    resultado.raiz = dAtual;
    resultado.iteracoes = iteracoes;
    resultado.erroFinal = erro;
    resultado.convergiu = convergiu;

    return resultado;
}

#endif //METNUMERICOS_NEWTONRAPHSON_H