#ifndef METNUMERICOS_FUNCOES_H
#define METNUMERICOS_FUNCOES_H

#include <cmath>

// Função F(d)
inline double f(double a, double d) {
    return ((a * d) - (d * log(d)));
}

// Função F'(x)
inline double df(double a, double d) {
    return (a - (log(d) + 1.0));
}

// Achar Intervalos
inline void gerarIntervaloAutomatico(double a, double &limInf, double &limSup) {
    double raizExata = exp(a);

    // Pega o inteiro imediatamente abaixo e acima da raiz
    limInf = floor(raizExata);
    limSup = ceil(raizExata);

    // Se a raizExata for um número inteiro cravado (ex: a=0 -> e^0 = 1) floor e ceil seriam iguais
    if (limInf == limSup) {
        limInf -= 0.5;
        limSup += 0.5;
    }

    // O domínio da função original tem ln(d), então d tem que ser > 0.
    // Se o limite inferior for 0 ou negativo, empurramos ele para um valor positivo pequeno.
    if (limInf <= 0) {
        limInf = raizExata / 10.0;
    }
}

#endif //METNUMERICOS_FUNCOES_H
