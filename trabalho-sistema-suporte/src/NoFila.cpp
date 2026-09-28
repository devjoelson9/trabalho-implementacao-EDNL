#include "../headers/NoFila.hpp"

NoFila::NoFila(Chamado* chamado)
    : ponteiroChamado(chamado), proximo(nullptr) {}

NoFila::~NoFila() {}

Chamado* NoFila::getPonteiroChamado() const {
    return ponteiroChamado;
}

NoFila* NoFila::getProximo() const {
    return proximo;
}

void NoFila::setProximo(NoFila* proximo) {
    this->proximo = proximo;
}