#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <windows.h>
#include <conio.h>

#define BACKCOLOR 7
#define FRONTCOLOR 0
#define SELECTCOLOR 4
#define TOPMENU 5
#define LEFTMENU 20
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

void Homework1()
{
	float health;
	std::cout << "Enter your champion health:\n";
	std::cin >> health;
	while (health > 0)
	{
		float item_distance = 0;
		float item_impact = 0;
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
		if (item_distance < 100 && item_impact>0)
			damage = result_impact;
		else
			damage = item_impact;
		health += damage;
		if (health > 0 && health < 1)
			health = 1;
		if (item_impact > 0)
			std::cout << "You taken heal " << damage << std::endl;
		else
			std::cout << "You taken damage " << damage << std::endl;

		std::cout << "Your health: " << health << std::endl << std::endl;

	}
	std::cout << "You are died\n";
}

void Homework2() {
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
}

class Building
{
private:
	static int nextId;
	int id;
	int maxAge;
	int initialCost;
	int currentAge;

	void Destroy() {
		std::cout << "Building with ID " << id << " has been destroyed.\n";
	}
public:
	Building(int maxAge, int initialCost)
		: maxAge(maxAge), initialCost(initialCost), currentAge(0)
	{
		id = nextId++;
	}
	int GetCost() const
	{
		if (currentAge >= maxAge)
			return 0;
		return initialCost * (maxAge - currentAge) / maxAge;
	}
	void ToAge(int years)
	{
		currentAge += years;
		if (currentAge >= maxAge) {
			Destroy();
		}
	}
	int GetId() const
	{
		return id;
	}

};
int Building::nextId = 1;
void Homework3()
{
	Building buildingOne(50, 10000);
	std::cout << "Initial cost: " << buildingOne.GetCost() << std::endl;

	buildingOne.ToAge(10);
	std::cout << "Cost after 10 years: " << buildingOne.GetCost() << std::endl;

	buildingOne.ToAge(25);
	std::cout << "Cost after 35 years: " << buildingOne.GetCost() << std::endl;
	buildingOne.ToAge(20);
	std::cout << "Cost after 55 years: " << buildingOne.GetCost() << std::endl;

}


// homework4
class Weapon
{
public:
	virtual ~Weapon() = default;

	virtual float GetDamage() const = 0;
	virtual std::string GetName() const = 0;
};

class Sword : public Weapon
{
public:
	float GetDamage() const override
	{
		return 60.0f;
	}

	std::string GetName() const override
	{
		return "Sword";
	}
};

class Bow : public Weapon
{
public:
	float GetDamage() const override
	{
		return 35.0f;
	}

	std::string GetName() const override
	{
		return "Bow";
	}
};

class MagicWand : public Weapon
{
public:
	float GetDamage() const override
	{
		return 78.0f;
	}

	std::string GetName() const override
	{
		return "Magic Wand";
	}
};

void SetColor(unsigned short backColor, unsigned short frontColor)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD color = ((backColor & 0x0f) << 4) + (frontColor & 0x0f);
	SetConsoleTextAttribute(h, color);
}
void SetCursor(unsigned short row, unsigned short column)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c{ column,row };
	SetConsoleCursorPosition(h, c);
}
void PaintMenu(const char** textMenu, size_t sizeMenu, size_t select)
{
	SetColor(BACKCOLOR, FRONTCOLOR);
	SetCursor(TOPMENU, LEFTMENU);
	std::cout << "__________________________________________________________________________________";
	for (size_t i = 0; i < sizeMenu; i++)
	{
		SetCursor(TOPMENU + i + 1, LEFTMENU + 25);
		if (i == select)
			SetColor(BACKCOLOR, SELECTCOLOR);
		else
			SetColor(BACKCOLOR, FRONTCOLOR);
		std::cout << (i == select ? "=>" : " ") << textMenu[i];
		std::cout << "           ";
	}
	std::cout << "\n                    __________________________________________________________________________________";

	SetCursor(20, 0);
}
size_t Menu(const char** textMenu, size_t sizeMenu, size_t select)
{
	unsigned char c = 72;
	while (true)
	{
		if (c == 72 || c == 80)PaintMenu(textMenu, sizeMenu, select);
		c = _getch();
		switch (c)
		{
		case 13: return select;
		case 72:
			if (select == 0) select = sizeMenu;
			select--;
			break;//up
		case 80:
			select++;
			if (select == sizeMenu)
				select = 0;
			break;//down

		default:
			break;
		}
	}

	return select;
}
//void homework4() {
//	Character hero;
//
//	hero.AddWeapon(std::make_unique<Sword>());
//	hero.AddWeapon(std::make_unique<Bow>());
//	hero.AddWeapon(std::make_unique<MagicWand>());
//
//	SetColor(BACKCOLOR, FRONTCOLOR);
//	system("cls");
//	size_t select = 0;
//	const char* textMenu[] = { "Show all weapon",
//							   "Select sword",
//							   "Select bow",
//							   "Select MagicWand",
//							   "Exit" };
//	size_t sizeMenu = sizeof(textMenu) / sizeof(*textMenu);
//
//	while (1)
//	{
//		select = Menu(textMenu, sizeMenu, select);
//		system("cls");
//		switch (select)
//		{
//		case 0:
//			hero.ShowWeapons();
//			break;
//		case 1:
//			hero.SetActiveWeapon(0);
//			std::cout << "Changed active weapon to: " << hero.GetActiveWeapon()->GetName() << "\n";
//			break;
//		case 2:
//			hero.SetActiveWeapon(1);
//			std::cout << "Changed active weapon to: " << hero.GetActiveWeapon()->GetName() << "\n";
//			break;
//		case 3:
//			hero.SetActiveWeapon(2);
//			std::cout << "Changed active weapon to: " << hero.GetActiveWeapon()->GetName() << "\n";
//			break;
//		case 4:
//		break;
//		default:
//			break;
//		}
//
//	}
//}

//homework5
class IDamage
{
public:
	virtual void ApplyDamage(float Damage) = 0;
};
class IHealthReceiver
{
public:
	virtual void ReceiveNewHealth(float NewHealth) = 0;
};

class IHealthNotify
{
public:
	virtual void Attach(IHealthReceiver* receiver) = 0;
	virtual void Detach(IHealthReceiver* receiver) = 0;
};
class Character :public IDamage, public IHealthNotify
{
private:
	std::vector<std::unique_ptr<Weapon>> weapons;
	std::vector< IHealthReceiver*> subscribers;
	Weapon* activeWeapon = nullptr;
	float health = 100.0f;

public:
	void AddWeapon(std::unique_ptr<Weapon> weapon)
	{
		if (weapons.empty())
		{
			activeWeapon = weapon.get();
		}
		weapons.push_back(std::move(weapon));
	}

	void SetActiveWeapon(int index)
	{
		if (index >= 0 && index < weapons.size())
		{
			activeWeapon = weapons[index].get();
		}
		else
		{
			std::cout << "Invalid weapon index!" << std::endl;
		}
	}

	Weapon* GetActiveWeapon() const
	{
		return activeWeapon;
	}

	void ShowWeapons() const
	{
		for (size_t i = 0; i < weapons.size(); ++i)
		{
			std::cout << i << ": " << weapons[i]->GetName() << " (Damage: " << weapons[i]->GetDamage() << ")\n";
		}
	}

	virtual void ApplyDamage(float Damage)
	{
		health -= Damage;
		for (IHealthReceiver* receiver : subscribers)
		{
			receiver->ReceiveNewHealth(health);
		}
	}
	virtual void Attach(IHealthReceiver* receiver)
	{
		subscribers.push_back(receiver);
	}
	virtual void Detach(IHealthReceiver* receiver)
	{
		subscribers.erase(std::find(subscribers.begin(), subscribers.end(), receiver));
	}
	
};
class HealthObserver : public IHealthReceiver
{
public:
	void ReceiveNewHealth(float NewHealth) override
	{
		std::cout << "New health received: " << NewHealth << std::endl;
	}
};

class Enemy: public IHealthReceiver
{
	virtual void ReceiveNewHealth(float NewHealth)
	{
		std::cout << "Enemy got info: " << NewHealth << std::endl;
	}
};

void DamageActor(IDamage* damagableActor)
{
	damagableActor->ApplyDamage(10.f);
}
int main()
{
	Character hero;
	Enemy enemy;
	HealthObserver observer;

	hero.Attach(&observer);
	hero.Attach(&enemy);

	DamageActor(&hero);
	DamageActor(&hero);



	return 0;
}