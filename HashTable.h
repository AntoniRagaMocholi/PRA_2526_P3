#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2526_P1/ListLinked.h"

template <typename V>
class HashTable : public Dict<V> {

private:
    int n;
    int max;
    ListLinked<TableEntry<V>>* table;

    int h(std::string key) {
        int suma = 0;
        for (int i = 0; i < key.size(); i++)
            suma += int(key.at(i));
        return suma % max;
    }

public:
    HashTable(int size) {
        n = 0;
        max = size;
        table = new ListLinked<TableEntry<V>>[max];
    }

    ~HashTable() {
        delete[] table;
    }

    int capacity() {
        return max;
    }

    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> temp(key);

        if (table[pos].contains(temp))
            throw std::runtime_error("Key '" + key + "' already exists!");

        table[pos].append(TableEntry<V>(key, value));
        n++;
    }

    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> temp(key);

        int index = table[pos].indexOf(temp);
        if (index == -1)
            throw std::runtime_error("Key '" + key + "' not found!");

        return table[pos].get(index).value;
    }

    V remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> temp(key);

        int index = table[pos].indexOf(temp);
        if (index == -1)
            throw std::runtime_error("Key '" + key + "' not found!");

        V val = table[pos].get(index).value;
        table[pos].remove(index);
        n--;
        return val;
    }

    int entries() override {
        return n;
    }

    V operator[](std::string key) {
        return search(key);
    }

    friend std::ostream& operator<<(std::ostream &out, const HashTable<V> &ht) {
        out << "HashTable [entries: " << ht.n
            << ", capacity: " << ht.max << "]\n==============\n\n";

        for (int i = 0; i < ht.max; i++) {
            out << "== Cubeta " << i << " ==\n\n";
            out << "List => " << ht.table[i] << "\n\n";
        }

        out << "==============\n";
        return out;
    }
};

#endif

