# Lista de contatos distribuída

## Ideas:

1. Usar própria conexão para designar os outros servers
  - Ou seja, ao se conectar com um servidor válido, caso algum outro servidor esteja online, ele deverá avisar aos outros e os outros servidores avisarão aos clientes conectados que há outro servidor disponível.
  - Ter algo como "possiblyAliveServer: List<Server>"
2. Usar proxies em `/etc/hosts`? Sendo assim, sempre teriamos um server especifico que seria o discovery de serviços, onde os demais iriam se cadastrar e o client iria pedir um server. 
3. Ou ter três servidores conhecidos e tentar de um a um?
