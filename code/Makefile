# Nom du programme
SERVEUR_TARGET = ../serveur.exe
CLIENT_TARGET = ../client.exe

# Compilateur , ici celui pour le c++
CC = g++

# Options de compilation
CFLAGS = -Wall -Wextra -std=c++17

# Chemin vers les bibliothèques SFML et les drapeaux de compilation
SFML_INCLUDE = -I/usr/local/include
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

# Fichiers source
SERVEUR_SRCS = serveur.cpp interface/Menu.cpp interface/TableauDesScores.cpp interface/GameOver.cpp interface/GameOverMulti.cpp global_variables.cpp Animation.cpp objet/Entite.cpp objet/asteroide.cpp objet/tir.cpp objet/player.cpp # Ajoutez ici tous les fichiers source de votre projet
CLIENT_SRCS = client.cpp interface/Menu.cpp interface/TableauDesScores.cpp interface/GameOver.cpp interface/GameOverMulti.cpp global_variables.cpp Animation.cpp objet/Entite.cpp objet/asteroide.cpp objet/tir.cpp objet/player.cpp # Ajoutez ici tous les fichiers source de votre projet

# Règle de construction du serveur
$(SERVEUR_TARGET): $(SERVEUR_SRCS)
	$(CC) $(CFLAGS) $(SFML_INCLUDE) $^ -o $@ $(SFML_LIBS)

# Règle de construction du client
$(CLIENT_TARGET): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(SFML_INCLUDE) $^ -o $@ $(SFML_LIBS)

# Règle pour nettoyer les fichiers temporaires et l'exécutable
clean:
	rm -f $(CLIENT_TARGET) $(SERVEUR_TARGET)all: $(CLIENT_TARGET) $(SERVEUR_TARGET)


all: $(CLIENT_TARGET) $(SERVEUR_TARGET)

client: $(CLIENT_TARGET)

serveur: $(SERVEUR_TARGET)

.PHONY: all client serveur


