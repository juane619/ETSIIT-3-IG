# ETSIIT_IG_P4
Juan Emilio García Martínez
Practice 4 of Computer Graphics

Uso: ./bin/practica4 'archivo_ply' ['archivo_rev'].

- Cambiar modo de pintado de cada figura: c(ajedrez), f(sólido), t(todo), l(lines).

- Figuras que se pueden dibujar:
	- Tecla 1: tetraedro.
	- Tecla 2: cubo.
	- Tecla 3: archivo ply. (si no existe, no pintará nada)
	- Tecla 4: revolución (si no se especifica archivo, se crearán los vértices a mano)
		Pintar tapas ('/') o no ('*')
		Añadir lado ('+'). Quitar lado ('-').
	- Tecla 5: modelo jerárquico (maquina excavadora giratoria con ruedas).
	
		Tiene varias funcionalidades(grados de libertad): giro del cuerpo(m/M), apertura/cerrado del brazo completo(n/N), mitad del brazo(b/B) 
		y cazo(v/V), movimiento de la máquina completa(w avanzar, s retroceder, segun la orientación de la máquina).
		
		Aumento/disminución de velocidad de cada grado de libertad: pistones(h/H), giro del cuerpo(j/J), velocidad máquina y ruedas(k/K).
	- Tecla 6: extra P1, prisma.
	- Tecla 7: extra P2, barrido. 
				
				Hay tres formas de generar por barrido. Yo implemento dos de ellas: por traslación y por revolución (respectivos constructores)
				Se puede elegir si pintar tapas de barrido o no por parámetro en constructor.

