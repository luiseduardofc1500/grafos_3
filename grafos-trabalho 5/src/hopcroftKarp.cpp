#include "hopcroftKarp.hpp"

typedef std::vector<std::vector<bool>> ArestasMarcadas;

ArestasMarcadas marcarArestasIniciais(const GrafoBiPartido &g)
{
    auto arestasMarcadas = std::vector<std::vector<bool>>(g.a.size(), std::vector<bool>(g.b.size()));
    auto nivel = 0;
    for (size_t y = nivel; y < g.matrizAdjacencia.size(); y++)
    {
        for (size_t x = nivel; x < g.matrizAdjacencia.size(); x++)
        {
            if (g.matrizAdjacencia[y][x])
            {
                arestasMarcadas[y][x] = true;
                nivel++;
                break;
            }
        }
    }

    return arestasMarcadas;
}

std::vector<int> indicesVerticesANaoMarcados(
    const std::vector<Vertice> &verticesA,
    const ArestasMarcadas &arestasMarcadas)
{
    auto vertices = std::vector<int>();
    for (size_t y = 0; y < arestasMarcadas.size(); y++)
    {
        auto marcado = false;
        for (size_t x = 0; x < arestasMarcadas[0].size(); x++)
        {
            if (arestasMarcadas[y][x])
            {
                marcado = true;
                break;
            }
        }

        if (!marcado)
        {
            vertices.push_back(y);
        }
    }
    return vertices;
}

ArestasMarcadas bfsAlternado(
    const GrafoBiPartido &g,
    const ArestasMarcadas &arestasMarcadas,
    const std::vector<int> &indicesVerticesNaoMarcados)
{
    auto resultadoBusca = ArestasMarcadas(arestasMarcadas.size(), std::vector<bool>(arestasMarcadas[0].size()));

    auto verticesAencontrados = std::vector<Vertice>();

    auto inicio = indicesVerticesNaoMarcados[0];
    auto indiceVerticeAtual = 0;
    for (size_t y = 0; y < g.a.size(); y++)
    {
        if (inicio == y)
        {
            indiceVerticeAtual = y;
        }
    }

    while (true)
    {
        // Vai para B pela primeira aresta não marcada
        auto indiceVerticeB = 0;
        for (size_t x = 0; x < g.b.size(); x++)
        {
            if (g.matrizAdjacencia[indiceVerticeAtual][x] && !arestasMarcadas[indiceVerticeAtual][x])
            {
                indiceVerticeB = x;
                resultadoBusca[indiceVerticeAtual][x] = true;
                verticesAencontrados.push_back(g.a[indiceVerticeAtual]);
                break;
            }
        }

        // Volta para A pela lista de arestas marcadas
        bool caminhoEncontrado = false;
        for (size_t y = 0; y < g.a.size(); y++)
        {
            if (g.matrizAdjacencia[y][indiceVerticeB] && arestasMarcadas[y][indiceVerticeB] && !resultadoBusca[y][indiceVerticeB])
            {
                caminhoEncontrado = true;
                resultadoBusca[y][indiceVerticeB] = true;
                indiceVerticeAtual = y;
                break;
            }
        }
        if (!caminhoEncontrado)
        {
            break;
        }
    }

    return resultadoBusca;
}

std::vector<Aresta> hopcroftKarp(const GrafoBiPartido &g)
{
    auto arestasMarcadas = marcarArestasIniciais(g);

    while (true)
    {
        const auto indicesVerticesNaoMarcados = indicesVerticesANaoMarcados(g.a, arestasMarcadas);
        if (indicesVerticesNaoMarcados.empty())
        {
            break;
        }

        const auto resultadoBfs = bfsAlternado(g, arestasMarcadas, indicesVerticesNaoMarcados);
        for (size_t y = 0; y < resultadoBfs.size(); y++)
        {
            for (size_t x = 0; x < resultadoBfs[0].size(); x++)
            {
                if (resultadoBfs[y][x])
                {
                    arestasMarcadas[y][x] = !arestasMarcadas[y][x];
                }
            }
        }
        break;
    }

    auto arestas = std::vector<Aresta>();
    for (size_t y = 0; y < arestasMarcadas.size(); y++)
    {
        for (size_t x = 0; x < arestasMarcadas[0].size(); x++)
        {
            if (arestasMarcadas[y][x])
            {
                arestas.push_back(Aresta{.v1 = g.a[y], .v2 = g.b[x]});
            }
        }
    }
    return arestas;
}
