#include "../headers/FilaAtendimento.hpp"
#include <iostream>

FilaAtendimento::FilaAtendimento() : frente(nullptr), tras(nullptr), tamanho(0) {}

FilaAtendimento::~FilaAtendimento() {
    while (!estaVazia()) {
        desenfileirar();
    }
}

void FilaAtendimento::enfileirar(Chamado* chamado) {
    NoFila* novo = new NoFila(chamado);
    if (estaVazia()) {
        frente = novo;
    } else {
        tras->setProximo(novo);
    }
    tras = novo;
    tamanho++;
}

Chamado* FilaAtendimento::desenfileirar() {
    if (estaVazia()) {
        return nullptr;
    }
    NoFila* temp = frente;
    Chamado* chamado = temp->getPonteiroChamado();
    frente = frente->getProximo();
    if (frente == nullptr) {
        tras = nullptr;
    }
    delete temp;
    tamanho--;
    return chamado;
}

Chamado* FilaAtendimento::espiarFrente() {
    if (estaVazia()) {
        return nullptr;
    }
    return frente->getPonteiroChamado();
}

bool FilaAtendimento::estaVazia() {
    return tamanho == 0;
}

int FilaAtendimento::getTamanho() {
    return tamanho;
}

bool FilaAtendimento::contemChamado(int id) {
    NoFila* atual = frente;
    while (atual != nullptr) {
        if (atual->getPonteiroChamado()->getId() == id) {
            return true;
        }
        atual = atual->getProximo();
    }
    return false;
}

bool FilaAtendimento::removerPorId(int id) {
    NoFila* anterior = nullptr;
    NoFila* atual = frente;

    while (atual != nullptr) {
        if (atual->getPonteiroChamado()->getId() == id) {
            if (anterior == nullptr) {
                frente = atual->getProximo();
            } else {
                anterior->setProximo(atual->getProximo());
            }

            if (atual == tras) {
                tras = anterior;
            }

            delete atual;
            tamanho--;
            return true;
        }

        anterior = atual;
        atual = atual->getProximo();
    }

    return false;
}