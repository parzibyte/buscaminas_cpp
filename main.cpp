#include <iostream>
#include <vector>

using namespace std;

class Celda
{
private:
	int x, y;
	bool tieneMina;

public:
	Celda(int x, int y, bool tieneMina)
	{
		this->x = x;
		this->y = y;
		this->tieneMina = tieneMina;
	}
	void imprimir()
	{
		cout << "Celda en " << this->x << ", " << this->y << " con mina? " << this->tieneMina << "\n";
	}
};
class Tablero
{
private:
	// const int altura = 10;
	//  int contenido[this->altura][3]; // Aquí cambiar la altura, anchura
	int altura, anchura;
	vector<vector<Celda>> contenido;

public:
	Tablero(int altura, int anchura)
	{
		this->altura = altura;
		this->anchura = anchura;
		int x, y;
		for (y = 0; y < this->altura; y++)
		{
			vector<Celda> fila;
			for (x = 0; x < this->anchura; x++)
			{
				fila.push_back((Celda(x, y, false)));
			}
			this->contenido.push_back(fila);
		}
	}

	void imprimir()
	{

		int x, y;
		for (y = 0; y < this->altura; y++)
		{
			for (x = 0; x < this->anchura; x++)
			{
				Celda c = this->contenido.at(y).at(x);
				c.imprimir();
			}
		}
	}
};

int main()
{
	Tablero t(7, 3);
	t.imprimir();
	// cout << "Hola";
}