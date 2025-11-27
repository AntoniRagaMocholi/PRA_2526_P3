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
        int sum = 0;
        for (char c : key) {
            sum += static_cast<int>(c);
        }
        return sum % max;
    }

public:
    HashTable(int size) {
        max = size;
        n = 0;
        table = new ListLinked<TableEntry<V>>[max];
    }
    ~HashTable() {
        delete[] table;
    }
    int capacity() {
        return max;
    }

   
    V operator[](std::string key) {
        return search(key);
    }

    
    void insert(std::string key, V value) override {
        int pos = h(key);
        TableEntry<V> temp(key, value);

        if (table[pos].contains(temp)) {
            throw std::runtime_error("Key already exists");
        }
        table[pos].insertAtEnd(temp);
        n++;
    }

    
    V search(std::string key) override {
        int pos = h(key);
        TableEntry<V> temp(key);

        if (table[pos].contains(temp)) {
            return table[pos].indexOf(temp).getValue();
        }
        throw std::runtime_error("Key not found");
    }

    
    V remove(std::string key) override {
        int pos = h(key);
        TableEntry<V> temp(key);

        if (table[pos].contains(temp)) {
            V value = table[pos].indexOf(temp).getValue();
            table[pos].remove(temp);
            n--;
            return value;
        }
        throw std::runtime_error("Key not found");
    }

   
    int entries() override {
        return n;
    }

    
    friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& ht) {
    	out << "HashTable [entries: " << ht.n << ", capacity: " << ht.max << "]\n";
    	out << "==============\n";
    	for (int i = 0; i < ht.max; ++i) {
        	out << "== Cubeta " << i << " ==\n";
        	out << "List => [";
        	for (auto entry = ht.table[i].begin(); entry != ht.table[i].end(); ++entry) {
            		out << " ('" << entry->data.getKey() << "' => " << entry->data.getValue() << ")";
        }
  		out << "]\n";
    	}
    	out << "==============\n";
   	return out;
    }

};

#endif
