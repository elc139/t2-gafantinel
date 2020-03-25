# Pthreads
### 1. Explique como se encontram implementadas as 4 etapas de projeto: particionamento, comunicação, aglomeração, mapeamento (use trechos de código para ilustrar a explicação).

### 2. Considerando o tempo (em microssegundos) mostrado na saída do programa, qual foi a aceleração (speedup) com o uso de threads?

Considerando os resultados obtidos:

```
./pthreads_dotprod 1 1000000 2000 
10000.000000
1 thread(s), 6978713 usec

./pthreads_dotprod 2 500000 2000  
10000.000000
2 thread(s), 3789415 usec
```
E considerando que a aceleração(speedup) pode ser obtido através da Lei de Amdahl, temos que:
```
6978713/3789415 = 1,8416
```

### 3. A aceleração se sustenta para outros tamanhos de vetores, números de threads e repetições? Para responder a essa questão,você terá que realizar diversas execuções, variando o tamanho do problema (tamanho dos vetores e número de repetições) e o número de threads (1, 2, 4, 8..., dependendo do número de núcleos). Cada caso deve ser executado várias vezes, para depois calcular-se um tempo de processamento médio para cada caso. Atenção aos fatores que podem interferir na confiabilidade da medição: uso compartilhado do computador, tempos muito pequenos, etc.

Para responder a questão, foi implementado o seguinte script:
```
#!/bin/bash
echo '~~~~~~ START ~~~~~~'
for i in $(seq 1 10); do threads=1; for i in $(seq 1 8); do ./pthreads_dotprod $threads $((1000000/$threads)) 2000 | grep 'thread'; echo ''; threads=$(($threads+1)); done; done
echo '~~~~~~ END ~~~~~~'
echo ''
```
O script executa o programa pthreads_dotprod com um incremento de 1 thread por execução até 8 threads em 10 iterações, totalizando 80 execuções.

Notou-se que a aceleração se sustentou ao longo dos experimentos, obtendo ganho de desempenho acentuado a partir de 2 threads (1,8x de aceleração)em relação ao caso base até atingir um plateau derca de 2,2x de aceleração com 6, 7 e 8 threads.
### 4. Elabore um gráfico/tabela de aceleração a partir dos dados obtidos no exercício anterior.

![](pthreads_dotprod/grafico.png)

A tabela completa pode ser conferida em ```tabela.ods```

### 5. Explique as diferenças entre pthreads_dotprod.c e pthreads_dotprod2.c. Com as linhas removidas, o programa está correto?

O programa ```pthreads_dotprod.c``` tem o cuidado de executar as operações de soma com o auxílio de um mutex, o que garante que o resultado da operação será correto, independente da velocidade em que cada thread é executada. O programa ```pthreads_dotprod2.c```, por sua vez, tem as linhas correspondentes ao mutex removidas, o que pode acarretar uma condição de corrida no programa, já que as threads são executadas desordenadamente e podem vir a retornar um output diferente do esperado.
# OpenMP

## Referências

https://pt.wikipedia.org/wiki/Lei_de_Amdahl