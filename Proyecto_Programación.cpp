#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct tPolinomio
{
    int grado;           /*Grado del polinomio*/
    vector<double> coef; /*Coeficientes*/
};

int grado_mayor(vector<string> &polinomios, int a)
{
    int grado_m{0}, aux;
    string grado;

    for (int i = 0; i < polinomios[a].size(); i++)
    {
        grado.clear();
        aux = 0;

        if (isalpha(polinomios[a][i])) 
        {
            i++;
            for (int j = i; j < polinomios[a].size(); j++)
            {
                if (isalpha(polinomios[a][j]))
                    break;
                else
                    grado += polinomios[a][j];
            }

            aux = stoi(grado);
        }
        if (aux > grado_m)
            grado_m = aux;
    }
    return grado_m;
}

int maximo(vector<string> &polinomios)
{
    int max{0}, aux{0};

    for (int i = 0; i < polinomios.size(); i++)
    {
        aux = grado_mayor(polinomios, i);
        if (aux > max)
            max = aux;
    }
    return max;
}

vector<double> coeficiente(vector<string> &polinomios, int a, int max)
{
    vector<double> monomio(max, 0);
    string valor, pos_s;
    int pos_v{0};

    for (int i = 0; i < polinomios[a].size(); i++)
    {
        valor.clear(), pos_s.clear();
        if (polinomios[a][i] == '+' || polinomios[a][i] == '-' || isdigit(polinomios[a][i]))
        {
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
                else if (isdigit(polinomios[a][i]))
                    valor += polinomios[a][i];
                else
                    continue;
            }
            monomio[pos_v] = stod(valor);
        }
    }
    return monomio;
}

int main()
{
    short n(0);
    string polinomio;
    vector<string> polinomios;
    vector<tPolinomio> grupo_monomios;

    cout << "Ingrese la cantidad de polinomios a sumar: ";
    cin >> n;

    cin.ignore();
    for (int i = 0; i < n; i++)
    {
        cout << "Polinomio " << i + 1 << ": ";
        getline(cin, polinomio);
        polinomios.push_back(polinomio);
    }

    int max = maximo(polinomios);

    for (int i = 0; i < n; i++)
        grupo_monomios.push_back({grado_mayor(polinomios, i), coeficiente(polinomios, i, max)});
    
    return 0;
}

