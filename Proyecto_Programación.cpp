/*************INTEGRANTES*************/
//  Mateo Moreno (215814)
//  Micaela Jaramillo(329549)
//  Jonathan Casanova(330016)

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct tPolinomio
{
    int grado;                                                                          /*Grado del polinomio*/
    vector<double> coef;                                                                /*Coeficientes*/
};

bool error_polinomio(string &polinomio);                                                //Funcion Error

void arreglo_grados(string &polinomio, string &polinomio_copia);                        //Funcion Grados

long long grado_mayor(vector<string> &polinomios, int &a);                              //Funcion Grados Mayor de cada Polinomio

int maximo(vector<string> &polinomios);                                                 //Funcion Grado Maximo del Polinomio    

vector<double> coeficiente(vector<string> &polinomios, int a, int max);                 //Funcion Coeficiente

vector<double> suma_monomios(vector<vector<tPolinomio>> &grupo_monomios, int maximo);   //Funcion Suma de Monomios

/***************Punto de Entrada del Programa****************/
int main()
{
    short n(0);
    string polinomio, polinomio_copia;
    vector<string> polinomios;

    cout << "*********************** PROYECTO **********************\n\n"
         << "Ingrese la cantidad de polinomios a sumar: ";
    cin >> n;
    while (n < 1)
    {
        cout << "ERROR!! " << n << " Polinomios no es valido ya que debe ser mayor que 0\n\n"
             << "Ingrese la cantidad de polinomios a sumar: ";
        cin >> n;
    }
    cout << endl;

    /*Pregunta a chatGPT: ¿Como puedo aumentar la cantidad de vectores luego de que el usuario ingreso un el valor de vectores deseados?*/
    vector<vector<tPolinomio>> grupo_monomios(n);           //Utilizar vector de vectores permite almanecer muchos vectores dentro de un mismo vector

    cin.ignore();                                                                               //Ignora caracteres que se quedaron en el bufer
    for (int i = 0; i < n; i++)                                                                 //Se guarda los polinomios
    {
        bool repeticion = false;
        cout << "Polinomio " << i + 1 << ": ";
        while (repeticion != true)
        {
            getline(cin, polinomio);
            repeticion = error_polinomio(polinomio);
            if (repeticion == false)
                cout << "ERROR!! Ingrese de manera correcta el polinomio " << i + 1 << ": ";
        }
        arreglo_grados(polinomio, polinomio_copia);
        polinomios.push_back(polinomio_copia);
    }

    int max_grado = maximo(polinomios);                                                         //Se crea un espacion en donde se guarde el maximo grado de todos los polinomios

    for (int i = 0; i < n; i++)                                                                 //Guarda y separa los monomios en el vector de vectores
    {
        grupo_monomios[i].push_back(tPolinomio());                                              //Agregar un nuevo elemento vacío al vector en la posición i
        grupo_monomios[i][0].grado = grado_mayor(polinomios, i);
        grupo_monomios[i][0].coef = coeficiente(polinomios, i, max_grado);
        grupo_monomios[i][0].coef.pop_back();
    }

    vector<double> total_polinomio(max_grado);                                                  //Se crea el vector que contendra la suma de polinomios

    cout << endl;

    total_polinomio = suma_monomios(grupo_monomios, max_grado);

    cout << "La suma de polinomios es de grado " << max_grado << ":\n";

    for (int i = 0; i <= max_grado; i++)                                                        //Imprime el vector
    {
        if (total_polinomio[i] == 0)
            continue;
        else if (i == 0)
        {
            if (total_polinomio[i] > 0)
                cout << "+" << total_polinomio[i] << " ";
            else
                cout << total_polinomio[i] << " ";
        }
        else if (total_polinomio[i] > 0)
            cout << "+" << total_polinomio[i] << "*x" << i << " ";
        else
            cout << total_polinomio[i] << "*x" << i << " ";
    }

    cout << "\n\n********************** GRACIAS ************************";

    return 0;
}

/**Funcion que analiza si lo que se ingreso es correcto o no**/
bool error_polinomio(string &polinomio)
{
    bool s;
    char siguiente, actual, anterior, a;
    if (polinomio.size() < 3)
        return s = 1;
    else
    {
        for (int i = 1; i < polinomio.size() - 1; i++)                                          //Bucle que analiza cada caracter
        {
            siguiente = polinomio[i + 1];                                                       //Se define 3 variables para analizar en una repeticion 3 posiciones a la vez
            actual = polinomio[i];
            anterior = polinomio[i - 1];
            if ((isalpha(actual) && actual != 'x'))                                             //Retorna 0 para ERROR y 1 para CORRECTO
            {
                s = 0;
                break;
            }
            else if (isalpha(actual) && isalpha(siguiente))
            {
                s = 0;
                break;
            }
            else if (isdigit(anterior) && actual == ' ' && isdigit(siguiente))
            {
                s = 0;
                break;
            }
            else if ((anterior == '+' || anterior == '-') && (actual == '+' || actual == '-'))
            {
                s = 0;
                break;
            }
            else if ((anterior == '+' || anterior == '-') && (actual == ' ') && (siguiente == '+' || siguiente == '-'))
            {
                s = 0;
                break;
            }
            else
                s = 1;
        }
    }
    return s;
}

/**Funcion que añade en una cadena de caracteres *x0**/
void arreglo_grados(string &polinomio, string &polinomio_copia)                                  
{
    char siguiente, actual, anterior, atras;
    int a = 0;
    polinomio_copia = polinomio;                                                                //Se crea 2 string uno para que modificaciones y otro para que analice cada caracter

    for (int i = 1; i < polinomio.size() - 1; i++)
    {
        siguiente = (i + 1 < polinomio.size()) ? polinomio[i + 1] : '\0';                       //Se define 4 variables para analizar en una repeticion 4 posiciones a la vez
        actual = polinomio[i];
        anterior = polinomio[i - 1];
        atras = polinomio[i - 2];
        if ((atras != 'x' && isdigit(anterior) && (actual == ' ') && (siguiente == '+' || siguiente == '-')))
        {
            if (a == 0)
                polinomio_copia.insert(i, "*x0");
            else
                polinomio_copia.insert(i + a, "*x0");
            a += 3;
        }

        else if ((atras != 'x' && isdigit(anterior) && (actual == '+')))
        {
            if (a == 0)
                polinomio_copia.insert(i, "*x0");
            else
                polinomio_copia.insert(i + a, "*x0");
            a += 3;
        }

        else if ((atras != 'x' && isdigit(anterior) && (actual == '-')))
        {
            if (a == 0)
                polinomio_copia.insert(i, "*x0");
            else
                polinomio_copia.insert(i + a, "*x0");
            a += 3;
        }

        else if (isdigit(polinomio.back()) && actual != 'x')
        {
            if (i == polinomio.size() - 2)
                polinomio_copia += "*x0";
        }
        else
            continue;
    }
}

/**Funcion utilizada para encontrar el grado mayor de cada polinomio**/
long long grado_mayor(vector<string> &polinomios, int &a)
{  
    long long grado_m{0}, aux;
    string grado;

    for (int i = 0; i < polinomios[a].length(); i++)
    {
        grado.clear();                                                                          //Cada repeticion reiniciara las variables
        aux = 0;

        /*Pregunta a chatGPT: ¿Que funcion puede reconocer una letra o un numero?*/
        if (isalpha(polinomios[a][i]))                   //La funcion isalpha analiza si el caracter es alfabetico
        {
            i++;
            for (int j = i; j < polinomios[a].length(); j++)
            {
                if (isalpha(polinomios[a][j]))
                    break;
                else
                    grado += polinomios[a][j];
            }

            /*Pregunta a chatGPT: ¿Como convierto un caracter en una valor numerico?*/
            aux = stoi(grado);                           //La funcion stoi transforma un string en un valor int
        }
        if (aux > grado_m)
            grado_m = aux;
    }
    return grado_m;
}

/**Funcion utilizada para encontrar el grado maximo entre todos los polinomios**/
int maximo(vector<string> &polinomios)
{
    int v_max{0}, v_aux{0};

    for (int i = 0; i < polinomios.size(); i++)
    {
        v_aux = grado_mayor(polinomios, i);
        if (v_aux > v_max)
            v_max = v_aux;
    }
    return v_max;
}

/**Funcion utilizada para dividir el polinomio en diferentes monomios**/
vector<double> coeficiente(vector<string> &polinomios, int a, int max)
{
    vector<double> monomio(max + 1, 0);
    string valor, pos_s;
    int pos_v = 0;

    for (int i = 0; i < polinomios[a].size(); i++)                                              //Bucle que separa los coeficiente de cada monomio y le pondra en 1 posicion en base a su grado
    {
        valor.clear(), pos_s.clear();
        if (polinomios[a][i] == '+' || polinomios[a][i] == '-' || isdigit(polinomios[a][i]) || polinomios[a][i] == 'x')
        {
            int signo = 1;
            if (polinomios[a][i] == '-')
                signo = -1;

            for (i; i < polinomios[a].size(); i++)
            {
                if (isalpha(polinomios[a][i]))
                {
                    i++;
                    for (int j = i; j < polinomios[a].size(); j++)
                    {
                        if (isalpha(polinomios[a][j]))
                            break;
                        else
                            pos_s += polinomios[a][j];
                    }
                    pos_v = stoi(pos_s);
                    break;
                }
                else if (isdigit(polinomios[a][i]) || polinomios[a][i] == '.')
                    valor += polinomios[a][i];
                else
                    continue;
            }
            if (pos_v <= max)
            {
                {
                    /*Pregunta a chatGPT: ¿Porque al ingresar stoi con un string este no devuelve un decimal?*/
                    monomio[pos_v] += signo * stod(valor);      // La funcion stoi transforma un string en un valor double
                }
            }
        }
    }
    return monomio;
}

/**Funcion utilizada para sumar los monomios de cada vector**/
vector<double> suma_monomios(vector<vector<tPolinomio>> &grupo_monomios, int maximo)
{
    vector<double> suma(maximo);
    for (int i = 0; i < grupo_monomios.size(); i++)                                             //Bucle para sumar todos los coeficientes obtenidos
    {
        for (int j = 0; j <= grupo_monomios[i][0].coef.size(); j++)
        {
            suma[j] += grupo_monomios[i][0].coef[j];
        }
    }
    return suma;
}
