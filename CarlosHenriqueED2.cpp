#include <stdio.h>
#include <conio2.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct letra
{
    char caracter;
    struct letra *prox, *ant;
};

struct linha
{
    int nro;
    struct letra *inicioL;
    struct linha *top, *botton;
};

struct listagen
{
  char letra, final;
  struct listagen *prim, *prox;  
};

typedef struct letra Letra;
typedef struct linha Linha;
typedef struct listagen ListaGen;

void Menu()
{
    //Topo
    gotoxy(1,1);
    printf("F2 - Abrir");
    gotoxy(21, 1);
    printf("F3 - Salvar");
    gotoxy(41,1);
    printf("F4 - Sair");
    gotoxy(61,1);
    printf("F5 - Exibir");
    gotoxy(1,2);
    printf("--------------------------------------------------------------------------------");
    gotoxy(1,24);
    printf("--------------------------------------------------------------------------------");
    gotoxy(1,25);
    printf("COL =");
    gotoxy(11,25);
    printf("LIN =");
    gotoxy(21,25);
    printf("INSERT");
    //Rodapé  
}

void TelaArquivo()
{
	system("cls");
	gotoxy(10,5);
	printf("%c",201);
	gotoxy(70,5);
	printf("%c",187);
	gotoxy(10,20);
	printf("%c",200);
	gotoxy(70,20);
	printf("%c",188);
	for(int i=6; i<20; i++)
	{
		gotoxy(10,i);
		printf("%c",186);
		gotoxy(70,i);
		printf("%c",186);
	}
	
	for(int i=11; i<70; i++)
	{
		gotoxy(i,5);
		printf("%c",205);
		gotoxy(i,20);
		printf("%c",205);
	}
}
Letra *NovaLetra(char info)
{
    Letra *NovaLetra = (Letra*)malloc(sizeof(Letra));
    NovaLetra->prox = NULL;
    NovaLetra->ant = NULL;
    NovaLetra->caracter = info;
    
    return NovaLetra;
}

void NovaLinhaBranco(Linha **L)
{
    *L = (Linha*)malloc(sizeof(Linha));
    (*L)->top = NULL;
    (*L)->botton = NULL;
    (*L)->nro = 0;
    (*L)->inicioL = NovaLetra(0);   
}

void InicializaEstrutura(Linha **Inicio, Linha **CLinha, Letra **Cursor)
{
    NovaLinhaBranco(&*Inicio);
    *CLinha = *Inicio;
    *Cursor = (*CLinha)->inicioL;
}

void NovaLinha(Linha **CLinha, Letra **Cursor)
{
    Linha *aux;
    NovaLinhaBranco(&aux);
    aux->top = *CLinha;
    if((*CLinha)->botton!=NULL)
    {
    	aux->botton = (*CLinha)->botton;
    	(*CLinha)->botton->top = aux;
    }	
	(*CLinha)->botton = aux;
    *CLinha = aux;
    *Cursor = (*CLinha)->inicioL;
}

void InsereInsert(int *lin, int *col,Linha **CLinha,Letra **Cursor, char info);
void InsereLetra(int *lin, int *col,Linha **CLinha,Letra **Cursor, char info)
{
	Letra *nova = NovaLetra(info), *aux;
    if((*Cursor)->caracter == 0)
    {
        nova->prox = *Cursor;
	    nova->ant = (*Cursor)->ant;
        if((*Cursor)->ant==NULL)
            (*CLinha)->inicioL = nova;
        else
            (*Cursor)->ant->prox = nova;
        (*Cursor)->ant = nova;  
        if(info!='§')	
        	(*CLinha)->nro++;
    }
    else
    {
        (*Cursor)->caracter = info;
        *Cursor = (*Cursor)->prox;
    }
    if(info!='§')
    	*col = *col+1;	
}

void InsereInsert(int *lin, int *col,Linha **CLinha,Letra **Cursor, char info)
{
	Letra *nova = NovaLetra(info), *aux;
    if((*Cursor)->ant==NULL)
    {
        nova->prox = *Cursor;
        (*Cursor)->ant = nova;
        (*CLinha)->inicioL = nova;
    }     	    
	else
	{
	    nova->prox = *Cursor;
	    nova->ant = (*Cursor)->ant;
	    (*Cursor)->ant->prox = nova;
	    (*Cursor)->ant = nova;
	}
	if(info!='§')
	{
		*col =*col+1;	
		(*CLinha)->nro++;
	}
}

void ResetarLinha(Letra **cursor)
{
	if(*cursor != NULL)
	{
		ResetarLinha(&(*cursor)->prox);
		free(*cursor);
		*cursor = NULL;
	}
}

void Destruir(Linha **Inicio)
{
	Linha *aux;
	while(*Inicio != NULL)
	{
		ResetarLinha(&(*Inicio)->inicioL);
		aux = *Inicio;
		*Inicio = (*Inicio)->botton;
		free(aux);
	}
}

void Liga_DeslIns(int *insert)
{
    gotoxy(28,25);
    if(*insert == 0)
    {
        *insert = 1;
        printf("||||");
    }
    else
    {
        *insert = 0;
        printf("    ");
    }
}


void ExibeLetra(int *col, int *lin,Linha *Inicio, Letra *Cursor)
{
	int neg = 0,cont=0;
	while(Inicio!=NULL && cont<21)
	{
		Cursor = Inicio->inicioL;
		for(int i=0; i<Inicio->nro; i++)
		{
			if(Cursor->caracter=='§')
			{
				if(neg==0)
					neg = 1;
				else
					neg = 0;
				i--;
			}
			else
			{
				gotoxy(*col,*lin);
				if(neg==1)
				{
					textcolor(14);
					printf("%c",Cursor->caracter);
					textcolor(7);
				}
				else
					printf("%c",Cursor->caracter);
				*col = *col+1;
			}
			
			Cursor = Cursor->prox;
			
		}
		Inicio = Inicio->botton;
		if(Inicio!=NULL)
		{
			*lin = *lin+1;
			*col = 1;
			cont++;	
		}
	}
}

void Home(int *col, Linha *CLinha, Letra **Cursor)
{
    *Cursor = CLinha->inicioL;
    *col =1;
}

void End(int *col, Linha *CLinha, Letra **Cursor)
{
    *Cursor = CLinha->inicioL;
    *col = 1;
    while((*Cursor)->prox !=NULL)
    {
        *Cursor = (*Cursor)->prox;
        if((*Cursor)->caracter!='§')
            *col = *col+1;
    }
}

void Backspace(int *lin, int *col,Linha **Inicio, Linha **CLinha, Letra **Cursor)
{
    Letra *del;
    Linha *aux;
    if(*col==2)
    {
        (*CLinha)->inicioL = *Cursor;
        del = (*Cursor)->ant;
        (*Cursor)->ant = NULL;
        if(del->caracter != '§')
        {
        	*col = *col-1;
        	(*CLinha)->nro--;
        }
        free(del);
        del = NULL;
    }
    else
    {
    	if(*col>2)
        {
            del = (*Cursor)->ant;
            (*Cursor)->ant->ant->prox =*Cursor; 
            (*Cursor)->ant = (*Cursor)->ant->ant;
            if(del->caracter != '§')
	        {
	        	*col = *col-1;
	        	(*CLinha)->nro--;
	        }
	        free(del);
            del = NULL;
        }
        /*else
        	if((*CLinha)->nro==0)
        	{
        		if((*CLinha)->top!=NULL || (*CLinha)->botton!=NULL)
        		{
        			aux = *CLinha;
	        		if((*CLinha)->botton !=NULL)
	        			(*CLinha)->botton->top = (*CLinha)->top;
	        		if((*CLinha)->top!=NULL)
	        		{
	        			(*CLinha)->top->botton = (*CLinha)->botton;
	        			*CLinha = aux->top;
	        			*Cursor = (*CLinha)->inicioL;
	        			while((*Cursor)->prox!=NULL)
	        				*Cursor = (*Cursor)->prox;
	        		}
	        		else
	        		{
	        			*Inicio = (*CLinha)->botton;
	        			*CLinha = aux->button;
	        			*Cursor = (*CLinha)->inicioL;
	        		}
	        		free(aux);	
        		}
        	}*/
    }
}

void Delete(int *lin, int *col, Linha **CLinha, Letra **Cursor)
{
    Letra *del;
    if((*Cursor)->prox!=NULL)
    {
        if((*Cursor)->ant == NULL)
        {
            del = *Cursor;
            *Cursor = (*Cursor)->prox;
            (*Cursor)->ant = NULL;
            (*CLinha)->inicioL = *Cursor;
        }
        else
        {
            del = *Cursor;
            *Cursor = (*Cursor)->prox;
            del->ant->prox = *Cursor;
            (*Cursor)->ant = del->ant;
        }
        if(del->caracter != '§')
        	(*CLinha)->nro--;
        free(del);
        del = NULL;
    }
}

void PageDown(int *lin, int *col,Linha **InicioTela,Linha *Inicio, Letra **Cursor,Linha **CLinha)
{
    Linha *aux = *InicioTela;
    for(int i=0; i<21; i++)
        if(aux->botton !=NULL)
            aux = aux->botton;
    if(aux->botton!=NULL)
    {
        *InicioTela = aux;
        *CLinha = *InicioTela;
        *Cursor = (*CLinha)->inicioL;
        *lin = 3;
        *col = 1;
    }  
    else
    {
        for(int i=0; i<21; i++)
        {
            if(aux!=Inicio)
                aux = aux->top;
        }
    }
}

void PageUp(int *lin, int *col,Linha **InicioTela,Linha *Inicio, Letra **Cursor,Linha **CLinha)
{
    Linha *aux = *InicioTela;
    for(int i=0; i<21; i++)
        if(aux!=Inicio)
            aux = aux->top;
    if(aux->top!=Inicio)
    {
        *InicioTela = aux;
        *CLinha = *InicioTela;
        *Cursor = (*CLinha)->inicioL;
        *lin = 3;
        *col = 1;
    }  
    else
    {
        *InicioTela = Inicio;
        *CLinha = Inicio;
        *Cursor = (*CLinha)->inicioL;
        *lin = 3;
        *col =1;
    }
}

int AndaEsquerda(int col, Letra **Cursor)
{
    if(col>1)
    {
    	col--;
    	*Cursor = (*Cursor)->ant;
    }
    return col;    
}

int AndaDireita(int col, Linha *aux, Letra **Cursor)
{
    if(col<=aux->nro)
    {
    	col++;
    	*Cursor = (*Cursor)->prox;
    }
    return col;
}

void AndaBaixo(int *lin,int *col,Linha **aux, Letra **Cursor,Linha *Inicio, Linha **IniTela)
{
    if(*lin<23 && (*aux)->botton != NULL)
    {
        int i=1;
        *lin = *lin +1;;
        *aux = (*aux)->botton;
        *Cursor = (*aux)->inicioL;
        while((*Cursor)->prox!=NULL && i<*col)
        {
            *Cursor = (*Cursor)->prox;
            i++;
        } 
        *col = i;
    }
    else
    {
        if(*lin>=23)
        {
            if((*aux)->botton!=NULL)
            {
                *IniTela = (*IniTela)->botton;
                *aux = (*aux)->botton;
                *Cursor = (*aux)->inicioL;
            }
                
        }
    }
    
}

void AndaCima(int *lin, int *col, Linha **CLinha, Letra **Cursor, Linha *Inicio, Linha **IniTela)
{
    if(*lin>3 && (*CLinha)->top!=NULL)
    {
        int i=1;
        *lin= *lin-1;
        *CLinha = (*CLinha)->top;
        *Cursor = (*CLinha)->inicioL;
        while((*Cursor)->prox!=NULL && i<*col)
        {
            *Cursor = (*Cursor)->prox;
            i++;
        } 
        *col = i;
    }
    else
    {
        if(*lin<=3)
        {
            if(*CLinha!=Inicio)
            {
                *IniTela = (*IniTela)->top;
                *CLinha = (*CLinha)->top;
                *Cursor = (*CLinha)->inicioL;
            }
        }
    } 
}

void ExibirFormatado(Linha *Inicio)
{
    int Pri_Lin, Rec_Dir, Rec_Esq, TL=0, i=0, lin,col, ini=1, neg=0, pos;
    char aux[30],vetP[500][30];
    Linha *auxLin = Inicio;
    Letra *auxCursor; 
    system("cls");
    TelaArquivo();
    gotoxy(27,6);
    printf("Configuracao dos paragrafos");
    gotoxy(11,7);
    printf("-----------------------------------------------------------");
    gotoxy(13,9);
    printf("Primeira linha: ");
    gotoxy(30,9);
    scanf("%d",&Pri_Lin);
    gotoxy(13,11);
    printf("Recuo esquerdo: ");
    gotoxy(30,11);
    scanf("%d",&Rec_Esq);
    gotoxy(13,13);
    printf("Recuo direito: ");
    gotoxy(30,13);
    scanf("%d",&Rec_Dir);
 
    //Separa palavras em vet
    while(auxLin!=NULL)
    {
        auxCursor = auxLin->inicioL;
        i=0;
        while(auxCursor!=NULL)
        {
            if(auxCursor->caracter!=' ')
                aux[i++] = auxCursor->caracter;
            else
            {
                aux[i] = '\0';
                strcpy(vetP[TL++],aux);
                i=0;
                aux[i] = '\0';
            }
            auxCursor = auxCursor->prox;
        }
        aux[i] = '\0';
        if(aux[0]!='\0')
            strcpy(vetP[TL++],aux);
        auxLin = auxLin->botton;
    }
    
    //Printa palavras com config acima
    system("cls");
    i=0;
    lin=1;
    col = 1;
    for(int k=0;k<80;k++)
    {
        if(k%5==0)
        {
            if(neg==0)
            {
                neg=1;
                textcolor(14);
            }
            else
            {
                neg=0;
                textcolor(7);
            } 
        }
        gotoxy(col,lin);
        printf("|");
        col++; 
    }
    col=1;
    neg=0;
    textcolor(7); 
    while(i<TL)
    {
        if(ini==1)
        {
            lin++;
            ini=0;
            vetP[i][0] = toupper(vetP[i][0]);
            col = Pri_Lin+1;
            
        }
        else
        {
            if(col+strlen(vetP[i])>81-Rec_Dir)
            {
                lin++;
                col=Rec_Esq+1;
            }            
        }
        for(int j=0; j<strlen(vetP[i]); j++)
        {
            if(vetP[i][j] == '§')
            {
                if(neg==0)
                {
                    neg=1;
                    textcolor(14);
                }
                else
                {
                    neg=0;
                    textcolor(7);
                }      
            }
            else
            {
                gotoxy(col,lin);
                printf("%c ",vetP[i][j]);
                col++;
            }
        }
            
        col++;
        if(vetP[i][strlen(vetP[i])-1]=='.' || vetP[i][strlen(vetP[i])-1]=='!' || vetP[i][strlen(vetP[i])-1]=='?')
            ini=1;
        i++;
    }
    
    getch();
}

//Tentativa com texto justificado, mas não deu certo!
/*void ExibirFormatado(Linha *Inicio)
{
    int Pri_Lin, Rec_Dir, Rec_Esq, TL=0, i=0,j,letras, lin,col, ini=1, neg=0, pos, flag=0;
    char aux[30],vetP[500][30];
    Linha *auxLin = Inicio;
    Letra *auxCursor; 
    system("cls");
    TelaArquivo();
    gotoxy(27,6);
    printf("Configuracao dos paragrafos");
    gotoxy(11,7);
    printf("-----------------------------------------------------------");
    gotoxy(13,9);
    printf("Primeira linha: ");
    gotoxy(30,9);
    scanf("%d",&Pri_Lin);
    gotoxy(13,11);
    printf("Recuo esquerdo: ");
    gotoxy(30,11);
    scanf("%d",&Rec_Esq);
    gotoxy(13,13);
    printf("Recuo direito: ");
    gotoxy(30,13);
    scanf("%d",&Rec_Dir);
 
    //Separa palavras em vet
    while(auxLin!=NULL)
    {
        auxCursor = auxLin->inicioL;
        i=0;
        while(auxCursor!=NULL)
        {
            if(auxCursor->caracter!=' ')
                aux[i++] = auxCursor->caracter;
            else
            {
                aux[i] = '\0';
                strcpy(vetP[TL++],aux);
                i=0;
                aux[i] = '\0';
            }
            auxCursor = auxCursor->prox;
        }
        aux[i] = '\0';
        if(aux[0]!='\0')
            strcpy(vetP[TL++],aux);
        auxLin = auxLin->botton;
    }
    
    //Printa palavras com config acima
    system("cls");
    i=0;
    lin=1;
    col = 1;
    for(int k=0;k<80;k++)
    {
        if(k%5==0)
        {
            if(neg==0)
            {
                neg=1;
                textcolor(14);
            }
            else
            {
                neg=0;
                textcolor(7);
            } 
        }
        gotoxy(col,lin);
        printf("|");
        col++; 
    }
    col=1;
    neg=0;
    textcolor(7); 
    while(i<TL)
    {
    	j=i;
    	letras = 0;
    	flag=0;
    	//Ver quantas palavras caberão na linha
        while(j<TL && letras+strlen(vetP[j])<80-Rec_Dir && flag==0)
        {
        	letras+= strlen(vetP[j]);
        	if(vetP[j][strlen(vetP[j])-1]=='.' || vetP[j][strlen(vetP[j])-1]=='!' || vetP[j][strlen(vetP[j])-1]=='?')
        		flag = 1;
        	j++;
        }
        //Verificar se é a última linha do paragrafo
		if(j<=TL && flag==1)
		{
			while(i<j)
			{
				if(ini==1)
		        {
		            lin++;
		            ini=0;
		            vetP[i][0] = toupper(vetP[i][0]);
		            col = Pri_Lin+1;
		            
		        }
		        else
		        {
		            if(col+strlen(vetP[i])>80-Rec_Dir)
		            {
		                lin++;
		                col=Rec_Esq+1;
		            }            
		        }
		        for(int j=0; j<strlen(vetP[i]); j++)
		        {
		            if(vetP[i][j] == '§')
		            {
		                if(neg==0)
		                {
		                    neg=1;
		                    textcolor(14);
		                }
		                else
		                {
		                    neg=0;
		                    textcolor(7);
		                }
		            }
		            else
		            {
		                gotoxy(col,lin);
		                printf("%c ",vetP[i][j]);
		                col++;
		            }
		        }           
		        col++;
		        i++;
			}
			
		}
		else
		{
		    if(j<TL)
		    {
		        //Ver quantos espaços serao necessarios
    			int palavras = j-i;
    			int dif_letras = 80-Rec_Dir-letras;
    			while(palavras%dif_letras>4)
    			{
    			    j--;
    			    palavras = j-i;
    			    letras = letras - strlen(vetP[j]);
    			    dif_letras = 80-Rec_Dir-letras;
    			}
    			if(palavras%dif_letras <= 4)
    			{
    				while(i<j)
    				{
    					if(ini==1)
    			        {
    			            lin++;
    			            ini=0;
    			            vetP[i][0] = toupper(vetP[i][0]);
    			            col = Pri_Lin+1;
    			            
    			        }
    			        else
    			        {
    			            if(col+strlen(vetP[i])>80-Rec_Dir)
    			            {
    			                lin++;
    			                col=Rec_Esq+1;
    			            }            
    			        }
    			        for(int j=0; j<strlen(vetP[i]); j++)
    			        {
    			            if(vetP[i][j] == '§')
    			            {
    			                if(neg==0)
    			                {
    			                    neg=1;
    			                    textcolor(14);
    			                }
    			                else
    			                {
    			                    neg=0;
    			                    textcolor(7);
    			                }
    			            }
    			            else
    			            {
    			                gotoxy(col,lin);
    			                printf("%c ",vetP[i][j]);
    			                col++;
    			            }
    			        }           
    			        col+= palavras%dif_letras;
    			        col++;
    			        i++;
    				}
    			}  
		    }
		}
    	
        if(vetP[i][strlen(vetP[i])-1]=='.' || vetP[i][strlen(vetP[i])-1]=='!' || vetP[i][strlen(vetP[i])-1]=='?')
            ini=1;
    }
    
    getch();
}*/

void InserePalavra(ListaGen **Palavras, char texto[50],int i)
{
    ListaGen *Nova, *aux, *ant;
    if(texto[i] != '\0')
    {
        //Cria caixa
        Nova = (ListaGen*)malloc(sizeof(ListaGen));
        Nova->prim = NULL;
        Nova->prox = NULL;
        Nova->letra = texto[i];
        if(texto[i+1]!='\0')
            Nova->final = 'F';
        else
            Nova->final = 'T';
        
        //Posiciona caixa
        if(*Palavras == NULL)
        {
            *Palavras = Nova;
            InserePalavra(&Nova->prim,texto,i+1);
        }      
        else
        {
            aux = *Palavras;
            if(texto[i] < aux->letra)
            {
                Nova->prox = aux;
                *Palavras = Nova;
                InserePalavra(&Nova->prim,texto,i+1);
            }
            else
            {
                while(aux!=NULL && texto[i]>aux->letra)
                {
                    ant = aux;
                    aux = aux->prox;
                }
                if(aux==NULL)
                {
                    ant->prox = Nova;
                    InserePalavra(&Nova->prim,texto,i+1);
                }
                else
                {
                    if(texto[i] == aux->letra)
                    {
                        if(Nova->final == 'F')
                            InserePalavra(&aux->prim,texto,i+1);
                        else
                            aux->final = 'T';
                    }
                        
                    else
                    {
                        Nova->prox = aux;
                        ant->prox = Nova;
                        InserePalavra(&Nova->prim, texto, i+1);
                    }
                }                
            }            
        }
    }
}

void SeparaPalavra(ListaGen **Palavras, Letra *Cursor)
{
    char palavra[50];
    int i=0;
    if(Cursor->caracter == 32)
        Cursor = Cursor->ant;
    while(Cursor->ant != NULL && Cursor->ant->caracter!=' ')
        Cursor = Cursor->ant;
    
    while(Cursor!=NULL && Cursor->caracter!=' ')
    {
    	if(Cursor->caracter!='§' && Cursor->caracter!=',' && Cursor->caracter!='.'  && Cursor->caracter!='!' && Cursor->caracter!='?')
        	palavra[i++] = tolower(Cursor->caracter);
        Cursor = Cursor->prox;
    }
    palavra[i] = '\0';
    
    if(strlen(palavra)>2)
    	InserePalavra(&*Palavras,palavra,0);
}

void BuscaPalavra(ListaGen *Palavras,char palavra[50],int i,char Indicar[50])
{
	ListaGen *aux = Palavras;
	if(aux!=NULL)
	{
		if(i<strlen(palavra))
		{
			//Busca na ListaGen a palavra
			while(aux!=NULL && aux->letra<palavra[i])
				aux = aux->prox;
			if(aux==NULL)
				Indicar[0] = '\0';
			else
			{
				if(aux->letra!=palavra[i])
					Indicar[0] = '\0';
				else
				{
					Indicar[i] = aux->letra;
					Indicar[i+1] = '\0';
					if(aux->prim != NULL)
						BuscaPalavra(aux->prim, palavra, i+1, Indicar);
				}
			}
		}
		else
		{
			Indicar[i] = aux->letra;
			Indicar[i+1] = '\0';
			if(aux->final == 'F')
				BuscaPalavra(aux->prim, palavra, i+1, Indicar);
		}		
	}
}

void IndicaPalavra(ListaGen *Palavras, Letra *Cursor)
{
	char palavra[50], Indicar[50];
	Indicar[0] = '\0';
    int i=0;
    if(Cursor->caracter!=' ')
    {
    	while(Cursor->ant != NULL && Cursor->ant->caracter!=' ')
        	Cursor = Cursor->ant;
    
	    while(Cursor!=NULL && Cursor->caracter!=' ')
	    {
	    	if(Cursor->caracter!='§' && Cursor->caracter!=',' && Cursor->caracter!='.' && Cursor->caracter!='!' && Cursor->caracter!='?')
	        	palavra[i++] = tolower(Cursor->caracter);
	        Cursor = Cursor->prox;
	    }
	    palavra[i] = '\0';
	    BuscaPalavra(Palavras,palavra,0,Indicar);
	    gotoxy(35,25);
	    printf("%s",Indicar);
    }
}

void InserePalavra(int *lin, int*col,Linha **CLinha, Letra **Cursor, ListaGen *Palavras)
{
	char palavra[50], Indicar[50];
	Letra *aux = *Cursor;
	Indicar[0] = '\0';
    int i=0;
    if(aux->caracter!=' ')
    {
    	while(aux->ant != NULL && aux->ant->caracter!=' ')
        	aux = aux->ant;
    
	    while(aux!=NULL && aux->caracter!=' ')
	    {
	    	if(aux->caracter!='§' && aux->caracter!=',' && aux->caracter!='.'  && aux->caracter!='!' && aux->caracter!='?')
	        	palavra[i++] = tolower(aux->caracter);
	        aux = aux->prox;
	    }
	    palavra[i] = '\0';
	    BuscaPalavra(Palavras,palavra,0,Indicar);
	    if(Indicar[0]!='\0')
	    	for(i=strlen(palavra);i<strlen(Indicar);i++)
	    		InsereInsert(&*lin,&*col,&*CLinha,&*Cursor,Indicar[i]);
	}
}

void Salvar(Linha *Inicio)
{
    char nome[50];
    FILE*Arq;
    Linha *aux = Inicio;
    Letra *Cursor;
    TelaArquivo();
    gotoxy(25,10);
    printf("Nome que deseja salvar o arquivo:");
    gotoxy(25,12);
    fflush(stdin);
    gets(nome);
    Arq = fopen(nome,"w");
    while(aux!=NULL)
    {
        Cursor = aux->inicioL;
        while(Cursor->prox!=NULL)
        {
            fprintf(Arq,"%c",Cursor->caracter);
            Cursor= Cursor->prox;
        }
        fprintf(Arq,"\n");
        aux = aux->botton;
    }
    fclose(Arq);
    gotoxy(25,14);
    if(stricmp(nome,"\0")!=0)
    	printf("Salvo com sucesso...");
    else
    	printf("Erro: Nome de arquivo invalido!");
    getch();
}

void Abrir(int *lin, int *col,Linha **Inicio,Linha **CLinha, Letra **Cursor, ListaGen **Palavras)
{
    FILE *Arq;
    char info, nome[50];
    TelaArquivo();
    gotoxy(25,10);
    printf("Nome do arquivo:");
    gotoxy(25,12);
    gets(nome);
    Arq = fopen(nome,"r+");
    if(Arq == NULL)
    {
        gotoxy(25,14);
        printf("Erro ao abrir o arquivo...");
        getch();
    }
    else
    {
        if(*Inicio!=NULL)
        {
            Destruir(&*Inicio);
            InicializaEstrutura(&*Inicio,&*CLinha, &*Cursor);
            *lin = 3;
            *col =1;
        }
        fscanf(Arq,"%c",&info);
        while(!feof(Arq))
        {
            if(info == 32)
        		SeparaPalavra(&*Palavras, *Cursor);
        	if(info!=10)
            	InsereLetra(&*lin,&*col,&*CLinha,&*Cursor,info);
            else
            {
                SeparaPalavra(&*Palavras, *Cursor);
            	NovaLinha(&*CLinha, &*Cursor);
        	}
			fscanf(Arq,"%c",&info);
        }
    } 
    fclose(Arq);
}


int main()
{
	char op;
	int lin=3, col=1, Pag, insert=0, xtexto, ytexto, neg=0;
	Linha *Inicio = NULL, *CLinha, *aux, *IniTela;
	Letra *Cursor;
	ListaGen *Palavras = NULL;
	gotoxy(col,lin);
	InicializaEstrutura(&Inicio, &CLinha, &Cursor);
	IniTela = Inicio;
	do 
	{
	    system("cls");
	    Menu();
	    ytexto =3; xtexto =1;
		gotoxy(3,1);
		ExibeLetra(&xtexto,&ytexto,IniTela,Cursor);
		gotoxy(7,25);
    	printf("%d ",col);
    	gotoxy(17,25);
    	printf("%d  ",lin-2);
    	if(insert == 1)
    	{
    	    gotoxy(28,25);
    	    printf("||||");
    	}
    	if(Cursor->ant!=NULL && Cursor->ant->caracter!=' ')
    		IndicaPalavra(Palavras, Cursor);
        gotoxy(col,lin);
		op = getch();
		if(op == -32)
		{		
			op = getch();	
			switch(op) {
				case 82: //INSERT
					Liga_DeslIns(&insert);
                	gotoxy(col,lin);
					break;
				case 71: //HOME
				    Home(&col, CLinha, &Cursor);
					break;
				case 79: //END
				    End(&col, CLinha, &Cursor);
					break;
				case 73: //PAGE UP	
                    PageUp(&lin,&col,&IniTela,Inicio,&Cursor,&CLinha);			
					break;
				case 81: //PAGE DOWN
				    PageDown(&lin,&col,&IniTela,Inicio,&Cursor,&CLinha);	
					break;
				case 83: //DEL
				    Delete(&lin,&col,&CLinha,&Cursor);
					break;
				case 75: //ESQUERDA
					col = AndaEsquerda(col,&Cursor);
		            break;
		        case 72: //CIMA
		        	AndaCima(&lin,&col,&CLinha,&Cursor,Inicio,&IniTela);
		            break;
		        case 77: //DIREITA
		        	col = AndaDireita(col,CLinha,&Cursor);
		            break;
		        case 80: //BAIXO
		        	AndaBaixo(&lin,&col,&CLinha,&Cursor,Inicio,&IniTela);
		            break;
			}
		}
		else if (op == NULL)
		{
			op = getch();
			switch(op) {
				case 60: //F2
					Abrir(&lin,&col,&Inicio, &CLinha, &Cursor, &Palavras);
					IniTela = Inicio;
					ytexto =3; xtexto =1;
					gotoxy(3,1);
					ExibeLetra(&xtexto,&ytexto,IniTela,Cursor);
					col = xtexto;
					lin = ytexto;
            		break;
            	case 61: //F3
            	    Salvar(Inicio);
            		break;
            	case 63: //F5
            	    ExibirFormatado(Inicio);
            		break;
            	case 68: //F10
                	if(insert==0)
            		  InsereInsert(&lin,&col,&CLinha,&Cursor,'§');
            		if(insert==1)
					   InsereLetra(&lin,&col,&CLinha,&Cursor,'§');
        			break;
			}
		}
		else {
			switch(op) {
				case 8: //BACKSPACE
					Backspace(&lin,&col,&Inicio,&CLinha,&Cursor);
					break;
				case 9: //TAB
					InserePalavra(&lin, &col, &CLinha, &Cursor,Palavras);
					break;
				case 13: //ENTER
					SeparaPalavra(&Palavras, Cursor);
                    NovaLinha(&CLinha, &Cursor);
					lin++;
					col = 1;
					if(lin>23)
					{
						lin = 23;
						IniTela = IniTela->botton;
					}
					break;
				case 32://Espaço
				    SeparaPalavra(&Palavras, Cursor);
				    if(insert==0)
					   InsereInsert(&lin,&col,&CLinha,&Cursor, op);
					if(insert==1)
					   InsereLetra(&lin,&col,&CLinha,&Cursor, op);
				    break;
				default: //LETRA
				    if(insert==0)
					   InsereInsert(&lin,&col,&CLinha,&Cursor, op);
					if(insert==1)
					   InsereLetra(&lin,&col,&CLinha,&Cursor, op);
			}
		}
	}while(op!=62); //F4
	return 1;
}
