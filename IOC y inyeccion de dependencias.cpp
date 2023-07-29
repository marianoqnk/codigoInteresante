/* Ejemplo sacado de :https://es.stackoverflow.com/questions/575291/c%C3%B3mo-aplicar-el-principio-de-inversi%C3%B3n-de-dependencias-en-c*/
include <iostream>

class IPersistence{
public:
    virtual void save(int entity)    = 0;
    virtual int get(int id)          = 0;
    virtual void update(int entity)  = 0;
    virtual void delete_(int entity) = 0;
    virtual ~IPersistence() = default;
};

class Sqlite : public IPersistence{
public:
    void save(int entity) override{
        std::cout<<"el dato "<<entity<<" se ha guardado en la base de datos sqlite\n";
    }
    int get(int id) override{
        return id;
    }
    void update(int entity) override{
        std::cout<<"el dato "<<entity<<" se ha actualizado en la base de datos sqlite\n";
    }
    void delete_(int entity) override{
        std::cout<<"el dato "<<entity<<" se ha eliminado de la base de datos sqlite\n";
    }
};

class MySql : public IPersistence{
public:
    void save(int entity) override{
        std::cout<<"el dato "<<entity<<" se ha guardado en la base de datos mysql\n";
    }
    int get(int id) override{
        return id;
    }
    void update(int entity) override{
        std::cout<<"el dato "<<entity<<" se ha actualizado en la base de datos mysql\n";
    }
    void delete_(int entity) override{
        std::cout<<"el dato "<<entity<<" se ha eliminado de la base de datos mysql\n";
    }
};

class DataBase{
    IPersistence *dataBase_;
public:
    DataBase(IPersistence *dataBase):dataBase_{dataBase}{};
    ~DataBase(){ delete dataBase_; }

    void save(int entity)   { dataBase_->save(entity);    }
    int get(int id)         { return dataBase_->get(id);  }
    void update(int entity) { dataBase_->update(entity);  }
    void delete_(int entity){ dataBase_->delete_(entity); }
};

int main(){
    DataBase db(new MySql);

    db.save(12345);

    return 0;
}

/* Respuesta*/

#include <iostream>
#include <string>

class Sqlite {
public:
    using type = int;
    void save(int entity) {
        std::cout << "el dato " << entity << " se ha guardado en la base de datos sqlite\n";
    }
    int get(int id) {
        return id;
    }
    void update(int entity) {
        std::cout << "el dato " << entity << " se ha actualizado en la base de datos sqlite\n";
    }
    void delete_(int entity) {
        std::cout << "el dato " << entity << " se ha eliminado de la base de datos sqlite\n";
    }
};

class MySql {
public:
    using type = std::string;
    void save(std::string entity) {
        std::cout << "el dato " << entity << " se ha guardado en la base de datos mysql\n";
    }
    std::string get(int id) {
        return "datos de la entidad con id " + std::to_string(id);
    }
    void update(std::string entity) {
        std::cout << "el dato " << entity << " se ha actualizado en la base de datos mysql\n";
    }
    void delete_(std::string entity) {
        std::cout << "el dato " << entity << " se ha eliminado de la base de datos mysql\n";
    }
};

template<class T>
class DataBase{
    using type = typename T::type;
    T& dataBase_;
public:
    // sinceramente no veo buena idea que pases un puntero al 
    // constructor de database y luego esta en su destructor haga
    // delete de el, ya que no es database quien crea la memoria
    // al cual apunta el puntero, una referencia esta bien, la memoria
    // se crea y destruye automáticamente
    DataBase(T& dataBase) : dataBase_{ dataBase } { };
    //~DataBase(){ delete dataBase_; }

    void save(type entity)   { dataBase_.save(entity);    }
    type get(int id)         { return dataBase_.get(id);  }
    void update(type entity) { dataBase_.update(entity);  }
    void delete_(type entity){ dataBase_.delete_(entity); }
};

int main(){
    Sqlite sqlite { };
    DataBase<Sqlite> db1(sqlite);
    db1.save(12345); // el dato 12345 se ha guardado en la base de datos sqlite

    MySql mysql { };
    DataBase<MySql> db2(mysql);
    db2.save("54321"); // el dato 54321 se ha guardado en la base de datos mysql

    return 0;
}