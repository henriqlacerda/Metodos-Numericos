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

int main() {
    int n;
    double epsilon;
    
    string sepHeader(120, '-');
    string sepResposta(126, '-');
    string sepFoguete(100, '-');
    string sepMetodos(100, '-');

    cout << CIANO << sepHeader << "\n";
    cout << "                    TEMA 01 - DESLOCAMENTO DO FOGUETE ESPACIAL (METODOS NUMERICOS)\n";
    cout << sepHeader << "\n\n" << RESET;

    cout << NEGRITO << "Digite o numero de foguetes a analisar (n): " << RESET;
    cin >> n;

    vector<double> valoresA(n);
    vector<double> limInf(n);
    vector<double> limSup(n);

    for (int i = 0; i < n; i++) {
        cout << "Digite o parametro de ajuste 'a' para o foguete " << i + 1 << ": ";
        cin >> valoresA[i];

        gerarIntervaloAutomatico(valoresA[i], limInf[i], limSup[i]);
        cout << AMARELO << "  -> Isolamento gerado analiticamente (e^a): [" 
             << defaultfloat << setprecision(4) << limInf[i] << ", " << limSup[i] << "]\n\n" << RESET;
    }

    cout << NEGRITO << "Digite a precisao desejada (epsilon, ex: 0.00001): " << RESET;
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

    cout << "\n" << CIANO << sepResposta << "\n";
    cout << "                                QUADRO RESPOSTA (RAIZES E ERROS)\n";
    cout << sepResposta << "\n" << RESET;
    
    cout << left << setw(8) << "Foguete" << " | "
         << setw(8) << "Valor a" << " | "
         << setw(25) << "Bisseccao (Raiz | Erro)" << " | "
         << setw(25) << "Pos. Falsa (Raiz | Erro)" << " | "
         << setw(25) << "Newton (Raiz | Erro)" << " | "
         << setw(10) << "Estado" << "\n";
    cout << sepResposta << "\n";

    for (int i = 0; i < n; i++) {
        ostringstream bStr, pfStr, nrStr;
        bStr << fixed << setprecision(casasPrecision) << resultadosB[i].raiz << " (" << scientific << setprecision(1) << resultadosB[i].erroAbs << ")";
        pfStr << fixed << setprecision(casasPrecision) << resultadosPF[i].raiz << " (" << scientific << setprecision(1) << resultadosPF[i].erroAbs << ")";
        nrStr << fixed << setprecision(casasPrecision) << resultadosNR[i].raiz << " (" << scientific << setprecision(1) << resultadosNR[i].erroAbs << ")";

        cout << left << setw(8) << (i + 1) << " | "
             << defaultfloat << setprecision(2) << setw(8) << valoresA[i] << " | "
             << setw(25) << bStr.str() << " | "
             << setw(25) << pfStr.str() << " | "
             << setw(25) << nrStr.str() << " | ";

        bool explosao = (resultadosB[i].raiz > 2.0) || (resultadosPF[i].raiz > 2.0) || (resultadosNR[i].raiz > 2.0);
        
        if (explosao) {
            cout << VERMELHO << left << setw(10) << "[EXPLOSAO]" << RESET << "\n";
        } else {
            cout << VERDE << left << setw(10) << "[SEGURO]" << RESET << "\n";
        }
    }
    cout << sepResposta << "\n\n\n";

    cout << CIANO << "----------------------------------------------------------------------------------------------------\n";
    cout << "                                QUADRO COMPARATIVO DETALHADO\n";
    cout << "----------------------------------------------------------------------------------------------------\n" << RESET;
    cout << "Epsilon utilizado: " << scientific << epsilon << defaultfloat << "\n\n";

    for (int i = 0; i < n; i++) {
        ostringstream ossIsol;
        ossIsol << "[" << defaultfloat << setprecision(3) << limInf[i] << ", " << limSup[i] << "]";

        cout << CIANO << sepFoguete << "\n" << RESET;
        cout << NEGRITO << " FOGUETE " << (i + 1) 
             << "   |   Valor a: " << defaultfloat << setprecision(2) << valoresA[i] 
             << "   |   Isolamento: " << ossIsol.str() << RESET << "\n";
        cout << CIANO << sepFoguete << "\n" << RESET;

        cout << left << setw(16) << "Metodo" << " | "
             << setw(16) << "Raiz" << " | "
             << setw(12) << "Iteracoes" << " | "
             << setw(20) << "Erro Absoluto" << " | "
             << setw(20) << "Erro Relativo" << "\n";
        cout << sepMetodos << "\n";

        cout << left << setw(16) << "Bisseccao" << " | "
             << fixed << setprecision(casasPrecision) << setw(16) << resultadosB[i].raiz << " | "
             << setw(12) << resultadosB[i].iteracoes << " | "
             << scientific << setprecision(2) << setw(20) << resultadosB[i].erroAbs << " | "
             << scientific << setprecision(2) << setw(20) << resultadosB[i].erroRel << "\n";

        cout << left << setw(16) << "Pos. Falsa" << " | "
             << fixed << setprecision(casasPrecision) << setw(16) << resultadosPF[i].raiz << " | "
             << setw(12) << resultadosPF[i].iteracoes << " | "
             << scientific << setprecision(2) << setw(20) << resultadosPF[i].erroAbs << " | "
             << scientific << setprecision(2) << setw(20) << resultadosPF[i].erroRel << "\n";

        cout << left << setw(16) << "Newton" << " | "
             << fixed << setprecision(casasPrecision) << setw(16) << resultadosNR[i].raiz << " | "
             << setw(12) << resultadosNR[i].iteracoes << " | "
             << scientific << setprecision(2) << setw(20) << resultadosNR[i].erroAbs << " | "
             << scientific << setprecision(2) << setw(20) << resultadosNR[i].erroRel << "\n\n";
    }

    return 0;
}