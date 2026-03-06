# FusionANNS

FusionANNS ist ein Lern- und Experimentierprojekt in **C++20** für
Approximate Nearest Neighbor (ANN) Retrieval.  
Der aktuelle Stand ist ein **sauberes MVP-Grundgerüst**, das bewusst klein
gehalten ist: einfache Vektoren, Distanzfunktionen, ein brutaler
Baseline-Index (Linear Scan) und ein lauffähiges Beispiel.

## Status (MVP)

Der aktuelle Code ist auf **Struktur und Korrektheit** ausgelegt, nicht auf
maximale Performance.

Bereits implementiert:

- CMake-basierter Build mit C++20
- Core-Library `fusionanns_core`
- Abstraktes `Index`-Interface
- `FlatIndex` als brute-force Referenzimplementierung
- Distanzfunktionen `l2_distance` und `inner_product`
- Beispielprogramm `fusionanns`
- Minimaler Test `fusionanns_basic_test` (über CTest)

Noch nicht implementiert:

- HNSW / graph-basierte ANN-Algorithmen
- Quantisierung (z. B. PQ)
- SIMD / Multithreading / GPU
- Benchmark- und Profiling-Infrastruktur

## Projektziele

Langfristig soll FusionANNS eine modulare Plattform für ANN-Experimente werden:

- verschiedene Index-Strategien unter einer gemeinsamen API
- reproduzierbare Vergleiche von Recall, Latenz, Speicherbedarf
- saubere Trennung von Datenmodell, Distanzmetriken, Indexlogik und Tests

Das aktuelle MVP bildet dafür die technische Grundlage.

## Projektstruktur

```text
FusionANNS/
├── CMakeLists.txt
├── include/
│   └── fusionanns/
│       ├── distance.h
│       ├── index.h
│       └── vector.h
├── src/
│   ├── distance.cpp
│   ├── flat_index.cpp
│   ├── main.cpp
│   └── vector.cpp
├── tests/
│   └── basic_test.cpp
├── TASK.md
└── README.md
```

## Architekturüberblick

### 1) `Vector`

Dateien: `include/fusionanns/vector.h`, `src/vector.cpp`

Aufgaben:

- Speicherung eines dichten Float-Vektors
- Zugriff auf Dimension über `dim()`
- Elementzugriff über `operator[]` (bounds-checked via `std::vector::at`)

Konstruktoren:

- `Vector(std::size_t dim)`: erstellt einen Nullvektor dieser Dimension
- `Vector(std::vector<float> data)`: übernimmt Daten; wirft bei leerem Vektor
  `std::invalid_argument`

### 2) Distanzfunktionen

Dateien: `include/fusionanns/distance.h`, `src/distance.cpp`

Implementiert:

- `float l2_distance(const Vector& a, const Vector& b)`
- `float inner_product(const Vector& a, const Vector& b)`

Verhalten:

- Beide Funktionen prüfen gleiche Dimension.
- Bei Dimensionsfehler: `std::invalid_argument`.

Hinweis: `l2_distance` gibt aktuell die **quadratische L2-Distanz**
(`sum((a_i - b_i)^2)`) zurück, ohne `sqrt`.

### 3) Index-API und FlatIndex

Dateien: `include/fusionanns/index.h`, `src/flat_index.cpp`

`Index` ist ein abstraktes Interface:

- `void add(const Vector& v)`
- `std::size_t search(const Vector& query, std::size_t k, std::vector<std::size_t>& results) const`

Erzeugung einer konkreten Implementierung erfolgt über:

- `std::unique_ptr<Index> make_flat_index();`

`FlatIndex`-Verhalten:

- speichert Vektoren intern in einem `std::vector<Vector>`
- prüft konsistente Dimension beim Einfügen
- `search(...)`:
  - leert `results`
  - liefert bei leerem Index oder `k == 0` direkt `0`
  - berechnet L2-Distanzen für alle Vektoren
  - bestimmt Top-`k` über `std::partial_sort`
  - schreibt die Indizes der nächsten Nachbarn in `results`

## Build und Ausführung

### Voraussetzungen

- Linux
- CMake >= 3.16
- C++20-kompatibler Compiler (z. B. GCC 11+, Clang 14+)

### Build

```bash
cmake -S . -B build
cmake --build build
```

### Beispielprogramm ausführen

```bash
./build/fusionanns
```

Beispielausgabe (kann je nach Datensatz variieren):

```text
Query nearest neighbors (k=2):
  rank 1: index #0
  rank 2: index #3
```

### Tests ausführen

```bash
ctest --test-dir build --output-on-failure
```

Oder direkt:

```bash
./build/fusionanns_basic_test
```

## CMake-Targets

- `fusionanns_core`: statische Core-Library mit Vector/Distance/FlatIndex
- `fusionanns`: Beispiel-Executable
- `fusionanns_basic_test`: Minimaltest

## Minimales API-Beispiel

```cpp
#include <vector>
#include "fusionanns/index.h"
#include "fusionanns/vector.h"

int main() {
    auto index = fusionanns::make_flat_index();
    index->add(fusionanns::Vector(std::vector<float>{1.0F, 0.0F}));
    index->add(fusionanns::Vector(std::vector<float>{0.0F, 1.0F}));

    std::vector<std::size_t> results;
    const auto found = index->search(
        fusionanns::Vector(std::vector<float>{0.9F, 0.1F}),
        1,
        results
    );
    return found == 1 ? 0 : 1;
}
```

## Designprinzipien

- kleine, verständliche API statt frühem Overengineering
- minimale Abhängigkeiten (nur C++-Standardbibliothek)
- klare Erweiterbarkeit über das `Index`-Interface
- zuerst Korrektheit und Lesbarkeit, dann Optimierung

## Bekannte Grenzen des MVP

- Kein echter ANN-Algorithmus, nur lineare Suche
- Keine Persistenz (Index wird nicht gespeichert/geladen)
- Keine Batch-Search oder parallele Query-Verarbeitung
- Keine Metrik-Abstraktion im Index (FlatIndex nutzt fest L2)
- Kein separates Test-Framework (nur `assert`-basierter Test)

## Nächste sinnvolle Schritte

- zusätzliche Index-Implementierung (z. B. HNSW-Prototyp)
- Benchmark-CLI mit reproduzierbaren Datensätzen
- sauberere Trennung zwischen Distanzmetrik und Indexlogik
- Unit-Tests mit Testframework (z. B. Catch2 oder GoogleTest)
- optional OpenMP/SIMD-Pfade für Performance-Experimente

## Entwicklungsregeln

- keine Änderungen außerhalb dieses Repositories
- kleine, reviewbare Commits
- Fokus auf nachvollziehbare, wartbare Implementierung
