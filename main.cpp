#include <iostream>
#include <fstream>
#include <windows.h>
#include <cstdlib>
#include <vector>
#include <conio.h>

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

vector <Znajomy> dodanieDanych ( vector <Znajomy> znajomi, int idZalogowanegoUzytkownika )
{
    Znajomy osoba;
    string imie, nazwisko, nr_tel, adresEmail, adresZamieszkania;
    int iloscZnajomych = znajomi.size();
    int idUzytkownika = idZalogowanegoUzytkownika;
    cout << iloscZnajomych << endl;
    system ("pause");

    fstream plik;
    plik.open("ksiazkaAdresowa.txt");
    if (plik.good())
    {
        plik.close();
    }
    else
    {
        plik.open("ksiazkaAdresowa.txt", ios::out);
        plik.close();
    }
    int ostatnieId;
    if(znajomi.empty())
    {
        ostatnieId = 0;
    }
    else
    {
        ostatnieId = znajomi[iloscZnajomych - 1].id;
    }

    system("cls");
    string daneAdresata;
    cout << "Podaj imie znajomego: ";
    cin >> imie;
    cout << "Podaj nazwisko znajomego: ";
    cin >> nazwisko;

    int i = 0;
    while ( i < iloscZnajomych )
    {
        if (( znajomi[i].imie == imie ) && ( znajomi[i].nazwisko == nazwisko ))
        {
            cout << "Znajomy o takich danych juz istnieje. Wpisz inne dane: " << endl;
            cout << "Podaj imie znajomego: ";
            cin >> imie;
            cout << "Podaj nazwisko znajomego: ";
            cin >> nazwisko;
        }
        else
        {
            i++;
        }
    }
    cout << "Podaj numer telefonu znajomego: ";
    cin.sync();
    getline ( cin, nr_tel );
    cout << "Podaj adres e-mail znajomego: ";
    cin >> adresEmail;
    while( !szukajZnaku ( adresEmail, '@' ))
    {
        cout << "Nieprawidlowy adres e-mail. Podaj adres e-mail znajomego: ";
        cin >> adresEmail;
    }
    cout << "Podaj adres zamieszkania znajomego: ";
    cin.ignore();
    getline ( cin, adresZamieszkania );

    osoba = {ostatnieId + 1, idUzytkownika, imie, nazwisko, nr_tel, adresEmail, adresZamieszkania };
    znajomi.push_back(osoba);

    plik.open ( "ksiazkaAdresowa.txt", ios::out | ios::app );

    if ( plik.good() == true )
    {
        plik << znajomi[iloscZnajomych].id << "|";
        plik << idZalogowanegoUzytkownika << "|";
        plik << znajomi[iloscZnajomych].imie << "|";
        plik << znajomi[iloscZnajomych].nazwisko << "|";
        plik << znajomi[iloscZnajomych].nr_tel << "|";
        plik << znajomi[iloscZnajomych].adresEmail << "|";
        plik << znajomi[iloscZnajomych].adresZamieszkania << "|";
        plik << endl;

        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych" << endl;
        Sleep(1000);
    }

    cout << "Dane znajomego zostaly dodane" << endl;
    Sleep(1000);
    return znajomi;
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

vector <Znajomy> edycjaDanychWybranegoZnajomego ( vector <Znajomy> znajomi, int idDoEdycji, char wybor, string daneDoEdycji )
{
    fstream plik;
    int indexDoEdycji;

    for ( int i = 0; i < znajomi.size(); i++ )
    {
        if ( znajomi[i].id == idDoEdycji )
        {
            indexDoEdycji = i;
        }
    }

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

    plik.open("ksiazkaAdresowa.txt", ios::out);
    if ( plik.good() )
    {
        if ( idDoEdycji > 1 )
        {
            for ( int i = 0; i < indexDoEdycji; i++ )
            {
                plik << znajomi[i].id << "|";
                plik << znajomi[i].idUzytkownika << "|";
                plik << znajomi[i].imie << "|";
                plik << znajomi[i].nazwisko << "|";
                plik << znajomi[i].nr_tel << "|";
                plik << znajomi[i].adresEmail << "|";
                plik << znajomi[i].adresZamieszkania << "|" << endl;
            }
        }
        plik << znajomi[indexDoEdycji].id << "|";
        plik << znajomi[indexDoEdycji].idUzytkownika << "|";
        plik << znajomi[indexDoEdycji].imie << "|";
        plik << znajomi[indexDoEdycji].nazwisko << "|";
        plik << znajomi[indexDoEdycji].nr_tel << "|";
        plik << znajomi[indexDoEdycji].adresEmail << "|";
        plik << znajomi[indexDoEdycji].adresZamieszkania << "|" << endl;

        if (  indexDoEdycji + 1 < znajomi.size() )
        {
            for ( int i = idDoEdycji; i < znajomi.size(); i++ )
            {
                plik << znajomi[i].id << "|";
                plik << znajomi[i].idUzytkownika << "|";
                plik << znajomi[i].imie << "|";
                plik << znajomi[i].nazwisko << "|";
                plik << znajomi[i].nr_tel << "|";
                plik << znajomi[i].adresEmail << "|";
                plik << znajomi[i].adresZamieszkania << "|" << endl;
            }
        }
        plik.close();
        cout << "Kontakt zedytowany" << endl;
        Sleep(1500);
        return znajomi;
    }
    else
    {
        plik.close();
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

vector <Znajomy> usuniecieZnajomegoZKsiazkiAdresowej ( vector <Znajomy> znajomi, int idDoUsuniecia )
{
    char wybor;
    fstream plik;

    system("cls");

    bool poprawneId = czyIdJestPoprawne ( znajomi, idDoUsuniecia );

    if (poprawneId)
    {
        int ile = 0;

        for ( int i = 0; i < znajomi.size(); i++ )
        {
            if ( znajomi[i].id == idDoUsuniecia )
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

        cout << endl << "Czy jestes pewien, ze chcesz usunac znajomego z ksiazki adresowej?" << endl << "<Jesli tak, wcisnij 't'. Aby wyjsc z programu nacisnij jakikolwiek inny klawisz>" << endl;
        char znak;
        cin >> znak;

        if (znak == 't')
        {
            cout << "Wybrales usuniecie znajomego z ksiazki adresowej" << endl;

            plik.open("Plik tymczasowy.txt", ios::out);
            if(plik.good())
            {
                for (int i = 0; i < znajomi.size(); i++)
                {
                    if (idDoUsuniecia == znajomi[i].id)
                    {
                        continue;
                    }
                    else
                    {
                        plik << znajomi[i].id << "|";
                        plik << znajomi[i].idUzytkownika << "|";
                        plik << znajomi[i].imie << "|";
                        plik << znajomi[i].nazwisko << "|";
                        plik << znajomi[i].nr_tel << "|";
                        plik << znajomi[i].adresEmail << "|";
                        plik << znajomi[i].adresZamieszkania << "|" << endl;
                    }
                }
                plik.close();

                remove("ksiazkaAdresowa.txt");
                rename("Plik tymczasowy.txt", "ksiazkaAdresowa.txt");


                int indexDoUsuniecia = 0;
                for (int i = 1; i < znajomi.size(); i++)
                {
                    if (znajomi[i].id == idDoUsuniecia)
                    {
                        indexDoUsuniecia = i;

                    }
                }
                znajomi.erase ( znajomi.begin() + indexDoUsuniecia);

                system("cls");
                cout << "Kontakt usuniety!" << endl;
                Sleep(1000);
                return znajomi;
            }
            else
            {
                plik.close();
                system("cls");
                cout << "Blad odczytu pliku!" << endl;
                Sleep(1000);
                return znajomi;
            }
        }
        else
        {
            system("cls");
            cout << "Nie usunieto kontaktu!";
            Sleep(1000);
            return znajomi;
        }
    }
    else
    {
        system("cls");
        cout << "Kontakt o podanym id nie istnieje!";
        Sleep(1000);
        return znajomi;
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
    int idDoUsuniecia;
    int idZalogowanegoUzytkownika = 0;
    int czyMenuJestAktywne = true;
    int czyMenuEdycjiJestAktywne = true;

    char wybor;

    uzytkownicy = wczytywanieUzytkownikowDoStruktury ( uzytkownicy );
    iloscZnajomych = znajomi.size();
    iloscUzytkownikow = uzytkownicy.size();

    while ( 1 )
    {
        if ( idZalogowanegoUzytkownika == 0)
        {
            system("cls");
            cout << "1. Rejestracja" << endl;
            cout << "2. Logowanie" << endl;
            cout << "9. Zakoncz program" << endl;
            cout << endl;
            cin >> wybor;

            if (wybor == '1')
            {
                uzytkownicy = rejestracja ( uzytkownicy, iloscUzytkownikow );
            }
            else if (wybor == '2')
            {
                idZalogowanegoUzytkownika = logowanie ( uzytkownicy, iloscUzytkownikow );
                znajomi = wczytywanieZnajomychDoStruktury ( znajomi, idZalogowanegoUzytkownika );
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
            system ( "cls");
            cout << "1. Dodaj dane znajomego" << endl;
            cout << "2. Wyszukaj znajomych po imieniu" << endl;
            cout << "3. Wyszukaj znajomych po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich znajomych" << endl;
            cout << "5. Usun znajomego" << endl;
            cout << "6. Edytuj dane znajomego" << endl;
            cout << "7. Zmien haslo" << endl;
            cout << "9. Wyloguj sie" << endl;
            cout << endl;
            cout << "Twoj wybor: ";
            cin >> wybor;

            if ( wybor == '1' )
            {
                system ( "cls" );
                znajomi = dodanieDanych ( znajomi, idZalogowanegoUzytkownika );
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
                cout << "Podaj id kontaktu ktory chcesz usunac: ";
                cin >> idDoUsuniecia;
                znajomi = usuniecieZnajomegoZKsiazkiAdresowej ( znajomi, idDoUsuniecia );
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
