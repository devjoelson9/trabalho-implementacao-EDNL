#include "../headers/Chamado.hpp"

Chamado::Chamado(int id, std::string solicitante, std::string descricao, Categoria categoria, Prioridade prioridade)
    : id(id), solicitante(solicitante), descricao(descricao), categoria(categoria), prioridade(prioridade), status(Status::ABERTO) {}

Chamado::~Chamado() {}

void Chamado::atualizarStatus(const Status& novoStatus, const std::string& observacao) {
    status = novoStatus;
    historico.adicionarEvento("agora", observacao);
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