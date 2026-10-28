#ifndef METNUMERICOS_ESTRUTURAS_H
#define METNUMERICOS_ESTRUTURAS_H

struct ResultadoMetodo {
    double raiz;
    int iteracoes;
    double erroAbs; 
    double erroRel; 
    bool convergiu;
};

#endif //METNUMERICOS_ESTRUTURAS_H