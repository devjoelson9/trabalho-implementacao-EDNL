#ifndef CHAMADO_HPP
#define CHAMADO_HPP

#include "ListaHistorico.hpp"
#include<string>

enum class Categoria{
    HARDWARE,
    SOFTWARE,
    REDE,
    SISTEMA,
    CONTA_ACESSO
};

enum class Prioridade{
    BAIXA,
    MEDIA,
    ALTA,
    CRITICA
};

enum class Status{
    ABERTO,
    EM_ATENDIMENTO,
    RESOLVIDO,
    CANCELADO
};

class Chamado {
    private:
        int id;
        std::string solicitante;
        std::string descricao;
        Categoria categoria;
        Prioridade prioridade;
        Status status;
        ListaHistorico historico;
    public:
        Chamado(int id, std::string solicitante, std::string descricao, Categoria categoria, Prioridade prioridade);
        ~Chamado();

        void atualizarStatus(const Status& novoStatus, const std::string& observacao);

        int getId() const;
        std::string getSolicitante() const;
        std::string getDescricao() const;
        Categoria getCategoria() const;
        Prioridade getPrioridade() const;
        Status getStatus() const;
    };
#endif