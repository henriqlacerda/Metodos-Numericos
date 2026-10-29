#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

#include "funcoes.h"
#include "bisseccao.h"
#include "posicaoFalsa.h"
#include "newtonRaphson.h"

#define RESET    "\033[0m"
#define VERMELHO "\033[1;31m"
#define VERDE    "\033[1;32m"
#define AMARELO  "\033[1;33m"
#define CIANO    "\033[1;36m"
#define NEGRITO  "\033[1m"

int obterCasasDecimais(double eps) {
    if (eps <= 0) return 6;
    int casas = static_cast<int>(ceil(-log10(eps)));
    return (casas < 2) ? 2 : casas;
}

// Função auxiliar para formatar a célula do Quadro Comparativo
string formatarComparativo(int iteracoes, double erroAbs, double erroRel) {
    ostringstream oss;
    oss << iteracoes << " it | " 
        << scientific << setprecision(2) << erroAbs << " | " 
        << erroRel;
    return oss.str();
}

int main() {
    int n;
    double epsilon;

    cout << CIANO << "---------------------------------------------------------------------------------------------------------\n";
    cout << "                    TEMA 01 - DESLOCAMENTO DO FOGUETE ESPACIAL (MÉTODOS NUMÉRICOS)\n";
    cout << "---------------------------------------------------------------------------------------------------------\n\n" << RESET;

    cout << NEGRITO << "Digite o número de foguetes a analisar (n): " << RESET;
    cin >> n;

    vector<double> valoresA(n);
    vector<double> limInf(n);
    vector<double> limSup(n);

    for (int i = 0; i < n; i++) {
        cout << "Digite o parâmetro de ajuste 'a' para o foguete " << i + 1 << ": ";
        cin >> valoresA[i];

        gerarIntervaloAutomatico(valoresA[i], limInf[i], limSup[i]);
        cout << AMARELO << "  -> Isolamento gerado analiticamente (e^a): [" 
             << limInf[i] << ", " << limSup[i] << "]\n\n" << RESET;
    }

    cout << NEGRITO << "Digite a precisão desejada (epsilon, ex: 0.00001): " << RESET;
    cin >> epsilon;

    int casasPrecision = obterCasasDecimais(epsilon);

    vector<ResultadoMetodo> resultadosB(n), resultadosPF(n), resultadosNR(n);

    for (int i = 0; i < n; i++) {
        double a = valoresA[i];
        
        resultadosB[i] = bisseccao(a, epsilon, limInf[i], limSup[i]);
        resultadosPF[i] = posicaoFalsa(a, epsilon, limInf[i], limSup[i]);
        
        double chuteInicial = (limInf[i] + limSup[i]) / 2.0;
        resultadosNR[i] = newtonRaphson(a, chuteInicial, epsilon);
    }

    cout << "\n" << CIANO << "---------------------------------------------------------------------------------------------------------\n";
    cout << "                                QUADRO RESPOSTA (RAÍZES CALCULADAS)\n";
    cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;
    cout << left << setw(9) << "Foguete" 
         << setw(10) << "Valor a" 
         << setw(20) << "Raiz Bissecção" 
         << setw(20) << "Raiz Pos. Falsa" 
         << setw(20) << "Raiz Newton" 
         << setw(15) << "Estado" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(9) << (i + 1)
             << defaultfloat << setprecision(2) << setw(10) << valoresA[i];
             
        cout << fixed << setprecision(casasPrecision)
             << setw(20) << resultadosB[i].raiz
             << setw(20) << resultadosPF[i].raiz
             << setw(20) << resultadosNR[i].raiz;

        // Estado de segurança
        if (resultadosNR[i].raiz > 2.0) {
            cout << VERMELHO << "[EXPLOSÃO]" << RESET << "\n";
        } else {
            cout << VERDE << "[SEGURO]" << RESET << "\n";
        }
    }
    cout << "---------------------------------------------------------------------------------------------------------\n\n";

    cout << CIANO << "------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                              QUADRO COMPARATIVO (ITERAÇÕES E ERROS)\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------\n" << RESET;
    cout << "Epsilon utilizado: " << scientific << epsilon << defaultfloat << "\n";
    cout << "Formato das colunas de método: (it | Erro Abs | Erro Rel)\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(9) << "Foguete"
         << setw(10) << "Valor a"
         << setw(16) << "Isolamento"
         << setw(30) << "Bissecção"
         << setw(30) << "Pos. Falsa"
         << setw(30) << "Newton" << "\n";
    cout << "------------------------------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(9) << (i + 1)
             << defaultfloat << setprecision(2) << setw(10) << valoresA[i];

        string isol = "[" + to_string((int)limInf[i]) + ", " + to_string((int)limSup[i]) + "]";
        cout << setw(16) << isol;

        string bStr = formatarComparativo(resultadosB[i].iteracoes, resultadosB[i].erroAbs, resultadosB[i].erroRel);
        string pfStr = formatarComparativo(resultadosPF[i].iteracoes, resultadosPF[i].erroAbs, resultadosPF[i].erroRel);
        string nrStr = formatarComparativo(resultadosNR[i].iteracoes, resultadosNR[i].erroAbs, resultadosNR[i].erroRel);

        cout << setw(30) << bStr
             << setw(30) << pfStr
             << setw(30) << nrStr << "\n";
    }
    cout << "------------------------------------------------------------------------------------------------------------------------------\n";

    return 0;
}