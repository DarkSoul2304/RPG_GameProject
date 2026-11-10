#include <iostream>
#include "rpg_system.h"

using namespace std;
string nazwyLokacji[5] = {"Karczma", "Las", "Wioska", "Bagna", "Jaskinia"};

void menuHandlu(Player& gracz, Merchant& kupiec) {
    int wybor = 0;
    while(wybor != 4) {
        czyscEkran(); 
        cout << "\n======================================" << endl;
        cout << "  STOISKO: " << kupiec.imie << " (Kasa: " << kupiec.gold << ")" << endl;
        cout << "======================================" << endl;
        cout << "1. Obejrzyj towary kupca" << endl;
        cout << "2. Kup przedmiot" << endl;
        cout << "3. Sprzedaj swoj przedmiot" << endl;
        cout << "4. Odejdz od stoiska" << endl;
        cout << "> Czego szukasz? ";
        cin >> wybor;

        cout << endl;
        switch(wybor) {
            case 1:
                pokazSklep(kupiec);
                czekajNaEnter();
                break;
            case 2: {
                int id;
                cout << "Podaj ID przedmiotu do kupienia: ";
                cin >> id;
                kupPrzedmiot(gracz, kupiec, id);
                czekajNaEnter();
                break;
            }
            case 3: {
                int id;
                cout << "Podaj ID przedmiotu do sprzedania: ";
                cin >> id;
                sprzedajPrzedmiot(gracz, kupiec, id);
                czekajNaEnter();
                break;
            }
            case 4:
                cout << kupiec.imie << ": Bywaj. I nie zgin za szybko." << endl;
                czekajNaEnter();
                break;
            default:
                cout << "Nieznana opcja." << endl;
                czekajNaEnter();
        }
    }
}

int main() {
    // 1. Inicjalizacja kupcow
    Merchant kupiec_karczma = {500, "Odo", {
        {1, "Zardzewialy Miecz", 20, ItemRarity::BASIC, ItemCategory::WEAPON},
        {2, "Skorzana Zbroja", 50, ItemRarity::BASIC, ItemCategory::ARMOR},
        {3, "Mikstura Zdrowia", 15, ItemRarity::RARE, ItemCategory::ELIXIR}
    }};

    Merchant kupiec_wioska = {1000, "Kaelen", {
        {1, "Stalowy Miecz", 120, ItemRarity::RARE, ItemCategory::WEAPON},
        {2, "Ciezka Zbroja", 200, ItemRarity::EPIC, ItemCategory::ARMOR}
    }};

    // 2. PROLOG I TWORZENIE POSTACI
    czyscEkran();
   
    string podaneImie;
    int wyborKlasy;

    cout << "Deszcz z loskotem uderzal o zgnile deski Karczmy 'Pod Wisielcem'...\n";
    cout << "Karczmarz przeciera kufel i patrzy na Ciebie spode lba.\n";
    cout << "- Jak cie zwa, wedrowcze?\n> ";
    cin >> podaneImie;

    cout << "\n- A, slyszalem to imie. Podobno jestes...\n";
    cout << "1. Zbieglym dezerterem (150 HP, 20 zlota)\n";
    cout << "2. Zrujnowanym szlachcicem (80 HP, 200 zlota)\n";
    cout << "3. Wedrownym alchemikiem (110 HP, 100 zlota)\n> ";
    cin >> wyborKlasy;

    Player gracz;
    gracz.imie = podaneImie;
    gracz.aktualnaLokacja = 0;
    
    switch(wyborKlasy) {
        case 1: gracz.maxHp = 150; gracz.hp = 150; gracz.gold = 20; break;
        case 2: gracz.maxHp = 80; gracz.hp = 80; gracz.gold = 200; break;
        case 3: gracz.maxHp = 110; gracz.hp = 110; gracz.gold = 100; break;
        default: gracz.maxHp = 100; gracz.hp = 100; gracz.gold = 50; break;
    }

    czekajNaEnter();

    int wyborGlowny = 0;
    while(wyborGlowny != 5) {
        czyscEkran();
        
        // HUD - Statystyki widoczne cały czas
        cout << "=================================================\n";
        cout << " BOHATER: " << gracz.imie 
             << " | ZLOTO: " << gracz.gold 
             << " | HP: " << gracz.hp << "/" << gracz.maxHp << "\n";
        cout << " LOKACJA: "<<nazwyLokacji[gracz.aktualnaLokacja]<<"\n";
        cout << "=================================================\n";
        
        cout << "Co robisz dalej?\n";
        cout << "1. Sprawdz swoj ekwipunek\n";
        cout << "2. Rozejrzyj sie za kupcem\n";
        cout << "3. Spojrz na mape\n";
        cout << "4. Wyjdz z karczmy na szlak (Jeszcze niedostepne)\n"; 
        cout << "5. Zakoncz gre\n";
        cout << "> ";
        cin >> wyborGlowny;

        switch(wyborGlowny) {
            
            case 1:
                pokazEkwipunek(gracz);
                czekajNaEnter();
                break;
            
            case 2:
                if(gracz.aktualnaLokacja == 0){
                    menuHandlu(gracz, kupiec_karczma);
                } else if (gracz.aktualnaLokacja == 2){
                    menuHandlu(gracz, kupiec_wioska);
                } else {
                    cout<<"Rozgladasz sie, ale nie ma tu z kim handlowac.\n";
                    czekajNaEnter();
                }
                break;
            
            case 3:
                pokazMape(gracz.aktualnaLokacja);
                czekajNaEnter();
                break;
            
            case 4:{
                int kierunek;
                cout << "\nDokad chcesz wyruszyc?\n";
                cout << "1. Na wschod (W glab Kniei)\n";
                cout << "2. Na zachod (Powrot)\n";
                cout << "3. Zostan tutaj\n> ";
                cin >> kierunek;
                if(kierunek==1){
                    if(gracz.aktualnaLokacja<4){
                        gracz.aktualnaLokacja++;
                        cout<<"Wyruszasz w drogę do " << nazwyLokacji[gracz.aktualnaLokacja]<<endl;
                    } else {
                        cout<<"Nie możesz wyruszyc dalej, dalej jest tylko przepaść\n";
                    }
                }
                else if(kierunek==2){
                    if(gracz.aktualnaLokacja==0){
                        cout<<"Nie masz gdzie wracać, tam jest tylko przepaść!\n";
                    } else {
                        gracz.aktualnaLokacja--;
                        cout<<"Wyruszasz w drogę do " << nazwyLokacji[gracz.aktualnaLokacja]<<endl;
                    }
                }
                else if(kierunek==3){
                }
                else{
                    cout<<"Nieznana opcja.\n";
                }
                czekajNaEnter();
                break;
            }
            case 5:
                cout << "\nOpuszczasz Zelazna Knieje. Do zobaczenia!\n";
                break;
            
            default:
                cout << "\nNieznana opcja.\n";
                czekajNaEnter();
        }
    }

    return 0;
}
