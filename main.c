#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

/* Lê uma linha inteira (descarta o excesso se a linha for longa).
   Retorna 0 se a entrada acabou (EOF). */
int ler_linha(char *buf, int tam) {
    if (fgets(buf, tam, stdin) == NULL)
        return 0;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;
    }
    return 1;
}

/* Só aceita se o resto da linha for vazio ou espaços. */
int so_espacos(const char *p) {
    while (*p) {
        if (!isspace((unsigned char)*p))
            return 0;
        p++;
    }
    return 1;
}

/* Lê a opção do menu. Retorna 1 se válida, 0 se inválida, -1 se EOF. */
int ler_opcao(int *opcao) {
    char buf[64];
    char *fim;

    if (!ler_linha(buf, sizeof buf))
        return -1;

    long v = strtol(buf, &fim, 10);
    if (fim == buf || !so_espacos(fim))
        return 0;
    if (v < 1 || v > 5)
        return 0;

    *opcao = (int)v;
    return 1;
}

/* Pede um número até o usuário digitar um valor válido. Retorna 0 em EOF. */
int ler_numero(const char *mensagem, double *valor) {
    char buf[64];
    char *fim;

    while (1) {
        printf("%s", mensagem);
        if (!ler_linha(buf, sizeof buf))
            return 0;

        double v = strtod(buf, &fim);
        if (fim != buf && so_espacos(fim) && isfinite(v)) {
            *valor = v;
            return 1;
        }
        printf("Entrada inválida! Digite um número.\n");
    }
}

/* Pergunta s/n até receber uma resposta válida. Retorna 1 (s), 0 (n). */
int perguntar_continuar(void) {
    char buf[64];

    while (1) {
        printf("Deseja realizar outra operação? (s/n): ");
        if (!ler_linha(buf, sizeof buf))
            return 0;

        char *p = buf;
        while (isspace((unsigned char)*p))
            p++;

        char c = tolower((unsigned char)*p);
        if ((c == 's' || c == 'n') && so_espacos(p + 1))
            return c == 's';

        printf("Resposta inválida! Digite 's' ou 'n'.\n");
    }
}

void exibir_menu(void) {
    printf("===============================\n");
    printf("   Calculadora Simples\n");
    printf("===============================\n");
    printf("Selecione uma operação:\n");
    printf("1. Adição\n");
    printf("2. Subtração\n");
    printf("3. Multiplicação\n");
    printf("4. Divisão\n");
    printf("5. Sair\n");
    printf("Opção: ");
}

int main(void) {
    int opcao;
    double a, b;

    while (1) {
        exibir_menu();

        int status = ler_opcao(&opcao);
        if (status == -1)
            break;
        if (status == 0) {
            printf("Opção inválida! Digite um número de 1 a 5.\n\n");
            continue;
        }

        if (opcao == 5)
            break;

        if (!ler_numero("Digite o primeiro número: ", &a))
            break;
        if (!ler_numero("Digite o segundo número: ", &b))
            break;

        switch (opcao) {
            case 1:
                printf("Resultado: %g + %g = %g\n", a, b, a + b);
                break;
            case 2:
                printf("Resultado: %g - %g = %g\n", a, b, a - b);
                break;
            case 3:
                printf("Resultado: %g * %g = %g\n", a, b, a * b);
                break;
            case 4:
                if (b == 0)
                    printf("Erro: divisão por zero não é permitida.\n");
                else
                    printf("Resultado: %g / %g = %g\n", a, b, a / b);
                break;
        }

        if (!perguntar_continuar())
            break;
        printf("\n");
    }

    printf("Obrigado por usar a calculadora! Até a próxima.\n");

    return 0;
}
