# Nom du programme
TARGET = main.exe

# Compilateur , ici celui pour le c++
CC = g++

# Options de compilation
CFLAGS = -Wall -Wextra -std=c++17

# Chemin vers les bibliothèques SFML et les drapeaux de compilation
SFML_INCLUDE = -I/usr/local/include
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

# Fichiers source
SRCS = code/main.cpp code/interface/Menu.cpp code/interface/TableauDesScores.cpp code/interface/GameOver.cpp code/global_variables.cpp # Ajoutez ici tous les fichiers source de votre projet

# Règle de construction du programme
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(SFML_INCLUDE) $^ -o $@ $(SFML_LIBS)

# Règle pour nettoyer les fichiers temporaires et l'exécutable
clean:
	rm -f $(TARGET)
