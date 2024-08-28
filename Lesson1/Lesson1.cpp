#include <iostream>


int main()
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
