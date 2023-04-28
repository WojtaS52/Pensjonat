#include <iostream>
#include "interface/InterfaceTerminal.h"
#include "exceptions/ParameterException.h"
#include "exceptions/LogicException.h"
#include "model/Client.h"
#include "model/Address.h"
#include "model/Room.h"
#include "model/Rent.h"
#include "managers/ClientManager.h"
#include "managers/RoomManager.h"
#include "managers/RentManager.h"

using namespace std;

InterfaceTerminal::InterfaceTerminal(const ClientManagerPtr &clientManager, const RoomManagerPtr &roomManager,
                                     const RentManagerPtr &rentManager) : clientManager(clientManager),
                                                                          roomManager(roomManager),
                                                                          rentManager(rentManager) {}

InterfaceTerminal::~InterfaceTerminal() {

}

void InterfaceTerminal::begin(){


    bool log = true;
    char user;
    cout<<"Dzien dobry. Witaj w porgramie obslugujacym pensjonat\n";

    while(log){
        cout<<":---------------------:\n";
        cout<<"Strona glowna:\n";
        cout<<"1)Obsluga klientow\n";
        cout<<"2)Obsluga pokojow\n";
        cout<<"3)Obsluga wynajmem\n";
        cout<<"4)Wyjscie z programu\n";
        cout<<":---------------------:\n";


        cin>>user;


            if(user=='1'){
                client();

            }

            else if(user=='2'){
                room();


            }

            else if(user=='3'){
                rent();

            }

            else if(user=='4'){
                log = false;

            }
            else{
                cout << "Podales wartsc spoza przedzialu [1,4], podaj liczbe jeszcze raz\n";
            }

    }

}
void::InterfaceTerminal::client(){


    bool log = true;
    char user;

    while(log){
        cout<<":---------------------:\n";
        cout<<"1) Rejestracja klienta\n";
        cout<<"2) Informacje o kliencie\n" ;
        cout<<"3) Informacje o wszystkich klientach\n";
        cout<<"4) Archiwizacja(Derejestracja) klienta\n";
        cout<<"5) Powrot do strony glownej\n";
        cout<<":---------------------:\n";
        cin>>user;

        switch(user){
            case '1': {
                string firstName, surname, personalID, country, city, street, number;
                cout << "Podaj imie klienta: \n";
                cin.ignore();
                getline(cin, firstName);
                cout << "\nPodaj nazwisko klienta: \n";
                getline(cin, surname);
                cout << "\nPodaj personalID klienta: \n";
                cin >> personalID;

                cout << "Podaj kraj klienta: \n";
                cin.ignore();
                getline(cin, country);
                cout << "Podaj nazwe miasta klienta: \n";
                getline(cin, city);
                cout << "Podaj nazwe ulicy gdzie klient mieszka: \n";
                getline(cin, street);
                cout << "Podaj numer mieszkania klienta: \n";
                getline(cin, number);

                try {

                    clientManager->addClient(firstName, surname, personalID,
                                             make_shared<Address>(country, city, street, number));

                }
                catch (LogicException &err) {

                    cerr << "Logical error: " << err.what() << "\n";
                }
                catch (ParameterException &err) {

                    cerr << "Parameter error: " << err.what() << "\n";
                }
                break;
            }

            case '2': {
                string personalID;
                cout << "Podaj personalID klienta: \n";
                cin >> personalID;

                ClientPtr client = clientManager->getClient(personalID);

                if (client != nullptr) {
                    cout<<client->getInfo()<<"\n";
                    break;
                }
                cout << "Nie ma danego klienta w bazie danych!\n";

                break;
            }


            case '3':
                cout << clientManager->getClientInfo()<<"\n";
                break;

            case '4': {
                string personalID;
                cout << "Podaj personalID klienta: \n";
                cin >> personalID;

                try {
                    ClientPtr client = clientManager->getClient(personalID);

                    if (client == nullptr) {
                        cout << "Klient o podanym peselu nie istnieje!\n";
                        break;
                    }

                    clientManager->unregisterClient(client);
                }

                catch (ParameterException &err) {
                    cerr << "Parameter error: " << err.what() << endl;
                }
                catch (LogicException &err) {
                    cerr << "Logic error: " << err.what() << "\n";
                }
            }
            case '5':
                log = false;
                break;
            default:
                cout<<"Podales niepoprawna wartosc\n";
                break;

        }

    }




}
void::InterfaceTerminal::room(){

    bool exit = false;
    while (!exit) {
        cout<<":-----------------------------------:\n";
        cout << "1) Zarejestruj(dodaj) nowy pokoj\n";
        cout << "2) Wyswietl informacje o pokoju\n";
        cout << "3) Wyswietl informacje o wszystkich pokojach w pensjonacie\n";
        cout << "4) Wyrejestruj pokoj\n";
        cout << "5) Powrot do menu\n";
        cout<<":-----------------------------------:\n";

        char user;
        cin >> user;

        switch (user) {

            case '1': {
                int basePrice, roomNumber, roomCapacity;
                cout << "Podaj cene(doba): ";
                cin >> basePrice;
                cout << "Podaj numer pokoju: ";
                cin >> roomNumber;
                cout << "Podaj ilosc osob w pokoju: ";
                cin >> roomCapacity;

                try {
                    roomManager->addRoom(basePrice,roomNumber, roomCapacity);

                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }


            case '2': {
                int number;
                cout << "Podaj numer pokoju: ";
                cin >> number;
                RoomPtr room = roomManager->getRoom(number);

                if (room == nullptr) {
                    cout << "Nie posiadamy pokoju o podanym numerze!" << endl;
                    return;
                }

                cout <<room->getInfo()<< endl;
                break;
            }


            case '3':
                cout<< roomManager->getRoomsInfo() << "\n";

                break;


            case '4': {

                int roomNumber;
                cout << "Podaj numer pokoju, ktory chcesz wyrejestrowac: \n";
                cin >> roomNumber;

                try {
                    roomManager->removeRoom(roomManager->getRoom(roomNumber));

                } catch (ParameterException &e) {
                    cerr << "Parameter error: " << e.what() << endl;
                } catch (LogicException &e) {
                    cerr << "Logic error: " << e.what() << endl;
                }
                break;
            }

            case '5':
                exit = true;
                break;

            default:
                cout << "Bledny wybor!\n";
                break;
        }
    }


}

void::InterfaceTerminal::rent(){

    bool exit = false;
    while (!exit) {
        cout<<":-----------------------------------:\n";
        cout << "1) Wynajmij pokoj\n";
        cout << "2) Wyswietl informacje o wynajmie pokoju\n";
        cout << "3) Wyswietl informacje o wszystkich obecnych wynajmowanych pokojach\n";
        cout << "4) Wyswietl informacje o wszystkich archiwalnych wynajmach\n";
        cout << "5) Zakoncz wynajem pokoju\n";
        cout << "6) Powrot do menu\n";
        cout<<":-----------------------------------:\n";

        char user;
        cin >> user;

        switch (user) {

            case '1': {
                string personalID;
                int basePrice, roomCapacity;
                cout << "Podaj numer Id klienta: \n";
                cin >> personalID;

                ClientPtr client = clientManager->getClient(personalID);
                if (client == nullptr) {
                    cout << "Klient nie istnieje!" << endl;
                    return;
                }

                cout << "Podaj cene za pokoj: \n";
                cin >> basePrice;
                cout << "Podaj ilosc osob w pokoju: ";
                cin >> roomCapacity;

                RoomPtr room = roomManager->getRoom(basePrice, roomCapacity);
                if (room == nullptr) {
                    cout << "Nie znaleziono odpowiedniego pokoju!\n";
                    return;
                }

                try {
                    rentManager->rentRoom(client,room);

                } catch (ParameterException &err) {
                    cerr << "Parameter error: " << err.what() << endl;
                } catch (LogicException &err) {
                    cerr << "Logic error: " << err.what() << endl;
                }
                break;
            }

            case '2': {
                int roomNumber;
                cout << "Podaj numer pokoju klienta: ";
                cin >> roomNumber;

                RentPtr rent = rentManager->getRent(roomManager->getRoom(roomNumber));
                if (rent == nullptr) {
                    cout << "Nie znaleziono wynajmu\n";
                    return;
                }

                cout << rent->getInfo() << endl;
                break;
            }

            case '3':
                cout << rentManager->getPresentRentsReport() << endl;
                break;


            case '4':
                cout << rentManager->getArchiveRentsReport() << endl;
                break;

               
            case '5': {
                int number;
                cout << "Podaj numer pokoju: ";
                cin >> number;

                try {
                    rentManager->returnRoom(roomManager->getRoom(number));

                } catch (ParameterException &err) {
                    cerr << "Parameter error: " << err.what() << endl;
                } catch (LogicException &err) {
                    cerr << "Logic error: " << err.what() << endl;
                }
                break;
            }

            case '6':
                exit = true;
                break;

            default:
                cout << "Bledny wybor!" << endl;
                break;
        }
    }




}

