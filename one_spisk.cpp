#include <iostream>
#include <string>
using namespace std;   

template<typename T>
class List
{
public:
    List();
    ~List();

    void push_front(T data); // добавление эл-та в начало списка
    void push_back(T data); // добавление эл в конец списка
    void insert(T value, int index); // добавление эл-та по указонному индоксу
    
    void pop_front(); // удаление 1-ого эл-та в списке
    void pop_back(); // удаление последнего эл-та
    void removeAt(int index); // удаление эл-та по указонному индоксу
    void clear(); // удаление всего списка
   
    int GetSize() {return Size;} // размер списка
    T& operator[](const int index); // Переопределение оператора []

private:
    template<typename T1>
    class Node // класс эл-та   
    {
    public:
        Node *pNext; // указатель на следущий эл-т
        T1 data; // данные эл-та
        
        Node(T1 data=T1(), Node *pNext=nullptr)
        {
            this->data = data;
            this->pNext = pNext;
        }
    };

    int Size; // счетчик эл-тов
    Node<T> *head; // указатель на первый эл-т нашего списка
};


template<typename T>
List<T>::List()
{
    Size = 0;
    head = nullptr;
}

template<typename T>
List<T>::~List()
{
    clear();
}


template<typename T>
void List<T>::push_front(T data)
{
    head = new Node<T>(data, head); // создаем новый эл-т head и присваиваем адресс старого head к новому head
    Size++;
}

template<typename T>
void List<T>::push_back(T data)
{
    if ((head == nullptr)) // проверяем, не пустой ли наш список 
    {
        head = new Node<T>(data); // создаем эл-т с даннами data
    }
    else 
    {
        Node<T> *current = this->head; // временно присваиваем значение нашего заголовка 

        while (current->pNext != nullptr) // ищем эл-т, у которого адресс указывает на nullptr, т.е. ищем последний эл-т нашего списка
        {
            current = current->pNext; 
        }
        current->pNext = new Node<T>(data); // пересваиваем адресс эл-та, который указывал на nullptr, на адресс нового в конец добавленного эл-та
    }
    Size++;
}

template<typename T> 
void List<T>::insert(T data, int index)
{
    if (index == 0)
    {
        push_front(data);
    }
    else   
    {
        Node<T> *previous = this->head; // временно присваиваем адресс первого эл-та

        for (int i = 0; i < index-1; i++) // ищем предыдущий эл-т нашего индекса
        {
            previous = previous->pNext;
        }

        Node<T> *newNode = new Node<T>(data, previous->pNext); // создаем эл-т и передаем ему данные data и адресс следующего эл-та относительно previous
        previous->pNext = newNode; // к предыдущему эл-ту относительно нашего эл-та, который мы добовляем, в его поле pNext добовляем адресс нашего текущего эл-та 
        Size++;
    }
    
}


template<typename T>
void List<T>::pop_front()
{
    Node<T> *temp = head; // присваиваем адресс первого эл-та 
    head = head->pNext; // переменной head присваиваем адресс следующего эл-та
    delete temp; // удаляем первый эл-т
    Size--;
} 

template<typename T>
void List<T>::pop_back()
{
    removeAt(Size-1);
}

template<typename T>
void List<T>::clear()
{
    while (Size)
    {
        pop_front();
    }
}

template<typename T>
void List<T>::removeAt(int index)
{
    if (index == 0)
    {
        pop_front();
    }
    else
    {
        Node<T> *previous = this->head;
        for (int i = 0; i < index-1; i++) // ищем предыдущий эл-т нашего индекса
        {
            previous = previous->pNext;
        }

 
        Node<T> *toDelete = previous->pNext; // присваиваем адресс эл-та, который хотим удалить
        previous->pNext = toDelete->pNext; // к предыдущему эл-ту относительно нашего эл-та, который хотим удалить, 
                                           // в его поле pNext добовляем адресс следующего эл-та относительно нашего эл-та, который хотим удалить
        delete toDelete;
        Size--;
    }
}


template<typename T>
T& List<T>::operator[](const int index)
{
    int counter = 0;
    Node<T> *current = this->head;
    while (current != nullptr)
    {
        if (counter == index)
        {
            return current->data;
        }
        current = current->pNext;
        counter++;
    }
}

//Переопределение оператора <<
template<typename T>
ostream& operator<<(ostream& out, List<T>& lst) {
    int Size = lst.GetSize();
    
    for (int i = 0; i < Size; i++)
    {
        out << i << "-й: " << lst[i] << endl;
    }
    return out;
}

int main() {
    List<int> lst;

    cout << "push_front (Добавление эл-та в начало списка) " << endl;
    lst.push_front(5);
    lst.push_front(7);
    lst.push_front(67);
    cout << lst;

    cout << endl << "push_back (Добавление эл-та в конец списка) " << endl;
    lst.push_back(101);
    cout << lst;

    cout << endl << "insert (добавление эл-та с индексом 2 и со значением 99) " << endl;
    lst.insert(99, 2);
    cout << lst;

    cout << endl << "pop_front (удаление первого эл-та списка) " << endl;
    lst.pop_front();
    cout << lst;

    cout << endl << "pop_back (удаление последнего эл-та списка) " << endl;
    lst.pop_back();
    cout << lst;

    cout << endl << "removeAt (удаление эл-та с индексом 1) " << endl;
    lst.removeAt(1);
    cout << lst;

    cout << endl << "Эл-ов в списке: " << lst.GetSize() << endl << "Выполняю метод clear" << endl; 
    lst.clear();
    cout << "Эл-ов в списке: " << lst.GetSize() << endl;
    
    return 0;
}


