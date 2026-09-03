#include "../headers/FilaAtendimento.hpp"
#include <iostream>

FilaAtendimento::FilaAtendimento() : frente(nullptr), tras(nullptr), tamanho(0) {}

FilaAtendimento::~FilaAtendimento() {
    while (!estaVazia()) {
        desenfileirar();
    }
}

void FilaAtendimento::enfileirar(Chamado chamado) {
    NoFila* novo = new NoFila(chamado);
    if (estaVazia()) {
        frente = novo;
    } else {
        tras->setProximo(novo);
    }
    tras = novo;
    tamanho++;
}

Chamado FilaAtendimento::desenfileirar() {
    if (estaVazia()) {
        return Chamado(-1, "", "", Categoria::HARDWARE, Prioridade::BAIXA);
    }
    NoFila* temp = frente;
    Chamado chamado = temp->getChamadoRef();
    frente = frente->getProximo();
    if (frente == nullptr) {
        tras = nullptr;
    }
    delete temp;
    tamanho--;
    return chamado;
}

Chamado FilaAtendimento::espiarFrente() {
    if (estaVazia()) {
        return Chamado(-1, "", "", Categoria::HARDWARE, Prioridade::BAIXA);
    }
    return frente->getChamadoRef();
}

bool FilaAtendimento::estaVazia() {
    return tamanho == 0;
}

int FilaAtendimento::getTamanho() {
    return tamanho;
}