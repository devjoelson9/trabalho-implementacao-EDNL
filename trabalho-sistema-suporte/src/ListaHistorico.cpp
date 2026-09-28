#include "../headers/ListaHistorico.hpp"
#include <iostream>
#include <ctime>
#include <iomanip>
#include <sstream>

ListaHistorico::ListaHistorico() : inicio(nullptr) {}

ListaHistorico::ListaHistorico(const ListaHistorico& other) : inicio(nullptr) {
    if (other.inicio == nullptr) return;
    
    EventoHistorico* atual = other.inicio;
    EventoHistorico* ultimo = nullptr;
    
    while (atual != nullptr) {
        EventoHistorico* novo = new EventoHistorico(atual->getDataHorario(), atual->getDescricao());
        if (inicio == nullptr) {
            inicio = novo;
        } else {
            ultimo->setProximo(novo);
        }
        ultimo = novo;
        atual = atual->getProximo();
    }
}

ListaHistorico& ListaHistorico::operator=(const ListaHistorico& other) {
    if (this == &other) return *this;

    EventoHistorico* atual = inicio;
    while (atual != nullptr) {
        EventoHistorico* proximo = atual->getProximo();
        delete atual;
        atual = proximo;
    }
    inicio = nullptr;

    EventoHistorico* origem = other.inicio;
    EventoHistorico* ultimo = nullptr;

    while (origem != nullptr) {
        EventoHistorico* novo = new EventoHistorico(origem->getDataHorario(), origem->getDescricao());
        if (inicio == nullptr) {
            inicio = novo;
        } else {
            ultimo->setProximo(novo);
        }
        ultimo = novo;
        origem = origem->getProximo();
    }

    return *this;
}

ListaHistorico::~ListaHistorico() {
    EventoHistorico* atual = inicio;
    while (atual != nullptr) {
        EventoHistorico* proximo = atual->getProximo();
        delete atual;
        atual = proximo;
    }
}

void ListaHistorico::adicionarEvento(const std::string& descricao) {
    time_t agora = time(0);
    tm* tempoLocal = localtime(&agora);

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << tempoLocal->tm_mday << "/"
        << std::setw(2) << tempoLocal->tm_mon + 1 << "/"
        << tempoLocal->tm_year + 1900 << " "
        << std::setw(2) << tempoLocal->tm_hour << ":"
        << std::setw(2) << tempoLocal->tm_min << ":"
        << std::setw(2) << tempoLocal->tm_sec;

    EventoHistorico* novo = new EventoHistorico(oss.str(), descricao);
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

void ListaHistorico::exibirHistorico() const {
    EventoHistorico* atual = inicio;
    while (atual != nullptr) {
        std::cout << "[" << atual->getDataHorario() << "] " << atual->getDescricao() << std::endl;
        if (atual->getProximo() != nullptr) {
            std::cout << "    v" << std::endl;
        }
        atual = atual->getProximo();
    }
}