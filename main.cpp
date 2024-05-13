#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

class Genero {
private:
    string nombre;
    Genero* pointer;

public:
    Genero() {
        nombre = " ";
        pointer = nullptr;
    }

    Genero(string n) {
        nombre = n;
        pointer = nullptr;
    }

    string get_nombre() const {
        return nombre;
    }

    void set_nombre(string n) {
        nombre = n;
    }

    Genero* get_next() {
        return pointer;
    }

    void set_next(Genero* g) {
        pointer = g;
    }

    string to_string() {
        return get_nombre();
    }

    friend std::ostream& operator<<(std::ostream& os, Genero& b) {
        return os << b.to_string();
    }
};

class Cancion {
private:
    string titulo;
    vector<string> artistas;
    string album;
    int duracion;
    Cancion* pointer;
    Genero* generoPointer;

public:
    Cancion() {
        titulo = " ";
        album = " ";
        duracion = 0;
        pointer = nullptr;
        generoPointer = nullptr;
    }

    Cancion(string t, const vector<string>& a, string al, int d, Genero* g) {
        titulo = t;
        artistas = a;
        album = al;
        duracion = d;
        pointer = nullptr;
        generoPointer = g;
    }

    inline const string& get_titulo() const { return titulo; }
    inline const vector<string>& get_artistas() const { return artistas; }
    inline const string& get_album() const { return album; }
    inline int get_duracion() const { return duracion; }

    void set_titulo(const string& t) { titulo = t; }
    void set_artistas(const vector<string>& a) { artistas = a; }
    void set_album(const string& al) { album = al; }
    void set_duracion(int d) { duracion = d; }

    inline Genero* get_generoPointer() const { return generoPointer; }
    void set_generoPointer(Genero* g) { generoPointer = g; }

    Cancion* get_next() { return pointer; }
    void set_next(Cancion* c) { pointer = c; }

    Cancion& operator=(const Cancion& f) {
        set_titulo(f.titulo);
        set_artistas(f.artistas);
        set_album(f.album);
        set_duracion(f.duracion);
        return *this;
    }

    string to_string() const {
        stringstream ss;
        ss << "------------------------------------\n"
           << "|       " << titulo << "\n"
           << "|       ";
        for (const auto& artist : artistas) {
            ss << artist << ", ";
        }
        ss << "\n"
           << "|       " << album << "\n"
           << "|       Duracion: " << duracion << "s\n"
           << "|       Genero: " << generoPointer->get_nombre() << "\n"
           << "------------------------------------\n";
        return ss.str();
    }

    friend std::ostream& operator<<(std::ostream& os, Cancion& b) {
        return os << b.to_string();
    }
};

class Nodo {
    Genero* genero;
    Cancion* cancion;
    Nodo* pointer;
    Nodo* prev;
    int size;

public:
    Nodo() {
        genero = nullptr;
        cancion = nullptr;
        pointer = nullptr;
        prev = nullptr;
        size = 0;
    }

    ~Nodo() {
        delete cancion;
    }

    Nodo(Genero* g) : genero(g), cancion(nullptr), pointer(nullptr), prev(nullptr), size(0) {}

    Genero* get_dato() {
        return genero;
    }

    void set_dato(Genero* g) {
        genero = g;
    }

    Nodo* get_next() {
        return pointer;
    }

    Nodo* get_prev() {
        return prev;
    }

    void set_next(Nodo* p) {
        pointer = p;
    }

    void set_prev(Nodo* a) {
        prev = a;
    }

    void push_back(const string& t, const vector<string>& a, const string& al, int d, Genero* g) {
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

    Cancion* get(int i) {
        if (i < size && i >= 0) {
            Cancion* c = cancion;
            for (int x = 0; x < i; x++) {
                c = c->get_next();
            }
            return c;
        } else {
            if (size == 0) {
                cout << "La playlist está vacía";
            } else {
                cout << "La posicion no existe";
            }
            return nullptr;
        }
    }

    Cancion* get_genero(const string& d) {
        genero = new Genero(d);
        cout << "El género de la canción " << d << " es " << *get(0) << endl;
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

    friend std::ostream& operator<<(std::ostream& os, Nodo& b) {
        return os << b.to_string();
    }
};

class Playlist {
    unique_ptr<Nodo> ptr;
    int size;

public:
    Playlist() : ptr(nullptr), size(0) {}

    ~Playlist() {}

    void push_back(Genero* d) {
        if (size == 0) {
            ptr = make_unique<Nodo>(d);
            size++;
        } else {
            Nodo* t = ptr.get();
            while (t->get_next() != nullptr) {
                t = t->get_next();
            }
            t->set_next(new Nodo(d));
            size++;
        }
        cout << endl;
    }

    int getSize() const {
        return size;
    }

    void print() const {
        if (size == 0) {
            cout << "La lista está vacía" << endl;
        } else {
            Nodo* t = ptr.get();
            do {
                cout << (*t);
                t = t->get_next();
            } while (t != nullptr);
            cout << endl;
        }
    }

    Nodo* get(int i) const {
        if (i < size && i >= 0) {
            Nodo* n = ptr.get();
            for (int x = 0; x < i; x++) {
                n = n->get_next();
            }
            return n;
        } else {
            if (size == 0) {
                cout << "La playlist está vacía";
            } else {
                cout << "La posicion no existe";
            }
            return nullptr;
        }
    }

    void insert(Genero* p, int pos) {
        if (pos >= 0 && pos <= size) {
            if (size == 0 || pos == size) {
                push_back(p);
            } else {
                if (pos == 0) {
                    auto new_node = make_unique<Nodo>(p);
                    new_node->set_next(ptr.release());
                    ptr = move(new_node);
                } else {
                    Nodo* n = get(pos - 1);
                    n->set_next(new Nodo(p));
                }
                size++;
            }
        } else {
            cout << "La posicion no existe" << endl;
        }
    }

    void remove(int pos) {
        if ((pos >= 0 && pos < size) && size > 0) {
            if (pos == 0) {
                ptr.reset(ptr->get_next());
            } else {
                Nodo* t = get(pos - 1);
                Nodo* t2 = t->get_next();
                t->set_next(t2->get_next());
            }
            size--;
        } else {
            cout << "La posicion no existe o la lista está vacía" << endl;
        }
    }

    void readSongsFromFile(const string& filename, const string& gen_name) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Failed to open file: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            istringstream iss(line);
            string title, artists_str, album, genre;
            int duration;

            if (getline(iss, title, ',') &&
                getline(iss, artists_str, ',') &&
                getline(iss, album, ',') &&
                getline(iss, genre, ',') &&
                (iss >> duration)) {
                if (genre == gen_name) {
                    push_back(new Genero(gen_name));

                    // Parse artists
                    vector<string> artists;
                    stringstream artistsStream(artists_str);
                    string artist;
                    while (getline(artistsStream, artist, '&')) {
                        artists.push_back(artist);
                    }

                    // Add song to the playlist
                    get(getSize() - 1)->push_back(title, artists, album, duration, get(getSize() - 1)->get_dato());
                }
            } else {
                cerr << "Invalid format in line: " << line << endl;
            }
        }

        file.close();
    }

   /*void printGenero(const string& gen_name) {
    Nodo* current = ptr.get();
    bool found = false;
    while (current != nullptr) {
        if (current->get_dato()->get_nombre() == gen_name) {
            cout << (*current) << endl;
            found = true;
            break;
        }
        current = current->get_next();
    }
    if (!found) {
        cout << "Género '" << gen_name << "' no encontrado." << endl;
    }
}
*/

};

int main() {

    Playlist pl;
        int opcion;
        do {
            cout << "Selecciona un género para recibir recomendaciones musicales:" << endl;
            cout << "1. Rock" << endl;
            cout << "2. Pop" << endl;
            cout << "3. Reggaeton" << endl;
            cout << "4. Indie" <<endl;
            cout << "5. Folk" <<endl;
            cout << "6. R&B" <<endl;
            cout << "0. Salir" << endl;
            cout << "Opción: ";
            cin >> opcion;
    
            switch (opcion) {
                case 1:
                    pl.push_back(new Genero("Rock"));
                    pl.readSongsFromFile("songs.txt", "Rock");
                    break;
                case 2:
                    pl.push_back(new Genero("Pop"));
                    pl.readSongsFromFile("songs.txt", "Pop");
                    break;
                case 3:
                    pl.push_back(new Genero("Reggaeton"));
                    pl.readSongsFromFile("songs.txt", "Reggaeton");
                    break;
                case 4:
                    pl.push_back(new Genero("Indie"));
                    pl.readSongsFromFile("songs.txt", "Indie");
                    break;
                case 5:
                    pl.push_back(new Genero("Folk"));
                    pl.readSongsFromFile("songs.txt", "Folk");
                    break;
                case 6:
                    pl.push_back(new Genero("R&B"));
                    pl.readSongsFromFile("songs.txt", "R&B");
                    break;
                case 0:
                    cout << "Saliendo del programa..." << endl;
                    break;
                default:
                    cout << "Opción no válida. Por favor, seleccione nuevamente." << endl;
            }
            pl.print();
        } while (opcion != 0);
        return 0;

}
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
    Playlist pl = Playlist();
    pl.push_back(new Genero("Rock"));
    pl.push_back(new Genero("Pop"));
    pl.push_back(new Genero("Reggaeton"));
    // Leer canciones
    pl.readSongsFromFile("songs.txt", "Rock");
    pl.readSongsFromFile("songs.txt", "Pop");
    pl.readSongsFromFile("songs.txt", "Reggaeton");
    pl.print();
    return 0;
    */
