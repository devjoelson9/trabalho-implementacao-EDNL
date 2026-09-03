#ifndef LISTA_HISTORICO_HPP
#define LISTA_HISTORICO_HPP

#include "EventoHistorico.hpp"
#include <string>

class ListaHistorico{
    private:
        EventoHistorico* inicio;
    public:
        ListaHistorico();
        ~ListaHistorico();

        void adicionarEvento(const std::string& dataHorario, const std::string& descricao);
        void exibirHistorico();
};

#endif