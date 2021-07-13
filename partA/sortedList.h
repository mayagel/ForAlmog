//
// Created by Tom Guy on 06/06/2021.
//

#include <stdexcept>

#ifndef EX2_SORTEDLIST_H
#define EX2_SORTEDLIST_H

namespace mtm
{

    template<class T>
    class SortedList
    {
    private:
        class Node //helper class node - the nodes in the list
        {
            T data; //data value - a class T object
            Node *next = nullptr; // the next node in the list

            ~Node(); // d'tor

            T &operator*(); // operator *

            Node &operator=(const Node &other); //operator =

            explicit Node(const T &data_to_insert); // c'tor

            Node(Node &other); // copy c'tor

            Node *getNext(); // return the next node in the list

            void setNext(Node *next); // setter to next

            friend class SortedList<T>;
        };

        Node *head = nullptr; //points to the first node in the list
        Node *tail = nullptr; // points to the next of the last node in the list
        int size = 0; // the number of nodes in the list

        void clear();

    public:

        class const_iterator // ac const iterator for the list
        {
        private:
            class Node *element; // the node that the iterator points to

            class Node *getNext(); // return the next of the current node

            const_iterator operator+(int number); // operator + : receive an integer and return the value of the
            // node in the wanted place. throw out_of_range in case of exception
            void setNext(class Node *next); // set the next to the node that the iterator points to

            explicit const_iterator(class Node *node); // c'tor

        public:
            const_iterator operator++(); //operator ++

            bool operator==(const_iterator iter); // operator ==

            const T &operator*() const; //operator *

            friend class SortedList<T>;

            bool operator!=(const_iterator other); // operator !=
        };

        SortedList() = default; // constructor
        ~SortedList();  // destructor
        SortedList(const SortedList &list);  // copy
        void insert(const T &data);  // insert
        const_iterator begin() const; // return a const_iterator containing the beginning of the list
        const_iterator end() const;  // return the end of the list
        void remove(const_iterator iterator);           // remove
        int length();             // length
        SortedList<T> &operator=(const SortedList &list); // operator =
        template<class condition>
        SortedList<T> filter(condition cond); //return a list containing only values that pass the filter function

        template<class operation>
        SortedList<T> apply(operation func); //return a list containing all the values after the apply changed them.

    };

    template<class T>
    T &SortedList<T>::Node::operator*()
    {
        return data;
    }

    template<class T>
    typename SortedList<T>::Node *SortedList<T>::Node::getNext()
    {
        return next;
    }

    template<class T>
    typename SortedList<T>::Node &SortedList<T>::Node::operator=(const SortedList<T>::Node &other)
    {
        if (&other == this)
        {
            return *this;
        }
        T new_data = other.data;
        delete &data;
        data = new_data;
        return *this;
    }

    template<class T>
    SortedList<T>::Node::Node(const T &data_to_insert) : data(data_to_insert)
    {
    }

    template<class T>
    SortedList<T>::Node::Node(SortedList<T>::Node &other)
    {
        data = *other;
    }

    template<class T>
    void SortedList<T>::insert(const T &data)
    {
        bool inserted = false;
        auto *new_item = new SortedList<T>::Node(data);
        if (size == 0)
        {
            head = new_item;
            new_item->setNext(tail);
            inserted = true;
        }
        if (data < **head)
        {
            new_item->setNext(head);
            head = new_item;
            inserted = true;
        }
        if (!inserted)
        {
            const_iterator item = begin();
            for (item = begin(); item + 1 != end(); ++item)
            {
                if (data < *(item + 1))
                {
                    new_item->setNext(item.getNext());
                    item.setNext(new_item);
                    inserted = true;
                    break;
                }
            }
            if (!inserted)
            {
                new_item->setNext(tail);
                item.setNext(new_item);
            }
        }

        size++;
    }

    template<class T>
    void SortedList<T>::Node::setNext(SortedList<T>::Node *new_next)
    {
        next = new_next;
    }

    template<class T>
    SortedList<T>::Node::~Node()
    {
        delete next;
    }


    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const
    {
        return const_iterator(head);
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const
    {
        return const_iterator(tail);
    }

    template<class T>
    void SortedList<T>::remove(const_iterator iterator_to_remove)
    {
        if (!((*iterator_to_remove) < (**head)) && !((**head) < (*iterator_to_remove)))
        {
            SortedList<T>::Node *temp = head->getNext();
            head->setNext(nullptr);
            delete head;
            head = temp;
            size--;
            return;
        }
        auto previous = begin();
        for (auto iter = begin(); iter != end(); ++iter)
        {
            if (iterator_to_remove == iter)
            {
                previous.setNext(iter.getNext());
                break;
            }
            previous = iter;
        }
        size--;
    }

    template<class T>
    SortedList<T>::~SortedList()
    {
        delete head;
    }

    template<class T>
    SortedList<T>::SortedList(const SortedList &list)
    {
        for (auto iter = list.begin(); iter != list.end(); ++iter)
        {
            insert(*(iter));
        }
    }

    template<class T>
    int SortedList<T>::length()
    {
        return size;
    }

    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList &list)
    {
        if (&list == this)
        {
            return *this;
        }
        clear();
        for (auto iterator = list.begin(); iterator != list.end(); ++iterator)
        {
            insert(*iterator);
        }
        return *this;
    }

    template<class T>
    template<class condition>
    SortedList<T> SortedList<T>::filter(condition cond)
    {
        SortedList<T> new_list;
        for (auto iterator = begin(); iterator != end(); ++iterator)
        {
            if (cond(*iterator))
            {
                new_list.insert(*iterator);
            }
        }
        return new_list;
    }

    template<class T>
    template<class operation>
    SortedList<T> SortedList<T>::apply(operation func)
    {
        SortedList<T> new_list;
        for (auto iterator = begin(); iterator != end(); ++iterator)
        {
            new_list.insert(func(*iterator));
        }
        return new_list;
    }

    template<class T>
    void SortedList<T>::clear()
    {
        delete head;
        head = nullptr;
        size = 0;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++()
    {
        if (element == nullptr)
        {
            throw std::out_of_range("out of range");
        }
        element = element->getNext();
        return *this;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator==(const_iterator iter)
    {
        return element == iter.element;
    }

    template<class T>
    const T &SortedList<T>::const_iterator::operator*() const
    {
        return **element;
    }


    template<class T>
    typename SortedList<T>::Node *SortedList<T>::const_iterator::getNext()
    {
        return element->next;
    }

    template<class T>
    bool SortedList<T>::const_iterator::operator!=(SortedList::const_iterator other)
    {
        return element != other.element;
    }

    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator+(int number)
    {
        auto ret = *this;
        for (int i = 0; i < number; ++i)
        {
            ++ret;
        }
        return ret;
    }

    template<class T>
    void SortedList<T>::const_iterator::setNext(SortedList<T>::Node *next)
    {
        element->setNext(next);
    }

    template<class T>
    SortedList<T>::const_iterator::const_iterator(SortedList<T>::Node *node)
    {
        element = node;
    }

} // mtm

#endif //EX2_SORTEDLIST_H
