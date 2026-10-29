#ifndef METNUMERICOS_POSICAOFALSA_H
#define METNUMERICOS_POSICAOFALSA_H

#include <cmath>
#include <algorithm>
#include "funcoes.h"
#include "estruturas.h"

inline ResultadoMetodo posicaoFalsa(double a, double epsilon, double limInf, double limSup) {
    ResultadoMetodo resultado = {0.0, 0, 0.0, false};

    double a_int = limInf;
    double b_int = limSup;
    double Fa = f(a, a_int);
    double Fb = f(a, b_int);

    if (Fa * Fb > 0.0) {
        resultado.raiz = -1.0;
        resultado.erroAbs = -1.0;
        resultado.erroRel = -1.0;
        resultado.convergiu = false;
        return resultado;
    }

    double d = a_int;
    double d_ant = d;
    double Fd = Fa;
    double erro = INFINITY;
    int iteracoes = 0;
    int maxIteracoes = 1000;

    while (iteracoes < maxIteracoes) {
        if (std::abs(Fb - Fa) < 1e-15) break;

        d_ant = d;
        d = (a_int * Fb - b_int * Fa) / (Fb - Fa);
        Fd = f(a, d);
        iteracoes++;

        double erroPasso = std::abs(d - d_ant);
        double erroFuncao = std::abs(Fd);

        // Define o erro final como o menor valor atingido entre a variação e o valor da função
        erro = std::min(erroPasso, erroFuncao);

        if (erro <= epsilon) {
            break;
        }

        if (Fa * Fd > 0.0) {
            a_int = d;
            Fa = Fd;
        } else {
            b_int = d;
            Fb = Fd;
        }
    }

    resultado.raiz = d;
    resultado.iteracoes = iteracoes;
    resultado.erroAbs = erro;
    resultado.erroRel = erro / d;
    resultado.convergiu = (erro <= epsilon);

    return resultado;
}

#endif //METNUMERICOS_POSICAOFALSA_H