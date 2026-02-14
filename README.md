*This project has been created as part of the 42 curriculum by msedeno-.*

# Philosophers - 42 School Project

![Language](https://img.shields.io/badge/Language-C-blue)
![School](https://img.shields.io/badge/School-42-black)
![Success](https://img.shields.io/badge/Success-100%2F100-success)

---

## 🇬🇧 English Version

### Description
The **Philosophers** project serves as an introduction to the basics of **concurrent programming**. The objective is to solve the famous "Dining Philosophers" problem using **threads** and **mutexes**.

The project helps in learning how to:
- Create and manage threads with `pthread`.
- Synchronize access to shared resources using mutexes to prevent **data races**.
- Avoid **deadlocks** and handle resource starvation.
- Monitor execution states efficiently.

### Instructions

**Installation & Compilation:**
1. Clone the repository into your project folder.
2. Run `make` to compile the mandatory part. This will generate the `philo` executable.
   ```bash
   make
   ```
3. To compile with **Thread Sanitizer** (useful for debugging data races during development), run:
   ```bash
   make debug
   ```
4. To run memory and threading checks with **Valgrind/Helgrind**, run:
   ```bash
   make helgrind
   ```
5. To clean up object files, run `make clean`. To remove everything including the executable, run `make fclean`. To recompile from scratch, use `make re`.

**Usage:**
Run the program with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
1. `number_of_philosophers`: The number of philosophers and also the number of forks.
2. `time_to_die`: Time in milliseconds. If a philosopher doesn't start eating 'time_to_die' ms after the beginning of their last meal or the start of the simulation, they die.
3. `time_to_eat`: The time it takes for a philosopher to eat via holding two forks.
4. `time_to_sleep`: The time the philosopher will spend sleeping.
5. `[number_of_times_each_philosopher_must_eat]` (optional): If all philosophers eat at least this many times, the simulation will stop. If not specified, the simulation stops only when a philosopher dies.

**Example:**
```bash
./philo 5 800 200 200
```
*This starts a simulation with 5 philosophers, where a philosopher dies if not eating for 800ms, takes 200ms to eat, and 200ms to sleep.*

### Project Structure & Key Concepts

| Component | Description |
| :--- | :--- |
| **Threads (Pthreads)** | Each philosopher runs as a separate thread. A "Big Sister" monitor thread runs in parallel to check for deaths. |
| **Mutexes** | Protecting shared resources: forks, writing to the console (`write_mutex`), data updates (`meal_mutex`), and status flags (`death_mutex`). |
| **Deadlock Prevention** | Implemented via resource hierarchy or odd/even split strategy to prevent circular wait conditions. |
| **Timestamping** | All state changes are printed with a timestamp in milliseconds. |

### Resources  
**References:**  
- [Dining Philosophers Problem (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [Pthreads Man Pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Valgrind Helgrind Manual](https://valgrind.org/docs/manual/hg-manual.html)

---

## 🇪🇸 Versión en Español

### Descripción
El proyecto **Philosophers** sirve como introducción a los fundamentos de la **programación concurrente**. El objetivo es resolver el famoso problema de "La Cena de los Filósofos" utilizando **hilos (threads)** y **mutexes**.

Este proyecto permite aprender a:
- Crear y gestionar hilos con `pthread`.
- Sincronizar el acceso a recursos compartidos usando mutexes para evitar condiciones de carrera (**data races**).
- Evitar interbloqueos (**deadlocks**) y gestionar la inanición de recursos.
- Monitorizar estados de ejecución de forma eficiente.

### Instrucciones

**Instalación y Compilación:**
1. Clona el repositorio en tu carpeta de proyecto.
2. Ejecuta `make` para compilar la parte obligatoria. Esto generará el ejecutable `philo`.
   ```bash
   make
   ```
3. Para compilar con **Thread Sanitizer** (útil para depurar data races durante el desarrollo), ejecuta:
   ```bash
   make debug
   ```
4. Para ejecutar comprobaciones de memoria y concurrencia con **Valgrind/Helgrind**, ejecuta:
   ```bash
   make helgrind
   ```
5. Para limpiar los archivos objeto, ejecuta `make clean`. Para eliminar todo, incluido el ejecutable, ejecuta `make fclean`. Para recompilar desde cero, usa `make re`.

**Uso:**
Ejecuta el programa con los siguientes argumentos:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Argumentos:**
1. `number_of_philosophers`: El número de filósofos y también el número de tenedores.
2. `time_to_die`: Tiempo en milisegundos. Si un filósofo no empieza a comer 'time_to_die' ms después del inicio de su última comida o del inicio de la simulación, muere.
3. `time_to_eat`: El tiempo que tarda un filósofo en comer usando dos tenedores.
4. `time_to_sleep`: El tiempo que pasa el filósofo durmiendo.
5. `[number_of_times_each_philosopher_must_eat]` (opcional): Si todos los filósofos comen al menos este número de veces, la simulación se detiene. Si no se especifica, la simulación solo se detiene cuando muere un filósofo.

**Ejemplo:**
```bash
./philo 5 800 200 200
```
*Esto inicia una simulación con 5 filósofos, donde un filósofo muere si no come en 800ms, tarda 200ms en comer y 200ms en dormir.*

### Estructura del Proyecto y Conceptos Clave

| Componente | Descripción |
| :--- | :--- |
| **Hilos (Threads)** | Cada filósofo se ejecuta como un hilo independiente. Un hilo supervisor (`Big Sister`) corre en paralelo para verificar muertes. |
| **Mutexes** | Protegen recursos compartidos: tenedores, escritura en consola (`write_mutex`), actualizaciones de datos (`meal_mutex`) y banderas de estado (`death_mutex`). |
| **Prevención Deadlocks** | Implementada mediante jerarquía de recursos o estrategia par/impar para evitar condiciones de espera circular. |
| **Marcas de Tiempo** | Todos los cambios de estado se imprimen con una marca de tiempo en milisegundos. |

### Recursos
**Referencias:**
- [Problema de la cena de los filósofos (Wikipedia)](https://es.wikipedia.org/wiki/Problema_de_la_cena_de_los_fil%C3%B3sofos)
- [Pthreads Man Pages](https://man7.org/linux/man-pages/man7/pthreads.7.html)
- [Valgrind Helgrind Manual](https://valgrind.org/docs/manual/hg-manual.html)
