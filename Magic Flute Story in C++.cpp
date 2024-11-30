#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

// Function to play the flute
void playFlute(const string& melody) {
    cout << "\n🎵 Playing the magical flute melody: " << melody << " 🎵" << endl;
    for (char note : melody) {
        cout << "Playing note: " << note << "..." << endl;
        this_thread::sleep_for(chrono::milliseconds(500)); // Simulates playing time
    }
    cout << "✨ The melody resonates through the village... ✨" << endl;
}

// Magical effects function
void magicEffect(const string& effect) {
    cout << "\n🌟 Magic Effect Activated: " << effect << " 🌟" << endl;
}

// Main story logic
int main() {
    cout << "Welcome to the Magical Flute Story Program!" << endl;

    // Define a list of villagers and their problems
    vector<pair<string, string>> villagers = {
        {"Marie", "sick and bedridden"},
        {"Paul", "stuck with broken tools"},
        {"Jean", "hungry due to no crops"}
    };

    // Introduce the hero
    cout << "\nYou are Jak, the magical flutist of the village." << endl;

    // Iterate through villagers and help them
    for (const auto& villager : villagers) {
        cout << "\nVillager " << villager.first << " needs help! They are " << villager.second << "." << endl;

        // Play a melody to solve the problem
        string melody = "CDEFG";
        playFlute(melody);

        // Display the magical effect
        if (villager.second == "sick and bedridden") {
            magicEffect("Healing energy restores " + villager.first + " to health!");
        } else if (villager.second == "stuck with broken tools") {
            magicEffect(villager.first + "'s tools are magically repaired!");
        } else if (villager.second == "hungry due to no crops") {
            magicEffect("Fields are suddenly filled with crops for " + villager.first + "!");
        }
    }

    // End of story
    cout << "\nThe village is now happy and peaceful, thanks to your magical flute. 🎶" << endl;
    cout << "Thank you for playing the story!" << endl;

    return 0;
}
