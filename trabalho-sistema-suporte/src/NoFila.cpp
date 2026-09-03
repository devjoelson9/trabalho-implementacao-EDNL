#include "../headers/NoFila.hpp"

NoFila::NoFila(Chamado chamado)
    : chamadoRef(chamado), proximo(nullptr) {}

NoFila::~NoFila() {}

Chamado NoFila::getChamadoRef() const {
    return chamadoRef;
}

NoFila* NoFila::getProximo() const {
    return proximo;
}

void NoFila::setProximo(NoFila* proximo) {
    this->proximo = proximo;
}