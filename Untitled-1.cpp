#include <iostream>
#include <vector>
#include <string> /*Para que pueda leer de mejor forma el string*/
using namespace std;

struct tPolinomio
{
    int grado; /*Grado del polinomio*/
    vector<double>coef; /*Coeficiente*/
};

int grado_pol(string &cadena_pol); /*Identifica el grado del polinomio*/

int main(){
    int num;
    string cadena_pol;
    vector<string>temp_pol; /*Guarda los datos del polinomio*/

    cout<<"Introduzca la cantidad de polinomios a sumar: ";
    cin>>num;
    cin.ignore(); /*Se utilizo ChatGPT porque daba un error al ingresar el polinomio*/
    for (int i = 1; i<num+1; i++){
        cout<<"Polinomio "<<i<<": ";
        getline(cin, cadena_pol);
        temp_pol.push_back(cadena_pol);
    }
    

    return 0; 
}

int grado_pol(string &cadena_pol){

}