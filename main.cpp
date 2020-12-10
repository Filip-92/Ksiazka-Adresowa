#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <conio.h>
#include <algorithm>
#include <sstream>

using namespace std;

struct Znajomy
{
    int id = 0, idUzytkownika = 0;
    string imie, nazwisko, nr_tel, adresEmail, adresZamieszkania;
};

struct Uzytkownik
{
    int idUzytkownika = 0;
    string nazwa, haslo;
};

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

vector <Uzytkownik> rejestracja ( vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow )
{
    string nazwa, haslo;
    int idUzytkownika;
    iloscUzytkownikow = uzytkownicy.size();
    cout << iloscUzytkownikow << endl;
    system("pause");

    Uzytkownik pojedynczyUzytkownik;

    fstream plik;
    plik.open("Uzytkownicy.txt");
    if (plik.good())
    {
        plik.close();
    }
    else
    {
        plik.open("Uzytkownicy.txt", ios::out);
        plik.close();
    }

    system("cls");
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while (i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            cout << "Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin >> nazwa;
            i = 0;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj haslo: ";
    cin >> haslo;

    idUzytkownika = iloscUzytkownikow + 1;

    pojedynczyUzytkownik = { idUzytkownika, nazwa, haslo };
    uzytkownicy.push_back ( pojedynczyUzytkownik );

    plik.open ( "Uzytkownicy.txt", ios::out | ios::app );

    if ( plik.good() == true )
    {
        plik << uzytkownicy[iloscUzytkownikow].idUzytkownika << "|";
        plik << uzytkownicy[iloscUzytkownikow].nazwa << "|";
        plik << uzytkownicy[iloscUzytkownikow].haslo << "|";
        plik << endl;

        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych" << endl;
        Sleep(1000);
    }

    cout << "Konto zostalo zalozone" << endl;
    Sleep(1000);

    return uzytkownicy;
}

int logowanie ( vector <Uzytkownik> uzytkownicy, int iloscUzytkownikow )
{
    string nazwa, haslo;
    iloscUzytkownikow = uzytkownicy.size();

    fstream plik;
    plik.open("Uzytkownicy.txt");
    if (plik.good())
    {
        plik.close();
    }
    else
    {
        plik.open("Uzytkownicy.txt", ios::out);
        plik.close();
    }

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwa;
    int i = 0;
    while (i < iloscUzytkownikow)
    {
        if (uzytkownicy[i].nazwa == nazwa)
        {
            for(int proby = 0; proby < 3; proby++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-proby << ": ";
                cin >> haslo;
                if(uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie." << endl;
                    Sleep(1000);
                    return uzytkownicy[i].idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne gaslo. Poczekaj 3 sekundy przed kolejna proba" << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout << "Nie ma uzytkownika z takim loginem" << endl;
    Sleep(1500);
    return 0;
}

vector <Uzytkownik> wczytywanieUzytkownikowDoStruktury (vector <Uzytkownik>& uzytkownicy)
{
    string linia;
    int nr_linii = 1;
    fstream plik;

    Uzytkownik pojedynczyUzytkownik;

    plik.open ( "Uzytkownicy.txt", ios::in );

    if (plik.is_open())
    {
        while(getline(plik,linia))
        {
            string uzytkownik[3];
            int koniecStringa = linia.length();
            int index = 0;
            int poczatekSlowa = 0;
            int dlugoscSlowa = 0;
            int indexUzytkownika = 0;

            for ( index = 0; index < koniecStringa; index++ )
            {
                if((int) linia[index] == 124)
                {
                    dlugoscSlowa = index - poczatekSlowa;
                    uzytkownik [ indexUzytkownika ] = linia.substr( poczatekSlowa, dlugoscSlowa );
                    poczatekSlowa = index + 1;
                    indexUzytkownika++;
                }
            }
            pojedynczyUzytkownik.idUzytkownika = atoi(uzytkownik[0].c_str());
            pojedynczyUzytkownik.nazwa = uzytkownik[1];
            pojedynczyUzytkownik.haslo = uzytkownik[2];

            uzytkownicy.push_back ( pojedynczyUzytkownik );
        }
        plik.close();

        return uzytkownicy;
    }
    else
    {
        plik.close();
        return uzytkownicy;
    }
}

vector <Uzytkownik> zmianaHaslaUzytkownika ( vector <Uzytkownik> uzytkownicy, int idZalogowanegoUzytkownika )
{
    fstream plik;
    int indexDoEdycji;
    string haslo;
    cout << "Podaj nowe haslo: ";
    cin >> haslo;

    for ( int i = 0; i < uzytkownicy.size(); i++ )
    {
        if ( uzytkownicy[i].idUzytkownika == idZalogowanegoUzytkownika )
        {
            indexDoEdycji = i;
            uzytkownicy[i].haslo = haslo;
        }

    plik.open("Uzytkownicy.txt", ios::out);
    if ( plik.good() )
    {
        if ( idZalogowanegoUzytkownika > 1 )
        {
            for ( int i = 0; i < indexDoEdycji; i++ )
            {
                plik << uzytkownicy[i].idUzytkownika << "|";
                plik << uzytkownicy[i].nazwa << "|";
                plik << uzytkownicy[i].haslo << "|" << endl;
            }
        }
        plik << uzytkownicy[indexDoEdycji].idUzytkownika << "|";
        plik << uzytkownicy[indexDoEdycji].nazwa << "|";
        plik << uzytkownicy[indexDoEdycji].haslo << "|" << endl;

        if (  indexDoEdycji + 1 < uzytkownicy.size() )
        {
            for ( int i = idZalogowanegoUzytkownika; i < uzytkownicy.size(); i++ )
            {
                plik << uzytkownicy[i].idUzytkownika << "|";
                plik << uzytkownicy[i].nazwa << "|";
                plik << uzytkownicy[i].haslo << "|" << endl;
            }
        }
        plik.close();
        cout << "Haslo zostalo zmienione" << endl;
        Sleep(1500);
        return uzytkownicy;
    }
    else
    {
        plik.close();
        cout << "Blad odczytu pliku!" << endl;
        Sleep(1000);
        return uzytkownicy;
    }
}
}

bool szukajZnaku ( string tekst, char szukanyZnak )
{
    size_t znalezionaPozycja = tekst.find ( szukanyZnak );
    if( znalezionaPozycja == string::npos )
    {
        return false;
    }
    else
        return true;
}

string konwersjaIntNaString ( int liczba )
{
    ostringstream ss;
    ss << liczba;
    string str = ss.str();
    return str;
}

Znajomy pobierzDaneZnajomego ( string daneZnajomegoOddzielonePionowymiKreskami )
{
    Znajomy znajomy;
    string pojedynczaDanaZnajomego = "";
    int numerPojedynczejDanejZnajomego = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneZnajomegoOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneZnajomegoOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaZnajomego += daneZnajomegoOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejZnajomego)
            {
            case 1:
                znajomy.id = atoi(pojedynczaDanaZnajomego.c_str());
                break;
            case 2:
                znajomy.idUzytkownika = atoi(pojedynczaDanaZnajomego.c_str());
                break;
            case 3:
                znajomy.imie = pojedynczaDanaZnajomego;
                break;
            case 4:
                znajomy.nazwisko = pojedynczaDanaZnajomego;
                break;
            case 5:
                znajomy.nr_tel = pojedynczaDanaZnajomego;
                break;
            case 6:
                znajomy.adresEmail = pojedynczaDanaZnajomego;
                break;
            case 7:
                znajomy.adresZamieszkania = pojedynczaDanaZnajomego;
                break;
            }
            pojedynczaDanaZnajomego = "";
            numerPojedynczejDanejZnajomego++;
        }
    }
    return znajomy;
}

string pobierzLiczbe(string tekst, int pozycjaZnaku)
{
    string liczba = "";
    while(isdigit(tekst[pozycjaZnaku]) == true)
    {
        liczba += tekst[pozycjaZnaku];
        pozycjaZnaku ++;
    }
    return liczba;
}

int konwersjaStringNaInt(string liczba)
{
    int liczbaInt;
    istringstream iss(liczba);
    iss >> liczbaInt;

    return liczbaInt;
}

int pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami ( string daneJednegoZnajomegoOddzielonePionowymiKreskami )
{
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoZnajomegoOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = konwersjaStringNaInt ( pobierzLiczbe ( daneJednegoZnajomegoOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika ) );

    return idUzytkownika;
}

int pobierzIdZnajomegoZDanychOddzielonychPionowymiKreskami ( string daneJednegoZnajomegoOddzielonePionowymiKreskami )
{
    int pozycjaRozpoczeciaIdZnajomego = 0;
    int idZnajomego = konwersjaStringNaInt ( pobierzLiczbe ( daneJednegoZnajomegoOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdZnajomego ) );
    return idZnajomego;
}

int wczytajZnajomychZalogowanegoUzytkownikaZPliku ( vector <Znajomy> &znajomi, int idZalogowanegoUzytkownika )
{
    Znajomy znajomy;
    int idOstatniegoZnajomego = 0;
    string daneJednegoZnajomegoOddzielonePionowymiKreskami = "";
    string daneOstaniegoZnajomegoWPliku = "";
    fstream plik;
    plik.open ( "ksiazkaAdresowa.txt", ios::in );

    if ( plik.good() == true )
    {
        while ( getline ( plik, daneJednegoZnajomegoOddzielonePionowymiKreskami ) )
        {
            if ( idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami ( daneJednegoZnajomegoOddzielonePionowymiKreskami ) )
            {
                znajomy = pobierzDaneZnajomego ( daneJednegoZnajomegoOddzielonePionowymiKreskami );
                znajomi.push_back(znajomy);
            }
        }
        daneOstaniegoZnajomegoWPliku = daneJednegoZnajomegoOddzielonePionowymiKreskami;
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    plik.close();

    if ( daneOstaniegoZnajomegoWPliku != "" )
    {
        idOstatniegoZnajomego = pobierzIdZnajomegoZDanychOddzielonychPionowymiKreskami ( daneOstaniegoZnajomegoWPliku );
        return idOstatniegoZnajomego;
    }
    else
        return 0;
}

int pobierzZPlikuIdOstatniegoZnajomego()
{
    int idOstatniegoZnajomego = 0;
    string daneJednegoZnajomegoOddzielonePionowymiKreskami = "";
    string daneOstaniegoZnajomegoWPliku = "";
    fstream plik;
    plik.open ( "ksiazkaAdresowa.txt", ios::in );

    if (plik.good() == true)
    {
        while ( getline ( plik, daneJednegoZnajomegoOddzielonePionowymiKreskami ) ) {}
            daneOstaniegoZnajomegoWPliku = daneJednegoZnajomegoOddzielonePionowymiKreskami;
            plik.close();
    }
    else
        cout << "Nie udalo sie otworzyc pliku i wczytac danych." << endl;

    if (daneOstaniegoZnajomegoWPliku != "")
    {
        idOstatniegoZnajomego = pobierzIdZnajomegoZDanychOddzielonychPionowymiKreskami ( daneOstaniegoZnajomegoWPliku );
    }
    return idOstatniegoZnajomego;
}

int podajIdOstatniegoZnajomegoPoUsunieciuWybranegoZnajomego ( int idUsuwanegoZnajomego, int idOstatniegoZnajomego )
{
    if ( idUsuwanegoZnajomego == idOstatniegoZnajomego )
        return pobierzZPlikuIdOstatniegoZnajomego();
    else
        return idOstatniegoZnajomego;
}

bool czyPlikJestPusty(fstream &plik)
{
    plik.seekg(0, ios::end);
    if (plik.tellg() == 0)
        return true;
    else
        return false;
}

string zamienDaneZnajomegoNaLinieZDanymiOddzielonymiPionowymiKreskami( Znajomy znajomy )
{
    string liniaZDanymiZnajomego = "";

    liniaZDanymiZnajomego += konwersjaIntNaString(znajomy.id) + '|';
    liniaZDanymiZnajomego += konwersjaIntNaString(znajomy.idUzytkownika) + '|';
    liniaZDanymiZnajomego += znajomy.imie + '|';
    liniaZDanymiZnajomego += znajomy.nazwisko + '|';
    liniaZDanymiZnajomego += znajomy.nr_tel + '|';
    liniaZDanymiZnajomego += znajomy.adresEmail + '|';
    liniaZDanymiZnajomego += znajomy.adresZamieszkania + '|';

    return liniaZDanymiZnajomego;
}

void dopiszZnajomegoDoPliku (Znajomy znajomy)
{
    string liniaZDanymiZnajomego = "";
    fstream plik;
    plik.open ( "ksiazkaAdresowa.txt", ios::out | ios::app );

    if (plik.good() == true)
    {
        liniaZDanymiZnajomego = zamienDaneZnajomegoNaLinieZDanymiOddzielonymiPionowymiKreskami ( znajomy );

        if (czyPlikJestPusty(plik) == true)
        {
            plik << liniaZDanymiZnajomego;
        }
        else
        {
            plik << endl << liniaZDanymiZnajomego ;
        }
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
    }
    plik.close();
}

Znajomy podajDaneNowegoZnajomego ( vector <Znajomy>& znajomi, int idZalogowanegoUzytkownika, int idOstatniegoZnajomego )
{
    Znajomy osoba;
    string imie, nazwisko, nr_tel, adresEmail, adresZamieszkania;
    int id;
    int idUzytkownika;
    int iloscZnajomych = znajomi.size();

    osoba.id = ++idOstatniegoZnajomego;
    osoba.idUzytkownika = idZalogowanegoUzytkownika;

    cout << iloscZnajomych << endl;
    system ("pause");

    system("cls");
    string daneAdresata;
    cout << "Podaj imie znajomego: ";
    cin >> osoba.imie;
    cout << "Podaj nazwisko znajomego: ";
    cin >> osoba.nazwisko;

    int i = 0;
    while ( i < iloscZnajomych )
    {
        if (( znajomi[i].imie == osoba.imie ) && ( znajomi[i].nazwisko == nazwisko ))
        {
            cout << "Znajomy o takich danych juz istnieje. Wpisz inne dane: " << endl;
            cout << "Podaj imie znajomego: ";
            cin >> osoba.imie;
            cout << "Podaj nazwisko znajomego: ";
            cin >> osoba.nazwisko;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj numer telefonu znajomego: ";
    cin.sync();
    getline ( cin, osoba.nr_tel );
    cout << "Podaj adres e-mail znajomego: ";
    cin >> osoba.adresEmail;
    while( !szukajZnaku ( osoba.adresEmail, '@' ))
    {
        cout << "Nieprawidlowy adres e-mail. Podaj adres e-mail znajomego: ";
        cin >> osoba.adresEmail;
    }
    cout << "Podaj adres zamieszkania znajomego: ";
    cin.ignore();
    getline ( cin, osoba.adresZamieszkania );

    return osoba;
}

int dodajDaneZnajomego ( vector <Znajomy>& znajomi, int idZalogowanegoUzytkownika, int idOstatniegoZnajomego )
{
    Znajomy osoba;
    int idUzytkownika = idZalogowanegoUzytkownika;
    int iloscZnajomych = znajomi.size();

    osoba = podajDaneNowegoZnajomego ( znajomi, idZalogowanegoUzytkownika, idOstatniegoZnajomego );

    znajomi.push_back(osoba);

    dopiszZnajomegoDoPliku(osoba);
    return ++idOstatniegoZnajomego;
}

vector <Znajomy> wczytywanieZnajomychDoStruktury ( vector <Znajomy>& znajomi, int idZalogowanegoUzytkownika )
{
    string linia;
    int nr_linii = 1;
    fstream plik;

    Znajomy pojedynczyKontakt;

    plik.open ( "ksiazkaAdresowa.txt", ios::in );

    if (plik.is_open())
    {
        while(getline(plik,linia))
        {
            string znajomy[7];
            int koniecStringa = linia.length();
            int index = 0;
            int poczatekSlowa = 0;
            int dlugoscSlowa = 0;
            int indexZnajomego = 0;

            for ( index = 0; index < koniecStringa; index++ )
            {
                if((int) linia[index] == 124)
                {
                    dlugoscSlowa = index - poczatekSlowa;
                    znajomy [ indexZnajomego ] = linia.substr( poczatekSlowa, dlugoscSlowa );
                    poczatekSlowa = index + 1;
                    indexZnajomego++;
                }
            }
                pojedynczyKontakt.id = atoi(znajomy[0].c_str());
                pojedynczyKontakt.idUzytkownika = atoi(znajomy[1].c_str());
                pojedynczyKontakt.imie = znajomy[2];
                pojedynczyKontakt.nazwisko = znajomy[3];
                pojedynczyKontakt.nr_tel = znajomy[4];
                pojedynczyKontakt.adresEmail = znajomy[5];
                pojedynczyKontakt.adresZamieszkania = znajomy[6];

                if ( pojedynczyKontakt.idUzytkownika == idZalogowanegoUzytkownika )
                {
                znajomi.push_back ( pojedynczyKontakt );
                }
        }
        plik.close();

        return znajomi;
    }
    else
    {
        plik.close();
        return znajomi;
    }
}

void wyswietlZnajomych ( vector <Znajomy> znajomi )
{
    int iloscZnajomych = znajomi.size();
    string imie;
    fstream plik;
    char wybor = '0';
    system ( "cls" );
    cout << "LISTA WSZYSTKICH ZNAJOMYCH" << endl;
    cout << endl;

    int ile = 0;

    for ( int i = 0; i < znajomi.size(); i++ )
    {
        if( znajomi[i].id >= 1 )
        {
            ile++;
            cout << znajomi[i].id << "|";
            cout << znajomi[i].imie << "|" << znajomi[i].nazwisko << "|";
            cout << znajomi[i].nr_tel << "|";
            cout << znajomi[i].adresEmail << "|";
            cout << znajomi[i].adresZamieszkania << "|";
            cout << endl;
        }
    }
    Sleep(1500);
    if ( ile <= 0 )
    {
        cout << "Brak znajomych w ksiazce adresowej" << endl;
        Sleep(1500);
    }
    while ( wybor != '1' )
    {
        cout << endl;
        cout << "Aby powrocic do menu glownego, wybierz 1" << endl;
        cin >> wybor;
    }
}

void szukaniePoImieniu ( vector <Znajomy>& znajomi )
{
    int iloscZnajomych = znajomi.size();
    string imie;
    char wybor = '0';
    system ( "cls" );
    cout << "Wyszukiwanie po imieniu. Podaj imie: ";
    cin >> imie;
    system ( "cls" );
    int ile = 0;

    for ( int i = 0; i < iloscZnajomych; i++ )
    {
        if ( znajomi[i].imie == imie )
        {
            ile++;
            cout << znajomi[i].id << "|";
            cout << znajomi[i].imie << "|" << znajomi[i].nazwisko << "|";
            cout << znajomi[i].nr_tel << "|";
            cout << znajomi[i].adresEmail << "|";
            cout << znajomi[i].adresZamieszkania << "|";
            cout << endl;
        }
    }
    Sleep(1500);
    if( ile == 0 )
    {
        cout << "Brak znajomych o tym imieniu" << endl;
        Sleep(1500);
    }
    while ( wybor != '1' )
    {
        cout << endl;
        cout << "Aby powrocic do menu glownego, wybierz 1" << endl;
        cin >> wybor;
    }
}

void szukaniePoNazwisku ( vector <Znajomy>& znajomi )
{
    int iloscZnajomych = znajomi.size();
    string nazwisko;
    char wybor = '0';
    system ( "cls" );
    cout << "Wyszukiwanie po nazwisku. Podaj nazwisko: ";
    cin >> nazwisko;
    system ( "cls" );
    int ile = 0;

    for ( int i = 0; i < iloscZnajomych; i++ )
    {
        if ( znajomi[i].nazwisko == nazwisko )
        {
            ile++;
            cout << znajomi[i].id << "|";
            cout << znajomi[i].imie << "|" << znajomi[i].nazwisko << "|";
            cout << znajomi[i].nr_tel << "|";
            cout << znajomi[i].adresEmail << "|";
            cout << znajomi[i].adresZamieszkania << "|";
            cout << endl;
        }
    }
    Sleep(1500);
    if ( ile == 0 )
    {
        cout << "Brak znajomych o tym nazwisku" << endl;
        Sleep(1500);
    }
    while ( wybor != '1' )
    {
        cout << endl;
        cout << "Aby powrocic do menu glownego, wybierz 1" << endl;
        cin >> wybor;
    }
}

bool jestEdytowane ( vector <Znajomy> znajomi, int idDoEdycji )
{
    if (znajomi.empty())
    {
        system("cls");
        cout << "Brak kontaktow";
        Sleep(1500);
        return true;
    }
    for ( int i = 0; i < znajomi.size(); i++ )
    {
        if ( znajomi[i].id == idDoEdycji )
        {
            return false;
        }
    }
    system("cls");
    cout << "Brak kontaktu o podanym id";
    Sleep(1500);
    return true;
}

vector <Znajomy> wektorEdycjiZnajomych ( vector <Znajomy> znajomi, int indexDoEdycji, char wybor, string daneDoEdycji )
{
    switch ( wybor )
    {
    case '1':
        znajomi[indexDoEdycji].imie = daneDoEdycji;
        break;
    case '2':
        znajomi[indexDoEdycji].nazwisko = daneDoEdycji;
        break;
    case '3':
        znajomi[indexDoEdycji].nr_tel = daneDoEdycji;
        break;
    case '4':
        znajomi[indexDoEdycji].adresEmail = daneDoEdycji;
        break;
    case '5':
        znajomi[indexDoEdycji].adresZamieszkania = daneDoEdycji;
        break;
    }
    return znajomi;
}

Znajomy wczytajPojedynczyKontakt ( string danePojedynczegoZnajomego )
{
    Znajomy pojedynczyKontakt;
    string pojedynczeDane = "";
    int numerPojedynczejDanej = 1;

    for ( int pozycjaZnaku = 0; pozycjaZnaku < danePojedynczegoZnajomego.length(); pozycjaZnaku++ )
    {
        if ( danePojedynczegoZnajomego[pozycjaZnaku] != '|' )
        {
            pojedynczeDane += danePojedynczegoZnajomego[pozycjaZnaku];
        }
        else
        {
            switch ( numerPojedynczejDanej )
            {
            case 1:
                pojedynczyKontakt.id = atoi ( pojedynczeDane.c_str() );
                break;
            case 2:
                pojedynczyKontakt.idUzytkownika = atoi ( pojedynczeDane.c_str() );
                break;
            case 3:
                pojedynczyKontakt.imie = pojedynczeDane;
                break;
            case 4:
                pojedynczyKontakt.nazwisko = pojedynczeDane;
                break;
            case 5:
                pojedynczyKontakt.nr_tel = pojedynczeDane;
                break;
            case 6:
                pojedynczyKontakt.adresEmail = pojedynczeDane;
                break;
            case 7:
                pojedynczyKontakt.adresZamieszkania = pojedynczeDane;
                break;
            }
            pojedynczeDane = "";
            numerPojedynczejDanej++;
        }
    }
    return pojedynczyKontakt;
}

vector <Znajomy> tworzenieTymczasowegoWektoraZnajomych (int idDoEdycji)
{
    Znajomy pojedynczyKontakt;
    vector <Znajomy> znajomiTemp;
    string danePojedynczegoZnajomego = "";

    fstream plik;
    plik.open("ksiazkaAdresowa.txt", ios::in);

   if ( plik.good() == true )
        while (getline ( plik, danePojedynczegoZnajomego ) )
   {
       pojedynczyKontakt = wczytajPojedynczyKontakt ( danePojedynczegoZnajomego );

       if ( pojedynczyKontakt.id != idDoEdycji )
       {
           znajomiTemp.push_back ( pojedynczyKontakt );
       }
   }
   plik.close();
   return znajomiTemp;
}

vector <Znajomy> edycjaDanychWybranegoZnajomego ( vector <Znajomy> znajomi, int idDoEdycji, char wybor, string daneDoEdycji )
{
    string linia;
    int nr_linii = 1;

    vector <Znajomy> znajomiTemp;
    fstream plikTymczasowy;
    int indexDoEdycji;

    for ( int i = 0; i < znajomi.size(); i++ )
    {
        if ( znajomi[i].id == idDoEdycji )
        {
            indexDoEdycji = i;
        }
    }

    znajomi = wektorEdycjiZnajomych ( znajomi, indexDoEdycji, wybor, daneDoEdycji );

    plikTymczasowy.open ( "ksiazkaAdresowa_tymaczasowa.txt", ios::out | ios::app );
    if(plikTymczasowy.good())
    {
        znajomiTemp = tworzenieTymczasowegoWektoraZnajomych ( idDoEdycji );

        if ( idDoEdycji > 1 )
        {
            for ( int i = 0; i < znajomiTemp.size(); i++ )
            {
                if ( znajomiTemp[i].id < idDoEdycji )
                {
                    plikTymczasowy << znajomiTemp[i].id << "|";
                    plikTymczasowy << znajomiTemp[i].idUzytkownika << "|";
                    plikTymczasowy << znajomiTemp[i].imie << "|";
                    plikTymczasowy << znajomiTemp[i].nazwisko << "|";
                    plikTymczasowy << znajomiTemp[i].nr_tel << "|";
                    plikTymczasowy << znajomiTemp[i].adresEmail << "|";
                    plikTymczasowy << znajomiTemp[i].adresZamieszkania << "|" << endl;
                }
            }
        }
        plikTymczasowy << znajomi[indexDoEdycji].id << "|";
        plikTymczasowy << znajomi[indexDoEdycji].idUzytkownika << "|";
        plikTymczasowy << znajomi[indexDoEdycji].imie << "|";
        plikTymczasowy << znajomi[indexDoEdycji].nazwisko << "|";
        plikTymczasowy << znajomi[indexDoEdycji].nr_tel << "|";
        plikTymczasowy << znajomi[indexDoEdycji].adresEmail << "|";
        plikTymczasowy << znajomi[indexDoEdycji].adresZamieszkania << "|" << endl;


        if ( idDoEdycji < znajomiTemp.size() + 1 )
        {
            for ( int i = 0; i < znajomiTemp.size(); i++ )
            {
                if ( znajomiTemp[i].id > idDoEdycji )
                {
                    plikTymczasowy << znajomiTemp[i].id << "|";
                    plikTymczasowy << znajomiTemp[i].idUzytkownika << "|";
                    plikTymczasowy << znajomiTemp[i].imie << "|";
                    plikTymczasowy << znajomiTemp[i].nazwisko << "|";
                    plikTymczasowy << znajomiTemp[i].nr_tel << "|";
                    plikTymczasowy << znajomiTemp[i].adresEmail << "|";
                    plikTymczasowy << znajomiTemp[i].adresZamieszkania << "|" << endl;
                }
            }
        }
        plikTymczasowy.close();

        remove("ksiazkaAdresowa.txt");
        rename("ksiazkaAdresowa_tymaczasowa.txt", "ksiazkaAdresowa.txt");

        cout << "Kontakt zedytowany" << endl;
        Sleep(1500);
        return znajomi;
    }
    else
    {
        plikTymczasowy.close();
        cout << "Blad odczytu pliku!" << endl;
        Sleep(1000);
        return znajomi;
    }
}

bool czyIdJestPoprawne (vector <Znajomy> znajomi, int idDoUsuniecia)
{
    for (int i = 0; i < znajomi.size(); i++)
    {
        if (znajomi[i].id == idDoUsuniecia)
        {
            return true;
        }
    }
    return false;
}

void usunWybranaLinieWPliku ( int numerUsuwanejLinii )
{
    fstream odczytywanyPlikTekstowy, tymczasowyPlikTekstowy;
    string wczytanaLinia = "";
    int numerWczytanejLinii = 1;

    odczytywanyPlikTekstowy.open ( "ksiazkaAdresowa.txt", ios::in );
    tymczasowyPlikTekstowy.open ( "ksiazkaAdresowa_tymaczasowa.txt", ios::out | ios::app);

    if (odczytywanyPlikTekstowy.good() == true && numerUsuwanejLinii != 0)
    {
        while (getline(odczytywanyPlikTekstowy, wczytanaLinia))
        {
            if (numerWczytanejLinii == numerUsuwanejLinii) {}
            else if (numerWczytanejLinii == 1 && numerWczytanejLinii != numerUsuwanejLinii)
                tymczasowyPlikTekstowy << wczytanaLinia;
            else if (numerWczytanejLinii == 2 && numerUsuwanejLinii == 1)
                tymczasowyPlikTekstowy << wczytanaLinia;
            else if (numerWczytanejLinii > 2 && numerUsuwanejLinii == 1)
                tymczasowyPlikTekstowy << endl << wczytanaLinia;
            else if (numerWczytanejLinii > 1 && numerUsuwanejLinii != 1)
                tymczasowyPlikTekstowy << endl << wczytanaLinia;
            numerWczytanejLinii++;
        }
        odczytywanyPlikTekstowy.close();
        tymczasowyPlikTekstowy.close();

        remove ( "ksiazkaAdresowa.txt" );
        rename ( "ksiazkaAdresowa_tymaczasowa.txt", "ksiazkaAdresowa.txt" );
    }
}

int zwrocNumerLiniiSzukanegoAdresata ( int idZnajomego )
{
    bool czyIstniejeZnajomy = false;
    int numerLiniiWPlikuTekstowym = 1;
    string daneJednegoZnajomegoOddzielonePionowymiKreskami = "";
    fstream plik;
    plik.open ( "ksiazkaAdresowa.txt", ios::in );

    if (plik.good() == true && idZnajomego != 0)
    {
        while ( getline ( plik, daneJednegoZnajomegoOddzielonePionowymiKreskami ) )
        {
            if ( idZnajomego == pobierzIdZnajomegoZDanychOddzielonychPionowymiKreskami ( daneJednegoZnajomegoOddzielonePionowymiKreskami ) )
            {
                czyIstniejeZnajomy = true;
                plik.close();
                return numerLiniiWPlikuTekstowym;
            }
            else
                numerLiniiWPlikuTekstowym++;
        }
        if (czyIstniejeZnajomy = false)
        {
            plik.close();
            return 0;
        }
    }
    return 0;
}

int usunZnajomegoZKsiazkiAdresowej ( vector <Znajomy> znajomi )
{
    fstream plikTymczasowy;
    char wybor;
    vector <Znajomy> znajomiTemp;
    int idUsuwanegoZnajomego = 0;
    int numerLiniiUsuwanegoZnajomego = 0;
    bool czyZnajomyIstnieje = false;

    system("cls");

    if ( !znajomi.empty() )
    {
        cout << "Podaj id kontaktu do usuniecia: ";
        cin >> idUsuwanegoZnajomego;

            for ( int i = 0; i < znajomi.size(); i++ )
        {
            if ( znajomi[i].id == idUsuwanegoZnajomego )
            {
                cout << znajomi[i].id << "|";
                cout << znajomi[i].imie << "|" << znajomi[i].nazwisko << "|";
                cout << znajomi[i].nr_tel << "|";
                cout << znajomi[i].adresEmail << "|";
                cout << znajomi[i].adresZamieszkania << "|";
                cout << endl;
            }
        }

        znajomiTemp = tworzenieTymczasowegoWektoraZnajomych ( idUsuwanegoZnajomego );

        for ( vector <Znajomy> ::iterator itr = znajomi.begin(); itr != znajomi.end(); itr++ )
        {
            if ( itr -> id == idUsuwanegoZnajomego )
            {
                czyZnajomyIstnieje = true;

                cout << endl << "Czy jestes pewien, ze chcesz usunac znajomego z ksiazki adresowej?" << endl;
                cout << "<Jesli tak, wcisnij 't'. Aby wyjsc z programu nacisnij jakikolwiek inny klawisz>" << endl;
                char znak;
                cin >> znak;

                if (znak == 't')
                {
                    cout << "Wybrales usuniecie znajomego z ksiazki adresowej" << endl;

                    numerLiniiUsuwanegoZnajomego = zwrocNumerLiniiSzukanegoAdresata ( idUsuwanegoZnajomego );
                    usunWybranaLinieWPliku ( numerLiniiUsuwanegoZnajomego );

                    znajomi.erase(itr);

                    system("cls");
                    cout << "Kontakt usuniety!" << endl;
                    Sleep(1000);
                    return idUsuwanegoZnajomego;
                }
                else
                {
                    system("cls");
                    cout << "Nie usunieto kontaktu!";
                    Sleep(1000);
                    return 0;
                }
            }
        }
        if ( czyZnajomyIstnieje == false )
        {
            cout << "Kontakt o podanym id nie istnieje!" << endl;
            Sleep(1000);
            return 0;
        }
    }
    else
    {
        cout << "Brak kontaktow!";
        Sleep(1000);
        return 0;
    }
}

int main()
{
    vector <Znajomy> znajomi;
    vector <Uzytkownik> uzytkownicy;
    int idZnajomego = 0;
    int iloscZnajomych = 0;
    int iloscUzytkownikow = 0;
    int idDoEdycji;
    int idUsunietegoZnajomego = 0;
    int idZalogowanegoUzytkownika = 0;
    int czyMenuJestAktywne = true;
    int czyMenuEdycjiJestAktywne = true;
    int idOstatniegoZnajomego = 0;

    char wybor;

    uzytkownicy = wczytywanieUzytkownikowDoStruktury ( uzytkownicy );
    iloscZnajomych = znajomi.size();
    iloscUzytkownikow = uzytkownicy.size();

    while ( 1 )
    {
        if ( idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "   MENU GLOWNE" << endl;
            cout << "------------------" << endl;
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << "------------------" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if (wybor == '1')
            {
                system("cls");
                uzytkownicy = rejestracja ( uzytkownicy, iloscUzytkownikow );
            }
            else if (wybor == '2')
            {
                system("cls");
                idZalogowanegoUzytkownika = logowanie ( uzytkownicy, iloscUzytkownikow );

                system ( "cls");
                cout << "Witaj " << uzytkownicy[idZalogowanegoUzytkownika-1].nazwa << " w programie Ksiazka adresowa" << endl;
                Sleep(1000);
            }
            else if (wybor == '9')
            {
                exit(0);
            }
        }
        else
        {
            if ( czyMenuJestAktywne )
            {
            znajomi.clear();
            idOstatniegoZnajomego = wczytajZnajomychZalogowanegoUzytkownikaZPliku ( znajomi, idZalogowanegoUzytkownika );

            system ( "cls");
            cout << "        MENU UZYTKOWNIKA" << endl;
            cout << "---------------------------------" << endl;
            cout << "1. Dodaj dane znajomego" << endl;
            cout << "2. Wyszukaj znajomych po imieniu" << endl;
            cout << "3. Wyszukaj znajomych po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich znajomych" << endl;
            cout << "5. Usun znajomego" << endl;
            cout << "6. Edytuj dane znajomego" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout << "---------------------------------" << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if ( wybor == '1' )
            {
                system ( "cls" );
                idOstatniegoZnajomego = dodajDaneZnajomego ( znajomi, idZalogowanegoUzytkownika, idOstatniegoZnajomego );
            }
            else if ( wybor == '2' )
            {
                szukaniePoImieniu ( znajomi );
            }
            else if ( wybor == '3' )
            {
                szukaniePoNazwisku ( znajomi );
            }
            else if ( wybor == '4' )
            {
                system ( "cls" );
                wyswietlZnajomych ( znajomi );
            }
            else if ( wybor == '5' )
            {
                system ( "cls" );
                idUsunietegoZnajomego = usunZnajomegoZKsiazkiAdresowej ( znajomi );
                idOstatniegoZnajomego = podajIdOstatniegoZnajomegoPoUsunieciuWybranegoZnajomego ( idUsunietegoZnajomego, idOstatniegoZnajomego );
            }
            else if ( wybor == '6' )
            {
                system ( "cls" );
                cout << "Podaj id kontaktu ktory chcesz edytowac: ";
                cin >> idDoEdycji;
                czyMenuJestAktywne = jestEdytowane ( znajomi, idDoEdycji );
                czyMenuEdycjiJestAktywne = true;
            }
            else if ( wybor == '7' )
            {
                system ( "cls" );
                uzytkownicy = zmianaHaslaUzytkownika ( uzytkownicy, idZalogowanegoUzytkownika );
            }
            else if ( wybor == '9' )
            {
                system ( "cls" );
                cout << "Wylogowywanie";
                cout << endl;
                Sleep(1000);
                idZalogowanegoUzytkownika = 0;
                znajomi.clear();
            }
            }
            else
            {
                while( czyMenuEdycjiJestAktywne )
                {
                    int ile = 0;

                    for ( int i = 0; i < znajomi.size(); i++ )
                    {
                        if ( znajomi[i].id == idDoEdycji )
                        {
                            system ("cls");
                            ile++;
                            cout << "EDYCJA DANYCH ZNAJOMEGO" << endl;
                            cout << endl;
                            cout << znajomi[i].id << "|";
                            cout << znajomi[i].imie << "|" << znajomi[i].nazwisko << "|";
                            cout << znajomi[i].nr_tel << "|";
                            cout << znajomi[i].adresEmail << "|";
                            cout << znajomi[i].adresZamieszkania << "|";
                            cout << endl;
                        }
                    }
                    cout << endl;
                    cout << "Wybierz dane znajomego ktore chcesz edytowac:" << endl;
                    cout << "1 - Imie" << endl;
                    cout << "2 - Nazwisko" << endl;
                    cout << "3 - Numer telefonu" << endl;
                    cout << "4 - Email" << endl;
                    cout << "5 - Adres" << endl;
                    cout << "6 - Powrot do menu glownego" << endl;

                    cout << endl;
                    cout << "Twoj wybor: ";
                    cin >> wybor;

                    if ( wybor == '1' )
                    {
                        system("cls");
                        string edytujImie;
                        cout << "Podaj nowe imie: ";
                        cin >> edytujImie;
                        znajomi = edycjaDanychWybranegoZnajomego ( znajomi, idDoEdycji, wybor, edytujImie );
                    }
                    else if ( wybor == '2' )
                    {
                        system("cls");
                        string edytujNazwisko;
                        cout << "Podaj nowe nazwisko: ";
                        cin >> edytujNazwisko;
                        znajomi = edycjaDanychWybranegoZnajomego ( znajomi, idDoEdycji, wybor, edytujNazwisko );
                    }
                    else if ( wybor == '3' )
                    {
                        system("cls");
                        string edytujNrTel;
                        cout << "Podaj nowy numer telefonu: ";
                        cin.ignore();
                        getline ( cin, edytujNrTel );
                        znajomi = edycjaDanychWybranegoZnajomego ( znajomi, idDoEdycji, wybor, edytujNrTel );
                    }
                    else if ( wybor == '4' )
                    {
                        system("cls");
                        string edytujEmail;
                        cout << "Podaj nowy adres e-mail: ";
                        cin >> edytujEmail;
                        znajomi = edycjaDanychWybranegoZnajomego ( znajomi, idDoEdycji, wybor, edytujEmail );
                        break;
                    }
                    else if ( wybor == '5' )
                    {
                        system("cls");
                        string edytujAdresZamieszkania;
                        cout << "Podaj nowy adres zamieszkania: ";
                        cin.ignore();
                        getline ( cin, edytujAdresZamieszkania );
                        znajomi = edycjaDanychWybranegoZnajomego ( znajomi, idDoEdycji, wybor, edytujAdresZamieszkania );
                    }
                    else if ( wybor == '6' )
                    {
                        system("cls");
                        cout << "Wybrano powrot do menu glownego";
                        Sleep(1000);
                        znajomi = znajomi;
                        czyMenuJestAktywne = true;
                        czyMenuEdycjiJestAktywne = false;
                    }
                }
            }
        }
    }
    return 0;
}
