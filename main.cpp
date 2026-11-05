#include <iostream>
#include "rpg_system.h"

using namespace std;

int main(){
    Player gracz = {100, "Kristina", {}};

    Merchant kupiec = {500, "Roche", {
        {1, "Zardzewialy Miecz", 20, ItemRarity::BASIC, ItemCategory::WEAPON},
        {2, "Skorzana Zbroja", 50, ItemRarity::BASIC, ItemCategory::ARMOR},
        {3, "Mikstura Zdrowia", 15, ItemRarity::RARE, ItemCategory::ELIXIR}
    }};

    int wybor = 0;
    while(wybor!=5){
        cout << "\n=== MENU ===" << endl;
        cout << "1. Pokaz moj ekwipunek" << endl;
        cout << "2. Pokaz towar kupca" << endl;
        cout << "3. Kup przedmiot" << endl;
        cout << "4. Sprzedaj przedmiot" << endl;
        cout << "5. Wyjdz" << endl;
        cout << "Wybierz akcje: "<<endl;
        cin >> wybor;
        cout<< " "<<endl;
        cout<< " "<<endl;

        switch(wybor) {
            case 1:
                pokazEkwipunek(gracz);
                break;
            case 2:
                pokazSklep(kupiec);
                break;
            case 3: {
                int id;
                cout << "Podaj ID przedmiotu do kupienia: ";
                cin >> id;
                kupPrzedmiot(gracz, kupiec, id);
                break;
                        
            }
            case 4: {
                int id;
                cout << "Podaj ID przedmiotu ktory chcesz sprzedac: ";
                cin >> id;
                sprzedajPrzedmiot(gracz, kupiec, id);
                break;
            }
            case 5:
                cout << "Bywaj!" << endl;
                break;
            default:
                cout << "Nieznana opcja." << endl;
        }
    }

    return 0;

}

