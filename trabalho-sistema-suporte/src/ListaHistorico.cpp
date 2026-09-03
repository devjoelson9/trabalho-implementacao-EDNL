#include "../headers/ListaHistorico.hpp"
#include <iostream>

ListaHistorico::ListaHistorico() : inicio(nullptr) {}

ListaHistorico::~ListaHistorico() {
    EventoHistorico* atual = inicio;
    while (atual != nullptr) {
        EventoHistorico* proximo = atual->getProximo();
        delete atual;
        atual = proximo;
    }
}

void ListaHistorico::adicionarEvento(const std::string& dataHorario, const std::string& descricao) {
    EventoHistorico* novo = new EventoHistorico(dataHorario, descricao);
    if (inicio == nullptr) {
        inicio = novo;
    } else {
        EventoHistorico* atual = inicio;
        while (atual->getProximo() != nullptr) {
            atual = atual->getProximo();
        }
        atual->setProximo(novo);
    }
}

void ListaHistorico::exibirHistorico() {
    EventoHistorico* atual = inicio;
    while (atual != nullptr) {
        std::cout << "[" << atual->getDataHorario() << "] " << atual->getDescricao() << std::endl;
        if (atual->getProximo() != nullptr) {
            std::cout << "    \u2193" << std::endl;
        }
        atual = atual->getProximo();
    }
}