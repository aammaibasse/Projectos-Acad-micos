#include<iostream>
#include<conio.h>
#include<cstring>
#define T 100
using namespace std;
class dPessoalC
{public:
/*Definicao dos setters*/
	void setNome(char *x){	toupper(*x);	strcpy(nome,x);	}
	void setGen(char x){ 	if(x=='m'||x=='M') gen="Masculino"; gen="Femenino ";	}
	void setBi(string x){	bi=x;	}
	void setTel(int x){		tel=x;	}
/*Definicao dos getters*/
	string getNome(){	return nome; }
	string getGen(){	return gen;	 }
	string getBi(){		return bi;	 }
	int getTel(){		return tel;	 }
	
private:
	char nome[16];
	string gen;
	string bi;
	int tel;

};
class dBancarios: public dPessoalC
{public:
	dBancarios(){
		dep=0;
		lev=0;
		empr=0;
		saldo=100;
		divida=0;
		PIN=1234;
		activo=false;
		nConta=1000;
	}
/*Definicao dos setters*/
	void setTipo(int x){
			 if(x==1) tipo="Ordem  ";
		else if(x==2) tipo="Salario";
		else if(x==3) tipo="Prazo  ";
				 else tipo="-------";
	}
	void setConta(int x){	nConta=1000+x;	}
	void setSaldo(float x){		saldo+=x;	}
	void setDepos(float x){		saldo+=x;		dep=x;	}
	void setLevant(float x){	saldo-=(x+7);	lev=x;	}
	void setTransf(float x){	saldo-=(x+7);	trans=x;	}
	void setEmprest(float x){	saldo+=x;		empr=x;	divida=x+0.7*x;	}
	void setSaldar(float x){	divida-=x;		saldo-=x;	}
	void setEstado(bool x){		activo=x;	}
	void setPin(int x){			PIN=x;		}
/*Definicao dos getters*/
	string getTipo(){	return tipo;	}
	int getConta(){		return nConta;	}
	float getSaldo(){	return saldo;	}
	float getDepos(){	return dep;		}
	float getLevant(){	return lev;		}
	float getTransf(){	return trans;	}
	float getEmprest(){	return empr;	}
	float getDivida(){	return divida;	}
	bool getEstado(){	return activo;	}
	bool confPin(int x){	if(x==PIN)	return true;	}
	
 private:
	string tipo;	// [1 Salario 2 Ordem 3 Prazo]
	int nConta;
	float saldo;
	float dep;
	float trans;
	float lev;
	float empr;
	float divida;
	bool activo;
	int PIN;
};
class MetodoCliente
{public:
 	MetodoCliente(){		PINadm=7777;	}

/*			Areao de Cliente			*/
	int login(){
		int conta,pin;
		topo();
		if(contas==0){
			cout<<"\t  **  Nenhum Cliente Cadastrado...  **\n";
			down();
		}else{
			topo();
			cout<<endl<<"\tDigite o numero da conta: ";	cin>>conta;
			for(int i=0;i<T;i++){
				if(conta==C[i].getConta()){
					conta=0;
					do{
						cout<<"\t"<<C[i].getNome()<<" digite o PIN: "; cin>>pin;
						if(C[i].confPin(pin)==true)
							return i;
							break;						
					}while(C[i].confPin(pin)!=true && conta<3);
			//		break;
				}
			}
		}
		return -1;
	}
	static int menu(){
		MetodoCliente::topo();
		cout<<endl<<"\t+-----------------------------------------+"
			<<endl<<"\t|             Menu do Cliente             |"
			<<endl<<"\t| +-------------------------------------+ |"
			<<endl<<"\t| |  [1] Depositar     [5] Saldar       | |"
			<<endl<<"\t| |  [2] Levantar      [6] Extrato      | |"
			<<endl<<"\t| |  [3] Transferir    [7] Minha Conta  | |"
			<<endl<<"\t| |  [4] Emprestimo    [0] Sair         | |"
			<<endl<<"\t| +-------------------------------------+ |"
			<<endl<<"\t|_________________________________________|"
			<<endl<<"\t\t\t\t\t\t:";
		int op;
		cin>>op;
		if(op<0||op>5) menu();
		return op;
	}	
	void deposit (int p){
		int conta;	float valor;
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |            DEPOSITO           |"
			<<endl<<"\t     +-------------------------------+"
			<<endl;
			  cout<<"\t     [1] Minha Conta     [2] Outra  ";
			  cin>>conta;
			if(conta==2){
			  cout<<"\t     Numero da conta: ";	cin>>conta;
				for(int i=0;i<T;i++){
					if(conta==C[i].getConta()){
						p=i;	conta=0;
						cout<<"\t     Titular: "<<C[p].getNome();
						break;
					}
					conta++;
				}
			}
		if(conta>T){
			cout<<endl<<"\t     +-------------------------------+"
				<<endl<<"\t     |       CONTA NAO ENCOTRADA     |"
				<<endl<<"\t     +-------------------------------+";			
		}else{
			cout<<endl<<"\t    Valor: ";		cin>>valor;
			C[p].setDepos(valor);
			capitalBancario+=valor;
			cout<<endl<<"\t     +-------------------------------+"
				<<endl<<"\t     |       Deposito Efetuado!        |"
				<<endl<<"\t     +-------------------------------+";
		}
		MetodoCliente::down();
	}
	void levant (int p){
		float valor;
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |          LEVANTAMENTO         |"
			<<endl<<"\t     +-------------------------------+"
			<<endl
			<<endl<<"\t      Valor: ";		cin>>valor;
		if(valor+7<=C[p].getSaldo()){
			C[p].setLevant(valor);	
			cout<<endl<<"\t      Saldo: "<<C[p].getSaldo();
			capitalBancario-=valor;
		}else{
			cout<<endl<<"\t          Saldo Insuficiente"
				<<endl<<"\t      Saldo: "<<C[p].getSaldo();
		}
		MetodoCliente::down();
	}
	void transf (int p){
		float valor;	int conta,x=1;
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |         TRANSFERENCIA         |"
			<<endl<<"\t     +-------------------------------+"
			<<endl
			<<endl<<"\t      Numero da conta: ";	cin>>conta;
		for(int i=0 ; i<T ; i++ && x++){	
			if(conta==C[i].getConta()){
				conta=i;	x=0;
				cout<<endl<<"\t          Titular: "<<C[conta].getNome();
					break;
			}
		}
		if(x!=0)
			cout<<endl<<"\t         Conta nao encotrada...";
		else{
			cout<<endl<<"\t      Valor: ";				cin>>valor;
			if(valor+7<=C[p].getSaldo()){
				C[p].setTransf(valor);
				C[conta].setDepos(valor);
				cout<<endl<<"\t           Valor transferido\n"
					<<endl<<"\t      Saldo: "<<C[p].getSaldo();
			}else{
				cout<<endl<<"\t           Saldo Insuficiente"
					<<endl<<"\t      Saldo: "<<C[p].getSaldo();
			}			
		}
		MetodoCliente::down();
	}
	void emprest (int p){
		float valor;
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |           EMPRESTIMO          |"
			<<endl<<"\t     +-------------------------------+"
			<<endl
			<<endl<<"\t      Valor: ";		cin>>valor;
		if(valor<capitalBancario){									/*	Definir um ponteiro para capital*/
			C[p].setEmprest(valor);	
			cout<<endl<<"\t      Emprestimo Autorizado...\n"
				<<endl<<"\t      Saldo: "<<C[p].getSaldo();
			capitalBancario-=valor;
		}else{
			cout<<endl<<"\t          Credito Indisponivel...";
		}
		MetodoCliente::down();
	}
	void saldar (int p){
		char c='s';	static int x=1; float valor;
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |          SALDAR DIVIDA        |"
			<<endl<<"\t     +-------------------------------+"
			<<endl
			<<endl<<"\t     Divida: "<<C[p].getDivida();
		while(x<=5 && c=='S'|| c=='s' || C[p].getDivida()==0){
			cout<<endl<<"\t     "<<x<<"* Presatacao: ";
			cin>>valor;
			C[p].setSaldar(valor);
			capitalBancario+=valor;
			cout<<endl<<"\t     Divida: "<<C[p].getDivida();
			if(x<5){
				cout<<endl<<"\t     Fazer outra prestacao [S/N]: ";
				cin>>c;				
			}
		}
		if(x==5)	x=1;
		if(C[p].getDivida()==0)
			cout<<endl<<"\t     Divida Paga! ";
		MetodoCliente::down();	
	}
	void verDados (int p){
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |         DADOS DA CONTA        |"
			<<endl<<"\t     +-------------------------------+"
			<<endl
			<<endl<<"\t       Tipo: "<<C[p].getTipo()<<"    Numero: "<<C[p].getConta()
			<<endl<<"\t       Titular: "<<C[p].getNome()<<" --- Gen: "<<C[p].getGen()
			<<endl<<"\t       Telefone: "<<C[p].getTel()
			<<endl<<"\t       Divida: "<<C[p].getDivida()
			<<endl<<"\t       Saldo: "<<C[p].getSaldo();
		MetodoCliente::down();
	}
	void extrato (int p){
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |            EXTRATO            |"
			<<endl<<"\t     +-------------------------------+"
			<<endl
			<<endl<<"\t      Conta..........:"<<C[p].getConta();
		if(C[p].getDepos()>0)	cout<<endl<<"\t      Deposito.......: "<<C[p].getDepos();
		if(C[p].getLevant()>0)	cout<<endl<<"\t      Levantamento...: "<<C[p].getLevant();
		if(C[p].getTransf()>0)	cout<<endl<<"\t      Transferencia..: "<<C[p].getTransf();
		if(C[p].getEmprest()>0)	cout<<endl<<"\t      Emprestimo.....: "<<C[p].getEmprest();
		if(C[p].getDivida()>0)	cout<<endl<<"\t      Divida.........: "<<C[p].getDivida();
		MetodoCliente::down();
	}
	static void Capital(void){
		MetodoCliente::topo();
		cout<<endl<<"\t     +--------------------------------+"
			<<endl<<"\t     |        CAPITAL DO BANCO        |"
			<<endl<<"\t     +--------------------------------+"
			<<endl
			<<endl<<"\t        Contas activas...: "<<contas
			<<endl<<"\t        Capital actual...: "<<capitalBancario<<"MZN";
		MetodoCliente::down();
		getch();
	}
	static void topo(){
		system("cls");
		system("color 1F");
		cout<<endl<<"\t                BLUE  BANK  "
			<<endl<<"\t              +------------+"
			<<endl<<"\t+-----------------------------------------+"
			<<endl<<endl;
	}
	static void down(){
		cout<<endl<<endl<<"\t+-----------------------------------------+"
				  <<endl<<"\t                  BlueBank\n";
		getch();	
	}

/*			Areao de Administrador		*/
	bool loginAdm(){
		int pin,x=0;
		do{
			MetodoCliente::topo();
			cout<<endl<<"\t             ARLINDO MAIBASSE"
				<<endl<<"\t               Codigo: ";	cin>>pin;
			if(pin!=PINadm){
				cout<<"\n\t             Codigo Incorreto ...";
				getch();
				x++;	
			}			
		}while(x<3 && pin!=PINadm);
		if(pin==PINadm)
			return true;
		return false;
	}
	static int menuAdm(){
		MetodoCliente::topo();
		cout<<endl<<"\t+-----------------------------------------+"
			<<endl<<"\t|          Menu do Administrador          |"
			<<endl<<"\t| +-------------------------------------+ |"
			<<endl<<"\t| |  [1] Cadastrar      [4] Listar      | |"
			<<endl<<"\t| |  [2] Cancelar       [5] Capital     | |"
			<<endl<<"\t| |  [3] Encotrar       [0] Sair        | |"
			<<endl<<"\t| +-------------------------------------+ |"
			<<endl<<"\t|_________________________________________|"
			<<endl<<"\t\t\t\t\t\t:";
		int op;
		cin>>op;
		if(op<0||op>5) menu();
		return op;
	}	
	void registar (void){
		int i=contas;
		char op;
		do{		
			int num;
			string bi;
			char nome[16],gen;
			fflush(stdin);
			MetodoCliente::topo();
			cout<<endl<<"\t     +-------------------------------+"
				<<endl<<"\t     |  Preencha os campos a seguir  |"
				<<endl<<"\t     +-------------------------------+"
				<<endl;
			cout<<"\t  Nome: ";				gets(nome);		fflush(stdin);
			cout<<"\t  Genero [M/F]: ";		cin>>gen;		fflush(stdin);
			cout<<"\t  Telefone: ";			cin>>num;
			cout<<"\t  Nr de BI: ";			cin>>bi;		fflush(stdin);
			C[i].setNome(nome);
			C[i].setGen(gen);
			C[i].setTel(num);
			C[i].setBi(bi);
			cout<<"\t  Tipo de conta [1 Salario 2 Ordem 3 Prazo]\n\t  ";	cin>>num;	
			C[i].setTipo(num);
			C[i].setConta(i);
			C[i].setSaldo(133.58);
			C[i].setEstado(true);
			cout<<"\t  Numero da Conta: "<<C[i].getConta()<<endl;
			cout<<"\t  PIN: 1234"<<endl;
			
			capitalBancario+=C[i].getSaldo();										// Somando o capital final do Banco
			cout<<endl<<"\t     +-------------------------------+"
				<<endl<<"\t     |   Conta Criada Com Sucesso!   |"
				<<endl<<"\t     +-------------------------------+";
			contas++;																	// Sama do total de clientes cadastrsdos
			MetodoCliente::down();	
			cout<<"\n\n\t Cadastrar outro? [S/N]\t";	cin>>op;	fflush(stdin);
		}while(contas<T && op=='S'||op=='s');
	}
	void cancelar (void){
		int p,conta,pin;
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |        Cancelar Conta         |"
			<<endl<<"\t     +-------------------------------+"
			<<endl;
		cout<<"\t  Numero da conta: ";	cin>>conta;
		for(p=0;p<contas;p++){
			if(conta==C[p].getConta()){
				cout<<"\t  PIN [Adm]: ";		cin>>pin;
				if(C[p].confPin(pin)==true || pin==PINadm){
					C[p].setEstado(false);
					cout<<endl<<"\t     +-------------------------------+"
						<<endl<<"\t     |        Conta Cancelada!       |"
						<<endl<<"\t     +-------------------------------+";
					p=0;
					break;
				}
			}
		}
		if(p!=0){
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |    Numero de Conta Invalido   |"
			<<endl<<"\t     +-------------------------------+";
		}
		MetodoCliente::down();
	}
	void listar (void){
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |       Dados dos Clientes      |"
			<<endl<<"\t     +-------------------------------+"
			<<endl;
		for(int p=0;p<contas;p++){
			if(C[p].getEstado()==true){
				cout<<endl<<"\t+-----------------------------------------+"
					<<endl<<"\t  Tipo: "<<C[p].getTipo()
					<<endl<<"\t  Conta: "<<C[p].getConta()
					<<endl<<"\t  Titular: "<<C[p].getNome()<<"  ---  Gen: "<<C[p].getGen()
					<<endl<<"\t  Divida: "<<C[p].getDivida()
					<<endl<<"\t  Saldo: "<<C[p].getSaldo();
			}
		}
		MetodoCliente::down();
	}
	void procurar (void){
		int conta;
		MetodoCliente::topo();
		cout<<endl<<"\t     +-------------------------------+"
			<<endl<<"\t     |         PROCURAR CONTA        |"
			<<endl<<"\t     +-------------------------------+"
			<<endl;
		cout<<"\t  Numero da Conta: ";cin>>conta;
		for(int p=0;p<contas;p++){
			if(conta==C[p].getConta()){
				MetodoCliente::topo();
				cout<<endl<<"\t     +-------------------------------+"
					<<endl<<"\t     |         DADOS DA CONTA        |"
					<<endl<<"\t     +-------------------------------+"
					<<endl
					<<endl<<"\t  Tipo: "<<C[p].getTipo()<<"          Conta: "<<C[p].getConta()
					<<endl<<"\t  Titular: "<<C[p].getNome()<<"  ---  Gen: "<<C[p].getGen()
					<<endl<<"\t  Telefone: "<<C[p].getTel()
					<<endl<<"\t  Divida: "<<C[p].getDivida()
					<<endl<<"\t  Saldo: "<<C[p].getSaldo();
					conta=0;
				break;				
			}
		}
		if(conta!=0) cout<<"\t            CONTA NAO EXISTENTE";
		MetodoCliente::down();
	}

private:
	int PINadm;
	static int contas;
	static long double capitalBancario;
	dBancarios C[T];							//	Objecto para manipulacao de dados e transacoes do [T] clientes	
};

int MetodoCliente::contas=0;
long double MetodoCliente::capitalBancario=5000000;
int main(void){
	MetodoCliente::topo();
	MetodoCliente X;
	
	cout<<endl<<"\t+-----------------------------------------+"
		<<endl<<"\t|               Entrar Como               |"
		<<endl<<"\t| +-------------------------------------+ |"
		<<endl<<"\t| |  [1] Administrador    [2] Cliente   | |"
		<<endl<<"\t| +-------------------------------------+ |"
		<<endl<<"\t|_________________________________________|"
		<<endl<<"\t\t\t\t\t\t:";
	int op;
	cin>>op;
	if(op==1){
		if(X.loginAdm()==true){
			do{
				op=X.menuAdm();
				switch(op){
				case 1:{	X.registar();	break;	}
				case 2:{	X.cancelar();	break;	}
				case 3:{	X.procurar();	break;	}
				case 4:{	X.listar();		break;	}
				case 5:{	X.Capital();	break;	}
				}
			}while(op!=0);	
		}	
	}
	else if(op==2){
		op=X.login();
		if(op>-1){
			do{
				int x;
				x=X.menu();
				switch(x){
				case 1:{	X.deposit(op);	break;	}
				case 2:{	X.levant(op);	break;	}
				case 3:{	X.transf(op);	break;	}
				case 4:{	X.emprest(op);	break;	}
				case 5:{	X.saldar(op);	break;	}
				case 6:{	X.extrato(op);	break;	}
				case 7:{	X.verDados(op);	break;	}
				}
			}while(op!=0);
		}
	}
	char sn;
	cout<<"\n\n\n\t Terminar Programa [S/N]\t";cin>>sn;
	if(sn=='N'||sn=='n') main();
	
	cout<<endl<<"\t+-----------------------------------------+"
		<<endl<<"\t     OBRIGADO POR USAR NOSSA PLATAFORMA"<<
	endl<<endl<<"\t                  BlueBank"
		<<endl;	
	return 0;
}

