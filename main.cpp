#include <iostream>
#include <cstdlib> // Do rand() i srand()
#include <ctime>   // Do time()
#include "rpg_system.h"
#include "rpg_system.h"

using namespace std;
string nazwyLokacji[5] = {"Karczma", "Las", "Wioska", "Bagna", "Jaskinia"};

void menuEkwipunku(Player& gracz) {
    int wybor = 0;
    while(wybor != 2) {
        czyscEkran();
        cout << "\n======================================" << endl;
        cout << "       ZARZADZANIE EKWIPUNKIEM        " << endl;
        cout << "======================================" << endl;
        cout << " BRON: " << gracz.zalozonaBron.nazwa << " (+" << gracz.zalozonaBron.wartoscEfektu << " DMG)\n";
        cout << " PANCERZ: " << gracz.zalozonyPancerz.nazwa << " (-" << gracz.zalozonyPancerz.wartoscEfektu << "% DMG)\n";
        cout << "--------------------------------------" << endl;
        pokazEkwipunek(gracz);
        cout << "--------------------------------------" << endl;
        cout << "1. Zaloz przedmiot z plecaka" << endl;
        cout << "2. Wroc do menu glownego" << endl;
        cout << "> ";
        cin >> wybor;
        czyscBufor();

        if (wybor == 1) {
            int id;
            cout << "Podaj ID przedmiotu do zalozenia: ";
            cin >> id;
            czyscBufor();

            bool znaleziono = false;
            for (size_t i = 0; i < gracz.ekwipunek.size(); i++) {
                if (gracz.ekwipunek[i].ID == id) {
                    znaleziono = true;
                    Item wybranyItem = gracz.ekwipunek[i]; // Kopiujemy wybrany przedmiot

                    if (wybranyItem.category == ItemCategory::WEAPON) {
                        gracz.ekwipunek[i] = gracz.zalozonaBron; // Stara bron wraca do plecaka
                        gracz.zalozonaBron = wybranyItem;        // Nowa wedruje do rak
                        cout << "Zalozyles: " << wybranyItem.nazwa << "!\n";
                    } 
                    else if (wybranyItem.category == ItemCategory::ARMOR) {
                        gracz.ekwipunek[i] = gracz.zalozonyPancerz; // Stary pancerz wraca do plecaka
                        gracz.zalozonyPancerz = wybranyItem;        // Nowy wedruje na cialo
                        cout << "Zalozyles: " << wybranyItem.nazwa << "!\n";
                    }
                    else {
                        cout << "Nie mozesz tego zalozyc! (To prawdopodobnie mikstura).\n";
                    }
                    break; // Konczymy szukanie
                }
            }
            if (!znaleziono) {
                cout << "Nie masz w plecaku przedmiotu o takim ID.\n";
            }
            czekajNaEnter();
        }
    }
}

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
        czyscBufor();

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
                czyscBufor();
                kupPrzedmiot(gracz, kupiec, id);
                czekajNaEnter();
                break;
            }
            case 3: {
                int id;
                cout << "Podaj ID przedmiotu do sprzedania: ";
                cin >> id;
                czyscBufor();
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
    srand(time(NULL));
    // 1. Inicjalizacja kupcow
    Merchant kupiec_karczma = {500, "Odo", {
        {1, "Zardzewialy Miecz", 20, ItemRarity::BASIC, ItemCategory::WEAPON, 10},
        {2, "Skorzana Zbroja", 50, ItemRarity::BASIC, ItemCategory::ARMOR, 15},
        {3, "Mikstura Zdrowia", 15, ItemRarity::RARE, ItemCategory::ELIXIR, 30}
    }};

    Merchant kupiec_wioska = {1000, "Kaelen", {
        {1, "Stalowy Miecz", 120, ItemRarity::RARE, ItemCategory::WEAPON, 35},
        {2, "Ciezka Zbroja", 200, ItemRarity::EPIC, ItemCategory::ARMOR, 40}
    }};

    // 2. PROLOG I TWORZENIE POSTACI
    czyscEkran();
   
    string podaneImie;
    int wyborKlasy;

    cout << "Deszcz z loskotem uderzal o zgnile deski Karczmy 'Pod Wisielcem'...\n";
    cout << "Karczmarz przeciera kufel i patrzy na Ciebie spode lba.\n";
    cout << "- Jak cie zwa, wedrowcze?\n> ";
    cin >> podaneImie;
    czyscBufor();

    cout << "\n- A, slyszalem to imie. Podobno jestes...\n";
    cout << "1. Zbieglym dezerterem (150 HP, 20 zlota)\n";
    cout << "2. Zrujnowanym szlachcicem (80 HP, 200 zlota)\n";
    cout << "3. Wedrownym alchemikiem (110 HP, 100 zlota)\n> ";
    cin >> wyborKlasy;
    czyscBufor();

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
    gracz.zalozonaBron = {0, "Gole Piesci", 0, ItemRarity::BASIC, ItemCategory::WEAPON, 5}; 
    gracz.zalozonyPancerz = {0, "Podstawowy stroj", 0, ItemRarity::BASIC, ItemCategory::ARMOR, 0};

    int wyborGlowny = 0;
    while(wyborGlowny != 5) {
        czyscEkran();
        
        // HUD - Statystyki widoczne cały czas
        cout << "=================================================\n";
        cout << " BOHATER: " << gracz.imie 
             << " | ZLOTO: " << gracz.gold 
             << " | HP: " << gracz.hp << "/" << gracz.maxHp << "\n";
        cout << " BRON: " << gracz.zalozonaBron.nazwa << " (+" << gracz.zalozonaBron.wartoscEfektu << " DMG)\n";
        cout << " PANCERZ: " << gracz.zalozonyPancerz.nazwa << " (-" << gracz.zalozonyPancerz.wartoscEfektu << "% DMG)\n";
        cout << " LOKACJA: "<<nazwyLokacji[gracz.aktualnaLokacja]<<"\n";
        cout << "=================================================\n";
        
        cout << "Co robisz dalej?\n";
        cout << "1. Sprawdz swoj ekwipunek\n";
        cout << "2. Rozejrzyj sie za kupcem\n";
        cout << "3. Spojrz na mape\n";
        cout << "4. Wyjdz z karczmy na szlak\n"; 
        cout << "5. Zakoncz gre\n";
        cout << "> ";
        cin >> wyborGlowny;
        czyscBufor();

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
                czyscBufor();
                bool ruszylSie = false;
                if(kierunek==1){
                    if(gracz.aktualnaLokacja<4){
                        gracz.aktualnaLokacja++;
                        cout<<"Wyruszasz w drogę do " << nazwyLokacji[gracz.aktualnaLokacja]<<endl;
                        ruszylSie = true;
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
                        ruszylSie = true;
                    }
                }
                else if(kierunek==3){
                }
                else{
                    cout<<"Nieznana opcja.\n";
                }
                czekajNaEnter();
                if(ruszylSie){
                    if(gracz.aktualnaLokacja == 1 || gracz.aktualnaLokacja == 3 || gracz.aktualnaLokacja == 4 ){
                        if(rand()%100<50){
                            Enemy potwor;
                            if (gracz.aktualnaLokacja == 1) {
                                potwor = {"Wsciekly Wilk", 40, 40, 5, 12, 15}; // Las
                            } else if (gracz.aktualnaLokacja == 3) {
                                potwor = {"Topielec", 60, 60, 10, 18, 30}; // Bagna
                            } else if (gracz.aktualnaLokacja == 4) {
                                potwor = {"Troll Jaskiniowy", 120, 120, 15, 25, 100}; // Jaskinia
                            }
                            bool przezyl = battle(gracz, potwor);
                            if(!przezyl){
                                wyborGlowny = 5;
                            }
                        }
                    }
                }
                break;
            }
            case 5:
                break;
            
            default:
                cout << "\nNieznana opcja.\n";
                czekajNaEnter();
        }
    }
    
    czyscEkran();
    cout << "\n=================================================\n";
    
    if (gracz.hp <= 0) {
        cout << "                   KONIEC GRY\n";
        cout << " Twoje cialo uzyzni mroczna ziemie...\n";
    } else {
        cout << " Opuszczasz Zelazna Knieje caly i zdrow. Do zobaczenia!\n";
    }
    
    cout << "=================================================\n";
    cout << " PODSUMOWANIE TWOJEJ PRZYGODY:\n";
    cout << " - Bohater: " << gracz.imie << "\n";
    cout << " - Zgromadzone zloto: " << gracz.gold << " monet\n";
    cout << " - Ostatnia lokacja: " << nazwyLokacji[gracz.aktualnaLokacja] << "\n";
    cout << "=================================================\n";
    
    czekajNaEnter();
    return 0;
}
