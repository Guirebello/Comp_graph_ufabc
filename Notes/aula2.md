# Instalação OpenGl + GLFW

Video seguido:  <https://www.youtube.com/watch?v=LwaYz46Nl8g>

- baixe os pre compiled binaries: <https://www.glfw.org/download.html>
- Crie um diretorio e um arquivo main.cpp no vscode com o codigo de exemplo:  <https://www.glfw.org/documentation.html>
- Dentro dos binaries do glfw baixados, pegue as pastas include e lib-mingw-w64 e cole elas dentro do diretorio onde esta o projeto de exemplo (o main.cpp)
- Após isto, execute os comandos abaixo

#### Compilar
```
g++ -Wall -Iinclude -g main.cpp -o main.exe -Llib-mingw-w64 -lglfw3 -lgdi32 -lopengl32
```
#### executar
```
./main
```


# Tarefa pra casa

- Configurar GLUT no windows/VS Code (vale ponto)
