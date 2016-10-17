#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>
#include <queue>
#include <unordered_map>
#include <sstream>

using namespace std;

// Source: Yodle careers

/**
 * Description can be found in the problem page. I fumbled
 * with this one quite a bit for a little while. I kept going
 * back and forth from "Ok for each circuit I need to ..." and
 * "Ok for each juggler I need to ..." because in my mind for each
 * circuit I needed to do something for each juggler. Trying to model
 * the problem was tough. I first thought I'd need some array for each
 * circuit. I figured this array or structure would contain juggler/dot
 * product pairs of all the jugglers that have listed this circuit as a
 * preference. We would then figure out given all of the jugglers who listed
 * this circuit as a preference which top (j/c) jugglers would make it. I then
 * realized it is possible for a juggler to be assigned to a circuit not on his
 * preference list. In this case my instant reaction was that I'd need to expand
 * the circuit array to not only include jugglers that prefer this circuit, but instead
 * include ALL jugglers. Then when I assigned one juggler, I'd have to go through all the
 * other circuit arrays and remove the juggler since he is no longer a free agent. Of course
 * this is terribly space inefficient because we need j*c space since we're storing each juggler
 * (c) times. Later it is obvious we do not need this. For some reason when thinking of assigning
 * a juggler to a circuit, I had it in my mind that the assignment must be permanent. The permanent
 * assigning of a juggler turns out to be very inefficient.
 *
 * How I thought of permanently assigning a juggler
 * At first I thought I'd start with a circuit and start with the top performing juggler in that circuit array.
 * I'd then wanted to see if I could assign that juggler to this circuit. To do that I had to see if it first could
 * be assigned to a circuit it prefers more. This meant looking at its most preferred circuit and seeing if it can be
 * permanently assigned to it instead. To see if it could be permanently assigned to a preferred circuit I'd have to check
 * this juggler's [dot product w/ circuit] against all other unassigned jugglers in that circuit's array. If the juggler in
 * question's dot product with the circuit was in the top (j/c) for that circuit we could assign. If not, we do the same thing
 * for each other circuit lower on the preference list.
 *
 * ---- Some optimizations to make ----
 * Notice that whenever we start with a circuit and find a good juggler, we inevitably go through the juggler's preferred circuits to see if
 * it can be permanently assigned to one of them. If it cannot then we need to assign it to any circuit in which it is a top performer. It would
 * make sense to just start with some random juggler, and go through its list of preferred circuits and see if it can be permanently assigned to one.
 * We would do this until we have assigned all jugglers.
 *
 * We should realize that all of the jugglers in some circuit's array are just unassigned jugglers in the universe, or jugglers assigned to that specific circuit.
 * If ever a juggler gets assigned permanently, we remove it from all other circuit arrays. It would make much more sense to keep a single set of all unassigned
 * jugglers and then when trying to assign a juggler to its most preferred circuit just check its dot product against all other jugglers in the universe to see if
 * it can be a top performer. If it can be, assign it, if not move to its next most preferred circuit.
 * ---------------------------------
 *
 * ---- Gale Shapely stable matching optimization ----
 * We can still see it is a little roundabout in that say we have a juggler we are trying to assign to a preferred circuit. We have to check the juggler against
 * all other jugglers to see if it can be a top performer in that circuit. If the juggler cannot be assigned that means we have found at least (j/c) jugglers whose
 * dot product values are better suited for that circuit however we don't even bother assigning those other jugglers. Since this problem is a slight modification of
 * the Gale Shapely stable marriage problem what we instead need to do is consider temporary assignments. Instead we take a juggler and automatically assign it to its
 * most preferred circuit that doesn't already have (j/c) jugglers in it. If we come across a full circuit that our juggler wants to be in we have to realize we can only
 * let him in if he out-performs some other juggler already in that circuit. If he out-performs one of them, we take the weakest juggler and add him to the set of unassigned
 * jugglers and assign our previously unassigned juggler to the circuit. We keep doing this for all of the unassigned jugglers first trying to fit them into circuits that actually
 * prefer, however if it is clear they cannot make it into a circuit they prefer, we must throw them in some other one.
 */

/**
 * Circuits and Jugglers have these things in common
 */
class HEPItem {
private:
  int H, E, P;
  string name;

public:
  HEPItem(string name, int H, int E, int P): name(name), H(H), E(E), P(P) {}

  int dotProduct(HEPItem* hepItem) {
    return ((this->H * hepItem->H) + (this->E * hepItem->E) + (this->P * hepItem->P));
  }

  string getName() {
    return this->name;
  }
};

class Juggler: public HEPItem {
private:
  vector<string> circuitPreferences;

public:
  Juggler(string name, int H, int E, int P, const vector<string>& preferenceVector): HEPItem(name, H, E, P), circuitPreferences(preferenceVector) {}

  vector<string> getCircuitPreferences() {
    return circuitPreferences;
  }
};

class Circuit: public HEPItem {
private:
  vector<Juggler*> assignedJugglers; // vector of jugglers assigned to this circuit

public:
  Circuit(string name, int H, int E, int P): HEPItem(name, H, E, P) {}

  static int maxJugglers; // shared ceiling value for number of jugglers/circuit

  /**
   * Used to tell us whether or not the circuit is full.
   * If it is not, we auto-accept anyone.
   */
  bool canBlindlyAssignJuggler() {
    if (assignedJugglers.size() < maxJugglers) return true;
    return false;
  }

  /**
   * Used to tell us whether or not some juggler can
   * out-perform one of the already assigned jugglers
   * in this circuit. Throws exception if we can blindly
   * assign a juggler instead.
   */
  bool canReplaceWeakJuggler(Juggler* juggler) {
    if (assignedJugglers.size() < maxJugglers) throw logic_error("Why replace a weak juggler if we're not filled yet? Try canBlindlyAssignJuggler()");

    // See if weaker juggler exists
    for (int i = 0; i < assignedJugglers.size(); ++i) {
      if (assignedJugglers[i]->dotProduct(this) < juggler->dotProduct(this)) return true;
    }

    return false;
  }

  /**
   * Removes weakest assigned juggler and replaces with stronger
   * input juggler. Assumes given juggler is stronger than at least
   * one other already assigned juggler. (canAssignJuggler must be called first).
   * Throws exception if we can blindly assign a juggler instead.
   */
  Juggler* replaceWeakestJuggler(Juggler* strongerJuggler) {
    if (assignedJugglers.size() < maxJugglers) throw logic_error("Tried to replace weakest juggler in non-full circuit of size: " + assignedJugglers.size());
    int weakestJugglerIndex = 0, weakestDotProduct = INT_MAX;

    // Find index of weaker juggler
    for (int i = 0; i < assignedJugglers.size(); ++i) {
      if (assignedJugglers[i]->dotProduct(this) < weakestDotProduct) {
        weakestDotProduct = assignedJugglers[i]->dotProduct(this);
        weakestJugglerIndex = i;
      }
    }

    // Save ptr to weaker juggler and overwrite with stronger input juggler
    Juggler* weakestAssignedJuggler = assignedJugglers[weakestJugglerIndex];
    assignedJugglers[weakestJugglerIndex] = strongerJuggler;

    // Return weaker juggler (will go back to unassigned juggler queue)
    return weakestAssignedJuggler;
  }

  /**
   * Used to commit a juggler to a non-full circuit. Throws
   * exception if circuit is full
   */
  void blindlyAssignJuggler(Juggler* inputJuggler) {
    if (assignedJugglers.size() == maxJugglers) throw logic_error("Tried to blindly assign juggler to full already full circuit, try replaceWeakestJuggler()");
    assignedJugglers.push_back(inputJuggler);
  }

  // Utility to print all juggler names and their circuit preference/dot product values
  void printOutputLine(const unordered_map<string, Circuit*>& circuitMap) {
    vector<string> jugglerCircuitPreferences;
    Circuit* preferredCircuit;
    cout << this->getName() << " ";
    for (int i = 0; i < assignedJugglers.size(); ++i) {
      cout << assignedJugglers[i]->getName() << " ";
      jugglerCircuitPreferences = assignedJugglers[i]->getCircuitPreferences();

      // For each preferred circuit, print the circuit name and corresponding dot product
      for (string pref : jugglerCircuitPreferences) {
        preferredCircuit = circuitMap.find(pref)->second;
        cout << preferredCircuit->getName() << ": " << assignedJugglers[i]->dotProduct(preferredCircuit) << " ";
      }
    }
    cout << endl;
  }

};

int Circuit::maxJugglers = 0; // define static variable so we can set later

vector<string> parsePreferencesToVector(string preferenceLine) {
  stringstream ss(preferenceLine);
  vector<string> returnPreferenceVector;

  while (ss.good()) {
    string substr;
    getline(ss, substr, ',');
    returnPreferenceVector.push_back(substr);
  }

  return returnPreferenceVector;
}

int main() {
  unsigned int numCircuits = 0, numJugglers = 0;
  string inputString;
  unordered_map<string, Circuit*> circuitMap;
  queue<Juggler*> unassignedJugglers;

  // stdin parsing
  // Temp data for each HEPItem
  string name, H, E, P;
  string preferenceLine;
  vector<string> preferenceVector; // Juggler specific data
  while (cin >> inputString) {
    cin >> name >> H >> E >> P;
    if (inputString == "C") {
      pair<string, Circuit*> insertPair = make_pair(name, new Circuit(name, stoi(H.substr(2)), stoi(E.substr(2)), stoi(P.substr(2))));
      circuitMap.insert(insertPair);
    } else if (inputString == "J") {
      // Parse preferences
      cin >> preferenceLine;
      preferenceVector = parsePreferencesToVector(preferenceLine);
      unassignedJugglers.push(new Juggler(name, stoi(H.substr(2)), stoi(E.substr(2)), stoi(P.substr(2)), preferenceVector));
    }
  }

  // cout << "We made it here...all of the parsing is done!" << endl;
  // cout << "There are " << unassignedJugglers.size() << " unassignedJugglers" << endl;
  // cout << "There are " << circuitMap.size() << " circuits" << endl;
  // cout << "This means there will be " << unassignedJugglers.size()/circuitMap.size() << " jugglers assigned to a circuit" << endl;

  // Set Circuit static variable
  Circuit::maxJugglers = unassignedJugglers.size()/circuitMap.size();

  Juggler* jugglerToAssign, *weakerJuggler;
  bool assigned;
  while (unassignedJugglers.size()) {
    assigned = false;
    jugglerToAssign = unassignedJugglers.front();
    vector<string> jugglerCircuitPreferences = jugglerToAssign->getCircuitPreferences();

    // Try to assign a juggler to a circuit of their preference
    for (string pref : jugglerCircuitPreferences) {
      if (circuitMap[pref]->canBlindlyAssignJuggler()) {
        circuitMap[pref]->blindlyAssignJuggler(jugglerToAssign);
        unassignedJugglers.pop();
        assigned = true;
        break;
      } else if (circuitMap[pref]->canReplaceWeakJuggler(jugglerToAssign)) {
        weakerJuggler = circuitMap[pref]->replaceWeakestJuggler(jugglerToAssign);
        unassignedJugglers.push(weakerJuggler);
        unassignedJugglers.pop();
        assigned = true;
        break;
      }
    }

    // If we were able to assign juggler to preference, don't keep trying to assign...just continue
    if (assigned) continue;

    // They can't be a top performer in any of their preferred circuits, so find another one for them for now
    for (unordered_map<string, Circuit*>::iterator i = circuitMap.begin(); i != circuitMap.end(); ++i) {
      if (i->second->canBlindlyAssignJuggler()) {
        i->second->blindlyAssignJuggler(jugglerToAssign);
        unassignedJugglers.pop();
        break;
      } else if (i->second->canReplaceWeakJuggler(jugglerToAssign)) {
        weakerJuggler = i->second->replaceWeakestJuggler(jugglerToAssign);
        unassignedJugglers.push(weakerJuggler);
        unassignedJugglers.pop();
        break;
      }
    }
  }

  // Only print C1970 jugglers if it exists (we could be working with another test file)
  for (unordered_map<string, Circuit*>::iterator i = circuitMap.begin(); i != circuitMap.end(); ++i) {
    i->second->printOutputLine(circuitMap);
  }

  // if (circuitMap.find("C1970") != circuitMap.end()) circuitMap["C1970"]->printOutputLine(circuitMap);

  // Gotta be memory safe
  for (unordered_map<string, Circuit*>::iterator i = circuitMap.begin(); i != circuitMap.end(); ++i) {
    delete i->second;
  }

  return 0;
}
