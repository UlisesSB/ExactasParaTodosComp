# 🚀 Expo Exactas 2026 - Ingeniería en Computación

Bienvenido al repositorio central de los proyectos interactivos presentados en el stand de **Ingeniería en Computación** para la "Expo Exactas" de la **FACET UNT**. 

Este repositorio consolida cuatro proyectos distintos de software y hardware, diseñados para demostrar de forma visual e interactiva el alcance, las herramientas y el impacto global de nuestra carrera.

---

## 📂 Estructura del Repositorio

El proyecto está diseñado para funcionar como una web unificada hosteada en **GitHub Pages**. Desde el `index.html` principal (el menú) se puede navegar fluidamente entre los distintos módulos:

ExactasParaTodosComputacion/
│
├── index.html                 # Menú principal de la exposición
├── README.md                  # Documentación del repositorio
│
├── Mapa/                      # 🌍 Módulo 1: Mapa Global
│   ├── admin-ingenieros.html  # Panel de carga (Privado)
│   └── mapa-ingenieros.html   # Visualizador Leaflet (Público)
│
├── Carreras/                  # 🎓 Módulo 2: Plan y Diferencias
│   └── index.html             
│
├── Escaner/                   # 📱 Módulo 3: Radar ESP32-C3
│   └── index.html             
│
└── CamaraASCII/               # 🤖 Módulo 4: Visión Artificial
    └── index.html             

---

## 🧩 Descripción de los Módulos

### 🌍 1. Mapa de Egresados
Un visualizador geográfico interactivo de alta calidad desarrollado con **Leaflet.js** que responde a la pregunta: *¿Dónde están hoy nuestros ingenieros?*
* **Animación Automática:** Realiza "vuelos" parabólicos entre distintos países para mostrar el perfil, la empresa y el cargo de los egresados de la facultad.
* **Panel de Administración:** Incluye una interfaz local oculta (`admin-ingenieros.html`) con una herramienta de recorte de imágenes (Cropper.js) para que los encargados del stand puedan cargar nuevos ingenieros y coordenadas en tiempo real sin tocar el código.

### 🎓 2. Plan de Carreras
Una presentación animada e interactiva pensada para orientar a los futuros ingresantes.
* **Desmitificación:** Explica de forma clara las diferencias entre Ingeniería en Computación, Electrónica, Sistemas e Informática.
* **Curricula Visual:** Presenta el plan de estudios completo de la carrera, clasificando y separando visualmente las materias por colores según sus tres pilares fundamentales: **Software**, **Hardware** y **Redes**.

### 📱 3. Escáner de Dispositivos (Radar)
Un proyecto de integración entre hardware y software orientado al análisis de redes. 
* Utiliza un microcontrolador **ESP32-C3** programado para rastrear las tramas de conexión (Probe Requests) emitidas constantemente por los teléfonos móviles a través de **Wi-Fi y Bluetooth (BLE)**.
* **Interfaz de Radar:** Muestra en pantalla los dispositivos cercanos, estimando qué tan lejos se encuentran (en base a la potencia de la señal o RSSI) y determinando la marca del fabricante utilizando las direcciones MAC.

### 🤖 4. Visión Artificial ASCII
Un homenaje a la cultura hacker y la visión por computadora.
* Convierte la transmisión de video de la cámara web en arte **ASCII en tiempo real** directamente en el navegador, sin necesidad de servidores externos.
* Mapea el nivel de luminancia de cada píxel a un arreglo hiper-denso de caracteres, logrando una representación fiel de los visitantes del stand.
* Permite descargar el retrato en formato `.txt`.

---

## 🛠️ Tecnologías Utilizadas

* **Frontend:** HTML5, CSS3 (Variables, Grid, Flexbox), JavaScript Vanilla.
* **Bibliotecas:** Leaflet.js (Mapas), Cropper.js (Edición de imágenes).
* **Hardware:** ESP32-C3 (Módulo de Escáner Inalámbrico).
* **Almacenamiento:** `localStorage` (Persistencia de base de datos JSON en el cliente).

---

## ⚙️ Cómo ejecutar el proyecto localmente

1. Clona este repositorio:
   git clone https://github.com/UlisesSB/ExactasParaTodosComp
   
2. No se requiere instalación de dependencias (Node.js ni NPM). 
3. Simplemente abre la carpeta con Visual Studio Code y ejecuta el `index.html` raíz utilizando la extensión **Live Server**, o sube la carpeta a cualquier hosting estático (como GitHub Pages) para verlo en vivo.

---
Desarrollado por Ulises A. Rodriguez (uarodriguez.com) para el stand de Ingeniería en Computación 2026.