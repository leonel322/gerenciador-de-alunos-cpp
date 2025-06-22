#include <iostream>
#include <fstream>

using namespace std;

struct aluno{
    string nome;
    float nota1;
    float nota2;
    float media;
    string situacao;
};
float lerOpcao(int min, int max, const string &mensagemErro, string mensagemAviso = "Opcao invalida");
bool alunoExiste(const aluno (&listaAluno)[100], int posicaoAtual, const string &nome);
void exibirDadosAluno(const aluno (&listaAluno)[100], int indice);
void calcularMedia(aluno (&listaAluno)[100], int indice);
void cadastrarAluno(aluno (&listaAluno)[100], int & posicaoAtual);
void salvarAluno(aluno (&listaAluno)[100], int  posicaoAtual);
void carregarAluno(aluno (& listaAluno)[100], int & posicaoAtual);
int procurarAluno(const aluno (&listaAluno)[100], int  posicaoAtual);
void alterarNotaAluno(aluno (&listaAluno)[100], int posicaoAtual);
void listarTodosAlunos(const aluno(&listaAluno)[100], int posicaoAtual);
void mostrarMediaTurma(const aluno(&listaAluno)[100], int posicaoAtual);
void filtrarAluno(const string &tipo, const aluno(& listaAluno)[100], int posicaoAtual);

int main(){
    const int tamanho_maximo = 100;
    aluno listaAluno[tamanho_maximo];
    int opcao1;
    int opcao2;
    bool execucao = true;
    int posicaoAtual = 0;
    
    carregarAluno(listaAluno, posicaoAtual);
    
    while (execucao){
        cout << "Seja bem vindo ao sistema de gerenciamento de alunos\n";
        cout << "1- Adicionar novo aluno\n";
        cout << "2- Procurar aluno pelo nome\n";
        cout << "3- Alterar nota de um aluno\n";
        cout << "4- Listar todos os alunos\n";
        cout << "5- Media da turma\n";
        cout << "6- Sair do programa\n";
        opcao1 = lerOpcao(1, 6, "Selecione uma das opcoes");
        
        if(opcao1 > 1 && opcao1 < 6){
            if (posicaoAtual == 0){
                cout << "Nenhum aluno cadastrado\n";
                continue;
            }
        }
        
        switch (opcao1){
            case 1:
                cadastrarAluno(listaAluno, posicaoAtual);
                break;
            case 2:
                procurarAluno(listaAluno, posicaoAtual);
                break;
            case 3:
                alterarNotaAluno(listaAluno, posicaoAtual);
                break;
            case 4:
                listarTodosAlunos(listaAluno, posicaoAtual);
                break;
            case 5:
                mostrarMediaTurma(listaAluno, posicaoAtual);
                break;
            case 6:
                cout << "deseja sair do programa? (1- sim 2- nao)\n";
                opcao2 = lerOpcao(1, 2, "deseja sair do programa? (1- sim 2- nao)");
                if(opcao2 == 1){
                    execucao = false;
                    cout <<"Encerrando o programa\n";
                }
        }         
    }
    return 0;
}


float lerOpcao (int min, int max, const string &mensagemErro, string mensagemAviso){
    int opcao;
    while(!(cin >> opcao) || opcao < min || opcao > max){
        cin.clear();
        cin.ignore(1000, '\n');
        cout << mensagemAviso << endl << mensagemErro << endl;
    }
    cin.clear();
    cin.ignore(1000, '\n'); 
    return opcao;
}

bool alunoExiste(const aluno (&listaAluno)[100], int posicaoAtual, const string &nome){
   
    for(int i = 0; i < posicaoAtual; i++){
        if (nome == listaAluno[i].nome){
            cout << "Aluno ja cadastrado\n";
            return true;
        }
    }           
    return false;
}
void exibirDadosAluno(const aluno (&listaAluno)[100], int indice){
    
    cout << "\nAluno numero: "<< indice + 1 << endl;
    cout << "Nome...................: "<< listaAluno[indice].nome << endl;
    cout << "Primeira nota.......: "<< listaAluno[indice].nota1 << endl;
    cout << "Segunda nota......: "<< listaAluno[indice].nota2 << endl;
    cout << "Media do aluno...: " << listaAluno[indice].media << endl;
    cout << "Situacao do aluno: " << listaAluno[indice].situacao << endl;
    
}

void calcularMedia(aluno (&listaAluno)[100], int indice){
    float nota1 = listaAluno[indice].nota1;
    float nota2 = listaAluno[indice].nota2;
    
    listaAluno[indice].media = (nota1 + nota2) / 2;
    if (listaAluno[indice].media < 5){
        listaAluno[indice].situacao = "Reprovado";
    }else{
        listaAluno[indice].situacao = "Aprovado";
    }
    
    return;
    
}


void cadastrarAluno(aluno (&listaAluno)[100], int & posicaoAtual){
    string nome;
    float nota1;
    float nota2;
    int opcao;
    bool achou;
    
    if (posicaoAtual == 100){
        cout << "Máximo de alunos cadastrados alcançado por favor elimine algum aluno antes de cadastrar outro\n";
        return;
    }
    cout << "Aluno numero: " << posicaoAtual + 1 << endl;
    cout << "Digite o nome do aluno\n";
    getline(cin, nome);
    achou = alunoExiste(listaAluno, posicaoAtual, nome);
    if(achou){
        return;
    }
    cout << "Digite a primeira nota do aluno\n";
    nota1 = lerOpcao(0, 10, "A nota do aluno tem que ser de 0 a 10");
    cout << "Digite a segundo nota do aluno\n";
    nota2 = lerOpcao(0, 10, "A nota do aluno tem que ser de 0 a 10");
    
    cout << "Dados do aluno novo:\n";
    cout << "Nome: "<< nome << endl;
    cout << "Primeira nota: " << nota1 << endl;
    cout << "Segunda nota: " << nota2 << endl;
    cout << "Deseja guarda registrar o aluno?(1-sim 2 -nao)\n";
    opcao = lerOpcao(1, 2, "Deseja registrar o aluno?(1-sim 2 -nao)");
    if (opcao == 2){
        return;
        }
    listaAluno[posicaoAtual].nome = nome;
    listaAluno[posicaoAtual].nota1 = nota1;
    listaAluno[posicaoAtual].nota2 = nota2;
    calcularMedia(listaAluno, posicaoAtual);
    posicaoAtual++;
    salvarAluno(listaAluno, posicaoAtual);
    cout << "Usuario cadastrado com sucesos\n";
    
    
}

void salvarAluno(aluno (& listaAluno)[100], int posicaoAtual){
    ofstream abrirArquivo("Alunos cadastrados.txt");
    if(!abrirArquivo.is_open()){
        cerr << "O programa nao conseguiu abrir o ficheiro \n";
        return;
    }
    for(int i = 0; i < posicaoAtual; i++){
        abrirArquivo << listaAluno[i].nome << endl;
        abrirArquivo << listaAluno[i].nota1 << endl;
        abrirArquivo << listaAluno[i].nota2 << endl;
        abrirArquivo << listaAluno[i].media << endl;
        abrirArquivo << listaAluno[i].situacao << endl;
        abrirArquivo << "----------------------------\n";
    }  
    abrirArquivo.close();  
}

void carregarAluno(aluno (&listaAluno)[100], int &posicaoAtual) {
    ifstream carregarArquivo("Alunos cadastrados.txt");
    if (!carregarArquivo.is_open()) {
        cerr << "O programa nao conseguiu abrir o arquivo\n";
        return;
    }

    string linha;
    while (getline(carregarArquivo, linha)) {
   
        listaAluno[posicaoAtual].nome = linha;
        
        if (!getline(carregarArquivo, linha)) break;
        listaAluno[posicaoAtual].nota1 = stoi(linha);
        
        if (!getline(carregarArquivo, linha)) break;
        listaAluno[posicaoAtual].nota2 = stoi(linha);
        
        if (!getline(carregarArquivo, linha)) break;
        listaAluno[posicaoAtual].media = stof(linha);
     
        if (!getline(carregarArquivo, linha)) break;
        listaAluno[posicaoAtual].situacao = linha;
        
        if (!getline(carregarArquivo, linha)) break;
        
        posicaoAtual++;
        
    }
    carregarArquivo.close();
}

int procurarAluno(const aluno (&listaAluno)[100], int posicaoAtual){
    string buscarNome;
   
    cout << "Digite o nome do aluno\n";
    getline(cin, buscarNome);
    for(int i = 0; i < posicaoAtual; i++){
        if(buscarNome == listaAluno[i].nome){
            exibirDadosAluno(listaAluno, i);
            return i;
        }        
    }
    cout << "Aluno nao encontrado\n"; 
    return -1;
}


void alterarNotaAluno(aluno (&listaAluno)[100], int posicaoAtual){
    int indice;
    float opcao1;
    float novaNota1;
    float novaNota2;
    bool apenasNota1 = false;
    bool apenasNota2 = false;
    
    indice = procurarAluno(listaAluno, posicaoAtual);
    if (indice == -1){
        return;
    }
    
    cout << "1- Alterar todas as notas\n";
    cout << "2- Alterar apenas a primeira nota\n";
    cout << "3- Alterar apenas a segunda nota\n";
    cout << "4- Voltar\n";
    opcao1 = lerOpcao(1, 4, "escolha uma das opcoes");
    
    if(opcao1 == 1){
        apenasNota1 = true;
        apenasNota2 = true;
    }else if(opcao1 == 2){
        apenasNota1 = true;
    }else if(opcao1 == 3){
        apenasNota2 = true;
    }else{
        return;
    }  
    if(apenasNota1){
        cout << "Digite a primeira nota: \n";
        novaNota1 = lerOpcao(0, 10, "A nota do aluno tem que ser de 0 a 10");
        listaAluno[indice].nota1 = novaNota1;
    }
    if(apenasNota2){
        cout << "Digite a segunda nota: \n";
        novaNota2 = lerOpcao(0, 10, "A nota do aluno tem que ser de 0 a 10");
        listaAluno[indice].nota2 = novaNota2;
    }
    
    calcularMedia(listaAluno, indice);
    salvarAluno(listaAluno, posicaoAtual);
    cout << "As notas foram alteradas\n";
}

void listarTodosAlunos(const aluno(&listaAluno)[100], int posicaoAtual){
    
    for(int i =0; i < posicaoAtual; i++){
        exibirDadosAluno(listaAluno, i);
        cout << "\n";
    } 
}

void mostrarMediaTurma(const aluno(&listaAluno)[100], int posicaoAtual){
    string situacao;
    int opcao1;
    float mediaTotal = 0;
    for(int i = 0; i < posicaoAtual; i++){
            mediaTotal += listaAluno[i].media;
    }
    mediaTotal /= posicaoAtual;

    if(mediaTotal < 5){
        situacao = "A turma esta abaixo da media positiva ";
    }else if(mediaTotal < 8.5){
        situacao= "A turma esta aceitavel na media";
    }else{
        situacao = "A turma esta com uma media alta";
    }
    cout << "Quantidade de alunos na turma: " << posicaoAtual << endl;
    cout << "Media total da turma: " << mediaTotal<< endl;
    cout << "situacao: " << situacao << endl;
    
    cout << "\n1- Ver todos os alunos Aprovados";
    cout << "\n2- Ver todos os alunos reprovados";
    cout << "\n3- Voltar\n";
    opcao1 = lerOpcao(1, 3, "Escolha uma das opcoes");
    switch(opcao1){
        case 1:
            filtrarAluno("Aprovados", listaAluno, posicaoAtual);
            break;
        case 2:
            filtrarAluno("Reprovados", listaAluno, posicaoAtual);
            break;
    }
    
}

void filtrarAluno(const string &tipo, const aluno(& listaAluno)[100], int posicaoAtual){
    
    if(tipo == "Aprovados"){
        for(int i = 0; i < posicaoAtual; i++){
            if(listaAluno[i].situacao == "Aprovado"){
               cout << "\nNumero do aluno: " << i + 1 << endl;
               cout << "Nome: " << listaAluno[i].nome << endl;
               cout << "Media: " << listaAluno[i].media << endl;
               cout << "Estado: " << listaAluno[i].situacao << endl;
            }
        }
    }else{
        for(int i = 0; i < posicaoAtual; i++){
            if(listaAluno[i].situacao == "Reprovado"){
               cout << "\nNumero do aluno: " << i + 1 << endl;
               cout << "Nome: " << listaAluno[i].nome << endl;
               cout << "Media: " << listaAluno[i].media << endl;
               cout << "Estado: " << listaAluno[i].situacao << endl;
            }
        }
    }
}