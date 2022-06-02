#include <iostream>
#include <vector>
#include <stdlib.h> // rand
#include <unistd.h> // getpid
#include <sstream>

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

	bool estaDescubierta()
	{
		return this->descubierta;
	}

	void setDescubierta(bool descubierta)
	{
		this->descubierta = descubierta;
	}
};
class Tablero
{
private:
	int altura, anchura;
	bool modoProgramador; // El modo programador te deja ver las minas y minas cercanas aunque no las hayas descubierto
	vector<vector<Celda>> contenido;

	string obtenerRepresentacionMina(int x, int y)
	{
		Celda c = this->contenido.at(y).at(x);
		if (c.estaDescubierta() || this->modoProgramador)
		{
			if (c.tieneMina())
			{
				return "*";
			}
			else
			{
				int cantidad = this->minasCercanas(y, x);
				string cantidadComoCadena = "";
				stringstream ss;
				ss << cantidad;
				ss >> cantidadComoCadena;
				return cantidadComoCadena;
			}
		}
		else
		{
			return ".";
		}
	}

	int minasCercanas(int fila, int columna)
	{
		int conteo = 0, filaInicio, filaFin, columnaInicio, columnaFin;
		if (fila <= 0)
		{
			filaInicio = 0;
		}
		else
		{
			filaInicio = fila - 1;
		}

		if (fila + 1 >= this->altura)
		{
			filaFin = this->altura - 1;
		}
		else
		{
			filaFin = fila + 1;
		}

		if (columna <= 0)
		{
			columnaInicio = 0;
		}
		else
		{
			columnaInicio = columna - 1;
		}
		if (columna + 1 >= this->anchura)
		{
			columnaFin = this->anchura - 1;
		}
		else
		{
			columnaFin = columna + 1;
		}
		int m;
		for (m = filaInicio; m <= filaFin; m++)
		{
			int l;
			for (l = columnaInicio; l <= columnaFin; l++)
			{
				if (this->contenido.at(m).at(l).tieneMina())
				{
					conteo++;
				}
			}
		}
		return conteo;
	}

public:
	Tablero()
	{
	}
	Tablero(int altura, int anchura, bool modoProgramador)
	{
		this->altura = altura;
		this->anchura = anchura;
		this->modoProgramador = modoProgramador;
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
			if (m <= 1)
			{
				cout << "|---";
			}
			else
			{
				cout << "+---";
			}
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
				cout << "| " << this->obtenerRepresentacionMina(x, y) << " ";
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
	/*
			Regresa false si había una mina. true en caso contrario
		*/
	bool descubrir(int x, int y)
	{
		this->contenido.at(y).at(x).setDescubierta(true);
		Celda celda = this->contenido.at(y).at(x);
		if (celda.tieneMina())
		{
			return false;
		}
		return true;
	}
	void setModoProgramador(bool modoProgramador)
	{
		this->modoProgramador = modoProgramador;
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
		this->jugar();
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

	/*
		solicitarFila y solicitarColumna piden la fila y columna del 1 al N, pero
		recordemos que los índices se manejan del 0 al N-1, por eso es que se resta 1
	*/

	int solicitarFila()
	{
		int fila = 0;
		cout << "Ingresa la fila: ";
		cin >> fila;
		return fila - 1;
	}

	int solicitarColumna()
	{
		int columna = 0;
		cout << "Ingresa la columna: ";
		cin >> columna;
		return columna - 1;
	}

	bool jugadorGana()
	{
		return false;
	}

	void jugar()
	{
		int fila, columna;
		while (true)
		{
			this->tablero.imprimir();
			fila = this->solicitarFila();
			columna = this->solicitarColumna();
			bool ok = this->tablero.descubrir(columna, fila);
			if (!ok)
			{
				cout << "Perdiste\n";
				// El modo programador te permite ver todo. Entonces lo activamos y volvemos a imprimir. No hay problema porque el jugador ya perdió
				this->tablero.setModoProgramador(true);
				this->tablero.imprimir();
				break;
			}

			if (this->jugadorGana())
			{
				cout << "Ganaste\n";
				break;
			}
		}
	}
};

int main()
{
	srand(getpid());
	Juego juego(Tablero(5, 5, false), 3);
}