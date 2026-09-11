# 🎟️ TurnManager — Sistema de Administración de Colas

Proyecto #1 del curso **IC-2001 Estructuras de Datos** — Bachillerato en Ingeniería en Computación, Instituto Tecnológico de Costa Rica.
Prof. Mauricio Avilés · Grupo 40 · 2024

## 📌 Descripción

**TurnoFlow** es el núcleo de un sistema de administración de colas (turnero) desarrollado en **C++**, inspirado en los sistemas de tiquetes numerados que se usan en bancos, hospitales, instituciones de gobierno y comercios. El sistema permite configurar de forma flexible **tipos de usuario**, **servicios**, **áreas** y **ventanillas**, generar tiquetes con una prioridad calculada dinámicamente, atenderlos en orden de prioridad y consultar estadísticas de uso.

El proyecto fue implementado desde cero utilizando **estructuras de datos propias** (listas, colas y montículos genéricos mediante plantillas) y **programación orientada a objetos**, sin depender de contenedores de la STL para el manejo de las entidades del dominio.

## 🎯 Funcionalidades principales

- **Solicitud de tiquetes**: un usuario elige su tipo de usuario y el servicio deseado; el sistema genera un tiquete y lo inserta en la cola de prioridad del área correspondiente.
- **Atención de tiquetes**: una ventanilla extrae el siguiente tiquete de mayor prioridad de la cola de su área y registra la hora de atención.
- **Administración del sistema**: alta, baja y modificación de tipos de usuario, áreas (con sus ventanillas) y servicios, incluyendo el reordenamiento manual de la lista de servicios y la limpieza de colas/estadísticas sin borrar la configuración base.
- **Consulta de estadísticas**: tiempo promedio de espera por área, tiquetes dispensados por área, tiquetes atendidos por ventanilla, tiquetes solicitados por servicio y por tipo de usuario.
- **Interfaz de consola** con menús organizados por sección para probar todas las funcionalidades.

## 🧮 Modelo del dominio

| Entidad | Atributos clave | Notas |
|---|---|---|
| `TipoUsuario` | descripción, prioridad, tiquetes emitidos | Lista ordenada por prioridad. |
| `Servicio` | descripción, prioridad, área asociada, tiquetes solicitados | Orden configurable manualmente (no se reordena por prioridad ni por área). |
| `Area` | descripción, código, ventanillas, servicios, cola de tiquetes, tiquetes dispensados | Cada área gestiona su propia cola de prioridad y una lista paralela para poder recorrer/imprimir su contenido. |
| `Ventanilla` | nombre (código de área + consecutivo), tiquete actual, tiquetes atendidos | Se crean automáticamente al definir un área. |
| `Tiquete` | código (código de área + consecutivo global desde 100), tipo de usuario, servicio, área, hora de creación/atención, prioridad final | La prioridad final se calcula como `PT = PU * 10 + PS` (prioridad de usuario × 10 + prioridad de servicio). |

Al eliminar un elemento del que dependen otros (por ejemplo, un área con servicios y ventanillas asociadas, o un tipo de usuario/servicio con tiquetes en cola), el sistema advierte al usuario y elimina en cascada los datos relacionados para mantener la consistencia.

## 🧱 Estructuras de datos implementadas

Todas las estructuras se implementaron como **plantillas (templates)** genéricas y en **memoria dinámica**, con sus respectivos destructores para la liberación de memoria:

| Estructura | Archivo | Uso en el proyecto |
|---|---|---|
| `List` (interfaz) | `List.h` | Contrato común para listas. |
| `ArrayList<T>` | `ArrayList.h` | Listas de tipos de usuario, servicios, áreas, ventanillas y tiquetes atendidos/copia. |
| `Node<T>` | `Node.h` | Nodo genérico para estructuras enlazadas. |
| `LinkedList<T>` | `LinkedList.h` | Lista enlazada genérica. |
| `Queue` (interfaz) | `Queue.h` | Contrato común para colas. |
| `LinkedQueue<T>` | `LinkedQueue.h` | Cola enlazada genérica. |
| `PriorityQueue` (interfaz) | `PriorityQueue.h` | Contrato común para colas de prioridad. |
| `MinHeap<T>` | `MinHeap.h` | Montículo mínimo usado como base de la cola de prioridad. |
| `HeapPriorityQueue<T>` | `HeapPriorityQueue.h` | Cola de prioridad de cada `Area`, donde se almacenan los tiquetes pendientes por atender. |
| `KVPair<K,V>` | `KVPair.h` | Par llave-valor auxiliar para el manejo interno del heap. |

## 🗂️ Estructura del repositorio

```
.
├── Proyecto1.cpp                # Programa principal: menús y lógica de la interfaz de consola
├── TipoUsuario.h                # Clase TipoUsuario
├── Servicio.h                   # Clase Servicio
├── Area.h                       # Clase Area (agrega ventanillas, servicios y cola de tiquetes)
├── Ventanilla.h                 # Clase Ventanilla
├── Tiquete.h                    # Clase Tiquete
├── List.h / ArrayList.h         # Interfaz y lista basada en arreglo
├── Node.h / LinkedList.h        # Nodo y lista enlazada
├── Queue.h / LinkedQueue.h      # Interfaz y cola enlazada
├── PriorityQueue.h              # Interfaz de cola de prioridad
├── MinHeap.h / HeapPriorityQueue.h  # Montículo y cola de prioridad basada en heap
├── KVPair.h                     # Par llave-valor auxiliar
├── Proyecto1.sln / .vcxproj*    # Archivos de solución/proyecto de Visual Studio
└── README.md                    # Este archivo
```

## 🖥️ Menú del sistema

1. **Estado de las colas** — áreas, ventanillas y tiquetes en espera.
2. **Tiquetes** — seleccionar tipo de usuario y servicio para generar un tiquete.
3. **Atender** — atender el siguiente tiquete en una ventanilla de un área.
4. **Administración**
   - Tipos de usuario (agregar/eliminar)
   - Áreas (agregar, modificar cantidad de ventanillas, eliminar)
   - Servicios disponibles (agregar, eliminar, reordenar)
   - Limpiar colas y estadísticas
5. **Estadísticas del sistema** — tiempos de espera y conteos por área, ventanilla, servicio y tipo de usuario.
6. **Salir**

## ⚙️ Compilación y ejecución

El proyecto incluye un archivo de solución de **Visual Studio** (`Proyecto1.sln`), pero puede compilarse con cualquier compilador de C++ estándar (C++11 o superior):

```bash
g++ -std=c++17 Proyecto1.cpp -o TurnoFlow
./TurnoFlow
```

> El código incluye un método para cargar datos de ejemplo (áreas, servicios, tipos de usuario) al inicio del `main`; actualmente está comentado pero puede activarse para pruebas rápidas.

## 🧪 Notas de diseño

- El manejo de tiempo (hora de creación y atención de un tiquete, cálculo de tiempo de espera) se implementó con `ctime`/`time.h`, y el formato de presentación `hh:mm:ss` con `iomanip`/`sstream`.
- Todas las entidades del dominio (`Area`, `Servicio`, `Ventanilla`, `TipoUsuario`, `Tiquete`) se manejan mediante **punteros en memoria dinámica**, evitando así la necesidad de implementar constructor de copia y operador de asignación para cada una.
- Cada clase implementa un método `print()` para facilitar la inspección de sus datos desde los menús de consola.

## 🔭 Posibles mejoras

- Mejorar la organización de la liberación de memoria dinámica para reducir el riesgo de fugas.
- Expresar el tiempo promedio de espera en minutos/horas en vez de solo segundos cuando aplique.
- Persistencia de datos (guardar/cargar el estado del sistema entre ejecuciones).
- Revisar la eliminación en cascada de áreas para evitar inconsistencias al recalcular estadísticas.

## 👥 Créditos

Proyecto elaborado por **Ariana Jiménez Paniagua** (carné 2023201036) para el curso **IC-2001 Estructuras de Datos**, TEC, 2024.
