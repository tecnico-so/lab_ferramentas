# Guião 1 (Extra): Ferramentas de Desenvolvimento Avançadas

Este guião contém exercícios extra para que se familiarizem com ferramentas de compilação de C.

## 1. Formatadores de Código

A formatação de código é um assunto contencioso. Código bem formatado é extremamente importante (a maioria do código é lido mais vezes do que é escrito) e uma formatação adequada e uniforme facilita a compreensão. Contudo, o que constitui *formatação adequada* é um tópico que facilmente degenera numa discussão de gosto pessoal e distrai do objetivo principal (o desenvolvimento). Para além disso, é difícil e trabalhoso manter qualquer tipo de formatação de forma consistente, especialmente quando a dimensão do projeto vai aumentando.

Para colmatar este problema, existem formatadores automáticos de código. Por exemplo, em Python existe o [`autopep8`](https://pypi.org/project/autopep8/), em Rust o [`rustfmt`](https://github.com/rust-lang/rustfmt) e em Go o `go fmt`.

Para C (e C++) existe o [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html).

Para correr o clang-format:

```sh
clang-format -i <source_files>
```

Para configurar o estilo de formatação, existe o ficheiro `.clang-format`. O `clang-format` deteta a presença deste ficheiro e utiliza-o como referência. Nos projetos, será fornecido com o código base um ficheiro `.clang-format`, uniformizando assim o estilo a usar.


## 2. Warnings

Como já devem ter experiência noutras UCs, `C` é uma linguagem onde é fácil cometer erros de programação difíceis de compreender. Há vários *pitfalls*, desde erros de memória (*double-free*, *memory-leaks*, *use-after-free*) a conversões implícitas. Para além de impedirem a execução correcta dos programas, podem causar vulnerabilidades de segurança. Para os evitar, é preciso assumir um estilo de programação bastante rígido, consistente e defensivo. Contudo, para auxiliar neste esforço, o compilador tem um conjunto de *warnings*, que avisam quando certos padrões de programação menos corretos (ou mesmo completamente incorretos) são usados.

Estes warnings têm de ser ativados explicitamente. Com a flag `-Werror`, eles são elevados a erros. Ou seja, o compilador interrompe a compilação até o erro ser corrigido. Alguns exemplos de flags:

 - `-Wall`: ativa a maioria dos warnings (ao contrário do que o nome indica, não são todos)
 - `-Wextra`: ativa mais warnings (continuam sem ser todos)
 - `-Wcast-align`: quando é feito um cast que altera os requisitos de alinhamento
 - `-Wconversion`: quando uma conversão pode alterar um valor.
```c
int main() {
    unsigned int x = 2 << 17;
    unsigned short y = x;
    return 0;
}
```

Compilar com `clang -Wconversion test.c` emite um warning com:

```
% clang -Wconversion test.c
test.c:3:24: warning: implicit conversion loses integer precision: 'unsigned int' to 'unsigned short' [-Wimplicit-int-conversion]
    unsigned short y = x;
                   ~   ^
1 warning generated.
```

 - `-Wfloat-equal`: comparar números de floating point para igualdade pode dar resultados impressionantes, na forma de erros espectaculares. Para mais informações [What Every Computer Scientist Should Know About Floating-Point Arithmetic](http://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html)

 - `-Wformat=2`: analiza as format strings de funções tipo `printf`, verificando que os elementos e os descriptores de formatação estão bem colocados.
 - `-Wnull-dereference`: detecta algumas instâncias de derreferências de null pointers.
 - `-Wshadow`: detecta quanto se está a renomear uma variável.
```c
int f(int x) {
    int res = 0;
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < i; j++) {
            int x = i * j;
            res += x;
        }
    }

    return res;
}

int main() {
    f(42);
}
```

Compilar com `clang -Wshadow test.c` emite um warning com:
    
```
% clang -Wshadow test.c
test.c:5:17: warning: declaration shadows a local variable [-Wshadow]
            int x = i * j;
                ^
test.c:1:11: note: previous declaration is here
int f(int x) {
          ^
1 warning generated.

```

 - `-Wsign-conversion`: conversão implícita entre tipos com e sem sinal
 - `-Wswitch-enum`: obriga a que todos os casos possíveis de um `switch` que use um enum sejam utilizados.
     Exemplo:
```c
typedef enum student_status_t {
    PARTY,
    SLEEP,
    EAT,
    STUDY,
} student_status_t;

char const * const status_str(student_status_t status) {
    switch (status) {
        case PARTY: return "party";
        case SLEEP: return "sleep";
        case EAT: return "eat";
    }

    return "oops";
}

int main() {
    if (status_str(PARTY)[0] == 'p') {
        return 0;
    }
    return -1;
}

```

Compilar com `clang -Wswitch-enum test.c` emite um warning com:
    
```
% clang test.c
test.c:9:13: warning: enumeration value 'STUDY' not handled in switch [-Wswitch]
    switch (status) {
            ^
1 warning generated.
```

 - `-Wundef`: avisa quando um valor usado numa macro não está definido
 - `-Wunreachable-code`: avisa quando há código que não é atingível.
     Exemplo:
```c
int f() {
    return 1024;
}
int main() {
    if (42 % 2 == 0) {
        return 42;
    } else {
        return 24;
    }

    f();
    return -1;
}
```

Compilar com `clang -Wunreachable-code test.c` emite um warning com:
    
```
% clang -Wunreachable-code test.c
test.c:11:5: warning: code will never be executed [-Wunreachable-code]
    f();
    ^
1 warning generated.
```

 - `-Wunused`: quando um elemento de código não é utilizado.
```c
int sum(int a, int b) {
    int sum = a + b;
    return a + b;
}

int main() {
    sum(1, 2);
    return 0;
}
```

Compilar com `clang -Wunused test.c` emite um warning com:
    
```
% clang -Wunused test.c
test.c:2:9: warning: unused variable 'sum' [-Wunused-variable]
    int sum = a + b;
        ^
1 warning generated.
```

Se estiverem curiosos, podem consultar a [lista completa de warnings do Clang](https://clang.llvm.org/docs/DiagnosticsReference.html#wundef). É de notar que há warnings que podem não compreender à partida a sua utilidade ou sequer o que estão de facto a fazer. Isto é natural, mas significa que a sua utilização é ainda mais importante: estão a salvaguardar-vos de subtilezas e detalhes da linguagem que não conhecem.

## 3. Makefiles avançados

Como descrito no guião principal, o `make` é uma ferramenta fulcral para acelerar o vosso desenvolvimento de código em `C`. Explora na directoria `extra` o Makefile apresentado. Esta directoria tem uma versão alterada do código da BST presente em `src`. Utiliza o make para corrigir alguns dos erros automaticamente (e.g.: de formatação) e os warnings para encontrar outros bugs.
