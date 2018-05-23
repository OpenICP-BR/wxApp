# OpenICP-BR
*Read this in other languages: [English](README.md), [Português (Brasil)](README.pt-BR.md).*

<h1 align="center">
  <br>
  <img src="https://github.com/gjvnq/OpenICP-BR/blob/master/res/logo-512.png" alt="OpenICP-BR logo" width="160">
</h1>

<h4 align="center">An opensource GUI tool for digital sigatures that are legally valid in Brazil (standard: <a href="http://www.iti.gov.br/icp-brasil" target="_blank">ICP-Brasil</a>).</h4>

OpenICP-BR is a cross-platform (Linux, macOS, Windows) desktop app for signing documents as well as verifying the sigunatures acording to the <a href="http://www.iti.gov.br/icp-brasil" target="_blank">ICP-Brasil</a> (Brazilian Publick Key Infrastructure).

## Installation
[RELEASES]: https://github.com/gjvnq/OpenICP-BR/releases

### OS X

1. Download [OpenICP-BR.dmg][RELEASES].
2. Open and drag the app into the `Applications` folder.
3. Done!

### Windows
coming soon

### Linux

*Arch Linux:*

1. Install it from AUR: `pacaur -S openicp-br-git`.

*Other linux distributions:*

Follow compilation instructions.

## Compilation (for developers)

Follow these instructions:

  * [Linux 64bit](COMPILE.linux.arch.64bit.md)
  * [macOS](COMPILE.macOS.md)
  * [Windows](COMPILE.win.md)

## Features

- [x] Add certificates
- [x] Sign documents
- [ ] Verify signatures
- [ ] Check CRL (Certificate Revocation List)
- [ ] Support certificates in smart cards
- [ ] Auto updates

## Built with
- [wxWidgets](https://wxwidgets.org)
- [OpenSSL](https://www.openssl.org)

## License

[AGPL - Affero GNU Public License](https://www.gnu.org/licenses/agpl-3.0.en.html)