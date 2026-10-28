#ifndef METNUMERICOS_BISSECCAO_H
#define METNUMERICOS_BISSECCAO_H

#include <cmath>
#include "funcoes.h"
#include "estruturas.h"

inline ResultadoMetodo bisseccao(double a, double epsilon, double limInf, double limSup) {
    ResultadoMetodo resultado = {0.0, 0, 0.0, false};
    
    double fa = f(a, limInf);
    double fb = f(a, limSup);
    
    if (fa * fb > 0.0) {
        resultado.raiz = -1.0;
        resultado.erroFinal = -1.0;
        resultado.convergiu = false;
        return resultado; 
    }

    double a_int = limInf;
    double b_int = limSup;
    double c = a_int;
    double erro = (b_int - a_int) / 2.0;
    int iteracoes = 0;
    int maxIteracoes = 1000;

    // O loop continua até que o erro seja estritamente menor ou igual ao epsilon
    while (erro > epsilon && iteracoes < maxIteracoes) {
        c = (a_int + b_int) / 2.0; // Ponto médio de precisão dupla (double) sem truncamento
        double fc = f(a, c);
        iteracoes++;

        if (fc == 0.0) {
            erro = 0.0;
            break;
        }

        if (fa * fc < 0.0) {
            b_int = c;
            fb = fc;
        } else {
            a_int = c;
            fa = fc;
        }

        erro = (b_int - a_int) / 2.0;
    }

    resultado.raiz = c;
    resultado.iteracoes = iteracoes;
    resultado.erroFinal = erro;
    resultado.convergiu = (erro <= epsilon);

    return resultado;
}

#endif //METNUMERICOS_BISSECCAO_H