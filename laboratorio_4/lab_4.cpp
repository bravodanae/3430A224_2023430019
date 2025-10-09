#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

// ESTRUCTURA DEL NODO
struct Node {
    int info;      
    Node* left;     // puntero al hijo izquierdo
    Node* right;    // puntero al hijo derecho
};

// CREAR UN NUEVO NODO
Node* createNode(int data) {
    Node* newNode = new Node;  // reservar memoria para el nuevo nodo
    newNode->info = data;      // asignar el valor al nodo
    newNode->left = nullptr;   // inicializar hijo izquierdo en null
    newNode->right = nullptr;  // inicializar hijo derecho en null
    return newNode;            // retornar el nodo creado
}

// INSERTAR NODO EN EL ABB
void insertNode(Node*& root, int data) {
    if (root == nullptr) {          // si el arbol esta vacio
        root = createNode(data);    // crear el nodo como raiz
        return;
    }

    if (data < root->info) {        // si el dato es menor que la raiz
        insertNode(root->left, data);  // insertar recursivamente en el subarbol izquierdo
    } else if (data > root->info) { // si el dato es mayor que la raiz
        insertNode(root->right, data); // insertar recursivamente en el subarbol derecho
    } else {
        cout << "Numero repetido, no se inserta " << endl; // no permitir duplicados
    }
}

// BUSCAR UN VALOR EN EL ARBOL
bool search(Node* root, int data) {
    if (root == nullptr) return false;       // si el nodo es null, no se encontro
    if (data == root->info) return true;    // si el dato coincide, se encontro
    if (data < root->info) return search(root->left, data);   // buscar en el subarbol izquierdo
    else return search(root->right, data);                   // buscar en el subarbol derecho
}

// ENCONTRAR EL MENOR VALOR (PARA ELIMINAR)
Node* findMin(Node* root) {
    while (root != nullptr && root->left != nullptr) // recorrer hasta el nodo mas a la izquierda
        root = root->left;
    return root; // retornar el nodo con el valor minimo
}

// ELIMINAR UN NODO DEL ARBOL BINARIO
Node* deleteNode(Node* root, int data) {
    if (root == nullptr) {
        cout << "El numero no existe." << endl;
        return root; // no existe el nodo
    }

    if (data < root->info)
        root->left = deleteNode(root->left, data);   // eliminar en subarbol izquierdo
    else if (data > root->info)
        root->right = deleteNode(root->right, data); // eliminar en subarbol derecho
    else {
        // Caso 1: sin hijos
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            return nullptr;
        }
        // Caso 2: un solo hijo
        else if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Caso 3: dos hijos
        Node* temp = findMin(root->right);        // encontrar el minimo en el subarbol derecho
        root->info = temp->info;                  // reemplazar valor
        root->right = deleteNode(root->right, temp->info); // eliminar nodo duplicado
    }
    return root;
}

// MODIFICAR UN NODO
void modifyNode(Node*& root, int oldValue, int newValue) {
    if (!search(root, oldValue)) {         // verificar que el valor a modificar exista
        cout << "El valor a modificar no existe." << endl;
        return;
    }
    if (search(root, newValue)) {          // verificar que el nuevo valor no exista
        cout << "El nuevo valor ya existe en el arbol." << endl;
        return;
    }
    root = deleteNode(root, oldValue);     // eliminar el valor antiguo
    insertNode(root, newValue);            // insertar el nuevo valor
    cout << "Valor modificado correctamente." << endl;
}

// RECORRIDOS DEL ARBOL
void preOrder(Node* root) {
    if (root == nullptr) return;
    cout << root->info << " ";    // procesar nodo actual
    preOrder(root->left);         // recorrer subarbol izquierdo
    preOrder(root->right);        // recorrer subarbol derecho
}

void inOrder(Node* root) {
    if (root == nullptr) return;
    inOrder(root->left);          // recorrer subarbol izquierdo
    cout << root->info << " ";    // procesar nodo actual
    inOrder(root->right);         // recorrer subarbol derecho
}

void postOrder(Node* root) {
    if (root == nullptr) return;
    postOrder(root->left);        // recorrer subarbol izquierdo
    postOrder(root->right);       // recorrer subarbol derecho
    cout << root->info << " ";    // procesar nodo actual
}

// FUNCION PARA GENERAR EL GRAFO (Graphviz)
void recorrer(Node* node, ofstream& fp) {
    if (node != nullptr) {
        // si existe hijo izquierdo
        if (node->left != nullptr) {
            fp << node->info << "->" << node->left->info << ";" << endl;
        } else { 
            string cad = to_string(node->info) + "i";
            fp << "\"" << cad << "\" [shape=point];" << endl;
            fp << node->info << "->\"" << cad << "\";" << endl;
        }

        // si existe hijo derecho
        if (node->right != nullptr) {
            fp << node->info << "->" << node->right->info << ";" << endl;
        } else { 
            string cad = to_string(node->info) + "d";
            fp << "\"" << cad << "\" [shape=point];" << endl;
            fp << node->info << "->\"" << cad << "\";" << endl;
        }

        recorrer(node->left, fp);     // recorrer subarbol izquierdo
        recorrer(node->right, fp);    // recorrer subarbol derecho
    }
}


// GENERAR Y MOSTRAR EL GRAFO
void visualize(Node* root) {
    if (root == nullptr) {
        cout << "El arbol esta vacio." << endl;
        return;
    }

    ofstream fp("arbol.txt");         // abrir archivo para graphviz
    if (!fp.is_open()) {
        cout << "Error al crear archivo arbol.txt" << endl;
        return;
    }

    fp << "digraph G {" << endl;
    fp << "node [style=filled fillcolor=yellow];" << endl;
    recorrer(root, fp);               // generar nodos y aristas
    fp << "}" << endl;
    fp.close();

    cout << "Archivo arbol.txt generado correctamente." << endl;
    cout << "Creando imagen arbol.png ..." << endl;

    system("dot -Tpng -o arbol.png arbol.txt");  // generar imagen con Graphviz
    system("eog arbol.png");                     // abrir imagen 
}


// MENU PRINCIPAL
void menu() {
    Node* root = nullptr;    // inicializar arbol vacio
    int opcion, valor, nuevo;

    do {
        cout << endl;
        cout << " MENU ARBOL BINARIO DE BUSQUEDA " << endl;
        cout << "1. Insertar numero" << endl;
        cout << "2. Eliminar numero" << endl;
        cout << "3. Modificar numero" << endl;
        cout << "4. Mostrar recorridos" << endl;
        cout << "5. Visualizar arbol con Graphviz" << endl;
        cout << "6. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese numero a insertar: ";
                cin >> valor;
                insertNode(root, valor);
                break;
            case 2:
                cout << "Ingrese numero a eliminar: ";
                cin >> valor;
                root = deleteNode(root, valor);
                break;
            case 3:
                cout << "Ingrese valor a modificar: ";
                cin >> valor;
                cout << "Ingrese nuevo valor: ";
                cin >> nuevo;
                modifyNode(root, valor, nuevo);
                break;
            case 4:
                cout << "\n--- Preorden ---" << endl;
                preOrder(root);
                cout << "\n--- Inorden ---" << endl;
                inOrder(root);
                cout << "\n--- Posorden ---" << endl;
                postOrder(root);
                cout << endl;
                break;
            case 5:
                visualize(root);
                break;
            case 6:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida " << endl;
        }

    } while (opcion != 6);  // repetir hasta que el usuario elija salir
}


int main() {
    menu();   
    return 0;
}
