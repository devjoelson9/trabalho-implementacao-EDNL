#include "../headers/SistemaSuporte.hpp"
#include <iostream>
#include <limits>

SistemaSuporte::SistemaSuporte() {}

SistemaSuporte::~SistemaSuporte() {}

int SistemaSuporte::lerInteiro(const std::string& mensagem, int min, int max) {
    int valor;
    while (true) {
        std::cout << mensagem;
        if (std::cin >> valor) {
            if (valor >= min && valor <= max) {
                return valor;
            }
            std::cout << "Valor invalido! Digite um numero entre " << min << " e " << max << "." << std::endl;
        } else {
            std::cin.clear();
            std::cout << "Entrada invalida! Digite um numero." << std::endl;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void SistemaSuporte::abrirChamado() {
    int id;
    std::string solicitante, descricao;

    std::cout << "\n--- ABRIR CHAMADO ---\n";
    id = lerInteiro("ID unico: ", 1, 1000000);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Solicitante: ";
    std::getline(std::cin, solicitante);

    std::cout << "Descricao: ";
    std::getline(std::cin, descricao);

    int cat = lerInteiro("Categoria (1-Hardware, 2-Software, 3-Rede, 4-Sistema, 5-Conta/Acesso): ", 1, 5);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    int pri = lerInteiro("Prioridade (1-BAIXA, 2-MEDIA, 3-ALTA, 4-CRITICA): ", 1, 4);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Categoria categoria = static_cast<Categoria>(cat - 1);
    Prioridade prioridade = static_cast<Prioridade>(pri - 1);

    Chamado chamado(id, solicitante, descricao, categoria, prioridade);
    if (arvoreChamados.inserir(chamado)) {
        std::cout << "\nChamado #" << id << " aberto com sucesso!" << std::endl;
    } else {
        std::cout << "\nErro: Ja existe um chamado com o ID " << id << "!" << std::endl;
    }
}

void SistemaSuporte::buscarChamado() {
    int id;
    std::cout << "\nID do chamado para busca: ";
    std::cin >> id;

    Chamado* chamado = arvoreChamados.buscar(id);
    if (chamado != nullptr) {
        std::cout << "\n+---------------------------------------+\n";
        std::cout << "  Chamado #" << chamado->getId() << "\n";
        std::cout << "+---------------------------------------+\n";
        std::cout << "  Solicitante : " << chamado->getSolicitante() << "\n";
        std::cout << "  Descricao   : " << chamado->getDescricao() << "\n";
        std::cout << "  Categoria   : " << Chamado::categoriaToString(chamado->getCategoria()) << "\n";
        std::cout << "  Prioridade  : " << Chamado::prioridadeToString(chamado->getPrioridade()) << "\n";
        std::cout << "  Status      : " << Chamado::statusToString(chamado->getStatus()) << "\n";
        std::cout << "+---------------------------------------+\n";
    } else {
        std::cout << "\nChamado nao encontrado!" << std::endl;
    }
}

void SistemaSuporte::removerChamado() {
    int id;
    std::cout << "\nID do chamado a remover: ";
    std::cin >> id;

    Chamado* ptr = arvoreChamados.buscar(id);
    if (ptr == nullptr) {
        std::cout << "\nChamado nao encontrado!" << std::endl;
        return;
    }

    bool estavaNaFila = filaAtendimento.removerPorId(id);

    arvoreChamados.remover(id);

    if (estavaNaFila) {
        std::cout << "\nChamado #" << id << " tambem foi retirado da fila de atendimento." << std::endl;
    }

    std::cout << "\nChamado #" << id << " removido com sucesso!" << std::endl;
}

void SistemaSuporte::listarChamados() {
    std::cout << "\n=========================================\n";
    std::cout << "       LISTA DE CHAMADOS (ORDEM)         \n";
    std::cout << "=========================================\n";
    arvoreChamados.listarEmOrdem();
    std::cout << "=========================================\n";
}

void SistemaSuporte::listarPorIntervalo() {
    int idInicio, idFim;
    std::cout << "\nID Inicial: ";
    std::cin >> idInicio;
    std::cout << "ID Final: ";
    std::cin >> idFim;

    std::cout << "\n=== CHAMADOS NO INTERVALO [" << idInicio << " a " << idFim << "] ===\n";
    arvoreChamados.listarPorIntervalo(idInicio, idFim);
}

void SistemaSuporte::encaminharParaAtendimento() {
    int id;
    std::cout << "\nID do chamado para encaminhar: ";
    std::cin >> id;

    Chamado* ptr = arvoreChamados.buscar(id);
    if (ptr == nullptr) {
        std::cout << "\nChamado nao encontrado!" << std::endl;
        return;
    }

    if (ptr->getStatus() != Status::ABERTO) {
        std::cout << "\nChamado #" << id << " nao pode ser encaminhado. Status atual: "
                  << Chamado::statusToString(ptr->getStatus()) << std::endl;
        std::cout << "Somente chamados com status ABERTO entram na fila de atendimento." << std::endl;
        return;
    }

    if (filaAtendimento.contemChamado(id)) {
        std::cout << "\nChamado #" << id << " ja esta na fila de atendimento!" << std::endl;
        return;
    }

    filaAtendimento.enfileirar(ptr);
    ptr->registrarEvento("Encaminhado para a fila de atendimento");
    std::cout << "\nChamado #" << id << " encaminhado para a fila de atendimento!" << std::endl;
}

void SistemaSuporte::atenderProximo() {
    if (filaAtendimento.estaVazia()) {
        std::cout << "\nFila de atendimento vazia!" << std::endl;
        return;
    }

    Chamado* chamado = filaAtendimento.desenfileirar();
    arvoreChamados.atualizarStatus(chamado->getId(), Status::EM_ATENDIMENTO, "");

    std::cout << "\n-----------------------------------------\n";
    std::cout << " ATENDENDO PROXIMO CHAMADO: #" << chamado->getId() << "\n";
    std::cout << " Solicitante: " << chamado->getSolicitante() << "\n";
    std::cout << "-----------------------------------------\n";
}

void SistemaSuporte::consultarHistorico() {
    int id;
    std::cout << "\nID do chamado para historico: ";
    std::cin >> id;

    Chamado* chamado = arvoreChamados.buscar(id);
    if (chamado != nullptr) {
        std::cout << "\nChamado " << chamado->getId() << "\n\n";
        chamado->getHistorico().exibirHistorico();
        std::cout << std::endl;
    } else {
        std::cout << "\nChamado nao encontrado!" << std::endl;
    }
}

void SistemaSuporte::alterarStatus() {
    int id;
    std::cout << "\nID do chamado: ";
    std::cin >> id;

    Chamado* chamado = arvoreChamados.buscar(id);
    if (chamado == nullptr) {
        std::cout << "\nChamado nao encontrado!" << std::endl;
        return;
    }

    int status = lerInteiro("Novo status (1-ABERTO, 2-EM_ATENDIMENTO, 3-RESOLVIDO, 4-CANCELADO): ", 1, 4);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string observacao;
    std::cout << "Observacao: ";
    std::getline(std::cin, observacao);

    if (arvoreChamados.atualizarStatus(id, static_cast<Status>(status - 1), observacao)) {
        std::cout << "\nStatus alterado com sucesso!" << std::endl;
    } else {
        std::cout << "\nErro ao alterar status!" << std::endl;
    }
}

void SistemaSuporte::exibirEstatisticas() {
    int abertos = 0, emAtendimento = 0, resolvidos = 0, cancelados = 0;
    arvoreChamados.obterContagemStatus(abertos, emAtendimento, resolvidos, cancelados);

    std::cout << "\n----------- ESTATISTICAS ------------\n\n";
    std::cout << "Total de chamados: " << arvoreChamados.getQuantidadeTotal() << "\n\n";

    Chamado* menor = arvoreChamados.buscarMenorID();
    if (menor != nullptr) {
        std::cout << "Menor ID: " << menor->getId() << "\n";
    } else {
        std::cout << "Menor ID: N/A\n";
    }

    Chamado* maior = arvoreChamados.buscarMaiorID();
    if (maior != nullptr) {
        std::cout << "Maior ID: " << maior->getId() << "\n\n";
    } else {
        std::cout << "Maior ID: N/A\n\n";
    }

    std::cout << "Altura da BST: " << arvoreChamados.getAltura() << "\n\n";
    std::cout << "Chamados na fila: " << filaAtendimento.getTamanho() << "\n\n";

    std::cout << "Chamados abertos: " << abertos << "\n";
    std::cout << "Em atendimento: " << emAtendimento << "\n";
    std::cout << "Resolvidos: " << resolvidos << "\n";
    std::cout << "Cancelados: " << cancelados << "\n";
    std::cout << "\n-------------------------------------\n";
}

void SistemaSuporte::preOrdem() {
    std::cout << "\n=== PERCURSO PRE-ORDEM ===" << std::endl;
    arvoreChamados.percursoPreOrdem();
}

void SistemaSuporte::posOrdem() {
    std::cout << "\n=== PERCURSO POS-ORDEM ===" << std::endl;
    arvoreChamados.percursoPosOrdem();
}

void SistemaSuporte::emLargura() {
    std::cout << "\n=== PERCURSO EM LARGURA ===" << std::endl;
    arvoreChamados.percursoEmLargura();
}

void SistemaSuporte::consultarFrenteFila() {
    Chamado* chamado = filaAtendimento.espiarFrente();

    if (chamado == nullptr) {
        std::cout << "\nFila de atendimento vazia!" << std::endl;
        return;
    }

    std::cout << "\n+---------------------------------------+\n";
    std::cout << "  PRIMEIRO DA FILA (nao retirado)\n";
    std::cout << "+---------------------------------------+\n";
    std::cout << "  Chamado #" << chamado->getId() << "\n";
    std::cout << "  Solicitante : " << chamado->getSolicitante() << "\n";
    std::cout << "  Descricao   : " << chamado->getDescricao() << "\n";
    std::cout << "  Status      : " << Chamado::statusToString(chamado->getStatus()) << "\n";
    std::cout << "+---------------------------------------+\n";
    std::cout << "\nChamados restantes na fila: " << filaAtendimento.getTamanho() << std::endl;
}
