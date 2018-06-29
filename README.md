# Paginação de Memória
Crie uma estrutura de dados que represente um sistema de paginação de memória com as seguintes características:
- 512 páginas de 8KB e 256 frames;
- uma tabela de páginas será criada, associando (aleatoriamente) 256 páginas às 256 molduras disponíveis;
- representação de endereços virtuais e reais na notação binária, separados na forma de tuplas número da página/descolamento e número da moldura/deslocamento, respectivamente 9+13 bits e 8+13 bits;
- endereços deverão ser tratados na forma de Bytes;
  - ex.: página 1 mapeada na moldura 0
    - EV [9000] (pág. nr. 1, deslocamento de 808B = 000000001 0001100101000)
    - ER [808] (moldura nr. 0, deslocamento de 808B = 00000000 0001100101000)
- os processos podem "acessar" 4MB e o sistema disponibiliza 2MB de memória física.
Após:
- uma entrada será fornecida definindo a quantidade de endereços (N);
- em seguida, serão criados N endereços aleatórios (EV) entre 0 e 4194303;
- como saída, fornecerá a localização na tabela de páginas na forma nr. da página/deslocamento em decimal e binário e o respectivo endereço físico (ER) na forma nr.da moldura/deslocamento em decimal e binário, quando houver. Caso contrário, informar que houve PF.
- sumarizar a taxa de acertos (hit ratio) e a taxa de page faults (miss ratio).
