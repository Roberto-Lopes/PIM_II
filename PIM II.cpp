/*###############################################################
				Projeto PIM - ADS 1° Período 
				Roberto Lopes Martins Arruda
				RA: N020CJ7
###############################################################*/

//bibliotecas e constantes.
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	
	#define QTD_FUNC 7
	#define QTD_CLIENTE 50
	#define QTD_SERV 50
	#define QTD_DESP 50

//variáveis globais.
	int i, qtd_serv, qtd_func, qtd_cli, qtd_desp;


//estruturas.
	typedef struct{
		char nome_funcionario[50], endereco_funcionario[500], cargo[20], login[20], senha[20], telefone_funcionario[12], CPF_funcionario[11];
		float salario;
		int codigo_funcionario;
	} Funcionario;
	
	typedef struct{
		char nome_cliente[50], endereco_cliente[500], CPF_cliente[12], telefone_cliente[13];	
		int codigo_cliente;
	} Cliente;
	
	typedef struct{
		char nome_servico[50];
		float valor;
		int codigo_servico;
	} Servico;
	
	typedef struct{
		char nome_despesa[50];
		float valor;
		int codigo_despesa;
	} Despesa;
	
	Funcionario funcionarios[QTD_FUNC];
	Cliente clientes[QTD_CLIENTE];
	Servico servicos[QTD_SERV];
	Despesa despesas[QTD_DESP];

//declaração de funções.
	void menu_principal();
	void funcionario();
	void cadastro_funcionario();
	void lista_funcionario();
	void deletar_funcionario();
	void contador_funcionario();
	void cliente();
	void lista_cliente();
	void cadastro_cliente();
	void deletar_cliente();
	void contador_cliente();
	void servico();
	void cadastro_servico();
	void lista_servico();
	void deletar_servico();
	void contador_servico();
	void despesa();
	void lista_despesa();
	void cadastro_despesa();
	void deletar_despesa();
	void contador_despesa();
	void relatorio_despesa();
	

//arquivos.
	FILE* arqFunc;
	FILE* arqCli;
	FILE* arqServ;
	FILE* arqDesp;
	FILE* relatorio_despesas;

//main.		
	int main(){
		menu_principal();
		return 0;
	}

//funções.

	//Função menu principal abre um menu para selção de outra função
	void menu_principal(){
		int op;
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nMenu principal\n1- Funcionario\n2- Cliente\n3- Servico\n4- Despesas\n5- Sair\n\n opcao: ");
		scanf("%d", &op);
		getchar();
		switch(op){
			case 1:
				funcionario();
				break;
			case 2:
				cliente();
				break;
			case 3:
				servico();
				break;
			case 4:
				despesa();
				break;
			case 5:	
				exit(1);
			default: 
				printf("Opcao invalida! ");
				getchar();
				menu_principal();
				break;
		}
		getchar();
	}
	
	//Função funcionário abre um menu para seleção de outra função.
	void funcionario(){
		int op;
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nFuncionarios\n1- Lista de funcionarios\n2- Cadastro de funcionario\n3- Deletar funcionario\n4- Voltar\n5- Sair do programa\n\n opcao: ");
		scanf("%d", &op);
		getchar();
		switch(op){
			case 1:
				lista_funcionario();
				break;
			case 2:
				cadastro_funcionario();
				break;
			case 3:
				deletar_funcionario();
				break;
			case 4:
				menu_principal();
				break;
			case 5:
				exit(1);
			default:
				printf("Opcao invalida! ");
				getchar();
				funcionario();
				break;
		}
		getchar();
	}
	
	//Função contador funcionário cria adiciona a uma variável global, a quantidade de funcionários registrados.
	void contador_funcionario(){
		Funcionario func_temp;
		qtd_func = 0;
		arqFunc = fopen("Funcionarios.txt", "rb");
		if(arqFunc!=NULL){
			while(fread(&func_temp, sizeof(Funcionario), 1, arqFunc)){
				qtd_func++;
			}
		}
		fclose(arqFunc);
	}
	
	//Função lista funcionário cria uma lista de todos os funcionários cadastrados.
	void lista_funcionario(){
		Funcionario func_temp;
		
		arqFunc = fopen("Funcionarios.txt", "rb");
		
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nLista de servicos:\n----------------------------------------------\n");
		
		if(arqFunc!=NULL){
			while(fread(&func_temp, sizeof(Funcionario), 1, arqFunc)){
				printf("\nCodigo do funcionario: %d", func_temp.codigo_funcionario);
				printf("\nNome: %s", func_temp.nome_funcionario);
				printf("CPF: %s", func_temp.CPF_funcionario);
				printf("\nTelefone: %s", func_temp.telefone_funcionario);
				printf("\nEndereco: %s", func_temp.endereco_funcionario);
				printf("Cargo: %s", func_temp.cargo);
				printf("Salario: R$%0.2f", func_temp.salario);
				printf("\nLogin: %s", func_temp.login);
				printf("\n----------------------------------------------\n");
			}
		}else printf("Nao foi possivel abrir o arquivo Funcionarios!\n0- Voltar");
		printf("\n0- Voltar ");
		getchar();
		fclose(arqFunc);
		funcionario();
	}
	
	//Função cadastro funcionário abre uma tela para o usuário inserir informações e registrar um novo funcionário.
	void cadastro_funcionario(){
		Funcionario func_temp;
		
		int op=1;
		
		do{
			system("cls");
			printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nCadastros de funcionarios\n\n----------------------------------------------\n");
			contador_funcionario();
			func_temp.codigo_funcionario = qtd_func+1;
			printf("Nome: ");
			fgets(func_temp.nome_funcionario, sizeof(func_temp.nome_funcionario), stdin);
			printf("CPF: ");
			scanf("%s", func_temp.CPF_funcionario);
			printf("Telefone: ");
			scanf("%s", func_temp.telefone_funcionario);
			fgetchar();
			printf("Endereco: ");
			fgets(func_temp.endereco_funcionario, sizeof(func_temp.endereco_funcionario), stdin);
			printf("Cargo: ");
			fgets(func_temp.cargo, sizeof(func_temp.cargo), stdin);
			printf("Salario: R$");
			scanf("%f", &func_temp.salario);
			fflush(stdin);
			printf("Login: ");
			fgets(func_temp.login, sizeof(func_temp.login), stdin);
			fflush(stdin);
			printf("Senha: ");
			fgets(func_temp.senha, sizeof(func_temp.senha), stdin);
			arqFunc = fopen("Funcionarios.txt", "ab");
			fwrite(&func_temp, sizeof(Funcionario), 1, arqFunc);
			fflush(stdin);
			printf("\nFuncionario cadastrado com sucesso!\n\n1- Novo cadastro\n0- Sair ");
			scanf("%d", &op);
			fflush(stdin);
			fclose(arqFunc);
		}while(op!=0);
		funcionario();
	}
	
	//Função deletar funcionario abre uma tela de seleção para deletar um funcionário previamente registrado.
	void deletar_funcionario(){
		Funcionario func_temp;
		FILE* temp = fopen("temp.txt", "wb");
		arqFunc = fopen("Funcionarios.txt", "rb");
		int aux;
		
		if(arqFunc!=NULL&&temp!=NULL){
			system("cls");
			printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nDigite o codigo do funcionario para deletar: ");
			scanf("%d", &aux);
			while(fread(&func_temp, sizeof(Funcionario), 1, arqFunc)){
				if(func_temp.codigo_funcionario==aux){
					printf("\n----------------------------------------------\n");
					printf("Codigo: %d", func_temp.codigo_funcionario);
					printf("\nNome: %s", func_temp.nome_funcionario);
					printf("CPF: %s", func_temp.CPF_funcionario);
					printf("\n----------------------------------------------\n");
				}else{
					fwrite(&func_temp, sizeof(Funcionario), 1, temp);
				}
			}
		}else printf("Nao foi possivel abrir o arquivo Funcionarios!\n\n0 - Voltar ");
		fclose(arqFunc);
		fclose(temp);
	
		printf("\n\nDeseja realmente deletar esses dados:\n\n1- Continuar\n0- Voltar ");
		scanf("%d", &aux);
		if(aux==1){
			if(remove("Funcionarios.txt")==0&&rename("temp.txt","Funcionarios.txt")==0){
				system("cls");
				printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nFuncionario deletado com sucesso!");	
				getchar();
			}
		}else remove("temp.txt");
		printf("\n\n0- Voltar ");
		getchar();
		funcionario();
	}
	
	//Função cliente abre um menu para seleção de outra função.
	void cliente(){
		int op;
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nCLientes\n1- Lista de clientes\n2- Cadastro de cliente\n3- Deletar cliente\n4- Voltar\n5- Sair do programa\n\n opcao: ");
		scanf("%d", &op);
		getchar();
		switch(op){
			case 1:
				lista_cliente();
				break;
			case 2:
				cadastro_cliente();
				break;
			case 3:
				deletar_cliente();
				break;
			case 4:
				menu_principal(); 
				break;
			case 5:
				exit(1);
			default:
				printf("Opcao invalida! ");
				getchar();
				cliente();
				break;
		}
	}
	
	//Função lista cliente cria uma lista de todos os clientes cadastrados.
	void lista_cliente(){
		Cliente cli_temp;
		
		arqCli = fopen("Clientes.txt", "rb");
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nLista de funcionarios\n\n----------------------------------------------\n");
		if(arqCli!=NULL){
			while(fread(&cli_temp, sizeof(Cliente), 1, arqCli)==1){
				printf("Codigo do cliente: %d", cli_temp.codigo_cliente);
				printf("\nNome: %s", cli_temp.nome_cliente);
				printf("CPF: %s", cli_temp.CPF_cliente);
				printf("\nTelefone: %s", cli_temp.telefone_cliente);
				printf("\nEndereco: %s", cli_temp.endereco_cliente);
				printf("\n----------------------------------------------\n");
			}
		}else printf("Nao foi possivel abrir o arquivo Clientes!");
		fclose(arqCli);
		printf("\n\n0- Voltar ");
		getchar();		
		cliente();
	}
	
	//Função contador cliente cria adiciona a uma variável global, a quantidade de clientes registrados.
	void contador_cliente(){
		Cliente cli_temp;
		qtd_cli = 0;
		arqCli = fopen("Clientes.txt", "rb");
		
		if(arqCli!=NULL){
			while(fread(&cli_temp, sizeof(Cliente), 1, arqCli)){
				qtd_cli++;
			}
		}
		fclose(arqCli);
	}
	
	//Função cadastro cliente abre uma tela para o usuário inserir informações e registrar um novo cliente.
	void cadastro_cliente(){
		Cliente cli_temp;
		int op = 1;
		do{
			contador_cliente();
			cli_temp.codigo_cliente = qtd_cli+1;
			system("cls");
			printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nCadastro de cliente\nNome: ");
			fgets(cli_temp.nome_cliente, sizeof(cli_temp.nome_cliente), stdin);
			printf("CPF: ");
			scanf("%s", cli_temp.CPF_cliente);
			fflush(stdin);
			printf("Telefone: ");
			scanf("%s", cli_temp.telefone_cliente);
			fflush(stdin);
			printf("Endereco: ");
			fgets(cli_temp.endereco_cliente, sizeof(cli_temp.endereco_cliente), stdin);
			fflush(stdin);
			arqCli = fopen("Clientes.txt", "ab");
			fwrite(&cli_temp, sizeof(Cliente), 1, arqCli);
			printf("\nCliente cadastrado com sucesso!\n\n1- Novo cadastro\n0- Voltar ");
			scanf("%d", &op);
			getchar();
			fclose(arqCli);
		}while(op==1);
		cliente();
	}
	
	//Função deletar cliente abre uma tela de seleção para deletar um cliente previamente registrado.
	void deletar_cliente(){
		Cliente cli_temp;
		FILE* temp = fopen("temp.txt", "wb");
		arqCli = fopen("Clientes.txt", "rb");
		int aux;
		
		if(arqCli!=NULL&&temp!=NULL){
			system("cls");
			printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nDigite o codigo do cliente para deletar: ");
			scanf("%d", &aux);
			while(fread(&cli_temp, sizeof(Cliente), 1, arqCli)){
				if(cli_temp.codigo_cliente==aux){
					printf("\n----------------------------------------------\n");
					printf("Codigo: %d", cli_temp.codigo_cliente);
					printf("\nNome: %s", cli_temp.nome_cliente);
					printf("CPF: %s", cli_temp.CPF_cliente);
					printf("\n----------------------------------------------\n");
				}else{
					fwrite(&cli_temp, sizeof(Cliente), 1, temp);
				}
			}
		}else printf("Nao foi possivel abrir o arquivo Clientes!\n\n0 - Voltar ");
		fclose(arqCli);
		fclose(temp);
	
		printf("\n\nDeseja realmente deletar esses dados:\n\n1- Continuar\n0- Voltar ");
		scanf("%d", &aux);
		if(aux==1){
			if(remove("Clientes.txt")==0&&rename("temp.txt","Clientes.txt")==0){
				system("cls");
				printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nCliente deletado com sucesso!");	
				getchar();
			}
		}else remove("temp.txt");
		printf("\n\n0- Voltar ");
		getchar();
		cliente();
	}
	
	//Função servico abre um menu para seleção de outra função.
	void servico(){
		int op;
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nServicos\n1- Lista de servicos\n2- Cadastrar servico\n3- Deletar servico\n4- Voltar\n5- Sair do programa\n\n opcao: ");
		scanf("%d", &op);
		getchar();
		switch(op){
			case 1:
				lista_servico();
				break;
			case 2:
				cadastro_servico();
				break;
			case 3:
				deletar_servico();
				break;
			case 4:
				menu_principal();
				break;
			case 5:
				exit(1);
			default:
				printf("\nOpcao invalida!");
				getchar();
				servico();
				break;
		}
	}
	
	//Função contador servico cria adiciona a uma variável global, a quantidade de serviços registrados.
	void contador_servico(){
		Servico serv_temp;
		qtd_serv=0;
		arqServ = fopen("Servicos.txt", "rb");
		if(arqServ!=NULL){
			while(fread(&serv_temp, sizeof(Servico), 1, arqServ)==1){
				qtd_serv++;
			}
		}
		fclose(arqServ);
		
	}
	
	//Função lista servico cria uma lista de todos os serviços cadastrados.
	void lista_servico(){
		Servico serv_temp;
		
		arqServ = fopen("Servicos.txt", "rb");
		
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nLista de servicos:\n----------------------------------------------\n");
		
		if(arqServ!=NULL){
			while(fread(&serv_temp, sizeof(Servico), 1, arqServ)==1){
				if(serv_temp.codigo_servico!=0){
					printf("\nCodigo do servico: %d\n", serv_temp.codigo_servico);
					printf("Tipo: %s", serv_temp.nome_servico);
					printf("Valor: R$%0.2f", serv_temp.valor);
					printf("\n----------------------------------------------\n");
				}
			}
		}else printf("Nao foi possivel abrir o arquivo Servicos!\n");
		fclose(arqServ);
		printf("\n\n0- Voltar ");
		getchar();
		servico();
	}
	
	//Função cadastro servico abre uma tela para o usuário inserir informações e registrar um novo serviço.
	void cadastro_servico(){
		Servico serv_temp;
		int op=1;
		do{
			system("cls");
			printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nCadastro de servico\nTipo: ");
			fgets(serv_temp.nome_servico, sizeof(serv_temp.nome_servico), stdin);
			printf("Valor: R$");
			scanf("%f", &serv_temp.valor);
			contador_servico();
			serv_temp.codigo_servico = qtd_serv+1;
			arqServ = fopen("Servicos.txt", "ab");
			fwrite(&serv_temp, sizeof(Servico), 1, arqServ);
			printf("\nServico cadastrado com sucesso!\n1- Novo cadastro\n0- Sair ");
			scanf("%d", &op);
			getchar();
			fclose(arqServ);
		}while(op==1);
		servico();
	}

	//Função deletar servico abre uma tela de seleção para deletar um serviço previamente registrado.
	void deletar_servico(){
		Servico serv_temp;
		FILE* temp = fopen("temp.txt", "wb");
		arqServ = fopen("Servicos.txt", "rb");
		int aux;
		
		if(arqServ!=NULL&&temp!=NULL){
			system("cls");
			printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nDigite o codigo do servico para deletar: ");
			scanf("%d", &aux);
			while(fread(&serv_temp, sizeof(Servico), 1, arqServ)){
				if(serv_temp.codigo_servico==aux){
					printf("\n----------------------------------------------\n");
					printf("Codigo: %d", serv_temp.codigo_servico);
					printf("\nNome: %s", serv_temp.nome_servico);
					printf("Valor: R$%0.2f\n", serv_temp.valor);
					printf("\n----------------------------------------------\n");
				}else{
					fwrite(&serv_temp, sizeof(Servico), 1, temp);
				}
			}
		}else printf("Nao foi possivel abrir o arquivo Servicos!\n\n0 - Voltar ");
		fclose(arqServ);
		fclose(temp);
	
		printf("\n\nDeseja realmente deletar esses dados:\n\n1- Continuar\n0- Voltar ");
		scanf("%d", &aux);
		if(aux==1){
			if(remove("Servicos.txt")==0&&rename("temp.txt","Servicos.txt")==0){
				system("cls");
				printf("NOME DA EMPRESA\n\nServico deletado com sucesso!");	
				getchar();
			}
		}else remove("temp.txt");
		printf("\n\n0- Voltar ");
		getchar();
		servico();
	}
	
	//Função despesa abre um menu para seleção de outra função.
	void despesa(){
		int op;
		system("cls");
		printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nDespesas\n1- Lista de despesas\n2- Cadastrar despesa\n3- Deletar despesa\n4- Relatorio de despesas\n5- Voltar\n6- Sair do programa\n\n opcao: ");
		scanf("%d", &op);
		getchar();
		switch(op){
			case 1:
				lista_despesa();
				break;
			case 2:
				cadastro_despesa();
				break;
			case 3:
				deletar_despesa();
				break;
			case 4:
				relatorio_despesa();
				break;
			case 5:	
				menu_principal();
				break;
			case 6:
				exit(1);
			default:
				printf("\nOpcao invalida!");
				getchar();
				despesa();
				break;
		}
	}

	//Função contador despesa cria adiciona a uma variável global, a quantidade de despesas registrados.
	void contador_despesa(){
		Despesa desp_temp;
			qtd_desp=0;
			arqDesp = fopen("Despesas.txt", "rb");
			if(arqDesp!=NULL){
				while(fread(&desp_temp, sizeof(Despesa), 1, arqDesp)==1){
					qtd_desp++;
				}
			}
			fclose(arqDesp);
			
	}
	
	//Função lista despesa cria uma lista de todos as despesas cadastrados.
	void lista_despesa(){
		Despesa desp_temp;
			
			arqDesp = fopen("Despesas.txt", "rb");
			
			system("cls");
			printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nLista de despesas:\n----------------------------------------------\n");
			
			if(arqDesp!=NULL){
				while(fread(&desp_temp, sizeof(Despesa), 1, arqDesp)==1){
					if(desp_temp.codigo_despesa!=0){
						printf("\nCodigo do despesa: %d\n", desp_temp.codigo_despesa);
						printf("Tipo: %s", desp_temp.nome_despesa);
						printf("Valor: R$%0.2f", desp_temp.valor);
						printf("\n----------------------------------------------\n");
					}
				}
			}else printf("Nao foi possivel abrir o arquivo Despesas!\n");
			fclose(arqDesp);
			printf("\n\n0- Voltar ");
			getchar();
			despesa();
	}

	//Função cadastro despesa abre uma tela para o usuário inserir informações e registrar uma nova despesa.
	void cadastro_despesa(){
		Despesa desp_temp;
			int op=1;
			do{
				system("cls");
				printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nCadastro de despesa\nTipo: ");
				fgets(desp_temp.nome_despesa, sizeof(desp_temp.nome_despesa), stdin);
				printf("Valor: R$");
				scanf("%f", &desp_temp.valor);
				contador_despesa();
				desp_temp.codigo_despesa = qtd_desp+1;
				arqDesp = fopen("Despesas.txt", "ab");
				fwrite(&desp_temp, sizeof(Despesa), 1, arqDesp);
				printf("\nDespesa cadastrada com sucesso!\n1- Novo cadastro\n0- Sair ");
				scanf("%d", &op);
				getchar();
				fclose(arqDesp);
			}while(op==1);
			despesa();
	}
	
	//Função deletar despesa abre uma tela de seleção para deletar uma despesa previamente registrado.
	void deletar_despesa(){
		Despesa desp_temp;
			FILE* temp = fopen("temp.txt", "wb");
			arqDesp = fopen("Despesas.txt", "rb");
			int aux;
			
			if(arqDesp!=NULL&&temp!=NULL){
				system("cls");
				printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nDigite o codigo da despesa para deletar: ");
				scanf("%d", &aux);
				while(fread(&desp_temp, sizeof(Despesa), 1, arqDesp)){
					if(desp_temp.codigo_despesa==aux){
						printf("\n----------------------------------------------\n");
						printf("Codigo: %d", desp_temp.codigo_despesa);
						printf("\nNome: %s", desp_temp.nome_despesa);
						printf("Valor: R$%0.2f\n", desp_temp.valor);
						printf("\n----------------------------------------------\n");
					}else{
						fwrite(&desp_temp, sizeof(Despesa), 1, temp);
					}
				}
			}else printf("Nao foi possivel abrir o arquivo Despesas!\n\n0 - Voltar ");
			fclose(arqDesp);
			fclose(temp);
		
			printf("\n\nDeseja realmente deletar esses dados:\n\n1- Continuar\n0- Voltar ");
			scanf("%d", &aux);
			if(aux==1){
				if(remove("Despesas.txt")==0&&rename("temp.txt","Despesas.txt")==0){
					system("cls");
					printf("SHARP - SERVICOS E SOLUCOES EM DESIGN GRAFICO\n\nDespesa deletada com sucesso!");	
					getchar();
				}
			}else remove("temp.txt");
			printf("\n\n0- Voltar ");
			getchar();
			despesa();
	}
	
	//Função relatorio despesa cria um abre o explorador com o caminho de um arquivo txt criado que contém uma lista de despesas registradas e a soma de todas as despesas.
	void relatorio_despesa(){
		Despesa desp_temp;
		float soma=0;
		i=0;
		arqDesp = fopen("Despesas.txt", "rb");
		if(arqDesp!=NULL){
			while(fread(&desp_temp, sizeof(Despesa), 1, arqDesp)){
					despesas[i].codigo_despesa = desp_temp.codigo_despesa;
					strcpy(despesas[i].nome_despesa, desp_temp.nome_despesa);
					despesas[i].valor = desp_temp.valor;
					soma+= despesas[i].valor;
					i++;				
			}
		}else printf("Nao foi possivel abrir o arquivo Despesas! ");
		fclose(arqDesp);
		
		relatorio_despesas = fopen("Relatório de despesas.txt", "w");
		if(relatorio_despesas!=NULL){
			for(i=0;i<QTD_DESP;i++){
				if(despesas[i].codigo_despesa!=0){
					fprintf(relatorio_despesas, "\n----------------------------------------------\n");
					fprintf(relatorio_despesas, "Tipo: %s\nValor: R$%0.2f", despesas[i].nome_despesa, despesas[i].valor);
					fprintf(relatorio_despesas, "\n----------------------------------------------\n");
				}
			}
			fprintf(relatorio_despesas, "\n\nValor total de despesas: R$%0.2f", soma);
			system("explorer C:\\Users\\rober\\OneDrive\\Documentos\\ADS 1\\PIM\\Software");
		}else printf("Nao foi possivel abrir o arquivo Relatorio de despesas! ");
		fclose(relatorio_despesas);
		getchar();
		despesa();
	}
