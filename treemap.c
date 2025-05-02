#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {

    TreeMap* new = (TreeMap*) malloc(sizeof(TreeMap));      // Se reserva memoria para el arbol.
    if (new == NULL) return NULL;                           // Si falla la reserva de memoria se retorna NULL.

    new->root = NULL;                                       // Se inicializan los nodos en NULL
    new->current = NULL;
    new->lower_than = lower_than;                           // Se define la función de comparación del arbol como la que entró a la función.

    return new;                                             // Se retorna el arbol.
}

/*
3.- Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). 
Esta función inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo. 
Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. 
Luego crear el nuevo nodo y enlazarlo. 

Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).
*/
void insertTreeMap(TreeMap * tree, void* key, void * value) {

    if (tree == NULL) return;                               // Si el tree es NULL simplemente se retorna sin hacer nada.
    TreeNode* newNode = createTreeNode(key, value);         // Se crea el nuevo nodo con la función createTreeNode.

    if (tree->root == NULL){                                // Si el arbol está vacío se guarda el nuevo nodo como root.
        tree->root = newNode;
        tree->current = newNode;
        return;
    }

    TreeNode* aux = tree->root;                             // Se crea un nodo auxiliar desde root para la búsqueda.
    TreeNode* parent = NULL;                                // Se crea un nodo parent para saber cual será el padre del nodo a insertar.
    
    while (aux != NULL) {                                   // Ciclo que compara por key hasta encontrar una posición válida para insertar.
        if (is_equal(tree, aux->pair->key, key)){           // Si hay una clave igual, se libera la memoria reservada y se retorna.
            free(newNode);
            free(newNode->pair);
            return;
        }

        parent = aux;                                       // Se guarda el parent antes de avanzar.
        if (tree->lower_than(key, aux->pair->key)){
            aux = aux->left;
        }
        else {
            aux = aux->right;
        }
    }

    newNode->parent = parent;                               // Se asigna el parent al nuevo nodo.
    if (tree->lower_than(key, parent->pair->key)) {         // Se usa lower_than para saber si va a la izquierda o a la derecha.
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    tree->current = newNode;                                // Se actualiza el current.
}

TreeNode * minimum(TreeNode * x){

    return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;    // Retornar NULL en caso de que esté vacío.
    TreeNode* aux = tree->root;                             // Se crea un nodo auxiliar desde root para la búsqueda.
    
    while (aux != NULL) {                                   // Ciclo que compara por key hasta que se encuentra, siguiendo la lógica de la función lower_than.
        if (is_equal(tree, aux->pair->key, key)){      
            tree->current = aux;                            // Si se encontró se retorna el pair y se actualiza el current.
            return aux->pair;
        }

        if (tree->lower_than(key, aux->pair->key)){
            aux = aux->left;
        }
        else {
            aux = aux->right;
        }
    }
    
    return NULL;                                             // Si no se encontró retorna NULL.
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
