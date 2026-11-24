#ifndef METNUMERICOS_POSICAOFALSA_H
#define METNUMERICOS_POSICAOFALSA_H

#include <cmath>
#include "funcoes.h"
#include "estruturas.h"

inline ResultadoMetodo posicaoFalsa(double a, double epsilon, double limInf, double limSup) {
    ResultadoMetodo resultado = {};

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
    double erro = std::abs(Fa);   // erro da aproximação inicial: |f(d)|
    int iteracoes = 0;
    int maxIteracoes = 1000;

    // Mesmo critério do Newton-Raphson: para quando |f(d)| <= epsilon
    while (erro > epsilon && iteracoes < maxIteracoes) {
        if (std::abs(Fb - Fa) < 1e-15) break;

        d = (a_int * Fb - b_int * Fa) / (Fb - Fa);
        double Fd = f(a, d);
        iteracoes++;

        erro = std::abs(Fd);

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