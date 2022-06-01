#include <iostream>
#include <vector>
#include <stdlib.h> // rand
#include <unistd.h> // getpid

using namespace std;

class Celda
{
private:
	int x, y;
	bool mina;

public:
	Celda(int x, int y, bool tieneMina)
	{
		this->x = x;
		this->y = y;
		this->mina = tieneMina;
	}
	void imprimir()
	{
		cout << "Celda en " << this->x << ", " << this->y << " con mina? " << this->mina << "\n";
	}

	bool establecerMina(bool tieneMina)
	{
		if (this->tieneMina())
		{
			return false;
		}
		else
		{
			this->mina = tieneMina;
			return true;
		}
	}

	bool tieneMina()
	{
		return this->mina;
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
	Tablero()
	{
	}
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

	bool colocarMina(int x, int y)
	{
		return this->contenido.at(y).at(x).establecerMina(true);
	}

	int obtenerAltura()
	{
		return this->altura;
	}
	int obtenerAnchura()
	{
		return this->anchura;
	}
};

class Juego
{
private:
	Tablero tablero;
	int cantidadMinas;

	int aleatorio_en_rango(int minimo, int maximo)
	{
		return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
	}

	int filaAleatoria()
	{
		return this->aleatorio_en_rango(0, this->tablero.obtenerAltura() - 1);
	}

	int columnaAleatoria()
	{
		return this->aleatorio_en_rango(0, this->tablero.obtenerAnchura() - 1);
	}

public:
	Juego(Tablero tablero, int cantidadMinas)
	{
		this->tablero = tablero;
		this->cantidadMinas = cantidadMinas;
		this->colocarMinasAleatoriamente();
	}

	void colocarMinasAleatoriamente()
	{
		int x, y, minasColocadas = 0;

		while (minasColocadas < this->cantidadMinas)
		{
			x = this->columnaAleatoria();
			y = this->filaAleatoria();
			if (this->tablero.colocarMina(x, y))
			{
				minasColocadas++;
			}
		}
	}
};

int main()
{
	srand(getpid());
	Juego juego(Tablero(3, 2), 3);
}