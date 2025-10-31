// COMSC210 | Lab 28 | Tanmayee Chalamalasetti
// IDE Used: VS Code

#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>

#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat>& trip);
void add_goat(list<Goat>& trip, string[], string[]);
void display_trip(list<Goat> trip);
void sort_goats_age(list<Goat>& trip);
void remove_under_seven(list<Goat>& trip);
int main_menu();

int main() {
  srand(time(0));
  bool again;

  // read & populate arrays for names and colors
  ifstream fin("names.txt");
  string names[SZ_NAMES];
  int i = 0;
  while (fin >> names[i++]);
  fin.close();
  ifstream fin1("colors.txt");
  string colors[SZ_COLORS];
  i = 0;
  while (fin1 >> colors[i++]);
  fin1.close();

  // create & populate a trip of Goats using std::list of random size 8-15
  int tripSize = rand() % 8 + 8;
  list<Goat> trip;
  int age;
  string name, color;
  for (int i = 0; i < tripSize; i++) {
    age = rand() % MAX_AGE;  // defined in Goat.h
    name = names[rand() % SZ_NAMES];
    color = colors[rand() % SZ_COLORS];
    Goat tmp(name, age, color);
    trip.push_back(tmp);
  }

  // Goat Manager 3001 Engine
  int sel = main_menu();
  while (sel != 11) {
    switch (sel) {
      case 1:
        cout << "Adding a goat.\n";
        add_goat(trip, names, colors);
        break;
      case 2:
        cout << "Removing a goat.\n";
        delete_goat(trip);
        break;
      case 3:
        cout << "Displaying goat data.\n";
        display_trip(trip);
        break;
      case 4:
        cout << "Sorting goat data by age in ascending order.\n";
        sort_goats_age(trip);
        break;
      case 5:
        cout << "Removing goats under 7\n";
        remove_under_seven(trip);
        break;
      default:
        cout << "Invalid selection.\n";
        break;
    }
    sel = main_menu();
  }

  return 0;
}

int main_menu() {
  cout << "*** GOAT MANAGER 3001 ***\n";
  cout << "[1] Add a goat\n";
  cout << "[2] Delete a goat\n";
  cout << "[3] List goats\n";
  cout << "[4] Sort goats\n";
  cout << "[5] Remove goats under 7\n";
  cout << "[5] Find a goat\n";
  cout << "[6] \n";
  cout << "[11] Quit\n";
  cout << "Choice --> ";
  int choice;
  cin >> choice;
  while (choice < 1 || choice > 11) {
    cout << "Invalid, again --> ";
    cin >> choice;
  }
  return choice;
}

void delete_goat(list<Goat>& trip) {
  cout << "DELETE A GOAT\n";
  int index = select_goat(trip);
  auto it = trip.begin();
  advance(it, index - 1);
  trip.erase(it);
  cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat>& trip, string nms[], string cls[]) {
  cout << "ADD A GOAT\n";
  int age = rand() % MAX_AGE;
  string nm = nms[rand() % SZ_NAMES];
  string cl = cls[rand() % SZ_COLORS];
  Goat tmp(nm, age, cl);
  trip.push_back(tmp);
  cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
  int i = 1;
  for (auto gt : trp)
    cout << "\t"
         << "[" << i++ << "] " << gt.get_name() << " (" << gt.get_age() << ", "
         << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
  int input;
  cout << "Make a selection:\n";
  display_trip(trp);
  cout << "Choice --> ";
  cin >> input;
  while (input < 1 or input > trp.size()) {
    cout << "Invalid choice, again --> ";
    cin >> input;
  }
  return input;
}

void sort_goats_age(list<Goat>& trip) {
  cout << "Sort the goats by age:\n";
  trip.sort(
      [](const Goat& a, const Goat& b) { return a.get_age() < b.get_age(); });
  cout << "Sorted by age";
}

void remove_under_seven(list<Goat>& trip) {
  trip.erase(remove_if(trip.begin(), trip.end(),
                       [](const Goat& g) { return g.get_age() < 7; }),
             trip.end());
  cout << "After removing goats under 7:\n";
}
