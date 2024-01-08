#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <iostream>
#include <WinSock2.h>
#include <stdio.h>
#include <WS2tcpip.h>
#include <Windows.h>

#include <iostream>
#include <queue>
#include <random>
#include <string>
#include <WS2tcpip.h>
#include <corecrt_io.h>
#include "my_socket.h"

class InputData {
public:
    InputData(int rows, int columns, int numberOfAnts, int movement);
    std::string& serialize(std::string& dataToSend) const;
    //void showWorldState(std::string world);
private:
    int rows;
    int columns;
    int numberOfAnts;
    int movement;
};

InputData::InputData(int rows, int columns, int numberOfAnts, int movement) :
        rows(rows),
        columns(columns),
        numberOfAnts(numberOfAnts),
        movement(movement) {
}

std::string &InputData::serialize(std::string &dataToSend) const {
    dataToSend += std::to_string(this->rows) + ";" +
              std::to_string(this->columns) + ";" +
              std::to_string(this->numberOfAnts) + ";" +
              std::to_string(this->movement) + ";";
    return dataToSend;
}



/*void InputData::showWorldState(std::string world) {
    printf("\n");
    for (int i = 0; i < this->columns; ++i) {
        printf("----");
    }
    printf("-\n");
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            switch (world->array_world[i * this->columns + j]) {
                case -1:
                    printf("| # ");
                    break;
                case 1:
                    printf("|   ");
                    break;
                case 2:
                    printf("| . ");
                    break;
                default:
                    printf("Something went wrong with world array. Unexpected character!\n");
                    printf("\nThis is not suppose to be here -> %d\n", world->array_world[i * this->columns + j]);
                    return;
            }
            //printf("%d ", world->array_world[i * world->columns + j]);
        }
        printf("|\n");
        for (int j = 0; j < this->columns; ++j) {
            printf("----");
        }
        printf("-\n");
    }
    printf("\n");
}*/

int main(int argc, char* argv[]) {
    MySocket* mySocket = MySocket::createConnection("frios2.fri.uniza.sk", 11112);

    int rows, columns;
    int numberOfAnts, movement;
    printf("\n--------------------------------------Langton's ants----------------------------------------\n");

    std::cout << "Enter the number of rows in the world: ";
    std::cin >> rows;
    std::cin.ignore();

    std::cout << "Enter the number of columns in the world: ";
    std::cin >> columns;

    std::cout << "Rows X Columns = " << rows << " X " << columns << std::endl;

    std::cout << "How many ants do you want in the world: ";
    std::cin >> numberOfAnts;

    std::cout << "Movement of ants:" << std::endl
              << "0 -> Direct" << std::endl
              << "1 -> Inverse" << std::endl
              << "Choose what movement do you want: ";

    std::cin >> movement;

    std::cout << "You chose a " << movement << " movement with " << numberOfAnts << " ants." << std::endl;

    movement = (movement == 1) ? movement : -1;

    InputData data(rows, columns, numberOfAnts, movement);
    if (mySocket != nullptr) {
        std::string input;
        mySocket->sendData(data.serialize(input));
        mySocket->sendEndMessage();
        std::cout << input << std::endl;


        std::cout << "Cakanie na odpoved od servera\n" << std::endl;

        closesocket(reinterpret_cast<SOCKET>(mySocket));
       // Sleep(5000);
        /*std::string receivedData = mySocket->receiveData();
        std::cout << "Received from server: " << receivedData << std::endl;
        std::cout << receivedData << std::endl;*/
        //sleep(8);
        char buf[1024] = {0};
        int received = recv(reinterpret_cast<SOCKET>(mySocket), buf, sizeof(buf), 0);
        if (received == -1) {
            std::cout << "Prijimanie odpovede neprebehlo uspesne" << std::endl;
            closesocket(reinterpret_cast<SOCKET>(mySocket));
            return -1;
        }
        printf("Anoooo\n");



        /*while (true) {
            char buf[1024];
            mySocket->receiveData(buf);

        }*/
        /*int clientSocket;
        struct sockaddr_in serverAddr;
        char buffer[1024];

        // Create socket
        clientSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (clientSocket == -1) {
            perror("Error creating socket");
            exit(EXIT_FAILURE);
        }

        // Set up server address structure
        memset(&serverAddr, 0, sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(11112);

        // Connect to the server
        if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
            perror("Error connecting to server");
            close(clientSocket);
            exit(EXIT_FAILURE);
        }

        // Receive data from the server
        size_t bytesReceived = recv(clientSocket, buffer, 1023, 0);
        if (bytesReceived == -1) {
            perror("Error receiving data");
        } else {
            buffer[bytesReceived] = '\0';
            printf("Received data from server: %s\n", buffer);
            for (char i : buffer) {
                printf("%c ", i);
            }
        }

        // Close the socket
        close(clientSocket);*/
    }

    /*int sockfd, newsockfd;
    socklen_t cli_len;
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    char buffer[1024];


    //bzero((char*)&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi("11112"));

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Error creating socket");
        return 1;
    }

    if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("Error binding socket address");
        return 2;
    }

    listen(sockfd, 5);
    cli_len = sizeof(cli_addr);

    newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &cli_len);
    if (newsockfd < 0)
    {
        perror("ERROR on accept");
        return 3;
    }

    //bzero(buffer,256);
    n = read(newsockfd, buffer, sizeof(buffer) - 1);
    if (n < 0)
    {
        perror("Error reading from socket");
        return 4;
    }
    printf("Here is the message: %s\n", buffer);

    const char* msg = "I got your message";
    n = write(newsockfd, msg, strlen(msg)+1);
    if (n < 0)
    {
        perror("Error writing to socket");
        return 5;
    }

    close(newsockfd);
    close(sockfd);*/
    /*if (this->serverSocket != nullptr) {
        std::string input;
        this->serverSocket->sendData(piEstimaton.serialize(input));
        this->serverSocket->sendEndMessage();
    }*/
    /*ThreadData data(3000, 10, mySocket);
    std::thread thProduce(produce, std::ref(data));

    consume(data);
    thProduce.join();
*/
    delete mySocket;
    mySocket = nullptr;


    return 0;
}

/*void ThreadData::consume() {
    PiEstimation piEstimaton;
    for (long long i = 1; i <= this->replicationsCount; ++i) {
        Point item;

        {
            std::unique_lock<std::mutex> lock(this->mutex);
            while (this->buffer.size() <= 0) {
                this->isFull.wait(lock);
            }
            item = this->buffer.front();
            this->buffer.pop();
            this->isEmpty.notify_one();
        }
        std::cout << i << ": ";
        piEstimaton.addPoint(item);
        if (i % 1000 == 0 && this->serverSocket != nullptr) {
            std::string input;
            this->serverSocket->sendData(piEstimaton.serialize(input));
        }
    }
    if (this->serverSocket != nullptr) {
        std::string input;
        this->serverSocket->sendData(piEstimaton.serialize(input));
        this->serverSocket->sendEndMessage();
    }
}*/
