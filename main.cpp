#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// --- Version 1 : avec find() ---
bool contientFind(const string& mot1, const string& mot2) {
    size_t pos = 0;
    for (char c : mot2) {
        size_t trouve = mot1.find(c, pos);      // recherche à partir de pos
        if (trouve == string::npos) return false;
        pos = trouve + 1;                        // on continue après
    }
    return true;
}

// --- Version 2 : from scratch (sous-séquence) ---
bool contientScratch(const string& mot1, const string& mot2) {
    size_t j = 0;
    for (size_t i = 0; i < mot1.size() && j < mot2.size(); ++i) {
        if (mot1[i] == mot2[j]) ++j;
    }
    return j == mot2.size();                     // tous les caractères trouvés
}

int main() {
    string mot2;
    cout << "Entrez le mot 2 : ";
    cin >> mot2;

    // Chargement du fichier en mémoire une seule fois
    ifstream f("mots.txt");
    if (!f) { cerr << "Impossible d'ouvrir mots.txt\n"; return 1; }

    vector<string> mots;
    mots.reserve(10000000);
    string m;
    while (f >> m) mots.push_back(m);
    cout << "Fichier chargé : " << mots.size() << " mots\n\n";

    vector<size_t> tailles = {10, 100, 1000, 10000, 100000, 1000000, 10000000};

    cout << "N\t\tOccurrences\tfind() (s)\tscratch (s)\n";
    cout << "---------------------------------------------------------\n";

    for (size_t n : tailles) {
        if (n > mots.size()) break;

        // --- Test avec find() ---
        long long occFind = 0;
        auto t0 = high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i)
            if (contientFind(mots[i], mot2)) ++occFind;
        auto t1 = high_resolution_clock::now();

        // --- Test from scratch ---
        long long occScratch = 0;
        auto t2 = high_resolution_clock::now();
        for (size_t i = 0; i < n; ++i)
            if (contientScratch(mots[i], mot2)) ++occScratch;
        auto t3 = high_resolution_clock::now();

        double dtFind    = duration<double>(t1 - t0).count();
        double dtScratch = duration<double>(t3 - t2).count();

        cout << n << "\t\t" << occFind << "\t\t"
             << dtFind << "\t\t" << dtScratch << "\n";
    }
    return 0;
}
