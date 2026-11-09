#pragma once
#include <string>
#include <vector>

extern const size_t MAX_INVENTORY_SIZE;

enum class ItemRarity{
    BASIC = 1,
    RARE = 2,
    EPIC = 3,
    LEGENDARY = 4,
};

enum class ItemCategory{
    WEAPON = 1,
    ARMOR = 2,
    ELIXIR = 3,
    OTHER = 4,
};

struct Item{
    int ID;
    std::string nazwa;
    int basicPrice;
    ItemRarity rarity;
    ItemCategory category;
};

struct Player{
    int hp;
    int maxHp;
    int gold;
    int aktualnaLokacja;
    std::string imie;
    std::vector<Item> ekwipunek; //wektor w ktorym kazdy element jest pojedyncza struktura Item
};

struct Merchant{
    int gold;
    std::string imie;
    std::vector<Item> asortyment;
};

struct Enemy {
    std::string nazwa;
    int hp;
    int maxHp;
    int minDamage;
    int maxDamage;
    int goldDrop; 
};

inline bool czyPelnyEkwipunek(const Player& gracz){
    return gracz.ekwipunek.size() >= MAX_INVENTORY_SIZE;
}

void pokazSklep(const Merchant& kupiec);
void pokazEkwipunek(const Player& gracz);

bool kupPrzedmiot(Player& gracz, Merchant& kupiec, int idPrzedmiotu);
bool sprzedajPrzedmiot(Player& gracz, Merchant& kupiec, int idPrzedmiotu);

void czyscEkran();
void czekajNaEnter();

void pokazMape(int aktualnaLokalizacja);
