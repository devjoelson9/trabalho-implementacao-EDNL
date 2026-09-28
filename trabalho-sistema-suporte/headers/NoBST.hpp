#ifndef NO_BST_HPP
#define NO_BST_HPP

#include "Chamado.hpp"

class NoBST{
    private:
        Chamado chamado;
        NoBST* esquerdo;
        NoBST* direito;
        NoBST* pai;
    public:
        NoBST(Chamado chamado);
        ~NoBST();

        Chamado getChamado() const;
        Chamado& getChamado();
        NoBST* getEsquerdo() const;
        NoBST* getDireito() const;
        NoBST* getPai() const;
        void setEsquerdo(NoBST* esquerdo);
        void setDireito(NoBST* direito);
        void setPai(NoBST* pai);
        void setChamado(const Chamado& chamado);
    };
#endif