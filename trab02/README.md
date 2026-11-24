# Métodos Numéricos
> Trabalho 02

Este repositório foi criado com o objetivo de auxiliar o grupo no trabalho 01 que tem como tema sistemas de equações. Assim, dividimos as tarefas em algumas partes:

| Integrante | Tarefa | Item | Apresentação | Oq falta fazer
|---|---|---|---|---|
| Henrique (líder) | Coordena, integra os módulos, gera o executável estático (-static) e monta o arquivo único para envio | — | Introdução | Tudo |
| Max | Código: fatoração LU (Doolittle) sem pivotamento, substituição progressiva e regressiva, tratamento de pivô nulo | a | Metodologia (LU) | Tudo |
| Chimecho | Código: fatoração LDP, com D e P extraídas de U, resolvendo Ly = f, Dz = y, Px = z | b | Metodologia (LDP) | Tudo |
| Diego | Código: entrada/saída (n, A, f), validação, cálculo do módulo de cada dᵢ e alerta se passar de 2 cm. Também faz o README | suporte a a e b | Exemplos (demo do programa) | Tudo |
| Caio | Calibração com A e f padrão e quadro resposta do LU, variando A e f | c e d (LU) | Exemplos (quadro LU) | Tudo |
| Carlos | Quadro resposta do LDP, variando A e f, e comparação LU × LDP (erro de arredondamento, casos de falha) | d (LDP) | Exemplos (quadro LDP) | Tudo |
| Davi | Análise física do foguete: quais configurações ultrapassam |dᵢ| > 2 cm, margem de segurança, sensibilidade / e / Conclusão | Tudo |

**Ordem de apresentação (15 min)**
- Introdução, Henrique: 2 min
- Metodologia LU, Max: 2 min
- Metodologia LDP, Chimecho: 2 min
- Demo do programa, Diego: 3 min
- Quadros LU e LDP, Caio e Carlos: 3 min
- Conclusão, Davi: 2 min
- Folga: 1 min

**Gabarito para conferir o código (a e f do enunciado)**

det(A) = −54. Os pivôs são 3, −7/3 e 54/7, todos não nulos, então a LU sem pivotamento funciona.

- L = [[1, 0, 0], [1/3, 1, 0], [3, −30/7, 1]]
- D = diag(3, −7/3, 54/7)
- P = [[1, −2/3, 1/3], [0, 1, −11/7], [0, 0, 1]]
- y = (8, 10/3, 9/7) e z = (8/3, −10/7, 1/6)
- d = (11/6, −7/6, 1/6) ≈ (1,833; −1,167; 0,167) cm

Como $max | d_i | \approx 1,83 cm < 2 cm$, com os dados padrão o foguete não explode. Mas a folga é de só $\approx 8%$, e isso já é um bom ponto de partida para o Davi na análise.

**Dicas**
- Combinem a assinatura das funções antes de codar (ex.: void lu(const Matriz& A, Matriz& L, Matriz& U)). Assim a integração do Henrique não vira um caos.
- Incluam no quadro um caso com pivô nulo ($A_{1 1} = 0$). A LU sem pivotamento quebra nele, e isso entra na análise.
- Todo mundo precisa estar presente no dia da apresentação. Quem faltar leva 0 naquela parte.