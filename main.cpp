#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <windows.h>
#include <sstream>

using namespace std;

struct Pamietnik {
    int index;
    string data;
    string imie;
    string nazwisko;
    string tytul;
    string opis;
};

void dodajWpis(vector<Pamietnik> &wpisy) {
    Pamietnik nowyWpis;
    nowyWpis.index = wpisy.size() + 1;

    cout << "Podaj date wpisu (dd.mm.rrrr - gg:mm): ";
    cin.ignore();
    getline(cin, nowyWpis.data);
    cout << "Podaj imie: ";
    getline(cin, nowyWpis.imie);
    cout << "Podaj nazwisko: ";
    getline(cin, nowyWpis.nazwisko);
    cout << "Podaj tytul wpisu: ";
    getline(cin, nowyWpis.tytul);
    cout << "Podaj tresc wpisu: ";
    getline(cin, nowyWpis.opis);

    wpisy.push_back(nowyWpis);

    system("CLS");

    cout << "Wpis dodany pomyslnie.\n";
    Sleep(1500);

    system("CLS");
}

void wyswietlanie(vector<Pamietnik> &wpisy) {
    system("CLS");
    if (wpisy.empty()) {
        cout << "Brak wpisow do wyswietlenia." << endl;
    } else {
            cout << "+-------------- WYSWIETLANIE WPISOW --------------+" << endl;
        for (const Pamietnik &wpis : wpisy) {
            cout << "Index: " << wpis.index << endl;
            cout << "Data: " << wpis.data << endl;
            cout << "Imie: " << wpis.imie << endl;
            cout << "Nazwisko: " << wpis.nazwisko << endl;
            cout << "Tytul: " << wpis.tytul << endl;
            cout << "Opis: ";

            const int max_chars_per_line = 60;
            for (size_t i = 0; i < wpis.opis.length(); ++i) {
                cout << wpis.opis[i];
                if ((i + 1) % max_chars_per_line == 0) {
                    cout << endl;
                    cout << "     ";
                }
            }

            cout << endl;
            cout << "----------------------------------------------" << endl;
        }
    }
    cout << endl;
    cout << "Nacisnij Enter, aby wrocic do menu...";
    cin.ignore();
    cin.get();
    system("CLS");
}

void usunPoIndeksie(vector<Pamietnik> &wpisy) {
    int index;
    cout << "Podaj index wpisu do usuniecia: ";
    cin >> index;

    auto it = find_if(wpisy.begin(), wpisy.end(), [index](const Pamietnik &wpis) {
        return wpis.index == index;
    });

    if (it != wpisy.end()) {
        wpisy.erase(it);

        for (auto &wpis : wpisy) {
            if (wpis.index > index) {
                wpis.index--;
            }
        }

        cout << "Wpis o indeksie " << index << " zostal usuniety." << endl;
    } else {
        cout << "Nie znaleziono wpisu o podanym indeksie." << endl;
    }
}

void usunPoDacie(vector<Pamietnik> &wpisy) {
    string data;
    cout << "Podaj date wpisu do usuniecia (dd.mm.rrrr - gg:mm): ";
    cin.ignore();
    getline(cin, data);

    auto it = find_if(wpisy.begin(), wpisy.end(), [data](const Pamietnik &wpis) {
        return wpis.data == data;
    });

    if (it != wpisy.end()) {
        int indexToDelete = it->index;
        wpisy.erase(it);

        for (auto &wpis : wpisy) {
            if (wpis.index > indexToDelete) {
                wpis.index--;
            }
        }

        cout << "Wpis z data " << data << " zostal usuniety." << endl;
    } else {
        cout << "Nie znaleziono wpisu o podanej dacie." << endl;
    }
}

void usunPoTytule(vector<Pamietnik> &wpisy) {
    string tytul;
    cout << "Podaj tytul wpisu do usuniecia: ";
    cin.ignore();
    getline(cin, tytul);

    auto it = find_if(wpisy.begin(), wpisy.end(), [tytul](const Pamietnik &wpis) {
        return wpis.tytul == tytul;
    });

    if (it != wpisy.end()) {
        int indexToDelete = it->index;
        wpisy.erase(it);

        for (auto &wpis : wpisy) {
            if (wpis.index > indexToDelete) {
                wpis.index--;
            }
        }

        cout << "Wpis o tytule " << tytul << " zostal usuniety." << endl;
    } else {
        cout << "Nie znaleziono wpisu o podanym tytule." << endl;
    }
}

void edytowanie(vector<Pamietnik> &wpisy) {
    int index;
    cout << "Podaj index wpisu do edycji: ";
    cin >> index;

    auto it = find_if(wpisy.begin(), wpisy.end(), [index](const Pamietnik &wpis) {
        return wpis.index == index;
    });

    if (it != wpisy.end()) {
        cout << "Co chcesz edytowac w wpisie o indeksie " << index << "?" << endl;
        cout << "1. Data" << endl;
        cout << "2. Imie" << endl;
        cout << "3. Nazwisko" << endl;
        cout << "4. Tytul" << endl;
        cout << "5. Opis" << endl;
        cout << "Wybierz opcje: ";

        int wybor;
        cin >> wybor;

        switch (wybor) {
            case 1:
                cout << "Nowa data (dd.mm.rrrr - gg:mm): ";
                cin.ignore();
                getline(cin, it->data);
                break;
            case 2:
                cout << "Nowe imie: ";
                cin.ignore();
                getline(cin, it->imie);
                break;
            case 3:
                cout << "Nowe nazwisko: ";
                cin.ignore();
                getline(cin, it->nazwisko);
                break;
            case 4:
                cout << "Nowy tytul: ";
                cin.ignore();
                getline(cin, it->tytul);
                break;
            case 5:
                cout << "Nowy opis: ";
                cin.ignore();
                getline(cin, it->opis);
                break;
            default:
                cout << "Nieprawidlowy wybor." << endl;
                return;
        }
        system("CLS");
        cout << "Wpis o indeksie " << index << " zostal zaktualizowany." << endl;
        system("PAUSE");
        system("CLS");
    } else {
        system("CLS");
        cout << "Nie znaleziono wpisu o podanym indeksie." << endl;
        system("PAUSE");
        system("CLS");
    }
}

void szukanie(vector<Pamietnik> &wpisy) {
    int wybor;
    cout << "Wybierz opcje szukania:" << endl;
    cout << "1. Szukaj po indeksie" << endl;
    cout << "2. Szukaj po tytule" << endl;
    cout << "Wybierz opcje: ";
    cin >> wybor;

    switch (wybor) {
        case 1: {
            int index;
            system("CLS");
            cout << "Podaj index wpisu do wyszukania: ";
            cin >> index;

            for (const auto &wpis : wpisy) {
                if (wpis.index == index) {
                    system("CLS");
                    cout << "+-------------- WYSWIETLANIE WPISU --------------+" << endl;
                    cout << "Index: " << wpis.index << endl;
                    cout << "Data: " << wpis.data << endl;
                    cout << "Imie: " << wpis.imie << endl;
                    cout << "Nazwisko: " << wpis.nazwisko << endl;
                    cout << "Tytul: " << wpis.tytul << endl;
                    cout << "Opis: " << wpis.opis << endl;
                    cout << "----------------------------------------------" << endl;
                    return;
                }
            }
            system("CLS");
            cout << "Nie znaleziono wpisu o podanym indeksie." << endl;
            break;
        }
        case 2: {
            string tytul;
            system("CLS");
            cout << "Podaj tytul wpisu do wyszukania: ";
            cin.ignore();
            getline(cin, tytul);

            for (const auto &wpis : wpisy) {
                if (wpis.tytul == tytul) {
                    system("CLS");
                    cout << "+-------------- WYSWIETLANIE WPISU --------------+" << endl;
                    cout << "Index: " << wpis.index << endl;
                    cout << "Data: " << wpis.data << endl;
                    cout << "Imie: " << wpis.imie << endl;
                    cout << "Nazwisko: " << wpis.nazwisko << endl;
                    cout << "Tytul: " << wpis.tytul << endl;
                    cout << "Opis: " << wpis.opis << endl;
                    cout << "----------------------------------------------" << endl;
                    return;
                }
            }
            system("CLS");
            cout << "Nie znaleziono wpisu o podanym tytule." << endl;
            break;
        }
        default:
            system("CLS");
            cout << "Nieprawidlowy wybor." << endl;
            break;
    }
}

bool porownajDaty(const Pamietnik &wpis1, const Pamietnik &wpis2) {
    return wpis1.data < wpis2.data;
}

void sortowanieIWyswietlanie(vector<Pamietnik> &wpisy) {
    bool zamiana = true;
    int rozmiar = wpisy.size();

    while (zamiana) {
        zamiana = false;
        for (int i = 0; i < rozmiar - 1; ++i) {
            if (porownajDaty(wpisy[i + 1], wpisy[i])) {
                swap(wpisy[i], wpisy[i + 1]);
                zamiana = true;
            }
        }
        --rozmiar;
    }

    system("CLS");
    cout << "+-------------- WYSWIETLANIE POSORTOWANYCH WPISOW --------------+" << endl;
    for (const Pamietnik &wpis : wpisy) {
        cout << "Index: " << wpis.index << endl;
        cout << "Data: " << wpis.data << endl;
        cout << "Imie: " << wpis.imie << endl;
        cout << "Nazwisko: " << wpis.nazwisko << endl;
        cout << "Tytul: " << wpis.tytul << endl;
        cout << "Opis: " << wpis.opis << endl;
        cout << "----------------------------------------------" << endl;
    }
    cout << endl;
    cout << "Nacisnij Enter, aby wrocic do menu...";
    cin.ignore();
    cin.get();
    system("CLS");
}

void zapisywanie(vector<Pamietnik> &wpisy) {

    ofstream plik;
    string nazwaPliku;
    char wybor;

    system("CLS");
    cout << "Czy chcesz uzyc istniejacego pliku czy utworzyc nowy? (i-istniejacy/n-nowy): ";
    cin >> wybor;

    if (wybor == 'i' || wybor == 'I') {
        cout << "Podaj nazwe istniejacego pliku: ";
        cin >> nazwaPliku;

        ifstream existingFile(nazwaPliku);
        if (existingFile.good()) {
            existingFile.close();
            cout << "Czy chcesz nadpisac istniejacy plik? (t/n): ";
            cin >> wybor;
            if (wybor == 't' || wybor == 'T') {
                plik.open(nazwaPliku, ios::out | ios::trunc);
            } else {
                plik.open(nazwaPliku, ios::out | ios::app);
            }
        } else {
            plik.open(nazwaPliku, ios::out | ios::trunc);
        }
    } else if (wybor == 'n' || wybor == 'N') {
        cout << "Podaj nazwe nowego pliku: ";
        cin >> nazwaPliku;
        plik.open(nazwaPliku, ios::out | ios::trunc);
    } else {
        system("CLS");
        cout << "Nieprawidlowy wybor." << endl;
        system("PAUSE");
        system("CLS");
        return;
    }

    if (!plik.is_open()) {
        system("CLS");
        cout << "Blad podczas otwierania pliku." << endl;
        system("PAUSE");
        system("CLS");
        return;
    }

    for (const Pamietnik &wpis : wpisy) {
        plik << "Index: " << wpis.index << endl;
        plik << "Data: " << wpis.data << endl;
        plik << "Imie: " << wpis.imie << endl;
        plik << "Nazwisko: " << wpis.nazwisko << endl;
        plik << "Tytul: " << wpis.tytul << endl;
        plik << "Opis: " << wpis.opis << endl;
        plik << "----------------------------------------------" << endl;
    }

    plik.close();
    system("CLS");
    cout << "Wpisy zostaly zapisane do pliku: " << nazwaPliku << endl;
    system("PAUSE");
    system("CLS");
}

void wczytajWpisy(vector<Pamietnik> &wpisy) {
    ifstream plik;
    string nazwaPliku;
    char wybor;

    cout << "Podaj nazwe pliku do wczytania: ";
    cin >> nazwaPliku;
    system("CLS");

    plik.open(nazwaPliku);

    if (!plik.is_open()) {
        system("CLS");
        cout << "Blad podczas otwierania pliku." << endl;
        system("PAUSE");
        system("CLS");
        return;
    }

    if (!wpisy.empty()) {
        system("CLS");
        cout << "Uwaga: Istnieja juz dane w strukturze. Czy chcesz je usunac przed wczytaniem danych z pliku? (t/n): ";
        cin >> wybor;

        if (wybor == 't' || wybor == 'T') {
            wpisy.clear();
            system("CLS");
            cout << "Dane w strukturze zostaly usuniete." << endl;
            system("PAUSE");
            system("CLS");
        } else if (wybor == 'n' || wybor == 'N') {
            system("CLS");
            cout << "Dane w strukturze nie zostaly usuniete." << endl;
            system("PAUSE");
            system("CLS");
        }
    }

    Pamietnik wpis;
    string linia;
    int index = 1;
    while (getline(plik, linia)) {
        if (linia.find("Index:") != string::npos) {
            wpis.index = index++; // Inkrementacja indeksu
            getline(plik, linia); // Data
            wpis.data = linia.substr(6);
            getline(plik, linia); // Imie
            wpis.imie = linia.substr(6);
            getline(plik, linia); // Nazwisko
            wpis.nazwisko = linia.substr(10);
            getline(plik, linia); // Tytul
            wpis.tytul = linia.substr(7);
            getline(plik, linia); // Opis
            wpis.opis = linia.substr(6);
            wpisy.push_back(wpis);
        }
    }

    system("CLS");
    cout << "Wczytano dane z pliku: " << nazwaPliku << endl;
    system("PAUSE");
    system("CLS");
    plik.close();
}



int main() {

    vector<Pamietnik> wpisy;

    int wybor;

    do {

        cout << "+------- MENU GLOWNE -------+" << endl;
        cout << "|1) Dodaj wpis              |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|2) Usun wpis               |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|3) Wyswietl wpisy          |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|4) Edytuj wpis             |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|5) Szukaj wpisu            |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|6) Sortuj wpisy wg. daty   |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|7) Zapisz wpisy do pliku   |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|8) Wczytaj wpisy           |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "|9) Wyjscie                 |" << endl;
        cout << "+---------------------------+" << endl;
        cout << "Wybierz opcje: ";
        cin >> wybor;
        cout << "\n";

        switch (wybor) {
            case 1:
                system("CLS");
                dodajWpis(wpisy);
                break;
            case 2: {
                system("CLS");
                int wyborUsun;
                cout << "+------- MENU USUWANIA WPISU -------+" << endl;
                cout << "|1) Usun wpis po indeksie           |" << endl;
                cout << "|2) Usun wpis po dacie              |" << endl;
                cout << "|3) Usun wpis po tytule             |" << endl;
                cout << "+-----------------------------------+" << endl;
                cout << "Wybierz opcje: ";
                cin >> wyborUsun;
                switch (wyborUsun) {
                    case 1:
                        usunPoIndeksie(wpisy);
                        break;
                    case 2:
                        usunPoDacie(wpisy);
                        break;
                    case 3:
                        usunPoTytule(wpisy);
                        break;
                    default:
                        cout << "Nie ma takiej opcji w menu usuwania!" << endl;
                        break;
                }
                cout << "\n";
                system("PAUSE");
                system("CLS");
                break;
            }
            case 3:
                system("CLS");
                wyswietlanie(wpisy);
                break;
            case 4:
                system("CLS");
                edytowanie(wpisy);
                break;
            case 5: {
                system("CLS");
                szukanie(wpisy);
                system("PAUSE");
                system("CLS");
                break;
            }
            case 6:
                system("CLS");
                sortowanieIWyswietlanie(wpisy);
                break;
                break;
            case 7:
                zapisywanie(wpisy);
                break;
            case 8:
                system("CLS");
                wczytajWpisy(wpisy);
                break;
            case 9:
                system("CLS");
                cout << "Do widzenia!" << endl;
                wpisy.clear();
                break;
            default:
                cout << "Nie ma takiej opcji w menu!" << endl;
                cout << "\n";
                Sleep(1500);
                system("CLS");
                break;
        }

    } while (wybor != 9);

    return 0;
}
