#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <typeinfo>
#include <exception>

using namespace std;

//liste in clase fiindca fac in general inserari si stergeri, rar parcurgeri si mai niciodata random access
//vectori in main fiindca vreau des random access


class ExceptieMare: public exception {
public:
    virtual const char* what() const throw() {
        return "Ati introdus un numar prea mare!";
    }
}exceptieMare;


class ExceptieMica: public exception {
public:
    virtual const char* what() const throw() {
        return "Ati introdus un numar prea mic!";
    }
}exceptieMica;


class ExceptieComanda: public exception {
public:
    virtual const char* what() const throw() {
        return "Comanda invalida!";
    }
}exceptieComanda;


class ExceptieMarime: public exception {
public:
    virtual const char* what() const throw() {
        return "Format marime invalid! Introduceti o valoare dintre urmatoarele: XS, S, M, L, XL";
    }
}exceptieMarime;

class ExceptieIndice: public exception {
public:
    virtual const char* what() const throw() {
        return "Indice invalid!";
    }
}exceptieIndice;

class ExceptieCantitate: public exception {
public:
    virtual const char* what() const throw() {
        return "Cantitate peste limita stocului disponibil!";
    }
}exceptieCantitate;


//verificari pt inputuri de date din obiecte
template <class X>
bool verificaMicMare(X parametru, X valmic, X valmare)
{
    try
    {
        if(parametru < valmic)
            throw exceptieMica;
        if(parametru > valmare)
            throw exceptieMare;
    }
    catch(ExceptieMica& e)
    {
        cout << endl << e.what() << endl;
        cout << "Introduceti o expresie mai mare sau egala cu " << valmic << "\n\n";
        return false;
    }
    catch(ExceptieMare& e)
    {
        cout << endl << e.what() << endl;
        cout << "Introduceti o expresie mai mica sau egala cu " << valmare << "\n\n";
        return false;
    }
    return true; //returnam daca valorile au trecut sau nu verificarea
}

//verificari pt inputuri de comenzi
bool verificaComanda(int comanda, int limitaInf, int limitaSup)
{
    try
    {
        if(comanda < limitaInf || comanda > limitaSup)
            throw exceptieComanda;
    }
    catch(ExceptieComanda& e)
    {
        cout << endl << e.what() << endl;
        cout << "Comenzile valide sunt intre " << limitaInf << " si " << limitaSup << "\n\n";
        return false;
    }
    return true; //returnam daca valorile au trecut sau nu verificarea
}

//verificari pt inputuri de marimi
bool verificaMarime(string marime)
{
    try
    {
        if(marime != "XS" && marime != "S" && marime != "M" && marime != "L" && marime != "XL")
            throw exceptieMarime;
    }
    catch(ExceptieMarime& e)
    {
        cout << endl << e.what() << "\n\n";
        return false;
    }
    return true;
}

//verificari pt indici
bool verificaIndice(int indice, int limitaInf, int limitaSup)
{
    try
    {
        if(indice < limitaInf || indice > limitaSup)
            throw exceptieIndice;
    }
    catch(ExceptieIndice& e)
    {
        cout << endl << e.what() << endl;
        cout << "Un indice valid se afla intre " << limitaInf << " si " << limitaSup << endl;
        return false;
    }
    return true;
}

//verificari pentru cantitati din produse ce au un stoc limitat
bool verificaCantitate(int cantitate, int stoc)
{
    try
    {
        if(cantitate > stoc)
            throw exceptieCantitate;
        if(cantitate <= 0)
            throw 1;
    }
    catch(ExceptieCantitate& e)
    {
        cout << endl << e.what() << endl;
        return false;
    }
    catch(int a)
    {
        cout << "\nCantitatea introdusa trebuie sa fie mai mare decat 0!\n";
        return false;
    }
    return true;
}



class Produs {

protected:

    string material;
    float pret;
    int stoc;

public:

    //constructori
    Produs(string material = "nimic", float pret = 0.0, int stoc = 0); //un singur constructor si pt fara parametrii si cu parametrii
    Produs(const Produs& p); //copy constructor

    //operatori
    Produs& operator=(const Produs& p);
    friend istream& operator>>(istream& in, Produs& p);
    friend ostream& operator<<(ostream& out, const Produs& p);

    //metode
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;
    virtual void modificam();
    void esteCumparat(int cant) {this -> stoc -= cant;}

    //setteri si getteri
    void setMaterial(string material) {this -> material = material;}
    void setPret(float pret) {this -> pret = pret;}
    void setStoc(float stoc) {this -> stoc = stoc;}

    float getPret() {return this -> pret;}
    int getStoc() {return this -> stoc;}

    //destructor
    virtual ~Produs() {};

};

//clasa PRODUS
//constructori
Produs::Produs(string material, float pret, int stoc) {
    this -> material = material;
    this -> pret = pret;
    this -> stoc = stoc;
}
Produs::Produs(const Produs& p)
{
    this -> material = p.material;
    this -> pret = p.pret;
    this -> stoc = p.stoc;
}

//operatori
Produs& Produs::operator=(const Produs& p)
{
    if(this != &p)
    {
        this -> material = p.material;
        this -> pret = p.pret;
        this -> stoc = p.stoc;
    }
    return *this;
}
istream& operator>>(istream& in, Produs& p)
{
    return p.citire(in);
}
ostream& operator <<(ostream& out, const Produs& p)
{
    return p.afisare(out);
}
//metode
istream& Produs::citire(istream& in)
{
    bool verificare = false;
    cout << "Material: ";
    in >> this -> material;
    while(!verificare)
    {
        cout << "Pret: ";
        in >> this -> pret;
        verificare = verificaMicMare(this -> pret, (float)0.0, (float)1000.0);
    }
    verificare = false;

    while(!verificare)
    {
        cout << "Cate avem in stoc? ";
        in >> this -> stoc;
        verificare = verificaMicMare(this -> stoc, 0, 1000);
    }

    return in;
}
ostream& Produs::afisare(ostream& out) const
{
    out << "Material: " << this -> material << '\n';
    out << "Pret: " << this -> pret << '\n';
    if(this -> stoc == 0)
        out << "Nu avem produse in stoc!\n";
    else out << "In stoc: " << this -> stoc << '\n';

    return out;
}
void Produs::modificam() {}




class Bobina: virtual public Produs {

protected:

    string culoareB;
    char grosime; //char intre 1 si 7
    float crosetaRecomandata;

public:

    //constructori
    Bobina(); //fara parametrii
    Bobina(string material, string culoareB, char grosime, float crosetaRecomandata, float pret, int stoc);//toti parametrii
    Bobina(const Bobina& Obj); //copy constructor

    //operatori
    Bobina &operator =(const Bobina& Obj);
    //folosim operatorii de citire si afisare mosteniti din produs, dar suprascriem functiile citire si afisare

    //metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    void modificam();

    //setteri si getteri
    void setCuloareB(string culoare) {this -> culoareB = culoare;}
    void setGrosime(char grosime) {this -> grosime = grosime;}
    void setCrosetaRecomandata(float crosetaRecomandata) {this -> crosetaRecomandata = crosetaRecomandata;}

    //destructor
    virtual ~Bobina() {};
};

//clasa BOBINA
//constructori
Bobina::Bobina(): Produs("bumbac"), culoareB("negru"), grosime('0'), crosetaRecomandata(0.0) {};
Bobina::Bobina(string material, string culoareB, char grosime, float crosetaRecomandata, float pret, int stoc): Produs(material, pret, stoc) {
    this -> culoareB = culoareB;
    this -> grosime = grosime;
    this -> crosetaRecomandata = crosetaRecomandata;
}
Bobina::Bobina(const Bobina& Obj): Produs(Obj) {
    this -> culoareB = Obj.culoareB;
    this -> grosime = Obj.grosime;
    this -> crosetaRecomandata = Obj.crosetaRecomandata;
}
//operatori
Bobina& Bobina::operator =(const Bobina& Obj) {
    if(this != &Obj) {
        Produs::operator=(Obj);
        this -> culoareB = Obj.culoareB;
        this -> grosime = Obj.grosime;
        this -> crosetaRecomandata = Obj.crosetaRecomandata;
    }
    return *this;
}
//metode
istream& Bobina::citire(istream& in)
{
    bool verificare = false;
    cout << "Culoare: ";
    in >> this -> culoareB;
    while(!verificare)
    {
        cout << "Grosime [1 - 7]: ";
        in >> this -> grosime;
        verificare = verificaMicMare(this -> grosime, '1', '7');
    }
    verificare = false;
    while(!verificare)
    {
        cout << "Croseta Recomandata: ";
        in >> this -> crosetaRecomandata;
        verificare = verificaMicMare(this -> crosetaRecomandata, (float)1.0, (float)35.0);
    }
    Produs::citire(in);

    return in;
}
ostream& Bobina::afisare(ostream& out) const
{
    out << "Culoare: " << this -> culoareB << '\n';
    out << "Grosime: " << this -> grosime << '\n';
    out << "Croseta Recomandata: " << this -> crosetaRecomandata << '\n';
    Produs::afisare(out);

    return out;
}
void Bobina::modificam()
{
    //alegem ce vrem sa modificam la ea
    int modificare;
    bool verif = false;
    while(!verif)
    {
        cout << "\nModificati: \n 1 - Materialul \n 2 - Culoarea \n 3 - Grosimea \n 4 - Croseta Recomandata";
        cout << "\n 5 - Pretul \n";
        cin >> modificare;
        verif = verificaComanda(modificare, 1, 5);
    }
    switch(modificare)
    {
    //modificam materialul
    case 1:
        {
            string materialNou;
            cout << "\n Dati noul material: ";
            cin.get();
            getline(cin, materialNou);
            this -> setMaterial(materialNou);
            break;
        }
    //modificam culoarea
    case 2:
        {
            string culoareNoua;
            cout << "\n Dati noua culoare: ";
            cin >> culoareNoua;
            this -> setCuloareB(culoareNoua);
            break;
        }
    //modificam grosimea
    case 3:
        {
            char grosimeNoua;
            bool verificare = false;
            while(!verificare)
            {
                cout << "\n Dati noua grosime [0-7]: ";
                cin >> grosimeNoua;
                verificare = verificaMicMare(grosimeNoua, '1', '7');
            }
            this -> setGrosime(grosimeNoua);
            break;
        }
    //modificam marimea crosetei recomandate
    case 4:
        {
            float crosetaNoua;
            bool verificare = false;
            while(!verificare)
            {
                cout << "\n Dati marimea noii crosete: ";
                cin >> crosetaNoua;
                verificare = verificaMicMare(crosetaNoua, (float) 1.0, (float) 35.0);
            }
            this -> setCrosetaRecomandata(crosetaNoua);
            break;
        }
    //modficam pretul
    case 5:
        {
            float pretNou;
            bool verificare = false;
            while(!verificare)
            {
                cout << "\n Dati noul pret: ";
                cin >> pretNou;
                verificare = verificaMicMare(pretNou, (float)0.0, (float)1000.0);
            }
            this -> setPret(pretNou);
            break;
        }
    default:
        cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
    }
    //afisam bobina modificata
    system("cls");
    cout << " Modificare realizata cu succes! Bobina actualizata: \n";
    cout << (*this);
}




class Nasture: virtual public Produs {

protected:

    string forma;
    string culoareN;

public:

    //constructori
    Nasture(string forma = "rotund", string culoareN = "negru", string material = "plastic", float pret = 0.0, int stoc = 0);
    Nasture(const Nasture& n);

    //operatori
    Nasture& operator=(const Nasture& n);
    //folosim operatorii de citire si afisare mosteniti din produs, dar suprascriem functiile citire si afisare

    //metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    void modificam();

    //setteri si getteri
    void setForma(string forma) {this -> forma = forma;}
    void setCuloareN(string culoare) {this -> culoareN = culoare;}

    //destructor
    virtual ~Nasture() {};

};

//clasa NASTURE
//constructori
Nasture::Nasture(string forma, string culoareN, string material, float pret, int stoc): Produs(material, pret, stoc) {
    this -> forma = forma;
    this -> culoareN = culoareN;
}
Nasture::Nasture(const Nasture& n): Produs(n)
{
    this -> forma = n.forma;
    this -> culoareN = n.culoareN;
}
//operatori
Nasture& Nasture::operator=(const Nasture& n)
{
    if(this != &n)
    {
        Produs::operator=(n);
        this -> forma = n.forma;
        this -> culoareN = n.culoareN;
    }
    return *this;
}
//metode
istream& Nasture::citire(istream& in)
{
    cout << "Forma: ";
    in >> this -> forma;
    cout << "Culoarea: ";
    in >> this -> culoareN;
    Produs::citire(in);

    return in;
}
ostream& Nasture::afisare(ostream& out) const
{
    out << "Forma: " << this -> forma << '\n';
    out << "Culoarea: " << this -> culoareN << '\n';
    Produs::afisare(out);

    return out;
}
void Nasture::modificam()
{
    int modificare;
    bool verif = false;
    //alegem ce vrem sa modificam
    while(!verif)
    {
        cout << "\nModificati: \n 1 - Forma \n 2 - Culoarea \n 3 - Materialul \n 4 - Pretul \n";
        cin >> modificare;
        verif = verificaComanda(modificare, 1, 4);
    }
    switch(modificare)
    {
    //modificam forma
    case 1:
        {
            string formaNoua;
            cout << "\n Dati noua forma: ";
            cin >> formaNoua;
            this -> setForma(formaNoua);
            break;
        }
    //modificam culoarea
    case 2:
        {
            string culoareNoua;
            cout << "\n Dati noua culoare: ";
            cin >> culoareNoua;
            this -> setCuloareN(culoareNoua);
            break;
        }
    //modificam materialul
    case 3:
        {
            char materialNou[20];
            cout << "\n Dati noul material: ";
            cin >> materialNou;
            this -> setMaterial(materialNou);
            break;
        }

    //modificam pretul
    case 4:
        {
            float pretNou;
            bool verificare = false;
            while(!verificare)
            {
                cout << "\n Dati noul pret: ";
                cin >> pretNou;
                verificare = verificaMicMare(pretNou, (float)0.0, (float)1000.0);
            }

            this -> setPret(pretNou);
            break;
        }
    default:
        cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
    }
    //afisam nasturii modificati
    system("cls");
    cout << " Modificare realizata cu succes! Nasturi actualizati: \n";
    cout << (*this);
}





class Amigurumi: public Bobina, public Nasture
{
private:
    string nume;
    string marime; //XS-XL

public:
    //constructori
    Amigurumi(string material = "nimic", string culoareB = "negru", char grosime = '0', float crosetaRecomandata = 0.0, float pret = 0.0,
              int stoc = 0, string forma = "patrat", string culoareN = "negru", string nume = "anonim", string marime = "nimic");
    Amigurumi(const Amigurumi& obj);

    //operatori
    Amigurumi& operator=(const Amigurumi& obj);
    //folosim operatorii de citire si afisare mosteniti din produs, dar suprascriem functiile citire si afisare

    //metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    void modificam();
    int calcPuncte(int cantitate);

    //setteri si getteri
    void setNume(string nume) {this -> nume = nume;}
    void setMarime(string marime) {this -> marime = marime;}

    //destructor
    virtual ~Amigurumi() {};
};
//clasa AMIGURUMI
//constructori
Amigurumi::Amigurumi(string material, string culoareB, char grosime, float crosetaRecomandata, float pret, int stoc, string forma,
                     string culoareN, string nume, string marime): Produs(material, pret, stoc), Bobina(material, culoareB, grosime,
                     crosetaRecomandata, pret, stoc), Nasture(forma, culoareN, material, pret, stoc)
{
    this -> nume = nume;
    this -> marime = marime;
}
Amigurumi::Amigurumi(const Amigurumi& obj): Produs(obj), Bobina(obj), Nasture(obj)
{
    this -> nume = obj.nume;
    this -> marime = obj.marime;
}
//operatori
Amigurumi& Amigurumi::operator=(const Amigurumi& obj)
{
    if(this != &obj)
    {
        Bobina::operator=(obj);
        Nasture::operator=(obj);
        this -> nume = obj.nume;
        this -> marime = obj.marime;
    }
    return *this;
}
//metode
istream& Amigurumi::citire(istream& in)
{
    //chemam citire pt produs si pe cele din bobina si nasture le copiem, altfel cream amiguitati
    //chestii amigurumi
    cout << "Nume Amigurumi: ";
    in >> this -> nume;
    bool verificare = false;
    while(!verificare)
    {
        cout << "Marime [XS - XL]: ";
        in >> this -> marime;
        verificare = verificaMarime(this -> marime);
    }


    //chestii bobina
    cout << "Culoare Bobine: ";
    in >> this -> culoareB;
    verificare = false;
    while(!verificare)
    {
        cout << "Grosime [1 - 7]: ";
        in >> this -> grosime;
        verificare = verificaMicMare(this -> grosime, '1', '7');
    }
    verificare = false;
    while(!verificare)
    {
        cout << "Croseta Recomandata: ";
        in >> this -> crosetaRecomandata;
        verificare = verificaMicMare(this -> crosetaRecomandata, (float)1.0, (float)35.0);
    }

    //chestii nasture
    cout << "Forma Nasturi: ";
    in >> this -> forma;
    cout << "Culoare Nasturi: ";
    in >> this -> culoareN;

    //chestii produs
    Produs::citire(in);

    return in;
}
ostream& Amigurumi::afisare(ostream& out) const
{
    //date amigurumi
    out << "Nume Amigurumi: " << this -> nume << '\n';
    out << "Marime: " << this -> marime << '\n';

    //date bobina
    out << "Culoare Bobina: " << this -> culoareB << '\n';
    out << "Grosime: " << this -> grosime << '\n';
    out << "Croseta Recomandata: " << this -> crosetaRecomandata << '\n';

    //date nasture
    out << "Forma Nasturi: " << this -> forma << '\n';
    out << "Culoare Nasturi: " << this -> culoareN << '\n';

    //date produs
    Produs::afisare(out);

    return out;
}
void Amigurumi::modificam()
{
    int modificare;
    //alegem ce vrem sa modificam
    bool verif = false;
    while(!verif)
    {
        cout << "\nModificati: \n 1 - Numele \n 2 - Marimea \n 3 - Culoarea Bobinei \n 4 - Grosimea \n";
        cout << " 5 - Croseta Recomandata \n 6 - Culoarea Nasturilor \n 7 - Forma Nasturilor \n";
        cout << " 8 - Materialul \n 9 - Pretul \n";
        cin >> modificare;
        verif = verificaComanda(modificare, 1, 9);
    }
    switch(modificare)
    {
    //modificam numele
    case 1:
        {
            string numeNou;
            cout << "\n Dati noul nume: ";
            cin.ignore();
            getline(cin, numeNou);
            this -> setNume(numeNou);
            break;
        }
    //modificam marimea
    case 2:
        {
            string marimeNoua;
            verif = false;
            while(!verif)
            {
                cout << "\n Dati noua marime: ";
                cin >> marimeNoua;
                verif = verificaMarime(marimeNoua);
            }
            this -> setMarime(marimeNoua);
            break;
        }
    //modificam culoarea bobinei
    case 3:
        {
            string nouaCuloareB;
            cout << "\n Dati noua culoare a bobinei: ";
            cin >> nouaCuloareB;
            this -> setCuloareB(nouaCuloareB);
            break;
        }
    //modificam grosimea
    case 4:
        {
            char grosimeNoua;
            verif = false;
            while(!verif)
            {
                cout << "\n Dati noua grosime [1-7]: ";
                cin >> grosimeNoua;
                verif = verificaMicMare(grosimeNoua, '1', '7');
            }
            this -> setGrosime(grosimeNoua);
            break;
        }
    //modificam croseta recomandata
    case 5:
        {
            float crosetaRecomandataNoua;
            verif = false;
            while(!verif)
            {
                cout << "\n Dati marimea noii crosete recomandate: ";
                cin >> crosetaRecomandataNoua;
                verif = verificaMicMare(crosetaRecomandataNoua, (float)1.0, (float)35.0);
            }

            this -> setCrosetaRecomandata(crosetaRecomandataNoua);
            break;
        }
    //modificam culoarea nasturilor
    case 6:
        {
            string nouaCuloareN;
            cout << "\n Dati noua culoare a nasturilor: ";
            cin >> nouaCuloareN;
            this -> setCuloareN(nouaCuloareN);
            break;
        }
    //modificam forma nasturilor
    case 7:
        {
            string formaNoua;
            cout << "\n Dati noua forma a nasturilor: ";
            cin >> formaNoua;
            this -> setForma(formaNoua);
            break;
        }
    //modificam materialul
    case 8:
        {
            string materialNou;
            cout << "\n Dati noul material: ";
            cin >> materialNou;
            this -> setMaterial(materialNou);
            break;
        }
    //modificam pretul
    case 9:
        {
            float pretNou;
            verif = false;
            while(!verif)
            {
                cout << "\n Dati noul pret: ";
                cin >> pretNou;
                verif = verificaMicMare(pretNou, (float)0.0, (float)1000.0);
            }
            this -> setPret(pretNou);
            break;
        }
    default:
        cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
    }
    //afisam croseta modificata
    system("cls");
    cout << " Modificare realizata cu succes! Croseta actualizata: \n";
    cout << (*this);
}
int Amigurumi::calcPuncte(int cantitate)
{
    return floor((this -> pret) * 5 / 100 * cantitate);
}



class Croseta: public Produs {

private:

    float marime;
    bool manerErgonomic;

public:

    //constructori
    Croseta();// fara parametrii
    Croseta(float marime, bool manerErgonomic); //toti parametrii
    Croseta(const Croseta& Obj);

    //operatori
    Croseta &operator =(const Croseta &Obj);
    //folosim operatorii de citire si afisare mosteniti din produs, dar suprascriem functiile citire si afisare

    //metode
    istream& citire(istream& in);
    ostream& afisare(ostream& out) const;
    void modificam();

    //setteri si getteri
    void setMarime(float marime) {this -> marime = marime;}
    void setManerErgonomic(bool manerErgonomic) {this -> manerErgonomic = manerErgonomic;}

    bool getManerErgonomic() {return this -> manerErgonomic;}

     //destructor
    ~Croseta() {};
};

//clasa CROSETA
Croseta::Croseta(): Produs("nimic"), marime(0.0), manerErgonomic(false) {};
Croseta::Croseta(float marime, bool manerErgonomic): Produs(material, pret, stoc) {
    this -> marime = marime;
    this -> manerErgonomic = manerErgonomic;
}
Croseta::Croseta(const Croseta& Obj): Produs(Obj) {
    this -> marime = Obj.marime;
    this -> manerErgonomic = Obj.manerErgonomic;
}
//operatori
Croseta& Croseta::operator =(const Croseta &Obj) {
    if(this != &Obj) {
        Produs::operator=(Obj);
        this -> marime = Obj.marime;
        this -> manerErgonomic = Obj.manerErgonomic;
    }
    return *this;
}
//metode
istream& Croseta::citire(istream &in) {
    bool verif = false;
    while(!verif)
    {
        cout << "Marimea: ";
        in >> this -> marime;
        verif = verificaMicMare(this -> marime, (float)1.0, (float)1000.0);
    }
    Produs::citire(in);
    cout << "Maner ergonomic? [0/1]: ";
    in >> this -> manerErgonomic;

    return in;
}
ostream& Croseta::afisare(ostream &out) const
{
    out << "Marimea: " << this -> marime << '\n';
    Produs::afisare(out);
    if(!this -> manerErgonomic)
        out << "NU ";
    out << "ARE maner ergonomic" << '\n';

    return out;
}
void Croseta::modificam()
{
    int modificare;
    //alegem ce vrem sa modificam
    bool verif = false;
    while(!verif)
    {
        cout << "\nModificati: \n 1 - Marimea \n 2 - Materialul \n 3 - Manerul ergonomic \n 4 - Pretul \n";
        cin >> modificare;
        verif = verificaComanda(modificare, 1, 4);
    }
    switch(modificare)
    {
    //modificam marimea
    case 1:
        {
            float marimeNoua;
            verif = false;
            while(!verif)
            {
                cout << "\n Dati noua marime: ";
                cin >> marimeNoua;
                verif = verificaMicMare(marimeNoua, (float)1.0, (float)35.0);
            }

            this -> setMarime(marimeNoua);
            break;
        }
    //modificam materialul
    case 2:
        {
            string materialNou;
            cout << "\n Dati noul material: ";
            cin >> materialNou;
            this -> setMaterial(materialNou);
            break;
        }
    //modificam manerul ergonomic
    case 3:
        {
            if(this -> getManerErgonomic())
                this -> setManerErgonomic(false);
            else this -> setManerErgonomic(true);
            break;
        }
    //modificam pretul
    case 4:
        {
            float pretNou;
            verif = false;
            while(!verif)
            {
               cout << "\n Dati noul pret: ";
                cin >> pretNou;
                verif = verificaMicMare(pretNou, (float)0.0, (float)1000.0);
            }
            this -> setPret(pretNou);
            break;
        }
    default:
        cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
    }
    //afisam croseta modificata
    system("cls");
    cout << " Modificare realizata cu succes! Croseta actualizata: \n";
    cout << (*this);
}






class Proiect {

private:

    string nume;
    float timpNecesar;
    int nrBobine;
    int nrCrosete;
    set <float> croseteNecesare;

public:

    //constructori
    Proiect(); //fara parametrii
    Proiect(string nume, float timpNecesar, int nrBobine, set <float> croseteNecesare, int nrCrosete); //toti parametrii
    Proiect(const Proiect& Obj); //copy constructor

    //operatori
    Proiect &operator =(const Proiect &Obj);
    friend istream& operator >>(istream &in, Proiect& p);//nu e const fiindca vr sa o schimbam
    friend ostream& operator <<(ostream &out, const Proiect& p);

    //setteri si getteri
    void setNume(string nume) {this -> nume = nume;}
    void setTimpNecesar(float timpNecesar) {this -> timpNecesar = timpNecesar;}
    void setNrBobine(float nrBobine) {this -> nrBobine = nrBobine;}
    void setCroseteNecesare(set <float> croseteNecesare)
    {
        this -> nrCrosete = croseteNecesare.size();
        this -> croseteNecesare = croseteNecesare;
    }

    float getTimpNecesar() const {return this -> timpNecesar;}

    //destructor
    ~Proiect() {};
};

//clasa PROIECT
//constructori
Proiect::Proiect(): nume("Necunoscut"), timpNecesar(0.0), nrBobine(0), nrCrosete(0) {
    this -> croseteNecesare = {};
}
Proiect::Proiect(string nume, float timpNecesar, int nrBobine, set <float> croseteNecesare, int nrCrosete) {
    this -> nume = nume;
    this -> timpNecesar = timpNecesar;
    this -> nrBobine = nrBobine;
    this -> nrCrosete = nrCrosete;
    this -> croseteNecesare = croseteNecesare;
}
Proiect::Proiect(const Proiect& Obj) {
    this -> nume = Obj.nume;
    this -> timpNecesar = Obj.timpNecesar;
    this -> nrBobine = Obj.nrBobine;
    this -> nrCrosete = Obj.nrCrosete;
    this -> croseteNecesare = Obj.croseteNecesare;
}
//operatori
Proiect& Proiect::operator =(const Proiect &Obj) {
    if(this != &Obj) {
        this -> nume = Obj.nume;
        this -> timpNecesar = Obj.timpNecesar;
        this -> nrBobine = Obj.nrBobine;
        this -> nrCrosete = Obj.nrCrosete;
        this -> croseteNecesare = Obj.croseteNecesare;
    }
    return *this;
}
istream& operator >>(istream &in, Proiect &p) {
    cout << "Numele Proiectului: ";
    cin.ignore();
    getline(in, p.nume);

    bool verif = false;
    while(!verif)
    {
        cout << "Timpul necesar realizarii proiectului (in zile): ";
        in >> p.timpNecesar;
        verif = verificaMicMare(p.timpNecesar, (float) 0.5, (float)90.0);
    }

    verif = false;
    while(!verif)
    {
        cout << "Numarul de bobine necesare: ";
        in >> p.nrBobine;
        verif = verificaMicMare(p.nrBobine, 1, 10);
    }

    verif = false;
    while(!verif)
    {
        cout << "Numarul de crosete necesare: ";
        in >> p.nrCrosete;
        verif = verificaMicMare(p.nrCrosete, 1, 6);
    }


    if(p.nrCrosete)
        cout << "Marimile crosetelor necesare: \n";

    if(!p.croseteNecesare.empty())
        p.croseteNecesare.clear(); //eliberam vectorul
    for(int i = 0; i < p.nrCrosete; i++)
    {
        float marime;
        verif = false;
        while(!verif)
        {
            cout << " - croseta " << i + 1 << ": ";
            in >> marime;
            verif = verificaMicMare(marime, (float) 1.0, (float) 35.0);
        }
        p.croseteNecesare.insert(marime);
    }
    //reactualizam numarul de crosete in cazul in care am avut duplicate
    p.nrCrosete = p.croseteNecesare.size();
    return in;
}
ostream& operator <<(ostream &out, const Proiect &p)
{
    out << "Nume Proiect: " << p.nume << '\n';
    out << "Timp necesar realizarii proiectului: " << p.timpNecesar << " zile\n";
    out << "Numarul de bobine necesare: " << p.nrBobine << '\n';
    if(p.nrCrosete > 0)
    {
        out << p.nrCrosete << " crosete necesare: \n";
        int cnt = 0;
        for(auto i = p.croseteNecesare.begin(); i != p.croseteNecesare.end(); i++)
        {
            cnt++;
            out << " - croseta " << cnt << ": " << *i << '\n';
        }
    }
    else out << "Nu necesita nicio croseta\n";

    return out;
}




class Cos {
private:
    map <int, pair<Produs*, int>> produse;
    //cosul meu o sa aiba un produs, caruia ii va fi atribuita o cantitate
    //si fiecarei astfel de perechi ii va fi atribuit un indice (cheia din map =))

public:
    //constructor
    Cos() {this -> produse = {};}
    Cos(map <int, pair<Produs*, int>> produse) {this -> produse = produse;}
    Cos(const Cos& c) {this -> produse = c.produse;}

    //operatori
    Cos& operator=(const Cos& c);
    friend istream& operator >>(istream& in, Cos& c);
    friend ostream& operator <<(ostream& out, const Cos& c);

    //metode
    void adaugaProdus(Produs* p, int cantitate); //adauga un produs in cos
    float calcTotal(bool) const; //calculeaza pretul total al produselor din cos
    void cumparam(); //scade stocul tuturor produselor din cos
    int calcPuncte() const; //calculeaza cate puncte bonus primeste un client la finalizarea unei comenzi

    //setteri si getteri
    void setProduse(map <int, pair<Produs*, int>> produse) {this -> produse = produse;}
    map <int, pair<Produs*, int>> getProduse() {return this -> produse;} //nu e nevoie de const fiindca returneaza o copie

    //destructor
    ~Cos() {};

};
//clasa COS
//operatori
Cos& Cos::operator=(const Cos& c)
{
    if(this != &c)
    {
        this -> produse = c.produse;
    }
    return *this;
}
istream& operator>>(istream& in, Cos& c)
{
    //daca avem ceva in cos il golim
    c.setProduse({});
    bool vremSaAdaugam = true;
    while(vremSaAdaugam)
    {
        int indice, cantitate, optiune;
        bool verif = false;
        while(!verif)
        {
            cout << "Adaugati produse in cos: \n";
            cout << " 1 - o bobina \n 2 - o croseta \n 3 - un nasture \n 4 - un amigurumi \n";
            cin >> optiune;
            verif = verificaComanda(optiune, 1, 4);
        }

        verif = false;
        while(!verif)
        {
            cout << "\nCate produse de acest fel vreti sa adaugati in cos? ";
            cin >> cantitate;
            verif = verificaMicMare(cantitate, 1, 100);
        }
        switch(optiune)
        {
        case 1:
            {
                Produs* produsNou = new Bobina();
                in >> *produsNou;
                indice = c.produse.size();
                c.produse[indice] = make_pair(produsNou, cantitate);
                break;
            }
        case 2:
            {
                Produs* produsNou = new Croseta();
                in >> *produsNou;
                indice = c.produse.size();
                c.produse[indice] = make_pair(produsNou, cantitate);
                break;
            }
        case 3:
            {
                Produs* produsNou = new Nasture();
                in >> *produsNou;
                indice = c.produse.size();
                c.produse[indice] = make_pair(produsNou, cantitate);
                break;
            }
        case 4:
            {
                Produs* produsNou = new Amigurumi();
                in >> *produsNou;
                indice = c.produse.size();
                c.produse[indice] = make_pair(produsNou, cantitate);
                break;
            }
        default:
            cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
        }
        cout << "Doriti sa mai adaugati? [0/1]: ";
        cin >> vremSaAdaugam;
        cout << endl;
    }

}
ostream& operator<<(ostream& out, const Cos& c)
{
    out << "Produsele din cosul dumneavoastra: \n\n";
    for(auto i = c.produse.begin(); i != c.produse.end(); i++)
    {
        //afisam indexul
        out << " Produsul " << i -> first + 1 << '\n';

        //afisam tipul de produs corespunzator
        if(dynamic_cast<Bobina*>((i -> second).first))
            out << " Bobina:\n";
        if(dynamic_cast<Croseta*>((i -> second).first))
            out << " Croseta:\n";
        if(dynamic_cast<Nasture*>((i -> second).first))
            out << " Nasture:\n";
        if(dynamic_cast<Amigurumi*>((i -> second).first))
            out << " Amigurumi:\n";

        //afisam produsul
        out << *(i -> second).first;
        //afisam cantitatea
        out << " Cantitate: " << (i -> second).second << "\n\n";

    }
    //afisam totalul
    float total = c.calcTotal(true);
    out << "\nTOTAL: " << total << "\n\n";


    out << " Primiti " << c.calcPuncte() << " puncte bonus la finalizarea acestei comenzi! \n\n";

    return out;
}
//metode
void Cos::adaugaProdus(Produs* p, int cantitate)
{
    //verificam daca produsul este deja in cos
    int indice = -1;
    for(auto i = this -> produse.begin(); i != this -> produse.end() && indice < 0; i++)
    {
        if((i -> second).first == p)
            indice = i -> first;
    }
    if(indice < 0) //daca produsul nu e in cos il adaugam
    {
        int indice = this -> produse.size();
        this -> produse[indice] = make_pair(p, cantitate);
    }
    else {
        //altfel ii crestem cantitatea
        if(cantitate + (this -> produse[indice]).second > (*p).getStoc())
        //daca vr sa punem mai mult decat cate avem in stoc, punem doar cate avem in stoc =)
            cantitate = (*p).getStoc() - (this -> produse[indice]).second;
        (this -> produse[indice]).second += cantitate;
    }
}
float Cos::calcTotal(bool afisez) const
{
    float total = 0.0;
    for(auto i = (this -> produse).begin(); i != (this -> produse).end(); ++i)
        total += (*((i -> second).first)).getPret() * (i -> second).second; //adaugam pretul obiectului * cantitatea din cos
    if(afisez) //daca vrem sa afisam detalii despre total
    {
        if(total < 100) {
            cout << "\nTOTAL FARA TRANSPORT: " << total;
            cout << "\nTRANSPORT: 15\n Mai adaugati produse in valoare de " << 100 - total << " pentru a beneficia de transport gratuit!\n";
            total += 15;
        }
        else cout << "\n Felicitari! Transportul este gratuit!\n";
    }
    else {
        if(total < 100) total += 15;
    }
    return total;
}
void Cos::cumparam()
{
    //scadem stocul fiecarui obiect din cos cu atatea unitati cate cumparam
    for(auto i = (this -> produse).begin(); i != (this -> produse).end(); ++i)
        (*((i -> second).first)).esteCumparat((i -> second).second);
}
int Cos::calcPuncte() const
{
    //cautam amigurumi si le adunam punctele
    int suma = 0;
    for(auto i = this -> produse.begin(); i != this -> produse.end(); i++)
        if(typeid(*((i -> second).first)) == typeid(Amigurumi)) //daca avem un amigurumi
            suma += dynamic_cast<Amigurumi*>((i -> second).first) -> calcPuncte((i -> second).second);
    return suma;
}




class Client {

private:

    string nume;
    string email;
    string parola;
    bool trimiteAnunturi;
    float bani;
    float timpLiber; //in zile
    list <Proiect> proiecte;
    Cos cos;
    int puncteBonus; //se pot folosi pentru reduceri, daca cumperi amigurumi

public:

    //constructori
    Client(); //constructor fara parametrii
    // toti parametrii
    Client(string nume, string email, string parola, bool trimiteAnunturi, float bani, float timpLiber, list <Proiect> proiecte, Cos cos,
           int puncteBonus);
    Client(const Client& Obj); //copy constructor

    //operatori
    Client &operator =(const Client &Obj);
    friend istream& operator >>(istream& in, Client& C);//nu e const fiindca vr sa o schimbam
    friend ostream& operator <<(ostream &out, const Client& C);

    //metode
    void iaVacanta(float zile);
    void cumpara(int cant);
    void adaugaProiect(const Proiect& p);
    void primestePuncte(int puncte);

    //setteri si getteri
    void setNume(string nume) {this -> nume = nume;}
    void setEmail(string email) {this -> email = email;}
    void setParola(string parola) {this -> parola = parola;}
    void setTrimiteAnunturi(bool trimiteAnunturi) {this -> trimiteAnunturi = trimiteAnunturi;}
    void setBani(float bani) {this -> bani = bani;}
    void setTimpLiber(float timpLiber) {this -> timpLiber = timpLiber;}
    void setProiecte(list <Proiect> proiecte) {this -> proiecte = proiecte;}
    void setCos(Cos cos) {this -> cos = cos;}

    string getNume() {return this -> nume;}
    string getEmail() {return this -> email;}
    string getParola() {return this -> parola;}
    bool getTrimiteAnunturi() {return this -> trimiteAnunturi;}
    float getBani() {return this -> bani;}
    float getTimpLiber() {return this -> timpLiber;}
    Cos getCos() {return this -> cos;}
    int getPuncteBonus() {return this -> puncteBonus;}

    //destructor
    ~Client() {};
};

//clasa CLIENT
Client::Client():nume("Anonim"), email(""), parola(""), trimiteAnunturi(false), bani(0.0), timpLiber(0.0), puncteBonus(0) {
    this -> proiecte = {};
}
Client::Client(string nume, string email, string parola, bool trimiteAnunturi, float bani, float timpLiber, list <Proiect> proiecte, Cos cos,
               int puncteBonus)
{
    this -> nume = nume;
    this -> email = email;
    this -> parola = parola;
    this -> trimiteAnunturi = trimiteAnunturi;
    this -> bani = bani;
    this -> timpLiber = timpLiber;
    this -> proiecte = proiecte;
    this -> cos = cos;
    this -> puncteBonus = puncteBonus;
}
Client::Client(const Client& Obj) {
    this -> nume = Obj.nume;
    this -> email = Obj.email;
    this -> parola = Obj.parola;
    this -> trimiteAnunturi = Obj.trimiteAnunturi;
    this -> bani = Obj.bani;
    this -> timpLiber = Obj.timpLiber;
    this -> proiecte = Obj.proiecte;
    this -> cos = Obj.cos;
    this -> puncteBonus = Obj.puncteBonus;
}
//operatori
Client& Client::operator =(const Client &Obj) {
    if(this != &Obj) {
        this -> nume = Obj.nume;
        this -> email = Obj.email;
        this -> parola = Obj.parola;
        this -> trimiteAnunturi = Obj.trimiteAnunturi;
        this -> bani = Obj.bani;
        this -> timpLiber = Obj.timpLiber;
        this -> proiecte = Obj.proiecte;
        this -> cos = Obj.cos;
        this -> puncteBonus = Obj.puncteBonus;
    }
    return *this;
}
istream& operator >>(istream& in, Client& C) {
    cout << "Numele clientului: ";
    cin.ignore(); //il folosesti cand treci de la cin >> la getline/get
    getline(in, C.nume);
    cout << "Email: ";
    getline(in, C.email);
    bool parolaInvalida = true;
    while(parolaInvalida)
    {
        try
        {
            cout << "Parola: ";
            string aux;
            getline(in, aux);
            cout << "Confirmare parola: ";
            string aux2;
            getline(in, aux2);
            if(aux == aux2)
            {
                C.parola = aux;
                parolaInvalida = false;
            }
            else throw 1;
        }
        catch(int x)
        {
            cout << "\x1B[31mParola si confirmarea parolei nu conicid!\x1B[97m\n";
        }
    }

    bool verif = false;
    while(!verif)
    {
        cout << "Suma de bani de care dispune: ";
        in >> C.bani;
        verif = verificaMicMare(C.bani, (float)0.0, (float)100000000.0);
    }
    verif = false;
    while(!verif)
    {
        cout << "Timpul liber (in zile): ";
        in >> C.timpLiber;
        verif = verificaMicMare(C.timpLiber, (float)0.0, (float)1000.0);
    }

    cout << "Ati realizat proiecte? [0/1]: ";
    bool areProiecte;
    in >> areProiecte;

    if(!areProiecte && !C.proiecte.empty()) //daca nu are proiecte, dar vectorul proiecte nu e gol, il eliberam
        C.proiecte.clear();
    else if(areProiecte)
    {
        cout << "\nAdaugati proiecte \n\n";
        while(areProiecte)
        {
            Proiect aux;
            in >> aux;
            C.proiecte.push_back(aux);
            cout << "Mai adaugati proiecte? [0/1]: ";
            in >> areProiecte;
        }
    }
    cout << "Doriti sa primiti oferte si anunturi pe adresa de mail? [0/1]: ";
    in >> C.trimiteAnunturi;

    return in;
}
ostream& operator <<(ostream &out, const Client& C) {
    out << "Numele clientului: " << C.nume << '\n';
    out << "Emailul: " << C.email << '\n';
    //nu afisam parola
    if(C.trimiteAnunturi == false)
        out << "NU ";
    out << "Doreste sa primeasca anunturi \n";
    out << "Suma de bani de care dispune: " << C.bani << '\n';
    out << "Timpul liber: " << C.timpLiber << " zile\n";
    if(!C.proiecte.empty())
    {
        out << C.proiecte.size() << " proiecte realizate: \n";
        int cnt = 0;
        for(auto i = C.proiecte.begin(); i != C.proiecte.end(); i++)
        {
            cnt++;
            out << " - proiectul " << cnt << ": \n" << *i << '\n';
        }
    }
    else out << "Nu a realizat niciun proiect\n";
    if(C.puncteBonus) out << "Are " << C.puncteBonus << " puncte bonus acumulate\n";
    else out << "Nu are niciun punct bonus\n";

    return out;
}
//metode
void Client::iaVacanta(float zile)
{
    this -> timpLiber += zile;
    this -> bani -= 100 * zile; //fiindca am stabilit eu ca o zi de vacanta te costa 100 =)
}
void Client::cumpara(int cant)
{
    this -> bani -= cant;
}
void Client::adaugaProiect(const Proiect& p)
{
    this -> proiecte.push_back(p);
    //scadem timpul de care avem nevoie pt realizarea proiectului
    this -> timpLiber -= p.getTimpNecesar();
}
void Client::primestePuncte(int puncte)
{
    this -> puncteBonus += puncte;
}




template <class T>
void vizualizare_stoc(vector <T>& lista, int indice, Cos& cos)
{
    //indice tre sa fie mai mic decat 3
    string s[4] = {"bobine", "crosete", "nasturi", "amigurumi"};
    //daca nu avem produse in stoc
    if(lista.empty())
    {
        cout << "Din pacate, momentan nu avem " << s[indice] << " in stoc. \nVa rugam reveniti mai tarziu!";
        //iese din if si ofera ocazia utilizatorului sa iasa din program
    }
    //daca avem produse in stoc
    else {
        //afisam stocul cu tot cu indicele produselor in lista lor
        cout << "Stocul nostru de " << s[indice] << " : \n\n";
        for(int i = 0; i < lista.size(); i++)
            cout << "Tipul " << i + 1 << " de " << s[indice] << ":\n" << lista[i] << endl << endl;

        //intrebam utilizatorul daca vrea sa cumpere ceva
        bool cumparam;
        cout << "\nDoriti sa adaugati " << s[indice] << " in cos? [0/1]: ";
        cin >> cumparam;
        //daca vrea sa adauge in cos
        if(cumparam)
        {
            //face selectia produsului dupa indicele ei in lista
            int indiceProdus, cantitate;
            bool verif = false;
            while(!verif)
            {
                cout << "\nCe tip de " << s[indice] << " doriti sa cumparati? ";
                cin >> indiceProdus;
                verif = verificaIndice(indiceProdus, 1, lista.size());
                indiceProdus--;
            }
            verif = false;
            while(!verif)
            {
                cout << "\nCate produse de acest tip doriti sa adaugati in cos? ";
                cin >> cantitate;
                //verificam daca avem destule produse in stoc
                verif = verificaCantitate(cantitate, lista[indiceProdus].getStoc());
            }
            //le adaugam in cos
            Produs* p = &(lista[indiceProdus]); //p pointeaza spre un produs de tip T
            cos.adaugaProdus(p, cantitate);
        }
    }
}


template <class T>
void reactualizare_stoc(vector <T>& lista, int indice, bool& stop, int& profil)
{
    //indice tre sa fie mai mic decat 3
    string s[4] = {"bobine", "crosete", "nasturi", "amigurumi"};
    // putem sa adaugam, stergem sau modificam produse
    int adauga;
    bool verif = false;
    while(!verif)
    {
        cout << " Reactualizarea stocului de " << s[indice] << "! \n";
        cout << " Doriti sa: \n 1 - Adaugati noi produse \n 2 - Stergeti produse \n 3 - Modificati produse \n";
        cin >> adauga;
        verif = verificaComanda(adauga, 1, 3);
    }
    switch(adauga)
    {
    //daca alegem sa adaugam un produs
    case 1:
        {
            bool vremSaAdaugam = true; //ne tine in meniul de adaugare pana vrem sa iesim
            while(vremSaAdaugam)
            {
                system("cls");
                //introducem un produs auxiliar pe care il adaugam la lista doar in momentul in care confirmam faptul ca datele sunt corecte
                cout << " Adaugati noi " << s[indice] << "\n\n";
                T ProdusCurent;
                cin >> ProdusCurent;
                bool confirmare;
                cout << "\n Urmatoarele date sunt corecte?\n\n";
                cout << ProdusCurent;
                cout << "\n Da\/Nu? [1/0]: ";
                cin >> confirmare;
                //daca avem confirmarea
                if(confirmare)
                {
                    //adaugam produsul la lista
                    lista.push_back(ProdusCurent);
                    int iesire;
                    verif = false;
                    while(!verif)
                    {
                        cout << "\n Stoc actualizat! Doriti sa: \n 1 - Mai adaugati produse \n 2 - Va intoarceti la meniul principal";
                        cout << "\n 3 - Iesiti\n";
                        cin >> iesire;
                        verif = verificaComanda(iesire, 1, 3);
                    }
                    //daca vrem sa ramanem in meniul de adaugat nu schimbam nimic
                    //daca vrem sa iesim
                    if(iesire == 3)
                    {
                        system("cls");
                        cout << "Bye, Boss! <3\n";
                        profil = false;
                        stop = false;
                        vremSaAdaugam = false;
                    }
                    else {
                        //daca vr ne intoarcem inapoi iesim din while
                        if(iesire == 2)
                            vremSaAdaugam = false;
                    }
                }
            }
            break;
        }
    //daca alegem sa stergem un produs
    case 2:
        {
            bool vremSaStergem = true; //ne tine in meniul de stergere pana decidem sa iesim
            while(vremSaStergem)
            {
                system("cls");
                cout << "Stergeti " << s[indice] << "\n\n";
                //verificam daca avem produse in stoc
                if(lista.empty())
                {
                    cout << "Nu avem inca " << s[indice] << " in stoc! =(\n";
                    //iesim din if si afisam optiunile de iesire
                }
                else {
                    //afisam stocul curent cu indicii produselor din lista
                    cout << "Stocul curent: \n";
                    for(int i = 0; i < lista.size(); i++)
                        cout << "Tipul de " << s[indice] << ' ' << i + 1 << ": \n" << lista[i] << endl;
                    //selectam produsul cu ajutorul indicelui din lista
                    verif = false;
                    int indice, cantitate;
                    while(!verif)
                    {
                        cout << "Doriti sa stergeti " << s[indice] << " de tipul: ";
                        cin >> indice;
                        verif = verificaIndice(indice, 1, lista.size()); //verificam validitatea indicelui
                    }
                    indice--;
                    verif = false;
                    while(!verif)
                    {
                        cout << "Cate produse de acest fel doriti sa stergeti? ";
                        cin >> cantitate;
                        verif = verificaCantitate(cantitate, lista[indice].getStoc());
                    }
                    //daca vrem sa stergem mai putine decat sunt in stoc
                    if(cantitate < lista[indice].getStoc())
                        //modificam stocul (e ca si cum sunt cumparate)
                        lista[indice].esteCumparat(cantitate);
                    //daca vrei sa stergi cate produse sunt in stoc pur si simplu iti sterge obiectul
                    else lista.erase(lista.begin() + indice);
                    //afisam stocul actualizat
                    system("cls");
                    cout << "Stocul actual: \n\n";
                    for(int i = 0; i < lista.size(); i++)
                        cout << lista[i] << endl;
                }
                //afisam optiunile de iesire
                int iesire;
                verif = false;
                while(!verif)
                {
                    cout << "\n Doriti sa: \n 1 - Mai stergeti produse \n 2 - Va intoarceti la meniul principal";
                    cout << "\n 3 - Iesiti \n";
                    cin >> iesire;
                    verif = verificaComanda(iesire, 1, 3);
                }
                //daca vrem sa mai stergem nu facem nimic
                //daca vrem sa iesim de tot
                if(iesire == 3)
                {
                    system("cls");
                    cout << "Bye, Boss! <3\n";
                    profil = false;
                    stop = false;
                    vremSaStergem = false;
                }
                else {
                    //daca vr ne intoarcem inapoi iesim din while
                    if(iesire == 2)
                        vremSaStergem = false;
                }
            }
            break;
        }
    //daca vrem sa modificam o bobina
    case 3:
        {
            bool vremSaModificam = true; //ne tine in meniul de modificare pana vrem sa iesim
            while(vremSaModificam)
            {
                system("cls");
                cout << "Modificati " << s[indice] <<"! \n";
                //verificam daca avem produse in stoc
                if(lista.empty())
                {
                    cout << "Nu avem inca " << s[indice] << " in stoc";
                }
                //daca avem produse in stoc
                else {
                    //afisam stocul curent cu tot cu indicele produselor din lista
                    cout << "Stocul curent de " << s[indice] << ": \n";
                    for(int i = 0; i < lista.size(); i++)
                        cout << "Tipul " << i + 1 << " de " << s[indice] << ": \n" << lista[i] << endl;
                    //selectam produsul ce urmeaza sa fie modificat prin intermediul indicelui din lista
                    int indice;
                    verif = false;
                    while(!verif)
                    {
                        cout << "Doriti sa modificati " << s[indice] << " de tipul numarul: ";
                        cin >> indice;
                        verif = verificaIndice(indice, 1, lista.size()); //verificam validitatea indicelui
                    }
                    indice--;
                    system("cls");
                    //afisam produsul ce urmeaza sa fie modificat
                    cout << "Modificam urmatorul produs: \n\n";
                    cout << lista[indice];
                    lista[indice].modificam();
                }
                //afisam optiunile de iesire
                int iesire;
                verif = false;
                while(!verif)
                {
                    cout << "\n Mai departe doriti sa: \n 1 - Continuati sa modificati produse";
                    cout << "\n 2 - Reveniti la meniul principal \n 3 - Iesiti \n";
                    cin >> iesire;
                    verif = verificaComanda(iesire, 1, 3);
                }
                //daca vrem sa iesim din program
                if(iesire == 3)
                {
                    system("cls");
                    cout << "Bye, Boss! <3\n";
                    profil = false;
                    stop = false;
                    vremSaModificam = false;
                }
                else {
                    //daca vrem sa ne intoarcem la meniul principal
                    if(iesire == 2)
                        vremSaModificam = false;
                }
            }
            break;
        }
        default:
            cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
    }
}



//meniu Singletone
class Meniu {

    static Meniu* obiect;

    Meniu() = default;
    Meniu(const Meniu&) = delete;
    ~Meniu() {
        delete[] obiect;
    };

public:
    static Meniu* getInstance() {
        if(!obiect)
            obiect = new Meniu();
        return obiect;
    }

    void start() {

        //schimbam culoarea consolei, primul simbol e pentru fundal, al doilea pt font
        system("color 3f");
        //"stocul"
        vector <Client> listaClienti;
        vector <Bobina> listaBobine;
        vector <Nasture> listaNasturi;
        vector <Croseta> listaCrosete;
        vector <Amigurumi> listaAmigurumi;
        vector <Proiect> listaProiecte;
        bool stop = true; //controleaza cand iesim din program
        while(stop)
        {
            //stergem ce s-a afisat pana la momentul respectiv in consola
            system("cls");
            int identitate; //tine minte daca suntem client sau administrator
            bool verif = false;
            while(!verif)
            {
                cout << " Hello! Bine ati venit la Granny Mary \n Sunteti: \n 1 - Client \n 2 - Administrator \n";
                cin >> identitate;
                verif = verificaComanda(identitate, 1, 2);
            }
            switch(identitate)
            {
            case 1:
            {
                bool profil = true; //controleaza cand iesim din profilul ales
                while(profil)
                {
                    int comanda;
                    system("cls");
                    int cont;
                    verif = false;
                    while(!verif)
                    {
                        cout << " Hello, Mister Costumer! \n Va rugam realizati una dintre urmatoarele actiuni: \n 1 - Inregistrati-va";
                        cout << "\n 2 - Daca aveti deja un cont, autentificati-va \n 3 - Mergeti inapoi \n 4 - Iesiti \n";
                        cin >> cont;
                        verif = verificaComanda(cont, 1, 4);
                    }
                    //inregistrare client nou
                    if(cont == 1)
                    {
                        system("cls");
                        cout << " Deveniti parte din comunitatea noastra!\n\n";
                        //facem un client auxiliar pe care il punem in lista de clienti doar in momentul in care confirma ca datele sunt corecte
                        Client ClientCurent;
                        cin >> ClientCurent;
                        bool confirmare;
                        cout << "\n Urmatoarele date sunt corecte?\n\n";
                        //nu o sa-i afisez parola dar oricum trebuie sa fi trecut de confirmarea ei
                        cout << ClientCurent;
                        cout << "\n Da\/Nu? [1/0]: ";
                        cin >> confirmare;
                        //daca confirma il bagam in lista si ii oferim sansa sa iasa din program
                        //indiferent de confirmare, se intoarce inapoi la meniu anterior
                        if(confirmare)
                        {
                            listaClienti.push_back(ClientCurent);
                            bool iesire;
                            cout << "\n Cont creat cu succes! Doriti sa iesiti? [0/1]: ";
                            cin >> iesire;
                            if(iesire)
                            {
                                system("cls");
                                cout << "O zi frumoasa! Va mai asteptam!";
                                stop = false;
                                profil = false;
                            }
                        }
                    }
                    else {
                            //autentificare
                            if(cont == 2)
                            {
                                bool neAutentificam = true;
                                while(neAutentificam)
                                {
                                    system("cls");
                                    cout << "Autentificati-va!\n\n";
                                    //se introduce un email si o parola care sunt dupa cautate in lista de clienti inregistrati
                                    string email, parola;
                                    cout << "Email: ";
                                    cin.ignore();
                                    getline(cin, email);
                                    cout << "Parola: "; //nu stiu sa o ascund...
                                    getline(cin, parola);
                                    int indiceCurent = -1;//daca gasim clientul in lista ii pastram indicele pt a putea sa manipulam usor obiectul respectiv
                                    for(int i = 0; i < listaClienti.size(); i++)
                                        if(listaClienti[i].getEmail() == email && listaClienti[i].getParola() == parola)
                                            indiceCurent = i;
                                    //daca indicele curent e 0, avand in vedere ca lista de clienti e indexata de la 1, inseamna ca nu am gasit clientul in lista
                                    if(indiceCurent == -1)
                                    {
                                        //ii oferim sansa sa mai incerce, sa revina la meniul anterior sau sa iasa cu totul din program
                                        int iesire;
                                        verif = false;
                                        while(!verif)
                                        {
                                            cout << "\nAutentificare esuata! Email sau parola incorecta.";
                                            cout << "\nDoriti sa: \n1- Incercati din nou \n2 - Reveniti la meniul anterior \n3 - Iesiti\n";
                                            cin >> iesire;
                                            verif = verificaComanda(iesire, 1, 3);
                                        }
                                        if(iesire == 3)
                                        {
                                            system("cls");
                                            cout << "O zi frumoasa! Va mai asteptam!";
                                            stop = true;
                                            profil = true;
                                            neAutentificam = false;
                                        }
                                        else {
                                            if(iesire == 2)
                                                neAutentificam = false;
                                        }
                                    }
                                    //autentificare reusita
                                    else {
                                            bool autentificati = true; //controleaza cat suntem autentificati, astfel incat sa putem iesi doar din cont daca vrem
                                            while(autentificati)
                                            {
                                                system("cls");
                                                verif = false;
                                                while(!verif)
                                                {
                                                    cout << "Bine ati revenit, " << listaClienti[indiceCurent].getNume() << '\n';
                                                    cout << "Ce doriti sa faceti?\n 1 - Vizualizati-ne stocul \n 2 - Alegeti-va urmatorul proiect";
                                                    cout << "\n 3 - Contul meu \n 4 - Iesiti din cont \n 5 - Iesiti din aplicatie \n";
                                                    cin >> comanda;
                                                    verif = verificaComanda(comanda, 1, 5);
                                                }
                                                system("cls");
                                                switch(comanda)
                                                {
                                                //daca vrem sa vizualizam un stoc / sa cumparam ceva
                                                case 1:
                                                    {
                                                        bool vremSaCumparam = true;
                                                        //luam un pointer pe care il trimitem spre functia adaugaProdus daca vrem sa punem ceva in cos
                                                        Produs* p;
                                                        while(vremSaCumparam)
                                                        {
                                                            system("cls");
                                                            int fel_produs; //daca vrem sa vedem/cumparam bobine sau crosete sau etc
                                                            verif = false;
                                                            while(!verif)
                                                            {
                                                                cout << " Doriti sa vizualizati oferta noastra de: \n 1 - Bobine \n 2 - Crosete\n 3 - Nasturi \n 4 - Amigurumi \n";
                                                                //sa apara asta doar daca am ceva in cos
                                                                if(!(listaClienti[indiceCurent].getCos()).getProduse().empty())
                                                                {
                                                                    cout << " Sau: \n 5 - Doriti sa va vizualizati cosul?\n";
                                                                    cin >> fel_produs;
                                                                    verif = verificaComanda(fel_produs, 1, 5);
                                                                }
                                                                else {
                                                                    cin >> fel_produs;
                                                                    verif = verificaComanda(fel_produs, 1, 4);
                                                                }
                                                            }
                                                            system("cls");
                                                            Cos c = listaClienti[indiceCurent].getCos(); //un cos temporar
                                                            switch(fel_produs)
                                                            {
                                                            //daca vrem sa vedem/cumparam bobine
                                                            case 1:
                                                                {
                                                                    vizualizare_stoc(listaBobine, 0, c);
                                                                    break;
                                                                }
                                                            //daca vrem sa vedem/cumparam crosete
                                                            case 2:
                                                                {
                                                                    vizualizare_stoc(listaCrosete, 1, c);
                                                                    break;
                                                                }
                                                            //daca vrem sa vedem/cumparam nasturi
                                                            case 3:
                                                                {
                                                                    vizualizare_stoc(listaNasturi, 2, c);
                                                                    break;
                                                                }
                                                            //daca vrem sa vedem/cumparam amigurumi
                                                            case 4:
                                                                {
                                                                    vizualizare_stoc(listaAmigurumi, 3, c);
                                                                    break;
                                                                }
                                                            //daca dorim sa vizualizam cosul
                                                            case 5:
                                                                {
                                                                    cout << c;
                                                                    int comandam; //tine minte daca dam comanda sau nu
                                                                    verif = false;
                                                                    while(!verif)
                                                                    {
                                                                        cout << "Doriti sa: \n 1 - Modificati cosul \n 2 - Goliti cosul";
                                                                        cout << " \n 3 - Finalizati comanda \n 4 - Vedeti optiunile de iesire \n";
                                                                        cin >> comandam;
                                                                        verif = verificaComanda(comandam, 1, 4);
                                                                    }
                                                                    switch(comandam)
                                                                    {
                                                                    //daca vrem sa modificam un produs din cos
                                                                    case 1:
                                                                        {
                                                                            map <int, pair<Produs*, int>> produse_temp = c.getProduse();
                                                                            cout << "\n Introduceti numarul produsului pe care doriti sa-l ";
                                                                            cout << "modificati: ";
                                                                            int indiceProdus;
                                                                            cin >> indiceProdus;
                                                                            indiceProdus--;
                                                                            if(produse_temp.count(indiceProdus) == 0)
                                                                                cout << "\n Indicele introdus nu este valid";
                                                                            else {
                                                                                int cantitateNoua;
                                                                                verif = false;
                                                                                while(!verif)
                                                                                {
                                                                                    cout << "\n Introduceti noua cantitate pe care vreti sa o aveti";
                                                                                    cout << " in cos din acest produs: ";
                                                                                    cin >> cantitateNoua;
                                                                                    verif = verificaCantitate(cantitateNoua,
                                                                                                              (*produse_temp[indiceProdus].first).getStoc());
                                                                                }
                                                                                produse_temp[indiceProdus].second = cantitateNoua;
                                                                                c.setProduse(produse_temp);
                                                                                system("cls");
                                                                                cout << "Modificare realizata cu succes!\n";
                                                                                cout << c;
                                                                            }
                                                                            break;
                                                                        }
                                                                    //daca vrem sa golim cosul
                                                                    case 2:
                                                                        {
                                                                            c.setProduse({});
                                                                            //setam dictionarul la unul gol
                                                                            cout << "\nCosul dumneavoastra a fost golit!\n";
                                                                            break;
                                                                        }
                                                                    //daca vrem sa dam comanda
                                                                    case 3:
                                                                        {
                                                                            //verificam daca clientul are destui bani cat sa finalizeze comanda
                                                                            if(listaClienti[indiceCurent].getBani() >= c.calcTotal(false))
                                                                            {
                                                                                //ii crestem clientului punctele bonus
                                                                                listaClienti[indiceCurent].primestePuncte(c.calcPuncte());
                                                                                //realizam tranzactia <=> clientului ii scad banii,
                                                                                //cumparam fiecare obiect din cos (ii scade stocul)
                                                                                listaClienti[indiceCurent].cumpara(c.calcTotal(false));
                                                                                c.cumparam();
                                                                                //golim cosul
                                                                                c.setProduse({});
                                                                                cout << "\nTranzactie realizata cu succes!\n";

                                                                            }
                                                                            else cout << "Nu aveti un buget suficient de mare pentru a realiza tranzactia dorita!\n";
                                                                            break;
                                                                        }
                                                                    case 4:
                                                                        {
                                                                            //vrem sa iesim asa ca nu facem nimic
                                                                            break;
                                                                        }
                                                                    default:
                                                                        cout << "Cum ai reusit sa scapati de verificare cu aceasta comanda invalida?!";
                                                                    }
                                                                    break;
                                                                }
                                                            default:
                                                                cout << "Cum ai reusit sa scapati de verificare cu aceasta comanda invalida?!";
                                                            }
                                                            listaClienti[indiceCurent].setCos(c);
                                                            //la final, indiferent de ce am ales sa facem, oferim posibilitatea iesirii din program
                                                            //sau de intoarcere la meniul principal
                                                            int iesire;
                                                            verif = false;
                                                            while(!verif)
                                                            {
                                                                cout << "\n Ati dori sa:";
                                                                cout << " \n1 - Mergeti inapoi \n2 - Intorceti-va la meniul principal \n3 - Iesiti\n";
                                                                cin >> iesire;
                                                                verif = verificaComanda(iesire, 1, 3);
                                                            }
                                                            if(iesire == 3)
                                                            {
                                                                system("cls");
                                                                cout << "O zi frumoasa! Va mai asteptam!\n";
                                                                stop = false;
                                                                profil = false;
                                                                neAutentificam = false;
                                                                autentificati = false;
                                                                vremSaCumparam = false;
                                                            }
                                                            else {
                                                                if(iesire == 2)
                                                                    vremSaCumparam = false;
                                                            }
                                                        }
                                                        break;
                                                    }
                                                //daca vrem sa vizualizam/sa ne alegem un proiect
                                                case 2:
                                                    {
                                                        //daca nu avem niciun proiect
                                                        if(listaProiecte.empty())
                                                        {
                                                            cout << "Din pacate, momentan nu avem proiecte postate. \nVa rugam reveniti mai tarziu!";
                                                            //dupa iese din if si ii dam ocazia sa iasa din program sau sa se intoarca la meniul principal
                                                        }
                                                        //daca avem proiecte
                                                        else {
                                                            //afisam lista de proiecte cu indicele lor in lista de proiecte
                                                            cout << "Vizualizati pattern-urile noastre si alegeti-va viitorul proiect!\n\n";
                                                            for(int i = 0; i < listaProiecte.size(); i++)
                                                                cout << "Proiectul " << i + 1 << ": \n" << listaProiecte[i] << endl;
                                                            //selectam un nou proiect cu ajutorul indicelui din lista proiectelor
                                                            int indiceProiect;
                                                            verif = false;
                                                            while(!verif)
                                                            {
                                                                cout << "\nAlegeti-va viitorul proiect: ";
                                                                cin >> indiceProiect;
                                                                //verificam validitatea indicelui
                                                                verif = verificaIndice(indiceProiect, 1, listaProiecte.size());
                                                            }
                                                            indiceProiect--;
                                                            //daca vrem sa alegem un proiect valid
                                                            system("cls");
                                                            //afisam proiectul
                                                            cout << "Ati ales proiectul " << indiceProiect << endl;
                                                            cout << listaProiecte[indiceProiect] << endl;
                                                            //verificam daca nu avem timp
                                                            if(listaClienti[indiceCurent].getTimpLiber() < listaProiecte[indiceProiect].getTimpNecesar())
                                                            {
                                                                //ii sugeram sa-si ia o vacanta
                                                                cout << "\nDin pacate, nu aveti timp liber suficient pentru a termina proiectul =(";
                                                                cout << "\nVa sugeram calduros sa va luati o vacanta!";
                                                                int concendiu;
                                                                verif = false;
                                                                while(!verif)
                                                                {
                                                                    cout << "\n1 - Imi iau concediu \n2 - Renunt la proiect =( \n";
                                                                    cin >> concendiu;
                                                                    verif = verificaComanda(concendiu, 1, 2);
                                                                }
                                                                //daca isi ia vacanta
                                                                if(concendiu)
                                                                {
                                                                    //ii spunem ca vacanta costa si de cate zile are nevoie macar pentru a realiza proiectul dorit
                                                                    float diferenta = listaProiecte[indiceProiect].getTimpNecesar();
                                                                    diferenta -= listaClienti[indiceCurent].getTimpLiber();
                                                                    cout << "\nAveti nevoie de macar ";
                                                                    cout << diferenta; //numarul de zile necesar pt a realiza proiectul
                                                                    cout << " zile de vacanta \n";
                                                                    cout << "Luati in considerare faptul ca fiecare zi de concediu costa 100 de lei :P\n";
                                                                    int zile;
                                                                    verif = false;
                                                                    while(!verif)
                                                                    {
                                                                        cout << "Cate zile de concediu doriti sa va luati? ";
                                                                        cin >> zile; //cate zile de vacanta vrea clientul sa isi ia
                                                                        verif = verificaMicMare(zile, 0, 1000);
                                                                    }
                                                                    //daca nu are bani de atatea zile de vacanta
                                                                    if(zile * 100 > listaClienti[indiceCurent].getBani())
                                                                            cout << "\nNu aveti destui bani sa va luati " << zile << " zile de concediu...";
                                                                    else {
                                                                        //daca are bani, dar si-a luat prea putine zile de concediu
                                                                        if(zile < diferenta)
                                                                        {
                                                                            cout << "\nNu v-ati luat destule zile de vacanta...";
                                                                            listaClienti[indiceCurent].iaVacanta(zile); //i le adaugam totusi (ii scadem si banii)
                                                                        }
                                                                        //daca are bani si si-a luat destule
                                                                        else
                                                                        {
                                                                            //ii adaugam zilele luate si ii scadem banii
                                                                            listaClienti[indiceCurent].iaVacanta(zile);
                                                                            //ii adaugam proiectul la lista si ii scadem zilele necesare
                                                                            listaClienti[indiceCurent].adaugaProiect(listaProiecte[indiceProiect]);
                                                                            cout << "\nAti realizat proiectul cu succes! Felicitari!!";
                                                                        }

                                                                    }
                                                                }
                                                            }
                                                            //daca avem timp il adaugam la lista noastra de proiecte
                                                            else {
                                                                listaClienti[indiceCurent].adaugaProiect(listaProiecte[indiceProiect]);
                                                                cout << "\nAti realizat proiectul cu succes! Felicitari!!";
                                                            }
                                                        }
                                                        //ii oferim posibilitatea sa iasa din program/sa se intoarca la meniul principal
                                                        int iesire;
                                                        verif = false;
                                                        while(!verif)
                                                        {
                                                            cout << " \n1 - Iesiti \n2 - Intorceti-va la meniul principal\n";
                                                            cin >> iesire;
                                                            verif = verificaComanda(iesire, 1, 2);
                                                        }
                                                        if(iesire == 1)
                                                        {
                                                            system("cls");
                                                            cout << "O zi frumoasa! Va mai asteptam!\n";
                                                            stop = false;
                                                            profil = false;
                                                            neAutentificam = false;
                                                            autentificati = false;
                                                        }
                                                        break;
                                                    }
                                                //modificam sau stergem contul curent
                                                case 3:
                                                    {
                                                        //ii afisam datele contului
                                                        system("cls");
                                                        cout << "Contul Dumneavoastra: \n\n";
                                                        cout << listaClienti[indiceCurent];
                                                        //poate sa-si stearga sau sa-si modifice contul
                                                        int modificare;
                                                        verif = false;
                                                        while(!verif)
                                                        {
                                                            cout << "\n 1 - Modificati-va contul \n 2 - Stergeti-va contul \n 3 - Inapoi \n 4 - Iesiti \n";
                                                            cin >> modificare;
                                                            verif = verificaComanda(modificare, 1, 4);
                                                        }
                                                        //modificam contul
                                                        switch(modificare)
                                                        {
                                                        case 1:
                                                            {
                                                                bool vremSaModificam = true; //ne mentine in meniul de schimbare a contului pana zicem ca vrem sa iesim
                                                                while(vremSaModificam)
                                                                {
                                                                    system("cls");
                                                                    //afisam din nou datele contului
                                                                    cout << "Contul Dumneavoastra: \n\n";
                                                                    cout << listaClienti[indiceCurent];
                                                                    //ii dam posibilitatea sa-si modifice orice detaliu din cont
                                                                    int schimbare;
                                                                    verif = false;
                                                                    while(!verif)
                                                                    {
                                                                        cout << "\n Ce doriti sa modificati? \n 1 - Numele \n 2 - Emailul \n 3 - Parola";
                                                                        cout << "\n 4 - Decizia de a primi anunturi \n 5 - Banii \n 6 - Timpul liber ";
                                                                        cout << "\n 7 - Proiectele \n";
                                                                        cin >> schimbare;
                                                                        verif = verificaComanda(schimbare, 1, 7);
                                                                    }
                                                                    switch(schimbare)
                                                                    {
                                                                    //schimbam numele
                                                                    case 1:
                                                                        {
                                                                            string numeNou;
                                                                            cout << "\n Dati noul nume: ";
                                                                            cin.ignore();
                                                                            getline(cin, numeNou);
                                                                            listaClienti[indiceCurent].setNume(numeNou);
                                                                            break;
                                                                        }
                                                                    //schimbam email-ul
                                                                    case 2:
                                                                        {
                                                                            string emailNou;
                                                                            cout << "\n Dati noul email: ";
                                                                            cin.ignore();
                                                                            getline(cin, emailNou);
                                                                            listaClienti[indiceCurent].setEmail(emailNou);
                                                                            break;
                                                                        }
                                                                    //schimbam parola
                                                                    case 3:
                                                                        {
                                                                            string aux, aux2; //citim doua auxiliare pt parola si confirmarea ei
                                                                            bool parolaInvalida = true;
                                                                            cin.ignore();
                                                                            //tot citim pana cele doua auxiliare sunt egale
                                                                            while(parolaInvalida)
                                                                            {
                                                                                try
                                                                                {
                                                                                    cout << "\n Dati noua parola: ";
                                                                                    getline(cin, aux);
                                                                                    cout << "\n Confirmati parola: ";
                                                                                    getline(cin, aux2);
                                                                                    //iesim din while cand sunt egale, moment in care setam si parola
                                                                                    if(aux == aux2)
                                                                                    {
                                                                                        listaClienti[indiceCurent].setParola(aux);
                                                                                        parolaInvalida = false;
                                                                                    }
                                                                                    else throw 1;
                                                                                }
                                                                                catch(int a)
                                                                                {
                                                                                    // \x1B inseamna ca fundalul ramane la fel, [31m - font rosu, [97m - font alb
                                                                                    cout << "\n \x1B[31mParola si confirmarea parolei nu conicid!\x1B[97m";
                                                                                }
                                                                            }
                                                                            break;
                                                                        }
                                                                    //schimbam daca vrem sau nu anunturi
                                                                    case 4:
                                                                        {
                                                                            if(listaClienti[indiceCurent].getTrimiteAnunturi())
                                                                                listaClienti[indiceCurent].setTrimiteAnunturi(false);
                                                                            else listaClienti[indiceCurent].setTrimiteAnunturi(true);
                                                                            break;
                                                                        }
                                                                    //schimbam bugetul
                                                                    case 5:
                                                                        {
                                                                            float baniNoi;
                                                                            verif = false;
                                                                            while(!verif)
                                                                            {
                                                                                cout << "\n Cat sunteti dispus sa investiti in produsele noastre? ";
                                                                                cin >> baniNoi;
                                                                                verif = verificaMicMare(baniNoi, (float)0.0, (float)100000000.0);
                                                                            }
                                                                            listaClienti[indiceCurent].setBani(baniNoi);
                                                                            break;
                                                                        }
                                                                    //schimbam timpul liber pe care il avem
                                                                    case 6:
                                                                        {
                                                                            float timpNou;
                                                                            verif = false;
                                                                            while(!verif)
                                                                            {
                                                                                cout << "\n Cat timp liber aveti la dispozitie? ";
                                                                                cin >> timpNou;
                                                                                verif =verificaMicMare(timpNou, (float)0.0, (float)1000.0);
                                                                            }
                                                                            listaClienti[indiceCurent].setTimpLiber(timpNou);
                                                                            break;
                                                                        }
                                                                    //schimbam proiectele pe care le-am realizat
                                                                    case 7:
                                                                        {
                                                                            int nrProiecteNou;
                                                                            list <Proiect> proiecteNoi = {};
                                                                            verif = false;
                                                                            while(!verif)
                                                                            {
                                                                                cout << "\n Dati numarul nou de proiecte: ";
                                                                                cin >> nrProiecteNou;
                                                                                verif = verificaMicMare(nrProiecteNou, 0, 100);
                                                                            }
                                                                            system("cls");
                                                                            cout << "Dati noile proiecte: \n";
                                                                            for(int i = 0; i < nrProiecteNou; i++)
                                                                            {
                                                                                Proiect aux;
                                                                                cin >> aux;
                                                                                proiecteNoi.push_back(aux);
                                                                                cout << '\n';
                                                                            }
                                                                            listaClienti[indiceCurent].setProiecte(proiecteNoi);
                                                                            break;
                                                                        }
                                                                    default:
                                                                        throw runtime_error("Comanda invalida!!");
                                                                    }
                                                                    system("cls");
                                                                    //afisam contul modificat si vedem daca vrea sa mai modifice ceva sau nu
                                                                    cout << " Modificare realizata cu succes! \n Contul dumneavoastra: \n\n";
                                                                    cout << listaClienti[indiceCurent] << endl;
                                                                    int iesire;
                                                                    verif = false;
                                                                    while(!verif)
                                                                    {
                                                                        cout << " Doriti sa:\n 1 - Continuati modificarile\n";
                                                                        cout << " 2 - Intorceti-va la meniu\n 3 - Iesiti\n";
                                                                        cin >> iesire;
                                                                        verif = verificaComanda(iesire, 1, 3);
                                                                    }
                                                                    if(iesire == 3)
                                                                    {
                                                                        system("cls");
                                                                        cout << "O zi frumoasa! Va mai asteptam!\n";
                                                                        vremSaModificam = false;
                                                                        neAutentificam = false;
                                                                        autentificati = false;
                                                                        profil = false;
                                                                        stop = false;
                                                                    }
                                                                    else {
                                                                        if(iesire == 2)
                                                                            vremSaModificam = false;
                                                                    }
                                                                }
                                                                break;
                                                            }
                                                        //stergem contul
                                                        case 2:
                                                            {
                                                                //ne asiguram ca vr sa-si stearga permanent contul
                                                                bool stergere;
                                                                cout << "\n Sunteti sigur ca vreti sa va stergeti permanent contul? [0/1]: ";
                                                                cin >> stergere;
                                                                //stergem contul curent din lista
                                                                if(stergere)
                                                                {
                                                                    listaClienti.erase(listaClienti.begin() + indiceCurent);
                                                                    cout << "\n Contul a fost sters cu succes!";
                                                                }
                                                                int iesire;
                                                                verif = false;
                                                                while(!verif)
                                                                {
                                                                    cout << "\n Doriti sa: \n 1 - Ramaneti in aplicatie \n 2 - Iesiti \n";
                                                                    cin >> iesire;
                                                                    verif = verificaComanda(iesire, 1, 2);
                                                                }
                                                                //daca vrem sa iesim
                                                                if(iesire == 2)
                                                                {
                                                                    system("cls");
                                                                    cout << "O zi frumoasa! Va mai asteptam!\n";
                                                                    stop = false;
                                                                    profil = false;
                                                                    neAutentificam = false;
                                                                    autentificati = false;
                                                                }
                                                                else {
                                                                    //daca vrem sa ramanem in aplicatie
                                                                    //o sa trebuiasca sa ne autentificam din nou
                                                                    autentificati = false;
                                                                    neAutentificam = false;
                                                                }
                                                                break;
                                                            }
                                                        //daca vrem sa mergem inapoi
                                                        case 3:
                                                            {
                                                                break;
                                                            }
                                                        //daca vrem sa iesim de tot
                                                        case 4:
                                                            {
                                                                system("cls");
                                                                cout << "O zi frumoasa! Va mai asteptam!\n";
                                                                stop = false;
                                                                profil = false;
                                                                neAutentificam = false;
                                                                autentificati = false;
                                                                break;
                                                            }
                                                        default:
                                                            cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
                                                        }
                                                        break;
                                                    }
                                                //daca vrem sa iesim din cont
                                                case 4:
                                                    {
                                                        neAutentificam = false;
                                                        autentificati = false;
                                                        break;
                                                    }
                                                //daca vrem sa iesim din aplicatie
                                                case 5:
                                                    {
                                                        system("cls");
                                                        cout << "O zi frumoasa! Va mai asteptam!\n";
                                                        stop = false;
                                                        profil = false;
                                                        neAutentificam = false;
                                                        autentificati = false;
                                                        break;
                                                    }
                                                default:
                                                    cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
                                                }
                                            }
                                    }
                                }

                            }

                            else {
                                //vrem sa ne intoarcem
                                if(cont == 3)
                                {
                                    profil = false;
                                }
                                //vrem sa iesim
                                else {
                                        system("cls");
                                        cout << "O zi frumoasa! Va mai asteptam!";
                                        stop = false;
                                        profil = false;
                                }
                            }
                    }

                }
            break;
            }
            //daca suntem administrator
            case 2:
                 {
                int profil = true; //controleaza cand iesim din profilul ales
                while(profil)
                {
                    int comanda;
                    system("cls");
                    verif = false;
                    while(!verif)
                    {
                        cout << " Hello, Boss! \n Cu ce va pot ajuta astazi? \n 1 - Vreau sa reactualizez un stoc\n";
                        cout << " 2 - Vreau sa reactualizez lista de proiecte \n 3 - Vreau sa vizualizez lista de clienti \n";
                        cout << " 4 - Inapoi \n 5 - Iesiti \n";
                        cin >> comanda;
                        verif = verificaComanda(comanda, 1, 5);
                    }
                    system("cls");
                    switch(comanda)
                    {
                    //daca vrem sa reactualizam un stoc
                    case 1:
                        {
                            verif = false;
                            int felStoc; //tine minte cu ce fel de stoc alegem sa lucram
                            while(!verif)
                            {
                                cout << "Doriti sa reactualizati stocul de: \n";
                                cout << " 1 - Bobine\n 2 - Crosete\n 3 - Nasturi \n 4 - Amigurumi \n";
                                cin >> felStoc;
                                verif = verificaComanda(felStoc, 1, 4);
                            }
                            system("cls");
                            switch(felStoc)
                            {
                            //daca vrem sa reactualizam stocul de bobine
                            case 1:
                                {
                                    reactualizare_stoc(listaBobine, 0, stop, profil);
                                    break;
                                }
                            //reactualizam stocul de crosete
                            case 2:
                                {
                                    reactualizare_stoc(listaCrosete, 1, stop, profil);
                                    break;
                                }
                            //reactualizam stocul de nasturi
                            case 3:
                                {
                                    reactualizare_stoc(listaNasturi, 2, stop, profil);
                                    break;
                            }
                            //reactualizam stocul de amigurumi
                            case 4:
                                {
                                    reactualizare_stoc(listaAmigurumi, 3, stop, profil);
                                    break;
                                }
                            default:
                                cout << "Cum ati reusit sa scapati de verificare cu aceasta comanda invalida?!";
                            }
                            break;
                        }
                    //daca vrem sa reactualizam proiectele
                    case 2:
                        {
                            int adaugam;
                            verif = false;
                            while(!verif)
                            {
                                cout << " Reactualizarea proiectelor! \n";
                                cout << "Doriti sa: \n 1 - Adaugati un nou proiect \n 2 - Stergeti un proiect (neindicat)";
                                cout << "\n 3 - Modificati un proiect existent\n";
                                cin >> adaugam;
                                verif = verificaComanda(adaugam, 1, 3);
                            }
                            //daca vrem sa adaugam un proiect
                            if(adaugam == 1)
                            {
                                bool vremSaAdaugam = true; //ne mentine in meniul de adaugat pana vrem sa iesim
                                while(vremSaAdaugam)
                                {
                                    system("cls");
                                    //citim un proiect auxiliar ce va fi adaugat la lista de proiecte doar dupa confirmarea corectitudinii datelor
                                    cout << " Adaugati un nou proiect\n\n";
                                    Proiect ProiectCurent;
                                    cin >> ProiectCurent;
                                    bool confirmare;
                                    cout << "\n Urmatoarele date sunt corecte?\n\n";
                                    cout << ProiectCurent;
                                    cout << "\n Da\/Nu? [1/0]: ";
                                    cin >> confirmare;
                                    //daca primim confirmarea
                                    if(confirmare)
                                    {
                                        //adaugam proiectul in lista
                                        listaProiecte.push_back(ProiectCurent);
                                        cout << "\nLista actualizata!";

                                    }
                                    //afisam optiunile de iesire
                                    int iesire;
                                    verif = false;
                                    while(!verif)
                                    {
                                        cout << "Doriti sa: \n 1 - Mai adaugati proiecte \n 2 - Va intoarceti la meniul principal";
                                        cout << "\n 3 - Iesiti \n";
                                        cin >> iesire;
                                        verif = verificaComanda(iesire, 1, 3);
                                    }
                                    //daca vrem sa ramanem in meniul de adaugat nu facem nimic
                                    //daca vrem sa iesim din program
                                    if(iesire == 3)
                                    {
                                        system("cls");
                                        cout << "Bye, Boss! <3\n";
                                        profil = false;
                                        stop = false;
                                        vremSaAdaugam = false;
                                    }
                                    else {
                                        //daca vrem sa ne intoarcem la meniul principal
                                        if(iesire == 2)
                                            vremSaAdaugam = false;
                                    }
                                }
                            }
                            else {
                                //daca vrem sa stergem un proiect
                                if(adaugam == 2)
                                {
                                    bool vremSaStergem = true; //ne mentine in meniul de stergere pana vrem sa iesim
                                    while(vremSaStergem)
                                    {
                                        system("cls");
                                        cout << " Stregeti un proiect \n\n";
                                        //verificam daca avem proiecte postate
                                        if(listaProiecte.empty())
                                            cout << "Nu avem inca proiecte postate!";
                                        //daca avem proiecte in stoc
                                        else {
                                            //afisam lista curenta cu tot cu indicii proiectelor in lista de proiecte
                                            cout << " Lista curenta de pattern-uri disponibile: \n";
                                            for(int i = 0; i < listaProiecte.size(); i++)
                                                cout << "Proiectul " << i << ": \n" << listaProiecte[i] << endl;
                                            //selectam proiectul prin intermediul indicelui sau din lista de proiecte
                                            int indice;
                                            verif = false;
                                            while(!verif)
                                            {
                                                cout << "Doriti sa stergeti proiectul numarul: ";
                                                cin >> indice;
                                                verif = verificaIndice(indice, 1, listaProiecte.size());
                                            }
                                            indice--;
                                            //stregem proiectul cu indicele "indice" din lista de proiecte
                                            listaProiecte.erase(listaProiecte.begin() + indice);
                                            //afisam stocul actualizat
                                            system("cls");
                                            cout << "Lista actualizata de proiecte din revista: \n\n";
                                            for(int i = 0; i < listaProiecte.size(); i++)
                                                cout << listaProiecte[i] << endl;
                                        }
                                        //afisam optiunile de iesire
                                        int iesire;
                                        verif = false;
                                        while(!verif)
                                        {
                                            cout << "Mai departe doriti sa: \n 1 - Continuati sa stergeti proiecte \n 2 - Reveniti la meniul principal";
                                            cout << "\n 3 - Iesiti \n";
                                            cin >> iesire;
                                            verif = verificaComanda(iesire, 1, 3);
                                        }
                                        //daca vrem sa ramanem in meniul de stergere nu facem nimic
                                        //daca vrem sa iesim din program
                                        if(iesire == 3)
                                        {
                                            system("cls");
                                            cout << "Bye, Boss! <3\n";
                                            profil = false;
                                            stop = false;
                                            vremSaStergem = false;
                                        }
                                        else {
                                            //daca vrem sa ne intoarcem la meniul principal
                                            if(iesire == 2)
                                                vremSaStergem = false;
                                        }
                                    }
                                }
                                else {
                                    //daca vrem sa modificam un proiect
                                    if(adaugam == 3)
                                    {
                                        bool vremSaModificam = true;//ne mentine in meniul de modificat
                                        while(vremSaModificam)
                                        {
                                            system("cls");
                                            cout << "Modificati un proiect! \n";
                                            //verificam daca avem proiecte postate
                                            if(listaProiecte.empty())
                                                cout << "Nu avem proiecte posatate!";
                                            //daca avem proiecte postate
                                            else {
                                                //afisam lista proiectelor curente cu tot cu indicii proiectelor in ea
                                                cout << "Lista curenta de pattern-uri disponibile: \n";
                                                for(int i = 0; i < listaProiecte.size(); i++)
                                                    cout << "Proiectul " << i + 1 << ": \n" << listaProiecte[i] << endl;
                                                //selectam proiectul prin intermediul indicelui din lista
                                                int indice;
                                                verif = false;
                                                while(!verif)
                                                {
                                                    cout << "Doriti sa modificati proiectul numarul: ";
                                                    cin >> indice;
                                                    verif = verificaIndice(indice, 1, listaProiecte.size());
                                                }
                                                indice--;
                                                system("cls");
                                                //afisam proiectul selectat
                                                cout << "Modificam proiectul: \n";
                                                cout << listaProiecte[indice];
                                                int modificare;
                                                //selectam ce vrem sa modificam
                                                verif = false;
                                                while(!verif)
                                                {
                                                    cout << "\nModificati: \n 1 - Numele proiectului \n 2 - Timpul necesar realizarii sale \n 3 - Numarul de bobine";
                                                    cout << "\n 4 - Crosetele Necesare\n";
                                                    cin >> modificare;
                                                    verif = verificaComanda(modificare, 1, 4);
                                                }
                                                switch(modificare)
                                                {
                                                //modificam numele
                                                case 1:
                                                    {
                                                        string numeNou;
                                                        cout << "\n Dati noul nume: ";
                                                        cin.get();
                                                        getline(cin, numeNou);
                                                        listaProiecte[indice].setNume(numeNou);
                                                        break;
                                                    }
                                                //modificam timpul necesar realizarii lui
                                                case 2:
                                                    {
                                                        float timpNou;
                                                        verif = false;
                                                        while(!verif)
                                                        {
                                                            cout << "\n Dati noul timp necesar realizarii proiectului (in ore): ";
                                                            cin >> timpNou;
                                                            verif = verificaMicMare(timpNou, (float)0.5, (float)90.0);
                                                        }
                                                        listaProiecte[indice].setTimpNecesar(timpNou);
                                                        break;
                                                    }
                                                //modificam numarul de bobine necesare realizarii lui
                                                case 3:
                                                    {
                                                        int nrBobineNou;
                                                        verif = false;
                                                        while(!verif)
                                                        {
                                                            cout << "\n Dati noul numar de bobine necesare realizarii proiectului: ";
                                                            cin >> nrBobineNou;
                                                            verif = verificaMicMare(nrBobineNou, 1, 10);
                                                        }

                                                        listaProiecte[indice].setNrBobine(nrBobineNou);
                                                        break;
                                                    }
                                                //modificam crosetele necesare realizarii lui
                                                case 4:
                                                    {
                                                        int nrCroseteNou;
                                                        set <float> croseteNoi;
                                                        verif = false;
                                                        while(!verif)
                                                        {
                                                            cout << "\n Dati numarul crosetelor noi: ";
                                                            cin >> nrCroseteNou;
                                                            verif = verificaMicMare(nrCroseteNou, 1, 6);
                                                        }

                                                        cout << "\n Dati marimile noilor crosete: ";
                                                        for(int i = 0; i < nrCroseteNou; i++)
                                                        {
                                                            float aux;
                                                            verif = false;
                                                            while(!verif)
                                                            {
                                                                cout << "\n - croseta " << i + 1 << ": ";
                                                                cin >> aux;
                                                                verif = verificaMicMare(aux, (float)1.0, (float)35.0);
                                                            }
                                                            croseteNoi.insert(aux);
                                                        }
                                                        listaProiecte[indice].setCroseteNecesare(croseteNoi);
                                                        break;
                                                    }
                                                default:
                                                    cout << "Cum ati reusit sa treceti de verificare cu aceasta comanda invalida?!";
                                                }
                                                //afisam proiectul modificat
                                                system("cls");
                                                cout << " Modificare realizata cu succes! Proiectul actualizat: \n";
                                                cout << listaProiecte[indice];
                                            }
                                            //afisam optiunile de iesire
                                            int iesire;
                                            verif = false;
                                            while(!verif)
                                            {
                                                cout << "\n Mai departe doriti sa: \n 1 - Continuati sa modificati proiecte";
                                                cout << "\n 2 - Reveniti la meniul principal \n 3 - Iesiti \n";
                                                cin >> iesire;
                                                verif = verificaComanda(iesire, 1, 3);
                                            }
                                            //daca vrem sa ramanem in meniul de modificat nu facem nimic
                                            //daca vrem sa iesim din program
                                            if(iesire == 3)
                                            {
                                                system("cls");
                                                cout << "Bye, Boss! <3\n";
                                                profil = false;
                                                stop = false;
                                                vremSaModificam = false;
                                            }
                                            else {
                                                //daca vrem sa ne intoarcem la meniul principal
                                                if(iesire == 2)
                                                    vremSaModificam = false;
                                            }
                                        }

                                    }
                                    else cout << "Cum ati reusit sa treceti de verificare cu aceasta comanda invalida?!";
                                }
                            }
                            break;
                        }
                    //daca vrem sa afisam lista de clienti inregistrati
                    case 3:
                        {
                            //verificam daca avem clienti inregistrati
                            if(!listaClienti.empty())
                            {
                                //afisam lista clientilor
                                cout << " Lista clientilor inregistrati: \n\n";
                                for(int i = 0; i < listaClienti.size(); i++)
                                    cout << listaClienti[i] << endl;
                                //afisam cati clienti inregistrati avem
                                if(listaClienti.size() == 1)
                                    cout << "\n Avem un singur client inregistrat! Se putea si mai bine... \n";
                                else cout << "\n Avem un total de " << listaClienti.size() << " clienti inregistrati! \n Bravo noua!! =) \n";
                            }
                            //daca nu avem clienti
                            else cout << "Nu avem clienti inregistrati =(( \n";
                            //afisam optiunile de iesire
                            bool iesire;
                            cout << "Doriti sa iesiti? [0/1]: ";
                            cin >> iesire;
                            //daca vrm sa iesim
                            if(iesire)
                            {
                                system("cls");
                                cout << "Bye, Boss! <3\n";
                                profil = false;
                                stop = false;
                            }
                            break;
                        }
                    //daca vrem sa iesim din meniul de administrator
                    case 4:
                        {
                            profil = false;
                            break;
                        }
                    //daca vrem sa iesim din program
                    case 5:
                        {
                            system("cls");
                            cout << "Bye, Boss! <3\n";
                            profil = false;
                            stop = false;
                            break;
                        }
                    default:
                        {
                            cout << "Cum ati reusit sa treceti de verificare cu aceasta comanda invalida?!";
                            break;
                        }
                    }
                }
            break;
            }
            default: {
                cout << "Cum ati reusit sa treceti de verificare cu aceasta comanda invalida?!";
                break;
            }
            }
            }
        //gata start()
    }
};

Meniu* Meniu::obiect = 0;

int main()
{
    Meniu* meniu = meniu -> getInstance();
    (*meniu).start();

    return 0;
}
