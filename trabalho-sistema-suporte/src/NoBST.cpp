#include "../headers/NoBST.hpp"

NoBST::NoBST(Chamado chamado)
    : chamado(chamado), esquerdo(nullptr), direito(nullptr), pai(nullptr) {}

NoBST::~NoBST() {}

Chamado NoBST::getChamado() const {
    return chamado;
}

Chamado& NoBST::getChamado() {
    return chamado;
}

NoBST* NoBST::getEsquerdo() const {
    return esquerdo;
}

NoBST* NoBST::getDireito() const {
    return direito;
}

NoBST* NoBST::getPai() const {
    return pai;
}

void NoBST::setEsquerdo(NoBST* esquerdo) {
    this->esquerdo = esquerdo;
    if (esquerdo != nullptr) {
        esquerdo->setPai(this);
    }
}

void NoBST::setDireito(NoBST* direito) {
    this->direito = direito;
    if (direito != nullptr) {
        direito->setPai(this);
    }
}

void NoBST::setPai(NoBST* pai) {
    this->pai = pai;
}

void NoBST::setChamado(const Chamado& chamado) {
    this->chamado = chamado;
}