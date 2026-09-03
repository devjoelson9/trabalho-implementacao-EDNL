#include "../headers/ArvoreBST.hpp"
#include <iostream>
#include <queue>

NoBST* ArvoreBST::inserirRec(NoBST* no, Chamado chamado) {
    if (no == nullptr) {
        return new NoBST(chamado);
    }
    if (chamado.getId() < no->getChamado().getId()) {
        no->setEsquerdo(inserirRec(no->getEsquerdo(), chamado));
    } else if (chamado.getId() > no->getChamado().getId()) {
        no->setDireito(inserirRec(no->getDireito(), chamado));
    }
    return no;
}

NoBST* ArvoreBST::removerRec(NoBST* no, int id) {
    if (no == nullptr) return nullptr;

    if (id < no->getChamado().getId()) {
        no->setEsquerdo(removerRec(no->getEsquerdo(), id));
    } else if (id > no->getChamado().getId()) {
        no->setDireito(removerRec(no->getDireito(), id));
    } else {
        if (no->getEsquerdo() == nullptr) {
            NoBST* temp = no->getDireito();
            delete no;
            return temp;
        } else if (no->getDireito() == nullptr) {
            NoBST* temp = no->getEsquerdo();
            delete no;
            return temp;
        }
        NoBST* temp = menorNo(no->getDireito());
        no->setChamado(temp->getChamado());
        no->setDireito(removerRec(no->getDireito(), temp->getChamado().getId()));
    }
    return no;
}

NoBST* ArvoreBST::buscarRec(NoBST* no, int id) {
    if (no == nullptr || no->getChamado().getId() == id) {
        return no;
    }
    if (id < no->getChamado().getId()) {
        return buscarRec(no->getEsquerdo(), id);
    }
    return buscarRec(no->getDireito(), id);
}

NoBST* ArvoreBST::menorNo(NoBST* no) {
    NoBST* atual = no;
    while (atual && atual->getEsquerdo() != nullptr) {
        atual = atual->getEsquerdo();
    }
    return atual;
}

void ArvoreBST::emOrdemRec(NoBST* no) {
    if (no != nullptr) {
        emOrdemRec(no->getEsquerdo());
        std::cout << "ID: " << no->getChamado().getId() << std::endl;
        emOrdemRec(no->getDireito());
    }
}

void ArvoreBST::preOrdemRec(NoBST* no) {
    if (no != nullptr) {
        std::cout << "ID: " << no->getChamado().getId() << std::endl;
        preOrdemRec(no->getEsquerdo());
        preOrdemRec(no->getDireito());
    }
}

void ArvoreBST::posOrdemRec(NoBST* no) {
    if (no != nullptr) {
        posOrdemRec(no->getEsquerdo());
        posOrdemRec(no->getDireito());
        std::cout << "ID: " << no->getChamado().getId() << std::endl;
    }
}

int ArvoreBST::alturaRec(NoBST* no) {
    if (no == nullptr) return -1;
    int altEsq = alturaRec(no->getEsquerdo());
    int altDir = alturaRec(no->getDireito());
    return 1 + std::max(altEsq, altDir);
}

int ArvoreBST::contarRec(NoBST* no) {
    if (no == nullptr) return 0;
    return 1 + contarRec(no->getEsquerdo()) + contarRec(no->getDireito());
}

void ArvoreBST::listarIntervaloRec(NoBST* no, int idInicio, int idFim) {
    if (no == nullptr) return;
    if (no->getChamado().getId() > idInicio) {
        listarIntervaloRec(no->getEsquerdo(), idInicio, idFim);
    }
    if (no->getChamado().getId() >= idInicio && no->getChamado().getId() <= idFim) {
        std::cout << "ID: " << no->getChamado().getId() << std::endl;
    }
    if (no->getChamado().getId() < idFim) {
        listarIntervaloRec(no->getDireito(), idInicio, idFim);
    }
}

void ArvoreBST::contarStatusRecursivo(NoBST* no, int& abertos, int& emAtendimento, int& resolvidos, int& cancelados) {
    if (no == nullptr) return;

    if (no->getChamado().getStatus() == Status::ABERTO) abertos++;
    else if (no->getChamado().getStatus() == Status::EM_ATENDIMENTO) emAtendimento++;
    else if (no->getChamado().getStatus() == Status::RESOLVIDO) resolvidos++;
    else if (no->getChamado().getStatus() == Status::CANCELADO) cancelados++;

    contarStatusRecursivo(no->getEsquerdo(), abertos, emAtendimento, resolvidos, cancelados);
    contarStatusRecursivo(no->getDireito(), abertos, emAtendimento, resolvidos, cancelados);
}

ArvoreBST::ArvoreBST() : raiz(nullptr) {}

ArvoreBST::~ArvoreBST() {}

bool ArvoreBST::inserir(Chamado chamado) {
    if (buscarRec(raiz, chamado.getId()) != nullptr) {
        return false;
    }
    raiz = inserirRec(raiz, chamado);
    return true;
}

Chamado ArvoreBST::buscar(int id) {
    NoBST* no = buscarRec(raiz, id);
    if (no != nullptr) {
        return no->getChamado();
    }
    return Chamado(-1, "", "", Categoria::HARDWARE, Prioridade::BAIXA);
}

bool ArvoreBST::remover(int id) {
    if (buscarRec(raiz, id) == nullptr) {
        return false;
    }
    raiz = removerRec(raiz, id);
    return true;
}

void ArvoreBST::listarEmOrdem() {
    emOrdemRec(raiz);
}

Chamado ArvoreBST::buscarMenorID() {
    NoBST* no = menorNo(raiz);
    if (no != nullptr) {
        return no->getChamado();
    }
    return Chamado(-1, "", "", Categoria::HARDWARE, Prioridade::BAIXA);
}

Chamado ArvoreBST::buscarMaiorID() {
    NoBST* no = raiz;
    if (no == nullptr) {
        return Chamado(-1, "", "", Categoria::HARDWARE, Prioridade::BAIXA);
    }
    while (no->getDireito() != nullptr) {
        no = no->getDireito();
    }
    return no->getChamado();
}

int ArvoreBST::getAltura() {
    return alturaRec(raiz);
}

int ArvoreBST::getQuantidadeTotal() {
    return contarRec(raiz);
}

void ArvoreBST::listarPorIntervalo(int idInicio, int idFim) {
    listarIntervaloRec(raiz, idInicio, idFim);
}

void ArvoreBST::percursoPreOrdem() {
    preOrdemRec(raiz);
}

void ArvoreBST::percursoPosOrdem() {
    posOrdemRec(raiz);
}

void ArvoreBST::percursoEmLargura() {
    if (raiz == nullptr) return;

    std::queue<NoBST*> fila;
    fila.push(raiz);

    while (!fila.empty()) {
        NoBST* no = fila.front();
        fila.pop();

        std::cout << "ID: " << no->getChamado().getId() << std::endl;

        if (no->getEsquerdo() != nullptr) {
            fila.push(no->getEsquerdo());
        }
        if (no->getDireito() != nullptr) {
            fila.push(no->getDireito());
        }
    }
}

void ArvoreBST::obterContagemStatus(int& abertos, int& emAtendimento, int& resolvidos, int& cancelados) {
    abertos = emAtendimento = resolvidos = cancelados = 0;
    contarStatusRecursivo(raiz, abertos, emAtendimento, resolvidos, cancelados);
}