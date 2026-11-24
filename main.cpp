#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// ==========================================
// CLASSE BASE: PESSOA
// ==========================================
class Pessoa
{
protected:
    string nome;
    string cpf;
    string telefone;
    string email;

public:
    Pessoa(string nome, string cpf, string telefone, string email)
    {
        this->nome = nome;
        this->cpf = cpf;
        this->telefone = telefone;
        this->email = email;
    }

    virtual ~Pessoa() {}

    // Metodo virtual puro (torna Pessoa abstrata)
    virtual void exibirDados() const = 0;
};

// ==========================================
// CLASSE PROFESSOR
// Herda de Pessoa
// ==========================================
class Professor : public Pessoa
{
private:
    string matricula;
    string areaEnsino;

public:
    Professor(string nome, string cpf, string telefone,
              string email, string matricula, string areaEnsino)
        : Pessoa(nome, cpf, telefone, email)
    {
        this->matricula = matricula;
        this->areaEnsino = areaEnsino;
    }

    void exibirDados() const override
    {
        cout << "\n========== PROFESSOR ==========\n";
        cout << "Nome: " << nome << endl;
        cout << "CPF: " << cpf << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "E-mail: " << email << endl;
        cout << "Matricula: " << matricula << endl;
        cout << "Area de ensino: " << areaEnsino << endl;
    }

    void ministrarAula() const
    {
        cout << "Professor(a) " << nome << " (" << matricula
             << ") esta ministrando aula de " << areaEnsino << ".\n";
    }

    void consultarTurmas() const
    {
        cout << "Professor(a) " << nome << " (" << matricula
             << ") consultou suas turmas de " << areaEnsino << ".\n";
    }
};

// ==========================================
// CLASSE ALUNO
// Herda de Pessoa
// ==========================================
class Aluno : public Pessoa
{
private:
    string matricula;
    string curso;
    string periodo;

public:
    Aluno(string nome, string cpf, string telefone,
          string email, string matricula, string curso, string periodo)
        : Pessoa(nome, cpf, telefone, email)
    {
        this->matricula = matricula;
        this->curso = curso;
        this->periodo = periodo;
    }

    void exibirDados() const override
    {
        cout << "\n============ ALUNO ============\n";
        cout << "Nome: " << nome << endl;
        cout << "CPF: " << cpf << endl;
        cout << "Telefone: " << telefone << endl;
        cout << "E-mail: " << email << endl;
        cout << "Matricula: " << matricula << endl;
        cout << "Curso: " << curso << endl;
        cout << "Periodo: " << periodo << endl;
    }

    void realizarMatricula() const
    {
        cout << "Aluno(a) " << nome << " (" << matricula
             << ") realizou matricula no curso " << curso
             << " (" << periodo << ").\n";
    }

    void consultarNotas() const
    {
        cout << "Aluno(a) " << nome << " (" << matricula
             << ") consultou suas notas do curso " << curso << ".\n";
    }
};

// ==========================================
// CLASSE ESCOLA
// ==========================================
class Escola
{
private:
    string nome;
    string endereco;
    string telefone;
    vector<Pessoa *> pessoas;

public:
    Escola(string nome, string endereco, string telefone)
    {
        this->nome = nome;
        this->endereco = endereco;
        this->telefone = telefone;
    }

    // Impede copia para evitar dupla liberacao de memoria
    Escola(const Escola &) = delete;
    Escola &operator=(const Escola &) = delete;

    ~Escola()
    {
        for (Pessoa *pessoa : pessoas)
        {
            delete pessoa;
        }
        pessoas.clear();
    }

    void cadastrarAluno(Aluno *aluno)
    {
        pessoas.push_back(aluno);
        cout << "\nAluno cadastrado com sucesso!\n";
    }

    void cadastrarProfessor(Professor *professor)
    {
        pessoas.push_back(professor);
        cout << "\nProfessor cadastrado com sucesso!\n";
    }

    void listarPessoas() const
    {
        cout << "\n================================\n";
        cout << "CADASTRO DA ESCOLA: " << nome << "\n";
        cout << "================================\n";
        for (const Pessoa *pessoa : pessoas)
        {
            pessoa->exibirDados();
        }
        if (pessoas.empty())
        {
            cout << "Nenhuma pessoa cadastrada.\n";
        }
    }

    void listarAlunos() const
    {
        cout << "\n======= LISTA DE ALUNOS =======\n";
        bool encontrou = false;
        for (const Pessoa *pessoa : pessoas)
        {
            const Aluno *aluno = dynamic_cast<const Aluno *>(pessoa);
            if (aluno != nullptr)
            {
                aluno->exibirDados();
                encontrou = true;
            }
        }
        if (!encontrou)
        {
            cout << "Nenhum aluno cadastrado.\n";
        }
    }

    void listarProfessores() const
    {
        cout << "\n===== LISTA DE PROFESSORES =====\n";
        bool encontrou = false;
        for (const Pessoa *pessoa : pessoas)
        {
            const Professor *professor = dynamic_cast<const Professor *>(pessoa);
            if (professor != nullptr)
            {
                professor->exibirDados();
                encontrou = true;
            }
        }
        if (!encontrou)
        {
            cout << "Nenhum professor cadastrado.\n";
        }
    }

    void executarAcoesAlunos() const
    {
        cout << "\n======= ACOES DOS ALUNOS =======\n";
        bool encontrou = false;
        for (const Pessoa *pessoa : pessoas)
        {
            const Aluno *aluno = dynamic_cast<const Aluno *>(pessoa);
            if (aluno != nullptr)
            {
                aluno->realizarMatricula();
                aluno->consultarNotas();
                encontrou = true;
            }
        }
        if (!encontrou)
        {
            cout << "Nenhum aluno cadastrado.\n";
        }
    }

    void executarAcoesProfessores() const
    {
        cout << "\n===== ACOES DOS PROFESSORES ====\n";
        bool encontrou = false;
        for (const Pessoa *pessoa : pessoas)
        {
            const Professor *professor = dynamic_cast<const Professor *>(pessoa);
            if (professor != nullptr)
            {
                professor->ministrarAula();
                professor->consultarTurmas();
                encontrou = true;
            }
        }
        if (!encontrou)
        {
            cout << "Nenhum professor cadastrado.\n";
        }
    }
};

// ==========================================
// FUNCAO AUXILIAR PARA LER TEXTOS
// ==========================================
string lerTexto(string mensagem)
{
    string valor;
    cout << mensagem;
    getline(cin, valor);
    return valor;
}

// ==========================================
// FUNCAO PRINCIPAL (MENU INTERATIVO)
// ==========================================
int main()
{
    Escola escola("Escola do Saber", "Rua Principal, 100", "(11) 3333-4444");
    int opcao = -1;

    do
    {
        cout << "\n================================\n";
        cout << "   SISTEMA - ESCOLA DO SABER\n";
        cout << "================================\n";
        cout << "1. Cadastrar Aluno\n";
        cout << "2. Cadastrar Professor\n";
        cout << "3. Listar Todas as Pessoas\n";
        cout << "4. Listar Alunos\n";
        cout << "5. Listar Professores\n";
        cout << "6. Executar Acoes de Alunos (Matricula e Notas)\n";
        cout << "7. Executar Acoes de Professores (Aula e Turmas)\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";

        if (!(cin >> opcao))
        {
            if (cin.eof())
            {
                cout << "\nEntrada encerrada.\n";
                break;
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcao = -1;
            cout << "\nEntrada invalida! Digite um numero.\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (opcao == 1)
        {
            cout << "\n--- Cadastro de Aluno ---\n";
            string nome = lerTexto("Nome: ");
            string cpf = lerTexto("CPF: ");
            string telefone = lerTexto("Telefone: ");
            string email = lerTexto("E-mail: ");
            string matricula = lerTexto("Matricula: ");
            string curso = lerTexto("Curso: ");
            string periodo = lerTexto("Periodo: ");

            escola.cadastrarAluno(new Aluno(nome, cpf, telefone, email, matricula, curso, periodo));
        }
        else if (opcao == 2)
        {
            cout << "\n--- Cadastro de Professor ---\n";
            string nome = lerTexto("Nome: ");
            string cpf = lerTexto("CPF: ");
            string telefone = lerTexto("Telefone: ");
            string email = lerTexto("E-mail: ");
            string matricula = lerTexto("Matricula: ");
            string areaEnsino = lerTexto("Area de ensino: ");

            escola.cadastrarProfessor(new Professor(nome, cpf, telefone, email, matricula, areaEnsino));
        }
        else if (opcao == 3)
        {
            escola.listarPessoas();
        }
        else if (opcao == 4)
        {
            escola.listarAlunos();
        }
        else if (opcao == 5)
        {
            escola.listarProfessores();
        }
        else if (opcao == 6)
        {
            escola.executarAcoesAlunos();
        }
        else if (opcao == 7)
        {
            escola.executarAcoesProfessores();
        }
        else if (opcao == 0)
        {
            cout << "\nEncerrando o sistema...\n";
        }
        else
        {
            cout << "\nOpcao invalida! Tente novamente.\n";
        }

    } while (opcao != 0);

    return 0;
}