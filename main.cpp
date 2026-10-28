#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <string>
#include <sstream> // Formatação segura de strings

using namespace std;

#include "funcoes.h"
#include "bisseccao.h"
#include "posicaoFalsa.h"
#include "newtonRaphson.h"

// Códigos de cores ANSI para o terminal do Linux
#define RESET    "\033[0m"
#define VERMELHO "\033[1;31m"
#define VERDE    "\033[1;32m"
#define AMARELO  "\033[1;33m"
#define CIANO    "\033[1;36m"
#define NEGRITO  "\033[1m"

// Função auxiliar para calcular casas decimais baseadas no epsilon
int obterCasasDecimais(double eps) {
    if (eps <= 0) return 6;
    int casas = static_cast<int>(ceil(-log10(eps)));
    return (casas < 2) ? 2 : casas;
}

// Função auxiliar para montar a string da tabela com segurança
string formatarSaidaTabela(double raiz, int iteracoes, int casas) {
    ostringstream oss;
    oss << fixed << setprecision(casas) << raiz << " (" << iteracoes << " it)";
    return oss.str();
}

int main() {
    int n;
    double epsilon;

    cout << CIANO << "---------------------------------------------------------------------------------\n";
    cout << "           TEMA 01 - DESLOCAMENTO DO FOGUETE ESPACIAL (MÉTODOS NUMÉRICOS)\n";
    cout << "---------------------------------------------------------------------------------\n\n" << RESET;

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

    // QUADRO RESPOSTA (ERROS)
    cout << "\n" << CIANO << "---------------------------------------------------------------------------------\n";
    cout << "                                QUADRO RESPOSTA (ERRO FINAL)\n";
    cout << "---------------------------------------------------------------------------------\n" << RESET;
    cout << left << setw(10) << "Foguete" 
         << setw(12) << "Valor a" 
         << setw(22) << "Erro Bissecção" 
         << setw(22) << "Erro Pos. Falsa" 
         << setw(22) << "Erro Newton" << "\n";
    cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << (i + 1)
             << defaultfloat << setprecision(2) << setw(12) << valoresA[i]
             << scientific << setprecision(2)
             << setw(22) << resultadosB[i].erroFinal
             << setw(22) << resultadosPF[i].erroFinal
             << setw(22) << resultadosNR[i].erroFinal << "\n";
    }
    cout << "---------------------------------------------------------------------------------\n\n";

    // QUADRO COMPARATIVO
    cout << CIANO << "---------------------------------------------------------------------------------------------------------\n";
    cout << "                                       QUADRO COMPARATIVO\n";
    cout << "---------------------------------------------------------------------------------------------------------\n" << RESET;
    cout << "Epsilon utilizado: " << scientific << epsilon << defaultfloat << "\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";
    cout << left << setw(9) << "Foguete"
         << setw(16) << "Isolamento"
         << setw(25) << "Bissecção (d | it)"
         << setw(25) << "Pos. Falsa (d | it)"
         << setw(25) << "Newton (d | it)"
         << setw(15) << "Estado (d > 2cm)" << "\n";
    cout << "---------------------------------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(9) << (i + 1);

        string isol = "[" + to_string((int)limInf[i]) + ", " + to_string((int)limSup[i]) + "]";
        cout << setw(16) << isol;

        string bStr = formatarSaidaTabela(resultadosB[i].raiz, resultadosB[i].iteracoes, casasPrecision);
        string pfStr = formatarSaidaTabela(resultadosPF[i].raiz, resultadosPF[i].iteracoes, casasPrecision);
        string nrStr = formatarSaidaTabela(resultadosNR[i].raiz, resultadosNR[i].iteracoes, casasPrecision);

        cout << setw(25) << bStr
             << setw(25) << pfStr
             << setw(25) << nrStr;

        double dMax = resultadosNR[i].raiz;
        if (dMax > 2.0) {
            cout << VERMELHO << "[EXPLOSÃO]" << RESET << "\n";
        } else {
            cout << VERDE << "[SEGURO]" << RESET << "\n";
        }
    }
    cout << "---------------------------------------------------------------------------------------------------------\n";

    return 0;
}