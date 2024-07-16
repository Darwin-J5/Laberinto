#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define tamaño 13 //tamaño del laberinto
#define pared '0' //paredes del laberinto
#define camino ' ' //camino para recorrer el laberinto
#define inicio 'A' //comienzo del laberinto
#define fin 'B' //final del laberinto
#define recorrido '.' //camino reccorrido hasta el final

//estructura que define las coordenadas en el laberinto
typedef struct{
    int x, y;
} coordenadas;

//declara la matriz del laberinto
char laberinto[tamaño][tamaño];

//funcion que crea las paredes del laberinto
void CrearParedes(){
    for(int i = 0; i < tamaño; i++){
        for(int j = 0; j < tamaño; j++){
            laberinto[i][j] = pared;
        }
    }
}

//funcion para presentar el laberinto
void PresentarLaberinto(){
    for(int i = 0; i < tamaño; i++){
        for(int j = 0; j < tamaño; j++){
            printf("%c  ", laberinto[i][j]);
        }
        printf("\n");
    }
}

//funcion que crea los caminos del laberinto
void CrearCaminos(int x, int y){
    int direccion[] = {0, 1, 2, 3}; //arreglo que representa las direcciones
    for(int i = 0; i < 4; i++){
        int aleatorio = rand() % 4;
        int temp = direccion[aleatorio];
        direccion[aleatorio] = direccion[i];
        direccion[i] = temp;
    }
    for(int i = 0; i < 4; i++){
        int act_x = x, act_y = y; //posicion actual de la creacion de camino en el laberinto
        switch (direccion[i]){
            case 0: act_x = x + 2; break;
            case 1: act_y = y + 2; break;
            case 2: act_x = x - 2; break;
            case 3: act_y = y - 2; break;
        }
        if(act_x > 0 && act_x < tamaño - 1 && act_y > 0 && act_y < tamaño - 1 && laberinto[act_y][act_x] == pared){
            laberinto[act_y][act_x] = camino;
            laberinto[act_y - (act_y - y)/2][act_x - (act_x - x)/2] = camino;
            CrearCaminos(act_x, act_y);
        }
    }
}

//funcion que crea los caminos dentro del laberinto
void GenerarLaberinto(){
    laberinto[1][1] = camino;
    CrearCaminos(1, 1);
    laberinto[0][1] = inicio;
    laberinto[tamaño - 1][tamaño - 2] = fin;
}

//funcion para resolver automaticamente el laberinto
int Resolver(int x, int y){
    //si las coordenadas se encuentran fuera de lugar, devuelve un valor de 0
    if( x < 0 || y < 0 || x >= tamaño || y >= tamaño){
        return 0;
    }
    //si se encuentra el final en las coordenadas, devuelve un valor de 1
    if(laberinto[y][x] == fin){
        return 1;
    }
    //si la coordenada no es ni el inicio ni un camino, devuelve un valor de 0
    if(laberinto[y][x] != camino && laberinto[y][x] != inicio){
        return 0;
    }
    //marca la posicion actual como parte de la solucion
    laberinto[y][x] = recorrido;
    //intenta moverse hacia las 4 direcciones y si alguna devuelve un valor de 1, la condicion tambien lo hara 
    if(Resolver(x + 1, y) || Resolver(x, y + 1) || Resolver(x - 1, y) || Resolver(x, y - 1)){
        return 1;
    }
    //si ninguna condicion se cumple, se borrara el camino realizado y se devolvera un valor de 0
    laberinto[y][x] = camino;
    return 0;
}

//funcion principal
int main(){
    srand(time(NULL)); //genera un numero aleatorio
    CrearParedes(); //llama a la funcion para crear las paredes del laberinto
    GenerarLaberinto(); //llama a la funcion para generar un laberinto aleatorio
    printf("LABERINTO GENERADO ALEATORIAMENTE:\n\n"); //genera un mensaje para presentar el laberinto
    PresentarLaberinto(); //llama a la funcion para presentar el laberinto generado
    //la condicion llama a la funcion para tratar de resolver el laberinto
    if(Resolver(1, 1)){ //si la funcion devuelve el valor de 1:
        printf("\n\nLABERINTO RESUELTO\n\n"); //genera un mensaje que presenta el laberinto resuelto
        PresentarLaberinto(); //llama a la funcion para presentar el laberinto ya resuelto
    }else{ //de otro modo:
        printf("\n\nNO SE PUEDE RESOLVER EL LABERINTO\n"); //genera un mensaje avisando que no se puede resolver el laberinto
    }
    return 0;
}
