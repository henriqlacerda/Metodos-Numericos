#include "entrada_saida.h"

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

namespace {

constexpr int N_MAX = 100;
constexpr double TOL = 1e-9;  // evita alarme falso por arredondamento quando |d| = limite

const char* const RESET    = "\033[0m";
const char* const VERMELHO = "\033[1;31m";
const char* const VERDE    = "\033[1;32m";

// aceita ponto ou vírgula decimal e fração (ex: -7/3)
bool converter(std::string s, double& v) {
    std::replace(s.begin(), s.end(), ',', '.');
    const std::size_t barra = s.find('/');
    if (barra != std::string::npos) {
        double num = 0.0, den = 0.0;
        if (!converter(s.substr(0, barra), num) ||
            !converter(s.substr(barra + 1), den) || den == 0.0) return false;
        v = num / den;
        return std::isfinite(v);
    }
    char* fim = nullptr;
    v = std::strtod(s.c_str(), &fim);
    return !s.empty() && *fim == '\0' && std::isfinite(v);
}

// repete a pergunta até receber um número válido
double lerNumero(const std::string& rotulo) {
    while (true) {
        std::cout << rotulo << " = " << std::flush;
        std::string s;
        if (!(std::cin >> s)) {
            std::cerr << "\nEntrada encerrada.\n";
            std::exit(1);
        }
        double v = 0.0;
        if (converter(s, v)) return v;
        std::cout << "  Valor inválido, digite um número.\n";
    }
}

int lerInteiro(const std::string& rotulo, int minimo, int maximo) {
    while (true) {
        const double v = lerNumero(rotulo);
        if (v >= minimo && v <= maximo && v == std::floor(v)) return static_cast<int>(v);
        std::cout << "  Digite um inteiro de " << minimo << " a " << maximo << ".\n";
    }
}

}  // namespace

void lerSistema(Matriz& A, Vetor& f) {
    std::cout << "Dados: 1 = padrão do enunciado, 2 = digitar\n";
    if (lerInteiro("Opção", 1, 2) == 1) {
        A = {{3, -2, 1}, {1, -3, 4}, {9, 4, -5}};
        f = {8, 6, 11};
    } else {
        const int n = lerInteiro("n (número de deslocamentos)", 1, N_MAX);
        A.assign(n, Vetor(n));
        f.assign(n, 0.0);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                A[i][j] = lerNumero("A[" + std::to_string(i + 1) + "][" + std::to_string(j + 1) + "]");
        for (int i = 0; i < n; ++i)
            f[i] = lerNumero("f[" + std::to_string(i + 1) + "]");
    }

    std::cout << "\nSistema [A | f]:\n";
    for (std::size_t i = 0; i < f.size(); ++i) {
        for (double a : A[i]) std::cout << std::setw(10) << a;
        std::cout << "  |" << std::setw(10) << f[i] << '\n';
    }
}

void imprimirResultado(const Vetor& d, double limite) {
    // guarda o formato para não afetar o que o main imprime depois
    const std::ios::fmtflags formato = std::cout.flags();
    const std::streamsize precisao = std::cout.precision();

    std::cout << std::fixed << std::setprecision(6) << '\n';
    double maior = 0.0;
    int acima = 0;
    bool invalido = false;
    for (std::size_t i = 0; i < d.size(); ++i) {
        const double modulo = std::fabs(d[i]);
        std::cout << "d" << i + 1 << " = " << d[i] << " cm   |d" << i + 1 << "| = " << modulo << " cm";
        if (!std::isfinite(d[i])) {
            invalido = true;
        } else if (modulo > limite + TOL) {
            ++acima;
            std::cout << "   <-- ALERTA: passou de " << limite << " cm";
        }
        maior = std::max(maior, modulo);
        std::cout << '\n';
    }

    if (invalido) {
        std::cout << VERMELHO << "RESULTADO NUMÉRICO INVÁLIDO: não é possível avaliar o foguete." << RESET << '\n';
    } else if (acima > 0) {
        std::cout << VERMELHO << "[EXPLOSÃO] " << acima << " deslocamento(s) acima do limite." << RESET << '\n';
    } else {
        std::cout << VERDE << "[SEGURO] margem de " << std::setprecision(2)
                  << std::max(0.0, (limite - maior) / limite * 100) << "%" << RESET << '\n';
    }

    std::cout.flags(formato);
    std::cout.precision(precisao);
}