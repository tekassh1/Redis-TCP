// #include <iostream>

// using namespace std;

// int main() {
//     while (true) {
//         cntr++;
//         new_connection = accept(s_listen, (SOCKADDR*) &addr, &sizeofaddr);

//         if (new_connection == 0) {
//             cout << "Client connection error!" << endl;
//         }
//         else {
//             cout << "Client connected successfully!" << endl;
//             char msg[256] = "Hello, my client!";
//             send(new_connection, msg, sizeof(msg), NULL);
//         }
//         cout << "Client " << cntr << " connected" << endl;
//     }
// }