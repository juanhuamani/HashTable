#include <iostream>
#include <vector>
using namespace std;
using std::pair;
using std::vector;

enum Condition {Vacio, Lleno};

template<typename K,typename T>
class Table{
    private:
        pair<K*, vector<T>*> table;
        Condition c;
    public:
        template<typename M,typename N> friend class HashTable;
        Table(){
            table.first = nullptr;
            table.second = new vector<T>;
            c = Vacio;
        }
        ~Table(){}
};

template<typename K,typename T>
class HashTable{
private:
    Table<K,T>* base;
    unsigned int size;
private:
    int hashFunction(K key, int i){
        return (key + i) % size;
    }

public:
    HashTable(unsigned int size){
        this->size = size;
        base = new Table<K, T> [size];
    }
    void insertData(K key, T data){
        int indice = 0;
        for (unsigned int i = 0; i < size; i++){
            indice = hashFunction(key, i);
            if (base[indice].c == Vacio){
                base[indice].c = Lleno;
                base[indice].table.first = new K (key);
                base[indice].table.second->push_back(data);
                return;
            }
            else if (*base[indice].table.first == key){
                base[indice].table.second->push_back(data);
                return;
            }
        } 
        return;
    }
    void displayHash(){
        for (unsigned int i = 0; i < size; i++){
            cout << i << "\t";
            if (base[i].table.first == nullptr){
                cout << "NULL\n";
            }  
            else{
                cout << *base[i].table.first << "\t";
                for (const auto& j : *base[i].table.second){
                    cout << j << ", ";
                }
                cout << endl;
            }
        }
    }     
};



class Cliete{
private:
    string nombre;
    string email;
public:
    Cliete(string nombre, string email){
        this->nombre = nombre;
        this->email = email;
    }
    ~Cliete(){}

    friend std::ostream& operator<<(std::ostream& os, const Cliete& e){
        return os << e.nombre << " - " <<e.email;
    }
};


class Peliculas{
private:
    string nombre;
    string recaudacion ;
public:
    Peliculas(string nombre, string recaudacion){
        this->nombre = nombre;
        this->recaudacion = recaudacion;
    }
    ~Peliculas(){}

    friend std::ostream& operator<<(std::ostream& os, const Peliculas& e){
        return os << e.nombre << " - " <<e.recaudacion;
    }
};




int main(){
    
/*/
    HashTable<int, string> base(10);

    base.insertData(42, "Juan");
    base.insertData(42, "Jose");
    base.insertData(42, "Fernanda");

    base.insertData(15, "Saul");
    base.insertData(15, "Diego");

    base.insertData(23, "Gaspi");
    base.insertData(23, "Pedro");
    base.insertData(23, "Tomy");

    base.insertData(2, "Tiago");

    base.displayHash();
/*/
/*/
    HashTable<int, Cliete> base(10);
    
    Cliete e1("Juan", "Juan7476@gmail.com");
    Cliete e2("Jose", "Jose846@gmail.com");
    Cliete e3("Fernanda", "Fernanda747@gmail.com");
    Cliete e4("Saul", "Saul1341@gmail.com");
    Cliete e5("Diego", "Diego1231@gmail.com");
    
    base.insertData(20212463, e1);
    base.insertData(20201394, e2);
    base.insertData(20201113, e3);
    base.insertData(20193023, e4);
    base.insertData(20219349, e5);
    base.displayHash();
/*/

    HashTable<int, Peliculas> base(10);
    
    Peliculas e1("Avatar", "$2 923 818 852");
    Peliculas e2("Avengers: Endgame", "$2 797 501 328");
    Peliculas e3("Titanic", "$2 201 657 264");
    Peliculas e4("StarWars:EpisodioVII", "$2 069 521 700");
    Peliculas e5("SpiderMan:NoWayHome", "$1 916 306 995");
    
    base.insertData(201605, e1);
    base.insertData(201806, e2);
    base.insertData(199603, e3);
    base.insertData(101604, e4);
    base.insertData(202105, e5);
    base.displayHash();

    return 0;
}
