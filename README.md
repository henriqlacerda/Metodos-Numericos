# Metodos Numericos
> Trabalho 01
---

Este repositório foi criado com o objetivo de auxiliar o grupo no trabalho 01 que tem como tema raízes de equações. Assim, dividimos as tarefas em algumas partes:

## 1. Líder e Integrador (C++/Linux) - Henrique
**Responsabilidade central:** Coordenar o andamento da equipe, estruturar o programa base e realizar o envio.  
**Tarefas:** Criar a interface de texto do programa em C/C++ que recebe os dados de entrada: número de foguetes ($n$), o parâmetro $a$ de cada foguete e a precisão $\epsilon$. Integrar os códigos dos desenvolvedores em um único arquivo, compilar o projeto em ambiente Linux garantindo que o executável não tenha ligações dinâmicas (LIBs estáticas), e enviar o arquivo final compactado.   

**Tudo feito**

## 2. Desenvolvedor 1 (Método da Bissecção) - Chimecho
**Responsabilidade central:** Lidar com a primeira exigência algorítmica do Tema 01.   
**Tarefas:** Implementar em C/C++ o algoritmo do método da Bissecção aplicado exclusivamente à equação do foguete espacial $f(d)=a*d-d*ln(d)$. Estruturar o retorno da função para que ela entregue a raiz calculada, o número de iterações e o erro final.      

**Tudo feito**

## 3. Desenvolvedor 2 (Método da Posição Falsa) - Caio
**Responsabilidade central:** Lidar com a segunda exigência algorítmica do Tema 01.   
**Tarefas:** Implementar em C/C++ o algoritmo do método da Posição Falsa para calcular o deslocamento $d$. Manter a mesma estrutura de dados do Desenvolvedor 1 para que o Líder consiga mesclar os códigos facilmente.      

**Tudo feito**

## 4. Desenvolvedor 3 (Método de Newton-Raphson) - Diego
**Responsabilidade central:** Lidar com a terceira e mais complexa exigência algorítmica do Tema 01.   
**Tarefas:** Calcular matematicamente a derivada da função $f(d)=a*d-d*ln(d)$ e implementar o método de Newton-Raphson em C/C++. Implementar travas matemáticas no código para o caso da derivada se aproximar de zero durante as iterações.      

**Tudo feito**

## 5. Engenheiro de Testes e Geração de Quadros - Max
**Responsabilidade central:** Criar os dados de saída requisitados (outputs) usando o código integrado.   
**Tarefas:** Rodar o sistema usando o teste padrão obrigatório ($a=1$, isolamento = (2, 3) e $\epsilon=10^{-5}$). Alimentar o sistema com dados variados para montar o quadro resposta (com os erros de cada foguete) e o quadro comparativo (mostrando isolamento, raízes e dados para cada método executado).   

**O que falta fazer?:** Tudo
  
## 6. Analista Matemático - ?
**Responsabilidade central:** Cumprir o item "g" do escopo do projeto.   
**Tarefas:** Avaliar os resultados e quadros gerados pelo Membro 5 e redigir uma análise detalhada sobre o efeito da variação do valor do parâmetro $a$ sobre o comportamento de cada método. Explicar, por exemplo, qual método convergiu mais rápido, qual teve mais dificuldade dependendo do valor de $a$, e por que isso ocorreu. Esta análise formará a "Conclusão" da apresentação.      

**O que falta fazer?:** Tudo

## 7. Estruturador da Apresentação - ?
**Responsabilidade central:** Garantir os 3,0 pontos destinados à etapa visual e oral.   
**Tarefas:** Montar os slides contendo obrigatoriamente Introdução, Metodologia, Exemplos e Conclusão. Como o tempo total é de apenas 15 minutos (mais 5 minutos de dúvidas), este membro deve dividir o roteiro e cronometrar as falas para que os 7 consigam falar de forma fluida sem estourar o tempo.   

**O que falta fazer?:** Tudo

---

## OBS's

@Max olhe tudo: se tá retornando tudo certo, se n tá faltando nd q o Bento pediu, etc.

@Davi faz a análise completa pls. Tem um ngc p estimar a raiz que a gnt implementou no código tem que ter isso e talvez tenha outras coisas tb. Enfim, tem que olhar o código todo e analisar matematicamente a função tb.