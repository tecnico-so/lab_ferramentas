# Guião Ferramentas de Desenvolvimento

![IST](img/IST_DEI.png)  

## Objectivos

No final deste guião, deverá ser capaz de:

- Estar familiarizado com o ambiente UNIX.
- Utilizar a ferramenta `make` para gerar software.

## 1 - Contacto com o ambiente UNIX

1. Crie um diretório no seu computador e descarregue o arquivo `bst.zip` (binary search tree) que está disponível na página da disciplina (no fénix), na secção “Laboratórios”. Para extrair os ficheiros contidos no arquivo, use o comando:

```sh
unzip bst.zip
```

2. Relembre o que fazem os comandos básicos como, por exemplo, `cd`, `ls`, `cat`, `cp`, `mv`, `rm`, `mkdir` e `rmdir`.
Recorde também que a generalidade dos comandos aceitam *switches* (também chamados
argumentos, opções ou *flags*) que modificam o seu comportamento. Compare, por exemplo, o
comportamento do comando `ls`, sem argumentos, com o comando `ls -l`.

Na secção seguinte detalha-se como pode obter ajuda ou informações sobre um certo comando em
ambientes UNIX.

## 2 - Utilização do manual

1. Pode aceder a informação detalhada sobre comandos de sistema, programas e funções da linguagem C, usando o comando `man` (abreviatura de "manual"), sob a forma das chamadas *manpages*.

Por exemplo, para se informar sobre o uso do próprio comando `man` deve escrever:
```sh
man man
```

Para navegar nas páginas do manual podem ser usadas as setas do teclado e as teclas “PageUp” e
“PageDown”. Para sair do manual basta pressionar a tecla `q`.


2. O manual encontra-se organizado em secções numeradas de 1 a 9. Para a cadeira de Sistemas
Operativos, as secções mais relevantes são:

- Secção 1: comandos/utilidades da *shell*
- Secção 2: chamadas de sistema
- Secção 3: funções de bibliotecas (e.g., a biblioteca do C)

Isto é relevante pois existem comandos/funções com o mesmo nome que têm propósito e funcionamento diferentes.

Por exemplo, isso observa-se para o comando `printf` que está na secção 1 e a função `printf` da linguagem C que está na secção 3. Ao invocar o manual, pode especificar a que secção pretende aceder, indicando o seu número antes do nome. Experimente os seguintes comandos:
```sh
man printf
man 3 printf
```


3. O manual também contém informação sobre programas/ferramentas. Por exemplo, para
consultar a *manpage* do comando `zip`:
```sh
man zip
```

Outra forma de obter informação recorre directamente aos programas/ferramentas e ao uso
do *switch* `--help`, que é geralmente suportado:
```sh
zip --help
```

Experimente também usar o *switch* `--help` ou consultar a manpage dos seguintes programas: `gdb`, `gcc` e `make`[^footnote1].

[^footnote1]: No caso de programas como o (GNU) `make`, a sua documentação completa está apenas disponível como um manual *Texinfo*, acessível pelo comando `info`. Se quiser saber, por exemplo, como escrever um *Makefile*, a *manpage* do `make` recomenda consultar o manual completo com `info make`.


4. O uso do manual é especialmente útil para obter informação sobre as funções do C e identificar os valores devolvidos – notar a secção `RETURN VALUE`. Este aspeto é muito importante, pois nenhum programa deve chamar uma função e, no retorno, ignorar se ocorreu alguma situação de erro durante a execução da função. Como regra, antes de usar uma função, os alunos devem estudar nas *manpages*  as diversas situações de erro que podem ocorrer e assegurar que o
programa as trata devidamente (analisando o retorno da função).

## 3 - Redireção dos canais de entrada/saída
1. Em ambientes UNIX, cada processo tem três canais fundamentais de entrada/saída: *stdin*, *stdout* e *stderr*.

- O *stdin* (“standard input”) representa o dispositivo de entrada de um programa - tipicamente o teclado;
- O *stdout* (“standard output”) representa o dispositivo de saída – tipicamente o terminal;
- O *stderr* (“standard error”) representa um dispositivo alternativo de saída para mensagens de erro, que, por defeito, é o mesmo dispositivo que o *stdout*.

2. É possível redirecionar qualquer um destes dispositivos para ficheiros usando redirection operators (`<`, `>`, `&>`, `>>`, ... ). Experimente executar os seguintes comandos, examinando o conteúdo da diretoria atual, e dos ficheiros referidos, após cada um deles:
```sh
echo Hello World
echo Hello World > my_stdout.txt
echo Hello again >> my_stdout.txt
echo Goodbye > my_stdout.txt
cat my_stdout.txt nonexistent_file 2> my_stderr.txt
cat my_stdout.txt nonexistent_file &> my_stdout_and_stderr.txt
cat < my_stdout.txt
```

**NOTA**: As sintaxes apresentadas em cima representam apenas alguns exemplos. Durante as aulas teóricas serão descritas formas mais genéricas de redirecionar os canais de Entrada/Saída dos processos Unix. No entanto, podem encontrar já detalhes sobre os *redirection operators* na secção `REDIRECTION` da *manpage* do *bash* (`man bash`) ou pesquisar informação na Internet.

3. É também possível redirecionar o *stdout* de um comando para o *stdin* de outro, criando assim uma cadeia de comandos para processar informação. Por exemplo, a seguinte cadeia de comandos lê o conteúdo do ficheiro `/etc/passwd`, filtra as linhas que contenham a palavra *root* e imprime a 7ª coluna (colunas separadas pelo caracter ‘:’) de cada linha:

```sh
cat /etc/passwd | grep root | cut -d : -f 7
```

Estas redireções são feitas com recurso a *pipes*, conceito que será abordado mais a fundo durante as aulas teóricas.


## Conclusão

...

## Agradecimentos

- ...
