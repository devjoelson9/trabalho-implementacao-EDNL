#ifndef NO_FILA_HPP
#define NO_FILA_HPP

#include "Chamado.hpp"

class NoFila{
    private:
        Chamado chamadoRef;
        NoFila* proximo;
    public:
        NoFila(Chamado chamado);
        ~NoFila();

        Chamado getChamadoRef() const;
        NoFila* getProximo() const;
        void setProximo(NoFila* proximo);
    };
#endif