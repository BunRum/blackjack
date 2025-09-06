#include <any>
#include <array>
#include <iostream>
#include <print>
#include <string>
#include <vector>
using namespace std;

template <typename T>
T prompt(string message) {
	print("{}", message);
	T value{};
	cin >> value;
	return value;
}

class Deck {
public:
	vector<int> cards = {};
	Deck() {
		for (int i = 0; i < 2; i++) {
			Hit();
		}
	}
	int drawCard() {
		int cardDrawn = 1 + (rand() % 10);
		return cardDrawn;
	}

	int sumCards() {
		int Sum = 0;
		for (int i = 0; i < cards.size(); i++) {
			Sum += cards[i];
		}
		return Sum;
	}

	void Hit() { cards.push_back(drawCard()); }
};

int main() {
	string help = "[1] - Hit [2] - Stand [3] - Restart\nInput: ";

	srand(time(nullptr));  // Seed RNG with current time

	Deck playerDeck;
	Deck dealerDeck;

    while (true) {
        println("Dealers Deck: {} ({})", dealerDeck.cards, dealerDeck.sumCards());
        println("Your Deck: {} ({})", playerDeck.cards, playerDeck.sumCards());
        auto decision = prompt<int>(help);

        if (decision == 1) {
            playerDeck.Hit();
            if (playerDeck.sumCards() > 21) {
                println("You Bust! Dealer Wins!");
                break;
            }
        } else if (decision == 2) {
            while (dealerDeck.sumCards() < 20) {
                dealerDeck.Hit();
                println("Dealers Deck: {} ({})", dealerDeck.cards, dealerDeck.sumCards());
            }
            if (dealerDeck.sumCards() > 21) {
                println("Dealer Busts, You win!");
            } else if (playerDeck.sumCards() > dealerDeck.sumCards()) {
                println("You Win!");
            } else if (playerDeck.sumCards() < dealerDeck.sumCards()) {
                println("Dealer Wins!");
                if (dealerDeck.sumCards() == 21) {
                    println("Dealer got Blackjack!");
                }
            } else {
                println("It's a Tie!");
            }
            break;
        } else if (decision == 3) {
            playerDeck = Deck();
            dealerDeck = Deck();
        }
    }

	return 0;
}