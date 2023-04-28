//
// Created by student on 12.06.2022.
//

#ifndef PENSJONAT_REPOSITORY_H
#define PENSJONAT_REPOSITORY_H

#include <vector>
#include <functional>
#include <string>


template<class T>
class Repository {

private:
    std::vector<T> elements;

public:

    Repository();

    virtual ~Repository();    // destruct
    int size() const;

    T get(unsigned int id) const;

    void add(T element);

    T find(const std::function<bool(T)> &predicate) const;

    std::vector<T> findAll(const std::function<bool(T)> &predicate) const;

    std::string report() const;

    void remove(T element);


};


#endif //PENSJONAT_REPOSITORY_H
