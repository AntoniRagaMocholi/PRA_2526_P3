#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>

template <typename V>
class TableEntry {
private:
    std::string key;
    V value;

public:
    
    TableEntry(std::string key, V value) : key(key), value(value) {}

    TableEntry(std::string key) : key(key), value(V()) {}

  
    TableEntry() : key(""), value(V()) {}

   
    std::string getKey() const {
        return key;
    }

   
    V getValue() const {
        return value;
    }

    
    friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key == te2.key;
    }

   
    friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2) {
        return te1.key != te2.key;
    }

   
    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& te) {
        out << "(" << te.key << " => " << te.value << ")";
        return out;
    }
};

#endif
