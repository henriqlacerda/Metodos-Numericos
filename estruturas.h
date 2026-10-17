#ifndef METNUMERICOS_ESTRUTURAS_H
#define METNUMERICOS_ESTRUTURAS_H

// Modelo de Resposta dos métodos
struct ResultadoMetodo {
    double raiz;
    int iteracoes;
    double erroFinal;
    bool convergiu;
};

#endif //METNUMERICOS_ESTRUTURAS_H
