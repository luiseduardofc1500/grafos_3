#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono> 
#include <cstdlib>
#include <ctime>
#include "hopcroftKarp.hpp"

void gerarInstanciaAleatoriaESalvar(int numDisciplinas, int numSalasHorarios, const std::string& nomeArquivo) {
    GrafoBiPartido instancia;

    for (int i = 0; i < numDisciplinas; ++i) {
        instancia.a.push_back("Disciplina" + std::to_string(i));
    }

    for (int i = 0; i < numSalasHorarios; ++i) {
        instancia.b.push_back("Sala-Horario" + std::to_string(i));
    }

    instancia.matrizAdjacencia.resize(numDisciplinas, std::vector<bool>(numSalasHorarios, false));
    for (int i = 0; i < numDisciplinas; ++i) {
        for (int j = 0; j < numSalasHorarios; ++j) {
            instancia.matrizAdjacencia[i][j] = rand() % 2 == 1;
        }
    }

    // Salvar instância em um formato compatível
    std::ofstream arquivo(nomeArquivo);
    if (arquivo.is_open()) {
        arquivo << "GrafoBiPartido g;\n";
        arquivo << "g.a = {";
        for (const auto& disciplina : instancia.a) {
            arquivo << "\"" << disciplina << "\", ";
        }
        arquivo << "};\n";

        arquivo << "g.b = {";
        for (const auto& salaHorario : instancia.b) {
            arquivo << "\"" << salaHorario << "\", ";
        }
        arquivo << "};\n";

        arquivo << "g.matrizAdjacencia = {\n";
        for (const auto& linha : instancia.matrizAdjacencia) {
            arquivo << "    {";
            for (bool valor : linha) {
                arquivo << (valor ? "true" : "false") << ", ";
            }
            arquivo << "},\n";
        }
        arquivo << "};\n";

        arquivo.close();
        std::cout << "Instância salva em '" << nomeArquivo << "'." << std::endl;
    } else {
        std::cerr << "Erro ao abrir o arquivo: " << nomeArquivo << std::endl;
    }
}





int main(int argc, char const *argv[])
{
    srand(static_cast<unsigned int>(time(nullptr)));
    //gerarInstanciaAleatoriaESalvar(30, 30, "instanciaCriada.txt");
GrafoBiPartido g;
g.a = {"Web-I", "Web-II", "Grafos", "APOO", "FMC-2", "BIOINFO"};
g.b = {"Sala1-Manha", "Sala1-Tarde", "Sala1-Noite", "Sala2-Manha", "Sala2-Tarde", "Sala3-Manha" };
g.matrizAdjacencia = {
    {true, false, true, false, true, false},
    {false, true, false, false, false, true},
    {true, false, false, false, false, true},
    {true, true, true, false, false, false},
    {true, true, true, false, false, false},
    {true, false, false, true, false, true},
};



     // Início da medição de tempo
    auto start_time = std::chrono::high_resolution_clock::now();

    auto arestas = hopcroftKarp(g);

    // Fim da medição de tempo
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

    // Resultados
    std::cout << "\nResultado do emparelhamento:" << std::endl;
    for (const auto& aresta : arestas)
    {
        std::cout << "(" << aresta.v1 << ", " << aresta.v2 << ")" << std::endl;
    }

    // Exibindo o tempo de execução
    std::cout << "Tempo de execução: " << duration.count() << " microssegundos" << std::endl;

    return 0;
}
