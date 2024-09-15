# Lista de contatos distribuída

Projeto que visa criar uma lista de contatos distribuida, ou seja, replicada em diversos servidores.


## Ideas:

1. Usar própria conexão para designar os outros servers
    - Ou seja, ao se conectar com um servidor válido, caso algum outro servidor esteja online, ele deverá avisar aos outros e os outros servidores avisarão aos clientes conectados que há outro servidor disponível.
    - Ter algo como "possiblyAliveServer: List<Server>"
2. Ou ter três servidores conhecidos e tentar de um a um?
3. Usar proxies em `/etc/hosts`? Sendo assim, sempre teriamos um server especifico que seria o discovery de serviços, onde os demais iriam se cadastrar e o client iria pedir um server. 
    - Create an entry in hosts to simulate an online server: `sudo bash -c 'echo "127.0.0.1 contact-server" >> /etc/hosts'`
    - Then make a request: `curl -XGET http://contact-server:8000/`
