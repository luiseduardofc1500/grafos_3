#ifndef HOPCROFT_KARP_HPP
#define HOPCROFT_KARP_HPP

#include <iostream>
#include <string>
#include <vector>

// É um vértice. Armazenado como um rótulo.
typedef std::string Vertice;

// É uma aresta.
struct Aresta
{
    Vertice v1;
    Vertice v2;
};

// É uma matriz específica para grafos bi-partidos, pois os vértices de A são
// as linhas e os vértices de B são as colunas.
typedef std::vector<std::vector<bool>> MatrizAdjacencia;

// É um grafo bi-partido.
struct GrafoBiPartido
{
    std::vector<Vertice> a;
    std::vector<Vertice> b;
    MatrizAdjacencia matrizAdjacencia;
};

std::vector<Aresta> hopcroftKarp(const GrafoBiPartido &g);

#endif
