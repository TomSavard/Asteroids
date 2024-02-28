# Nom des programmes
CLIENT_TARGET = client.exe
SERVEUR_TARGET = serveur.exe

# Compilateur, ici celui pour le C++
CC = g++

# Options de compilation
CFLAGS = -Wall -Wextra -std=c++17

# Chemin vers les bibliothèques SFML et les drapeaux de compilation
SFML_INCLUDE = -I/usr/local/include
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio

# Fichiers source du client
CLIENT_SRCS = client.cpp

# Fichiers source du serveur
SERVEUR_SRCS = serveur.cpp

# Règle de construction du client
$(CLIENT_TARGET): $(CLIENT_SRCS)
	$(CC) $(CFLAGS) $(SFML_INCLUDE) $^ -o $@ $(SFML_LIBS)

# Règle de construction du serveur
$(SERVEUR_TARGET): $(SERVEUR_SRCS)
	$(CC) $(CFLAGS) $(SFML_INCLUDE) $^ -o $@ $(SFML_LIBS)

# Règle pour nettoyer les fichiers temporaires et les exécutables
clean:
	rm -f $(CLIENT_TARGET) $(SERVEUR_TARGET)

all: $(CLIENT_TARGET) $(SERVEUR_TARGET)

client: $(CLIENT_TARGET)

serveur: $(SERVEUR_TARGET)

.PHONY: all client serveur