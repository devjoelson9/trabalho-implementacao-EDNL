#ifndef FILA_ATENDIMENTO_HPP
#define FILA_ATENDIMENTO_HPP

#include "NoFila.hpp"

class FilaAtendimento{
    private:
        NoFila* frente;
        NoFila* tras;
        int tamanho;

    public:
        FilaAtendimento();
        ~FilaAtendimento();

        void enfileirar(Chamado chamado);
        Chamado desenfileirar();
        Chamado espiarFrente();
        bool estaVazia();
        int getTamanho();
};

#endif