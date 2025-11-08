# Instruções para Mover as Texturas

Para organizar as texturas na pasta `/texturas`, você precisa mover os seguintes arquivos:

## Arquivos para mover:

Mova todos estes arquivos para a pasta `texturas/`:

1. `pedra-28.jpg`
2. `madeira.jpg`
3. `metal.jpg`
4. `plastico.jpg`
5. `black.png`
6. `tecido.jpg`
7. `tecido_claro.jpg`
8. `wall.jpg`
9. `floor.jpg`
10. `azulejo.png`
11. `ceramica.jpg`
12. `chao_banheiro.png`
13. `sofa.png`
14. `wood2.jpg`
15. `wood3.png`
16. `colcha.jpg`
17. `wardrobe.jpg`
18. `table.jpg`
19. `bedframe.jpg`

## Como fazer no PowerShell:

```powershell
# Execute este comando na raiz do projeto:
Move-Item *.jpg texturas/
Move-Item *.png texturas/
```

Ou você pode mover manualmente arrastando os arquivos para a pasta `texturas/`.

**Importante:** A pasta `texturas/` já foi criada e o código já foi atualizado para buscar as texturas nela!
