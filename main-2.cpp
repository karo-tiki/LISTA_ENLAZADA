//lista enlazada circular
#include <iostream>
#include <functional> 
using namespace std;
template <class EN>
struct nodo {
    EN val;
    nodo<EN> *next;
    nodo(EN v, nodo<EN> *n = nullptr) {
        val = v;
        next = n;
    }
};
template <class T, class functor>
struct lista_c {
    nodo<T> *head = NULL;
    functor compare;

    bool find(T va);
    void add(T va);
    void del(T va);
    void print();
};
template <class T, class functor>
void lista_c<T, functor>::add(T va) {
    if (!find(va)) {
        nodo<T> *nuevo = new nodo<T>(va);
        if (!head) {
            head = nuevo;
            nuevo->next = head;
        } else {
            nodo<T> *temp = head;
            nodo<T> *prev = NULL;

            do {
                if (compare(va, temp->val)) {
                    nuevo->next = temp;

                    if (prev) {
                        prev->next = nuevo;
                    } else {
                        nodo<T> *last = head;
                        while (last->next != head) {
                            last = last->next;
                        }
                        head = nuevo;
                        last->next = head;
                    }
                    return;
                }
                prev = temp;
                temp = temp->next;

            } while (temp != head);

            prev->next = nuevo;
            nuevo->next = head;
        }
    }
}

template <class T, class functor>
bool lista_c<T, functor>::find(T valor) {
    nodo<T> *actual = head;
    if (!head) {
        return false;
    }
    do {
        if (actual->val == valor) {
            return true;
        }
        actual = actual->next;
    } while (actual != head);
    return false;
}

template <class T, class functor>
void lista_c<T, functor>::del(T valor) {
    if (!head) {
        return;
    }
    nodo<T> *temp = head;
    nodo<T> *prev = NULL;
    while (temp->valor != valor) {
        if (temp->next == head) {
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    if (temp->next == head && prev == NULL) {
        head = NULL;
        delete temp;
        return;
    }
    if (temp == head) {
        prev = head;
        while (prev->next != head) {
            prev = prev->next;
        }
        head = temp->next;
        prev->next = head;
        delete temp;
    }
    if (temp->next == head) {
        prev->next = head;
        delete temp;
    } else {
        prev->next = temp->next;
        delete temp;
    }
}

template <class T, class functor>
void lista_c<T, functor>::print() {
    if (!head) {
        return;
    }
    nodo<T> *temp = head;
    cout<<"head-> ";
    do {
        cout<<temp->val<<"->";
        temp = temp->next;
    } while (temp != head);
    cout<<"head";
    cout << endl;
}

int main() {
    //lista_c<int, greater<int>> lista;
    lista_c<int, less<int>> lista;
    lista.add(1);
    lista.add(5);
    lista.add(5);
    lista.add(7);
    lista.add(10);
    lista.add(15);
    cout<<"lista enlazada circular"<<endl;
    lista.print();

    return 0;
}
