//ANTES
class FornoEletrico{
public:
    void AssarPizza() {
        std::cout << "Assando pizza no forno elétrico" << std::endl;
    }
};

class Restaurante {
    FornoEletrico forno;  
public:
    void PrepararPizza() {
        forno.AssarPizza();  // Só sabe usar forno elétrico
    }
};

//DEPOIS
class IForno {
public:
    virtual void Assar() = 0;
    virtual ~IForno() = default;
};

// Implementações concretas
class FornoEletrico : public IForno {
public:
    void Assar() override {
        std::cout << "Assando no forno elétrico" << std::endl;
    }
};

class FornoALenha : public IForno {
public:
    void Assar() override {
        std::cout << "Assando no forno a lenha" << std::endl;
    }
};

class FornoVapor : public IForno {
public:
    void Assar() override {
        std::cout << "Cozinhando no forno a vapor" << std::endl;
    }
};

class Restaurante {
    IForno& forno;  
public:
    Restaurante(IForno& f) : forno(f) {}

    void PrepararPrato() {
        forno.Assar();  // Usa qualquer forno
    }
};
