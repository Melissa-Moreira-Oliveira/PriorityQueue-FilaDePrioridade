#ifndef FILADEPRIORIDADE_H
#define FILADEPRIORIDADE_H
#include <iostream>
using namespace std;
template<typename T>
struct Nodo
{
    T elemento;
    int prioridade;//1 = baixa, 2 = media, 3 = alta
    Nodo<T>* anterior;
    Nodo<T>* proximo;
    Nodo(T elemento, int prioridade, Nodo<T>* anterior, Nodo<T>* proximo){
        this->elemento = elemento;
        this->prioridade = prioridade;
        this->anterior = anterior;
        this->proximo = proximo;
    }
};

template<typename T>
struct FilaDePrioridade//duplamente encadeada
{
    int cardinalidade;
    Nodo<T>* inicio;//primeiro elemento
    Nodo<T>* fim;//ultimo elemento
};

template<typename T>
void cria(FilaDePrioridade<T> &fila)
{
    fila.cardinalidade = 0;
    fila.inicio = nullptr;
    fila.fim = nullptr;
}

template<typename T>
bool ehVazia(FilaDePrioridade<T> fila){
    return fila.cardinalidade == 0;
}

template<typename T>
bool existeElemento(FilaDePrioridade<T> fila, T elemento, int prioridade){
    Nodo<T>* atual = fila.inicio;
    while(atual != nullptr){
        if (atual->elemento == elemento && atual->prioridade == prioridade)
            return true;
        atual = atual->proximo;
    }
    return false;
}

template<typename T>
void adiciona(FilaDePrioridade<T> &fila, T elemento, int prioridade){
    if(fila.inicio == nullptr){
        Nodo<T> *novo = new Nodo<T>(elemento, prioridade, nullptr, nullptr);
        fila.inicio = novo;
        fila.fim = novo;
        fila.cardinalidade++;
        return;
    }
    Nodo<T>* novo = new Nodo<T>(elemento, prioridade, fila.fim, nullptr);
    fila.fim->proximo = novo;
    fila.fim = novo;
    fila.cardinalidade++;
}


template<typename T>
void retira(FilaDePrioridade<T> &fila){
    if(ehVazia(fila)) {
        cout << "Fila vazia." << endl;
        return;
    }
    Nodo<T>* atual = fila.inicio;
    Nodo<T>* maiorPrioridade = atual;
    while(atual != nullptr){
        if(atual->prioridade == 3){
            maiorPrioridade = atual;
            break;
        }
        if(atual->prioridade > maiorPrioridade->prioridade)
            maiorPrioridade = atual;
        atual = atual->proximo;
    }
    if(maiorPrioridade == fila.inicio){
        fila.inicio = maiorPrioridade->proximo;
        if(fila.cardinalidade == 1)
            fila.fim = nullptr;
        else
            fila.inicio->anterior = nullptr;
    }
    else if(maiorPrioridade == fila.fim){
        fila.fim = maiorPrioridade->anterior;
        fila.fim->proximo = nullptr;
    }
    else {
        maiorPrioridade->anterior->proximo = maiorPrioridade->proximo;
        maiorPrioridade->proximo->anterior = maiorPrioridade->anterior;
    }
    delete maiorPrioridade;
    fila.cardinalidade--;
}

template<typename T>
void destroi(FilaDePrioridade<T> &fila){
    cout << "Destruindo fila..." << endl;
    if(ehVazia(fila)) {
        cout << "Fila vazia." << endl;
        return;
    }
    Nodo<T> *atual = fila.inicio;
    while(atual != nullptr){
        Nodo<T> *temp = atual;
        atual = atual->proximo;
        delete temp;
    }
    fila.inicio = nullptr;
    fila.fim = nullptr;
    fila.cardinalidade = 0;
}

template<typename T>
void mostraPorPrioridade(FilaDePrioridade<T> fila){
    if(ehVazia(fila)) {
        cout << "Fila vazia." << endl;
        return;
    }
    string prioridade[4] = {"","baixa", "media", "alta"};
    for(int i = 3; i > 0; i--){
        cout << "Prioridade " << prioridade[i] << ": ";
        Nodo<T>* atual = fila.inicio;
        while(atual != nullptr){
            if(atual->prioridade == i)
                cout << atual->elemento << " ";
            atual = atual->proximo;
        }
        cout << endl;
    }
    cout << endl;
}


#endif //FILADEPRIORIDADE_H
