#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

typedef map<string, vector<string>> mapParser;

vector<string> split(const string& str, const string& delim)
{
	vector<string> tokens;
	size_t prev = 0, pos = 0;
	do
	{
		pos = str.find(delim, prev);
		if (pos == string::npos)
		{
			pos = str.length();
		}
		string token = str.substr(prev, pos - prev);
		if (!token.empty())
		{
			tokens.push_back(token);
		}
		prev = pos + delim.length();
	} while (pos < str.length() && prev < str.length());

	return tokens;
}

void parseFile(string nombre, mapParser &mapaP)
{
    ifstream file;
    file.open(nombre);
    string str; 
    while (getline(file, str))
    {
        auto splitted = split(str, " ");
        mapaP[splitted[0]].push_back(splitted[1]);
    }
    file.close();
}

void printMapParser(mapParser &mapaP)
{
    for (auto it : mapaP)
    {
        cout << it.first << " -> ";
        for (auto it2 : it.second)
        {
            cout << it2 << " ";
        }
        cout << endl;
    }
}

/*Entrada
r1 abc
r1 aab
r2 ab
r2 bc
*/
/*Querys:
r1 aXc
r1 aaX
r2 aX
*/
/*
la salida de este archivo debe ser un conjunto de strings, una por cada consulta, separados por cambio de linea
con todos los valores posibles de X en cada consulta
*/

pair<mapParser, mapParser> parser()
{
    mapParser mapaInput, mapaConsulta;
    parseFile("entradaMiniProlog.txt", mapaInput);
    parseFile("consultaMiniProlog.txt", mapaConsulta);
    return make_pair(mapaInput, mapaConsulta);
}