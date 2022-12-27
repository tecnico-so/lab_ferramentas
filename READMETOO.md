# Guião extra sobre ferramentas de desenvolvimento avançadas

Este guião contém exercícios extra para que se familiarizem com ferramentas de compilação de C.

## 1. _Makefiles_ avançados

Como descrito no guião principal, o `make` é uma ferramenta fulcral para acelerar o desenvolvimento de código em `C`.
Explore na directoria [`extra`](extra/) o `Makefile` apresentado.
Esta diretoria tem uma versão alterada do código da BST presente em [`src`](src/).

Utilize o `make` para corrigir alguns dos erros automaticamente, como por exemplo, erros de formatação.
Use os _warnings_ para encontrar outros _bugs_.

## 2. Avisos (_Warnings_)

Como já devem ter experiência noutras cadeiras, o `C` é uma linguagem onde é fácil cometer erros de programação difíceis de compreender.
Há vários _pitfalls_, desde erros de memória (_double-free_, _memory-leaks_, _use-after-free_) a conversões implícitas.
Para além de impedirem a execução correta dos programas, podem causar vulnerabilidades de segurança.
Para os evitar, é preciso assumir um estilo de programação bastante rígido, consistente e defensivo.
Contudo, para auxiliar neste esforço, o compilador tem um conjunto de _warnings_, que avisam quando certos padrões de programação menos corretos (ou mesmo completamente incorretos) são usados.

Estes _warnings_ têm de ser ativados explicitamente.
Com a _flag_ `-Werror`, eles são elevados a erros, ou seja, o compilador interrompe a compilação até o erro ser corrigido.
Seguem-se alguns exemplos de _flags_ que podem ser usadas:

- `-Wall`: ativa a maioria dos _warnings_ (ao contrário do que o nome indica, não são todos);
- `-Wextra`: ativa mais _warnings_ (continuam sem ser todos);
- `-Wcast-align`: quando é feito um _cast_ que altera os requisitos de alinhamento;
- `-Wconversion`: quando uma conversão pode alterar um valor.

```c
int main() {
    unsigned int x = 2 << 17;
    unsigned short y = x;
    return 0;
}
```

Compilar com `clang -Wconversion test.c` emite um _warning_ com:

```sh
% clang -Wconversion test.c
test.c:3:24: warning: implicit conversion loses integer precision: 'unsigned int' to 'unsigned short' [-Wimplicit-int-conversion]
    unsigned short y = x;
                   ~   ^
1 warning generated.
```

- `-Wfloat-equal`: comparar números de vírgula flutuante (_floating point_) para testar a igualdade pode dar resultados diferentes do esperado.
Para mais informações, leia o seguinte artigo: [_What Every Computer Scientist Should Know About Floating-Point Arithmetic_](http://docs.oracle.com/cd/E19957-01/806-3568/ncg_goldberg.html).
Alguns erros são impressionantes ou mesmo espetaculares.

- `-Wformat=2`: analiza as _format strings_ de funções tipo `printf`, verificando que os elementos e os descriptores de formatação estão bem colocados;
- `-Wnull-dereference`: detecta algumas instâncias de derreferências de *null pointers*;
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

Compilar com `clang -Wshadow test.c` emite um aviso com:

```sh
% clang -Wshadow test.c
test.c:5:17: warning: declaration shadows a local variable [-Wshadow]
            int x = i * j;
                ^
test.c:1:11: note: previous declaration is here
int f(int x) {
          ^
1 warning generated.

```

- `-Wsign-conversion`: conversão implícita entre tipos com e sem sinal;
- `-Wswitch-enum`: obriga a que todos os casos possíveis de um `switch` que use um enum sejam utilizados.
Por exemplo:

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

Compilar com `clang -Wswitch-enum test.c` emite um aviso com:

```sh
% clang test.c
test.c:9:13: warning: enumeration value 'STUDY' not handled in switch [-Wswitch]
    switch (status) {
            ^
1 warning generated.
```

- `-Wundef`: avisa quando um valor usado numa _macro_ não está definido;
- `-Wunreachable-code`: avisa quando há código que não é atingível.
Por exemplo:

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

Compilar com `clang -Wunreachable-code test.c` emite um _warning_ com:

```sh
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

Compilar com `clang -Wunused test.c` emite um aviso com:

```sh
% clang -Wunused test.c
test.c:2:9: warning: unused variable 'sum' [-Wunused-variable]
    int sum = a + b;
        ^
1 warning generated.
```

Se tiver curiosidade, pode consultar a [lista completa de *warnings* do `clang`](https://clang.llvm.org/docs/DiagnosticsReference.html#wundef).
É de notar que há avisos que podem não se compreender à partida a sua utilidade ou sequer o que estão de facto a fazer.
Isto é natural, mas significa que a sua utilização é ainda mais importante: estão a salvaguardar-vos de subtilezas e detalhes da linguagem que podemos não conhecer.

<!-- "Quem te avisa, teu amigo é!" -- Provérbio Popular Português -->

## 3. Formatadores de Código

A formatação de código é um assunto contencioso.
O código bem formatado é extremamente importante (a maioria do código é lido mais vezes do que é escrito) e uma formatação adequada e uniforme facilita a compreensão.
Contudo, o que constitui _formatação adequada_ é um tópico que facilmente degenera numa discussão de gosto pessoal e distrai do objetivo principal (o desenvolvimento).
Para além disso, é difícil e trabalhoso manter qualquer tipo de formatação de forma consistente, especialmente quando a dimensão do projeto vai aumentando.

Para colmatar este problema, existem formatadores automáticos de código.
Por exemplo, em Python existe o [`autopep8`](https://pypi.org/project/autopep8/), em Rust o [`rustfmt`](https://github.com/rust-lang/rustfmt) e em Go o `go fmt`.  
Para C (e C++) existe o [`clang-format`](https://clang.llvm.org/docs/ClangFormat.html).

Para correr o `clang-format`, usar o comando:

```sh
clang-format -i <source_files>
```

Para configurar o estilo de formatação, existe o ficheiro `.clang-format`.
O comando `clang-format` deteta a presença deste ficheiro e utiliza-o como referência.
Nos projetos, será fornecido com o código base um ficheiro `.clang-format` para uniformizar o estilo a usar.

----

Contactos para sugestões/correções: [LEIC-Alameda](mailto:leic-so-alameda@disciplinas.tecnico.ulisboa.pt), [LEIC-Tagus](mailto:leic-so-tagus@disciplinas.tecnico.ulisboa.pt), [LETI](mailto:leti-so-tagus@disciplinas.tecnico.ulisboa.pt)
