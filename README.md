# Princípios de Projeto

Repositório para atividade de **Engenharia de Software – UTFPR campus Campo Mourão (2025/1)**.
* **Acadêmica:** Victória S. Mottin
* **Professor:** Reginaldo Ré

## 1 – Single Responsibility Principle (SRP)

* O princípio da responsabilidade única estabelece que toda classe deve possuir uma única responsabilidade e assim, um único motivo para mudar.
* Recomenda-se a divisão do sistema em classes de apresentação e classes de implementação, promovendo a separação de interesses e responsabilidades.
* **Vantagens:** Resulta em um código mais coeso, menor, legível, fácil de testar e com baixo acoplamento.

---

### Exemplo

Para ilustrar, a classe `Pedido` inicialmente acumulava responsabilidades de cálculo do total do pedido e persistência, acessando e salvando as informações do pedido no banco de dados. O SRP recomenda reestruturar o código de modo a separar essas responsabilidades em classes distintas, fazendo com que o cálculo do total, um atributo essencial ao pedido, seja responsabilidade da própria classe e o acesso ao banco seja dado como responsabilidade de outra `PedidoRepository`.

- Antes:

```cpp
class Pedido {
private:
    std::vector<std::string> itens;

public:
    Pedido(const std::vector<std::string>& itens) : itens(itens) {}

    // Responsabilidade 1: Calcular total
    double calcularTotal() {
        return itens.size() * 100;
    }

    // Responsabilidade 2: Salvar no banco de dados
    void salvarNoBanco() {
        std::cout << "Pedido salvo no banco de dados." << std::endl;
    }
};
```

- Depois:

```cpp
// Classe 1: Responsável apenas pelos dados e cálculos do pedido
class Pedido {
private:
    std::vector<std::string> itens;

public:
    Pedido(const std::vector<std::string>& itens) : itens(itens) {}

    double calcularTotal() const {
        return itens.size() * 100;
    }

    std::vector<std::string> getItens() const {
        return itens;
    }
};


// Classe 2: Responsável apenas por persistência
class PedidoRepository {
public:
    void salvar(const Pedido& pedido) {
        std::cout << "Pedido salvo no banco: Total R$" << pedido.calcularTotal() << std::endl;
    }
};
```

---

## 2 – Dependency Inversion Principle (DIP)

* O princípio da inversão de dependência indica que é preferível estabelecer relações de dependência com abstrações (interfaces) ao invés de classes concretas.
* **Vantagens:** Facilita a troca de implementações e a extensão do sistema, além de possibilitar testes com objetos que ainda não foram implementados (mocks).

---

### Exemplo 

A classe `Restaurante` tem uma dependência direta a um objeto `FornoEletrico`, o qual é utilizado no método `PrepararPizza()` e restringe a forma em que o método funciona, ou seja, só se pode preparar pizza com este forno elétrico. O DIP introduz uma abstração que torna `Restaurante` uma classe muito mais flexível, de modo a poder implementar diferentes tipos de fornos que podem realizar a mesma ação por possuírem a mesma interface.

- Antes:

```cpp
class FornoEletrico{
public:
    void AssarPizza() {
        std::cout << "Assando pizza no forno elétrico" << std::endl;
    }
};

class Restaurante {
    FornoEletrico forno;  // Dependência fixa
public:
    void PrepararPizza() {
        forno.AssarPizza();  // Só sabe usar forno elétrico
    }
};
```

- Depois:

```cpp
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
    IForno& forno;  // Depende da abstração
public:
    Restaurante(IForno& f) : forno(f) {}

    void PrepararPrato() {
        forno.Assar();  // Usa qualquer forno
    }
};
```

---

## 3 – Prefira Composição a Herança

* O princípio de preferência de composição a herança sugere a reutilização de objetos por meio da composição (montagem) em vez da criação de hierarquias de herança extensas.
* **Vantagens:** Resulta em estruturas mais flexíveis, permite a combinação de comportamentos em tempo de execução e evita o problema da classe base frágil, onde alterações na classe ancestral podem impactar inesperadamente as classes descendentes.

---

### Exemplo

A classe `Personagem` define um modelo do participante em um sistema que usa herança para definir habilidades como atacar e defender, fazendo com que cada um possua um método de cada tipo de ação que é somente substituído de acordo com o personagem. A composição que é aplicada no lugar da herança permite uma flexibilidade muito maior na combinação dessas habilidades para cada um, de modo que se tornam possíveis vários tipos de ataque e de defesa para personagens diferentes, assim como a possibilidade de existirem personagens que não atacam ou defendem. Adicionar novas habilidades não interfere na classe `Personagem`.

- Antes:

```cpp
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

```

- Depois:

```cpp
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

// Personagem agora "possui" habilidades através de composição
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

```

---

## 4 – Princípio de Demeter 

* O princípio de Demeter propõe que um objeto deve interagir apenas com ele mesmo, seus campos, os argumentos recebidos ou os objetos que ele cria. Seu objetivo é fazer com que cada objeto tenha o mínimo de conhecimento possível sobre os outros que não estão a ele relacionados.
* Tem como finalidade a redução de cadeias de chamadas excessivas, como em `a.getB().getC().getD()`.
* **Vantagens:** Reduz acoplamento entre partes separadas, diminuindo dependências e auxiliando na modularização e encapsulamento de objetos do sistema.

---

### Exemplo:

Abaixo pode ser vista uma implementação em que a recuperação do atributo nome de uma classe `Cliente` envolve uma cadeia de chamadas envolvendo os objetos `Pedido` e `Endereco` (`enderecoEntrega.getCliente().getNome()`), fazendo com que informações da estrutura interna dos objetos sejam expostas sem necessidade e caso haja alguma mudança em `getCliente()`, por exemplo, o método pare de funcionar. O princípio visa simplificar essa sequência, promovendo um menor acoplamento através da criação do método `getNomeDoClienteDoPedido()` que relaciona o pedido com seu próprio endereço e não "conhece" `Cliente`.

- Antes:

```cpp
class Cliente {
public:
    std::string getNome() {
        return "João";
    }
};

class Endereco {
public:
    Cliente& getCliente() {
        static Cliente cliente; 
        return cliente;
    }
};

class Pedido {
private:
    Endereco enderecoEntrega; 

public:
    std::string getNomeCliente() {
        return enderecoEntrega.getCliente().getNome(); 
    }
};
```

- Depois:

```cpp
class Cliente {
public:
    std::string getNome() {
        return "João";
    }
};

class Endereco {
private:
    Cliente clienteAssociado; 

public:
    Endereco(const Cliente& cli) : clienteAssociado(cli) {} 

    std::string getNomeClienteAssociado() {
        return clienteAssociado.getNome(); // Endereço mostra apenas o nome do cliente
    }
};

class Pedido {
private:
    Endereco enderecoEntrega;

public:
    Pedido(const Endereco& end) : enderecoEntrega(end) {}

    std::string getNomeDoClienteDoPedido() {
        return enderecoEntrega.getNomeClienteAssociado(); 
    }
};
```
