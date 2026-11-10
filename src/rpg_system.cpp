#include <iostream>
#include <cstdlib>
#include "rpg_system.h"
using namespace std;

const size_t MAX_INVENTORY_SIZE = 10;
static float podatekHandlowy = 0.15f;

void pokazEkwipunek(const Player& gracz){
    
    cout << "--- Ekwipunek gracza: " << gracz.imie << "---" <<endl;
    cout << "Zloto: " << gracz.gold << " monet." << endl;

    int i = 1;
    for(const auto& przedmiot : gracz.ekwipunek){
        cout << i << ". " << przedmiot.nazwa << " (Cena: " << przedmiot.basicPrice << " monet)"<<endl;
        i++;
    }
}

void pokazSklep(const Merchant& kupiec){
    
    cout << "--- Asortyment: " << kupiec.imie << "---" <<endl;
    cout << "Kasa: " << kupiec.gold << " monet." << endl;

    int i = 1;
    for(const auto& przedmiot : kupiec.asortyment){
        cout << i << ". " << przedmiot.nazwa << " (Cena: " << przedmiot.basicPrice << " monet)"<<endl;
        i++;
    }
}

bool kupPrzedmiot(Player& gracz, Merchant& kupiec, int idPrzedmiotu){
    for(size_t i=0; i <kupiec.asortyment.size(); i++){
        if(idPrzedmiotu==kupiec.asortyment[i].ID){
            int cena = kupiec.asortyment[i].basicPrice*(1.0f+podatekHandlowy);
            if(gracz.ekwipunek.size()>=MAX_INVENTORY_SIZE){
                cout<<"W inwentarzu niema swobodnego miejsca, transakcja nieudana!"<<endl;
                return false;
            } else if(gracz.gold<cena){
                cout<<"Niedostateczna ilosc kosztow, transakcja nieudana!"<<endl;
                return false;
            } else {
                kupiec.gold += cena;
                gracz.gold -= cena;
                gracz.ekwipunek.push_back(kupiec.asortyment[i]);
                kupiec.asortyment.erase(kupiec.asortyment.begin()+i);
                return true;
            }
        }
    }
    cout << "Kupiec nie znalazł przedmiotu o takim ID." << endl;
    return false;
}

bool sprzedajPrzedmiot(Player& gracz, Merchant& kupiec, int idPrzedmiotu){
    for(size_t i=0; i <gracz.ekwipunek.size(); i++){
        if(idPrzedmiotu==gracz.ekwipunek[i].ID){
            int cena = gracz.ekwipunek[i].basicPrice;
            if(kupiec.gold<cena){
                cout<<"Kupiec nie ma wystarczajacej liczby srodkow."<<endl;
                return false;
            } else {
                kupiec.gold -= cena;
                gracz.gold += cena;
                kupiec.asortyment.push_back(gracz.ekwipunek[i]);
                gracz.ekwipunek.erase(gracz.ekwipunek.begin()+i);
                return true;
            }
        }
    }
    cout << "Nie masz przedmiotu o takim ID!" << endl;
    return false;
}

void czyscEkran() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void czekajNaEnter() {
    cout << "\n[ Nacisnij ENTER, aby kontynuowac... ]";
    cin.ignore(10000, '\n'); 
    cin.get(); 
}

void pokazMape(int aktualnaLokacja) {
    cout << "\n======================================\n";
    cout << "             MAPA SWIATA              \n";
    cout << "======================================\n";

    cout << "  [0] Karczma " << (aktualnaLokacja == 0 ? " <-- [TUTAJ JESTES]" : "") << "\n";
    cout << "       |\n       V\n";
    cout << "  [1] Las     " << (aktualnaLokacja == 1 ? " <-- [TUTAJ JESTES]" : "") << "\n";
    cout << "       |\n       V\n";
    cout << "  [2] Wioska  " << (aktualnaLokacja == 2 ? " <-- [TUTAJ JESTES]" : "") << "\n";
    cout << "       |\n       V\n";
    cout << "  [3] Bagna   " << (aktualnaLokacja == 3 ? " <-- [TUTAJ JESTES]" : "") << "\n";
    cout << "       |\n       V\n";
    cout << "  [4] Jaskinia" << (aktualnaLokacja == 4 ? " <-- [TUTAJ JESTES]" : "") << "\n";

    cout << "======================================\n\n";
}

bool battle(Player& gracz, Enemy potwor){
    czyscEkran();
    cout << "!!! WALKA !!!\n";
    cout << "Na twojej drodze staje " << potwor.nazwa << "!\n";
    czekajNaEnter();

    while(gracz.hp > 0 && potwor.hp > 0){
        czyscEkran();
        cout << "--- " << potwor.nazwa << " (HP: " << potwor.hp << "/" << potwor.maxHp << ") ---\n";
        cout << "BOHATER: " << gracz.imie << " (HP: " << gracz.hp << "/" << gracz.maxHp << ")\n";
        cout << "================================\n";
        cout << "1. Atakuj mieczem\n";
        cout << "2. Uzyj mikstury\n";
        cout << "3. Uciekaj\n> ";

        int akcja;
        cin>>akcja;

        if(akcja == 1){
            potwor.hp -= 20;
            if(potwor.hp>0) gracz.hp -= potwor.maxDamage;
        }

        else if (akcja == 2){
            bool maMiksture = false;
            for (size_t i = 0; i < gracz.ekwipunek.size(); i++) {
                if (gracz.ekwipunek[i].category == ItemCategory::ELIXIR) {
                maMiksture = true;
                gracz.hp += 20;
                if (gracz.hp > gracz.maxHp){
                    gracz.hp = gracz.maxHp; // Blokujemy na maksimum!
                }
                
                gracz.ekwipunek.erase(gracz.ekwipunek.begin() + i);
                cout << "Wypijasz miksture. Czujesz przyplyw sil!\n";
                break;
            }
        }
        if (maMiksture == false) {
            cout << "Przeszukujesz torbe, ale nie masz zadnych mikstur!\n";
        }
        gracz.hp -= potwor.maxDamage; 
        czekajNaEnter();
        }
    
        else if(akcja == 3) {
            cout<<"Uciekasz w panice!";
            czekajNaEnter();
            return true;
        }
        
        else {
        cout<<"Nieznana opcja, tracisz runde!\n";
        gracz.hp -= potwor.maxDamage;
        czekajNaEnter();
    }
    }

    if (gracz.hp <= 0) {
        cout << "Polegles w walce z " << potwor.nazwa << "...\n";
        czekajNaEnter();
        return false; // Gracz nie żyje
    } else {
        cout << "Zabijasz " << potwor.nazwa << " i zdobywasz " << potwor.goldDrop << " zlota!\n";
        gracz.gold += potwor.goldDrop;
        czekajNaEnter();
        return true; // Gracz wygrał
    }
}
