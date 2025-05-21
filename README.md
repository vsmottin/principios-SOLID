# Princípios de Projeto

Repositório para atividade de **Engenharia de Software – UTFPR campus Campo Mourão (2025/1)**.  
**Acadêmica:** Victória S. Mottin | **Professor:** Reginaldo Ré

## 1 – Single Responsibility Principle (SRP)

* **O que é?** Uma classe deve ter **apenas um motivo para mudar**.  
* **Para que serve?** Código menor, mais legível, fácil de testar e com baixo acoplamento.  
* **Exemplo** (`src/responsabilida_unica`):  
  * Antes: `` 
  * Depois:  ``

---

## 2 – Dependency Inversion Principle (DIP)

* **O que é?** Módulos de alto nível dependem de abstrações (interfaces), não de classes concretas.  
* **Para que serve?** Facilita trocar implementações e fazer testes com objetos ainda não implementados (mocks).  
* **Exemplo** (`src/inversao_dependencia`):  
  * 

---

## 3 – Prefira Composição a Herança

* **O que é?** Reutilizar comportamento compondo objetos em vez de criar grandes hierarquias de herança.  
* **Para que serve?** Estruturas mais flexíveis; combina comportamentos em tempo de execução; evita o problema da classe base frágil.  
* **Exemplo** (`src/composicao`):
  *

---

## 4 – Princípio de Demeter (Lei do Menor Conhecimento)

* **O que é?** Um objeto deve interagir só com: ele mesmo, seus campos, argumentos ou objetos que cria.  
* **Para que serve?** Reduz cadeias de chamadas longas (`a.getB().getC().getD()`) e o acoplamento entre partes do sistema.  
* **Exemplo** (`src/demeter`):  
  * Antes: ``
  * Depois: ``



