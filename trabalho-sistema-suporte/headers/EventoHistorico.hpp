#ifndef EVENTO_HISTORICO_HPP
#define EVENTO_HISTORICO_HPP

#include<string>

class EventoHistorico{
    private:
        std::string dataHorario;
        std::string descricao;
        EventoHistorico* proximo; 
    public:
        EventoHistorico(const std::string& dataHorario, const std::string& descricao);
        ~EventoHistorico();

        std::string getDataHorario() const;
        std::string getDescricao() const;

        EventoHistorico* getProximo() const;
        void setProximo(EventoHistorico* proximo);
};

#endif