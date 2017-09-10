#ifndef MOD1_LISTA3
#define MOD1_LISTA3

#include <string>

struct AvlNode
{
    int _key;
    
    //fator de balanceamento = hd-he
    int _balance_factor;
    
    AvlNode* _up;
    AvlNode* _left;
    AvlNode* _right;
};

class Avl
{
public:
    //Cria uma arvore vazia
    Avl();
    
    //Cria uma arvore com um primeiro elemento
    Avl(int key);
    
    //Cria uma arvore a partir de outra
    Avl(const Avl& orig);
    
    //Destroi a arvore
    virtual ~Avl();
    
    //Retorna a altura da arvore
    int height();
    
    //Insere um elemento na arvore
    void insert(int key);
    
    //Exibe a arvore no formato
    // <raiz<sub-arvore esquerda><sub-arvore direita>>
    void show(const std::string& title);
    
    /** Funcoes para percorrer a arvore em ordem: **/
    
    //Posiciona o cursor no primeiro elemento
    bool first();
    
    //Posiciona o cursor no ultimo elemento
    bool last();
    
    //Atualiza o no cursor para o proximo elemento
    bool next();
    
    //Atualiza o no cursor para o elemento anterior
    bool prev();
    
    //Exibe o valor do no cursor atual
    int value();
    
private:
    
    /* Mantenha as funcoes privadas necessarias
     * criadas para a Abb e crie as funcoes
     * (recursivas ou nao) que julgar necessarias
     * para a Avl */
    
    //Funcao recursiva para exibir a arvore
    void show_rec(AvlNode* node);
    
    //Funcao para destruir a arvore
    void freeAvl();
    
    //Funcao recursiva para calcular a altura
    int height_rec(AvlNode *root);
    
    //Funcao recursiva para inserir novo elemento
    AvlNode * insert_rec(AvlNode * root, int key);
    
    //Funcao para rotacionar a direita
    AvlNode * rr_rotation(AvlNode * root);
    
    //Funcao para rotacionar a esquerda
    AvlNode * ll_rotation(AvlNode * root);
    
    //Funcao para rotacionar a esquerda e depois a direita
    AvlNode * lr_rotation(AvlNode * root);
    
    //Funcao para rotacionar a direita e depois a esquerda
    AvlNode * rl_rotation(AvlNode * root);
    
    //Funcao para verificar a necessidade de rotacao
    AvlNode * balance(AvlNode * root);
    
private:
    AvlNode* _root;
    AvlNode* _cursor;
};

#endif
