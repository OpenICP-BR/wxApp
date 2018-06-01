# OpenICP-BR
*Read this in other languages: [English](README.md), [Português (Brasil)](README.pt-BR.md).*

<h1 align="center">
  <br>
  <img src="https://github.com/gjvnq/OpenICP-BR/blob/master/res/logo-512.png" alt="OpenICP-BR logo" width="160">
</h1>

<h4 align="center">Uma ferramenta de código aberto para assinaturas digitais legalmente válidas (ICP-Brasil).</h4>

O OpenICP-BR é um aplicativo multiplataforma (Linux, macOS, Windows) para a área/mesa de trabalho para assinar e verificar assinaturas digitais de arcordo com o <a href="http://www.iti.gov.br/icp-brasil" target="_blank">ICP-Brasil</a> (Infraestrutura de Chaves Públicas Brasileira).

## Instalação
[RELEASES]: https://github.com/gjvnq/OpenICP-BR/releases

### OS X

1. Baixe o arquivo [OpenICP-BR-v0.2.1.dmg][RELEASES].
2. Abra-o e arraste o app para a pasta `Aplicativos`.
3. Pronto!

### Windows

1. Baixe o arquivo [Instalador-OpenICP-BR-v0.2.1.exe][RELEASES].
2. Execute-o.
3. Siga as instruções do instalador.
4. Pronto!

OBS: Não é necessária permissão de administrador para instalar a versão para Windows, já que esta *não* instala em `C:\Arquivos de Programas (x86)`, mas sim em `C:\Usuários\Meu Usuário\AppData\Local`.

### Linux

*Arch Linux:*

1. Instale pelo AUR: `pacaur -S openicp-br-git`.

OU

1. Baixe o arquivo [OpenICP-BR-v0.2.1.pkg.tar.gz][RELEASES].
2. Instale-o: `sudo pacman -U OpenICP-BR-v0.2.1.pkg.tar.gz`.

*Outras distribuições Linux:*

1. Baixe o arquivo [OpenICP-BR-v0.2.1.tar.gz][RELEASES].
2. Verifique se o [wxWidgets](https://wxwidgets.org) está instalado.
3. Extaria-o no diretório raíz: `sudo tar xvf OpenICP-BR-v0.2.1.tar.gz -C /`.

## Compilação (para desenvolvedores)

Siga essas instruções:

  * [Linux 64 bits](COMPILE.linux.arch.64bit.md)
  * [macOS](COMPILE.macOS.md)
  * [Windows](COMPILE.win.md)

## Recursos

- [x] Adicionar certificados
- [x] Assinar documentos
- [ ] Verificar assinaturas
- [ ] Checar as CRLs (Listas de Certificados Revogados)
- [ ] Suportar certificados em smartcards
- [ ] Atualizações automáticas

## Feito com
- [wxWidgets](https://wxwidgets.org)
- [OpenSSL](https://www.openssl.org)

## Licença

[AGPL - Licença Pública Geral Affero GNU](http://licencas.softwarelivre.org/agpl-3.0.pt-br.html)