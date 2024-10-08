# Lista de contatos distribuída

Projeto que visa criar uma lista de contatos distribuida, ou seja, replicada em diversos servidores.

## Tech Stack

- Frontend using C++ and QT.

## Ideias:

1. Usar própria conexão para designar os outros servers
    - Ou seja, ao se conectar com um servidor válido, caso algum outro servidor esteja online, ele deverá avisar aos outros e os outros servidores avisarão aos clientes conectados que há outro servidor disponível.
    - Ter algo como `possiblyAliveServer: List<Server>`
2. Ou ter três servidores conhecidos e tentar de um a um?
3. Usar proxies em `/etc/hosts`? Sendo assim, sempre teriamos um server especifico que seria o discovery de serviços, onde os demais iriam se cadastrar e o client iria pedir um server. 
    - Create an entry in hosts to simulate an online server: `sudo bash -c 'echo "127.0.0.1 contact-server" >> /etc/hosts'`
    - Then make a request: `curl -XGET http://contact-server:8000/`

## Solução escolhida (MVP):

### Conexão 
- TODO: Pesquisar sobre relógios de Lamport ou relógio vetorial para solucionar o problema de sincronização.
  - Maybe we can use the logical clock to match updates and creation.
  - The data is saved with the logical clock to that extent.
  - Test it with slow internet.
  - See [this article](https://lamport.azurewebsites.net/pubs/time-clocks.pdf), [Wikipedia](https://pt.wikipedia.org/wiki/Rel%C3%B3gios_de_Lamport) and [UFRN site](https://dimap.ufrn.br/~thais/SD20041/SincronizacaoDist.pdf). 
- Parece que o professor quer um _nameserver_... Posso usar um e direcionar os dados para ele... Posso também usar o próprio nameserver do linux?
  - De inicio iremos usar o servidor nativo de hosts do Linux, depois podemos usar um servidor central para ser como um "service discovery", ou "Service Regsitry. Ver [link](https://fullcycle.com.br/entenda-como-funciona-o-service-discovery/).
  - Para isso, adicionaremos:
      - `sudo bash -c 'echo "127.0.0.1 contact-server-1" >> /etc/hosts'`
      - `sudo bash -c 'echo "127.0.0.1 contact-server-2" >> /etc/hosts'`
      - `sudo bash -c 'echo "127.0.0.1 contact-server-3" >> /etc/hosts'`

1. O cliente deve conhecer um dos três servidores, ao conectar-se nele, receberá os endereços de outros possíveis servidores, caso esse venha a cair.
    - 1.1. Esse caso poderia também ser solucionado de forma melhor usando um _nameserver_. Um servidor que redirecionaria os clientes para os servidores "vivos".
2. Servidores manterão uma conexão aberta um com o outro, mantendo-os vivos por um _heartbeat_ com datas.
    - 2.1. Novamente, seria melhor ter um _nameserver_ para poder saber por onde se conectar aos outros dois servidores, pois estes iriam se cadastrar no _nameserver_ principal
3. Quando um servidor cair, os outros servidores saberão de sua "queda", avisando aos seus clientes que estes servidores não estão mais online.
4. O cliente que perder a conexão, deverá ir à outro servidor para poder fazer suas operações.

### Cadastro/Atualização de Contato
Dado que o cliente esteja conectado à um servidor válido.

1. Toda vez que o cliente cadastrar ou atualizar um contato em um servidor, o servidor deverá atualizar os outros servidores da mudança do contato (PS: Ver sincronismo).
2. Quando um servidor ficar online, ou um que estava "caído" subir, ele deverá pedir atualizações de contato desde a hora em que ele caiu (Para isso salvar data e hora na agenda).
    * Ou então apenas manter em memória e pegar uma cópia completa de todos os dados.
3. Ver também sobre: Atualização usando relógio vetoriais.
