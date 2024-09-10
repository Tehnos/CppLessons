#include <iostream>
#include <vector>
#include <string>
void Homework1()
{
	float health;
	std::cout << "Enter your champion health:\n";
	std::cin >> health;
	while (health > 0)
	{
		float item_distance=0;
		float item_impact=0;
		std::cout << "Enter distance to item:\n";
		std::cin >> item_distance;
		if (item_distance < 0)
		{
			std::cout << "Distance cant be less zero, enter correct distance\n";
			std::cin >> item_distance;
		}
		std::cout << "Enter a number(If the number is greater than zero, it is a cure; if less, it is a harm):\n";
		std::cin >> item_impact;
		float result_impact = item_impact * (1 - item_distance / 100);
		float damage;
		if (item_distance <100 && item_impact>0)
			damage = result_impact;
		else
			damage = item_impact;
		health += damage;
		if (health > 0 && health < 1)
			health = 1;
		if(item_impact > 0)
			std::cout << "You taken heal " << damage << std::endl;
		else
			std::cout << "You taken damage " << damage << std::endl;

		std::cout<<"Your health: " << health <<std::endl << std::endl;

	}
	std::cout << "You are died\n";
}

struct Player {
    std::string name;
    int clan;
    float health;
    float damage;

    Player(std::string name, int clan, float health, float damage)
        : name(name), clan(clan), health(health), damage(damage) {}
};

std::vector<Player> clan0;
std::vector<Player> clan1;

void addPlayer() {
    std::string name;
    int clan;
    float health, damage;
    std::cout << "Enter player name: ";
    std::cin >> name;
    std::cout << "Enter clan number (0 or 1): ";
    std::cin >> clan;
    std::cout << "Enter player health: ";
    std::cin >> health;
    std::cout << "Enter player damage: ";
    std::cin >> damage;

    if (clan == 0) {
        clan0.push_back(Player(name, clan, health, damage));
    }
    else if (clan == 1) {
        clan1.push_back(Player(name, clan, health, damage));
    }
    else {
        std::cout << "Invalid clan number!\n";
    }
}

void removePlayer() {
    std::string name;
    int clan;
    std::cout << "Enter player name: ";
    std::cin >> name;
    std::cout << "Enter clan number (0 or 1): ";
    std::cin >> clan;

    std::vector<Player>* targetClan = (clan == 0) ? &clan0 : &clan1;
    for (auto it = targetClan->begin(); it != targetClan->end(); ++it) {
        if (it->name == name) {
            targetClan->erase(it);
            std::cout << "Player removed.\n";
            return;
        }
    }
    std::cout << "Player not found.\n";
}

void conductFight() {
    float totalHealth0 = 0, totalDamage0 = 0;
    float totalHealth1 = 0, totalDamage1 = 0;

    for (const auto& player : clan0) {
        totalHealth0 += player.health;
        totalDamage0 += player.damage;
    }

    for (const auto& player : clan1) {
        totalHealth1 += player.health;
        totalDamage1 += player.damage;
    }

    std::cout << "Total health of clan 0: " << totalHealth0 << "\n";
    std::cout << "Total damage of clan 0: " << totalDamage0 << "\n";
    std::cout << "Total health of clan 1: " << totalHealth1 << "\n";
    std::cout << "Total damage of clan 1: " << totalDamage1 << "\n";

    if (totalDamage0 >= totalHealth1 && totalDamage1 >= totalHealth0) {
        std::cout << "Draw. Both clans perished.\n";
    }
    else if (totalDamage0 >= totalHealth1) {
        std::cout << "Clan 0 wins!\n";
    }
    else if (totalDamage1 >= totalHealth0) {
        std::cout << "Clan 1 wins!\n";
    }
    else {
        std::cout << "No one wins. The fight continues.\n";
    }
}

void simulateFight() {
    std::cout << "Fight begins!\n";

    while (!clan0.empty() && !clan1.empty()) {
        Player& attacker0 = clan0.front();
        Player& defender1 = clan1.front();

        std::cout << attacker0.name << " from clan 0 attacks " << defender1.name << " from clan 1\n";
        defender1.health -= attacker0.damage;
        std::cout << defender1.name << " now has " << defender1.health << " health\n";

        if (defender1.health <= 0) {
            std::cout << defender1.name << " has died!\n";
            clan1.erase(clan1.begin());
        }

        if (clan1.empty()) break;

        Player& attacker1 = clan1.front();
        Player& defender0 = clan0.front();

        std::cout << attacker1.name << " from clan 1 attacks " << defender0.name << " from clan 0\n";
        defender0.health -= attacker1.damage;
        std::cout << defender0.name << " now has " << defender0.health << " health\n";

        if (defender0.health <= 0) {
            std::cout << defender0.name << " has died!\n";
            clan0.erase(clan0.begin());
        }
    }

    if (clan0.empty() && clan1.empty()) {
        std::cout << "Draw! Both clans perished.\n";
    }
    else if (clan0.empty()) {
        std::cout << "Clan 1 wins!\n";
    }
    else if (clan1.empty()) {
        std::cout << "Clan 0 wins!\n";
    }
}

int main() {
    int command;

    while (true) {
        std::cout << "Enter command (0 - add player, 1 - remove player, 2 - conduct fight, 3 - simulate fight, 4 - exit): ";
        std::cin >> command;

        if (command == 0) {
            addPlayer();
        }
        else if (command == 1) {
            removePlayer();
        }
        else if (command == 2) {
            conductFight();
            break;
        }
        else if (command == 3) {
            simulateFight();
            break;
        }
        else if (command == 4) {
            std::cout << "Program terminated.\n";
            break;
        }
        else {
            std::cout << "Invalid command, please try again.\n";
        }
    }

    return 0;
}
