#include "../headers/SistemaSuporte.hpp"
#include <iostream>

SistemaSuporte::SistemaSuporte() {}

SistemaSuporte::~SistemaSuporte() {}

void SistemaSuporte::abrirChamado() {
    int id;
    std::string solicitante, descricao;
    int cat, pri;

    std::cout << "ID do chamado: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Solicitante: ";
    std::getline(std::cin, solicitante);

    std::cout << "Descricao: ";
    std::getline(std::cin, descricao);

    std::cout << "Categoria (1-HARDWARE, 2-SOFTWARE, 3-REDE, 4-SISTEMA, 5-CONTA_ACESSO): ";
    std::cin >> cat;

    std::cout << "Prioridade (1-BAIXA, 2-MEDIA, 3-ALTA, 4-CRITICA): ";
    std::cin >> pri;

    Categoria categoria = static_cast<Categoria>(cat - 1);
    Prioridade prioridade = static_cast<Prioridade>(pri - 1);

    Chamado chamado(id, solicitante, descricao, categoria, prioridade);
    if (arvoreChamados.inserir(chamado)) {
        std::cout << "Chamado aberto com sucesso!" << std::endl;
    } else {
        std::cout << "Erro: ID ja existe!" << std::endl;
    }
}

void SistemaSuporte::buscarChamado() {
    int id;
    std::cout << "ID do chamado: ";
    std::cin >> id;

    Chamado chamado = arvoreChamados.buscar(id);
    if (chamado.getId() != -1) {
        std::cout << "Chamado encontrado!" << std::endl;
        std::cout << "Solicitante: " << chamado.getSolicitante() << std::endl;
        std::cout << "Descricao: " << chamado.getDescricao() << std::endl;
    } else {
        std::cout << "Chamado nao encontrado!" << std::endl;
    }
}

void SistemaSuporte::removerChamado() {
    int id;
    std::cout << "ID do chamado: ";
    std::cin >> id;

    if (arvoreChamados.remover(id)) {
        std::cout << "Chamado removido com sucesso!" << std::endl;
    } else {
        std::cout << "Chamado nao encontrado!" << std::endl;
    }
}

void SistemaSuporte::listarChamados() {
    std::cout << "=== Chamados em Ordem ===" << std::endl;
    arvoreChamados.listarEmOrdem();
}

void SistemaSuporte::listarPorIntervalo() {
    int idInicio, idFim;
    std::cout << "ID Inicio: ";
    std::cin >> idInicio;
    std::cout << "ID Fim: ";
    std::cin >> idFim;

    std::cout << "=== Chamados no Intervalo ===" << std::endl;
    arvoreChamados.listarPorIntervalo(idInicio, idFim);
}

void SistemaSuporte::encaminharParaAtendimento() {
    int id;
    std::cout << "ID do chamado: ";
    std::cin >> id;

    Chamado chamado = arvoreChamados.buscar(id);
    if (chamado.getId() != -1) {
        filaAtendimento.enfileirar(chamado);
        std::cout << "Chamado encaminhado para atendimento!" << std::endl;
    } else {
        std::cout << "Chamado nao encontrado!" << std::endl;
    }
}

void SistemaSuporte::atenderProximo() {
    if (filaAtendimento.estaVazia()) {
        std::cout << "Fila de atendimento vazia!" << std::endl;
        return;
    }

    Chamado chamado = filaAtendimento.desenfileirar();
    std::cout << "Atendendo chamado ID: " << chamado.getId() << std::endl;
    std::cout << "Solicitante: " << chamado.getSolicitante() << std::endl;
}

void SistemaSuporte::consultarHistorico() {
    int id;
    std::cout << "ID do chamado: ";
    std::cin >> id;

    Chamado chamado = arvoreChamados.buscar(id);
    if (chamado.getId() != -1) {
        std::cout << "\nChamado " << chamado.getId() << "\n" << std::endl;
        chamado.atualizarStatus(chamado.getStatus(), "Consulta realizada");
        std::cout << std::endl;
    } else {
        std::cout << "Chamado nao encontrado!" << std::endl;
    }
}

void SistemaSuporte::alterarStatus() {
    int id, status;
    std::cout << "ID do chamado: ";
    std::cin >> id;

    Chamado chamado = arvoreChamados.buscar(id);
    if (chamado.getId() != -1) {
        std::cout << "Novo status (1-ABERTO, 2-EM_ATENDIMENTO, 3-RESOLVIDO, 4-CANCELADO): ";
        std::cin >> status;
        std::cin.ignore();

        std::string observacao;
        std::cout << "Observacao: ";
        std::getline(std::cin, observacao);

        chamado.atualizarStatus(static_cast<Status>(status - 1), observacao);
        std::cout << "Status alterado com sucesso!" << std::endl;
    } else {
        std::cout << "Chamado nao encontrado!" << std::endl;
    }
}

void SistemaSuporte::exibirEstatisticas() {
    int abertos = 0, emAtendimento = 0, resolvidos = 0, cancelados = 0;
    arvoreChamados.obterContagemStatus(abertos, emAtendimento, resolvidos, cancelados);

    std::cout << "\n========= ESTATISTICAS =========" << std::endl;
    std::cout << "\nTotal de chamados: " << arvoreChamados.getQuantidadeTotal() << std::endl;

    Chamado menor = arvoreChamados.buscarMenorID();
    if (menor.getId() != -1) {
        std::cout << "\nMenor ID: " << menor.getId() << std::endl;
    }
    Chamado maior = arvoreChamados.buscarMaiorID();
    if (maior.getId() != -1) {
        std::cout << "Maior ID: " << maior.getId() << std::endl;
    }

    std::cout << "Altura da BST: " << arvoreChamados.getAltura() << std::endl;
    std::cout << "Chamados na fila: " << filaAtendimento.getTamanho() << std::endl;

    std::cout << "Chamados abertos: " << abertos << std::endl;
    std::cout << "Em atendimento: " << emAtendimento << std::endl;
    std::cout << "Resolvidos: " << resolvidos << std::endl;
    std::cout << "Cancelados: " << cancelados << "\n" << std::endl;
}