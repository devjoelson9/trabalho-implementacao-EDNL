#ifndef LISTA_HISTORICO_HPP
#define LISTA_HISTORICO_HPP

#include "EventoHistorico.hpp"
#include <string>

class ListaHistorico{
    private:
        EventoHistorico* inicio;
    public:
        ListaHistorico();
        ListaHistorico(const ListaHistorico& other);
        ListaHistorico& operator=(const ListaHistorico& other);
        ~ListaHistorico();

        void adicionarEvento(const std::string& descricao);
        void exibirHistorico() const;
};

#endif