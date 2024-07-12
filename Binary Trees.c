#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct arvore
{
    int info;
    struct arvore *esq;
    struct arvore *dir;
} arvore;

arvore *LerArvore(FILE *arq)
{

    char c;
    int num;

    fscanf(arq, "%c", &c);
    fscanf(arq, "%d", &num);

    if (num == -1)
    {
        fscanf(arq, "%c", &c);
        return NULL;
    }
    else
    {
        arvore *a = (arvore *)malloc(sizeof(arvore));
        a->info = num;
        a->esq = LerArvore(arq);
        a->dir = LerArvore(arq);
        fscanf(arq, "%c", &c);
        return a;
    }
}

void ImprimirPreOrdem(arvore *a)
{

    if (a == NULL)
    {
        return;
    }

    printf("%d ", a->info);
    ImprimirPreOrdem(a->esq);
    ImprimirPreOrdem(a->dir);
}

void ImprimirEmOrdem(arvore *a)
{

    if (a == NULL)
    {
        return;
    }

    ImprimirEmOrdem(a->esq);
    printf("%d ", a->info);
    ImprimirEmOrdem(a->dir);
}

void ImprimirPosOrdem(arvore *a)
{

    if (a == NULL)
    {
        return;
    }

    ImprimirPosOrdem(a->esq);
    ImprimirPosOrdem(a->dir);
    printf("%d ", a->info);
}

int altura(arvore *a)
{

    if (a == NULL)
    {
        return 0;
    }
    else
    {
        int he, hd;
        he = altura(a->esq);
        hd = altura(a->dir);

        if (he > hd)
        {
            return he + 1;
        }
        else
        {
            return hd + 1;
        }
    }
}

void ImprimirNivel(arvore *a, int cont, int nivel)
{

    if (a != NULL)
    {
        if (cont == nivel)
        {
            printf("%d ", a->info);
        }
        else
        {
            ImprimirNivel(a->esq, cont + 1, nivel);
            ImprimirNivel(a->dir, cont + 1, nivel);
        }
    }
}

void ImprimirEmLargura(arvore *a)
{

    if (a != NULL)
    {
        int i;
        int h = altura(a);

        for (i = 0; i < h; i++)
        {
            ImprimirNivel(a, 0, i);
            printf("\n");
        }
    }
}

int VerificarSeExisteX(arvore *a, int x)
{

    if (a == NULL)
    {
        return 0;
    }

    if (a->info == x)
    {
        return 1;
    }
    else if (a->info > x)
    {
        return VerificarSeExisteX(a->esq, x);
    }
    else
    {
        return VerificarSeExisteX(a->dir, x);
    }
}

int ImprimirNivelNo(arvore *a, int x)
{

    if (a != NULL)
    {
        if (a->info == x)
        {
            return 0;
        }

        int ret;

        if (a->info > x)
        {
            ret = ImprimirNivelNo(a->esq, x);
            if (ret != -1)
            {
                return ret + 1;
            }
        }
        else
        {
            ret = ImprimirNivelNo(a->dir, x);
            if (ret != -1)
            {
                return ret + 1;
            }
        }
    }
    return -1;
}

void ImprimirFolhasMenoresX(arvore *a, int x)
{
    if (a == NULL)
    {
        return;
    }
    if (a->esq == NULL && a->dir == NULL && a->info < x)
    {
        printf("%d ", a->info);
    }
        ImprimirFolhasMenoresX(a->esq, x);
        ImprimirFolhasMenoresX(a->dir, x);

}

arvore *InserirElemento(arvore *a, int x)
{
    if (a == NULL)
    {
        arvore *noNovo = (arvore *)malloc(sizeof(arvore));
        noNovo->info = x;
        noNovo->esq = NULL;
        noNovo->dir = NULL;
        return noNovo;
    }
    if (a->info > x)
    {
        a->esq = InserirElemento(a->esq, x);
    }
    else
    {
        a->dir = InserirElemento(a->dir, x);
    }

    return a;
}

arvore *RemoverElemento(arvore *a, int x)
{
    if (a != NULL)
    {
        if (a->info == x)
        {
            if (a->esq == NULL && a->dir == NULL)
            {
                free(a);
                return NULL;
            }
            else if (a->esq == NULL)
            {
                arvore *aux = a->dir;
                free(a);
                return aux;
            }
            else if (a->dir == NULL)
            {
                arvore *aux = a->esq;
                free(a);
                return aux;
            }
            else
            {
                arvore *aux = a->esq;
                while (aux->dir != NULL)
                {
                    aux = aux->dir;
                }
                a->info = aux->info;
                a->esq = RemoverElemento(a->esq, aux->info);
            }
        }
        else if (a->info > x)
        {
            a->esq = RemoverElemento(a->esq, x);
        }
        else
        {
            a->dir = RemoverElemento(a->dir, x);
        }
    }
    return a;
}

void ApagaArvore(arvore *a) {
    if (a == NULL) {
        return;
    }
    ApagaArvore(a->esq);
    ApagaArvore(a->dir);
    free(a);
}

int main()
{

    FILE *arq;
    int aux, aux2;
    arvore *a;

    do
    {
        printf("\nEscolha uma opcao:\n");
        printf("1. Ler arvore do arquivo\n");
        printf("2. Imprimir arvore\n");
        printf("3. Verificar se existe um elemento\n");
        printf("4. Imprimir Nivel de um No X\n");
        printf("5. Imprimir Folhas menores que:\n");
        printf("6. Inserir Elemento\n");
        printf("7. Remover Elemento\n");
        printf("8. Sair\n");

        scanf("%d", &aux);
        switch (aux)
        {
        case 1:
            arq = fopen("arvore2.txt", "rt");
            if (arq == NULL)
            {
                printf("Erro ao abrir o arquivo");
                return 1;
            }
            a = LerArvore(arq);
            fclose(arq);
            break;
        case 2:
            printf("\nEscolha uma opcao:\n");
            printf("1. Pre-Ordem\n");
            printf("2. Em-Ordem\n");
            printf("3. Pos-Ordem\n");
            printf("4. Em Largura\n");

            scanf("%d", &aux);

            switch (aux)
            {
            case 1:
                ImprimirPreOrdem(a);
                break;
            case 2:
                ImprimirEmOrdem(a);
                break;
            case 3:
                ImprimirPosOrdem(a);
                break;
            case 4:
                ImprimirEmLargura(a);
            }
            break;
        case 3:
            printf("Valor:\n");
            scanf("%d", &aux);

            aux2 = VerificarSeExisteX(a, aux);

            if (aux2 == 1)
            {
                printf("Existe");
            }
            else
            {
                printf("Nao Existe");
            }
            break;
        case 4:
            printf("Valor:\n");
            scanf("%d", &aux2);
            int aux3 = ImprimirNivelNo(a, aux2);
            if (aux != -1)
            {
                printf("Nivel: %d\n", aux3);
            }
            else
            {
                printf("Valor %d não encontrado na árvore.\n", aux2);
            }
            break;
        case 5:
            printf("Valor:\n");
            scanf("%d", &aux2);
            ImprimirFolhasMenoresX(a, aux2);
            break;
        case 6:
            printf("Valor:\n");
            scanf("%d", &aux2);
            a = InserirElemento(a, aux2);
            break;
        case 7:
            printf("Valor:\n");
            scanf("%d", &aux2);
            a = RemoverElemento(a, aux2);
            break;
        case 8:
            ApagaArvore(a);
            printf("Fim..");
            break;
        }
    } while (aux != 8);

    return 0;
}