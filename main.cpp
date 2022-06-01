#include <iostream>
#include <vector>
#include <stdlib.h> // rand
#include <unistd.h> // getpid

using namespace std;

class Celda
{
private:
	int x, y;
	bool mina, descubierta;

public:
	Celda(int x, int y, bool tieneMina)
	{
		this->x = x;
		this->y = y;
		this->mina = tieneMina;
		this->descubierta = false;
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

	string obtenerRepresentacionParaJugador()
	{
		if (this->descubierta)
		{
			if (this->tieneMina())
			{
				return "*";
			}
			else
			{
				return "2";
			}
		}
		else
		{
			return ".";
		}
	}

	string obtenerRepresentacionParaProgramador()
	{
		if (this->tieneMina())
		{
			return "*";
		}
		else
		{
			return "2";
		}
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

	void imprimirSeparadorEncabezado()
	{
		int m;
		for (m = 0; m <= this->anchura; m++)
		{
			cout << "----";
			if (m + 2 == this->anchura)
			{
				cout << "-";
			}
		}
		cout << "\n";
	}

	void imprimirSeparadorFilas()
	{
		int m;
		for (m = 0; m <= this->anchura; m++)
		{
			cout << "+---";
			if (m == this->anchura)
			{
				cout << "+";
			}
		}
		cout << "\n";
	}

	void imprimirEncabezado()
	{
		this->imprimirSeparadorEncabezado();
		cout << "|   ";
		int l;
		for (l = 0; l < this->anchura; l++)
		{
			cout << "| " << l + 1 << " ";
			if (l + 1 == this->anchura)
			{
				cout << "|";
			}
		}
		cout << "\n";
	}

	void imprimir()
	{
		this->imprimirEncabezado();
		this->imprimirSeparadorEncabezado();
		int x, y;
		for (y = 0; y < this->altura; y++)
		{
			cout << "| " << y + 1 << " ";
			for (x = 0; x < this->anchura; x++)
			{
				Celda c = this->contenido.at(y).at(x);
				cout << "| " << c.obtenerRepresentacionParaJugador() << " ";
				if (x + 1 == this->anchura)
				{
					cout << "|";
				}
			}
			cout << "\n";
			this->imprimirSeparadorFilas();
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
		this->tablero.imprimir();
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
	Juego juego(Tablero(5, 5), 3);
}