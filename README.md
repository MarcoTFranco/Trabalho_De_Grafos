# Trabalho Prático Final - GCC218: Algoritmos em Grafos

Trabalho desenvolvido para a disciplina GCC218 - Algoritmos em Grafos da Universidade Federal de Lavras (UFLA), sob orientação do Prof. Mayron César O. Moreira.

O objetivo deste trabalho é otimização de rotas de transporte urbano com foco em minimizar a distância máxima entre pontos consecutivos. Baseado em grafos e variações do Problema do Caixeiro Viajante (TSP), o projeto explora algoritmos de otimização para melhorar eficiência e experiência dos passageiros.

# Descrição do Problema
Uma empresa de transportes urbanos deseja otimizar a rota de uma linha de ônibus. A linha possui n pontos aos quais o motorista deve realizar uma parada, com a condição de que todos os pontos sejam visitados exatamente uma vez, e ao fim do trajeto, o motorista deve retornar ao ponto inicial. O objetivo é minimizar a distância máxima entre dois pontos quaisquer do percurso.

# Objetivos
### O trabalho visa:
- Modelar o problema usando grafos.
- Escolher a estrutura de dados mais apropriada para o problema.
- Implementar um algoritmo eficiente para encontrar a solução.

# Tecnologias
O projeto foi implementado utilizando C++ e bibliotecas da standard library.

# Instruções para Execução
### Clonando o Repositório
Primeiro, clone o repositório para sua máquina local:

```sh
git clone https://github.com/seu-usuario/trabalho-gcc218.git
```
### Compilando o Código
Após clonar o repositório, compile o código com o seguinte comando:

```sh
g++ main.cpp -o tsp_problem
```
### Executando o Programa
Para executar o programa, utilize o comando abaixo, fornecendo o arquivo de entrada e o arquivo de saída como parâmetros:

```sh
./tsp_problem nomeDoArquivoDeEntrada.txt nomeDoArquivoDeSaida.txt
```
>:bulb:: Verifique se o arquivo de entrada está no formato e local correto.

# Autoria
O projeto foi feito pelos alunos [Bernado Diniz](https://github.com/youserz),[Marco Franco](https://github.com/MarcoTFranco).
