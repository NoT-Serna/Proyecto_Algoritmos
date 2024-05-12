#include<iostream>
#include<math.h>
#include<string>
#include <chrono>
#include <thread>
#include <fstream>
#include <sstream>

using namespace std;

class Genero{
private:
    string nombre;
    Genero* pointer;

public:
    Genero(){
        nombre = " ";
        pointer = nullptr;
    }

    ~Genero(){

    }

    Genero(string n){
        nombre = n;
        pointer = nullptr;
    }

    string get_dato(){
        return nombre;
    }

    void set_dato(string n){
        nombre = n;
    }

    Genero* get_next(){
        return pointer;
    }

    void set_next(Genero* g){
        pointer = g;
    }

    string to_string(){
        return get_dato();
    }

    friend std::ostream& operator<<(std::ostream& os, Genero& b){
        return os <<b.to_string();
    }

};

class Cancion {
private:
    string titulo;
    string artista;
    string album;
    int duracion; // Duración en segundos
    Cancion* pointer;
    Genero* generoPointer; // Pointer to the corresponding genre

public:
    Cancion() {
        titulo = " ";
        artista = " ";
        album = " ";
        duracion = 0;
        pointer = NULL;
        generoPointer = NULL;
    }

    ~Cancion() {}

    Cancion(string t, string a, string al, int d, Genero* g) {
        titulo = t;
        artista = a;
        album = al;
        duracion = d;
        pointer = NULL;
        generoPointer = g;
    }

    // Getters
    inline const string& get_titulo() const { return titulo; }
    inline const string& get_artista() const { return artista; }
    inline const string& get_album() const { return album; }
    inline int get_duracion() const { return duracion; }

    // Setters
    void set_titulo(const string& t) { titulo = t; }
    void set_artista(const string& a) { artista = a; }
    void set_album(const string& al) { album = al; }
    void set_duracion(int d) { duracion = d; }

    // Get the corresponding genre
    inline Genero* get_generoPointer() const { return generoPointer; }

    // Set the corresponding genre
    void set_generoPointer(Genero* g) { generoPointer = g; }

    Cancion* get_next() { return pointer; }

    void set_next(Cancion* c) { pointer = c; }

    Cancion& operator=(const Cancion& f) {
        set_titulo(f.titulo);
        set_artista(f.artista);
        set_album(f.album);
        set_duracion(f.duracion);
        return *this;
    }

    string to_string() const {
        return "------------------------------------\n"
               "|       " + titulo + "\n"
               "|       " + artista + "\n"
               "|       " + album + "\n"
               "|       Duracion: " + std::to_string(duracion) + "s\n"
               "|       Genero: " + generoPointer->get_dato() + "\n"
               "------------------------------------\n";
    }

    friend std::ostream& operator<<(std::ostream& os, Cancion& b) {
        return os << b.to_string();
    }
};


class Nodo{
    Genero* genero;
    Cancion* cancion;
    Nodo* pointer;
    Nodo* prev;
    int size;

public:
    Nodo(){
        genero = nullptr;
        cancion = nullptr;
        pointer = nullptr;
        prev = nullptr;
        int size;
    }

    ~Nodo(){
        delete cancion;
   }

    Nodo(Genero* g){
      genero = g;
      pointer = NULL;
      prev = NULL;
      cancion = NULL;
      size = 0;
  }
    
    Genero* get_dato(){
      return genero;
  }
  
  void set_dato(Genero* g){
      genero = g;
  }
  
  Nodo* get_next(){
      return pointer;
  }
  
  Nodo* get_prev(){
      return prev;
  }
  
  void set_next(Nodo* p){
      pointer = p;
  }
  
  void set_prev(Nodo* a){
      prev = a;
  }

  void push_back(string t, string a, string al, int d, Genero* g) {
    if (size == 0) {
        cancion = new Cancion(t, a, al, d, g);
        size++;
    } else {
        Cancion* c_1 = cancion;
        while (c_1->get_next() != nullptr) {
            c_1 = c_1->get_next();
        }
        c_1->set_next(new Cancion(t, a, al, d, g));
        size++;
    }
}


    Cancion* get(int i){
        if(i < size && i>=0){
            Cancion* c = cancion;
            for(int x = 0; x<i; x++){
                c = c->get_next();
            }
            return c;
        }else{
            if(size == 0){
                cout<<"La playlist está vacía";
            }else{
                cout<<"La posicion no existe";
            }
            return NULL;
        }

    }

    Cancion* get_genero(string d){
        genero = new Genero(d);
        cout<<"El género de la canción "<< d << " es " << *get(0)<<endl;
        return get(0);
    }

    string to_string() const {
    string s = genero->to_string() + ":\n>>";
    Cancion* c = cancion;
    while (c != nullptr) {
        s.append(c->to_string());
        c = c->get_next();
    }
    s.append("\n");
    return s;
}




    friend std:: ostream& operator<<(std:: ostream& os, Nodo& b){
        return os <<b.to_string();
    }

};

class Playlist{
    
    Nodo* ptr;
    int size;

public:  

    Playlist(){
        ptr = NULL;
        size = 0;
    }
    
    ~Playlist(){
        Nodo* t = ptr;
        Nodo* n;
        while(t->get_next() != NULL){
            n = t;
            t = t->get_next();    
            delete n;
        }
        delete t;
    }
    
    void push_back(Genero* d){
        
        if(size == 0){
            ptr = new Nodo(d);
            size++;
        }else{
            Nodo* t = ptr;
            while(t->get_next() != NULL){
                t = t->get_next();    
            }
            t->set_next(new Nodo(d));
            size++;
        }
        cout<<endl;
        
    }
    
    int getSize(){
        return size;
    }
    
    void print(){
        if(size == 0){
            cout<<"La lista está vacía"<<endl;
        }else{
            Nodo* t = ptr;
            do{
                cout<<(*t);
                t = t->get_next();
                
            }while(t != NULL);
            cout<<endl;
        }
    }
    
    Nodo* get(int i){
        if(i < size && i>=0){
            Nodo* n = ptr;
            for(int x = 0; x<i;x++){
                n = n->get_next();
            }
            return n;
        }else{
            //throw invalid_argument("La posicion no existe");
            if(size == 0){
                cout<<"La playlist está vacía";
            }else{
                cout<<"La posicion no existe";
            }
            return NULL;
        }
        
    }
    
    
    void insert(Genero* p, int pos){
        if(pos >= 0 && pos <= size){
            if(size == 0 || pos == size){ 
                push_back(p);
            }else{
                Nodo* n = new Nodo(p);
                if(pos == 0){
                    n->set_next(ptr);
                    ptr = n;
                }else{
                    Nodo* t = get(pos-1);
                    n->set_next(t->get_next());
                    t->set_next(n);
                }
                size++;
            }
        }else{
            cout<<"La posicion no existe"<<endl;
            
        }
        
    }
    
    void remove(int pos){
        
        if((pos >= 0 && pos <= size) && size > 0){
            if(pos == 0){ 
                Nodo* t = ptr;
                ptr = ptr->get_next();
                delete t;
            }else{
                Nodo* t = get(pos-1);
                Nodo* t2 = t->get_next();
                
                t->set_next(t2->get_next());
                delete t2;
            }
            size--;
        }else{
            cout<<"La posicion no existe o la lista está vacía"<<endl;
        }
        
    }

    void readSongsFromFile(const string& filename, const string& gen_name) {
    ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << endl;
        return;
    }

    string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, artist, album;
        int duration;

        if (getline(iss, title, ',') &&
            getline(iss, artist, ',') &&
            getline(iss, album, ',') &&
            (iss >> duration)) {
            bool found = false;
            Nodo* current = ptr;
            while (current != nullptr) {
                if (current->get_dato()->get_dato() == gen_name) {
                    current->push_back(title, artist, album, duration, current->get_dato());
                    found = true;
                    break;
                }
                current = current->get_next();
            }
            if (!found) {
                std::cerr << "Genre '" << gen_name << "' not found." << endl;
            }
        } else {
            std::cerr << "Invalid format in line: " << line << endl;
        }
    }

    file.close();
}



    
};

int main() {

    /*
    Playlist pl = Playlist();
    
 
    pl.push_back(new Genero("Rock"));
    pl.push_back(new Genero("Pop"));
    // Añadir canciones al género
    if (pl.getSize() > 0) {
        pl.get(0)->push_back("Welcome to the Jungle", "Guns N' Roses", "Appetite For Destruction", 263);
        pl.get(0)->push_back("Black Dog", "Led Zeppelin", "Led Zeppelin IV", 317);
        pl.get(1)->push_back("Billie Jean", "Michael Jackson", "Thriller", 310);
        pl.get(1)->push_back("Human Nature", "Micheal Jackson", "Thriller", 250);
    } else {
        cout << "Playlist esta vacía. Añada un genero primero." << endl;
    }

    pl.print();

    */

    Playlist pl = Playlist();

    pl.push_back(new Genero("Rock"));
    pl.push_back(new Genero("Pop"));

    // Leer canciones
    pl.readSongsFromFile("songs.txt", "Rock");
    pl.readSongsFromFile("songs.txt", "Pop");
    pl.readSongsFromFile("songs.txt", "Reggaeton");

    pl.print();
    return 0;
}
