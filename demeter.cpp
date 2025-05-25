//ANTES
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

//DEPOIS
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
        return clienteAssociado.getNome(); 
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
