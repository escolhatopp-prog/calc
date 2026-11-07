#include <stdio.h>

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
    char continuar;

    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            /* entrada inválida: limpa o buffer e volta ao menu */
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("Opção inválida! Tente novamente.\n\n");
            continuar = 's';
            continue;
        }

        if (opcao == 5) {
            break;
        }

        if (opcao < 1 || opcao > 4) {
            printf("Opção inválida! Tente novamente.\n\n");
            continuar = 's';
            continue;
        }

        double a, b;
        printf("Digite o primeiro número: ");
        scanf("%lf", &a);
        printf("Digite o segundo número: ");
        scanf("%lf", &b);

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
                if (b == 0) {
                    printf("Erro: divisão por zero não é permitida.\n");
                } else {
                    printf("Resultado: %g / %g = %g\n", a, b, a / b);
                }
                break;
        }

        printf("Deseja realizar outra operação? (s/n): ");
        scanf(" %c", &continuar);
        printf("\n");

    } while (continuar == 's' || continuar == 'S');

    printf("Obrigado por usar a calculadora! Até a próxima.\n");

    return 0;
}
