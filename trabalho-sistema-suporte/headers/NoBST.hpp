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
        NoBST(Chamado Chamado);
        ~NoBST();
    };
#endif