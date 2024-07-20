
#include <list>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <iomanip> //pentru setarea coloanei la afisare

#include <thread> //pentru comanda de asteptare
#include <chrono> //pentru comanda de asteptare

#include <Windows.h>

using namespace std;

class Suc {
	string nume, fructProvenienta;
	int cantitate;

protected:
	Suc(string nume, string fructProvenienta, int cantitate) {
		this->nume = nume;
		this->fructProvenienta = fructProvenienta;
		this->cantitate = cantitate;
	}

public:
	virtual void afisare_suc() {
		cout << "-------------------------------------------------------------------------------------------------------" << endl;
		cout << "Nume: " << left << setw(14) << nume;
		cout << "Fruct provenienta: " << left << setw(12) << fructProvenienta << "\t";
		cout << "Cantitate ramasa: " << cantitate << "\t";
	}

	string get_nume()
	{
		return nume;
	}

	string get_provenienta() {
		return fructProvenienta;
	}

	int get_cantitate() {
		return cantitate;
	}

	int get_cantitateMinusUnu() {
		cantitate = cantitate--;
		return cantitate;
	}

	void get_cantitateMinusUnuDepozit()
	{
		if (cantitate > 1)
			cantitate = cantitate - 1;
		else
		{
			cantitate = 100;
		}
	}

	void get_cantitatePlusZece()
	{
		cantitate = cantitate + 10;
	}

	void cantitateCompletare(list<Suc*>sucuriPreparator, list<Suc*>sucuriDepozit, string numeSucDepozit) {
		for (Suc* d : sucuriDepozit) {
			if (d->get_nume() == numeSucDepozit) {
				d->get_cantitateMinusUnuDepozit();
			}
		}

		for (Suc* p : sucuriPreparator) {
			if (p->get_nume() == numeSucDepozit) {
				p->get_cantitatePlusZece();
			}
		}
	}

	virtual int returnare_zahar()
	{
		return 3;
	}

	virtual float cantitate_zahar()
	{
		return 0;
	}

	virtual string indulcitor_suc()
	{
		return "necunoscut";
	}
};

class DaSuc : Suc
{
private:
	float cantitateZahar;
	bool zahar;

public:
	DaSuc(string nume, string fructProvenienta, int cantitate, float cantitateZahar) : Suc(nume, fructProvenienta, cantitate)
	{
		this->cantitateZahar = cantitateZahar;
		zahar = 1;
	}

	void afisare_suc()
		override
	{
		Suc::afisare_suc();
		cout << "Cantitate zahar: " << cantitateZahar;
	}

	int returnare_zahar()
	{
		return zahar;
	}

	float cantitate_zahar()
		override
	{
		return cantitateZahar;
	}
};

class NuSuc : Suc
{
private:
	string indulcitor;
	bool zahar;

public:
	NuSuc(string nume, string fructProvenienta, int cantitate, string indulcitor) : Suc(nume, fructProvenienta, cantitate)
	{
		this->indulcitor = indulcitor;
		zahar = 0;
	}

	void afisare_suc()
		override
	{
		Suc::afisare_suc();
		cout << "Indulcitor: " << indulcitor;
	}

	int returnare_zahar()
	{
		return zahar;
	}

	string indulcitor_suc()
		override
	{
		return indulcitor;
	}
};

class Depozit
{
private:
	list <Suc*> sucuri;

public:
	Depozit(list<Suc*>s)
	{
		sucuri.assign(s.begin(), s.end());
	}

	void afisare_depozit()
	{
		for (Suc* x : sucuri)
		{
			x->afisare_suc();
			cout << endl;
		}
	}
};

class Client
{
private:
	string nume, email, parola;
	list <string> sucuri;

public:
	Client(string nume, string email, string parola)
	{
		this->nume = nume;
		this->email = email;
		this->parola = parola;
	}

	void afisare_client()
	{
		cout << "-----------------------------------" << endl;
		cout << "Nume: " << nume << endl;
		cout << "Email: " << email << endl;
		cout << "Parola: " << parola;
	}

	string get_email()
	{
		return email;
	}

	string get_nume()
	{
		return nume;
	}

	string get_parola()
	{
		return parola;
	}

	void modificare_parola(string parola_noua)
	{
		parola = parola_noua;
	}

	//adauga un suc in lista existenta
	void adaugare_suc_la_utilizator(string s)
	{
		sucuri.push_back(s);
	}

	//egaleza lista de sucuri din clasa cu lista primita
	void adaugareListaLaUtilizator(list<string>sucuriDinFisier) {
		sucuri = sucuriDinFisier;
	}

	void afisareListaSucuri() {
		for (string s : sucuri) {
			cout << s << endl;
		}
	}

	void scriereFisierClasaClientUrmator(ofstream& fout) {
		for (string s : sucuri) {
			fout << s << endl;
		}
		fout << "EndList" << endl;
	}
};

Client* clientPrezent = nullptr;

//Creare fisiere necesare. Daca aceste fisiere exista - functiile pot fi oprite
#if 1
static void creareFisierDepozit() {
	ofstream fout;
	fout.open("depozit.txt"); //de scriere
	fout << "Aspartam " << "Denumire fruct: Mere " << "Contine zahar: 0 " << "Indulcitor: Aspartam " << "Cantitate: 48 / 100" << endl;
	fout << "Sucraloza " << "Denumire fruct: Pere " << "Contine zahar: 0 " << "Indulcitor: Sucraloza " << "Cantitate: 28 / 100" << endl;
	fout << "Zaharina " << "Denumire fruct: Arbuz " << "Contine zahar: 0 " << "Indulcitor: Zaharina " << "Cantitate: 13 / 100" << endl;
	fout << "Stevia " << "Denumire fruct: Visine " << "Contine zahar: 0 " << "Indulcitor: Stevia " << "Cantitate: 36 / 100" << endl;
	fout << "Eritritol " << "Denumire fruct: Capsuni " << "Contine zahar: 0 " << "Indulcitor: Eritritol " << "Cantitate: 73 / 100" << endl;
	fout << "Orange " << "Denumire fruct: Portocale " << "Contine zahar: 1 " << "Cantitate de zahar: 0.22 " << "Cantitate: 10 / 100" << endl;
	fout << "Cola " << "Denumire fruct: Lamaie " << "Contine zahar: 1 " << "Cantitate de zahar: 0.66 " << "Cantitate: 86 / 100" << endl;
	fout << "Fanta " << "Denumire fruct: Portocale " << "Contine zahar: 1 " << "Cantitate de zahar: 0.64 " << "Cantitate: 23 / 100" << endl;
	fout << "Pepsi " << "Denumire fruct: Lamaie " << "Contine zahar: 1 " << "Cantitate de zahar: 0.6 " << "Cantitate: 16 / 100" << endl;
	fout << "Aloe " << "Denumire fruct: Aloe " << "Contine zahar: 1 " << "Cantitate de zahar: 0.1 " << "Cantitate: 40 / 100" << endl;
	fout << "EndList";
	fout.close();
}
void creareFisierPreparator() {
	ofstream fout;
	fout.open("preparator.txt"); //de scriere
	fout << "Aspartam " << "Fruct provenienta: Mere " << "Contine zahar: 0 " << "Indulcitor: Aspartam " << "Cantitate: 4" << endl;
	fout << "Sucraloza " << "Fruct provenienta: Pere " << "Contine zahar: 0 " << "Indulcitor: Sucraloza " << "Cantitate: 2" << endl;
	fout << "Zaharina " << "Fruct provenienta: Arbuz " << "Contine zahar: 0 " << "Indulcitor: Zaharina " << "Cantitate: 1" << endl;
	fout << "Stevia " << "Fruct provenienta: Visine " << "Contine zahar: 0 " << "Indulcitor: Stevia " << "Cantitate: 3" << endl;
	fout << "Eritritol " << "Fruct provenienta: Capsuni " << "Contine zahar: 0 " << "Indulcitor: Eritritol " << "Cantitate: 7" << endl;
	fout << "Orange " << "Fruct provenienta: Portocale " << "Contine zahar: 1 " << "Cantitate de zahar: 0.22 " << "Cantitate: 1" << endl;
	fout << "Cola " << "Fruct provenienta: Lamaie " << "Contine zahar: 1 " << "Cantitate de zahar: 0.66 " << "Cantitate: 8" << endl;
	fout << "Fanta " << "Fruct provenienta: Portocale " << "Contine zahar: 1 " << "Cantitate de zahar: 0.64 " << "Cantitate: 2" << endl;
	fout << "Pepsi " << "Fruct provenienta: Lamaie " << "Contine zahar: 1 " << "Cantitate de zahar: 0.6 " << "Cantitate: 1" << endl;
	fout << "Aloe " << "Fruct provenienta: Aloe " << "Contine zahar: 1 " << "Cantitate de zahar: 0.1 " << "Cantitate: 4" << endl;
	fout << "EndList";
	fout.close();
}
void creareFisierClienti() {
	ofstream fout;
	fout.open("clienti.txt"); //de scriere
	fout << "Alexandru alexandru.client@gmail.com parola1" << endl;
	fout << "Denis denis.client@gmail.com parola2" << endl;
	fout << "Victoria victoria.client@gmail.com parola3" << endl;
	fout << "Bogdana bogdana.client@gmail.com parola4" << endl;
	fout << "EndList";
	fout.close();
}
void creareFisierIstoricComenzi() {
	ofstream fout;
	fout.open("istoricComenzi.txt"); //de scriere
	fout << "alexandru.client@gmail.com" << endl;
	fout << "Pepsi" << endl << "Cola" << endl << "Orange" << endl << "Stevia" << endl;
	fout << "EndList" << endl;
	fout << "denis.client@gmail.com" << endl;
	fout << "Pepsi" << endl << "Fanta" << endl << "Orange" << endl << "Stevia" << endl;
	fout << "EndList" << endl;
	fout << "victoria.client@gmail.com" << endl;
	fout << "Stevia" << endl;
	fout << "EndList" << endl;
	fout << "bogdana.client@gmail.com" << endl;
	fout << "Orange" << endl << "Cola" << endl << "Orange" << endl;
	fout << "EndList" << endl;
	fout << "EndFisier";
	fout.close();
}

//Verificare daca exista fisierele necesare
void verificareExistentaFisiereNecesare() {
	ifstream file;
	string depozit = "depozit.txt";
	string preparator = "preparator.txt";
	string clienti = "clienti.txt";
	string istoricComenzi = "istoricComenzi.txt";

	file.open(depozit);
	if (file.good()) {
		Sleep(300);
		cout << depozit << " a fost deschis" << endl;
	}
	else {
		cout << "Fisierul " << depozit << " nu exista sau nu poate fi deschis.\n";
		Sleep(500);
		creareFisierDepozit();
		cout << "Fisierul " << depozit << " a fost creat" << endl;
		Sleep(500);
	}
	file.close();

	file.open(preparator);
	if (file.good()) {
		Sleep(300);
		cout << preparator << " a fost deschis" << endl;
	}
	else {
		Sleep(500);
		cout << "Fisierul " << preparator << " nu exista sau nu poate fi deschis.\n";
		creareFisierPreparator();
		Sleep(500);
		cout << "Fisierul " << preparator << " a fost creat" << endl;
	}
	file.close();

	file.open(clienti);
	if (file.good()) {
		Sleep(300);
		cout << clienti << " a fost deschis" << endl;
	}
	else {
		Sleep(500);
		cout << "Fisierul " << clienti << " nu exista sau nu poate fi deschis.\n";
		creareFisierClienti();
		Sleep(500);
		cout << "Fisierul " << clienti << " a fost creat" << endl;
	}
	file.close();

	file.open(istoricComenzi);
	if (file.good()) {
		Sleep(300);
		cout << istoricComenzi << " a fost deschis" << endl;
	}
	else {
		Sleep(500);
		cout << "Fisierul " << istoricComenzi << " nu exista sau nu poate fi deschis.\n";
		creareFisierIstoricComenzi();
		Sleep(500);
		cout << "Fisierul " << istoricComenzi << " a fost creat" << endl;
		cout << "Apasati un buton!" << endl;
		char ch = _getch();
	}
	file.close();
	Sleep(800);
}
#endif

//Scriere in fisiere dupa modificari -------------------------------------------
#if 1
void scriereFisierDepozitUrmator(list<Suc*>sucuriDepozit) {
	ofstream fout;
	fout.open("depozit.txt"); //de scriere
	for (Suc* x : sucuriDepozit) {
		if (x->returnare_zahar() == 0)
			fout << x->get_nume() << " Denumire fruct: " << x->get_provenienta() << " Contine zahar: 0 " << "Indulcitor: " << x->indulcitor_suc() << " Cantitate: " << x->get_cantitate() << " / 100" << endl;
		else {
			fout << x->get_nume() << " Denumire fruct: " << x->get_provenienta() << " Contine zahar: 1 " << "Cantitate de zahar: " << x->cantitate_zahar() << " Cantitate: " << x->get_cantitate() << " / 100" << endl;
		}
	}
	fout << "EndList";
	fout.close();
}
void scriereFisierPreparatorUrmator(list<Suc*>sucuriPreparator) {
	ofstream fout;
	fout.open("preparator.txt"); //de scriere
	for (Suc* x : sucuriPreparator) {
		if (x->returnare_zahar() == 0)
			fout << x->get_nume() << " Fruct provenienta: " << x->get_provenienta() << " Contine zahar: 0 " << "Indulcitor: " << x->indulcitor_suc() << " Cantitate: " << x->get_cantitate() << endl;
		else {
			fout << x->get_nume() << " Fruct provenienta: " << x->get_provenienta() << " Contine zahar: 1 " << "Cantitate de zahar: " << x->cantitate_zahar() << " Cantitate: " << x->get_cantitate() << endl;
		}
	}
	fout << "EndList";
	fout.close();
}
void scriereFisierClientiUrmator(list<Client*>clienti) {
	ofstream fout;
	fout.open("clienti.txt"); //de scriere
	for (Client* x : clienti) {
		fout << x->get_nume() << " " << x->get_email() << " " << x->get_parola() << endl;
	}
	fout << "EndList";
	fout.close();
}
void scriereFisierIstoricComenziUrmator(list<Client*>clienti) {
	ofstream fout;
	fout.open("istoricComenzi.txt"); //de scriere

	for (Client* x : clienti) {
		fout << x->get_email() << endl;
		x->scriereFisierClasaClientUrmator(fout);
	}
	fout << "EndFisier";
	fout.close();
}
#endif

//Citire din fisiere -----------------------------------------------------------
#if 1 
list<Suc*> citireFisierDepozit() {
	ifstream fin;
	list<Suc*>sucuri;

	string nume;
	string fructProvenienta;
	bool zahar;
	string indulcitor;
	float cantitateZahar;
	int cantitate;
	string next;

	DaSuc* ds;
	NuSuc* ns;
	Suc* s;

	fin.open("depozit.txt"); //de citire

	for (int i = 0; nume != "EndList"; i++) {
		fin >> nume;
		if (nume == "EndList") {
			return sucuri;
		}
		fin >> next;
		fin >> next;
		fin >> fructProvenienta;
		fin >> next;
		fin >> next;
		fin >> zahar;
		if (zahar == 0)
		{
			fin >> next;
			fin >> indulcitor;
			fin >> next;
			fin >> cantitate;
			fin >> next;
			fin >> next;
			ns = new NuSuc(nume, fructProvenienta, cantitate, indulcitor);
			s = (Suc*)ns;
			sucuri.push_back(s);
		}
		else
		{
			fin >> next;
			fin >> next;
			fin >> next;
			fin >> cantitateZahar;
			fin >> next;
			fin >> cantitate;
			fin >> next;
			fin >> next;
			ds = new DaSuc(nume, fructProvenienta, cantitate, cantitateZahar);
			s = (Suc*)ds;
			sucuri.push_back(s);
		}
	}
	fin.close();

	return sucuri;
}
list<Suc*> citireFisierPreparator() {
	ifstream fin;
	list<Suc*>sucuri;

	string nume;
	string fructProvenienta;
	bool zahar;
	string indulcitor;
	float cantitateZahar;
	int cantitate;
	string next;

	DaSuc* ds;
	NuSuc* ns;
	Suc* s;

	fin.open("preparator.txt"); //de citire

	for (int i = 0; nume != "EndList"; i++) {
		fin >> nume;
		if (nume == "EndList") {
			return sucuri;
		}
		fin >> next;
		fin >> next;
		fin >> fructProvenienta;
		fin >> next;
		fin >> next;
		fin >> zahar;
		if (zahar == 0)
		{
			fin >> next;
			fin >> indulcitor;
			fin >> next;
			fin >> cantitate;
			ns = new NuSuc(nume, fructProvenienta, cantitate, indulcitor);
			s = (Suc*)ns;
			sucuri.push_back(s);
		}
		else
		{
			fin >> next;
			fin >> next;
			fin >> next;
			fin >> cantitateZahar;
			fin >> next;
			fin >> cantitate;
			ds = new DaSuc(nume, fructProvenienta, cantitate, cantitateZahar);
			s = (Suc*)ds;
			sucuri.push_back(s);
		}
	}
	fin.close();

	return sucuri;
}
list<Client*> citireFisierClienti() {
	ifstream fin;
	list<Client*>clienti;

	string nume;
	string email;
	string parola;
	string next;

	Client* c;

	fin.open("clienti.txt"); //de citire

	for (int i = 0; nume != "EndList"; i++) {
		fin >> nume;
		if (nume == "EndList") {
			return clienti;
		}
		fin >> email;
		fin >> parola;

		c = new Client(nume, email, parola);
		clienti.push_back(c);
	}
	fin.close();

	return clienti;
}
void citireFisierIstoricComenzi(list<Client*>clienti) {
	ifstream fin;
	string nume;

	list<string>istoricComenzi;

	fin.open("istoricComenzi.txt"); //de citire

	for (Client* x : clienti) {
		fin >> nume;
		if (x->get_email() == nume) {
			while (nume != "EndList")
			{
				fin >> nume;
				if (nume != "EndList") {
					istoricComenzi.push_back(nume);
				}
			}
			x->adaugareListaLaUtilizator(istoricComenzi);
			istoricComenzi.clear();
		}
	}
}
#endif 

//Autentificare ----------------------------------------------------------------
#if 1
//Functie inregistrare client nou
int client_inregistrat(list<Client*>clienti, Client* c)
{
	for (Client* x : clienti)
	{
		if (x->get_email() == c->get_email())
		{
			cout << "Contul exista deja! " << endl;
			return 1;
		}
	}
	return 0;
}
list<Client*> inregistrareClientNou(list<Client*>clienti) {
	string nume, email, parola, ultimeCaractere;
	int k = 0;
	Client* c;

	ofstream lo;
	lo.open("log.txt", ios::app);

	do
	{
		try
		{
			cout << "Nume: ";
			cin >> nume;

			do
			{
				cout << "Email: ";
				cin >> email;
				if (email.length() < 10) {
					cout << "Email-ul trebuie sa contina cel putin 10 caractere!" << endl;
					throw runtime_error("Email-ul trebuie sa contina cel putin 10 caractere!");
				}
			} while (email.length() < 10);

			cout << "Parola: ";
			cin >> parola;

			c = new Client(nume, email, parola);

			if (client_inregistrat(clienti, c) == 0) {
				clientPrezent = c;
				clienti.push_back(c);
				cout << endl << "Clientul a fost inregistrat!";
			};

			k = 1;
		}
		catch (const runtime_error& e)
		{
			lo << "Eroare: " << e.what() << endl;
		}
	} while (k != 1);
	lo.close();
	return clienti;
}

//Autentificare
Client* functie_autentificare(list <Client*>& clienti)
{
	string email, parola;
	cout << "Email: ";
	cin >> email;
	cout << "Parola: ";
	cin >> parola;

	char ch;
	ofstream log;
	log.open("log.txt", ios::app);

	try
	{
		for (Client* c : clienti)
			if (c->get_email() == email && c->get_parola() == parola)
			{
				cout << "Autentificarea a avut succes!" << endl;
				return c;
				break;
			}
		cout << "Parola sau email incorect!" << endl;
		throw runtime_error("Parola sau email incorect!");
	}
	catch (const runtime_error& e) {
		log << "Eroare: " << e.what() << endl;
	}
	log.close();
	return nullptr;
}
void schimba_parola(list <Client*>& clienti)
{
	int k = 0;
	string nume, email, parola;
	cout << endl << "Nume: ";
	cin >> nume;
	cout << "Email: ";
	cin >> email;

	char ch;
	ofstream log;
	log.open("log.txt", ios::app);

	try
	{
		for (Client* c : clienti)
			if (c->get_nume() == nume && c->get_email() == email)
			{
				cout << "Introduceti noua parola: " << endl;
				cin >> parola;
				c->modificare_parola(parola);
				cout << "Parola a fost resetata cu succes!" << endl;
				k = 1;
			}
		if (k == 0) {
			cout << "Numele sau email-ul introdus nu a fost gasit!" << endl;
			throw runtime_error("Numele sau email-ul introdus nu a fost gasit!");
		}
	}
	catch (const runtime_error& e) {
		log << "Eroare: " << e.what() << endl;
	}
	log.close();
}
void schimba_parola_cunoscuta(list <Client*>& clienti)
{
	string parola;
	cout << "Introduceti noua parola: " << endl;
	cin >> parola;
	clientPrezent->modificare_parola(parola);
	cout << "Parola a fost resetata cu succes!" << endl;
}

//Autentificare sub numele Alexandru (pentru testari mai rapide)
Client* functie_autentificare_test(list <Client*>& clienti)
{
	string email, parola;
	email = "alexandru.client@gmail.com";
	parola = "nouaparola";

	for (Client* c : clienti)
		if (c->get_email() == email && c->get_parola() == parola)
		{
			cout << "Autentificarea a avut succes!" << endl;
			return c;
			break;
		}
	cout << "Parola sau email incorect!" << endl;
	return nullptr;
}
#endif

//Comanda suc ------------------------------------------------------------------
#if 1
Suc* returnare_suc(list<Suc*>sucuriPreparator, string nume)
{
	for (Suc* s : sucuriPreparator)
	{
		if (s->get_nume() == nume)
		{
			clientPrezent->adaugare_suc_la_utilizator(s->get_nume());
			return s;
		}
	}
	return nullptr;
}
int Comanda_suc(list<Suc*>sucuriPreparator, list<Suc*>sucuriDepozit) {
	int i = 0;
	int opt;
	string nume;
	int numar;

	Suc* s;
	cout << "Lista sucuri: " << endl;
	for (Suc* x : sucuriPreparator)
	{
		i++;
		cout << i << ". " << x->get_nume() << " : " << x->get_cantitate() << endl;
	}
	cout << "0. Back" << endl;
	cout << "Ce suc doriti sa comandati?" << endl;
	//prima metoda
#if 0
	cout << "Alegeti optiunea : ";
	cin >> opt;

	switch (opt)
	{
	case 1:
		nume = "Aspartam";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 2:
		nume = "Sucraloza";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 3:
		nume = "Zaharina";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 4:
		nume = "Stevia";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 5:
		nume = "Eritritol";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 6:
		nume = "Orange";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 7:
		nume = "Cola";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 8:
		nume = "Fanta";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 9:
		nume = "Pepsi";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 10:
		nume = "Aloe";
		s = returnare_suc(sucuriPreparator, nume);

		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		break;
	case 0:
		break;
	default:
		cout << "Optiunea nu exista!" << endl;
		break;
	}
#endif

	//a doua metoda
#if 1
	cout << "Scrieti denumirea: ";
	cin >> nume;
	if (nume == "0") {
		return 0;
	}
	cout << "Introduceti numarul de sucuri: ";
	cin >> numar;
	for (int i = 0; i < numar; i++)
	{
		s = returnare_suc(sucuriPreparator, nume);
		if (s->get_cantitate() == 0) {
			cout << "Sucul se prepara 10 secunde!" << endl;
			for (int i = 0; i < 10; i++) {
				this_thread::sleep_for(chrono::seconds(1));//asteptam 10 secunde
				cout << " - ";
			}
			cout << endl << "Sucul a fost preparat folosind frucutul - " << s->get_provenienta() << "!" << endl;
			s->cantitateCompletare(sucuriPreparator, sucuriDepozit, nume);
		}
		cout << "Sucul " << s->get_nume() << " a fost preparat!" << endl;
		cout << "Cantitatea ramasa: " << s->get_cantitateMinusUnu() << endl;
		Sleep(500);
	}

#endif
	return 0;
}
#endif

int main() {
	list<Suc*>sucuriDepozit;
	list<Suc*>sucuriPreparator;
	list<Client*>clienti;
	list<string>istoricComenzi;

	//verificare daca exista log.txt
	ifstream lo;
	lo.open("log.txt");
	if (lo.good()) {
		cout << "log.txt exista" << endl;
	}
	else {
		lo.close();
		ofstream lo;
		lo.open("log.txt");
		cout << "log.txt a fost creat" << endl;
	}
	lo.close();

	verificareExistentaFisiereNecesare();

	sucuriDepozit = citireFisierDepozit();
	sucuriPreparator = citireFisierPreparator();
	clienti = citireFisierClienti();
	citireFisierIstoricComenzi(clienti);

	int k = 0;
	int opt, opt1;
	char ch;
	string autentificat = "Client necunoscut";

	ofstream log;
	log.open("log.txt", ios::app);

	do
	{
		try
		{
			system("cls");
			cout << "Nume client: " << autentificat << endl;
			cout << "1) Inregistrare client nou" << endl;
			cout << "2) Autentificare client existent" << endl;
			cout << "3) Afisare sucuri disponibile" << endl;
			cout << "4) Afisare sucuri existente in depozit" << endl;
			cout << "5) Comanda suc" << endl;
			cout << "6) Afisare istoric comenzi" << endl;
			cout << "0) Iesire" << endl << endl;

			cout << "Alegeti optiunea: ";
			cin >> opt;

			switch (opt)
			{
			case 1:
				clienti = inregistrareClientNou(clienti);
				if (clientPrezent != nullptr) {
					autentificat = clientPrezent->get_nume();
				}
				else {
					autentificat = "Client necunoscut!";
				}
				ch = _getch();
				break;
			case 2:
				if (clientPrezent == nullptr) {
					cout << "\nOptiuni: " << endl;
					cout << "1. Autentificare" << endl;
					cout << "2. Resetare parola" << endl;
					cout << "3. Back" << endl;
					cout << "Alegeti optiunea: ";
					cin >> opt1;
					switch (opt1)
					{
					case 1:
						clientPrezent = functie_autentificare(clienti);
						if (clientPrezent != nullptr) {
							autentificat = clientPrezent->get_nume();
						}
						else {
							autentificat = "Client necunoscut!";
						}
						ch = _getch();
						break;
					case 2:
						schimba_parola(clienti);
						ch = _getch();
						break;
					case 3:
						break;
					default:
						cout << "Optiune introdusa nu este valida!" << endl;
						throw runtime_error("Optiunea introdusa nu este valida!");
						ch = _getch();
						break;
					}
				}
				else
				{
					cout << "\nOptiuni: " << endl;
					cout << "1. Autentificare" << endl;
					cout << "2. Modificare parola" << endl;
					cout << "3. Delogare" << endl;
					cout << "4. Back" << endl;
					cout << "Alegeti optiunea: ";
					cin >> opt1;
					switch (opt1)
					{
					case 1:
						clientPrezent = functie_autentificare(clienti);
						if (clientPrezent != nullptr) {
							autentificat = clientPrezent->get_nume();
						}
						else {
							autentificat = "Client necunoscut!";
						}
						ch = _getch();
						break;
					case 2:
						if (clientPrezent != nullptr) {
							schimba_parola_cunoscuta(clienti);
						}
						else {
							cout << "Client necunoscut!" << endl;
						}
						ch = _getch();
						break;
					case 3:
						clientPrezent = nullptr;
						autentificat = "Client necunoscut!";
						break;
					case 4:
						break;
					default:
						cout << "Optiune introdusa nu este valida!" << endl;
						throw runtime_error("Optiunea introdusa nu este valida!");
						ch = _getch();
						break;
					}
				}
				break;
			case 3:
				for (Suc* x : sucuriPreparator)
				{
					x->afisare_suc();
					cout << endl;
				}
				ch = _getch();
				break;
			case 4:
				for (Suc* x : sucuriDepozit)
				{
					x->afisare_suc();
					cout << endl;
				}
				ch = _getch();
				break;
			case 5:
				if (clientPrezent != nullptr) {
					Comanda_suc(sucuriPreparator, sucuriDepozit);
					scriereFisierDepozitUrmator(sucuriDepozit);
					scriereFisierPreparatorUrmator(sucuriPreparator);
				}
				else {
					cout << "Client necunoscut!";
				}
				ch = _getch();
				break;
			case 6:
				if (clientPrezent != nullptr) {
					cout << clientPrezent->get_nume() << endl;
					cout << clientPrezent->get_email() << endl;
					clientPrezent->afisareListaSucuri();
				}
				else {
					cout << "Client necunoscut!";
				}
				ch = _getch();
				break;
			
			case 0:
				scriereFisierClientiUrmator(clienti);
				scriereFisierIstoricComenziUrmator(clienti);
				log.close();
				exit(0);
			default:
					cout << "Optiunea intrudusa nu este valida!" << endl;
				
				break;
			}

		}

		catch (const runtime_error& e) {
			log << "Eroare: " << e.what() << endl;
			ch = _getch();
		}

	} while (1);

	log.close();
	return 0;
}