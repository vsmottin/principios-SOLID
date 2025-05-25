//ANTES
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


// DEPOIS
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

