#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

int itemCount = 0, item = 0;
#define BUFFER_SIZE 5
int BUFFER[BUFFER_SIZE];

int produceItem();
void sleepProducer();
void sleepConsumer();
void wakeupConsumer();
void wakeupProducer();
void consumer();
void producer();
void putItemIntoBuffer(int item,int BUFFER[],int *itemCount);
int removeItemFromBuffer(int *itemCount,int BUFFER[]);
void consumeItem();

int produceItem(){
    printf("Se produce un item.\n");
    int numero = rand() % (2);
    return numero;
}

void sleepProducer(){
    Sleep(3000);
    consumer();
}

void putItemIntoBuffer(int item,int BUFFER[],int *itemCount){
    printf("Item que se agregará al Buffer: %d\n", item);
    BUFFER[*itemCount] = item;
    printf("Item colocado en el buffer: %d\n", BUFFER[*itemCount], ", en la posición: %d\n", *itemCount);
    *itemCount = *itemCount + 1;
    Sleep(3000);
}

void wakeupConsumer(){
    Sleep(3000);
    consumer();
}

void producer() {
    printf("Se ingreso al productor.\n");
    while (true) {

        item = produceItem();

        if (itemCount == BUFFER_SIZE) {
            printf("El productor pasa a estado dormido porque el buffer está lleno.\n");
            sleepProducer();
        }

        putItemIntoBuffer(item, BUFFER, &itemCount);
        printf("Cantidad de items en el Buffer actualmente: %d\n", itemCount);

        if (itemCount == BUFFER_SIZE) {
            printf("El consumidor se despierta porque hay elementos en el Buffer.\n");
            wakeupConsumer();
        }
    }
}

void wakeupProducer(){
    Sleep(3000);
    producer();
}

void sleepConsumer(){
    Sleep(3000);
    producer();
}

int removeItemFromBuffer(int *itemCount,int BUFFER[]){
    printf("Se remueve un item del buffer.\n");

    int i = 0;
    int a;
    i = BUFFER[*itemCount-1];

    for(a = 0; a++; a<*itemCount){
        BUFFER[a] = BUFFER[a+1];
    }

    *itemCount = *itemCount - 1;
    return i;
}

void consumeItem(int item){
    printf("El item removido es: %d\n", item);
    Sleep(3000);
}

void consumer(){

    printf("Se ingreso a consumidor.\n");

    while (true) {
        if (itemCount == 0) {
            printf("El consumidor se duerme porque no hay elementos en el Buffer.\n");
            sleepConsumer();
        }

        item = removeItemFromBuffer(&itemCount, BUFFER);

        if (itemCount == 0) {
            printf("Se despierta al productor porque hay espacio en el Buffer.\n");
            wakeupProducer();
        }

        consumeItem(item);
    }
}

void randomConsProd(){
    int numero = rand() % (2);
    if (numero = 0) {
        printf("Productor despierto.\n");
        Sleep(3000);
        producer();
    } else {
        printf("Consumidor despierto.\n");
        Sleep(3000);
        consumer();
    }
}

int main (void){
    randomConsProd();
    return 0;
}
