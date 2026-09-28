#include "../headers/Chamado.hpp"
#include <cstdio>
#include <ctime>

Chamado::Chamado(int id, std::string solicitante, std::string descricao, Categoria categoria, Prioridade prioridade)
    : id(id), solicitante(solicitante), descricao(descricao), categoria(categoria), prioridade(prioridade), status(Status::ABERTO) {
    historico.adicionarEvento("Chamado aberto");
}

Chamado::~Chamado() {}

void Chamado::atualizarStatus(const Status& novoStatus, const std::string& observacao) {
    status = novoStatus;
    historico.adicionarEvento(observacao);
}

int Chamado::getId() const {
    return id;
}

std::string Chamado::getSolicitante() const {
    return solicitante;
}

std::string Chamado::getDescricao() const {
    return descricao;
}

Categoria Chamado::getCategoria() const {
    return categoria;
}

Prioridade Chamado::getPrioridade() const {
    return prioridade;
}

Status Chamado::getStatus() const {
    return status;
}

ListaHistorico& Chamado::getHistorico() {
    return historico;
}

std::string Chamado::statusToString(Status stat) {
    switch (stat) {
        case Status::ABERTO: return "ABERTO";
        case Status::EM_ATENDIMENTO: return "EM_ATENDIMENTO";
        case Status::RESOLVIDO: return "RESOLVIDO";
        case Status::CANCELADO: return "CANCELADO";
        default: return "DESCONHECIDO";
    }
}

std::string Chamado::categoriaToString(Categoria cat) {
    switch (cat) {
        case Categoria::HARDWARE: return "Hardware";
        case Categoria::SOFTWARE: return "Software";
        case Categoria::REDE: return "Rede";
        case Categoria::SISTEMA: return "Sistema";
        case Categoria::CONTA_ACESSO: return "Conta/Acesso";
        default: return "DESCONHECIDA";
    }
}

std::string Chamado::prioridadeToString(Prioridade pri) {
    switch (pri) {
        case Prioridade::BAIXA: return "Baixa";
        case Prioridade::MEDIA: return "Media";
        case Prioridade::ALTA: return "Alta";
        case Prioridade::CRITICA: return "Critica";
        default: return "DESCONHECIDA";
    }
}