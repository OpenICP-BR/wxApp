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

1. Baixe o arquivo [OpenICP-BR.dmg][RELEASES].
2. Abra-o e arraste o app para a pasta `Aplicativos`.
3. Pronto!

### Windows
em breve

### Linux

*Arch Linux:*

1. Instale pelo AUR: `pacaur -S openicp-br-git`.

*Outras distribuições Linux:*

Siga as instruções de compilação.

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