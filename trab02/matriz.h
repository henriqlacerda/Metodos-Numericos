#ifndef MATRIZ_H
#define MATRIZ_H

#include <cstddef>
#include <vector>

// Tipos comuns a todos os módulos. Combinados pelo grupo: alterar só avisando.
using Vetor  = std::vector<double>;
using Matriz = std::vector<Vetor>;  // Matriz[i][j] = a_(i+1)(j+1), índices a partir de 0

// Tolerância para considerar um pivô como nulo
constexpr double EPS = 1e-12;

// Maior |f_i - (A x)_i|: resíduo para validar uma solução x de A x = f.
// Retorna +infinito se as dimensões não baterem.
double residuoMaximo(const Matriz& A, const Vetor& x, const Vetor& f);

// Maior |v_i|: usado para comparar com o limite de 2 cm.
double maiorModulo(const Vetor& v);

#endif
