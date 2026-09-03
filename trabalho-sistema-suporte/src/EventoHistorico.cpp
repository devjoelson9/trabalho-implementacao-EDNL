#include "../headers/EventoHistorico.hpp"

EventoHistorico::EventoHistorico(const std::string& dataHorario, const std::string& descricao)
    : dataHorario(dataHorario), descricao(descricao), proximo(nullptr) {}

EventoHistorico::~EventoHistorico() {}

std::string EventoHistorico::getDataHorario() const {
    return dataHorario;
}

std::string EventoHistorico::getDescricao() const {
    return descricao;
}

EventoHistorico* EventoHistorico::getProximo() const {
    return proximo;
}

void EventoHistorico::setProximo(EventoHistorico* proximo) {
    this->proximo = proximo;
}