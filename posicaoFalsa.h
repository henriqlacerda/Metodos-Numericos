#ifndef METNUMERICOS_POSICAOFALSA_H
#define METNUMERICOS_POSICAOFALSA_H

#include "funcoes.h"
#include "estruturas.h"

// Implemente o método da Posição Falsa aqu
inline ResultadoMetodo posicaoFalsa(double a, double epsilon, double limInf, double limSup) {

    // Inicializa variáveis
    ResultadoMetodo resultado = {0.0, 0, 0.0, false};
    double a_int = limInf;
    double b_int = limSup;
    double Fa = f(a,limInf);
    double Fb = f(a,limSup);
    double d = (a_int*Fb - b_int*Fa)/(Fb - Fa); // Variável que irá guardar o d estimado (d')
    double d_ant; // Variável para guardar o d na última iteração
    double Fd = f(a,d); // Variável que irá guardar o F(d')

    // Tratamento de erro: "A função não muda de sinal entre a e b" (DÚVIDA: COMO TRATAR?)
    if (Fa*Fb > 0) {
        resultado.raiz = -1;
        resultado.erroFinal = -1;
        return resultado;
    }

    double tam_interv = std::abs(b_int - a_int);

    // Tratamento de caso: o tamanho do intervalo [a,b] está menor que a precisão
    if (tam_interv < epsilon) {
        resultado.raiz = limInf;
        if (a_int > 0 && b_int > 0) { // Teste de convergência
            if (Fa*Fb < 0) { // Nesse caso, ocorre mudança de sinal de Fa para Fb
                resultado.convergiu = true;
            }
        }
        return resultado;
    }
    
    while (std::abs(Fd) > epsilon) {  // Loop PRINCIPAL: enquanto não atingirmos a precisão desejada
        
        d_ant = d;  // d_ant guarda o valor de d mais recente

        // Calcula novo d e novo F(d)
        d = (a_int*Fb - b_int*Fa)/(Fb - Fa);
        Fd = f(a,d);

        if (Fa*Fd > 0.0) { // Caso 1: o novo intervalo será [d',b]
            a_int = d;
            Fa = Fd;
        } 
        else { // Caso 2: o novo intervalo será [a,d']
            b_int = d;
            Fb = Fd;
        }

        resultado.iteracoes++;  // Incrementa 1 iteração e altera a contagem
    }
    
    // Teste de convergência
    if (a_int > 0 && b_int > 0) { // Nesse caso, F(d) é contínua com d pertencendo a (0,+∞)
        if (Fa*Fb < 0) { // Nesse caso, ocorre mudança de sinal de Fa para Fb
            resultado.convergiu = true;
        }
    }

    resultado.raiz = d;
    resultado.erroFinal = d - d_ant;
    return resultado;
}

#endif //METNUMERICOS_POSICAOFALSA_H
