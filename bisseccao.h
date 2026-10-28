#ifndef METNUMERICOS_BISSECCAO_H
#define METNUMERICOS_BISSECCAO_H

#include <cmath>
#include "funcoes.h"
#include "estruturas.h"

inline double bissecionar(double a, double b, int casas_decimais) {
    int k_decimos = std::pow(10, casas_decimais);
    double novo_x = (a + b) / 2.0;
    return std::trunc(novo_x * k_decimos) / k_decimos;
}

inline ResultadoMetodo bisseccao(double a, double epsilon, double limInf, double limSup) {
    ResultadoMetodo resultado = {0.0, 0, 0.0, false};
    
    // Define as casas decimais para o truncamento baseado no epsilon fornecido
    int casas_decimais = (epsilon > 0) ? std::ceil(-std::log10(epsilon)) : 6;
    
    double fx_inf = f(a, limInf);
    double fx_sup = f(a, limSup);
    
    if (fx_inf * fx_sup > 0.0) {
        resultado.raiz = -1.0;
        resultado.erroFinal = -1.0;
        return resultado; 
    }

    int k_passo = 1;
    int passos_max = 1000;
    
    double x = bissecionar(limInf, limSup, casas_decimais);
    double fx = f(a, x);

    while (std::abs(fx) >= epsilon && std::abs(limInf - limSup) >= epsilon && k_passo <= passos_max) {
        if (fx_inf * fx < 0.0) {
            limSup = x;
            fx_sup = fx;
        } else {
            limInf = x;
            fx_inf = fx;
        }

        x = bissecionar(limInf, limSup, casas_decimais);
        fx = f(a, x);
        k_passo++;
    }

    resultado.raiz = x;
    resultado.iteracoes = k_passo;
    resultado.erroFinal = std::abs(limInf - limSup) / 2.0;
    resultado.convergiu = (k_passo <= passos_max);

    return resultado;
}

#endif //METNUMERICOS_BISSECCAO_H