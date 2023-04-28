//
// Created by student on 12.06.2022.
//

#include "model/Repository.h"
#include "exceptions/LogicException.h"
#include <vector>

#include "model/Client.h"
#include "model/Rent.h"
#include "model/Room.h"


template <class T>
Repository<T>::Repository() = default;

template <class T>
Repository<T>::~Repository<T>() {}

//Ptrs:
template
class Repository<ClientPtr>;

template
class Repository<RentPtr>;

template
class Repository<RoomPtr>;


template <class T>
T Repository<T>:: get(unsigned int id) const{

    if(size()<=id){

        throw LogicException("Zle numer indkesu");
    }
    return elements[id];

}

template <class T>
void Repository<T>::add(T element) {

    if(element!= nullptr){

        elements.push_back(element);

    }else{
        throw LogicException("Nie wolno dodawać nulla\n");
    }

}

template <class T>
T Repository<T>::find(const std::function<bool(T)> &predicate) const {

        for(int i = 0; i < size(); i++){

            T element = get(i);

            if(predicate(element)){

                return element;
            }
        }

    return nullptr;

}

template <class T>
std::vector<T> Repository<T>::findAll(const std::function<bool(T)> &predicate) const {

    //result
    std::vector<T> result;
    for(int i = 0; i < size(); ++i){

        T element = get(i);

        if(predicate(element)){

            result.push_back(element);
        }
    }

    return result;

}
template<class T>
int Repository<T>::size() const {
    return elements.size();
};

template<class T>
std::string Repository<T>::report() const {

    std::string lan; //tworzymy zmienna lancuchowa - lan

    for(int i =0; i < size() ; i++){

        lan = lan + (get(i)->getInfo()+"\n");
    }
    return lan;


}
//remove
template<class T>
void Repository<T>::remove(T element) {

    int i =0;
    while(i<size()){

        if(element == get(i))
        {
            elements.erase(elements.begin()+i);
        }
        i++;
    }
}
