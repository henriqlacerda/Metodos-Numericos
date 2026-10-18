#include <iostream>
#include <vector>
#include <iomanip> // Formatação dos quadros

using namespace std;

#include "funcoes.h" // Auxiliar
#include "bisseccao.h" // Chimecho
#include "posicaoFalsa.h" // Caio
#include "newtonRaphson.h" // Diego

// Henrique (main)
int main() {
  int n;
  double epsilon;

  cout << "---------------------------------------------------------\n";
  cout << "           TEMA 01 - DESLOCAMENTO DO FOGUETE\n";
  cout << "---------------------------------------------------------\n\n";

  // Entrada
  cout << "Digite o numero de foguetes a serem analisados (n): ";
  cin >> n;

  vector<double> valoresA(n);
  vector<double> limInf(n);
  vector<double> limSup(n);

  for (int i = 0; i < n; i++) {
    cout << "Digite o parametro de ajuste 'a' para o foguete " << i + 1 << ": ";
    cin >> valoresA[i];

    gerarIntervaloAutomatico(valoresA[i], limInf[i], limSup[i]);

    cout << "-> Intervalo gerado analiticamente (e^a): [" << limInf[i] << ", " << limSup[i] << "]\n\n";
  }

  cout << "Digite a precisao desejada (epsilon, ex: 0.00001): ";
  cin >> epsilon;

  cout << "\nCalculando...\n\n";

  // Saída

  // Preparando o Quadro Resposta
  cout << "---------------------------------------------------------------------------------\n";
  cout << "                                QUADRO RESPOSTA\n";
  cout << "---------------------------------------------------------------------------------\n";
  cout << left << setw(10) << "Foguete" << setw(10) << "Valor a" << setw(20) << "Erro Bisseccao" << setw(20) << "Erro Pos. Falsa" << setw(20) << "Erro Newton" << "\n";
  cout << "---------------------------------------------------------------------------------\n";

  // P ajudar na construção do quadro
  vector<ResultadoMetodo> resultadosB(n), resultadosPF(n), resultadosNR(n);

  for (int i = 0; i < n; i++) {
    double a = valoresA[i];

    resultadosB[i] = bisseccao(a, epsilon, limInf[i], limSup[i]);
    resultadosPF[i] = posicaoFalsa(a, epsilon, limInf[i], limSup[i]);

    double chuteInicial = (limInf[i] + limSup[i]) / 2.0;
    resultadosNR[i] = newtonRaphson(a, chuteInicial, epsilon);

    // Imprimindo linha no quadro de respostas
    cout << left << setw(10) << i + 1 << setw(10) << a << setw(20) << resultadosB[i].erroFinal << setw(20) << resultadosPF[i].erroFinal << setw(20) << resultadosNR[i].erroFinal << "\n";
  }
  cout << "---------------------------------------------------------------------------------\n\n";

  // Preparando o Quadro Comparativo
  cout << "---------------------------------------------------------------------------------\n";
  cout << "                              QUADRO COMPARATIVO\n";
  cout << "---------------------------------------------------------------------------------\n";
  cout << "Epsilon utilizado: " << epsilon << "\n";
  cout << "---------------------------------------------------------------------------------\n";
  cout << left << setw(10) << "Foguete" << setw(20) << "Isolamento" << setw(25) << "Raiz Bissec. (Iter)" << setw(25) << "Raiz PosFalsa (Iter)" << setw(25) << "Raiz Newton (Iter)" << "\n";
  cout << "---------------------------------------------------------------------------------\n";

  for (int i = 0; i < n; i++) {
    cout << left << setw(10) << i + 1;

    cout << fixed << setprecision(5);

    cout << "(" << limInf[i] << ", " << limSup[i] << ")" << setw(5) << "" << resultadosB[i].raiz << " (" << resultadosB[i].iteracoes << " it)      " << resultadosPF[i].raiz << " (" << resultadosPF[i].iteracoes << " it)      " << resultadosNR[i].raiz << " (" << resultadosNR[i].iteracoes << " it)\n";
  }
  cout << "---------------------------------------------------------------------------------\n";

  return 0;
}