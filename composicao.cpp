//ANTES
class Personagem {
public:
    virtual void atacar() = 0;
    virtual void defender() = 0;
};

class Guerreiro : public Personagem {
public:
    void atacar() override {
        std::cout << "Guerreiro ataca com espada!" << std::endl;
    }
    void defender() override {
        std::cout << "Guerreiro defende com escudo!" << std::endl;
    }
};

class Mago : public Personagem {
public:
    void atacar() override {
        std::cout << "Mago lança feitiço!" << std::endl;
    }
    void defender() override {
        std::cout << "Mago conjura barreira mágica!" << std::endl;
    }
};

//DEPOIS
// Interfaces para as habilidades
class HabilidadeAtaque {
public:
    virtual void atacar() = 0;
    virtual ~HabilidadeAtaque() = default;
};

class HabilidadeDefesa {
public:
    virtual void defender() = 0;
    virtual ~HabilidadeDefesa() = default;
};

// Implementações concretas 
class AtaqueEspada : public HabilidadeAtaque {
public:
    void atacar() override {
        std::cout << "Ataca com espada!" << std::endl;
    }
};

class AtaqueFeitico : public HabilidadeAtaque {
public:
    void atacar() override {
        std::cout << "Lança feitiço!" << std::endl;
    }
};

class DefesaEscudo : public HabilidadeDefesa {
public:
    void defender() override {
        std::cout << "Defende com escudo!" << std::endl;
    }
};

class DefesaBarreira : public HabilidadeDefesa {
public:
    void defender() override {
        std::cout << "Conjura barreira mágica!" << std::endl;
    }
};

class Personagem {
private:
    HabilidadeAtaque* ataque;
    HabilidadeDefesa* defesa;

public:
    Personagem(HabilidadeAtaque* atk, HabilidadeDefesa* def) : ataque(atk), defesa(def) {}

    void realizarAtaque() {
        if (ataque) {
            ataque-> atacar();
        }
    }

    void realizarDefesa() {
        if (defesa) {
            defesa-> defender();
        }
    }
};
