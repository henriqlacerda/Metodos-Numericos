#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip> // Formatação dos quadros

using namespace std;

// Estrutura padronizada que os métodos devem retornar
struct ResultadoMetodo {
    double raiz;
    int iteracoes;
    double erroFinal;
    bool convergiu; // Útil p caso do método falhar
};

// ---
// ESPAÇO PARA A INTEGRAÇÃO DOS CÓDIGOS DOS MÉTODOS
// ---

// Função f(d) = a*d - d*ln(d)
double f(double d, double a) {
    return a * d - d * log(d);
}

// Chimecho (Bissecção)
ResultadoMetodo metodoBisseccao(double a, double epsilon, double limiteInferior, double limiteSuperior) {
    ResultadoMetodo res;
    res.raiz = 0.0; res.iteracoes = 0; res.erroFinal = 0.0; res.convergiu = false;
    // Chimecho
    return res;
}

// Caio (Posição Falsa)
ResultadoMetodo metodoPosicaoFalsa(double a, double epsilon, double limiteInferior, double limiteSuperior) {
    ResultadoMetodo res;
    res.raiz = 0.0; res.iteracoes = 0; res.erroFinal = 0.0; res.convergiu = false;
    // Caio
    return res;
}

// Diego (Newton-Raphson)
ResultadoMetodo metodoNewtonRaphson(double a, double epsilon, double aproximacaoInicial) {
    ResultadoMetodo res;
    res.raiz = 0.0; res.iteracoes = 0; res.erroFinal = 0.0; res.convergiu = false;
    // Diego
    return res;
}

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
    for (int i = 0; i < n; i++) {
        cout << "Digite o parametro de ajuste 'a' para o foguete " << i + 1 << ": ";
        cin >> valoresA[i];
    }

    cout << "Digite a precisao desejada (epsilon, ex: 0.00001): ";
    cin >> epsilon;

    // Teste padrão
    double limInf = 2.0;
    double limSup = 3.0;
    double chuteInicial = 2.5; // Newton-Raphson

    cout << "\nCalculando...\n\n";

    // Saída
    
    // Preparando o Quadro Resposta
    cout << "---------------------------------------------------------------------------------\n";
    cout << "                                QUADRO RESPOSTA\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Foguete" << setw(10) << "Valor a" << setw(20) << "Erro Bissecção" << setw(20) << "Erro Pos. Falsa" << setw(20) << "Erro Newton" << "\n";
    cout << "---------------------------------------------------------------------------------\n";

    // P ajudar na construção do quadro
    vector<ResultadoMetodo> resultadosB(n), resultadosPF(n), resultadosNR(n);

    for (int i = 0; i < n; i++) {
        double a = valoresA[i];
        
        resultadosB[i] = metodoBisseccao(a, epsilon, limInf, limSup);
        resultadosPF[i] = metodoPosicaoFalsa(a, epsilon, limInf, limSup);
        resultadosNR[i] = metodoNewtonRaphson(a, epsilon, chuteInicial);

        // Imprimindo linha no quadro de respostas
        cout << left << setw(10) << i + 1 
             << setw(10) << a 
             << setw(20) << resultadosB[i].erroFinal 
             << setw(20) << resultadosPF[i].erroFinal 
             << setw(20) << resultadosNR[i].erroFinal << "\n";
    }
    cout << "---------------------------------------------------------------------------------\n\n";

    // Preparando o Quadro Comparativo
    cout << "---------------------------------------------------------------------------------\n";
    cout << "                              QUADRO COMPARATIVO\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << "Isolamento padrao utilizado: (" << limInf << ", " << limSup << ") | Epsilon: " << epsilon << "\n";
    cout << "---------------------------------------------------------------------------------\n";
    cout << left << setw(10) << "Foguete" << setw(25) << "Raiz Bissec. (Iter)" << setw(25) << "Raiz PosFalsa (Iter)" << setw(25) << "Raiz Newton (Iter)" << "\n";
    cout << "---------------------------------------------------------------------------------\n";

    for (int i = 0; i < n; i++) {
        cout << left << setw(10) << i + 1;
        
        cout << fixed << setprecision(5);
        
        cout << resultadosB[i].raiz << " (" << resultadosB[i].iteracoes << " it)      " << resultadosPF[i].raiz << " (" << resultadosPF[i].iteracoes << " it)      " << resultadosNR[i].raiz << " (" << resultadosNR[i].iteracoes << " it)\n";
    }
    cout << "---------------------------------------------------------------------------------\n";

    return 0;
}